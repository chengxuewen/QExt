#include "qtkmanagedservicefactorytracker_p.h"
#include "qtkconfigurationadminactivator_p.h"
#include "qtkconfigurationadminfactory_p.h"
#include "qtkconfigurationstore_p.h"
#include "qtkconfigurationimpl_p.h"

#include <QTKPluginFramework/Service/Config/QTKConfigurationException>
#include <QTKPluginFramework/Service/Log/QTKLogService>

#include <QRunnable>

QTKManagedServiceFactoryTracker::QTKManagedServiceFactoryTracker(
        QTKConfigurationAdminFactory* configurationAdminFactory,
        QTKConfigurationStore* configurationStore,
        QTKPluginContext* context)
    : QTKServiceTracker<QTKManagedServiceFactory*>(context),
      context(context),
      configurationAdminFactory(configurationAdminFactory),
      configurationStoreMutex(QMutex::Recursive),
      configurationStore(configurationStore),
      queue("QTKManagedServiceFactory Update Queue")
{

}

QTKManagedServiceFactory* QTKManagedServiceFactoryTracker::addingService(const QTKServiceReference& reference)
{
    QString factoryPid = reference.getProperty(QTKPluginConstants::SERVICE_PID).toString();
    if (factoryPid.isEmpty())
        return 0;

    QTKManagedServiceFactory* service = context->getService<QTKManagedServiceFactory>(reference);
    if (service == 0)
        return 0;

    {
        QMutexLocker lock(&configurationStoreMutex);
        addManagedServiceFactory(reference, factoryPid, service);
    }
    return service;
}

void QTKManagedServiceFactoryTracker::modifiedService(const QTKServiceReference& reference,
                                                      QTKManagedServiceFactory* service)
{
    QString factoryPid = reference.getProperty(QTKPluginConstants::SERVICE_PID).toString();
    {
        QMutexLocker lock(&configurationStoreMutex);
        if (getManagedServiceFactory(factoryPid) == service)
            return;
        QString previousPid = getPidForManagedServiceFactory(service);
        removeManagedServiceFactory(reference, previousPid);
        addingService(reference);
    }
}

void QTKManagedServiceFactoryTracker::removedService(const QTKServiceReference& reference,
                                                     QTKManagedServiceFactory* service)
{
    Q_UNUSED(service)

    QString factoryPid = reference.getProperty(QTKPluginConstants::SERVICE_PID).toString();
    {
        QMutexLocker lock(&configurationStoreMutex);
        removeManagedServiceFactory(reference, factoryPid);
    }
    context->ungetService(reference);
}

void QTKManagedServiceFactoryTracker::notifyDeleted(QTKConfigurationImpl* config)
{
    config->checkLocked();
    QString factoryPid = config->getFactoryPid(false);
    QTKServiceReference reference = getManagedServiceFactoryReference(factoryPid);
    if (reference && config->bind(reference.getPlugin()))
    {
        asynchDeleted(getManagedServiceFactory(factoryPid), config->getPid(false));
    }
}

void QTKManagedServiceFactoryTracker::notifyUpdated(QTKConfigurationImpl* config)
{
    config->checkLocked();
    QString factoryPid = config->getFactoryPid();
    QTKServiceReference reference = getManagedServiceFactoryReference(factoryPid);
    if (reference && config->bind(reference.getPlugin()))
    {
        QTKDictionary properties = config->getProperties();
        configurationAdminFactory->modifyConfiguration(reference, properties);
        asynchUpdated(getManagedServiceFactory(factoryPid), config->getPid(), properties);
    }
}

void QTKManagedServiceFactoryTracker::addManagedServiceFactory(
        const QTKServiceReference& reference, const QString& factoryPid,
        QTKManagedServiceFactory* service)
{
    QList<QTKConfigurationImplPtr> configs = configurationStore->getFactoryConfigurations(factoryPid);
    QTKConfigurationImplLocker lock(configs);

    if (trackManagedServiceFactory(factoryPid, reference, service))
    {
        foreach (QTKConfigurationImplPtr config, configs)
        {
            if (config->isDeleted())
            {
                // ignore this config
            }
            else if (config->bind(reference.getPlugin()))
            {
                QTKDictionary properties = config->getProperties();
                configurationAdminFactory->modifyConfiguration(reference, properties);
                asynchUpdated(service, config->getPid(), properties);
            }
            else
            {
                QTK_WARN(configurationAdminFactory->getLogService())
                        << "Configuration for " << QTKPluginConstants::SERVICE_PID << "="
                        << config->getPid() << " could not be bound to "
                        << reference.getPlugin()->getLocation();
            }
        }
    }
}

void QTKManagedServiceFactoryTracker::removeManagedServiceFactory(
        const QTKServiceReference& reference, const QString& factoryPid)
{
    QList<QTKConfigurationImplPtr> configs = configurationStore->getFactoryConfigurations(factoryPid);
    QTKConfigurationImplLocker lock(configs);
    untrackManagedServiceFactory(factoryPid, reference);
}

bool QTKManagedServiceFactoryTracker::trackManagedServiceFactory(const QString& factoryPid,
                                                                 const QTKServiceReference& reference,
                                                                 QTKManagedServiceFactory* service)
{
    QMutexLocker lock(&managedServiceFactoryMutex);
    if (managedServiceFactoryReferences.contains(factoryPid))
    {
        QTK_WARN(configurationAdminFactory->getLogService())
                << "QTKManagedServiceFactory already registered for "
                << QTKPluginConstants::SERVICE_PID << "=" << factoryPid;
        return false;
    }
    managedServiceFactoryReferences.insert(factoryPid, reference);
    managedServiceFactories.insert(factoryPid, service);
    return true;
}

void QTKManagedServiceFactoryTracker::untrackManagedServiceFactory(const QString& factoryPid,
                                                                   const QTKServiceReference& reference)
{
    Q_UNUSED(reference)

    QMutexLocker lock(&managedServiceFactoryMutex);
    managedServiceFactoryReferences.remove(factoryPid);
    managedServiceFactories.remove(factoryPid);
}

QTKManagedServiceFactory* QTKManagedServiceFactoryTracker::getManagedServiceFactory(const QString& factoryPid) const
{
    QMutexLocker lock(&managedServiceFactoryMutex);
    return managedServiceFactories.value(factoryPid);
}

QTKServiceReference QTKManagedServiceFactoryTracker::getManagedServiceFactoryReference(const QString& factoryPid) const
{
    QMutexLocker lock(&managedServiceFactoryMutex);
    return managedServiceFactoryReferences.value(factoryPid);
}

QString QTKManagedServiceFactoryTracker::getPidForManagedServiceFactory(QTKManagedServiceFactory* service) const
{
    QMutexLocker lock(&managedServiceFactoryMutex);
    QHash<QString, QTKManagedServiceFactory*>::ConstIterator end = managedServiceFactories.end();
    QHash<QString, QTKManagedServiceFactory*>::ConstIterator it;
    for (it = managedServiceFactories.begin(); it != end; ++it)
    {
        if (it.value() == service)
            return it.key();
    }
    return QString();
}

class _AsynchDeleteRunnable : public QRunnable
{
public:

    _AsynchDeleteRunnable(QTKManagedServiceFactory* service, const QString& pid,
                          QTKLogService* log)
        : service(service), pid(pid), log(log)
    {

    }

    void run()
    {
        try
        {
            service->deleted(pid);
        }
        catch (const std::exception* e)
        {
            QTK_ERROR_EXC(log, e);
        }
    }

private:

    QTKManagedServiceFactory* const service;
    const QString pid;
    QTKLogService* const log;
};

void QTKManagedServiceFactoryTracker::asynchDeleted(QTKManagedServiceFactory* service, const QString& pid)
{
    queue.put(new _AsynchDeleteRunnable(service, pid, configurationAdminFactory->getLogService()));
}

class _AsynchFactoryUpdateRunnable : public QRunnable
{
public:

    _AsynchFactoryUpdateRunnable(QTKManagedServiceFactory* service, const QString& pid,
                                 const QTKDictionary& properties, QTKLogService* log)
        : service(service), pid(pid), properties(properties), log(log)
    {

    }

    void run()
    {
        try
        {
            service->updated(pid, properties);
        }
        catch (const QTKConfigurationException* e)
        {
            // we might consider doing more for ConfigurationExceptions
            QTK_ERROR_EXC(log, e);
        }
        catch (const std::exception* e)
        {
            QTK_ERROR_EXC(log, e);
        }
    }

private:

    QTKManagedServiceFactory* const service;
    const QString pid;
    const QTKDictionary properties;
    QTKLogService* const log;
};

void QTKManagedServiceFactoryTracker::asynchUpdated(QTKManagedServiceFactory* service, const QString& pid,
                                                    const QTKDictionary& properties)
{
    queue.put(new _AsynchFactoryUpdateRunnable(service, pid, properties, configurationAdminFactory->getLogService()));
}
