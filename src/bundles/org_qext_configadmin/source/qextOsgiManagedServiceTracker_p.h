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


#ifndef _QEXTOSGIMANAGEDSERVICETRACKER_P_H
#define _QEXTOSGIMANAGEDSERVICETRACKER_P_H

#include <qextOsgiServiceTracker.h>
#include <qextOsgiManagedService.h>

#include "qextOsgiCMSerializedTaskQueue_p.h"

class QExtOsgiConfigurationAdminFactory;
class QExtOsgiConfigurationStore;
class QExtOsgiConfigurationImpl;

/**
 * QExtOsgiManagedServiceTracker tracks... ManagedServices and notifies them about related configuration changes
 */
class QExtOsgiManagedServiceTracker : public QExtOsgiServiceTracker<QExtOsgiManagedService*>
{

public:

    QExtOsgiManagedServiceTracker(QExtOsgiConfigurationAdminFactory* configurationAdminFactory,
                                  QExtOsgiConfigurationStore* configurationStore,
                                  QExtOsgiPluginContext* context);

    QExtOsgiManagedService* addingService(const QExtOsgiServiceReference& reference);
    void modifiedService(const QExtOsgiServiceReference& reference, QExtOsgiManagedService* service);
    void removedService(const QExtOsgiServiceReference& reference, QExtOsgiManagedService* service);

    void notifyDeleted(QExtOsgiConfigurationImpl* config);
    void notifyUpdated(QExtOsgiConfigurationImpl* config);

private:

    QExtOsgiPluginContext* context;
    QExtOsgiConfigurationAdminFactory* configurationAdminFactory;
    QMutex configurationStoreMutex;
    QExtOsgiConfigurationStore* configurationStore;

    // managedServiceMutex guards both managedServices and managedServiceReferences
    mutable QMutex managedServiceMutex;
    QHash<QString, QExtOsgiManagedService*> managedServices;
    QHash<QString, QExtOsgiServiceReference> managedServiceReferences;

    QExtOsgiCMSerializedTaskQueue queue;

    void addManagedService(const QExtOsgiServiceReference& reference, const QString& pid,
                           QExtOsgiManagedService* service);

    void removeManagedService(const QExtOsgiServiceReference& reference, const QString& pid);

    bool trackManagedService(const QString& pid, const QExtOsgiServiceReference& reference,
                             QExtOsgiManagedService* service);

    void untrackManagedService(const QString& pid, const QExtOsgiServiceReference& reference);

    QExtOsgiManagedService* getManagedService(const QString& pid) const;

    QExtOsgiServiceReference getManagedServiceReference(const QString& pid) const;

    QString getPidForManagedService(QExtOsgiManagedService* service) const;

    void asynchUpdated(QExtOsgiManagedService* service, const QExtOsgiDictionary& properties);
};

#endif // _QEXTOSGIMANAGEDSERVICETRACKER_P_H
