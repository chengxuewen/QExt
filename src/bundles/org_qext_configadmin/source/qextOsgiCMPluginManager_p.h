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


#ifndef _QEXTOSGICMPLUGINMANAGER_P_H
#define _QEXTOSGICMPLUGINMANAGER_P_H

#include <qextOsgiDictionary.h>
#include <qextOsgiServiceReference.h>

class _PluginTracker;

/**
 * PluginManager tracks and allows customization via ConfigurationPlugin
 */
class QExtOsgiCMPluginManager
{
public:
    QExtOsgiCMPluginManager(QExtOsgiPluginContext* context);
    ~QExtOsgiCMPluginManager();

    void start();
    void stop();

    void modifyConfiguration(const QExtOsgiServiceReference &managedReference, QExtOsgiDictionary &properties);

private:
    QScopedPointer<_PluginTracker> pluginTracker;
};

#endif // _QEXTOSGICMPLUGINMANAGER_P_H
