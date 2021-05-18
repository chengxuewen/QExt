#include <qexttcptaskthreadpool.h>
#include <qexttcptaskthreadpool_p.h>
#include <qexttcptaskthread.h>

#include <QSetIterator>
#include <QMutexLocker>
#include <QDebug>
#include <QThread>
#include <QTimer>



QEXTTcpTaskThreadPoolPrivate::QEXTTcpTaskThreadPoolPrivate(QEXTTcpTaskThreadPool *qq)
    : QEXTTcpAbstractThreadPoolPrivate(qq)
{

}

QEXTTcpTaskThreadPoolPrivate::~QEXTTcpTaskThreadPoolPrivate()
{

}



QEXTTcpTaskThreadPool::QEXTTcpTaskThreadPool(QObject *parent)
    : QEXTTcpAbstractThreadPool(*(new QEXTTcpTaskThreadPoolPrivate(this)), parent)
{
    QEXT_D(QEXTTcpTaskThreadPool);
    this->addThreads(120);
}

QEXTTcpTaskThreadPool::~QEXTTcpTaskThreadPool()
{

}

void QEXTTcpTaskThreadPool::setTcpThreadIdle(QEXTTcpAbstractThread *thread)
{
    QEXTTcpAbstractThreadPool::setTcpThreadIdle(thread);
    this->dispatchThreadHandleTask();
}

void QEXTTcpTaskThreadPool::removeThread()
{
    QEXT_D(QEXTTcpTaskThreadPool);
    if (this->allTcpThreadsCount() > 0) {
        d->m_threadMutex.lock();
        QEXTTcpAbstractThread *tcpThread = d->m_allThreadsSet.values().last();
        tcpThread->quit();
        d->m_threadMap.remove(tcpThread);
        d->m_allThreadsSet.remove(tcpThread);
        d->m_idleThreadsQueue.removeOne(tcpThread);
        d->m_workingThreadsSet.remove(tcpThread);
        d->m_threadMutex.unlock();
    }
}

void QEXTTcpTaskThreadPool::addThread()
{
    QEXT_D(QEXTTcpTaskThreadPool);
    QThread *thread = new QThread;
    QEXTTcpTaskThread *tcpThread = new QEXTTcpTaskThread(this);
    tcpThread->moveToThread(thread);
    if (!d->m_taskPool.isNull()) {
        tcpThread->setTaskPool(d->m_taskPool);
    }
    d->m_threadMutex.lock();
    d->m_allThreadsSet.insert(tcpThread);
    d->m_idleThreadsQueue.enqueue(tcpThread);
    d->m_threadMap.insert(tcpThread, thread);
    d->m_threadMutex.unlock();
    thread->start();
}

void QEXTTcpTaskThreadPool::dispatchThreadHandleTask()
{
    QEXT_D(QEXTTcpTaskThreadPool);
    if (!d->m_taskPool->isTaskEmpty()) {
        qDebug() << "QEXTTcpTaskThreadPool::dispatchThreadHandleTask():taskCount=" << d->m_taskPool->taskCount();
        QMutexLocker mutexLocker(&d->m_threadMutex);
        int threadsNum = d->m_idleThreadsQueue.size();
        qDebug() << "QEXTTcpTaskThreadPool::dispatchThreadHandleTask():threadsNum=" << threadsNum;
        if (threadsNum > 0) {
            QEXTTcpAbstractThread *thread = d->m_idleThreadsQueue.dequeue();
            QEXTTcpTaskThread *taskThread = dynamic_cast<QEXTTcpTaskThread *>(thread);
            if (taskThread) {
                QTimer::singleShot(0, taskThread, SLOT(fetchTask()));
            }
        }
    }
}

void QEXTTcpTaskThreadPool::setTaskPool(QSharedPointer<QEXTTcpAbstractTaskPool> taskPool)
{
    QEXT_D(QEXTTcpTaskThreadPool);
    QMutexLocker mutexLocker(&d->m_taskPoolMutex);
    if (!taskPool.isNull() && taskPool != d->m_taskPool) {
        if (!d->m_taskPool.isNull()) {
            disconnect(d->m_taskPool.data(), SIGNAL(newTaskReady()),
                       this, SLOT(dispatchThreadHandleTask()));
        }
        d->m_taskPool = taskPool;
        QMutexLocker mutexLocker(&d->m_threadMutex);
        QListIterator<QEXTTcpAbstractThread *> iter(d->m_allThreadsSet.toList());
        while (iter.hasNext()) {
            iter.next()->setTaskPool(taskPool);
        }
        connect(d->m_taskPool.data(), SIGNAL(newTaskReady()),
                this, SLOT(dispatchThreadHandleTask()), Qt::QueuedConnection);
    }
}
