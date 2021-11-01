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

#ifndef QTKPLUGIN_H
#define QTKPLUGIN_H

#include "qtkpluginframework_global.h"
#include "qtkversion.h"
#include "qtkpluginconstants.h"
#include "qtkpluginlocalization.h"
#include "Service/Log/qtklogstream.h"

#include <QHash>
#include <QWeakPointer>
#include <QMetaType>
#include <QUrl>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

class QTKPluginFrameworkContext;
class QTKPluginContext;
class QTKPluginArchive;
class QTKPluginPrivate;

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKPlugin class
 * An installed plugin in the Framework.
 *
 * <p>
 * A <code>%QTKPlugin</code> object is the access point to define the lifecycle of
 * an installed plugin. Each plugin installed in the plugin environment must have
 * an associated <code>%QTKPlugin</code> object.
 *
 * <p>
 * A plugin must have a unique identity, a <code>long</code>, chosen by the
 * Framework. This identity must not change during the lifecycle of a plugin,
 * even when the plugin is updated. Uninstalling and then reinstalling the
 * plugin must create a new unique identity.
 *
 * <p>
 * A plugin can be in one of six states:
 * <ul>
 * <li>{@link #State_Uninstalled}
 * <li>{@link #State_Installed}
 * <li>{@link #State_Resolved}
 * <li>{@link #State_Starting}
 * <li>{@link #State_Stopping}
 * <li>{@link #State_Active}
 * </ul>
 * <p>
 * They can be ORed together using the <code>States</code> type to
 * determine if a plugin is in one of the valid states.
 *
 * <p>
 * A plugin should only execute code when its state is one of
 * <code>State_Starting</code>, <code>State_Active</code>, or <code>State_Stopping</code>.
 * An <code>State_Uninstalled</code> plugin can not be set to another state; it is a
 * zombie and can only be reached because references are kept somewhere.
 *
 * <p>
 * The Framework is the only entity that is allowed to create
 * <code>%QTKPlugin</code> objects, and these objects are only valid within the
 * Framework that created them.
 *
 * @remarks This class is thread safe.
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKPlugin
{
public:
    enum State {
        /**
         * The plugin is uninstalled and may not be used.
         *
         * <p>
         * The <code>State_Uninstalled</code> state is only visible after a plugin is
         * uninstalled; the plugin is in an unusable state but references to the
         * <code>%QTKPlugin</code> object may still be available and used for
         * introspection.
         */
        State_Uninstalled = 0x00000001,

        /**
         * The plugin is installed but not yet resolved.
         *
         * <p>
         * A plugin is in the <code>State_Installed</code> state when it has been
         * installed in the Framework but is not or cannot be resolved.
         * <p>
         * This state is visible if the plugin's code dependencies are not resolved.
         * The Framework may attempt to resolve an <code>State_Installed</code> plugin's
         * code dependencies and move the plugin to the <code>State_Resolved</code>
         * state.
         */
        State_Installed = 0x00000002,

        /**
         * The plugin is resolved and is able to be started.
         *
         * <p>
         * A plugin is in the <code>State_Resolved</code> state when the Framework has
         * successfully resolved the plugin's code dependencies. These dependencies
         * include:
         * <ul>
         * <li>The plugin's required plugin dependencies from its
         * {@link QTKPluginConstants::REQUIRE_PLUGIN} Manifest header.
         * </ul>
         * <p>
         * Note that the plugin is not active yet. A plugin must be put in the
         * <code>State_Resolved</code> state before it can be started. The Framework may
         * attempt to resolve a plugin at any time.
         */
        State_Resolved = 0x00000004,

        /**
         * The plugin is in the process of starting.
         *
         * <p>
         * A plugin is in the <code>State_Starting</code> state when its
         * {@link #start(const StartOptions&) start} method is active. A plugin must be in this
         * state when the plugin's {@link QTKPluginActivator::start} method is called. If the
         * <code>QTKPluginActivator::start</code> method completes without exception,
         * then the plugin has successfully started and must move to the
         * <code>State_Active</code> state.
         * <p>
         * If the plugin does not have a
         * {@link QTKPluginConstants#ACTIVATION_EAGER eager activation policy}, then the
         * plugin may remain in this state for some time until the activation is
         * triggered.
         */
        State_Starting = 0x00000008,

        /**
         * The plugin is in the process of stopping.
         *
         * <p>
         * A plugin is in the <code>State_Stopping</code> state when its
         * {@link #stop(const StopOptions&) stop} method is active. A plugin must be in this state
         * when the plugin's {@link QTKPluginActivator::stop} method is called. When the
         * <code>QTKPluginActivator::stop</code> method completes the plugin is
         * stopped and must move to the <code>State_Resolved</code> state.
         */
        State_Stopping = 0x00000010,

        /**
         * The plugin is now running.
         *
         * <p>
         * A plugin is in the <code>State_Active</code> state when it has been
         * successfully started and activated.
         */
        State_Active = 0x00000020
    };
    /**
     * Represents an ORed combination of plugin states.
     *
     * @see #State
     */
    Q_DECLARE_FLAGS(States, State)

    enum StartOption {
        /**
         * The plugin start operation is transient and the persistent autostart
         * setting of the plugin is not modified.
         *
         * <p>
         * This option may be set when calling {@link #start(const StartOptions&)} to notify the
         * framework that the autostart setting of the plugin must not be modified.
         * If this option is not set, then the autostart setting of the plugin is
         * modified.
         *
         * @see #start(const StartOptions&)
         */
        StartOption_StartTransient = 0x00000001,

        /**
         * The plugin start operation must activate the plugin according to the
         * plugin's declared
         * {@link QTKPluginConstants#PLUGIN_ACTIVATIONPOLICY activation policy}.
         *
         * <p>
         * This bit may be set when calling {@link #start(const StartOptions&)} to notify the
         * framework that the plugin must be activated using the plugin's declared
         * activation policy.
         *
         * @see QTKPluginConstants#PLUGIN_ACTIVATIONPOLICY
         * @see #start(const StartOptions&)
         */
        StartOption_StartActivationPolicy = 0x00000002
    };
    /**
     * Represents an ORed combination of start options.
     *
     * @see #StartOption
     */
    Q_DECLARE_FLAGS(StartOptions, StartOption)

    enum StopOption {
        /**
         * The plugin stop is transient and the persistent autostart setting of the
         * plugin is not modified.
         *
         * <p>
         * This option may be set when calling {@link #stop(const StopOptions&)} to notify the
         * framework that the autostart setting of the plugin must not be modified.
         * If this option is not set, then the autostart setting of the plugin is
         * modified.
         *
         * @see #stop(const StopOptions&)
         */
        StopOption_StopTransient = 0x00000001
    };
    /**
     * Represents an ORed combination of stop options.
     *
     * @see #StopOption
     */
    Q_DECLARE_FLAGS(StopOptions, StopOption)

    virtual ~QTKPlugin();

    /**
     * @brief getState
     * Returns this plugin's current state.
     *
     * <p>
     * A plugin can be in only one state at any time.
     *
     * @return An element of <code>State_Uninstalled</code>,<code>State_Installed</code>,
     *         <code>State_Resolved</code>,<code>State_Starting</code>,
     *         <code>State_Stopping</code>,<code>State_Active</code>.
     */
    State getState() const;


    /**
     * Updates this plugin from a <code>QUrl</code>.
     *
     * <p>
     * If the specified <code>QURl</code> is <code>empty</code>, the
     * Framework creates the <code>QUrl</code> from which to read the
     * updated plugin by interpreting, in an implementation dependent manner,
     * this plugin's {@link QTKPluginConstants#PLUGIN_UPDATELOCATION
     * Plugin-UpdateLocation} Manifest header, if present, or this plugin's
     * original location.
     *
     * <p>
     * If this plugin's state is <code>State_Active</code>, it must be stopped before
     * the update and started after the update successfully completes.
     *
     * <p>
     * If this plugin has exported any classes that are used by another
     * plugin, these classes remain available until the Framework is relaunched.
     *
     * <p>
     * The following steps are required to update a plugin:
     * <ol>
     * <li>If this plugin's state is <code>State_Uninstalled</code> then an
     * <code>QTKIllegalStateException</code> is thrown.
     *
     * <li>If this plugin's state is <code>State_Active</code>, <code>State_Starting</code>
     * or <code>State_Stopping</code>, this plugin is stopped as described in the
     * <code>QTKPlugin::stop()</code> method. If <code>QTKPlugin::stop()</code> throws an
     * exception, the exception is rethrown terminating the update.
     *
     * <li>The updated version of this plugin is read from the URL and
     * installed. If the Framework is unable to install the updated version of
     * this plugin, the original version of this plugin is restored and a
     * <code>QTKPluginException</code> is thrown after completion of the
     * remaining steps.
     *
     * <li>This plugin's state is set to <code>State_Installed</code>.
     *
     * <li>If the updated version of this plugin was successfully installed, a
     * plugin event of type {@link QTKPluginEvent#UPDATED} is fired.
     *
     * <li>If this plugin's state was originally <code>State_Active</code>, the
     * updated plugin is started as described in the <code>QTKPlugin::start()</code>
     * method. If <code>QTKPlugin::start()</code> throws an exception, a Framework
     * event of type {@link QTKPluginFrameworkEvent#Type_PluginError} is fired containing the
     * exception.
     * </ol>
     *
     * <b>Preconditions </b>
     * <ul>
     * <li><code>getState()</code> not in &#x007B; <code>State_Uninstalled</code>
     * &#x007D;.
     * </ul>
     * <b>Postconditions, no exceptions thrown </b>
     * <ul>
     * <li><code>getState()</code> in &#x007B; <code>State_Installed</code>,
     * <code>State_Resolved</code>, <code>State_Active</code> &#x007D;.
     * <li>This plugin has been updated.
     * </ul>
     * <b>Postconditions, when an exception is thrown </b>
     * <ul>
     * <li><code>getState()</code> in &#x007B; <code>State_Installed</code>,
     * <code>State_Resolved</code>, <code>State_Active</code> &#x007D;.
     * <li>Original plugin is still used; no update occurred.
     * </ul>
     *
     * @param updateLocation The <code>QUrl</code> from which to read the new
     *        plugin or <code>null</code> to indicate the Framework must create
     *        the URL from this plugin's
     *        {@link QTKPluginConstants#PLUGIN_UPDATELOCATION Plugin-UpdateLocation}
     *        Manifest header, if present, or this plugin's original location.
     * @throws QTKPluginException If the update location cannot be read or the update
     *         fails.
     * @throws QTKIllegalStateException If this plugin has been uninstalled or this
     *         plugin tries to change its own state.
     * @see #stop()
     * @see #start()
     */
    void update(const QUrl &updateLocation = QUrl());

    /**
     * Returns this plugin's {@link QTKPluginContext}. The returned
     * <code>QTKPluginContext</code> can be used by the caller to act on behalf
     * of this plugin.
     *
     * <p>
     * If this plugin is not in the {@link #State_Starting}, {@link #State_Active}, or
     * {@link #State_Stopping} states, then this
     * plugin has no valid <code>QTKPluginContext</code>. This method will
     * return <code>0</code> if this plugin has no valid
     * <code>QTKPluginContext</code>.
     *
     * @return A <code>QTKPluginContext</code> for this plugin or
     *         <code>0</code> if this plugin has no valid
     *         <code>QTKPluginContext</code>.
     */
    QTKPluginContext *getPluginContext() const;

    /**
     * Returns this plugin's unique identifier. This plugin is assigned a unique
     * identifier by the Framework when it was installed in the plugin
     * environment.
     *
     * <p>
     * A plugin's unique identifier has the following attributes:
     * <ul>
     * <li>Is unique and persistent.
     * <li>Is a <code>long</code>.
     * <li>Its value is not reused for another plugin, even after a plugin is
     * uninstalled.
     * <li>Does not change while a plugin remains installed.
     * <li>Does not change when a plugin is updated.
     * </ul>
     *
     * <p>
     * This method must continue to return this plugin's unique identifier while
     * this plugin is in the <code>State_Uninstalled</code> state.
     *
     * @return The unique identifier of this plugin.
     */
    long getPluginId() const;

    /**
     * Returns this plugin's location identifier.
     *
     * <p>
     * The location identifier is the location passed to
     * <code>QTKPluginContext::installPlugin</code> when a plugin is installed.
     * The location identifier does not change while this plugin remains
     * installed, even if this plugin is updated.
     *
     * <p>
     * This method must continue to return this plugin's location identifier
     * while this plugin is in the <code>State_Uninstalled</code> state.
     *
     * @return The string representation of this plugin's location identifier.
     */
    QString getLocation() const;

    /**
     * Returns the version of this plugin as specified by its
     * <code>Plugin-Version</code> manifest header. If this plugin does not have a
     * specified version then {@link QTKVersion#emptyVersion} is returned.
     *
     * <p>
     * This method must continue to return this plugin's version while
     * this plugin is in the <code>State_Uninstalled</code> state.
     *
     * @return The version of this plugin.
     */
    QTKVersion getVersion() const;

    /**
     * Returns the symbolic name of this plugin as specified by its
     * <code>Plugin-SymbolicName</code> manifest header. The plugin symbolic
     * name together with a version must identify a unique plugin. The plugin
     * symbolic name should be based on the reverse domain name naming
     * convention like that used for java packages.
     *
     * <p>
     * This method must continue to return this plugin's symbolic name while
     * this plugin is in the <code>State_Uninstalled</code> state.
     *
     * @return The symbolic name of this plugin or a null QString if this
     *         plugin does not have a symbolic name.
     */
    QString getSymbolicName() const;

    /**
     * Returns a <code>QTKPluginLocalization</code> object for the
     * specified <code>locale</code>. The translations are loaded from a
     * .qm file starting with <code>base</code>.
     *
     * You can use the returned <code>QTKPluginLocalization</code>
     * object to dynamically translate text without changing the current
     * locale of the application. This can be used for example to
     * provide localized messages to multiple users which use the application
     * (maybe some kind of server) simultaneously but require different
     * localizations.
     *
     * @param locale The locale to be used by the returned
     *        <code>QTKPluginLocalization</code> object.
     * @param base The base name of the .qm message file which contains
     *        translated messages. Defaults to
     *        <code>QTKPluginConstants::PLUGIN_LOCALIZATION_DEFAULT_BASENAME</code>.
     * @return A locale specific <code>QTKPluginLocalization</code> instance.
     */
    QTKPluginLocalization getPluginLocalization(const QLocale &locale,
                                                const QString &strBase = QTKPluginConstants::PLUGIN_LOCALIZATION_DEFAULT_BASENAME) const;
    /**
     * @brief start
     * Starts this plugin.
     *
     * <p>
     * If this plugin's state is <code>State_Uninstalled</code> then an
     * <code>QTKIllegalStateException</code> is thrown.
     * <p>
     * The following steps are required to start this bundle:
     * <ol>
     * <li>If this plugin is in the process of being activated or deactivated
     * then this method must wait for activation or deactivation to complete
     * before continuing. If this does not occur in a reasonable time, a
     * <code>QTKPluginException</code> is thrown to indicate this plugin was unable
     * to be started.
     *
     * <li>If this plugin's state is <code>State_Active</code> then this method
     * returns immediately.
     *
     * <li>If the {@link #StartOption_StartTransient} option is not set then set this
     * plugin's autostart setting to <em>Started with declared activation</em>
     * if the {@link #StartOption_StartActivationPolicy} option is set or
     * <em>Started with lazy activation</em> if not set. When the Framework is
     * restarted and this plugin's autostart setting is not <em>Stopped</em>,
     * this plugin must be automatically started.
     *
     * <li>If this plugin's state is not <code>State_Resolved</code>, an attempt is
     * made to resolve this plugin. If the Framework cannot resolve this plugin,
     * a <code>QTKPluginException</code> is thrown.
     *
     * <li>If the {@link #StartOption_StartActivationPolicy} option is not set then:
     * <ul>
     * <li>If this plugin's state is <code>State_Starting</code> then this method
     * returns immediately.
     * <li>This plugin's state is set to <code>State_Starting</code>.
     * <li>A plugin event of type {@link QTKPluginEvent::LAZY_ACTIVATION} is fired.
     * <li>This method returns immediately and the remaining steps will be
     * followed when this plugin's activation is later triggered.
     * </ul>
     * If the {@link #StartOption_StartActivationPolicy} option is set and this
     * plugin's declared activation policy is {@link QTKPluginConstants#ACTIVATION_EAGER
     * eager} then:
     * <i></i>
     * <li>This plugin's state is set to <code>State_Starting</code>.
     *
     * <li>A plugin event of type {@link QTKPluginEvent::State_Starting} is fired.
     *
     * <li>The {@link QTKPluginActivator::start} method of this plugin's
     * <code>QTKPluginActivator</code>, is called. If the
     * <code>QTKPluginActivator</code> throws an exception then:
     * <ul>
     * <li>This plugin's state is set to <code>State_Stopping</code>.
     * <li>A plugin event of type {@link QTKPluginEvent::State_Stopping} is fired.
     * <li>Any services registered by this plugin must be unregistered.
     * <li>Any services used by this plugin must be released.
     * <li>Any listeners registered by this plugin must be removed.
     * <li>This plugin's state is set to <code>State_Resolved</code>.
     * <li>A plugin event of type {@link QTKPluginEvent::STOPPED} is fired.
     * <li>A <code>QTKPluginException</code> is then thrown.
     * </ul>
     * <i></i>
     * <li>If this plugin's state is <code>State_Uninstalled</code>, because this
     * plugin was uninstalled while the <code>QTKPluginActivator::start</code>
     * method was running, a <code>QTKPluginException</code> is thrown.
     *
     * <li>This plugin's state is set to <code>State_Active</code>.
     *
     * <li>A plugin event of type {@link QTKPluginEvent::STARTED} is fired.
     * </ol>
     *
     * <b>Preconditions </b>
     * <ul>
     * <li><code>getState()</code> in { <code>State_Installed</code>,
     * <code>State_Resolved</code>, <code>State_Starting</code> }
     * or { <code>State_Installed</code>, <code>State_Resolved</code> }
     * if this plugin has a eager activation policy.
     * </ul>
     * <b>Postconditions, no exceptions thrown </b>
     * <ul>
     * <li>Plugin autostart setting is modified unless the
     * {@link #StartOption_StartTransient} option was set.
     * <li><code>getState()</code> in { <code>State_Active</code> }
     * if the eager activation policy was used.
     * <li><code>QTKPluginActivator::start()</code> has been called and did not
     * throw an exception if the eager policy was used.
     * </ul>
     * <b>Postconditions, when an exception is thrown </b>
     * <ul>
     * <li>Depending on when the exception occurred, plugin autostart setting is
     * modified unless the {@link #StartOption_StartTransient} option was set.
     * <li><code>getState()</code> not in { <code>State_Starting</code>,
     * <code>State_Active</code> }.
     * </ul>
     *
     * @param options The options for starting this plugin. See
     *        {@link #StartOption_StartTransient} and {@link #StartOption_StartActivationPolicy}. The
     *        Framework must ignore unrecognized options.
     * @throws QTKPluginException If this plugin could not be started. This could
     *         be because a code dependency could not be resolved or the
     *         <code>QTKPluginActivator</code> could not be loaded or
     *         threw an exception.
     * @throws QTKIllegalStateException If this plugin has been uninstalled or this
     *         plugin tries to change its own state.
     */
    virtual void start(const StartOptions &options = StartOption_StartActivationPolicy);

    /**
     * @brief stop
     * Stops this plugin.
     *
     * <p>
     * The following steps are required to stop a plugin:
     * <ol>
     * <li>If this plugin's state is <code>State_Uninstalled</code> then an
     * <code>QTKIllegalStateException</code> is thrown.
     *
     * <li>If this plugin is in the process of being activated or deactivated
     * then this method must wait for activation or deactivation to complete
     * before continuing. If this does not occur in a reasonable time, a
     * <code>QTKPluginException</code> is thrown to indicate this plugin was unable
     * to be stopped.
     * <li>If the {@link #StopOption_StopTransient} option is not set then then set this
     * plugin's persistent autostart setting to <em>Stopped</em>. When the
     * Framework is restarted and this plugin's autostart setting is
     * <em>Stopped</em>, this bundle must not be automatically started.
     *
     * <li>If this plugin's state is not <code>State_Starting</code> or
     * <code>State_Active</code> then this method returns immediately.
     *
     * <li>This plugin's state is set to <code>State_Stopping</code>.
     *
     * <li>A plugin event of type {@link QTKPluginEvent::State_Stopping} is fired.
     *
     * <li>If this plugin's state was <code>State_Active</code> prior to setting the
     * state to <code>State_Stopping</code>, the {@link QTKPluginActivator#stop} method
     * of this plugin's <code>QTKPluginActivator</code> is
     * called. If that method throws an exception, this method must continue to
     * stop this plugin and a <code>QTKPluginException</code> must be thrown after
     * completion of the remaining steps.
     *
     * <li>Any services registered by this plugin must be unregistered.
     * <li>Any services used by this plugin must be released.
     * <li>Any listeners registered by this plugin must be removed.
     *
     * <li>If this plugin's state is <code>State_Uninstalled</code>, because this
     * plugin was uninstalled while the <code>QTKPluginActivator::stop</code> method
     * was running, a <code>QTKPluginException</code> must be thrown.
     *
     * <li>This plugin's state is set to <code>State_Resolved</code>.
     *
     * <li>A plugin event of type {@link QTKPluginEvent::STOPPED} is fired.
     * </ol>
     *
     * <b>Preconditions </b>
     * <ul>
     * <li><code>getState()</code> in { <code>State_Active</code> }.
     * </ul>
     * <b>Postconditions, no exceptions thrown </b>
     * <ul>
     * <li>Plugin autostart setting is modified unless the
     * {@link #StopOption_StopTransient} option was set.
     * <li><code>getState()</code> not in &#123; <code>State_Active</code>,
     * <code>State_Stopping</code> &#125;.
     * <li><code>QTKPluginActivator::stop</code> has been called and did not throw
     * an exception.
     * </ul>
     * <b>Postconditions, when an exception is thrown </b>
     * <ul>
     * <li>Plugin autostart setting is modified unless the
     * {@link #StopOption_StopTransient} option was set.
     * </ul>
     *
     * @param options The options for stoping this bundle. See
     *        {@link #StopOption_StopTransient}.
     * @throws QTKPluginException If this plugin's <code>QTKPluginActivator</code>
     *         threw an exception.
     * @throws QTKIllegalStateException If this plugin has been uninstalled or this
     *         plugin tries to change its own state.
     */
    virtual void stop(const StopOptions &options = 0);


    /**
     * Uninstalls this plugin.
     *
     * <p>
     * This method causes the Plugin Framework to notify other plugins that this
     * plugin is being uninstalled, and then puts this plugin into the
     * <code>State_Uninstalled</code> state. The Framework must remove any resources
     * related to this plugin that it is able to remove.
     *
     * <p>
     * If this plugin is required by other plugins which are already resolved,
     * the Framework must keep this plugin loaded until the
     * Framework is relaunched.
     *
     * <p>
     * The following steps are required to uninstall a plugin:
     * <ol>
     * <li>If this plugin's state is <code>State_Uninstalled</code> then an
     * <code>QTKIllegalStateException</code> is thrown.
     *
     * <li>If this plugin's state is <code>State_Active</code>, <code>State_Starting</code>
     * or <code>State_Stopping</code>, this plugin is stopped as described in the
     * <code>QTKPlugin::stop</code> method. If <code>QTKPlugin::stop</code> throws an
     * exception, a Framework event of type QTKPluginFrameworkEvent::Type_PluginError is
     * fired containing the exception.
     *
     * <li>This plugin's state is set to <code>State_Uninstalled</code>.
     *
     * <li>A plugin event of type QTKPluginEvent::State_Uninstalled is fired.
     *
     * <li>This plugin and any persistent storage area provided for this plugin
     * by the Framework are removed.
     * </ol>
     *
     * <b>Preconditions </b>
     * <ul>
     * <li><code>getState()</code> not in &#123; <code>State_Uninstalled</code>
     * &#125;.
     * </ul>
     * <b>Postconditions, no exceptions thrown </b>
     * <ul>
     * <li><code>getState()</code> in &#123; <code>State_Uninstalled</code>
     * &#125;.
     * <li>This plugin has been uninstalled.
     * </ul>
     * <b>Postconditions, when an exception is thrown </b>
     * <ul>
     * <li><code>getState()</code> not in &#123; <code>State_Uninstalled</code>
     * &#125;.
     * <li>This plugin has not been uninstalled.
     * </ul>
     *
     * @throws QTKPluginException If the uninstall failed. This can occur if
     *         another thread is attempting to change this plugin's state and
     *         does not complete in a timely manner.
     * @throws QTKIllegalStateException If this plugin has been uninstalled or this
     *         plugin tries to change its own state.
     * @see #stop()
     */
    virtual void uninstall();

    /**
     * Returns this plugin's Manifest headers and values. This method returns
     * all the Manifest headers and values from the main section of this
     * bundle's Manifest file; that is, all lines prior to the first named section.
     *
     * TODO: documentation about manifest value internationalization
     *
     * <p>
     * For example, the following Manifest headers and values are included if
     * they are present in the Manifest file:
     *
     * <pre>
     *     Plugin-Name
     *     Plugin-Vendor
     *     Plugin-QTKVersion
     *     Plugin-Description
     *     Plugin-DocURL
     *     Plugin-ContactAddress
     * </pre>
     *
     * <p>
     * This method must continue to return Manifest header information while
     * this plugin is in the <code>State_Uninstalled</code> state.
     *
     * @return A <code>QHash<Qstring, QString></code> object containing this plugin's
     *         Manifest headers and values.
     */
    virtual QHash<QString, QString> getHeaders();

    /**
     * Returns a list of all the files and directories
     * within this plugin whose longest sub-path matches the
     * specified path.
     * <p>
     * The specified path is always relative to the root of this plugin
     * (the plugins symbolic name) and may begin with a &quot;/&quot;.
     * A path value of &quot;/&quot; indicates the root of this plugin.
     * <p>
     * Returned paths indicating subdirectory paths end with a &quot;/&quot;.
     * The returned paths are all relative to the root of this plugin and must
     * not begin with &quot;/&quot;.
     * <p>
     *
     * @param path The path name for which to return resource paths.
     * @return A list of the resource paths (<code>QString</code>
     *         objects) or an empty list if no entry could be found.

     * @throws QTKIllegalStateException If this plugin has been
     *         uninstalled.
     */
    virtual QStringList getResourceList(const QString &strPath) const;

    /**
     * Returns a list of resources in this plugin.
     *
     * <p>
     * This method is intended to be used to obtain configuration, setup,
     * localization and other information from this plugin. This method can
     * either return only entries in the specified path or recurse into
     * subdirectories returning entries in the directory tree beginning at the
     * specified path.
     *
     * <p>
     * Examples:
     *
     * @code
     * // List all XML files in the OSGI-INF directory and below
     * QStringList r = b->findResources(&quot;OSGI-INF&quot;, &quot;*.xml&quot;, true);
     *
     * // Find a specific localization file
     * QStringList r = b->findResources(&quot;OSGI-INF/l10n&quot;, &quot;plugin_nl_DU.tm&quot;, false);
     * @endcode
     *
     * @param path The path name in which to look. The path is always relative
     *        to the root of this plugin and may begin with &quot;/&quot;. A
     *        path value of &quot;/&quot; indicates the root of this plugin.
     * @param filePattern The file name pattern for selecting entries in the
     *        specified path. The pattern is only matched against the last
     *        element of the entry path. Substring matching is supported, as
     *        specified in the Filter specification, using the wildcard
     *        character (&quot;*&quot;). If a null QString is specified, this
     *        is equivalent to &quot;*&quot; and matches all files.
     * @param recurse If <code>true</code>, recurse into subdirectories.
     *        Otherwise only return entries from the specified path.
     * @return A list of QString objects for each matching entry, or
     *         an empty list if an entry could not be found or if the caller
     *         does not have the appropriate
     *         <code>AdminPermission[this,RESOURCE]</code>, and the Plugin
     *         Framework supports permissions.
     * @throws QTKIllegalStateException If this plugin has been uninstalled.
     */
    virtual QStringList findResources(const QString &strPath, const QString &strFilePattern, bool bRecurse) const;

    /**
     * Returns a QByteArray containing a Qt resource located at the
     * specified path in this plugin.
     * <p>
     * The specified path is always relative to the root of this plugin
     * (the plugins symbolic name) and may
     * begin with &quot;/&quot;. A path value of &quot;/&quot; indicates the
     * root of this plugin.
     * <p>
     *
     * @param path The path name of the resource.
     * @return A QByteArray to the resource, or a null QByteArray if no resource could be
     *         found.
     * @throws QTKIllegalStateException If this plugin has been
     *         uninstalled.
     */
    virtual QByteArray getResource(const QString &strPath) const;

protected:
    friend class QTKPluginFramework;
    friend class QTKPluginFrameworkLauncherPrivate;
    friend class QTKPluginFrameworkPrivate;
    friend class QTKPluginFrameworkContext;
    friend class QTKPlugins;
    friend class QTKServiceReferencePrivate;

    QTKPlugin();
    void init(QTKPluginPrivate *pPrivate);
    void init(const QWeakPointer<QTKPlugin> &self, QTKPluginFrameworkContext *pPFWContext,
              QSharedPointer<QTKPluginArchive> pPluginArchive);

    // Do NOT change this to QScopedPointer<QTKPluginPrivate>!
    // We would need to include QTKPlugin.h (and QTKPluginPrivate_p.h)
    // at a lot of places...
    QTKPluginPrivate *d_ptr;

private:
    Q_DECLARE_PRIVATE(QTKPlugin)
    Q_DISABLE_COPY(QTKPlugin)
};

QTK_PLUGINFRAMEWORK_END_NAMESPACE

QTK_PLUGINFRAMEWORK_EXPORT QDebug operator<<(QDebug debug, QTK_PLUGINFRAMEWORK_NAMESPACE::QTKPlugin::State state);
QTK_PLUGINFRAMEWORK_EXPORT QDebug operator<<(QDebug debug, const QTK_PLUGINFRAMEWORK_NAMESPACE::QTKPlugin &plugin);
QTK_PLUGINFRAMEWORK_EXPORT QDebug operator<<(QDebug debug, QTK_PLUGINFRAMEWORK_NAMESPACE::QTKPlugin const *pPlugin);

QTK_PLUGINFRAMEWORK_EXPORT QTK_PLUGINFRAMEWORK_NAMESPACE::QTKLogStream& operator<<(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKLogStream &stream, QTK_PLUGINFRAMEWORK_NAMESPACE::QTKPlugin const *pPlugin);
QTK_PLUGINFRAMEWORK_EXPORT QTK_PLUGINFRAMEWORK_NAMESPACE::QTKLogStream& operator<<(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKLogStream &stream, const QSharedPointer<QTK_PLUGINFRAMEWORK_NAMESPACE::QTKPlugin> &plugin);

Q_DECLARE_OPERATORS_FOR_FLAGS(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKPlugin::States)
Q_DECLARE_OPERATORS_FOR_FLAGS(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKPlugin::StartOptions)
Q_DECLARE_OPERATORS_FOR_FLAGS(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKPlugin::StopOptions)

Q_DECLARE_METATYPE(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKPlugin*)
Q_DECLARE_METATYPE(QSharedPointer<QTK_PLUGINFRAMEWORK_NAMESPACE::QTKPlugin>)

#endif // QTKPLUGIN_H
