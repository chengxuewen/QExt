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


#ifndef _QEXTOSGICONFIGURATIONADMINIMPL_P_H
#define _QEXTOSGICONFIGURATIONADMINIMPL_P_H

#include <qextOsgiConfigurationAdmin.h>
#include <qextOsgiPlugin.h>

class QExtOsgiConfigurationAdminFactory;
class QExtOsgiConfigurationStore;

/**
 * QExtOsgiConfigurationAdminImpl provides the ConfigurationAdmin service implementation
 */
class QExtOsgiConfigurationAdminImpl : public QObject, public QExtOsgiConfigurationAdmin
{
    Q_OBJECT
    Q_INTERFACES(QExtOsgiConfigurationAdmin)

public:
    QExtOsgiConfigurationAdminImpl(QExtOsgiConfigurationAdminFactory* configurationAdminFactory,
                                   QExtOsgiConfigurationStore* configurationStore,
                                   QSharedPointer<QExtOsgiPlugin> plugin);

    QExtOsgiConfigurationPtr createFactoryConfiguration(const QString& factoryPid);

    QExtOsgiConfigurationPtr createFactoryConfiguration(const QString& factoryPid,
                                                        const QString& location);

    QExtOsgiConfigurationPtr getConfiguration(const QString& pid);

    QExtOsgiConfigurationPtr getConfiguration(const QString& pid, const QString& location);

    QList<QExtOsgiConfigurationPtr> listConfigurations(const QString& filterString = QString());

private:
    QExtOsgiConfigurationAdminFactory* const configurationAdminFactory;
    const QSharedPointer<QExtOsgiPlugin> plugin;
    QExtOsgiConfigurationStore* const configurationStore;

    void checkPID(const QString& pid);
};

#endif // _QEXTOSGICONFIGURATIONADMINIMPL_P_H
