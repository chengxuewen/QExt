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

#ifndef QTKPLUGINFRAMEWORK_P_H
#define QTKPLUGINFRAMEWORK_P_H

#include "qtkplugin_p.h"
#include "qtkpluginframework.h"
#include "qtkserviceregistration.h"
#include "qtkpluginframeworkevent.h"

#include <QMutex>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

class QTKPluginFrameworkContext;

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKPluginFrameworkPrivate class
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKPluginFrameworkPrivate : public QTKPluginPrivate
{
public:
    /**
     * @brief The QTKFrameworkEventWrapper struct
     * Holds all information for constructing a QTKPluginFrameworkEvent instance,
     * except for holding a QSharedPointer to the framework plug-in. This avoids
     * cyclic references in QTKPluginFramework.
     */
    struct QTKFrameworkEventWrapper
    {
        QTKFrameworkEventWrapper() : bIsNull(true) {}
        bool bIsNull;
        QTKPluginFrameworkEvent::Type eType;
    };

    QTKPluginFrameworkPrivate(QWeakPointer<QTKPlugin> pPlugin, QTKPluginFrameworkContext *pPFWContex);

    void init();
    void initRunTimePlugin();
    void activate(QTKPluginContext *pContext);
    void deactivate(QTKPluginContext *pContext);
    void uninitRunTimePlugin();

    /**
     * @brief shutdown
     * @param bRestart
     * This method starts a thread that stops this Framework,
     * stopping all started plug-ins.
     *
     * <p>If the framework is not started, this method does nothing.
     * If the framework is started, this method will:
     * <ol>
     * <li>Set the state of the QTKPluginFrameworkContext to <i>inactive</i>.</li>
     * <li>Suspended all started plug-ins as described in the
     * {@link QTKPlugin#stop()} method except that the persistent
     * state of the plug-in will continue to be started.
     * Reports any exceptions that occur during stopping using
     * <code>QTKPluginFramework</code>s.</li>
     * <li>Disable event handling.</li>
     * </ol></p>
     */
    void shutdown(bool bRestart);

    QHash<QString, QString> m_mapSystemHeaders;

    /**
     * @brief m_stopEvent
     * The event to return to callers waiting in QTKPluginFramework::waitForStop()
     * when the framework has been stopped.
     */
    QTKFrameworkEventWrapper m_stopEvent;

    /**
     * @brief m_shuttingDown
     * The flag indicating that the thread that performs shutdown of this
     * framework instance is running.
     */
    QAtomicInt m_shuttingDown;

    /**
     * @brief m_lockObj
     * Lock object
     */
    QTKLockObject m_lockObj;

private:
    /**
     * @brief shutdown0
     * Stop this FrameworkContext, suspending all started contexts.
     * This method suspends all started contexts so that they can be
     * automatically restarted when this FrameworkContext is next launched.
     *
     * <p>If the framework is not started, this method does nothing.
     * If the framework is started, this method will:
     * <ol>
     * <li>Set the state of the FrameworkContext to <i>inactive</i>.</li>
     * <li>Stop all started bundles as described in the
     * {@link Bundle#stop(int)} method except that the persistent
     * state of the bundle will continue to be started.
     * Reports any exceptions that occur during stopping using
     * <code>FrameworkErrorEvents</code>.</li>
     * <li>Disable event handling.</li>
     * </ol>
     * </p>
     *
     * @param bRestart
     * @param bWasActive
     */
    void shutdown0(bool bRestart, bool bWasActive);

    /**
     * @brief shutdownDone_unlocked
     * Tell system plugin shutdown finished.
     *
     * @param bRestart
     */
    void shutdownDone_unlocked(bool bRestart); //Tell system plugin shutdown finished.

    /**
     * @brief stopAllPlugins
     * Stop and unresolve all plug-ins.
     */
    void stopAllPlugins(); //Stop and unresolve all plug-ins.

    /**
     * @brief systemShuttingdownDone
     * Shutting down is done.
     *
     * @param pfwEvent
     */
    void systemShuttingdownDone(const QTKPluginFrameworkEvent &pfwEvent); //Shutting down is done.
    void systemShuttingdownDone_unlocked(const QTKPluginFrameworkEvent &pfwEvent);

    QList<QTKServiceRegistration> m_registrations;
};

QTK_PLUGINFRAMEWORK_END_NAMESPACE

#endif // QTKPLUGINFRAMEWORK_P_H
