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

#ifndef QTKSERVICEREGISTRATION_H
#define QTKSERVICEREGISTRATION_H

#include "qtkpluginframework_global.h"
#include "qtkdictionary.h"
#include "qtkservicereference.h"

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

class QTKServiceRegistrationPrivate;

/**
 * @brief The QTKServiceRegistration class
 * @ingroup PluginFramework
 *
 * A registered service.
 *
 * <p>
 * The Framework returns a <code>QTKServiceRegistration</code> object when a
 * <code>QTKPluginContext#registerService()</code> method invocation is successful.
 * The <code>QTKServiceRegistration</code> object is for the private use of the
 * registering plugin and should not be shared with other plugins.
 * <p>
 * The <code>QTKServiceRegistration</code> object may be used to update the
 * properties of the service or to unregister the service.
 *
 * @see QTKPluginContext#registerService()
 * @remarks This class is thread safe.
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKServiceRegistration
{
public:
    /**
     * @brief QTKServiceRegistration
     * Creates an invalid ctkServiceRegistration object. You can use
     * this object in boolean expressions and it will evaluate to
     * <code>false</code>.
     */
    QTKServiceRegistration();
    QTKServiceRegistration(const QTKServiceRegistration &serviceReg);
    ~QTKServiceRegistration();

    /**
     * @brief getReference
     * Returns a <code>ctkServiceReference</code> object for a service being
     * registered.
     * <p>
     * The <code>ctkServiceReference</code> object may be shared with other
     * plugins.
     *
     * @throws ctkIllegalStateException If this
     *         <code>ctkServiceRegistration</code> object has already been
     *         unregistered or if it is invalid.
     * @return <code>ctkServiceReference</code> object.
     */
    QTKServiceReference getReference() const;

    /**
     * @brief setProperties
     * Updates the properties associated with a service.
     *
     * <p>
     * The {@link ctkPluginConstants#OBJECTCLASS} and {@link ctkPluginConstants#SERVICE_ID} keys
     * cannot be modified by this method. These values are set by the Framework
     * when the service is registered in the environment.
     *
     * <p>
     * The following steps are required to modify service properties:
     * <ol>
     * <li>The service's properties are replaced with the provided properties.
     * <li>A service event of type {@link ctkServiceEvent#MODIFIED} is fired.
     * </ol>
     *
     * @param properties The properties for this service. See {@link ctkPluginConstants}
     *        for a list of standard service property keys. Changes should not
     *        be made to this object after calling this method. To update the
     *        service's properties this method should be called again.
     *
     * @throws ctkIllegalStateException If this <code>ctkServiceRegistration</code>
     *         object has already been unregistered or if it is invalid.
     * @throws ctkInvalidArgumentException If <code>properties</code> contains
     *         case variants of the same key name.
     */
    void setProperties(const QTKDictionary &properties);

    /**
     * @brief unregister
     * Unregisters a service. Remove a <code>ctkServiceRegistration</code> object
     * from the Framework service registry. All <code>ctkServiceReference</code>
     * objects associated with this <code>ctkServiceRegistration</code> object
     * can no longer be used to interact with the service once unregistration is
     * complete.
     *
     * <p>
     * The following steps are required to unregister a service:
     * <ol>
     * <li>The service is removed from the Framework service registry so that
     * it can no longer be obtained.
     * <li>A service event of type {@link ctkServiceEvent#UNREGISTERING} is fired
     * so that plugins using this service can release their use of the service.
     * Once delivery of the service event is complete, the
     * <code>ctkServiceReference</code> objects for the service may no longer be
     * used to get a service object for the service.
     * <li>For each plugin whose use count for this service is greater than
     * zero: <br>
     * The plugin's use count for this service is set to zero. <br>
     * If the service was registered with a {@link ctkServiceFactory} object, the
     * <code>ctkServiceFactory#ungetService</code> method is called to release
     * the service object for the plugin.
     * </ol>
     *
     * @throws ctkIllegalStateException If this
     *         <code>ctkServiceRegistration</code> object has already been
     *         unregistered or if it is invalid.
     * @see ctkPluginContext#ungetService
     * @see ctkServiceFactory#ungetService
     */
    void unregister();

    operator bool() const;

    /**
     * @brief operator =
     * Releases any resources held or locked by this
     * <code>ctkServiceRegistration</code> and renders it invalid.
     */
    QTKServiceRegistration& operator=(int iNull);
    bool operator<(const QTKServiceRegistration &other) const;
    bool operator==(const QTKServiceRegistration &serviceReg) const;
    QTKServiceRegistration& operator=(const QTKServiceRegistration &serviceReg);

protected:
    QTKServiceRegistration(QTKServiceRegistrationPrivate *pRegistrationPrivate);
    QTKServiceRegistration(QTKPluginPrivate *pPlugin, QObject *pService, const QTKDictionary &pProperties);

    friend class QTKServices;
    friend class QTKServiceReferencePrivate;
    friend uint QTK_PLUGINFRAMEWORK_EXPORT qHash(const QTKServiceRegistration &serviceReg);

    QTKServiceRegistrationPrivate* d_ptr;

private:
    Q_DECLARE_PRIVATE(QTKServiceRegistration)
};

uint QTK_PLUGINFRAMEWORK_EXPORT qHash(const QTKServiceRegistration &serviceReg);

QTK_PLUGINFRAMEWORK_END_NAMESPACE

#endif // QTKSERVICEREGISTRATION_H
