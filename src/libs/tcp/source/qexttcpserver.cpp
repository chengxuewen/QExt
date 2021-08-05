#include <qexttcpserver.h>
#include <qexttcpserver_p.h>
#include <qexttcptransferthreadpool.h>
#include <qexttcptransferthread.h>
#include <qexttcptaskthreadpool.h>

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
    m_taskPoolThread->quit();
    m_taskPoolThread->wait();
}

void QEXTTcpServerPrivate::initServer()
{
    QEXT_Q(QEXTTcpServer);
    qRegisterMetaType<QEXTSocketDescriptor>("QEXTSocketDescriptor");
    qRegisterMetaType<QSharedPointer<QEXTTcpAbstractTaskPool> >("QSharedPointer<QEXTTcpTaskPoolBase>");
    qRegisterMetaType<QAbstractSocket::SocketError>("QAbstractSocket::SocketError");
    qRegisterMetaType<QEXTTcpSocket::TransferErrorType>("QEXTTcpSocket::TransferErrorType");
    m_transferThreadPool.reset(new QEXTTcpTransferThreadPool(q));
    QEXTTcpTransferThreadPool *transferThreadPool = m_transferThreadPool.data();
    QObject::connect(transferThreadPool, SIGNAL(socketMessage(QEXTTcpServerSocket*,QString)),
                     q, SLOT(handleSocketMessage(QEXTTcpServerSocket*,QString)), Qt::QueuedConnection);
    QObject::connect(transferThreadPool, SIGNAL(socketConnected(QEXTTcpServerSocket*)),
                     q, SLOT(handleSocketConnected(QEXTTcpServerSocket*)), Qt::QueuedConnection);
    QObject::connect(transferThreadPool, SIGNAL(socketDisconnected(QEXTTcpServerSocket*)),
                     q, SLOT(handleSocketDisconnected(QEXTTcpServerSocket*)), Qt::QueuedConnection);
    QObject::connect(transferThreadPool, SIGNAL(socketError(QEXTTcpServerSocket*,QAbstractSocket::SocketError)),
                     q, SLOT(handleSocketError(QEXTTcpServerSocket*,QAbstractSocket::SocketError)), Qt::QueuedConnection);
    QObject::connect(transferThreadPool, SIGNAL(transferError(QEXTTcpSocket::TransferErrorType)),
                     q, SIGNAL(transferError(QEXTTcpSocket::TransferErrorType)), Qt::QueuedConnection);

    QObject::connect(q, SIGNAL(connectionRequest(QEXTSocketDescriptor)),
                     transferThreadPool, SLOT(establishConnection(QEXTSocketDescriptor)), Qt::QueuedConnection);

    m_taskPoolThread.reset(new QThread);
    m_taskPoolThread->start();
    m_taskThreadPool.reset(new QEXTTcpTaskThreadPool);
}



QEXTTcpServer::QEXTTcpServer(QObject *parent)
    : QTcpServer(parent), QEXTObject(*(new QEXTTcpServerPrivate(this)))
{
    QEXT_D(QEXTTcpServer);
    d->initServer();
}

QEXTTcpServer::QEXTTcpServer(QEXTTcpAbstractPacketParser *packetParser, QObject *parent)
    : QTcpServer(parent), QEXTObject(*(new QEXTTcpServerPrivate(this)))
{
    QEXT_D(QEXTTcpServer);
    d->initServer();
    this->setPacketParser(packetParser);
}

QEXTTcpServer::QEXTTcpServer(QEXTTcpAbstractPacketParser *packetParser, QEXTTcpAbstractTaskPool *taskPool, QObject *parent)
    : QTcpServer(parent), QEXTObject(*(new QEXTTcpServerPrivate(this)))
{
    QEXT_D(QEXTTcpServer);
    d->initServer();
    this->setPacketParser(packetParser);
    this->setTaskPool(taskPool);
}

QEXTTcpServer::QEXTTcpServer(QEXTTcpServerPrivate &dd, QObject *parent)
    : QTcpServer(parent), QEXTObject(dd)
{
    QEXT_D(QEXTTcpServer);
    d->initServer();
}

QEXTTcpServer::QEXTTcpServer(QEXTTcpServerPrivate &dd, QEXTTcpAbstractPacketParser *packetParser, QObject *parent)
    : QTcpServer(parent), QEXTObject(dd)
{
    QEXT_D(QEXTTcpServer);
    d->initServer();
    this->setPacketParser(packetParser);
}

QEXTTcpServer::QEXTTcpServer(QEXTTcpServerPrivate &dd, QEXTTcpAbstractPacketParser *packetParser,
                             QEXTTcpAbstractTaskPool *taskPool, QObject *parent)
    : QTcpServer(parent), QEXTObject(dd)
{
    QEXT_D(QEXTTcpServer);
    d->initServer();
    this->setPacketParser(packetParser);
    this->setTaskPool(taskPool);
}

QEXTTcpServer::~QEXTTcpServer()
{

}

int QEXTTcpServer::allSocketCount() const
{
    QEXT_DC(QEXTTcpServer);
    return d->m_allTcpSocketSet.size();
}

int QEXTTcpServer::maxSocketCount() const
{
    QEXT_DC(QEXTTcpServer);
    return d->m_maxTcpSocketCount;
}

void QEXTTcpServer::setMaxSocketCount(int maxSocketCount)
{
    QEXT_D(QEXTTcpServer);
    d->m_maxTcpSocketCount = qMax(maxSocketCount, d->m_allTcpSocketSet.size());
}

QEXTTcpAbstractPacketParser *QEXTTcpServer::packetParser() const
{
    QEXT_DC(QEXTTcpServer);
    return d->m_packetParser.data();
}

void QEXTTcpServer::setPacketParser(QEXTTcpAbstractPacketParser *packetParser)
{
    QEXT_D(QEXTTcpServer);
    if (packetParser && packetParser != d->m_packetParser.data()) {
        d->m_packetParser.reset(packetParser);
        d->m_transferThreadPool->setPacketParser(d->m_packetParser->cloneParser());
        d->m_taskThreadPool->setPacketParser(d->m_packetParser->cloneParser());
        if (!d->m_taskPool.isNull()) {
            d->m_taskPool->setPacketParser(packetParser->cloneParser());
        }
    }
}

QEXTTcpAbstractTaskPool *QEXTTcpServer::taskPool() const
{
    QEXT_DC(QEXTTcpServer);
    return d->m_taskPool.data();
}

void QEXTTcpServer::setTaskPool(QEXTTcpAbstractTaskPool *taskPool)
{
    QEXT_D(QEXTTcpServer);
    if (taskPool && taskPool != d->m_taskPool.data()) {
        if (!d->m_packetParser.isNull()) {
            taskPool->setPacketParser(d->m_packetParser->cloneParser());
        }
        taskPool->setParent(QEXT_NULLPTR);
        taskPool->moveToThread(d->m_taskPoolThread.data());
        d->m_taskPool = QSharedPointer<QEXTTcpAbstractTaskPool>(taskPool);
        d->m_transferThreadPool->setTaskPool(d->m_taskPool);
        d->m_taskThreadPool->setTaskPool(d->m_taskPool);
    }
}

void QEXTTcpServer::handleSocketMessage(QEXTTcpServerSocket *socket, const QString &msg)
{
    QEXT_D(QEXTTcpServer);
    Q_UNUSED(socket);
    qDebug() << msg;
}

void QEXTTcpServer::handleSocketConnected(QEXTTcpServerSocket *socket)
{
    QEXT_D(QEXTTcpServer);
    QMutexLocker mutexLocker(&d->m_socketMutex);
    socket->setParent(QEXT_NULLPTR);
    d->m_allTcpSocketSet.insert(socket);
}

void QEXTTcpServer::handleSocketDisconnected(QEXTTcpServerSocket *socket)
{
    QEXT_D(QEXTTcpServer);
    QMutexLocker mutexLocker(&d->m_socketMutex);
    d->m_invalidTcpSocketSet.insert(socket);
    d->m_allTcpSocketSet.remove(socket);
}

void QEXTTcpServer::handleSocketError(QEXTTcpServerSocket *socket, QAbstractSocket::SocketError error)
{
    emit this->socketError(socket->identityId(), error);
}


void QEXTTcpServer::incomingConnection(QEXTSocketDescriptor socketDescriptor)
{
    emit this->connectionRequest(socketDescriptor);
}


