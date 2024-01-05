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

#include <private/qextOsgiPluginFrameworkContext_p.h>
#include <private/qextOsgiServiceRegistration_p.h>
#include <private/qextOsgiServiceSlotEntry_p.h>
#include <private/qextOsgiServices_p.h>
#include <private/qextOsgiPlugin_p.h>
#include <qextOsgiServiceRegistration.h>
#include <qextOsgiPluginConstants.h>
#include <qextOsgiServiceFactory.h>

#include <QMutex>

#include <stdexcept>

//----------------------------------------------------------------------------
QExtOsgiServiceRegistration::QExtOsgiServiceRegistration()
    : d_ptr(0)
{

}

//----------------------------------------------------------------------------
QExtOsgiServiceRegistration::QExtOsgiServiceRegistration(const QExtOsgiServiceRegistration& reg)
    : d_ptr(reg.d_ptr)
{
    if (d_func()) d_func()->ref.ref();
}

//----------------------------------------------------------------------------
QExtOsgiServiceRegistration::QExtOsgiServiceRegistration(QExtOsgiServiceRegistrationPrivate* registrationPrivate)
    : d_ptr(registrationPrivate)
{
    if(d_func()) d_func()->ref.ref();
}

//----------------------------------------------------------------------------
QExtOsgiServiceRegistration::QExtOsgiServiceRegistration(QExtOsgiPluginPrivate* plugin, QObject* service,
                                               const QExtOsgiDictionary& props)
    : d_ptr(new QExtOsgiServiceRegistrationPrivate(plugin, service, props))
{

}

//----------------------------------------------------------------------------
QExtOsgiServiceRegistration::operator bool() const
{
    return d_func();
}

//----------------------------------------------------------------------------
QExtOsgiServiceRegistration& QExtOsgiServiceRegistration::operator=(int null)
{
    if (null == 0)
    {
        if (d_func() && !d_func()->ref.deref())
        {
            delete d_ptr;
        }
        d_ptr = 0;
    }
    return *this;
}

//----------------------------------------------------------------------------
QExtOsgiServiceRegistration::~QExtOsgiServiceRegistration()
{
    if (d_func() && !d_func()->ref.deref())
        delete d_ptr;
}

//----------------------------------------------------------------------------
QExtOsgiServiceReference QExtOsgiServiceRegistration::getReference() const
{
    Q_D(const QExtOsgiServiceRegistration);

    if (!d) throw QExtIllegalStateException("qextOsgiServiceRegistration object invalid");
    if (!d->available) throw QExtIllegalStateException("Service is unregistered");

    return d->reference;
}

//----------------------------------------------------------------------------
void QExtOsgiServiceRegistration::setProperties(const QExtOsgiDictionary& props)
{
    Q_D(QExtOsgiServiceRegistration);
    if (!d) throw QExtIllegalStateException("qextOsgiServiceRegistration object invalid");

    QMutexLocker lock(&d->eventLock);

    QSet<QExtOsgiServiceSlotEntry> before;
    // TBD, optimize the locking of services
    {
        QMutexLocker lock2(&d->plugin->fwCtx->globalFwLock);
        QMutexLocker lock3(&d->propsLock);

        if (d->available)
        {
            // NYI! Optimize the MODIFIED_ENDMATCH code
            int old_rank = d->properties.value(QExtOsgiPluginConstants::SERVICE_RANKING).toInt();
            before = d->plugin->fwCtx->listeners.getMatchingServiceSlots(d->reference, false);
            QStringList classes = d->properties.value(QExtOsgiPluginConstants::OBJECTCLASS).toStringList();
            qlonglong sid = d->properties.value(QExtOsgiPluginConstants::SERVICE_ID).toLongLong();
            d->properties = QExtOsgiServices::createServiceProperties(props, classes, sid);
            int new_rank = d->properties.value(QExtOsgiPluginConstants::SERVICE_RANKING).toInt();
            if (old_rank != new_rank)
            {
                d->plugin->fwCtx->services->updateServiceRegistrationOrder(*this, classes);
            }
        }
        else
        {
            throw QExtIllegalStateException("Service is unregistered");
        }
    }
    d->plugin->fwCtx->listeners.serviceChanged(
        d->plugin->fwCtx->listeners.getMatchingServiceSlots(d->reference),
        QExtOsgiServiceEvent(QExtOsgiServiceEvent::MODIFIED, d->reference), before);

    d->plugin->fwCtx->listeners.serviceChanged(
        before,
        QExtOsgiServiceEvent(QExtOsgiServiceEvent::MODIFIED_ENDMATCH, d->reference));
}

//----------------------------------------------------------------------------
void QExtOsgiServiceRegistration::unregister()
{
    Q_D(QExtOsgiServiceRegistration);
    if (!d) throw QExtIllegalStateException("qextOsgiServiceRegistration object invalid");

    if (d->unregistering) return; // Silently ignore redundant unregistration.
    {
        QMutexLocker lock(&d->eventLock);
        if (d->unregistering) return;
        d->unregistering = true;

        if (d->available)
        {
            if (d->plugin)
            {
                d->plugin->fwCtx->services->removeServiceRegistration(*this);
            }
        }
        else
        {
            throw QExtIllegalStateException("Service is unregistered");
        }
    }

    if (d->plugin)
    {
        d->plugin->fwCtx->listeners.serviceChanged(
            d->plugin->fwCtx->listeners.getMatchingServiceSlots(d->reference),
            QExtOsgiServiceEvent(QExtOsgiServiceEvent::UNREGISTERING, d->reference));
    }

    {
        QMutexLocker lock(&d->eventLock);
        {
            QMutexLocker lock2(&d->propsLock);
            d->available = false;
            if (d->plugin)
            {
                for (QHashIterator<QSharedPointer<QExtOsgiPlugin>, QObject*> i(d->serviceInstances); i.hasNext();)
                {
                    QObject* obj = i.next().value();
                    try
                    {
                        // NYI, don't call inside lock
                        qobject_cast<QExtOsgiServiceFactory*>(d->service)->ungetService(i.key(),
                                                                                    *this,
                                                                                    obj);
                    }
                    catch (const QExtException& ue)
                    {
                        QExtOsgiPluginFrameworkEvent pfwEvent(QExtOsgiPluginFrameworkEvent::PLUGIN_ERROR, d->plugin->q_func(), ue);
                        d->plugin->fwCtx->listeners.emitFrameworkEvent(pfwEvent);
                    }
                }
            }
            d->plugin = 0;
            d->dependents.clear();
            d->service = 0;
            d->serviceInstances.clear();
            d->reference = 0;
            d->unregistering = false;
        }
    }
}

//----------------------------------------------------------------------------
bool QExtOsgiServiceRegistration::operator<(const QExtOsgiServiceRegistration& o) const
{
    Q_D(const QExtOsgiServiceRegistration);
    if (!d) return true;
    return d->reference <(o.d_func()->reference);
}

//----------------------------------------------------------------------------
bool QExtOsgiServiceRegistration::operator==(const QExtOsgiServiceRegistration& registration) const
{
    Q_D(const QExtOsgiServiceRegistration);
    return d == registration.d_func();
}

//----------------------------------------------------------------------------
QExtOsgiServiceRegistration& QExtOsgiServiceRegistration::operator=(const QExtOsgiServiceRegistration& registration)
{
    QExtOsgiServiceRegistrationPrivate* curr_d = d_func();
    d_ptr = registration.d_ptr;
    if (d_ptr) d_ptr->ref.ref();

    if (curr_d && !curr_d->ref.deref())
        delete curr_d;

    return *this;
}

//----------------------------------------------------------------------------
uint qHash(const QExtOsgiServiceRegistration& serviceReg)
{
    return qHash(serviceReg.d_func());
}
