#include <qexttcpclientproxy.h>
#include <qexttcpclientproxy_p.h>
#include <qexttcpabstracttask.h>
#include <qexttcpclient.h>

#include <QDebug>
#include <QTimer>



QEXTTcpClientProxyPrivate::QEXTTcpClientProxyPrivate(QEXTTcpClientProxy *qq)
    : QEXTObjectPrivate(qq)
{
    m_syncRequestReplyPacket = QEXT_NULLPTR;
}

QEXTTcpClientProxyPrivate::~QEXTTcpClientProxyPrivate()
{

}

bool QEXTTcpClientProxyPrivate::waitForReply(int msecs)
{
    m_mutex.lock();
    m_syncRequestWaitCancelled = false;
    m_syncRequestReplyPacket = QEXT_NULLPTR;
    bool success = m_syncRequestWaitCondition.wait(&m_mutex, msecs);
    success = success && !m_syncRequestWaitCancelled;
    m_mutex.unlock();
    return success;
}

void QEXTTcpClientProxyPrivate::setRequestFlag(QEXTTcpAbstractPacket *send)
{
    QMutexLocker mutexLocker(&m_mutex);
    m_sendPacket.reset(send);
    m_syncRequestReplyReceived = false;
}

void QEXTTcpClientProxyPrivate::setSyncRequestReplyFlag(QEXTTcpAbstractPacket *reply)
{
    m_syncRequestReplyPacket = reply;
    m_syncRequestReplyReceived = true;
    m_syncRequestWaitCondition.wakeAll();
}



QEXTTcpClientProxy::QEXTTcpClientProxy(QObject *parent)
    : QObject(parent), QEXTObject(*(new QEXTTcpClientProxyPrivate(this)))
{

}

QEXTTcpClientProxy::QEXTTcpClientProxy(QEXTTcpClientProxyPrivate &dd, QObject *parent)
    : QObject(parent), QEXTObject(dd)
{

}

QEXTTcpClientProxy::~QEXTTcpClientProxy()
{

}

QString QEXTTcpClientProxy::name() const
{
    QEXT_DC(QEXTTcpClientProxy);
    return d->m_name;
}

QEXTTcpClientSocket *QEXTTcpClientProxy::socket() const
{
    QEXT_DC(QEXTTcpClientProxy);
    QMutexLocker mutexLocker(&d->m_mutex);
    return d->m_socket.data();
}

void QEXTTcpClientProxy::setSocket(QEXTTcpClientSocket *socket)
{
    QEXT_D(QEXTTcpClientProxy);
    QMutexLocker mutexLocker(&d->m_mutex);
    d->m_socket = socket;
}

QEXTTcpAbstractPacket *QEXTTcpClientProxy::sendPacket() const
{
    QEXT_DC(QEXTTcpClientProxy);
    QMutexLocker mutexLocker(&d->m_mutex);
    return d->m_sendPacket.data();
}

void QEXTTcpClientProxy::cancelWait()
{
    QEXT_D(QEXTTcpClientProxy);
    d->m_mutex.lock();
    d->m_syncRequestWaitCancelled = true;
    d->m_syncRequestWaitCondition.wakeAll();
    d->m_mutex.unlock();
}

QEXTTcpAbstractPacketParser *QEXTTcpClientProxy::packetParser() const
{
    QEXT_DC(QEXTTcpClientProxy);
    return d->m_packetParser.data();
}

void QEXTTcpClientProxy::setPacketParser(QEXTTcpAbstractPacketParser *packetParser)
{
    QEXT_D(QEXTTcpClientProxy);
    d->m_packetParser.reset(packetParser);
}

bool QEXTTcpClientProxy::sendSyncRequestPacket(QEXTTcpAbstractPacket *send, QEXTTcpAbstractPacket **rcv)
{
    QEXT_D(QEXTTcpClientProxy);
    if (!d->m_socket->isOpen()) {
        qCritical() << "QEXTTcpClientProxy::sendSyncRequestPacket():socket noy open";
        return false;
    }
    bool success = this->sendRequestPacket(send);
    if (success) {
        success = d->waitForReply(3000);
        if (success) {
            *rcv = d->m_syncRequestReplyPacket;
            d->m_syncRequestReplyPacket = QEXT_NULLPTR;
            return true;
        }
    }
    return false;
}

bool QEXTTcpClientProxy::sendRequestPacket(QEXTTcpAbstractPacket *send)
{
    QEXT_D(QEXTTcpClientProxy);
    if (!d->m_socket->isOpen()) {
        qCritical() << "QEXTTcpClientProxy::sendRequestPacket():socket noy open";
        return false;
    }
    if (send && send->isValid()) {
        if (!d->m_packetParser.isNull()) {
            d->m_packetParser->setRequestPacket(send);
        }
        d->setRequestFlag(send);
        emit this->newSendPacketReady(send);
        return true;
    }
    return false;
}

bool QEXTTcpClientProxy::sendReplyPacket(QEXTTcpAbstractPacket *send)
{
    QEXT_D(QEXTTcpClientProxy);
    if (!d->m_socket->isOpen()) {
        qCritical() << "QEXTTcpClientProxy::sendReplyPacket():socket noy open";
        return false;
    }
    if (send && send->isValid()) {
        if (!d->m_packetParser.isNull()) {
            d->m_packetParser->setReplyPacket(send);
        }
        emit this->newSendPacketReady(send);
        return true;
    }
    return false;
}

bool QEXTTcpClientProxy::sendNotifyPacket(QEXTTcpAbstractPacket *send)
{
    QEXT_D(QEXTTcpClientProxy);
    if (!d->m_socket->isOpen()) {
        qCritical() << "QEXTTcpClientProxy::sendNotifyPacket():socket noy open";
        return false;
    }
    if (send && send->isValid()) {
        if (!d->m_packetParser.isNull()) {
            d->m_packetParser->setNotifyPacket(send);
        }
        emit this->newSendPacketReady(send);
        return true;
    }
    return false;
}

void QEXTTcpClientProxy::enqueuePacket(QEXTTcpAbstractPacket *packet)
{
    if (packet) {
        QEXT_D(QEXTTcpClientProxy);
        d->m_mutex.lock();
        if (!d->m_packetParser.isNull() && !d->m_sendPacket.isNull()) {
            if (d->m_packetParser->checkIsSyncReplyPacket(d->m_sendPacket.data(), packet)) {
                d->setSyncRequestReplyFlag(packet);
            }
        }
        d->m_mutex.unlock();
        if (!d->m_syncRequestReplyReceived) {
            QMutexLocker mutexLocker(&d->m_packetQueueMutex);
            d->m_receivedPacketQueue.enqueue(packet);
            emit this->newReceivePacketReady();
        }
    }
}

QEXTTcpAbstractPacket *QEXTTcpClientProxy::dequeuePacket()
{
    QEXT_D(QEXTTcpClientProxy);
    QMutexLocker mutexLocker(&d->m_packetQueueMutex);
    return d->m_receivedPacketQueue.dequeue();
}

void QEXTTcpClientProxy::setName(const QString &name)
{
    QEXT_D(QEXTTcpClientProxy);
    d->m_name = name;
}
