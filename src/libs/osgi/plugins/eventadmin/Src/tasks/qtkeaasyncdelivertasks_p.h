#ifndef QTKEAASYNCDELIVERTASKS_P_H
#define QTKEAASYNCDELIVERTASKS_P_H

#include "qtkeadelivertask_p.h"
#include "../dispatch/qtkeadefaultthreadpool_p.h"

class QTKEARunnable;

template<class SyncDeliverTasks, class HandlerTask>
class QTKEAAsyncDeliverTasks : public QTKEADeliverTask<QTKEAAsyncDeliverTasks<SyncDeliverTasks,HandlerTask>, HandlerTask>
{
    typedef QTKEADeliverTask<SyncDeliverTasks, HandlerTask> DeliverTask;

public:
    QTKEAAsyncDeliverTasks(QTKEADefaultThreadPool *pPool, DeliverTask *pDeliverTask);

    void execute(const QList<HandlerTask> &tasks);

private:
    class TaskExecuter;

    QTKEADefaultThreadPool *m_pPool;
    DeliverTask *m_pDeliverTask;
    /** A map of running threads currently delivering async events. */
    QHash<QThread *, QTKEARunnable *> m_mapRunningThreads;
    QMutex m_runningThreadsMutex;
};

template<class SyncDeliverTasks, class HandlerTask>
class QTKEAAsyncDeliverTasks<SyncDeliverTasks, HandlerTask>::TaskExecuter : public QTKEARunnable
{
    typedef QTKEAAsyncDeliverTasks<SyncDeliverTasks, HandlerTask> TopClass;

public:
    TaskExecuter(TopClass *pTopClass, const QList<HandlerTask> &listTasks, QThread *pKey)
        : m_pTopClass(pTopClass),
          m_listTasks(listTasks),
          m_pKey(pKey)
    {
    }

    void run() {
        bool bRunning = true;
        do {
            QList<HandlerTask> listCurrTasks;

            {
                QMutexLocker lock(&m_tasksMutex);
                listCurrTasks.push_back(m_listTasks.takeFirst());
            }
            m_pTopClass->m_pDeliverTask->execute(listCurrTasks);
            {
                QMutexLocker lock(&m_pTopClass->m_runningThreadsMutex);
                bRunning = m_listTasks.size() > 0;
                if (!bRunning) {
                    QTKEARunnable *pRunnable = m_pTopClass->m_mapRunningThreads.take(m_pKey);
                    if (pRunnable->autoDelete() && !--pRunnable->m_iRef) {
                        delete pRunnable;
                    }
                }
            }
        } while (bRunning);
    }

    void add(const QList<HandlerTask> &listNewTasks) {
        QMutexLocker lock(&m_tasksMutex);
        m_listTasks.append(listNewTasks);
    }

private:
    TopClass *m_pTopClass;
    QList<HandlerTask> m_listTasks;
    QMutex m_tasksMutex;
    QThread *m_pKey;
};

template<class SyncDeliverTasks, class HandlerTask>
QTKEAAsyncDeliverTasks<SyncDeliverTasks, HandlerTask>::QTKEAAsyncDeliverTasks(QTKEADefaultThreadPool *pPool,
                                                                              DeliverTask *pDeliverTask)
    : m_pPool(pPool),
      m_pDeliverTask(pDeliverTask)
{
}

template<class SyncDeliverTasks, class HandlerTask>
void QTKEAAsyncDeliverTasks<SyncDeliverTasks, HandlerTask>::execute(const QList<HandlerTask> &listTasks)
{
    QThread *pCurrentThread = QThread::currentThread();
    TaskExecuter *pExecuter = nullptr;
    {
        QMutexLocker lock(&m_runningThreadsMutex);
        TaskExecuter *pRunningExecutor = dynamic_cast<TaskExecuter*>(m_mapRunningThreads.value(pCurrentThread));
        if (pRunningExecutor) {
            pRunningExecutor->add(listTasks);
        } else {
            pExecuter = new TaskExecuter(this, listTasks, pCurrentThread);
            ++pExecuter->m_iRef;
            m_mapRunningThreads.insert(pCurrentThread, pExecuter);
        }
    }
    if (pExecuter) {
        m_pPool->executeTask(pExecuter);
    }
}

#endif // QTKEAASYNCDELIVERTASKS_P_H
