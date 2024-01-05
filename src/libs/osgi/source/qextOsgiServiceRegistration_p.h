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


#ifndef _QEXTOSGISERVICEREGISTRATIONPRIVATE_H
#define _QEXTOSGISERVICEREGISTRATIONPRIVATE_H

#include <qextOsgiServiceReference.h>
#include <private/qextOsgiServiceProperties_p.h>

#include <QHash>
#include <QMutex>


class QExtOsgiPluginPrivate;
class QExtOsgiServiceRegistration;

/**
 * \ingroup PluginFramework
 */
class QExtOsgiServiceRegistrationPrivate
{

protected:

    friend class QExtOsgiServiceRegistration;

    // The QExtOsgiServiceReferencePrivate class holds a pointer to a
    // QExtOsgiServiceRegistrationPrivate instance and needs to manipulate
    // its reference count. This way it can keep the QExtOsgiServiceRegistrationPrivate
    // instance alive and keep returning service properties for
    // unregistered service instances.
    friend class QExtOsgiServiceReferencePrivate;

    /**
   * Reference count for implicitly shared private implementation.
   */
    QAtomicInt ref;

    /**
   * Service or QExtOsgiServiceFactory object.
   */
    QObject* service;

public:

    /**
   * Plugin registering this service.
   */
    QExtOsgiPluginPrivate* plugin;

    /**
   * Reference object to this service registration.
   */
    QExtOsgiServiceReference reference;

    /**
   * Service properties.
   */
    QExtOsgiServiceProperties properties;

    /**
   * Plugins dependent on this service. Integer is used as
   * reference counter, counting number of unbalanced getService().
   */
    QHash<QSharedPointer<QExtOsgiPlugin>,int> dependents;

    /**
   * Object instances that factory has produced.
   */
    QHash<QSharedPointer<QExtOsgiPlugin>, QObject*> serviceInstances;

    /**
   * Is service available. I.e., if <code>true</code> then holders
   * of a QExtOsgiServiceReference for the service are allowed to get it.
   */
    volatile bool available;

    /**
   * Avoid recursive unregistrations. I.e., if <code>true</code> then
   * unregistration of this service has started but is not yet
   * finished.
   */
    volatile bool unregistering;

    /**
   * Lock object for synchronous event delivery.
   */
    QMutex eventLock;

    QMutex propsLock;

    QExtOsgiServiceRegistrationPrivate(QExtOsgiPluginPrivate* plugin, QObject* service,
                                  const QExtOsgiDictionary& props);

    virtual ~QExtOsgiServiceRegistrationPrivate();

    /**
   * Check if a plugin uses this service
   *
   * @param p Plugin to check
   * @return true if plugin uses this service
   */
    bool isUsedByPlugin(QSharedPointer<QExtOsgiPlugin> p);

    virtual QObject* getService();

private:

    Q_DISABLE_COPY(QExtOsgiServiceRegistrationPrivate)

};


#endif // _QEXTOSGISERVICEREGISTRATIONPRIVATE_H
