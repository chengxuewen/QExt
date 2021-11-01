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

#ifndef QTKDEFAULTAPPLICATIONLAUNCHER_P_H
#define QTKDEFAULTAPPLICATIONLAUNCHER_P_H

#include "Service/Application/qtkapplicationlauncher.h"

#include <QSemaphore>
#include <QVariant>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

class QTKPluginContext;

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKDefaultApplicationLauncher class
 * A QTKApplicationLauncher is used to launch QTKApplicationRunnable objects using
 * the main thread.
 * <p>
 * This class is for use by platform-related plug-ins which implement application containers.
 * Clients outside of the base platform should not reference or subclass this class.
 * </p>
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKDefaultApplicationLauncher : public QObject, public QTKApplicationLauncher
{
    Q_OBJECT
    Q_INTERFACES(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKApplicationLauncher)

public:
    /**
     * @brief QTKDefaultApplicationLauncher::QTKDefaultApplicationLauncher
     * @param pContext
     * @param bFailOnNoDefault
     * @param bRelaunch
     */
    QTKDefaultApplicationLauncher(QTKPluginContext *pContext, bool bFailOnNoDefault, bool bRelaunch);


    /**
     * @brief QTKDefaultApplicationLauncher::start
     * Starts this application launcher on the current thread.  This method
     * should be called by the main thread to ensure that applications are
     * launched in the main thread.
     *
     * @param defaultContext
     * @return
     */
    QVariant start(const QVariant &defaultContext);

    /**
     * @brief QTKDefaultApplicationLauncher::reStart
     * Similar to the start method this method will restart the default method on the current thread.
     * This method assumes that the default application was launched at least once and that a QTKApplicationDescriptor
     * exists that can be used to relaunch the default application.
     *
     * @param argument The new context to re-start the default application with.
     * @return
     */
    QVariant reStart(const QVariant &argument);

    /**
     * @brief QTKDefaultApplicationLauncher::launch
     * Launches the specified runnable using the main thread.
     *
     * @param pApp A ParameterizedRunnalbe to run on the main thread.
     * @param applicationContext The context to launch the runnable with
     */
    void launch(QTKApplicationRunnable *pApp, const QVariant &applicationContext);

    /**
     * @brief QTKDefaultApplicationLauncher::shutdown
     * Forces the current runnable which is running to be stopped.
     * This method will return after the currently running QTKApplicationRunnable
     * has completely stopped.
     * <p>
     * After this method returns this QTKApplicationLauncher will no longer allow
     * applications to be launched.
     */
    void shutdown();

private:
    friend struct QTKFreeResources;

    /**
     * @brief QTKDefaultApplicationLauncher::runApplication
     * Waits for an application to be launched and the runs the application on the current thread (main).
     *
     * @param defaultContext
     * @return
     */
    QVariant runApplication(const QVariant &defaultContext);

    QTKApplicationRunnable *m_pRunnable;
    QVariant m_appContext;
    QSemaphore m_runningLock;
    QSemaphore m_waitForAppLock;
    QTKPluginContext *m_pContext;
    bool m_bRelaunch;
    bool m_bFailOnNoDefault;
};

QTK_PLUGINFRAMEWORK_END_NAMESPACE

#endif // QTKDEFAULTAPPLICATIONLAUNCHER_P_H
