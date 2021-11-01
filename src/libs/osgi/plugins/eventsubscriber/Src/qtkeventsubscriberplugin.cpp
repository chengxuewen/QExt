#include "qtkeventsubscriberplugin.h"

#include <QTKPluginFramework/Service/Event/QTKEventConstants>

void QTKEventSubscriberPlugin::start(QTKPluginContext *pContext)
{
    m_pEventHandler = new QTKSubscriberEventHandler();

    QTKDictionary publishedPropertys;
    publishedPropertys[QTKEventConstants::EVENT_TOPICS] = "org/qtk/eventpublisher/published";
    pContext->registerService<QTKEventHandler>(m_pEventHandler, publishedPropertys);
    QTKDictionary objPropertys;
    objPropertys[QTKEventConstants::EVENT_TOPICS] = "org/qtk/eventpublisher/published/obj";
    pContext->registerService<QTKEventHandler>(m_pEventHandler, objPropertys);
}

void QTKEventSubscriberPlugin::stop(QTKPluginContext *pContext)
{
    Q_UNUSED(pContext)
    delete  m_pEventHandler;
    m_pEventHandler = nullptr;
}
