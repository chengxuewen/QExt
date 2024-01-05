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


#ifndef _QEXTOSGISERVICESLOTENTRY_P_H
#define _QEXTOSGISERVICESLOTENTRY_P_H


#include <qextOsgiServiceEvent.h>
#include <private/qextOsgiLDAPExpr_p.h>

#include <QHash>
#include <QList>
#include <QString>
#include <QStringList>
#include <QExplicitlySharedDataPointer>

class QExtOsgiPlugin;
class QExtOsgiServiceSlotEntryData;

class QObject;


/**
 * \ingroup PluginFramework
 *
 * Data structure for saving information about slots registered for
 * receiving service lifecycle events.
 */
class QExtOsgiServiceSlotEntry
{

public:

    QExtOsgiServiceSlotEntry(QSharedPointer<QExtOsgiPlugin> p, QObject* receiver, const char* slot,
                        const QString& filter = QString());

    QExtOsgiServiceSlotEntry(const QExtOsgiServiceSlotEntry& other);

    // default constructor for use in QSet
    QExtOsgiServiceSlotEntry();
    ~QExtOsgiServiceSlotEntry();

    // assignment operator for use in QSet
    QExtOsgiServiceSlotEntry& operator=(const QExtOsgiServiceSlotEntry& other);

    bool operator==(const QExtOsgiServiceSlotEntry& other) const;

    void invokeSlot(const QExtOsgiServiceEvent& event);

    void setRemoved(bool removed);

    bool isRemoved() const;

    QSharedPointer<QExtOsgiPlugin> getPlugin() const;

    QExtOsgiLDAPExpr getLDAPExpr() const;

    QString getFilter() const;

    QExtOsgiLDAPExpr::LocalCache& getLocalCache() const;

private:

    friend uint qHash(const QExtOsgiServiceSlotEntry& serviceSlot);

    QExplicitlySharedDataPointer<QExtOsgiServiceSlotEntryData> d;

};

/**
 * \ingroup PluginFramework
 */
uint qHash(const QExtOsgiServiceSlotEntry& serviceSlot);

#endif // _QEXTOSGISERVICESLOTENTRY_P_H
