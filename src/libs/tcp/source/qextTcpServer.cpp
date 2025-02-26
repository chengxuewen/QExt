#include <private/qextTcpServer_p.h>
#include <qextTcpFactory.h>
#include <qextTcpTaskPool.h>
#include <qextTcpPacketParser.h>

#include <QTcpSocket>
#include <QDateTime>
#include <QThread>

QExtTcpServerPrivate::QExtTcpServerPrivate(QExtTcpServer *q)
    : q_ptr(q)
{
    m_maxSocketConnectionCount = 16;
    m_maxTaskThreadCount = 8;
}

QExtTcpServerPrivate::~QExtTcpServerPrivate()
{
    Q_Q(QExtTcpServer);
    QMutexLocker mutexLocker(&m_socketMutex);
    QSet<QSharedPointer<QExtTcpSocket> >::iterator iter;
    for (iter = m_allTcpSocketSet.begin(); iter != m_allTcpSocketSet.end(); ++iter)
    {
        (*iter)->disconnect(q);
        (*iter)->abort();
        m_socketWorkThreadQueue.enqueue((*iter)->detachWorkThread());
    }
    m_allTcpSocketSet.clear();

    QQueue<QSharedPointer<QThread> >::iterator queueIter;
    for (queueIter = m_socketWorkThreadQueue.begin(); queueIter < m_socketWorkThreadQueue.end(); ++queueIter)
    {
        (*queueIter)->quit();
        (*queueIter)->wait();
    }
    m_socketWorkThreadQueue.clear();

    m_idToTcpSocketMap.clear();
    m_idToTcpPacketDispatcher.clear();
}

void QExtTcpServerPrivate::initServer()
{
    Q_Q(QExtTcpServer);
    qRegisterMetaType<QExtSocketDescriptor>("QExtSocketDescriptor");
    qRegisterMetaType<QAbstractSocket::SocketError>("QAbstractSocket::SocketError");
    qRegisterMetaType<QExtTcpSocket::TransferErrorType>("QExtTcpSocket::TransferErrorType");
}


QExtTcpServer::QExtTcpServer()
    : QTcpServer(QEXT_NULLPTR), dd_ptr(new QExtTcpServerPrivate(this))
{
    Q_D(QExtTcpServer);
    d->initServer();
    this->setTcpFactory(QSharedPointer<QExtTcpFactory>(new QExtTcpFactory));
}

QExtTcpServer::QExtTcpServer(const QSharedPointer<QExtTcpFactory> &tcpFactory)
    : QTcpServer(QEXT_NULLPTR), dd_ptr(new QExtTcpServerPrivate(this))
{
    Q_D(QExtTcpServer);
    d->initServer();
    this->setTcpFactory(tcpFactory);
}

QExtTcpServer::QExtTcpServer(QExtTcpServerPrivate *d)
    : QTcpServer(QEXT_NULLPTR), dd_ptr(d)
{
    dd_ptr->initServer();
    this->setTcpFactory(QSharedPointer<QExtTcpFactory>(new QExtTcpFactory));
}

QExtTcpServer::QExtTcpServer(QExtTcpServerPrivate *d, const QSharedPointer<QExtTcpFactory> &tcpFactory)
    : QTcpServer(QEXT_NULLPTR), dd_ptr(d)
{
    dd_ptr->initServer();
    this->setTcpFactory(tcpFactory);
}

QExtTcpServer::~QExtTcpServer()
{

}

size_t QExtTcpServer::allSocketCount() const
{
    Q_D(const QExtTcpServer);
    QMutexLocker mutexLocker(&d->m_socketMutex);
    return d->m_allTcpSocketSet.size();
}

size_t QExtTcpServer::maxSocketConnectionCount() const
{
    Q_D(const QExtTcpServer);
    QMutexLocker mutexLocker(&d->m_socketMutex);
    return d->m_maxSocketConnectionCount;
}

void QExtTcpServer::setMaxSocketConnectionCount(size_t count)
{
    Q_D(QExtTcpServer);
    QMutexLocker mutexLocker(&d->m_socketMutex);
    d->m_maxSocketConnectionCount = count;
    /*close listen if connected socket equal to max count*/
    if (d->m_allTcpSocketSet.size() >= d->m_maxSocketConnectionCount)
    {
        d->m_address = this->serverAddress();
        d->m_port = this->serverPort();
        this->close();
    }
}

size_t QExtTcpServer::maxTaskThreadCount() const
{
    Q_D(const QExtTcpServer);
    QMutexLocker mutexLocker(&d->m_socketMutex);
    return d->m_maxTaskThreadCount;
}

void QExtTcpServer::setMaxTaskThreadCount(size_t count)
{
    Q_D(QExtTcpServer);
    QMutexLocker mutexLocker(&d->m_socketMutex);
    d->m_maxTaskThreadCount = count;
    QMap<QExtTag, QSharedPointer<QExtTcpPacketDispatcher> >::iterator iter;
    for (iter = d->m_idToTcpPacketDispatcher.begin(); iter != d->m_idToTcpPacketDispatcher.end(); ++iter)
    {
        (*iter)->taskPool()->threadPool()->setMaxThreadCount(count);
    }
}

void QExtTcpServer::runTask(int function)
{
    Q_D(QExtTcpServer);
    QMutexLocker mutexLocker(&d->m_socketMutex);
    if (!d->m_tcpFactory.isNull())
    {
        QMap<QExtTag, QSharedPointer<QExtTcpPacketDispatcher> >::iterator iter;
        for (iter = d->m_idToTcpPacketDispatcher.begin(); iter != d->m_idToTcpPacketDispatcher.end(); ++iter)
        {
            QExtTcpTask *task = d->m_tcpFactory->createTask((*iter), function);
            if (task)
            {
                (*iter)->taskPool()->enqueueTask(task);
            }
        }
    }
}

void QExtTcpServer::runTask(QExtTcpTask *task)
{
    Q_D(QExtTcpServer);
    QMutexLocker mutexLocker(&d->m_socketMutex);
    if (!d->m_tcpFactory.isNull())
    {
        QMap<QExtTag, QSharedPointer<QExtTcpPacketDispatcher> >::iterator iter;
        for (iter = d->m_idToTcpPacketDispatcher.begin(); iter != d->m_idToTcpPacketDispatcher.end(); ++iter)
        {
            if (task)
            {
                (*iter)->taskPool()->enqueueTask(task);
            }
        }
    }
}

QSharedPointer<QExtTcpFactory> QExtTcpServer::tcpFactory() const
{
    Q_D(const QExtTcpServer);
    QMutexLocker mutexLocker(&d->m_socketMutex);
    return d->m_tcpFactory;
}

void QExtTcpServer::setTcpFactory(const QSharedPointer<QExtTcpFactory> &tcpFactory)
{
    Q_D(QExtTcpServer);
    QMutexLocker mutexLocker(&d->m_socketMutex);
    if (tcpFactory != d->m_tcpFactory)
    {
        d->m_tcpFactory = tcpFactory;
        if (!tcpFactory.isNull())
        {
            QMap<QExtTag, QSharedPointer<QExtTcpPacketDispatcher> >::iterator iter;
            for (iter = d->m_idToTcpPacketDispatcher.begin(); iter != d->m_idToTcpPacketDispatcher.end(); ++iter)
            {
                (*iter)->setTcpFactory(tcpFactory);
            }
        }
    }
}

void QExtTcpServer::onSocketDisconnected()
{
    Q_D(QExtTcpServer);
    QMutexLocker mutexLocker(&d->m_socketMutex);
    QExtTcpSocket *socket = qobject_cast<QExtTcpSocket *>(this->sender());
    QExtTag socketId = socket->identityId();
    QSharedPointer<QExtTcpSocket> sharedSocket = d->m_idToTcpSocketMap.value(socketId);
    socket->disconnect(this);
    d->m_socketWorkThreadQueue.enqueue(socket->detachWorkThread());
    d->m_idToTcpSocketMap.remove(socketId);
    d->m_idToTcpPacketDispatcher.remove(socketId);
    d->m_allTcpSocketSet.remove(sharedSocket);
    /*start listen if connected socket less than max count*/
    if (d->m_allTcpSocketSet.size() < d->m_maxSocketConnectionCount)
    {
        this->listen(d->m_address, d->m_port);
    }
    emit this->serverMessage(tr("Info->socket %1 disconnected.").arg(socketId.toString()));
}

void QExtTcpServer::onSocketError(QAbstractSocket::SocketError error)
{
    Q_D(QExtTcpServer);
    QExtTcpSocket *socket = qobject_cast<QExtTcpSocket *>(this->sender());
    QExtTag socketId = socket->identityId();
    QSharedPointer<QExtTcpSocket> sharedSocket = d->m_idToTcpSocketMap.value(socketId);
    emit this->socketError(sharedSocket, error);
}

void QExtTcpServer::onSocketTransferError(QExtTcpSocket::TransferErrorType error)
{
    Q_D(QExtTcpServer);
    QExtTcpSocket *socket = qobject_cast<QExtTcpSocket *>(this->sender());
    QExtTag socketId = socket->identityId();
    QSharedPointer<QExtTcpSocket> sharedSocket = d->m_idToTcpSocketMap.value(socketId);
    emit this->socketTransferError(sharedSocket, error);
}

void QExtTcpServer::incomingConnection(QExtSocketDescriptor socketDescriptor)
{
    Q_D(QExtTcpServer);
    QMutexLocker mutexLocker(&d->m_socketMutex);
    QSharedPointer<QExtTcpSocket> socket(new QExtTcpSocket);
    if (socket->setSocketDescriptor(socketDescriptor))
    {
        /*close socket if connected socket equal to max count*/
        if (d->m_allTcpSocketSet.size() >= d->m_maxSocketConnectionCount)
        {
            socket->close();
            return;
        }

        QExtTag socketId = socket->updateIdentityId();
        QSharedPointer<QThread> thread = d->m_socketWorkThreadQueue.isEmpty() ? QSharedPointer<QThread>(new QThread) : d->m_socketWorkThreadQueue.dequeue();
        socket->attatchWorkThread(thread);
        if (!d->m_tcpFactory.isNull())
        {
            socket->setPacketParser(d->m_tcpFactory->createPacketParser());
            socket->setPacketDispatcher(d->m_tcpFactory->createPacketDispatcher(socket));
        }
        socket->packetDispatcher()->taskPool()->threadPool()->setMaxThreadCount(d->m_maxTaskThreadCount);

        connect(socket.data(), SIGNAL(disconnected()), this, SLOT(onSocketDisconnected()), Qt::QueuedConnection);
        connect(socket.data(), SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSocketError(QAbstractSocket::SocketError)), Qt::QueuedConnection);
        connect(socket.data(), SIGNAL(transferError(QExtTcpSocket::TransferErrorType)), this, SLOT(onSocketTransferError(QExtTcpSocket::TransferErrorType)), Qt::QueuedConnection);
        d->m_allTcpSocketSet.insert(socket);
        d->m_idToTcpSocketMap.insert(socketId, socket);
        d->m_idToTcpPacketDispatcher.insert(socketId, socket->packetDispatcher());
        thread->start();
        emit this->serverMessage(tr("Info->socket %1 connected.").arg(socketId.toString()));
        emit this->socketConnected(socket);

        /*close listen if connected socket equal to max count*/
        if (d->m_allTcpSocketSet.size() >= d->m_maxSocketConnectionCount)
        {
            d->m_address = this->serverAddress();
            d->m_port = this->serverPort();
            this->close();
        }
    }
    else
    {
        emit this->serverMessage(tr("Error->socket set socketDescriptor %1 failed.").arg(socketDescriptor));
    }
}
