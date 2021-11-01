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

#ifndef QTKPLUGINFRAMEWORKLISTENERS_P_H
#define QTKPLUGINFRAMEWORKLISTENERS_P_H

#include "qtkpluginevent.h"
#include "qtkpluginframeworkevent.h"
#include "qtkservicereference.h"
#include "qtkserviceslotentry_p.h"
#include "qtkserviceevent.h"

#include <QObject>
#include <QHash>
#include <QSet>
#include <QMutex>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKPluginFrameworkListeners class
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKPluginFrameworkListeners : public QObject
{
    Q_OBJECT

public:
    QTKPluginFrameworkListeners(QTKPluginFrameworkContext *pPFWContext);

    /**
     * @brief addServiceSlot
     * Add a slot receiving service envents with filter to the current framework.
     * If no filter is wanted, call with a null filter.
     *
     * @param pPlugin Who wants to add the slot.
     * @param pReceiver Object to add.
     * @param strFilter LDAP String used for filtering event before calling listener.
     */
    void addServiceSlot(QSharedPointer<QTKPlugin> pPlugin, QObject *pReceiver,
                        const char *pSlot, const QString &strFilter);

    /**
     * @brief removeServiceSlot
     * Remove a slot connected to service events.
     *
     * @param pPlugin The plugin removing this listener.
     * @param pReceiver The receiver containing the slot.
     * @param pSlot The slot in the receiver.
     */
    void removeServiceSlot(QSharedPointer<QTKPlugin> pPlugin, QObject *pReceiver, const char *pSlot);

    /**
     * @brief getMatchingServiceSlots
     * Gets the slots interested in modifications of the service reference
     *
     * @param serviceRef The reference related to the event describing the service modification.
     * @param bLockProps If access to the properties of the service object referenced by sr
     *        should be synchronized.
     * @return A set of listeners to notify.
     */
    QSet<QTKServiceSlotEntry> getMatchingServiceSlots(const QTKServiceReference &serviceRef, bool bLockProps = true);

    /**
     * @brief frameworkError
     * Convenience method for throwing framework error event.
     *
     * @param pPlugin Plugin which caused the error.
     * @param exception The exception.
     */
    void frameworkError(QSharedPointer<QTKPlugin> pPlugin, const QTKException &exception);

    /**
     * @brief serviceChanged
     * Receive notification that a service has had a change occur in its lifecycle.
     *
     * @param receivers
     * @param event
     * @param matchBefore
     */
    void serviceChanged(const QSet<QTKServiceSlotEntry> &receivers, const QTKServiceEvent &event,
                        QSet<QTKServiceSlotEntry> &matchBefore);
    void serviceChanged(const QSet<QTKServiceSlotEntry> &receivers, const QTKServiceEvent &event);
    void emitPluginChanged(const QTKPluginEvent &event);
    void emitFrameworkEvent(const QTKPluginFrameworkEvent &event);

Q_SIGNALS:
    void pluginChangedDirect(const QTKPluginEvent &event);
    void pluginChangedQueued(const QTKPluginEvent &event);
    void frameworkEvent(const QTKPluginFrameworkEvent &event);

private Q_SLOTS:
    void serviceListenerDestroyed(QObject *pListener);

private:
    void removeFromCache(const QTKServiceSlotEntry &serviceSlotEntry);
    void checkSimple(const QTKServiceSlotEntry &serviceSlotEntry);
    void addToSet(QSet<QTKServiceSlotEntry> &serviceSlotEntry, int iCacheIndex, const QString &strVal);
    void removeServiceSlot_unlocked(QSharedPointer<QTKPlugin> pPlugin, QObject *pReceiver, const char *pSlot);

    static const int sm_iObjectClassIx; // = 0;
    static const int sm_iServiceIdIx; // = 1;
    static const int sm_iServicePidIx; // = 2;

    QMutex m_mutex;
    QList<QString> m_listHashedServiceKeys;

    /**
     * @brief m_listComplicatedListeners
     * Service listeners with complicated or empty filters
     */
    QList<QTKServiceSlotEntry> m_listComplicatedListeners;

    /**
     * @brief m_listCache
     * Service listeners with "simple" filters are cached
     */
    QList<QHash<QString, QList<QTKServiceSlotEntry>>> m_listCache;

    QSet<QTKServiceSlotEntry> m_serviceSet;
    QTKPluginFrameworkContext *m_pPFWContext;
};

QTK_PLUGINFRAMEWORK_END_NAMESPACE

#endif // QTKPLUGINFRAMEWORKLISTENERS_P_H
