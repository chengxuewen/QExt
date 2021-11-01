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

#ifndef QTKAPPLICATIONDESCRIPTOR_H
#define QTKAPPLICATIONDESCRIPTOR_H

#include "../../qtkpluginframework_global.h"

#include <QHash>
#include <QVariant>
#include <QString>
#include <QLocale>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

struct QTKApplicationHandle;

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKApplicationDescriptor class
 * A service that represents an installed application and stores
 * information about it. The application descriptor can be used for instance
 * creation.
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKApplicationDescriptor
{
public:
    virtual ~QTKApplicationDescriptor() {}

    /**
     * @brief getApplicationId
     * Returns the identifier of the represented application.
     *
     * @return the identifier of the represented application
     */
    virtual QString getApplicationId() const = 0;

    /**
     * @brief getProperties
     * Returns the properties of the application descriptor as key-value pairs.
     * The return value contains the locale aware and unaware properties as
     * well. The returned <code>QHash</code> will include the service
     * properties of this <code>ctkApplicationDescriptor</code> as well.
     * <p>
     * The returned <code>QHash</code> will contain the standard CTK service
     * properties as well
     * (e.g. service.id, service.vendor etc.) and specialized application
     * descriptors may offer further service properties. The returned Map contains
     * a snapshot of the properties. It will not reflect further changes in the
     * property values nor will the update of the Map change the corresponding
     * service property.
     *
     * @param locale The locale, defaults to the default constructed <code>QLocale()</code>.
     *
     * @return copy of the service properties of this application descriptor service,
     *         according to the specified locale.
     *
     * @throws ctkIllegalStateException
     *             if the application descriptor is unregistered
     */
    virtual QTKProperties getProperties(const QLocale &locale) const = 0;

    /**
     * @brief getProperties
     * Returns the properties of the application descriptor as key-value pairs.
     * The return value contains the raw (non-localized) property values.
     * The returned <code>QHash</code> will include the service
     * properties of this <code>ctkApplicationDescriptor</code> as well.
     * <p>
     * The returned <code>QHash</code> will contain the standard CTK service
     * properties as well
     * (e.g. service.id, service.vendor etc.) and specialized application
     * descriptors may offer further service properties. The returned QHash contains
     * a snapshot of the properties. It will not reflect further changes in the
     * property values nor will the update of the Map change the corresponding
     * service property.
     *
     * @return copy of the non-localized service properties of this application
     *         descriptor service.
     *
     * @throws ctkIllegalStateException
     *             if the application descriptor is unregistered
     */
    virtual QTKProperties getProperties() const = 0;

    /**
     * @brief launch
     * Launches a new instance of an application. The <code>arguments</code> parameter
     * specifies the startup parameters for the instance to be launched, it may
     * be empty.
     * <p>
     * The following steps are made:
     * <ul>
     * <li>Check the locking state of the application. If locked then throw an
     * {@link ctkApplicationException} with the reason code
     * {@link ctkApplicationException#APPLICATION_LOCKED}.
     * <li>Create and start an application instance.
     * <li>Returns the <code>ctkApplicationHandle</code>.
     * </ul>
     * <p>
     * The <code>QHash</code> argument of the launch method contains startup arguments
     * for the application. The keys used in the QHash must be non-empty
     * <code>QString</code> objects. They can be standard or application specific.
     * CTK defines the <code>org.commontk.triggeringevent</code> key to be used to pass
     * the triggering event to a scheduled application, however in the future it
     * is possible that other well-known keys will be defined. To avoid unwanted
     * clashes of keys, the following rules should be applied:
     * <ul>
     * <li>The keys starting with the dash (-) character are application
     * specific, no well-known meaning should be associated with them.</li>
     * <li>Well-known keys should follow the reverse domain name based naming.
     * In particular, the keys standardized in CTK should start with
     * <code>org.commontk.</code>.</li>
     * </ul>
     * <P>
     * The method is synchronous, it returns only when the application instance
     * was successfully started or the attempt to start it failed.
     * <P>
     * This method never returns <code>null</code>. If launching an application
     * fails, the appropriate exception is thrown.
     *
     * @param arguments Arguments for the newly launched application, may be
     *        null
     *
     * @return the registered ctkApplicationHandle, which represents the newly
     *         launched application instance. Never returns <code>null</code>.
     *
     * @throws ctkApplicationException if starting the application failed
     * @throws ctkIllegalStateException if the application descriptor is
     *         unregistered
     * @throws std::invalid_argument if the specified <code>QHash</code> contains
     *         invalid keys (empty <code>QString</code>)
     */
    virtual QTKApplicationHandle* launch(const QHash<QString, QVariant>  &arguments) = 0;

    /**
     * @brief APPLICATION_NAME
     * The property key for the localized name of the application.
     */
    static const char *APPLICATION_NAME; // = "application.name";

    /**
     * @brief APPLICATION_ICON
     * The property key for the localized icon of the application.
     */
    static const char *APPLICATION_ICON; // = "application.icon";

    /**
     * @brief APPLICATION_PID
     * The property key for the unique identifier (PID) of the application.
     */
    static const char *APPLICATION_PID; // = QTKPluginConstants::SERVICE_PID;

    /**
     * @brief APPLICATION_VERSIO
     * The property key for the version of the application.
     */
    static const char *APPLICATION_VERSION; // = "application.version";

    /**
     * @brief APPLICATION_VENDOR
     * The property key for the name of the application vendor.
     */
    static const char *APPLICATION_VENDOR; // = QTKPluginConstants::SERVICE_VENDOR;

    /**
     * @brief APPLICATION_VISIBLE
     * The property key for the visibility property of the application.
     */
    static const char *APPLICATION_VISIBLE; // = "application.visible";

    /**
     * @brief APPLICATION_LAUNCHABLE
     * The property key for the launchable property of the application.
     */
    static const char *APPLICATION_LAUNCHABLE; // = "application.launchable";

    /**
     * @brief APPLICATION_LOCKED
     * The property key for the locked property of the application.
     */
    static const char *APPLICATION_LOCKED; // = "application.locked";

    /**
     * @brief APPLICATION_DESCRIPTION
     * The property key for the localized description of the application.
     */
    static const char *APPLICATION_DESCRIPTION; // = "application.description";

    /**
     * @brief APPLICATION_DOCUMENTATION
     * The property key for the localized documentation of the application.
     */
    static const char *APPLICATION_DOCUMENTATION; // = "application.documentation";

    /**
     * @brief APPLICATION_COPYRIGHT
     * The property key for the localized copyright notice of the application.
     */
    static const char *APPLICATION_COPYRIGHT; // = "application.copyright";

    /**
     * @brief APPLICATION_LICENSE
     * The property key for the localized license of the application.
     */
    static const char *APPLICATION_LICENSE; // = "application.license";

    /**
     * @brief APPLICATION_CONTAINER
     * The property key for the application container of the application.
     */
    static const char *APPLICATION_CONTAINER; // = "application.container";

    /**
     * @brief APPLICATION_LOCATION
     * The property key for the location of the application.
     */
    static const char *APPLICATION_LOCATION; // = "application.location";
};

QTK_PLUGINFRAMEWORK_END_NAMESPACE

Q_DECLARE_INTERFACE(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKApplicationDescriptor,
                    "org.qtk.service.application.ApplicationDescriptor")

#endif // QTKAPPLICATIONDESCRIPTOR_H
