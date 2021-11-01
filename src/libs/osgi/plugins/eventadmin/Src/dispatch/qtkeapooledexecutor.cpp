#include "qtkeapooledexecutor_p.h"
#include "qtkeachannel_p.h"
#include "../dispatch/qtkeainterruptiblethread_p.h"
#include "../dispatch/qtkeainterruptedexception_p.h"

// for QTK::msecsTo() - remove after switching to Qt 4.7
#include <QTKCore/QTKUtils>

#include <QDateTime>
#include <QDebug>

#include <limits>
#include <stdexcept>

const int QTKEAPooledExecutor::DEFAULT_MAXIMUMPOOLSIZE = std::numeric_limits<int>::max();
const int QTKEAPooledExecutor::DEFAULT_MINIMUMPOOLSIZE = 1;
const long QTKEAPooledExecutor::DEFAULT_KEEPALIVETIME = 60 * 1000;


QTKEAPooledExecutor::QTKEAPooledExecutor(QTKEAChannel *pChannel, int iMaxPoolSize)
    : m_waitWhenBlocked(this),
      m_discardOldestWhenBlocked(this),
      m_iMaximumPoolSize(iMaxPoolSize),
      m_iMinimumPoolSize(DEFAULT_MINIMUMPOOLSIZE),
      m_iPoolSize(0),
      m_lKeepAliveTime(DEFAULT_KEEPALIVETIME),
      m_bShutdown(false),
      m_pHandOff(pChannel),
      m_pBlockedExecutionHandler(0)
{
    this->runWhenBlocked();
}

QTKEAPooledExecutor::~QTKEAPooledExecutor()
{
    delete m_pHandOff;
    qDeleteAll(m_listStoppedThreads);
}

int QTKEAPooledExecutor::getMaximumPoolSize() const
{
    QMutexLocker lock(&m_mutex);
    return m_iMaximumPoolSize;
}

void QTKEAPooledExecutor::setMaximumPoolSize(int iNewMaximum)
{
    QMutexLocker lock(&m_mutex);
    if (iNewMaximum <= 0) {
        throw QTKInvalidArgumentException("maximum must be > 0");
    }
    m_iMaximumPoolSize = iNewMaximum;
}

int QTKEAPooledExecutor::getMinimumPoolSize() const
{
    QMutexLocker lock(&m_mutex);
    return m_iMinimumPoolSize;
}

void QTKEAPooledExecutor::setMinimumPoolSize(int iNewMinimum)
{
    QMutexLocker lock(&m_mutex);
    if (iNewMinimum < 0) throw QTKInvalidArgumentException("minimum must be >= 0");
    m_iMinimumPoolSize = iNewMinimum;
}

int QTKEAPooledExecutor::getPoolSize() const
{
    QMutexLocker lock(&m_mutex);
    return m_iPoolSize;
}

long QTKEAPooledExecutor::getKeepAliveTime() const
{
    QMutexLocker lock(&m_mutex);
    return m_lKeepAliveTime;
}

void QTKEAPooledExecutor::setKeepAliveTime(long lMsecs)
{
    QMutexLocker lock(&m_mutex);
    m_lKeepAliveTime = lMsecs;
}

QTKEAPooledExecutor::BlockedExecutionHandler* QTKEAPooledExecutor::getBlockedExecutionHandler() const
{
    QMutexLocker lock(&m_mutex);
    return m_pBlockedExecutionHandler;
}

void QTKEAPooledExecutor::setBlockedExecutionHandler(BlockedExecutionHandler *pHandler)
{
    QMutexLocker lock(&m_mutex);
    m_pBlockedExecutionHandler = pHandler;
}

int QTKEAPooledExecutor::createThreads(int iNumberOfThreads)
{
    int iNcreated = 0;
    for (int i = 0; i < iNumberOfThreads; ++i) {
        if (m_iPoolSize < m_iMaximumPoolSize) {
            addThread(0);
            ++iNcreated;
        } else {
            break;
        }
    }
    return iNcreated;
}

void QTKEAPooledExecutor::interruptAll()
{
    QMutexLocker lock(&m_mutex);
    foreach (QTKEAInterruptibleThread *pThread, m_mapThreads) {
        pThread->interrupt();
    }
}

void QTKEAPooledExecutor::shutdownNow()
{
    this->shutdownNow(&m_discardWhenBlocked);
}

void QTKEAPooledExecutor::shutdownNow(BlockedExecutionHandler *pHandler)
{
    QMutexLocker lock(&m_mutex);
    setBlockedExecutionHandler(pHandler);
    m_bShutdown = true; // don't allow new tasks
    m_iMinimumPoolSize = m_iMaximumPoolSize = 0; // don't make new threads
    this->interruptAll(); // interrupt all existing threads
}

void QTKEAPooledExecutor::shutdownAfterProcessingCurrentlyQueuedTasks()
{
    this->shutdownAfterProcessingCurrentlyQueuedTasks(new DiscardWhenBlocked());
}

void QTKEAPooledExecutor::shutdownAfterProcessingCurrentlyQueuedTasks(BlockedExecutionHandler *pHandler)
{
    QMutexLocker lock(&m_mutex);
    this->setBlockedExecutionHandler(pHandler);
    m_bShutdown = true;
    if (m_iPoolSize == 0) { // disable new thread construction when idle
        m_iMinimumPoolSize = m_iMaximumPoolSize = 0;
    }
}

bool QTKEAPooledExecutor::isTerminatedAfterShutdown() const
{
    QMutexLocker lock(&m_mutex);
    return m_bShutdown && m_iPoolSize == 0;
}

bool QTKEAPooledExecutor::awaitTerminationAfterShutdown(long lMaxWaitTime) const
{
    QMutexLocker lock(&m_mutex);
    QMutexLocker shutdownLock(&m_shutdownMutex);
    if (!m_bShutdown) {
        throw QTKIllegalStateException("not in shutdown state");
    }
    if (m_iPoolSize == 0) {
        return true;
    }
    qint64 liWaitTime = static_cast<qint64>(lMaxWaitTime);
    if (liWaitTime <= 0) {
        return false;
    }
    //TODO Use Qt4.7 API
    QDateTime start = QDateTime::currentDateTime();
    forever {
        m_waitCond.wait(&m_shutdownMutex, liWaitTime);
        if (m_iPoolSize == 0) {
            return true;
        }
        qint64 liCurrWait = QTKUtils::msecsTo(start, QDateTime::currentDateTime());
        liWaitTime = static_cast<qint64>(lMaxWaitTime) - liCurrWait;
        if (liWaitTime <= 0) {
            return false;
        }
    }
}

void QTKEAPooledExecutor::awaitTerminationAfterShutdown() const
{
    QMutexLocker lock(&m_mutex);
    if (!m_bShutdown) {
        throw QTKIllegalStateException("not in shutdown state");
    }
    while (m_iPoolSize > 0) {
        lock.unlock();
        QMutexLocker shutdownLock(&m_shutdownMutex);
        m_waitCond.wait(&m_shutdownMutex);
        lock.relock();
        // worker is done, wait for possibly not yet finished worker-thread
        foreach(QThread *pThread, m_listStoppedThreads) {
            pThread->wait();
        }
    }
}

QList<QTKEARunnable *> QTKEAPooledExecutor::drain()
{
    bool bWasInterrupted = false;
    QList<QTKEARunnable *> listTasks;
    forever {
        try {
            QTKEARunnable *pValue = m_pHandOff->poll(0);
            if (nullptr == pValue) {
                break;
            } else {
                listTasks.push_back(pValue);
            }
        } catch (const QTKEAInterruptedException &) {
            bWasInterrupted = true; // postpone re-interrupt until drained
        }
    }
    if (bWasInterrupted) {
        qobject_cast<QTKEAInterruptibleThread*>(QThread::currentThread())->interrupt();
    }
    return listTasks;
}

void QTKEAPooledExecutor::runWhenBlocked()
{
    this->setBlockedExecutionHandler(&m_runWhenBlocked);
}

void QTKEAPooledExecutor::waitWhenBlocked()
{
    setBlockedExecutionHandler(&m_waitWhenBlocked);
}

void QTKEAPooledExecutor::discardWhenBlocked()
{
    setBlockedExecutionHandler(&m_discardWhenBlocked);
}

void QTKEAPooledExecutor::abortWhenBlocked()
{
    setBlockedExecutionHandler(&m_abortWhenBlocked);
}

void QTKEAPooledExecutor::discardOldestWhenBlocked()
{
    setBlockedExecutionHandler(&m_discardOldestWhenBlocked);
}

void QTKEAPooledExecutor::execute(QTKEARunnable* pCommand)
{
    forever
    {
        {
            QMutexLocker lock(&m_mutex);
            if (!m_bShutdown)
            {
                int size = m_iPoolSize;

                // Ensure minimum number of threads
                if (size < m_iMinimumPoolSize)
                {
                    addThread(pCommand);
                    return;
                }

                // Try to give to existing thread
                if (m_pHandOff->offer(pCommand, 0))
                {
                    return;
                }

                // If cannot handoff and still under maximum, create new thread
                if (size < m_iMaximumPoolSize)
                {
                    addThread(pCommand);
                    return;
                }
            }
        }

        // Cannot hand off and cannot create -- ask for help
        if (getBlockedExecutionHandler()->blockedAction(pCommand))
        {
            return;
        }
    }
}

QTKEAPooledExecutor::Worker::Worker(QTKEAPooledExecutor* pPooledExecutor, QTKEARunnable* pFirstTask)
    : m_pFirstTask(pFirstTask), m_pPooledExecutor(pPooledExecutor)
{
    if (pFirstTask) ++pFirstTask->m_iRef;
}

void QTKEAPooledExecutor::Worker::run()
{
    try
    {
        QTKEARunnable* task = m_pFirstTask;
        m_pFirstTask = 0;

        if (task != 0)
        {
            const bool autoDelete = task->autoDelete();
            task->run();
            if (autoDelete && !--task->m_iRef) delete task;
        }

        while ( (task = m_pPooledExecutor->getTask()) != 0)
        {
            const bool autoDelete = task->autoDelete();
            task->run();
            if (autoDelete && !--task->m_iRef) delete task;
        }
    }
    catch (const QTKEAInterruptedException&)
    {
        m_pPooledExecutor->workerDone(this);
        return;
    }

    m_pPooledExecutor->workerDone(this);
}

bool QTKEAPooledExecutor::RunWhenBlocked::blockedAction(QTKEARunnable* pCommand)
{
    const bool autoDelete = pCommand->autoDelete();
    pCommand->run();
    if (autoDelete && !--pCommand->m_iRef) delete pCommand;
    return true;
}

QTKEAPooledExecutor::WaitWhenBlocked::WaitWhenBlocked(QTKEAPooledExecutor* pPooledExecutor)
    : m_pPooledExecutor(pPooledExecutor)
{}

bool QTKEAPooledExecutor::WaitWhenBlocked::blockedAction(QTKEARunnable* pCommand)
{
    {
        QMutexLocker lock(&m_pPooledExecutor->m_mutex);
        if (m_pPooledExecutor->m_bShutdown)
            return true;
    }
    m_pPooledExecutor->m_pHandOff->put(pCommand);
    return true;
}

bool QTKEAPooledExecutor::DiscardWhenBlocked::blockedAction(QTKEARunnable* pCommand)
{
    Q_UNUSED(pCommand)
    return true;
}

bool QTKEAPooledExecutor::AbortWhenBlocked::blockedAction(QTKEARunnable* pCommand)
{
    Q_UNUSED(pCommand)
    throw QTKRuntimeException("Pool is blocked");
}

QTKEAPooledExecutor::DiscardOldestWhenBlocked::DiscardOldestWhenBlocked(QTKEAPooledExecutor* pPooledExecutor)
    : m_pPooledExecutor(pPooledExecutor)
{}

bool QTKEAPooledExecutor::DiscardOldestWhenBlocked::blockedAction(QTKEARunnable* pCommand)
{
    QTKEARunnable* tmp = m_pPooledExecutor->m_pHandOff->poll(0);
    if (tmp && tmp->autoDelete() && !--tmp->m_iRef) delete tmp;

    if (!m_pPooledExecutor->m_pHandOff->offer(pCommand, 0))
    {
        const bool autoDelete = pCommand->autoDelete();
        pCommand->run();
        if (autoDelete && !--pCommand->m_iRef) delete pCommand;
    }
    return true;
}

void QTKEAPooledExecutor::addThread(QTKEARunnable* pCommand)
{
    Worker* worker = new Worker(this, pCommand);
    ++worker->m_iRef;
    QTKEAInterruptibleThread* thread = getThreadFactory()->newThread(worker);
    m_mapThreads.insert(worker, thread);
    ++m_iPoolSize;

    // do some garbage collection
    foreach (QTKEAInterruptibleThread* t, m_listStoppedThreads)
    {
        if (t != QTKEAInterruptibleThread::currentThread() && t->isFinished())
        {
            delete t;
            m_listStoppedThreads.removeAll(t);
        }
    }

    thread->start();
}

void QTKEAPooledExecutor::workerDone(Worker* pWorker)
{
    QMutexLocker lock(&m_mutex);
    m_listStoppedThreads << m_mapThreads.take(pWorker);
    if (--m_iPoolSize == 0 && m_bShutdown)
    {
        m_iMaximumPoolSize = m_iMinimumPoolSize = 0; // disable new threads
        m_waitCond.wakeAll(); // notify awaitTerminationAfterShutdown
    }

    // Create a replacement if needed
    if (m_iPoolSize == 0 || m_iPoolSize < m_iMinimumPoolSize)
    {
        try
        {
            QTKEARunnable* r = m_pHandOff->poll(0);
            if (r != 0)
            {
                if(m_bShutdown) // just consume task if shut down
                {
                    if (r->autoDelete() && !r->m_iRef) delete r;
                }
                else
                {
                    addThread(r);
                }
            }
        }
        catch(const QTKEAInterruptedException& ) {
            return;
        }
    }
}

QTKEARunnable* QTKEAPooledExecutor::getTask()
{
    long waitTime;
    {
        QMutexLocker lock(&m_mutex);
        if (m_iPoolSize > m_iMaximumPoolSize) // Cause to die if too many threads
            return 0;
        waitTime = (m_bShutdown)? 0 : m_lKeepAliveTime;
    }
    if (waitTime >= 0)
        return m_pHandOff->poll(waitTime);
    else
        return m_pHandOff->take();
}
