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

#ifndef _QEXTOSGIPLUGINPRIVATE_P_H
#define _QEXTOSGIPLUGINPRIVATE_P_H

#include <qextOsgiPlugin.h>
#include <qextOsgiPluginException.h>
#include <private/qextOsgiRequirePlugin_p.h>

#include <QHash>
#include <QPluginLoader>
#include <QDateTime>
#include <QFileInfo>
#include <QMutex>
#include <QWaitCondition>


class QExtOsgiPluginActivator;
class QExtOsgiPluginArchive;
class QExtOsgiPluginFrameworkContext;

/**
 * \ingroup PluginFramework
 */
class QExtOsgiPluginPrivate {

protected:

    const QWeakPointer<QExtOsgiPlugin> q_ptr;

    class LockObject
    {
    public:

        LockObject() {};

        void lock();
        bool tryLock();
        bool tryLock(int timeout);
        void unlock();

        bool wait(unsigned long time = ULONG_MAX);
        void wakeAll();
        void wakeOne();

    private:

        Q_DISABLE_COPY(LockObject)

        QMutex m_Lock;
        QWaitCondition m_Condition;
    };

public:

    inline QWeakPointer<QExtOsgiPlugin> q_func() { return q_ptr; }
    inline QWeakPointer<const QExtOsgiPlugin> q_func() const { return q_ptr; }
    friend class QExtOsgiPlugin;

    struct Locker
    {
        Locker(LockObject* obj) : m_Obj(obj) { m_Obj->lock(); }
        ~Locker() { m_Obj->unlock(); }
    private:
        LockObject* m_Obj;
    };

    /**
   * Construct a new plugin based on a QExtOsgiPluginArchive.
   *
   * @param fw QExtOsgiPluginFrameworkContext for this plugin.
   * @param ba QExtOsgiPlugin archive representing the shared library and cached data
   * @param checkContext AccessConrolContext to do permission checks against.
   * @exception QExtInvalidArgumentException Faulty manifest for bundle
   */
    QExtOsgiPluginPrivate(QWeakPointer<QExtOsgiPlugin> qq, QExtOsgiPluginFrameworkContext* fw,
                     QSharedPointer<QExtOsgiPluginArchive> pa /*, Object checkContext*/);

    /**
   * Construct a new empty QExtOsgiPlugin.
   *
   * Only called for the system plugin
   *
   * @param fw Framework for this plugin.
   */
    QExtOsgiPluginPrivate(QWeakPointer<QExtOsgiPlugin> qq,
                     QExtOsgiPluginFrameworkContext* fw,
                     long id,
                     const QString& loc,
                     const QString& sym,
                     const QExtOsgiVersion& ver);

    virtual ~QExtOsgiPluginPrivate();

    /**
   * Get updated plugin state. That means check if an installed
   * plugin has been resolved.
   *
   * @return QExtOsgiPlugin state
   */
    QExtOsgiPlugin::State getUpdatedState();

    /**
   * Get root for persistent storage area for this plugin.
   *
   * @return A QDir object representing the data root.
   */
    QFileInfo getDataRoot();

    /**
   * Set state to INSTALLED. We assume that the plug-in is resolved
   * when entering this method.
   */
    void setStateInstalled(bool sendEvent);

    /**
   * Purge any old files associated with this plug-in.
   */
    void purge();

    /**
   * Save the autostart setting to the persistent plugin storage.
   *
   * @param setting The autostart options to save.
   */
    void setAutostartSetting(const QExtOsgiPlugin::StartOptions& setting);

    void ignoreAutostartSetting();

    void modified();

    /**
   * Performs the actual activation.
   */
    void finalizeActivation();

    const QExtRuntimeException* stop0();

    /**
   * Stop code that is executed in the pluginThread without holding the
   * operationLock.
   */
    const QExtRuntimeException* stop1();

    /**
   *
   */
    void update0(const QUrl &updateLocation, bool wasActive);

    /**
   *
   */
    int getStartLevel();

    /**
   * Wait for an ongoing operation to finish.
   *
   * @param lock QMutex used for locking.
   * @param src Caller to include in exception message.
   * @param longWait True, if we should wait extra long before aborting.
   * @throws QExtOsgiPluginException if the ongoing (de-)activation does not finish
   *         within reasonable time.
   */
    void waitOnOperation(LockObject* lock, const QString& src, bool longWait);

    /**
   *
   */
    QStringList findResourceEntries(const QString& path,
                                    const QString& pattern, bool recurse) const;

    /**
   * Union of flags allowing plugin class access
   */
    static const QExtOsgiPlugin::States RESOLVED_FLAGS;

    QExtOsgiPluginFrameworkContext * const fwCtx;

    /**
   * QExtOsgiPlugin identifier
   */
    const long id;

    /**
   * QExtOsgiPlugin location identifier
   */
    const QString location;

    /**
   * QExtOsgiPlugin symbolic name
   */
    QString symbolicName;

    /**
   * QExtOsgiPlugin version
   */
    QExtOsgiVersion version;

    /**
   * State of the plugin
   */
    QExtOsgiPlugin::State state;

    /**
   * QExtOsgiPlugin archive
   */
    QSharedPointer<QExtOsgiPluginArchive> archive;

    /**
   * Directory for plugin data
   */
    QFileInfo pluginDir;

    /**
   * QExtOsgiPluginContext for the plugin
   */
    QScopedPointer<QExtOsgiPluginContext> pluginContext;

    /**
   * QExtOsgiPluginActivator for the plugin
   */
    QExtOsgiPluginActivator* pluginActivator;

    /**
   * The Qt plugin loader for the plugin
   */
    QPluginLoader pluginLoader;

    /**
   * Time when the plugin was last modified
   */
    QDateTime lastModified;

    /**
   * Stores the default locale entries when uninstalled
   */
    QHash<QString, QString> cachedHeaders;

    /**
   * Stores the raw manifest headers
   */
    QHash<QString, QString> cachedRawHeaders;

    /**
   * Type of operation in progress. Blocks bundle calls during activator and
   * listener calls
   */
    QAtomicInt operation;
    static const int IDLE = 0;
    static const int ACTIVATING = 1;
    static const int DEACTIVATING = 2;
    static const int RESOLVING = 3;
    static const int UNINSTALLING = 4;
    static const int UNRESOLVING = 5;
    static const int UPDATING = 6;

    LockObject operationLock;

    /** Saved exception of resolve failure. */
    QExtOsgiPluginException* resolveFailException;

    /**
   * True when this plugin has its activation policy
   * set to "eager"
   */
    bool eagerActivation;

    /** List of QExtOsgiRequirePlugin entries. */
    QList<QExtOsgiRequirePlugin*> require;

private:

    /** Remember if plugin was started */
    bool wasStarted;

    /**
   * Check manifest and cache certain manifest headers as variables.
   */
    void checkManifestHeaders();

    // This could potentially be run in its own thread,
    // parallelizing plugin activations
    QExtOsgiPluginException* start0();

    void startDependencies();

    /**
   * Remove a plugins registered listeners, registered services and
   * used services.
   *
   */
    void removePluginResources();

    QExtOsgiPlugin::State getUpdatedState_unlocked();

};


#endif // _QEXTOSGIPLUGINPRIVATE_P_H
