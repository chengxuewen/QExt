#ifndef _QEXTTCPPACKETDISPATCHER_P_H
#define _QEXTTCPPACKETDISPATCHER_P_H

#include <qextTcpGlobal.h>

#include <QSharedPointer>
#include <QPointer>
#include <QHash>
#include <QMutex>

class QEXTTcpSocket;
class QEXTTcpFactory;
class QEXTTcpTaskPool;
class QEXTTcpPacketTransceiver;
class QEXTTcpPacketDispatcher;
class QEXT_TCP_API QEXTTcpPacketDispatcherPrivate
{
public:
    explicit QEXTTcpPacketDispatcherPrivate(QEXTTcpPacketDispatcher *q);
    virtual ~QEXTTcpPacketDispatcherPrivate();

    QEXTTcpPacketDispatcher * const q_ptr;

    QPointer<QEXTTcpSocket> m_socket;
    QSharedPointer<QEXTTcpTaskPool> m_taskPool;

    mutable QMutex m_taskMutex;
    QSharedPointer<QEXTTcpFactory> m_tcpFactory;

    mutable QMutex m_transceiverMutex;
    QHash<quint64, QPointer<QEXTTcpPacketTransceiver> > m_requestPacketIdToReceiverMap;

private:
    QEXT_DECL_PUBLIC(QEXTTcpPacketDispatcher)
    QEXT_DECL_DISABLE_COPY(QEXTTcpPacketDispatcherPrivate)
};

#endif // _QEXTTCPPACKETDISPATCHER_P_H
