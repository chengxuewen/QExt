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

#ifndef _QEXTOSGILOCATIONMANAGER_H
#define _QEXTOSGILOCATIONMANAGER_H

#include <QString>

class QExtOsgiBasicLocation;

/**
 * This class is used to manage the various Locations for BlueBerry.
 * <p>
 * Clients may not extend this class.
 * </p>
 * @noextend This class is not intended to be subclassed by clients.
 */
class QExtOsgiLocationManager
{

public:

    static const QString READ_ONLY_AREA_SUFFIX; // = ".readOnly";

    // configuration area file/dir names
    static const QString CONFIG_FILE; // = "config.ini";
    static const QString QEXT_OSGI_PROPERTIES; // = "qextOsgi.properties";

    /**
   * Initializes the QFileInfo objects for the QExtOsgiLocationManager.
   */
    static void initializeLocations();

    /**
   * Returns the user QExtOsgiLocation object
   * @return the user QExtOsgiLocation object
   */
    static QExtOsgiBasicLocation* getUserLocation();

    /**
   * Returns the configuration QExtOsgiLocation object
   * @return the configuration QExtOsgiLocation object
   */
    static QExtOsgiBasicLocation* getConfigurationLocation();

    /**
   * Returns the install QExtOsgiLocation object
   * @return the install QExtOsgiLocation object
   */
    static QExtOsgiBasicLocation* getInstallLocation();

    /**
   * Returns the instance QExtOsgiLocation object
   * @return the instance QExtOsgiLocation object
   */
    static QExtOsgiBasicLocation* getInstanceLocation();

    static QExtOsgiBasicLocation* getCTKHomeLocation();

};

#endif // _QEXTOSGILOCATIONMANAGER_H
