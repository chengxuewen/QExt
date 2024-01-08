/*=============================================================================

  Library: CTK

  Copyright (c) German Cancer Research Center,
    Division of Medical and Biological Informatics

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=============================================================================*/

#include <qextOsgiPluginFramework.h>
#include <qextOsgiPluginConstants.h>
#include <qextOsgiPluginContext.h>
#include <qextOsgiPluginFrameworkLauncher.h>
#include <private/qextOsgiPluginContext_p.h>
#include <private/qextOsgiLocationManager_p.h>
#include <private/qextOsgiPluginFramework_p.h>
#include <private/qextOsgiPluginFrameworkContext_p.h>
#include <private/qextOsgiPluginFrameworkUtil_p.h>
#include <private/qextOsgiPluginFrameworkDebugOptions_p.h>
#include <private/qextOsgiBasicLocation_p.h>

#include <QtConcurrentRun>

//----------------------------------------------------------------------------
QExtOsgiPluginFrameworkPrivate::QExtOsgiPluginFrameworkPrivate(QWeakPointer<QExtOsgiPlugin> qq, QExtOsgiPluginFrameworkContext* fw)
    : QExtOsgiPluginPrivate(qq, fw, 0, QExtOsgiPluginConstants::SYSTEM_PLUGIN_LOCATION,
                            QExtOsgiPluginConstants::SYSTEM_PLUGIN_SYMBOLICNAME,
                            // TODO: read version from the manifest resource
                            QExtOsgiVersion(0, 9, 0)),
    shuttingDown(0)
{
    systemHeaders.insert(QExtOsgiPluginConstants::PLUGIN_SYMBOLICNAME, symbolicName);
    systemHeaders.insert(QExtOsgiPluginConstants::PLUGIN_NAME, location);
    systemHeaders.insert(QExtOsgiPluginConstants::PLUGIN_VERSION, version.toString());
}

//----------------------------------------------------------------------------
void QExtOsgiPluginFrameworkPrivate::init()
{
    this->state = QExtOsgiPlugin::STARTING;
    this->fwCtx->init();
}

//----------------------------------------------------------------------------
void QExtOsgiPluginFrameworkPrivate::initSystemPlugin()
{
    this->pluginContext.reset(new QExtOsgiPluginContext(this));
}

//----------------------------------------------------------------------------
void QExtOsgiPluginFrameworkPrivate::activate(QExtOsgiPluginContext* context)
{
    QExtOsgiProperties locationProperties;
    QExtOsgiBasicLocation* location = QExtOsgiLocationManager::getUserLocation();
    if (location != NULL)
    {
        locationProperties["type"] =  QExtOsgiPluginFrameworkLauncher::PROP_USER_AREA;
        registrations.push_back(context->registerService<QExtOsgiLocation>(location, locationProperties));
    }
    location = QExtOsgiLocationManager::getInstanceLocation();
    if (location != NULL)
    {
        locationProperties["type"] = QExtOsgiPluginFrameworkLauncher::PROP_INSTANCE_AREA;
        registrations.push_back(context->registerService<QExtOsgiLocation>(location, locationProperties));
    }
    location = QExtOsgiLocationManager::getConfigurationLocation();
    if (location != NULL)
    {
        locationProperties["type"] = QExtOsgiPluginFrameworkLauncher::PROP_CONFIG_AREA;
        registrations.push_back(context->registerService<QExtOsgiLocation>(location, locationProperties));
    }
    location = QExtOsgiLocationManager::getInstallLocation();
    if (location != NULL)
    {
        locationProperties["type"] = QExtOsgiPluginFrameworkLauncher::PROP_INSTALL_AREA;
        registrations.push_back(context->registerService<QExtOsgiLocation>(location, locationProperties));
    }

    location = QExtOsgiLocationManager::getCTKHomeLocation();
    if (location != NULL)
    {
        locationProperties["type"] = QExtOsgiPluginFrameworkLauncher::PROP_HOME_LOCATION_AREA;
        registrations.push_back(context->registerService<QExtOsgiLocation>(location, locationProperties));
    }

    QExtOsgiPluginFrameworkDebugOptions* dbgOptions = QExtOsgiPluginFrameworkDebugOptions::getDefault();
    dbgOptions->start(context);
    context->registerService<QExtOsgiDebugOptions>(dbgOptions);
}

//----------------------------------------------------------------------------
void QExtOsgiPluginFrameworkPrivate::deactivate(QExtOsgiPluginContext* /*context*/)
{
    foreach(QExtOsgiServiceRegistration registration, registrations)
    {
        if (registration)
        {
            try
            {
                registration.unregister();
            }
            catch (const QExtIllegalStateException&) {}
        }
    }
}

//----------------------------------------------------------------------------
void QExtOsgiPluginFrameworkPrivate::uninitSystemPlugin()
{
    this->pluginContext->d_func()->invalidate();
}

//----------------------------------------------------------------------------
void QExtOsgiPluginFrameworkPrivate::shutdown(bool restart)
{
    Locker sync(&lock);

    bool wasActive = false;
    switch (state)
    {
    case QExtOsgiPlugin::INSTALLED:
    case QExtOsgiPlugin::RESOLVED:
        shutdownDone_unlocked(false);
        break;
    case QExtOsgiPlugin::ACTIVE:
        wasActive = true;
        // Fall through
    case QExtOsgiPlugin::STARTING:
        if (shuttingDown.fetchAndAddOrdered(0) == 0)
        {
            try
            {
                const bool wa = wasActive;
                shuttingDown.fetchAndStoreOrdered(1);
                QtConcurrent::run(this, &QExtOsgiPluginFrameworkPrivate::shutdown0, restart, wa);
            }
            catch (const QExtException& e)
            {
                systemShuttingdownDone(QExtOsgiPluginFrameworkEvent(QExtOsgiPluginFrameworkEvent::PLUGIN_ERROR,
                                                                    this->q_func(), e));
            }
        }
        break;
    case QExtOsgiPlugin::STOPPING:
        // Shutdown already inprogress, fall through
    case QExtOsgiPlugin::UNINSTALLED:
        break;
    }
}

//----------------------------------------------------------------------------
void QExtOsgiPluginFrameworkPrivate::shutdown0(bool restart, bool wasActive)
{
    try
    {
        {
            Locker sync(&lock);
            waitOnOperation(&lock, QString("Framework::") + (restart ? "update" : "stop"), true);
            operation = DEACTIVATING;
            state = QExtOsgiPlugin::STOPPING;
        }

        fwCtx->listeners.emitPluginChanged(
            QExtOsgiPluginEvent(QExtOsgiPluginEvent::STOPPING, this->q_func()));

        if (wasActive)
        {
            stopAllPlugins();
            deactivate(this->pluginContext.data());
        }

        {
            Locker sync(&lock);
            fwCtx->uninit();
            shuttingDown.fetchAndStoreOrdered(0);
            shutdownDone_unlocked(restart);
        }

        if (restart)
        {
            if (wasActive)
            {
                q_func().toStrongRef()->start();
            }
            else
            {
                init();
            }
        }
    }
    catch (const QExtException& e)
    {
        shuttingDown.fetchAndStoreOrdered(0);
        systemShuttingdownDone(QExtOsgiPluginFrameworkEvent(QExtOsgiPluginFrameworkEvent::PLUGIN_ERROR,
                                                            this->q_func(), e));
    }
}

//----------------------------------------------------------------------------
void QExtOsgiPluginFrameworkPrivate::shutdownDone_unlocked(bool restart)
{
    QExtOsgiPluginFrameworkEvent::Type t = restart ? QExtOsgiPluginFrameworkEvent::FRAMEWORK_STOPPED_UPDATE : QExtOsgiPluginFrameworkEvent::FRAMEWORK_STOPPED;
    systemShuttingdownDone_unlocked(QExtOsgiPluginFrameworkEvent(t, this->q_func()));
}

//----------------------------------------------------------------------------
void QExtOsgiPluginFrameworkPrivate::stopAllPlugins()
{
    // TODO start level
    //  if (fwCtx.startLevelController != null)
    //  {
    //    fwCtx.startLevelController.shutdown();
    //  }

    // Stop all active plug-ins, in reverse plug-in ID order
    // The list will be empty when the start level service is in use.
    QList<QSharedPointer<QExtOsgiPlugin> > activePlugins = fwCtx->plugins->getActivePlugins();
#if QT_VERSION >= QT_VERSION_CHECK(5,2,0)
    std::sort(activePlugins.begin(), activePlugins.end(), pluginIdLessThan);
#else
    qSort(activePlugins.begin(), activePlugins.end(), pluginIdLessThan);
#endif
    QListIterator<QSharedPointer<QExtOsgiPlugin> > i(activePlugins);
    i.toBack();
    while(i.hasPrevious())
    {
        QSharedPointer<QExtOsgiPlugin> p = i.previous();
        try
        {
            if (p->getState() & (QExtOsgiPlugin::ACTIVE | QExtOsgiPlugin::STARTING))
            {
                // Stop plugin without changing its autostart setting.
                p->stop(QExtOsgiPlugin::STOP_TRANSIENT);
            }
        }
        catch (const QExtOsgiPluginException& pe)
        {
            fwCtx->listeners.frameworkError(p, pe);
        }
    }

    QList<QSharedPointer<QExtOsgiPlugin> > allPlugins = fwCtx->plugins->getPlugins();

    // Set state to INSTALLED and purge any unrefreshed bundles
    foreach (QSharedPointer<QExtOsgiPlugin> p, allPlugins)
    {
        if (p->getPluginId() != 0)
        {
            p->d_func()->setStateInstalled(false);
            p->d_func()->purge();
        }
    }
}

//----------------------------------------------------------------------------
void QExtOsgiPluginFrameworkPrivate::systemShuttingdownDone(const QExtOsgiPluginFrameworkEvent &fe)
{
    Locker sync(&lock);
    systemShuttingdownDone_unlocked(fe);
}

//----------------------------------------------------------------------------
void QExtOsgiPluginFrameworkPrivate::systemShuttingdownDone_unlocked(const QExtOsgiPluginFrameworkEvent &fe)
{

    if (state != QExtOsgiPlugin::INSTALLED)
    {
        state = QExtOsgiPlugin::RESOLVED;
        operation.fetchAndStoreOrdered(IDLE);
        lock.wakeAll();
    }
    stopEvent.isNull = fe.isNull();
    stopEvent.type = fe.getType();
}
