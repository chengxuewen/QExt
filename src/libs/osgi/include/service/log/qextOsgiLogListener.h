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

#ifndef QTKLOGLISTENER_H
#define QTKLOGLISTENER_H

#include "../../qtkpluginframework_global.h"
#include "qtklogentry.h"

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKLogListener class
 * Subscribes to <code>ctkLogEntry</code> objects from the <code>ctkLogReaderService</code>.
 *
 * <p>
 * <code>ctkLogListener</code> objects may be registered with the Framework service
 * registry. After the listener is registered, the <code>logged(ctkLogEntryPtr)</code>
 * method will be called for each <code>ctkLogEntry</code> object created.
 *
 * <p>
 * Qt slots can also be used to be notified about new <code>ctkLogEntry</code>
 * objects. See <code>ctkLogReaderService#connectLogListener()</code>.
 *
 * @remarks This class is thread safe.
 * @see ctkLogReaderService
 * @see ctkLogEntry
 * @see ctkLogReaderService#connectLogListener()
 * @see ctkLogReaderService#disconnectLogListener()
 */
class QTKLogListener
{
public:
    virtual ~QTKLogListener() {}

    /**
     * @brief logged
     * Listener method called for each ctkLogEntry object created.
     *
     * <p>
     * As with all event listeners, this method should return to its caller as
     * soon as possible.
     *
     * @param entry A <code>ctkLogEntry</code> object containing log information.
     * @see ctkLogEntry
     */
    virtual void logged(QTKLogEntryPtr entry) = 0;
};

QTK_PLUGINFRAMEWORK_END_NAMESPACE

Q_DECLARE_INTERFACE(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKLogListener,
                    "org.qtk.service.log.LogListener")

#endif // QTKLOGLISTENER_H
