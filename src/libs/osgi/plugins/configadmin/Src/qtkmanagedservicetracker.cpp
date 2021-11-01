#include "qtkmanagedservicetracker_p.h"
#include "qtkconfigurationimpl_p.h"
#include "qtkconfigurationadminfactory_p.h"

#include <QTKPluginFramework/Service/Config/QTKConfigurationException>
#include <QTKPluginFramework/Service/Log/QTKLogService>

#include <QRunnable>

QTKManagedServiceTracker::QTKManagedServiceTracker(QTKConfigurationAdminFactory* configurationAdminFactory,
                                                   QTKConfigurationStore* configurationStore,
                                                   QTKPluginContext* context)
    : QTKServiceTracker<QTKManagedService*>(context),
      context(context),
      configurationAdminFactory(configurationAdminFactory),
      configurationStoreMutex(QMutex::Recursive),
      configurationStore(configurationStore),
      queue("QTKManagedService Update Queue")
{

}

QTKManagedService* QTKManagedServiceTracker::addingService(const QTKServiceReference& reference)
{
    QString pid = reference.getProperty(QTKPluginConstants::SERVICE_PID).toString();
    if (pid.isEmpty())
        return 0;

    QTKManagedService* service = context->getService<QTKManagedService>(reference);
    if (service == 0)
        return 0;

    {
        QMutexLocker lock(&configurationStoreMutex);
        addManagedService(reference, pid, service);
    }
    return service;
}

void QTKManagedServiceTracker::modifiedService(const QTKServiceReference& reference, QTKManagedService* service)
{
    QString pid = reference.getProperty(QTKPluginConstants::SERVICE_PID).toString();
    {
        QMutexLocker lock(&configurationStoreMutex);
        if (getManagedService(pid) == service)
            return;
        QString previousPid = getPidForManagedService(service);
        removeManagedService(reference, previousPid);
        addingService(reference);
    }
}

void QTKManagedServiceTracker::removedService(const QTKServiceReference& reference, QTKManagedService* service)
{
    Q_UNUSED(service)

    QString pid = reference.getProperty(QTKPluginConstants::SERVICE_PID).toString();
    {
        QMutexLocker lock(&configurationStoreMutex);
        removeManagedService(reference, pid);
    }
    context->ungetService(reference);
}

void QTKManagedServiceTracker::notifyDeleted(QTKConfigurationImpl* config)
{
    config->checkLocked();
    QString pid = config->getPid(false);
    QTKServiceReference reference = getManagedServiceReference(pid);
    if (reference && config->bind(reference.getPlugin()))
        asynchUpdated(getManagedService(pid), QTKDictionary());
}

void QTKManagedServiceTracker::notifyUpdated(QTKConfigurationImpl* config) {
    config->checkLocked();
    QString pid = config->getPid();
    QTKServiceReference reference = getManagedServiceReference(pid);
    if (reference && config->bind(reference.getPlugin()))
    {
        QTKDictionary properties = config->getProperties();
        configurationAdminFactory->modifyConfiguration(reference, properties);
        asynchUpdated(getManagedService(pid), properties);
    }
}

void QTKManagedServiceTracker::addManagedService(const QTKServiceReference& reference,
                                                 const QString& pid,
                                                 QTKManagedService* service)
{
    QTKConfigurationImplPtr config = configurationStore->findConfiguration(pid);
    if (config.isNull() && trackManagedService(pid, reference, service))
    {
        asynchUpdated(service, QTKDictionary());
    }
    else
    {
        QTKConfigurationImplLocker lock(config.data());
        if (trackManagedService(pid, reference, service))
        {
            if (!config->getFactoryPid().isEmpty())
            {
                QTK_WARN(configurationAdminFactory->getLogService())
                        << "Configuration for " << QTKPluginConstants::SERVICE_PID << "="
                        << pid << " should only be used by a QTKManagedServiceFactory";
            }
            else if (config->isDeleted())
            {
                asynchUpdated(service, QTKDictionary());
            }
            else if (config->bind(reference.getPlugin()))
            {
                QTKDictionary properties = config->getProperties();
                configurationAdminFactory->modifyConfiguration(reference, properties);
                asynchUpdated(service, properties);
            }
            else
            {
                QTK_WARN(configurationAdminFactory->getLogService())
                        << "Configuration for " << QTKPluginConstants::SERVICE_PID << "="
                        << pid << " could not be bound to " << reference.getPlugin()->getLocation();
            }
        }
    }
}

void QTKManagedServiceTracker::removeManagedService(const QTKServiceReference& reference,
                                                    const QString& pid)
{
    QTKConfigurationImplPtr config = configurationStore->findConfiguration(pid);
    if (config.isNull())
    {
        untrackManagedService(pid, reference);
    }
    else
    {
        QTKConfigurationImplLocker lock(config.data());
        untrackManagedService(pid, reference);
    }
}

bool QTKManagedServiceTracker::trackManagedService(const QString& pid, const QTKServiceReference& reference,
                                                   QTKManagedService* service)
{
    QMutexLocker lock(&managedServiceMutex);
    if (managedServiceReferences.contains(pid))
    {
        QTK_WARN(configurationAdminFactory->getLogService())
                << "QTKManagedService already registered for " << QTKPluginConstants::SERVICE_PID
                << "=" << pid;
        return false;
    }
    managedServiceReferences.insert(pid, reference);
    managedServices.insert(pid, service);
    return true;
}

void QTKManagedServiceTracker::untrackManagedService(const QString& pid, const QTKServiceReference& reference)
{
    Q_UNUSED(reference)

    QMutexLocker lock(&managedServiceMutex);
    managedServiceReferences.remove(pid);
    managedServices.remove(pid);
}

QTKManagedService* QTKManagedServiceTracker::getManagedService(const QString& pid) const
{
    QMutexLocker lock(&managedServiceMutex);
    return managedServices.value(pid);
}

QTKServiceReference QTKManagedServiceTracker::getManagedServiceReference(const QString& pid) const
{
    QMutexLocker lock(&managedServiceMutex);
    return managedServiceReferences.value(pid);
}

QString QTKManagedServiceTracker::getPidForManagedService(QTKManagedService* service) const
{
    QMutexLocker lock(&managedServiceMutex);
    QHash<QString, QTKManagedService*>::ConstIterator end = managedServices.end();
    QHash<QString, QTKManagedService*>::ConstIterator it;
    for (it = managedServices.begin(); it != end; ++it)
    {
        if (it.value() == service)
            return it.key();
    }
    return QString();
}

class _AsynchUpdateRunnable : public QRunnable
{

public:

    _AsynchUpdateRunnable(QTKManagedService* service,
                          const QTKDictionary& properties,
                          QTKLogService* log)
        : service(service), properties(properties), log(log)
    {
    }

    void run()
    {
        try
        {
            service->updated(properties);
        }
        catch (const QTKConfigurationException* e)
        {
            // we might consider doing more for QTKConfigurationExceptions
            QTK_ERROR_EXC(log, e);
        }
        catch (const std::exception* e)
        {
            QTK_ERROR_EXC(log, e);
        }
    }

private:

    QTKManagedService* service;
    const QTKDictionary properties;
    QTKLogService * const log;
};

void QTKManagedServiceTracker::asynchUpdated(QTKManagedService* service, const QTKDictionary& properties)
{
    queue.put(new _AsynchUpdateRunnable(service, properties, configurationAdminFactory->getLogService()));
}
