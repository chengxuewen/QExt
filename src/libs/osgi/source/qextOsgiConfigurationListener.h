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


#ifndef _QEXTOSGICONFIGURATIONLISTENER_H
#define _QEXTOSGICONFIGURATIONLISTENER_H

#include <qextOsgiConfigurationEvent.h>

/**
 * \ingroup ConfigAdmin
 *
 * Listener for Configuration Events. When a <code>QExtOsgiConfigurationEvent</code>
 * is fired, it is asynchronously delivered to a
 * <code>QExtOsgiConfigurationListener</code>.
 *
 * <p>
 * <code>QExtOsgiConfigurationListener</code> objects are registered with the
 * Framework service registry and are notified with a
 * <code>QExtOsgiConfigurationEvent</code> object when an event is fired.
 * <p>
 * <code>QExtOsgiConfigurationListener</code> objects can inspect the received
 * <code>QExtOsgiConfigurationEvent</code> object to determine its type, the pid of
 * the <code>QExtOsgiConfiguration</code> object with which it is associated, and the
 * Configuration Admin service that fired the event.
 *
 * <p>
 * Security Considerations. Plugins wishing to monitor configuration events will
 * require <code>QExtOsgiServicePermission[QExtOsgiConfigurationListener,REGISTER]</code> to
 * register a <code>QExtOsgiConfigurationListener</code> service.
 */
struct QExtOsgiConfigurationListener
{
    virtual ~QExtOsgiConfigurationListener() {}

    /**
   * Receives notification of a QExtOsgiConfiguration that has changed.
   *
   * @param event The <code>QExtOsgiConfigurationEvent</code>.
   */
    virtual void configurationEvent(const QExtOsgiConfigurationEvent &event) = 0;
};

Q_DECLARE_INTERFACE(QExtOsgiConfigurationListener, "org.qext.service.cm.ConfigurationListener")

#endif // _QEXTOSGICONFIGURATIONLISTENER_H
