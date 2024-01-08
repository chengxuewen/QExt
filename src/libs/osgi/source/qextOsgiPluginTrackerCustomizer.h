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


#ifndef _QEXTOSGIPLUGINTRACKERCUSTOMIZER_H
#define _QEXTOSGIPLUGINTRACKERCUSTOMIZER_H

#include <qextOsgiPluginEvent.h>

#include <QVariant>

class QObject;
class QExtOsgiPlugin;

/**
 * \ingroup PluginFramework
 *
 * The <code>QExtOsgiPluginTrackerCustomizer</code> interface allows a
 * <code>QExtOsgiPluginTracker</code> to customize the <code>QExtOsgiPlugin</code>s that are
 * tracked. A <code>QExtOsgiPluginTrackerCustomizer</code> is called when a plugin is
 * being added to a <code>QExtOsgiPluginTracker</code>. The
 * <code>QExtOsgiPluginTrackerCustomizer</code> can then return an object for the
 * tracked plugin. A <code>QExtOsgiPluginTrackerCustomizer</code> is also called when a
 * tracked plugin is modified or has been removed from a
 * <code>QExtOsgiPluginTracker</code>.
 *
 * <p>
 * The methods in this interface may be called as the result of a
 * <code>QExtOsgiPluginEvent</code> being received by a <code>QExtOsgiPluginTracker</code>.
 * Since <code>QExtOsgiPluginEvent</code>s are received synchronously by the
 * <code>QExtOsgiPluginTracker</code>, it is highly recommended that implementations of
 * these methods do not alter plugin states while being synchronized on any
 * object.
 *
 * <p>
 * The <code>QExtOsgiPluginTracker</code> class is thread-safe. It does not call a
 * <code>QExtOsgiPluginTrackerCustomizer</code> while holding any locks.
 * <code>QExtOsgiPluginTrackerCustomizer</code> implementations must also be
 * thread-safe.
 *
 * \tparam T The type of the tracked object.
 * \remarks This class is thread safe.
 */
template<class T>
struct QExtOsgiPluginTrackerCustomizer {

    virtual ~QExtOsgiPluginTrackerCustomizer() {}

    /**
   * A plugin is being added to the <code>QExtOsgiPluginTracker</code>.
   *
   * <p>
   * This method is called before a plugin which matched the search parameters
   * of the <code>QExtOsgiPluginTracker</code> is added to the
   * <code>QExtOsgiPluginTracker</code>. This method should return the object to be
   * tracked for the specified <code>QExtOsgiPlugin</code>. The returned object is
   * stored in the <code>QExtOsgiPluginTracker</code> and is available from the
   * QExtOsgiPluginTracker::getObject(QExtOsgiPlugin*) method.
   *
   * @param plugin The <code>QExtOsgiPlugin</code> being added to the
   *        <code>QExtOsgiPluginTracker</code>.
   * @param event The plugin event which caused this customizer method to be
   *        called or an invalid event (QExtOsgiPluginEvent::isNull() returns <code>true</code>)
   *        if there is no plugin event associated
   *        with the call to this method.
   * @return The object to be tracked for the specified <code>QExtOsgiPlugin</code>
   *         object or <code>null</code> if the specified <code>QExtOsgiPlugin</code>
   *         object should not be tracked.
   */
    virtual T addingPlugin(QSharedPointer<QExtOsgiPlugin> plugin, const QExtOsgiPluginEvent &event) = 0;

    /**
   * A plugin tracked by the <code>QExtOsgiPluginTracker</code> has been modified.
   *
   * <p>
   * This method is called when a plugin being tracked by the
   * <code>QExtOsgiPluginTracker</code> has had its state modified.
   *
   * @param plugin The <code>QExtOsgiPlugin</code> whose state has been modified.
   * @param event The plugin event which caused this customizer method to be
   *        called or an invalid event (QExtOsgiPluginEvent::isNull() returns <code>true</code>)
   *        if there is no plugin event associated
   *        with the call to this method.
   * @param object The tracked object for the specified plugin.
   */
    virtual void modifiedPlugin(QSharedPointer<QExtOsgiPlugin> plugin, const QExtOsgiPluginEvent &event,
                                T object) = 0;

    /**
   * A plugin tracked by the <code>QExtOsgiPluginTracker</code> has been removed.
   *
   * <p>
   * This method is called after a plugin is no longer being tracked by the
   * <code>QExtOsgiPluginTracker</code>.
   *
   * @param plugin The <code>QExtOsgiPlugin</code> that has been removed.
   * @param event The plugin event which caused this customizer method to be
   *        called or an invalid event (QExtOsgiPluginEvent::isNull() returns <code>true</code>)
   *        if there is no plugin event associated
   *        with the call to this method.
   * @param object The tracked object for the specified plugin.
   */
    virtual void removedPlugin(QSharedPointer<QExtOsgiPlugin> plugin, const QExtOsgiPluginEvent &event,
                               T object) = 0;
};

#endif // _QEXTOSGIPLUGINTRACKERCUSTOMIZER_H
