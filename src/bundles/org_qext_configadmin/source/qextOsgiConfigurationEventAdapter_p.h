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

#ifndef _QEXTOSGICONFIGURATIONEVENTADAPTER_P_H
#define _QEXTOSGICONFIGURATIONEVENTADAPTER_P_H

#include <qextOsgiServiceTracker.h>
#include <qextOsgiConfigurationListener.h>
#include <qextOsgiEventAdmin.h>

#include <QObject>


class QExtOsgiConfigurationEventAdapter : public QObject, public QExtOsgiConfigurationListener
{
    Q_OBJECT
    Q_INTERFACES(QExtOsgiConfigurationListener)

public:
    // constants for Event topic substring
    static const QString TOPIC; // = "org/commontk/service/cm/ConfigurationEvent"
    static const QChar TOPIC_SEPARATOR; // = '/'
    // constants for Event types
    static const QString CM_UPDATED; // = "CM_UPDATED"
    static const QString CM_DELETED; // = "CM_DELETED"
    // constants for Event properties
    static const QString CM_FACTORY_PID; // = "cm.factoryPid"
    static const QString CM_PID; // = "cm.pid"
    static const QString SERVICE; // = "service"
    static const QString SERVICE_ID; // = "service.id"
    static const QString SERVICE_OBJECTCLASS; // = "service.objectClass"
    static const QString SERVICE_PID; // = "service.pid"

private:
    QExtOsgiPluginContext* const context;
    QExtOsgiServiceRegistration configListenerRegistration;
    QExtOsgiServiceTracker<QExtOsgiEventAdmin*> eventAdminTracker;

public:
    QExtOsgiConfigurationEventAdapter(QExtOsgiPluginContext* context);

    void start();
    void stop();

    void configurationEvent(const QExtOsgiConfigurationEvent& event);

    void putServiceReferenceProperties(QExtOsgiDictionary& properties, const QExtOsgiServiceReference& ref);
};

#endif // _QEXTOSGICONFIGURATIONEVENTADAPTER_P_H
