#ifndef QEXTTCPPACKETDISPATCHER_P_H
#define QEXTTCPPACKETDISPATCHER_P_H

#include <qextobject_p.h>

#include <qextnetworkglobal.h>

#include <QMutex>
#include <QPointer>
#include <QQueue>

class QEXTTcpClient;
class QEXTTcpPacketBase;
class QEXTTcpPacketDispatcher;
class QEXT_NETWORK_API QEXTTcpPacketDispatcherPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTTcpPacketDispatcherPrivate(QEXTTcpPacketDispatcher *qq);
    ~QEXTTcpPacketDispatcherPrivate();

    mutable QMutex m_mutex;
    QQueue<QEXTTcpPacketBase *> m_packetQueue;
    QPointer<QEXTTcpClient> m_tcpClient;

private:
    QEXT_DECLARE_PUBLIC(QEXTTcpPacketDispatcher)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpPacketDispatcherPrivate)
};

#endif // QEXTTCPPACKETDISPATCHER_P_H
