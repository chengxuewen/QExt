#include "qtkconfigurationadminfactory_p.h"
#include "qtkconfigurationadminimpl_p.h"
#include "qtkconfigurationimpl_p.h"

#include <QTKPluginFramework/Service/Log/QTKLogService>

QTKConfigurationAdminFactory::QTKConfigurationAdminFactory(QTKPluginContext* context, QTKLogService* log)
    : eventDispatcher(context, log), pluginManager(context), logService(log),
      configurationStore(this, context),
      managedServiceTracker(this, &configurationStore, context),
      managedServiceFactoryTracker(this, &configurationStore, context)
{

}

QTKConfigurationAdminFactory::~QTKConfigurationAdminFactory()
{
    qDeleteAll(configAdmins);
}

void QTKConfigurationAdminFactory::start()
{
    eventDispatcher.start();
    pluginManager.start();
    managedServiceTracker.open();
    managedServiceFactoryTracker.open();
}

void QTKConfigurationAdminFactory::stop()
{
    managedServiceTracker.close();
    managedServiceFactoryTracker.close();
    eventDispatcher.stop();
    pluginManager.stop();
}

QObject* QTKConfigurationAdminFactory::getService(QSharedPointer<QTKPlugin> plugin,
                                                  QTKServiceRegistration registration)
{
    QTKServiceReference reference = registration.getReference();
    eventDispatcher.setServiceReference(reference);
    QTKConfigurationAdminImpl* configAdmin = new QTKConfigurationAdminImpl(this, &configurationStore, plugin);
    configAdmins.push_back(configAdmin);
    return configAdmin;
}

void QTKConfigurationAdminFactory::ungetService(QSharedPointer<QTKPlugin> plugin,
                                                QTKServiceRegistration registration, QObject* service)
{
    Q_UNUSED(plugin)
    Q_UNUSED(registration)
    Q_UNUSED(service)
    // do nothing
}

void QTKConfigurationAdminFactory::pluginChanged(const QTKPluginEvent& event)
{
    if (event.getType() == QTKPluginEvent::Type_Uninstalled)
    {
        configurationStore.unbindConfigurations(event.getPlugin());
    }
}

void QTKConfigurationAdminFactory::checkConfigurationPermission()
{
    //TODO security
    //  SecurityManager sm = System.getSecurityManager();
    //  if (sm != null)
    //    sm.checkPermission(configurationPermission);
}

QTKLogService* QTKConfigurationAdminFactory::getLogService() const
{
    return logService;
}

void QTKConfigurationAdminFactory::dispatchEvent(QTKConfigurationEvent::Type type, const QString& factoryPid, const QString& pid)
{
    eventDispatcher.dispatchEvent(type, factoryPid, pid);
}

void QTKConfigurationAdminFactory::notifyConfigurationUpdated(QTKConfigurationImpl* config, bool isFactory)
{
    if (isFactory)
    {
        managedServiceFactoryTracker.notifyUpdated(config);
    }
    else
    {
        managedServiceTracker.notifyUpdated(config);
    }
}

void QTKConfigurationAdminFactory::notifyConfigurationDeleted(QTKConfigurationImpl* config, bool isFactory)
{
    if (isFactory)
    {
        managedServiceFactoryTracker.notifyDeleted(config);
    }
    else
    {
        managedServiceTracker.notifyDeleted(config);
    }
}

void QTKConfigurationAdminFactory::modifyConfiguration(const QTKServiceReference& reference,
                                                       QTKDictionary& properties)
{
    pluginManager.modifyConfiguration(reference, properties);
}
