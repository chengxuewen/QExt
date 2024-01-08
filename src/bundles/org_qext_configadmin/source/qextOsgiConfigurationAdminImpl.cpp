/*=============================================================================

  Library: CTK

  Copyright (c) German Cancer Research Center,
    Division of Medical and Biological Informatics

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=============================================================================*/


#include "qextOsgiConfigurationAdminImpl_p.h"
#include "qextOsgiConfigurationAdminFactory_p.h"
#include "qextOsgiConfigurationStore_p.h"

QExtOsgiConfigurationAdminImpl::QExtOsgiConfigurationAdminImpl(QExtOsgiConfigurationAdminFactory* configurationAdminFactory,
                                                               QExtOsgiConfigurationStore* configurationStore,
                                                               QSharedPointer<QExtOsgiPlugin> plugin)
    : configurationAdminFactory(configurationAdminFactory),
    plugin(plugin), configurationStore(configurationStore)
{

}

QExtOsgiConfigurationPtr QExtOsgiConfigurationAdminImpl::createFactoryConfiguration(const QString& factoryPid)
{
    checkPID(factoryPid);
    return configurationStore->createFactoryConfiguration(factoryPid, plugin->getLocation());
}

QExtOsgiConfigurationPtr QExtOsgiConfigurationAdminImpl::createFactoryConfiguration(const QString& factoryPid,
                                                                                    const QString& location)
{
    checkPID(factoryPid);
    configurationAdminFactory->checkConfigurationPermission();
    return configurationStore->createFactoryConfiguration(factoryPid, location);
}

QExtOsgiConfigurationPtr QExtOsgiConfigurationAdminImpl::getConfiguration(const QString& pid)
{
    checkPID(pid);
    QExtOsgiConfigurationImplPtr config = configurationStore->getConfiguration(pid, plugin->getLocation());
    if (!config->getPluginLocation(false).isEmpty() && config->getPluginLocation(false) != plugin->getLocation())
    {
        configurationAdminFactory->checkConfigurationPermission();
    }
    config->bind(plugin);
    return config;
}

QExtOsgiConfigurationPtr QExtOsgiConfigurationAdminImpl::getConfiguration(const QString& pid, const QString& location)
{
    checkPID(pid);
    configurationAdminFactory->checkConfigurationPermission();
    return configurationStore->getConfiguration(pid, location);
}

QList<QExtOsgiConfigurationPtr> QExtOsgiConfigurationAdminImpl::listConfigurations(const QString& filter)
{
    QString filterString = filter;
    if (filterString.isEmpty())
    {
        filterString = QString("(%1=*)").arg(QExtOsgiPluginConstants::SERVICE_PID);
    }

    //TODO security
    //try
    //{
    configurationAdminFactory->checkConfigurationPermission();
    //}
    //catch (const SecurityException& e) {
    //  filterString = "(&(" + ConfigurationAdmin.SERVICE_BUNDLELOCATION + "=" + bundle.getLocation() + ")" + filterString + ")";
    //}
    QList<QExtOsgiConfigurationImplPtr> configs = configurationStore->listConfigurations(QExtOsgiLDAPSearchFilter(filterString));
    QList<QExtOsgiConfigurationPtr> result;
    foreach(QExtOsgiConfigurationImplPtr config, configs)
    {
        result.push_back(config);
    }
    return result;
}

void QExtOsgiConfigurationAdminImpl::checkPID(const QString& pid)
{
    if (pid.isEmpty())
    {
        throw QExtInvalidArgumentException("PID cannot be empty");
    }
}
