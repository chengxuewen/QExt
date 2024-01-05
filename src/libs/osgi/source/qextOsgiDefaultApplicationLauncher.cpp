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

#include <private/qextOsgiDefaultApplicationLauncher_p.h>
#include <private/qextOsgiPluginFrameworkProperties_p.h>
#include <qext/osgi/service/application/qextOsgiApplicationDescriptor.h>
#include <qextOsgiPluginFrameworkLauncher.h>
#include <qextOsgiApplicationRunnable.h>
#include <qextOsgiPluginConstants.h>
#include <qextOsgiPluginContext.h>
#include <qextException.h>


#include <QVariant>
#include <QDebug>


//----------------------------------------------------------------------------
struct FreeResources
{
    QExtOsgiDefaultApplicationLauncher* launcher;

    FreeResources(QExtOsgiDefaultApplicationLauncher* launcher)
        : launcher(launcher)
    {}

    ~FreeResources()
    {
        //if (Profile.PROFILE && Profile.STARTUP)
        //  Profile.logExit("qextOsgiPluginFrameworkLauncher.run(QVariant)()");

        // free the runnable application and release the lock to allow another app to be launched.
        launcher->runnable = NULL;
        launcher->appContext.clear();
        launcher->runningLock.release();
    }
};

//----------------------------------------------------------------------------
QExtOsgiDefaultApplicationLauncher::QExtOsgiDefaultApplicationLauncher(QExtOsgiPluginContext* context, bool relaunch, bool failOnNoDefault)
    : runnable(NULL)
    , runningLock(1)
    , waitForAppLock(0)
    , context(context)
    , relaunch(relaunch)
    , failOnNoDefault(failOnNoDefault)
{
}

//----------------------------------------------------------------------------
QVariant QExtOsgiDefaultApplicationLauncher::start(const QVariant& defaultContext)
{
    // here we assume that launch has been called by runtime before we started
    // TODO this may be a bad assumption but it works for now because we register the app launcher as a service and runtime synchronously calls launch on the service
    if (failOnNoDefault && runnable == NULL)
    {
        throw QExtIllegalStateException("Unable to acquire application service. Ensure that an application container is active");
    }
    QVariant result;
    bool doRelaunch = false;
    do
    {
        try
        {
            result = runApplication(defaultContext);
        }
        catch (const std::exception& e)
        {
            if (!relaunch || (context->getPlugin()->getState() != QExtOsgiPlugin::ACTIVE))
            {
                throw;
            }
            qWarning() << "Application error:" << e.what();
        }
        doRelaunch = (relaunch && context->getPlugin()->getState() == QExtOsgiPlugin::ACTIVE) ||
                     QExtOsgiPluginFrameworkProperties::getProperty(QExtOsgiPluginFrameworkLauncher::PROP_OSGI_RELAUNCH).toBool();
    }
    while (doRelaunch);

    return result;
}

//----------------------------------------------------------------------------
void QExtOsgiDefaultApplicationLauncher::launch(QExtOsgiApplicationRunnable* app, const QVariant& applicationContext)
{
    waitForAppLock.tryAcquire(); // clear out any pending apps notifications
    if (!runningLock.tryAcquire()) // check to see if an application is currently running
    {
        throw QExtIllegalStateException("An application is already running.");
    }
    this->runnable = app;
    this->appContext = applicationContext;
    waitForAppLock.release(); // notify the main thread to launch an application.
    runningLock.release(); // release the running lock
}

//----------------------------------------------------------------------------
void QExtOsgiDefaultApplicationLauncher::shutdown()
{
    // this method will acquire and keep the runningLock to prevent
    // all future application launches.
    if (runningLock.tryAcquire())
    {
        return; // no application is currently running.
    }
    QExtOsgiApplicationRunnable* currentRunnable = runnable;
    currentRunnable->stop();
    runningLock.tryAcquire(1, 60000); // timeout after 1 minute.
}

//----------------------------------------------------------------------------
QVariant QExtOsgiDefaultApplicationLauncher::reStart(const QVariant& argument)
{
    QList<QExtOsgiServiceReference> refs;
    refs = context->getServiceReferences<QExtOsgiApplicationDescriptor>("(qext.application.default=true)");
    if (!refs.isEmpty())
    {
        QExtOsgiApplicationDescriptor* defaultApp = context->getService<QExtOsgiApplicationDescriptor>(refs.front());
        defaultApp->launch(QHash<QString, QVariant>());
        return start(argument);
    }
    throw QExtIllegalStateException("Unable to acquire application service. Ensure that an application container is active");
}

//----------------------------------------------------------------------------
QVariant QExtOsgiDefaultApplicationLauncher::runApplication(const QVariant& defaultContext)
{

    // wait for an application to be launched.
    waitForAppLock.acquire();
    // an application is ready; acquire the running lock.
    // this must happen after we have acquired an application (by acquiring waitForAppLock above).
    runningLock.acquire();

    // run the actual application on the current thread (main).
    FreeResources cleanup(this);
    return runnable->run(appContext.isValid() ? appContext : defaultContext);
}
