#include <private/qextTcpClient_p.h>
#include <qextTcpPacketDispatcher.h>
#include <qextTcpPacketParserInterface.h>
#include <qextTcpPacketParser.h>
#include <qextTcpSocket.h>
#include <qextTcpTaskPool.h>
#include <qextTcpFactory.h>

#include <QDebug>
#include <QHostAddress>

QExtTcpClientPrivate::QExtTcpClientPrivate(QExtTcpClient *q)
    : QExtTcpPacketTransceiverPrivate(q)
{
    qRegisterMetaType<QAbstractSocket::SocketState>("QAbstractSocket::SocketState");
    qRegisterMetaType<QAbstractSocket::SocketError>("QAbstractSocket::SocketError");
    qRegisterMetaType<QExtTcpSocket::TransferErrorType>("QExtTcpSocket::TransferErrorType");

    m_maxTaskThreadCount = 8;
    m_socket = QSharedPointer<QExtTcpSocket>(new QExtTcpSocket);
    m_socketThread = QSharedPointer<QThread>(new QThread);
    m_socketThread->start();
}

QExtTcpClientPrivate::~QExtTcpClientPrivate()
{
    m_socketThread->quit();
    m_socketThread->wait();
}




QExtTcpClient::QExtTcpClient()
    : QExtTcpPacketTransceiver(new QExtTcpClientPrivate(this))
{
    Q_D(QExtTcpClient);
    this->initClient();
    this->setTcpFactory(QSharedPointer<QExtTcpFactory>(new QExtTcpFactory));
}

QExtTcpClient::QExtTcpClient(const QSharedPointer<QExtTcpFactory> &tcpFactory)
    : QExtTcpPacketTransceiver(new QExtTcpClientPrivate(this))
{
    this->initClient();
    this->setTcpFactory(tcpFactory);
}

QExtTcpClient::QExtTcpClient(QExtTcpClientPrivate *d)
    : QExtTcpPacketTransceiver(d)
{
    this->initClient();
    this->setTcpFactory(QSharedPointer<QExtTcpFactory>(new QExtTcpFactory));
}

QExtTcpClient::QExtTcpClient(QExtTcpClientPrivate *d, const QSharedPointer<QExtTcpFactory> &tcpFactory)
    : QExtTcpPacketTransceiver(d)
{
    this->initClient();
    this->setTcpFactory(tcpFactory);
}

QExtTcpClient::~QExtTcpClient()
{

}

QSharedPointer<QExtTcpSocket> QExtTcpClient::socket() const
{
    Q_D(const QExtTcpClient);
    return d->m_socket;
}

QAbstractSocket::SocketState QExtTcpClient::socketState() const
{
    Q_D(const QExtTcpClient);
    return d->m_socket->state();
}

bool QExtTcpClient::isSocketConnected() const
{
    Q_D(const QExtTcpClient);
    return d->m_socket->isConnected();
}

void QExtTcpClient::startConnection(const QString &ipAddr, quint16 port)
{
    Q_D(QExtTcpClient);
    emit this->tryToClose();
    emit this->tryToConnect(ipAddr, port);
}

void QExtTcpClient::closeConnection()
{
    emit this->tryToClose();
}

void QExtTcpClient::abortConnection()
{
    emit this->tryToAbort();
}

QString QExtTcpClient::serverAddress() const
{
    Q_D(const QExtTcpClient);
    QMutexLocker mutexLocker(&d->m_socketMutex);
    return d->m_socket->peerAddress().toString();
}

quint16 QExtTcpClient::serverPort() const
{
    Q_D(const QExtTcpClient);
    QMutexLocker mutexLocker(&d->m_socketMutex);
    return d->m_socket->peerPort();
}

int QExtTcpClient::maxTaskThreadCount() const
{
    Q_D(const QExtTcpClient);
    QMutexLocker mutexLocker(&d->m_socketMutex);
    return d->m_maxTaskThreadCount;
}

void QExtTcpClient::setMaxTaskThreadCount(int maxThreadCount)
{
    Q_D(QExtTcpClient);
    QMutexLocker mutexLocker(&d->m_socketMutex);
    if (maxThreadCount != d->m_maxTaskThreadCount)
    {
        d->m_maxTaskThreadCount = maxThreadCount;
        d->m_socket->packetDispatcher()->taskPool()->threadPool()->setMaxThreadCount(maxThreadCount);
    }
}

void QExtTcpClient::runTask(int function)
{
    Q_D(const QExtTcpClient);
    QMutexLocker mutexLocker(&d->m_socketMutex);
    if (!d->m_tcpFactory.isNull())
    {
        QExtTcpTask *task = d->m_tcpFactory->createTask(d->m_packetDispatcher, function);
        if (task)
        {
            d->m_packetDispatcher->taskPool()->enqueueTask(task);
        }
    }
}

void QExtTcpClient::runTask(QExtTcpTask *task)
{
    Q_D(const QExtTcpClient);
    QMutexLocker mutexLocker(&d->m_socketMutex);
    if (!d->m_tcpFactory.isNull())
    {
        if (task)
        {
            d->m_packetDispatcher->taskPool()->enqueueTask(task);
        }
    }
}

QSharedPointer<QExtTcpFactory> QExtTcpClient::tcpFactory() const
{
    Q_D(const QExtTcpClient);
    QMutexLocker mutexLocker(&d->m_socketMutex);
    return d->m_tcpFactory;
}

void QExtTcpClient::setTcpFactory(const QSharedPointer<QExtTcpFactory> tcpFactory)
{
    Q_D(QExtTcpClient);
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

QExtTcpPacketDispatcher *QExtTcpClient::packetDispatcher() const
{
    Q_D(const QExtTcpClient);
    QMutexLocker mutexLocker(&d->m_packetDispatcherMutex);
    return d->m_packetDispatcher.data();
}

void QExtTcpClient::setPacketDispatcher(const QSharedPointer<QExtTcpPacketDispatcher> &dispatcher)
{
    Q_D(QExtTcpClient);
    QMutexLocker mutexLocker(&d->m_packetDispatcherMutex);
    if (dispatcher != d->m_packetDispatcher)
    {
        d->m_socket->setPacketDispatcher(dispatcher);
        d->m_packetDispatcher = dispatcher;
        d->m_packetDispatcher->taskPool()->threadPool()->setMaxThreadCount(d->m_maxTaskThreadCount);
    }
}

void QExtTcpClient::initClient()
{
    Q_D(QExtTcpClient);
    QMutexLocker mutexLocker(&d->m_socketMutex);
    if (!d->m_socket.isNull())
    {
        d->m_socket->setParent(QEXT_NULLPTR);
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
        connect(d->m_socket.data(), SIGNAL(transferError(QExtTcpSocket::TransferErrorType)), this, SIGNAL(transferError(QExtTcpSocket::TransferErrorType)));

        connect(this, SIGNAL(tryToConnect(QString, quint16)), d->m_socket.data(), SLOT(connectToServer(QString, quint16)));
        connect(this, SIGNAL(tryToClose()), d->m_socket.data(), SLOT(closeSocket()));
        connect(this, SIGNAL(tryToAbort()), d->m_socket.data(), SLOT(abortSocket()));
    }
}

