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

#include "qtkserviceregistration.h"
#include "qtkpluginframeworkcontext_p.h"
#include "qtkplugin_p.h"
#include "qtkpluginconstants.h"
#include "qtkservicefactory.h"
#include "qtkserviceregistration.h"
#include "qtkserviceregistration_p.h"
#include "qtkservices_p.h"
#include "qtkserviceslotentry_p.h"
#include "qtkpluginframeworkevent.h"

#include <QMutex>
#include <stdexcept>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

/**
 * @brief QTKServiceRegistration::QTKServiceRegistration
 * Creates an invalid QTKServiceRegistration object. You can use
 * this object in boolean expressions and it will evaluate to
 * <code>false</code>.
 */
QTKServiceRegistration::QTKServiceRegistration()
    : d_ptr(nullptr)
{

}

QTKServiceRegistration::QTKServiceRegistration(const QTKServiceRegistration &serviceReg)
    : d_ptr(serviceReg.d_ptr)
{
    if (d_func()) {
        d_func()->m_ref.ref();
    }
}

/**
 * @brief QTKServiceRegistration::QTKServiceRegistration
 * @param pRegistrationPrivate
 */
QTKServiceRegistration::QTKServiceRegistration(QTKServiceRegistrationPrivate *pRegistrationPrivate)
    : d_ptr(pRegistrationPrivate)
{
    if(d_func()) {
        d_func()->m_ref.ref();
    }
}

QTKServiceRegistration::QTKServiceRegistration(QTKPluginPrivate *pPlugin, QObject *pService,
                                               const QTKDictionary &pProperties)
    : d_ptr(new QTKServiceRegistrationPrivate(pPlugin, pService, pProperties))
{

}

QTKServiceRegistration::operator bool() const
{
    return d_func();
}

/**
 * @brief QTKServiceRegistration::operator =
 * Releases any resources held or locked by this
 * <code>QTKServiceRegistration</code> and renders it invalid.
 * @param iNull
 * @return
 */
QTKServiceRegistration& QTKServiceRegistration::operator=(int iNull)
{
    if (0 == iNull) {
        if (d_func() && !d_func()->m_ref.deref()) {
            delete d_ptr;
        }
        d_ptr = nullptr;
    }
    return *this;
}

QTKServiceRegistration::~QTKServiceRegistration()
{
    if (d_func() && !d_func()->m_ref.deref()) {
        delete d_ptr;
    }
}

QTKServiceReference QTKServiceRegistration::getReference() const
{
    Q_D(const QTKServiceRegistration);

    if (!d) {
        throw QTKIllegalStateException("QTKServiceRegistration object invalid");
    }
    if (!d->m_bAvailable) {
        throw QTKIllegalStateException("Service is unregistered");
    }

    return d->m_reference;
}

void QTKServiceRegistration::setProperties(const QTKDictionary &properties)
{
    Q_D(QTKServiceRegistration);
    if (!d) {
        throw QTKIllegalStateException("QTKServiceRegistration object invalid");
    }

    QMutexLocker locker(&d->m_eventLock);

    QSet<QTKServiceSlotEntry> before;
    // TBD, optimize the locking of services
    {
        QMutexLocker locker2(&d->m_pPluginPrivate->m_pPFWContext->sm_globalFWLock);
        QMutexLocker locker3(&d->m_propsLock);

        if (d->m_bAvailable) {
            // NYI! Optimize the Type_ModifiedEndMatch code
            int iOldRank = d->m_properties.value(QTKPluginConstants::SERVICE_RANKING).toInt();
            before = d->m_pPluginPrivate->m_pPFWContext->m_listeners.getMatchingServiceSlots(d->m_reference, false);
            QStringList listClasses = d->m_properties.value(QTKPluginConstants::OBJECT_CLASS).toStringList();
            qlonglong llIid = d->m_properties.value(QTKPluginConstants::SERVICE_ID).toLongLong();
            d->m_properties = QTKServices::createServiceProperties(properties, listClasses, llIid);
            int iewRank = d->m_properties.value(QTKPluginConstants::SERVICE_RANKING).toInt();
            if (iOldRank != iewRank) {
                d->m_pPluginPrivate->m_pPFWContext->m_pServices->updateServiceRegistrationOrder(*this, listClasses);
            }
        } else {
            throw QTKIllegalStateException("Service is unregistered");
        }
    }
    d->m_pPluginPrivate->m_pPFWContext->m_listeners.serviceChanged(
                d->m_pPluginPrivate->m_pPFWContext->m_listeners.getMatchingServiceSlots(d->m_reference),
                QTKServiceEvent(QTKServiceEvent::Type_Modified, d->m_reference), before);

    d->m_pPluginPrivate->m_pPFWContext->m_listeners.serviceChanged(
                before,
                QTKServiceEvent(QTKServiceEvent::Type_ModifiedEndMatch, d->m_reference));
}

void QTKServiceRegistration::unregister()
{
    Q_D(QTKServiceRegistration);
    if (!d) {
        throw QTKIllegalStateException("QTKServiceRegistration object invalid");
    }

    if (d->m_bUnregistering) { // Silently ignore redundant unregistration.
        return;
    }

    {
        QMutexLocker locker(&d->m_eventLock);
        if (d->m_bUnregistering) {
            return;
        }
        d->m_bUnregistering = true;

        if (d->m_bAvailable) {
            if (d->m_pPluginPrivate) {
                d->m_pPluginPrivate->m_pPFWContext->m_pServices->removeServiceRegistration(*this);
            }
        } else {
            throw QTKIllegalStateException("Service is unregistered");
        }
    }

    if (d->m_pPluginPrivate) {
        d->m_pPluginPrivate->m_pPFWContext->m_listeners.serviceChanged(
                    d->m_pPluginPrivate->m_pPFWContext->m_listeners.getMatchingServiceSlots(d->m_reference),
                    QTKServiceEvent(QTKServiceEvent::Type_Unregistering, d->m_reference));
    }

    {
        QMutexLocker locker(&d->m_eventLock);
        {
            QMutexLocker locker2(&d->m_propsLock);
            d->m_bAvailable = false;
            if (d->m_pPluginPrivate) {
                for (QHashIterator<QSharedPointer<QTKPlugin>, QObject*> i(d->m_mapServiceInstances); i.hasNext();) {
                    QObject *pObj = i.next().value();
                    try {
                        // NYI, don't call inside lock
                        qobject_cast<QTKServiceFactory*>(d->m_pService)->ungetService(i.key(),
                                                                                      *this,
                                                                                      pObj);
                    } catch (const QTKException &exception) {
                        QTKPluginFrameworkEvent pfwEvent(QTKPluginFrameworkEvent::Type_PluginError, d->m_pPluginPrivate->q_func(), exception);
                        d->m_pPluginPrivate->m_pPFWContext->m_listeners.emitFrameworkEvent(pfwEvent);
                    }
                }
            }
            d->m_pPluginPrivate = nullptr;
            d->m_mapDependents.clear();
            d->m_pService = nullptr;
            d->m_mapServiceInstances.clear();
            d->m_reference = 0;
            d->m_bUnregistering = false;
        }
    }
}

bool QTKServiceRegistration::operator<(const QTKServiceRegistration &other) const
{
    Q_D(const QTKServiceRegistration);
    if (!d) {
        return true;
    }
    return d->m_reference <(other.d_func()->m_reference);
}

bool QTKServiceRegistration::operator==(const QTKServiceRegistration &serviceReg) const
{
    Q_D(const QTKServiceRegistration);
    return d == serviceReg.d_func();
}

QTKServiceRegistration &QTKServiceRegistration::operator=(const QTKServiceRegistration &serviceReg)
{
    QTKServiceRegistrationPrivate *pServiceRegPrivate = d_func();
    d_ptr = serviceReg.d_ptr;
    if (d_ptr) {
        d_ptr->m_ref.ref();
    }

    if (pServiceRegPrivate && !pServiceRegPrivate->m_ref.deref()) {
        delete pServiceRegPrivate;
    }

    return *this;
}

uint qHash(const QTKServiceRegistration &serviceReg)
{
    QByteArray address((const char *)serviceReg.d_func());
    return qHash(address.toHex());
}

QTK_PLUGINFRAMEWORK_END_NAMESPACE
