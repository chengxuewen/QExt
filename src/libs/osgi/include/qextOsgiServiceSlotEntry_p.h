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

#ifndef QTKSERVICESLOTENTRY_P_H
#define QTKSERVICESLOTENTRY_P_H

#include "qtkpluginframework_global.h"
#include "qtkserviceevent.h"
#include "qtkldapexpr_p.h"

#include <QHash>
#include <QList>
#include <QString>
#include <QStringList>
#include <QExplicitlySharedDataPointer>

class QObject;

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

class QTKPlugin;
class QTKServiceSlotEntryData;

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKServiceSlotEntry class
 * Data structure for saving information about slots registered for receiving
 * service lifecycle events.
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKServiceSlotEntry
{
public:
    QTKServiceSlotEntry(QSharedPointer<QTKPlugin> pPlugin, QObject *pSeceiver, const char *pSlot,
                        const QString &strFilter = QString());
    QTKServiceSlotEntry(const QTKServiceSlotEntry &other);
    // default constructor for use in QSet
    QTKServiceSlotEntry();
    ~QTKServiceSlotEntry();

    // assignment operator for use in QSet
    QTKServiceSlotEntry& operator=(const QTKServiceSlotEntry &other);

    bool operator==(const QTKServiceSlotEntry &other) const;

    void invokeSlot(const QTKServiceEvent &event);

    void setRemoved(bool bRemoved);

    bool isRemoved() const;

    QSharedPointer<QTKPlugin> getPlugin() const;

    QTKLDAPExpr getLDAPExpr() const;

    QString getFilter() const;

    QTKLDAPExpr::LocalCache& getLocalCache() const;

private:
    friend uint qHash(const QTKServiceSlotEntry &serviceSlot);

    QExplicitlySharedDataPointer<QTKServiceSlotEntryData> d;
};

uint qHash(const QTKServiceSlotEntry &serviceSlotEntry);

QTK_PLUGINFRAMEWORK_END_NAMESPACE

#endif // QTKSERVICESLOTENTRY_P_H
