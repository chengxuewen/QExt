#include "qtkealogeventadapter_p.h"

#include <QTKPluginFramework/QTKPluginContext>
#include <QTKPluginFramework/QTKPluginConstants>
#include <QTKPluginFramework/Service/Event/QTKEventConstants>
#include <QTKPluginFramework/Service/Log/QTKLogService>

QTK_CORE_USE_NAMESPACE
QTK_PLUGINFRAMEWORK_USE_NAMESPACE

/**
 * @brief QTKLogListenerImpl::QTKLogListenerImpl
 * @param pAdapter
 */
QTKLogListenerImpl::QTKLogListenerImpl(QTKEALogEventAdapter *pAdapter)
    : m_pAdapter(pAdapter)
{

}

void QTKLogListenerImpl::logged(QTKLogEntryPtr entry)
{
    // This is where the assembly as specified in 133.6.6 OSGi R4
    // compendium is taking place (i.e., the log entry is adapted to
    // an event and posted via the QTKEventAdmin)

    QTKDictionary properties;

    QSharedPointer<QTKPlugin> pPlugin = entry->getPlugin();
    if (pPlugin) {
        properties.insert("plugin.id", QVariant::fromValue<long>(pPlugin->getPluginId()));
        const QString strSymbolicName = pPlugin->getSymbolicName();
        if (!strSymbolicName.isEmpty()) {
            properties.insert(QTKEventConstants::PLUGIN_SYMBOLIC_NAME, strSymbolicName);
        }
        properties.insert("plugin", QVariant::fromValue(pPlugin));
    }
    properties.insert("log.level", entry->getLevel());
    properties.insert(QTKEventConstants::MESSAGE, entry->getMessage());
    properties.insert(QTKEventConstants::TIME_STAMP, entry->getTime());
    properties.insert("log.entry", QVariant::fromValue(entry));

    const std::exception *pException = entry->getException();
    if (pException) {
        const QString strMessage(pException->what());
        if (!strMessage.isEmpty()) {
            properties.insert(QTKEventConstants::EXCEPTION_MESSAGE, strMessage);
        }
        properties.insert(QTKEventConstants::EXCEPTION, pException);
    }

    QTKServiceReference service = entry->getServiceReference();
    if (service) {
        properties.insert(QTKEventConstants::SERVICE, QVariant::fromValue(service));
        QVariant id = service.getProperty(QTKEventConstants::SERVICE_ID);
        if (id.isValid()) {
            properties.insert(QTKEventConstants::SERVICE_ID, id);
            QVariant pid = service.getProperty(QTKEventConstants::SERVICE_PID);
            if (pid.isValid()) {
                properties.insert(QTKEventConstants::SERVICE_PID, pid);
            }

            QVariant objectClass = service.getProperty(QTKPluginConstants::OBJECT_CLASS);
            if (objectClass.isValid()) {
                properties.insert(QTKEventConstants::SERVICE_OBJECT_CLASS, objectClass);
            }
        }
    }

    QString strTopic("org/qtk/service/log/LogEntry/");

    int iLevel = entry->getLevel();
    if (iLevel == QTKLogService::LOG_ERROR) {
        strTopic.append("LOG_ERROR");
    } else if (iLevel == QTKLogService::LOG_WARNING) {
        strTopic.append("LOG_WARNING");
    } else if (iLevel == QTKLogService::LOG_INFO) {
        strTopic.append("LOG_INFO");
    } else if (iLevel == QTKLogService::LOG_DEBUG) {
        strTopic.append("LOG_DEBUG");
    } else {
        strTopic.append("LOG_OTHER");
    }

    try {
        m_pAdapter->getEventAdmin()->postEvent(QTKEvent(strTopic, properties));
    } catch(const QTKIllegalStateException &) {
        // This is o.k. - indicates that we are stopped.
    }
}

/**
 * @brief QTKEALogEventAdapter::QTKEALogEventAdapter
 * @param context
 * @param admin
 */
QTKEALogEventAdapter::QTKEALogEventAdapter(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKPluginContext *pContext,
                                           QTK_PLUGINFRAMEWORK_NAMESPACE::QTKEventAdmin *pAdmin)
    : QTKEAAbstractAdapter(pAdmin),
      m_pLogListener(new QTKLogListenerImpl(this))
{
    m_serviceReg = pContext->registerService<QTKLogListener>(m_pLogListener);
}

QTKEALogEventAdapter::~QTKEALogEventAdapter()
{
    delete m_pLogListener;
}

void QTKEALogEventAdapter::destroy(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKPluginContext* context)
{
    Q_UNUSED(context)

    m_serviceReg.unregister();
}
