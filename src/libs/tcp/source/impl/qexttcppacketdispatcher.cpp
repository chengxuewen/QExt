#include <qexttcppacketdispatcher.h>
#include <qexttcppacketdispatcher_p.h>
#include <qexttcpclientproxy.h>
#include <qexttcpabstractpacket.h>
#include <qexttcpclient.h>

#include <QDebug>
#include <QTimer>



QEXTTcpPacketDispatcherPrivate::QEXTTcpPacketDispatcherPrivate(QEXTTcpPacketDispatcher *qq)
    : QEXTObjectPrivate(qq)
{

}

QEXTTcpPacketDispatcherPrivate::~QEXTTcpPacketDispatcherPrivate()
{

}



QEXTTcpPacketDispatcher::QEXTTcpPacketDispatcher(QObject *parent)
    : QEXTTcpAbstractPacketDispatcher(parent), QEXTObject(*(new QEXTTcpPacketDispatcherPrivate(this)))
{

}

QEXTTcpPacketDispatcher::QEXTTcpPacketDispatcher(QEXTTcpPacketDispatcherPrivate &dd, QObject *parent)
    : QEXTTcpAbstractPacketDispatcher(parent), QEXTObject(dd)
{

}

QEXTTcpPacketDispatcher::QEXTTcpPacketDispatcher(QEXTTcpClient *client, QObject *parent)
    : QEXTTcpAbstractPacketDispatcher(parent), QEXTObject(*(new QEXTTcpPacketDispatcherPrivate(this)))
{
    QEXT_DECL_D(QEXTTcpPacketDispatcher);
    d->m_tcpClient = client;
}

QEXTTcpPacketDispatcher::QEXTTcpPacketDispatcher(QEXTTcpPacketDispatcherPrivate &dd,
                                                 QEXTTcpClient *client, QObject *parent)
    : QEXTTcpAbstractPacketDispatcher(parent), QEXTObject(dd)
{
    QEXT_DECL_D(QEXTTcpPacketDispatcher);
    d->m_tcpClient = client;
}

QEXTTcpPacketDispatcher::~QEXTTcpPacketDispatcher()
{

}

QEXTTcpClient *QEXTTcpPacketDispatcher::tcpClient() const
{
    QEXT_DECL_DC(QEXTTcpPacketDispatcher);
    QMutexLocker mutexLocker(&d->m_mutex);
    return d->m_tcpClient.data();
}

void QEXTTcpPacketDispatcher::setTcpClient(QEXTTcpClient *client)
{
    QEXT_DECL_D(QEXTTcpPacketDispatcher);
    QMutexLocker mutexLocker(&d->m_mutex);
    d->m_tcpClient = client;
}

QList<QEXTTcpClientProxy *> QEXTTcpPacketDispatcher::allTcpClientProxyList() const
{
    QEXT_DECL_DC(QEXTTcpPacketDispatcher);
    QMutexLocker mutexLocker(&d->m_mutex);
    QList<QEXTTcpClientProxy *> proxyList;
    if (!d->m_tcpClient.isNull()) {
        proxyList = d->m_tcpClient->allProxies();
        proxyList.append(d->m_tcpClient);
    }
    return proxyList;
}

QEXTTcpAbstractPacket *QEXTTcpPacketDispatcher::dequeuePacket()
{
    QEXT_DECL_D(QEXTTcpPacketDispatcher);
    QMutexLocker mutexLocker(&d->m_mutex);
    if (d->m_packetQueue.isEmpty()) {
        return QEXT_DECL_NULLPTR;
    }
    return d->m_packetQueue.dequeue();
}

void QEXTTcpPacketDispatcher::enqueuePacket(QEXTTcpAbstractPacket *packet)
{
    if (packet) {
        QEXT_DECL_D(QEXTTcpPacketDispatcher);
        QMutexLocker mutexLocker(&d->m_mutex);
        d->m_packetQueue.enqueue(packet);
        QTimer::singleShot(0, this, SLOT(dispatchPacket()));
    }
}

int QEXTTcpPacketDispatcher::packetsCount() const
{
    QEXT_DECL_DC(QEXTTcpPacketDispatcher);
    QMutexLocker mutexLocker(&d->m_mutex);
    return d->m_packetQueue.size();
}

void QEXTTcpPacketDispatcher::dispatchPacket()
{
    QEXT_DECL_D(QEXTTcpPacketDispatcher);
    while (0 != this->packetsCount()) {
        QEXTTcpAbstractPacket *packet = this->dequeuePacket();
        if (packet) {
            if (!d->m_tcpClient.isNull()) {
                d->m_tcpClient->enqueuePacket(packet);
            }
        }
    }
}
