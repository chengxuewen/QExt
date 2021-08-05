#ifndef QEXTTCPPACKETDISPATCHER_P_H
#define QEXTTCPPACKETDISPATCHER_P_H

#include <qextobject_p.h>

#include <qexttcpglobal.h>

#include <QMutex>
#include <QPointer>
#include <QQueue>



class QEXTTcpClient;
class QEXTTcpAbstractPacket;
class QEXTTcpPacketDispatcher;
class QEXT_TCP_API QEXTTcpPacketDispatcherPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTTcpPacketDispatcherPrivate(QEXTTcpPacketDispatcher *qq);
    ~QEXTTcpPacketDispatcherPrivate();

    mutable QMutex m_mutex;
    QQueue<QEXTTcpAbstractPacket *> m_packetQueue;
    QPointer<QEXTTcpClient> m_tcpClient;

private:
    QEXT_DECLARE_PUBLIC(QEXTTcpPacketDispatcher)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpPacketDispatcherPrivate)
};



#endif // QEXTTCPPACKETDISPATCHER_P_H
