#include <qextTcpClient.h>
#include <qextTcpClient_p.h>
#include <qextTcpPacketDispatcher.h>
#include <qextTcpPacketParserInterface.h>
#include <qextTcpPacketParser.h>
#include <qextTcpSocket.h>
#include <qextTcpTaskPool.h>
#include <qextTcpFactory.h>

#include <QDebug>
#include <QHostAddress>

QEXTTcpClientPrivate::QEXTTcpClientPrivate(QEXTTcpClient *qq)
    : QEXTTcpPacketTransceiverPrivate(qq)
{
    qRegisterMetaType<QAbstractSocket::SocketState>("QAbstractSocket::SocketState");
    qRegisterMetaType<QAbstractSocket::SocketError>("QAbstractSocket::SocketError");
    qRegisterMetaType<QEXTTcpSocket::TransferErrorType>("QEXTTcpSocket::TransferErrorType");

    m_maxTaskThreadCount = 8;
    m_socket = QSharedPointer<QEXTTcpSocket>(new QEXTTcpSocket);
    m_socketThread = QSharedPointer<QThread>(new QThread);
    m_socketThread->start();
}

QEXTTcpClientPrivate::~QEXTTcpClientPrivate()
{
    m_socketThread->quit();
    m_socketThread->wait();
}




QEXTTcpClient::QEXTTcpClient()
    : QEXTTcpPacketTransceiver(*(new QEXTTcpClientPrivate(this)))
{
    QEXT_DECL_D(QEXTTcpClient);
    this->initClient();
    this->setTcpFactory(QSharedPointer<QEXTTcpFactory>(new QEXTTcpFactory));
}

QEXTTcpClient::QEXTTcpClient(const QSharedPointer<QEXTTcpFactory> &tcpFactory)
    : QEXTTcpPacketTransceiver(*(new QEXTTcpClientPrivate(this)))
{
    QEXT_DECL_D(QEXTTcpClient);
    this->initClient();
    this->setTcpFactory(tcpFactory);
}

QEXTTcpClient::QEXTTcpClient(QEXTTcpClientPrivate &dd)
    : QEXTTcpPacketTransceiver(dd)
{
    QEXT_DECL_D(QEXTTcpClient);
    this->initClient();
    this->setTcpFactory(QSharedPointer<QEXTTcpFactory>(new QEXTTcpFactory));
}

QEXTTcpClient::QEXTTcpClient(QEXTTcpClientPrivate &dd, const QSharedPointer<QEXTTcpFactory> &tcpFactory)
    : QEXTTcpPacketTransceiver(dd)
{
    QEXT_DECL_D(QEXTTcpClient);
    this->initClient();
    this->setTcpFactory(tcpFactory);
}

QEXTTcpClient::~QEXTTcpClient()
{

}

QSharedPointer<QEXTTcpSocket> QEXTTcpClient::socket() const
{
    QEXT_DECL_DC(QEXTTcpClient);
    return d->m_socket;
}

QAbstractSocket::SocketState QEXTTcpClient::socketState() const
{
    QEXT_DECL_DC(QEXTTcpClient);
    return d->m_socket->state();
}

bool QEXTTcpClient::isSocketConnected() const
{
    QEXT_DECL_DC(QEXTTcpClient);
    return d->m_socket->isConnected();
}

void QEXTTcpClient::startConnection(const QString &ipAddr, quint16 port)
{
    QEXT_DECL_D(QEXTTcpClient);
    emit this->tryToClose();
    emit this->tryToConnect(ipAddr, port);
}

void QEXTTcpClient::closeConnection()
{
    emit this->tryToClose();
}

void QEXTTcpClient::abortConnection()
{
    emit this->tryToAbort();
}

QString QEXTTcpClient::serverAddress() const
{
    QEXT_DECL_DC(QEXTTcpClient);
    QMutexLocker mutexLocker(&d->m_socketMutex);
    return d->m_socket->peerAddress().toString();
}

quint16 QEXTTcpClient::serverPort() const
{
    QEXT_DECL_DC(QEXTTcpClient);
    QMutexLocker mutexLocker(&d->m_socketMutex);
    return d->m_socket->peerPort();
}

int QEXTTcpClient::maxTaskThreadCount() const
{
    QEXT_DECL_DC(QEXTTcpClient);
    QMutexLocker mutexLocker(&d->m_socketMutex);
    return d->m_maxTaskThreadCount;
}

void QEXTTcpClient::setMaxTaskThreadCount(int maxThreadCount)
{
    QEXT_DECL_D(QEXTTcpClient);
    QMutexLocker mutexLocker(&d->m_socketMutex);
    if (maxThreadCount != d->m_maxTaskThreadCount)
    {
        d->m_maxTaskThreadCount = maxThreadCount;
        d->m_socket->packetDispatcher()->taskPool()->threadPool()->setMaxThreadCount(maxThreadCount);
    }
}

void QEXTTcpClient::runTask(int function)
{
    QEXT_DECL_DC(QEXTTcpClient);
    QMutexLocker mutexLocker(&d->m_socketMutex);
    if (!d->m_tcpFactory.isNull())
    {
        QEXTTcpTask *task = d->m_tcpFactory->createTask(d->m_packetDispatcher, function);
        if (task)
        {
            d->m_packetDispatcher->taskPool()->enqueueTask(task);
        }
    }
}

void QEXTTcpClient::runTask(QEXTTcpTask *task)
{
    QEXT_DECL_DC(QEXTTcpClient);
    QMutexLocker mutexLocker(&d->m_socketMutex);
    if (!d->m_tcpFactory.isNull())
    {
        if (task)
        {
            d->m_packetDispatcher->taskPool()->enqueueTask(task);
        }
    }
}

QSharedPointer<QEXTTcpFactory> QEXTTcpClient::tcpFactory() const
{
    QEXT_DECL_DC(QEXTTcpClient);
    QMutexLocker mutexLocker(&d->m_socketMutex);
    return d->m_tcpFactory;
}

void QEXTTcpClient::setTcpFactory(const QSharedPointer<QEXTTcpFactory> tcpFactory)
{
    QEXT_DECL_D(QEXTTcpClient);
    QMutexLocker mutexLocker(&d->m_socketMutex);
    d->m_tcpFactory = tcpFactory;
    if (!tcpFactory.isNull())
    {
        d->m_socket->setPacketParser(tcpFactory->createPacketParser());
        d->m_socket->setPacketDispatcher(tcpFactory->createPacketDispatcher(d->m_socket));
        d->m_packetDispatcher = d->m_socket->packetDispatcher();
        d->m_packetDispatcher->taskPool()->threadPool()->setMaxThreadCount(d->m_maxTaskThreadCount);
    }
}

QEXTTcpPacketDispatcher *QEXTTcpClient::packetDispatcher() const
{
    QEXT_DECL_DC(QEXTTcpClient);
    QMutexLocker mutexLocker(&d->m_packetDispatcherMutex);
    return d->m_packetDispatcher.data();
}

void QEXTTcpClient::setPacketDispatcher(const QSharedPointer<QEXTTcpPacketDispatcher> &dispatcher)
{
    QEXT_DECL_D(QEXTTcpClient);
    QMutexLocker mutexLocker(&d->m_packetDispatcherMutex);
    if (dispatcher != d->m_packetDispatcher)
    {
        d->m_socket->setPacketDispatcher(dispatcher);
        d->m_packetDispatcher = dispatcher;
        d->m_packetDispatcher->taskPool()->threadPool()->setMaxThreadCount(d->m_maxTaskThreadCount);
    }
}

void QEXTTcpClient::initClient()
{
    QEXT_DECL_D(QEXTTcpClient);
    QMutexLocker mutexLocker(&d->m_socketMutex);
    if (!d->m_socket.isNull())
    {
        d->m_socket->setParent(QEXT_DECL_NULLPTR);
        d->m_socket->attatchWorkThread(d->m_socketThread);
        if (!d->m_tcpFactory.isNull())
        {
            d->m_socket->setPacketParser(d->m_tcpFactory->createPacketParser());
            d->m_socket->setPacketDispatcher(d->m_tcpFactory->createPacketDispatcher(d->m_socket));
        }
        d->m_packetDispatcher = d->m_socket->packetDispatcher();
        d->m_packetDispatcher->taskPool()->threadPool()->setMaxThreadCount(d->m_maxTaskThreadCount);

        connect(d->m_socket.data(), SIGNAL(connected()), this, SIGNAL(socketConnected()));
        connect(d->m_socket.data(), SIGNAL(disconnected()), this, SIGNAL(socketDisconnected()));
        connect(d->m_socket.data(), SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SIGNAL(socketStateChanged(QAbstractSocket::SocketState)));
        connect(d->m_socket.data(), SIGNAL(error(QAbstractSocket::SocketError)), this, SIGNAL(socketError(QAbstractSocket::SocketError)));
        connect(d->m_socket.data(), SIGNAL(transferError(QEXTTcpSocket::TransferErrorType)), this, SIGNAL(transferError(QEXTTcpSocket::TransferErrorType)));

        connect(this, SIGNAL(tryToConnect(QString, quint16)), d->m_socket.data(), SLOT(connectToServer(QString, quint16)));
        connect(this, SIGNAL(tryToClose()), d->m_socket.data(), SLOT(closeSocket()));
        connect(this, SIGNAL(tryToAbort()), d->m_socket.data(), SLOT(abortSocket()));
    }
}

