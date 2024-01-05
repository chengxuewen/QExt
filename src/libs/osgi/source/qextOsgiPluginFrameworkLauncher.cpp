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

#include <qextOsgiPluginFrameworkLauncher.h>
#include <qextOsgiPluginFrameworkFactory.h>
#include <private/qextOsgiPluginFrameworkProperties_p.h>
#include <qextOsgiPluginFramework.h>
#include <qextOsgiPluginContext.h>
#include <qextOsgiPluginException.h>
#include <private/qextOsgiPlugin_p.h>
#include <private/qextOsgiDefaultApplicationLauncher_p.h>
#include <private/qextOsgiLocationManager_p.h>
#include <private/qextOsgiBasicLocation_p.h>

#include <QExtOsgiConfig.h>

#include <QStringList>
#include <QDirIterator>
#include <QFileInfo>
#include <QDebug>
#include <QRunnable>
#include <QSettings>
#include <QProcessEnvironment>

#ifdef _WIN32
#   include <windows.h>
#   include <cstdlib>
#endif // _WIN32


const QString QExtOsgiPluginFrameworkLauncher::PROP_USER_HOME = "user.home";
const QString QExtOsgiPluginFrameworkLauncher::PROP_USER_DIR = "user.dir";

// Framework properties
const QString QExtOsgiPluginFrameworkLauncher::PROP_PLUGINS = "qextOsgi.plugins";
const QString QExtOsgiPluginFrameworkLauncher::PROP_PLUGINS_START_OPTIONS = "qextOsgi.plugins.startOptions";
const QString QExtOsgiPluginFrameworkLauncher::PROP_DEBUG = "qextOsgi.debug";
const QString QExtOsgiPluginFrameworkLauncher::PROP_DEV = "qextOsgi.dev";
const QString QExtOsgiPluginFrameworkLauncher::PROP_CONSOLE = "qextOsgi.console";
const QString QExtOsgiPluginFrameworkLauncher::PROP_OS = "qextOsgi.os";
const QString QExtOsgiPluginFrameworkLauncher::PROP_ARCH = "qextOsgi.arch";

const QString QExtOsgiPluginFrameworkLauncher::PROP_NOSHUTDOWN = "qextOsgi.noShutdown";
const QString QExtOsgiPluginFrameworkLauncher::PROP_IGNOREAPP = "qextOsgi.ignoreApp";

const QString QExtOsgiPluginFrameworkLauncher::PROP_INSTALL_AREA = "qextOsgi.install.area";
const QString QExtOsgiPluginFrameworkLauncher::PROP_CONFIG_AREA = "qextOsgi.configuration.area";
const QString QExtOsgiPluginFrameworkLauncher::PROP_SHARED_CONFIG_AREA = "qextOsgi.sharedConfiguration.area";
const QString QExtOsgiPluginFrameworkLauncher::PROP_INSTANCE_AREA = "qextOsgi.instance.area";
const QString QExtOsgiPluginFrameworkLauncher::PROP_USER_AREA = "qextOsgi.user.area";
const QString QExtOsgiPluginFrameworkLauncher::PROP_HOME_LOCATION_AREA = "qextOsgi.home.location";


const QString QExtOsgiPluginFrameworkLauncher::PROP_CONFIG_AREA_DEFAULT = "qextOsgi.configuration.area.default";
const QString QExtOsgiPluginFrameworkLauncher::PROP_INSTANCE_AREA_DEFAULT = "qextOsgi.instance.area.default";
const QString QExtOsgiPluginFrameworkLauncher::PROP_USER_AREA_DEFAULT = "qextOsgi.user.area.default";

const QString QExtOsgiPluginFrameworkLauncher::PROP_EXITCODE = "qextOsgi.exitcode";
const QString QExtOsgiPluginFrameworkLauncher::PROP_EXITDATA = "qextOsgi.exitdata";
const QString QExtOsgiPluginFrameworkLauncher::PROP_CONSOLE_LOG = "qextOsgi.consoleLog";

const QString QExtOsgiPluginFrameworkLauncher::PROP_ALLOW_APPRELAUNCH = "qextOsgi.allowAppRelaunch";
const QString QExtOsgiPluginFrameworkLauncher::PROP_APPLICATION_LAUNCHDEFAULT = "qextOsgi.application.launchDefault";

const QString QExtOsgiPluginFrameworkLauncher::PROP_OSGI_RELAUNCH = "qextOsgi.pluginfw.relaunch";

static const QString PROP_FORCED_RESTART = "qextOsgi.forcedRestart";

class QExtOsgiPluginFrameworkLauncherPrivate
{
public:

    //----------------------------------------------------------------------------
    QExtOsgiPluginFrameworkLauncherPrivate()
        : fwFactory(0)
        , running(false)
        , processEnv(QProcessEnvironment::systemEnvironment())
    {
#ifdef CMAKE_INTDIR
        QString pluginPath = QEXT_OSGI_PLUGIN_DIR CMAKE_INTDIR "/";
#else
        QString pluginPath = QEXT_OSGI_PLUGIN_DIR;
#endif

        pluginSearchPaths.append(pluginPath);

        pluginLibFilter << "*.dll" << "*.so" << "*.dylib";
    }

    //----------------------------------------------------------------------------
    bool isForcedRestart() const
    {
        return QExtOsgiPluginFrameworkProperties::getProperty(PROP_FORCED_RESTART).toBool();
    }

    //----------------------------------------------------------------------------
    void loadConfigurationInfo()
    {
        QExtOsgiBasicLocation* configArea = QExtOsgiLocationManager::getConfigurationLocation();
        if (configArea == NULL)
        {
            return;
        }

        QUrl location(configArea->getUrl().toString() + QExtOsgiLocationManager::CONFIG_FILE);
        mergeProperties(QExtOsgiPluginFrameworkProperties::getProperties(), loadProperties(location));
    }

    //----------------------------------------------------------------------------
    void mergeProperties(QExtOsgiProperties& destination, const QExtOsgiProperties& source)
    {
        for (QExtOsgiProperties::const_iterator iter = source.begin(); iter != source.end(); ++iter)
        {
            if (!destination.contains(iter.key()))
            {
                destination.insert(iter.key(), iter.value());
            }
        }
    }

    //----------------------------------------------------------------------------
    QExtOsgiProperties loadProperties(const QUrl& location)
    {
        QExtOsgiProperties result;
        if (!location.isValid() || !QFileInfo(location.toLocalFile()).exists())
        {
            return result;
        }
        QSettings iniProps(location.toLocalFile(), QSettings::IniFormat);
        foreach (const QString& key, iniProps.allKeys())
        {
            result.insert(key, iniProps.value(key));
        }

        return substituteVars(result);
    }

    //----------------------------------------------------------------------------
    QExtOsgiProperties& substituteVars(QExtOsgiProperties& result)
    {
        for (QExtOsgiProperties::iterator iter = result.begin(); iter != result.end(); ++iter)
        {
            if (iter.value().type() == QVariant::String)
            {
                iter.value() = substituteVars(iter.value().toString());
            }
        }
        return result;
    }

    //----------------------------------------------------------------------------
    QString substituteVars(const QString& path)
    {
        QString buf;
        bool varStarted = false; // indicates we are processing a var substitute
        QString var; // the current var key
        for (QString::const_iterator iter = path.begin(); iter != path.end(); ++iter)
        {
            QChar tok = *iter;
            if (tok == '$')
            {
                if (!varStarted)
                {
                    varStarted = true; // we found the start of a var
                    var.clear();
                }
                else
                {
                    // we have found the end of a var
                    QVariant prop;
                    // get the value of the var from system properties
                    if (!var.isEmpty())
                    {
                        prop = QExtOsgiPluginFrameworkProperties::getProperty(var);
                    }
                    if (prop.isNull() && processEnv.contains(var))
                    {
                        prop = processEnv.value(var);
                    }
                    if (!prop.isNull())
                    {
                        // found a value; use it
                        buf.append(prop.toString());
                    }
                    else
                    {
                        // could not find a value append the var name w/o delims
                        buf.append(var);
                    }
                    varStarted = false;
                    var.clear();
                }
            }
            else
            {
                if (!varStarted)
                {
                    buf.append(tok); // the token is not part of a var
                }
                else
                {
                    var.append(tok); // the token is part of the var key; save the key to process when we find the end token
                }
            }
        }

        if (!var.isEmpty())
        {
            // found a case of $var at the end of the path with no trailing $; just append it as is.
            buf.append('$').append(var);
        }
        return buf;
    }

    //----------------------------------------------------------------------------
    QSharedPointer<QExtOsgiPlugin> install(const QUrl& pluginPath, QExtOsgiPluginContext* context)
    {
        try
        {
            return context->installPlugin(pluginPath);
        }
        catch (const QExtOsgiPluginException& exc)
        {
            qWarning() << "Failed to install plugin " << pluginPath << ":" << exc.printStackTrace();
            return QSharedPointer<QExtOsgiPlugin>();
        }
    }

    //----------------------------------------------------------------------------
    QSharedPointer<QExtOsgiPlugin> install(const QString& symbolicName, QExtOsgiPluginContext* context)
    {
        QString pluginPath = QExtOsgiPluginFrameworkLauncher::getPluginPath(symbolicName);
        if (pluginPath.isEmpty()) return QSharedPointer<QExtOsgiPlugin>();

        QExtOsgiPluginContext* pc = context;

        if (pc == 0 && fwFactory == 0)
        {
            fwFactory.reset(new QExtOsgiPluginFrameworkFactory(fwProps));
            try
            {
                fwFactory->getFramework()->init();
                pc = fwFactory->getFramework()->getPluginContext();
            }
            catch (const QExtOsgiPluginException& exc)
            {
                qCritical() << "Failed to initialize the plug-in framework:" << exc;
                fwFactory.reset();
                return QSharedPointer<QExtOsgiPlugin>();
            }
        }

        return install(QUrl::fromLocalFile(pluginPath), pc);
    }

    //----------------------------------------------------------------------------
    void resolvePlugin(const QSharedPointer<QExtOsgiPlugin>& plugin)
    {
        if (plugin)
        {
            plugin->d_func()->getUpdatedState();
        }
    }

    /*
   * Ensure all basic plugins are installed, resolved and scheduled to start. Returns a list containing
   * all basic bundles that are marked to start.
   */
    //----------------------------------------------------------------------------
    void loadBasicPlugins()
    {
        QVariant pluginsProp = QExtOsgiPluginFrameworkProperties::getProperty(QExtOsgiPluginFrameworkLauncher::PROP_PLUGINS);

        QVariant startOptionsProp = QExtOsgiPluginFrameworkProperties::getProperty(QExtOsgiPluginFrameworkLauncher::PROP_PLUGINS_START_OPTIONS);
        QExtOsgiPlugin::StartOptions startOptions = QExtOsgiPlugin::START_ACTIVATION_POLICY;
        if (startOptionsProp.isValid())
        {
            bool okay = false;
            int startOptionsInt = startOptionsProp.toInt(&okay);
            if (okay)
            {
                startOptions = QExtOsgiPlugin::StartOptions(startOptionsInt);
            }
        }

        QStringList installEntries;
        if (pluginsProp.type() == QVariant::StringList)
        {
            installEntries = pluginsProp.toStringList();
        }
        else
        {
            installEntries = pluginsProp.toString().split(',');
        }

        QList<QSharedPointer<QExtOsgiPlugin> > startEntries;
        QExtOsgiPluginContext* context = fwFactory->getFramework()->getPluginContext();
        foreach(const QString& installEntry, installEntries)
        {
            QUrl pluginUrl(installEntry);
            if (pluginUrl.isValid() && pluginUrl.scheme().isEmpty())
            {
                // try a local file path
                QFileInfo installFileInfo(installEntry);
                if (installFileInfo.exists())
                {
                    pluginUrl = QUrl::fromLocalFile(installFileInfo.absoluteFilePath());
                }
                else
                {
                    pluginUrl.clear();
                }
            }

            if (pluginUrl.isValid())
            {
                QSharedPointer<QExtOsgiPlugin> plugin = install(pluginUrl, context);
                if (plugin)
                {
                    startEntries.push_back(plugin);
                }
            }
            else
            {
                QSharedPointer<QExtOsgiPlugin> plugin = install(installEntry, context);
                if (plugin)
                {
                    // schedule all basic bundles to be started
                    startEntries.push_back(plugin);
                }
            }
        }

        foreach(QSharedPointer<QExtOsgiPlugin> plugin, startEntries)
        {
            this->resolvePlugin(plugin);
        }

        foreach(QSharedPointer<QExtOsgiPlugin> plugin, startEntries)
        {
            plugin->start(startOptions);
        }
    }


    QStringList pluginSearchPaths;
    QStringList pluginLibFilter;

    QExtOsgiProperties fwProps;

    QScopedPointer<QExtOsgiPluginFrameworkFactory> fwFactory;

    bool running;

    QScopedPointer<QExtOsgiDefaultApplicationLauncher> appLauncher;
    QExtOsgiServiceRegistration appLauncherRegistration;

    QProcessEnvironment processEnv;
};

const QScopedPointer<QExtOsgiPluginFrameworkLauncherPrivate> QExtOsgiPluginFrameworkLauncher::d(
    new QExtOsgiPluginFrameworkLauncherPrivate());

//----------------------------------------------------------------------------
void QExtOsgiPluginFrameworkLauncher::setFrameworkProperties(const QExtOsgiProperties& props)
{
    QExtOsgiPluginFrameworkProperties::setProperties(props);
}

//----------------------------------------------------------------------------
QVariant QExtOsgiPluginFrameworkLauncher::run(QRunnable* endSplashHandler, const QVariant& argument)
{
    if (d->running)
    {
        throw QExtIllegalStateException("Framework already running");
    }
    {
        struct Finalize {
            ~Finalize()
            {
                try
                {
                    // The application typically sets the exit code however the framework can request that
                    // it be re-started. We need to check for this and potentially override the exit code.
                    if (d->isForcedRestart())
                    {
                        QExtOsgiPluginFrameworkProperties::setProperty(PROP_EXITCODE, "23");
                    }
                    if (!QExtOsgiPluginFrameworkProperties::getProperty(PROP_NOSHUTDOWN).toBool())
                    {
                        shutdown();
                    }
                }
                catch (const std::exception& e)
                {
                    qWarning() << "Shutdown error:" << e.what();
                }
            }
        };
        Finalize finalizer;
        Q_UNUSED(finalizer)
        try
        {
            startup(endSplashHandler);
            if (QExtOsgiPluginFrameworkProperties::getProperty(PROP_IGNOREAPP).toBool() || d->isForcedRestart())
            {
                return argument;
            }
            return run(argument);
        }
        catch (const std::exception& e)
        {
            // ensure the splash screen is down
            if (endSplashHandler != NULL)
            {
                endSplashHandler->run();
            }
            // may use startupFailed to understand where the error happened
            if (const QExtException* ce = dynamic_cast<const QExtException*>(&e))
            {
                qWarning() << "Startup error:" << ce->printStackTrace();
            }
            else
            {
                qWarning() << "Startup error:" << e.what();
            }
        }
    }

    // we only get here if an error happened
    if (QExtOsgiPluginFrameworkProperties::getProperty(PROP_EXITCODE).isNull())
    {
        QExtOsgiPluginFrameworkProperties::setProperty(PROP_EXITCODE, "13");
        QExtOsgiPluginFrameworkProperties::setProperty(PROP_EXITDATA, QString("An error has occurred. See the console output and log file for details."));
    }
    return QVariant();
}

//----------------------------------------------------------------------------
QVariant QExtOsgiPluginFrameworkLauncher::run(const QVariant& argument)
{
    if (!d->running)
    {
        throw QExtIllegalStateException("Framework not running.");
    }
    // if we are just initializing, do not run the application just return.
    /*
  if (d->initialize)
  {
    return 0;
  }
  */
    try
    {
        if (!d->appLauncher)
        {
            bool launchDefault = QExtOsgiPluginFrameworkProperties::getProperty(PROP_APPLICATION_LAUNCHDEFAULT, true).toBool();
            // create the ApplicationLauncher and register it as a service
            d->appLauncher.reset(new QExtOsgiDefaultApplicationLauncher(d->fwFactory->getFramework()->getPluginContext(),
                                                                        QExtOsgiPluginFrameworkProperties::getProperty(PROP_ALLOW_APPRELAUNCH).toBool(),
                                                                        launchDefault));
            d->appLauncherRegistration = d->fwFactory->getFramework()->getPluginContext()->
                                         registerService<QExtOsgiApplicationLauncher>(d->appLauncher.data());

            // must start the launcher AFTER service registration because this method
            // blocks and runs the application on the current thread.  This method
            // will return only after the application has stopped.
            return d->appLauncher->start(argument);
        }
        return d->appLauncher->reStart(argument);
    }
    catch (const QExtException& e)
    {
        qWarning() << "Application launch failed:" << e.printStackTrace();
        throw;
    }
    catch (const std::exception& e)
    {
        qWarning() << "Application launch failed:" << e.what();
        throw;
    }
}

//----------------------------------------------------------------------------
QExtOsgiPluginContext* QExtOsgiPluginFrameworkLauncher::startup(QRunnable* endSplashHandler)
{
    if (d->running)
    {
        throw QExtIllegalStateException("Framework already running.");
    }
    QExtOsgiPluginFrameworkProperties::initializeProperties();
    //processCommandLine(args);
    QExtOsgiLocationManager::initializeLocations();
    d->loadConfigurationInfo();
    //finalizeProperties();
    d->fwFactory.reset(new QExtOsgiPluginFrameworkFactory(QExtOsgiPluginFrameworkProperties::getProperties()));
    //d->context = framework.getBundle(0).getBundleContext();
    //registerFrameworkShutdownHandlers();
    //publishSplashScreen(endSplashHandler);
    //consoleMgr = ConsoleManager.startConsole(framework);
    d->fwFactory->getFramework()->start();
    d->loadBasicPlugins();

    d->running = true;

    if (endSplashHandler != NULL)
    {
        endSplashHandler->run();
    }

    return d->fwFactory->getFramework()->getPluginContext();
}

void QExtOsgiPluginFrameworkLauncher::shutdown()
{
    if (!d->running || d->fwFactory == NULL)
        return;

    //if (appLauncherRegistration != null)
    //  appLauncherRegistration.unregister();
    //if (splashStreamRegistration != null)
    //  splashStreamRegistration.unregister();
    //if (defaultMonitorRegistration != null)
    //  defaultMonitorRegistration.unregister();
    if (d->appLauncher)
    {
        d->appLauncher->shutdown();
    }
    //appLauncherRegistration = null;
    //appLauncher = null;
    //splashStreamRegistration = null;
    //defaultMonitorRegistration = null;
    //d->fwFactory.reset();
    stop();
    d->running = false;
}

//----------------------------------------------------------------------------
long QExtOsgiPluginFrameworkLauncher::install(const QString& symbolicName, QExtOsgiPluginContext* context)
{
    QSharedPointer<QExtOsgiPlugin> plugin = d->install(symbolicName, context);
    if (plugin) return plugin->getPluginId();
    return -1;
}

//----------------------------------------------------------------------------
bool QExtOsgiPluginFrameworkLauncher::start(const QString& symbolicName, QExtOsgiPlugin::StartOptions options,
                                            QExtOsgiPluginContext* context)
{
    // instantiate and start the framework
    if (context == 0 && d->fwFactory == 0) {
        d->fwFactory.reset(new QExtOsgiPluginFrameworkFactory(d->fwProps));
        try
        {
            d->fwFactory->getFramework()->start();
        }
        catch (const QExtOsgiPluginException& exc)
        {
            qCritical() << "Failed to start the plug-in framework:" << exc;
            d->fwFactory.reset();
            return false;
        }
    }
    else if (context == 0 && d->fwFactory->getFramework()->getState() != QExtOsgiPlugin::ACTIVE)
    {
        try
        {
            d->fwFactory->getFramework()->start(options);
        }
        catch (const QExtOsgiPluginException& exc)
        {
            qCritical() << "Failed to start the plug-in framework:" << exc;
            d->fwFactory.reset();
            return false;
        }
    }

    if(!symbolicName.isEmpty())
    {
        QString pluginPath = getPluginPath(symbolicName);
        if (pluginPath.isEmpty()) return false;

        QExtOsgiPluginContext* pc = context ? context : getPluginContext();
        try
        {
            pc->installPlugin(QUrl::fromLocalFile(pluginPath))->start(options);
        }
        catch (const QExtOsgiPluginException& exc)
        {
            qWarning() << "Failed to install plugin:" << exc;
            return false;
        }
    }

    return true;
}

//----------------------------------------------------------------------------
bool QExtOsgiPluginFrameworkLauncher::stop(const QString& symbolicName,
                                           QExtOsgiPlugin::StopOptions options, QExtOsgiPluginContext* context)
{
    if (d->fwFactory == 0) return true;

    QExtOsgiPluginContext* pc = context ? context : getPluginContext();
    if (pc == 0)
    {
        qWarning() << "No valid plug-in context available";
        return false;
    }

    if(!symbolicName.isEmpty())
    {
        QString pluginPath = getPluginPath(symbolicName);
        if (pluginPath.isEmpty()) return false;

        try
        {
            QList<QSharedPointer<QExtOsgiPlugin> > plugins = pc->getPlugins();
            foreach(QSharedPointer<QExtOsgiPlugin> plugin, plugins)
            {
                if (plugin->getSymbolicName() == symbolicName)
                {
                    plugin->stop(options);
                    return true;
                }
            }
            qWarning() << "Plug-in" << symbolicName << "not found";
            return false;
        }
        catch (const QExtOsgiPluginException& exc)
        {
            qWarning() << "Failed to stop plug-in:" << exc;
            return false;
        }
    }
    else
    {
        // stop the framework
        QSharedPointer<QExtOsgiPluginFramework> fw =
            qSharedPointerCast<QExtOsgiPluginFramework>(pc->getPlugin(0));
        try
        {
            fw->stop();
            QExtOsgiPluginFrameworkEvent fe = fw->waitForStop(5000);
            if (fe.getType() == QExtOsgiPluginFrameworkEvent::FRAMEWORK_WAIT_TIMEDOUT)
            {
                qWarning() << "Stopping the plugin framework timed out";
                return false;
            }
        }
        catch (const QExtRuntimeException& e)
        {
            qWarning() << "Stopping the plugin framework failed: " << e;
            return false;
        }

        return true;
    }
}

//----------------------------------------------------------------------------
void QExtOsgiPluginFrameworkLauncher::resolve(const QSharedPointer<QExtOsgiPlugin>& plugin)
{
    d->resolvePlugin(plugin);
}

//----------------------------------------------------------------------------
void QExtOsgiPluginFrameworkLauncher::resolve()
{
    QList<QSharedPointer<QExtOsgiPlugin> > plugins = getPluginFramework()->getPluginContext()->getPlugins();
    foreach(const QSharedPointer<QExtOsgiPlugin>& plugin, plugins)
    {
        resolve(plugin);
    }
}

//----------------------------------------------------------------------------
QExtOsgiPluginContext* QExtOsgiPluginFrameworkLauncher::getPluginContext()
{
    if (d->fwFactory == 0) return 0;
    return d->fwFactory->getFramework()->getPluginContext();
}

//----------------------------------------------------------------------------
QSharedPointer<QExtOsgiPluginFramework> QExtOsgiPluginFrameworkLauncher::getPluginFramework()
{
    if (d->fwFactory)
        return d->fwFactory->getFramework();
    return QSharedPointer<QExtOsgiPluginFramework>();
}

//----------------------------------------------------------------------------
void QExtOsgiPluginFrameworkLauncher::appendPathEnv(const QString& path)
{
#ifdef _WIN32
#ifdef __MINGW32__
    QString pathVar("PATH");
    QString oldPath(getenv("PATH"));
    pathVar += "=" + oldPath + ";" + path;
    if(_putenv(qPrintable(pathVar)))
#else
    std::size_t bufferLength;
    getenv_s(&bufferLength, NULL, 0, "PATH");
    QString newPath = path;
    if (bufferLength > 0)
    {
        char* oldPath = new char[bufferLength];
        getenv_s(&bufferLength, oldPath, bufferLength, "PATH");
        newPath.append(";").append(oldPath);
        delete[] oldPath;
    }
    qDebug() << "new PATH:" << newPath;
    if(_putenv_s("PATH", qPrintable(newPath)))
#endif
    {
        LPVOID lpMsgBuf;
        DWORD dw = GetLastError();

        FormatMessageW(
            FORMAT_MESSAGE_ALLOCATE_BUFFER |
                FORMAT_MESSAGE_FROM_SYSTEM |
                FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            dw,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPWSTR) &lpMsgBuf,
            0, NULL );

        // Avoid project configuration conflicts regarding wchar_t considered
        // a built-in type or not by using QString::fromUtf16 instead of
        // QString::fromWCharArray
        // sa http://qt-project.org/wiki/toStdWStringAndBuiltInWchar
        QString msg = QString("Adding '%1' to the PATH environment variable failed: %2")
                          .arg(path).arg(QString::fromUtf16(reinterpret_cast<const ushort*>(lpMsgBuf)));

        qWarning() << msg;

        LocalFree(lpMsgBuf);
    }
#else
    Q_UNUSED(path)
#endif
}

//----------------------------------------------------------------------------
void QExtOsgiPluginFrameworkLauncher::addSearchPath(const QString& searchPath, bool addToPathEnv)
{
    d->pluginSearchPaths.prepend(searchPath);
    if (addToPathEnv) appendPathEnv(searchPath);
}

//----------------------------------------------------------------------------
QString QExtOsgiPluginFrameworkLauncher::getPluginPath(const QString& symbolicName)
{
    QString pluginFileName(symbolicName);
    pluginFileName.replace(".", "_");
    foreach(QString searchPath, d->pluginSearchPaths)
    {
        QDirIterator dirIter(searchPath, d->pluginLibFilter, QDir::Files);
        while(dirIter.hasNext())
        {
            dirIter.next();
            QFileInfo fileInfo = dirIter.fileInfo();
            QString fileBaseName = fileInfo.baseName();
            if (fileBaseName.startsWith("lib")) fileBaseName = fileBaseName.mid(3);

            if (fileBaseName == pluginFileName)
            {
                return fileInfo.canonicalFilePath();
            }
        }
    }

    return QString();
}

//----------------------------------------------------------------------------
QStringList QExtOsgiPluginFrameworkLauncher::getPluginSymbolicNames(const QString& searchPath)
{
    QStringList result;
    QDirIterator dirIter(searchPath, d->pluginLibFilter, QDir::Files);
    while(dirIter.hasNext())
    {
        dirIter.next();
        QFileInfo fileInfo = dirIter.fileInfo();
        QString fileBaseName = fileInfo.baseName();
        if (fileBaseName.startsWith("lib")) fileBaseName = fileBaseName.mid(3);
        result << fileBaseName.replace("_", ".");
    }

    return result;
}

