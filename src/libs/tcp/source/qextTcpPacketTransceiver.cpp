#include <qextTcpPacketTransceiver.h>
#include <qextTcpPacketTransceiver_p.h>
#include <qextTcpPacketDispatcher.h>
#include <qextTcpPacketParserInterface.h>

#include <QDebug>
#include <QDateTime>

QEXTTcpPacketTransceiverPrivate::QEXTTcpPacketTransceiverPrivate(QEXTTcpPacketTransceiver *qq)
    : QEXTObjectPrivate(qq)
{
    m_cancelled = false;
    m_receivedReply = false;
}

QEXTTcpPacketTransceiverPrivate::~QEXTTcpPacketTransceiverPrivate()
{
    m_waitForSyncReply.wakeAll();
}

QEXTTcpPacketTransceiver::QEXTTcpPacketTransceiver(const QSharedPointer<QEXTTcpPacketDispatcher> &dispatcher)
    : QObject(QEXT_DECL_NULLPTR), QEXTObject(*(new QEXTTcpPacketTransceiverPrivate(this)))
{
    QEXT_DECL_D(QEXTTcpPacketTransceiver);
    d->m_packetDispatcher = dispatcher;
}

QEXTTcpPacketTransceiver::QEXTTcpPacketTransceiver(QEXTTcpPacketTransceiverPrivate &dd)
    : QObject(QEXT_DECL_NULLPTR), QEXTObject(dd)
{
}

QEXTTcpPacketTransceiver::QEXTTcpPacketTransceiver(QEXTTcpPacketTransceiverPrivate &dd,
                                                   const QSharedPointer<QEXTTcpPacketDispatcher> &dispatcher)
    : QObject(QEXT_DECL_NULLPTR), QEXTObject(dd)
{
    QEXT_DECL_D(QEXTTcpPacketTransceiver);
    d->m_packetDispatcher = dispatcher;
}

QEXTTcpPacketTransceiver::~QEXTTcpPacketTransceiver()
{

}

QEXTId QEXTTcpPacketTransceiver::identityId() const
{
    QEXT_DECL_DC(QEXTTcpPacketTransceiver);
    return d->m_identityId;
}

bool QEXTTcpPacketTransceiver::isSocketValid() const
{
    return this->dispatcher()->isSocketValid();
}

bool QEXTTcpPacketTransceiver::send(const QSharedPointer<QEXTTcpPacketInterface> &sendPacket)
{
    QEXT_DECL_D(QEXTTcpPacketTransceiver);
    QSharedPointer<QEXTTcpPacketDispatcher> dispatcher = this->dispatcher();
    if (!dispatcher->isSocketValid())
    {
        this->setError("socket not connected");
        return false;
    }
    QSharedPointer<QEXTTcpPacketParserInterface> packetParser = dispatcher->packetParser();
    if (packetParser.isNull())
    {
        this->setError("packetParser not exist");
        return false;
    }
    return dispatcher->sendPacket(this, sendPacket);
}

bool QEXTTcpPacketTransceiver::sendReply(const QSharedPointer<QEXTTcpPacketInterface> &sendPacket,
                                         QSharedPointer<QEXTTcpPacketInterface> &receivedPacket)
{
    QEXT_DECL_D(QEXTTcpPacketTransceiver);
    QSharedPointer<QEXTTcpPacketDispatcher> dispatcher = this->dispatcher();
    if (!dispatcher->isSocketValid())
    {
        this->setError("socket not connected");
        return false;
    }
    QSharedPointer<QEXTTcpPacketParserInterface> packetParser = dispatcher->packetParser();
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

bool QEXTTcpPacketTransceiver::sendNotify(const QSharedPointer<QEXTTcpPacketInterface> &sendPacket)
{
    QEXT_DECL_D(QEXTTcpPacketTransceiver);
    QSharedPointer<QEXTTcpPacketDispatcher> dispatcher = this->dispatcher();
    if (!dispatcher->isSocketValid())
    {
        this->setError("socket not connected");
        return false;
    }
    QSharedPointer<QEXTTcpPacketParserInterface> packetParser = dispatcher->packetParser();
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

bool QEXTTcpPacketTransceiver::sendRequest(const QSharedPointer<QEXTTcpPacketInterface> &sendPacket)
{
    QEXT_DECL_D(QEXTTcpPacketTransceiver);
    QSharedPointer<QEXTTcpPacketDispatcher> dispatcher = this->dispatcher();
    if (!dispatcher->isSocketValid())
    {
        this->setError("socket not connected");
        return false;
    }
    QSharedPointer<QEXTTcpPacketParserInterface> packetParser = dispatcher->packetParser();
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

bool QEXTTcpPacketTransceiver::sendRequestSync(const QSharedPointer<QEXTTcpPacketInterface> &sendPacket,
                                               QSharedPointer<QEXTTcpPacketInterface> &receivedPacket,
                                               quint16 timeoutMsecs)
{
    QEXT_DECL_D(QEXTTcpPacketTransceiver);
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

bool QEXTTcpPacketTransceiver::waitForData(int msecs)
{
    QEXT_DECL_D(QEXTTcpPacketTransceiver);
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

void QEXTTcpPacketTransceiver::cancelWait()
{
    QEXT_DECL_D(QEXTTcpPacketTransceiver);
    d->m_syncMutex.lock();
    d->m_cancelled = true;
    d->m_waitForSyncReply.wakeAll();
    d->m_syncMutex.unlock();
}

QSharedPointer<QEXTTcpPacketInterface> QEXTTcpPacketTransceiver::syncSendedPacket() const
{
    QEXT_DECL_DC(QEXTTcpPacketTransceiver);
    QMutexLocker mutexLocker(&d->m_packetMutex);
    return d->m_sendPacket;
}

QSharedPointer<QEXTTcpPacketInterface> QEXTTcpPacketTransceiver::syncReceivedPacket() const
{
    QEXT_DECL_DC(QEXTTcpPacketTransceiver);
    QMutexLocker mutexLocker(&d->m_packetMutex);
    return d->m_receivedPacket;
}

int QEXTTcpPacketTransceiver::packetCount() const
{
    QEXT_DECL_DC(QEXTTcpPacketTransceiver);
    QMutexLocker mutexLocker(&d->m_packetMutex);
    return d->m_receivedPacketQueue.size();
}

bool QEXTTcpPacketTransceiver::isPacketQueueEmpty() const
{
    QEXT_DECL_DC(QEXTTcpPacketTransceiver);
    QMutexLocker mutexLocker(&d->m_packetMutex);
    return d->m_receivedPacketQueue.isEmpty();
}

QSharedPointer<QEXTTcpPacketInterface> QEXTTcpPacketTransceiver::dequeuePacket()
{
    QEXT_DECL_D(QEXTTcpPacketTransceiver);
    QMutexLocker mutexLocker(&d->m_packetMutex);
    if (!d->m_receivedPacketQueue.isEmpty())
    {
        return d->m_receivedPacketQueue.dequeue();
    }
    return QSharedPointer<QEXTTcpPacketInterface>();
}

void QEXTTcpPacketTransceiver::enqueuePacket(const QSharedPointer<QEXTTcpPacketInterface> &packet)
{
    QEXT_DECL_D(QEXTTcpPacketTransceiver);
    QSharedPointer<QEXTTcpPacketParserInterface> packetParser = d->m_packetDispatcher->packetParser();
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

QSharedPointer<QEXTTcpPacketParserInterface> QEXTTcpPacketTransceiver::packetParser() const
{
    QEXT_DECL_DC(QEXTTcpPacketTransceiver);
    QMutexLocker locker(&d->m_packetDispatcherMutex);
    return d->m_packetDispatcher->packetParser();
}

QSharedPointer<QEXTTcpPacketDispatcher> QEXTTcpPacketTransceiver::dispatcher() const
{
    QEXT_DECL_DC(QEXTTcpPacketTransceiver);
    QMutexLocker locker(&d->m_packetDispatcherMutex);
    return d->m_packetDispatcher;
}

QString QEXTTcpPacketTransceiver::lastError() const
{
    QEXT_DECL_DC(QEXTTcpPacketTransceiver);
    return d->m_lastError;
}

void QEXTTcpPacketTransceiver::setRequestSyncFlag(const QSharedPointer<QEXTTcpPacketInterface> &sendPacket)
{
    QEXT_DECL_D(QEXTTcpPacketTransceiver);
    QMutexLocker locker(&d->m_syncMutex);
    if (sendPacket)
    {
        d->m_receivedReply = false;
        QMutexLocker locker(&d->m_packetMutex);
        d->m_receivedPacket.clear();
        d->m_sendPacket = sendPacket;
    }
}

void QEXTTcpPacketTransceiver::resetRequestSyncFlag(const QSharedPointer<QEXTTcpPacketInterface> &receivedPacket)
{
    QEXT_DECL_D(QEXTTcpPacketTransceiver);
    QMutexLocker locker(&d->m_packetMutex);
    d->m_receivedReply = true;
    d->m_receivedPacket = receivedPacket;
    d->m_sendPacket.clear();
    d->m_waitForSyncReply.wakeAll();
}

void QEXTTcpPacketTransceiver::setError(const QString &error)
{
    QEXT_DECL_D(QEXTTcpPacketTransceiver);
    d->m_lastError = error;
    emit this->error(d->m_lastError);
}
