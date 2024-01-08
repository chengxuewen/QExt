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


#ifndef _QEXTOSGICONFIGURATIONEVENT_H
#define _QEXTOSGICONFIGURATIONEVENT_H

#include <qextOsgiServiceReference.h>

#include <QSharedDataPointer>
#include <QDebug>

class QExtOsgiConfigurationEventData;

/**
 * \ingroup ConfigAdmin
 * A Configuration Event.
 *
 * <p>
 * <code>QExtOsgiConfigurationEvent</code> objects are delivered to all registered
 * <code>QExtOsgiConfigurationListener</code> service objects. QExtOsgiConfigurationEvents
 * must be asynchronously delivered in chronological order with respect to each
 * listener.
 *
 * <p>
 * An enum type is used to identify the type of event. The following event types
 * are defined:
 * <ul>
 * <li>{@link #CM_UPDATED}
 * <li>{@link #CM_DELETED}
 * </ul>
 * Additional event types may be defined in the future.
 *
 * <p>
 * Security Considerations. <code>QExtOsgiConfigurationEvent</code> objects do not
 * provide <code>QExtOsgiConfiguration</code> objects, so no sensitive configuration
 * information is available from the event. If the listener wants to locate the
 * <code>QExtOsgiConfiguration</code> object for the specified pid, it must use
 * <code>QExtOsgiConfigurationAdmin</code>.
 *
 * @see QExtOsgiConfigurationListener
 */
class QEXT_OSGI_API QExtOsgiConfigurationEvent
{

    QSharedDataPointer<QExtOsgiConfigurationEventData> d;

public:

    enum Type
    {

        /**
     * A <code>QExtOsgiConfiguration</code> has been updated.
     *
     * <p>
     * This <code>QExtOsgiConfigurationEvent</code> type indicates that a
      <code>QExtOsgiConfiguration</code> object has been updated with new properties.
     *
     * An event is fired when a call to {@link QExtOsgiConfiguration#update(const QExtOsgiDictionary&)}
     * successfully changes a configuration.
     *
     * <p>
     * The value of <code>CM_UPDATED</code> is 1.
     */
        CM_UPDATED  = 0x00000001,

        /**
     * A <code>QExtOsgiConfiguration</code> has been deleted.
     *
     * <p>
     * This <code>QExtOsgiConfigurationEvent</code> type indicates that a
     * <code>QExtOsgiConfiguration</code> object has been deleted.
     *
     * An event is fired when a call to {@link QExtOsgiConfiguration#remove()}
     * successfully deletes a configuration.
     *
     * <p>
     * The value of <code>CM_DELETED</code> is 2.
     */
        CM_DELETED  = 0x00000002

    };

    /**
   * Default constructor for use with the Qt meta object system.
   */
    QExtOsgiConfigurationEvent();

    ~QExtOsgiConfigurationEvent();

    /**
   * Can be used to check if this QExtOsgiConfigurationEvent instance is valid,
   * or if it has been constructed using the default constructor.
   *
   * @return <code>true</code> if this event object is valid,
   *         <code>false</code> otherwise.
   */
    bool isNull() const;

    /**
   * Constructs a <code>ConfigurationEvent</code> object from the given
   * <code>ServiceReference</code> object, event type, and pids.
   *
   * @param reference The <code>ServiceReference</code> object of the
   *        Configuration Admin service that created this event.
   * @param type The event type. See {@link #getType}.
   * @param factoryPid The factory pid of the associated configuration if the
   *        target of the configuration is a ManagedServiceFactory. Otherwise
   *        <code>null</code> if the target of the configuration is a
   *        ManagedService.
   * @param pid The pid of the associated configuration.
   */
    QExtOsgiConfigurationEvent(const QExtOsgiServiceReference &reference,
                          Type type, const QString &factoryPid,
                          const QString &pid);

    QExtOsgiConfigurationEvent(const QExtOsgiConfigurationEvent &other);

    QExtOsgiConfigurationEvent &operator=(const QExtOsgiConfigurationEvent &other);

    /**
   * Returns the factory pid of the associated configuration.
   *
   * @return Returns the factory pid of the associated configuration if the
   *         target of the configuration is a QExtOsgiManagedServiceFactory. Otherwise
   *         an invalid string if the target of the configuration is a
   *         QExtOsgiManagedService.
   */
    QString getFactoryPid() const;

    /**
   * Returns the pid of the associated configuration.
   *
   * @return Returns the pid of the associated configuration.
   */
    QString getPid() const;

    /**
   * Return the type of this event.
   * <p>
   * The type values are:
   * <ul>
   * <li>{@link #CM_UPDATED}
   * <li>{@link #CM_DELETED}
   * </ul>
   *
   * @return The type of this event.
   */
    int getType() const;

    /**
   * Return the <code>QExtOsgiServiceReference</code> object of the Configuration
   * Admin service that created this event.
   *
   * @return The <code>QExtOsgiServiceReference</code> object for the Configuration
   *         Admin service that created this event.
   */
    QExtOsgiServiceReference getReference() const;
};

/**
 * \ingroup ConfigAdmin
 */

QEXT_OSGI_API QDebug operator<<(QDebug dbg, QExtOsgiConfigurationEvent::Type type);
QEXT_OSGI_API QDebug operator<<(QDebug dbg, const QExtOsgiConfigurationEvent &event);

/** @}*/

#endif // _QEXTOSGICONFIGURATIONEVENT_H
