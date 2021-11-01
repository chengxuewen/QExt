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

#ifndef QTKSERVICES_P_H
#define QTKSERVICES_P_H

#include "qtkplugin_p.h"
#include "qtkserviceregistration.h"

#include <QHash>
#include <QObject>
#include <QMutex>
#include <QStringList>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKServices class
 * Here we handle all the services that are registered in the framework.
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKServices
{
public:
    QTKServices(QTKPluginFrameworkContext *pPFWContext);
    ~QTKServices();

    /**
     * @brief createServiceProperties
     * Creates a new ctkDictionary object containing <code>in</code>
     * with the keys converted to lower case.
     *
     * @param listClasses A list of class names which will be added to the
     *        created ctkDictionary object under the key
     *        PluginConstants::OBJECTCLASS.
     * @param lId A service id which will be used instead of a default one.
     */
    static QTKDictionary createServiceProperties(const QTKDictionary &in,
                                                 const QStringList &listClasses = QStringList(),
                                                 long lId = -1);

    /**
     * @brief registerService
     * Register a service in the framework wide register.
     *
     * @param plugin The plugin registering the service.
     * @param classes The class names under which the service can be located.
     * @param service The service object.
     * @param properties The properties for this service.
     * @return A ctkServiceRegistration object.
     * @exception ctkInvalidArgumentException If one of the following is true:
     * <ul>
     * <li>The service object is 0.</li>
     * <li>The service parameter is not a ctkServiceFactory or an
     * instance of all the named classes in the classes parameter.</li>
     * </ul>
     */
    QTKServiceRegistration registerService(QTKPluginPrivate *pPlugin,
                                           const QStringList &listClasses,
                                           QObject *pService,
                                           const QTKDictionary &properties);

    /**
     * @brief updateServiceRegistrationOrder
     * Service ranking changed, reorder registered services
     * according to ranking.
     *
     * @param serviceReg The ctkServiceRegistrationPrivate object.
     * @param listClasses New rank of object.
     */
    void updateServiceRegistrationOrder(const QTKServiceRegistration &serviceReg,
                                        const QStringList &listClasses);

    /**
     * @brief checkServiceClass
     * Checks that a given service object is an instance of the given
     * class name.
     *
     * @param pService The service object to check.
     * @param strClasse The class name to check for.
     */
    bool checkServiceClass(QObject *pService, const QString &strClasse) const;

    /**
     * @brief get
     * Get all services implementing a certain class.
     * Only used internally by the framework.
     *
     * @param strClazz The class name of the requested service.
     * @return A sorted list of {@link ctkServiceRegistrationPrivate} objects.
     */
    QList<QTKServiceRegistration> get(const QString &strClazz) const;

    /**
     * @brief get
     * Get a service implementing a certain class.
     *
     * @param pPlugin The plugin requesting reference
     * @param strClazz The class name of the requested service.
     * @return A {@link ctkServiceReference} object.
     */
    QTKServiceReference get(QTKPluginPrivate *pPlugin, const QString &strClazz) const;

    /**
     * @brief get
     * Get all services implementing a certain class and then
     * filter these with a property filter.
     *
     * @param strClazz The class name of requested service.
     * @param strFilter The property filter.
     * @param pPlugin The plugin requesting reference.
     * @return A list of {@link ctkServiceReference} object.
     */
    QList<QTKServiceReference> get(const QString &strClazz, const QString &strFilter, QTKPluginPrivate *pPlugin) const;

    /**
     * @brief removeServiceRegistration
     * Remove a registered service.
     *
     * @param serviceReg The ctkServiceRegistration object that is registered.
     */
    void removeServiceRegistration(const QTKServiceRegistration &serviceReg) ;

    /**
     * @brief getRegisteredByPlugin
     * Get all services that a plugin has registered.
     *
     * @param pPluginPrivate The plugin
     * @return A set of {@link ctkServiceRegistration} objects
     */
    QList<QTKServiceRegistration> getRegisteredByPlugin(QTKPluginPrivate *pPluginPrivate) const;

    /**
     * @brief getUsedByPlugin
     * Get all services that a plugin uses.
     *
     * @param pPlugin The plugin
     * @return A set of {@link ctkServiceRegistration} objects
     */
    QList<QTKServiceRegistration> getUsedByPlugin(QSharedPointer<QTKPlugin> pPlugin) const;

    void clear();

    mutable QMutex m_mutex;

    /**
     * @brief m_mapServices
     * All registered services in the current framework.
     * Mapping of registered service to class names under which
     * the service is registerd.
     */
    QHash<QTKServiceRegistration, QStringList> m_mapServices;

    /**
     * @brief m_mapClassServices
     * Mapping of classname to registered service.
     * The List of registered services are ordered with the highest
     * ranked service first.
     */
    QHash<QString, QList<QTKServiceRegistration>> m_mapClassServices;
    QTKPluginFrameworkContext *m_pPFWContext;

private:
    QList<QTKServiceReference> getUnlocked(const QString &strClazz,
                                           const QString &strFilter,
                                           QTKPluginPrivate *pPlugin) const;
};

QTK_PLUGINFRAMEWORK_END_NAMESPACE

#endif // QTKSERVICES_P_H
