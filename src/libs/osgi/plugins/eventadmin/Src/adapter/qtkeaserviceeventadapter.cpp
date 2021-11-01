#include "qtkeaserviceeventadapter_p.h"

#include <QTKPluginFramework/QTKPluginContext>
#include <QTKPluginFramework/QTKPluginConstants>
#include <QTKPluginFramework/QTKServiceEvent>
#include <QTKPluginFramework/Service/Event/QTKEventConstants>


QTKEAServiceEventAdapter::QTKEAServiceEventAdapter(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKPluginContext *pContext,
                                                   QTK_PLUGINFRAMEWORK_NAMESPACE::QTKEventAdmin *pAdmin)
    : QTKEAAbstractAdapter(pAdmin)
{
    pContext->connectServiceListener(this, "serviceChanged");
}

void QTKEAServiceEventAdapter::destroy(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKPluginContext *pContext)
{
    pContext->disconnectServiceListener(this, "serviceChanged");
}

void QTKEAServiceEventAdapter::serviceChanged(const QTKServiceEvent &event)
{
    QTKDictionary properties;

    properties.insert(QTKEventConstants::EVENT, QVariant::fromValue(event));
    properties.insert(QTKEventConstants::SERVICE, QVariant::fromValue(event.getServiceReference()));

    QVariant id = event.getServiceReference().getProperty(QTKEventConstants::SERVICE_ID);
    if (id.isValid()) {
        properties.insert(QTKEventConstants::SERVICE_ID, id);
    }

    QVariant pid = event.getServiceReference().getProperty(QTKEventConstants::SERVICE_PID);
    if (pid.isValid()) {
        properties.insert(QTKEventConstants::SERVICE_PID, pid);
    }

    QVariant objectClass = event.getServiceReference().getProperty(QTKPluginConstants::OBJECT_CLASS);
    if (objectClass.isValid()) {
        properties.insert(QTKEventConstants::SERVICE_OBJECT_CLASS, objectClass);
    }

    QString strTopic("org/qtk/serviceevent/");
    switch (event.getType())
    {
    case QTKServiceEvent::Type_Registered:
    {
        strTopic.append("Type_Registered");
        break;
    }
    case QTKServiceEvent::Type_Modified:
    {
        strTopic.append("Type_Modifiedified");
        break;
    }
    case QTKServiceEvent::Type_Unregistering:
    {
        strTopic.append("Type_Unregistering");
        break;
    }
    default:
        return; // IGNORE
    }

    try {
        getEventAdmin()->postEvent(QTKEvent(strTopic, properties));
    } catch(const QTKIllegalStateException &) {
        // This is o.k. - indicates that we are stopped.
    }
}
