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

#ifndef QTKTRACKEDPLUGINLISTENER_P_H
#define QTKTRACKEDPLUGINLISTENER_P_H

#include "qtkpluginframework_global.h"
#include "qtkpluginevent.h"

#include <QObject>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKTrackedPluginListener class
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKTrackedPluginListener : public QObject
{
    Q_OBJECT
public:
    QTKTrackedPluginListener(QObject *pParent = nullptr) : QObject(pParent) {}

public Q_SLOTS:
    /**
     * @brief pluginChanged
     * Slot for the <code>ctkPluginTracker</code>
     * class. This method must NOT be synchronized to avoid deadlock
     * potential.
     *
     * @param event <code>ctkPluginEvent</code> object from the framework.
     */
    virtual void pluginChanged(const QTKPluginEvent &event) = 0;
};

QTK_PLUGINFRAMEWORK_END_NAMESPACE

#endif // QTKTRACKEDPLUGINLISTENER_P_H
