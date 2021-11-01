#ifndef QTKEVENTADMINIMPL_P_H
#define QTKEVENTADMINIMPL_P_H

#include "handler/qtkeahandlertasks_p.h"
#include "tasks/qtkeadelivertask_p.h"
#include "dispatch/qtkeasyncmasterthread_p.h"
#include "dispatch/qtkeadefaultthreadpool_p.h"

class QTKEADefaultThreadPool;

template<class HandlerTasks, class SyncDeliverTasks, class AsyncDeliverTasks>
class QTKEventAdminImpl
{
    typedef QTKEAHandlerTask<HandlerTasks> HandlerTask;
    typedef QTKEADeliverTask<SyncDeliverTasks, HandlerTask> SyncDeliverTaskInterface;
    typedef QTKEADeliverTask<AsyncDeliverTasks, HandlerTask> AsyncDeliverTaskInterface;
    typedef QTKEAHandlerTasks<HandlerTasks> HandlerTasksInterface;

public:
    QTKEventAdminImpl(HandlerTasksInterface *pManagers, QTKEADefaultThreadPool *pSyncPool,
                      QTKEADefaultThreadPool *pAsyncPool, int iTimeout,
                      const QStringList &listIgnoreTimeout);

    ~QTKEventAdminImpl();

    void postEvent(const QTKEvent &event);

    void sendEvent(const QTKEvent &event);

    QString subscribeSlot(const QObject *pSubscriber, const char *psMember, const QTKProperties &properties);

    void updateProperties(const QString &subsriptionId, const QTKProperties &properties);

    void stop();

    void update(HandlerTasksInterface *pManagers, int iTimeout, const QStringList &listIgnoreTimeout);

private:
    template<class DeliverTasks>
    void handleEvent(const QList<HandlerTask> &listManagers, DeliverTasks *pManager);

    void checkNull(void *pObject, const QString &strName);

private:
    struct StoppedHandlerTasks : public QTKEAHandlerTasks<HandlerTasks>
    {
        QList<QTKEAHandlerTask<HandlerTasks> > createHandlerTasks(const QTKEvent&)
        {
            throw QTKIllegalStateException("The EventAdmin is stopped");
        }
    };

    // The factory used to determine applicable QTKEventHandlers - this will be replaced
    // by a null object in stop() that subsequently throws an IllegalStateException
    QAtomicPointer<HandlerTasksInterface> m_managers;

    // The asynchronous event dispatcher
    AsyncDeliverTaskInterface *m_pPostManager;

    // The (interruptible) thread where sync events are handled
    QTKEASyncMasterThread m_syncMasterThread;

    // The synchronous event dispatcher
    SyncDeliverTasks *m_pSendManager;

    StoppedHandlerTasks m_stoppedHandlerTasks;
};

template<class HandlerTasks, class SyncDeliverTasks, class AsyncDeliverTasks>
QTKEventAdminImpl<HandlerTasks,SyncDeliverTasks,AsyncDeliverTasks>::
QTKEventAdminImpl(HandlerTasksInterface *pManagers, QTKEADefaultThreadPool *pSyncPool,
                  QTKEADefaultThreadPool *pAsyncPool, int iTimeout,
                  const QStringList &listIgnoreTimeout)
    : m_managers(pManagers)
{
    this->checkNull(pManagers, "Managers");
    this->checkNull(pSyncPool, "syncPool");
    this->checkNull(pAsyncPool, "asyncPool");

    m_pSendManager = new SyncDeliverTasks(pSyncPool, &m_syncMasterThread,
                                          (iTimeout > 100 ? iTimeout : 0),
                                          listIgnoreTimeout);

    m_pPostManager = new AsyncDeliverTasks(pAsyncPool, m_pSendManager);
}

template<class HandlerTasks, class SyncDeliverTasks, class AsyncDeliverTasks>
QTKEventAdminImpl<HandlerTasks,SyncDeliverTasks,AsyncDeliverTasks>::~QTKEventAdminImpl()
{
    delete m_pPostManager;
    delete m_pSendManager;
}

template<class HandlerTasks, class SyncDeliverTasks, class AsyncDeliverTasks>
void QTKEventAdminImpl<HandlerTasks,SyncDeliverTasks,AsyncDeliverTasks>::postEvent(const QTKEvent &event)
{
    this->handleEvent(m_managers.fetchAndAddOrdered(0)->createHandlerTasks(event), m_pPostManager);
}

template<class HandlerTasks, class SyncDeliverTasks, class AsyncDeliverTasks>
void QTKEventAdminImpl<HandlerTasks,SyncDeliverTasks,AsyncDeliverTasks>::sendEvent(const QTKEvent &event)
{
    this->handleEvent(m_managers.fetchAndAddOrdered(0)->createHandlerTasks(event), m_pSendManager);
}

template<class HandlerTasks, class SyncDeliverTasks, class AsyncDeliverTasks>
QString QTKEventAdminImpl<HandlerTasks,SyncDeliverTasks,AsyncDeliverTasks>::
subscribeSlot(const QObject *pSubscriber, const char *psMember, const QTKProperties &properties)
{
    Q_UNUSED(pSubscriber)
    Q_UNUSED(psMember)
    Q_UNUSED(properties)
    return QString();
}

template<class HandlerTasks, class SyncDeliverTasks, class AsyncDeliverTasks>
void QTKEventAdminImpl<HandlerTasks,SyncDeliverTasks,AsyncDeliverTasks>::
updateProperties(const QString &subsriptionId, const QTKProperties &properties)
{
    Q_UNUSED(subsriptionId)
    Q_UNUSED(properties)
}

template<class HandlerTasks, class SyncDeliverTasks, class AsyncDeliverTasks>
void QTKEventAdminImpl<HandlerTasks,SyncDeliverTasks,AsyncDeliverTasks>::stop()
{
    // replace the HandlerTasks with a null object that will throw an
    // IllegalStateException on a call to createHandlerTasks
    HandlerTasksInterface *pOldManagers = m_managers.fetchAndStoreOrdered(&m_stoppedHandlerTasks);
    delete pOldManagers;
    m_syncMasterThread.stop();
}

template<class HandlerTasks, class SyncDeliverTasks, class AsyncDeliverTasks>
void QTKEventAdminImpl<HandlerTasks,SyncDeliverTasks,AsyncDeliverTasks>::update(HandlerTasksInterface *pManagers, int iTimeout,
                                                                                const QStringList &listIgnoreTimeout)
{
    HandlerTasksInterface *pOldManagers = m_managers.fetchAndStoreOrdered(pManagers);
    delete pOldManagers;
    m_pSendManager->update(iTimeout, listIgnoreTimeout);
}

template<class HandlerTasks, class SyncDeliverTasks, class AsyncDeliverTasks>
template<class DeliverTasks>
void QTKEventAdminImpl<HandlerTasks,SyncDeliverTasks,AsyncDeliverTasks>::handleEvent(const QList<HandlerTask> &listManagers,
                                                                                     DeliverTasks *pManager)
{
    if (0 < listManagers.size()) {
        // This might throw an QTKIllegalStateException in case that we are stopped
        // and the null object for managers was not fast enough established
        // This is needed in the adapter/* classes due to them sending
        // events whenever they receive an event from their source.
        // Service importers that call us regardless of the fact that we are
        // stopped deserve an exception anyways
        pManager->execute(listManagers);
    }
}

template<class HandlerTasks, class SyncDeliverTasks, class AsyncDeliverTasks>
void QTKEventAdminImpl<HandlerTasks,SyncDeliverTasks,AsyncDeliverTasks>::checkNull(void *pObject, const QString &strName)
{
    if(nullptr == pObject) {
        throw QTKInvalidArgumentException(qPrintable(strName + " may not be null"));
    }
}


#endif // QTKEVENTADMINIMPL_P_H
