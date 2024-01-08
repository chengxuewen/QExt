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


#ifndef _QEXTOSGIMANAGEDSERVICEFACTORYTRACKER_P_H
#define _QEXTOSGIMANAGEDSERVICEFACTORYTRACKER_P_H

#include <qextOsgiServiceTracker.h>
#include <qextOsgiManagedServiceFactory.h>

#include "qextOsgiCMSerializedTaskQueue_p.h"

class QExtOsgiConfigurationAdminFactory;
class QExtOsgiConfigurationStore;
class QExtOsgiConfigurationImpl;

/**
 * QExtOsgiManagedServiceFactoryTracker tracks... ManagedServiceFactory(s) and notifies them about related configuration changes
 */
class QExtOsgiManagedServiceFactoryTracker : public QExtOsgiServiceTracker<QExtOsgiManagedServiceFactory*>
{

public:

    QExtOsgiManagedServiceFactoryTracker(QExtOsgiConfigurationAdminFactory* configurationAdminFactory,
                                         QExtOsgiConfigurationStore* configurationStore,
                                         QExtOsgiPluginContext* context);

    QExtOsgiManagedServiceFactory* addingService(const QExtOsgiServiceReference& reference);
    void modifiedService(const QExtOsgiServiceReference& reference, QExtOsgiManagedServiceFactory* service);
    void removedService(const QExtOsgiServiceReference& reference, QExtOsgiManagedServiceFactory* service);

    void notifyDeleted(QExtOsgiConfigurationImpl* config);
    void notifyUpdated(QExtOsgiConfigurationImpl* config);

private:

    QExtOsgiPluginContext* context;
    QExtOsgiConfigurationAdminFactory* configurationAdminFactory;
    QMutex configurationStoreMutex;
    QExtOsgiConfigurationStore* configurationStore;

    // managedServiceFactoryMutex guards both managedServiceFactories and managedServiceFactoryReferences
    mutable QMutex managedServiceFactoryMutex;
    QHash<QString, QExtOsgiManagedServiceFactory*> managedServiceFactories;
    QHash<QString, QExtOsgiServiceReference> managedServiceFactoryReferences;

    QExtOsgiCMSerializedTaskQueue queue;

    void addManagedServiceFactory(const QExtOsgiServiceReference& reference,
                                  const QString& factoryPid,
                                  QExtOsgiManagedServiceFactory* service);

    void removeManagedServiceFactory(const QExtOsgiServiceReference& reference,
                                     const QString& factoryPid);

    bool trackManagedServiceFactory(const QString& factoryPid,
                                    const QExtOsgiServiceReference& reference,
                                    QExtOsgiManagedServiceFactory* service);

    void untrackManagedServiceFactory(const QString& factoryPid,
                                      const QExtOsgiServiceReference& reference);

    QExtOsgiManagedServiceFactory* getManagedServiceFactory(const QString& factoryPid) const;

    QExtOsgiServiceReference getManagedServiceFactoryReference(const QString& factoryPid) const;

    QString getPidForManagedServiceFactory(QExtOsgiManagedServiceFactory* service) const;

    void asynchDeleted(QExtOsgiManagedServiceFactory* service, const QString& pid);

    void asynchUpdated(QExtOsgiManagedServiceFactory* service, const QString& pid,
                       const QExtOsgiDictionary& properties);
};

#endif // _QEXTOSGIMANAGEDSERVICEFACTORYTRACKER_P_H
