#include "qtklogplugin_p.h"
#include "qtklogqdebug_p.h"

#include <QtPlugin>
#include <QStringList>

QTKLogPlugin::QTKLogPlugin() : m_pLogService(0)
{

}

void QTKLogPlugin::start(QTKPluginContext* pContext)
{
    m_pLogService = new QTKLogQDebug();
    pContext->registerService(QStringList("QTKLogService"), m_pLogService);
}

void QTKLogPlugin::stop(QTKPluginContext* pContext)
{
    Q_UNUSED(pContext)
    if (m_pLogService)
    {
        delete m_pLogService;
        m_pLogService = 0;
    }
}

#if (QT_VERSION < QT_VERSION_CHECK(5,0,0))
Q_EXPORT_PLUGIN2(QTKLog, QTKLogPlugin)
#endif
