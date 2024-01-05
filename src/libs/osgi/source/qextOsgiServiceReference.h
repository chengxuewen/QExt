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

#ifndef _QEXTOSGISERVICEREFERENCE_H
#define _QEXTOSGISERVICEREFERENCE_H


#include <qextOsgiPlugin.h>
#include <qextOsgiGlobal.h>


#include <QVariant>
#include <QMetaType>

class QExtOsgiServiceRegistrationPrivate;
class QExtOsgiServiceReferencePrivate;
class QExtOsgiServiceEvent;

/**
 * \ingroup PluginFramework
 *
 * A reference to a service.
 *
 * <p>
 * The Framework returns <code>QExtOsgiServiceReference</code> objects from the
 * <code>QExtOsgiPluginContext::getServiceReference</code> and
 * <code>QExtOsgiPluginContext::getServiceReferences</code> methods.
 * <p>
 * A <code>QExtOsgiServiceReference</code> object may be shared between plugins and
 * can be used to examine the properties of the service and to get the service
 * object.
 * <p>
 * Every service registered in the Framework has a unique
 * <code>QExtOsgiServiceRegistration</code> object and may have multiple, distinct
 * <code>QExtOsgiServiceReference</code> objects referring to it.
 * <code>QExtOsgiServiceReference</code> objects associated with a
 * <code>QExtOsgiServiceRegistration</code> are considered equal
 * (more specifically, their <code>operator==()</code>
 * method will return <code>true</code> when compared).
 * <p>
 * If the same service object is registered multiple times,
 * <code>QExtOsgiServiceReference</code> objects associated with different
 * <code>QExtOsgiServiceRegistration</code> objects are not equal.
 *
 * @see QExtOsgiPluginContext::getServiceReference
 * @see QExtOsgiPluginContext::getServiceReferences
 * @see QExtOsgiPluginContext::getService
 * @remarks This class is thread safe.
 */
class QEXT_OSGI_API QExtOsgiServiceReference {

public:

    /**
   * Creates an invalid QExtOsgiServiceReference object. You can use
   * this object in boolean expressions and it will evaluate to
   * <code>false</code>.
   */
    QExtOsgiServiceReference();

    QExtOsgiServiceReference(const QExtOsgiServiceReference& ref);

    /**
   * Converts this QExtOsgiServiceReference instance into a boolean
   * expression. If this instance was default constructed or
   * the service it references has been unregistered, the conversion
   * returns <code>false</code>, otherwise it returns <code>true</code>.
   */
    operator bool() const;

    /**
   * Releases any resources held or locked by this
   * <code>QExtOsgiServiceReference</code> and renders it invalid.
   */
    QExtOsgiServiceReference& operator=(int null);

    ~QExtOsgiServiceReference();

    /**
   * Returns the property value to which the specified property key is mapped
   * in the properties <code>QExtOsgiDictionary</code> object of the service
   * referenced by this <code>QExtOsgiServiceReference</code> object.
   *
   * <p>
   * Property keys are case-insensitive.
   *
   * <p>
   * This method must continue to return property values after the service has
   * been unregistered. This is so references to unregistered services can
   * still be interrogated.
   *
   * @param key The property key.
   * @return The property value to which the key is mapped; an invalid QVariant
   *         if there is no property named after the key.
   */
    QVariant getProperty(const QString& key) const;

    /**
   * Returns a list of the keys in the <code>QExtOsgiDictionary</code>
   * object of the service referenced by this <code>QExtOsgiServiceReference</code>
   * object.
   *
   * <p>
   * This method will continue to return the keys after the service has been
   * unregistered. This is so references to unregistered services can
   * still be interrogated.
   *
   * <p>
   * This method is not <i>case-preserving</i>; this means that every key in the
   * returned array is in lower case, which may not be the case for the corresponding key in the
   * properties <code>QExtOsgiDictionary</code> that was passed to the
   * {@link QExtOsgiPluginContext::registerService(const QStringList&, QObject*, const QExtOsgiDictionary&)} or
   * {@link QExtOsgiServiceRegistration::setProperties} methods.
   *
   * @return A list of property keys.
   */
    QStringList getPropertyKeys() const;

    /**
   * Returns the plugin that registered the service referenced by this
   * <code>QExtOsgiServiceReference</code> object.
   *
   * <p>
   * This method must return <code>0</code> when the service has been
   * unregistered. This can be used to determine if the service has been
   * unregistered.
   *
   * @return The plugin that registered the service referenced by this
   *         <code>QExtOsgiServiceReference</code> object; <code>0</code> if that
   *         service has already been unregistered.
   * @see QExtOsgiPluginContext::registerService(const QStringList&, QObject* , const QExtOsgiDictionary&)
   */
    QSharedPointer<QExtOsgiPlugin> getPlugin() const;

    /**
   * Returns the plugins that are using the service referenced by this
   * <code>QExtOsgiServiceReference</code> object. Specifically, this method returns
   * the plugins whose usage count for that service is greater than zero.
   *
   * @return A list of plugins whose usage count for the service referenced
   *         by this <code>QExtOsgiServiceReference</code> object is greater than
   *         zero.
   */
    QList<QSharedPointer<QExtOsgiPlugin> > getUsingPlugins() const;

    /**
   * Compares this <code>QExtOsgiServiceReference</code> with the specified
   * <code>QExtOsgiServiceReference</code> for order.
   *
   * <p>
   * If this <code>QExtOsgiServiceReference</code> and the specified
   * <code>QExtOsgiServiceReference</code> have the same {@link QExtOsgiPluginConstants::SERVICE_ID
   * service id} they are equal. This <code>QExtOsgiServiceReference</code> is less
   * than the specified <code>QExtOsgiServiceReference</code> if it has a lower
   * {@link QExtOsgiPluginConstants::SERVICE_RANKING service ranking} and greater if it has a
   * higher service ranking. Otherwise, if this <code>QExtOsgiServiceReference</code>
   * and the specified <code>QExtOsgiServiceReference</code> have the same
   * {@link QExtOsgiPluginConstants::SERVICE_RANKING service ranking}, this
   * <code>QExtOsgiServiceReference</code> is less than the specified
   * <code>QExtOsgiServiceReference</code> if it has a higher
   * {@link QExtOsgiPluginConstants::SERVICE_ID service id} and greater if it has a lower
   * service id.
   *
   * @param reference The <code>QExtOsgiServiceReference</code> to be compared.
   * @return Returns a false or true if this
   *         <code>QExtOsgiServiceReference</code> is less than or greater
   *         than the specified <code>QExtOsgiServiceReference</code>.
   * @throws QExtInvalidArgumentException If the specified
   *         <code>QExtOsgiServiceReference</code> was not created by the same
   *         framework instance as this <code>QExtOsgiServiceReference</code>.
   */
    bool operator<(const QExtOsgiServiceReference& reference) const;

    bool operator==(const QExtOsgiServiceReference& reference) const;

    QExtOsgiServiceReference& operator=(const QExtOsgiServiceReference& reference);


protected:

    friend class QExtOsgiLDAPSearchFilter;
    friend class QExtOsgiServiceRegistrationPrivate;
    friend class QExtOsgiPluginContext;
    friend class QExtOsgiPluginPrivate;
    friend class QExtOsgiPluginFrameworkListeners;
    template<class S, class T> friend class QExtOsgiServiceTracker;
    template<class S, class T> friend class QExtOsgiServiceTrackerPrivate;
    template<class S, class R, class T> friend class QExtOsgiPluginAbstractTracked;

    friend QEXT_OSGI_API uint qHash(const QExtOsgiServiceReference&);

    QExtOsgiServiceReference(QExtOsgiServiceRegistrationPrivate* reg);

    QExtOsgiServiceReferencePrivate * d_ptr;

private:
    Q_DECLARE_PRIVATE(QExtOsgiServiceReference)
};

/**
 * \ingroup PluginFramework
 * @{
 */
QEXT_OSGI_API uint qHash(const QExtOsgiServiceReference& serviceRef);
QEXT_OSGI_API QDebug operator<<(QDebug dbg, const QExtOsgiServiceReference& serviceRef);
/** @}*/

Q_DECLARE_METATYPE(QExtOsgiServiceReference)


#endif // _QEXTOSGISERVICEREFERENCE_H
