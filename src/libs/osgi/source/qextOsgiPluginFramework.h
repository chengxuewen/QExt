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

#ifndef _QEXTOSGIPLUGINFRAMEWORK_H
#define _QEXTOSGIPLUGINFRAMEWORK_H

#include <qextOsgiGlobal.h>
#include <qextOsgiPlugin.h>
#include <qextOsgiPluginFrameworkEvent.h>

class QExtOsgiPluginFrameworkContext;
class QExtOsgiPluginFrameworkPrivate;

/**
 * \ingroup PluginFramework
 *
 * A %QExtOsgiPluginFramework instance. A %QExtOsgiPluginFramework is also known as a System %Plugin.
 *
 * <p>
 * %QExtOsgiPluginFramework instances are created using a QExtOsgiPluginFrameworkFactory. The methods
 * of this class can be used to manage and control the created plugin framework
 * instance.
 *
 * @remarks This class is thread safe.
 */
class QEXT_OSGI_API QExtOsgiPluginFramework : public QExtOsgiPlugin
{

public:

    /**
   * Initialize this %QExtOsgiPluginFramework. After calling this method, this %QExtOsgiPluginFramework
   * must:
   * <ul>
   * <li>Be in the {@link #STARTING} state.</li>
   * <li>Have a valid Plugin Context.</li>
   * <li>Be at start level 0.</li>
   * <li>Have event handling enabled.</li>
   * <li>Have create QExtOsgiPlugin objects for all installed plugins.</li>
   * <li>Have registered any framework services.</li>
   * </ul>
   *
   * <p>
   * This %QExtOsgiPluginFramework will not actually be started until {@link #start() start}
   * is called.
   *
   * <p>
   * This method does nothing if called when this %QExtOsgiPluginFramework is in the
   * {@link #STARTING}, {@link #ACTIVE} or {@link #STOPPING} states.
   *
   * @throws QExtOsgiPluginException If this %QExtOsgiPluginFramework could not be initialized.
   */
    void init();

    /**
   * Wait until this %QExtOsgiPluginFramework has completely stopped. The <code>stop</code>
   * and <code>update</code> methods perform an asynchronous
   * stop of the Framework. This method can be used to wait until the
   * asynchronous stop of this Framework has completed. This method will only
   * wait if called when this Framework is in the {@link #STARTING},
   * {@link #ACTIVE}, or {@link #STOPPING} states. Otherwise it will return
   * immediately.
   * <p>
   * A Framework Event is returned to indicate why this Framework has stopped.
   *
   * @param timeout Maximum number of milliseconds to wait until this
   *        Framework has completely stopped. A value of zero will wait
   *        indefinitely.
   * @return A Framework Event indicating the reason this method returned. The
   *         following <code>QExtOsgiPluginFrameworkEvent</code> types may be returned by
   *         this method.
   *         <ul>
   *         <li>{@link QExtOsgiPluginFrameworkEvent#FRAMEWORK_STOPPED STOPPED} - This Framework has
   *         been stopped. </li>
   *
   *         <li>{@link QExtOsgiPluginFrameworkEvent#FRAMEWORK_STOPPED_UPDATE STOPPED_UPDATE} - This
   *         Framework has been updated which has shutdown and will now
   *         restart.</li>
   *
   *         <li>{@link QExtOsgiPluginFrameworkEvent#PLUGIN_ERROR ERROR} - The Framework
   *         encountered an error while shutting down or an error has occurred
   *         which forced the framework to shutdown. </li>
   *
   *         <li> {@link QExtOsgiPluginFrameworkEvent#FRAMEWORK_WAIT_TIMEDOUT WAIT_TIMEDOUT} - This
   *         method has timed out and returned before this Framework has
   *         stopped.</li>
   *         </ul>
   */
    QExtOsgiPluginFrameworkEvent waitForStop(unsigned long timeout);

    /**
   * Start this %QExtOsgiPluginFramework.
   *
   * <p>
   * The following steps are taken to start this %QExtOsgiPluginFramework:
   * <ol>
   * <li>If this %QExtOsgiPluginFramework is not in the {@link #STARTING} state,
   * {@link #init() initialize} this %QExtOsgiPluginFramework.</li>
   * <li>All installed plugins must be started in accordance with each
   * plugin's persistent <i>autostart setting</i>. This means some plugins
   * will not be started, some will be started with <i>lazy activation</i>
   * and some will be started with their <i>declared activation</i> policy.
   * Any exceptions that occur during plugin starting must be wrapped in a
   * {@link QExtOsgiPluginException} and then published as a plugin framework event of type
   * {@link QExtOsgiPluginFrameworkEvent::PLUGIN_ERROR}</li>
   * <li>This %PluinFramework's state is set to {@link #ACTIVE}.</li>
   * <li>A plugin framework event of type {@link QExtOsgiPluginFrameworkEvent::FRAMEWORK_STARTED} is fired</li>
   * </ol>
   *
   * @param options Ignored. There are no start options for the %QExtOsgiPluginFramework.
   * @throws QExtOsgiPluginException If this %QExtOsgiPluginFramework could not be started.
   */
    void start(const QExtOsgiPlugin::StartOptions& options = QExtOsgiPlugin::StartOptions());

    /**
   * Stop this %QExtOsgiPluginFramework.
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
   * during plugin stopping must be wrapped in a {@link QExtOsgiPluginException} and
   * then published as a framework event of type {@link QExtOsgiPluginFrameworkEvent#PLUGIN_ERROR}</li>
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
   * @throws QExtOsgiPluginException If stopping this Framework could not be
   *         initiated.
   * @see "Start Level Service Specification"
   */
    void stop(const QExtOsgiPlugin::StopOptions& options = QExtOsgiPlugin::StopOptions());

    /**
   * The %QExtOsgiPluginFramework cannot be uninstalled.
   *
   * <p>
   * This method always throws a QExtOsgiPluginException.
   *
   * @throws QExtOsgiPluginException This Framework cannot be uninstalled.
   */
    void uninstall();

    /**
   * @see QExtOsgiPlugin::getHeaders()
   */
    QHash<QString, QString> getHeaders();

    /**
   * @see QExtOsgiPlugin::getResourceList()
   */
    QStringList getResourceList(const QString& path) const;

    /**
   * @see QExtOsgiPlugin::getResource()
   */
    QByteArray getResource(const QString& path) const;

protected:

    friend class QExtOsgiPluginFrameworkContext;

    QExtOsgiPluginFramework();

private:
    Q_DECLARE_PRIVATE(QExtOsgiPluginFramework)
    Q_DISABLE_COPY(QExtOsgiPluginFramework)
};


#endif // _QEXTOSGIPLUGINFRAMEWORK_H
