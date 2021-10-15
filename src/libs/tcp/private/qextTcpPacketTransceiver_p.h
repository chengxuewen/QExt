#ifndef QEXTTCPPACKETSYNCRECEIVER_P_H
#define QEXTTCPPACKETSYNCRECEIVER_P_H

#include <qextTcpGlobal.h>

#include <qextObject_p.h>
#include <qextId.h>

#include <QMutex>
#include <QQueue>
#include <QSet>
#include <QWaitCondition>
#include <QSharedPointer>
#include <QPointer>

class QEXTTcpPacketDispatcher;
class QEXTTcpPacketInterface;
class QEXTTcpPacketTransceiver;
class QEXT_TCP_API QEXTTcpPacketTransceiverPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTTcpPacketTransceiverPrivate(QEXTTcpPacketTransceiver *qq);
    ~QEXTTcpPacketTransceiverPrivate();

    QEXTId m_identityId;

    bool m_cancelled;
    bool m_receivedReply;
    QMutex m_syncMutex;
    QWaitCondition m_waitForSyncReply;

    mutable QMutex m_packetDispatcherMutex;
    QSharedPointer<QEXTTcpPacketDispatcher> m_packetDispatcher;

    mutable QMutex m_packetMutex;
    QSharedPointer<QEXTTcpPacketInterface> m_receivedPacket;
    QSharedPointer<QEXTTcpPacketInterface> m_sendPacket;
    QQueue<QSharedPointer<QEXTTcpPacketInterface> > m_receivedPacketQueue;

    QString m_lastError;

private:
    QEXT_DECL_PUBLIC(QEXTTcpPacketTransceiver)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpPacketTransceiverPrivate)
};

#endif // QEXTTCPPACKETSYNCRECEIVER_P_H
