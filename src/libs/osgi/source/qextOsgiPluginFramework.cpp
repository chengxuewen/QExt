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

#include "qtkpluginframework.h"
#include "qtkplugin_p.h"
#include "qtkpluginarchive_p.h"
#include "qtkpluginconstants.h"
#include "qtkpluginframework.h"
#include "qtkpluginframework_p.h"
#include "qtkpluginframeworkcontext_p.h"
#include "Service/Event/qtkevent.h"

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

QTKPluginFramework::QTKPluginFramework() : QTKPlugin()
{
    qRegisterMetaType<QTKPluginFrameworkEvent>("QTKPluginFrameworkEvent");
    qRegisterMetaType<QTKPluginEvent>("QTKPluginEvent");
    qRegisterMetaType<QTKServiceEvent>("QTKServiceEvent");
    qRegisterMetaType<QTKEvent>("QTKEvent");
    qRegisterMetaType<QTKProperties>("QTKProperties");
    qRegisterMetaType<QTKDictionary>("QTKDictionary");
    qRegisterMetaType<QTKServiceReference>("QTKServiceReference");
    qRegisterMetaType<QSharedPointer<QTKPlugin> >("QSharedPointer<QTKPlugin>");
}

/**
 * @brief QTKPluginFramework::init
 *
 * Initialize this %QTKPluginFramework. After calling this method, this %QTKPluginFramework
 * must:
 * <ul>
 * <li>Be in the {@link #QTKPlugin::State_Starting} state.</li>
 * <li>Have a valid Plugin Context.</li>
 * <li>Be at start level 0.</li>
 * <li>Have event handling enabled.</li>
 * <li>Have create QTKPlugin objects for all installed plugins.</li>
 * <li>Have registered any framework services.</li>
 * </ul>
 *
 * <p>
 * This %QTKPluginFramework will not actually be started until {@link #start() start}
 * is called.
 *
 * <p>
 * This method does nothing if called when this %QTKPluginFramework is in the
 * {@link #QTKPlugin::State_Starting}, {@link #QTKPlugin::State_Active} or
 * {@link #QTKPlugin::State_Stopping} states.
 *
 * @throws QTKIllegalStateException If this %QTKPluginFramework could not be initialized. *
 */
void QTKPluginFramework::init()
{
    Q_D(QTKPluginFramework);

    QTKPluginPrivate::QTKLocker sync(&d->m_lockObj);
    d->waitOnOperation(&d->m_lockObj, "Framework.init", true);
    switch (d->m_eState)
    {
    case QTKPlugin::State_Installed:
    case QTKPlugin::State_Resolved:
        break;
    case QTKPlugin::State_Starting:
    case QTKPlugin::State_Active:
        return;
    default:
        throw QTKIllegalStateException("INTERNAL ERROR, Illegal state");
    }
    d->init();
}

/**
 * @brief QTKPluginFramework::waitForStop
 *
 * Wait until this %QTKPluginFramework has completely stopped. The <code>stop</code>
 * and <code>update</code> methods perform an asynchronous
 * stop of the Framework. This method can be used to wait until the
 * asynchronous stop of this Framework has completed. This method will only
 * wait if called when this Framework is in the {@link #QTKPlugin::State_Starting},
 * {@link #QTKPlugin::State_Active}, or {@link #QTKPlugin::State_Stopping} states.
 * Otherwise it will return immediately.
 * <p>
 * A Framework Event is returned to indicate why this Framework has stopped.
 *
 * @param ulTimeout timeout Maximum number of milliseconds to wait until this
 *        Framework has completely stopped. A value of zero will wait indefinitely.
 * @return A Framework Event indicating the reason this method returned. The
 *         following <code>QTKPluginFrameworkEvent</code> types may be returned by
 *         this method.
 *         <ul>
 *         <li>{@link QTKPluginFrameworkEvent#Type_FrameworkStopped STOPPED} - This Framework has
 *         been stopped. </li>
 *
 *         <li>{@link QTKPluginFrameworkEvent#Type_FrameworkStoppedUpdate STOPPED_UPDATE} - This
 *         Framework has been updated which has shutdown and will now
 *         restart.</li>
 *
 *         <li>{@link QTKPluginFrameworkEvent#Type_PluginError ERROR} - The Framework
 *         encountered an error while shutting down or an error has occurred
 *         which forced the framework to shutdown. </li>
 *
 *         <li> {@link QTKPluginFrameworkEvent#Type_FrameworkWaitTimeOut WAIT_TIMEDOUT} - This
 *         method has timed out and returned before this Framework has
 *         stopped.</li>
 *         </ul>
 */
QTKPluginFrameworkEvent QTKPluginFramework::waitForStop(unsigned long ulTimeout)
{
    Q_D(QTKPluginFramework);

    QTKPluginPrivate::QTKLocker sync(&d->m_lockObj);

    // Already stopped?
    if ((d->m_eState & (State_Installed | State_Resolved)) == 0) {
        d->m_stopEvent.bIsNull = true;
        d->m_lockObj.wait(ulTimeout ? ulTimeout : ULONG_MAX);

        if (d->m_stopEvent.bIsNull) {
            return QTKPluginFrameworkEvent(QTKPluginFrameworkEvent::Type_FrameworkWaitTimeOut, this->d_func()->q_func());
        }
    } else if (d->m_stopEvent.bIsNull) {
        // Return this if stop or update have not been called and framework is stopped.
        d->m_stopEvent.bIsNull = false;
        d->m_stopEvent.eType = QTKPluginFrameworkEvent::Type_FrameworkStopped;
    }
    return d->m_stopEvent.bIsNull ? QTKPluginFrameworkEvent() :
                                    QTKPluginFrameworkEvent(QTKPluginFrameworkEvent::Type_FrameworkStopped,
                                                            this->d_func()->q_func());
}

/**
 * @brief QTKPluginFramework::start
 *
 * <p>
 * The following steps are taken to start this %QTKPluginFramework:
 * <ol>
 * <li>If this %QTKPluginFramework is not in the {@link #STARTING} state,
 * {@link #init() initialize} this %QTKPluginFramework.</li>
 * <li>All installed plugins must be started in accordance with each
 * plugin's persistent <i>autostart setting</i>. This means some plugins
 * will not be started, some will be started with <i>lazy activation</i>
 * and some will be started with their <i>declared activation</i> policy.
 * Any exceptions that occur during plugin starting must be wrapped in a
 * {@link QTKPluginException} and then published as a plugin framework event of type
 * {@link QTKPluginFrameworkEvent::Type_PluginError}</li>
 * <li>This %PluinFramework's state is set to {@link #ACTIVE}.</li>
 * <li>A plugin framework event of type {@link QTKPluginFrameworkEvent::Type_FrameworkStarted} is fired</li>
 * </ol>
 *
 * @param options
 */
void QTKPluginFramework::start(const QTKPlugin::StartOptions &options)
{
    Q_UNUSED(options);
    Q_D(QTKPluginFramework);

    QStringList pluginsToStart;
    {
        QTKPluginPrivate::QTKLocker sync(&d->m_lockObj);
        d->waitOnOperation(&d->m_lockObj, "QTKPluginFramework::start", true);

        switch (d->m_eState)
        {
        case State_Installed:
        case State_Resolved:
        {
            d->init();
        }
        case State_Starting:
        {
            d->m_operation.fetchAndStoreOrdered(QTKPluginPrivate::sm_iActivating);
            break;
        }
        case State_Active:
        {
            return;
        }
        default:
        {
            throw QTKIllegalStateException("INTERNAL ERROR, Illegal state");
        }
        }

        pluginsToStart = d->m_pPFWContext->m_pStorage->getStartOnLaunchPlugins();
    }

    d->activate(d->m_pPluginContext.data());

    // Start plugins according to their autostart setting.
    QStringListIterator iter(pluginsToStart);
    while (iter.hasNext()) {
        QSharedPointer<QTKPlugin> pPlugin = d->m_pPFWContext->m_pPlugins->getPlugin(iter.next());
        try {
            const int iAutostartSetting = pPlugin->d_func()->m_pArchive->getAutostartSetting();
            // Launch must not change the autostart setting of a plugin
            StartOptions options = QTKPlugin::StartOption_StartTransient;
            if (QTKPlugin::StartOption_StartActivationPolicy == iAutostartSetting) {
                // Transient start according to the plugins activation policy.
                options |= QTKPlugin::StartOption_StartActivationPolicy;
            }
            pPlugin->start(options);
        } catch (const QTKPluginException &pe) {
            d->m_pPFWContext->m_listeners.frameworkError(pPlugin, pe);
        }
    }

    {
        QTKPluginPrivate::QTKLocker sync(&d->m_lockObj);
        d->m_eState = State_Active;
        d->m_operation = QTKPluginPrivate::sm_iIdle;
        d->m_lockObj.wakeAll();
        d->m_pPFWContext->m_listeners.emitFrameworkEvent(QTKPluginFrameworkEvent(QTKPluginFrameworkEvent::Type_FrameworkStarted,
                                                                                 this->d_func()->q_func()));
    }
}

void QTKPluginFramework::stop(const StopOptions &options)
{
    Q_UNUSED(options)

    Q_D(QTKPluginFramework);
    d->shutdown(false);
}

void QTKPluginFramework::uninstall()
{
    throw QTKPluginException("uninstall of System plugin is not allowed",
                             QTKPluginException::Type_InvalidOperation);
}

QStringList QTKPluginFramework::getResourceList(const QString &strPath) const
{
    QString strResourcePath = QString(":/") + QTKPluginConstants::SYSTEM_PLUGIN_SYMBOLIC_NAME;
    if (strPath.startsWith('/')) {
        strResourcePath += strPath;
    } else {
        strResourcePath += QString("/") + strPath;
    }

    QStringList listPaths;
    QFileInfoList listEntryInfo = QDir(strResourcePath).entryInfoList();
    QListIterator<QFileInfo> infoIter(listEntryInfo);
    while (infoIter.hasNext()) {
        const QFileInfo &resInfo = infoIter.next();
        QString strEntry = resInfo.canonicalFilePath().mid(strResourcePath.size());
        if (resInfo.isDir()) {
            strEntry += "/";
        }

        listPaths << strEntry;
    }

    return listPaths;
}

QByteArray QTKPluginFramework::getResource(const QString &strPath) const
{
    QString strResourcePath = QString(":/") + QTKPluginConstants::SYSTEM_PLUGIN_SYMBOLIC_NAME;
    if (strPath.startsWith('/')) {
        strResourcePath += strPath;
    } else {
        strResourcePath += QString("/") + strPath;
    }

    QFile resourceFile(strResourcePath);
    resourceFile.open(QIODevice::ReadOnly);
    return resourceFile.readAll();
}

QHash<QString, QString> QTKPluginFramework::getHeaders()
{
    //TODO security
    Q_D(QTKPluginFramework);
    return d->m_mapSystemHeaders;
}

QTK_PLUGINFRAMEWORK_END_NAMESPACE
