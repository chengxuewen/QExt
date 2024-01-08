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
#include <qextOsgiServiceEvent.h>
#include <qextOsgiPluginContext.h>
// #include <qextOsgiTrackedService.h>
#include <qextOsgiPluginConstants.h>
#include <qextOsgiServiceReference.h>
#include <qextOsgiLDAPSearchFilter.h>
#include <qextOsgiServiceException.h>
#include <qextOsgiServiceReference.h>
#include <qextOsgiDebugOptionsListener.h>
#include <qextOsgiPluginAbstractTracked.h>
#include <qextOsgiTrackedServiceListener.h>
#include <qextOsgiServiceTrackerCustomizer.h>

#include <QVarLengthArray>
#include <QSharedPointer>
#include <QMutexLocker>
#include <QMutex>
#include <QDebug>

#include <limits>

template<typename S, typename T> class QExtOsgiTrackedService;
template<typename S, typename T> class QExtOsgiServiceTrackerPrivate;
class QExtOsgiPluginContext;

/**
 * @ingroup Osgi
 *
 * The <code>QExtOsgiServiceTracker</code> class simplifies using services from the Framework's service registry.
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
 * @tparam S The type of the service being tracked. The type must be an assignable datatype. Further, if the
 *         <code>QExtOsgiServiceTracker(QExtOsgiPluginContext*, QExtOsgiServiceTrackerCustomizer<T>*)</code>
 *         constructor is used, the type must have an associated interface id via
 *         Q_DECLARE_INTERFACE.
 * @tparam T The type of the tracked object. The type must be an assignable datatype, provide a boolean conversion
 *         function, and provide a constructor and an assignment operator which can handle 0 as an argument.
 * @remarks This class is thread safe.
 */
template<typename S = QObject *, typename T = S>
class QExtOsgiServiceTracker : protected QExtOsgiServiceTrackerCustomizer<T>
{
    typedef QExtOsgiServiceTracker<S, T> ServiceTracker;
    typedef QExtOsgiTrackedService<S, T> TrackedService;
    typedef QExtOsgiServiceTrackerPrivate<S, T> ServiceTrackerPrivate;
    typedef QExtOsgiServiceTrackerCustomizer<T> ServiceTrackerCustomizer;
public:
    ~QExtOsgiServiceTracker() {}

    /**
     * @brief reate a <code>QExtOsgiServiceTracker</code> on the specified <code>QExtOsgiServiceReference</code>.
     *
     * <p>
     * The service referenced by the specified <code>QExtOsgiServiceReference</code> will be tracked by this
     * <code>QExtOsgiServiceTracker</code>.
     *
     * @param context The <code>QExtOsgiPluginContext</code> against which the tracking is done.
     * @param reference The <code>QExtOsgiServiceReference</code> for the service to be tracked.
     * @param customizer The customizer object to call when services are added, modified, or removed in this
     *        <code>QExtOsgiServiceTracker</code>. If customizer is <code>null</code>, then this
     *        <code>QExtOsgiServiceTracker</code> will be used as the
     *        <code>QExtOsgiServiceTrackerCustomizer</code> and this
     *        <code>QExtOsgiServiceTracker</code> will call the
     *        <code>QExtOsgiServiceTrackerCustomizer</code> methods on itself.
     */
    QExtOsgiServiceTracker(QExtOsgiPluginContext *context,
                           const QExtOsgiServiceReference &reference,
                           QExtOsgiServiceTrackerCustomizer<T> *customizer = QEXT_NULLPTR)
        : d_ptr(new ServiceTrackerPrivate(this, context, reference, customizer))
    {
    }

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
    QExtOsgiServiceTracker(QExtOsgiPluginContext *context, const QString &clazz,
                           QExtOsgiServiceTrackerCustomizer<T> *customizer = QEXT_NULLPTR)
        : d_ptr(new ServiceTrackerPrivate(this, context, clazz, customizer))
    {
    }

    QExtOsgiServiceTracker(QExtOsgiPluginContext *context, const QExtOsgiLDAPSearchFilter &filter,
                           QExtOsgiServiceTrackerCustomizer<T> *customizer = QEXT_NULLPTR)
        : d_ptr(new ServiceTrackerPrivate(this, context, filter, customizer))
    {
    }

    /**
     * @brief Create a <code>QExtOsgiServiceTracker</code> on the class template argument S.
     *
     * <p>
     * Services registered under the interface name of the class template argument S will be tracked by this
     * <code>QExtOsgiServiceTracker</code>.
     *
     * @param context The <code>QExtOsgiPluginContext</code> against which the tracking is done.
     * @param customizer The customizer object to call when services are added, modified, or removed in this
     *        <code>QExtOsgiServiceTracker</code>. If customizer is null, then this <code>QExtOsgiServiceTracker</code>
     *        will be used as the <code>QExtOsgiServiceTrackerCustomizer</code> and this <code>QExtOsgiServiceTracker</code>
     *        will call the <code>QExtOsgiServiceTrackerCustomizer</code> methods on itself.
     */
    QExtOsgiServiceTracker(QExtOsgiPluginContext *context,
                           QExtOsgiServiceTrackerCustomizer<T> *customizer = QEXT_NULLPTR)
        : d_ptr(new ServiceTrackerPrivate(this, context, qobject_interface_iid<S>(), customizer))
    {
        const char *clazz = qobject_interface_iid<S>();
        if (clazz == 0)
        {
            throw QExtOsgiServiceException("The service interface class has no Q_DECLARE_INTERFACE macro");
        }
    }

    /**
     * @brief Open this <code>QExtOsgiServiceTracker</code> and begin tracking services.
     *
     * <p>
     * Services which match the search criteria specified when this <code>QExtOsgiServiceTracker</code> was created are
     * now tracked by this <code>QExtOsgiServiceTracker</code>.
     *
     * @throws QExtIllegalStateException If the <code>QExtOsgiPluginContext</code> with which this
     *         <code>QExtOsgiServiceTracker</code> was created is no longer valid.
     */
    virtual void open()
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

            t = QSharedPointer<TrackedService>(new TrackedService(this, d->customizer));
            {
                QMutexLocker lockT(t.data());
                try
                {
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
                        else // user supplied filter
                        {
                            references = d->getInitialReferences(QString(),
                                                                 (d->listenerFilter.isNull()) ? d->filter.toString()
                                                                                              : d->listenerFilter);
                        }
                    }
                    /* set tracked with the initial references */
                    t->setInitial(references);
                }
                catch (const QExtInvalidArgumentException& e)
                {
                    const QString what = QString("unexpected QExtInvalidArgumentException exception: %1").arg(e.what());
                    throw QExtRuntimeException(what);
                }
            }
            d->trackedService = t;
        }
        /* Call tracked outside of synchronized region */
        t->trackInitial(); /* process the initial references */
    }

    /**
     * @brief Close this <code>QExtOsgiServiceTracker</code>.
     *
     * <p>
     * This method should be called when this <code>QExtOsgiServiceTracker</code> should end the tracking of services.
     *
     * <p>
     * This implementation calls getServiceReferences() to get the list of tracked services to remove.
     */
    virtual void close()
    {
        Q_D(ServiceTracker);
        QSharedPointer<TrackedService> outgoing;
        QList<QExtOsgiServiceReference> references;
        {
            QMutexLocker locker(&d->mutex);
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
            catch (const QExtIllegalStateException &/*e*/)
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

    /**
     * @brief Wait for at least one service to be tracked by this <code>QExtOsgiServiceTracker</code>.
     * This method will also return when this <code>QExtOsgiServiceTracker</code> is closed.
     *
     * <p>
     * It is strongly recommended that <code>waitForService</code> is not used during the calling of the
     * <code>QExtOsgiPluginActivator</code> methods. <code>QExtOsgiPluginActivator</code> methods are expected to
     * complete in a short period of time.
     *
     * <p>
     * This implementation calls getService() to determine if a service is being tracked.
     *
     * @param timeout The time interval in milliseconds to wait. If zero, the method will wait indefinitely.
     * @return Returns the result of getService().
     */
    virtual T waitForService(unsigned long timeout)
    {
        Q_D(ServiceTracker);
        T object = this->getService();
        while (object == 0)
        {
            QSharedPointer<TrackedService> t = d->tracked();
            if (t.isNull()) // if ServiceTracker is not open
            {
                return 0;
            }
            {
                QMutexLocker lockT(t.data());
                if (t->size() == 0)
                {
                    t->wait(timeout);
                }
            }
            object = this->getService();
            if (timeout > 0)
            {
                return object;
            }
        }
        return object;
    }

    /**
     * @brief Return a list of <code>QExtOsgiServiceReference</code>s for all services being tracked by this
     * <code>QExtOsgiServiceTracker</code>.
     *
     * @return List of <code>QExtOsgiServiceReference</code>s.
     */
    virtual QList<QExtOsgiServiceReference> getServiceReferences() const
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

    /**
     * @brief Returns a <code>QExtOsgiServiceReference</code> for one of the services being tracked by this
     * <code>QExtOsgiServiceTracker</code>.
     *
     * <p>
     * If multiple services are being tracked, the service with the highest ranking (as specified in its
     * <code>service.ranking</code> property) is returned. If there is a tie in ranking, the service with the lowest
     * service ID (as specified in its <code>service.id</code> property); that is, the service that was registered
     * first is returned. This is the same algorithm used by <code>QExtOsgiPluginContext::getServiceReference()</code>.
     *
     * <p>
     * This implementation calls getServiceReferences() to get the list of references for the tracked services.
     *
     * @return A <code>QExtOsgiServiceReference</code> for a tracked service.
     * @throws QExtOsgiServiceException if no services are being tracked.
     */
    virtual QExtOsgiServiceReference getServiceReference() const
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

    /**
     * @brief Returns the service object for the specified <code>QExtOsgiServiceReference</code> if the specified
     * referenced service is being tracked by this <code>QExtOsgiServiceTracker</code>.
     *
     * @param reference The reference to the desired service.
     * @return A service object or <code>null</code> if the service referenced by the specified
     * <code>QExtOsgiServiceReference</code> is not being tracked.
     */
    virtual T getService(const QExtOsgiServiceReference &reference) const
    {
        Q_D(const ServiceTracker);
        QSharedPointer<TrackedService> t = d->tracked();
        if (t.isNull()) // if ServiceTracker is not open
        {
            return 0;
        }
        {
            QMutexLocker lockT(t.data());
            return t->getCustomizedObject(reference);
        }
    }

    /**
     * @brief Return a list of service objects for all services being tracked by this <code>QExtOsgiServiceTracker</code>.
     *
     * <p>
     * This implementation calls getServiceReferences() to get the list of references for the tracked services and then
     * calls getService(const QExtOsgiServiceReference&) for each reference to get the tracked service object.
     *
     * @return A list of service objects or an empty list if no services are being tracked.
     */
    virtual QList<T> getServices() const
    {
        Q_D(const ServiceTracker);
        QSharedPointer<TrackedService> t = d->tracked();
        if (t.isNull()) // if ServiceTracker is not open
        {
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

    /**
     * @brief Returns a service object for one of the services being tracked by this <code>QExtOsgiServiceTracker</code>.
     *
     * <p>
     * If any services are being tracked, this implementation returns the result of calling
     * <code>getService(getServiceReference())</code>.
     *
     * @return A service object or <code>null</code> if no services are being tracked.
     */
    virtual T getService() const
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

    /**
     * @brief Remove a service from this <code>QExtOsgiServiceTracker</code>.
     *
     * The specified service will be removed from this <code>QExtOsgiServiceTracker</code>.
     * If the specified service was being tracked then the <code>QExtOsgiServiceTrackerCustomizer::removedService</code>
     * method will be called for that service.
     *
     * @param The reference to the service to be removed.
     */
    virtual void remove(const QExtOsgiServiceReference &reference)
    {
        Q_D(ServiceTracker);
        QSharedPointer<TrackedService> t = d->tracked();
        if (t.isNull()) // if ServiceTracker is not open
        {
            return;
        }
        t->untrack(reference, QExtOsgiServiceEvent());
    }

    /**
     * @brief Return the number of services being tracked by this <code>QExtOsgiServiceTracker</code>.
     *
     * @return The number of services being tracked.
     */
    virtual int size() const
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

    /**
     * @brief Returns the tracking count for this <code>QExtOsgiServiceTracker</code>.
     *
     * The tracking count is initialized to 0 when this <code>QExtOsgiServiceTracker</code> is opened. Every time a
     * service is added, modified or removed from this <code>QExtOsgiServiceTracker</code>, the tracking count is incremented.
     *
     * <p>
     * The tracking count can be used to determine if this <code>QExtOsgiServiceTracker</code> has added, modified or
     * removed a service by comparing a tracking count value previously collected with the current tracking count value.
     * If the value has not changed, then no service has been added, modified or removed from this
     * <code>QExtOsgiServiceTracker</code> since the previous tracking count was collected.
     *
     * @return The tracking count for this <code>QExtOsgiServiceTracker</code> or -1 if
     * this <code>QExtOsgiServiceTracker</code> is not open.
     */
    virtual int getTrackingCount() const
    {
        Q_D(const ServiceTracker);
        QSharedPointer<TrackedService> t = d->tracked();
        if (t.isNull()) // if ServiceTracker is not open
        {
            return -1;
        }
        {
            QMutexLocker lockT(t.data());
            return t->getTrackingCount();
        }
    }

    /**
     * @brief Return a sorted <code>QMap</code> of the <code>QExtOsgiServiceReference</code>s and service objects for
     * all services being tracked by this <code>QExtOsgiServiceTracker</code>. The map is sorted in natural order
     * of <code>QExtOsgiServiceReference</code>. That is, the last entry is the service with the highest ranking and
     * the lowest service id.
     *
     * @return A <code>QMap</code> with the <code>QExtOsgiServiceReference</code>s and service objects for all services
     * being tracked by this <code>QExtOsgiServiceTracker</code>. If no services are being tracked, then the returned
     * map is empty.
     */
    virtual QMap<QExtOsgiServiceReference, T> getTracked() const
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

    /**
     * @brief Return if this <code>QExtOsgiServiceTracker</code> is empty.
     * @return <code>true</code> if this <code>QExtOsgiServiceTracker</code> is not tracking any services.
     */
    virtual bool isEmpty() const
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

protected:
    /**
     * @brief Default implementation of the
     * <code>QExtOsgiServiceTrackerCustomizer::addingService</code> method.
     *
     * <p>
     * This method is only called when this <code>QExtOsgiServiceTracker</code> has been constructed with a
     * <code>null</code> QExtOsgiServiceTrackerCustomizer argument.
     *
     * <p>
     * This implementation returns the result of calling <code>getService</code>
     * on the <code>QExtOsgiPluginContext</code> with which this
     * <code>QExtOsgiServiceTracker</code> was created passing the specified
     * <code>QExtOsgiServiceReference</code>.
     *
     * <p>
     * This method can be overridden in a subclass to customize the service object to be tracked for the service being
     * added. In that case, take care not to rely on the default implementation of
     * \link removedService(const QExtOsgiServiceReference&, T service) removedService\endlink to unget the service.
     *
     * @param reference The reference to the service being added to this <code>QExtOsgiServiceTracker</code>.
     * @return The service object to be tracked for the service added to this <code>ctlServiceTracker</code>.
     * @see QExtOsgiServiceTrackerCustomizer::addingService(const QExtOsgiServiceReference&)
     */
    T addingService(const QExtOsgiServiceReference &reference)
    {
        Q_D(ServiceTracker);
        return qobject_cast<T>(d->context->getService(reference));
    }

    /**
     * @brief Default implementation of the
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
    void modifiedService(const QExtOsgiServiceReference &reference, T service)
    {
        Q_UNUSED(reference)
        Q_UNUSED(service)
        /* do nothing */
    }

    /**
     * @brief Default implementation of the
     * <code>QExtOsgiServiceTrackerCustomizer::removedService</code> method.
     *
     * <p>
     * This method is only called when this <code>QExtOsgiServiceTracker</code> has been
     * constructed with a <code>null</code> QExtOsgiServiceTrackerCustomizer argument.
     * <p>
     * This implementation calls <code>ungetService</code>, on the
     * <code>QExtOsgiPluginContext</code> with which this <code>QExtOsgiServiceTracker</code>
     * was created, passing the specified <code>QExtOsgiServiceReference</code>.
     * <p>
     * This method can be overridden in a subclass. If the default
     * implementation of @link addingService(const QExtOsgiServiceReference&) addingService\endlink
     * method was used, this method must unget the service.
     *
     * @param reference The reference to removed service.
     * @param service The service object for the removed service.
     * @see QExtOsgiServiceTrackerCustomizer::removedService(const ServiceReference&, QObject*)
     */
    void removedService(const QExtOsgiServiceReference &reference, T service)
    {
        Q_UNUSED(service)

        Q_D(ServiceTracker);
        d->context->ungetService(reference);
    }

private:
    friend class QExtOsgiTrackedService<S, T>;
    friend class QExtOsgiServiceTrackerPrivate<S, T>;

    inline ServiceTrackerPrivate *d_func()
    {
        return reinterpret_cast<ServiceTrackerPrivate *>(qGetPtrHelper(d_ptr));
    }

    inline const ServiceTrackerPrivate *d_func() const
    {
        return reinterpret_cast<const ServiceTrackerPrivate *>(qGetPtrHelper(d_ptr));
    }

    const QScopedPointer<ServiceTrackerPrivate> d_ptr;
};


/***********************************************************************************************************************
** QExtOsgiServiceTrackerPrivate
***********************************************************************************************************************/
/**
 * @ingroup Osgi
 */
template<class S, class T>
class QExtOsgiServiceTrackerPrivate
{

public:
    QExtOsgiServiceTrackerPrivate(QExtOsgiServiceTracker<S, T> *st,
                                  QExtOsgiPluginContext *context,
                                  const QExtOsgiServiceReference &reference,
                                  QExtOsgiServiceTrackerCustomizer<T> *customizer)
        : context(context)
        , customizer(customizer)
        , trackReference(reference)
        , trackedService(0)
        , cachedReference(0)
        , cachedService(0)
        , q_ptr(st)
    {
        this->customizer = customizer ? customizer : q_func();
        this->listenerFilter = QString("(") + QExtOsgiPluginConstants::SERVICE_ID +
                               "=" + reference.getProperty(QExtOsgiPluginConstants::SERVICE_ID).toString() + ")";
        try
        {
            this->filter = QExtOsgiLDAPSearchFilter(listenerFilter);
        }
        catch (const QExtInvalidArgumentException& e)
        {
            /* we could only get this exception if the ServiceReference was invalid */
            QExtInvalidArgumentException ia(QString("unexpected QExtInvalidArgumentException exception: %1").arg(e.what()));
            throw ia;
        }
    }

    QExtOsgiServiceTrackerPrivate(QExtOsgiServiceTracker<S,T> *st,
                                  QExtOsgiPluginContext* context, const QString &clazz,
                                  QExtOsgiServiceTrackerCustomizer<T> *customizer)
        : context(context)
        , customizer(customizer)
        , trackClass(clazz)
        , trackReference(0)
        , trackedService(0)
        , cachedReference(0)
        , cachedService(0)
        , q_ptr(st)
    {
        this->customizer = customizer ? customizer : q_func();
        this->listenerFilter = QString("(") + QExtOsgiPluginConstants::OBJECTCLASS + "=" + clazz + ")";
        try
        {
            this->filter = QExtOsgiLDAPSearchFilter(listenerFilter);
        }
        catch (const QExtInvalidArgumentException& e)
        {
            /* we could only get this exception if the clazz argument was malformed */
            QExtInvalidArgumentException ia(QString("unexpected QExtInvalidArgumentException exception: %1").arg(e.what()));
            throw ia;
        }
    }

    QExtOsgiServiceTrackerPrivate(QExtOsgiServiceTracker<S,T>* st,
                                  QExtOsgiPluginContext* context, const QExtOsgiLDAPSearchFilter& filter,
                                  QExtOsgiServiceTrackerCustomizer<T>* customizer)
        : context(context)
        , filter(filter)
        , customizer(customizer)
        , listenerFilter(filter.toString())
        , trackReference(0)
        , trackedService(0)
        , cachedReference(0)
        , cachedService(0)
        , q_ptr(st)
    {
        this->customizer = customizer ? customizer : q_func();
        if (context == 0)
        {
            throw QExtInvalidArgumentException("The plugin context cannot be null.");
        }
    }

    ~QExtOsgiServiceTrackerPrivate() {}

    /**
     * @brief Returns the list of initial <code>QExtOsgiServiceReference</code>s that will be tracked by this
     * <code>QExtOsgiServiceTracker</code>.
     *
     * @param className The class name with which the service was registered, or <code>null</code> for all services.
     * @param filterString The filter criteria or <code>null</code> for all services.
     * @return The list of initial <code>QExtOsgiServiceReference</code>s.
     * @throws QExtInvalidArgumentException If the specified filterString has an invalid syntax.
     */
    QList<QExtOsgiServiceReference> getInitialReferences(const QString &className,
                                                         const QString &filterString)
    {
        return context->getServiceReferences(className, filterString);
    }

    QList<QExtOsgiServiceReference> getServiceReferences_unlocked(QExtOsgiTrackedService<S,T>* t) const
    {
        if (t->size() == 0)
        {
            return QList<QExtOsgiServiceReference>();
        }
        return t->getTracked();
    }

    /**
     * @brief Called by the QExtOsgiTrackedService object whenever the set of tracked services is modified. Clears the cache.
     * @note This method must not be synchronized since it is called by QExtOsgiTrackedService while QExtOsgiTrackedService
     * is synchronized. We don't want synchronization interactions between the listener thread and the user thread.
     */
    void modified()
    {
        cachedReference = 0; /* clear cached value */
        cachedService = 0; /* clear cached value */
        if (DEBUG_FLAG)
        {
            qDebug() << "qextOsgiServiceTracker::modified:" << filter;
        }
    }

    /**
     * @brief set this to true to compile in debug messages
     */
    static const bool DEBUG_FLAG; //	= false;

    /**
     * @brief The Plugin Context used by this <code>QExtOsgiServiceTracker</code>.
     */
    QExtOsgiPluginContext *const context;

    /**
     * @brief The filter used by this <code>QExtOsgiServiceTracker</code> which specifies the search criteria for the
     * services to track.
     */
    QExtOsgiLDAPSearchFilter filter;

    /**
     * @brief The <code>QExtOsgiServiceTrackerCustomizer</code> for this tracker.
     */
    QExtOsgiServiceTrackerCustomizer<T> *customizer;

    /**
     * @brief Filter string for use when adding the ServiceListener. If this field is set, then certain optimizations
     * can be taken since we don't have a user supplied filter.
     */
    QString listenerFilter;

    /**
     * @brief Class name to be tracked. If this field is set, then we are tracking by class name.
     */
    QString trackClass;

    /**
     * @brief Reference to be tracked. If this field is set, then we are tracking a single QExtOsgiServiceReference.
     */
    QExtOsgiServiceReference trackReference;

    /**
     * @brief Tracked services:
     *  <code>QExtOsgiServiceReference</code> -> customized Object and <code>QExtOsgiServiceSlotEntry</code> object
     */
    QSharedPointer<QExtOsgiTrackedService<S, T> > trackedService;

    /**
     * @brief Accessor method for the current QExtOsgiTrackedService object. This method is only intended to be used by
     * the unsynchronized methods which do not modify the trackedService field.
     * @return The current Tracked object.
     */
    QSharedPointer<QExtOsgiTrackedService<S, T> > tracked() const { return trackedService; }

    /**
     * @brief Cached QExtOsgiServiceReference for getServiceReference.
     */
    mutable QExtOsgiServiceReference cachedReference;

    /**
     * @brief Cached service object for getService. This field is volatile since it is accessed by multiple threads.
     */
    mutable T volatile cachedService;

    mutable QMutex mutex;

private:
    inline QExtOsgiServiceTracker<S,T>* q_func()
    {
        return static_cast<QExtOsgiServiceTracker<S,T> *>(q_ptr);
    }

    inline const QExtOsgiServiceTracker<S,T>* q_func() const
    {
        return static_cast<const QExtOsgiServiceTracker<S,T> *>(q_ptr);
    }

    friend class QExtOsgiServiceTracker<S,T>;

    QExtOsgiServiceTracker<S,T> * const q_ptr;
};

//----------------------------------------------------------------------------
template<class S, class T>
const bool QExtOsgiServiceTrackerPrivate<S,T>::DEBUG_FLAG = false;


/***********************************************************************************************************************
** QExtOsgiTrackedService
***********************************************************************************************************************/
/**
 * \ingroup PluginFramework
 */
template<typename S, typename T>
class QExtOsgiTrackedService : public QExtOsgiTrackedServiceListener,
                               public QExtOsgiPluginAbstractTracked<QExtOsgiServiceReference, T, QExtOsgiServiceEvent>
{
public:
    QExtOsgiTrackedService(QExtOsgiServiceTracker<S, T> *serviceTracker,
                           QExtOsgiServiceTrackerCustomizer<T> *customizer)
        : serviceTracker(serviceTracker), customizer(customizer)
    {

    }

    /**
     * Slot connected to service events for the
     * <code>QExtOsgiServiceTracker</code> class. This method must NOT be
     * synchronized to avoid deadlock potential.
     *
     * @param event <code>QExtOsgiServiceEvent</code> object from the framework.
     */
    void serviceChanged(const QExtOsgiServiceEvent &event)
    {
        /* Check if we had a delayed call (which could happen when we close). */
        if (this->closed)
        {
            return;
        }

        QExtOsgiServiceReference reference = event.getServiceReference();
        if (serviceTracker->d_func()->DEBUG_FLAG)
        {
            qDebug() << "qextOsgiTrackedService::serviceChanged["
                     << event.getType() << "]: " << reference;
        }

        switch (event.getType())
        {
        case QExtOsgiServiceEvent::REGISTERED :
        case QExtOsgiServiceEvent::MODIFIED :
        {
            if (!serviceTracker->d_func()->listenerFilter.isNull())
            {
                // service listener added with filter
                this->track(reference, event);
                /* If the customizer throws an unchecked exception, it is safe to let it propagate */
            }
            else
            {
                // service listener added without filter
                if (serviceTracker->d_func()->filter.match(reference))
                {
                    this->track(reference, event);
                    /* If the customizer throws an unchecked exception, it is safe to let it propagate */
                }
                else
                {
                    this->untrack(reference, event);
                    /* If the customizer throws an unchecked exception, it is safe to let it propagate */
                }
            }
            break;
        }
        case QExtOsgiServiceEvent::MODIFIED_ENDMATCH :
        case QExtOsgiServiceEvent::UNREGISTERING :
            this->untrack(reference, event);
            /* If the customizer throws an unchecked exception, it is safe to let it propagate */
            break;
        }
    }

private:
    typedef QExtOsgiPluginAbstractTracked<QExtOsgiServiceReference, T, QExtOsgiServiceEvent> Superclass;

    QExtOsgiServiceTracker<S, T> *serviceTracker;
    QExtOsgiServiceTrackerCustomizer<T> *customizer;

    /**
     * @brief Increment the tracking count and tell the tracker there was a modification.
     */
    void modified()
    {
        Superclass::modified(); /* increment the modification count */
        serviceTracker->d_func()->modified();
    }

    /**
     * @brief Call the specific customizer adding method. This method must not be called while synchronized on this object.
     * @param item Item to be tracked.
     * @param related Action related object.
     * @return Customized object for the tracked item or <code>null</code> if the item is not to be tracked.
     */
    T customizerAdding(QExtOsgiServiceReference item, const QExtOsgiServiceEvent &related)
    {
        Q_UNUSED(related)
        return customizer->addingService(item);
    }

    /**
     * @brief Call the specific customizer modified method. This method must not be called while synchronized on this object.
     * @param item Tracked item.
     * @param related Action related object.
     * @param object Customized object for the tracked item.
     */
    void customizerModified(QExtOsgiServiceReference item,
                            const QExtOsgiServiceEvent &related, T object)
    {
        Q_UNUSED(related)
        customizer->modifiedService(item, object);
    }

    /**
     * @brief Call the specific customizer removed method. This method must not be called while synchronized on this object.
     * @param item Tracked item.
     * @param related Action related object.
     * @param object Customized object for the tracked item.
     */
    void customizerRemoved(QExtOsgiServiceReference item,
                           const QExtOsgiServiceEvent &related, T object)
    {
        Q_UNUSED(related)
        customizer->removedService(item, object);
    }
};

#endif // _QEXTOSGISERVICETRACKER_H
