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


#include "qextOsgiManagedServiceFactoryTracker_p.h"
#include "qextOsgiConfigurationAdminActivator_p.h"
#include "qextOsgiConfigurationAdminFactory_p.h"
#include "qextOsgiConfigurationStore_p.h"
#include "qextOsgiConfigurationImpl_p.h"

#include <qextOsgiConfigurationException.h>
#include <qextOsgiLogService.h>


#include <QRunnable>

QExtOsgiManagedServiceFactoryTracker::QExtOsgiManagedServiceFactoryTracker(QExtOsgiConfigurationAdminFactory* configurationAdminFactory,
                                                                           QExtOsgiConfigurationStore* configurationStore,
                                                                           QExtOsgiPluginContext* context)
    : QExtOsgiServiceTracker<QExtOsgiManagedServiceFactory*>(context)
    , context(context)
    , configurationAdminFactory(configurationAdminFactory)
    , configurationStoreMutex(QMutex::Recursive)
    , configurationStore(configurationStore)
    , queue("QExtOsgiManagedServiceFactory Update Queue")
{

}

QExtOsgiManagedServiceFactory* QExtOsgiManagedServiceFactoryTracker::addingService(const QExtOsgiServiceReference& reference)
{
    QString factoryPid = reference.getProperty(QExtOsgiPluginConstants::SERVICE_PID).toString();
    if (factoryPid.isEmpty())
        return 0;

    QExtOsgiManagedServiceFactory* service = context->getService<QExtOsgiManagedServiceFactory>(reference);
    if (service == 0)
        return 0;

    {
        QMutexLocker lock(&configurationStoreMutex);
        addManagedServiceFactory(reference, factoryPid, service);
    }
    return service;
}

void QExtOsgiManagedServiceFactoryTracker::modifiedService(const QExtOsgiServiceReference& reference,
                                                           QExtOsgiManagedServiceFactory* service)
{
    QString factoryPid = reference.getProperty(QExtOsgiPluginConstants::SERVICE_PID).toString();
    {
        QMutexLocker lock(&configurationStoreMutex);
        if (getManagedServiceFactory(factoryPid) == service)
            return;
        QString previousPid = getPidForManagedServiceFactory(service);
        removeManagedServiceFactory(reference, previousPid);
        addingService(reference);
    }
}

void QExtOsgiManagedServiceFactoryTracker::removedService(const QExtOsgiServiceReference& reference,
                                                          QExtOsgiManagedServiceFactory* service)
{
    Q_UNUSED(service)

    QString factoryPid = reference.getProperty(QExtOsgiPluginConstants::SERVICE_PID).toString();
    {
        QMutexLocker lock(&configurationStoreMutex);
        removeManagedServiceFactory(reference, factoryPid);
    }
    context->ungetService(reference);
}

void QExtOsgiManagedServiceFactoryTracker::notifyDeleted(QExtOsgiConfigurationImpl* config)
{
    config->checkLocked();
    QString factoryPid = config->getFactoryPid(false);
    QExtOsgiServiceReference reference = getManagedServiceFactoryReference(factoryPid);
    if (reference && config->bind(reference.getPlugin()))
    {
        asynchDeleted(getManagedServiceFactory(factoryPid), config->getPid(false));
    }
}

void QExtOsgiManagedServiceFactoryTracker::notifyUpdated(QExtOsgiConfigurationImpl* config)
{
    config->checkLocked();
    QString factoryPid = config->getFactoryPid();
    QExtOsgiServiceReference reference = getManagedServiceFactoryReference(factoryPid);
    if (reference && config->bind(reference.getPlugin()))
    {
        QExtOsgiDictionary properties = config->getProperties();
        configurationAdminFactory->modifyConfiguration(reference, properties);
        asynchUpdated(getManagedServiceFactory(factoryPid), config->getPid(), properties);
    }
}

void QExtOsgiManagedServiceFactoryTracker::addManagedServiceFactory(
    const QExtOsgiServiceReference& reference, const QString& factoryPid,
    QExtOsgiManagedServiceFactory* service)
{
    QList<QExtOsgiConfigurationImplPtr> configs = configurationStore->getFactoryConfigurations(factoryPid);
    QExtOsgiConfigurationImplLocker lock(configs);

    if (trackManagedServiceFactory(factoryPid, reference, service))
    {
        foreach (QExtOsgiConfigurationImplPtr config, configs)
        {
            if (config->isDeleted())
            {
                // ignore this config
            }
            else if (config->bind(reference.getPlugin()))
            {
                QExtOsgiDictionary properties = config->getProperties();
                configurationAdminFactory->modifyConfiguration(reference, properties);
                asynchUpdated(service, config->getPid(), properties);
            }
            else
            {
                QEXT_OSGI_WARN(configurationAdminFactory->getLogService())
                    << "Configuration for " << QExtOsgiPluginConstants::SERVICE_PID << "="
                    << config->getPid() << " could not be bound to "
                    << reference.getPlugin()->getLocation();
            }
        }
    }
}

void QExtOsgiManagedServiceFactoryTracker::removeManagedServiceFactory(
    const QExtOsgiServiceReference& reference, const QString& factoryPid)
{
    QList<QExtOsgiConfigurationImplPtr> configs = configurationStore->getFactoryConfigurations(factoryPid);
    QExtOsgiConfigurationImplLocker lock(configs);
    untrackManagedServiceFactory(factoryPid, reference);
}

bool QExtOsgiManagedServiceFactoryTracker::trackManagedServiceFactory(const QString& factoryPid,
                                                                      const QExtOsgiServiceReference& reference,
                                                                      QExtOsgiManagedServiceFactory* service)
{
    QMutexLocker lock(&managedServiceFactoryMutex);
    if (managedServiceFactoryReferences.contains(factoryPid))
    {
        QEXT_OSGI_WARN(configurationAdminFactory->getLogService())
            << "QExtOsgiManagedServiceFactory already registered for "
            << QExtOsgiPluginConstants::SERVICE_PID << "=" << factoryPid;
        return false;
    }
    managedServiceFactoryReferences.insert(factoryPid, reference);
    managedServiceFactories.insert(factoryPid, service);
    return true;
}

void QExtOsgiManagedServiceFactoryTracker::untrackManagedServiceFactory(const QString& factoryPid,
                                                                        const QExtOsgiServiceReference& reference)
{
    Q_UNUSED(reference)

    QMutexLocker lock(&managedServiceFactoryMutex);
    managedServiceFactoryReferences.remove(factoryPid);
    managedServiceFactories.remove(factoryPid);
}

QExtOsgiManagedServiceFactory* QExtOsgiManagedServiceFactoryTracker::getManagedServiceFactory(const QString& factoryPid) const
{
    QMutexLocker lock(&managedServiceFactoryMutex);
    return managedServiceFactories.value(factoryPid);
}

QExtOsgiServiceReference QExtOsgiManagedServiceFactoryTracker::getManagedServiceFactoryReference(const QString& factoryPid) const
{
    QMutexLocker lock(&managedServiceFactoryMutex);
    return managedServiceFactoryReferences.value(factoryPid);
}

QString QExtOsgiManagedServiceFactoryTracker::getPidForManagedServiceFactory(QExtOsgiManagedServiceFactory* service) const
{
    QMutexLocker lock(&managedServiceFactoryMutex);
    QHash<QString, QExtOsgiManagedServiceFactory*>::ConstIterator end = managedServiceFactories.end();
    QHash<QString, QExtOsgiManagedServiceFactory*>::ConstIterator it;
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

    _AsynchDeleteRunnable(QExtOsgiManagedServiceFactory* service, const QString& pid,
                          QExtOsgiLogService* log)
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
            QEXT_OSGI_ERROR_EXC(log, e);
        }
    }

private:

    QExtOsgiManagedServiceFactory* const service;
    const QString pid;
    QExtOsgiLogService* const log;
};

void QExtOsgiManagedServiceFactoryTracker::asynchDeleted(QExtOsgiManagedServiceFactory* service, const QString& pid)
{
    queue.put(new _AsynchDeleteRunnable(service, pid, configurationAdminFactory->getLogService()));
}

class _AsynchFactoryUpdateRunnable : public QRunnable
{
public:

    _AsynchFactoryUpdateRunnable(QExtOsgiManagedServiceFactory* service, const QString& pid,
                                 const QExtOsgiDictionary& properties, QExtOsgiLogService* log)
        : service(service), pid(pid), properties(properties), log(log)
    {

    }

    void run()
    {
        try
        {
            service->updated(pid, properties);
        }
        catch (const QExtOsgiConfigurationException* e)
        {
            // we might consider doing more for ConfigurationExceptions
            QEXT_OSGI_ERROR_EXC(log, e);
        }
        catch (const std::exception* e)
        {
            QEXT_OSGI_ERROR_EXC(log, e);
        }
    }

private:

    QExtOsgiManagedServiceFactory* const service;
    const QString pid;
    const QExtOsgiDictionary properties;
    QExtOsgiLogService* const log;
};

void QExtOsgiManagedServiceFactoryTracker::asynchUpdated(QExtOsgiManagedServiceFactory* service, const QString& pid,
                                                         const QExtOsgiDictionary& properties)
{
    queue.put(new _AsynchFactoryUpdateRunnable(service, pid, properties, configurationAdminFactory->getLogService()));
}
