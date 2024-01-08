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

#include <private/qextOsgiPluginFrameworkContext_p.h>
#include <private/qextOsgiPluginFrameworkUtil_p.h>
#include <private/qextOsgiPluginFramework_p.h>
#include <private/qextOsgiPluginFrameworkProperties_p.h>
#include <private/qextOsgiPluginArchive_p.h>
#include <private/qextOsgiPluginStorageSQL_p.h>
#include <qextOsgiPluginConstants.h>
#include <private/qextOsgiLocationManager_p.h>
#include <private/qextOsgiBasicLocation_p.h>
#include <private/qextOsgiServices_p.h>
#include <qextUtils.h>

//----------------------------------------------------------------------------
QMutex QExtOsgiPluginFrameworkContext::globalFwLock;
int QExtOsgiPluginFrameworkContext::globalId = 1;

//----------------------------------------------------------------------------
QExtOsgiPluginFrameworkContext::QExtOsgiPluginFrameworkContext()
    : plugins(0), listeners(this), services(0), systemPlugin(new QExtOsgiPluginFramework()),
    storage(0), firstInit(true), props(QExtOsgiPluginFrameworkProperties::getProperties()),
    initialized(false)
{
    {
        QMutexLocker lock(&globalFwLock);
        id = globalId++;
        systemPlugin->QExtOsgiPlugin::init(new QExtOsgiPluginFrameworkPrivate(systemPlugin, this));
    }

    initProperties();
    log() << "created";
}

//----------------------------------------------------------------------------
QExtOsgiPluginFrameworkContext::~QExtOsgiPluginFrameworkContext()
{
    if (initialized)
    {
        this->uninit();
    }
}

//----------------------------------------------------------------------------
void QExtOsgiPluginFrameworkContext::initProperties()
{
    props[QExtOsgiPluginConstants::FRAMEWORK_VERSION] = "0.9";
    props[QExtOsgiPluginConstants::FRAMEWORK_VENDOR] = "CommonTK";
}

//----------------------------------------------------------------------------
void QExtOsgiPluginFrameworkContext::init()
{
    log() << "initializing";

    if (debug.framework)
    {
        QExtOsgiBasicLocation* location = QExtOsgiLocationManager::getConfigurationLocation();
        if (location)
        {
            log() << "Configuration location:" << location->getUrl().toString();
        }
        location = QExtOsgiLocationManager::getInstallLocation();
        if (location)
        {
            log() << "Install location:" << location->getUrl().toString();
        }
        location = QExtOsgiLocationManager::getCTKHomeLocation();
        if (location)
        {
            log() << "CTK Home location:" << location->getUrl().toString();
        }
        location= QExtOsgiLocationManager::getUserLocation();
        if (location)
        {
            log() << "User location:" << location->getUrl().toString();
        }
        location = QExtOsgiLocationManager::getInstanceLocation();
        if (location)
        {
            log() << "Instance location" << location->getUrl().toString();
        }
    }

    if (firstInit && QExtOsgiPluginConstants::FRAMEWORK_STORAGE_CLEAN_ONFIRSTINIT
                         == props[QExtOsgiPluginConstants::FRAMEWORK_STORAGE_CLEAN])
    {
        deleteFWDir();
        firstInit = false;
    }

    // Pre-load libraries
    // This may speed up installing new plug-ins if they have dependencies on
    // one of these libraries. It prevents repeated loading and unloading of the
    // pre-loaded libraries during caching of the plug-in meta-data.
    if (props[QExtOsgiPluginConstants::FRAMEWORK_PRELOAD_LIBRARIES].isValid())
    {
        QStringList preloadLibs = props[QExtOsgiPluginConstants::FRAMEWORK_PRELOAD_LIBRARIES].toStringList();
        QLibrary::LoadHints loadHints;
        QVariant loadHintsVariant = props[QExtOsgiPluginConstants::FRAMEWORK_PLUGIN_LOAD_HINTS];
        if (loadHintsVariant.isValid())
        {
            loadHints = loadHintsVariant.value<QLibrary::LoadHints>();
        }

        foreach(QString preloadLib, preloadLibs)
        {
            QLibrary lib;
            QStringList nameAndVersion = preloadLib.split("$");

            QString libraryName;
            if (nameAndVersion.count() == 1)
            {
                libraryName = nameAndVersion.front();
                lib.setFileName(nameAndVersion.front());
            }
            else if (nameAndVersion.count() == 2)
            {
                libraryName = nameAndVersion.front() + "." + nameAndVersion.back();
                lib.setFileNameAndVersion(nameAndVersion.front(), nameAndVersion.back());
            }
            else
            {
                qWarning() << "Wrong syntax in" << preloadLib << ". Use <lib-name>[$version]. Skipping.";
                continue;
            }

            lib.setLoadHints(loadHints);
            log() << "Pre-loading library" << lib.fileName() << "with hints [" << static_cast<int>(loadHints) << "]";
            if (!lib.load())
            {
                qWarning() << "Pre-loading library" << lib.fileName() << "failed:" << lib.errorString() << "\nCheck your library search paths.";
            }
        }
    }

    QExtOsgiPluginFrameworkPrivate *const systemPluginPrivate = systemPlugin->d_func();
    systemPluginPrivate->initSystemPlugin();

    storage = new QExtOsgiPluginStorageSQL(this);
    dataStorage = QExtOsgiPluginFrameworkUtil::getFileStorage(this, "data");
    services = new QExtOsgiServices(this);
    plugins = new QExtOsgiPlugins(this);

    plugins->load();

    log() << "inited";
    initialized = true;

    log() << "Installed plugins:";
    // Use the ordering in the plugin storage to get a sorted list of plugins.
    QList<QSharedPointer<QExtOsgiPluginArchive> > allPAs = storage->getAllPluginArchives();
    foreach (QSharedPointer<QExtOsgiPluginArchive> pa, allPAs)
    {
        QSharedPointer<QExtOsgiPlugin> plugin = plugins->getPlugin(pa->getPluginLocation().toString());
        log() << " #" << plugin->getPluginId() << " " << plugin->getSymbolicName() << ":"
              << plugin->getVersion() << " location:" << plugin->getLocation();
    }
}

//----------------------------------------------------------------------------
void QExtOsgiPluginFrameworkContext::uninit()
{
    if (!initialized) return;

    log() << "uninit";

    QExtOsgiPluginFrameworkPrivate *const systemPluginPrivate = systemPlugin->d_func();
    systemPluginPrivate->uninitSystemPlugin();

    plugins->clear();
    delete plugins;
    plugins = 0;

    delete storage; // calls storage->close()
    storage = 0;

    delete services;
    services = 0;

    initialized = false;
}

//----------------------------------------------------------------------------
int QExtOsgiPluginFrameworkContext::getId() const
{
    return id;
}

//----------------------------------------------------------------------------
QFileInfo QExtOsgiPluginFrameworkContext::getDataStorage(long id)
{
    return QFileInfo(dataStorage.absolutePath() + '/' + QString::number(id) + '/');
}

//----------------------------------------------------------------------------
void QExtOsgiPluginFrameworkContext::checkOurPlugin(QExtOsgiPlugin* plugin) const
{
    QExtOsgiPluginPrivate *pp = plugin->d_func();
    if (this != pp->fwCtx)
    {
        throw QExtInvalidArgumentException("qextOsgiPlugin does not belong to this framework: " + plugin->getSymbolicName());
    }
}

//----------------------------------------------------------------------------
QDebug QExtOsgiPluginFrameworkContext::log() const
{
    static QString nirvana;
    nirvana.clear();
    if (debug.framework)
        return qDebug() << "Framework instance " << getId() << ": ";
    else
        return QDebug(&nirvana);
}

//----------------------------------------------------------------------------
void QExtOsgiPluginFrameworkContext::resolvePlugin(QExtOsgiPluginPrivate *plugin)
{
    if (debug.resolve)
    {
        qDebug() << "resolve:" << plugin->symbolicName << "[" << plugin->id << "]";
    }

    // If we enter with tempResolved set, it means that we already have
    // resolved plugins. Check that it is true!
    if (tempResolved.size() > 0 && !tempResolved.contains(plugin))
    {
        QExtOsgiPluginException pe("resolve: InternalError1!", QExtOsgiPluginException::RESOLVE_ERROR);
        listeners.frameworkError(plugin->q_func(), pe);
        throw pe;
    }

    tempResolved.clear();
    tempResolved.insert(plugin);

    checkRequirePlugin(plugin);

    tempResolved.clear();

    if (debug.resolve)
    {
        qDebug() << "resolve: Done for" << plugin->symbolicName << "[" << plugin->id << "]";
    }
}

//----------------------------------------------------------------------------
void QExtOsgiPluginFrameworkContext::checkRequirePlugin(QExtOsgiPluginPrivate *plugin)
{
    if (!plugin->require.isEmpty())
    {
        if (debug.resolve)
        {
            qDebug() << "checkRequirePlugin: check requiring plugin" << plugin->id;
        }

        QListIterator<QExtOsgiRequirePlugin*> i(plugin->require);
        while (i.hasNext())
        {
            QExtOsgiRequirePlugin* pr = i.next();
            QList<QExtOsgiPlugin*> pl = plugins->getPlugins(pr->name, pr->pluginRange);
            QExtOsgiPluginPrivate *ok = 0;
            for (QListIterator<QExtOsgiPlugin*> pci(pl); pci.hasNext() && ok == 0; )
            {
                QExtOsgiPluginPrivate *p2 = pci.next()->d_func();
                if (tempResolved.contains(p2))
                {
                    ok = p2;
                }
                else if (QExtOsgiPluginPrivate::RESOLVED_FLAGS & p2->state)
                {
                    ok = p2;
                }
                else if (p2->state == QExtOsgiPlugin::INSTALLED) {
                    QSet<QExtOsgiPluginPrivate*> oldTempResolved = tempResolved;
                    tempResolved.insert(p2);

                    // TODO check if operation locking is correct in case of
                    // multi-threaded plug-in start up. Maybe refactor out the dependency
                    // checking (use the "package" lock)
                    QExtOsgiPluginPrivate::Locker sync(&p2->operationLock);
                    p2->operation.fetchAndStoreOrdered(QExtOsgiPluginPrivate::RESOLVING);
                    checkRequirePlugin(p2);
                    tempResolved = oldTempResolved;
                    p2->state = QExtOsgiPlugin::RESOLVED;
                    listeners.emitPluginChanged(QExtOsgiPluginEvent(QExtOsgiPluginEvent::RESOLVED, p2->q_func()));
                    p2->operation.fetchAndStoreOrdered(QExtOsgiPluginPrivate::IDLE);
                    ok = p2;
                }
            }

            if (!ok && pr->resolution == QExtOsgiPluginConstants::RESOLUTION_MANDATORY)
            {
                tempResolved.clear();
                if (debug.resolve)
                {
                    qDebug() << "checkRequirePlugin: failed to satisfy:" << pr->name;
                }
                throw QExtOsgiPluginException(QString("Failed to resolve required plugin: %1").arg(pr->name));
            }
        }
    }
}

//----------------------------------------------------------------------------
void QExtOsgiPluginFrameworkContext::deleteFWDir()
{
    QString d = QExtOsgiPluginFrameworkUtil::getFrameworkDir(this);

    QFileInfo fwDirInfo(d);
    if (fwDirInfo.exists())
    {
        if(fwDirInfo.isDir())
        {
            log() << "deleting old framework directory.";
            bool bOK = qext::removeDirRecursively(fwDirInfo.absoluteFilePath());
            if(!bOK)
            {
                qDebug() << "Failed to remove existing fwdir" << fwDirInfo.absoluteFilePath();
            }
        }
    }
}
