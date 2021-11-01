#include "qtkeventpublisherplugin.h"

#include <QTKPluginFramework/QTKPluginContext>
#include <QTKPluginFramework/QTKServiceReference>
#include <QTKPluginFramework/Service/Event/QTKEventAdmin>

#include <QDateTime>
#include <QWidget>

void QTKEventPublisherPlugin::start(QTKPluginContext *pContext)
{
    m_pContext = pContext;
    m_timer.setInterval(500);
    connect(&m_timer, &QTimer::timeout, this, &QTKEventPublisherPlugin::timerTimeout);
    m_timer.start();
}

void QTKEventPublisherPlugin::stop(QTKPluginContext *pContext)
{
    (void)pContext;
    m_timer.stop();
}

void QTKEventPublisherPlugin::timerTimeout()
{
    static bool bFlag = false;
    static quint64 liId = 0;

    QTKServiceReference serviceRef = m_pContext->getServiceReference<QTKEventAdmin>();
    if (serviceRef) {
        QTKEventAdmin *pEventAdmin = m_pContext->getService<QTKEventAdmin>(serviceRef);
        QTKDictionary propertys;
        propertys["flag"] = bFlag;
        propertys["id"] = ++liId;
        propertys["send datetime"] = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz");
        QTKEvent event("org/qtk/eventpublisher/published", propertys);
        pEventAdmin->sendEvent(event);

        QTKDictionary property2s;
        property2s["obj"] = "QTKEventPublisherPlugin";
        QTKEvent objEvent("org/qtk/eventpublisher/published/obj", property2s);
        pEventAdmin->postEvent(objEvent);
    }

    bFlag = !bFlag;
}
