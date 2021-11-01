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

#ifndef QTKAPPLICATIONHANDLE_H
#define QTKAPPLICATIONHANDLE_H

#include "../../qtkpluginframework_global.h"

#include <QObject>
#include <QString>

class QVariant;

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

struct QTKApplicationDescriptor;

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKApplicationHandle class
 * ApplicationHandle is a service interface which represents an instance
 * of an application. It provides the functionality to query and manipulate the
 * lifecycle state of the represented application instance. It defines constants
 * for the lifecycle states.
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKApplicationHandle
{
public:
    virtual ~QTKApplicationHandle() {}

    virtual QTKApplicationDescriptor* getApplicationDescriptor() const = 0;
    virtual QString getState() const = 0;
    virtual QVariant getExitValue(long timeout) const = 0;
    virtual QString getInstanceId() const = 0;
    virtual void destroy() = 0;

    /**
     * @brief APPLICATION_PID
     * The property key for the unique identifier (PID) of the application
     * instance.
     */
    static const char *APPLICATION_PID; // = QTKPluginConstants::SERVICE_PID;

    /**
     * @brief APPLICATION_DESCRIPTOR
     * The property key for the pid of the corresponding application descriptor.
     */
    static const char *APPLICATION_DESCRIPTOR; // = "application.descriptor";

    /**
     * @brief APPLICATION_STATE
     * The property key for the state of this application instance.
     */
    static const char *APPLICATION_STATE; // = "application.state";

    /**
     * @brief APPLICATION_SUPPORTS_EXITVALUE
     * The property key for the supports exit value property of this application
     * instance.
     */
    static const char *APPLICATION_SUPPORTS_EXITVALUE; // = "application.supports.exitvalue";

    /**
     * @brief RUNNING
     * The application instance is running. This is the initial state of a newly
     * created application instance.
     */
    static const char *RUNNING; // = "RUNNING";

    /**
     * @brief STOPPING
     * The application instance is being stopped. This is the state of the
     * application instance during the execution of the <code>destroy()</code>
     * method.
     */
    static const char *STOPPING; // = "STOPPING";
};

QTK_PLUGINFRAMEWORK_END_NAMESPACE

Q_DECLARE_INTERFACE(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKApplicationHandle,
                    "org.qtk.service.application.ApplicationHandle")

#endif // QTKAPPLICATIONHANDLE_H
