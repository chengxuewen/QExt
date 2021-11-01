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

#include "qtkplugin.h"
#include "qtkplugin_p.h"
#include "qtkplugincontext.h"
#include "qtkplugincontext_p.h"
#include "qtkpluginframeworkutil_p.h"
#include "qtkpluginarchive_p.h"
#include "qtkpluginframeworkcontext_p.h"
#include "qtkservices_p.h"

#include <QTKCore/QTKUtils>

#include <QStringList>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

QTKPlugin::QTKPlugin()
    : d_ptr(nullptr)
{

}

void QTKPlugin::init(QTKPluginPrivate *pPrivate)
{
    if (nullptr != d_ptr) {
        throw QTKIllegalStateException("QTKPlugin already initialized");
    }
    d_ptr = pPrivate;
}

void QTKPlugin::init(const QWeakPointer<QTKPlugin> &self,
                     QTKPluginFrameworkContext *pPFWContext,
                     QSharedPointer<QTKPluginArchive> pPluginArchive)
{
    if (nullptr != d_ptr) {
        throw QTKIllegalStateException("QTKPlugin already initialized");
    }
    d_ptr = new QTKPluginPrivate(self, pPFWContext, pPluginArchive);
}

QTKPlugin::~QTKPlugin()
{
    delete d_ptr;
}

QTKPlugin::State QTKPlugin::getState() const
{
    Q_D(const QTKPlugin);
    return d->m_eState;
}

void QTKPlugin::start(const StartOptions &options)
{
    Q_D(QTKPlugin);

    if (d->m_eState == State_Uninstalled) {
        throw QTKIllegalStateException("QTKPlugin is uninstalled");
    }

    // Initialize the activation; checks initialization of lazy
    // activation.

    //TODO 1: If activating or deactivating, wait a litle
    // we don't use mutliple threads to start plugins for now
    //waitOnActivation(lock, "QTKPlugin::start", false);

    //2: start() is idempotent, i.e., nothing to do when already started
    if (d->m_eState == State_Active) {
        return;
    }

    //3: Record non-transient start requests.
    if ((options & StartOption_StartTransient) == 0) {
        d->setAutostartSetting(options);
    }

    //4: Resolve plugin (if needed)
    d->getUpdatedState();

    //5: Eager?
    if ((options & StartOption_StartActivationPolicy) && !d->m_bEagerActivation ) {
        if (State_Starting == d->m_eState) return;
        d->m_eState = State_Starting;
        d->m_pPluginContext.reset(new QTKPluginContext(this->d_func()));
        QTKPluginEvent pluginEvent(QTKPluginEvent::Type_LazyActivation, d->q_ptr);
        d->m_pPFWContext->m_listeners.emitPluginChanged(pluginEvent);
    } else {
        d->finalizeActivation();
    }
}

void QTKPlugin::stop(const StopOptions &options)
{
    Q_D(QTKPlugin);

    const QTKRuntimeException* pSavedException = nullptr;

    //1:
    if (State_Uninstalled == d->m_eState) {
        throw QTKIllegalStateException("QTKPlugin is uninstalled");
    }

    // 2: If an operation is in progress, wait a little
    d->waitOnOperation(&d->m_operationLock, "Plugin::stop", false);

    //3:
    if ((options & StopOption_StopTransient) == 0) {
        d->ignoreAutostartSetting();
    }

    switch (d->m_eState)
    {
    case State_Installed:
    case State_Resolved:
    case State_Stopping:
    case State_Uninstalled:
    {
        //4:
        return;
    }
    case State_Active:
    case State_Starting: // Lazy start...
    {
        pSavedException = d->stop0();
        break;
    }
    };

    if (nullptr != pSavedException) {
        if (const QTKPluginException *pPluginExc = dynamic_cast<const QTKPluginException*>(pSavedException)) {
            QTKPluginException pluginException(*pPluginExc);
            delete pSavedException;
            throw pluginException;
        } else {
            QTKRuntimeException runtimeException(*pSavedException);
            delete pSavedException;
            throw runtimeException;
        }
    }
}

void QTKPlugin::update(const QUrl &updateLocation)
{
    Q_D(QTKPlugin);

    QTKPluginPrivate::QTKLocker sync(&d->m_operationLock);
    const bool bWasActive = d->m_eState == State_Active;

    switch (d->getUpdatedState_unlocked())
    {
    case State_Active:
    {
        this->stop(StopOption_StopTransient);
        // Fall through
    }
    case State_Resolved:
    case State_Installed:
    {
        // Load new plugin
        //secure.callUpdate0(this, in, wasActive);
        d->update0(updateLocation, bWasActive);
        break;
    }
    case State_Starting:
    {
        // Wait for RUNNING state, this doesn't happen now
        // since we are synchronized.
        throw QTKIllegalStateException("Plugin is in STARTING state");
    }
    case State_Stopping:
    {
        // Wait for RESOLVED state, this doesn't happen now
        // since we are synchronized.
        throw QTKIllegalStateException("Plugin is in STOPPING state");
    }
    case State_Uninstalled:
    {
        throw QTKIllegalStateException("Plugin is in UNINSTALLED state");
    }
    }
}

void QTKPlugin::uninstall()
{
    Q_D(QTKPlugin);
    {
        QTKPluginPrivate::QTKLocker sync(&d->m_operationLock);
        if (d->m_pArchive) {
            try {
                d->m_pArchive->setStartLevel(-2); // Mark as uninstalled
            } catch (...) {

            }
        }

        switch (d->m_eState)
        {
        case State_Uninstalled:
        {
            throw QTKIllegalStateException("Plugin is in UNINSTALLED state");
        }
        case State_Starting: // Lazy start
        case State_Active:
        case State_Stopping:
        {
            const QTKRuntimeException *pRuntimeException = nullptr;
            try {
                d->waitOnOperation(&d->m_operationLock, "QTKPlugin::uninstall", true);
                if (d->m_eState & (State_Active | State_Starting)) {
                    pRuntimeException = d->stop0();
                }
            } catch (const QTKException &exception) {
                // Force to install
                d->setStateInstalled(false);
                d->m_operationLock.wakeAll();
                pRuntimeException = new QTKRuntimeException("Stopping plug-in failed", exception);
            }
            d->m_operation.fetchAndStoreOrdered(QTKPluginPrivate::sm_iUnInstalling);
            if (nullptr != pRuntimeException) {
                d->m_pPFWContext->m_listeners.frameworkError(this->d_func()->q_func(), *pRuntimeException);
                delete pRuntimeException;
            }
        }

        case State_Resolved:  // Fall through
        case State_Installed:
        {
            d->m_pPFWContext->m_pPlugins->remove(d->m_strLocation);
            if (d->m_operation.fetchAndAddOrdered(0) != QTKPluginPrivate::sm_iUnInstalling) {
                try {
                    d->waitOnOperation(&d->m_operationLock, "Plugin::uninstall", true);
                    d->m_operation.fetchAndStoreOrdered(QTKPluginPrivate::sm_iUnInstalling);
                } catch (const QTKPluginException &pluginException) {
                    // Make sure that the context is invalid
                    if (nullptr != d->m_pPluginContext) {
                        d->m_pPluginContext->d_func()->invalidate();
                        d->m_pPluginContext.reset();
                    }
                    d->m_operation.fetchAndStoreOrdered(QTKPluginPrivate::sm_iUnInstalling);
                    d->m_pPFWContext->m_listeners.frameworkError(this->d_func()->q_func(), pluginException);
                }
            }

            d->m_eState = State_Installed;
            d->m_pPFWContext->m_listeners.emitPluginChanged(QTKPluginEvent(QTKPluginEvent::Type_Unresolved, d->q_func()));
            d->m_mapCachedHeaders = getHeaders();
            d->m_pPluginActivator = nullptr;
            d->m_eState = State_Uninstalled;

            // Purge old archive
            if (d->m_pArchive) {
                d->m_pArchive->purge();
            }
            d->m_operation.fetchAndStoreOrdered(QTKPluginPrivate::sm_iIdle);

            if (d->m_pluginDir.exists()) {
                if (!QTKUtils::removeDirRecursively(d->m_pluginDir.absolutePath())) {
                    d->m_pPFWContext->m_listeners.frameworkError(this->d_func()->q_func(), QTKRuntimeException("Failed to delete plugin data"));
                }
                d->m_pluginDir.setFile("");
            }

            // id, location and headers survive after uninstall.

            // There might be plug-in threads that are running start or stop
            // operations. This will wake them and give them a chance to terminate.
            d->m_operationLock.wakeAll();
            break;
        }
        }
    }
    d->m_pPFWContext->m_listeners.emitPluginChanged(QTKPluginEvent(QTKPluginEvent::Type_Uninstalled, d->q_ptr));
}

QTKPluginContext *QTKPlugin::getPluginContext() const
{
    Q_D(const QTKPlugin);
    return d->m_pPluginContext.data();
}

long QTKPlugin::getPluginId() const
{
    Q_D(const QTKPlugin);
    return d->m_lId;
}

QString QTKPlugin::getLocation() const
{
    Q_D(const QTKPlugin);
    return d->m_strLocation;
}

QHash<QString, QString> QTKPlugin::getHeaders()
{
    Q_D(QTKPlugin);
    if (d->m_mapCachedRawHeaders.empty()) {
        d->m_mapCachedRawHeaders = d->m_pArchive->getUnlocalizedAttributes();
    }

    if (d->m_eState == State_Uninstalled) {
        return d->m_mapCachedHeaders;
    }

    return d->m_mapCachedRawHeaders;
}

QString QTKPlugin::getSymbolicName() const
{
    Q_D(const QTKPlugin);
    return d->m_strSymbolicName;
}

QStringList QTKPlugin::getResourceList(const QString &strPath) const
{
    Q_D(const QTKPlugin);
    return d->m_pArchive->findResourcesPath(strPath);
}

QStringList QTKPlugin::findResources(const QString &strPath,
                                     const QString &strFilePattern, bool bRecurse) const
{
    Q_D(const QTKPlugin);
    return d->findResourceEntries(strPath, strFilePattern, bRecurse);
}

QByteArray QTKPlugin::getResource(const QString &strPath) const
{
    Q_D(const QTKPlugin);
    return d->m_pArchive->getPluginResource(strPath);
}

QTKPluginLocalization QTKPlugin::getPluginLocalization(const QLocale &locale, const QString &strBase) const
{
    Q_D(const QTKPlugin);

    // There are five searching candidates possible:
    // base +
    //    "_" + language1 + "_" + country1 + ".qm"
    // or "_" + language1 + ".qm"
    // or "_" + language2 + "_" + country2 + ".qm"
    // or "_" + language2 + ".qm"
    // or ""  + ".qm"
    //
    // Where language1[_country1[_variation1]] is the requested locale,
    // and language2[_country2[_variation2]] is the default locale.

    QChar localeSep('_');
    QChar baseSep('_');

    QStringList listSearchCandidates;

    QStringList listLocaleParts = locale.name().split(localeSep);
    QStringList listDefaultParts = QLocale().name().split(localeSep);

    listSearchCandidates << baseSep + listLocaleParts[0] + localeSep + listLocaleParts[1];
    listSearchCandidates << baseSep + listLocaleParts[0];
    listSearchCandidates << baseSep + listDefaultParts[0] + localeSep + listDefaultParts[1];
    listSearchCandidates << baseSep + listDefaultParts[0];
    listSearchCandidates << "";

    QString strLocalizationPath = strBase.left(strBase.lastIndexOf('/'));
    QStringList listResource = this->getResourceList(strLocalizationPath);

    foreach(QString strResource, listResource) {
        foreach(QString strCandidate, listSearchCandidates) {
            if (strResource.endsWith(strCandidate + ".qm")) {
                return QTKPluginLocalization(strLocalizationPath + '/' + strResource, locale, d->q_ptr);
            }
        }
    }

    return QTKPluginLocalization();
}

QTKVersion QTKPlugin::getVersion() const
{
    Q_D(const QTKPlugin);
    return d->m_version;
}

QDebug operator<<(QDebug debug, QTKPlugin::State state)
{
    switch (state)
    {
    case QTKPlugin::State_Uninstalled:
    {
        return debug << "State_Uninstalled";
    }
    case QTKPlugin::State_Installed:
    {
        return debug << "State_Installed";
    }
    case QTKPlugin::State_Resolved:
    {
        return debug << "State_Resolved";
    }
    case QTKPlugin::State_Starting:
    {
        return debug << "State_Starting";
    }
    case QTKPlugin::State_Stopping:
    {
        return debug << "State_Stopping";
    }
    case QTKPlugin::State_Active:
    {
        return debug << "State_Active";
    }
    default:
    {
        return debug << "unknown state";
    }
    }
}

QDebug operator<<(QDebug debug, const QTKPlugin &plugin)
{
    debug.nospace() << "QTKPlugin["
                    << "id=" << plugin.getPluginId()
                    << ", state=" << plugin.getState()
                    << ", loc=" << plugin.getLocation()
                    << ", symName=" << plugin.getSymbolicName()
                    << "]";
    return debug.maybeSpace();
}

QDebug operator<<(QDebug debug, QTKPlugin const *pPlugin)
{
    return operator<<(debug, *pPlugin);
}

QTKLogStream& operator<<(QTKLogStream &stream, QTKPlugin const *pPlugin)
{
    stream << pPlugin->getSymbolicName();
    return stream;
}

QTKLogStream& operator<<(QTKLogStream &stream, const QSharedPointer<QTKPlugin> &plugin)
{
    return operator<<(stream, plugin.data());
}

