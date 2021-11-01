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

#ifndef QTKSERVICEREFERENCE_P_H
#define QTKSERVICEREFERENCE_P_H

#include "qtkserviceproperties_p.h"

#include <QAtomicInt>
#include <QSharedPointer>

class QObject;

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

class QTKServiceRegistrationPrivate;
class QTKServiceReference;
class QTKPlugin;

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKServiceReferencePrivate class
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKServiceReferencePrivate
{
public:
    QTKServiceReferencePrivate(QTKServiceRegistrationPrivate *pServiceRegPrivate);
    ~QTKServiceReferencePrivate();

    /**
     * @brief getService
      * Get the service object.
      *
      * @param pPlugin requester of service.
      * @return Service requested or null in case of failure.
      */
    QObject *getService(QSharedPointer<QTKPlugin> pPlugin);

    /**
     * @brief ungetService
     * Unget the service object.
     *
     * @param pPlugin Plugin who wants remove service.
     * @param bCheckRefCounter If true decrement refence counter and remove service
     *                        if we reach zero. If false remove service without
     *                        checking refence counter.
     * @return True if service was remove or false if only refence counter was
     *         decremented.
     */
    bool ungetService(QSharedPointer<QTKPlugin> pPlugin, bool bCheckRefCounter);

    /**
     * @brief getProperties
     * Get all properties registered with this service.
     *
     * @return A ctkDictionary object containing properties or being empty
     *         if service has been removed.
     */
    const QTKServiceProperties &getProperties() const;

    /**
     * @brief getProperty
     * Returns the property value to which the specified property key is mapped
     * in the properties <code>ctkDictionary</code> object of the service
     * referenced by this <code>ctkServiceReference</code> object.
     *
     * <p>
     * Property keys are case-insensitive.
     *
     * <p>
     * This method must continue to return property values after the service has
     * been unregistered. This is so references to unregistered services can
     * still be interrogated.
     *
     * @param strKey The property key.
     * @param bLock If <code>true</code>, access of the properties of the service
     *        referenced by this <code>ctkServiceReference</code> object will be
     *        synchronized.
     * @return The property value to which the key is mapped; an invalid QVariant
     *         if there is no property named after the key.
     */
    QVariant getProperty(const QString &strKey, bool bLock) const;

    /**
     * @brief m_ref
     * Reference count for implicitly shared private implementation.
     */
    QAtomicInt m_ref;

    /**
     * @brief m_pRegistration
     * Link to registration object for this reference.
     */
    QTKServiceRegistrationPrivate* const m_pRegistration;

protected:
    friend uint QTK_PLUGINFRAMEWORK_EXPORT qHash(const QTKServiceReference &serviceRef);

private:
    Q_DISABLE_COPY(QTKServiceReferencePrivate)
};

QTK_PLUGINFRAMEWORK_END_NAMESPACE

#endif // QTKSERVICEREFERENCE_P_H
