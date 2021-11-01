#include "qtkcmpluginmanager_p.h"

#include <QTKPluginFramework/QTKServiceTracker>
#include <QTKPluginFramework/Service/Config/QTKConfigurationPlugin>

#include <QStringList>

#include <set>

struct QTKPluginTrackerCompare
{
    bool operator() (const QTKServiceReference& l, const QTKServiceReference& r) const
    {
        return getRank(l) < getRank(r);
    }

    int getRank(const QTKServiceReference& ref) const
    {
        QVariant ranking = ref.getProperty(QTKConfigurationPlugin::CM_RANKING);
        if (!ranking.isValid() || !(ranking.canConvert<int>()))
            return 0;
        return ranking.toInt();
    }
};

class QTKPluginTracker : public QTKServiceTracker<QTKConfigurationPlugin*>
{
    mutable QMutex mutex;
    typedef std::set<QTKServiceReference, QTKPluginTrackerCompare> ServiceRefContainer;
    ServiceRefContainer serviceReferences;
    QTKPluginContext* context;

public:

    QTKPluginTracker(QTKPluginContext* context)
        : QTKServiceTracker<QTKConfigurationPlugin*>(context),
          context(context)
    {
    }

    QList<QTKServiceReference> getServiceReferences() const
    {
        QMutexLocker lock(&mutex);
        QList<QTKServiceReference> refs;
        ServiceRefContainer::const_iterator refEnd = serviceReferences.end();
        for (ServiceRefContainer::const_iterator it = serviceReferences.begin();
             it != refEnd; ++it)
        {
            refs.push_back(*it);
        }
        return refs;
    }

    QTKConfigurationPlugin* addingService(const QTKServiceReference& reference)
    {
        QMutexLocker lock(&mutex);
        serviceReferences.insert(reference);
        return context->getService<QTKConfigurationPlugin>(reference);
    }

    void modifiedService(const QTKServiceReference& reference, QTKConfigurationPlugin* service)
    {
        Q_UNUSED(reference)
        Q_UNUSED(service)
        // nothing to do
    }

    void removedService(const QTKServiceReference& reference, QTKConfigurationPlugin* service)
    {
        Q_UNUSED(service)

        QMutexLocker lock(&mutex);
        serviceReferences.erase(reference);
        context->ungetService(reference);
    }
};

QTKCMPluginManager::QTKCMPluginManager(QTKPluginContext* context)
{
    pluginTracker.reset(new QTKPluginTracker(context));
}

QTKCMPluginManager::~QTKCMPluginManager()
{

}

void QTKCMPluginManager::start()
{
    pluginTracker->open();
}

void QTKCMPluginManager::stop()
{
    pluginTracker->close();
}

void QTKCMPluginManager::modifyConfiguration(const QTKServiceReference& managedReference, QTKDictionary& properties)
{
    if (properties.empty())
        return;

    QList<QTKServiceReference> references = pluginTracker->getServiceReferences();
    foreach(QTKServiceReference ref, references)
    {
        QVariant pids = ref.getProperty(QTKConfigurationPlugin::CM_TARGET);
        if (pids.isValid() && pids.canConvert<QStringList>())
        {
            QString pid = properties.value(QTKPluginConstants::SERVICE_PID).toString();
            if (!pids.toStringList().contains(pid))
                continue;
        }
        QTKConfigurationPlugin* plugin = pluginTracker->getService(ref);
        if (plugin != 0)
            plugin->modifyConfiguration(managedReference, properties);
    }
}
