#include <qexttcpabstracttask.h>
#include <qexttcpabstracttask_p.h>

#include <QDebug>



quint64 QEXTTcpAbstractTaskPrivate::sm_id = 0;

QEXTTcpAbstractTaskPrivate::QEXTTcpAbstractTaskPrivate(QEXTTcpAbstractTask *qq)
    : QEXTObjectPrivate(qq),
      m_timestamp(QDateTime::currentDateTime())
{
    m_id = ++sm_id;
    m_finished = false;
}

QEXTTcpAbstractTaskPrivate::~QEXTTcpAbstractTaskPrivate()
{

}



QEXTTcpAbstractTask::QEXTTcpAbstractTask(QEXTTcpAbstractTaskPool *taskPool, QObject *parent)
    : QEXTObject(*(new QEXTTcpAbstractTaskPrivate(this)))
{
    QEXT_D(QEXTTcpAbstractTask);
    d->m_taskPool = taskPool;
}

QEXTTcpAbstractTask::QEXTTcpAbstractTask(QEXTTcpAbstractTaskPrivate &dd, QEXTTcpAbstractTaskPool *taskPool, QObject *parent)
    : QEXTObject(dd)
{
    QEXT_D(QEXTTcpAbstractTask);
    d->m_taskPool = taskPool;
}

QEXTTcpAbstractTask::~QEXTTcpAbstractTask()
{

}

QEXTTcpAbstractTaskPool *QEXTTcpAbstractTask::taskPool() const
{
    QEXT_DC(QEXTTcpAbstractTask);
    return d->m_taskPool.data();
}

quint64 QEXTTcpAbstractTask::id() const
{
    QEXT_DC(QEXTTcpAbstractTask);
    return d->m_id;
}

QDateTime QEXTTcpAbstractTask::timestamp() const
{
    QEXT_DC(QEXTTcpAbstractTask);
    return d->m_timestamp;
}

bool QEXTTcpAbstractTask::isFinished() const
{
    QEXT_DC(QEXTTcpAbstractTask);
    QMutexLocker mutexLocker(&d->m_mutex);
    return d->m_finished;
}

bool QEXTTcpAbstractTask::isErrored() const
{
    QEXT_DC(QEXTTcpAbstractTask);
    QMutexLocker mutexLocker(&d->m_mutex);
    return !d->m_errorString.isEmpty();
}

QString QEXTTcpAbstractTask::errorString() const
{
    QEXT_DC(QEXTTcpAbstractTask);
    QMutexLocker mutexLocker(&d->m_mutex);
    return d->m_errorString;
}

void QEXTTcpAbstractTask::setErrorString(const QString &string)
{
    QEXT_D(QEXTTcpAbstractTask);
    QMutexLocker mutexLocker(&d->m_mutex);
    d->m_errorString = string;
}

void QEXTTcpAbstractTask::setFinished(const bool &finished)
{
    QEXT_D(QEXTTcpAbstractTask);
    QMutexLocker mutexLocker(&d->m_mutex);
    d->m_finished = finished;
}
