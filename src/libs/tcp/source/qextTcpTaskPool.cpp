#include <qextTcpTaskPool.h>
#include <qextTcpTaskPool_p.h>
#include <qextTcpPacketDispatcher.h>
#include <qextTcpTask.h>

#include <QQueue>

QEXTTcpTaskPoolPrivate::QEXTTcpTaskPoolPrivate(QEXTTcpTaskPool *qq)
    : QEXTObjectPrivate(qq)
{

}

QEXTTcpTaskPoolPrivate::~QEXTTcpTaskPoolPrivate()
{
    QQueue<QEXTTcpTask *>::iterator iter;
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

QEXTTcpTaskPool::QEXTTcpTaskPool(QEXTTcpPacketDispatcher *dispatcher)
    : QObject(QEXT_DECL_NULLPTR), QEXTObject(*(new QEXTTcpTaskPoolPrivate(this)))
{
    QEXT_DECL_D(QEXTTcpTaskPool);
    d->m_packetDispatcher = dispatcher;
}

QEXTTcpTaskPool::~QEXTTcpTaskPool()
{

}

bool QEXTTcpTaskPool::isWaitingTaskEmpty() const
{
    QEXT_DECL_DC(QEXTTcpTaskPool);
    return 0 == d->m_waitingTaskQueue.count();
}

bool QEXTTcpTaskPool::isRunningTaskEmpty() const
{
    QEXT_DECL_DC(QEXTTcpTaskPool);
    return 0 == d->m_runningTaskSet.count();
}

int QEXTTcpTaskPool::waitingTaskCount() const
{
    QEXT_DECL_DC(QEXTTcpTaskPool);
    return d->m_waitingTaskQueue.count();
}

int QEXTTcpTaskPool::runningTaskCount() const
{
    QEXT_DECL_DC(QEXTTcpTaskPool);
    return d->m_runningTaskSet.count();
}

QThreadPool *QEXTTcpTaskPool::threadPool() const
{
    QEXT_DECL_DC(QEXTTcpTaskPool);
    return const_cast<QThreadPool *>(&d->m_threadPool);
}

void QEXTTcpTaskPool::enqueueTask(QEXTTcpTask *task)
{
    QEXT_DECL_D(QEXTTcpTaskPool);
    QMutexLocker mutexLocker(&d->m_mutex);
    task->setParent(QEXT_DECL_NULLPTR);
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

void QEXTTcpTaskPool::onTaskError(const QString &error)
{
    QEXT_DECL_D(QEXTTcpTaskPool);
    QMutexLocker mutexLocker(&d->m_mutex);
    QEXTTcpTask *task = qobject_cast<QEXTTcpTask *>(this->sender());
    quint64 id = d->m_idToTaskMap.key(task);
    QEXTId identityId = d->m_idToIdentityIdMap.value(id);
    emit this->taskError(identityId, error);
}

void QEXTTcpTaskPool::onTaskFinished(quint64 id)
{
    QEXT_DECL_D(QEXTTcpTaskPool);
    QMutexLocker mutexLocker(&d->m_mutex);
    QEXTTcpTask *task = d->m_idToTaskMap.value(id);
    QEXTId identityId = d->m_idToIdentityIdMap.value(id);
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
