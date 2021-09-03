#include <qextTcpServer.h>
#include <qextTcpServer_p.h>
#include <qextTcpPacketParser.h>

#include <QTcpSocket>
#include <QDateTime>
#include <QThread>

QEXTTcpServerPrivate::QEXTTcpServerPrivate(QEXTTcpServer *qq)
    : QEXTObjectPrivate(qq)
{
    m_maxTcpSocketCount = 256;
}

QEXTTcpServerPrivate::~QEXTTcpServerPrivate()
{
    QEXT_DECL_Q(QEXTTcpServer);
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
    for (queueIter = m_socketWorkThreadQueue.begin(); queueIter < m_socketWorkThreadQueue.end(); ++queueIter) {
        (*queueIter)->quit();
        (*queueIter)->wait();
    }
    m_socketWorkThreadQueue.clear();

    m_idToTcpSocketMap.clear();
}

void QEXTTcpServerPrivate::initServer()
{
    QEXT_DECL_Q(QEXTTcpServer);
    qRegisterMetaType<QEXTSocketDescriptor>("QEXTSocketDescriptor");
    qRegisterMetaType<QAbstractSocket::SocketError>("QAbstractSocket::SocketError");
    qRegisterMetaType<QEXTTcpSocket::TransferErrorType>("QEXTTcpSocket::TransferErrorType");
}


QEXTTcpServer::QEXTTcpServer()
    : QTcpServer(), QEXTObject(*(new QEXTTcpServerPrivate(this)))
{
    QEXT_DECL_D(QEXTTcpServer);
    d->initServer();
    this->setPacketParser(QSharedPointer<QEXTTcpPacketParserInterface>(new QEXTTcpPacketParser));
}

QEXTTcpServer::QEXTTcpServer(const QSharedPointer<QEXTTcpPacketParserInterface> &packetParser)
    : QTcpServer(), QEXTObject(*(new QEXTTcpServerPrivate(this)))
{
    QEXT_DECL_D(QEXTTcpServer);
    d->initServer();
    this->setPacketParser(packetParser);
    this->setPacketDispatcherFactory(QSharedPointer<QEXTTcpPacketDispatcherFactory>(new QEXTTcpPacketDispatcherFactory));
}

QEXTTcpServer::QEXTTcpServer(const QSharedPointer<QEXTTcpPacketParserInterface> &packetParser,
                             const QSharedPointer<QEXTTcpPacketDispatcherFactory> &dispatcherFactory)
    : QTcpServer(), QEXTObject(*(new QEXTTcpServerPrivate(this)))
{
    QEXT_DECL_D(QEXTTcpServer);
    d->initServer();
    this->setPacketParser(packetParser);
    this->setPacketDispatcherFactory(dispatcherFactory);
}

QEXTTcpServer::QEXTTcpServer(QEXTTcpServerPrivate &dd)
    : QTcpServer(), QEXTObject(dd)
{
    QEXT_DECL_D(QEXTTcpServer);
    d->initServer();
}

QEXTTcpServer::~QEXTTcpServer()
{

}

int QEXTTcpServer::allSocketCount() const
{
    QEXT_DECL_DC(QEXTTcpServer);
    return d->m_allTcpSocketSet.size();
}

int QEXTTcpServer::maxSocketCount() const
{
    QEXT_DECL_DC(QEXTTcpServer);
    return d->m_maxTcpSocketCount;
}

void QEXTTcpServer::setMaxSocketCount(int maxSocketCount)
{
    QEXT_DECL_D(QEXTTcpServer);
    d->m_maxTcpSocketCount = qMax(maxSocketCount, d->m_allTcpSocketSet.size());
}

QSharedPointer<QEXTTcpPacketParserInterface> QEXTTcpServer::packetParser() const
{
    QEXT_DECL_DC(QEXTTcpServer);
    return d->m_packetParser;
}

void QEXTTcpServer::setPacketParser(const QSharedPointer<QEXTTcpPacketParserInterface> &packetParser)
{
    QEXT_DECL_D(QEXTTcpServer);
    if (packetParser != d->m_packetParser)
    {
        d->m_packetParser = packetParser;
        if (!packetParser.isNull())
        {
            QSet<QSharedPointer<QEXTTcpSocket> >::iterator iter;
            for (iter = d->m_allTcpSocketSet.begin(); iter != d->m_allTcpSocketSet.end(); ++iter)
            {
                (*iter)->setPacketParser(packetParser);
            }
        }
    }
}

QSharedPointer<QEXTTcpPacketDispatcherFactory> QEXTTcpServer::packetDispatcherFactory() const
{
    QEXT_DECL_DC(QEXTTcpServer);
    return d->m_packetDispatcherFactory;
}

void QEXTTcpServer::setPacketDispatcherFactory(const QSharedPointer<QEXTTcpPacketDispatcherFactory> &packetDispatcherFactory)
{
    QEXT_DECL_D(QEXTTcpServer);
    if (packetDispatcherFactory != d->m_packetDispatcherFactory.data())
    {
        d->m_packetDispatcherFactory = packetDispatcherFactory;
        if (!packetDispatcherFactory.isNull())
        {
            QSet<QSharedPointer<QEXTTcpSocket> >::iterator iter;
            for (iter = d->m_allTcpSocketSet.begin(); iter != d->m_allTcpSocketSet.end(); ++iter)
            {
                (*iter)->setPacketDispatcher(packetDispatcherFactory->createPacketDispatcher((*iter)));
            }
        }
    }
}

void QEXTTcpServer::onSocketDisconnected()
{
    QEXT_DECL_D(QEXTTcpServer);
    QMutexLocker mutexLocker(&d->m_socketMutex);
    QEXTTcpSocket *socket = qobject_cast<QEXTTcpSocket *>(this->sender());
    QEXTId socketId = socket->identityId();
    QSharedPointer<QEXTTcpSocket> sharedSocket = d->m_idToTcpSocketMap.value(socketId);
    socket->disconnect(this);
    d->m_socketWorkThreadQueue.enqueue(socket->detachWorkThread());
    d->m_idToTcpSocketMap.remove(socketId);
    d->m_allTcpSocketSet.remove(sharedSocket);
    emit this->serverMessage(tr("Info->socket %1 disconnected.").arg(socketId.toString()));
}

void QEXTTcpServer::onSocketError(QAbstractSocket::SocketError error)
{
    QEXT_DECL_D(QEXTTcpServer);
    QEXTTcpSocket *socket = qobject_cast<QEXTTcpSocket *>(this->sender());
    QEXTId socketId = socket->identityId();
    QSharedPointer<QEXTTcpSocket> sharedSocket = d->m_idToTcpSocketMap.value(socketId);
    emit this->socketError(sharedSocket, error);
}

void QEXTTcpServer::onSocketTransferError(QEXTTcpSocket::TransferErrorType error)
{
    QEXT_DECL_D(QEXTTcpServer);
    QEXTTcpSocket *socket = qobject_cast<QEXTTcpSocket *>(this->sender());
    QEXTId socketId = socket->identityId();
    QSharedPointer<QEXTTcpSocket> sharedSocket = d->m_idToTcpSocketMap.value(socketId);
    emit this->socketTransferError(sharedSocket, error);
}

void QEXTTcpServer::incomingConnection(QEXTSocketDescriptor socketDescriptor)
{
    QEXT_DECL_D(QEXTTcpServer);
    QMutexLocker mutexLocker(&d->m_socketMutex);
    QSharedPointer<QEXTTcpSocket> socket(new QEXTTcpSocket);
    if (!socket.isNull())
    {
        if (socket->setSocketDescriptor(socketDescriptor))
        {
            QEXTId socketId = socket->updateIdentityId();
            QSharedPointer<QThread> thread = d->m_socketWorkThreadQueue.isEmpty() ? QSharedPointer<QThread>(new QThread) : d->m_socketWorkThreadQueue.dequeue();
            socket->attatchWorkThread(thread);
            if (!d->m_packetParser.isNull())
            {
                socket->setPacketParser(d->m_packetParser);
            }
            if (!d->m_packetDispatcherFactory.isNull())
            {
                socket->setPacketDispatcher(d->m_packetDispatcherFactory->createPacketDispatcher(socket));
            }

            connect(socket.data(), SIGNAL(disconnected()), this, SLOT(onSocketDisconnected()), Qt::QueuedConnection);
            connect(socket.data(), SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSocketError(QAbstractSocket::SocketError)), Qt::QueuedConnection);
            connect(socket.data(), SIGNAL(transferError(QEXTTcpSocket::TransferErrorType)), this, SLOT(onSocketTransferError(QEXTTcpSocket::TransferErrorType)), Qt::QueuedConnection);
            d->m_allTcpSocketSet.insert(socket);
            d->m_idToTcpSocketMap.insert(socketId.toString(), socket);
            thread->start();
            emit this->serverMessage(tr("Info->socket %1 connected.").arg(socketId.toString()));
            emit this->socketConnected(socket);
        }
        else
        {
            emit this->serverMessage(tr("Error->socket set socketDescriptor %1 failed.").arg(socketDescriptor));
        }
    }
}
