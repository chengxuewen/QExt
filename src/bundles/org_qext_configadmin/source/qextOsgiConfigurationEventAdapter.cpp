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

#include "qextOsgiConfigurationEventAdapter_p.h"

#include <qextOsgiEvent.h>

const QString QExtOsgiConfigurationEventAdapter::TOPIC = "org/commontk/service/cm/ConfigurationEvent";
const QChar QExtOsgiConfigurationEventAdapter::TOPIC_SEPARATOR = '/';

const QString QExtOsgiConfigurationEventAdapter::CM_UPDATED = "CM_UPDATED";
const QString QExtOsgiConfigurationEventAdapter::CM_DELETED = "CM_DELETED";

const QString QExtOsgiConfigurationEventAdapter::CM_FACTORY_PID = "cm.factoryPid";
const QString QExtOsgiConfigurationEventAdapter::CM_PID = "cm.pid";
const QString QExtOsgiConfigurationEventAdapter::SERVICE = "service";
const QString QExtOsgiConfigurationEventAdapter::SERVICE_ID = "service.id";
const QString QExtOsgiConfigurationEventAdapter::SERVICE_OBJECTCLASS = "service.objectClass";
const QString QExtOsgiConfigurationEventAdapter::SERVICE_PID = "service.pid";


QExtOsgiConfigurationEventAdapter::QExtOsgiConfigurationEventAdapter(QExtOsgiPluginContext* context)
    : context(context), eventAdminTracker(context)
{

}

void QExtOsgiConfigurationEventAdapter::start()
{
    eventAdminTracker.open();
    configListenerRegistration = context->registerService<QExtOsgiConfigurationListener>(this);
}

void QExtOsgiConfigurationEventAdapter::stop()
{
    configListenerRegistration.unregister();
    configListenerRegistration = 0;
    eventAdminTracker.close();
}

void QExtOsgiConfigurationEventAdapter::configurationEvent(const QExtOsgiConfigurationEvent& event)
{
    QExtOsgiEventAdmin* eventAdmin = eventAdminTracker.getService();
    if (eventAdmin == 0)
    {
        return;
    }
    QString typeName;
    switch (event.getType())
    {
    case QExtOsgiConfigurationEvent::CM_UPDATED :
        typeName = CM_UPDATED;
        break;
    case QExtOsgiConfigurationEvent::CM_DELETED :
        typeName = CM_DELETED;
        break;
    default : // do nothing
        return;
    }
    QString topic = TOPIC + TOPIC_SEPARATOR + typeName;
    QExtOsgiServiceReference ref = event.getReference();
    if (!ref)
    {
        throw QExtRuntimeException("QExtOsgiConfigurationEvent::getServiceReference() is null");
    }
    QExtOsgiDictionary properties;
    properties.insert(CM_PID, event.getPid());
    if (event.getFactoryPid().isNull())
    {
        properties.insert(CM_FACTORY_PID, event.getFactoryPid());
    }
    putServiceReferenceProperties(properties, ref);
    QExtOsgiEvent convertedEvent(topic, properties);
    eventAdmin->postEvent(convertedEvent);
}

void QExtOsgiConfigurationEventAdapter::putServiceReferenceProperties(QExtOsgiDictionary& properties, const QExtOsgiServiceReference& ref)
{
    properties.insert(SERVICE, QVariant::fromValue(ref));
    properties.insert(SERVICE_ID, ref.getProperty(QExtOsgiPluginConstants::SERVICE_ID));
    QVariant o = ref.getProperty(QExtOsgiPluginConstants::SERVICE_PID);
    if (o.canConvert<QString>())
    {
        properties.insert(SERVICE_PID, o);
    }
    QVariant o2 = ref.getProperty(QExtOsgiPluginConstants::OBJECTCLASS);
    if (o.canConvert<QStringList>())
    {
        properties.insert(SERVICE_OBJECTCLASS, o2);
    }
}
