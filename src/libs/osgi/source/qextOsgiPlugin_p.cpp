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

#include "qtkplugin_p.h"
#include "qtkpluginconstants.h"
#include "qtkplugindatabaseexception.h"
#include "qtkpluginarchive_p.h"
#include "qtkpluginframeworkcontext_p.h"
#include "qtkpluginframeworkutil_p.h"
#include "qtkpluginactivator.h"
#include "qtkplugincontext_p.h"
#include "qtkservicereference_p.h"
#include "qtkserviceregistration.h"
#include "qtkservices_p.h"

// for qtk::msecsTo() - remove after switching to Qt 4.7
#include <QTKCore/QTKUtils>

#include <typeinfo>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

const QTKPlugin::States QTKPluginPrivate::sm_resolvedFlags = QTKPlugin::State_Resolved
        | QTKPlugin::State_Starting | QTKPlugin::State_Active | QTKPlugin::State_Stopping;

/**
 * @brief QTKPluginPrivate::QTKPluginPrivate
 * @param qObj
 * @param pPFWContext
 * @param pluginArchive
 */
QTKPluginPrivate::QTKPluginPrivate(QWeakPointer<QTKPlugin> qObj,
                                   QTKPluginFrameworkContext* pPFWContext,
                                   QSharedPointer<QTKPluginArchive> pluginArchive)
    : q_ptr(qObj),
      m_pPFWContext(pPFWContext),
      m_lId(pluginArchive->getPluginId()),
      m_strLocation(pluginArchive->getPluginLocation().toString()),
      m_eState(QTKPlugin::State_Installed),
      m_pArchive(pluginArchive),
      m_pPluginContext(nullptr),
      m_pPluginActivator(nullptr),
      m_pluginLoader(pluginArchive->getLibLocation()),
      m_pResolveFailException(nullptr),
      m_bEagerActivation(false),
      m_bLockObject(false)
{
    // Get library load hints
    if (pPFWContext->m_properties.contains(QTKPluginConstants::FRAMEWORK_LOAD_HINTS)) {
        QVariant loadHintsVariant = pPFWContext->m_properties[QTKPluginConstants::FRAMEWORK_LOAD_HINTS];
        if (loadHintsVariant.isValid()) {
            QLibrary::LoadHints loadHints = loadHintsVariant.value<QLibrary::LoadHints>();
            m_pluginLoader.setLoadHints(loadHints);
        }
    }

    this->checkManifestHeaders();

    m_pluginDir = m_pPFWContext->getDataStorage(m_lId);
    try {
        m_pArchive->setStartLevel(0);
    } catch (const std::exception &e) {
        qWarning() << "Failed to set start level on #" << m_lId << ":" << e.what();
    }

    m_lastModified = m_pArchive->getLastModified();
    if (m_lastModified.isNull()) {
        modified();
    }

    // fill require list
    QString strRequireString = m_pArchive->getAttribute(QTKPluginConstants::REQUIRE_PLUGIN);
    QList<QMap<QString, QStringList> > listRequire = QTKPluginFrameworkUtil::parseEntries(QTKPluginConstants::REQUIRE_PLUGIN,
                                                                                          strRequireString, true, true, false);
    QListIterator<QMap<QString, QStringList> > i(listRequire);
    while (i.hasNext()) {
        const QMap<QString, QStringList> map = i.next();
        const QStringList &listRes = map.value(QTKPluginConstants::RESOLUTION_DIRECTIVE);
        const QStringList &listVersion = map.value(QTKPluginConstants::PLUGIN_VERSION_ATTRIBUTE);
        QTKRequirePlugin *pRequirePlugin = new QTKRequirePlugin(this, map.value("$key").front(),
                                                                listRes.empty() ? QString() : listRes.front(),
                                                                listVersion.empty() ? QString() : listVersion.front());
        m_listRequirePlugin.push_back(pRequirePlugin);
    }
}

QTKPluginPrivate::QTKPluginPrivate(QWeakPointer<QTKPlugin> pObj,
                                   QTKPluginFrameworkContext *pPFWContext,
                                   long lId, const QString &strLocation,
                                   const QString &strSymbolicName,
                                   const QTKVersion &ver)
    : q_ptr(pObj),
      m_pPFWContext(pPFWContext),
      m_lId(lId),
      m_strLocation(strLocation),
      m_strSymbolicName(strSymbolicName),
      m_version(ver),
      m_eState(QTKPlugin::State_Installed),
      m_pArchive(nullptr),
      m_pPluginContext(nullptr),
      m_pPluginActivator(nullptr),
      m_pResolveFailException(nullptr),
      m_bEagerActivation(false),
      m_bLockObject(false)
{
    this->modified();
}

QTKPluginPrivate::~QTKPluginPrivate()
{
    qDeleteAll(m_listRequirePlugin);
}

void QTKPluginPrivate::QTKLockObject::lock()
{
    m_lock.lock();
}

bool QTKPluginPrivate::QTKLockObject::tryLock()
{
    return m_lock.tryLock();
}

bool QTKPluginPrivate::QTKLockObject::tryLock(int iTimeout)
{
    return m_lock.tryLock(iTimeout);
}

void QTKPluginPrivate::QTKLockObject::unlock()
{
    m_lock.unlock();
}

bool QTKPluginPrivate::QTKLockObject::wait(unsigned long ulTime)
{
    return m_waitCondition.wait(&m_lock, ulTime);
}

void QTKPluginPrivate::QTKLockObject::wakeAll()
{
    m_waitCondition.wakeAll();
}

void QTKPluginPrivate::QTKLockObject::wakeOne()
{
    m_waitCondition.wakeOne();
}

QTKPlugin::State QTKPluginPrivate::getUpdatedState()
{
    if (m_eState & QTKPlugin::State_Installed) {
        QTKLocker sync(&m_operationLock);
        this->getUpdatedState_unlocked();
    }
    return m_eState;
}

QTKPlugin::State QTKPluginPrivate::getUpdatedState_unlocked()
{
    if (m_eState & QTKPlugin::State_Installed) {
        try {
            if (QTKPlugin::State_Installed == m_eState) {
                m_operation.fetchAndStoreOrdered(sm_iResolving);
                m_pPFWContext->resolvePlugin(this);
                m_eState = QTKPlugin::State_Resolved;
                // TODO plugin threading
                //bundleThread().bundleChanged(new BundleEvent(BundleEvent.RESOLVED, this));
                m_pPFWContext->m_listeners.emitPluginChanged(QTKPluginEvent(QTKPluginEvent::Type_Resolved, this->q_func()));
                m_operation.fetchAndStoreOrdered(sm_iIdle);
            }
        } catch (const QTKPluginException &pe) {
            if (m_pResolveFailException) {
                delete m_pResolveFailException;
            }
            m_pResolveFailException = new QTKPluginException(pe);
            this->m_pPFWContext->m_listeners.frameworkError(this->q_func(), pe);
        }
    }
    return m_eState;
}

QFileInfo QTKPluginPrivate::getDataRoot()
{
    return m_pluginDir;
}

void QTKPluginPrivate::setStateInstalled(bool bSendEvent)
{
    QTKLocker sync(&m_operationLock);

    // Make sure that the context is invalid
    if (nullptr != m_pPluginContext) {
        m_pPluginContext->d_func()->invalidate();
        m_pPluginContext.reset();
    }
    m_eState = QTKPlugin::State_Installed;
    if (bSendEvent) {
        m_operation.fetchAndStoreOrdered(sm_iUnResolving);
        // TODO: plugin thread
        //bundleThread().bundleChanged(new BundleEvent(BundleEvent.UNRESOLVED, this));
        m_pPFWContext->m_listeners.emitPluginChanged(QTKPluginEvent(QTKPluginEvent::Type_Unresolved, this->q_func()));
    }
    m_operation.fetchAndStoreOrdered(sm_iIdle);
}

void QTKPluginPrivate::purge()
{
    if (QTKPlugin::State_Uninstalled == m_eState) {
        m_pPFWContext->m_pPlugins->remove(m_strLocation);
    }
}

void QTKPluginPrivate::setAutostartSetting(const QTKPlugin::StartOptions& setting)
{
    try {
        if (m_pArchive) {
            m_pArchive->setAutostartSetting(setting);
        }
    } catch (const QTKPluginDatabaseException &e) {
        m_pPFWContext->m_listeners.frameworkError(this->q_func(), e);
    }
}

void QTKPluginPrivate::ignoreAutostartSetting()
{
    try {
        if (m_pArchive) {
            m_pArchive->setAutostartSetting(-1);
        }
    } catch (const QTKPluginDatabaseException &e) {
        m_pPFWContext->m_listeners.frameworkError(this->q_func(), e);
    }
}

void QTKPluginPrivate::modified()
{
    m_lastModified = QDateTime::currentDateTime();
    if (m_pArchive) {
        m_pArchive->setLastModified(m_lastModified);
    }
}

void QTKPluginPrivate::checkManifestHeaders()
{
    m_strSymbolicName = m_pArchive->getAttribute(QTKPluginConstants::PLUGIN_SYMBOLIC_NAME);

    if (m_strSymbolicName.isEmpty()) {
        throw QTKInvalidArgumentException(QString("QTKPlugin has no symbolic name, location=") +
                                          m_strLocation);
    }

    QString strPluginVersion = m_pArchive->getAttribute(QTKPluginConstants::PLUGIN_VERSION);
    if (!strPluginVersion.isEmpty()) {
        try {
            m_version = QTKVersion(strPluginVersion);
        } catch (const std::exception &e) {
            throw QTKInvalidArgumentException(QString("QTKPlugin does not specify a valid ") +
                                              QTKPluginConstants::PLUGIN_VERSION + " header. Got exception: " + e.what());
        }
    }

    QSharedPointer<QTKPlugin> snp = m_pPFWContext->m_pPlugins->getPlugin(m_strSymbolicName, m_version);
    // TBD! Should we allow update to same version?
    if (!snp.isNull() && snp->d_func() != this) {
        throw QTKInvalidArgumentException(QString("Plugin with same symbolic name and version is already installed (")
                                          + m_strSymbolicName + ", " + m_version.toString() + ")");
    }

    QString strActivationPolicy = m_pArchive->getAttribute(QTKPluginConstants::PLUGIN_ACTIVATION_POLICY);
    if (QTKPluginConstants::ACTIVATION_EAGER == strActivationPolicy) {
        m_bEagerActivation = true;
    }

}

void QTKPluginPrivate::finalizeActivation()
{
    QTKLocker sync(&m_operationLock);

    // 4: Resolve plugin (if needed)
    switch (getUpdatedState_unlocked())
    {
    case QTKPlugin::State_Installed:
    {
        Q_ASSERT_X(m_pResolveFailException != 0, Q_FUNC_INFO, "no resolveFailException");
        throw QTKPluginException(*m_pResolveFailException);
    }
    case QTKPlugin::State_Starting:
    {
        if (m_operation.fetchAndAddOrdered(0) == sm_iActivating) { // finalization already in progress.
            return;
        }
        // Lazy activation; fall through to RESOLVED.
    }
    case QTKPlugin::State_Resolved:
    {
        //6:
        m_eState = QTKPlugin::State_Starting;
        m_operation.fetchAndStoreOrdered(sm_iActivating);
        if (m_pPFWContext->m_debug.bLazyActivationEnabled) {
            qDebug() << "activating #" << m_lId;
        }
        //7:
        if (nullptr == m_pPluginContext) {
            m_pPluginContext.reset(new QTKPluginContext(this));
        }
        // start dependencies
        this->startDependencies();
        //TODO plugin threading
        //QTKRuntimeException* e = bundleThread().callStart0(this);
        QTKRuntimeException *e = this->start0();
        m_operation.fetchAndStoreOrdered(sm_iIdle);
        m_operationLock.wakeAll();
        if (e) {
            QTKRuntimeException re(*e);
            delete e;
            throw re;
        }
        break;
    }
    case QTKPlugin::State_Active:
    {
        break;
    }
    case QTKPlugin::State_Stopping:
    {
        // This happens if start is called from inside the QTKPluginActivator::stop method.
        // Don't allow it.
        throw QTKPluginException("start called from QTKPluginActivator::stop",
                                 QTKPluginException::Type_ActivatorError);
    }
    case QTKPlugin::State_Uninstalled:
    {
        throw QTKIllegalStateException("QTKPlugin is in UNINSTALLED state");
    }
    }
}

const QTKRuntimeException* QTKPluginPrivate::stop0()
{
    m_bLockObject = m_eState == QTKPlugin::State_Active;
    // 5:
    m_eState = QTKPlugin::State_Stopping;
    m_operation.fetchAndStoreOrdered(sm_iDeactivating);
    // 6-13:
    // TODO plugin threading
    //const QTKRuntimeException* savedException = pluginThread().callStop1(this);
    const QTKRuntimeException *pSavedException = this->stop1();
    if (QTKPlugin::State_Uninstalled != m_eState) {
        m_eState = QTKPlugin::State_Resolved;
        // TODO plugin threading
        //bundleThread().bundleChanged(new BundleEvent(BundleEvent.STOPPED, this));
        m_pPFWContext->m_listeners.emitPluginChanged(QTKPluginEvent(QTKPluginEvent::Type_Stopped, this->q_func()));

        m_operationLock.wakeAll();
        m_operation.fetchAndStoreOrdered(sm_iIdle);
    }
    return pSavedException;
}

const QTKRuntimeException *QTKPluginPrivate::stop1()
{
    const QTKRuntimeException *pRuntimeException = nullptr;

    //6:
    m_pPFWContext->m_listeners.emitPluginChanged(QTKPluginEvent(QTKPluginEvent::Type_Stopping, q_func()));

    //7:
    if (m_bLockObject && m_pPluginActivator) {
        try {
            m_pPluginActivator->stop(m_pPluginContext.data());
            if (QTKPlugin::State_Stopping != m_eState) {
                if (QTKPlugin::State_Uninstalled == m_eState) {
                    return new QTKIllegalStateException("Plug-in is uninstalled");
                } else {
                    return new QTKIllegalStateException("Plug-in changed state because of refresh during stop");
                }
            }
        } catch (const QTKException &e) {
            pRuntimeException = new QTKPluginException("QTKPlugin::stop: PluginActivator stop failed",
                                                       QTKPluginException::Type_ActivatorError, e);
        } catch (...) {
            pRuntimeException = new QTKPluginException("QTKPlugin::stop: PluginActivator stop failed",
                                                       QTKPluginException::Type_ActivatorError);
        }
        m_pPluginActivator = nullptr;
    }

    if (m_operation.fetchAndAddOrdered(0) == sm_iDeactivating) {
        // Call hooks after we've called PluginActivator::stop(), but before we've
        // cleared all resources
        if (nullptr != m_pPluginContext) {
            // TODO service listener hooks
            //fwCtx->listeners.serviceListeners.hooksBundleStopped(this);

            //8-10:
            this->removePluginResources();
            m_pPluginContext->d_func()->invalidate();
            m_pPluginContext.reset();
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

    return pRuntimeException;
}

void QTKPluginPrivate::update0(const QUrl& updateLocation, bool bWasActive)
{
    const bool bWasResolved = m_eState == QTKPlugin::State_Resolved;
    const int iOldStartLevel = this->getStartLevel();
    QSharedPointer<QTKPluginArchive> pNewArchive;

    m_operation.fetchAndStoreOrdered(sm_iUpdating);
    try {
        // New plugin as stream supplied?
        QUrl updateUrl(updateLocation);
        if (updateUrl.isEmpty()) {
            // Try Plugin-UpdateLocation
            QString strUpdate = m_pArchive != 0 ? m_pArchive->getAttribute(QTKPluginConstants::PLUGIN_UPDATE_LOCATION) : QString();
            if (strUpdate.isEmpty()) {
                // Take original location
                updateUrl = m_strLocation;
            }
        }

        if(updateUrl.scheme() != "file") {
            QString strMsg = "Unsupported update URL:";
            strMsg += updateUrl.toString();
            throw QTKPluginException(strMsg);
        }

        pNewArchive = m_pPFWContext->m_pStorage->updatePluginArchive(m_pArchive, updateUrl, updateUrl.toLocalFile());
        //checkCertificates(newArchive);
        this->checkManifestHeaders();
        pNewArchive->setStartLevel(iOldStartLevel);
        m_pPFWContext->m_pStorage->replacePluginArchive(m_pArchive, pNewArchive);
    } catch (const std::exception &e) {
        if (!pNewArchive.isNull()) {
            pNewArchive->purge();
        }
        m_operation.fetchAndStoreOrdered(sm_iIdle);
        if (bWasActive) {
            try {
                this->q_func().data()->start();
            } catch (const QTKPluginException &pe) {
                m_pPFWContext->m_listeners.frameworkError(this->q_func(), pe);
            }
        }

        try {
            const QTKPluginException &pe = dynamic_cast<const QTKPluginException&>(e);
            throw pe;
        } catch (std::bad_cast) {
            throw QTKPluginException(QString("Failed to get update plugin: ") + e.what(),
                                     QTKPluginException::Type_Unspecified);
        }
    }

    bool bPurgeOld = false;
    // TODO: check if dependent plug-ins are started. If not, set purgeOld to true.

    // Activate new plug-in
    QSharedPointer<QTKPluginArchive> pOldArchive = m_pArchive;
    m_pArchive = pNewArchive;
    m_mapCachedRawHeaders.clear();
    m_eState = QTKPlugin::State_Installed;

    // Purge old archive
    if (bPurgeOld) {
        //secure.purge(this, oldProtectionDomain);
        if (nullptr != pOldArchive) {
            pOldArchive->purge();
        }
    }

    // Broadcast events
    if (bWasResolved) {
        // TODO: use plugin threading
        //bundleThread().bundleChanged(new BundleEvent(BundleEvent.UNRESOLVED, this));
        m_pPFWContext->m_listeners.emitPluginChanged(QTKPluginEvent(QTKPluginEvent::Type_Unresolved, this->q_func()));
    }
    //bundleThread().bundleChanged(new BundleEvent(BundleEvent.UPDATED, this));
    m_pPFWContext->m_listeners.emitPluginChanged(QTKPluginEvent(QTKPluginEvent::Type_Updated, this->q_func()));
    m_operation.fetchAndStoreOrdered(sm_iIdle);

    // Restart plugin previously stopped in the operation
    if (bWasActive) {
        try {
            this->q_func().data()->start();
        } catch (const QTKPluginException &pe) {
            m_pPFWContext->m_listeners.frameworkError(this->q_func(), pe);
        }
    }
}

int QTKPluginPrivate::getStartLevel()
{
    if (nullptr != m_pArchive) {
        return m_pArchive->getStartLevel();
    } else {
        return 0;
    }
}

void QTKPluginPrivate::waitOnOperation(QTKLockObject *pLockObj, const QString &strSrc, bool bLongWait)
{
    if (m_operation.fetchAndAddOrdered(0) != sm_iIdle) {
        qint64 iLeft = bLongWait ? 20000 : 500;
        QDateTime waitUntil = QDateTime::currentDateTime().addMSecs(iLeft);
        do {
            pLockObj->wait(iLeft);
            if (m_operation.fetchAndAddOrdered(0) == sm_iIdle) {
                return;
            }
            iLeft = QTKUtils::msecsTo(QDateTime::currentDateTime(), waitUntil);
        } while (iLeft > 0);

        //
        QString strOperation;
        switch (m_operation.fetchAndAddOrdered(0))
        {
        case sm_iIdle:
        {
            // Should not happen!
            return;
        }
        case sm_iActivating:
        {
            strOperation = "start";
            break;
        }
        case sm_iDeactivating:
        {
            strOperation = "stop";
            break;
        }
        case sm_iResolving:
        {
            strOperation = "resolve";
            break;
        }
        case sm_iUnInstalling:
        {
            strOperation = "uninstall";
            break;
        }
        case sm_iUnResolving:
        {
            strOperation = "unresolve";
            break;
        }
        case sm_iUpdating:
        {
            strOperation = "update";
            break;
        }
        default:
        {
            strOperation = "unknown operation";
            break;
        }
        }
        throw QTKPluginException(strSrc + " called during " + strOperation + " of plug-in",
                                 QTKPluginException::Type_StateChangeError);
    }
}

QStringList QTKPluginPrivate::findResourceEntries(const QString &strPath,
                                                  const QString &strPattern, bool bRecurse) const
{
    QStringList listResult;
    QStringList listResources = m_pArchive->findResourcesPath(strPath);
    foreach(QString strFp, listResources) {
        QString strLastComponentOfPath = strFp.section('/', -1);
        bool bsDirectory = strFp.endsWith("/");

        if (!bsDirectory && (strPattern.isNull() ||
                             QTKPluginFrameworkUtil::filterMatch(strPattern, strLastComponentOfPath))) {
            listResult << (strPath + strFp);
        }
        if (bsDirectory && bRecurse) {
            QStringList listSubResources = findResourceEntries(strFp, strPattern, bRecurse);
            foreach (QString strSubResource, listSubResources) {
                listResult << (strPath + strSubResource);
            }
        }
    }
    return listResult;
}

void QTKPluginPrivate::startDependencies()
{
    QListIterator<QTKRequirePlugin*> i(this->m_listRequirePlugin);
    while (i.hasNext()) {
        QTKRequirePlugin *pRequirePlugin = i.next();
        QList<QTKPlugin*> listPlugin = m_pPFWContext->m_pPlugins->getPlugins(pRequirePlugin->m_strName, pRequirePlugin->m_pluginRange);
        if (listPlugin.isEmpty()) {
            if (pRequirePlugin->m_strResolution == QTKPluginConstants::RESOLUTION_MANDATORY) {
                // We should never get here, since the plugin can only be
                // started if all its dependencies could be resolved.
                throw QTKPluginException(
                            QString("Internal error: dependent plugin %1 inside version range %2 is not installed.").
                            arg(pRequirePlugin->m_strName).arg(pRequirePlugin->m_pluginRange.toString()));
            } else {
                continue;
            }
        }

        // We take the first plugin in the list (highest version number)
        // Immediately start the dependencies (no lazy activation) but do not
        // change the autostart setting of the plugin.
        listPlugin.front()->start(QTKPlugin::StartOption_StartTransient);
    }
}

QTKPluginException* QTKPluginPrivate::start0()
{
    QTKPluginException *pPluginException = nullptr;

    m_pPFWContext->m_listeners.emitPluginChanged(QTKPluginEvent(QTKPluginEvent::Type_Starting, this->q_func()));

    QTKPluginException::Type eErrorType = QTKPluginException::Type_ManifestError;
    try {
        m_pluginLoader.load();
        if (!m_pluginLoader.isLoaded()) {
            eErrorType = QTKPluginException::Type_ActivatorError;
            throw QTKPluginException(QString("Loading plugin %1 failed: %2").arg(m_pluginLoader.fileName()).arg(m_pluginLoader.errorString()),
                                     QTKPluginException::Type_ActivatorError);
        }

        m_pPluginActivator = qobject_cast<QTKPluginActivator*>(m_pluginLoader.instance());
        if (nullptr == m_pPluginActivator) {
            throw QTKPluginException(QString("Creating QTKPluginActivator instance from %1 failed: %2").arg(m_pluginLoader.fileName()).arg(m_pluginLoader.errorString()),
                                     QTKPluginException::Type_ActivatorError);
        }

        m_pPluginActivator->start(m_pPluginContext.data());

        if (m_eState != QTKPlugin::State_Starting) {
            eErrorType = QTKPluginException::Type_StateChangeError;
            if (QTKPlugin::State_Uninstalled == m_eState) {
                throw QTKPluginException("QTKPlugin uninstalled during start()", QTKPluginException::Type_StateChangeError);
            } else {
                throw QTKPluginException("QTKPlugin changed state because of refresh during start()", QTKPluginException::Type_StateChangeError);
            }
        }
        m_eState = QTKPlugin::State_Active;
    } catch (const QTKException &e) {
        pPluginException = new QTKPluginException("QTKPlugin start failed", eErrorType, e);
    } catch (...) {
        pPluginException = new QTKPluginException("QTKPlugin start failed", eErrorType);
    }

    if (m_pPFWContext->m_debug.bLazyActivationEnabled) {
        qDebug() << "activating #" << m_lId << "completed.";
    }

    if (nullptr == pPluginException) {
        //10:
        m_pPFWContext->m_listeners.emitPluginChanged(QTKPluginEvent(QTKPluginEvent::Type_Started, this->q_func()));
    } else if (m_operation.fetchAndAddOrdered(0) == sm_iActivating) {
        // 8:
        m_eState = QTKPlugin::State_Stopping;
        m_pPFWContext->m_listeners.emitPluginChanged(QTKPluginEvent(QTKPluginEvent::Type_Stopping, this->q_func()));
        this->removePluginResources();
        m_pPluginContext->d_func()->invalidate();
        m_pPluginContext.reset();
        m_eState = QTKPlugin::State_Resolved;
        m_pPFWContext->m_listeners.emitPluginChanged(QTKPluginEvent(QTKPluginEvent::Type_Stopped, this->q_func()));
    }

    return pPluginException;
}

void QTKPluginPrivate::removePluginResources()
{
    // automatic disconnect due to Qt signal slot
    //fwCtx->listeners.removeAllListeners(this);

    QList<QTKServiceRegistration> listServiceRegistration = m_pPFWContext->m_pServices->getRegisteredByPlugin(this);
    QMutableListIterator<QTKServiceRegistration> i(listServiceRegistration);
    while (i.hasNext()) {
        try {
            i.next().unregister();
        } catch (const QTKIllegalStateException& /*ignore*/) {
            // Someone has unregistered the service after stop completed.
            // This should not occur, but we don't want get stuck in
            // an illegal state so we catch it.
        }
    }

    listServiceRegistration = m_pPFWContext->m_pServices->getUsedByPlugin(q_func());
    QListIterator<QTKServiceRegistration> i2(listServiceRegistration);
    while (i2.hasNext()) {
        i2.next().getReference().d_func()->ungetService(q_func(), false);
    }
}

QTK_PLUGINFRAMEWORK_END_NAMESPACE
