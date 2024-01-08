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


#ifndef _QEXTOSGICONFIGURATIONSTORE_P_H
#define _QEXTOSGICONFIGURATIONSTORE_P_H

#include <qextOsgiLDAPSearchFilter.h>

#include "qextOsgiConfigurationImpl_p.h"

#include <QSharedPointer>
#include <QHash>
#include <QDir>
#include <QMutex>

class QExtOsgiConfigurationImpl;
class QExtOsgiConfigurationAdminFactory;
class QExtOsgiPluginContext;
class QExtOsgiPlugin;

/**
 * QExtOsgiConfigurationStore manages all active configurations along with persistence. The current
 * implementation uses a filestore and serialization of the configuration dictionaries to files
 * identified by their pid. Persistence details are in the constructor, saveConfiguration, and
 * deleteConfiguration and can be factored out separately if required.
 */
class QExtOsgiConfigurationStore
{
public:
    QExtOsgiConfigurationStore(QExtOsgiConfigurationAdminFactory* configurationAdminFactory,
                               QExtOsgiPluginContext* context);

    void saveConfiguration(const QString& pid, QExtOsgiConfigurationImpl* config);
    void removeConfiguration(const QString& pid);

    QExtOsgiConfigurationImplPtr getConfiguration(const QString& pid, const QString& location);

    QExtOsgiConfigurationImplPtr createFactoryConfiguration(const QString& factoryPid, const QString& location);

    QExtOsgiConfigurationImplPtr findConfiguration(const QString& pid);

    QList<QExtOsgiConfigurationImplPtr> getFactoryConfigurations(const QString& factoryPid);
    QList<QExtOsgiConfigurationImplPtr> listConfigurations(const QExtOsgiLDAPSearchFilter& filter);

    void unbindConfigurations(QSharedPointer<QExtOsgiPlugin> plugin);

private:
    QMutex mutex;
    QExtOsgiConfigurationAdminFactory* configurationAdminFactory;
    static const QString STORE_DIR; // = "store"
    static const QString PID_EXT; // = ".pid"
    QHash<QString, QExtOsgiConfigurationImplPtr> configurations;
    int createdPidCount;
    QDir store;

    void writeConfigurationFile(QFile& configFile,
                                const QExtOsgiDictionary& configProperties);
    void deleteConfigurationFile(QFile& configFile);

};

#endif // _QEXTOSGICONFIGURATIONSTORE_P_H
