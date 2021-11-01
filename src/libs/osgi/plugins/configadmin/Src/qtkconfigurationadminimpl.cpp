#include "qtkconfigurationadminimpl_p.h"
#include "qtkconfigurationadminfactory_p.h"
#include "qtkconfigurationstore_p.h"

QTKConfigurationAdminImpl::QTKConfigurationAdminImpl(QTKConfigurationAdminFactory* configurationAdminFactory,
                                                     QTKConfigurationStore* configurationStore,
                                                     QSharedPointer<QTKPlugin> plugin)
    : configurationAdminFactory(configurationAdminFactory),
      plugin(plugin), configurationStore(configurationStore)
{

}

QTKConfigurationPtr QTKConfigurationAdminImpl::createFactoryConfiguration(const QString& factoryPid)
{
    checkPID(factoryPid);
    return configurationStore->createFactoryConfiguration(factoryPid, plugin->getLocation());
}

QTKConfigurationPtr QTKConfigurationAdminImpl::createFactoryConfiguration(const QString& factoryPid,
                                                                          const QString& location)
{
    checkPID(factoryPid);
    configurationAdminFactory->checkConfigurationPermission();
    return configurationStore->createFactoryConfiguration(factoryPid, location);
}

QTKConfigurationPtr QTKConfigurationAdminImpl::getConfiguration(const QString& pid)
{
    checkPID(pid);
    QTKConfigurationImplPtr config = configurationStore->getConfiguration(pid, plugin->getLocation());
    if (!config->getPluginLocation(false).isEmpty() && config->getPluginLocation(false) != plugin->getLocation())
    {
        configurationAdminFactory->checkConfigurationPermission();
    }
    config->bind(plugin);
    return config;
}

QTKConfigurationPtr QTKConfigurationAdminImpl::getConfiguration(const QString& pid, const QString& location)
{
    checkPID(pid);
    configurationAdminFactory->checkConfigurationPermission();
    return configurationStore->getConfiguration(pid, location);
}

QList<QTKConfigurationPtr> QTKConfigurationAdminImpl::listConfigurations(const QString& filter)
{
    QString filterString = filter;
    if (filterString.isEmpty())
    {
        filterString = QString("(%1=*)").arg(QTKPluginConstants::SERVICE_PID);
    }

    //TODO security
    //try
    //{
    configurationAdminFactory->checkConfigurationPermission();
    //}
    //catch (SecurityException e) {
    //  filterString = "(&(" + ConfigurationAdmin.SERVICE_BUNDLELOCATION + "=" + bundle.getLocation() + ")" + filterString + ")";
    //}
    QList<QTKConfigurationImplPtr> configs = configurationStore->listConfigurations(QTKLDAPSearchFilter(filterString));
    QList<QTKConfigurationPtr> result;
    foreach(QTKConfigurationImplPtr config, configs)
    {
        result.push_back(config);
    }
    return result;
}

void QTKConfigurationAdminImpl::checkPID(const QString& pid)
{
    if (pid.isEmpty())
    {
        throw QTKInvalidArgumentException("PID cannot be empty");
    }
}
