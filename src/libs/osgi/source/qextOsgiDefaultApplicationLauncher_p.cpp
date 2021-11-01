/****************************************************************************
** Library: QTK
**
** Copyright (c) German Cancer Research Center,
**     Division of Medical and Biological Informatics
** Copyright (c) chengxuewen <1398831004@qq.com>
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
** http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
**
****************************************************************************/

#include "qtkdefaultapplicationlauncher_p.h"
#include "qtkapplicationrunnable.h"
#include "qtkpluginconstants.h"
#include "qtkplugincontext.h"
#include "qtkpluginframeworklauncher.h"
#include "qtkpluginframeworkproperties_p.h"
#include "Service/Application/qtkapplicationdescriptor.h"

#include <QTKCore/QTKException>

#include <QVariant>
#include <QDebug>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

/**
 * @brief The QTKFreeResources struct
 */
struct QTKFreeResources
{
    QTKFreeResources(QTKDefaultApplicationLauncher *pLauncher) {
        m_pLauncher = pLauncher;
    }

    ~QTKFreeResources() {
        //if (Profile.PROFILE && Profile.STARTUP)
        //  Profile.logExit("QTKPluginFrameworkLauncher.run(QVariant)()");

        // free the runnable application and release the lock to allow another app to be launched.
        m_pLauncher->m_pRunnable = nullptr;
        m_pLauncher->m_appContext.clear();
        m_pLauncher->m_runningLock.release();
    }

    QTKDefaultApplicationLauncher *m_pLauncher;
};

QTKDefaultApplicationLauncher::QTKDefaultApplicationLauncher(QTKPluginContext* pContext,
                                                             bool bFailOnNoDefault, bool bRelaunch)
    : m_pRunnable(nullptr),
      m_runningLock(1),
      m_waitForAppLock(0),
      m_pContext(pContext),
      m_bRelaunch(bRelaunch),
      m_bFailOnNoDefault(bFailOnNoDefault)
{

}

QVariant QTKDefaultApplicationLauncher::start(const QVariant &defaultContext)
{
    // here we assume that launch has been called by runtime before we started
    // TODO this may be a bad assumption but it works for now because we register the app launcher as a service and runtime synchronously calls launch on the service
    if (m_bFailOnNoDefault && nullptr == m_pRunnable) {
        throw QTKIllegalStateException("Unable to acquire application service. Ensure that an application container is active");
    }
    QVariant result;
    bool bDoRelaunch = false;
    do {
        try {
            result = this->runApplication(defaultContext);
        } catch (const std::exception &e) {
            if (!m_bRelaunch || (m_pContext->getPlugin()->getState() != QTKPlugin::State_Active)) {
                throw;
            }
            qWarning() << "Application error:" << e.what();
        }
        bDoRelaunch = (m_bRelaunch && m_pContext->getPlugin()->getState() == QTKPlugin::State_Active) ||
                QTKPluginFrameworkProperties::getProperty(QTKPluginFrameworkLauncher::PROPERTIE_PLUGINFRAMEWORK_RELAUNCH).toBool();
    } while (bDoRelaunch);

    return result;
}

void QTKDefaultApplicationLauncher::launch(QTKApplicationRunnable *pApp, const QVariant &applicationContext)
{
    m_waitForAppLock.tryAcquire(); // clear out any pending apps notifications
    // check to see if an application is currently running
    if (!m_runningLock.tryAcquire()) {
        throw QTKIllegalStateException("An application is aready running.");
    }
    m_pRunnable = pApp;
    m_appContext = applicationContext;
    m_waitForAppLock.release(); // notify the main thread to launch an application.
    m_runningLock.release(); // release the running lock
}

void QTKDefaultApplicationLauncher::shutdown()
{
    // this method will aquire and keep the runningLock to prevent
    // all future application launches.
    if (m_runningLock.tryAcquire()) {
        return; // no application is currently running.
    }
    QTKApplicationRunnable *pCurrentRunnable = m_pRunnable;
    pCurrentRunnable->stop();
    m_runningLock.tryAcquire(1, 60000); // timeout after 1 minute.
}

QVariant QTKDefaultApplicationLauncher::reStart(const QVariant& argument)
{
    QList<QTKServiceReference> serviceReference;
    serviceReference = m_pContext->getServiceReferences<QTKApplicationDescriptor>("(QTK.application.default=true)");
    if (!serviceReference.isEmpty()) {
        QTKApplicationDescriptor *pDefaultApp = m_pContext->getService<QTKApplicationDescriptor>(serviceReference.front());
        pDefaultApp->launch(QHash<QString, QVariant>());
        return start(argument);
    }
    throw QTKIllegalStateException("Unable to acquire application service. Ensure that an application container is active");
}

QVariant QTKDefaultApplicationLauncher::runApplication(const QVariant &defaultContext)
{
    Q_UNUSED(defaultContext)
    m_waitForAppLock.acquire();
    m_runningLock.acquire();
    return  defaultContext;
}

QTK_PLUGINFRAMEWORK_END_NAMESPACE
