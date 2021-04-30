#include <qexttcpclientsocket.h>
#include <qexttcpclientsocket_p.h>
#include <qexttcppacketbase.h>
#include <qexttcppacketdispatcher.h>

#include <QHostAddress>
#include <QDebug>
#include <QTimer>

QEXTTcpClientSocketPrivate::QEXTTcpClientSocketPrivate(QEXTTcpClientSocket *qq)
    : QEXTTcpSocketPrivate(qq)
{

}

QEXTTcpClientSocketPrivate::~QEXTTcpClientSocketPrivate()
{

}



QEXTTcpClientSocket::QEXTTcpClientSocket(QObject *parent)
    : QEXTTcpSocket(*(new QEXTTcpClientSocketPrivate(this)), parent)
{
    qRegisterMetaType<QAbstractSocket::SocketError>("QAbstractSocket::SocketError");

    QEXT_D(QEXTTcpClientSocket);
    connect(this, SIGNAL(readyRead()), this, SLOT(readPacket()));
}

QEXTTcpClientSocket::~QEXTTcpClientSocket()
{

}

QEXTTcpPacketParserBase *QEXTTcpClientSocket::packetParser() const
{
    QEXT_DC(QEXTTcpClientSocket);
    QMutexLocker mutexLocker(&d->m_packetParserMutex);
    return d->m_packetParser.data();
}

void QEXTTcpClientSocket::setPacketParser(QEXTTcpPacketParserBase *packetParser)
{
    QEXT_D(QEXTTcpClientSocket);
    QMutexLocker mutexLocker(&d->m_packetParserMutex);
    d->m_packetParser.reset(packetParser);
}

QEXTTcpPacketDispatcherBase *QEXTTcpClientSocket::packetDispatcher() const
{
    QEXT_DC(QEXTTcpClientSocket);
    QMutexLocker mutexLocker(&d->m_packetDispatcherMutex);
    return d->m_packetDispatcher.data();
}

void QEXTTcpClientSocket::setPacketDispatcher(QEXTTcpPacketDispatcherBase *packetDispatcher)
{
    QEXT_D(QEXTTcpClientSocket);
    QMutexLocker mutexLocker(&d->m_packetDispatcherMutex);
    d->m_packetDispatcher = packetDispatcher;
}

QString QEXTTcpClientSocket::serverAddress() const
{
    QEXT_DC(QEXTTcpClientSocket);
    QMutexLocker mutexLocker(&d->m_socketMutex);
    return d->m_serverIpAddr;
}

quint16 QEXTTcpClientSocket::serverPort() const
{
    QEXT_DC(QEXTTcpClientSocket);
    QMutexLocker mutexLocker(&d->m_socketMutex);
    return d->m_serverPort;
}

void QEXTTcpClientSocket::connectToServer()
{
    QEXT_D(QEXTTcpClientSocket);
    QMutexLocker mutexLocker(&d->m_socketMutex);
    this->connectToHost(d->m_serverIpAddr, d->m_serverPort);
}

void QEXTTcpClientSocket::closeSocket()
{
    QEXT_D(QEXTTcpClientSocket);
    this->close();
}

void QEXTTcpClientSocket::abortSocket()
{
    QEXT_D(QEXTTcpClientSocket);
    this->abort();
}

void QEXTTcpClientSocket::setServerAddress(const QString &ipAddr)
{
    QEXT_D(QEXTTcpClientSocket);
    QMutexLocker mutexLocker(&d->m_socketMutex);
    d->m_serverIpAddr = ipAddr;
}

void QEXTTcpClientSocket::setServerPort(quint16 port)
{
    QEXT_D(QEXTTcpClientSocket);
    QMutexLocker mutexLocker(&d->m_socketMutex);
    d->m_serverPort = port;
}

void QEXTTcpClientSocket::sendPacket()
{
    QEXT_D(QEXTTcpClientSocket);
    QMutexLocker mutexLocker(&d->m_packetMutex);
    if (this->isOpen()) {
        qDebug() << "QEXTTcpClientSocket::sendPacket():packetSize=" << d->m_sendPacketQueue.size();
        while (!d->m_sendPacketQueue.isEmpty()) {
            QEXTTcpPacketBase *packet = d->m_sendPacketQueue.dequeue();
            if (this->packetParser()) {
                qint64 size = this->packetParser()->writeData(this, packet);
                if (packet->header()->headerSize() + packet->header()->contentSize() != size) {
                    emit this->transferError(TransferError_PacketParserWriteFailed);
                }
            } else {
                emit this->transferError(TransferError_PacketParserNotExist);
            }
        }
    } else {
        emit this->transferError(TransferError_SocketNotConnected);
    }
}

void QEXTTcpClientSocket::enqueueSendPacket(QEXTTcpPacketBase *packet)
{
    QEXT_D(QEXTTcpClientSocket);
    d->m_packetMutex.lock();
    qDebug() << "QEXTTcpClientSocket::enqueueSendPacket():packetSize=" << d->m_sendPacketQueue.size();
    d->m_sendPacketQueue.enqueue(packet);
    d->m_packetMutex.unlock();
    QTimer::singleShot(0, this, SLOT(sendPacket()));
}

void QEXTTcpClientSocket::updateIdentityId()
{
    QEXT_D(QEXTTcpClientSocket);
    if (!d->m_identityId.isValid()) {
        d->m_identityId = QString("%1:%2:%3").arg(d->sm_id, 5, 10, QLatin1Char('0'))
                .arg(d->m_serverIpAddr).arg(d->m_serverPort);
    }
}

void QEXTTcpClientSocket::readPacket()
{
    QEXT_D(QEXTTcpClientSocket);
    d->m_packetParserMutex.lock();
    if (!d->m_packetParser.isNull()) {
        bool success = true;
        QEXTTcpPacketBase *packet = d->m_packetParser->readData(this, success);
        if (packet) {
            QMutexLocker mutexLocker(&d->m_packetDispatcherMutex);
            if (d->m_packetDispatcher.isNull()) {
                emit this->packetNotDispatched(packet);
                emit this->transferError(TransferError_PacketDispatcherNotExist);
            } else {
                d->m_packetDispatcher->enqueuePacket(packet);
            }
        } else if (!success) {
            this->readAll();
            emit this->transferError(TransferError_PacketParserReadFailed);
        }
    } else {
        this->readAll();
        emit this->transferError(TransferError_PacketParserNotExist);
    }
    d->m_packetParserMutex.unlock();
    if (this->bytesAvailable()) {
        this->readPacket();
    }
}
