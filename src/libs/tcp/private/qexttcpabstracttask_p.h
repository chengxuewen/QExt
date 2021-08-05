#ifndef QEXTTCPABSTRACTTASK_P_H
#define QEXTTCPABSTRACTTASK_P_H

#include <qextobject_p.h>

#include <qexttcpglobal.h>
#include <qexttcpabstracttask.h>

#include <QDateTime>
#include <QWaitCondition>
#include <QQueue>
#include <QPointer>
#include <QHash>
#include <QMutex>



class QEXTTcpAbstractPacket;
class QEXTTcpAbstractTask;
class QEXT_TCP_API QEXTTcpAbstractTaskPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTTcpAbstractTaskPrivate(QEXTTcpAbstractTask *qq);
    ~QEXTTcpAbstractTaskPrivate();

    const QDateTime m_timestamp;
    QPointer<QEXTTcpAbstractTaskPool> m_taskPool;

    mutable QMutex m_mutex;
    bool m_finished;
    QString m_errorString;

    quint64 m_id;
    static quint64 sm_id;

private:
    QEXT_DECLARE_PUBLIC(QEXTTcpAbstractTask)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpAbstractTaskPrivate)
};



#endif // QEXTTCPABSTRACTTASK_P_H
