#ifndef _QEXTTCPPACKETDISPATCHER_P_H
#define _QEXTTCPPACKETDISPATCHER_P_H

#include <qextTcpPacketDispatcher.h>

#include <QSharedPointer>
#include <QPointer>
#include <QHash>
#include <QMutex>

class QExtTcpSocket;
class QExtTcpFactory;
class QExtTcpTaskPool;
class QExtTcpPacketTransceiver;
class QExtTcpPacketDispatcher;
class QEXT_TCP_API QExtTcpPacketDispatcherPrivate
{
public:
    explicit QExtTcpPacketDispatcherPrivate(QExtTcpPacketDispatcher *q);
    virtual ~QExtTcpPacketDispatcherPrivate();

    QExtTcpPacketDispatcher * const q_ptr;

    QPointer<QExtTcpSocket> m_socket;
    QSharedPointer<QExtTcpTaskPool> m_taskPool;

    mutable QMutex m_taskMutex;
    QSharedPointer<QExtTcpFactory> m_tcpFactory;

    mutable QMutex m_transceiverMutex;
    QHash<quint64, QPointer<QExtTcpPacketTransceiver> > m_requestPacketIdToReceiverMap;

private:
    Q_DECLARE_PUBLIC(QExtTcpPacketDispatcher)
    Q_DISABLE_COPY(QExtTcpPacketDispatcherPrivate)
};

#endif // _QEXTTCPPACKETDISPATCHER_P_H
