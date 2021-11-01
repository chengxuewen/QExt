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

#include "qtkserviceslotentry_p.h"
#include "qtkldapexpr_p.h"
#include "qtkplugin.h"

#include <QTKCore/QTKException>

#include <QSharedData>

#include <cstring>

QTK_CORE_USE_NAMESPACE

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

class QTKServiceSlotEntryData : public QSharedData
{
public:

    QTKServiceSlotEntryData(QSharedPointer<QTKPlugin> pPlugin, QObject *pReceiver,
                            const char *psSlot)
        : m_pPlugin(pPlugin),
          m_pReceiver(pReceiver),
          m_psSlot(psSlot),
          m_bRemoved(false),
          m_uiHashValue(0)
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
    QTKLDAPExpr::LocalCache m_localCache;
    QTKLDAPExpr m_ldap;
    QSharedPointer<QTKPlugin> m_pPlugin;
    QObject *m_pReceiver;
    const char *m_psSlot;
    bool m_bRemoved;
    uint m_uiHashValue;
};

QTKServiceSlotEntry::QTKServiceSlotEntry(QSharedPointer<QTKPlugin> pPlugin, QObject *pSeceiver, const char *pSlot,
                                         const QString &strFilter)
    : d(new QTKServiceSlotEntryData(pPlugin, pSeceiver, pSlot))
{
    if (!strFilter.isNull()) {
        d->m_ldap = QTKLDAPExpr(strFilter);
    }
}

QTKServiceSlotEntry::QTKServiceSlotEntry(const QTKServiceSlotEntry &other)
    : d(other.d)
{

}

/**
 * @brief QTKServiceSlotEntry::QTKServiceSlotEntry
 * default constructor for use in QSet
 */
QTKServiceSlotEntry::QTKServiceSlotEntry() : d(new QTKServiceSlotEntryData(QSharedPointer<QTKPlugin>(0), 0, 0))
{

}

/**
 * @brief QTKServiceSlotEntry::operator =
 * assignment operator for use in QSet
 *
 * @param other
 * @return
 */
QTKServiceSlotEntry& QTKServiceSlotEntry::operator=(const QTKServiceSlotEntry &other)
{
    d = other.d;
    return *this;
}

QTKServiceSlotEntry::~QTKServiceSlotEntry()
{

}

bool QTKServiceSlotEntry::operator==(const QTKServiceSlotEntry &other) const
{
    return ((d->m_pPlugin == 0 || other.d->m_pPlugin == 0) || d->m_pPlugin == other.d->m_pPlugin)
            && d->m_pReceiver == other.d->m_pReceiver
            && ((d->m_psSlot == 0 || other.d->m_psSlot == 0) || std::strcmp(d->m_psSlot, other.d->m_psSlot) == 0);
}

void QTKServiceSlotEntry::invokeSlot(const QTKServiceEvent &event)
{
    if (!QMetaObject::invokeMethod(d->m_pReceiver, d->m_psSlot,
                                   Qt::DirectConnection,
                                   Q_ARG(QTKServiceEvent, event)))
    {
        throw QTKRuntimeException(QString("Slot %1 of %2 could not be invoked. A call to "
                                          "QTKPluginContext::connectServiceListener() must only contain "
                                          "the slot name, not the whole signature.").
                                  arg(d->m_psSlot).arg(d->m_pReceiver->metaObject()->className()));
    }
}

void QTKServiceSlotEntry::setRemoved(bool bRemoved)
{
    d->m_bRemoved = bRemoved;
}

bool QTKServiceSlotEntry::isRemoved() const
{
    return d->m_bRemoved;
}

QSharedPointer<QTKPlugin> QTKServiceSlotEntry::getPlugin() const
{
    return d->m_pPlugin;
}

QTKLDAPExpr QTKServiceSlotEntry::getLDAPExpr() const
{
    return d->m_ldap;
}

QString QTKServiceSlotEntry::getFilter() const
{
    return d->m_ldap.isNull() ? QString() : d->m_ldap.toString();
}

QTKLDAPExpr::LocalCache &QTKServiceSlotEntry::getLocalCache() const
{
    return d->m_localCache;
}

uint qHash(const QTKServiceSlotEntry &serviceSlotEntry)
{
    if (0 == serviceSlotEntry.d->m_uiHashValue) {
        QByteArray receiverAddress((const char *)serviceSlotEntry.d->m_pReceiver);
        QByteArray slotAddress((const char *)serviceSlotEntry.d->m_psSlot);
        serviceSlotEntry.d->m_uiHashValue = qHash(serviceSlotEntry.d->m_pPlugin) * 4 +
                qHash(receiverAddress.toHex()) * 2 + qHash(slotAddress.toHex());
    }
    return serviceSlotEntry.d->m_uiHashValue;
}

QTK_PLUGINFRAMEWORK_END_NAMESPACE
