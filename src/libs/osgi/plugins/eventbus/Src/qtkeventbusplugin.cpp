#include "qtkeventbusplugin.h"
#include "qtkeventbusimpl.h"

#include <QtPlugin>

#include <iostream>

QTKEventBusPlugin* QTKEventBusPlugin::m_pInstance = nullptr;

void QTKEventBusPlugin::start(QTKPluginContext *pContext)
{
    m_pInstance = this;
    m_pContext = pContext;
    m_pBus = new QTKEventBusImpl;
    pContext->registerService(QStringList("QTKEventAdminBus"), m_pBus);
    pContext->registerService<QTKEventAdminBus>(m_pBus);
}

void QTKEventBusPlugin::stop(QTKPluginContext *pContext)
{
    Q_UNUSED(pContext)
    delete m_pBus;
}

QTKEventBusPlugin *QTKEventBusPlugin::getInstance()
{
    return m_pInstance;
}

QTKPluginContext *QTKEventBusPlugin::getPluginContext() const
{
    return m_pContext;
}

