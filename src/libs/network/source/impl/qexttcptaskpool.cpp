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
    : QEXTTcpTaskPoolBase(parent), QEXTObject(*(new QEXTTcpTaskPoolPrivate(this)))
{

}

QEXTTcpTaskPool::QEXTTcpTaskPool(QEXTTcpPacketParserBase *packetParser, QObject *parent)
    : QEXTTcpTaskPoolBase(parent), QEXTObject(*(new QEXTTcpTaskPoolPrivate(this)))
{
    QEXT_D(QEXTTcpTaskPool);
    d->m_packetParser.reset(packetParser);
}

QEXTTcpTaskPool::~QEXTTcpTaskPool()
{

}

bool QEXTTcpTaskPool::isTaskEmpty() const
{
    QEXT_DC(QEXTTcpTaskPool);
    QMutexLocker mutexLocker(&d->m_taskMutex);
    return d->m_taskQueue.isEmpty();
}

int QEXTTcpTaskPool::taskCount() const
{
    QEXT_DC(QEXTTcpTaskPool);
    QMutexLocker mutexLocker(&d->m_taskMutex);
    return d->m_taskQueue.size();
}

QEXTTcpTaskBase *QEXTTcpTaskPool::dequeueTask()
{
    QEXT_D(QEXTTcpTaskPool);
    QMutexLocker mutexLocker(&d->m_taskMutex);
    return d->m_taskQueue.isEmpty() ? QEXT_NULLPTR : d->m_taskQueue.dequeue();
}

QList<QEXTTcpTaskBase *> QEXTTcpTaskPool::allUnfinishedTasks() const
{
    QEXT_DC(QEXTTcpTaskPool);
    QMutexLocker mutexLocker(&d->m_taskMutex);
    return d->m_unfinishedTaskMap.values();
}

QList<QEXTTcpTaskBase *> QEXTTcpTaskPool::allExpiredTasks() const
{
    QEXT_DC(QEXTTcpTaskPool);
    QMutexLocker mutexLocker(&d->m_taskMutex);
    return d->m_expiredTasksSet.toList();
}

QEXTTcpPacketParserBase *QEXTTcpTaskPool::packetParser() const
{
    QEXT_DC(QEXTTcpTaskPool);
    QMutexLocker mutexLocker(&d->m_packetParserMutex);
    return d->m_packetParser.data();
}

void QEXTTcpTaskPool::setPacketParser(QEXTTcpPacketParserBase *packetParser)
{
    QEXT_D(QEXTTcpTaskPool);
    QMutexLocker mutexLocker(&d->m_packetParserMutex);
    if (packetParser != d->m_packetParser.data()) {
        d->m_packetParser.reset(packetParser);
    }
}

void QEXTTcpTaskPool::enqueuePacket(QEXTTcpPacketBase *packet)
{
    QEXT_D(QEXTTcpTaskPool);
    QEXTTcpTaskBase *task = new QEXTTcpTask(packet, this);
    d->m_taskMutex.lock();
    qDebug() << "QEXTTcpTaskPool::enqueuePacket():m_taskQueue.size=" << d->m_taskQueue.size();
    d->m_taskQueue.enqueue(task);
    d->m_taskMutex.unlock();
    emit this->newTaskReady();
}

void QEXTTcpTaskPool::sendPacket(QEXTTcpPacketBase *packet)
{
    emit this->newPacketReady(packet);
}

void QEXTTcpTaskPool::recoveryTask(QEXTTcpTaskBase *task)
{
    QEXT_D(QEXTTcpTaskPool);
    QMutexLocker mutexLocker(&d->m_taskMutex);
    if (task->isFinished()) {
        d->m_unfinishedTaskMap.remove(task->id());
        d->m_finishedTaskList.append(task);
        if (d->m_finishedTaskList.size() > 50) {
            qDeleteAll(d->m_finishedTaskList);
            d->m_finishedTaskList.clear();
        }
    } else {
        QEXTTcpTaskBase *multiTask = d->m_unfinishedTaskMap.value(task->id());
        if (multiTask && multiTask != task) {
            d->m_expiredTasksSet.insert(multiTask);
        }
        d->m_unfinishedTaskMap.insert(task->id(), task);
    }
}
