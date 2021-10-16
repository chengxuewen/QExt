#ifndef _QEXTTCPTASK_P_H
#define _QEXTTCPTASK_P_H

#include <qextObject_p.h>

#include <qextTcpGlobal.h>
#include <qextTcpTask.h>

#include <QDateTime>
#include <QWaitCondition>
#include <QQueue>
#include <QPointer>
#include <QHash>
#include <QMutex>

class QEXTTcpPacketInterface;
class QEXTTcpPacketTransceiver;
class QEXTTcpTask;
class QEXT_TCP_API QEXTTcpTaskPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTTcpTaskPrivate(QEXTTcpTask *qq);
    ~QEXTTcpTaskPrivate();

    const QDateTime m_timestamp;
    QSharedPointer<QEXTTcpPacketTransceiver> m_packetTransceiver;
    QSharedPointer<QEXTTcpPacketInterface> m_receivedPacket;

    mutable QMutex m_mutex;
    bool m_finished;
    QString m_errorString;

    quint64 m_id;
    static quint64 sm_id;

private:
    QEXT_DECL_PUBLIC(QEXTTcpTask)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpTaskPrivate)
};

#endif // _QEXTTCPTASK_P_H
