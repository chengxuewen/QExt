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


#ifndef _QEXTOSGICONFIGURATIONADMINFACTORY_P_H
#define _QEXTOSGICONFIGURATIONADMINFACTORY_P_H

#include <QObject>

#include <qextOsgiPluginEvent.h>
#include <qextOsgiServiceFactory.h>
#include <qextOsgiConfigurationListener.h>

#include "qextOsgiCMEventDispatcher_p.h"
#include "qextOsgiCMPluginManager_p.h"
#include "qextOsgiConfigurationStore_p.h"
#include "qextOsgiManagedServiceTracker_p.h"
#include "qextOsgiManagedServiceFactoryTracker_p.h"

struct QExtOsgiLogService;
class QExtOsgiConfigurationAdminImpl;
class QExtOsgiConfigurationImpl;

/**
 * QExtOsgiConfigurationAdminFactory provides a Configuration Admin ServiceFactory but more significantly
 * launches the whole implementation.
 */
class QExtOsgiConfigurationAdminFactory : public QObject, public QExtOsgiServiceFactory
{
    Q_OBJECT
    Q_INTERFACES(QExtOsgiServiceFactory)

public:
    QExtOsgiConfigurationAdminFactory(QExtOsgiPluginContext* context, QExtOsgiLogService* log);
    ~QExtOsgiConfigurationAdminFactory();

    void start();
    void stop();

    QObject* getService(QSharedPointer<QExtOsgiPlugin> plugin, QExtOsgiServiceRegistration registration);
    void ungetService(QSharedPointer<QExtOsgiPlugin> plugin, QExtOsgiServiceRegistration registration, QObject* service);

    void checkConfigurationPermission();

    QExtOsgiLogService* getLogService() const;

    void dispatchEvent(QExtOsgiConfigurationEvent::Type type, const QString& factoryPid, const QString& pid);

    void notifyConfigurationUpdated(QExtOsgiConfigurationImpl* config, bool isFactory);
    void notifyConfigurationDeleted(QExtOsgiConfigurationImpl* config, bool isFactory);

    void modifyConfiguration(const QExtOsgiServiceReference& reference, QExtOsgiDictionary& properties);

public Q_SLOTS:
    void pluginChanged(const QExtOsgiPluginEvent& event);

private:
    //Permission configurationPermission = new ConfigurationPermission("*", ConfigurationPermission.CONFIGURE); //$NON-NLS-1$
    QExtOsgiCMEventDispatcher eventDispatcher;
    QExtOsgiCMPluginManager pluginManager;
    QExtOsgiLogService* logService;
    QExtOsgiConfigurationStore configurationStore;
    QExtOsgiManagedServiceTracker managedServiceTracker;
    QExtOsgiManagedServiceFactoryTracker managedServiceFactoryTracker;

    QList<QExtOsgiConfigurationAdminImpl*> configAdmins;
};

#endif // _QEXTOSGICONFIGURATIONADMINFACTORY_P_H
