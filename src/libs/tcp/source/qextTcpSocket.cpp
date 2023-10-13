#include <private/qextTcpSocket_p.h>
#include <qextTcpPacketParser.h>
#include <qextTcpUtils.h>

#include <QDebug>
#include <QHostAddress>

int QExtTcpSocketPrivate::sm_id = 0;

QExtTcpSocketPrivate::QExtTcpSocketPrivate(QExtTcpSocket *q)
    : q_ptr(q)
{
    sm_id++;
    qRegisterMetaType<QAbstractSocket::SocketError>("QAbstractSocket::SocketError");
    qRegisterMetaType<QExtTcpSocket::TransferErrorType>("QExtTcpSocket::TransferErrorType");
}

QExtTcpSocketPrivate::~QExtTcpSocketPrivate()
{

}




QExtTcpSocket::QExtTcpSocket()
    : QTcpSocket(QEXT_DECL_NULLPTR), dd_ptr(new QExtTcpSocketPrivate(this))
{
    Q_D(QExtTcpSocket);
    connect(this, SIGNAL(connected()), this, SLOT(updateIdentityId()));
    connect(this, SIGNAL(readyRead()), this, SLOT(readPacket()));
    this->setPacketParser(QSharedPointer<QExtTcpPacketParserInterface>(new QExtTcpPacketParser));
    this->setPacketDispatcher(QSharedPointer<QExtTcpPacketDispatcher>(new QExtTcpPacketDispatcher(this)));
}

QExtTcpSocket::QExtTcpSocket(const QSharedPointer<QExtTcpPacketParserInterface> &packetParser)
    : QTcpSocket(QEXT_DECL_NULLPTR), dd_ptr(new QExtTcpSocketPrivate(this))
{
    Q_D(QExtTcpSocket);
    connect(this, SIGNAL(connected()), this, SLOT(updateIdentityId()));
    connect(this, SIGNAL(readyRead()), this, SLOT(readPacket()));
    this->setPacketParser(packetParser);
    this->setPacketDispatcher(QSharedPointer<QExtTcpPacketDispatcher>(new QExtTcpPacketDispatcher(this)));
}

QExtTcpSocket::QExtTcpSocket(QExtTcpSocketPrivate *d,
                             const QSharedPointer<QExtTcpPacketParserInterface> &packetParser)
    : QTcpSocket(QEXT_DECL_NULLPTR), dd_ptr(d)
{
    connect(this, SIGNAL(connected()), this, SLOT(updateIdentityId()));
    connect(this, SIGNAL(readyRead()), this, SLOT(readPacket()));
    this->setPacketParser(packetParser);
    this->setPacketDispatcher(QSharedPointer<QExtTcpPacketDispatcher>(new QExtTcpPacketDispatcher(this)));
}

QExtTcpSocket::~QExtTcpSocket()
{

}

bool QExtTcpSocket::isConnected() const
{
    return QTcpSocket::ConnectedState == this->state();
}

QSharedPointer<QExtTcpPacketParserInterface> QExtTcpSocket::packetParser() const
{
    Q_D(const QExtTcpSocket);
    QMutexLocker mutexLocker(&d->m_packetParserMutex);
    return d->m_packetParser;
}

void QExtTcpSocket::setPacketParser(const QSharedPointer<QExtTcpPacketParserInterface> &packetParser)
{
    Q_D(QExtTcpSocket);
    QMutexLocker mutexLocker(&d->m_packetParserMutex);
    if (packetParser != d->m_packetParser)
    {
        d->m_packetParser = packetParser;
    }
}

QSharedPointer<QExtTcpPacketDispatcher> QExtTcpSocket::packetDispatcher() const
{
    Q_D(const QExtTcpSocket);
    QMutexLocker mutexLocker(&d->m_packetDispatcherMutex);
    return d->m_packetDispatcher;
}

void QExtTcpSocket::setPacketDispatcher(const QSharedPointer<QExtTcpPacketDispatcher> &packetDispatcher)
{
    Q_D(QExtTcpSocket);
    QMutexLocker mutexLocker(&d->m_packetDispatcherMutex);
    if (packetDispatcher != d->m_packetDispatcher)
    {
        d->m_packetDispatcher = packetDispatcher;
    }
}

QSharedPointer<QThread> QExtTcpSocket::workThread() const
{
    Q_D(const QExtTcpSocket);
    return d->m_workThread;
}

QSharedPointer<QThread> QExtTcpSocket::detachWorkThread()
{
    Q_D(QExtTcpSocket);
    QSharedPointer<QThread> thread = d->m_workThread;
    if (!d->m_workThread.isNull())
    {
        this->setParent(QEXT_DECL_NULLPTR);
        thread->disconnect(this);
        d->m_workThread.clear();
    }
    return thread;
}

void QExtTcpSocket::attatchWorkThread(const QSharedPointer<QThread> &thread)
{
    Q_D(QExtTcpSocket);
    if (d->m_workThread != thread)
    {
        this->setParent(QEXT_DECL_NULLPTR);
        this->moveToThread(thread.data());
        d->m_workThread = thread;
    }
}

void QExtTcpSocket::enqueueSendPacket(const QSharedPointer<QExtTcpPacketInterface> &packet)
{
    Q_D(QExtTcpSocket);
    QMutexLocker mutexLocker(&d->m_packetMutex);
    d->m_sendPacketQueue.enqueue(packet);
}

QExtId QExtTcpSocket::identityId() const
{
    Q_D(const QExtTcpSocket);
    return d->m_identityId;
}

QString QExtTcpSocket::transferErrorText(int error)
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

QExtId QExtTcpSocket::updateIdentityId()
{
    Q_D(QExtTcpSocket);
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

void QExtTcpSocket::sendPacket()
{
    Q_D(QExtTcpSocket);
    QMutexLocker mutexLocker(&d->m_packetMutex);
    if (!d->m_packetParser.isNull())
    {
        while (!d->m_sendPacketQueue.isEmpty())
        {
            QSharedPointer<QExtTcpPacketInterface> packet = d->m_sendPacketQueue.dequeue();
            d->m_packetParser->writeData(this, packet);
            emit this->newPacketSend(QExtTcpUtils::packetData(packet));
        }
        d->m_sendPacketQueue.clear();
    }
    else
    {
        emit this->transferError(QExtTcpSocket::TransferError_PacketParserNotExist);
        emit this->transferErrorString(this->transferErrorText(QExtTcpSocket::TransferError_PacketParserNotExist));
    }
}

void QExtTcpSocket::connectToServer(const QString &ipAddress, quint16 port)
{
    this->abort();
    this->connectToHost(ipAddress, port);
}

void QExtTcpSocket::closeSocket()
{
    this->close();
}

void QExtTcpSocket::abortSocket()
{
    this->abort();
}

void QExtTcpSocket::readPacket()
{
    Q_D(QExtTcpSocket);
    //    qDebug() << "QExtTcpSocket::readPacket():" << this->thread();
    if (!d->m_packetParser.isNull())
    {
        bool success = true;
        QSharedPointer<QExtTcpPacketInterface> packet = d->m_packetParser->readData(this, success);
        if (!packet.isNull())
        {
            emit this->newPacketReceived(QExtTcpUtils::packetData(packet));
            if (!d->m_packetDispatcher.isNull())
            {
                if (!d->m_packetDispatcher->dispatchPacket(packet))
                {
                    //                    QExtTcpUtils::printPacket(packet);
                    emit this->transferError(QExtTcpSocket::TransferError_PacketTransceiverNotExist);
                    emit this->transferErrorString(this->transferErrorText(QExtTcpSocket::TransferError_PacketTransceiverNotExist));
                }
            }
            else
            {
                //                QExtTcpUtils::printPacket(packet);
                emit this->transferError(QExtTcpSocket::TransferError_PacketDispatcherNotExist);
                emit this->transferErrorString(this->transferErrorText(QExtTcpSocket::TransferError_PacketDispatcherNotExist));
            }
        }
        else if (!success)
        {
            this->readAll();
            emit this->transferError(QExtTcpSocket::TransferError_PacketParserReadFailed);
            emit this->transferErrorString(this->transferErrorText(QExtTcpSocket::TransferError_PacketParserReadFailed));
        }
    }
    else
    {
        this->readAll();
        emit this->transferError(QExtTcpSocket::TransferError_PacketParserNotExist);
        emit this->transferErrorString(this->transferErrorText(QExtTcpSocket::TransferError_PacketParserNotExist));
    }
}
