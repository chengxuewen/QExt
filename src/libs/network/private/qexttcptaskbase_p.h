#ifndef QEXTTCPTASKBASE_P_H
#define QEXTTCPTASKBASE_P_H

#include <qextobject_p.h>

#include <qextnetworkglobal.h>
#include <qexttcptaskbase.h>

#include <QDateTime>
#include <QWaitCondition>
#include <QQueue>
#include <QPointer>
#include <QHash>
#include <QMutex>

class QEXTTcpPacketBase;
class QEXTTcpTaskBase;
class QEXT_NETWORK_API QEXTTcpTaskBasePrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTTcpTaskBasePrivate(QEXTTcpTaskBase *qq);
    ~QEXTTcpTaskBasePrivate();

    const QDateTime m_timestamp;
    QPointer<QEXTTcpTaskPoolBase> m_taskPool;

    mutable QMutex m_mutex;
    bool m_finished;
    QString m_errorString;

    quint64 m_id;
    static quint64 sm_id;

private:
    QEXT_DECLARE_PUBLIC(QEXTTcpTaskBase)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpTaskBasePrivate)
};

#endif // QEXTTCPTASKBASE_P_H
