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

#include "qtklocationmanager_p.h"
#include "qtkpluginframeworkproperties_p.h"
#include "qtkbasiclocation_p.h"
#include "qtkpluginframeworklauncher.h"
#include "qtkpluginconstants.h"

#include <QTKCore/QTKException>

#include <QCoreApplication>
#include <QSettings>
#include <QFileInfo>
#include <QDir>
#include <QUrl>

QTK_CORE_USE_NAMESPACE

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

namespace {

static const char *READONLY_AREASUFFIX = ".readOnly";
// configuration area file/dir names
static const char *CONFIG_FILE = "config.ini";

// Constants for configuration location discovery
static const char *QTK = "qtk";
static const char *PRODUCT_SITE_MARKER = ".qtkproduct";
static const char *PRODUCT_SITE_ID = "id";
static const char *PRODUCT_SITE_VERSION = "version";
static const char *CONFIG_DIR = "configuration";

// Data mode constants for user, configuration and data locations.
static const char *NONE = "@none";
static const char *NODEFAULT = "@noDefault";
static const char *USER_HOME = "@user.home";
static const char *USER_DIR = "@user.dir";
// Placeholder for hashcode of installation directory
static const char *INSTALL_HASH_PLACEHOLDER = "@install.hash";
static const char *INSTANCE_DATA_AREAPREFIX = ".metadata/.plugins/";

static QScopedPointer<QTKBasicLocation> sg_pInstallLocation;
static QScopedPointer<QTKBasicLocation> sg_pConfigurationLocation;
static QScopedPointer<QTKBasicLocation> sg_pUserLocation;
static QScopedPointer<QTKBasicLocation> sg_pInstanceLocation;
static QScopedPointer<QTKBasicLocation> sg_pQTKHomeLocation;

static bool canWrite(const QUrl &location);
static bool canWrite(const QFileInfo &location);
static QString substituteVar(const QString &strSource, const QString &strVar, const QString &strProp);
static QString getInstallDirHash();
static QString computeDefaultUserAreaLocation(const QString &strPathAppendage);

static bool sg_bIsInitialized = false;

static QUrl BuildUrl(const QString &strLocation, bool bTrailingSlash)
{
    QUrl result(strLocation,QUrl::StrictMode);

    if (!result.isValid() || result.scheme().compare("file", Qt::CaseInsensitive) != 0) {
        result = QUrl::fromLocalFile(strLocation);
    }

    bool bIsFile = result.isValid() && result.scheme().compare("file", Qt::CaseInsensitive) == 0;
    if (bIsFile) {
        QString strPath = result.path();
        if (bTrailingSlash == strPath.endsWith('/')) {
            return result;
        }
        strPath = bTrailingSlash ? strPath + '/' : strPath.left(strPath.size()-1);
        result.setPath(strPath);
    }
    return result;
}

static QString ComputeQTKHomeLocation()
{
    // TODO MacOS do we need to walk out of the application bundle?
    return QCoreApplication::applicationDirPath();
}

QTKBasicLocation *BuildLocation(const QString &strProperty, const QUrl &defaultLocation,
                                const QString &strUserDefaultAppendage, bool bReadOnlyDefault,
                                bool bComputeReadOnly, const QString &strDataAreaPrefix)
{
    QString strLocation = QTKPluginFrameworkProperties::clearProperty(strProperty).toString();
    // the user/product may specify a non-default readOnly setting
    QVariant userReadOnlySetting = QTKPluginFrameworkProperties::getProperty(strProperty + QTKLocationManager::getReadOnlyAreaSuffix());
    bool bReadOnly = (userReadOnlySetting.isNull() ? bReadOnlyDefault : userReadOnlySetting.toBool());
    // if the instance location is not set, predict where the workspace will be and
    // put the instance area inside the workspace meta area.
    if (strLocation.isNull()) {
        return new QTKBasicLocation(strProperty, defaultLocation,
                                    !userReadOnlySetting.isNull() || !bComputeReadOnly ? bReadOnly : !canWrite(defaultLocation),
                                    strDataAreaPrefix);
    }
    QString strTrimmedLocation = strLocation.trimmed();
    if (strTrimmedLocation.compare(NONE, Qt::CaseInsensitive) == 0) {
        return nullptr;
    }
    if (strTrimmedLocation.compare(NODEFAULT, Qt::CaseInsensitive) == 0) {
        return new QTKBasicLocation(strProperty, QUrl(), bReadOnly, strDataAreaPrefix);
    }
    if (strTrimmedLocation.startsWith(USER_HOME)) {
        QString strase = substituteVar(strLocation, USER_HOME , QTKPluginFrameworkLauncher::PROPERTIE_USER_HOME);
        strLocation = QFileInfo(QDir(strase), strUserDefaultAppendage).absoluteFilePath();
    } else if (strTrimmedLocation.startsWith(USER_DIR)) {
        QString strBase = substituteVar(strLocation, USER_DIR, QTKPluginFrameworkLauncher::PROPERTIE_USER_DIR);
        strLocation = QFileInfo(QDir(strBase), strUserDefaultAppendage).absoluteFilePath();
    }
    int iIndex = strLocation.indexOf(INSTALL_HASH_PLACEHOLDER);
    if (0 == iIndex) {
        throw QTKRuntimeException("The location cannot start with '" + QLatin1String(INSTALL_HASH_PLACEHOLDER) + "': " + strLocation);
    } else if (iIndex > 0) {
        strLocation = strLocation.left(iIndex) + getInstallDirHash() + strLocation.mid(iIndex + QLatin1String(INSTALL_HASH_PLACEHOLDER).size());
    }
    QUrl url = BuildUrl(strLocation, true);
    QTKBasicLocation *pResult = nullptr;
    if (url.isValid()) {
        pResult = new QTKBasicLocation(strProperty, QUrl(), !userReadOnlySetting.isNull() || !bComputeReadOnly ? bReadOnly : !canWrite(url), strDataAreaPrefix);
        pResult->set(url, false);
    }
    return pResult;
}

static QString substituteVar(const QString &strSource, const QString &strVar, const QString &strProp)
{
    QString strValue = QTKPluginFrameworkProperties::getProperty(strProp).toString();
    return strValue + strSource.mid(strVar.size());
}

static QUrl ComputeInstallConfigurationLocation()
{
    QString strProperty = QTKPluginFrameworkProperties::getProperty(QTKPluginFrameworkLauncher::PROPERTIE_INSTALL_AREA).toString();
    if (!strProperty.isEmpty()) {
        return BuildUrl(strProperty, true);
    }
    return QUrl();
}

static QUrl ComputeSharedConfigurationLocation()
{
    QVariant property = QTKPluginFrameworkProperties::getProperty(QTKPluginFrameworkLauncher::PROPERTIE_SHAREDCONFIGURATION_AREA);
    if (property.isNull()) {
        return QUrl();
    }

    QUrl sharedConfigurationURL = BuildUrl(property.toString(), true);
    if (!sharedConfigurationURL.isValid()) {
        return QUrl();
    }
    if (sharedConfigurationURL.path().startsWith("/")) {
        // absolute
        return sharedConfigurationURL;
    }
    QUrl installURL = sg_pInstallLocation->getUrl();
    if (sharedConfigurationURL.scheme() != installURL.scheme()) {
        // different protocol
        return sharedConfigurationURL;
    }
    QString strSharedConfigPath = QDir::cleanPath(installURL.path() + '/' + sharedConfigurationURL.path());
    sharedConfigurationURL = installURL;
    sharedConfigurationURL.setPath(strSharedConfigPath);
    QTKPluginFrameworkProperties::setProperty(QTKPluginFrameworkLauncher::PROPERTIE_SHAREDCONFIGURATION_AREA, sharedConfigurationURL.toString());
    return QUrl();
}

static QString ComputeDefaultConfigurationLocation()
{
    // 1) We store the config state relative to the 'QTK' directory if possible
    // 2) If this directory is read-only
    //    we store the state in <user.home>/.commontk/<application-id>_<version> where <user.home>
    //    is unique for each local user, and <application-id> is the one
    //    defined in .eclipseproduct marker file. If .eclipseproduct does not
    //    exist, use "eclipse" as the application-id.

    QUrl installURL = ComputeInstallConfigurationLocation();
    if (installURL.isValid() && installURL.scheme() == "file") {
        QDir installDir(installURL.toLocalFile());
        QFileInfo defaultConfigDir(installDir, CONFIG_DIR);
        if (!defaultConfigDir.exists()) {
            installDir.mkpath(defaultConfigDir.absoluteFilePath());
        }
        if (defaultConfigDir.exists() && canWrite(defaultConfigDir)) {
            return defaultConfigDir.absoluteFilePath();
        }
    }
    // We can't write in the QTK install dir so try for some place in the user's home dir
    return computeDefaultUserAreaLocation(CONFIG_DIR);
}

static bool canWrite(const QFileInfo &location)
{
    if (location.isWritable() == false) {
        return false;
    }

    if (!location.isDir()) {
        return false;
    }

    return true;
}

static bool canWrite(const QUrl &location)
{
    if (location.isValid() && location.scheme() == "file") {
        QFileInfo locationDir(location.toLocalFile());
        if (!locationDir.exists()) {
            QDir().mkpath(locationDir.absoluteFilePath());
        }
        if (locationDir.exists() && canWrite(locationDir)) {
            return true;
        }
    }
    return false;
}

static QString computeDefaultUserAreaLocation(const QString &strPathAppendage)
{
    //    we store the state in <user.home>/.commontk/<application-id>_<version> where <user.home>
    //    is unique for each local user, and <application-id> is the one
    //    defined in .commontkproduct marker file. If .commontkproduct does not
    //    exist, use "commontk" as the application-id.
    QString strInstallProperty = QTKPluginFrameworkProperties::getProperty(QTKPluginFrameworkLauncher::PROPERTIE_INSTALL_AREA).toString();
    QUrl installURL = BuildUrl(strInstallProperty, true);
    if (!installURL.isValid()) {
        return QString::null;
    }
    QFileInfo installDir(installURL.toLocalFile());
    QString strInstallDirHash = getInstallDirHash();

    QString strAppName = "." + QLatin1String(QTK);
    QFileInfo QTKProduct(QDir(installDir.absoluteFilePath()), PRODUCT_SITE_MARKER);
    if (QTKProduct.exists()) {
        QSettings props(QTKProduct.absoluteFilePath(), QSettings::IniFormat);

        QString strAppId = props.value(PRODUCT_SITE_ID).toString();
        if (strAppId.trimmed().isEmpty()) {
            strAppId = QTK;
        }
        QString strAppVersion = props.value(PRODUCT_SITE_VERSION).toString();
        if (strAppVersion.trimmed().isEmpty()) {
            strAppVersion = "";
        }
        strAppName += "/" + strAppId + "_" + strAppVersion + "_" + strInstallDirHash;
    } else {
        // add the hash to help prevent collisions
        strAppName += "/" + strInstallDirHash;
    }
    QString strUserHome = QTKPluginFrameworkProperties::getProperty(QTKPluginFrameworkLauncher::PROPERTIE_USER_HOME).toString();
    return QFileInfo(QDir(strUserHome), strAppName + "/" + strPathAppendage).absoluteFilePath();
}

/**
 * @brief getInstallDirHash
 * Return hash code identifying an absolute installation path
 *
 * @return Hash code as String
 */
static QString getInstallDirHash()
{
    // compute an install dir hash to prevent configuration area collisions with other eclipse installs
    QString strInstallProperty = QTKPluginFrameworkProperties::getProperty(QTKPluginFrameworkLauncher::PROPERTIE_INSTALL_AREA).toString();
    QUrl installURL = BuildUrl(strInstallProperty, true);
    if (!installURL.isValid()) {
        return "";
    }
    QFileInfo installDir(installURL.toLocalFile());
    QString strStringToHash = installDir.canonicalFilePath();
    if (strStringToHash.isEmpty()) {
        // fall back to absolute path
        strStringToHash = installDir.absoluteFilePath();
    }
    uint uiashCode = qHash(strStringToHash);
    return QString::number(uiashCode);
}

} // namespace

/**
 * @brief QTKLocationManager::initializeLocations
 */
void QTKLocationManager::initializeLocations()
{
    if (sg_bIsInitialized) {
        return;
    }

    // set the QTK storage area if it exists
    QVariant osgiStorage = QTKPluginFrameworkProperties::getProperty(QTKPluginConstants::FRAMEWORK_STORAGE);
    if (!osgiStorage.isNull()) {
        QTKPluginFrameworkProperties::setProperty(QTKPluginFrameworkLauncher::PROPERTIE_CONFIGURATION_AREA, osgiStorage);
    }
    // do install location initialization first since others may depend on it
    // assumes that the property is already set
    sg_pInstallLocation.reset(BuildLocation(QTKPluginFrameworkLauncher::PROPERTIE_INSTALL_AREA, QUrl(), "", true, false, QString::null));

    // TODO not sure what the data area prefix should be here for the user area
    QScopedPointer<QTKBasicLocation> temp(BuildLocation(QTKPluginFrameworkLauncher::PROPERTIE_USER_AREA_DEFAULT, QUrl(), "", false, false, QString::null));
    QUrl defaultLocation = temp ? temp->getUrl() : QUrl();
    if (!defaultLocation.isValid()) {
        defaultLocation = BuildUrl(QFileInfo(QDir(QTKPluginFrameworkProperties::getProperty(QTKPluginFrameworkLauncher::PROPERTIE_USER_HOME).toString()), "user").absoluteFilePath(), true);
    }
    sg_pUserLocation.reset(BuildLocation(QTKPluginFrameworkLauncher::PROPERTIE_USER_AREA, defaultLocation, "", false, false, QString::null));

    temp.reset(BuildLocation(QTKPluginFrameworkLauncher::PROPERTIE_INSTANCE_AREA_DEFAULT, QUrl(), "", false, false, INSTANCE_DATA_AREAPREFIX));
    defaultLocation = temp ? temp->getUrl() : QUrl();
    if (!defaultLocation.isValid()) {
        defaultLocation = BuildUrl(QFileInfo(QDir(QTKPluginFrameworkProperties::getProperty(QTKPluginFrameworkLauncher::PROPERTIE_USER_DIR).toString()), "workspace").absoluteFilePath(), true);
    }
    sg_pInstanceLocation.reset(BuildLocation(QTKPluginFrameworkLauncher::PROPERTIE_INSTANCE_AREA, defaultLocation, "", false, false, INSTANCE_DATA_AREAPREFIX ));

    // compute a default but it is very unlikely to be used since main will have computed everything
    temp.reset(BuildLocation(QTKPluginFrameworkLauncher::PROPERTIE_CONFIGURATION_AREA_DEFAULT, QUrl(), "", false, false, QString::null));
    defaultLocation = temp ? temp->getUrl() : QUrl();
    if (!defaultLocation.isValid() && QTKPluginFrameworkProperties::getProperty(QTKPluginFrameworkLauncher::PROPERTIE_CONFIGURATION_AREA).isNull()) {
        // only compute the default if the configuration area property is not set
        defaultLocation = BuildUrl(ComputeDefaultConfigurationLocation(), true);
    }
    sg_pConfigurationLocation.reset(BuildLocation(QTKPluginFrameworkLauncher::PROPERTIE_CONFIGURATION_AREA, defaultLocation, "", false, false, QString::null));
    // get the parent location based on the system property. This will have been set on the
    // way in either by the caller/user or by main.  There will be no parent location if we are not
    // cascaded.
    QUrl parentLocation = ComputeSharedConfigurationLocation();
    if (parentLocation.isValid() && parentLocation != sg_pConfigurationLocation->getUrl()) {
        QTKBasicLocation *pParent = new QTKBasicLocation(QString::null, parentLocation, true, QString::null);
        sg_pConfigurationLocation->setParent(pParent);
    }

    if (QTKPluginFrameworkProperties::getProperty(QTKPluginFrameworkLauncher::PROPERTIE_HOME_LOCATION).isNull()) {
        QString strBlueberryHomeLocationPath = ComputeQTKHomeLocation();
        if (!strBlueberryHomeLocationPath.isEmpty()) {
            QTKPluginFrameworkProperties::setProperty(QTKPluginFrameworkLauncher::PROPERTIE_HOME_LOCATION, strBlueberryHomeLocationPath);
        }
    }
    // if QTK.home.location is not set then default to QTK.install.area
    if (QTKPluginFrameworkProperties::getProperty(QTKPluginFrameworkLauncher::PROPERTIE_HOME_LOCATION).isNull() &&
            !QTKPluginFrameworkProperties::getProperty(QTKPluginFrameworkLauncher::PROPERTIE_INSTALL_AREA).isNull()) {
        QTKPluginFrameworkProperties::setProperty(QTKPluginFrameworkLauncher::PROPERTIE_HOME_LOCATION,
                                                  QTKPluginFrameworkProperties::getProperty(QTKPluginFrameworkLauncher::PROPERTIE_INSTALL_AREA));
    }
    sg_pQTKHomeLocation.reset(BuildLocation(QTKPluginFrameworkLauncher::PROPERTIE_HOME_LOCATION, QUrl(), "", true, true, QString::null));

    sg_bIsInitialized = true;
}

QTKBasicLocation *QTKLocationManager::getUserLocation()
{
    return sg_pUserLocation.data();
}

QTKBasicLocation *QTKLocationManager::getConfigurationLocation()
{
    return sg_pConfigurationLocation.data();
}

QTKBasicLocation *QTKLocationManager::getInstallLocation()
{
    return sg_pInstallLocation.data();
}

QTKBasicLocation *QTKLocationManager::getInstanceLocation()
{
    return sg_pInstanceLocation.data();
}

QTKBasicLocation *QTKLocationManager::getQTKHomeLocation()
{
    return sg_pQTKHomeLocation.data();
}

const char *QTKLocationManager::getConfigFileName()
{
    return CONFIG_FILE;
}

const char *QTKLocationManager::getReadOnlyAreaSuffix()
{
    return READONLY_AREASUFFIX;
}

QTK_PLUGINFRAMEWORK_END_NAMESPACE
