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

#ifndef QTKTRACKEDSERVICELISTENER_P_H
#define QTKTRACKEDSERVICELISTENER_P_H

#include "qtkpluginframework_global.h"
#include "qtkserviceevent.h"

#include <QObject>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKTrackedServiceListener class
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKTrackedServiceListener : public QObject
{
    Q_OBJECT

public:
    QTKTrackedServiceListener(QObject *pParent = nullptr) : QObject(pParent) {}

public Q_SLOTS:
    /**
     * @brief serviceChanged
     * Slot connected to service events for the
     * <code>ctkServiceTracker</code> class. This method must NOT be
     * synchronized to avoid deadlock potential.
     *
     * @param event <code>ctkServiceEvent</code> object from the framework.
     */
    virtual void serviceChanged(const QTKServiceEvent &event) = 0;
};

QTK_PLUGINFRAMEWORK_END_NAMESPACE

#endif // QTKTRACKEDSERVICELISTENER_P_H
