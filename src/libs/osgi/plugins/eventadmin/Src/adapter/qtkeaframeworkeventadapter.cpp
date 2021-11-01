#include "qtkeaframeworkeventadapter_p.h"

#include <QTKPluginFramework/QTKPluginContext>
#include <QTKPluginFramework/Service/Event/QTKEventConstants>

QTKEAFrameworkEventAdapter::QTKEAFrameworkEventAdapter(QTKPluginContext* pContext, QTKEventAdmin* pAdmin)
    : QTKEAAbstractAdapter(pAdmin)
{
    pContext->connectFrameworkListener(this, SLOT(frameworkEvent(QTKPluginFrameworkEvent)));
}

void QTKEAFrameworkEventAdapter::destroy(QTKPluginContext* pContext)
{
    Q_UNUSED(pContext)
}

void QTKEAFrameworkEventAdapter::frameworkEvent(const QTKPluginFrameworkEvent& event)
{
    QTKDictionary properties;

    properties.insert(QTKEventConstants::EVENT, QVariant::fromValue(event));

    QSharedPointer<QTKPlugin> plugin = event.getPlugin();

    if (plugin)
    {
        properties.insert("plugin.id", QVariant::fromValue<long>(plugin->getPluginId()));

        const QString symbolicName = plugin->getSymbolicName();

        if (!symbolicName.isEmpty())
        {
            properties.insert(QTKEventConstants::PLUGIN_SYMBOLIC_NAME,
                              symbolicName);
        }

        properties.insert("plugin", QVariant::fromValue(plugin));
    }

    const QString message = event.getErrorString();

    if (!message.isEmpty())
    {
        //    properties.put(EventConstants.EXCEPTION_CLASS,
        //                   thrown.getClass().getName());

        //    final String message = thrown.getMessage();

        properties.insert(QTKEventConstants::EXCEPTION_MESSAGE,
                          message);

        //properties.put(EventConstants.EXCEPTION, thrown);
    }

    QString topic = "org/qtk/pluginframeworkevent/";

    switch (event.getType())
    {
    case QTKPluginFrameworkEvent::Type_FrameworkStarted:
        topic.append("STARTED");
        break;
    case QTKPluginFrameworkEvent::Type_PluginError:
        topic.append("ERROR");
        break;
        //  case QTKPluginFrameworkEvent::STARTLEVEL_CHANGED:
        //    topic.append("STARTLEVEL_CHANGED");
        //    break;
    case QTKPluginFrameworkEvent::Type_PluginWarning:
        topic.append("WARNING");
        break;
    case QTKPluginFrameworkEvent::Type_PluginInfo:
        topic.append("INFO");
        break;
    default:
        return; // IGNORE EVENT
    }

    try
    {
        getEventAdmin()->postEvent(QTKEvent(topic, properties));
    }
    catch(const QTKIllegalStateException& )
    {
        // This is o.k. - indicates that we are stopped.
    }
}
