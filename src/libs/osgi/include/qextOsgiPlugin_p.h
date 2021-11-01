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

#ifndef QTKPLUGIN_P_H
#define QTKPLUGIN_P_H

#include "qtkplugin.h"
#include "qtkversion.h"
#include "qtkpluginexception.h"
#include "qtkrequireplugin_p.h"

#include <QFileInfo>
#include <QSharedPointer>
#include <QPluginLoader>
#include <QDateTime>
#include <QWaitCondition>
#include <QMutex>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

class QTKPluginArchive;
class QTKPluginFrameworkContext;
class QTKPluginActivator;

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKPluginPrivate class
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKPluginPrivate
{
protected:
    class QTKLockObject
    {
    public:
        QTKLockObject() {}

        void lock();
        bool tryLock();
        bool tryLock(int iTimeout);
        void unlock();

        bool wait(unsigned long ulTime = ULONG_MAX);
        void wakeAll();
        void wakeOne();

    private:
        Q_DISABLE_COPY(QTKLockObject)
        QMutex m_lock;
        QWaitCondition m_waitCondition;
    };

    const QWeakPointer<QTKPlugin> q_ptr;

public:
    struct QTKLocker
    {
        QTKLocker(QTKLockObject *pObj) : m_pObj(pObj) { m_pObj->lock(); }
        ~QTKLocker() { m_pObj->unlock(); }

    private:
        QTKLockObject *m_pObj;
    };

    /**
     * @brief QTKPluginPrivate
     * Construct a new plugin based on a QTKPluginArchive.
     *
     * @param qObj Plugin weaker pointer.
     * @param pPFWContext QTKPluginFrameworkContext for this plugin.
     * @param pluginArchive QTKPlugin archive representing the shared library and cached data
     * @exception QTKInvalidArgumentException Faulty manifest for bundle
     */
    QTKPluginPrivate(QWeakPointer<QTKPlugin> qObj, QTKPluginFrameworkContext *pPFWContext,
                     QSharedPointer<QTKPluginArchive> pluginArchive);

    /**
     * @brief QTKPluginPrivate
     * Construct a new empty QTKPlugin. Only called for the system plugin.
     *
     * @param qObj Plugin weaker pointer.
     * @param pPFWContext QTKPluginFrameworkContext for this plugin.
     * @param lId
     * @param loc
     * @param strSymbolicName
     * @param ver
     */
    QTKPluginPrivate(QWeakPointer<QTKPlugin> qObj, QTKPluginFrameworkContext *pPFWContext,
                     long lId, const QString &loc, const QString &strSymbolicName, const QTKVersion &ver);

    virtual ~QTKPluginPrivate();

    inline QWeakPointer<QTKPlugin> q_func() { return q_ptr; }
    inline QWeakPointer<const QTKPlugin> q_func() const { return q_ptr; }

    /**
     * @brief getUpdatedState
     * Get updated plugin state. That means check if an installed plugin has been resolved.
     *
     * @return QTKPlugin state
     */
    QTKPlugin::State getUpdatedState();

    /**
     * @brief getDataRoot
     * Get root for persistent storage area for this plugin.
     *
     * @return A QDir object representing the data root.
     */
    QFileInfo getDataRoot();

    /**
     * @brief setStateInstalled
     * Set state to INSTALLED. We assume that the plug-in is resolved
     * when entering this method.
     * @param bSendEvent
     */
    void setStateInstalled(bool bSendEvent);

    /**
     * @brief purge
     * Purge any old files associated with this plug-in.
     */
    void purge();

    /**
     * @brief setAutostartSetting
     * Save the autostart setting to the persistent plugin storage.
     *
     * @param setting The autostart options to save.
     */
    void setAutostartSetting(const QTKPlugin::StartOptions &setting);
    void ignoreAutostartSetting();
    void modified();

    /**
     * @brief finalizeActivation
     * Performs the actual activation.
     */
    void finalizeActivation();
    const QTKRuntimeException *stop0();

    /**
     * @brief stop1
     * Stop code that is executed in the pluginThread without holding the
     * operationLock.
     * @return
     */
    const QTKRuntimeException *stop1();
    void update0(const QUrl &updateLocation, bool bWasActive);
    int getStartLevel();

    /**
     * @brief waitOnOperation
     * Wait for an ongoing operation to finish.
     *
     * @param pLockObj QMutex used for locking.
     * @param strSrc Caller to include in exception message.
     * @param bLongWait True, if we should wait extra long before aborting.
     * @throws QTKPluginException if the ongoing (de-)activation does not finish
     *         within reasonable time.
     */
    void waitOnOperation(QTKLockObject *pLockObj, const QString &strSrc, bool bLongWait);
    QStringList findResourceEntries(const QString &strPath, const QString &strPattern, bool bRecurse) const;

    static const QTKPlugin::States sm_resolvedFlags;    // Union of flags allowing plugin class access
    QTKPluginFrameworkContext * const m_pPFWContext;
    const long m_lId;   // QTKPlugin identifier
    const QString m_strLocation;    // QTKPlugin location identifier
    QString m_strSymbolicName;  // QTKPlugin symbolic name
    QTKVersion m_version;
    QTKPlugin::State m_eState;  // State of the plugin
    QSharedPointer<QTKPluginArchive> m_pArchive;    // QTKPlugin archive
    QScopedPointer<QTKPluginContext> m_pPluginContext;  // QTKPluginContext for the plugin
    QTKPluginActivator *m_pPluginActivator; // QTKPluginActivator for the plugin
    QFileInfo m_pluginDir;  // Directory for plugin data
    QPluginLoader m_pluginLoader;   // The Qt plugin loader for the plugin
    QDateTime m_lastModified;   // Time when the plugin was last modified
    QHash<QString, QString> m_mapCachedHeaders; // Stores the default locale entries when uninstalled
    QHash<QString, QString> m_mapCachedRawHeaders;  // Stores the raw manifest headers
    /**
     * Type of operation in progress. Blocks bundle calls during activator and
     * listener calls
     */
    QAtomicInt m_operation; // Atomic operation
    QTKLockObject m_operationLock;
    QTKPluginException *m_pResolveFailException;    // Saved exception of resolve failure.
    bool m_bEagerActivation;    // True when this plugin has its activation policy set to "eager"
    QList<QTKRequirePlugin*> m_listRequirePlugin;   // List of QTKRequirePlugin entries.

    static const int sm_iIdle = 0;
    static const int sm_iActivating = 1;
    static const int sm_iDeactivating = 2;
    static const int sm_iResolving = 3;
    static const int sm_iUnInstalling = 4;
    static const int sm_iUnResolving = 5;
    static const int sm_iUpdating = 6;

private:
    friend class QTKPlugin;

    /**
     * @brief checkManifestHeaders
     * Check manifest and cache certain manifest headers as variables.
     */
    void checkManifestHeaders();

    /**
     * @brief start0
     * This could potentially be run in its own thread, parallelizing plugin activations
     * @return
     */
    QTKPluginException *start0();
    void startDependencies();

    /**
     * @brief removePluginResources
     * Remove a plugins registered listeners, registered services and used services.
     */
    void removePluginResources();
    QTKPlugin::State getUpdatedState_unlocked();

    bool m_bLockObject;
};

QTK_PLUGINFRAMEWORK_END_NAMESPACE

#endif // QTKPLUGIN_P_H
