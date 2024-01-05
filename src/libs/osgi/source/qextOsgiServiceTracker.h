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


#ifndef _QEXTOSGISERVICETRACKER_H
#define _QEXTOSGISERVICETRACKER_H

#include <qextOsgiGlobal.h>
#include >qextOsgiLDAPSearchFilter.h>
#include <qextOsgiServiceReference.h>
#include <qextOsgiServiceTrackerCustomizer.h>

#include <QScopedPointer>

template<class S, class T> class QExtOsgiTrackedService;
template<class S, class T> class QExtOsgiServiceTrackerPrivate;
class QExtOsgiPluginContext;

/**
 * \ingroup PluginFramework
 *
 * The <code>QExtOsgiServiceTracker</code> class simplifies using services from the
 * Framework's service registry.
 * <p>
 * A <code>QExtOsgiServiceTracker</code> object is constructed with search criteria and
 * a <code>QExtOsgiServiceTrackerCustomizer</code> object. A <code>QExtOsgiServiceTracker</code>
 * can use a <code>QExtOsgiServiceTrackerCustomizer</code> to customize the service
 * objects to be tracked. The <code>QExtOsgiServiceTracker</code> can then be opened to
 * begin tracking all services in the Framework's service registry that match
 * the specified search criteria. The <code>QExtOsgiServiceTracker</code> correctly
 * handles all of the details of listening to <code>QExtOsgiServiceEvent</code>s and
 * getting and ungetting services.
 * <p>
 * The <code>getServiceReferences</code> method can be called to get references
 * to the services being tracked. The <code>getService</code> and
 * <code>getServices</code> methods can be called to get the service objects for
 * the tracked service.
 * <p>
 * The <code>QExtOsgiServiceTracker</code> class is thread-safe. It does not call a
 * <code>QExtOsgiServiceTrackerCustomizer</code> while holding any locks.
 * <code>QExtOsgiServiceTrackerCustomizer</code> implementations must also be
 * thread-safe.
 *
 * \tparam S The type of the service being tracked. The type must be an
 *         assignable datatype. Further, if the
 *         <code>QExtOsgiServiceTracker(QExtOsgiPluginContext*, QExtOsgiServiceTrackerCustomizer<T>*)</code>
 *         constructor is used, the type must have an associated interface id via
 *         Q_DECLARE_INTERFACE.
 * \tparam T The type of the tracked object. The type must be an assignable
 *         datatype, provide a boolean conversion function, and provide
 *         a constructor and an assignment operator which can handle 0 as an argument.
 * \remarks This class is thread safe.
 */
template<class S = QObject*, class T = S>
class QExtOsgiServiceTracker : protected QExtOsgiServiceTrackerCustomizer<T>
{
public:

    ~QExtOsgiServiceTracker();

    /**
   * Create a <code>QExtOsgiServiceTracker</code> on the specified
   * <code>QExtOsgiServiceReference</code>.
   *
   * <p>
   * The service referenced by the specified <code>QExtOsgiServiceReference</code>
   * will be tracked by this <code>QExtOsgiServiceTracker</code>.
   *
   * @param context The <code>QExtOsgiPluginContext</code> against which the tracking
   *        is done.
   * @param reference The <code>QExtOsgiServiceReference</code> for the service to be
   *        tracked.
   * @param customizer The customizer object to call when services are added,
   *        modified, or removed in this <code>QExtOsgiServiceTracker</code>. If
   *        customizer is <code>null</code>, then this
   *        <code>QExtOsgiServiceTracker</code> will be used as the
   *        <code>QExtOsgiServiceTrackerCustomizer</code> and this
   *        <code>QExtOsgiServiceTracker</code> will call the
   *        <code>QExtOsgiServiceTrackerCustomizer</code> methods on itself.
   */
    QExtOsgiServiceTracker(QExtOsgiPluginContext* context,
                      const QExtOsgiServiceReference& reference,
                      QExtOsgiServiceTrackerCustomizer<T>* customizer = 0);

    /**
   * Create a <code>QExtOsgiServiceTracker</code> on the specified class name.
   *
   * <p>
   * Services registered under the specified class name will be tracked by
   * this <code>QExtOsgiServiceTracker</code>.
   *
   * @param context The <code>QExtOsgiPluginContext</code> against which the tracking
   *        is done.
   * @param clazz The class name of the services to be tracked.
   * @param customizer The customizer object to call when services are added,
   *        modified, or removed in this <code>QExtOsgiServiceTracker</code>. If
   *        customizer is <code>null</code>, then this
   *        <code>QExtOsgiServiceTracker</code> will be used as the
   *        <code>QExtOsgiServiceTrackerCustomizer</code> and this
   *        <code>QExtOsgiServiceTracker</code> will call the
   *        <code>QExtOsgiServiceTrackerCustomizer</code> methods on itself.
   */
    QExtOsgiServiceTracker(QExtOsgiPluginContext* context, const QString& clazz,
                      QExtOsgiServiceTrackerCustomizer<T>* customizer = 0);

    /**
   * Create a <code>QExtOsgiServiceTracker</code> on the specified
   * <code>QExtOsgiLDAPSearchFilter</code> object.
   *
   * <p>
   * Services which match the specified <code>QExtOsgiLDAPSearchFilter</code> object will be
   * tracked by this <code>QExtOsgiServiceTracker</code>.
   *
   * @param context The <code>QExtOsgiPluginContext</code> against which the tracking
   *        is done.
   * @param filter The <code>QExtOsgiLDAPSearchFilter</code> to select the services to be
   *        tracked.
   * @param customizer The customizer object to call when services are added,
   *        modified, or removed in this <code>QExtOsgiServiceTracker</code>. If
   *        customizer is null, then this <code>QExtOsgiServiceTracker</code> will be
   *        used as the <code>QExtOsgiServiceTrackerCustomizer</code> and this
   *        <code>QExtOsgiServiceTracker</code> will call the
   *        <code>QExtOsgiServiceTrackerCustomizer</code> methods on itself.
   */
    QExtOsgiServiceTracker(QExtOsgiPluginContext* context, const QExtOsgiLDAPSearchFilter& filter,
                      QExtOsgiServiceTrackerCustomizer<T>* customizer = 0);

    /**
   * Create a <code>QExtOsgiServiceTracker</code> on the class template
   * argument S.
   *
   * <p>
   * Services registered under the interface name of the class template
   * argument S will be tracked by this <code>QExtOsgiServiceTracker</code>.
   *
   * @param context The <code>QExtOsgiPluginContext</code> against which the tracking
   *        is done.
   * @param customizer The customizer object to call when services are added,
   *        modified, or removed in this <code>QExtOsgiServiceTracker</code>. If
   *        customizer is null, then this <code>QExtOsgiServiceTracker</code> will be
   *        used as the <code>QExtOsgiServiceTrackerCustomizer</code> and this
   *        <code>QExtOsgiServiceTracker</code> will call the
   *        <code>QExtOsgiServiceTrackerCustomizer</code> methods on itself.
   */
    QExtOsgiServiceTracker(QExtOsgiPluginContext* context, QExtOsgiServiceTrackerCustomizer<T>* customizer = 0);

    /**
   * Open this <code>QExtOsgiServiceTracker</code> and begin tracking services.
   *
   * <p>
   * Services which match the search criteria specified when this
   * <code>QExtOsgiServiceTracker</code> was created are now tracked by this
   * <code>QExtOsgiServiceTracker</code>.
   *
   * @throws QExtIllegalStateException If the <code>QExtOsgiPluginContext</code>
   *         with which this <code>QExtOsgiServiceTracker</code> was created is no
   *         longer valid.
   */
    virtual void open();

    /**
   * Close this <code>QExtOsgiServiceTracker</code>.
   *
   * <p>
   * This method should be called when this <code>QExtOsgiServiceTracker</code> should
   * end the tracking of services.
   *
   * <p>
   * This implementation calls getServiceReferences() to get the list
   * of tracked services to remove.
   */
    virtual void close();

    /**
   * Wait for at least one service to be tracked by this
   * <code>QExtOsgiServiceTracker</code>. This method will also return when this
   * <code>QExtOsgiServiceTracker</code> is closed.
   *
   * <p>
   * It is strongly recommended that <code>waitForService</code> is not used
   * during the calling of the <code>QExtOsgiPluginActivator</code> methods.
   * <code>QExtOsgiPluginActivator</code> methods are expected to complete in a short
   * period of time.
   *
   * <p>
   * This implementation calls getService() to determine if a service
   * is being tracked.
   *
   * @param timeout The time interval in milliseconds to wait. If zero, the
   *        method will wait indefinitely.
   * @return Returns the result of getService().
   */
    virtual T waitForService(unsigned long timeout);

    /**
   * Return a list of <code>QExtOsgiServiceReference</code>s for all services being
   * tracked by this <code>QExtOsgiServiceTracker</code>.
   *
   * @return List of <code>QExtOsgiServiceReference</code>s.
   */
    virtual QList<QExtOsgiServiceReference> getServiceReferences() const;

    /**
   * Returns a <code>QExtOsgiServiceReference</code> for one of the services being
   * tracked by this <code>QExtOsgiServiceTracker</code>.
   *
   * <p>
   * If multiple services are being tracked, the service with the highest
   * ranking (as specified in its <code>service.ranking</code> property) is
   * returned. If there is a tie in ranking, the service with the lowest
   * service ID (as specified in its <code>service.id</code> property); that
   * is, the service that was registered first is returned. This is the same
   * algorithm used by <code>QExtOsgiPluginContext::getServiceReference()</code>.
   *
   * <p>
   * This implementation calls getServiceReferences() to get the list
   * of references for the tracked services.
   *
   * @return A <code>QExtOsgiServiceReference</code> for a tracked service.
   * @throws QExtOsgiServiceException if no services are being tracked.
   */
    virtual QExtOsgiServiceReference getServiceReference() const;

    /**
   * Returns the service object for the specified
   * <code>QExtOsgiServiceReference</code> if the specified referenced service is
   * being tracked by this <code>QExtOsgiServiceTracker</code>.
   *
   * @param reference The reference to the desired service.
   * @return A service object or <code>null</code> if the service referenced
   *         by the specified <code>QExtOsgiServiceReference</code> is not being
   *         tracked.
   */
    virtual T getService(const QExtOsgiServiceReference& reference) const;

    /**
   * Return a list of service objects for all services being tracked by this
   * <code>QExtOsgiServiceTracker</code>.
   *
   * <p>
   * This implementation calls getServiceReferences() to get the list
   * of references for the tracked services and then calls
   * getService(const QExtOsgiServiceReference&) for each reference to get the
   * tracked service object.
   *
   * @return A list of service objects or an empty list if no services
   *         are being tracked.
   */
    virtual QList<T> getServices() const;

    /**
   * Returns a service object for one of the services being tracked by this
   * <code>QExtOsgiServiceTracker</code>.
   *
   * <p>
   * If any services are being tracked, this implementation returns the result
   * of calling <code>getService(getServiceReference())</code>.
   *
   * @return A service object or <code>null</code> if no services are being
   *         tracked.
   */
    virtual T getService() const;

    /**
   * Remove a service from this <code>QExtOsgiServiceTracker</code>.
   *
   * The specified service will be removed from this
   * <code>QExtOsgiServiceTracker</code>. If the specified service was being tracked
   * then the <code>QExtOsgiServiceTrackerCustomizer::removedService</code> method will
   * be called for that service.
   *
   * @param reference The reference to the service to be removed.
   */
    virtual void remove(const QExtOsgiServiceReference& reference);

    /**
   * Return the number of services being tracked by this
   * <code>QExtOsgiServiceTracker</code>.
   *
   * @return The number of services being tracked.
   */
    virtual int size() const;

    /**
   * Returns the tracking count for this <code>QExtOsgiServiceTracker</code>.
   *
   * The tracking count is initialized to 0 when this
   * <code>QExtOsgiServiceTracker</code> is opened. Every time a service is added,
   * modified or removed from this <code>QExtOsgiServiceTracker</code>, the tracking
   * count is incremented.
   *
   * <p>
   * The tracking count can be used to determine if this
   * <code>QExtOsgiServiceTracker</code> has added, modified or removed a service by
   * comparing a tracking count value previously collected with the current
   * tracking count value. If the value has not changed, then no service has
   * been added, modified or removed from this <code>QExtOsgiServiceTracker</code>
   * since the previous tracking count was collected.
   *
   * @return The tracking count for this <code>QExtOsgiServiceTracker</code> or -1 if
   *         this <code>QExtOsgiServiceTracker</code> is not open.
   */
    virtual int getTrackingCount() const;

    /**
   * Return a sorted <code>QMap</code> of the <code>QExtOsgiServiceReference</code>s and
   * service objects for all services being tracked by this
   * <code>QExtOsgiServiceTracker</code>. The map is sorted in natural order
   * of <code>QExtOsgiServiceReference</code>. That is, the last entry is the service
   * with the highest ranking and the lowest service id.
   *
   * @return A <code>QMap</code> with the <code>QExtOsgiServiceReference</code>s
   *         and service objects for all services being tracked by this
   *         <code>QExtOsgiServiceTracker</code>. If no services are being tracked,
   *         then the returned map is empty.
   */
    virtual QMap<QExtOsgiServiceReference, T> getTracked() const;

    /**
   * Return if this <code>QExtOsgiServiceTracker</code> is empty.
   *
   * @return <code>true</code> if this <code>QExtOsgiServiceTracker</code> is not tracking any
   *         services.
   */
    virtual bool isEmpty() const;

protected:

    /**
   * Default implementation of the
   * <code>QExtOsgiServiceTrackerCustomizer::addingService</code> method.
   *
   * <p>
   * This method is only called when this <code>QExtOsgiServiceTracker</code> has been
   * constructed with a <code>null</code> QExtOsgiServiceTrackerCustomizer argument.
   *
   * <p>
   * This implementation returns the result of calling <code>getService</code>
   * on the <code>QExtOsgiPluginContext</code> with which this
   * <code>QExtOsgiServiceTracker</code> was created passing the specified
   * <code>QExtOsgiServiceReference</code>.
   * <p>
   * This method can be overridden in a subclass to customize the service
   * object to be tracked for the service being added. In that case, take care
   * not to rely on the default implementation of
   * \link removedService(const QExtOsgiServiceReference&, T service) removedService\endlink
   * to unget the service.
   *
   * @param reference The reference to the service being added to this
   *        <code>QExtOsgiServiceTracker</code>.
   * @return The service object to be tracked for the service added to this
   *         <code>ctlServiceTracker</code>.
   * @see QExtOsgiServiceTrackerCustomizer::addingService(const QExtOsgiServiceReference&)
   */
    T addingService(const QExtOsgiServiceReference& reference);

    /**
   * Default implementation of the
   * <code>QExtOsgiServiceTrackerCustomizer::modifiedService</code> method.
   *
   * <p>
   * This method is only called when this <code>QExtOsgiServiceTracker</code> has been
   * constructed with a <code>null</code> QExtOsgiServiceTrackerCustomizer argument.
   *
   * <p>
   * This implementation does nothing.
   *
   * @param reference The reference to modified service.
   * @param service The service object for the modified service.
   * @see QExtOsgiServiceTrackerCustomizer::modifiedService(const QExtOsgiServiceReference&, QObject*)
   */
    void modifiedService(const QExtOsgiServiceReference& reference, T service);

    /**
   * Default implementation of the
   * <code>QExtOsgiServiceTrackerCustomizer::removedService</code> method.
   *
   * <p>
   * This method is only called when this <code>QExtOsgiServiceTracker</code> has been
   * constructed with a <code>null</code> QExtOsgiServiceTrackerCustomizer argument.
   *
   * <p>
   * This implementation calls <code>ungetService</code>, on the
   * <code>QExtOsgiPluginContext</code> with which this <code>QExtOsgiServiceTracker</code>
   * was created, passing the specified <code>QExtOsgiServiceReference</code>.
   * <p>
   * This method can be overridden in a subclass. If the default
   * implementation of \link addingService(const QExtOsgiServiceReference&) addingService\endlink
   * method was used, this method must unget the service.
   *
   * @param reference The reference to removed service.
   * @param service The service object for the removed service.
   * @see QExtOsgiServiceTrackerCustomizer::removedService(const ServiceReference&, QObject*)
   */
    void removedService(const QExtOsgiServiceReference& reference, T service);

private:

    typedef QExtOsgiServiceTracker<S,T> ServiceTracker;
    typedef QExtOsgiTrackedService<S,T> TrackedService;
    typedef QExtOsgiServiceTrackerPrivate<S,T> ServiceTrackerPrivate;
    typedef QExtOsgiServiceTrackerCustomizer<T> ServiceTrackerCustomizer;

    friend class QExtOsgiTrackedService<S,T>;
    friend class QExtOsgiServiceTrackerPrivate<S,T>;

    inline ServiceTrackerPrivate* d_func()
    {
        return reinterpret_cast<ServiceTrackerPrivate*>(qGetPtrHelper(d_ptr));
    }

    inline const ServiceTrackerPrivate* d_func() const
    {
        return reinterpret_cast<const ServiceTrackerPrivate*>(qGetPtrHelper(d_ptr));
    }

    const QScopedPointer<ServiceTrackerPrivate> d_ptr;
};


#include "qextOsgiServiceTracker_p.h"
#include "qextOsgiTrackedService_p.h"
#include "qextOsgiServiceException.h"
#include "qextOsgiPluginConstants.h"
#include "qextOsgiPluginContext.h"

#include <QVarLengthArray>
#include <QDebug>

#include <stdexcept>
#include <limits>

//----------------------------------------------------------------------------
template<class S, class T>
QExtOsgiServiceTracker<S,T>::~QExtOsgiServiceTracker()
{
}

//----------------------------------------------------------------------------
template<class S, class T>
QExtOsgiServiceTracker<S,T>::QExtOsgiServiceTracker(QExtOsgiPluginContext* context,
                                           const QExtOsgiServiceReference& reference,
                                           ServiceTrackerCustomizer* customizer)
    : d_ptr(new ServiceTrackerPrivate(this, context, reference, customizer))
{
}

//----------------------------------------------------------------------------
template<class S, class T>
QExtOsgiServiceTracker<S,T>::QExtOsgiServiceTracker(QExtOsgiPluginContext* context, const QString& clazz,
                                           ServiceTrackerCustomizer* customizer)
    : d_ptr(new ServiceTrackerPrivate(this, context, clazz, customizer))
{
}

//----------------------------------------------------------------------------
template<class S, class T>
QExtOsgiServiceTracker<S,T>::QExtOsgiServiceTracker(QExtOsgiPluginContext* context, const QExtOsgiLDAPSearchFilter& filter,
                                           ServiceTrackerCustomizer* customizer)
    : d_ptr(new ServiceTrackerPrivate(this, context, filter, customizer))
{
}

//----------------------------------------------------------------------------
template<class S, class T>
QExtOsgiServiceTracker<S,T>::QExtOsgiServiceTracker(QExtOsgiPluginContext *context, QExtOsgiServiceTrackerCustomizer<T> *customizer)
    : d_ptr(new ServiceTrackerPrivate(this, context, qobject_interface_iid<S>(), customizer))
{
    const char* clazz = qobject_interface_iid<S>();
    if (clazz == 0) throw QExtOsgiServiceException("The service interface class has no Q_DECLARE_INTERFACE macro");
}

//----------------------------------------------------------------------------
template<class S, class T>
void QExtOsgiServiceTracker<S,T>::open()
{
    Q_D(ServiceTracker);
    QSharedPointer<TrackedService> t;
    {
        QMutexLocker lock(&d->mutex);
        if (d->trackedService)
        {
            return;
        }

        if (d->DEBUG_FLAG)
        {
            qDebug() << "qextOsgiServiceTracker<S,T>::open: " << d->filter;
        }

        t = QSharedPointer<TrackedService>(
            new TrackedService(this, d->customizer));
        {
            QMutexLocker lockT(t.data());
            try {
                d->context->connectServiceListener(t.data(), "serviceChanged", d->listenerFilter);
                QList<QExtOsgiServiceReference> references;
                if (!d->trackClass.isEmpty())
                {
                    references = d->getInitialReferences(d->trackClass, QString());
                }
                else
                {
                    if (!d->trackReference.getPlugin().isNull())
                    {
                        references.push_back(d->trackReference);
                    }
                    else
                    { /* user supplied filter */
                        references = d->getInitialReferences(QString(),
                                                             (d->listenerFilter.isNull()) ? d->filter.toString() : d->listenerFilter);
                    }
                }
                /* set tracked with the initial references */
                t->setInitial(references);
            }
            catch (const QExtInvalidArgumentException& e)
            {
                throw QExtRuntimeException(QString("unexpected QExtInvalidArgumentException exception: %1").arg(e.what()));
            }
        }
        d->trackedService = t;
    }
    /* Call tracked outside of synchronized region */
    t->trackInitial(); /* process the initial references */
}

//----------------------------------------------------------------------------
template<class S, class T>
void QExtOsgiServiceTracker<S,T>::close()
{
    Q_D(ServiceTracker);
    QSharedPointer<TrackedService> outgoing;
    QList<QExtOsgiServiceReference> references;
    {
        QMutexLocker lock(&d->mutex);
        outgoing = d->trackedService;
        if (outgoing.isNull())
        {
            return;
        }
        if (d->DEBUG_FLAG)
        {
            qDebug() << "qextOsgiServiceTracker<S,T>::close:" << d->filter;
        }
        outgoing->close();
        references = getServiceReferences();
        d->trackedService.clear();;
        try
        {
            d->context->disconnectServiceListener(outgoing.data(), "serviceChanged");
        }
        catch (const QExtIllegalStateException& /*e*/)
        {
            /* In case the context was stopped. */
        }
    }
    d->modified(); /* clear the cache */
    {
        QMutexLocker lockT(outgoing.data());
        outgoing->wakeAll(); /* wake up any waiters */
    }
    foreach (QExtOsgiServiceReference ref, references)
    {
        outgoing->untrack(ref, QExtOsgiServiceEvent());
    }

    if (d->DEBUG_FLAG)
    {
        QMutexLocker lock(&d->mutex);
        if ((d->cachedReference.getPlugin().isNull()) && (d->cachedService == 0))
        {
            qDebug() << "qextOsgiServiceTracker<S,T>::close[cached cleared]:"
                     << d->filter;
        }
    }
}

//----------------------------------------------------------------------------
template<class S, class T>
T QExtOsgiServiceTracker<S,T>::waitForService(unsigned long timeout)
{
    Q_D(ServiceTracker);
    T object = getService();
    while (object == 0)
    {
        QSharedPointer<TrackedService> t = d->tracked();
        if (t.isNull())
        { /* if ServiceTracker is not open */
            return 0;
        }
        {
            QMutexLocker lockT(t.data());
            if (t->size() == 0)
            {
                t->wait(timeout);
            }
        }
        object = getService();
        if (timeout > 0)
        {
            return object;
        }
    }
    return object;
}

//----------------------------------------------------------------------------
template<class S, class T>
QList<QExtOsgiServiceReference> QExtOsgiServiceTracker<S,T>::getServiceReferences() const
{
    Q_D(const ServiceTracker);
    QSharedPointer<TrackedService> t = d->tracked();
    if (t.isNull())
    { /* if ServiceTracker is not open */
        return QList<QExtOsgiServiceReference>();
    }
    {
        QMutexLocker lockT(t.data());
        return d->getServiceReferences_unlocked(t.data());
    }
}

//----------------------------------------------------------------------------
template<class S, class T>
QExtOsgiServiceReference QExtOsgiServiceTracker<S,T>::getServiceReference() const
{
    Q_D(const ServiceTracker);
    QExtOsgiServiceReference reference(0);
    {
        QMutexLocker lock(&d->mutex);
        reference = d->cachedReference;
    }
    if (!reference.getPlugin().isNull())
    {
        if (d->DEBUG_FLAG)
        {
            qDebug() << "qextOsgiServiceTracker<S,T>::getServiceReference[cached]:"
                     << d->filter;
        }
        return reference;
    }
    if (d->DEBUG_FLAG)
    {
        qDebug() << "qextOsgiServiceTracker<S,T>::getServiceReference:" << d->filter;
    }
    QList<QExtOsgiServiceReference> references = getServiceReferences();
    int length = references.size();
    if (length == 0)
    { /* if no service is being tracked */
        throw QExtOsgiServiceException("No service is being tracked");
    }
    int index = 0;
    if (length > 1)
    { /* if more than one service, select highest ranking */
        QVarLengthArray<int, 10> rankings(length);
        int count = 0;
        int maxRanking = std::numeric_limits<int>::min();
        for (int i = 0; i < length; i++)
        {
            bool ok = false;
            int ranking = references[i].getProperty(QExtOsgiPluginConstants::SERVICE_RANKING).toInt(&ok);
            if (!ok) ranking = 0;

            rankings[i] = ranking;
            if (ranking > maxRanking)
            {
                index = i;
                maxRanking = ranking;
                count = 1;
            }
            else
            {
                if (ranking == maxRanking)
                {
                    count++;
                }
            }
        }
        if (count > 1)
        { /* if still more than one service, select lowest id */
            qlonglong minId = std::numeric_limits<qlonglong>::max();
            for (int i = 0; i < length; i++)
            {
                if (rankings[i] == maxRanking)
                {
                    qlonglong id = references[i].getProperty(QExtOsgiPluginConstants::SERVICE_ID).toLongLong();
                    if (id < minId)
                    {
                        index = i;
                        minId = id;
                    }
                }
            }
        }
    }

    {
        QMutexLocker lock(&d->mutex);
        d->cachedReference = references[index];
        return d->cachedReference;
    }
}

//----------------------------------------------------------------------------
template<class S, class T>
T QExtOsgiServiceTracker<S,T>::getService(const QExtOsgiServiceReference& reference) const
{
    Q_D(const ServiceTracker);
    QSharedPointer<TrackedService> t = d->tracked();
    if (t.isNull())
    { /* if ServiceTracker is not open */
        return 0;
    }
    {
        QMutexLocker lockT(t.data());
        return t->getCustomizedObject(reference);
    }
}

//----------------------------------------------------------------------------
template<class S, class T>
QList<T> QExtOsgiServiceTracker<S,T>::getServices() const
{
    Q_D(const ServiceTracker);
    QSharedPointer<TrackedService> t = d->tracked();
    if (t.isNull())
    { /* if ServiceTracker is not open */
        return QList<T>();
    }
    {
        QMutexLocker lockT(t.data());
        QList<QExtOsgiServiceReference> references = d->getServiceReferences_unlocked(t.data());
        QList<T> objects;
        foreach (QExtOsgiServiceReference ref, references)
        {
            //objects << getService(ref);
            objects << t->getCustomizedObject(ref);
        }
        return objects;
    }
}

//----------------------------------------------------------------------------
template<class S, class T>
T QExtOsgiServiceTracker<S,T>::getService() const
{
    Q_D(const ServiceTracker);
    T service = d->cachedService;
    if (service != 0)
    {
        if (d->DEBUG_FLAG)
        {
            qDebug() << "qextOsgiServiceTracker<S,T>::getService[cached]:"
                     << d->filter;
        }
        return service;
    }
    if (d->DEBUG_FLAG)
    {
        qDebug() << "qextOsgiServiceTracker<S,T>::getService:" << d->filter;
    }

    try
    {
        QExtOsgiServiceReference reference = getServiceReference();
        if (reference.getPlugin().isNull())
        {
            return 0;
        }
        return d->cachedService = getService(reference);
    }
    catch (const QExtOsgiServiceException&)
    {
        return 0;
    }
}

//----------------------------------------------------------------------------
template<class S, class T>
void QExtOsgiServiceTracker<S,T>::remove(const QExtOsgiServiceReference& reference)
{
    Q_D(ServiceTracker);
    QSharedPointer<TrackedService> t = d->tracked();
    if (t.isNull())
    { /* if ServiceTracker is not open */
        return;
    }
    t->untrack(reference, QExtOsgiServiceEvent());
}

//----------------------------------------------------------------------------
template<class S, class T>
int QExtOsgiServiceTracker<S,T>::size() const
{
    Q_D(const ServiceTracker);
    QSharedPointer<TrackedService> t = d->tracked();
    if (t.isNull())
    { /* if ServiceTracker is not open */
        return 0;
    }
    {
        QMutexLocker lockT(t.data());
        return t->size();
    }
}

//----------------------------------------------------------------------------
template<class S, class T>
int QExtOsgiServiceTracker<S,T>::getTrackingCount() const
{
    Q_D(const ServiceTracker);
    QSharedPointer<TrackedService> t = d->tracked();
    if (t.isNull())
    { /* if ServiceTracker is not open */
        return -1;
    }
    {
        QMutexLocker lockT(t.data());
        return t->getTrackingCount();
    }
}

//----------------------------------------------------------------------------
template<class S, class T>
QMap<QExtOsgiServiceReference, T> QExtOsgiServiceTracker<S,T>::getTracked() const
{
    QMap<QExtOsgiServiceReference, T> map;
    Q_D(const ServiceTracker);
    QSharedPointer<TrackedService> t = d->tracked();
    if (t.isNull())
    { /* if ServiceTracker is not open */
        return map;
    }
    {
        QMutexLocker lockT(t.data());
        return t->copyEntries(map);
    }
}

//----------------------------------------------------------------------------
template<class S, class T>
bool QExtOsgiServiceTracker<S,T>::isEmpty() const
{
    Q_D(const ServiceTracker);
    QSharedPointer<TrackedService> t = d->tracked();
    if (t.isNull())
    { /* if ServiceTracker is not open */
        return true;
    }
    {
        QMutexLocker lockT(t.data());
        return t->isEmpty();
    }
}

//----------------------------------------------------------------------------
template<class S, class T>
T QExtOsgiServiceTracker<S,T>::addingService(const QExtOsgiServiceReference& reference)
{
    Q_D(ServiceTracker);
    return qobject_cast<T>(d->context->getService(reference));
}

//----------------------------------------------------------------------------
template<class S, class T>
void QExtOsgiServiceTracker<S,T>::modifiedService(const QExtOsgiServiceReference& reference, T service)
{
    Q_UNUSED(reference)
    Q_UNUSED(service)
    /* do nothing */
}

//----------------------------------------------------------------------------
template<class S, class T>
void QExtOsgiServiceTracker<S,T>::removedService(const QExtOsgiServiceReference& reference, T service)
{
    Q_UNUSED(service)

    Q_D(ServiceTracker);
    d->context->ungetService(reference);
}


#endif // _QEXTOSGISERVICETRACKER_H
