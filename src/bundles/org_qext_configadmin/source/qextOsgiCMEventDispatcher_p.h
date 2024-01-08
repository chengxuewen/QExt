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


#ifndef _QEXTOSGICMEVENTDISPATCHER_P_H
#define _QEXTOSGICMEVENTDISPATCHER_P_H

#include "qextOsgiCMSerializedTaskQueue_p.h"

#include <qextOsgiServiceTracker.h>
#include <qextOsgiConfigurationEvent.h>

struct QExtOsgiConfigurationListener;
struct QExtOsgiLogService;

/**
 * EventDispatcher is responsible for delivering Configuration Events to ConfigurationListeners.
 * The originating ConfigAdmin ServiceReference is needed when delivering events. This reference
 * is made available by the service factory before returning the service object.
 */
class QExtOsgiCMEventDispatcher
{

public:

    QExtOsgiCMEventDispatcher(QExtOsgiPluginContext *context, QExtOsgiLogService *log);

    void start();
    void stop();

    void setServiceReference(const QExtOsgiServiceReference& reference);

    void dispatchEvent(QExtOsgiConfigurationEvent::Type type, const QString &factoryPid, const QString &pid);

private:

    QMutex mutex;
    QExtOsgiServiceTracker<QExtOsgiConfigurationListener*> tracker;
    QExtOsgiCMSerializedTaskQueue queue;
    /** @GuardedBy mutex */
    QExtOsgiServiceReference configAdminReference;
    QExtOsgiLogService * const log;

    QExtOsgiConfigurationEvent createConfigurationEvent(QExtOsgiConfigurationEvent::Type type,
                                                        const QString &factoryPid, const QString &pid);
};

#endif // _QEXTOSGICMEVENTDISPATCHER_P_H
