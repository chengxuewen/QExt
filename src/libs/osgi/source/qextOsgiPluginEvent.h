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

#ifndef _QEXTOSGIPLUGINEVENT_H
#define _QEXTOSGIPLUGINEVENT_H

#include <qextOsgiGlobal.h>

#include <QSharedDataPointer>
#include <QSharedPointer>
#include <QMetaType>

class QExtOsgiPlugin;
class QExtOsgiPluginEventData;

/**
 * \ingroup PluginFramework
 *
 * An event from the Framework describing a plugin lifecycle change.
 * <p>
 * <code>QExtOsgiPluginEvent</code> objects are delivered to slots connected
 * via QExtOsgiPluginContext::connectPluginListener() when a change
 * occurs in a plugins's lifecycle. A type code is used to identify
 * the event type for future extendibility.
 *
 * @see QExtOsgiPluginContext#connectPluginListener
 */
class QEXT_OSGI_API QExtOsgiPluginEvent
{

    QSharedDataPointer<QExtOsgiPluginEventData> d;

public:

    enum Type {
        /**
     * The plugin has been installed.
     *
     * @see QExtOsgiPluginContext::installBundle(const QString&)
     */
        INSTALLED,

        /**
     * The plugin has been started.
     * <p>
     * The plugin's
     * \link QExtOsgiPluginActivator::start(QExtOsgiPluginContext*) QExtOsgiPluginActivator start\endlink method
     * has been executed.
     *
     * @see QExtOsgiPlugin::start()
     */
        STARTED,

        /**
     * The plugin has been stopped.
     * <p>
     * The plugin's
     * \link QExtOsgiPluginActivator::stop(QExtOsgiPluginContext*) QExtOsgiPluginActivator stop\endlink method
     * has been executed.
     *
     * @see QExtOsgiPlugin::stop()
     */
        STOPPED,

        /**
     * The plugin has been updated.
     *
     * @see QExtOsgiPlugin::update()
     */
        UPDATED,

        /**
     * The plugin has been uninstalled.
     *
     * @see QExtOsgiPlugin::uninstall()
     */
        UNINSTALLED,

        /**
     * The plugin has been resolved.
     *
     * @see QExtOsgiPlugin::RESOLVED
     */
        RESOLVED,

        /**
     * The plugin has been unresolved.
     *
     * @see QExtOsgiPlugin::INSTALLED
     */
        UNRESOLVED,

        /**
     * The plugin is about to be activated.
     * <p>
     * The plugin's
     * \link QExtOsgiPluginActivator::start(QExtOsgiPluginContext*) QExtOsgiPluginActivator start\endlink method
     * is about to be called. This
     * event is only delivered to synchronous slots, which have been registered with
     * Qt::DirectConnection or Qt::BlockingQueuedConnection in QExtOsgiPluginContext::connectPluginListener().
     *
     * @see QExtOsgiPlugin::start()
     */
        STARTING,

        /**
     * The plugin is about to deactivated.
     * <p>
     * The plugin's
     * \link QExtOsgiPluginActivator::stop(QExtOsgiPluginContext*) QExtOsgiPluginActivator stop\endlink method
     * is about to be called. This
     * event is only delivered to synchronous slots, which have been registered with
     * Qt::DirectConnection or Qt::BlockingQueuedConnection in QExtOsgiPluginContext::connectPluginListener().
     *
     * @see QExtOsgiPlugin::stop()
     */
        STOPPING,

        /**
     * The plugin will be lazily activated.
     * <p>
     * The plugin has a \link QExtOsgiPluginConstants::ACTIVATION_LAZY lazy activation policy\endlink
     * and is waiting to be activated. It is now in the
     * \link QExtOsgiPlugin::STARTING STARTING\endlink state and has a valid
     * <code>QExtOsgiPluginContext</code>. This
     * event is only delivered to synchronous slots, which have been registered with
     * Qt::DirectConnection or Qt::BlockingQueuedConnection in QExtOsgiPluginContext::connectPluginListener().
     */
        LAZY_ACTIVATION
    };

    /**
   * Default constructor for use with the Qt meta object system.
   */
    QExtOsgiPluginEvent();

    ~QExtOsgiPluginEvent();

    /**
   * Can be used to check if this QExtOsgiPluginEvent instance is valid,
   * or if it has been constructed using the default constructor.
   *
   * @return <code>true</code> if this event object is valid,
   *         <code>false</code> otherwise.
   */
    bool isNull() const;

    /**
   * Creates a plugin event of the specified type.
   *
   * @param type The event type.
   * @param plugin The plugin which had a lifecycle change.
   */
    QExtOsgiPluginEvent(Type type, QSharedPointer<QExtOsgiPlugin> plugin);

    QExtOsgiPluginEvent(const QExtOsgiPluginEvent &other);

    QExtOsgiPluginEvent &operator=(const QExtOsgiPluginEvent &other);

    /**
   * Returns the plugin which had a lifecycle change.
   *
   * @return The plugin that had a change occur in its lifecycle.
   */
    QSharedPointer<QExtOsgiPlugin> getPlugin() const;

    /**
   * Returns the type of lifecycle event. The type values are:
   * <ul>
   * <li>{@link #INSTALLED}
   * <li>{@link #RESOLVED}
   * <li>{@link #LAZY_ACTIVATION}
   * <li>{@link #STARTING}
   * <li>{@link #STARTED}
   * <li>{@link #STOPPING}
   * <li>{@link #STOPPED}
   * <li>{@link #UPDATED}
   * <li>{@link #UNRESOLVED}
   * <li>{@link #UNINSTALLED}
   * </ul>
   *
   * @return The type of lifecycle event.
   */
    Type getType() const;

};

Q_DECLARE_METATYPE(QExtOsgiPluginEvent)

/**
 * \ingroup PluginFramework
 * @{
 */
QEXT_OSGI_API QDebug operator<<(QDebug debug, QExtOsgiPluginEvent::Type eventType);
QEXT_OSGI_API QDebug operator<<(QDebug debug, const QExtOsgiPluginEvent &event);
/** @}*/

#endif // _QEXTOSGIPLUGINEVENT_H
