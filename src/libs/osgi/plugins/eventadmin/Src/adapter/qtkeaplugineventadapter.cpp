#include "qtkeaplugineventadapter_p.h"

#include <QTKPluginFramework/QTKPluginContext>
#include <QTKPluginFramework/Service/Event/QTKEventConstants>
#include <QTKPluginFramework/Service/Event/QTKEvent>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

QTKEAPluginEventAdapter::QTKEAPluginEventAdapter(QTKPluginContext *pContext, QTKEventAdmin *pAdmin)
    : QTKEAAbstractAdapter(pAdmin)
{
    pContext->connectPluginListener(this, SLOT(pluginChanged(QTKPluginEvent)));
}

void QTKEAPluginEventAdapter::destroy(QTKPluginContext *pContext)
{
    Q_UNUSED(pContext)
}

void QTKEAPluginEventAdapter::pluginChanged(const QTKPluginEvent &event)
{
    QTKDictionary properties;
    properties.insert(QTKEventConstants::EVENT, QVariant::fromValue(event));
    properties.insert("plugin.id", QVariant::fromValue<long>(event.getPlugin()->getPluginId()));

    const QString strSymbolicName = event.getPlugin()->getSymbolicName();

    if (!strSymbolicName.isEmpty()) {
        properties.insert(QTKEventConstants::PLUGIN_SYMBOLIC_NAME, strSymbolicName);
    }

    properties.insert("plugin", QVariant::fromValue(event.getPlugin()));

    QString strTopic("org/qtk/PluginEvent/");

    switch (event.getType())
    {
    case QTKPluginEvent::Type_Installed:
    {
        strTopic.append("INSTALLED");
        break;
    }
    case QTKPluginEvent::Type_Started:
    {
        strTopic.append("STARTED");
        break;
    }
    case QTKPluginEvent::Type_Stopped:
    {
        strTopic.append("STOPPED");
        break;
    }
    case QTKPluginEvent::Type_Updated:
    {
        strTopic.append("UPDATED");
        break;
    }
    case QTKPluginEvent::Type_Uninstalled:
    {
        strTopic.append("UNINSTALLED");
        break;
    }
    case QTKPluginEvent::Type_Resolved:
    {
        strTopic.append("RESOLVED");
        break;
    }
    case QTKPluginEvent::Type_Unresolved:
    {
        strTopic.append("UNRESOLVED");
        break;
    }
    default:
        return; // IGNORE EVENT
    };

    try {
        getEventAdmin()->postEvent(QTKEvent(strTopic, properties));
    } catch (const QTKIllegalStateException &) {
        // This is o.k. - indicates that we are stopped.
    }
}
