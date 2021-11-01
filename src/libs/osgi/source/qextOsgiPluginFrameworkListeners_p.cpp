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

#include "qtkpluginframeworklisteners_p.h"
#include "qtkpluginframeworkcontext_p.h"
#include "qtkpluginconstants.h"
#include "qtkldapexpr_p.h"
#include "qtkservicereference_p.h"

#include <QTKCore/QTKException>

#include <QStringListIterator>
#include <QDebug>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

const int QTKPluginFrameworkListeners::sm_iObjectClassIx = 0;
const int QTKPluginFrameworkListeners::sm_iServiceIdIx = 1;
const int QTKPluginFrameworkListeners::sm_iServicePidIx = 2;

QTKPluginFrameworkListeners::QTKPluginFrameworkListeners(QTKPluginFrameworkContext* pPFWContext)
    : m_pPFWContext(pPFWContext)
{
    m_listHashedServiceKeys << QString(QTKPluginConstants::OBJECT_CLASS).toLower()
                            << QString(QTKPluginConstants::SERVICE_ID).toLower()
                            << QString(QTKPluginConstants::SERVICE_PID).toLower();

    for (int i = 0; i < m_listHashedServiceKeys.size(); ++i) {
        m_listCache.push_back(QHash<QString, QList<QTKServiceSlotEntry> >());
    }
}

/**
 * @brief QTKPluginFrameworkListeners::addServiceSlot
 * Add a slot receiving service envents with filter to the current framework.
 * If no filter is wanted, call with a null filter.
 *
 * @param pPlugin Who wants to add the slot.
 * @param pReceiver Object to add.
 * @param pSlot The slot in the receiver.
 * @param strFilter LDAP String used for filtering event before calling listener.
 */
void QTKPluginFrameworkListeners::addServiceSlot(QSharedPointer<QTKPlugin> pPlugin, QObject *pReceiver,
                                                 const char *pSlot, const QString &strFilter)
{
    QMutexLocker lock(&m_mutex);
    Q_UNUSED(lock)
    QTKServiceSlotEntry serviceSlotEntry(pPlugin, pReceiver, pSlot, strFilter);
    if (m_serviceSet.contains(serviceSlotEntry)) {
        removeServiceSlot_unlocked(pPlugin, pReceiver, pSlot);
    }
    m_serviceSet.insert(serviceSlotEntry);
    this->checkSimple(serviceSlotEntry);

    connect(pReceiver, SIGNAL(destroyed(QObject*)), this, SLOT(serviceListenerDestroyed(QObject*)), Qt::DirectConnection);
}

/**
 * @brief QTKPluginFrameworkListeners::removeServiceSlot
 * Remove a slot connected to service events.
 *
 * @param plugin The plugin removing this listener.
 * @param pReceiver The receiver containing the slot.
 * @param pSlot The slot in the receiver.
 */
void QTKPluginFrameworkListeners::removeServiceSlot(QSharedPointer<QTKPlugin> plugin,
                                                    QObject *pReceiver,
                                                    const char *pSlot)
{
    QMutexLocker lock(&m_mutex);
    this->removeServiceSlot_unlocked(plugin, pReceiver, pSlot);
}

/**
 * @brief QTKPluginFrameworkListeners::removeServiceSlot_unlocked
 * The unsynchronized version of removeServiceSlot().
 *
 * @param pPlugin The plugin removing this listener.
 * @param pReceiver The receiver containing the slot.
 * @param pSlot The slot in the receiver.
 */
void QTKPluginFrameworkListeners::removeServiceSlot_unlocked(QSharedPointer<QTKPlugin> pPlugin,
                                                             QObject *pReceiver,
                                                             const char *pSlot)
{
    QTKServiceSlotEntry entryToRemove(pPlugin, pReceiver, pSlot);
    QMutableSetIterator<QTKServiceSlotEntry> ite(m_serviceSet);
    while (ite.hasNext()) {
        QTKServiceSlotEntry currentEntry = ite.next();
        if (currentEntry == entryToRemove) {
            currentEntry.setRemoved(true);
            //listeners.framework.hooks.handleServiceListenerUnreg(sle);
            this->removeFromCache(currentEntry);
            ite.remove();
            if (pSlot) {
                break;
            }
        }
    }

    if (pPlugin) {
        disconnect(pReceiver, SIGNAL(destroyed(QObject*)), this, SLOT(serviceListenerDestroyed(QObject*)));
    }
}

void QTKPluginFrameworkListeners::serviceListenerDestroyed(QObject *pListener)
{
    this->removeServiceSlot(QSharedPointer<QTKPlugin>(0), pListener, 0);
}

/**
 * @brief QTKPluginFrameworkListeners::getMatchingServiceSlots
 * Gets the slots interested in modifications of the service reference.
 *
 * @param serviceRef The reference related to the event describing the service modification.
 * @param bLockProps If access to the properties of the service object referenced by serviceRef
 *        should be synchronized.
 * @return A set of listeners to notify.
 */
QSet<QTKServiceSlotEntry> QTKPluginFrameworkListeners::getMatchingServiceSlots(const QTKServiceReference &serviceRef, bool bLockProps)
{
    QMutexLocker lock(&m_mutex);
    Q_UNUSED(lock);

    QSet<QTKServiceSlotEntry> set;
    set.reserve(m_serviceSet.size());
    // Check complicated or empty listener filters
    int n = 0;
    QTKLDAPExpr expr;
    foreach(const QTKServiceSlotEntry &sse, m_listComplicatedListeners) {
        ++n;
        expr = sse.getLDAPExpr();
        if (expr.isNull() || expr.evaluate(serviceRef.d_func()->getProperties(), false)) {
            set.insert(sse);
        }
    }

    if (m_pPFWContext->m_debug.bLdapEnabled) {
        qDebug() << "Added" << set.size() << "out of" << n
                 << "listeners with complicated filters";
    }

    // Check the cache
    QStringList listCache = serviceRef.d_func()->getProperty(QTKPluginConstants::OBJECT_CLASS, bLockProps).toStringList();
    foreach(QString objClass, listCache) {
        this->addToSet(set, sm_iObjectClassIx, objClass);
    }

    bool bOk = false;
    qlonglong llServiceId = serviceRef.d_func()->getProperty(QTKPluginConstants::SERVICE_ID, bLockProps).toLongLong(&bOk);
    if (bOk) {
        this->addToSet(set, sm_iServiceIdIx, QString::number(llServiceId));
    }

    QStringList listServicePids = serviceRef.d_func()->getProperty(QTKPluginConstants::SERVICE_PID, bLockProps).toStringList();
    foreach(QString strServicePid, listServicePids) {
        this->addToSet(set, sm_iServicePidIx, strServicePid);
    }

    return set;
}

/**
 * @brief QTKPluginFrameworkListeners::frameworkError
 * Convenience method for throwing framework error event.
 *
 * @param pPlugin Plugin which caused the error.
 * @param exception The exception.
 */
void QTKPluginFrameworkListeners::frameworkError(QSharedPointer<QTKPlugin> pPlugin, const QTKException &exception)
{
    emit this->frameworkEvent(QTKPluginFrameworkEvent(QTKPluginFrameworkEvent::Type_PluginError, pPlugin, exception));
}

void QTKPluginFrameworkListeners::emitFrameworkEvent(const QTKPluginFrameworkEvent &event)
{
    emit this->frameworkEvent(event);
}

void QTKPluginFrameworkListeners::emitPluginChanged(const QTKPluginEvent &event)
{
    emit this->pluginChangedDirect(event);

    if (!(event.getType() == QTKPluginEvent::Type_Starting ||
          event.getType() == QTKPluginEvent::Type_Stopping ||
          event.getType() == QTKPluginEvent::Type_LazyActivation)) {
        emit this->pluginChangedQueued(event);
    }
}

/**
 * @brief QTKPluginFrameworkListeners::serviceChanged
 * Receive notification that a service has had a change occur in its lifecycle.
 *
 * @param receivers
 * @param event
 */
void QTKPluginFrameworkListeners::serviceChanged(const QSet<QTKServiceSlotEntry> &receivers,
                                                 const QTKServiceEvent &event)
{
    QSet<QTKServiceSlotEntry> matchBefore;
    this->serviceChanged(receivers, event, matchBefore);
}

void QTKPluginFrameworkListeners::serviceChanged(const QSet<QTKServiceSlotEntry> &receivers,
                                                 const QTKServiceEvent &event,
                                                 QSet<QTKServiceSlotEntry> &matchBefore)
{
    QTKServiceReference sr = event.getServiceReference();
    int n = 0;

    foreach(QTKServiceSlotEntry entry, receivers) {
        if (!matchBefore.isEmpty()) {
            matchBefore.remove(entry);
        }
        try {
            ++n;
            entry.invokeSlot(event);
        } catch (const QTKException& pe) {
            frameworkError(entry.getPlugin(), pe);
        } catch (const std::exception& e) {
            frameworkError(entry.getPlugin(), QTKRuntimeException(e.what()));
        }
    }

    if (m_pPFWContext->m_debug.bLdapEnabled) {
        qDebug() << "Notified" << n << " listeners";
    }
}

/**
 * @brief QTKPluginFrameworkListeners::removeFromCache
 * Remove all references to a service slot from the service listener cache.
 *
 * @param serviceSlotEntry
 */
void QTKPluginFrameworkListeners::removeFromCache(const QTKServiceSlotEntry &serviceSlotEntry)
{
    if (!serviceSlotEntry.getLocalCache().isEmpty()) {
        for (int i = 0; i < m_listHashedServiceKeys.size(); ++i) {
            QHash<QString, QList<QTKServiceSlotEntry> > &keymap = m_listCache[i];
            QStringList &list = serviceSlotEntry.getLocalCache()[i];
            QStringListIterator it(list);
            while (it.hasNext()) {
                QString strValue = it.next();
                QList<QTKServiceSlotEntry> &listServiceSlotEntry = keymap[strValue];
                listServiceSlotEntry.removeAll(serviceSlotEntry);
                if (listServiceSlotEntry.isEmpty()) {
                    keymap.remove(strValue);
                }
            }
        }
    } else {
        m_listComplicatedListeners.removeAll(serviceSlotEntry);
    }
}

/**
 * @brief QTKPluginFrameworkListeners::checkSimple
 * Checks if the specified service slot's filter is simple enough to cache.
 *
 * @param serviceSlotEntry
 */
void QTKPluginFrameworkListeners::checkSimple(const QTKServiceSlotEntry &serviceSlotEntry)
{
    if (serviceSlotEntry.getLDAPExpr().isNull()) {
        m_listComplicatedListeners.push_back(serviceSlotEntry);
    } else {
        QTKLDAPExpr::LocalCache localCache;
        if (serviceSlotEntry.getLDAPExpr().isSimple(m_listHashedServiceKeys, localCache, false)) {
            serviceSlotEntry.getLocalCache() = localCache;
            for (int i = 0; i < m_listHashedServiceKeys.size(); ++i) {
                QStringListIterator it(localCache[i]);
                while (it.hasNext()) {
                    QString value = it.next();
                    QList<QTKServiceSlotEntry>& sses = m_listCache[i][value];
                    sses.push_back(serviceSlotEntry);
                }
            }
        } else {
            if (m_pPFWContext->m_debug.bLdapEnabled) {
                qDebug() << "## DEBUG: Too complicated filter:" << serviceSlotEntry.getFilter();
            }
            m_listComplicatedListeners.push_back(serviceSlotEntry);
        }
    }
}

/**
 * @brief QTKPluginFrameworkListeners::addToSet
 * Add all members of the specified list to the specified set.
 *
 * @param serviceSlotEntry
 * @param iCacheIndex
 * @param strVal
 */
void QTKPluginFrameworkListeners::addToSet(QSet<QTKServiceSlotEntry> &serviceSlotEntry,
                                           int iCacheIndex, const QString &strVal)
{
    QList<QTKServiceSlotEntry> &listServiceSlotEntry = m_listCache[iCacheIndex][strVal];
    if (!listServiceSlotEntry.isEmpty()) {
        if (m_pPFWContext->m_debug.bLdapEnabled) {
            qDebug() << m_listHashedServiceKeys[iCacheIndex] << "matches" << listServiceSlotEntry.size();
        }
        foreach (QTKServiceSlotEntry entry, listServiceSlotEntry) {
            serviceSlotEntry.insert(entry);
        }
    } else {
        if (m_pPFWContext->m_debug.bLdapEnabled) {
            qDebug() << m_listHashedServiceKeys[iCacheIndex] << "matches none";
        }
    }
}

QTK_PLUGINFRAMEWORK_END_NAMESPACE
