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


#ifndef _QEXTOSGIPLUGINTRACKER_H
#define _QEXTOSGIPLUGINTRACKER_H

#include <qextOsgiGlobal.h>
#include <qextOsgiPlugin.h>
#include <qextOsgiPluginTrackerCustomizer.h>
#include <qextOsgiPluginContext.h>
#include <private/qextOsgiPluginTracker_p.h>
#include <private/qextOsgiTrackedPlugin_p.h>

#include <QDebug>
#include <QScopedPointer>

template<class T> class QExtOsgiTrackedPlugin;
template<class T> class QExtOsgiPluginTrackerPrivate;

/**
 * \ingroup PluginFramework
 *
 * The <code>QExtOsgiPluginTracker</code> class simplifies tracking plugins much like
 * the <code>QExtOsgiServiceTracker</code> simplifies tracking services.
 * <p>
 * A <code>QExtOsgiPluginTracker</code> is constructed with state criteria and a
 * <code>QExtOsgiPluginTrackerCustomizer</code> object. A <code>QExtOsgiPluginTracker</code> can
 * use the <code>QExtOsgiPluginTrackerCustomizer</code> to select which plugins are
 * tracked and to create a customized object to be tracked with the plugin. The
 * <code>QExtOsgiPluginTracker</code> can then be opened to begin tracking all plugins
 * whose state matches the specified state criteria.
 * <p>
 * The <code>getPlugins</code> method can be called to get the
 * <code>QExtOsgiPlugin</code> objects of the plugins being tracked. The
 * <code>getObject</code> method can be called to get the customized object for
 * a tracked plugin.
 * <p>
 * The <code>QExtOsgiPluginTracker</code> class is thread-safe. It does not call a
 * <code>QExtOsgiPluginTrackerCustomizer</code> while holding any locks.
 * <code>QExtOsgiPluginTrackerCustomizer</code> implementations must also be
 * thread-safe.
 *
 * \tparam T The type of the tracked object. The type must be an assignable
 *         datatype, provide a boolean conversion function, and provide
 *         a constructor and an assignment operator which can handle 0 as an argument.
 * \remarks This class is thread safe.
 */
template<class T = QSharedPointer<QExtOsgiPlugin> >
class QExtOsgiPluginTracker : protected QExtOsgiPluginTrackerCustomizer<T>
{
public:

    ~QExtOsgiPluginTracker();

    /**
   * Create a <code>QExtOsgiPluginTracker</code> for plugins whose state is present in
   * the specified state mask.
   *
   * <p>
   * Plugins whose state is present on the specified state mask will be
   * tracked by this <code>QExtOsgiPluginTracker</code>.
   *
   * @param context The <code>QExtOsgiPluginContext</code> against which the tracking
   *        is done.
   * @param stateMask The bit mask of the <code>OR</code>ing of the plugin
   *        states to be tracked.
   * @param customizer The customizer object to call when plugins are added,
   *        modified, or removed in this <code>QExtOsgiPluginTracker</code>. If
   *        customizer is <code>null</code>, then this
   *        <code>QExtOsgiPluginTracker</code> will be used as the
   *        <code>QExtOsgiPluginTrackerCustomizer</code> and this
   *        <code>QExtOsgiPluginTracker</code> will call the
   *        <code>QExtOsgiPluginTrackerCustomizer</code> methods on itself. If the
   *        customizer is not <code>null</code>, this <code>QExtOsgiPluginTracker</code>
   *        takes ownership of the customizer.
   * @see QExtOsgiPlugin#getState()
   */
    QExtOsgiPluginTracker(QExtOsgiPluginContext* context, QExtOsgiPlugin::States stateMask,
                          QExtOsgiPluginTrackerCustomizer<T>* customizer = 0);

    /**
   * Open this <code>QExtOsgiPluginTracker</code> and begin tracking plugins.
   *
   * <p>
   * QExtOsgiPlugin's which match the state criteria specified when this
   * <code>QExtOsgiPluginTracker</code> was created are now tracked by this
   * <code>QExtOsgiPluginTracker</code>.
   *
   * @throws QExtIllegalStateException If the <code>QExtOsgiPluginContext</code>
   *         with which this <code>QExtOsgiPluginTracker</code> was created is no
   *         longer valid.
   */
    virtual void open();

    /**
   * Close this <code>QExtOsgiPluginTracker</code>.
   *
   * <p>
   * This method should be called when this <code>QExtOsgiPluginTracker</code> should
   * end the tracking of plugins.
   *
   * <p>
   * This implementation calls getPlugins() to get the list of
   * tracked plugins to remove.
   */
    virtual void close();

    /**
   * Return a list of <code>QExtOsgiPlugin</code>s for all plugins being tracked by
   * this <code>QExtOsgiPluginTracker</code>.
   *
   * @return A list of <code>QExtOsgiPlugin</code>s.
   */
    virtual QList<QSharedPointer<QExtOsgiPlugin> > getPlugins() const;

    /**
   * Returns the customized object for the specified <code>QExtOsgiPlugin</code> if
   * the specified plugin is being tracked by this <code>QExtOsgiPluginTracker</code>.
   *
   * @param plugin The <code>QExtOsgiPlugin</code> being tracked.
   * @return The customized object for the specified <code>QExtOsgiPlugin</code> or
   *         <code>null</code> if the specified <code>QExtOsgiPlugin</code> is not
   *         being tracked.
   */
    virtual T getObject(QSharedPointer<QExtOsgiPlugin> plugin) const;

    /**
   * Remove a plugin from this <code>QExtOsgiPluginTracker</code>.
   *
   * The specified plugin will be removed from this <code>QExtOsgiPluginTracker</code>.
   * If the specified plugin was being tracked then the
   * <code>QExtOsgiPluginTrackerCustomizer::removedPlugin</code> method will be called
   * for that plugin.
   *
   * @param plugin The <code>QExtOsgiPlugin</code> to be removed.
   */
    virtual void remove(QSharedPointer<QExtOsgiPlugin> plugin);

    /**
   * Return the number of plugins being tracked by this
   * <code>QExtOsgiPluginTracker</code>.
   *
   * @return The number of plugins being tracked.
   */
    virtual int size() const;

    /**
   * Returns the tracking count for this <code>QExtOsgiPluginTracker</code>.
   *
   * The tracking count is initialized to 0 when this
   * <code>QExtOsgiPluginTracker</code> is opened. Every time a plugin is added,
   * modified or removed from this <code>QExtOsgiPluginTracker</code> the tracking
   * count is incremented.
   *
   * <p>
   * The tracking count can be used to determine if this
   * <code>QExtOsgiPluginTracker</code> has added, modified or removed a plugin by
   * comparing a tracking count value previously collected with the current
   * tracking count value. If the value has not changed, then no plugin has
   * been added, modified or removed from this <code>QExtOsgiPluginTracker</code>
   * since the previous tracking count was collected.
   *
   * @return The tracking count for this <code>QExtOsgiPluginTracker</code> or -1 if
   *         this <code>QExtOsgiPluginTracker</code> is not open.
   */
    virtual int getTrackingCount() const;

    /**
   * Return a <code>QMap</code> with the <code>QExtOsgiPlugin</code>s and customized
   * objects for all plugins being tracked by this <code>QExtOsgiPluginTracker</code>.
   *
   * @return A <code>QMap</code> with the <code>QExtOsgiPlugin</code>s and customized
   *         objects for all services being tracked by this
   *         <code>QExtOsgiPluginTracker</code>. If no plugins are being tracked, then
   *         the returned map is empty.
   */
    virtual QMap<QSharedPointer<QExtOsgiPlugin>, T> getTracked() const;

    /**
   * Return if this <code>QExtOsgiPluginTracker</code> is empty.
   *
   * @return <code>true</code> if this <code>QExtOsgiPluginTracker</code> is not tracking any
   *         plugins.
   */
    virtual bool isEmpty() const;

protected:

    /**
   * Default implementation of the
   * <code>QExtOsgiPluginTrackerCustomizer::addingPlugin</code> method.
   *
   * <p>
   * This method is only called when this <code>QExtOsgiPluginTracker</code> has been
   * constructed with a <code>null</code> QExtOsgiPluginTrackerCustomizer argument.
   *
   * <p>
   * This implementation simply returns the specified <code>QExtOsgiPlugin*</code> in
   * a QVariant.
   *
   * <p>
   * This method can be overridden in a subclass to customize the object to be
   * tracked for the plugin being added.
   *
   * @param plugin The <code>QExtOsgiPlugin</code> being added to this
   *        <code>QExtOsgiPluginTracker</code> object.
   * @param event The plugin event which caused this customizer method to be
   *        called or an invalid event if there is no plugin event associated
   *        with the call to this method.
   * @return The specified plugin.
   * @see QExtOsgiPluginTrackerCustomizer::addingPlugin(QExtOsgiPlugin*, const QExtOsgiPluginEvent&)
   */
    T addingPlugin(QSharedPointer<QExtOsgiPlugin> plugin, const QExtOsgiPluginEvent& event);

    /**
   * Default implementation of the
   * <code>QExtOsgiPluginTrackerCustomizer::modifiedPlugin</code> method.
   *
   * <p>
   * This method is only called when this <code>QExtOsgiPluginTracker</code> has been
   * constructed with a <code>null</code> QExtOsgiPluginTrackerCustomizer argument.
   *
   * <p>
   * This implementation does nothing.
   *
   * @param plugin The <code>QExtOsgiPlugin</code> whose state has been modified.
   * @param event The plugin event which caused this customizer method to be
   *        called or an invalid event if there is no plugin event associated
   *        with the call to this method.
   * @param object The customized object for the specified QExtOsgiPlugin.
   * @see QExtOsgiPluginTrackerCustomizer::modifiedPlugin(QExtOsgiPlugin*, const QExtOsgiPluginEvent&, QVariant)
   */
    void modifiedPlugin(QSharedPointer<QExtOsgiPlugin> plugin, const QExtOsgiPluginEvent& event, T object);

    /**
   * Default implementation of the
   * <code>QExtOsgiPluginTrackerCustomizer::removedPlugin</code> method.
   *
   * <p>
   * This method is only called when this <code>QExtOsgiPluginTracker</code> has been
   * constructed with a <code>null</code> QExtOsgiPluginTrackerCustomizer argument.
   *
   * <p>
   * This implementation does nothing.
   *
   * @param plugin The <code>QExtOsgiPlugin</code> being removed.
   * @param event The plugin event which caused this customizer method to be
   *        called or an invalid event if there is no plugin event associated
   *        with the call to this method.
   * @param object The customized object for the specified plugin.
   * @see QExtOsgiPluginTrackerCustomizer::removedPlugin(QExtOsgiPlugin*, const QExtOsgiPluginEvent&, QVariant)
   */
    void removedPlugin(QSharedPointer<QExtOsgiPlugin> plugin, const QExtOsgiPluginEvent& event, T object);

private:

    typedef QExtOsgiPluginTracker<T> PluginTracker;
    typedef QExtOsgiTrackedPlugin<T> TrackedPlugin;
    typedef QExtOsgiPluginTrackerPrivate<T> PluginTrackerPrivate;
    typedef QExtOsgiPluginTrackerCustomizer<T> PluginTrackerCustomizer;

    friend class QExtOsgiTrackedPlugin<T>;
    friend class QExtOsgiPluginTrackerPrivate<T>;

    inline PluginTrackerPrivate* d_func()
    {
        return reinterpret_cast<PluginTrackerPrivate*>(qGetPtrHelper(d_ptr));
    }

    inline const PluginTrackerPrivate* d_func() const
    {
        return reinterpret_cast<const PluginTrackerPrivate*>(qGetPtrHelper(d_ptr));
    }

    const QScopedPointer<PluginTrackerPrivate> d_ptr;
};


//----------------------------------------------------------------------------
template<class T>
QExtOsgiPluginTracker<T>::~QExtOsgiPluginTracker()
{

}

//----------------------------------------------------------------------------
template<class T>
QExtOsgiPluginTracker<T>::QExtOsgiPluginTracker(QExtOsgiPluginContext* context, QExtOsgiPlugin::States stateMask,
                                                PluginTrackerCustomizer* customizer)
    : d_ptr(new PluginTrackerPrivate(this, context, stateMask, customizer))
{

}

//----------------------------------------------------------------------------
template<class T>
void QExtOsgiPluginTracker<T>::open()
{
    Q_D(PluginTracker);
    QSharedPointer<TrackedPlugin> t;
    {
        QMutexLocker lock(&d->mutex);
        if (d->trackedPlugin)
        {
            return;
        }

        if (d->DEBUG_FLAG)
        {
            qDebug() << "qextOsgiPluginTracker<T>::open";
        }

        t = QSharedPointer<TrackedPlugin>(new TrackedPlugin(this, d->customizer));
        {
            QMutexLocker lockT(t.data());
            d->context->connectPluginListener(t.data(), SLOT(pluginChanged(QExtOsgiPluginEvent)), Qt::DirectConnection);
            QList<QSharedPointer<QExtOsgiPlugin> > plugins = d->context->getPlugins();
            int length = plugins.size();
            for (int i = 0; i < length; i++)
            {
                QExtOsgiPlugin::State state = plugins[i]->getState();
                if ((d->mask & state) == 0)
                {
                    /* null out plugins whose states are not interesting */
                    plugins[i].clear();
                }
            }
            plugins.removeAll(QSharedPointer<QExtOsgiPlugin>());
            /* set tracked with the initial bundles */
            t->setInitial(plugins);
        }
        d->trackedPlugin = t;
    }
    /* Call tracked outside of synchronized region */
    t->trackInitial(); /* process the initial references */
}

//----------------------------------------------------------------------------
template<class T>
void QExtOsgiPluginTracker<T>::close()
{
    Q_D(PluginTracker);
    QList<QSharedPointer<QExtOsgiPlugin> > plugins;
    QSharedPointer<TrackedPlugin> outgoing;
    {
        QMutexLocker lock(&d->mutex);
        outgoing = d->trackedPlugin;
        if (outgoing.isNull())
        {
            return;
        }

        if (d->DEBUG_FLAG)
        {
            qDebug() << "qextOsgiPluginTracker<T>::close";
        }

        outgoing->close();
        plugins = getPlugins();
        d->trackedPlugin.clear();;

        outgoing->disconnect(SLOT(pluginChanged(QExtOsgiPluginEvent)));
    }

    foreach (QSharedPointer<QExtOsgiPlugin> plugin, plugins)
    {
        outgoing->untrack(plugin, QExtOsgiPluginEvent());
    }
}

//----------------------------------------------------------------------------
template<class T>
QList<QSharedPointer<QExtOsgiPlugin> > QExtOsgiPluginTracker<T>::getPlugins() const
{
    Q_D(const PluginTracker);
    QSharedPointer<TrackedPlugin> t = d->tracked();
    if (t.isNull())
    { /* if QExtOsgiPluginTracker is not open */
        return QList<QSharedPointer<QExtOsgiPlugin> >();
    }

    {
        QMutexLocker lock(t.data());
        return t->getTracked();
    }
}

//----------------------------------------------------------------------------
template<class T>
T QExtOsgiPluginTracker<T>::getObject(QSharedPointer<QExtOsgiPlugin> plugin) const
{
    Q_D(const PluginTracker);
    QSharedPointer<TrackedPlugin> t = d->tracked();
    if (t.isNull())
    {
        return T();
    }

    {
        QMutexLocker lock(t.data());
        return t->getCustomizedObject(plugin);
    }
}

//----------------------------------------------------------------------------
template<class T>
void QExtOsgiPluginTracker<T>::remove(QSharedPointer<QExtOsgiPlugin> plugin)
{
    Q_D(PluginTracker);
    QSharedPointer<TrackedPlugin> t = d->tracked();
    if (t.isNull())
    {
        return;
    }
    t->untrack(plugin, QExtOsgiPluginEvent());
}

//----------------------------------------------------------------------------
template<class T>
int QExtOsgiPluginTracker<T>::size() const
{
    Q_D(const PluginTracker);
    QSharedPointer<TrackedPlugin> t = d->tracked();
    if (t.isNull())
    {
        return 0;
    }

    {
        QMutexLocker lock(t.data());
        return t->size();
    }
}

//----------------------------------------------------------------------------
template<class T>
int QExtOsgiPluginTracker<T>::getTrackingCount() const
{
    Q_D(const PluginTracker);
    QSharedPointer<TrackedPlugin> t = d->tracked();
    if (t.isNull())
    {
        return -1;
    }

    {
        QMutexLocker lock(t.data());
        return t->getTrackingCount();
    }
}

//----------------------------------------------------------------------------
template<class T>
QMap<QSharedPointer<QExtOsgiPlugin>, T> QExtOsgiPluginTracker<T>::getTracked() const
{
    QMap<QSharedPointer<QExtOsgiPlugin>, T> map;
    Q_D(const PluginTracker);
    QSharedPointer<TrackedPlugin> t = d->tracked();
    if (t.isNull())
    { /* if PluginTracker is not open */
        return map;
    }
    {
        QMutexLocker lock(t.data());
        return t->copyEntries(map);
    }
}

//----------------------------------------------------------------------------
template<class T>
bool QExtOsgiPluginTracker<T>::isEmpty() const
{
    Q_D(const PluginTracker);
    QSharedPointer<TrackedPlugin> t = d->tracked();
    if (t.isNull())
    { /* if PluginTracker is not open */
        return true;
    }
    {
        QMutexLocker lock(t.data());
        return t->isEmpty();
    }
}

//----------------------------------------------------------------------------
template<>
inline QSharedPointer<QExtOsgiPlugin> QExtOsgiPluginTracker<QSharedPointer<QExtOsgiPlugin> >::addingPlugin(QSharedPointer<QExtOsgiPlugin> plugin, const QExtOsgiPluginEvent& event)
{
    Q_UNUSED(event)

    return plugin;
}

//----------------------------------------------------------------------------
template<class T>
T QExtOsgiPluginTracker<T>::addingPlugin(QSharedPointer<QExtOsgiPlugin> plugin, const QExtOsgiPluginEvent& event)
{
    Q_UNUSED(plugin)
    Q_UNUSED(event)

    return 0;
}

//----------------------------------------------------------------------------
template<class T>
void QExtOsgiPluginTracker<T>::modifiedPlugin(QSharedPointer<QExtOsgiPlugin> plugin, const QExtOsgiPluginEvent& event, T object)
{
    Q_UNUSED(plugin)
    Q_UNUSED(event)
    Q_UNUSED(object)
    /* do nothing */
}

//----------------------------------------------------------------------------
template<class T>
void QExtOsgiPluginTracker<T>::removedPlugin(QSharedPointer<QExtOsgiPlugin> plugin, const QExtOsgiPluginEvent& event, T object)
{
    Q_UNUSED(plugin)
    Q_UNUSED(event)
    Q_UNUSED(object)
    /* do nothing */
}


#endif // _QEXTOSGIPLUGINTRACKER_H
