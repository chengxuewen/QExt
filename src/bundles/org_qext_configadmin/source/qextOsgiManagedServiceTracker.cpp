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


#include "qextOsgiManagedServiceTracker_p.h"
#include "qextOsgiConfigurationImpl_p.h"
#include "qextOsgiConfigurationAdminFactory_p.h"

#include <qextOsgiConfigurationException.h>
#include <qextOsgiLogService.h>

#include <QRunnable>

QExtOsgiManagedServiceTracker::QExtOsgiManagedServiceTracker(QExtOsgiConfigurationAdminFactory* configurationAdminFactory,
                                                             QExtOsgiConfigurationStore* configurationStore,
                                                             QExtOsgiPluginContext* context)
    : QExtOsgiServiceTracker<QExtOsgiManagedService*>(context)
    , context(context)
    , configurationAdminFactory(configurationAdminFactory)
    , configurationStoreMutex(QMutex::Recursive)
    , configurationStore(configurationStore)
    , queue("QExtOsgiManagedService Update Queue")
{

}

QExtOsgiManagedService* QExtOsgiManagedServiceTracker::addingService(const QExtOsgiServiceReference& reference)
{
    QString pid = reference.getProperty(QExtOsgiPluginConstants::SERVICE_PID).toString();
    if (pid.isEmpty())
        return 0;

    QExtOsgiManagedService* service = context->getService<QExtOsgiManagedService>(reference);
    if (service == 0)
        return 0;

    {
        QMutexLocker lock(&configurationStoreMutex);
        addManagedService(reference, pid, service);
    }
    return service;
}

void QExtOsgiManagedServiceTracker::modifiedService(const QExtOsgiServiceReference& reference, QExtOsgiManagedService* service)
{
    QString pid = reference.getProperty(QExtOsgiPluginConstants::SERVICE_PID).toString();
    {
        QMutexLocker lock(&configurationStoreMutex);
        if (getManagedService(pid) == service)
            return;
        QString previousPid = getPidForManagedService(service);
        removeManagedService(reference, previousPid);
        addingService(reference);
    }
}

void QExtOsgiManagedServiceTracker::removedService(const QExtOsgiServiceReference& reference, QExtOsgiManagedService* service)
{
    Q_UNUSED(service)

    QString pid = reference.getProperty(QExtOsgiPluginConstants::SERVICE_PID).toString();
    {
        QMutexLocker lock(&configurationStoreMutex);
        removeManagedService(reference, pid);
    }
    context->ungetService(reference);
}

void QExtOsgiManagedServiceTracker::notifyDeleted(QExtOsgiConfigurationImpl* config)
{
    config->checkLocked();
    QString pid = config->getPid(false);
    QExtOsgiServiceReference reference = getManagedServiceReference(pid);
    if (reference && config->bind(reference.getPlugin()))
        asynchUpdated(getManagedService(pid), QExtOsgiDictionary());
}

void QExtOsgiManagedServiceTracker::notifyUpdated(QExtOsgiConfigurationImpl* config) {
    config->checkLocked();
    QString pid = config->getPid();
    QExtOsgiServiceReference reference = getManagedServiceReference(pid);
    if (reference && config->bind(reference.getPlugin()))
    {
        QExtOsgiDictionary properties = config->getProperties();
        configurationAdminFactory->modifyConfiguration(reference, properties);
        asynchUpdated(getManagedService(pid), properties);
    }
}

void QExtOsgiManagedServiceTracker::addManagedService(const QExtOsgiServiceReference& reference,
                                                      const QString& pid,
                                                      QExtOsgiManagedService* service)
{
    QExtOsgiConfigurationImplPtr config = configurationStore->findConfiguration(pid);
    if (config.isNull() && trackManagedService(pid, reference, service))
    {
        asynchUpdated(service, QExtOsgiDictionary());
    }
    else
    {
        QExtOsgiConfigurationImplLocker lock(config.data());
        if (trackManagedService(pid, reference, service))
        {
            if (!config->getFactoryPid().isEmpty())
            {
                QEXT_OSGI_WARN(configurationAdminFactory->getLogService())
                    << "Configuration for " << QExtOsgiPluginConstants::SERVICE_PID << "="
                    << pid << " should only be used by a QExtOsgiManagedServiceFactory";
            }
            else if (config->isDeleted())
            {
                asynchUpdated(service, QExtOsgiDictionary());
            }
            else if (config->bind(reference.getPlugin()))
            {
                QExtOsgiDictionary properties = config->getProperties();
                configurationAdminFactory->modifyConfiguration(reference, properties);
                asynchUpdated(service, properties);
            }
            else
            {
                QEXT_OSGI_WARN(configurationAdminFactory->getLogService())
                    << "Configuration for " << QExtOsgiPluginConstants::SERVICE_PID << "="
                    << pid << " could not be bound to " << reference.getPlugin()->getLocation();
            }
        }
    }
}

void QExtOsgiManagedServiceTracker::removeManagedService(const QExtOsgiServiceReference& reference,
                                                         const QString& pid)
{
    QExtOsgiConfigurationImplPtr config = configurationStore->findConfiguration(pid);
    if (config.isNull())
    {
        untrackManagedService(pid, reference);
    }
    else
    {
        QExtOsgiConfigurationImplLocker lock(config.data());
        untrackManagedService(pid, reference);
    }
}

bool QExtOsgiManagedServiceTracker::trackManagedService(const QString& pid, const QExtOsgiServiceReference& reference,
                                                        QExtOsgiManagedService* service)
{
    QMutexLocker lock(&managedServiceMutex);
    if (managedServiceReferences.contains(pid))
    {
        QEXT_OSGI_WARN(configurationAdminFactory->getLogService())
            << "QExtOsgiManagedService already registered for " << QExtOsgiPluginConstants::SERVICE_PID
            << "=" << pid;
        return false;
    }
    managedServiceReferences.insert(pid, reference);
    managedServices.insert(pid, service);
    return true;
}

void QExtOsgiManagedServiceTracker::untrackManagedService(const QString& pid, const QExtOsgiServiceReference& reference)
{
    Q_UNUSED(reference)

    QMutexLocker lock(&managedServiceMutex);
    managedServiceReferences.remove(pid);
    managedServices.remove(pid);
}

QExtOsgiManagedService* QExtOsgiManagedServiceTracker::getManagedService(const QString& pid) const
{
    QMutexLocker lock(&managedServiceMutex);
    return managedServices.value(pid);
}

QExtOsgiServiceReference QExtOsgiManagedServiceTracker::getManagedServiceReference(const QString& pid) const
{
    QMutexLocker lock(&managedServiceMutex);
    return managedServiceReferences.value(pid);
}

QString QExtOsgiManagedServiceTracker::getPidForManagedService(QExtOsgiManagedService* service) const
{
    QMutexLocker lock(&managedServiceMutex);
    QHash<QString, QExtOsgiManagedService*>::ConstIterator end = managedServices.end();
    QHash<QString, QExtOsgiManagedService*>::ConstIterator it;
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

    _AsynchUpdateRunnable(QExtOsgiManagedService* service,
                          const QExtOsgiDictionary& properties,
                          QExtOsgiLogService* log)
        : service(service), properties(properties), log(log)
    {
    }

    void run()
    {
        try
        {
            service->updated(properties);
        }
        catch (const QExtOsgiConfigurationException* e)
        {
            // we might consider doing more for QExtOsgiConfigurationExceptions
            QEXT_OSGI_ERROR_EXC(log, e);
        }
        catch (const std::exception* e)
        {
            QEXT_OSGI_ERROR_EXC(log, e);
        }
    }

private:

    QExtOsgiManagedService* service;
    const QExtOsgiDictionary properties;
    QExtOsgiLogService * const log;
};

void QExtOsgiManagedServiceTracker::asynchUpdated(QExtOsgiManagedService* service, const QExtOsgiDictionary& properties)
{
    queue.put(new _AsynchUpdateRunnable(service, properties, configurationAdminFactory->getLogService()));
}
