#include <qextTcpClient.h>
#include <qextTcpClient_p.h>
#include <qextTcpPacketDispatcher.h>
#include <qextTcpPacketParserInterface.h>
#include <qextTcpPacketParser.h>
#include <qextTcpSocket.h>

#include <QDebug>
#include <QHostAddress>

QEXTTcpClientPrivate::QEXTTcpClientPrivate(QEXTTcpClient *qq)
    : QEXTTcpPacketTransceiverPrivate(qq)
{
    qRegisterMetaType<QAbstractSocket::SocketState>("QAbstractSocket::SocketState");
    qRegisterMetaType<QAbstractSocket::SocketError>("QAbstractSocket::SocketError");
    qRegisterMetaType<QEXTTcpSocket::TransferErrorType>("QEXTTcpSocket::TransferErrorType");

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
    this->setPacketParser(QSharedPointer<QEXTTcpPacketParserInterface>(new QEXTTcpPacketParser));
    this->setPacketDispatcher(QSharedPointer<QEXTTcpPacketDispatcher>(new QEXTTcpPacketDispatcher(d->m_socket)));
}

QEXTTcpClient::QEXTTcpClient(const QSharedPointer<QEXTTcpPacketParserInterface> &packetParser)
    : QEXTTcpPacketTransceiver(*(new QEXTTcpClientPrivate(this)))
{
    QEXT_DECL_D(QEXTTcpClient);
    this->initClient();
    this->setPacketParser(packetParser);
    this->setPacketDispatcher(QSharedPointer<QEXTTcpPacketDispatcher>(new QEXTTcpPacketDispatcher(d->m_socket)));
}

QEXTTcpClient::QEXTTcpClient(const QSharedPointer<QEXTTcpPacketDispatcher> &dispatcher)
    : QEXTTcpPacketTransceiver(*(new QEXTTcpClientPrivate(this)))
{
    QEXT_DECL_D(QEXTTcpClient);
    this->initClient();
    this->setPacketParser(QSharedPointer<QEXTTcpPacketParserInterface>(new QEXTTcpPacketParser));
    this->setPacketDispatcher(dispatcher);
}

QEXTTcpClient::QEXTTcpClient(const QSharedPointer<QEXTTcpPacketParserInterface> &packetParser,
                             const QSharedPointer<QEXTTcpPacketDispatcher> &dispatcher)
    : QEXTTcpPacketTransceiver(*(new QEXTTcpClientPrivate(this)))
{
    QEXT_DECL_D(QEXTTcpClient);
    this->initClient();
    this->setPacketParser(packetParser);
    this->setPacketDispatcher(dispatcher);
}

QEXTTcpClient::QEXTTcpClient(QEXTTcpClientPrivate &dd)
    : QEXTTcpPacketTransceiver(dd)
{
    QEXT_DECL_D(QEXTTcpClient);
    this->initClient();
    this->setPacketParser(QSharedPointer<QEXTTcpPacketParserInterface>(new QEXTTcpPacketParser));
    this->setPacketDispatcher(QSharedPointer<QEXTTcpPacketDispatcher>(new QEXTTcpPacketDispatcher(d->m_socket)));
}

QEXTTcpClient::QEXTTcpClient(QEXTTcpClientPrivate &dd,
                             const QSharedPointer<QEXTTcpPacketDispatcher> &dispatcher)
    : QEXTTcpPacketTransceiver(dd)
{
    QEXT_DECL_D(QEXTTcpClient);
    this->initClient();
    this->setPacketParser(QSharedPointer<QEXTTcpPacketParserInterface>(new QEXTTcpPacketParser));
    this->setPacketDispatcher(dispatcher);
}

QEXTTcpClient::QEXTTcpClient(QEXTTcpClientPrivate &dd,
                             const QSharedPointer<QEXTTcpPacketParserInterface> &packetParser)
    : QEXTTcpPacketTransceiver(dd)
{
    QEXT_DECL_D(QEXTTcpClient);
    this->initClient();
    this->setPacketParser(packetParser);
    this->setPacketDispatcher(QSharedPointer<QEXTTcpPacketDispatcher>(new QEXTTcpPacketDispatcher(d->m_socket)));
}

QEXTTcpClient::QEXTTcpClient(QEXTTcpClientPrivate &dd,
                             const QSharedPointer<QEXTTcpPacketParserInterface> &packetParser,
                             const QSharedPointer<QEXTTcpPacketDispatcher> &dispatcher)
    : QEXTTcpPacketTransceiver(dd)
{
    QEXT_DECL_D(QEXTTcpClient);
    this->initClient();
    this->setPacketParser(packetParser);
    this->setPacketDispatcher(dispatcher);
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
    return d->m_socket->peerAddress().toString();
}

quint16 QEXTTcpClient::serverPort() const
{
    QEXT_DECL_DC(QEXTTcpClient);
    return d->m_socket->peerPort();
}

QSharedPointer<QEXTTcpPacketParserInterface> QEXTTcpClient::packetParser() const
{
    QEXT_DECL_DC(QEXTTcpClient);
    QMutexLocker mutexLocker(&d->m_packetParserMutex);
    return d->m_packetParser;
}

void QEXTTcpClient::setPacketParser(const QSharedPointer<QEXTTcpPacketParserInterface> packetParser)
{
    QEXT_DECL_D(QEXTTcpClient);
    QMutexLocker mutexLocker(&d->m_packetParserMutex);
    if (packetParser != d->m_packetParser)
    {
        d->m_packetParser = packetParser;
        d->m_socket->setPacketParser(packetParser);
    }
}

QSharedPointer<QEXTTcpPacketDispatcher> QEXTTcpClient::packetDispatcher() const
{
    QEXT_DECL_DC(QEXTTcpClient);
    QMutexLocker mutexLocker(&d->m_packetDispatcherMutex);
    return d->m_packetDispatcher;
}

void QEXTTcpClient::setPacketDispatcher(const QSharedPointer<QEXTTcpPacketDispatcher> &dispatcher)
{
    QEXT_DECL_D(QEXTTcpClient);
    QMutexLocker mutexLocker(&d->m_packetDispatcherMutex);
    if (dispatcher != d->m_packetDispatcher)
    {
        d->m_packetDispatcher = dispatcher;
        d->m_socket->setPacketDispatcher(dispatcher);
    }
}

void QEXTTcpClient::initClient()
{
    QEXT_DECL_D(QEXTTcpClient);
    QMutexLocker locker(&d->m_socketMutex);
    if (!d->m_socket.isNull())
    {
        d->m_socket->setParent(QEXT_DECL_NULLPTR);
        d->m_socket->moveToThread(d->m_socketThread.data());
        connect(d->m_socket.data(), SIGNAL(connected()), this, SIGNAL(socketConnected()));
        connect(d->m_socket.data(), SIGNAL(disconnected()), this, SIGNAL(socketDisconnected()));
        connect(d->m_socket.data(), SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SIGNAL(socketStateChanged(QAbstractSocket::SocketState)));
        connect(d->m_socket.data(), SIGNAL(error(QAbstractSocket::SocketError)), this, SIGNAL(socketError(QAbstractSocket::SocketError)));
        connect(d->m_socket.data(), SIGNAL(transferError(QEXTTcpSocket::TransferErrorType)), this, SIGNAL(transferError(QEXTTcpSocket::TransferErrorType)));

        connect(this, SIGNAL(tryToConnect(QString,quint16)), d->m_socket.data(), SLOT(connectToServer(QString,quint16)));
        connect(this, SIGNAL(tryToClose()), d->m_socket.data(), SLOT(closeSocket()));
        connect(this, SIGNAL(tryToAbort()), d->m_socket.data(), SLOT(abortSocket()));
    }
}

