#include <private/qextTcpPacketTransceiver_p.h>
#include <qextTcpPacketDispatcher.h>
#include <qextTcpPacketParserInterface.h>

#include <QDebug>
#include <QDateTime>

QExtTcpPacketTransceiverPrivate::QExtTcpPacketTransceiverPrivate(QExtTcpPacketTransceiver *q)
    : q_ptr(q)
{
    m_cancelled = false;
    m_receivedReply = false;
}

QExtTcpPacketTransceiverPrivate::~QExtTcpPacketTransceiverPrivate()
{
    m_waitForSyncReply.wakeAll();
}

QExtTcpPacketTransceiver::QExtTcpPacketTransceiver(const QSharedPointer<QExtTcpPacketDispatcher> &dispatcher)
    : QObject(QEXT_NULLPTR), dd_ptr(new QExtTcpPacketTransceiverPrivate(this))
{
    Q_D(QExtTcpPacketTransceiver);
    d->m_packetDispatcher = dispatcher;
}

QExtTcpPacketTransceiver::QExtTcpPacketTransceiver(QExtTcpPacketTransceiverPrivate *d)
    : QObject(QEXT_NULLPTR), dd_ptr(d)
{
}

QExtTcpPacketTransceiver::QExtTcpPacketTransceiver(QExtTcpPacketTransceiverPrivate *d,
                                                   const QSharedPointer<QExtTcpPacketDispatcher> &dispatcher)
    : QObject(QEXT_NULLPTR), dd_ptr(d)
{
    dd_ptr->m_packetDispatcher = dispatcher;
}

QExtTcpPacketTransceiver::~QExtTcpPacketTransceiver()
{

}

QExtTagId QExtTcpPacketTransceiver::identityId() const
{
    Q_D(const QExtTcpPacketTransceiver);
    return d->m_identityId;
}

bool QExtTcpPacketTransceiver::isSocketValid() const
{
    return this->dispatcher()->isSocketValid();
}

bool QExtTcpPacketTransceiver::send(const QSharedPointer<QExtTcpPacketInterface> &sendPacket)
{
    Q_D(QExtTcpPacketTransceiver);
    QSharedPointer<QExtTcpPacketDispatcher> dispatcher = this->dispatcher();
    if (!dispatcher->isSocketValid())
    {
        this->setError("socket not connected");
        return false;
    }
    QSharedPointer<QExtTcpPacketParserInterface> packetParser = dispatcher->packetParser();
    if (packetParser.isNull())
    {
        this->setError("packetParser not exist");
        return false;
    }
    return dispatcher->sendPacket(this, sendPacket);
}

bool QExtTcpPacketTransceiver::sendReply(const QSharedPointer<QExtTcpPacketInterface> &sendPacket,
                                         QSharedPointer<QExtTcpPacketInterface> &receivedPacket)
{
    Q_D(QExtTcpPacketTransceiver);
    QSharedPointer<QExtTcpPacketDispatcher> dispatcher = this->dispatcher();
    if (!dispatcher->isSocketValid())
    {
        this->setError("socket not connected");
        return false;
    }
    QSharedPointer<QExtTcpPacketParserInterface> packetParser = dispatcher->packetParser();
    if (packetParser.isNull())
    {
        this->setError("packetParser not exist");
        return false;
    }
    if (!packetParser->setReplyPacket(sendPacket, receivedPacket))
    {
        this->setError("setReplyPacket failed");
        return false;
    }
    return dispatcher->sendPacket(this, sendPacket);
}

bool QExtTcpPacketTransceiver::sendNotify(const QSharedPointer<QExtTcpPacketInterface> &sendPacket)
{
    Q_D(QExtTcpPacketTransceiver);
    QSharedPointer<QExtTcpPacketDispatcher> dispatcher = this->dispatcher();
    if (!dispatcher->isSocketValid())
    {
        this->setError("socket not connected");
        return false;
    }
    QSharedPointer<QExtTcpPacketParserInterface> packetParser = dispatcher->packetParser();
    if (packetParser.isNull())
    {
        this->setError("packetParser not exist");
        return false;
    }
    if (!packetParser->setNotifyPacket(sendPacket))
    {
        this->setError("setNotifyPacket failed");
        return false;
    }
    return dispatcher->sendPacket(this, sendPacket);
}

bool QExtTcpPacketTransceiver::sendRequest(const QSharedPointer<QExtTcpPacketInterface> &sendPacket)
{
    Q_D(QExtTcpPacketTransceiver);
    QSharedPointer<QExtTcpPacketDispatcher> dispatcher = this->dispatcher();
    if (!dispatcher->isSocketValid())
    {
        this->setError("socket not connected");
        return false;
    }
    QSharedPointer<QExtTcpPacketParserInterface> packetParser = dispatcher->packetParser();
    if (packetParser.isNull())
    {
        this->setError("packetParser not exist");
        return false;
    }
    if (!packetParser->setRequestPacket(sendPacket))
    {
        this->setError("setRequestPacket failed");
        return false;
    }
    return dispatcher->sendPacket(this, sendPacket);
}

bool QExtTcpPacketTransceiver::sendRequestSync(const QSharedPointer<QExtTcpPacketInterface> &sendPacket,
                                               QSharedPointer<QExtTcpPacketInterface> &receivedPacket,
                                               quint16 timeoutMsecs)
{
    Q_D(QExtTcpPacketTransceiver);
    this->setRequestSyncFlag(sendPacket);
    if (this->sendRequest(sendPacket))
    {
        if (this->waitForData(timeoutMsecs))
        {
            receivedPacket = this->syncReceivedPacket();
            return true;
        }
    }
    return false;
}

bool QExtTcpPacketTransceiver::waitForData(int msecs)
{
    Q_D(QExtTcpPacketTransceiver);
    d->m_syncMutex.lock();
    d->m_cancelled = false;
    bool success = true;
    while (success && !d->m_receivedReply)
    {
        success = d->m_waitForSyncReply.wait(&d->m_syncMutex, msecs);
    }
    success = success && !d->m_cancelled;
    d->m_syncMutex.unlock();
    return success;
}

void QExtTcpPacketTransceiver::cancelWait()
{
    Q_D(QExtTcpPacketTransceiver);
    d->m_syncMutex.lock();
    d->m_cancelled = true;
    d->m_waitForSyncReply.wakeAll();
    d->m_syncMutex.unlock();
}

QSharedPointer<QExtTcpPacketInterface> QExtTcpPacketTransceiver::syncSendedPacket() const
{
    Q_D(const QExtTcpPacketTransceiver);
    QMutexLocker mutexLocker(&d->m_packetMutex);
    return d->m_sendPacket;
}

QSharedPointer<QExtTcpPacketInterface> QExtTcpPacketTransceiver::syncReceivedPacket() const
{
    Q_D(const QExtTcpPacketTransceiver);
    QMutexLocker mutexLocker(&d->m_packetMutex);
    return d->m_receivedPacket;
}

int QExtTcpPacketTransceiver::packetCount() const
{
    Q_D(const QExtTcpPacketTransceiver);
    QMutexLocker mutexLocker(&d->m_packetMutex);
    return d->m_receivedPacketQueue.size();
}

bool QExtTcpPacketTransceiver::isPacketQueueEmpty() const
{
    Q_D(const QExtTcpPacketTransceiver);
    QMutexLocker mutexLocker(&d->m_packetMutex);
    return d->m_receivedPacketQueue.isEmpty();
}

QSharedPointer<QExtTcpPacketInterface> QExtTcpPacketTransceiver::dequeuePacket()
{
    Q_D(QExtTcpPacketTransceiver);
    QMutexLocker mutexLocker(&d->m_packetMutex);
    if (!d->m_receivedPacketQueue.isEmpty())
    {
        return d->m_receivedPacketQueue.dequeue();
    }
    return QSharedPointer<QExtTcpPacketInterface>();
}

void QExtTcpPacketTransceiver::enqueuePacket(const QSharedPointer<QExtTcpPacketInterface> &packet)
{
    Q_D(QExtTcpPacketTransceiver);
    QSharedPointer<QExtTcpPacketParserInterface> packetParser = d->m_packetDispatcher->packetParser();
    if (packetParser->checkIsSyncReplyPacket(this->syncSendedPacket(), packet))
    {
        this->resetRequestSyncFlag(packet);
    }
    else
    {
        QMutexLocker locker(&d->m_packetMutex);
        d->m_receivedPacketQueue.enqueue(packet);
        emit this->packetReady();
    }
}

QSharedPointer<QExtTcpPacketParserInterface> QExtTcpPacketTransceiver::packetParser() const
{
    Q_D(const QExtTcpPacketTransceiver);
    QMutexLocker locker(&d->m_packetDispatcherMutex);
    return d->m_packetDispatcher->packetParser();
}

QSharedPointer<QExtTcpPacketDispatcher> QExtTcpPacketTransceiver::dispatcher() const
{
    Q_D(const QExtTcpPacketTransceiver);
    QMutexLocker locker(&d->m_packetDispatcherMutex);
    return d->m_packetDispatcher;
}

QString QExtTcpPacketTransceiver::lastError() const
{
    Q_D(const QExtTcpPacketTransceiver);
    return d->m_lastError;
}

void QExtTcpPacketTransceiver::setRequestSyncFlag(const QSharedPointer<QExtTcpPacketInterface> &sendPacket)
{
    Q_D(QExtTcpPacketTransceiver);
    QMutexLocker locker(&d->m_syncMutex);
    if (sendPacket)
    {
        d->m_receivedReply = false;
        QMutexLocker locker(&d->m_packetMutex);
        d->m_receivedPacket.clear();
        d->m_sendPacket = sendPacket;
    }
}

void QExtTcpPacketTransceiver::resetRequestSyncFlag(const QSharedPointer<QExtTcpPacketInterface> &receivedPacket)
{
    Q_D(QExtTcpPacketTransceiver);
    QMutexLocker locker(&d->m_packetMutex);
    d->m_receivedReply = true;
    d->m_receivedPacket = receivedPacket;
    d->m_sendPacket.clear();
    d->m_waitForSyncReply.wakeAll();
}

void QExtTcpPacketTransceiver::setError(const QString &error)
{
    Q_D(QExtTcpPacketTransceiver);
    d->m_lastError = error;
    emit this->error(d->m_lastError);
}
