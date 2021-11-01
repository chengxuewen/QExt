#include "qtkeaconfiguration_p.h"
#include "qtkeventadminservice_p.h"
#include "qtkeametatypeprovider_p.h"
#include "adapter/qtkeaframeworkeventadapter_p.h"
#include "adapter/qtkealogeventadapter_p.h"
#include "adapter/qtkeaplugineventadapter_p.h"
#include "adapter/qtkeaserviceeventadapter_p.h"

#include <QTKPluginFramework/QTKPluginContext>
#include <QTKPluginFramework/QTKPluginConstants>

#include <QtConcurrentRun>

const char *QTKEAConfiguration::PID = "org.qtk.eventadmin.impl.eventadmin";

const char *QTKEAConfiguration::PROP_CACHE_SIZE = "org.qtk.eventadmin.CacheSize";
const char *QTKEAConfiguration::PROP_THREAD_POOL_SIZE = "org.qtk.eventadmin.ThreadPoolSize";
const char *QTKEAConfiguration::PROP_TIMEOUT = "org.qtk.eventadmin.Timeout";
const char *QTKEAConfiguration::PROP_REQUIRE_TOPIC = "org.qtk.eventadmin.RequireTopic";
const char *QTKEAConfiguration::PROP_IGNORE_TIMEOUT = "org.qtk.eventadmin.IgnoreTimeout";
const char *QTKEAConfiguration::PROP_LOG_LEVEL = "org.qtk.eventadmin.LogLevel";


QTKEAConfiguration::QTKEAConfiguration(QTKPluginContext *pPluginContext )
    : m_pPluginContext(pPluginContext),
      m_pSyncPool(nullptr),
      m_pAsyncPool(nullptr),
      m_pAdmin(nullptr)
{
    // default configuration
    this->configure(QTKDictionary());
    this->startOrUpdate();

    try {
        QObject *pService = this;

        // add meta type provider
        m_pMetaTypeService.reset(tryToCreateMetaTypeProvider(qobject_cast<QTKManagedService*>(pService)));
        QStringList listInterfaceNames;
        if (m_pMetaTypeService.isNull()) {
            listInterfaceNames.append(getIIDs<QTKManagedService>());
        } else {
            listInterfaceNames.append(getIIDs<QTKManagedService, QTKMetaTypeProvider>());
            pService = m_pMetaTypeService.data();
        }
        QTKDictionary props;
        props.insert(QTKPluginConstants::SERVICE_PID, PID);
        m_managedServiceReg = pPluginContext->registerService(listInterfaceNames, pService, props);
    } catch (...) {
        // don't care
    }
}

QTKEAConfiguration::~QTKEAConfiguration()
{
    this->destroy();
}

void QTKEAConfiguration::updateFromConfigAdmin(const QTKDictionary &config)
{
    QMutexLocker lock(&m_mutex);
    this->configure(config);
    this->startOrUpdate();
}

void QTKEAConfiguration::configure(const QTKDictionary &config)
{
    if (config.isEmpty()) {
        // The size of various internal caches. At the moment there are 4
        // internal caches affected. Each will cache the determined amount of
        // small but frequently used objects (i.e., in case of the default value
        // we end-up with a total of 120 small objects being cached). A value of less
        // then 10 triggers the default value.
        m_iCacheSize = getIntProperty(PROP_CACHE_SIZE, m_pPluginContext->getProperty(PROP_CACHE_SIZE), 30, 10);

        // The size of the internal thread pool. Note that we must execute
        // each synchronous event dispatch that happens in the synchronous event
        // dispatching thread in a new thread, hence a small thread pool is o.k.
        // A value of less then 2 triggers the default value. A value of 2
        // effectively disables thread pooling. Furthermore, this will be used by
        // a lazy thread pool (i.e., new threads are created when needed). Ones the
        // the size is reached and no cached thread is available new threads will
        // be created.
        m_iThreadPoolSize = getIntProperty(PROP_THREAD_POOL_SIZE, m_pPluginContext->getProperty(PROP_THREAD_POOL_SIZE), 20, 2);

        // The timeout in milliseconds - A value of less then 100 turns timeouts off.
        // Any other value is the time in milliseconds granted to each EventHandler
        // before it gets blacklisted.
        m_iTimeout = getIntProperty(PROP_TIMEOUT, m_pPluginContext->getProperty(PROP_TIMEOUT), 5000, INT_MIN);

        // Are EventHandler required to be registered with a topic? - The default is
        // true. The specification says that EventHandler must register with a list
        // of topics they are interested in. Setting this value to false will enable
        // that handlers without a topic are receiving all events
        // (i.e., they are treated the same as with a topic=*).
        m_bRequireTopic = getBoolProperty(m_pPluginContext->getProperty(PROP_REQUIRE_TOPIC), true);
        QVariant value = m_pPluginContext->getProperty(PROP_IGNORE_TIMEOUT);
        if (value.isValid()) {
            m_listIgnoreTimeout = value.toStringList();
        } else {
            m_listIgnoreTimeout.clear();
        }
        m_iLogLevel = getIntProperty(PROP_LOG_LEVEL, m_pPluginContext->getProperty(PROP_LOG_LEVEL),
                                     QTKLogService::LOG_WARNING, // default log level is WARNING
                                     QTKLogService::LOG_ERROR);
    } else {
        m_iCacheSize = getIntProperty(PROP_CACHE_SIZE, config.value(PROP_CACHE_SIZE), 30, 10);
        m_iThreadPoolSize = getIntProperty(PROP_THREAD_POOL_SIZE, config.value(PROP_THREAD_POOL_SIZE), 20, 2);
        m_iTimeout = getIntProperty(PROP_TIMEOUT, config.value(PROP_TIMEOUT), 5000, INT_MIN);
        m_bRequireTopic = getBoolProperty(config.value(PROP_REQUIRE_TOPIC), true);
        m_listIgnoreTimeout.clear();
        QVariant value = config.value(PROP_IGNORE_TIMEOUT);
        if (value.canConvert<QStringList>()) {
            m_listIgnoreTimeout = value.toStringList();
        } else {
            QTK_WARN(QTKEventAdminActivator::getLogService())
                    << "Value for property:" << PROP_IGNORE_TIMEOUT << " cannot be converted to QStringList - Using default";
        }
        m_iLogLevel = getIntProperty(PROP_LOG_LEVEL, config.value(PROP_LOG_LEVEL),
                                     QTKLogService::LOG_WARNING, // default log level is WARNING
                                     QTKLogService::LOG_ERROR);
    }
    // a timeout less or equals to 100 means : disable timeout
    if (m_iTimeout <= 100) {
        m_iTimeout = 0;
    }
}

void QTKEAConfiguration::destroy()
{
    QMutexLocker lock(&m_mutex);
    if (!m_listAdapters.isEmpty()) {
        foreach (QTKEAAbstractAdapter *pAdapter, m_listAdapters) {
            pAdapter->destroy(m_pPluginContext);
            delete pAdapter;
        }
        m_listAdapters.clear();
    }
    if (m_managedServiceReg) {
        m_managedServiceReg.unregister();
        m_managedServiceReg = 0;
    }
    // We need to unregister manually
    if (m_registration) {
        m_registration.unregister();
        m_registration = 0;
    }
    if (m_pAdmin) {
        m_pAdmin->stop();
        delete m_pAdmin;
        m_pAdmin = nullptr;
    }
    if (m_pAsyncPool) {
        m_pAsyncPool->close();
        delete m_pAsyncPool;
        m_pAsyncPool = nullptr;
    }
    if (m_pSyncPool) {
        m_pSyncPool->close();
        delete m_pSyncPool;
        m_pSyncPool = nullptr;
    }
}

void QTKEAConfiguration::startOrUpdate()
{
    QTKEventAdminService::TopicHandlerFiltersInterface *pTopicHandlerFilters =
            new QTKEventAdminService::TopicHandlerFilters(
                new QTKEventAdminService::TopicCacheMap(m_iCacheSize), m_bRequireTopic);

    QTKEventAdminService::FiltersInterface *pFilters =
            new QTKEventAdminService::Filters(
                new QTKEventAdminService::LDAPCacheMap(m_iCacheSize), m_pPluginContext);

    // Note that this uses a lazy thread pool that will create new threads on
    // demand - in case none of its cached threads is free - until threadPoolSize
    // is reached. Subsequently, a threadPoolSize of 2 effectively disables
    // caching of threads.
    if (nullptr == m_pSyncPool) {
        m_pSyncPool = new QTKEADefaultThreadPool(m_iThreadPoolSize, true);
    } else {
        m_pSyncPool->configure(m_iThreadPoolSize);
    }

    int iAsyncThreadPoolSize = m_iThreadPoolSize > 5 ? m_iThreadPoolSize / 2 : 2;
    if (nullptr == m_pAsyncPool) {
        m_pAsyncPool = new QTKEADefaultThreadPool(iAsyncThreadPoolSize, false);
    } else {
        m_pAsyncPool->configure(iAsyncThreadPoolSize);
    }

    // The handlerTasks object is responsible to determine concerned QTKEventHandler
    // for a given event. Additionally, it keeps a list of blacklisted handlers.
    // Note that blacklisting is deactivated by selecting a different scheduler
    // below (and not in this HandlerTasks object!)
    QTKEventAdminService::HandlerTasksInterface *pHandlerTasks =
            new QTKEventAdminService::BlacklistingHandlerTasks(
                m_pPluginContext, new QTKEventAdminService::BlackList(), pTopicHandlerFilters, pFilters);

    if (nullptr == m_pAdmin) {
        m_pAdmin = new QTKEventAdminService(m_pPluginContext, pHandlerTasks, m_pSyncPool, m_pAsyncPool,
                                            m_iTimeout, m_listIgnoreTimeout);

        // Finally, adapt the outside events to our kind of events as per spec
        this->adaptEvents(m_pAdmin);

        // register the admin wrapped in a service factory (SecureEventAdminFactory)
        // that hands-out the m_admin object wrapped in a decorator that checks
        // appropriated permissions of each calling plugin
        //TODO SecureEventAdminFactory
        //registration = pluginContext->registerService<QTKEventAdmin>(
        //      new QTKEASecureEventAdminFactory(admin));
        m_registration = m_pPluginContext->registerService<QTKEventAdmin>(m_pAdmin);
    } else {
        m_pAdmin->update(pHandlerTasks, m_iTimeout, m_listIgnoreTimeout);
    }

}

void QTKEAConfiguration::adaptEvents(QTKEventAdmin *pAdmin)
{
    m_listAdapters << new QTKEAFrameworkEventAdapter(m_pPluginContext, pAdmin);
    m_listAdapters << new QTKEAPluginEventAdapter(m_pPluginContext, pAdmin);
    m_listAdapters << new QTKEAServiceEventAdapter(m_pPluginContext, pAdmin);
    m_listAdapters << new QTKEALogEventAdapter(m_pPluginContext, pAdmin);
}

QObject *QTKEAConfiguration::tryToCreateMetaTypeProvider(QTKManagedService *pManagedService)
{
    try {
        return new QTKEAMetaTypeProvider(pManagedService, m_iCacheSize, m_iThreadPoolSize,
                                         m_iTimeout, m_bRequireTopic, m_listIgnoreTimeout);
    } catch (...) {
        // we simply ignore this
    }
    return nullptr;
}

void QTKEAConfiguration::updated(const QTKDictionary &properties)
{
    // do this in the background as we don't want to stop
    // the config admin
    QtConcurrent::run(this, &QTKEAConfiguration::updateFromConfigAdmin, properties);
}

int QTKEAConfiguration::getIntProperty(const QString &strKey, const QVariant &value,
                                       int iDefaultValue, int iMin)
{
    if(value.isValid()) {
        int iResult = iDefaultValue;
        if (value.canConvert<int>()) {
            bool bOk;
            iResult = value.toInt(&bOk);
            if (!bOk) {
                QTK_WARN(QTKEventAdminActivator::getLogService())
                        << "Unable to parse property: " << strKey << " - Using default: " << iDefaultValue;
                return iDefaultValue;
            }
        } else {
            QTK_WARN(QTKEventAdminActivator::getLogService())
                    << "Unable to convert property to int: " << strKey << " - Using default: " << iDefaultValue;
            return iDefaultValue;
        }

        if(iResult >= iMin) {
            return iResult;
        }

        QTK_WARN(QTKEventAdminActivator::getLogService())
                << "Value for property: " << strKey << " is too low - Using default: " << iDefaultValue;
    }

    return iDefaultValue;
}

bool QTKEAConfiguration::getBoolProperty(const QVariant &value, bool bDefaultValue)
{
    if(value.isValid()) {
        if (value.canConvert<bool>()) {
            return value.toBool();
        }
    }

    return bDefaultValue;
}
