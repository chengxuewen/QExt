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


#ifndef _QEXTOSGITRACKEDPLUGIN_P_H
#define _QEXTOSGITRACKEDPLUGIN_P_H

#include <qextOsgiPlugin.h>
#include <qextOsgiPluginEvent.h>
#include <qextOsgiPluginTracker.h>
#include <private/qextOsgiTrackedPluginListener_p.h>
#include <private/qextOsgiPluginAbstractTracked_p.h>

#include <QSharedPointer>

/**
 * \ingroup PluginFramework
 */
template<typename T>
class QExtOsgiTrackedPlugin : public QExtOsgiTrackedPluginListener,
                              public QExtOsgiPluginAbstractTracked<QSharedPointer<QExtOsgiPlugin>, T, QExtOsgiPluginEvent>
{

public:
    QExtOsgiTrackedPlugin(QExtOsgiPluginTracker<T>* pluginTracker,
                          QExtOsgiPluginTrackerCustomizer<T>* customizer);


    /**
   * Slot for the <code>QExtOsgiPluginTracker</code>
   * class. This method must NOT be synchronized to avoid deadlock
   * potential.
   *
   * @param event <code>QExtOsgiPluginEvent</code> object from the framework.
   */
    void pluginChanged(const QExtOsgiPluginEvent &event);

private:

    typedef QExtOsgiPluginAbstractTracked<QSharedPointer<QExtOsgiPlugin>, T, QExtOsgiPluginEvent> Superclass;

    QExtOsgiPluginTracker<T>* pluginTracker;
    QExtOsgiPluginTrackerCustomizer<T>* customizer;

    /**
   * Call the specific customizer adding method. This method must not be
   * called while synchronized on this object.
   *
   * @param item Item to be tracked.
   * @param related Action related object.
   * @return Customized object for the tracked item or <code>null</code>
   *         if the item is not to be tracked.
   */
    T customizerAdding(QSharedPointer<QExtOsgiPlugin> item,
                       const QExtOsgiPluginEvent &related);

    /**
   * Call the specific customizer modified method. This method must not be
   * called while synchronized on this object.
   *
   * @param item Tracked item.
   * @param related Action related object.
   * @param object Customized object for the tracked item.
   */
    void customizerModified(QSharedPointer<QExtOsgiPlugin> item,
                            const QExtOsgiPluginEvent &related, T object);

    /**
   * Call the specific customizer removed method. This method must not be
   * called while synchronized on this object.
   *
   * @param item Tracked item.
   * @param related Action related object.
   * @param object Customized object for the tracked item.
   */
    void customizerRemoved(QSharedPointer<QExtOsgiPlugin> item,
                           const QExtOsgiPluginEvent &related, T object);
};


//----------------------------------------------------------------------------
template<class T>
QExtOsgiTrackedPlugin<T>::QExtOsgiTrackedPlugin(QExtOsgiPluginTracker<T>* pluginTracker,
                                                QExtOsgiPluginTrackerCustomizer<T>* customizer)
    : pluginTracker(pluginTracker), customizer(customizer)
{

}

//----------------------------------------------------------------------------
template<class T>
void QExtOsgiTrackedPlugin<T>::pluginChanged(const QExtOsgiPluginEvent &event)
{
    /*
   * Check if we had a delayed call (which could happen when we
   * close).
   */
    if (this->closed)
    {
        return;
    }

    QSharedPointer<QExtOsgiPlugin> plugin = event.getPlugin();
    QExtOsgiPlugin::State state = plugin->getState();
    if (pluginTracker->d_func()->DEBUG_FLAG)
    {
        qDebug() << "qextOsgiTrackedPlugin<T>::pluginChanged[" << state << "]: " << *plugin;
    }

    if (pluginTracker->d_func()->mask & state)
    {
        this->track(plugin, event);
        /*
     * If the customizer throws an exception, it is safe
     * to let it propagate
     */
    }
    else
    {
        this->untrack(plugin, event);
        /*
     * If the customizer throws an exception, it is safe
     * to let it propagate
     */
    }
}

//----------------------------------------------------------------------------
template<class T>
T QExtOsgiTrackedPlugin<T>::customizerAdding(QSharedPointer<QExtOsgiPlugin> item,
                                             const QExtOsgiPluginEvent &related)
{
    return customizer->addingPlugin(item, related);
}

//----------------------------------------------------------------------------
template<class T>
void QExtOsgiTrackedPlugin<T>::customizerModified(QSharedPointer<QExtOsgiPlugin> item,
                                                  const QExtOsgiPluginEvent &related,
                                                  T object)
{
    customizer->modifiedPlugin(item, related, object);
}

//----------------------------------------------------------------------------
template<class T>
void QExtOsgiTrackedPlugin<T>::customizerRemoved(QSharedPointer<QExtOsgiPlugin> item,
                                                 const QExtOsgiPluginEvent &related,
                                                 T object)
{
    customizer->removedPlugin(item, related, object);
}


#endif // _QEXTOSGITRACKEDPLUGIN_P_H
