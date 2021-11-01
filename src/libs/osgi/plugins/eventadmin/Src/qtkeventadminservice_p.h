#ifndef QTKEVENTADMINSERVICE_P_H
#define QTKEVENTADMINSERVICE_P_H

#include "qtkeventadminimpl_p.h"
#include "handler/qtkeacleanblacklist_p.h"
#include "util/qtkealeastrecentlyusedcachemap_p.h"
#include "handler/qtkeacachetopichandlerfilters_p.h"
#include "handler/qtkeacachefilters_p.h"
#include "tasks/qtkeasyncdelivertasks_p.h"
#include "tasks/qtkeaasyncdelivertasks_p.h"
#include "dispatch/qtkeasignalpublisher_p.h"

#include <QTKPluginFramework/Service/Event/QTKEventAdmin>

#include <QObject>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

class QTKEASlotHandler;

class QTKEventAdminService : public QObject, public QTKEventAdmin
{
    Q_OBJECT
    Q_INTERFACES(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKEventAdmin)

public:
    typedef QTKEACleanBlackList BlackList;
    typedef QTKEABlackList<BlackList> BlackListInterface;

    typedef QTKEALeastRecentlyUsedCacheMap<QString, QString> TopicCacheMap;
    typedef QTKEACacheTopicHandlerFilters<TopicCacheMap> TopicHandlerFilters;
    typedef QTKEATopicHandlerFilters<TopicHandlerFilters> TopicHandlerFiltersInterface;
    typedef QTKEALeastRecentlyUsedCacheMap<QString, QTKLDAPSearchFilter> LDAPCacheMap;
    typedef QTKEACacheFilters<LDAPCacheMap> Filters;
    typedef QTKEAFilters<Filters> FiltersInterface;

    typedef QTKEABlacklistingHandlerTasks<BlackList, TopicHandlerFilters, Filters> BlacklistingHandlerTasks;
    typedef QTKEAHandlerTasks<BlacklistingHandlerTasks> HandlerTasksInterface;

    typedef QTKEAHandlerTask<BlacklistingHandlerTasks> HandlerTask;
    typedef HandlerTask HandlerTaskInterface;
    typedef QTKEASyncDeliverTasks<HandlerTask> SyncDeliverTasks;
    typedef QTKEADeliverTask<SyncDeliverTasks, HandlerTask> SyncDeliverTasksInterface;
    typedef QTKEAAsyncDeliverTasks<SyncDeliverTasks, HandlerTask> AsyncDeliverTasks;
    typedef QTKEADeliverTask<AsyncDeliverTasks, HandlerTask> AsyncDeliverTasksInterface;

public:
    QTKEventAdminService(QTKPluginContext* pContext,
                         HandlerTasksInterface* pManagers,
                         QTKEADefaultThreadPool* pSyncPool,
                         QTKEADefaultThreadPool* pAsyncPool,
                         int iTimeout,
                         const QStringList& listIgnoreTimeout);

    ~QTKEventAdminService();

    void postEvent(const QTKEvent &event);

    void sendEvent(const QTKEvent &event);

    void publishSignal(const QObject *pPublisher, const char *psSignal,
                       const QString &strTopic,
                       Qt::ConnectionType eType = Qt::QueuedConnection);

    void unpublishSignal(const QObject *pPublisher, const char *psSignal = nullptr,
                         const QString &strTopic = "");

    qlonglong subscribeSlot(const QObject *pSubscriber, const char *psMember,
                            const QTKDictionary &properties,
                            Qt::ConnectionType eType = Qt::AutoConnection);

    void unsubscribeSlot(qlonglong llSubscriptionId);

    bool updateProperties(qlonglong llSubscriptionId, const QTKDictionary &properties);

    void stop();

    void update(HandlerTasksInterface *pManagers, int iTimeout,
                const QStringList &listIgnoreTimeout);

private:
    QTKEventAdminImpl<BlacklistingHandlerTasks, SyncDeliverTasks, AsyncDeliverTasks> m_impl;

    QTKPluginContext *m_pContext;
    QHash<const QObject*, QList<QTKEASignalPublisher*> > m_mapSignalPublisher;
    QHash<qlonglong, QTKEASlotHandler*> m_mapSlotHandler;
};

#endif // QTKEVENTADMINSERVICE_P_H
