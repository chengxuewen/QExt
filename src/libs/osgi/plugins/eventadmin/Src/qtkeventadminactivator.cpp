#include "qtkeventadminactivator_p.h"
#include "util/qtkealogtracker_p.h"
#include "qtkeaconfiguration_p.h"

#include <QtPlugin>

QTKEALogTracker* QTKEventAdminActivator::sm_pLogTracker = nullptr;

QTKEventAdminActivator::QTKEventAdminActivator()
    : m_pConfig(nullptr)
{

}

QTKEventAdminActivator::~QTKEventAdminActivator()
{
    if (m_pConfig) {
        delete m_pConfig;
    }
}

void QTKEventAdminActivator::start(QTKPluginContext *pContext)
{
    m_logFileFallback.open(stdout, QIODevice::WriteOnly);
    sm_pLogTracker = new QTKEALogTracker(pContext, &m_logFileFallback);
    sm_pLogTracker->open();

    if (m_pConfig) {
        delete m_pConfig;
    }
    // this creates the event admin and starts it
    m_pConfig = new QTKEAConfiguration(pContext);
}

void QTKEventAdminActivator::stop(QTKPluginContext *pContext)
{
    Q_UNUSED(pContext)

    if (m_pConfig) {
        m_pConfig->destroy();
    }

    sm_pLogTracker->close();
    delete sm_pLogTracker;
    sm_pLogTracker = nullptr;

    m_logFileFallback.close();
}

QTKLogService *QTKEventAdminActivator::getLogService()
{
    return sm_pLogTracker;
}

