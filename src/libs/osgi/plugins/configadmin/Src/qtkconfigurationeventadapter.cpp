#include "qtkconfigurationeventadapter_p.h"

#include <QTKPluginFramework/Service/Event/QTKEvent>

const QString QTKConfigurationEventAdapter::TOPIC = "org/qtk/service/cm/configurationevent";
const QChar QTKConfigurationEventAdapter::TOPIC_SEPARATOR = '/';

const QString QTKConfigurationEventAdapter::CM_UPDATED = "CM_UPDATED";
const QString QTKConfigurationEventAdapter::CM_DELETED = "CM_DELETED";

const QString QTKConfigurationEventAdapter::CM_FACTORY_PID = "cm.factoryPid";
const QString QTKConfigurationEventAdapter::CM_PID = "cm.pid";
const QString QTKConfigurationEventAdapter::SERVICE = "service";
const QString QTKConfigurationEventAdapter::SERVICE_ID = "service.id";
const QString QTKConfigurationEventAdapter::SERVICE_OBJECTCLASS = "service.objectClass";
const QString QTKConfigurationEventAdapter::SERVICE_PID = "service.pid";


QTKConfigurationEventAdapter::QTKConfigurationEventAdapter(QTKPluginContext* context)
    : context(context), eventAdminTracker(context)
{

}

void QTKConfigurationEventAdapter::start()
{
    eventAdminTracker.open();
    configListenerRegistration = context->registerService<QTKConfigurationListener>(this);
}

void QTKConfigurationEventAdapter::stop()
{
    configListenerRegistration.unregister();
    configListenerRegistration = 0;
    eventAdminTracker.close();
}

void QTKConfigurationEventAdapter::configurationEvent(const QTKConfigurationEvent& event)
{
    QTKEventAdmin* eventAdmin = eventAdminTracker.getService();
    if (eventAdmin == 0)
    {
        return;
    }
    QString typeName;
    switch (event.getType())
    {
    case QTKConfigurationEvent::CM_UPDATED :
        typeName = CM_UPDATED;
        break;
    case QTKConfigurationEvent::CM_DELETED :
        typeName = CM_DELETED;
        break;
    default : // do nothing
        return;
    }
    QString topic = TOPIC + TOPIC_SEPARATOR + typeName;
    QTKServiceReference ref = event.getReference();
    if (!ref)
    {
        throw QTKRuntimeException("QTKConfigurationEvent::getServiceReference() is null");
    }
    QTKDictionary properties;
    properties.insert(CM_PID, event.getPid());
    if (event.getFactoryPid().isNull())
    {
        properties.insert(CM_FACTORY_PID, event.getFactoryPid());
    }
    putServiceReferenceProperties(properties, ref);
    QTKEvent convertedEvent(topic, properties);
    eventAdmin->postEvent(convertedEvent);
}

void QTKConfigurationEventAdapter::putServiceReferenceProperties(QTKDictionary& properties, const QTKServiceReference& ref)
{
    properties.insert(SERVICE, QVariant::fromValue(ref));
    properties.insert(SERVICE_ID, ref.getProperty(QTKPluginConstants::SERVICE_ID));
    QVariant o = ref.getProperty(QTKPluginConstants::SERVICE_PID);
    if (o.canConvert<QString>())
    {
        properties.insert(SERVICE_PID, o);
    }
    QVariant o2 = ref.getProperty(QTKPluginConstants::OBJECT_CLASS);
    if (o.canConvert<QStringList>())
    {
        properties.insert(SERVICE_OBJECTCLASS, o2);
    }
}
