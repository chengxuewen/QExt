#include <qextTcpServer.h>
#include <qextTcpServer_p.h>
#include <qextTcpFactory.h>
#include <qextTcpTaskPool.h>
#include <qextTcpPacketParser.h>

#include <QTcpSocket>
#include <QDateTime>
#include <QThread>

QEXTTcpServerPrivate::QEXTTcpServerPrivate(QEXTTcpServer *q)
    : q_ptr(q)
{
    m_maxSocketConnectionCount = 16;
    m_maxTaskThreadCount = 8;
}

QEXTTcpServerPrivate::~QEXTTcpServerPrivate()
{
    Q_Q(QEXTTcpServer);
    QMutexLocker mutexLocker(&m_socketMutex);
    QSet<QSharedPointer<QEXTTcpSocket> >::iterator iter;
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

void QEXTTcpServerPrivate::initServer()
{
    Q_Q(QEXTTcpServer);
    qRegisterMetaType<QEXTSocketDescriptor>("QEXTSocketDescriptor");
    qRegisterMetaType<QAbstractSocket::SocketError>("QAbstractSocket::SocketError");
    qRegisterMetaType<QEXTTcpSocket::TransferErrorType>("QEXTTcpSocket::TransferErrorType");
}


QEXTTcpServer::QEXTTcpServer()
    : QTcpServer(QEXT_DECL_NULLPTR), d_ptr(new QEXTTcpServerPrivate(this))
{
    Q_D(QEXTTcpServer);
    d->initServer();
    this->setTcpFactory(QSharedPointer<QEXTTcpFactory>(new QEXTTcpFactory));
}

QEXTTcpServer::QEXTTcpServer(const QSharedPointer<QEXTTcpFactory> &tcpFactory)
    : QTcpServer(QEXT_DECL_NULLPTR), d_ptr(new QEXTTcpServerPrivate(this))
{
    Q_D(QEXTTcpServer);
    d->initServer();
    this->setTcpFactory(tcpFactory);
}

QEXTTcpServer::QEXTTcpServer(QEXTTcpServerPrivate *d)
    : QTcpServer(QEXT_DECL_NULLPTR), d_ptr(d)
{
    d_ptr->initServer();
    this->setTcpFactory(QSharedPointer<QEXTTcpFactory>(new QEXTTcpFactory));
}

QEXTTcpServer::QEXTTcpServer(QEXTTcpServerPrivate *d, const QSharedPointer<QEXTTcpFactory> &tcpFactory)
    : QTcpServer(QEXT_DECL_NULLPTR), d_ptr(d)
{
    d_ptr->initServer();
    this->setTcpFactory(tcpFactory);
}

QEXTTcpServer::~QEXTTcpServer()
{

}

size_t QEXTTcpServer::allSocketCount() const
{
    Q_D(const QEXTTcpServer);
    QMutexLocker mutexLocker(&d->m_socketMutex);
    return d->m_allTcpSocketSet.size();
}

size_t QEXTTcpServer::maxSocketConnectionCount() const
{
    Q_D(const QEXTTcpServer);
    QMutexLocker mutexLocker(&d->m_socketMutex);
    return d->m_maxSocketConnectionCount;
}

void QEXTTcpServer::setMaxSocketConnectionCount(size_t count)
{
    Q_D(QEXTTcpServer);
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

size_t QEXTTcpServer::maxTaskThreadCount() const
{
    Q_D(const QEXTTcpServer);
    QMutexLocker mutexLocker(&d->m_socketMutex);
    return d->m_maxTaskThreadCount;
}

void QEXTTcpServer::setMaxTaskThreadCount(size_t count)
{
    Q_D(QEXTTcpServer);
    QMutexLocker mutexLocker(&d->m_socketMutex);
    d->m_maxTaskThreadCount = count;
    QMap<QEXTId, QSharedPointer<QEXTTcpPacketDispatcher> >::iterator iter;
    for (iter = d->m_idToTcpPacketDispatcher.begin(); iter != d->m_idToTcpPacketDispatcher.end(); ++iter)
    {
        (*iter)->taskPool()->threadPool()->setMaxThreadCount(count);
    }
}

void QEXTTcpServer::runTask(int function)
{
    Q_D(QEXTTcpServer);
    QMutexLocker mutexLocker(&d->m_socketMutex);
    if (!d->m_tcpFactory.isNull())
    {
        QMap<QEXTId, QSharedPointer<QEXTTcpPacketDispatcher> >::iterator iter;
        for (iter = d->m_idToTcpPacketDispatcher.begin(); iter != d->m_idToTcpPacketDispatcher.end(); ++iter)
        {
            QEXTTcpTask *task = d->m_tcpFactory->createTask((*iter), function);
            if (task)
            {
                (*iter)->taskPool()->enqueueTask(task);
            }
        }
    }
}

void QEXTTcpServer::runTask(QEXTTcpTask *task)
{
    Q_D(QEXTTcpServer);
    QMutexLocker mutexLocker(&d->m_socketMutex);
    if (!d->m_tcpFactory.isNull())
    {
        QMap<QEXTId, QSharedPointer<QEXTTcpPacketDispatcher> >::iterator iter;
        for (iter = d->m_idToTcpPacketDispatcher.begin(); iter != d->m_idToTcpPacketDispatcher.end(); ++iter)
        {
            if (task)
            {
                (*iter)->taskPool()->enqueueTask(task);
            }
        }
    }
}

QSharedPointer<QEXTTcpFactory> QEXTTcpServer::tcpFactory() const
{
    Q_D(const QEXTTcpServer);
    QMutexLocker mutexLocker(&d->m_socketMutex);
    return d->m_tcpFactory;
}

void QEXTTcpServer::setTcpFactory(const QSharedPointer<QEXTTcpFactory> &tcpFactory)
{
    Q_D(QEXTTcpServer);
    QMutexLocker mutexLocker(&d->m_socketMutex);
    if (tcpFactory != d->m_tcpFactory)
    {
        d->m_tcpFactory = tcpFactory;
        if (!tcpFactory.isNull())
        {
            QMap<QEXTId, QSharedPointer<QEXTTcpPacketDispatcher> >::iterator iter;
            for (iter = d->m_idToTcpPacketDispatcher.begin(); iter != d->m_idToTcpPacketDispatcher.end(); ++iter)
            {
                (*iter)->setTcpFactory(tcpFactory);
            }
        }
    }
}

void QEXTTcpServer::onSocketDisconnected()
{
    Q_D(QEXTTcpServer);
    QMutexLocker mutexLocker(&d->m_socketMutex);
    QEXTTcpSocket *socket = qobject_cast<QEXTTcpSocket *>(this->sender());
    QEXTId socketId = socket->identityId();
    QSharedPointer<QEXTTcpSocket> sharedSocket = d->m_idToTcpSocketMap.value(socketId);
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

void QEXTTcpServer::onSocketError(QAbstractSocket::SocketError error)
{
    Q_D(QEXTTcpServer);
    QEXTTcpSocket *socket = qobject_cast<QEXTTcpSocket *>(this->sender());
    QEXTId socketId = socket->identityId();
    QSharedPointer<QEXTTcpSocket> sharedSocket = d->m_idToTcpSocketMap.value(socketId);
    emit this->socketError(sharedSocket, error);
}

void QEXTTcpServer::onSocketTransferError(QEXTTcpSocket::TransferErrorType error)
{
    Q_D(QEXTTcpServer);
    QEXTTcpSocket *socket = qobject_cast<QEXTTcpSocket *>(this->sender());
    QEXTId socketId = socket->identityId();
    QSharedPointer<QEXTTcpSocket> sharedSocket = d->m_idToTcpSocketMap.value(socketId);
    emit this->socketTransferError(sharedSocket, error);
}

void QEXTTcpServer::incomingConnection(QEXTSocketDescriptor socketDescriptor)
{
    Q_D(QEXTTcpServer);
    QMutexLocker mutexLocker(&d->m_socketMutex);
    QSharedPointer<QEXTTcpSocket> socket(new QEXTTcpSocket);
    if (socket->setSocketDescriptor(socketDescriptor))
    {
        /*close socket if connected socket equal to max count*/
        if (d->m_allTcpSocketSet.size() >= d->m_maxSocketConnectionCount)
        {
            socket->close();
            return;
        }

        QEXTId socketId = socket->updateIdentityId();
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
        connect(socket.data(), SIGNAL(transferError(QEXTTcpSocket::TransferErrorType)), this, SLOT(onSocketTransferError(QEXTTcpSocket::TransferErrorType)), Qt::QueuedConnection);
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
