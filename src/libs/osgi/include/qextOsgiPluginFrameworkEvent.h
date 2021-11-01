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

#ifndef QTKPLUGINFRAMEWORKEVENT_H
#define QTKPLUGINFRAMEWORKEVENT_H

#include "qtkpluginframework_global.h"

#include <QTKCore/QTKException>

#include <QSharedDataPointer>
#include <QSharedPointer>
#include <QMetaType>

QTK_CORE_USE_NAMESPACE

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

class QTKPlugin;
class QTKPluginFrameworkEventData;

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKPluginFrameworkEvent class
 * A general event from the Framework.
 *
 * <p>
 * <code>QTKPluginFrameworkEvent</code> objects are delivered to slots connected
 * via QTKPluginContext::connectFrameworkListener when a general event occurs
 * within the plugin environment.
 * A type code is used to identify the event type for future extendability.
 *
 * @see QTKPluginContext#connectFrameworkListener
 * @see QTKEventBus
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKPluginFrameworkEvent
{
public:
    enum Type {
        /**
         * The Framework has started.
         *
         * <p>
         * This event is fired when the Framework has started after all installed
         * plugins that are marked to be started have been started and the Framework
         * has reached the initial start level. The source of this event is the
         * System Plugin.
         */
        Type_FrameworkStarted,
        /**
         * An error has occurred.
         *
         * <p>
         * There was an error associated with a plugin.
         */
        Type_PluginError,
        /**
         * A warning has occurred.
         *
         * <p>
         * There was a warning associated with a plugin.
         */
        Type_PluginWarning,
        /**
         * An informational event has occurred.
         *
         * <p>
         * There was an informational event associated with a plugin.
         */
        Type_PluginInfo,
        /**
         * The Framework has stopped.
         *
         * <p>
         * This event is fired when the Framework has been stopped because of a stop
         * operation on the system plugin. The source of this event is the System
         * Plugin.
         */
        Type_FrameworkStopped,
        /**
         * The Framework has stopped during update.
         *
         * <p>
         * This event is fired when the Framework has been stopped because of an
         * update operation on the system plugin. The Framework will be restarted
         * after this event is fired. The source of this event is the System Plugin.
         */
        Type_FrameworkStoppedUpdate,
        /**
         * The Framework did not stop before the wait timeout expired.
         *
         * <p>
         * This event is fired when the Framework did not stop before the wait
         * timeout expired. The source of this event is the System Plugin.
         */
        Type_FrameworkWaitTimeOut
    };

    /**
     * @brief QTKPluginFrameworkEvent
     * Default constructor for use with the Qt meta object system.
     */
    QTKPluginFrameworkEvent();

    /**
     * @brief QTKPluginFrameworkEvent
     * Creates a Framework event regarding the specified plugin and exception.
     *
     * @param eType The event type.
     * @param pPlugin The event source.
     * @param exception The related exception.
     */
    QTKPluginFrameworkEvent(Type eType, QSharedPointer<QTKPlugin> pPlugin, const QTKException &exception);

    /**
     * @brief QTKPluginFrameworkEvent
     * Creates a Framework event regarding the specified plugin.
     *
     * @param eType The event type.
     * @param pPlugin The event source.
     */
    QTKPluginFrameworkEvent(Type eType, QSharedPointer<QTKPlugin> pPlugin);
    QTKPluginFrameworkEvent(const QTKPluginFrameworkEvent &other);

    ~QTKPluginFrameworkEvent();

    QTKPluginFrameworkEvent& operator=(const QTKPluginFrameworkEvent &other);

    /**
     * @brief isNull
     * Can be used to check if this QTKPluginFrameworkEvent instance is valid,
     * or if it has been constructed using the default constructor.
     *
     * @return <code>true</code> if this event object is valid,
     *         <code>false</code> otherwise.
     */
    bool isNull() const;

    /**
     * @brief getErrorString
     * Returns the exception error string related to this event.
     *
     * @return The related error string.
     */
    QString getErrorString() const;

    /**
     * @brief getPlugin
     * Returns the plugin associated with the event. This plugin is also the
     * source of the event.
     *
     * @return The plugin associated with the event.
     */
    QSharedPointer<QTKPlugin> getPlugin() const;

    /**
     * @brief getType
     * Returns the type of framework event.
     * <p>
     * The type values are:
     * <ul>
     * <li>{@link #Type_FrameworkStarted}
     * <li>{@link #Type_PluginError}
     * <li>{@link #Type_PluginWarning}
     * <li>{@link #Type_PluginInfo}
     * <li>{@link #Type_FrameworkStopped}
     * <li>{@link #Type_FrameworkStoppedUpdate}
     * <li>{@link #Type_FrameworkWaitTimeOut}
     * </ul>
     *
     * @return The type of state change.
     */
    Type getType() const;

private:
    QSharedDataPointer<QTKPluginFrameworkEventData> d;
};

/**
 * @ingroup QTKPluginFramework
 * @{
 */
QTK_PLUGINFRAMEWORK_EXPORT QDebug operator<<(QDebug dbg, QTKPluginFrameworkEvent::Type type);
QTK_PLUGINFRAMEWORK_EXPORT QDebug operator<<(QDebug dbg, const QTKPluginFrameworkEvent &event);
/** @} */

QTK_PLUGINFRAMEWORK_END_NAMESPACE

Q_DECLARE_METATYPE(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKPluginFrameworkEvent)

#endif // QTKPLUGINFRAMEWORKEVENT_H
