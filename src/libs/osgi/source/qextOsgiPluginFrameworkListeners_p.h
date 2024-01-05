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

#ifndef _QEXTOSGIPLUGINFRAMEWORKLISTENERS_H
#define _QEXTOSGIPLUGINFRAMEWORKLISTENERS_H

#include <qextOsgiPluginEvent.h>
#include <qextOsgiServiceEvent.h>
#include <qextOsgiServiceReference.h>
#include <qextOsgiPluginFrameworkEvent.h>
#include <private/qextOsgiServiceSlotEntry_p.h>

#include <QObject>
#include <QHash>
#include <QSet>
#include <QMutex>

/**
 * \ingroup PluginFramework
 */
class QExtOsgiPluginFrameworkListeners : public QObject
{

    Q_OBJECT

public:

    QExtOsgiPluginFrameworkListeners(QExtOsgiPluginFrameworkContext* pluginFw);

    /**
   * Add a slot receiving service envents with filter to the current framework.
   * If no filter is wanted, call with a null filter.
   *
   * @param plugin Who wants to add the slot.
   * @param listener Object to add.
   * @param filter LDAP String used for filtering event before calling listener.
   */
    void addServiceSlot(QSharedPointer<QExtOsgiPlugin> plugin, QObject* receiver,
                        const char* slot, const QString& filter);

    /**
   * Remove a slot connected to service events.
   *
   * @param plugin The plugin removing this listener.
   * @param receiver The receiver containing the slot.
   * @param slot The slot in the receiver.
   */
    void removeServiceSlot(QSharedPointer<QExtOsgiPlugin> plugin, QObject* receiver,
                           const char* slot);

    /**
   * Gets the slots interested in modifications of the service reference
   *
   * @param sr The reference related to the event describing the service modification.
   * @param lockProps If access to the properties of the service object referenced by sr
   *        should be synchronized.
   * @return A set of listeners to notify.
   */
    QSet<QExtOsgiServiceSlotEntry> getMatchingServiceSlots(const QExtOsgiServiceReference& sr, bool lockProps = true);

    /**
   * Convenience method for throwing framework error event.
   *
   * @param p Plugin which caused the error.
   * @param e The exception.
   */
    void frameworkError(QSharedPointer<QExtOsgiPlugin> p, const QExtException& e);

    /**
   * Receive notification that a service has had a change occur in its lifecycle.
   */
    void serviceChanged(const QSet<QExtOsgiServiceSlotEntry>& receivers,
                        const QExtOsgiServiceEvent& evt,
                        QSet<QExtOsgiServiceSlotEntry>& matchBefore);

    void serviceChanged(const QSet<QExtOsgiServiceSlotEntry>& receivers,
                        const QExtOsgiServiceEvent& evt);

    void emitPluginChanged(const QExtOsgiPluginEvent& event);

    void emitFrameworkEvent(const QExtOsgiPluginFrameworkEvent& event);

Q_SIGNALS:

    void pluginChangedDirect(const QExtOsgiPluginEvent& event);
    void pluginChangedQueued(const QExtOsgiPluginEvent& event);

    void frameworkEvent(const QExtOsgiPluginFrameworkEvent& event);

private Q_SLOTS:

    void serviceListenerDestroyed(QObject* listener);

private:

    QMutex mutex;

    QList<QString> hashedServiceKeys;
    static const int OBJECTCLASS_IX; // = 0;
    static const int SERVICE_ID_IX; // = 1;
    static const int SERVICE_PID_IX; // = 2;

    // Service listeners with complicated or empty filters
    QList<QExtOsgiServiceSlotEntry> complicatedListeners;

    // Service listeners with "simple" filters are cached
    QList<QHash<QString, QList<QExtOsgiServiceSlotEntry> > > cache;

    QSet<QExtOsgiServiceSlotEntry> serviceSet;

    QExtOsgiPluginFrameworkContext* pluginFw;

    /**
   * Remove all references to a service slot from the service listener
   * cache.
   */
    void removeFromCache(const QExtOsgiServiceSlotEntry& sse);

    /**
   * Checks if the specified service slot's filter is simple enough
   * to cache.
   */
    void checkSimple(const QExtOsgiServiceSlotEntry& sse);

    /**
   * Add all members of the specified list to the specified set.
   */
    void addToSet(QSet<QExtOsgiServiceSlotEntry>& set, int cache_ix, const QString& val);

    /**
   * The unsynchronized version of removeServiceSlot().
   */
    void removeServiceSlot_unlocked(QSharedPointer<QExtOsgiPlugin> plugin, QObject* receiver,
                                    const char* slot);
};


#endif // _QEXTOSGIPLUGINFRAMEWORKLISTENERS_H
