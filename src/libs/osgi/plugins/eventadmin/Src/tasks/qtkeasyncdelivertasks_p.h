#ifndef QTKEASYNCDELIVERTASKS_P_H
#define QTKEASYNCDELIVERTASKS_P_H

#include "qtkeadelivertask_p.h"
#include "qtkeasyncthread_p.h"
#include "../dispatch/qtkeadefaultthreadpool_p.h"
#include "../dispatch/qtkeasyncmasterthread_p.h"
#include "../util/qtkearendezvous_p.h"
#include "../util/qtkeatimeoutexception_p.h"

#include <QMutex>
#include <QDateTime>

class QTKEADefaultThreadPool;
class QTKEASyncMasterThread;

template<class HandlerTask>
class QTKEASyncDeliverTasks : public QTKEADeliverTask<QTKEASyncDeliverTasks<HandlerTask>, HandlerTask>
{
public:
    QTKEASyncDeliverTasks(QTKEADefaultThreadPool *pPool, QTKEASyncMasterThread *pSyncMasterThread,
                          long lTimeout, const QList<QString> &ignoreTimeout);

    void update(long lTimeout, const QList<QString> &listIgnoreTimeout);

    void execute(const QList<HandlerTask> &listTasks);

    void executeInSyncMaster(const QList<HandlerTask> &listTasks);

private:
    struct Matcher
    {
        virtual ~Matcher() {}
        virtual bool match(const QString &strClassName) const = 0;
    };

    /** Match a class name. */
    struct ClassMatcher : public Matcher
    {
    public:
        ClassMatcher(const QString &strName)
            : m_strClassName(strName)
        {

        }

        bool match(const QString &strName) const
        {
            return m_strClassName == strName;
        }

    private:
        const QString m_strClassName;
    };


    bool useTimeout(const HandlerTask &task);


    /** The thread pool used to spin-off new threads. */
    QTKEADefaultThreadPool *m_pPool;

    /** This is a QTKEAInterruptibleThread used to execute the handlers */
    QTKEASyncMasterThread *m_pSyncMasterThread;

    /** The timeout for event handlers, 0 = disabled. */
    long m_lTimeout;
    /** The matchers for ignore timeout handling. */
    QList<Matcher *> m_listIgnoreTimeoutMatcher;
    QMutex m_mutex;
};


template<class HandlerTask>
class QTKTimeoutRunnable : public QTKEARunnable
{
public:
    QTKTimeoutRunnable(HandlerTask *pTask)
        : m_pTask(pTask)
    {

    }

    void run()
    {
        try {
            // notify the outer thread to start the timer
            m_startBarrier.waitForRendezvous();
            // execute the task
            m_pTask->execute();
            // stop the timer
            m_timerBarrier.waitForRendezvous();
        } catch (const QTKIllegalStateException &) {
            // this can happen on shutdown, so we ignore it
        }
    }

    QTKEARendezvous m_timerBarrier;
    QTKEARendezvous m_startBarrier;

private:
    HandlerTask *m_pTask;
};

template<class HandlerTask>
class QTKRunInSyncMaster : public QRunnable
{
public:
    QTKRunInSyncMaster(QTKEASyncDeliverTasks<HandlerTask> *pHandlerTasks, const QList<HandlerTask> &listasks)
        : m_pHandlerTasks(pHandlerTasks),
          m_listTasks(listasks)
    {

    }

    void run()
    {
        m_pHandlerTasks->executeInSyncMaster(m_listTasks);
    }

private:
    QTKEASyncDeliverTasks<HandlerTask> *m_pHandlerTasks;
    const QList<HandlerTask> &m_listTasks;
};

template<class HandlerTask>
QTKEASyncDeliverTasks<HandlerTask>::QTKEASyncDeliverTasks(QTKEADefaultThreadPool *pPool, QTKEASyncMasterThread *pSyncMasterThread,
                                                          long lTimeout, const QList<QString> &ignoreTimeout)
    : m_pPool(pPool),
      m_pSyncMasterThread(pSyncMasterThread)
{
    this->update(lTimeout, ignoreTimeout);
}

template<class HandlerTask>
void QTKEASyncDeliverTasks<HandlerTask>::update(long lTimeout, const QList<QString> &listIgnoreTimeout)
{
    {
        QMutexLocker lock(&m_mutex);
        m_lTimeout = lTimeout;
    }

    if (listIgnoreTimeout.isEmpty()) {
        QMutexLocker lock(&m_mutex);
        qDeleteAll(m_listIgnoreTimeoutMatcher);
        m_listIgnoreTimeoutMatcher.clear();
    } else {
        QList<Matcher *> listNewMatcher;
        foreach (QString strValue, listIgnoreTimeout) {
            strValue = strValue.trimmed();
            if (!strValue.isEmpty()) {
                listNewMatcher.push_back(new ClassMatcher(strValue));
            }
        }

        {
            QMutexLocker lock(&m_mutex);
            qDeleteAll(m_listIgnoreTimeoutMatcher);
            m_listIgnoreTimeoutMatcher = listNewMatcher;
        }
    }
}

template<class HandlerTask>
void QTKEASyncDeliverTasks<HandlerTask>::execute(const QList<HandlerTask> &listTasks)
{
    QTKRunInSyncMaster<HandlerTask> runnable(this, listTasks);
    runnable.setAutoDelete(false);
    m_pSyncMasterThread->syncRun(&runnable);
}

template<class HandlerTask>
void QTKEASyncDeliverTasks<HandlerTask>::executeInSyncMaster(const QList<HandlerTask> &listTasks)
{
    QThread *const pSleepingThread = QThread::currentThread();
    QTKEASyncThread *const pSyncThread = qobject_cast<QTKEASyncThread*>(pSleepingThread);

    foreach (HandlerTask task, listTasks) {
        if (!useTimeout(task)) {
            // no timeout, we can directly execute
            task.execute();
        } else if (nullptr != pSyncThread) {
            // if this is a cascaded event, we directly use this thread
            // otherwise we could end up in a starvation
            //TODO use Qt4.7 API
            //long startTime = System.currentTimeMillis();
            QDateTime startTime = QDateTime::currentDateTime();
            task.execute();
            if (startTime.time().msecsTo(QDateTime::currentDateTime().time()) > m_lTimeout) {
                task.blackListHandler();
            }
        } else {
            QTKTimeoutRunnable<HandlerTask> *pTimeoutRunnable = new QTKTimeoutRunnable<HandlerTask>(&task);
            QTKEAScopedRunnableReference runnableRef(pTimeoutRunnable);

            QTKEARendezvous *pStartBarrier = &pTimeoutRunnable->m_startBarrier;
            QTKEARendezvous *pTimerBarrier = &pTimeoutRunnable->m_timerBarrier;
            m_pPool->executeTask(pTimeoutRunnable);

            // we wait for the inner thread to start
            pStartBarrier->waitForRendezvous();

            // timeout handling
            // we sleep for the sleep time
            // if someone wakes us up it's the finished inner task
            try {
                pTimerBarrier->waitAttemptForRendezvous(m_lTimeout);
            } catch (const QTKEATimeoutException &) {
                // if we timed out, we have to blacklist the handler
                task.blackListHandler();
            }
        }
    }
}

template<class HandlerTask>
bool QTKEASyncDeliverTasks<HandlerTask>::useTimeout(const HandlerTask &task)
{
    // we only check the classname if a timeout is configured
    long lTimeout = 0;
    {
        QMutexLocker lock(&m_mutex);
        lTimeout = m_lTimeout;
    }

    if (lTimeout > 0) {
        QList<Matcher *> listCurrMatcher; {
            QMutexLocker lock(&m_mutex);
            listCurrMatcher = m_listIgnoreTimeoutMatcher;
        }
        if (!listCurrMatcher.isEmpty()) {
            QString strClassName = task.getHandlerClassName();
            foreach (Matcher *pMatcher, listCurrMatcher) {
                if (pMatcher) {
                    if (pMatcher->match(strClassName)) {
                        return false;
                    }
                }
            }
        }
        return true;
    }
    return false;
}

#endif // QTKEASYNCDELIVERTASKS_P_H
