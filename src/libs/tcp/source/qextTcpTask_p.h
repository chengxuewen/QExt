#ifndef _QEXTTCPTASK_P_H
#define _QEXTTCPTASK_P_H

#include <qextTcpTask.h>

#include <QDateTime>
#include <QWaitCondition>
#include <QQueue>
#include <QPointer>
#include <QHash>
#include <QMutex>

class QExtTcpPacketInterface;
class QExtTcpPacketTransceiver;
class QExtTcpTask;
class QEXT_TCP_API QExtTcpTaskPrivate
{
public:
    explicit QExtTcpTaskPrivate(QExtTcpTask *q);
    virtual ~QExtTcpTaskPrivate();

    QExtTcpTask * const q_ptr;

    const QDateTime m_timestamp;
    QSharedPointer<QExtTcpPacketTransceiver> m_packetTransceiver;
    QSharedPointer<QExtTcpPacketInterface> m_receivedPacket;

    mutable QMutex m_mutex;
    bool m_finished;
    QString m_errorString;

    quint64 m_id;
    static quint64 sm_id;

private:
    Q_DECLARE_PUBLIC(QExtTcpTask)
    Q_DISABLE_COPY(QExtTcpTaskPrivate)
};

#endif // _QEXTTCPTASK_P_H
