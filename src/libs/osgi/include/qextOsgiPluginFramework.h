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

#ifndef QTKPLUGINFRAMEWORK_H
#define QTKPLUGINFRAMEWORK_H

#include "qtkpluginframework_global.h"
#include "qtkpluginframeworkevent.h"
#include "qtkplugin.h"

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

class QTKPluginFrameworkContext;
class QTKPluginFrameworkPrivate;

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKPluginFramework class
 *
 * A %QTKPluginFramework instance. A %QTKPluginFramework is also known as a System %Plugin.
 *
 * <p>
 * %QTKPluginFramework instances are created using a QTKPluginFrameworkFactory. The methods
 * of this class can be used to manage and control the created plugin framework instance.
 *
 * @remarks This class is thread safe.
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKPluginFramework : public QTKPlugin
{
public:
    /**
     * @brief init
     * Initialize this %QTKPluginFramework. After calling this method, this %QTKPluginFramework
     * must:
     * <ul>
     * <li>Be in the {@link #STARTING} state.</li>
     * <li>Have a valid Plugin Context.</li>
     * <li>Be at start level 0.</li>
     * <li>Have event handling enabled.</li>
     * <li>Have create QTKPlugin objects for all installed plugins.</li>
     * <li>Have registered any framework services.</li>
     * </ul>
     *
     * <p>
     * This %QTKPluginFramework will not actually be started until {@link #start() start}
     * is called.
     *
     * <p>
     * This method does nothing if called when this %QTKPluginFramework is in the
     * {@link #STARTING}, {@link #ACTIVE} or {@link #STOPPING} states.
     *
     * @throws QTKPluginException If this %QTKPluginFramework could not be initialized.
     */
    void init();

    /**
     * @brief waitForStop
     * Wait until this %QTKPluginFramework has completely stopped. The <code>stop</code>
     * and <code>update</code> methods perform an asynchronous
     * stop of the Framework. This method can be used to wait until the
     * asynchronous stop of this Framework has completed. This method will only
     * wait if called when this Framework is in the {@link #STARTING},
     * {@link #ACTIVE}, or {@link #STOPPING} states. Otherwise it will return
     * immediately.
     * <p>
     * A Framework Event is returned to indicate why this Framework has stopped.
     *
     * @param ulTimeout Maximum number of milliseconds to wait until this
     *        Framework has completely stopped. A value of zero will wait
     *        indefinitely.
     * @return A Framework Event indicating the reason this method returned. The
     *         following <code>QTKPluginFrameworkEvent</code> types may be returned by
     *         this method.
     *         <ul>
     *         <li>{@link QTKPluginFrameworkEvent#Type_FrameworkStopped STOPPED} - This Framework has
     *         been stopped. </li>
     *
     *         <li>{@link QTKPluginFrameworkEvent#Type_FrameworkStoppedUpdate STOPPED_UPDATE} - This
     *         Framework has been updated which has shutdown and will now
     *         restart.</li>
     *
     *         <li>{@link QTKPluginFrameworkEvent#Type_PluginError ERROR} - The Framework
     *         encountered an error while shutting down or an error has occurred
     *         which forced the framework to shutdown. </li>
     *
     *         <li> {@link QTKPluginFrameworkEvent#Type_FrameworkWaitTimeOut WAIT_TIMEDOUT} - This
     *         method has timed out and returned before this Framework has
     *         stopped.</li>
     *         </ul>
     */
    QTKPluginFrameworkEvent waitForStop(unsigned long ulTimeout);

    /**
     * @brief start
     * Start this %QTKPluginFramework.
     *
     * <p>
     * The following steps are taken to start this %QTKPluginFramework:
     * <ol>
     * <li>If this %QTKPluginFramework is not in the {@link #STARTING} state,
     * {@link #init() initialize} this %QTKPluginFramework.</li>
     * <li>All installed plugins must be started in accordance with each
     * plugin's persistent <i>autostart setting</i>. This means some plugins
     * will not be started, some will be started with <i>lazy activation</i>
     * and some will be started with their <i>declared activation</i> policy.
     * Any exceptions that occur during plugin starting must be wrapped in a
     * {@link QTKPluginException} and then published as a plugin framework event of type
     * {@link QTKPluginFrameworkEvent::Type_PluginError}</li>
     * <li>This %PluinFramework's state is set to {@link #ACTIVE}.</li>
     * <li>A plugin framework event of type {@link QTKPluginFrameworkEvent::Type_FrameworkStarted} is fired</li>
     * </ol>
     *
     * @param options Ignored. There are no start options for the %QTKPluginFramework.
     * @throws QTKPluginException If this %QTKPluginFramework could not be started.
     */
    void start(const QTKPlugin::StartOptions &options = 0);

    /**
     * @brief stop
     * Stop this %QTKPluginFramework.
     *
     * <p>
     * The method returns immediately to the caller after initiating the
     * following steps to be taken on another thread.
     * <ol>
     * <li>This Framework's state is set to {@link #STOPPING}.</li>
     * <li>All installed plugins must be stopped without changing each plugin's
     * persistent <i>autostart setting</i>. If this Framework implements the
     * optional <i>Start Level Service Specification</i>, then the start level
     * of this Framework is moved to start level zero (0), as described in the
     * <i>Start Level Service Specification</i>. Any exceptions that occur
     * during plugin stopping must be wrapped in a {@link QTKPluginException} and
     * then published as a framework event of type {@link QTKPluginFrameworkEvent#Type_PluginError}</li>
     * <li>Unregister all services registered by this Framework.</li>
     * <li>Event handling is disabled.</li>
     * <li>This Framework's state is set to {@link #RESOLVED}.</li>
     * <li>All resources held by this Framework are released. This includes
     * threads, loaded libraries, open files, etc.</li>
     * <li>Notify all threads that are waiting at {@link #waitForStop(unsigned long)
     * waitForStop} that the stop operation has completed.</li>
     * </ol>
     * <p>
     * After being stopped, this Framework may be discarded, initialized or
     * started.
     *
     * @param options Ignored. There are no stop options for the Framework.
     * @throws QTKPluginException If stopping this Framework could not be
     *         initiated.
     * @see "Start Level Service Specification"
     */
    void stop(const StopOptions &options = 0);

    /**
     * @brief uninstall
     * The %QTKPluginFramework cannot be uninstalled.
     *
     * <p>
     * This method always throws a QTKPluginException.
     *
     * @throws QTKPluginException This Framework cannot be uninstalled.
     */
    void uninstall();

    /**
     * @brief getHeaders
     * @return
     * @see QTKPlugin::getHeaders()
     */
    QHash<QString, QString> getHeaders();

    /**
     * @brief getResourceList
     * @param strPath
     * @return
     * @see QTKPlugin::getResourceList()
     */
    QStringList getResourceList(const QString &strPath) const;

    /**
     * @brief getResource
     * @param strPath
     * @return
     * @see QTKPlugin::getResource()
     */
    QByteArray getResource(const QString &strPath) const;

protected:
    friend class QTKPluginFrameworkContext;
    QTKPluginFramework();

private:
    Q_DECLARE_PRIVATE(QTKPluginFramework)
    Q_DISABLE_COPY(QTKPluginFramework)
};

QTK_PLUGINFRAMEWORK_END_NAMESPACE

#endif // QTKPLUGINFRAMEWORK_H
