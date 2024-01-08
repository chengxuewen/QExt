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


#include "qextOsgiConfigurationAdminActivator_p.h"
#include "qextOsgiConfigurationAdminFactory_p.h"
#include "qextOsgiConfigurationEventAdapter_p.h"

#include <qextOsgiServiceTracker.h>
#include <qextOsgiConfigurationAdmin.h>
#include <qextOsgiConfigurationListener.h>

#include <QtPlugin>


QExtOsgiConfigurationAdminActivator::QExtOsgiConfigurationAdminActivator()
    : logTracker(0), factory(0), eventAdapter(0)
{
}

QExtOsgiConfigurationAdminActivator::~QExtOsgiConfigurationAdminActivator()
{
    delete logTracker;
    delete factory;
}

void QExtOsgiConfigurationAdminActivator::start(QExtOsgiPluginContext* context)
{
    logFileFallback.open(stdout, QIODevice::WriteOnly);
    logTracker = new QExtOsgiCMLogTracker(context, &logFileFallback);
    logTracker->open();
    eventAdapter = new QExtOsgiConfigurationEventAdapter(context);
    eventAdapter->start();
    factory = new QExtOsgiConfigurationAdminFactory(context, logTracker);
    factory->start();
    context->connectPluginListener(factory, SLOT(pluginChanged(QExtOsgiPluginEvent)));
    registration = context->registerService<QExtOsgiConfigurationAdmin>(factory);
}

void QExtOsgiConfigurationAdminActivator::stop(QExtOsgiPluginContext* context)
{
    Q_UNUSED(context)

    if (registration)
    {
        registration.unregister();
    }

    factory->stop();
    delete factory;
    factory = 0;

    eventAdapter->stop();
    delete eventAdapter;
    eventAdapter = 0;

    logTracker->close();
    delete logTracker;
    logTracker = 0;

    logFileFallback.close();
}

#if (QT_VERSION < QT_VERSION_CHECK(5,0,0))
Q_EXPORT_PLUGIN2(org_commontk_configadmin, QExtOsgiConfigurationAdminActivator)
#endif
