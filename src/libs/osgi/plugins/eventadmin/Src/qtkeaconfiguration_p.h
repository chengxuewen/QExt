#ifndef QTKEACONFIGURATION_P_H
#define QTKEACONFIGURATION_P_H

#include "dispatch/qtkeadefaultthreadpool_p.h"
#include "qtkeventadminservice_p.h"

#include <QTKPluginFramework/Service/Config/QTKManagedService>
#include <QTKPluginFramework/QTKPluginContext>

#include <QString>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

class QTKEAAbstractAdapter;

class QTKEAConfiguration : public QObject, public QTKManagedService
{
    Q_OBJECT
    Q_INTERFACES(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKManagedService)

public:
    QTKEAConfiguration(QTKPluginContext *pPluginContext);
    ~QTKEAConfiguration();

    void updated(const QTKDictionary &properties);

    void updateFromConfigAdmin(const QTKDictionary &config);

    void configure(const QTKDictionary &config);

    void destroy();

    /** The PID for the event admin. */
    static const char *PID; // = "org.qtk.eventadmin.impl.EventAdmin"

    static const char *PROP_CACHE_SIZE; // = "org.qtk.eventadmin.CacheSize"
    static const char *PROP_THREAD_POOL_SIZE; // = "org.qtk.eventadmin.ThreadPoolSize"
    static const char *PROP_TIMEOUT; // = "org.qtk.eventadmin.Timeout"
    static const char *PROP_REQUIRE_TOPIC; // = "org.qtk.eventadmin.RequireTopic"
    static const char *PROP_IGNORE_TIMEOUT; // = "org.qtk.eventadmin.IgnoreTimeout"
    static const char *PROP_LOG_LEVEL; // = "org.qtk.eventadmin.LogLevel"

private:
    void startOrUpdate();

    void adaptEvents(QTKEventAdmin *pAdmin);

    QObject* tryToCreateMetaTypeProvider(QTKManagedService *pManagedService);

    int getIntProperty(const QString &strKey, const QVariant &value, int iDefaultValue, int iMin);

    bool getBoolProperty(const QVariant &obj, bool bDefaultValue);

private:
    QMutex m_mutex;
    /** The plugin context. */
    QTKPluginContext *m_pPluginContext;
    int m_iCacheSize;
    int m_iThreadPoolSize;
    int m_iTimeout;
    bool m_bRequireTopic;
    QStringList m_listIgnoreTimeout;
    int m_iLogLevel;
    // The thread pool used - this is a member because we need to close it on stop
    QTKEADefaultThreadPool *m_pSyncPool;
    QTKEADefaultThreadPool *m_pAsyncPool;
    // The actual implementation of the service - this is a member because we need to
    // close it on stop. Note, security is not part of this implementation but is
    // added via a decorator in the start method (this is the wrapped object without
    // the wrapper).
    QTKEventAdminService *m_pAdmin;
    QScopedPointer<QObject> m_pMetaTypeService;
    // The registration of the security decorator factory (i.e., the service)
    QTKServiceRegistration m_registration;
    // all adapters
    QList<QTKEAAbstractAdapter *> m_listAdapters;
    QTKServiceRegistration m_managedServiceReg;
};


#endif // QTKEACONFIGURATION_P_H
