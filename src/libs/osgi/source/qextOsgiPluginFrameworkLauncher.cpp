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

#include "qtkpluginframeworklauncher.h"
#include "qtkpluginframeworkfactory.h"
#include "qtkpluginframeworkproperties_p.h"
#include "qtkpluginframework.h"
#include "qtkplugincontext.h"
#include "qtkpluginexception.h"
#include "qtkplugin_p.h"
#include "qtkdefaultapplicationlauncher_p.h"
#include "qtklocationmanager_p.h"
#include "qtkbasiclocation_p.h"

#include <qtkinfo.h>

#include <QStringList>
#include <QDirIterator>
#include <QFileInfo>
#include <QDebug>
#include <QRunnable>
#include <QSettings>
#include <QProcessEnvironment>

#ifdef _WIN32
#include <windows.h>
#include <cstdlib>
#endif // _WIN32

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

const char *QTKPluginFrameworkLauncher::PROPERTIE_USER_HOME = "user.home";
const char *QTKPluginFrameworkLauncher::PROPERTIE_USER_DIR = "user.dir";

// Framework properties
const char *QTKPluginFrameworkLauncher::PROPERTIE_PLUGINS = "QTK.plugins";
const char *QTKPluginFrameworkLauncher::PROPERTIE_PLUGINS_STARTOPTIONS = "QTK.plugins.startOptions";
const char *QTKPluginFrameworkLauncher::PROPERTIE_DEBUG = "QTK.debug";
const char *QTKPluginFrameworkLauncher::PROPERTIE_DEV = "QTK.dev";
const char *QTKPluginFrameworkLauncher::PROPERTIE_CONSOLE = "QTK.console";
const char *QTKPluginFrameworkLauncher::PROPERTIE_OS = "QTK.os";
const char *QTKPluginFrameworkLauncher::PROPERTIE_ARCH = "QTK.arch";

const char *QTKPluginFrameworkLauncher::PROPERTIE_NOSHUTDOWN = "QTK.noShutdown";
const char *QTKPluginFrameworkLauncher::PROPERTIE_IGNOREAPP = "QTK.ignoreApp";

const char *QTKPluginFrameworkLauncher::PROPERTIE_INSTALL_AREA = "QTK.install.area";
const char *QTKPluginFrameworkLauncher::PROPERTIE_CONFIGURATION_AREA = "QTK.configuration.area";
const char *QTKPluginFrameworkLauncher::PROPERTIE_SHAREDCONFIGURATION_AREA = "QTK.sharedConfiguration.area";
const char *QTKPluginFrameworkLauncher::PROPERTIE_INSTANCE_AREA = "QTK.instance.area";
const char *QTKPluginFrameworkLauncher::PROPERTIE_USER_AREA = "QTK.user.area";
const char *QTKPluginFrameworkLauncher::PROPERTIE_HOME_LOCATION = "QTK.home.location";


const char *QTKPluginFrameworkLauncher::PROPERTIE_CONFIGURATION_AREA_DEFAULT = "QTK.configuration.area.default";
const char *QTKPluginFrameworkLauncher::PROPERTIE_INSTANCE_AREA_DEFAULT = "QTK.instance.area.default";
const char *QTKPluginFrameworkLauncher::PROPERTIE_USER_AREA_DEFAULT = "QTK.user.area.default";

const char *QTKPluginFrameworkLauncher::PROPERTIE_EXITCODE = "QTK.exitcode";
const char *QTKPluginFrameworkLauncher::PROPERTIE_EXITDATA = "QTK.exitdata";
const char *QTKPluginFrameworkLauncher::PROPERTIE_CONSOLELOG = "QTK.consoleLog";

const char *QTKPluginFrameworkLauncher::PROPERTIE_ALLOWAPPRELAUNCH = "QTK.allowAppRelaunch";
const char *QTKPluginFrameworkLauncher::PROPERTIE_APPLICATION_LAUNCHDEFAULT = "QTK.application.launchDefault";

const char *QTKPluginFrameworkLauncher::PROPERTIE_PLUGINFRAMEWORK_RELAUNCH = "QTK.pluginfw.relaunch";

static const char *PROPERTIE_FORCED_RESTART = "QTK.forcedRestart";

class QTKPluginFrameworkLauncherPrivate
{
public:
    QTKPluginFrameworkLauncherPrivate()
        : m_pPFWFactory(nullptr)
        , m_bRunning(false)
        , m_processEnv(QProcessEnvironment::systemEnvironment())
    {
#ifdef CMAKE_INTDIR
        QString pluginPath = QTK_PLUGIN_DIR CMAKE_INTDIR "/";
#else
        QString pluginPath = QTK_PLUGIN_DIR;
#endif

        m_listPluginSearchPaths.append(pluginPath);
        m_listPluginLibFilter << "*.dll" << "*.so" << "*.dylib";
    }

    bool isForcedRestart() const {
        return QTKPluginFrameworkProperties::getProperty(PROPERTIE_FORCED_RESTART).toBool();
    }

    void loadConfigurationInfo() {
        QTKBasicLocation *pConfigArea = QTKLocationManager::getConfigurationLocation();
        if (nullptr == pConfigArea) {
            return;
        }

        QUrl location(pConfigArea->getUrl().toString() + QTKLocationManager::getConfigFileName());
        this->mergeProperties(QTKPluginFrameworkProperties::getProperties(), loadProperties(location));
    }

    void mergeProperties(QTKProperties &destination, const QTKProperties &source) {
        for (QTKProperties::const_iterator iter = source.begin(); iter != source.end(); ++iter) {
            if (!destination.contains(iter.key())) {
                destination.insert(iter.key(), iter.value());
            }
        }
    }

    QTKProperties loadProperties(const QUrl &location) {
        QTKProperties result;
        if (!location.isValid() || !QFileInfo(location.toLocalFile()).exists()) {
            return result;
        }
        QSettings iniProps(location.toLocalFile(), QSettings::IniFormat);
        foreach (const QString& key, iniProps.allKeys()) {
            result.insert(key, iniProps.value(key));
        }

        return substituteVars(result);
    }

    QTKProperties &substituteVars(QTKProperties &result) {
        for (QTKProperties::iterator iter = result.begin(); iter != result.end(); ++iter) {
            if (iter.value().type() == QVariant::String) {
                iter.value() = substituteVars(iter.value().toString());
            }
        }
        return result;
    }

    QString substituteVars(const QString &strPath) {
        QString strBuf;
        bool bVarStarted = false; // indicates we are processing a var subtitute
        QString strVar; // the current var key
        for (QString::const_iterator iter = strPath.begin(); iter != strPath.end(); ++iter) {
            QChar tok = *iter;
            if (tok == '$') {
                if (!bVarStarted) {
                    bVarStarted = true; // we found the start of a var
                    strVar.clear();
                } else {
                    // we have found the end of a var
                    QVariant prop;
                    // get the value of the var from system properties
                    if (!strVar.isEmpty()) {
                        prop = QTKPluginFrameworkProperties::getProperty(strVar);
                    }
                    if (prop.isNull() && m_processEnv.contains(strVar)) {
                        prop = m_processEnv.value(strVar);
                    }
                    if (!prop.isNull()) {
                        // found a value; use it
                        strBuf.append(prop.toString());
                    } else {
                        // could not find a value append the var name w/o delims
                        strBuf.append(strVar);
                    }
                    bVarStarted = false;
                    strVar.clear();
                }
            } else {
                if (!bVarStarted) {
                    strBuf.append(tok); // the token is not part of a var
                } else {
                    strVar.append(tok); // the token is part of the var key; save the key to process when we find the end token
                }
            }
        }

        if (!strVar.isEmpty()) {
            // found a case of $var at the end of the path with no trailing $; just append it as is.
            strBuf.append('$').append(strVar);
        }
        return strBuf;
    }

    QSharedPointer<QTKPlugin> install(const QUrl &pluginPath, QTKPluginContext *pContext) {
        try {
            return pContext->installPlugin(pluginPath);
        } catch (const QTKPluginException &e) {
            qWarning() << "Failed to install plugin " << pluginPath << ":" << e.printStackTrace();
            return QSharedPointer<QTKPlugin>();
        }
    }

    QSharedPointer<QTKPlugin> install(const QString &strSymbolicName, QTKPluginContext *pContext) {
        QString strPluginPath = QTKPluginFrameworkLauncher::getPluginPath(strSymbolicName);
        if (strPluginPath.isEmpty()) {
            return QSharedPointer<QTKPlugin>();
        }

        QTKPluginContext *pPluginContext = pContext;

        if (nullptr == pPluginContext && nullptr == m_pPFWFactory) {
            m_pPFWFactory.reset(new QTKPluginFrameworkFactory(m_pfwProperties));
            try {
                m_pPFWFactory->getFramework()->init();
                pPluginContext = m_pPFWFactory->getFramework()->getPluginContext();
            }  catch (const QTKPluginException& exc) {
                qCritical() << "Failed to initialize the plug-in framework:" << exc;
                m_pPFWFactory.reset();
                return QSharedPointer<QTKPlugin>();
            }
        }

        return install(QUrl::fromLocalFile(strPluginPath), pPluginContext);
    }

    void resolvePlugin(const QSharedPointer<QTKPlugin> &pPlugin) {
        if (pPlugin) {
            pPlugin->d_func()->getUpdatedState();
        }
    }

    void loadBasicPlugins() {
        QVariant pluginsProp = QTKPluginFrameworkProperties::getProperty(QTKPluginFrameworkLauncher::PROPERTIE_PLUGINS);
        QVariant startOptionsProp = QTKPluginFrameworkProperties::getProperty(QTKPluginFrameworkLauncher::PROPERTIE_PLUGINS_STARTOPTIONS);
        QTKPlugin::StartOptions startOptions = QTKPlugin::StartOption_StartActivationPolicy;
        if (startOptionsProp.isValid()) {
            bool bOkay = false;
            int iStartOptionsInt = startOptionsProp.toInt(&bOkay);
            if (bOkay) {
                startOptions = QTKPlugin::StartOptions(iStartOptionsInt);
            }
        }

        QStringList listInstallEntries;
        if (pluginsProp.type() == QVariant::StringList) {
            listInstallEntries = pluginsProp.toStringList();
        } else {
            listInstallEntries = pluginsProp.toString().split(',');
        }

        QList<QSharedPointer<QTKPlugin> > listStartEntries;
        QTKPluginContext *pContext = m_pPFWFactory->getFramework()->getPluginContext();
        foreach(const QString &strInstallEntry, listInstallEntries) {
            QUrl pluginUrl(strInstallEntry);
            if (pluginUrl.isValid() && pluginUrl.scheme().isEmpty()) {
                // try a local file path
                QFileInfo installFileInfo(strInstallEntry);
                if (installFileInfo.exists()) {
                    pluginUrl = QUrl::fromLocalFile(installFileInfo.absoluteFilePath());
                } else {
                    pluginUrl.clear();
                }
            }

            if (pluginUrl.isValid()) {
                QSharedPointer<QTKPlugin> pPlugin = this->install(pluginUrl, pContext);
                if (pPlugin) {
                    listStartEntries.push_back(pPlugin);
                }
            } else {
                QSharedPointer<QTKPlugin> pPlugin = this->install(strInstallEntry, pContext);
                if (pPlugin) {
                    // schedule all basic bundles to be started
                    listStartEntries.push_back(pPlugin);
                }
            }
        }

        foreach(QSharedPointer<QTKPlugin> pPlugin, listStartEntries) {
            this->resolvePlugin(pPlugin);
        }

        foreach(QSharedPointer<QTKPlugin> pPlugin, listStartEntries) {
            pPlugin->start(startOptions);
        }
    }


    QStringList m_listPluginSearchPaths;
    QStringList m_listPluginLibFilter;
    QTKProperties m_pfwProperties;
    QScopedPointer<QTKPluginFrameworkFactory> m_pPFWFactory;
    bool m_bRunning;
    QScopedPointer<QTKDefaultApplicationLauncher> m_pAppLauncher;
    QTKServiceRegistration m_appLauncherRegistration;
    QProcessEnvironment m_processEnv;
};

const QScopedPointer<QTKPluginFrameworkLauncherPrivate> QTKPluginFrameworkLauncher::d(new QTKPluginFrameworkLauncherPrivate());

void QTKPluginFrameworkLauncher::setFrameworkProperties(const QTKProperties &properties)
{
    QTKPluginFrameworkProperties::setProperties(properties);
}

QVariant QTKPluginFrameworkLauncher::run(QRunnable *pEndSplashHandler, const QVariant &argument)
{
    if (d->m_bRunning) {
        throw QTKIllegalStateException("Framework already running");
    }

    {
        struct Finalize {
            ~Finalize() {
                try {
                    // The application typically sets the exit code however the framework can request that
                    // it be re-started. We need to check for this and potentially override the exit code.
                    if (d->isForcedRestart()) {
                        QTKPluginFrameworkProperties::setProperty(PROPERTIE_EXITCODE, "23");
                    }
                    if (!QTKPluginFrameworkProperties::getProperty(PROPERTIE_NOSHUTDOWN).toBool()) {
                        shutdown();
                    }
                } catch (const std::exception &e) {
                    qWarning() << "Shutdown error:" << e.what();
                }
            }
        };

        Finalize finalizer;
        Q_UNUSED(finalizer)
        try {
            startup(pEndSplashHandler);
            if (QTKPluginFrameworkProperties::getProperty(PROPERTIE_IGNOREAPP).toBool() || d->isForcedRestart()) {
                return argument;
            }
            return run(argument);
        } catch (const std::exception &e) {
            // ensure the splash screen is down
            if (nullptr != pEndSplashHandler) {
                pEndSplashHandler->run();
            }
            // may use startupFailed to understand where the error happened
            if (const QTKException *exception = dynamic_cast<const QTKException *>(&e)) {
                qWarning() << "Startup error:" << exception->printStackTrace();
            } else {
                qWarning() << "Startup error:" << e.what();
            }
        }
    }

    // we only get here if an error happened
    if (QTKPluginFrameworkProperties::getProperty(PROPERTIE_EXITCODE).isNull()) {
        QTKPluginFrameworkProperties::setProperty(PROPERTIE_EXITCODE, "13");
        QTKPluginFrameworkProperties::setProperty(PROPERTIE_EXITDATA, QString("An error has occured. See the console output and log file for details."));
    }
    return QVariant();
}

QVariant QTKPluginFrameworkLauncher::run(const QVariant &argument)
{
    if (!d->m_bRunning) {
        throw QTKIllegalStateException("Framework not running.");
    }

    try {
        if (!d->m_pAppLauncher) {
            bool bLaunchDefault = QTKPluginFrameworkProperties::getProperty(PROPERTIE_ALLOWAPPRELAUNCH, true).toBool();
            // create the ApplicationLauncher and register it as a service
            d->m_pAppLauncher.reset(new QTKDefaultApplicationLauncher(d->m_pPFWFactory->getFramework()->getPluginContext(),
                                                                      QTKPluginFrameworkProperties::getProperty(PROPERTIE_ALLOWAPPRELAUNCH).toBool(),
                                                                      bLaunchDefault));
            d->m_appLauncherRegistration = d->m_pPFWFactory->getFramework()->getPluginContext()->
                    registerService<QTKApplicationLauncher>(d->m_pAppLauncher.data());

            // must start the launcher AFTER service registration because this method
            // blocks and runs the application on the current thread.  This method
            // will return only after the application has stopped.
            return d->m_pAppLauncher->start(argument);
        }
        return d->m_pAppLauncher->reStart(argument);
    } catch (const QTKException &e) {
        qWarning() << "Application launch failed:" << e.printStackTrace();
        throw;
    } catch (const std::exception &e) {
        qWarning() << "Application launch failed:" << e.what();
        throw;
    }
}

QTKPluginContext* QTKPluginFrameworkLauncher::startup(QRunnable *pEndSplashHandler)
{
    if (d->m_bRunning) {
        throw QTKIllegalStateException("Framework already running.");
    }
    QTKPluginFrameworkProperties::initializeProperties();
    QTKLocationManager::initializeLocations();
    d->loadConfigurationInfo();
    d->m_pPFWFactory.reset(new QTKPluginFrameworkFactory(QTKPluginFrameworkProperties::getProperties()));
    d->m_pPFWFactory->getFramework()->start();
    d->loadBasicPlugins();
    d->m_bRunning = true;

    if (nullptr != pEndSplashHandler) {
        pEndSplashHandler->run();
    }

    return d->m_pPFWFactory->getFramework()->getPluginContext();
}

void QTKPluginFrameworkLauncher::shutdown()
{
    if (!d->m_bRunning || nullptr == d->m_pPFWFactory) {
        return;
    }

    if (d->m_pAppLauncher) {
        d->m_pAppLauncher->shutdown();
    }

    QTKPluginFrameworkLauncher::stop();
    d->m_bRunning = false;
}

long QTKPluginFrameworkLauncher::install(const QString &strSymbolicName, QTKPluginContext *pContext)
{
    QSharedPointer<QTKPlugin> pPlugin = d->install(strSymbolicName, pContext);
    if (pPlugin) {
        return pPlugin->getPluginId();
    }
    return -1;
}

bool QTKPluginFrameworkLauncher::start(const QString &strSymbolicName, QTKPlugin::StartOptions options,
                                       QTKPluginContext *pContext)
{
    // instantiate and start the framework
    if (nullptr == pContext && nullptr == d->m_pPFWFactory) {
        d->m_pPFWFactory.reset(new QTKPluginFrameworkFactory(d->m_pfwProperties));
        try {
            d->m_pPFWFactory->getFramework()->start();
        } catch (const QTKPluginException &e) {
            qCritical() << "Failed to start the plug-in framework:" << e;
            d->m_pPFWFactory.reset();
            return false;
        }
    } else if (nullptr == pContext && d->m_pPFWFactory->getFramework()->getState() != QTKPlugin::State_Active) {
        try {
            d->m_pPFWFactory->getFramework()->start(options);
        } catch (const QTKPluginException &e) {
            qCritical() << "Failed to start the plug-in framework:" << e;
            d->m_pPFWFactory.reset();
            return false;
        }
    }

    if(!strSymbolicName.isEmpty()) {
        QString strPluginPath = getPluginPath(strSymbolicName);
        if (strPluginPath.isEmpty()) {
            return false;
        }

        QTKPluginContext *pPluginContext = pContext ? pContext : getPluginContext();
        try {
            pPluginContext->installPlugin(QUrl::fromLocalFile(strPluginPath))->start(options);
        } catch (const QTKPluginException &e) {
            qWarning() << "Failed to install plugin:" << e;
            return false;
        }
    }

    return true;
}

bool QTKPluginFrameworkLauncher::stop(const QString &strSymbolicName,
                                      QTKPlugin::StopOptions options, QTKPluginContext *pContext)
{
    if (nullptr == d->m_pPFWFactory) {
        return true;
    }

    QTKPluginContext *pPluginContext = pContext ? pContext : getPluginContext();
    if (nullptr == pPluginContext) {
        qWarning() << "No valid plug-in context available";
        return false;
    }

    if(!strSymbolicName.isEmpty()) {
        QString strPluginPath = getPluginPath(strSymbolicName);
        if (strPluginPath.isEmpty()) {
            return false;
        }

        try {
            QList<QSharedPointer<QTKPlugin> > listPlugins = pPluginContext->getPlugins();
            foreach(QSharedPointer<QTKPlugin> pPlugin, listPlugins) {
                if (pPlugin->getSymbolicName() == strSymbolicName) {
                    pPlugin->stop(options);
                    return true;
                }
            }
            qWarning() << "Plug-in" << strSymbolicName << "not found";
            return false;
        } catch (const QTKPluginException &e) {
            qWarning() << "Failed to stop plug-in:" << e;
            return false;
        }
    } else {
        // stop the framework
        QSharedPointer<QTKPluginFramework> pPFW = qSharedPointerCast<QTKPluginFramework>(pPluginContext->getPlugin(0));
        try {
            pPFW->stop();
            QTKPluginFrameworkEvent pfwEvent = pPFW->waitForStop(5000);
            if (pfwEvent.getType() == QTKPluginFrameworkEvent::Type_FrameworkWaitTimeOut) {
                qWarning() << "Stopping the plugin framework timed out";
                return false;
            }
        } catch (const QTKRuntimeException &e) {
            qWarning() << "Stopping the plugin framework failed: " << e;
            return false;
        }

        return true;
    }
}

void QTKPluginFrameworkLauncher::resolve(const QSharedPointer<QTKPlugin> &plugin)
{
    d->resolvePlugin(plugin);
}

void QTKPluginFrameworkLauncher::resolve()
{
    QList<QSharedPointer<QTKPlugin> > listPlugins = QTKPluginFrameworkLauncher::getPluginFramework()->getPluginContext()->getPlugins();
    foreach(const QSharedPointer<QTKPlugin> &plugin, listPlugins) {
        QTKPluginFrameworkLauncher::resolve(plugin);
    }
}

QTKPluginContext* QTKPluginFrameworkLauncher::getPluginContext()
{
    if (nullptr == d->m_pPFWFactory) {
        return nullptr;
    }
    return d->m_pPFWFactory->getFramework()->getPluginContext();
}

QSharedPointer<QTKPluginFramework> QTKPluginFrameworkLauncher::getPluginFramework()
{
    if (d->m_pPFWFactory) {
        return d->m_pPFWFactory->getFramework();
    }
    return QSharedPointer<QTKPluginFramework>();
}

void QTKPluginFrameworkLauncher::appendPathEnv(const QString &strPath)
{
#ifdef _WIN32
#ifdef __MINGW32__
    QString strPathVar("PATH");
    QString strOldPath(getenv("PATH"));
    strPathVar += "=" + strOldPath + ";" + strPath;
    if(_putenv(qPrintable(strPathVar)))
#else
    std::size_t bufferLength;
    getenv_s(&bufferLength, nullptr, 0, "PATH");
    QString strNewPath = strPath;
    if (bufferLength > 0)
    {
        char* psOldPath = new char[bufferLength];
        getenv_s(&bufferLength, psOldPath, bufferLength, "PATH");
        strNewPath.append(";").append(psOldPath);
        delete[] psOldPath;
    }
    qDebug() << "new PATH:" << strNewPath;
    if(_putenv_s("PATH", qPrintable(strNewPath)))
#endif
    {
        LPVOID lpMsgBuf;
        DWORD dw = GetLastError();

        FormatMessageW(
                    FORMAT_MESSAGE_ALLOCATE_BUFFER |
                    FORMAT_MESSAGE_FROM_SYSTEM |
                    FORMAT_MESSAGE_IGNORE_INSERTS,
                    nullptr,
                    dw,
                    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                    (LPWSTR) &lpMsgBuf,
                    0, nullptr );

        // Avoid project configuration conflicts regarding wchar_t considered
        // a built-in type or not by using QString::fromUtf16 instead of
        // QString::fromWCharArray
        // sa http://qt-project.org/wiki/toStdWStringAndBuiltInWchar
        QString strMsg = QString("Adding '%1' to the PATH environment variable failed: %2")
                .arg(strPath).arg(QString::fromUtf16(reinterpret_cast<const ushort*>(lpMsgBuf)));

        qWarning() << strMsg;

        LocalFree(lpMsgBuf);
    }
#else
    Q_UNUSED(strPath)
#endif
}

void QTKPluginFrameworkLauncher::addSearchPath(const QString &strSearchPath, bool bAddToPathEnv)
{
    d->m_listPluginSearchPaths.prepend(strSearchPath);
    if (bAddToPathEnv) {
        QTKPluginFrameworkLauncher::appendPathEnv(strSearchPath);
    }
}

QString QTKPluginFrameworkLauncher::getPluginPath(const QString &strSymbolicName)
{
    QString strPluginFileName(strSymbolicName);
    strPluginFileName.replace(".", "_");
    foreach(QString strSearchPath, d->m_listPluginSearchPaths) {
        QDirIterator dirIter(strSearchPath, d->m_listPluginLibFilter, QDir::Files);
        while(dirIter.hasNext()) {
            dirIter.next();
            QFileInfo fileInfo = dirIter.fileInfo();
            QString strFileBaseName = fileInfo.baseName();
            if (strFileBaseName.startsWith("lib")) {
                strFileBaseName = strFileBaseName.mid(3);
            }

            if (strFileBaseName == strPluginFileName) {
                return fileInfo.canonicalFilePath();
            }
        }
    }

    return QString();
}

QStringList QTKPluginFrameworkLauncher::getPluginSymbolicNames(const QString &strSearchPath)
{
    QStringList listResult;
    QDirIterator dirIter(strSearchPath, d->m_listPluginLibFilter, QDir::Files);
    while(dirIter.hasNext()) {
        dirIter.next();
        QFileInfo fileInfo = dirIter.fileInfo();
        QString strFileBaseName = fileInfo.baseName();
        if (strFileBaseName.startsWith("lib")) {
            strFileBaseName = strFileBaseName.mid(3);
        }
        listResult << strFileBaseName.replace("_", ".");
    }

    return listResult;
}

QTK_PLUGINFRAMEWORK_END_NAMESPACE
