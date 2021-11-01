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

#ifndef QTKPLUGINTRACKERCUSTOMIZER_H
#define QTKPLUGINTRACKERCUSTOMIZER_H

#include "qtkpluginframework_global.h"
#include "qtkpluginevent.h"

#include <QVariant>

class QObject;

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

class QTKPlugin;

/**
 * @ingroup QTKPluginFramework
 *
 * The <code>QTKPluginTrackerCustomizer</code> interface allows a
 * <code>QTKPluginTracker</code> to customize the <code>QTKPlugin</code>s that are
 * tracked. A <code>QTKPluginTrackerCustomizer</code> is called when a plugin is
 * being added to a <code>QTKPluginTracker</code>. The
 * <code>QTKPluginTrackerCustomizer</code> can then return an object for the
 * tracked plugin. A <code>QTKPluginTrackerCustomizer</code> is also called when a
 * tracked plugin is modified or has been removed from a
 * <code>QTKPluginTracker</code>.
 *
 * <p>
 * The methods in this interface may be called as the result of a
 * <code>QTKPluginEvent</code> being received by a <code>QTKPluginTracker</code>.
 * Since <code>QTKPluginEvent</code>s are received synchronously by the
 * <code>QTKPluginTracker</code>, it is highly recommended that implementations of
 * these methods do not alter plugin states while being synchronized on any
 * object.
 *
 * <p>
 * The <code>QTKPluginTracker</code> class is thread-safe. It does not call a
 * <code>QTKPluginTrackerCustomizer</code> while holding any locks.
 * <code>QTKPluginTrackerCustomizer</code> implementations must also be
 * thread-safe.
 *
 * \tparam T The type of the tracked object.
 * \remarks This class is thread safe.
 */
template<class T>
struct QTKPluginTrackerCustomizer {
    virtual ~QTKPluginTrackerCustomizer() {}

    /**
     * @brief addingPlugin
     * A plugin is being added to the <code>QTKPluginTracker</code>.
     *
     * <p>
     * This method is called before a plugin which matched the search parameters
     * of the <code>QTKPluginTracker</code> is added to the
     * <code>QTKPluginTracker</code>. This method should return the object to be
     * tracked for the specified <code>QTKPlugin</code>. The returned object is
     * stored in the <code>QTKPluginTracker</code> and is available from the
     * QTKPluginTracker::getObject(QTKPlugin*) method.
     *
     * @param pPlugin The <code>QTKPlugin</code> being added to the
     *        <code>QTKPluginTracker</code>.
     * @param event The plugin event which caused this customizer method to be
     *        called or an invalid event (QTKPluginEvent::isNull() returns <code>true</code>)
     *        if there is no plugin event associated
     *        with the call to this method.
     * @return The object to be tracked for the specified <code>QTKPlugin</code>
     *         object or <code>null</code> if the specified <code>QTKPlugin</code>
     *         object should not be tracked.
     */
    virtual T addingPlugin(QSharedPointer<QTKPlugin> pPlugin, const QTKPluginEvent &event) = 0;

    /**
     * @brief modifiedPlugin
     * A plugin tracked by the <code>QTKPluginTracker</code> has been modified.
     *
     * <p>
     * This method is called when a plugin being tracked by the
     * <code>QTKPluginTracker</code> has had its state modified.
     *
     * @param pPlugin The <code>QTKPlugin</code> whose state has been modified.
     * @param event The plugin event which caused this customizer method to be
     *        called or an invalid event (QTKPluginEvent::isNull() returns <code>true</code>)
     *        if there is no plugin event associated
     *        with the call to this method.
     * @param object The tracked object for the specified plugin.
     */
    virtual void modifiedPlugin(QSharedPointer<QTKPlugin> pPlugin, const QTKPluginEvent &event, T object) = 0;

    /**
     * @brief removedPlugin
     * A plugin tracked by the <code>QTKPluginTracker</code> has been removed.
     *
     * <p>
     * This method is called after a plugin is no longer being tracked by the
     * <code>QTKPluginTracker</code>.
     *
     * @param pPlugin The <code>QTKPlugin</code> that has been removed.
     * @param event The plugin event which caused this customizer method to be
     *        called or an invalid event (QTKPluginEvent::isNull() returns <code>true</code>)
     *        if there is no plugin event associated
     *        with the call to this method.
     * @param object The tracked object for the specified plugin.
     */
    virtual void removedPlugin(QSharedPointer<QTKPlugin> pPlugin, const QTKPluginEvent &event, T object) = 0;
};

QTK_PLUGINFRAMEWORK_END_NAMESPACE

#endif // QTKPLUGINTRACKERCUSTOMIZER_H
