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

#ifndef QTKSERVICEREGISTRATION_P_H
#define QTKSERVICEREGISTRATION_P_H

#include "qtkserviceproperties_p.h"
#include "qtkservicereference.h"

#include <QHash>
#include <QMutex>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

class QTKPluginPrivate;
class QTKServiceRegistration;

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKServiceRegistrationPrivate class
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKServiceRegistrationPrivate
{
public:
    QTKServiceRegistrationPrivate(QTKPluginPrivate *pPlugin, QObject *pService,
                                  const QTKDictionary &props);
    virtual ~QTKServiceRegistrationPrivate();

    /**
     * @brief isUsedByPlugin
     * Check if a plugin uses this service
     *
     * @param pPluginPrivate Plugin to check
     * @return true if plugin uses this service
     */
    bool isUsedByPlugin(QSharedPointer<QTKPlugin> pPluginPrivate);
    virtual QObject *getService();

    friend class QTKServiceRegistration;

    // The ctkServiceReferencePrivate class holds a pointer to a
    // ctkServiceRegistrationPrivate instance and needs to manipulate
    // its reference count. This way it can keep the ctkServiceRegistrationPrivate
    // instance alive and keep returning service properties for
    // unregistered service instances.
    friend class QTKServiceReferencePrivate;

    /**
     * @brief m_pPluginPrivate
     * Plugin registering this service.
     */
    QTKPluginPrivate *m_pPluginPrivate;

    /**
     * @brief m_reference
     * Reference object to this service registration.
     */
    QTKServiceReference m_reference;

    /**
     * @brief m_properties
     * Service properties.
     */
    QTKServiceProperties m_properties;

    /**
     * @brief m_mapDependents
     * Plugins dependent on this service. Integer is used as
     * reference counter, counting number of unbalanced getService().
     */
    QHash<QSharedPointer<QTKPlugin>, int> m_mapDependents;

    /**
     * @brief m_mapServiceInstances
     * Object instances that factory has produced.
     */
    QHash<QSharedPointer<QTKPlugin>, QObject*> m_mapServiceInstances;

    /**
     * @brief m_bAvailable
     * Is service available. I.e., if <code>true</code> then holders
     * of a ctkServiceReference for the service are allowed to get it.
     */
    volatile bool m_bAvailable;

    /**
     * @brief m_bUnregistering
     * Avoid recursive unregistrations. I.e., if <code>true</code> then
     * unregistration of this service has started but is not yet
     * finished.
     */
    volatile bool m_bUnregistering;

    /**
     * @brief m_ref
     * Reference count for implicitly shared private implementation.
     */
    QAtomicInt m_ref;

    /**
     * @brief m_pService
     * Service or ctkServiceFactory object.
     */
    QObject *m_pService;

    /**
     * @brief m_eventLock
     * Lock object for synchronous event delivery.
     */
    QMutex m_eventLock;
    QMutex m_propsLock;

private:
    Q_DISABLE_COPY(QTKServiceRegistrationPrivate)
};

QTK_PLUGINFRAMEWORK_END_NAMESPACE

#endif // QTKSERVICEREGISTRATION_P_H
