#ifndef _QEXTTCPPACKETSYNCRECEIVER_P_H
#define _QEXTTCPPACKETSYNCRECEIVER_P_H

#include <qextTcpPacketTransceiver.h>
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
class QEXT_TCP_API QEXTTcpPacketTransceiverPrivate
{
public:
    explicit QEXTTcpPacketTransceiverPrivate(QEXTTcpPacketTransceiver *q);
    virtual ~QEXTTcpPacketTransceiverPrivate();

    QEXTTcpPacketTransceiver * const q_ptr;

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
    Q_DECLARE_PUBLIC(QEXTTcpPacketTransceiver)
    Q_DISABLE_COPY(QEXTTcpPacketTransceiverPrivate)
};

#endif // _QEXTTCPPACKETSYNCRECEIVER_P_H
