#ifndef _QEXTTCPPACKETSYNCRECEIVER_P_H
#define _QEXTTCPPACKETSYNCRECEIVER_P_H

#include <qextTcpPacketTransceiver.h>
#include <qextTag.h>

#include <QMutex>
#include <QQueue>
#include <QSet>
#include <QWaitCondition>
#include <QSharedPointer>
#include <QPointer>

class QExtTcpPacketDispatcher;
class QExtTcpPacketInterface;
class QExtTcpPacketTransceiver;
class QEXT_TCP_API QExtTcpPacketTransceiverPrivate
{
public:
    explicit QExtTcpPacketTransceiverPrivate(QExtTcpPacketTransceiver *q);
    virtual ~QExtTcpPacketTransceiverPrivate();

    QExtTcpPacketTransceiver * const q_ptr;

    QExtTag m_identityId;

    bool m_cancelled;
    bool m_receivedReply;
    QMutex m_syncMutex;
    QWaitCondition m_waitForSyncReply;

    mutable QMutex m_packetDispatcherMutex;
    QSharedPointer<QExtTcpPacketDispatcher> m_packetDispatcher;

    mutable QMutex m_packetMutex;
    QSharedPointer<QExtTcpPacketInterface> m_receivedPacket;
    QSharedPointer<QExtTcpPacketInterface> m_sendPacket;
    QQueue<QSharedPointer<QExtTcpPacketInterface> > m_receivedPacketQueue;

    QString m_lastError;

private:
    Q_DECLARE_PUBLIC(QExtTcpPacketTransceiver)
    Q_DISABLE_COPY(QExtTcpPacketTransceiverPrivate)
};

#endif // _QEXTTCPPACKETSYNCRECEIVER_P_H
