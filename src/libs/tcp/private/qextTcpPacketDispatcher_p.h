#ifndef QEXTTCPPACKETDISPATCHER_P_H
#define QEXTTCPPACKETDISPATCHER_P_H

#include <qextTcpGlobal.h>

#include <qextobject_p.h>

#include <QSharedPointer>
#include <QPointer>
#include <QHash>
#include <QMutex>

class QEXTTcpSocket;
class QEXTTcpTaskPool;
class QEXTTcpPacketTransceiver;
class QEXTTcpTaskFactory;
class QEXTTcpPacketDispatcher;
class QEXT_TCP_API QEXTTcpPacketDispatcherPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTTcpPacketDispatcherPrivate(QEXTTcpPacketDispatcher *qq);
    ~QEXTTcpPacketDispatcherPrivate();

    mutable QMutex m_socketMutex;
    QWeakPointer<QEXTTcpSocket> m_socket;

    mutable QMutex m_taskMutex;
    QSharedPointer<QEXTTcpTaskFactory> m_taskFactory;
    QSharedPointer<QEXTTcpTaskPool> m_taskPool;

    mutable QMutex m_transceiverMutex;
    QHash<quint64, QPointer<QEXTTcpPacketTransceiver> > m_requestPacketIdToReceiverMap;

private:
    QEXT_DECL_PUBLIC(QEXTTcpPacketDispatcher)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpPacketDispatcherPrivate)
};

#endif // QEXTTCPPACKETDISPATCHER_P_H
