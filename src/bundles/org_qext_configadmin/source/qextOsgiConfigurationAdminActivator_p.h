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


#ifndef _QEXTOSGICONFIGURATIONADMINACTIVATOR_P_H
#define _QEXTOSGICONFIGURATIONADMINACTIVATOR_P_H

#include <qextOsgiPluginActivator.h>
#include "qextOsgiCMLogTracker_p.h"

class QExtOsgiConfigurationAdminFactory;
class QExtOsgiConfigurationEventAdapter;

/**
 * The QExtOsgiConfigurationAdminActivator starts the QExtOsgiConfigurationAdminFactory but also handles passing in the Service
 * Registration needed by Asynch threads. Asynch threads are controlled by the QExtOsgiConfigurationAdminFactory
 * start and stop. It requires some care to handle pending events as the service is registered before
 * activating the threads. (see QExtOsgiConfigurationAdminEventDispatcher)
 */
class QExtOsgiConfigurationAdminActivator : public QObject, public QExtOsgiPluginActivator
{
    Q_OBJECT
    Q_INTERFACES(QExtOsgiPluginActivator)
#ifdef HAVE_QT5
    Q_PLUGIN_METADATA(IID "org_commontk_configadmin")
#endif

public:

    QExtOsgiConfigurationAdminActivator();
    ~QExtOsgiConfigurationAdminActivator();

    void start(QExtOsgiPluginContext* context);
    void stop(QExtOsgiPluginContext* context);

private:

    QFile logFileFallback;

    QExtOsgiCMLogTracker* logTracker;
    QExtOsgiServiceRegistration registration;
    QExtOsgiConfigurationAdminFactory* factory;
    QExtOsgiConfigurationEventAdapter* eventAdapter;

}; // QExtOsgiConfigurationAdminActivator

#endif // _QEXTOSGICONFIGURATIONADMINACTIVATOR_P_H
