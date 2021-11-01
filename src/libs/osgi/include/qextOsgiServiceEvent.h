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

#ifndef QTKSERVICEEVENT_H
#define QTKSERVICEEVENT_H

#include "qtkpluginframework_global.h"
#include "qtkservicereference.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QMetaType>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

class QTKServiceEventData;

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKServiceEvent class
 * An event from the Plugin Framework describing a service lifecycle change.
 * <p>
 * <code>QTKServiceEvent</code> objects are delivered to
 * slots connected via QTKPluginContext::connectServiceListener() when a
 * change occurs in this service's lifecycle. A type code is used to identify
 * the event type for future extendability.
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKServiceEvent
{
public:
    enum Type {
        /**
         * This service has been registered.
         * <p>
         * This event is synchronously delivered <strong>after</strong> the service
         * has been registered with the Framework.
         *
         * @see QTKPluginContext#registerService()
         */
        Type_Registered = 0x00000001,
        /**
         * The properties of a registered service have been modified.
         * <p>
         * This event is synchronously delivered <strong>after</strong> the service
         * properties have been modified.
         *
         * @see QTKServiceRegistration#setProperties
         */
        Type_Modified = 0x00000002,
        /**
         * This service is in the process of being unregistered.
         * <p>
         * This event is synchronously delivered <strong>before</strong> the service
         * has completed unregistering.
         *
         * <p>
         * If a plugin is using a service that is <code>Type_Unregistering</code>, the
         * plugin should release its use of the service when it receives this event.
         * If the plugin does not release its use of the service when it receives
         * this event, the Framework will automatically release the plugin's use of
         * the service while completing the service unregistration operation.
         *
         * @see QTKServiceRegistration#unregister
         * @see QTKPluginContext#ungetService
         */
        Type_Unregistering = 0x00000004,
        /**
         * The properties of a registered service have been modified and the new
         * properties no longer match the listener's filter.
         * <p>
         * This event is synchronously delivered <strong>after</strong> the service
         * properties have been modified. This event is only delivered to slots
         * which were added with a non-<code>null</code> filter where the filter
         * matched the service properties prior to the modification but the filter
         * does not match the modified service properties.
         *
         * @see QTKServiceRegistration#setProperties
         */
        Type_ModifiedEndMatch = 0x00000008
    };

    /**
     * @brief QTKServiceEvent
     * Default constructor for use with the Qt meta object system.
     */
    QTKServiceEvent();

    /**
     * @brief QTKServiceEvent
     * Creates a new service event object.
     *
     * @param eType The event type.
     * @param reference A <code>QTKServiceReference</code> object to the service
     *        that had a lifecycle change.
     */
    QTKServiceEvent(Type eType, const QTKServiceReference &reference);
    QTKServiceEvent(const QTKServiceEvent &other);
    ~QTKServiceEvent();

    /**
     * @brief isNull
     * @return
     * Can be used to check if this QTKServiceEvent instance is valid,
     * or if it has been constructed using the default constructor.
     *
     * @return <code>true</code> if this event object is valid,
     *         <code>false</code> otherwise.
     */
    bool isNull() const;

    /**
     * @brief getServiceReference
     * Returns a reference to the service that had a change occur in its
     * lifecycle.
     * <p>
     * This reference is the source of the event.
     *
     * @return Reference to the service that had a lifecycle change.
     */
    QTKServiceReference getServiceReference() const;

    /**
     * @brief getType
     * Returns the type of event. The event type values are:
     * <ul>
     * <li>{@link #Type_Registered} </li>
     * <li>{@link #Type_Modified} </li>
     * <li>{@link #Type_ModifiedEndMatch} </li>
     * <li>{@link #Type_Unregistering} </li>
     * </ul>
     *
     * @return Type of service lifecycle change.
     */
    Type getType() const;
    static const char *getTypeName(const Type &eType);

    QTKServiceEvent& operator=(const QTKServiceEvent &other);

    QSharedDataPointer<QTKServiceEventData> d;
};

/**
 * @ingroup QTKPluginFramework
 * @{
 */
QTK_PLUGINFRAMEWORK_EXPORT QDebug operator<<(QDebug dbg, QTKServiceEvent::Type eType);
QTK_PLUGINFRAMEWORK_EXPORT QDebug operator<<(QDebug dbg, const QTKServiceEvent &event);
/** @}*/

QTK_PLUGINFRAMEWORK_END_NAMESPACE

Q_DECLARE_METATYPE(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKServiceEvent)

#endif // QTKSERVICEEVENT_H
