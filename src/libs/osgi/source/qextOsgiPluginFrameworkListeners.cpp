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

#include <private/qextOsgiPluginFrameworkListeners_p.h>
#include <private/qextOsgiPluginFrameworkContext_p.h>
#include <private/qextOsgiServiceReference_p.h>
#include <private/qextOsgiLDAPExpr_p.h>
#include <qextOsgiPluginConstants.h>
#include <qextException.h>

#include <QStringListIterator>
#include <QDebug>

const int QExtOsgiPluginFrameworkListeners::OBJECTCLASS_IX = 0;
const int QExtOsgiPluginFrameworkListeners::SERVICE_ID_IX = 1;
const int QExtOsgiPluginFrameworkListeners::SERVICE_PID_IX = 2;

//----------------------------------------------------------------------------
QExtOsgiPluginFrameworkListeners::QExtOsgiPluginFrameworkListeners(QExtOsgiPluginFrameworkContext* pluginFw)
    : pluginFw(pluginFw)
{
    hashedServiceKeys << QExtOsgiPluginConstants::OBJECTCLASS.toLower()
                      << QExtOsgiPluginConstants::SERVICE_ID.toLower()
                      << QExtOsgiPluginConstants::SERVICE_PID.toLower();

    for (int i = 0; i < hashedServiceKeys.size(); ++i)
    {
        cache.push_back(QHash<QString, QList<QExtOsgiServiceSlotEntry> >());
    }
}

//----------------------------------------------------------------------------
void QExtOsgiPluginFrameworkListeners::addServiceSlot(
    QSharedPointer<QExtOsgiPlugin> plugin, QObject *receiver,
    const char *slot, const QString &filter)
{
    QMutexLocker lock(&mutex); Q_UNUSED(lock)
    QExtOsgiServiceSlotEntry sse(plugin, receiver, slot, filter);
    if (serviceSet.contains(sse))
    {
        removeServiceSlot_unlocked(plugin, receiver, slot);
    }
    serviceSet.insert(sse);
    checkSimple(sse);

    connect(receiver, SIGNAL(destroyed(QObject*)), this, SLOT(serviceListenerDestroyed(QObject*)), Qt::DirectConnection);
}

//----------------------------------------------------------------------------
void QExtOsgiPluginFrameworkListeners::removeServiceSlot(QSharedPointer<QExtOsgiPlugin> plugin,
                                                         QObject *receiver,
                                                         const char *slot)
{
    QMutexLocker lock(&mutex);
    removeServiceSlot_unlocked(plugin, receiver, slot);
}

//----------------------------------------------------------------------------
void QExtOsgiPluginFrameworkListeners::removeServiceSlot_unlocked(QSharedPointer<QExtOsgiPlugin> plugin,
                                                                  QObject *receiver,
                                                                  const char *slot)
{
    QExtOsgiServiceSlotEntry entryToRemove(plugin, receiver, slot);
    QMutableSetIterator<QExtOsgiServiceSlotEntry> it(serviceSet);
    while (it.hasNext())
    {
        QExtOsgiServiceSlotEntry currentEntry = it.next();
        if (currentEntry == entryToRemove)
        {
            currentEntry.setRemoved(true);
            //listeners.framework.hooks.handleServiceListenerUnreg(sle);
            removeFromCache(currentEntry);
            it.remove();
            if (slot) break;
        }
    }

    if (plugin)
    {
        disconnect(receiver, SIGNAL(destroyed(QObject*)), this, SLOT(serviceListenerDestroyed(QObject*)));
    }
}

//----------------------------------------------------------------------------
void QExtOsgiPluginFrameworkListeners::serviceListenerDestroyed(QObject *listener)
{
    this->removeServiceSlot(QSharedPointer<QExtOsgiPlugin>(0), listener, 0);
}

//----------------------------------------------------------------------------
QSet<QExtOsgiServiceSlotEntry> QExtOsgiPluginFrameworkListeners::getMatchingServiceSlots(
    const QExtOsgiServiceReference &sr, bool lockProps)
{
    QMutexLocker lock(&mutex); Q_UNUSED(lock);

    QSet<QExtOsgiServiceSlotEntry> set;
    set.reserve(serviceSet.size());
    // Check complicated or empty listener filters
    int n = 0;
    QExtOsgiLDAPExpr expr;
    foreach (const QExtOsgiServiceSlotEntry& sse, complicatedListeners)
    {
        ++n;
        expr = sse.getLDAPExpr();
        if (expr.isNull() || expr.evaluate(sr.d_func()->getProperties(), false))
        {
            set.insert(sse);
        }
    }

    if (pluginFw->debug.ldap)
    {
        qDebug() << "Added" << set.size() << "out of" << n
                 << "listeners with complicated filters";
    }

    // Check the cache
    QStringList c = sr.d_func()->getProperty(QExtOsgiPluginConstants::OBJECTCLASS, lockProps).toStringList();
    foreach (QString objClass, c)
    {
        addToSet(set, OBJECTCLASS_IX, objClass);
    }

    bool ok = false;
    qlonglong service_id = sr.d_func()->getProperty(QExtOsgiPluginConstants::SERVICE_ID, lockProps).toLongLong(&ok);
    if (ok)
    {
        addToSet(set, SERVICE_ID_IX, QString::number(service_id));
    }

    QStringList service_pids = sr.d_func()->getProperty(QExtOsgiPluginConstants::SERVICE_PID, lockProps).toStringList();
    foreach (QString service_pid, service_pids)
    {
        addToSet(set, SERVICE_PID_IX, service_pid);
    }

    return set;
}

//----------------------------------------------------------------------------
void QExtOsgiPluginFrameworkListeners::frameworkError(QSharedPointer<QExtOsgiPlugin> p, const QExtException& e)
{
    emit frameworkEvent(QExtOsgiPluginFrameworkEvent(QExtOsgiPluginFrameworkEvent::PLUGIN_ERROR, p, e));
}

//----------------------------------------------------------------------------
void QExtOsgiPluginFrameworkListeners::emitFrameworkEvent(const QExtOsgiPluginFrameworkEvent &event)
{
    emit frameworkEvent(event);
}

//----------------------------------------------------------------------------
void QExtOsgiPluginFrameworkListeners::emitPluginChanged(const QExtOsgiPluginEvent &event)
{
    emit pluginChangedDirect(event);

    if (!(event.getType() == QExtOsgiPluginEvent::STARTING ||
          event.getType() == QExtOsgiPluginEvent::STOPPING ||
          event.getType() == QExtOsgiPluginEvent::LAZY_ACTIVATION))
    {
        emit pluginChangedQueued(event);
    }
}

//----------------------------------------------------------------------------
void QExtOsgiPluginFrameworkListeners::serviceChanged(
    const QSet<QExtOsgiServiceSlotEntry>& receivers,
    const QExtOsgiServiceEvent &evt)
{
    QSet<QExtOsgiServiceSlotEntry> matchBefore;
    serviceChanged(receivers, evt, matchBefore);
}

//----------------------------------------------------------------------------
void QExtOsgiPluginFrameworkListeners::serviceChanged(
    const QSet<QExtOsgiServiceSlotEntry>& receivers,
    const QExtOsgiServiceEvent &evt,
    QSet<QExtOsgiServiceSlotEntry>& matchBefore)
{
    QExtOsgiServiceReference sr = evt.getServiceReference();
    //QStringList classes = sr.getProperty(QExtOsgiPluginConstants::OBJECTCLASS).toStringList();
    int n = 0;

    //framework.hooks.filterServiceEventReceivers(evt, receivers);

    foreach (QExtOsgiServiceSlotEntry l, receivers)
    {
        if (!matchBefore.isEmpty())
        {
            matchBefore.remove(l);
        }

        // TODO permission checks
        //if (l.bundle.hasPermission(new ServicePermission(sr, ServicePermission.GET))) {
        //foreach (QString clazz, classes)
        //{
        try
        {
            ++n;
            l.invokeSlot(evt);
        }
        catch (const QExtException& pe)
        {
            frameworkError(l.getPlugin(), pe);
        }
        catch (const std::exception& e)
        {
            frameworkError(l.getPlugin(), QExtRuntimeException(e.what()));
        }

        //break;
        //}
        //}
    }

    if (pluginFw->debug.ldap)
    {
        qDebug() << "Notified" << n << " listeners";
    }
}

//----------------------------------------------------------------------------
void QExtOsgiPluginFrameworkListeners::removeFromCache(const QExtOsgiServiceSlotEntry& sse)
{
    if (!sse.getLocalCache().isEmpty())
    {
        for (int i = 0; i < hashedServiceKeys.size(); ++i)
        {
            QHash<QString, QList<QExtOsgiServiceSlotEntry> >& keymap = cache[i];
            QStringList &l = sse.getLocalCache()[i];
            QStringListIterator it(l);
            while (it.hasNext())
            {
                QString value = it.next();
                QList<QExtOsgiServiceSlotEntry>& sses = keymap[value];
                sses.removeAll(sse);
                if (sses.isEmpty())
                {
                    keymap.remove(value);
                }
            }
        }
    }
    else
    {
        complicatedListeners.removeAll(sse);
    }
}

//----------------------------------------------------------------------------
void QExtOsgiPluginFrameworkListeners::checkSimple(const QExtOsgiServiceSlotEntry& sse)
{
    if (sse.getLDAPExpr().isNull()) // || listeners.nocacheldap) {
    {
        complicatedListeners.push_back(sse);
    }
    else
    {
        QExtOsgiLDAPExpr::LocalCache local_cache;
        if (sse.getLDAPExpr().isSimple(hashedServiceKeys, local_cache, false))
        {
            sse.getLocalCache() = local_cache;
            for (int i = 0; i < hashedServiceKeys.size(); ++i)
            {
                QStringListIterator it(local_cache[i]);
                while (it.hasNext())
                {
                    QString value = it.next();
                    QList<QExtOsgiServiceSlotEntry>& sses = cache[i][value];
                    sses.push_back(sse);
                }
            }
        }
        else
        {
            if (pluginFw->debug.ldap)
            {
                qDebug() << "## DEBUG: Too complicated filter:" << sse.getFilter();
            }
            complicatedListeners.push_back(sse);
        }
    }
}

//----------------------------------------------------------------------------
void QExtOsgiPluginFrameworkListeners::addToSet(QSet<QExtOsgiServiceSlotEntry>& set,
                                                int cache_ix, const QString &val)
{
    QList<QExtOsgiServiceSlotEntry>& l = cache[cache_ix][val];
    if (!l.isEmpty())
    {
        if (pluginFw->debug.ldap)
        {
            qDebug() << hashedServiceKeys[cache_ix] << "matches" << l.size();
        }
        foreach (QExtOsgiServiceSlotEntry entry, l)
        {
            set.insert(entry);
        }
    }
    else
    {
        if (pluginFw->debug.ldap)
        {
            qDebug() << hashedServiceKeys[cache_ix] << "matches none";
        }
    }
}
