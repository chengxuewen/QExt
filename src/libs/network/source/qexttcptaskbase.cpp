#include <qexttcptaskbase.h>
#include <qexttcptaskbase_p.h>

#include <QDebug>

quint64 QEXTTcpTaskBasePrivate::sm_id = 0;

QEXTTcpTaskBasePrivate::QEXTTcpTaskBasePrivate(QEXTTcpTaskBase *qq)
    : QEXTObjectPrivate(qq),
      m_timestamp(QDateTime::currentDateTime())
{
    m_id = ++sm_id;
    m_finished = false;
}

QEXTTcpTaskBasePrivate::~QEXTTcpTaskBasePrivate()
{

}



QEXTTcpTaskBase::QEXTTcpTaskBase(QEXTTcpTaskPoolBase *taskPool, QObject *parent)
    : QEXTObject(*(new QEXTTcpTaskBasePrivate(this)))
{
    QEXT_D(QEXTTcpTaskBase);
    d->m_taskPool = taskPool;
}

QEXTTcpTaskBase::QEXTTcpTaskBase(QEXTTcpTaskBasePrivate &dd, QEXTTcpTaskPoolBase *taskPool, QObject *parent)
    : QEXTObject(dd)
{
    QEXT_D(QEXTTcpTaskBase);
    d->m_taskPool = taskPool;
}

QEXTTcpTaskBase::~QEXTTcpTaskBase()
{

}

QEXTTcpTaskPoolBase *QEXTTcpTaskBase::taskPool() const
{
    QEXT_DC(QEXTTcpTaskBase);
    return d->m_taskPool.data();
}

quint64 QEXTTcpTaskBase::id() const
{
    QEXT_DC(QEXTTcpTaskBase);
    return d->m_id;
}

QDateTime QEXTTcpTaskBase::timestamp() const
{
    QEXT_DC(QEXTTcpTaskBase);
    return d->m_timestamp;
}

bool QEXTTcpTaskBase::isFinished() const
{
    QEXT_DC(QEXTTcpTaskBase);
    QMutexLocker mutexLocker(&d->m_mutex);
    return d->m_finished;
}

bool QEXTTcpTaskBase::isErrored() const
{
    QEXT_DC(QEXTTcpTaskBase);
    QMutexLocker mutexLocker(&d->m_mutex);
    return !d->m_errorString.isEmpty();
}

QString QEXTTcpTaskBase::errorString() const
{
    QEXT_DC(QEXTTcpTaskBase);
    QMutexLocker mutexLocker(&d->m_mutex);
    return d->m_errorString;
}

void QEXTTcpTaskBase::setErrorString(const QString &string)
{
    QEXT_D(QEXTTcpTaskBase);
    QMutexLocker mutexLocker(&d->m_mutex);
    d->m_errorString = string;
}

void QEXTTcpTaskBase::setFinished(const bool &finished)
{
    QEXT_D(QEXTTcpTaskBase);
    QMutexLocker mutexLocker(&d->m_mutex);
    d->m_finished = finished;
}
