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

#ifndef QTKLOCATIONMANAGER_P_H
#define QTKLOCATIONMANAGER_P_H

#include "qtkpluginframework_global.h"

#include <QString>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

class QTKBasicLocation;

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKLocationManager class
 * This class is used to manage the various Locations for BlueBerry.
 * <p>
 * Clients may not extend this class.
 * </p>
 * @note This class is not intended to be subclassed by clients.
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKLocationManager
{
public:
    /**
     * @brief initializeLocations
     * Initializes the QFileInfo objects for the QTKLocationManager.
     */
    static void initializeLocations();

    /**
     * @brief getUserLocation
     * Returns the user QTKLocation object
     * @return The user QTKLocation object
     */
    static QTKBasicLocation *getUserLocation();

    /**
     * @brief getConfigurationLocation
     * Returns the configuration QTKLocation object
     *
     * @return The configuration QTKLocation object
     */
    static QTKBasicLocation *getConfigurationLocation();

    /**
     * @brief getInstallLocation
     * Returns the install QTKLocation object
     *
     * @return The install QTKLocation object
     */
    static QTKBasicLocation *getInstallLocation();

    /**
     * @brief getInstanceLocation
     * Returns the instance QTKLocation object
     *
     * @return The instance QTKLocation object
     */
    static QTKBasicLocation *getInstanceLocation();
    static QTKBasicLocation *getQTKHomeLocation();
    static const char *getConfigFileName();
    static const char *getReadOnlyAreaSuffix();
};

QTK_PLUGINFRAMEWORK_END_NAMESPACE

#endif // QTKLOCATIONMANAGER_P_H
