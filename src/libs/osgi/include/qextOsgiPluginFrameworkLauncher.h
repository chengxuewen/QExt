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

#ifndef QTKPLUGINFRAMEWORKLAUNCHER_H
#define QTKPLUGINFRAMEWORKLAUNCHER_H

#include "qtkpluginframework_global.h"
#include "qtkpluginframework.h"

#include <QString>
#include <QSharedPointer>

class QRunnable;

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

class QTKPluginFrameworkLauncherPrivate;

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKPluginFrameworkLauncher class
 * Sets up and starts the QTK Plugin Framework.
 *
 * This is a convenience class to start an instance of the QTK Plugin
 * Framework and to install and start plugins.
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKPluginFrameworkLauncher
{
public:
    /**
     * @brief setFrameworkProperties
     * Specify the set of framework properties to be used when
     * initializing the Plugin Framework.
     *
     * <p>
     * If the framework has already been initialized by a call
     * to #install or #start, the
     * new properties do not have any effect until the framework
     * is restarted.
     *
     * @param properties The initial Plugin Framework properties.
     */
    static void setFrameworkProperties(const QTKProperties &properties);

    /**
     * @brief run
     * Launches the platform and runs a single application. The application is either identified
     * in the given arguments (e.g., -application &lt;app id&gt;) or in the <code>eclipse.application</code>
     * System property.  This convenience method starts
     * up the platform, runs the indicated application, and then shuts down the
     * platform. The platform must not be running already.
     *
     * @param pEndSplashHandler the block of code to run to tear down the splash
     * 	screen or <code>null</code> if no tear down is required
     * @param argument the argument passed to the application. Default is QVariant().
     * @return the result of running the application
     * @throws Exception if anything goes wrong
     */
    static QVariant run(QRunnable *pEndSplashHandler = nullptr, const QVariant &argument = QVariant());

    /**
     * @brief run
     * Runs the application for which the platform was started. The platform
     * must be running.
     * <p>
     * The given argument is passed to the application being run.  If it is <code>null</code>
     * then the command line arguments used in starting the platform, and not consumed
     * by the platform code, are passed to the application as a <code>String[]</code>.
     * </p>
     * @param argument the argument passed to the application. May be <code>null</code>
     * @return the result of running the application
     * @throws std::exception if anything goes wrong
     */
    static QVariant run(const QVariant &argument);

    /**
     * @brief startup
     * Starts the platform and sets it up to run a single application. The application is either identified
     * in the given arguments (e.g., -application &lt;app id&gt;) or in the <code>eclipse.application</code>
     * System property.  The platform must not be running already.
     * <p>
     * The given runnable (if not <code>null</code>) is used to tear down the splash screen if required.
     * </p>
     * @param pEndSplashHandler the arguments passed to the application
     * @return BundleContext the context of the system bundle
     * @throws Exception if anything goes wrong
     */
    static QTKPluginContext* startup(QRunnable *pEndSplashHandler);

    /**
     * @brief shutdown
     * Shuts down the Platform. The state of the Platform is not automatically
     * saved before shutting down.
     * <p>
     * On return, the Platform will no longer be running (but could be re-launched
     * with another call to startup). If relaunching, care must be taken to reinitialize
     * any System properties which the platform uses (e.g., osgi.instance.area) as
     * some policies in the platform do not allow resetting of such properties on
     * subsequent runs.
     * </p><p>
     * Any objects handed out by running Platform,
     * including Platform runnables obtained via getRunnable, will be
     * permanently invalid. The effects of attempting to invoke methods
     * on invalid objects is undefined.
     * </p>
     * @throws std::exception if anything goes wrong
     */
    static void shutdown();

    /**
     * @brief install
     * Install the plugin with the given symbolic name using the provided
     * <code>QTKPluginContext</code>.
     *
     * <p>
     * This method instantiates and initializes an instance of a
     * QTKPluginFramework object, if no plugin context is provided and
     * if there is no framework already initialized.
     *
     * <p>
     * The plugin is searched in the paths previously given by calls
     * to #addSearchPath(const QString&, bool) and in the default
     * QTK plugin installation path.
     *
     * @param strSymbolicName The symbolic name of the plugin to install.
     * @param pContext The plugin context used for installing the plugin.
     * @return The plugin id if the plugin was found and successfully
     *         installed, <code>-1</code> otherwise.
     */
    static long install(const QString &strSymbolicName, QTKPluginContext *pContext = nullptr);

    /**
     * @brief start
     * This method instantiates, initializes, and starts an instance of a
     * QTKPluginFramework object, if no plugin context is provided and
     * if there is no framework already running. It then installs and
     * starts the plugin with the given symbolic name (if not empty).
     *
     * <p>
     * If a symbolic name is given, the plugin is searched in the paths previously given by calls
     * to #addSearchPath(const QString&, bool) and in the default
     * QTK plugin installation path and is started using the given <code>options</code>.
     *
     * <p>
     * If a plugin context is provided, this context is used to install the plugin,
     * otherwise the Plugin Framework context is used.
     *
     * \param & The symbolic name of the plugin to install.
     * \param options The options used to start the plugin.
     * \param pContext The plugin context to use for installing the plugin.
     * \return <code>true</code> if the plugin was found and successfully
     *         installed, <code>false</code> otherwise.
     *
     * \see QTKPlugin::StartOptions
     */
    static bool start(const QString &strSymbolicName = QString(),
                      QTKPlugin::StartOptions options = QTKPlugin::StartOption_StartActivationPolicy,
                      QTKPluginContext *pContext = nullptr);

    /**
     * @brief stop
     * This method either stops the plug-in with the given <code>symbolicName</code> using
     * the supplied stop options <code>options</code>
     * or the complete framework (if <code>symbolicName</code> is empty).
     *
     * <p>
     * If a plugin context is provided, this context is used to find the plug-in,
     * otherwise the Plugin Framework context is used.
     *
     * \param strSymbolicName The symbolic name of the plugin to stop.
     * \param options The options used to stop the plugin.
     * \param pContext The plugin context to use for finding the plugin.
     * \return <code>true</code> if the plugin was found and successfully
     *         stopped or the complete framework was successfully stopped,
     *         <code>false</code> otherwise.
     *
     * \see QTKPlugin::StopOptions
     */
    static bool stop(const QString &strSymbolicName = QString(),
                     QTKPlugin::StopOptions options = 0, QTKPluginContext *pContext = nullptr);

    /**
     * @brief resolve
     * Resolve the given plug-in.
     *
     * This method tries to resolv the given plug-in. In case of an error,
     * a framework event of type QTKPluginFrameworkEvent::PLUGIN_ERROR is send.
     *
     * @param plugin The plug-in to be resolved.
     */
    static void resolve(const QSharedPointer<QTKPlugin> &plugin);

    /**
     * @brief resolve
     * Resolve all currently installed plug-ins.
     *
     * In case of an error, a framework event of type
     * QTKPluginFrameworkEvent::PLUGIN_ERROR is send.
     */
    static void resolve();

    /**
     * @brief getPluginContext
     * Get the plugin context for the Plugin Framework.
     *
     * \return The context associated to the Plugin Framework, or <code>null</code>
     *         if the framework has not been initialized yet.
     */
    static QTKPluginContext* getPluginContext();

    /**
     * @brief getPluginFramework
     * Get the Plugin Framework:
     *
     * \return The initialized Plugin Framework, or <code>null</code> if the
     *         framework has not been initialized yet.
     */
    static QSharedPointer<QTKPluginFramework> getPluginFramework();

    /**
     * @brief appendPathEnv
     * This is a utility method to append a path to the PATH environment variable
     * on Windows platforms.
     *
     * <p>
     * This method does nothing on non-Windows platforms.
     *
     * \param strPath The path to be appended to PATH
     */
    static void appendPathEnv(const QString &strPath);

    /**
     * @brief addSearchPath
     * Add a path to the list of search paths for plugins.
     *
     * When calling #install(const QString&, QTKPluginContext*), #start, or
     * #getPluginPath(const QString&), the plugin is searched in the
     * paths given as arguments to this method. The least recently added
     * path is searched first.
     *
     * \param strSearchPath The path to add.
     * \param bAddToPathEnv If <code>true</code>, add the given path to the
     *        PATH environment variable, using #appendPathEnv(const QString&).
     */
    static void addSearchPath(const QString &strSearchPath, bool bAddToPathEnv = true);

    /**
     * @brief getPluginPath
     * Get the full path (including the file name) to the plugin with the
     * given symbolic name.
     *
     * <p>
     * The paths given by calls to #addSearchPath(const QString&, bool) are searched
     * for a shared library with a base name equaling <code>symbolicName</code>.
     *
     * \param strSymbolicName The symbolic name of the plugin to find.
     * \return The full path (including the file name) to the plugin (shared library)
     *         or a null QString if the plugin was not found.
     */
    static QString getPluginPath(const QString &strSymbolicName);

    /**
     * @brief getPluginSymbolicNames
     * Get a list of symbolic names for the plugins in <code>searchPath</code>.
     *
     * <p>
     * The symbolic names are deduced from the shared libraries found in
     * <code>searchPath</code>, which may not represent loadable QTK plugins.
     *
     * \param strSearchPath The path to look for plugins.
     * \return A list of potential plugin symbolic names.
     */
    static QStringList getPluginSymbolicNames(const QString &strSearchPath);

    // System properties
    static const char *PROPERTIE_USER_HOME; // = "user.home";
    static const char *PROPERTIE_USER_DIR; // = "user.dir";

    // Framework properties
    static const char *PROPERTIE_PLUGINS; // = "QTK.plugins";
    static const char *PROPERTIE_PLUGINS_STARTOPTIONS; // = "QTK.plugins.startOptions";
    static const char *PROPERTIE_DEBUG; // = "QTK.debug";
    static const char *PROPERTIE_DEV; // = "QTK.dev";
    static const char *PROPERTIE_CONSOLE; // = "QTK.console";
    static const char *PROPERTIE_OS; // = "QTK.os";
    static const char *PROPERTIE_ARCH; // = "QTK.arch";

    static const char *PROPERTIE_NOSHUTDOWN; // = "QTK.noShutdown";
    static const char *PROPERTIE_IGNOREAPP; // = "QTK.ignoreApp";

    static const char *PROPERTIE_INSTALL_AREA; // = "QTK.install.area";
    static const char *PROPERTIE_CONFIGURATION_AREA; // = "QTK.configuration.area";
    static const char *PROPERTIE_SHAREDCONFIGURATION_AREA; // = "QTK.sharedConfiguration.area";
    static const char *PROPERTIE_INSTANCE_AREA; // = "QTK.instance.area";
    static const char *PROPERTIE_USER_AREA; // = "QTK.user.area";
    static const char *PROPERTIE_HOME_LOCATION; // = "QTK.home.location";

    static const char *PROPERTIE_CONFIGURATION_AREA_DEFAULT; // = "QTK.configuration.area.default";
    static const char *PROPERTIE_INSTANCE_AREA_DEFAULT; // = "QTK.instance.area.default";
    static const char *PROPERTIE_USER_AREA_DEFAULT; // = "QTK.user.area.default";

    static const char *PROPERTIE_EXITCODE; // = "QTK.exitcode";
    static const char *PROPERTIE_EXITDATA; // = "QTK.exitdata";
    static const char *PROPERTIE_CONSOLELOG; // = "QTK.consoleLog";

    static const char *PROPERTIE_ALLOWAPPRELAUNCH; // = "QTK.allowAppRelaunch";
    static const char *PROPERTIE_APPLICATION_LAUNCHDEFAULT; // = "QTK.application.launchDefault";

    static const char *PROPERTIE_PLUGINFRAMEWORK_RELAUNCH; // = "QTK.pluginfw.relaunch";

private:
    static const QScopedPointer<QTKPluginFrameworkLauncherPrivate> d;
    Q_DISABLE_COPY(QTKPluginFrameworkLauncher)
};

QTK_PLUGINFRAMEWORK_END_NAMESPACE

#endif // QTKPLUGINFRAMEWORKLAUNCHER_H
