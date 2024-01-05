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

#include <qext/osgi/service/datalocation/qextOsgiLocation.h>

const QString QExtOsgiLocation::INSTANCE_FILTER = QString("(&(objectClass=") +
                                                  qobject_interface_iid<QExtOsgiLocation*>() +
                                                  ")(type=qext.instance.area))";

const QString QExtOsgiLocation::INSTALL_FILTER = QString("(&(objectClass=") +
                                                 qobject_interface_iid<QExtOsgiLocation*>() +
                                                 ")(type=qext.install.area))";

const QString QExtOsgiLocation::CONFIGURATION_FILTER = QString("(&(objectClass=") +
                                                       qobject_interface_iid<QExtOsgiLocation*>() +
                                                       ")(type=qext.configuration.area))";

const QString QExtOsgiLocation::USER_FILTER = QString("(&(objectClass=") +
                                              qobject_interface_iid<QExtOsgiLocation*>() +
                                              ")(type=qext.user.area))";

const QString QExtOsgiLocation::QEXT_OSGI_HOME_FILTER = QString("(&(objectClass=") +
                                                  qobject_interface_iid<QExtOsgiLocation*>() +
                                                  ")(type=qext.home.location))";
