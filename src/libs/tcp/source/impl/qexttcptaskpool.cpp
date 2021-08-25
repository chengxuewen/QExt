#include <qexttcptaskpool.h>
#include <qexttcptaskpool_p.h>
#include <qexttcptask.h>

#include <QDebug>
#include <QMutexLocker>



QEXTTcpTaskPoolPrivate::QEXTTcpTaskPoolPrivate(QEXTTcpTaskPool *qq)
    : QEXTObjectPrivate(qq)
{

}

QEXTTcpTaskPoolPrivate::~QEXTTcpTaskPoolPrivate()
{

}



QEXTTcpTaskPool::QEXTTcpTaskPool(QObject *parent)
    : QEXTTcpAbstractTaskPool(parent), QEXTObject(*(new QEXTTcpTaskPoolPrivate(this)))
{

}

QEXTTcpTaskPool::QEXTTcpTaskPool(QEXTTcpAbstractPacketParser *packetParser, QObject *parent)
    : QEXTTcpAbstractTaskPool(parent), QEXTObject(*(new QEXTTcpTaskPoolPrivate(this)))
{
    QEXT_DECL_D(QEXTTcpTaskPool);
    d->m_packetParser.reset(packetParser);
}

QEXTTcpTaskPool::~QEXTTcpTaskPool()
{

}

bool QEXTTcpTaskPool::isTaskEmpty() const
{
    QEXT_DECL_DC(QEXTTcpTaskPool);
    QMutexLocker mutexLocker(&d->m_taskMutex);
    return d->m_taskQueue.isEmpty();
}

int QEXTTcpTaskPool::taskCount() const
{
    QEXT_DECL_DC(QEXTTcpTaskPool);
    QMutexLocker mutexLocker(&d->m_taskMutex);
    return d->m_taskQueue.size();
}

QEXTTcpAbstractTask *QEXTTcpTaskPool::dequeueTask()
{
    QEXT_DECL_D(QEXTTcpTaskPool);
    QMutexLocker mutexLocker(&d->m_taskMutex);
    return d->m_taskQueue.isEmpty() ? QEXT_DECL_NULLPTR : d->m_taskQueue.dequeue();
}

QList<QEXTTcpAbstractTask *> QEXTTcpTaskPool::allUnfinishedTasks() const
{
    QEXT_DECL_DC(QEXTTcpTaskPool);
    QMutexLocker mutexLocker(&d->m_taskMutex);
    return d->m_unfinishedTaskMap.values();
}

QList<QEXTTcpAbstractTask *> QEXTTcpTaskPool::allExpiredTasks() const
{
    QEXT_DECL_DC(QEXTTcpTaskPool);
    QMutexLocker mutexLocker(&d->m_taskMutex);
    return d->m_expiredTasksSet.toList();
}

QEXTTcpAbstractPacketParser *QEXTTcpTaskPool::packetParser() const
{
    QEXT_DECL_DC(QEXTTcpTaskPool);
    QMutexLocker mutexLocker(&d->m_packetParserMutex);
    return d->m_packetParser.data();
}

void QEXTTcpTaskPool::setPacketParser(QEXTTcpAbstractPacketParser *packetParser)
{
    QEXT_DECL_D(QEXTTcpTaskPool);
    QMutexLocker mutexLocker(&d->m_packetParserMutex);
    if (packetParser != d->m_packetParser.data()) {
        d->m_packetParser.reset(packetParser);
    }
}

void QEXTTcpTaskPool::parsePacket(QEXTTcpAbstractPacket *packet)
{
    QEXT_DECL_D(QEXTTcpTaskPool);
    QEXTTcpAbstractTask *task = new QEXTTcpTask(packet, this);
    this->enqueueTask(task);
}

void QEXTTcpTaskPool::sendPacket(QEXTTcpAbstractPacket *packet)
{
    emit this->newPacketReady(packet);
}

void QEXTTcpTaskPool::enqueueTask(QEXTTcpAbstractTask *task)
{
    QEXT_DECL_D(QEXTTcpTaskPool);
    d->m_taskMutex.lock();
    d->m_taskQueue.enqueue(task);
    d->m_taskMutex.unlock();
    emit this->newTaskReady();
}

void QEXTTcpTaskPool::recoveryTask(QEXTTcpAbstractTask *task)
{
    QEXT_DECL_D(QEXTTcpTaskPool);
    QMutexLocker mutexLocker(&d->m_taskMutex);
    if (task->isFinished()) {
        d->m_unfinishedTaskMap.remove(task->id());
        d->m_finishedTaskList.append(task);
        if (d->m_finishedTaskList.size() > 50) {
            qDeleteAll(d->m_finishedTaskList);
            d->m_finishedTaskList.clear();
        }
    } else {
        QEXTTcpAbstractTask *multiTask = d->m_unfinishedTaskMap.value(task->id());
        if (multiTask && multiTask != task) {
            d->m_expiredTasksSet.insert(multiTask);
        }
        d->m_unfinishedTaskMap.insert(task->id(), task);
    }
}
