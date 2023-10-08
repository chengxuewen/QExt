#include <private/qextTcpSocket_p.h>
#include <qextTcpPacketParser.h>
#include <qextTcpUtils.h>

#include <QDebug>
#include <QHostAddress>

int QEXTTcpSocketPrivate::sm_id = 0;

QEXTTcpSocketPrivate::QEXTTcpSocketPrivate(QEXTTcpSocket *q)
    : q_ptr(q)
{
    sm_id++;
    qRegisterMetaType<QAbstractSocket::SocketError>("QAbstractSocket::SocketError");
    qRegisterMetaType<QEXTTcpSocket::TransferErrorType>("QEXTTcpSocket::TransferErrorType");
}

QEXTTcpSocketPrivate::~QEXTTcpSocketPrivate()
{

}




QEXTTcpSocket::QEXTTcpSocket()
    : QTcpSocket(QEXT_DECL_NULLPTR), dd_ptr(new QEXTTcpSocketPrivate(this))
{
    Q_D(QEXTTcpSocket);
    connect(this, SIGNAL(connected()), this, SLOT(updateIdentityId()));
    connect(this, SIGNAL(readyRead()), this, SLOT(readPacket()));
    this->setPacketParser(QSharedPointer<QEXTTcpPacketParserInterface>(new QEXTTcpPacketParser));
    this->setPacketDispatcher(QSharedPointer<QEXTTcpPacketDispatcher>(new QEXTTcpPacketDispatcher(this)));
}

QEXTTcpSocket::QEXTTcpSocket(const QSharedPointer<QEXTTcpPacketParserInterface> &packetParser)
    : QTcpSocket(QEXT_DECL_NULLPTR), dd_ptr(new QEXTTcpSocketPrivate(this))
{
    Q_D(QEXTTcpSocket);
    connect(this, SIGNAL(connected()), this, SLOT(updateIdentityId()));
    connect(this, SIGNAL(readyRead()), this, SLOT(readPacket()));
    this->setPacketParser(packetParser);
    this->setPacketDispatcher(QSharedPointer<QEXTTcpPacketDispatcher>(new QEXTTcpPacketDispatcher(this)));
}

QEXTTcpSocket::QEXTTcpSocket(QEXTTcpSocketPrivate *d,
                             const QSharedPointer<QEXTTcpPacketParserInterface> &packetParser)
    : QTcpSocket(QEXT_DECL_NULLPTR), dd_ptr(d)
{
    connect(this, SIGNAL(connected()), this, SLOT(updateIdentityId()));
    connect(this, SIGNAL(readyRead()), this, SLOT(readPacket()));
    this->setPacketParser(packetParser);
    this->setPacketDispatcher(QSharedPointer<QEXTTcpPacketDispatcher>(new QEXTTcpPacketDispatcher(this)));
}

QEXTTcpSocket::~QEXTTcpSocket()
{

}

bool QEXTTcpSocket::isConnected() const
{
    return QTcpSocket::ConnectedState == this->state();
}

QSharedPointer<QEXTTcpPacketParserInterface> QEXTTcpSocket::packetParser() const
{
    Q_D(const QEXTTcpSocket);
    QMutexLocker mutexLocker(&d->m_packetParserMutex);
    return d->m_packetParser;
}

void QEXTTcpSocket::setPacketParser(const QSharedPointer<QEXTTcpPacketParserInterface> &packetParser)
{
    Q_D(QEXTTcpSocket);
    QMutexLocker mutexLocker(&d->m_packetParserMutex);
    if (packetParser != d->m_packetParser)
    {
        d->m_packetParser = packetParser;
    }
}

QSharedPointer<QEXTTcpPacketDispatcher> QEXTTcpSocket::packetDispatcher() const
{
    Q_D(const QEXTTcpSocket);
    QMutexLocker mutexLocker(&d->m_packetDispatcherMutex);
    return d->m_packetDispatcher;
}

void QEXTTcpSocket::setPacketDispatcher(const QSharedPointer<QEXTTcpPacketDispatcher> &packetDispatcher)
{
    Q_D(QEXTTcpSocket);
    QMutexLocker mutexLocker(&d->m_packetDispatcherMutex);
    if (packetDispatcher != d->m_packetDispatcher)
    {
        d->m_packetDispatcher = packetDispatcher;
    }
}

QSharedPointer<QThread> QEXTTcpSocket::workThread() const
{
    Q_D(const QEXTTcpSocket);
    return d->m_workThread;
}

QSharedPointer<QThread> QEXTTcpSocket::detachWorkThread()
{
    Q_D(QEXTTcpSocket);
    QSharedPointer<QThread> thread = d->m_workThread;
    if (!d->m_workThread.isNull())
    {
        this->setParent(QEXT_DECL_NULLPTR);
        thread->disconnect(this);
        d->m_workThread.clear();
    }
    return thread;
}

void QEXTTcpSocket::attatchWorkThread(const QSharedPointer<QThread> &thread)
{
    Q_D(QEXTTcpSocket);
    if (d->m_workThread != thread)
    {
        this->setParent(QEXT_DECL_NULLPTR);
        this->moveToThread(thread.data());
        d->m_workThread = thread;
    }
}

void QEXTTcpSocket::enqueueSendPacket(const QSharedPointer<QEXTTcpPacketInterface> &packet)
{
    Q_D(QEXTTcpSocket);
    QMutexLocker mutexLocker(&d->m_packetMutex);
    d->m_sendPacketQueue.enqueue(packet);
}

QEXTId QEXTTcpSocket::identityId() const
{
    Q_D(const QEXTTcpSocket);
    return d->m_identityId;
}

QString QEXTTcpSocket::transferErrorText(int error)
{
    switch (error)
    {
    case TransferError_SocketError:
        return tr("Socket error");
    case TransferError_SocketNotFound:
        return tr("Socket not found");
    case TransferError_SocketNotConnected:
        return tr("Socket not connected");
    case TransferError_PacketParserNotExist:
        return tr("Packet parser not exist");
    case TransferError_PacketParserReadFailed:
        return tr("Packet parser read failed");
    case TransferError_PacketParserWriteFailed:
        return tr("Packet parser write failed");
    case TransferError_PacketDispatcherNotExist:
        return tr("Packet dispatcher not exist");
    case TransferError_PacketTransceiverNotExist:
        return tr("Packet transceiver not exist");
    case TransferError_TaskPoolNotExist:
        return tr("Task pool not exist");
    default:
        break;
    }
    return "";
}

QEXTId QEXTTcpSocket::updateIdentityId()
{
    Q_D(QEXTTcpSocket);
    if (this->state() == QTcpSocket::ConnectedState)
    {
        d->m_peerAddress = this->peerAddress().toString();
        d->m_peerPort = this->peerPort();
        d->m_identityId = QString("%1:%2:%3")
                .arg(d->sm_id, 5, 10, QLatin1Char('0'))
                .arg(d->m_peerAddress)
                .arg(d->m_peerPort);
    }
    return d->m_identityId;
}

void QEXTTcpSocket::sendPacket()
{
    Q_D(QEXTTcpSocket);
    QMutexLocker mutexLocker(&d->m_packetMutex);
    if (!d->m_packetParser.isNull())
    {
        while (!d->m_sendPacketQueue.isEmpty())
        {
            QSharedPointer<QEXTTcpPacketInterface> packet = d->m_sendPacketQueue.dequeue();
            d->m_packetParser->writeData(this, packet);
            emit this->newPacketSend(QEXTTcpUtils::packetData(packet));
        }
        d->m_sendPacketQueue.clear();
    }
    else
    {
        emit this->transferError(QEXTTcpSocket::TransferError_PacketParserNotExist);
        emit this->transferErrorString(this->transferErrorText(QEXTTcpSocket::TransferError_PacketParserNotExist));
    }
}

void QEXTTcpSocket::connectToServer(const QString &ipAddress, quint16 port)
{
    this->abort();
    this->connectToHost(ipAddress, port);
}

void QEXTTcpSocket::closeSocket()
{
    this->close();
}

void QEXTTcpSocket::abortSocket()
{
    this->abort();
}

void QEXTTcpSocket::readPacket()
{
    Q_D(QEXTTcpSocket);
    //    qDebug() << "QEXTTcpSocket::readPacket():" << this->thread();
    if (!d->m_packetParser.isNull())
    {
        bool success = true;
        QSharedPointer<QEXTTcpPacketInterface> packet = d->m_packetParser->readData(this, success);
        if (!packet.isNull())
        {
            emit this->newPacketReceived(QEXTTcpUtils::packetData(packet));
            if (!d->m_packetDispatcher.isNull())
            {
                if (!d->m_packetDispatcher->dispatchPacket(packet))
                {
                    //                    QEXTTcpUtils::printPacket(packet);
                    emit this->transferError(QEXTTcpSocket::TransferError_PacketTransceiverNotExist);
                    emit this->transferErrorString(this->transferErrorText(QEXTTcpSocket::TransferError_PacketTransceiverNotExist));
                }
            }
            else
            {
                //                QEXTTcpUtils::printPacket(packet);
                emit this->transferError(QEXTTcpSocket::TransferError_PacketDispatcherNotExist);
                emit this->transferErrorString(this->transferErrorText(QEXTTcpSocket::TransferError_PacketDispatcherNotExist));
            }
        }
        else if (!success)
        {
            this->readAll();
            emit this->transferError(QEXTTcpSocket::TransferError_PacketParserReadFailed);
            emit this->transferErrorString(this->transferErrorText(QEXTTcpSocket::TransferError_PacketParserReadFailed));
        }
    }
    else
    {
        this->readAll();
        emit this->transferError(QEXTTcpSocket::TransferError_PacketParserNotExist);
        emit this->transferErrorString(this->transferErrorText(QEXTTcpSocket::TransferError_PacketParserNotExist));
    }
}
