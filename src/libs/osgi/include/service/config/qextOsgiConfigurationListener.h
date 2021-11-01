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

#ifndef QTKCONFIGURATIONLISTENER_H
#define QTKCONFIGURATIONLISTENER_H

#include "qtkconfigurationevent.h"
#include "../../qtkpluginframework_global.h"

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKConfigurationListener class
 * Listener for Configuration Events. When a <code>ctkConfigurationEvent</code>
 * is fired, it is asynchronously delivered to a
 * <code>ctkConfigurationListener</code>.
 *
 * <p>
 * <code>ctkConfigurationListener</code> objects are registered with the
 * Framework service registry and are notified with a
 * <code>ctkConfigurationEvent</code> object when an event is fired.
 * <p>
 * <code>ctkConfigurationListener</code> objects can inspect the received
 * <code>ctkConfigurationEvent</code> object to determine its type, the pid of
 * the <code>ctkConfiguration</code> object with which it is associated, and the
 * Configuration Admin service that fired the event.
 *
 * <p>
 * Security Considerations. Plugins wishing to monitor configuration events will
 * require <code>ctkServicePermission[ctkConfigurationListener,REGISTER]</code> to
 * register a <code>ctkConfigurationListener</code> service.
 */
class QTKConfigurationListener
{
public:
    virtual ~QTKConfigurationListener() {}

    /**
     * @brief configurationEvent
     * Receives notification of a ctkConfiguration that has changed.
     *
     * @param event The <code>ctkConfigurationEvent</code>.
     */
    virtual void configurationEvent(const QTKConfigurationEvent &event) = 0;
};

QTK_PLUGINFRAMEWORK_END_NAMESPACE

Q_DECLARE_INTERFACE(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKConfigurationListener,
                    "org.qtk.service.cm.ConfigurationListener")

#endif // QTKCONFIGURATIONLISTENER_H
