#include "qtkmtprovidertracker_p.h"
#include "qtkmtmsg_p.h"

#include <QTKPluginFramework/Service/Config/QTKManagedService>
#include <QTKPluginFramework/Service/Config/QTKManagedServiceFactory>
#include <QTKPluginFramework/Service/Log/QTKLogService>

#include <QCoreApplication>

class QTKMTProviderTracker::MetaTypeProviderWrapper
{
public:

    QTKMetaTypeProvider* provider;
    QString pid;
    bool factory;

    MetaTypeProviderWrapper(QTKMetaTypeProvider* provider, const QString& pid, bool factory)
        : provider(provider), pid(pid), factory(factory)
    {

    }

    bool operator==(const MetaTypeProviderWrapper& o) const
    {
        if (this == &o)
            return true;
        return provider == o.provider && pid == o.pid && factory == o.factory;
    }

};

uint qHash(const QTKMTProviderTracker::MetaTypeProviderWrapper wrapper)
{
    uint result = 17;
    result = 31 * result + qHash(wrapper.provider);
    result = 31 * result + qHash(wrapper.pid);
    result = 31 * result + (wrapper.factory ? 1 : 0);
    return result;
}

QTKMTProviderTracker::QTKMTProviderTracker(const QSharedPointer<QTKPlugin>& plugin, QTKLogService* log, QTKServiceTracker<>* tracker)
    : _plugin(plugin), log(log), _tracker(tracker)
{

}

QStringList QTKMTProviderTracker::getPids() const
{
    return getPids(false);
}

QStringList QTKMTProviderTracker::getFactoryPids() const
{
    return getPids(true);
}

QSharedPointer<QTKPlugin> QTKMTProviderTracker::getPlugin() const
{
    return _plugin;
}

QTKObjectClassDefinitionPtr QTKMTProviderTracker::getObjectClassDefinition(const QString& id, const QLocale& locale)
{
    if (_plugin->getState() != QTKPlugin::State_Active)
    {
        return QTKObjectClassDefinitionPtr(); // return none if not active
    }

    QSet<MetaTypeProviderWrapper> wrappers = getMetaTypeProviders();
    QSet<MetaTypeProviderWrapper>::ConstIterator end = wrappers.end();
    for (QSet<MetaTypeProviderWrapper>::ConstIterator it = wrappers.begin();
         it != end; ++it)
    {
        if (id == (*it).pid)
        {
            // found a matching pid now call the actual provider
            return (*it).provider->getObjectClassDefinition(id, locale);
        }
    }
    return QTKObjectClassDefinitionPtr();
}

QList<QLocale> QTKMTProviderTracker::getLocales() const
{
    if (_plugin->getState() != QTKPlugin::State_Active)
    {
        return QList<QLocale>(); // return none if not active
    }

    QSet<MetaTypeProviderWrapper> wrappers = getMetaTypeProviders();
    QList<QLocale> locales;
    // collect all the unique locales from all providers we found
    QSet<MetaTypeProviderWrapper>::ConstIterator end = wrappers.end();
    for (QSet<MetaTypeProviderWrapper>::ConstIterator it = wrappers.begin();
         it != end; ++it)
    {
        QList<QLocale> wrappedLocales = (*it).provider->getLocales();
        if (wrappedLocales.isEmpty())
            continue;
        for (int j = 0; j < wrappedLocales.size(); j++)
            if (!locales.contains(wrappedLocales[j]))
                locales.push_back(wrappedLocales[j]);
    }
    return locales;
}

QStringList QTKMTProviderTracker::getPids(bool factory) const
{
    if (_plugin->getState() != QTKPlugin::State_Active)
    {
        return QStringList(); // return none if not active
    }

    QSet<MetaTypeProviderWrapper> wrappers = getMetaTypeProviders();
    QStringList results;
    QSet<MetaTypeProviderWrapper>::ConstIterator end = wrappers.end();
    for (QSet<MetaTypeProviderWrapper>::ConstIterator it = wrappers.begin();
         it != end; ++it)
    {
        // return only the correct type of pids (regular or factory)
        if (factory == (*it).factory)
            results.push_back((*it).pid);
    }
    return results;
}

QSet<QTKMTProviderTracker::MetaTypeProviderWrapper> QTKMTProviderTracker::getMetaTypeProviders() const
{
    QMap<QTKServiceReference, QObject*> services = _tracker->getTracked();
    if (services.isEmpty())
    {
        return QSet<MetaTypeProviderWrapper>();
    }
    QList<QTKServiceReference> serviceReferences = services.keys();
    QSet<MetaTypeProviderWrapper> result;
    foreach (QTKServiceReference serviceReference, serviceReferences)
    {
        if (serviceReference.getPlugin() == _plugin)
        {
            QObject* service = services.value(serviceReference);
            // If the service is not a QTKMetaTypeProvider, we're not interested in it.
            if (QTKMetaTypeProvider* metatypeService = qobject_cast<QTKMetaTypeProvider*>(service))
            {
                // Include the METATYPE_PID, if present, to return as part of getPids(). Also, include the
                // METATYPE_FACTORY_PID, if present, to return as part of getFactoryPids().
                // The filter ensures at least one of these properties was set for a standalone QTKMetaTypeProvider.
                addMetaTypeProviderWrappers(QTKMetaTypeProvider::METATYPE_PID, serviceReference, metatypeService, false, result);
                addMetaTypeProviderWrappers(QTKMetaTypeProvider::METATYPE_FACTORY_PID, serviceReference, metatypeService, true, result);
                // If the service is a QTKManagedService, include the SERVICE_PID to return as part of getPids().
                // The filter ensures the SERVICE_PID property was set.
                if (qobject_cast<QTKManagedService*>(service))
                {
                    addMetaTypeProviderWrappers(QTKPluginConstants::SERVICE_PID, serviceReference, metatypeService, false, result);
                }
                // If the service is a QTKManagedServiceFactory, include the SERVICE_PID to return as part of getFactoryPids().
                // The filter ensures the SERVICE_PID property was set.
                else if (qobject_cast<QTKManagedServiceFactory*>(service))
                {
                    addMetaTypeProviderWrappers(QTKPluginConstants::SERVICE_PID, serviceReference, metatypeService, true, result);
                }
            }
        }
    }
    return result;
}

void QTKMTProviderTracker::addMetaTypeProviderWrappers(const QString& servicePropertyName,
                                                       const QTKServiceReference& serviceReference,
                                                       QTKMetaTypeProvider* service, bool factory,
                                                       QSet<MetaTypeProviderWrapper>& wrappers) const
{
    QStringList pids = getStringProperty(servicePropertyName, serviceReference.getProperty(servicePropertyName));
    foreach (QString pid, pids)
    {
        wrappers.insert(MetaTypeProviderWrapper(service, pid, factory));
    }
}

QStringList QTKMTProviderTracker::getStringProperty(const QString& name, const QVariant& value) const
{
    // Don't log a warning if the value is null. The filter guarantees at least one of the necessary properties
    // is there. If others are not, this method will get called with value equal to null.
    if (value.isNull())
        return QStringList();

    if (value.canConvert<QStringList>())
    {
        return value.toStringList();
    }

    QTK_WARN(log) << QCoreApplication::translate(QTKMTMsg::CONTEXT, QTKMTMsg::INVALID_PID_METATYPE_PROVIDER_IGNORED)
                     .arg(_plugin->getSymbolicName()).arg(_plugin->getPluginId()).arg(name). arg(value.toString());
    return QStringList();
}

