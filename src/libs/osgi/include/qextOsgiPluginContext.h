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

#ifndef QTKPLUGINCONTEXT_H
#define QTKPLUGINCONTEXT_H

#include "qtkpluginframework_global.h"
#include "qtkpluginevent.h"
#include "qtkserviceexception.h"
#include "qtkservicereference.h"
#include "qtkserviceregistration.h"

#include <QHash>
#include <QString>
#include <QVariant>
#include <QUrl>
#include <QSharedPointer>
#include <QFileInfo>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

class QTKPlugin;
class QTKPluginPrivate;
class QTKPluginContextPrivate;

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKPluginContext class
 * A plugin's execution context within the Framework. The context is used to
 * grant access to other methods so that this plugin can interact with the
 * Framework.
 *
 * <p>
 * <code>QTKPluginContext</code> methods allow a plugin to:
 * <ul>
 * <li>Subscribe to events published by the Framework.
 * <li>Register service objects with the Framework service registry.
 * <li>Retrieve <code>ServiceReferences</code> from the Framework service
 * registry.
 * <li>Get and release service objects for a referenced service.
 * <li>Install new plugins in the Framework.
 * <li>Get the list of plugins installed in the Framework.
 * <li>Get the {@link QTKPlugin} object for a plugin.
 * <li>Create <code>QFile</code> objects for files in a persistent storage
 * area provided for the plugin by the Framework.
 * </ul>
 *
 * <p>
 * A <code>QTKPluginContext</code> object will be created and provided to the
 * plugin associated with this context when it is started using the
 * {@link QTKPluginActivator::start} method. The same <code>QTKPluginContext</code>
 * object will be passed to the plugin associated with this context when it is
 * stopped using the {@link QTKPluginActivator::stop} method. A
 * <code>QTKPluginContext</code> object is generally for the private use of its
 * associated plugin and is not meant to be shared with other plugins in the
 * plugin environment.
 *
 * <p>
 * The <code>QTKPlugin</code> object associated with a <code>QTKPluginContext</code>
 * object is called the <em>context plugin</em>.
 *
 * <p>
 * The <code>QTKPluginContext</code> object is only valid during the execution of
 * its context plugin; that is, during the period from when the context plugin
 * is in the <code>STARTING</code>, <code>STOPPING</code>, and
 * <code>ACTIVE</code> plugin states. If the <code>QTKPluginContext</code>
 * object is used subsequently, a <code>QTKIllegalStateException</code> must be
 * thrown. The <code>QTKPluginContext</code> object must never be reused after
 * its context plugin is stopped.
 *
 * <p>
 * The Framework is the only entity that can create <code>QTKPluginContext</code>
 * objects and they are only valid within the Framework that created them.
 *
 * @remarks This class is thread safe.
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKPluginContext
{
public:
    ~QTKPluginContext();

    /**
     * @brief getProperty
     * Returns the value of the specified property. If the key is not found in
     * the Framework properties, the system properties are then searched. The
     * method returns an invalid QVariant if the property is not found.
     *
     * @param strkey The name of the requested property.
     * @return The value of the requested property, or an invalid QVariant if
     *         the property is undefined.
     */
    QVariant getProperty(const QString &strkey) const;

    /**
     * @brief getPlugin
     * Returns the <code>QTKPlugin</code> object associated with this
     * <code>QTKPluginContext</code>. This plugin is called the context plugin.
     *
     * @return The <code>QTKPlugin</code> object associated with this
     *         <code>QTKPluginContext</code>.
     * @throws QTKIllegalStateException If this QTKPluginContext is no
     *         longer valid.
     */
    QSharedPointer<QTKPlugin> getPlugin() const;

    /**
     * @brief getPlugin
     * Returns the plugin with the specified identifier.
     *
     * @param lId The identifier of the plugin to retrieve.
     * @return A <code>QTKPlugin</code> object or <code>0</code> if the
     *         identifier does not match any installed plugin.
     */
    QSharedPointer<QTKPlugin> getPlugin(long lId) const;

    /**
     * @brief getPlugins
     * Returns a list of all installed plugins.
     * <p>
     * This method returns a list of all plugins installed in the plugin
     * environment at the time of the call to this method. However, since the
     * Framework is a very dynamic environment, plugins can be installed or
     * uninstalled at anytime.
     *
     * @return A QList of <code>QTKPlugin</code> objects, one object per
     *         installed plugin.
     */
    QList<QSharedPointer<QTKPlugin> > getPlugins() const;

    /**
     * @brief registerService
     * Registers the specified service object with the specified properties
     * under the specified class names into the Framework. A
     * <code>QTKServiceRegistration</code> object is returned. The
     * <code>QTKServiceRegistration</code> object is for the private use of the
     * plugin registering the service and should not be shared with other
     * plugins. The registering plugin is defined to be the context plugin.
     * Other plugins can locate the service by using either the
     * {@link #getServiceReferences} or {@link #getServiceReference} method.
     *
     * <p>
     * A plugin can register a service object that implements the
     * {@link QTKServiceFactory} interface to have more flexibility in providing
     * service objects to other plugins.
     *
     * <p>
     * The following steps are required to register a service:
     * <ol>
     * <li>If <code>service</code> is not a <code>QTKServiceFactory</code>, an
     * <code>QTKInvalidArgumentException</code> is thrown if <code>service</code>
     * is not an instance of all the specified class names.
     * <li>The Framework adds the following service properties to the service
     * properties from the specified <code>QTKDictionary</code> (which may be
     * omitted): <br/>
     * A property named {@link QTKPluginConstants#SERVICE_ID} identifying the
     * registration number of the service <br/>
     * A property named {@link QTKPluginConstants#OBJECTCLASS} containing all the
     * specified classes. <br/>
     * Properties with these names in the specified <code>QTKDictionary</code> will
     * be ignored.
     * <li>The service is added to the Framework service registry and may now be
     * used by other plugins.
     * <li>A service event of type {@link QTKServiceEvent#Type_Registered} is fired.
     * <li>A <code>QTKServiceRegistration</code> object for this registration is
     * returned.
     * </ol>
     *
     * @param listClazzes The class names under which the service can be located.
     *        The class names will be stored in the service's
     *        properties under the key {@link QTKPluginConstants#OBJECTCLASS}.
     * @param pService The service object or a <code>QTKServiceFactory</code>
     *        object.
     * @param properties The properties for this service. The keys in the
     *        properties object must all be <code>QString</code> objects. See
     *        {@link QTKPluginConstants} for a list of standard service property keys.
     *        Changes should not be made to this object after calling this
     *        method. To update the service's properties the
     *        {@link QTKServiceRegistration::setProperties} method must be called.
     *        The set of properties may be omitted if the service has
     *        no properties.
     * @return A <code>QTKServiceRegistration</code> object for use by the plugin
     *         registering the service to update the service's properties or to
     *         unregister the service.
     * @throws QTKInvalidArgumentException If one of the following is true:
     *         <ul>
     *         <li><code>service</code> is <code>0</code>. <li><code>service
     *         </code> is not a <code>QTKServiceFactory</code> object and is not an
     *         instance of all the named classes in <code>clazzes</code>. <li>
     *         <code>properties</code> contains case variants of the same key
     *         name.
     *         </ul>
     * @throws QTKIllegalStateException If this QTKPluginContext is no longer valid.
     * @see QTKServiceRegistration
     * @see QTKServiceFactory
     */
    QTKServiceRegistration registerService(const QStringList &listClazzes, QObject *pService, const QTKDictionary &properties = QTKDictionary());

    /**
     * @brief registerService
     * Registers the specified service object with the specified properties
     * under the specified class name with the Framework.
     *
     * <p>
     * This method is otherwise identical to
     * registerService(const QStringList&, QObject*, const QTKDictionary&) and is provided as
     * a convenience when <code>service</code> will only be registered under a single
     * class name. Note that even in this case the value of the service's
     * QTKPluginConstants::OBJECTCLASS property will be a QStringList, rather
     * than just a single string.
     *
     * @param pClazz The class name under which the service can be located.
     * @param pService The service object or a QTKServiceFactory object.
     * @param properties The properties for this service.
     * @return A QTKServiceRegistration object for use by the plugin
     *         registering the service to update the service's properties or to
     *         unregister the service.
     * @throws QTKIllegalStateException If this QTKPluginContext is no longer valid.
     * @see registerService(const QStringList&, QObject*, const QTKDictionary&)
     */
    QTKServiceRegistration registerService(const char *pClazz, QObject *pService, const QTKDictionary &properties = QTKDictionary());

    template<class S>
    QTKServiceRegistration registerService(QObject *pService, const QTKDictionary &properties = QTKDictionary())
    {
        const char *pClazz = qobject_interface_iid<S*>();
        if (nullptr == pClazz) {
            throw QTKServiceException(QString("The interface class you are registering your service %1 against has no Q_DECLARE_INTERFACE macro")
                                      .arg(pService->metaObject()->className()));
        }
        return this->registerService(pClazz, pService, properties);
    }

    /**
     * @brief getServiceReferences
     * Returns a list of <code>QTKServiceReference</code> objects. The returned
     * list contains services that
     * were registered under the specified class and match the specified filter
     * expression.
     *
     * <p>
     * The list is valid at the time of the call to this method. However since
     * the Framework is a very dynamic environment, services can be modified or
     * unregistered at any time.
     *
     * <p>
     * The specified <code>filter</code> expression is used to select the
     * registered services whose service properties contain keys and values
     * which satisfy the filter expression. See {@link QTKLDAPSearchFilter} for a description
     * of the filter syntax. If the specified <code>filter</code> is
     * empty, all registered services are considered to match the
     * filter. If the specified <code>filter</code> expression cannot be parsed,
     * an <code>QTKInvalidArgumentException</code> will be thrown with a human readable
     * message where the filter became unparsable.
     *
     * <p>
     * The result is a list of <code>QTKServiceReference</code> objects for all
     * services that meet all of the following conditions:
     * <ul>
     * <li>If the specified class name, <code>clazz</code>, is not
     * empty, the service must have been registered with the
     * specified class name. The complete list of class names with which a
     * service was registered is available from the service's
     * {@link QTKPluginConstants::OBJECTCLASS objectClass} property.
     * <li>If the specified <code>filter</code> is not empty, the
     * filter expression must match the service.
     * </ul>
     *
     * @param strClazz The class name with which the service was registered or
     *        an empty string for all services.
     * @param strFilter The filter expression or empty for all
     *        services.
     * @return A list of <code>QTKServiceReference</code> objects or
     *         an empty list if no services are registered which satisfy the
     *         search.
     * @throws QTKInvalidArgumentException If the specified <code>filter</code>
     *         contains an invalid filter expression that cannot be parsed.
     * @throws QTKIllegalStateException If this QTKPluginContext is no longer valid.
     */
    QList<QTKServiceReference> getServiceReferences(const QString &strClazz, const QString &strFilter = QString());

    /**
     * Returns a list of <code>QTKServiceReference</code> objects. The returned
     * list contains services that
     * were registered under the Qt interface id of the template argument <code>S</code>
     * and match the specified filter expression.
     *
     * <p>
     * This method is identical to getServiceReferences(const QString&, const QString&) except that
     * the class name for the service object is automatically deduced from the template argument.
     *
     * @param strFilter The filter expression or empty for all
     *        services.
     * @return A list of <code>QTKServiceReference</code> objects or
     *         an empty list if no services are registered which satisfy the
     *         search.
     * @throws QTKInvalidArgumentException If the specified <code>filter</code>
     *         contains an invalid filter expression that cannot be parsed.
     * @throws QTKIllegalStateException If this QTKPluginContext is no longer valid.
     * @see getServiceReferences(const QString&, const QString&)
     */
    template<class S>
    QList<QTKServiceReference> getServiceReferences(const QString &strFilter = QString())
    {
        const char *pClazz = qobject_interface_iid<S*>();
        if (nullptr == pClazz) {
            throw QTKServiceException("The service interface class has no Q_DECLARE_INTERFACE macro");
        }
        return this->getServiceReferences(QString(pClazz), strFilter);
    }

    /**
     * @brief getServiceReference
     * Returns a <code>QTKServiceReference</code> object for a service that
     * implements and was registered under the specified class.
     *
     * <p>
     * The returned <code>QTKServiceReference</code> object is valid at the time of
     * the call to this method. However as the Framework is a very dynamic
     * environment, services can be modified or unregistered at any time.
     *
     * <p>
     * This method is the same as calling
     * {@link QTKPluginContext::getServiceReferences(const QString&, const QString&)} with an
     * empty filter expression. It is provided as a convenience for
     * when the caller is interested in any service that implements the
     * specified class.
     * <p>
     * If multiple such services exist, the service with the highest ranking (as
     * specified in its {@link QTKPluginConstants::SERVICE_RANKING} property) is returned.
     * <p>
     * If there is a tie in ranking, the service with the lowest service ID (as
     * specified in its {@link QTKPluginConstants::SERVICE_ID} property); that is, the
     * service that was registered first is returned.
     *
     * @param strClazz The class name with which the service was registered.
     * @return A <code>QTKServiceReference</code> object, or <code>0</code> if
     *         no services are registered which implement the named class.
     * @throws QTKIllegalStateException If this QTKPluginContext is no longer valid.
     * @throws QTKServiceException It no service was registered under the given class name.
     * @see #getServiceReferences(const QString&, const QString&)
     */
    QTKServiceReference getServiceReference(const QString &strClazz);

    /**
     * Returns a <code>QTKServiceReference</code> object for a service that
     * implements and was registered under the specified template class argument.
     *
     * <p>
     * This method is identical to getServiceReference(const QString&) except that
     * the class name for the service object is automatically deduced from the template argument.
     *
     * @return A <code>QTKServiceReference</code> object, or <code>0</code> if
     *         no services are registered which implement the named class.
     * @throws QTKIllegalStateException If this QTKPluginContext is no longer valid.
     * @throws QTKServiceException It no service was registered under the given class name.
     * @see #getServiceReference(const QString&)
     * @see #getServiceReferences(const QString&)
     */
    template<class S>
    QTKServiceReference getServiceReference()
    {
        const char *pClazz = qobject_interface_iid<S*>();
        if (nullptr == pClazz) {
            throw QTKServiceException("The service interface class has no Q_DECLARE_INTERFACE macro");
        }
        return this->getServiceReference(QString(pClazz));
    }

    /**
     * @brief getService
     * Returns the service object referenced by the specified
     * <code>QTKServiceReference</code> object.
     * <p>
     * A plugin's use of a service is tracked by the plugin's use count of that
     * service. Each time a service's service object is returned by
     * {@link #getService(const QTKServiceReference&)} the context plugin's use count for
     * that service is incremented by one. Each time the service is released by
     * {@link #ungetService(const QTKServiceReference&)} the context plugin's use count
     * for that service is decremented by one.
     * <p>
     * When a plugin's use count for a service drops to zero, the plugin should
     * no longer use that service.
     *
     * <p>
     * This method will always return <code>0</code> when the service
     * associated with this <code>reference</code> has been unregistered.
     *
     * <p>
     * The following steps are required to get the service object:
     * <ol>
     * <li>If the service has been unregistered, <code>0</code> is returned.
     * <li>The context plugin's use count for this service is incremented by
     * one.
     * <li>If the context plugin's use count for the service is currently one
     * and the service was registered with an object implementing the
     * <code>QTKServiceFactory</code> interface, the
     * {@link QTKServiceFactory::getService} method is
     * called to create a service object for the context plugin. This service
     * object is cached by the Framework. While the context plugin's use count
     * for the service is greater than zero, subsequent calls to get the
     * services's service object for the context plugin will return the cached
     * service object. <br>
     * If the service object returned by the <code>QTKServiceFactory</code> object
     * is not an instance of all the classes named when the service
     * was registered or the <code>QTKServiceFactory</code> object throws an
     * exception, <code>0</code> is returned and a Framework event of type
     * {@link QTKPluginFrameworkEvent::Type_PluginError} containing a {@link QTKServiceException}
     * describing the error is fired.
     * <li>The service object for the service is returned.
     * </ol>
     *
     * @param reference A reference to the service.
     * @return A service object for the service associated with
     *         <code>reference</code> or <code>0</code> if the service is not
     *         registered, the service object returned by a
     *         <code>QTKServiceFactory</code> does not implement the classes under
     *         which it was registered or the <code>QTKServiceFactory</code> threw
     *         an exception.
     * @throws QTKIllegalStateException If this QTKPluginContext is no
     *         longer valid.
     * @throws QTKInvalidArgumentException If the specified
     *         <code>QTKServiceReference</code> was not created by the same
     *         framework instance as this <code>QTKPluginContext</code> or
     *         if it is invalid (default constructed).
     * @see #ungetService(const QTKServiceReference&)
     * @see QTKServiceFactory
     */
    QObject* getService(const QTKServiceReference &reference);

    /**
     * Returns the service object referenced by the specified
     * <code>QTKServiceReference</code> object.
     * <p>
     * This is a convenience method which is identical to QObject* getService(QTKServiceReference)
     * except that it casts the service object to the supplied template argument type
     *
     * @return A service object for the service associated with
     *         <code>reference</code> or <code>0</code> if the service is not
     *         registered, the service object returned by a
     *         <code>QTKServiceFactory</code> does not implement the classes under
     *         which it was registered, the <code>QTKServiceFactory</code> threw
     *         an exception or the service could not be casted to the desired type.
     * @throws QTKIllegalStateException If this QTKPluginContext is no
     *         longer valid.
     * @throws QTKInvalidArgumentException If the specified
     *         <code>QTKServiceReference</code> was not created by the same
     *         framework instance as this <code>QTKPluginContext</code> or
     *         if it is invalid (default constructed).
     * @see #getService(const QTKServiceReference&)
     * @see #ungetService(const QTKServiceReference&)
     * @see QTKServiceFactory
     */
    template<class S>
    S* getService(const QTKServiceReference &reference)
    {
        return qobject_cast<S*>(getService(reference));
    }

    /**
     * @brief ungetService
     * Releases the service object referenced by the specified
     * <code>QTKServiceReference</code> object. If the context plugin's use count
     * for the service is zero, this method returns <code>false</code>.
     * Otherwise, the context plugins's use count for the service is decremented
     * by one.
     *
     * <p>
     * The service's service object should no longer be used and all references
     * to it should be destroyed when a bundle's use count for the service drops
     * to zero.
     *
     * <p>
     * The following steps are required to unget the service object:
     * <ol>
     * <li>If the context plugin's use count for the service is zero or the
     * service has been unregistered, <code>false</code> is returned.
     * <li>The context plugin's use count for this service is decremented by
     * one.
     * <li>If the context plugin's use count for the service is currently zero
     * and the service was registered with a <code>QTKServiceFactory</code> object,
     * the
     * {@link QTKServiceFactory#ungetService}
     * method is called to release the service object for the context plugin.
     * <li><code>true</code> is returned.
     * </ol>
     *
     * @param reference A reference to the service to be released.
     * @return <code>false</code> if the context plugin's use count for the
     *         service is zero or if the service has been unregistered;
     *         <code>true</code> otherwise.
     * @throws QTKIllegalStateException If this QTKPluginContext is no
     *         longer valid.
     * @throws QTKInvalidArgumentException If the specified
     *         <code>QTKServiceReference</code> was not created by the same
     *         framework instance as this <code>QTKPluginContext</code>.
     * @see #getService
     * @see QTKServiceFactory
     */
    bool ungetService(const QTKServiceReference &reference);

    /**
     * @brief getDataFile
     * Creates a <code>QFileInfo</code> object for a file or directoryin the
     * persistent storage area provided for the plugin by the Framework.
     *
     * <p>
     * A <code>QFileInfo</code> object for the base directory of the persistent
     * storage area provided for the context plugin by the Framework can be
     * obtained by calling this method with an empty string as
     * <code>filename</code>.
     *
     * <p>
     * If the permissions are enabled, the Framework will
     * ensure that the plugin has the <code>QTKFilePermission</code> with
     * actions <code>read</code>,<code>write</code>,<code>delete</code>
     * for all files (recursively) in the persistent storage area provided for
     * the context plugin.
     *
     * @param strFilename A relative name to the file or directory to be accessed.
     * @return A <code>QFileInfo</code> object that represents the requested file
     *         or directory.
     * @throws QTKIllegalStateException If this QTKPluginContext is no longer valid.
     */
    QFileInfo getDataFile(const QString &strFilename);

    /**
     * @brief installPlugin
     * Installs a plugin from the specified <code>QIODevice</code> object.
     *
     * <p>
     * If the specified <code>QIODevice</code> is <code>null</code>, the
     * Framework must create the <code>QIODevice</code> from which to read the
     * plugin by interpreting, in an implementation dependent manner, the
     * specified <code>location</code>.
     *
     * <p>
     * The specified <code>location</code> identifier will be used as the
     * identity of the plugin. Every installed plugin is uniquely identified by
     * its location identifier which is typically in the form of a URL.
     *
     * <p>
     * The following steps are required to install a plugin:
     * <ol>
     * <li>If a plugin containing the same location identifier is already
     * installed, the <code>QTKPlugin</code> object for that plugin is returned.
     *
     * <li>The plugin's content is read from the input stream. If this fails, a
     * {@link QTKPluginException} is thrown.
     *
     * <li>The plugin's associated resources are allocated. The associated
     * resources minimally consist of a unique identifier and a persistent
     * storage area. If this step fails, a <code>QTKPluginException</code>
     * is thrown.
     *
     * <li>The plugin's state is set to <code>INSTALLED</code>.
     *
     * <li>A plugin event of type {@link QTKPluginEvent#INSTALLED} is fired.
     *
     * <li>The <code>QTKPlugin</code> object for the newly or previously installed
     * plugin is returned.
     * </ol>
     *
     * <b>Postconditions, no exceptions thrown </b>
     * <ul>
     * <li><code>getState()</code> in &#123; <code>INSTALLED</code>,
     * <code>RESOLVED</code> &#125;.
     * <li>Plugin has a unique ID.
     * </ul>
     * <b>Postconditions, when an exception is thrown </b>
     * <ul>
     * <li>Plugin is not installed and no trace of the plugin exists.
     * </ul>
     *
     * @param location The location identifier of the plugin to install.
     * @param pInput The <code>QIODevice</code> object from which this plugin
     *        will be read or <code>null</code> to indicate the Framework must
     *        create the I/O device from the specified location identifier.
     *        The I/O device must always be closed when this method completes,
     *        even if an exception is thrown.
     * @return The <code>QTKPlugin</code> object of the installed plugin.
     * @throws QTKPluginException If the I/O device cannot be read or the
     *         installation failed.
     * @throws QTKIllegalStateException If this QTKPluginContext is no longer valid.
     */
    QSharedPointer<QTKPlugin> installPlugin(const QUrl &location, QIODevice *pInput = nullptr);

    /**
     * @brief connectPluginListener
     * Connects the specified <code>slot</code> to the context
     * plugins's signal which is emitted when a plugin has
     * a lifecycle state change. The signature of the slot
     * must be "slotName(QTKPluginEvent)".
     *
     * @param pReceiver The object to connect to.
     * @param pSlot The slot to be connected.
     * @param eType The Qt connection type. Only Qt::DirectConnection,
     *        Qt::QueuedConnection, or Qt::BlockingQueuedConnection is allowed.
     * @returns <code>true</code> if the connection was successfull;
     *          <code>false</code> otherwise.
     * @throws QTKIllegalStateException If this QTKPluginContext is no
     *         longer valid.
     * @see QTKPluginEvent
     * @see QTKEventBus
     */
    bool connectPluginListener(const QObject *pReceiver, const char *pSlot, Qt::ConnectionType eType = Qt::QueuedConnection);

    /**
     * @brief disconnectPluginListener
     * Disconnects the specified <code>slot</code> from the context
     * plugin.
     *
     * <p>
     * If <code>slot</code> is not connected to the context plugin,
     * this method does nothing.
     *
     * @param pReceiver The object which has previously connected <code>slot</code>.
     * @param pSlot The Qt slot to be disconnected. If <code>nullptr</code>, all slots
     *        previously connected via connectPluginListener are disconnected.
     * @throws QTKIllegalStateException If this QTKPluginContext is no longer valid.
     */
    void disconnectPluginListener(const QObject *pReceiver, const char *pSlot = nullptr);

    /**
     * @brief connectFrameworkListener
     * Connects the specified <code>slot</code> to the context
     * plugin's signal which emits general Framework events. The signature
     * of the slot must be "slotName(QTKPluginFrameworkEvent)".
     *
     * @param pReceiver The object to connect to.
     * @param pSlot The slot to be connected.
     * @param eType The Qt connection type.
     * @returns <code>true</code> if the connection was successfull;
     *          <code>false</code> otherwise.
     * @throws QTKIllegalStateException If this QTKPluginContext is no
     *         longer valid.
     * @see QTKPluginFrameworkEvent
     * @see QTKEventBus
     */
    bool connectFrameworkListener(const QObject *pReceiver, const char *pSlot, Qt::ConnectionType eType = Qt::QueuedConnection);

    /**
     * @brief disconnectFrameworkListener
     * Disconnects the specified <code>slot</code> from the context
     * plugin.
     *
     * <p>
     * If <code>slot</code> is not connected to the context plugin,
     * this method does nothing.
     *
     * @param pReceiver The object which has previously connected <code>slot</code>.
     * @param pSlot The Qt slot to be disconnected. If <code>nullptr</code>, all slots
     *        previously connected via connectFrameworkListener are disconnected.
     * @throws QTKIllegalStateException If this QTKPluginContext is no longer valid.
     */
    void disconnectFrameworkListener(const QObject *pReceiver, const char *pSlot = nullptr);

    /**
     * @brief connectServiceListener
     * Connects the specified <code>slot</code> with the
     * specified <code>filter</code> to the context plugins's signal emitting
     * service events when a service has a lifecycle state change. The signature
     * of the slot must be "slotName(const QTKServiceEvent&)", but only the name
     * of the slot must be provided as the argument.
     * See {@link QTKLDAPSearchFilter} for a description of
     * the filter syntax.
     *
     * <p>
     * If the object to connect to is destroyed, the slot is automatically
     * disconnected. To explicitly disconnect the slot, use
     * disconnectServiceListener().
     *
     * <p>
     * If the context plugin's list of listeners already contains the same
     * slot for the given receiver, then this
     * method replaces that slot's filter (which may be <code>null</code>)
     * with the specified one (which may be <code>null</code>).
     *
     * <p>
     * The slot is called if the filter criteria is met. To filter based
     * upon the class of the service, the filter should reference the
     * {@link QTKPluginConstants#OBJECTCLASS} property. If <code>filter</code> is
     * <code>null</code>, all services are considered to match the filter.
     *
     * <p>
     * When using a <code>filter</code>, it is possible that the
     * <code>QTKServiceEvent</code>s for the complete lifecycle of a service
     * will not be delivered to the slot. For example, if the
     * <code>filter</code> only matches when the property <code>x</code> has
     * the value <code>1</code>, the listener will not be called if the
     * service is registered with the property <code>x</code> not set to the
     * value <code>1</code>. Subsequently, when the service is modified
     * setting property <code>x</code> to the value <code>1</code>, the
     * filter will match and the slot will be called with a
     * <code>ServiceEvent</code> of type <code>Type_Modified</code>. Thus, the
     * slot will not be called with a <code>ServiceEvent</code> of type
     * <code>Type_Registered</code>.
     *
     * @param pReceiver The object to connect to.
     * @param pSlot The name of the slot to be connected.
     * @param strFilter The filter criteria.
     * @throws QTKInvalidArgumentException If <code>filter</code> contains an
     *         invalid filter string that cannot be parsed.
     * @throws QTKIllegalStateException If this QTKPluginContext is no
     *         longer valid.
     * @see QTKServiceEvent
     * @see disconnectServiceListener()
     * @see QTKEventBus
     */
    void connectServiceListener(QObject *pReceiver, const char *pSlot, const QString &strFilter = QString());

    /**
     * @brief disconnectServiceListener
     * Disconnects a slot which has been previously connected
     * with a call to connectServiceListener().
     *
     * @param pReceiver The object containing the slot.
     * @param pSlot The slot to be disconnected.
     * @see connectServiceListener()
     */
    void disconnectServiceListener(QObject *pReceiver, const char *pSlot);

protected:
    QTKPluginContext(QTKPluginPrivate *pPlugin);

    QTKPluginContextPrivate  *const d_ptr;

private:
    friend class QTKPluginFrameworkPrivate;
    friend class QTKPlugin;
    friend class QTKPluginPrivate;
    Q_DECLARE_PRIVATE(QTKPluginContext)
};

QTK_PLUGINFRAMEWORK_END_NAMESPACE

#endif // QTKPLUGINCONTEXT_H
