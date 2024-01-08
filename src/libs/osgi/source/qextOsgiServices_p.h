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


#ifndef _QEXTOSGISERVICES_P_H
#define _QEXTOSGISERVICES_P_H

#include <private/qextOsgiPlugin_p.h>
#include <qextOsgiServiceRegistration.h>

#include <QHash>
#include <QObject>
#include <QMutex>
#include <QStringList>


/**
 * \ingroup PluginFramework
 *
 * Here we handle all the services that are registered in the framework.
 */
class QExtOsgiServices {

public:

    mutable QMutex mutex;

    /**
   * Creates a new QExtOsgiDictionary object containing <code>in</code>
   * with the keys converted to lower case.
   *
   * @param classes A list of class names which will be added to the
   *        created QExtOsgiDictionary object under the key
   *        PluginConstants::OBJECTCLASS.
   * @param sid A service id which will be used instead of a default one.
   */
    static QExtOsgiDictionary createServiceProperties(const QExtOsgiDictionary &in,
                                                      const QStringList &classes = QStringList(),
                                                      long sid = -1);

    /**
   * All registered services in the current framework.
   * Mapping of registered service to class names under which
   * the service is registered.
   */
    QHash<QExtOsgiServiceRegistration, QStringList> services;

    /**
   * Mapping of classname to registered service.
   * The List of registered services are ordered with the highest
   * ranked service first.
   */
    QHash<QString, QList<QExtOsgiServiceRegistration> > classServices;


    QExtOsgiPluginFrameworkContext* framework;

    QExtOsgiServices(QExtOsgiPluginFrameworkContext* fwCtx);

    ~QExtOsgiServices();

    void clear();

    /**
   * Register a service in the framework wide register.
   *
   * @param plugin The plugin registering the service.
   * @param classes The class names under which the service can be located.
   * @param service The service object.
   * @param properties The properties for this service.
   * @return A QExtOsgiServiceRegistration object.
   * @exception QExtInvalidArgumentException If one of the following is true:
   * <ul>
   * <li>The service object is 0.</li>
   * <li>The service parameter is not a QExtOsgiServiceFactory or an
   * instance of all the named classes in the classes parameter.</li>
   * </ul>
   */
    QExtOsgiServiceRegistration registerService(QExtOsgiPluginPrivate *plugin,
                                           const QStringList &classes,
                                           QObject *service,
                                           const QExtOsgiDictionary &properties);


    /**
   * Service ranking changed, reorder registered services
   * according to ranking.
   *
   * @param serviceRegistration The QExtOsgiServiceRegistrationPrivate object.
   * @param rank New rank of object.
   */
    void updateServiceRegistrationOrder(const QExtOsgiServiceRegistration& sr,
                                        const QStringList &classes);


    /**
   * Checks that a given service object is an instance of the given
   * class name.
   *
   * @param service The service object to check.
   * @param cls     The class name to check for.
   */
    bool checkServiceClass(QObject *service, const QString &cls) const;


    /**
   * Get all services implementing a certain class.
   * Only used internally by the framework.
   *
   * @param clazz The class name of the requested service.
   * @return A sorted list of {@link QExtOsgiServiceRegistrationPrivate} objects.
   */
    QList<QExtOsgiServiceRegistration> get(const QString &clazz) const;


    /**
   * Get a service implementing a certain class.
   *
   * @param plugin The plugin requesting reference
   * @param clazz The class name of the requested service.
   * @return A {@link QExtOsgiServiceReference} object.
   */
    QExtOsgiServiceReference get(QExtOsgiPluginPrivate *plugin, const QString &clazz) const;


    /**
   * Get all services implementing a certain class and then
   * filter these with a property filter.
   *
   * @param clazz The class name of requested service.
   * @param filter The property filter.
   * @param plugin The plugin requesting reference.
   * @return A list of {@link QExtOsgiServiceReference} object.
   */
    QList<QExtOsgiServiceReference> get(const QString &clazz, const QString &filter,
                                   QExtOsgiPluginPrivate *plugin) const;


    /**
   * Remove a registered service.
   *
   * @param sr The QExtOsgiServiceRegistration object that is registered.
   */
    void removeServiceRegistration(const QExtOsgiServiceRegistration& sr) ;


    /**
   * Get all services that a plugin has registered.
   *
   * @param p The plugin
   * @return A set of {@link QExtOsgiServiceRegistration} objects
   */
    QList<QExtOsgiServiceRegistration> getRegisteredByPlugin(QExtOsgiPluginPrivate *p) const;


    /**
   * Get all services that a plugin uses.
   *
   * @param p The plugin
   * @return A set of {@link QExtOsgiServiceRegistration} objects
   */
    QList<QExtOsgiServiceRegistration> getUsedByPlugin(QSharedPointer<QExtOsgiPlugin> p) const;

private:

    QList<QExtOsgiServiceReference> get_unlocked(const QString &clazz, const QString &filter,
                                            QExtOsgiPluginPrivate *plugin) const;

};



#endif // _QEXTOSGISERVICES_P_H
