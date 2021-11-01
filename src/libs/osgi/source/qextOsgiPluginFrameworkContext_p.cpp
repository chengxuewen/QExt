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

#include "qtkpluginframeworkcontext_p.h"
#include "qtkpluginframeworkutil_p.h"
#include "qtkpluginframework_p.h"
#include "qtkpluginframeworkproperties_p.h"
#include "qtkpluginarchive_p.h"
#include "qtkpluginstoragesql_p.h"
#include "qtkpluginconstants.h"
#include "qtklocationmanager_p.h"
#include "qtkbasiclocation_p.h"
#include "qtkservices_p.h"

#include <QTKCore/QTKUtils>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

QMutex QTKPluginFrameworkContext::sm_globalFWLock;
int QTKPluginFrameworkContext::sm_iGlobalId = 1;

/**
 * @brief QTKPluginFrameworkContext::QTKPluginFrameworkContext
 * Contruct a framework context
 */
QTKPluginFrameworkContext::QTKPluginFrameworkContext()
    : m_pPlugins(nullptr),
      m_listeners(this),
      m_pServices(nullptr),
      m_pRunTimePlugin(new QTKPluginFramework()),
      m_pStorage(nullptr),
      m_bFirstInit(true),
      m_properties(QTKPluginFrameworkProperties::getProperties()),
      m_bInitialized(false)
{
    {
        QMutexLocker lock(&sm_globalFWLock);
        m_iId = sm_iGlobalId++;
        m_pRunTimePlugin->QTKPlugin::init(new QTKPluginFrameworkPrivate(m_pRunTimePlugin, this));
    }

    this->initProperties();
    this->log() << "created";
}

QTKPluginFrameworkContext::~QTKPluginFrameworkContext()
{
    if (m_bInitialized) {
        this->uninit();
    }
}

void QTKPluginFrameworkContext::initProperties()
{
    m_properties[QTKPluginConstants::FRAMEWORK_VERSION] = "1.0";
    m_properties[QTKPluginConstants::FRAMEWORK_VENDOR] = "QTK";
}

/**
 * @brief QTKPluginFrameworkContext::init
 * Initialize the framework
 */
void QTKPluginFrameworkContext::init()
{
    this->log() << "initializing";

    if (m_debug.bFrameworkEnabled) {
        QTKBasicLocation *pLocation = QTKLocationManager::getConfigurationLocation();
        if (pLocation) {
            this->log() << "Configuration location:" << pLocation->getUrl().toString();
        }
        pLocation = QTKLocationManager::getInstallLocation();
        if (pLocation) {
            this->log() << "Install location:" << pLocation->getUrl().toString();
        }
        pLocation = QTKLocationManager::getQTKHomeLocation();
        if (pLocation) {
            this->log() << "QTK Home location:" << pLocation->getUrl().toString();
        }
        pLocation= QTKLocationManager::getUserLocation();
        if (pLocation) {
            this->log() << "User location:" << pLocation->getUrl().toString();
        }
        pLocation = QTKLocationManager::getInstanceLocation();
        if (pLocation) {
            this->log() << "Instance location" << pLocation->getUrl().toString();
        }
    }


    if (m_bFirstInit && QTKPluginConstants::FRAMEWORK_STORAGE_CLEAN_ON_FIRST_INIT == m_properties[QTKPluginConstants::FRAMEWORK_STORAGE_CLEAN]) {
        this->deleteFWDir();
        m_bFirstInit = false;
    }

    // Pre-load libraries
    // This may speed up installing new plug-ins if they have dependencies on
    // one of these libraries. It prevents repeated loading and unloading of the
    // pre-loaded libraries during caching of the plug-in meta-data.
    if (m_properties[QTKPluginConstants::FRAMEWORK_PRE_LOADLIBS].isValid()) {
        QStringList listPreloadLibs = m_properties[QTKPluginConstants::FRAMEWORK_PRE_LOADLIBS].toStringList();
        QLibrary::LoadHints loadHints;
        QVariant loadHintsVariant = m_properties[QTKPluginConstants::FRAMEWORK_LOAD_HINTS];
        if (loadHintsVariant.isValid()) {
            loadHints = loadHintsVariant.value<QLibrary::LoadHints>();
        }

        foreach(QString preloadLib, listPreloadLibs) {
            QLibrary lib;
            QStringList listNameAndVersion = preloadLib.split("$");

            QString libraryName;
            if (listNameAndVersion.count() == 1) {
                libraryName = listNameAndVersion.front();
                lib.setFileName(listNameAndVersion.front());
            } else if (listNameAndVersion.count() == 2) {
                libraryName = listNameAndVersion.front() + "." + listNameAndVersion.back();
                lib.setFileNameAndVersion(listNameAndVersion.front(), listNameAndVersion.back());
            } else {
                qWarning() << "Wrong syntax in" << preloadLib
                           << ". Use <lib-name>[$version]. Skipping.";
                continue;
            }

            lib.setLoadHints(loadHints);
            this->log() << "Pre-loading library" << lib.fileName()
                        << "with hints [" << static_cast<int>(loadHints) << "]";
            if (!lib.load()) {
                qWarning() << "Pre-loading library" << lib.fileName() << "failed:" << lib.errorString() << "\nCheck your library search paths.";
            }
        }
    }

    QTKPluginFrameworkPrivate* const pRunTimePluginPrivate = m_pRunTimePlugin->d_func();
    pRunTimePluginPrivate->initRunTimePlugin();

    m_pStorage = new QTKPluginStorageSQL(this);
    m_dataStorage = QTKPluginFrameworkUtil::getFileStorage(this, "data");
    m_pServices = new QTKServices(this);
    m_pPlugins = new QTKPlugins(this);

    m_pPlugins->load();

    this->log() << "inited";
    m_bInitialized = true;

    this->log() << "Installed plugins:";
    // Use the ordering in the plugin storage to get a sorted list of plugins.
    QList<QSharedPointer<QTKPluginArchive> > listAllPluginArchives = m_pStorage->getAllPluginArchives();
    foreach (QSharedPointer<QTKPluginArchive> pluginArchive, listAllPluginArchives) {
        QSharedPointer<QTKPlugin> pPlugin = m_pPlugins->getPlugin(pluginArchive->getPluginLocation().toString());
        this->log() << " #" << pPlugin->getPluginId()
                    << " " << pPlugin->getSymbolicName()
                    << ":" << pPlugin->getVersion()
                    << " location:" << pPlugin->getLocation();
    }
}

/**
 * @brief QTKPluginFrameworkContext::uninit
 * Undo as much as possible of what init() does.
 */
void QTKPluginFrameworkContext::uninit()
{
    if (!m_bInitialized) {
        return;
    }

    this->log() << "uninit";

    QTKPluginFrameworkPrivate* const pSystemPluginPrivate = m_pRunTimePlugin->d_func();
    pSystemPluginPrivate->uninitRunTimePlugin();

    delete m_pPlugins;
    m_pPlugins = nullptr;

    m_pStorage->deleteLater();
    m_pStorage = nullptr;

    delete m_pServices;
    m_pServices = nullptr;

    m_bInitialized = false;
}

int QTKPluginFrameworkContext::getId() const
{
    return m_iId;
}

/**
 * @brief QTKPluginFrameworkContext::getDataStorage
 * Get private plugin data storage file handle
 *
 * @param lId
 * @return Return private plugin data storage file info.
 */
QFileInfo QTKPluginFrameworkContext::getDataStorage(long lId)
{
    return QFileInfo(m_dataStorage.absolutePath() + '/' + QString::number(lId) + '/');
}

/**
 * @brief QTKPluginFrameworkContext::checkOurPlugin
 * Check that the plugin belongs to this framework instance.
 *
 * @param pPlugin plugin instance pointer.
 * @throws QTKInvalidArgumentException
 */
void QTKPluginFrameworkContext::checkOurPlugin(QTKPlugin *pPlugin) const
{
    QTKPluginPrivate *pPluginPrivate = pPlugin->d_func();
    if (this != pPluginPrivate->m_pPFWContext) {
        throw QTKInvalidArgumentException("QTKPlugin does not belong to this framework: " + pPlugin->getSymbolicName());
    }
}

/**
 * @brief QTKPluginFrameworkContext::log
 * Log message for debugging framework
 *
 * @return debug handle.
 */
QDebug QTKPluginFrameworkContext::log() const
{
    static QString strNirvana;
    strNirvana.clear();
    if (m_debug.bFrameworkEnabled) {
        return qDebug() << "Framework instance " << this->getId() << ": ";
    } else {
        return QDebug(&strNirvana);
    }
}

/**
 * @brief QTKPluginFrameworkContext::resolvePlugin
 * Check that the plugin specified can resolve all its
 * Require-QTKPlugin constraints.
 *
 * @param pPlugin plugin QTKPlugin to check, must be in QTKPlugin::State_Installed state
 * @throws QTKPluginException
 */
void QTKPluginFrameworkContext::resolvePlugin(QTKPluginPrivate *pPlugin)
{
    if (m_debug.bResolveEnabled) {
        qDebug() << "resolve:" << pPlugin->m_strSymbolicName << "[" << pPlugin->m_lId << "]";
    }

    // If we enter with tempResolved set, it means that we already have
    // resolved plugins. Check that it is true!
    if (m_tempResolved.size() > 0 && !m_tempResolved.contains(pPlugin)) {
        QTKPluginException pPluginException("resolve: InternalError1!", QTKPluginException::Type_ResolveError);
        m_listeners.frameworkError(pPlugin->q_func(), pPluginException);
        throw pPluginException;
    }

    m_tempResolved.clear();
    m_tempResolved.insert(pPlugin);

    this->checkRequirePlugin(pPlugin);

    m_tempResolved.clear();

    if (m_debug.bResolveEnabled) {
        qDebug() << "resolve: Done for" << pPlugin->m_strSymbolicName << "[" << pPlugin->m_lId << "]";
    }
}

void QTKPluginFrameworkContext::checkRequirePlugin(QTKPluginPrivate *pPlugin)
{
    if (!pPlugin->m_listRequirePlugin.isEmpty()) {
        if (m_debug.bResolveEnabled) {
            qDebug() << "checkRequirePlugin: check requiring plugin" << pPlugin->m_lId;
        }

        QListIterator<QTKRequirePlugin*> ite(pPlugin->m_listRequirePlugin);
        while (ite.hasNext()) {
            QTKRequirePlugin *pRequirePlugin = ite.next();
            QList<QTKPlugin *> listPlugin = m_pPlugins->getPlugins(pRequirePlugin->m_strName, pRequirePlugin->m_pluginRange);
            QTKPluginPrivate *pPluginPrivate = nullptr;
            for (QListIterator<QTKPlugin *> iter(listPlugin); iter.hasNext() && pPluginPrivate == nullptr; ) {
                QTKPluginPrivate *pPrivate = iter.next()->d_func();
                if (m_tempResolved.contains(pPrivate)) {
                    pPluginPrivate = pPrivate;
                } else if (QTKPluginPrivate::sm_resolvedFlags & pPrivate->m_eState) {
                    pPluginPrivate = pPrivate;
                } else if (pPrivate->m_eState == QTKPlugin::State_Installed) {
                    QSet<QTKPluginPrivate *> oldTempResolved = m_tempResolved;
                    m_tempResolved.insert(pPrivate);

                    // TODO check if operation locking is correct in case of
                    // multi-threaded plug-in start up. Maybe refactor out the dependency
                    // checking (use the "package" lock)
                    QTKPluginPrivate::QTKLocker sync(&pPrivate->m_operationLock);
                    pPrivate->m_operation.fetchAndStoreOrdered(QTKPluginPrivate::sm_iResolving);
                    this->checkRequirePlugin(pPrivate);
                    m_tempResolved = oldTempResolved;
                    pPrivate->m_eState = QTKPlugin::State_Resolved;
                    m_listeners.emitPluginChanged(QTKPluginEvent(QTKPluginEvent::Type_Resolved, pPrivate->q_func()));
                    pPrivate->m_operation.fetchAndStoreOrdered(QTKPluginPrivate::sm_iIdle);
                    pPluginPrivate = pPrivate;
                }
            }

            if (!pPluginPrivate && pRequirePlugin->m_strResolution == QTKPluginConstants::RESOLUTION_MANDATORY) {
                m_tempResolved.clear();
                if (m_debug.bResolveEnabled) {
                    qDebug() << "checkRequirePlugin: failed to satisfy:" << pRequirePlugin->m_strName;
                }
                throw QTKPluginException(QString("Failed to resolve required plugin: %1").arg(pRequirePlugin->m_strName));
            }
        }
    }
}

/**
 * @brief QTKPluginFrameworkContext::deleteFWDir
 * Delete framework directory if it exists.
 */
void QTKPluginFrameworkContext::deleteFWDir()
{
    QString strDir = QTKPluginFrameworkUtil::getFrameworkDir(this);

    QFileInfo pfwDirInfo(strDir);
    if (pfwDirInfo.exists()) {
        if(pfwDirInfo.isDir()) {
            this->log() << "deleting old framework directory.";
            bool bOK = QTKUtils::removeDirRecursively(pfwDirInfo.absoluteFilePath());
            if(!bOK) {
                qDebug() << "Failed to remove existing fwdir" << pfwDirInfo.absoluteFilePath();
            }
        }
    }
}

QTK_PLUGINFRAMEWORK_END_NAMESPACE
