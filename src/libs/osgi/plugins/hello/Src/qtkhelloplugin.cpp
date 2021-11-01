#include "qtkhelloplugin.h"
#include "qtkhelloimpl.h"

void QTKHelloPlugin::start(QTKPluginContext *pContext)
{
    m_service.reset(new QTKHelloImpl(pContext));
}

void QTKHelloPlugin::stop(QTKPluginContext *pContext)
{
    Q_UNUSED(pContext)
}
