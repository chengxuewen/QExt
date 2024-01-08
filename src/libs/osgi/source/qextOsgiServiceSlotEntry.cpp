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

#include <private/qextOsgiServiceSlotEntry_p.h>
#include <private/qextOsgiLDAPExpr_p.h>
#include <qextOsgiPlugin.h>
#include <qextException.h>

#include <QSharedData>

#include <cstring>

class QExtOsgiServiceSlotEntryData : public QSharedData
{
public:

    QExtOsgiServiceSlotEntryData(QSharedPointer<QExtOsgiPlugin> p, QObject *receiver,
                            const char *slot)
        : plugin(p), receiver(receiver),
        slot(slot), removed(false),
        hashValue(0)
    {

    }

    /**
   * The elements of "simple" filters are cached, for easy lookup.
   *
   * The grammar for simple filters is as follows:
   *
   * <pre>
   * Simple = '(' attr '=' value ')'
   *        | '(' '|' Simple+ ')'
   * </pre>
   * where <code>attr</code> is one of {@link Constants#OBJECTCLASS},
   * {@link Constants#SERVICE_ID} or {@link Constants#SERVICE_PID}, and
   * <code>value</code> must not contain a wildcard character.
   * <p>
   * The index of the vector determines which key the cache is for
   * (see {@link ServiceListenerState#hashedKeys}). For each key, there is
   * a vector pointing out the values which are accepted by this
   * ServiceListenerEntry's filter. This cache is maintained to make
   * it easy to remove this service listener.
   */
    QExtOsgiLDAPExpr::LocalCache local_cache;

    QExtOsgiLDAPExpr ldap;
    QSharedPointer<QExtOsgiPlugin> plugin;
    QObject *receiver;
    const char *slot;
    bool removed;

    uint hashValue;
};

//----------------------------------------------------------------------------
QExtOsgiServiceSlotEntry::QExtOsgiServiceSlotEntry(
    QSharedPointer<QExtOsgiPlugin> p, QObject *receiver, const char *slot, const QString &filter)
    : d(new QExtOsgiServiceSlotEntryData(p, receiver, slot))
{
    if (!filter.isNull())
    {
        d->ldap = QExtOsgiLDAPExpr(filter);
    }
}

//----------------------------------------------------------------------------
QExtOsgiServiceSlotEntry::QExtOsgiServiceSlotEntry(const QExtOsgiServiceSlotEntry& other)
    : d(other.d)
{

}

//----------------------------------------------------------------------------
QExtOsgiServiceSlotEntry::QExtOsgiServiceSlotEntry()
    : d(new QExtOsgiServiceSlotEntryData(QSharedPointer<QExtOsgiPlugin>(0), 0, 0))
{

}

//----------------------------------------------------------------------------
QExtOsgiServiceSlotEntry& QExtOsgiServiceSlotEntry::operator=(const QExtOsgiServiceSlotEntry& other)
{
    d = other.d;
    return *this;
}

//----------------------------------------------------------------------------
QExtOsgiServiceSlotEntry::~QExtOsgiServiceSlotEntry()
{

}

//----------------------------------------------------------------------------
bool QExtOsgiServiceSlotEntry::operator==(const QExtOsgiServiceSlotEntry& other) const
{
    return ((d->plugin == 0 || other.d->plugin == 0) || d->plugin == other.d->plugin) &&
           d->receiver == other.d->receiver &&
           ((d->slot == 0 || other.d->slot == 0) || std::strcmp(d->slot, other.d->slot) == 0);
}

//----------------------------------------------------------------------------
void QExtOsgiServiceSlotEntry::invokeSlot(const QExtOsgiServiceEvent &event)
{
    if (!QMetaObject::invokeMethod(d->receiver, d->slot,
                                   Qt::DirectConnection,
                                   Q_ARG(QExtOsgiServiceEvent, event)))
    {
        throw QExtRuntimeException(
            QString("Slot %1 of %2 could not be invoked. A call to "
                    "qextOsgiPluginContext::connectServiceListener() must only contain "
                    "the slot name, not the whole signature.").
            arg(d->slot).arg(d->receiver->metaObject()->className()));
    }
}

//----------------------------------------------------------------------------
void QExtOsgiServiceSlotEntry::setRemoved(bool removed)
{
    d->removed = removed;
}

//----------------------------------------------------------------------------
bool QExtOsgiServiceSlotEntry::isRemoved() const
{
    return d->removed;
}

//----------------------------------------------------------------------------
QSharedPointer<QExtOsgiPlugin> QExtOsgiServiceSlotEntry::getPlugin() const
{
    return d->plugin;
}

//----------------------------------------------------------------------------
QExtOsgiLDAPExpr QExtOsgiServiceSlotEntry::getLDAPExpr() const
{
    return d->ldap;
}

//----------------------------------------------------------------------------
QString QExtOsgiServiceSlotEntry::getFilter() const
{
    return d->ldap.isNull() ? QString() : d->ldap.toString();
}

//----------------------------------------------------------------------------
QExtOsgiLDAPExpr::LocalCache& QExtOsgiServiceSlotEntry::getLocalCache() const
{
    return d->local_cache;
}

//----------------------------------------------------------------------------
uint qHash(const QExtOsgiServiceSlotEntry& serviceSlot)
{
    if (serviceSlot.d->hashValue == 0)
    {
        serviceSlot.d->hashValue = qHash(serviceSlot.d->plugin) * 4 +
                                   qHash(serviceSlot.d->receiver) * 2 + qHash(serviceSlot.d->slot);
    }
    return serviceSlot.d->hashValue;
}
