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

#ifndef QTKPLUGINEVENT_H
#define QTKPLUGINEVENT_H

#include "qtkpluginframework_global.h"

#include <QSharedDataPointer>
#include <QSharedPointer>
#include <QMetaType>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

class QTKPlugin;
class QTKPluginEventData;

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKPluginEvent class
 * An event from the Framework describing a plugin lifecycle change.
 * <p>
 * <code>QTKPluginEvent</code> objects are delivered to slots connected
 * via QTKPluginContext::connectPluginListener() when a change
 * occurs in a plugins's lifecycle. A type code is used to identify
 * the event type for future extendability.
 *
 * @see QTKPluginContext#connectPluginListener
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKPluginEvent
{
public:
    enum Type {
        /**
         * The plugin has been installed.
         *
         * @see QTKPluginContext::installBundle(const QString&)
         */
        Type_Installed,

        /**
         * The plugin has been started.
         * <p>
         * The plugin's
         * @link QTKPluginActivator::start(QTKPluginContext*) QTKPluginActivator start\endlink method
         * has been executed.
         *
         * @see QTKPlugin::start()
         */
        Type_Started,

        /**
         * The plugin has been stopped.
         * <p>
         * The plugin's
         * @link QTKPluginActivator::stop(QTKPluginContext*) QTKPluginActivator stop\endlink method
         * has been executed.
         *
         * @see QTKPlugin::stop()
         */
        Type_Stopped,

        /**
         * The plugin has been updated.
         *
         * @see QTKPlugin::update()
         */
        Type_Updated,

        /**
         * The plugin has been uninstalled.
         *
         * @see QTKPlugin::uninstall()
         */
        Type_Uninstalled,

        /**
         * The plugin has been resolved.
         *
         * @see QTKPlugin::RESOLVED
         */
        Type_Resolved,

        /**
         * The plugin has been unresolved.
         *
         * @see QTKPlugin::INSTALLED
         */
        Type_Unresolved,

        /**
         * The plugin is about to be activated.
         * <p>
         * The plugin's
         * @link QTKPluginActivator::start(QTKPluginContext*) QTKPluginActivator start\endlink method
         * is about to be called. This
         * event is only delivered to synchronuous slots, which have been registered with
         * Qt::DirectConnection or Qt::BlockingQueuedConnection in QTKPluginContext::connectPluginListener().
         *
         * @see QTKPlugin::start()
         */
        Type_Starting,

        /**
         * The plugin is about to deactivated.
         * <p>
         * The plugin's
         * @link QTKPluginActivator::stop(QTKPluginContext*) QTKPluginActivator stop@endlink method
         * is about to be called. This
         * event is only delivered to synchronuous slots, which have been registered with
         * Qt::DirectConnection or Qt::BlockingQueuedConnection in QTKPluginContext::connectPluginListener().
         *
         * @see QTKPlugin::stop()
         */
        Type_Stopping,

        /**
         * The plugin will be lazily activated.
         * <p>
         * The plugin has a \link QTKPluginConstants::ACTIVATION_LAZY lazy activation policy\endlink
         * and is waiting to be activated. It is now in the
         * @link QTKPlugin::STARTING STARTING\endlink state and has a valid
         * <code>QTKPluginContext</code>. This
         * event is only delivered to synchronuous slots, which have been registered with
         * Qt::DirectConnection or Qt::BlockingQueuedConnection in QTKPluginContext::connectPluginListener().
         */
        Type_LazyActivation
    };

    /**
     * @brief QTKPluginEvent
     * Default constructor for use with the Qt meta object system.
     */
    QTKPluginEvent();

    /**
     * @brief QTKPluginEvent
     * Creates a plugin event of the specified type.
     *
     * @param eType The event type.
     * @param pPlugin The plugin which had a lifecycle change.
     */
    QTKPluginEvent(Type eType, QSharedPointer<QTKPlugin> pPlugin);
    QTKPluginEvent(const QTKPluginEvent &other);
    ~QTKPluginEvent();

    /**
     * @brief isNull
     * Can be used to check if this QTKPluginEvent instance is valid,
     * or if it has been constructed using the default constructor.
     *
     * @return <code>true</code> if this event object is valid,
     *         <code>false</code> otherwise.
     */
    bool isNull() const;

    /**
     * @brief getPlugin
     * Returns the plugin which had a lifecycle change.
     *
     * @return The plugin that had a change occur in its lifecycle.
     */
    QSharedPointer<QTKPlugin> getPlugin() const;

    /**
     * @brief getType
     * Returns the type of lifecyle event. The type values are:
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
    QTKPluginEvent& operator=(const QTKPluginEvent &other);

private:
    QSharedDataPointer<QTKPluginEventData> d;
};

/**
 * @ingroup QTKPluginFramework
 * @{
 */
QTK_PLUGINFRAMEWORK_EXPORT QDebug operator<<(QDebug debug, QTKPluginEvent::Type eEventType);
QTK_PLUGINFRAMEWORK_EXPORT QDebug operator<<(QDebug debug, const QTKPluginEvent &event);
/** @}*/

QTK_PLUGINFRAMEWORK_END_NAMESPACE

Q_DECLARE_METATYPE(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKPluginEvent)

#endif // QTKPLUGINEVENT_H
