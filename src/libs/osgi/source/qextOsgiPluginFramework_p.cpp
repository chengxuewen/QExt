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

#include "qtkpluginframework_p.h"
#include "qtkpluginconstants.h"
#include "qtkplugincontext_p.h"
#include "qtklocationmanager_p.h"
#include "qtkpluginframework_p.h"
#include "qtkpluginframeworkcontext_p.h"
#include "qtkpluginframeworkutil_p.h"
#include "qtkpluginframeworkdebugoptions_p.h"
#include "qtkpluginframeworklauncher.h"
#include "qtkversion.h"

#include <qtkbasiclocation_p.h>

#include <QtConcurrentRun>
#include <QObject>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

QTKPluginFrameworkPrivate::QTKPluginFrameworkPrivate(QWeakPointer<QTKPlugin> pPlugin, QTKPluginFrameworkContext *pPFWContex)
    : QTKPluginPrivate(pPlugin, pPFWContex, 0, QTKPluginConstants::SYSTEM_PLUGIN_LOCATION,
                       QTKPluginConstants::SYSTEM_PLUGIN_SYMBOLIC_NAME,
                       QTKVersion(0, 9, 0)),
      m_shuttingDown(0)
{
    m_mapSystemHeaders.insert(QTKPluginConstants::PLUGIN_SYMBOLIC_NAME, m_strSymbolicName);
    m_mapSystemHeaders.insert(QTKPluginConstants::PLUGIN_NAME, m_strLocation);
    m_mapSystemHeaders.insert(QTKPluginConstants::PLUGIN_VERSION, m_version.toString());
}

void QTKPluginFrameworkPrivate::init()
{
    m_eState = QTKPlugin::State_Starting;
    m_pPFWContext->init();
}

void QTKPluginFrameworkPrivate::initRunTimePlugin()
{
    this->m_pPluginContext.reset(new QTKPluginContext(this));
}

void QTKPluginFrameworkPrivate::activate(QTKPluginContext *pContext)
{
    QTKProperties locationProperties;
    QTKBasicLocation *pLocation = QTKLocationManager::getUserLocation();
    if (nullptr != pLocation) {
        locationProperties["type"] =  QTKPluginFrameworkLauncher::PROPERTIE_USER_AREA;
        m_registrations.push_back(pContext->registerService<QTKLocation>(pLocation, locationProperties));
    }
    pLocation = QTKLocationManager::getInstanceLocation();
    if (nullptr != pLocation) {
        locationProperties["type"] = QTKPluginFrameworkLauncher::PROPERTIE_INSTANCE_AREA;
        m_registrations.push_back(pContext->registerService<QTKLocation>(pLocation, locationProperties));
    }
    pLocation = QTKLocationManager::getConfigurationLocation();
    if (nullptr != pLocation) {
        locationProperties["type"] = QTKPluginFrameworkLauncher::PROPERTIE_CONFIGURATION_AREA;
        m_registrations.push_back(pContext->registerService<QTKLocation>(pLocation, locationProperties));
    }
    pLocation = QTKLocationManager::getInstallLocation();
    if (nullptr != pLocation) {
        locationProperties["type"] = QTKPluginFrameworkLauncher::PROPERTIE_INSTALL_AREA;
        m_registrations.push_back(pContext->registerService<QTKLocation>(pLocation, locationProperties));
    }
    pLocation = QTKLocationManager::getQTKHomeLocation();
    if (nullptr != pLocation) {
        locationProperties["type"] = QTKPluginFrameworkLauncher::PROPERTIE_HOME_LOCATION;
        m_registrations.push_back(pContext->registerService<QTKLocation>(pLocation, locationProperties));
    }

    QTKPluginFrameworkDebugOptions *pDebugOptions = QTKPluginFrameworkDebugOptions::getDefault();
    pDebugOptions->start(pContext);
    pContext->registerService<QTKDebugOptions>(pDebugOptions);
}

void QTKPluginFrameworkPrivate::deactivate(QTKPluginContext *)
{
    foreach(QTKServiceRegistration registration, m_registrations) {
        if (registration) {
            try {
                registration.unregister();
            } catch (const QTKIllegalStateException &) {

            }
        }
    }
}

void QTKPluginFrameworkPrivate::uninitRunTimePlugin()
{
    m_pPluginContext->d_func()->invalidate();
}

void QTKPluginFrameworkPrivate::shutdown(bool bRestart)
{
    QTKLocker sync(&m_lockObj);

    bool bWasActive = false;
    switch (m_eState)
    {
    case QTKPlugin::State_Installed:
    case QTKPlugin::State_Resolved:
    {
        shutdownDone_unlocked(false);
        break;
    }
    case QTKPlugin::State_Active:
    {
        bWasActive = true;
    }
    case QTKPlugin::State_Starting:
    {
        if (m_shuttingDown.fetchAndAddOrdered(0) == 0) {
            try {
                const bool bWa = bWasActive;
                m_shuttingDown.fetchAndStoreOrdered(1);
                QtConcurrent::run(this, &QTKPluginFrameworkPrivate::shutdown0, bRestart, bWa);
            } catch (const QTKException &e) {
                systemShuttingdownDone(QTKPluginFrameworkEvent(QTKPluginFrameworkEvent::Type_PluginError,
                                                               this->q_func(), e));
            }
        }
        break;
    }
    case QTKPlugin::State_Stopping:
    case QTKPlugin::State_Uninstalled:
    {
        break;
    }
    }
}

void QTKPluginFrameworkPrivate::shutdown0(bool bRestart, bool bWasActive)
{
    try {
        {
            QTKLocker sync(&m_lockObj);
            waitOnOperation(&m_lockObj, QString("Framework::") + (bRestart ? "update" : "stop"), true);
            m_operation = sm_iDeactivating;
            m_eState = QTKPlugin::State_Stopping;
        }

        m_pPFWContext->m_listeners.emitPluginChanged(QTKPluginEvent(QTKPluginEvent::Type_Stopping, this->q_func()));

        if (bWasActive) {
            this->stopAllPlugins();
            this->deactivate(this->m_pPluginContext.data());
        }

        {
            QTKLocker sync(&m_lockObj);
            m_pPFWContext->uninit();
            m_shuttingDown.fetchAndStoreOrdered(0);
            this->shutdownDone_unlocked(bRestart);
        }

        if (bRestart) {
            if (bWasActive) {
                q_func().toStrongRef()->start();
            } else {
                this->init();
            }
        }
    } catch (const QTKException &e) {
        m_shuttingDown.fetchAndStoreOrdered(0);
        this->systemShuttingdownDone(QTKPluginFrameworkEvent(QTKPluginFrameworkEvent::Type_PluginError,
                                                             this->q_func(), e));
    }
}

void QTKPluginFrameworkPrivate::shutdownDone_unlocked(bool bRestart)
{
    QTKPluginFrameworkEvent::Type eType = bRestart ? QTKPluginFrameworkEvent::Type_FrameworkStoppedUpdate : QTKPluginFrameworkEvent::Type_FrameworkStopped;
    this->systemShuttingdownDone_unlocked(QTKPluginFrameworkEvent(eType, this->q_func()));
}

void QTKPluginFrameworkPrivate::stopAllPlugins()
{
    // Stop all active plug-ins, in reverse plug-in ID order
    // The list will be empty when the start level service is in use.
    QList<QSharedPointer<QTKPlugin> > activePlugins = m_pPFWContext->m_pPlugins->getActivePlugins();
    qSort(activePlugins.begin(), activePlugins.end(), pluginIdLessThan);
    QListIterator<QSharedPointer<QTKPlugin> > ite(activePlugins);
    ite.toBack();
    while(ite.hasPrevious()) {
        QSharedPointer<QTKPlugin> p = ite.previous();
        try {
            if (p->getState() & (QTKPlugin::State_Active | QTKPlugin::State_Starting)) {
                // Stop plugin without changing its autostart setting.
                p->stop(QTKPlugin::StopOption_StopTransient);
            }
        } catch (const QTKPluginException &pe) {
            m_pPFWContext->m_listeners.frameworkError(p, pe);
        }
    }

    QList<QSharedPointer<QTKPlugin> > listAllPlugins = m_pPFWContext->m_pPlugins->getPlugins();
    // Set state to INSTALLED and purge any unrefreshed bundles
    foreach (QSharedPointer<QTKPlugin> p, listAllPlugins) {
        if (0 != p->getPluginId()) {
            p->d_func()->setStateInstalled(false);
            p->d_func()->purge();
        }
    }
}

void QTKPluginFrameworkPrivate::systemShuttingdownDone(const QTKPluginFrameworkEvent &pfwEvent)
{
    QTKLocker sync(&m_lockObj);
    systemShuttingdownDone_unlocked(pfwEvent);
}

void QTKPluginFrameworkPrivate::systemShuttingdownDone_unlocked(const QTKPluginFrameworkEvent &pfwEvent)
{
    if (QTKPlugin::State_Installed != m_eState) {
        m_eState = QTKPlugin::State_Resolved;
        m_operation.fetchAndStoreOrdered(sm_iIdle);
        m_lockObj.wakeAll();
    }
    m_stopEvent.bIsNull = pfwEvent.isNull();
    m_stopEvent.eType = pfwEvent.getType();
}

QTK_PLUGINFRAMEWORK_END_NAMESPACE
