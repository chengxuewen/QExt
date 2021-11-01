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

#ifndef QTKPLUGINTRACKER_H
#define QTKPLUGINTRACKER_H

#include "qtkpluginframework_global.h"
#include "qtkplugin.h"
#include "qtkplugintrackercustomizer.h"
#include "qtkplugincontext.h"
#include "qtktrackedpluginlistener_p.h"
#include "qtkpluginabstracttracked_p.h"
#include "qtkpluginevent.h"

#include <QMutex>
#include <QDebug>
#include <QScopedPointer>
#include <QSharedPointer>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

template<class T> class QTKTrackedPlugin;
template<class T> class QTKPluginTrackerPrivate;

/**
 * @ingroup QTKPluginFramework
 *
 * The <code>QTKPluginTracker</code> class simplifies tracking plugins much like
 * the <code>QTKServiceTracker</code> simplifies tracking services.
 * <p>
 * A <code>QTKPluginTracker</code> is constructed with state criteria and a
 * <code>QTKPluginTrackerCustomizer</code> object. A <code>QTKPluginTracker</code> can
 * use the <code>QTKPluginTrackerCustomizer</code> to select which plugins are
 * tracked and to create a customized object to be tracked with the plugin. The
 * <code>QTKPluginTracker</code> can then be opened to begin tracking all plugins
 * whose state matches the specified state criteria.
 * <p>
 * The <code>getPlugins</code> method can be called to get the
 * <code>QTKPlugin</code> objects of the plugins being tracked. The
 * <code>getObject</code> method can be called to get the customized object for
 * a tracked plugin.
 * <p>
 * The <code>QTKPluginTracker</code> class is thread-safe. It does not call a
 * <code>QTKPluginTrackerCustomizer</code> while holding any locks.
 * <code>QTKPluginTrackerCustomizer</code> implementations must also be
 * thread-safe.
 *
 * \tparam T The type of the tracked object. The type must be an assignable
 *         datatype, provide a boolean conversion function, and provide
 *         a constructor and an assignment operator which can handle 0 as an argument.
 * \remarks This class is thread safe.
 */
template<class T = QSharedPointer<QTKPlugin> >
class QTKPluginTracker : protected QTKPluginTrackerCustomizer<T>
{
public:
    ~QTKPluginTracker();

    /**
     * @brief QTKPluginTracker
     * Create a <code>QTKPluginTracker</code> for plugins whose state is present in
     * the specified state mask.
     *
     * <p>
     * Plugins whose state is present on the specified state mask will be
     * tracked by this <code>QTKPluginTracker</code>.
     *
     * @param context The <code>QTKPluginContext</code> against which the tracking
     *        is done.
     * @param stateMask The bit mask of the <code>OR</code>ing of the plugin
     *        states to be tracked.
     * @param customizer The customizer object to call when plugins are added,
     *        modified, or removed in this <code>QTKPluginTracker</code>. If
     *        customizer is <code>null</code>, then this
     *        <code>QTKPluginTracker</code> will be used as the
     *        <code>QTKPluginTrackerCustomizer</code> and this
     *        <code>QTKPluginTracker</code> will call the
     *        <code>QTKPluginTrackerCustomizer</code> methods on itself. If the
     *        customizer is not <code>null</code>, this <code>QTKPluginTracker</code>
     *        takes ownership of the customizer.
     * @see QTKPlugin#getState()
     */
    QTKPluginTracker(QTKPluginContext *pContext, QTKPlugin::States stateMask,
                     QTKPluginTrackerCustomizer<T> *pCustomizer = nullptr);

    /**
     * @brief open
     * Open this <code>QTKPluginTracker</code> and begin tracking plugins.
     *
     * <p>
     * QTKPlugin's which match the state criteria specified when this
     * <code>QTKPluginTracker</code> was created are now tracked by this
     * <code>QTKPluginTracker</code>.
     *
     * @throws QTKIllegalStateException If the <code>QTKPluginContext</code>
     *         with which this <code>QTKPluginTracker</code> was created is no
     *         longer valid.
     */
    virtual void open();

    /**
     * @brief close
     * Close this <code>QTKPluginTracker</code>.
     *
     * <p>
     * This method should be called when this <code>QTKPluginTracker</code> should
     * end the tracking of plugins.
     *
     * <p>
     * This implementation calls getPlugins() to get the list of
     * tracked plugins to remove.
     */
    virtual void close();

    /**
     * @brief getPlugins
     * Return a list of <code>QTKPlugin</code>s for all plugins being tracked by
     * this <code>QTKPluginTracker</code>.
     *
     * @return A list of <code>QTKPlugin</code>s.
     */
    virtual QList<QSharedPointer<QTKPlugin> > getPlugins() const;

    /**
     * @brief getObject
     * Returns the customized object for the specified <code>QTKPlugin</code> if
     * the specified plugin is being tracked by this <code>QTKPluginTracker</code>.
     *
     * @param plugin The <code>QTKPlugin</code> being tracked.
     * @return The customized object for the specified <code>QTKPlugin</code> or
     *         <code>null</code> if the specified <code>QTKPlugin</code> is not
     *         being tracked.
     */
    virtual T getObject(QSharedPointer<QTKPlugin> plugin) const;

    /**
     * @brief remove
     * Remove a plugin from this <code>QTKPluginTracker</code>.
     *
     * The specified plugin will be removed from this <code>QTKPluginTracker</code>.
     * If the specified plugin was being tracked then the
     * <code>QTKPluginTrackerCustomizer::removedPlugin</code> method will be called
     * for that plugin.
     *
     * @param plugin The <code>QTKPlugin</code> to be removed.
     */
    virtual void remove(QSharedPointer<QTKPlugin> plugin);

    /**
     * @brief size
     * Return the number of plugins being tracked by this
     * <code>QTKPluginTracker</code>.
     *
     * @return The number of plugins being tracked.
     */
    virtual int size() const;

    /**
     * @brief getTrackingCount
     * Returns the tracking count for this <code>QTKPluginTracker</code>.
     *
     * The tracking count is initialized to 0 when this
     * <code>QTKPluginTracker</code> is opened. Every time a plugin is added,
     * modified or removed from this <code>QTKPluginTracker</code> the tracking
     * count is incremented.
     *
     * <p>
     * The tracking count can be used to determine if this
     * <code>QTKPluginTracker</code> has added, modified or removed a plugin by
     * comparing a tracking count value previously collected with the current
     * tracking count value. If the value has not changed, then no plugin has
     * been added, modified or removed from this <code>QTKPluginTracker</code>
     * since the previous tracking count was collected.
     *
     * @return The tracking count for this <code>QTKPluginTracker</code> or -1 if
     *         this <code>QTKPluginTracker</code> is not open.
     */
    virtual int getTrackingCount() const;

    /**
     * @brief getTracked
     * Return a <code>QMap</code> with the <code>QTKPlugin</code>s and customized
     * objects for all plugins being tracked by this <code>QTKPluginTracker</code>.
     *
     * @return A <code>QMap</code> with the <code>QTKPlugin</code>s and customized
     *         objects for all services being tracked by this
     *         <code>QTKPluginTracker</code>. If no plugins are being tracked, then
     *         the returned map is empty.
     */
    virtual QMap<QSharedPointer<QTKPlugin>, T> getTracked() const;

    /**
     * @brief isEmpty
     * Return if this <code>QTKPluginTracker</code> is empty.
     *
     * @return <code>true</code> if this <code>QTKPluginTracker</code> is not tracking any
     *         plugins.
     */
    virtual bool isEmpty() const;

protected:
    /**
     * @brief addingPlugin
     * Default implementation of the
     * <code>QTKPluginTrackerCustomizer::addingPlugin</code> method.
     *
     * <p>
     * This method is only called when this <code>QTKPluginTracker</code> has been
     * constructed with a <code>null</code> QTKPluginTrackerCustomizer argument.
     *
     * <p>
     * This implementation simply returns the specified <code>QTKPlugin*</code> in
     * a QVariant.
     *
     * <p>
     * This method can be overridden in a subclass to customize the object to be
     * tracked for the plugin being added.
     *
     * @param pPlugin The <code>QTKPlugin</code> being added to this
     *        <code>QTKPluginTracker</code> object.
     * @param event The plugin event which caused this customizer method to be
     *        called or an invalid event if there is no plugin event associated
     *        with the call to this method.
     * @return The specified plugin.
     * @see QTKPluginTrackerCustomizer::addingPlugin(QTKPlugin*, const QTKPluginEvent&)
     */
    T addingPlugin(QSharedPointer<QTKPlugin> pPlugin, const QTKPluginEvent &event);

    /**
     * @brief modifiedPlugin
     * Default implementation of the
     * <code>QTKPluginTrackerCustomizer::modifiedPlugin</code> method.
     *
     * <p>
     * This method is only called when this <code>QTKPluginTracker</code> has been
     * constructed with a <code>null</code> QTKPluginTrackerCustomizer argument.
     *
     * <p>
     * This implementation does nothing.
     *
     * @param pPlugin The <code>QTKPlugin</code> whose state has been modified.
     * @param event The plugin event which caused this customizer method to be
     *        called or an invalid event if there is no plugin event associated
     *        with the call to this method.
     * @param object The customized object for the specified QTKPlugin.
     * @see QTKPluginTrackerCustomizer::modifiedPlugin(QTKPlugin*, const QTKPluginEvent&, QVariant)
     */
    void modifiedPlugin(QSharedPointer<QTKPlugin> pPlugin, const QTKPluginEvent &event, T object);

    /**
     * @brief removedPlugin
     * Default implementation of the
     * <code>QTKPluginTrackerCustomizer::removedPlugin</code> method.
     *
     * <p>
     * This method is only called when this <code>QTKPluginTracker</code> has been
     * constructed with a <code>null</code> QTKPluginTrackerCustomizer argument.
     *
     * <p>
     * This implementation does nothing.
     *
     * @param pPlugin The <code>QTKPlugin</code> being removed.
     * @param event The plugin event which caused this customizer method to be
     *        called or an invalid event if there is no plugin event associated
     *        with the call to this method.
     * @param object The customized object for the specified plugin.
     * @see QTKPluginTrackerCustomizer::removedPlugin(QTKPlugin*, const QTKPluginEvent&, QVariant)
     */
    void removedPlugin(QSharedPointer<QTKPlugin> pPlugin, const QTKPluginEvent &event, T object);

private:
    typedef QTKPluginTracker<T> PluginTracker;
    typedef QTKTrackedPlugin<T> TrackedPlugin;
    typedef QTKPluginTrackerPrivate<T> PluginTrackerPrivate;
    typedef QTKPluginTrackerCustomizer<T> PluginTrackerCustomizer;

    friend class QTKTrackedPlugin<T>;
    friend class QTKPluginTrackerPrivate<T>;

    inline PluginTrackerPrivate* d_func() {
        return reinterpret_cast<PluginTrackerPrivate*>(qGetPtrHelper(d_ptr));
    }

    inline const PluginTrackerPrivate* d_func() const {
        return reinterpret_cast<const PluginTrackerPrivate*>(qGetPtrHelper(d_ptr));
    }

    const QScopedPointer<PluginTrackerPrivate> d_ptr;
};


template<class T>
QTKPluginTracker<T>::~QTKPluginTracker()
{

}

template<class T>
QTKPluginTracker<T>::QTKPluginTracker(QTKPluginContext *pContext, QTKPlugin::States stateMask,
                                      PluginTrackerCustomizer *pCustomizer)
    : d_ptr(new PluginTrackerPrivate(this, pContext, stateMask, pCustomizer))
{

}

template<class T>
void QTKPluginTracker<T>::open()
{
    Q_D(PluginTracker);
    QSharedPointer<TrackedPlugin> pTrackedPlugin;
    {
        QMutexLocker lock(&d->m_mutex);
        if (d->m_pTrackedPlugin) {
            return;
        }

        if (d->sm_bDebugFlag) {
            qDebug() << "QTKPluginTracker<T>::open";
        }

        pTrackedPlugin = QSharedPointer<TrackedPlugin>(new TrackedPlugin(this, d->m_pCustomizer));
        {
            QMutexLocker lockT(pTrackedPlugin.data());
            d->m_pContext->connectPluginListener(pTrackedPlugin.data(), SLOT(pluginChanged(QTKPluginEvent)), Qt::DirectConnection);
            QList<QSharedPointer<QTKPlugin> > plugins = d->m_pContext->getPlugins();
            int iLength = plugins.size();
            for (int i = 0; i < iLength; i++) {
                QTKPlugin::State state = plugins[i]->getState();
                if ((d->m_mask & state) == 0) {
                    /* null out plugins whose states are not interesting */
                    plugins[i].clear();
                }
            }
            plugins.removeAll(QSharedPointer<QTKPlugin>());
            /* set tracked with the initial bundles */
            pTrackedPlugin->setInitial(plugins);
        }
        d->m_pTrackedPlugin = pTrackedPlugin;
    }
    /* Call tracked outside of synchronized region */
    pTrackedPlugin->trackInitial(); /* process the initial references */
}

template<class T>
void QTKPluginTracker<T>::close()
{
    Q_D(PluginTracker);
    QList<QSharedPointer<QTKPlugin> > listPlugins;
    QSharedPointer<TrackedPlugin> pOutgoing;
    {
        QMutexLocker lock(&d->m_mutex);
        pOutgoing = d->m_pTrackedPlugin;
        if (pOutgoing.isNull()) {
            return;
        }

        if (d->sm_bDebugFlag) {
            qDebug() << "QTKPluginTracker<T>::close";
        }

        pOutgoing->close();
        listPlugins = getPlugins();
        d->m_pTrackedPlugin.clear();;

        pOutgoing->disconnect(SLOT(pluginChanged(QTKPluginEvent)));
    }

    foreach (QSharedPointer<QTKPlugin> pPlugin, listPlugins) {
        pOutgoing->untrack(pPlugin, QTKPluginEvent());
    }
}

template<class T>
QList<QSharedPointer<QTKPlugin> > QTKPluginTracker<T>::getPlugins() const
{
    Q_D(const PluginTracker);
    QSharedPointer<TrackedPlugin> pTrackedPlugin = d->tracked();
    if (pTrackedPlugin.isNull()) { /* if QTKPluginTracker is not open */
        return QList<QSharedPointer<QTKPlugin> >();
    }

    {
        QMutexLocker lock(pTrackedPlugin.data());
        return pTrackedPlugin->getTracked();
    }
}

template<class T>
T QTKPluginTracker<T>::getObject(QSharedPointer<QTKPlugin> pPlugin) const
{
    Q_D(const PluginTracker);
    QSharedPointer<TrackedPlugin> pTrackedPlugin = d->tracked();
    if (pTrackedPlugin.isNull()) {
        return T();
    }

    {
        QMutexLocker lock(pTrackedPlugin.data());
        return pTrackedPlugin->getCustomizedObject(pPlugin);
    }
}

template<class T>
void QTKPluginTracker<T>::remove(QSharedPointer<QTKPlugin> pPlugin)
{
    Q_D(PluginTracker);
    QSharedPointer<TrackedPlugin> pTrackedPlugin = d->tracked();
    if (pTrackedPlugin.isNull()) {
        return;
    }

    pTrackedPlugin->untrack(pPlugin, QTKPluginEvent());
}

template<class T>
int QTKPluginTracker<T>::size() const
{
    Q_D(const PluginTracker);
    QSharedPointer<TrackedPlugin> pTrackedPlugin = d->tracked();
    if (pTrackedPlugin.isNull()) {
        return 0;
    }

    {
        QMutexLocker lock(pTrackedPlugin.data());
        return pTrackedPlugin->size();
    }
}

template<class T>
int QTKPluginTracker<T>::getTrackingCount() const
{
    Q_D(const PluginTracker);
    QSharedPointer<TrackedPlugin> pTrackedPlugin = d->tracked();
    if (pTrackedPlugin.isNull()) {
        return -1;
    }

    {
        QMutexLocker lock(pTrackedPlugin.data());
        return pTrackedPlugin->getTrackingCount();
    }
}

template<class T>
QMap<QSharedPointer<QTKPlugin>, T> QTKPluginTracker<T>::getTracked() const
{
    QMap<QSharedPointer<QTKPlugin>, T> map;
    Q_D(const PluginTracker);
    QSharedPointer<TrackedPlugin> pTrackedPlugin = d->tracked();
    if (pTrackedPlugin.isNull()) { /* if PluginTracker is not open */
        return map;
    }

    {
        QMutexLocker lock(pTrackedPlugin.data());
        return pTrackedPlugin->copyEntries(map);
    }
}

template<class T>
bool QTKPluginTracker<T>::isEmpty() const
{
    Q_D(const PluginTracker);
    QSharedPointer<TrackedPlugin> pTrackedPlugin = d->tracked();
    if (pTrackedPlugin.isNull()) { /* if PluginTracker is not open */
        return true;
    }

    {
        QMutexLocker lock(pTrackedPlugin.data());
        return pTrackedPlugin->isEmpty();
    }
}

template<>
inline QSharedPointer<QTKPlugin> QTKPluginTracker<QSharedPointer<QTKPlugin> >::addingPlugin(QSharedPointer<QTKPlugin> pPlugin, const QTKPluginEvent &event)
{
    Q_UNUSED(event)
    return pPlugin;
}

template<class T>
T QTKPluginTracker<T>::addingPlugin(QSharedPointer<QTKPlugin> pPlugin, const QTKPluginEvent &event)
{
    Q_UNUSED(pPlugin)
    Q_UNUSED(event)

    return 0;
}

template<class T>
void QTKPluginTracker<T>::modifiedPlugin(QSharedPointer<QTKPlugin> pPlugin, const QTKPluginEvent &event, T object)
{
    Q_UNUSED(pPlugin)
    Q_UNUSED(event)
    Q_UNUSED(object)
}

template<class T>
void QTKPluginTracker<T>::removedPlugin(QSharedPointer<QTKPlugin> pPlugin, const QTKPluginEvent &event, T object)
{
    Q_UNUSED(pPlugin)
    Q_UNUSED(event)
    Q_UNUSED(object)
}

template<class T>
class QTKPluginTrackerPrivate
{
public:
    QTKPluginTrackerPrivate(QTKPluginTracker<T> *pPluginTracker,
                            QTKPluginContext *pContext, QTKPlugin::States stateMask,
                            QTKPluginTrackerCustomizer<T> *pCustomizer);

    ~QTKPluginTrackerPrivate();

    QSharedPointer<QTKTrackedPlugin<T> > tracked() const;

    static const bool sm_bDebugFlag; //	= false;
    QTKPluginContext* const m_pContext;
    QTKPluginTrackerCustomizer<T> *m_pCustomizer;
    QSharedPointer<QTKTrackedPlugin<T> > m_pTrackedPlugin;
    QTKPlugin::States m_mask;
    mutable QMutex m_mutex;

private:
    inline QTKPluginTracker<T>* q_func() {
        return static_cast<QTKPluginTracker<T> *>(q_ptr);
    }

    inline const QTKPluginTracker<T>* q_func() const {
        return static_cast<const QTKPluginTracker<T> *>(q_ptr);
    }

    friend class QTKPluginTracker<T>;

    QTKPluginTracker<T> * const q_ptr;
};

template<class T>
const bool QTKPluginTrackerPrivate<T>::sm_bDebugFlag = false;

template<class T>
QTKPluginTrackerPrivate<T>::QTKPluginTrackerPrivate(QTKPluginTracker<T> *pPluginTracker, QTKPluginContext *pContext,
                                                    QTKPlugin::States stateMask, QTKPluginTrackerCustomizer<T> *pCustomizer)
    : m_pContext(pContext),
      m_pCustomizer(pCustomizer),
      m_mask(stateMask),
      q_ptr(pPluginTracker)
{
    this->m_pCustomizer = pCustomizer ? pCustomizer : q_func();
}

template<class T>
QTKPluginTrackerPrivate<T>::~QTKPluginTrackerPrivate()
{
    if (m_pCustomizer != q_func()) {
        delete m_pCustomizer;
    }
}

template<class T>
QSharedPointer<QTKTrackedPlugin<T> > QTKPluginTrackerPrivate<T>::tracked() const
{
    return m_pTrackedPlugin;
}


template<class T>
class QTKTrackedPlugin : public QTKTrackedPluginListener,
        public QTKPluginAbstractTracked<QSharedPointer<QTKPlugin>, T, QTKPluginEvent>
{

public:
    QTKTrackedPlugin(QTKPluginTracker<T> *pPluginTracker,
                     QTKPluginTrackerCustomizer<T> *pCustomizer);

    /**
     * @brief pluginChanged
     * Slot for the <code>ctkPluginTracker</code>
     * class. This method must NOT be synchronized to avoid deadlock
     * potential.
     *
     * @param event <code>ctkPluginEvent</code> object from the framework.
     */
    void pluginChanged(const QTKPluginEvent &event);

private:
    typedef QTKPluginAbstractTracked<QSharedPointer<QTKPlugin>, T, QTKPluginEvent> Superclass;

    QTKPluginTracker<T> *m_pPluginTracker;
    QTKPluginTrackerCustomizer<T> *m_pCustomizer;

    /**
     * @brief customizerAdding
     * Call the specific customizer adding method. This method must not be
     * called while synchronized on this object.
     *
     * @param pItem Item to be tracked.
     * @param event Action related object.
     * @return Customized object for the tracked item or <code>null</code>
     *         if the item is not to be tracked.
     */
    T customizerAdding(QSharedPointer<QTKPlugin> pItem,
                       const QTKPluginEvent &event);

    /**
     * @brief customizerModified
     * Call the specific customizer modified method. This method must not be
     * called while synchronized on this object.
     *
     * @param pItem Tracked item.
     * @param event Action related object.
     * @param object Customized object for the tracked item.
     */
    void customizerModified(QSharedPointer<QTKPlugin> pItem,
                            const QTKPluginEvent &event, T object);

    /**
     * @brief customizerRemoved
     * Call the specific customizer removed method. This method must not be
     * called while synchronized on this object.
     *
     * @param pItem Tracked item.
     * @param event Action related object.
     * @param object Customized object for the tracked item.
     */
    void customizerRemoved(QSharedPointer<QTKPlugin> pItem,
                           const QTKPluginEvent &event, T object);
};

template<class T>
QTKTrackedPlugin<T>::QTKTrackedPlugin(QTKPluginTracker<T> *pPluginTracker,
                                      QTKPluginTrackerCustomizer<T> *pCustomizer)
    : m_pPluginTracker(pPluginTracker),
      m_pCustomizer(pCustomizer)
{

}

template<class T>
void QTKTrackedPlugin<T>::pluginChanged(const QTKPluginEvent &event)
{
    if (this->m_bClosed) {
        return;
    }

    QSharedPointer<QTKPlugin> pPlugin = event.getPlugin();
    QTKPlugin::State eState = pPlugin->getState();
    if (m_pPluginTracker->d_func()->sm_bDebugFlag) {
        qDebug() << "QTKTrackedPlugin<T>::pluginChanged[" << eState << "]: " << *pPlugin;
    }

    if (m_pPluginTracker->d_func()->m_mask & eState) {
        this->track(pPlugin, event);
    } else {
        this->untrack(pPlugin, event);
    }
}

template<class T>
T QTKTrackedPlugin<T>::customizerAdding(QSharedPointer<QTKPlugin> pItem,
                                        const QTKPluginEvent &event)
{
    return m_pCustomizer->addingPlugin(pItem, event);
}

template<class T>
void QTKTrackedPlugin<T>::customizerModified(QSharedPointer<QTKPlugin> pItem,
                                             const QTKPluginEvent &event,
                                             T object)
{
    m_pCustomizer->modifiedPlugin(pItem, event, object);
}

template<class T>
void QTKTrackedPlugin<T>::customizerRemoved(QSharedPointer<QTKPlugin> pItem,
                                            const QTKPluginEvent &event,
                                            T object)
{
    m_pCustomizer->removedPlugin(pItem, event, object);
}

QTK_PLUGINFRAMEWORK_END_NAMESPACE

#endif // QTKPLUGINTRACKER_H
