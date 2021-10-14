#ifndef QEXTTCPPACKETDISPATCHER_P_H
#define QEXTTCPPACKETDISPATCHER_P_H

#include <qextTcpGlobal.h>

#include <qextObject_p.h>

#include <QSharedPointer>
#include <QPointer>
#include <QHash>
#include <QMutex>

class QEXTTcpSocket;
class QEXTTcpFactory;
class QEXTTcpTaskPool;
class QEXTTcpPacketTransceiver;
class QEXTTcpPacketDispatcher;
class QEXT_TCP_API QEXTTcpPacketDispatcherPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTTcpPacketDispatcherPrivate(QEXTTcpPacketDispatcher *qq);
    ~QEXTTcpPacketDispatcherPrivate();

    QPointer<QEXTTcpSocket> m_socket;
    QSharedPointer<QEXTTcpTaskPool> m_taskPool;

    mutable QMutex m_taskMutex;
    QSharedPointer<QEXTTcpFactory> m_tcpFactory;

    mutable QMutex m_transceiverMutex;
    QHash<quint64, QPointer<QEXTTcpPacketTransceiver> > m_requestPacketIdToReceiverMap;

private:
    QEXT_DECL_PUBLIC(QEXTTcpPacketDispatcher)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpPacketDispatcherPrivate)
};

#endif // QEXTTCPPACKETDISPATCHER_P_H
