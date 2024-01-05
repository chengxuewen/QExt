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

#include <private/qextOsgiPlugin_p.h>
#include <private/qextOsgiPluginArchive_p.h>
#include <private/qextOsgiPluginFrameworkContext_p.h>
#include <private/qextOsgiPluginFrameworkUtil_p.h>
#include <private/qextOsgiServiceReference_p.h>
#include <private/qextOsgiPluginContext_p.h>
#include <private/qextOsgiServices_p.h>
#include <qextOsgiPluginDatabaseException.h>
#include <qextOsgiServiceRegistration.h>
#include <qextOsgiPluginConstants.h>
#include <qextOsgiPluginActivator.h>

// for qext::msecsTo() - remove after switching to Qt 4.7
#include <qextUtils.h>

#include <typeinfo>

const QExtOsgiPlugin::States QExtOsgiPluginPrivate::RESOLVED_FLAGS = QExtOsgiPlugin::RESOLVED | QExtOsgiPlugin::STARTING | QExtOsgiPlugin::ACTIVE | QExtOsgiPlugin::STOPPING;

//----------------------------------------------------------------------------
void QExtOsgiPluginPrivate::LockObject::lock()
{
    m_Lock.lock();
}

//----------------------------------------------------------------------------
bool QExtOsgiPluginPrivate::LockObject::tryLock()
{
    return m_Lock.tryLock();
}

//----------------------------------------------------------------------------
bool QExtOsgiPluginPrivate::LockObject::tryLock(int timeout)
{
    return m_Lock.tryLock(timeout);
}

//----------------------------------------------------------------------------
void QExtOsgiPluginPrivate::LockObject::unlock()
{
    m_Lock.unlock();
}

//----------------------------------------------------------------------------
bool QExtOsgiPluginPrivate::LockObject::wait(unsigned long time)
{
    return m_Condition.wait(&m_Lock, time);
}

//----------------------------------------------------------------------------
void QExtOsgiPluginPrivate::LockObject::wakeAll()
{
    m_Condition.wakeAll();
}

//----------------------------------------------------------------------------
void QExtOsgiPluginPrivate::LockObject::wakeOne()
{
    m_Condition.wakeOne();
}

//----------------------------------------------------------------------------
QExtOsgiPluginPrivate::QExtOsgiPluginPrivate(
    QWeakPointer<QExtOsgiPlugin> qq,
    QExtOsgiPluginFrameworkContext* fw,
    QSharedPointer<QExtOsgiPluginArchive> pa)
    : q_ptr(qq), fwCtx(fw), id(pa->getPluginId()),
    location(pa->getPluginLocation().toString()), state(QExtOsgiPlugin::INSTALLED),
    archive(pa), pluginContext(0), pluginActivator(0), pluginLoader(pa->getLibLocation()),
    resolveFailException(0), eagerActivation(false), wasStarted(false)
{
    //TODO
    //checkCertificates(pa);

    // Get library load hints
    if (fw->props.contains(QExtOsgiPluginConstants::FRAMEWORK_PLUGIN_LOAD_HINTS))
    {
        QVariant loadHintsVariant = fw->props[QExtOsgiPluginConstants::FRAMEWORK_PLUGIN_LOAD_HINTS];
        if (loadHintsVariant.isValid())
        {
            QLibrary::LoadHints loadHints = loadHintsVariant.value<QLibrary::LoadHints>();
            pluginLoader.setLoadHints(loadHints);
        }
    }

    checkManifestHeaders();

    pluginDir = fwCtx->getDataStorage(id);
    //  int oldStartLevel = archive->getStartLevel();
    try
    {
        //TODO: StartLevel Service
        //if (fwCtx->startLevelController == 0)
        //{
        archive->setStartLevel(0);
        //}
        //    else
        //    {
        //      if (oldStartLevel == -1)
        //      {
        //        archive->setStartLevel(fwCtx->startLevelController->getInitialPluginStartLevel());
        //      }
        //    }
    }
    catch (const std::exception& e)
    {
        qDebug() << "Failed to set start level on #" << id << ":" << e.what();
    }

    lastModified = archive->getLastModified();
    if (lastModified.isNull())
    {
        modified();
    }

    // fill require list
    QString requireString = archive->getAttribute(QExtOsgiPluginConstants::REQUIRE_PLUGIN);
    QList<QMap<QString, QStringList> > requireList = QExtOsgiPluginFrameworkUtil::parseEntries(QExtOsgiPluginConstants::REQUIRE_PLUGIN,
                                                                                               requireString, true, true, false);
    QListIterator<QMap<QString, QStringList> > i(requireList);
    while (i.hasNext())
    {
        const QMap<QString, QStringList>& e = i.next();
        const QStringList& res = e.value(QExtOsgiPluginConstants::RESOLUTION_DIRECTIVE);
        const QStringList& version = e.value(QExtOsgiPluginConstants::PLUGIN_VERSION_ATTRIBUTE);
        QExtOsgiRequirePlugin* rp = new QExtOsgiRequirePlugin(this, e.value("$key").front(),
                                                    res.empty() ? QString() : res.front(),
                                                    version.empty() ? QString() : version.front());
        require.push_back(rp);
    }
}

//----------------------------------------------------------------------------
QExtOsgiPluginPrivate::QExtOsgiPluginPrivate(QWeakPointer<QExtOsgiPlugin> qq,
                                             QExtOsgiPluginFrameworkContext* fw,
                                             long id, const QString& loc, const QString& sym, const QExtOsgiVersion& ver)
    : q_ptr(qq), fwCtx(fw), id(id), location(loc), symbolicName(sym), version(ver),
    state(QExtOsgiPlugin::INSTALLED), archive(0), pluginContext(0),
    pluginActivator(0), resolveFailException(0),
    eagerActivation(false), wasStarted(false)
{
    modified();
}

//----------------------------------------------------------------------------
QExtOsgiPluginPrivate::~QExtOsgiPluginPrivate()
{
    qDeleteAll(require);
}

//----------------------------------------------------------------------------
QExtOsgiPlugin::State QExtOsgiPluginPrivate::getUpdatedState()
{
    if (state & QExtOsgiPlugin::INSTALLED)
    {
        Locker sync(&operationLock);
        getUpdatedState_unlocked();
    }
    return state;
}

//----------------------------------------------------------------------------
QExtOsgiPlugin::State QExtOsgiPluginPrivate::getUpdatedState_unlocked()
{
    if (state & QExtOsgiPlugin::INSTALLED)
    {
        try
        {
            if (state == QExtOsgiPlugin::INSTALLED)
            {
                operation.fetchAndStoreOrdered(RESOLVING);
                fwCtx->resolvePlugin(this);
                state = QExtOsgiPlugin::RESOLVED;
                // TODO plugin threading
                //bundleThread().bundleChanged(new BundleEvent(BundleEvent.RESOLVED, this));
                fwCtx->listeners.emitPluginChanged(QExtOsgiPluginEvent(QExtOsgiPluginEvent::RESOLVED, this->q_func()));
                operation.fetchAndStoreOrdered(IDLE);
            }
        }
        catch (const QExtOsgiPluginException& pe)
        {
            if (resolveFailException) delete resolveFailException;
            resolveFailException = new QExtOsgiPluginException(pe);
            this->fwCtx->listeners.frameworkError(this->q_func(), pe);
        }
    }
    return state;
}

//----------------------------------------------------------------------------
QFileInfo QExtOsgiPluginPrivate::getDataRoot()
{
    return pluginDir;
}

//----------------------------------------------------------------------------
void QExtOsgiPluginPrivate::setStateInstalled(bool sendEvent)
{
    Locker sync(&operationLock);

    // Make sure that the context is invalid
    if (pluginContext != 0)
    {
        pluginContext->d_func()->invalidate();
        pluginContext.reset();
    }
    state = QExtOsgiPlugin::INSTALLED;
    if (sendEvent)
    {
        operation.fetchAndStoreOrdered(UNRESOLVING);
        // TODO: plugin thread
        //bundleThread().bundleChanged(new BundleEvent(BundleEvent.UNRESOLVED, this));
        fwCtx->listeners.emitPluginChanged(QExtOsgiPluginEvent(QExtOsgiPluginEvent::UNRESOLVED, this->q_func()));
    }
    operation.fetchAndStoreOrdered(IDLE);
}

//----------------------------------------------------------------------------
void QExtOsgiPluginPrivate::purge()
{
    if (state == QExtOsgiPlugin::UNINSTALLED)
    {
        fwCtx->plugins->remove(location);
    }
    //  Vector fix = oldGenerations;
    //  if (fix != null) {
    //    oldGenerations = null;
    //    for (Iterator i = fix.iterator(); i.hasNext();) {
    //      ((BundleGeneration)i.next()).purge(true);
    //    }
    //  }
}

//----------------------------------------------------------------------------
void QExtOsgiPluginPrivate::setAutostartSetting(const QExtOsgiPlugin::StartOptions& setting) {
    try
    {
        if (archive)
        {
            archive->setAutostartSetting(setting);
        }
    }
    catch (const QExtOsgiPluginDatabaseException& e)
    {
        this->fwCtx->listeners.frameworkError(this->q_func(), e);
    }
}

//----------------------------------------------------------------------------
void QExtOsgiPluginPrivate::ignoreAutostartSetting()
{
    try
    {
        if (archive)
        {
            archive->setAutostartSetting(-1);
        }
    }
    catch (const QExtOsgiPluginDatabaseException& e)
    {
        this->fwCtx->listeners.frameworkError(this->q_func(), e);
    }
}

//----------------------------------------------------------------------------
void QExtOsgiPluginPrivate::modified()
{
    lastModified = QDateTime::currentDateTime();
    if (archive)
    {
        archive->setLastModified(lastModified);
    }
}

//----------------------------------------------------------------------------
void QExtOsgiPluginPrivate::checkManifestHeaders()
{
    symbolicName = archive->getAttribute(QExtOsgiPluginConstants::PLUGIN_SYMBOLICNAME);

    if (symbolicName.isEmpty())
    {
        throw QExtInvalidArgumentException(QString("qextOsgiPlugin has no symbolic name, location=") +
                                           location);
    }

    QString mpv = archive->getAttribute(QExtOsgiPluginConstants::PLUGIN_VERSION);
    if (!mpv.isEmpty())
    {
        try
        {
            version = QExtOsgiVersion(mpv);
        }
        catch (const std::exception& e)
        {
            throw QExtInvalidArgumentException(QString("qextOsgiPlugin does not specify a valid ") +
                                               QExtOsgiPluginConstants::PLUGIN_VERSION + " header. Got exception: " + e.what());
        }
    }

    QSharedPointer<QExtOsgiPlugin> snp = fwCtx->plugins->getPlugin(symbolicName, version);
    // TBD! Should we allow update to same version?
    if (!snp.isNull() && snp->d_func() != this)
    {
        throw QExtInvalidArgumentException(QString("Plugin with same symbolic name and version is already installed (")
                                           + symbolicName + ", " + version.toString() + ")");
    }

    QString ap = archive->getAttribute(QExtOsgiPluginConstants::PLUGIN_ACTIVATIONPOLICY);
    if (QExtOsgiPluginConstants::ACTIVATION_EAGER == ap)
    {
        eagerActivation = true;
    }

}

//----------------------------------------------------------------------------
void QExtOsgiPluginPrivate::finalizeActivation()
{
    Locker sync(&operationLock);

    // 4: Resolve plugin (if needed)
    switch (getUpdatedState_unlocked())
    {
    case QExtOsgiPlugin::INSTALLED:
        Q_ASSERT_X(resolveFailException != 0, Q_FUNC_INFO, "no resolveFailException");
        throw QExtOsgiPluginException(*resolveFailException);
    case QExtOsgiPlugin::STARTING:
        if (operation.fetchAndAddOrdered(0) == ACTIVATING) return; // finalization already in progress.
            // Lazy activation; fall through to RESOLVED.
#if (QT_VERSION >= QT_VERSION_CHECK(5,8,0))
        Q_FALLTHROUGH();
#else
            /* FALLTHRU */
#endif
    case QExtOsgiPlugin::RESOLVED:
    {
        //6:
        state = QExtOsgiPlugin::STARTING;
        operation.fetchAndStoreOrdered(ACTIVATING);
        if (fwCtx->debug.lazy_activation)
        {
            qDebug() << "activating #" << this->id;
        }
        //7:
        if (!pluginContext)
        {
            pluginContext.reset(new QExtOsgiPluginContext(this));
        }
        // start dependencies
        startDependencies();
        //TODO plugin threading
        //QExtRuntimeException* e = bundleThread().callStart0(this);
        QExtRuntimeException* e = start0();
        operation.fetchAndStoreOrdered(IDLE);
        operationLock.wakeAll();
        if (e)
        {
            QExtRuntimeException re(*e);
            delete e;
            throw re;
        }
        break;
    }
    case QExtOsgiPlugin::ACTIVE:
        break;
    case QExtOsgiPlugin::STOPPING:
        // This happens if start is called from inside the QExtOsgiPluginActivator::stop method.
        // Don't allow it.
        throw QExtOsgiPluginException("start called from QExtOsgiPluginActivator::stop",
                                      QExtOsgiPluginException::ACTIVATOR_ERROR);
    case QExtOsgiPlugin::UNINSTALLED:
        throw QExtIllegalStateException("qextOsgiPlugin is in UNINSTALLED state");
    }
}

//----------------------------------------------------------------------------
const QExtRuntimeException* QExtOsgiPluginPrivate::stop0()
{
    wasStarted = state == QExtOsgiPlugin::ACTIVE;
    // 5:
    state = QExtOsgiPlugin::STOPPING;
    operation.fetchAndStoreOrdered(DEACTIVATING);
    // 6-13:
    // TODO plugin threading
    //const QExtRuntimeException* savedException = pluginThread().callStop1(this);
    const QExtRuntimeException* savedException = stop1();
    if (state != QExtOsgiPlugin::UNINSTALLED)
    {
        state = QExtOsgiPlugin::RESOLVED;
        // TODO plugin threading
        //bundleThread().bundleChanged(new BundleEvent(BundleEvent.STOPPED, this));
        fwCtx->listeners.emitPluginChanged(QExtOsgiPluginEvent(QExtOsgiPluginEvent::STOPPED, this->q_func()));

        operationLock.wakeAll();
        operation.fetchAndStoreOrdered(IDLE);
    }
    return savedException;
}

//----------------------------------------------------------------------------
const QExtRuntimeException* QExtOsgiPluginPrivate::stop1()
{
    const QExtRuntimeException* res = 0;

    //6:
    fwCtx->listeners.emitPluginChanged(QExtOsgiPluginEvent(QExtOsgiPluginEvent::STOPPING, q_func()));

    //7:
    if (wasStarted && pluginActivator)
    {
        try
        {
            pluginActivator->stop(pluginContext.data());
            if (state != QExtOsgiPlugin::STOPPING)
            {
                if (state == QExtOsgiPlugin::UNINSTALLED)
                {
                    return new QExtIllegalStateException("Plug-in is uninstalled");
                }
                else
                {
                    return new QExtIllegalStateException("Plug-in changed state because of refresh during stop");
                }
            }
        }
        catch (const QExtException& e)
        {
            res = new QExtOsgiPluginException("qextOsgiPlugin::stop: PluginActivator stop failed",
                                              QExtOsgiPluginException::ACTIVATOR_ERROR, e);
        }
        catch (...)
        {
            res = new QExtOsgiPluginException("qextOsgiPlugin::stop: PluginActivator stop failed",
                                              QExtOsgiPluginException::ACTIVATOR_ERROR);
        }
        pluginActivator = 0;
    }

    if (operation.fetchAndAddOrdered(0) == DEACTIVATING)
    {
        // Call hooks after we've called PluginActivator::stop(), but before we've
        // cleared all resources
        if (pluginContext)
        {
            // TODO service listener hooks
            //fwCtx->listeners.serviceListeners.hooksBundleStopped(this);

            //8-10:
            removePluginResources();
            pluginContext->d_func()->invalidate();
            pluginContext.reset();
        }
    }

    // This would unload the shared library and delete the activator if
    // there are no dependencies. However, objects from the plug-in might
    // have been created via C-function symbol lookups. Hence we cannot
    // safely unload the DLL. Maybe implement a in-DLL counter later
    // (http://stackoverflow.com/questions/460809/c-dll-unloading-issue and
    // http://boost.2283326.n4.nabble.com/shared-ptr-A-smarter-smart-pointer-proposal-for-dynamic-libraries-td2649749.html).
    // The activator itself will be delete during program termination
    // (by the QPluginLoader instance).
    //pluginLoader.unload();

    return res;
}

//----------------------------------------------------------------------------
void QExtOsgiPluginPrivate::update0(const QUrl& updateLocation, bool wasActive)
{
    const bool wasResolved = state == QExtOsgiPlugin::RESOLVED;
    const int oldStartLevel = getStartLevel();
    QSharedPointer<QExtOsgiPluginArchive> newArchive;

    operation.fetchAndStoreOrdered(UPDATING);
    try
    {
        // New plugin as stream supplied?
        QUrl updateUrl(updateLocation);
        if (updateUrl.isEmpty())
        {
            // Try Plugin-UpdateLocation
            QString update = archive != 0 ? archive->getAttribute(QExtOsgiPluginConstants::PLUGIN_UPDATELOCATION) : QString();
            if (update.isEmpty())
            {
                // Take original location
                updateUrl = location;
            }
        }

        if(updateUrl.scheme() != "file")
        {
            QString msg = "Unsupported update URL:";
            msg += updateUrl.toString();
            throw QExtOsgiPluginException(msg);
        }

        newArchive = fwCtx->storage->updatePluginArchive(archive, updateUrl, updateUrl.toLocalFile());
        //checkCertificates(newArchive);
        checkManifestHeaders();
        newArchive->setStartLevel(oldStartLevel);
        fwCtx->storage->replacePluginArchive(archive, newArchive);
    }
    catch (const std::exception& e)
    {
        if (!newArchive.isNull())
        {
            newArchive->purge();
        }
        operation.fetchAndStoreOrdered(IDLE);
        if (wasActive)
        {
            try
            {
                this->q_func().toStrongRef()->start();
            }
            catch (const QExtOsgiPluginException& pe)
            {
                fwCtx->listeners.frameworkError(this->q_func(), pe);
            }
        }
        try
        {
            const QExtOsgiPluginException& pe = dynamic_cast<const QExtOsgiPluginException&>(e);
            throw pe;
        }
        catch (const std::bad_cast&)
        {
            throw QExtOsgiPluginException(QString("Failed to get update plugin: ") + e.what(),
                                          QExtOsgiPluginException::UNSPECIFIED);
        }
    }

    bool purgeOld = false;
    // TODO: check if dependent plug-ins are started. If not, set purgeOld to true.

    // Activate new plug-in
    QSharedPointer<QExtOsgiPluginArchive> oldArchive = archive;
    archive = newArchive;
    cachedRawHeaders.clear();
    state = QExtOsgiPlugin::INSTALLED;

    // Purge old archive
    if (purgeOld)
    {
        //secure.purge(this, oldProtectionDomain);
        if (oldArchive != 0)
        {
            oldArchive->purge();
        }
    }

    // Broadcast events
    if (wasResolved)
    {
        // TODO: use plugin threading
        //bundleThread().bundleChanged(new BundleEvent(BundleEvent.UNRESOLVED, this));
        fwCtx->listeners.emitPluginChanged(QExtOsgiPluginEvent(QExtOsgiPluginEvent::UNRESOLVED, this->q_func()));
    }
    //bundleThread().bundleChanged(new BundleEvent(BundleEvent.UPDATED, this));
    fwCtx->listeners.emitPluginChanged(QExtOsgiPluginEvent(QExtOsgiPluginEvent::UPDATED, this->q_func()));
    operation.fetchAndStoreOrdered(IDLE);

    // Restart plugin previously stopped in the operation
    if (wasActive)
    {
        try
        {
            this->q_func().toStrongRef()->start();
        }
        catch (const QExtOsgiPluginException& pe)
        {
            fwCtx->listeners.frameworkError(this->q_func(), pe);
        }
    }
}

//----------------------------------------------------------------------------
int QExtOsgiPluginPrivate::getStartLevel()
{
    if (archive != 0)
    {
        return archive->getStartLevel();
    }
    else
    {
        return 0;
    }
}

//----------------------------------------------------------------------------
void QExtOsgiPluginPrivate::waitOnOperation(LockObject* lock, const QString& src, bool longWait)
{
    if (operation.fetchAndAddOrdered(0) != IDLE)
    {
        qint64 left = longWait ? 20000 : 500;
        QDateTime waitUntil = QDateTime::currentDateTime().addMSecs(left);
        do
        {
            lock->wait(left);
            if (operation.fetchAndAddOrdered(0) == IDLE)
            {
                return;
            }
            // TODO use Qt 4.7 QDateTime::msecsTo() API
            //left = QDateTime::currentDateTime().msecsTo(waitUntil);
            left = qext::msecsTo(QDateTime::currentDateTime(), waitUntil);
        } while (left > 0);

        QString op;
        switch (operation.fetchAndAddOrdered(0))
        {
        case IDLE:
            // Should not happen!
            return;
        case ACTIVATING:
            op = "start";
            break;
        case DEACTIVATING:
            op = "stop";
            break;
        case RESOLVING:
            op = "resolve";
            break;
        case UNINSTALLING:
            op = "uninstall";
            break;
        case UNRESOLVING:
            op = "unresolve";
            break;
        case UPDATING:
            op = "update";
            break;
        default:
            op = "unknown operation";
            break;
        }
        throw QExtOsgiPluginException(src + " called during " + op + " of plug-in",
                                      QExtOsgiPluginException::STATECHANGE_ERROR);
    }
}

//----------------------------------------------------------------------------
QStringList QExtOsgiPluginPrivate::findResourceEntries(const QString& path,
                                                       const QString& pattern, bool recurse) const
{
    QStringList result;
    QStringList resources = archive->findResourcesPath(path);
    foreach(QString fp, resources)
    {
        QString lastComponentOfPath = fp.section('/', -1);
        bool isDirectory = fp.endsWith("/");

        if (!isDirectory &&
            (pattern.isNull() || QExtOsgiPluginFrameworkUtil::filterMatch(pattern, lastComponentOfPath)))
        {
            result << (path + fp);
        }
        if (isDirectory && recurse)
        {
            QStringList subResources = findResourceEntries(fp, pattern, recurse);
            foreach (QString subResource, subResources)
            {
                result << (path + subResource);
            }
        }
    }
    return result;
}

//----------------------------------------------------------------------------
void QExtOsgiPluginPrivate::startDependencies()
{
    QListIterator<QExtOsgiRequirePlugin*> i(this->require);
    while (i.hasNext())
    {
        QExtOsgiRequirePlugin* pr = i.next();
        QList<QExtOsgiPlugin*> pl = fwCtx->plugins->getPlugins(pr->name, pr->pluginRange);
        if (pl.isEmpty())
        {
            if (pr->resolution == QExtOsgiPluginConstants::RESOLUTION_MANDATORY)
            {
                // We should never get here, since the plugin can only be
                // started if all its dependencies could be resolved.
                throw QExtOsgiPluginException(
                    QString("Internal error: dependent plugin %1 inside version range %2 is not installed.").
                    arg(pr->name).arg(pr->pluginRange.toString()));
            }
            else
            {
                continue;
            }
        }

        // We take the first plugin in the list (highest version number)
        // Immediately start the dependencies (no lazy activation) but do not
        // change the autostart setting of the plugin.
        pl.front()->start(QExtOsgiPlugin::START_TRANSIENT);
    }
}

//----------------------------------------------------------------------------
QExtOsgiPluginException* QExtOsgiPluginPrivate::start0()
{
    QExtOsgiPluginException* res = 0;

    fwCtx->listeners.emitPluginChanged(QExtOsgiPluginEvent(QExtOsgiPluginEvent::STARTING, this->q_func()));

    QExtOsgiPluginException::Type error_type = QExtOsgiPluginException::MANIFEST_ERROR;
    try {
        pluginLoader.load();
        if (!pluginLoader.isLoaded())
        {
            error_type = QExtOsgiPluginException::ACTIVATOR_ERROR;
            throw QExtOsgiPluginException(QString("Loading plugin %1 failed: %2").arg(pluginLoader.fileName()).arg(pluginLoader.errorString()),
                                          QExtOsgiPluginException::ACTIVATOR_ERROR);
        }

        pluginActivator = qobject_cast<QExtOsgiPluginActivator*>(pluginLoader.instance());
        if (!pluginActivator)
        {
            throw QExtOsgiPluginException(QString("Creating QExtOsgiPluginActivator instance from %1 failed: %2").arg(pluginLoader.fileName()).arg(pluginLoader.errorString()),
                                          QExtOsgiPluginException::ACTIVATOR_ERROR);
        }

        pluginActivator->start(pluginContext.data());

        if (state != QExtOsgiPlugin::STARTING)
        {
            error_type = QExtOsgiPluginException::STATECHANGE_ERROR;
            if (QExtOsgiPlugin::UNINSTALLED == state)
            {
                throw QExtOsgiPluginException("qextOsgiPlugin uninstalled during start()", QExtOsgiPluginException::STATECHANGE_ERROR);
            }
            else
            {
                throw QExtOsgiPluginException("qextOsgiPlugin changed state because of refresh during start()", QExtOsgiPluginException::STATECHANGE_ERROR);
            }
        }
        state = QExtOsgiPlugin::ACTIVE;
    }
    catch (const QExtException& e)
    {
        res = new QExtOsgiPluginException("qextOsgiPlugin start failed", error_type, e);
    }
    catch (...)
    {
        res = new QExtOsgiPluginException("qextOsgiPlugin start failed", error_type);
    }

    if (fwCtx->debug.lazy_activation)
    {
        qDebug() << "activating #" << id << "completed.";
    }

    if (res == 0)
    {
        //10:
        fwCtx->listeners.emitPluginChanged(QExtOsgiPluginEvent(QExtOsgiPluginEvent::STARTED, this->q_func()));
    }
    else if (operation.fetchAndAddOrdered(0) == ACTIVATING)
    {
        // 8:
        state = QExtOsgiPlugin::STOPPING;
        fwCtx->listeners.emitPluginChanged(QExtOsgiPluginEvent(QExtOsgiPluginEvent::STOPPING, this->q_func()));
        removePluginResources();
        pluginContext->d_func()->invalidate();
        pluginContext.reset();
        state = QExtOsgiPlugin::RESOLVED;
        fwCtx->listeners.emitPluginChanged(QExtOsgiPluginEvent(QExtOsgiPluginEvent::STOPPED, this->q_func()));
    }

    return res;
}

//----------------------------------------------------------------------------
void QExtOsgiPluginPrivate::removePluginResources()
{
    // automatic disconnect due to Qt signal slot
    //fwCtx->listeners.removeAllListeners(this);

    QList<QExtOsgiServiceRegistration> srs = fwCtx->services->getRegisteredByPlugin(this);
    QMutableListIterator<QExtOsgiServiceRegistration> i(srs);
    while (i.hasNext())
    {
        try
        {
            i.next().unregister();
        }
        catch (const QExtIllegalStateException& /*ignore*/)
        {
            // Someone has unregistered the service after stop completed.
            // This should not occur, but we don't want get stuck in
            // an illegal state so we catch it.
        }
    }

    QList<QExtOsgiServiceRegistration> s = fwCtx->services->getUsedByPlugin(q_func());
    QListIterator<QExtOsgiServiceRegistration> i2(s);
    while (i2.hasNext())
    {
        i2.next().getReference().d_func()->ungetService(q_func(), false);
    }

}
