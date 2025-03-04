#include <private/qextTcpTaskPool_p.h>
#include <qextTcpPacketDispatcher.h>
#include <qextTcpTask.h>

#include <QQueue>

QExtTcpTaskPoolPrivate::QExtTcpTaskPoolPrivate(QExtTcpTaskPool *q)
    : q_ptr(q)
{

}

QExtTcpTaskPoolPrivate::~QExtTcpTaskPoolPrivate()
{
    QQueue<QExtTcpTask *>::iterator iter;
    for (iter = m_waitingTaskQueue.begin(); iter != m_waitingTaskQueue.end(); ++iter)
    {
        (*iter)->disconnect();
        (*iter)->deleteLater();
    }
    m_waitingTaskQueue.clear();
    m_runningTaskSet.clear();
    m_idToTaskMap.clear();
    m_threadPool.waitForDone(1000);
}

QExtTcpTaskPool::QExtTcpTaskPool(QExtTcpPacketDispatcher *dispatcher)
    : QObject(QEXT_NULLPTR), dd_ptr(new QExtTcpTaskPoolPrivate(this))
{
    Q_D(QExtTcpTaskPool);
    d->m_packetDispatcher = dispatcher;
}

QExtTcpTaskPool::~QExtTcpTaskPool()
{

}

bool QExtTcpTaskPool::isWaitingTaskEmpty() const
{
    Q_D(const QExtTcpTaskPool);
    return 0 == d->m_waitingTaskQueue.count();
}

bool QExtTcpTaskPool::isRunningTaskEmpty() const
{
    Q_D(const QExtTcpTaskPool);
    return 0 == d->m_runningTaskSet.count();
}

int QExtTcpTaskPool::waitingTaskCount() const
{
    Q_D(const QExtTcpTaskPool);
    return d->m_waitingTaskQueue.count();
}

int QExtTcpTaskPool::runningTaskCount() const
{
    Q_D(const QExtTcpTaskPool);
    return d->m_runningTaskSet.count();
}

QThreadPool *QExtTcpTaskPool::threadPool() const
{
    Q_D(const QExtTcpTaskPool);
    return const_cast<QThreadPool *>(&d->m_threadPool);
}

void QExtTcpTaskPool::enqueueTask(QExtTcpTask *task)
{
    Q_D(QExtTcpTaskPool);
    QMutexLocker mutexLocker(&d->m_mutex);
    task->setParent(QEXT_NULLPTR);
    task->setAutoDelete(true);
    connect(task, SIGNAL(aboutToBeDelete(quint64)), this, SLOT(onTaskFinished(quint64)));
    connect(task, SIGNAL(error(QString)), this, SLOT(onTaskError(QString)));
    d->m_idToTaskMap.insert(task->id(), task);
    d->m_idToIdentityIdMap.insert(task->id(), task->identityId());
    if (d->m_threadPool.tryStart(task))
    {
        d->m_runningTaskSet.insert(task);
    }
    else
    {
        d->m_waitingTaskQueue.enqueue(task);
    }
}

void QExtTcpTaskPool::onTaskError(const QString &error)
{
    Q_D(QExtTcpTaskPool);
    QMutexLocker mutexLocker(&d->m_mutex);
    QExtTcpTask *task = qobject_cast<QExtTcpTask *>(this->sender());
    quint64 id = d->m_idToTaskMap.key(task);
    QExtTagId identityId = d->m_idToIdentityIdMap.value(id);
    emit this->taskError(identityId, error);
}

void QExtTcpTaskPool::onTaskFinished(quint64 id)
{
    Q_D(QExtTcpTaskPool);
    QMutexLocker mutexLocker(&d->m_mutex);
    QExtTcpTask *task = d->m_idToTaskMap.value(id);
    QExtTagId identityId = d->m_idToIdentityIdMap.value(id);
    d->m_idToTaskMap.remove(id);
    d->m_idToIdentityIdMap.remove(id);
    d->m_runningTaskSet.remove(task);
    emit this->taskFinished(identityId);
    if (!d->m_waitingTaskQueue.isEmpty())
    {
        task = d->m_waitingTaskQueue.head();
        if (d->m_threadPool.tryStart(task))
        {
            d->m_waitingTaskQueue.dequeue();
            d->m_runningTaskSet.insert(task);
        }
    }
}
