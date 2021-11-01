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

#ifndef QTKSERVICETRACKER_H
#define QTKSERVICETRACKER_H

#include "qtkpluginframework_global.h"
#include "qtkservicereference.h"
#include "qtkservicetrackercustomizer.h"
#include "qtkldapsearchfilter.h"
#include "qtkserviceexception.h"
#include "qtkpluginconstants.h"
#include "qtkplugincontext.h"
#include "qtktrackedservicelistener_p.h"
#include "qtkpluginabstracttracked_p.h"
#include "qtkserviceevent.h"

#include <QSharedPointer>
#include <QScopedPointer>
#include <QVarLengthArray>
#include <QMutexLocker>
#include <QMutex>
#include <QDebug>
#include <QtGlobal>

#include <stdexcept>
#include <limits>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

template<class S, class T> class QTKTrackedService;
template<class S, class T> class QTKServiceTrackerPrivate;
class QTKPluginContext;

/**
 * @ingroup QTKPluginFramework
 * The <code>QTKServiceTracker</code> class simplifies using services from the
 * Framework's service registry.
 * <p>
 * A <code>QTKServiceTracker</code> object is constructed with search criteria and
 * a <code>QTKServiceTrackerCustomizer</code> object. A <code>QTKServiceTracker</code>
 * can use a <code>QTKServiceTrackerCustomizer</code> to customize the service
 * objects to be tracked. The <code>QTKServiceTracker</code> can then be opened to
 * begin tracking all services in the Framework's service registry that match
 * the specified search criteria. The <code>QTKServiceTracker</code> correctly
 * handles all of the details of listening to <code>QTKServiceEvent</code>s and
 * getting and ungetting services.
 * <p>
 * The <code>getServiceReferences</code> method can be called to get references
 * to the services being tracked. The <code>getService</code> and
 * <code>getServices</code> methods can be called to get the service objects for
 * the tracked service.
 * <p>
 * The <code>QTKServiceTracker</code> class is thread-safe. It does not call a
 * <code>QTKServiceTrackerCustomizer</code> while holding any locks.
 * <code>QTKServiceTrackerCustomizer</code> implementations must also be
 * thread-safe.
 *
 * @tparam S The type of the service being tracked. The type must be an
 *         assignable datatype. Further, if the
 *         <code>QTKServiceTracker(QTKPluginContext*, QTKServiceTrackerCustomizer<T>*)</code>
 *         constructor is used, the type must have an associated interface id via
 *         Q_DECLARE_INTERFACE.
 * @tparam T The type of the tracked object. The type must be an assignable
 *         datatype, provide a boolean conversion function, and provide
 *         a constructor and an assignment operator which can handle 0 as an argument.
 * @remarks This class is thread safe.
 */
template<class S = QObject*, class T = S>
class QTKServiceTracker : protected QTKServiceTrackerCustomizer<T>
{
public:
    /**
     * @brief QTKServiceTracker
     * Create a <code>ctkServiceTracker</code> on the specified
     * <code>ctkServiceReference</code>.
     *
     * <p>
     * The service referenced by the specified <code>ctkServiceReference</code>
     * will be tracked by this <code>ctkServiceTracker</code>.
     *
     * @param pContext The <code>ctkPluginContext</code> against which the tracking
     *        is done.
     * @param serviceRef The <code>ctkServiceReference</code> for the service to be
     *        tracked.
     * @param pCustomizer The customizer object to call when services are added,
     *        modified, or removed in this <code>ctkServiceTracker</code>. If
     *        customizer is <code>null</code>, then this
     *        <code>ctkServiceTracker</code> will be used as the
     *        <code>ctkServiceTrackerCustomizer</code> and this
     *        <code>ctkServiceTracker</code> will call the
     *        <code>ctkServiceTrackerCustomizer</code> methods on itself.
     */
    QTKServiceTracker(QTKPluginContext *pContext, const QTKServiceReference &serviceRef,
                      QTKServiceTrackerCustomizer<T> *pCustomizer = nullptr);

    /**
     * @brief QTKServiceTracker
     * Create a <code>ctkServiceTracker</code> on the specified class name.
     *
     * <p>
     * Services registered under the specified class name will be tracked by
     * this <code>ctkServiceTracker</code>.
     *
     * @param pContext The <code>ctkPluginContext</code> against which the tracking
     *        is done.
     * @param strClazz The class name of the services to be tracked.
     * @param pCustomizer The customizer object to call when services are added,
     *        modified, or removed in this <code>ctkServiceTracker</code>. If
     *        customizer is <code>null</code>, then this
     *        <code>ctkServiceTracker</code> will be used as the
     *        <code>ctkServiceTrackerCustomizer</code> and this
     *        <code>ctkServiceTracker</code> will call the
     *        <code>ctkServiceTrackerCustomizer</code> methods on itself.
     */
    QTKServiceTracker(QTKPluginContext *pContext, const QString &strClazz,
                      QTKServiceTrackerCustomizer<T> *pCustomizer = nullptr);

    /**
     * @brief QTKServiceTracker
     * Create a <code>ctkServiceTracker</code> on the specified
     * <code>ctkLDAPSearchFilter</code> object.
     *
     * <p>
     * Services which match the specified <code>ctkLDAPSearchFilter</code> object will be
     * tracked by this <code>ctkServiceTracker</code>.
     *
     * @param pContext The <code>ctkPluginContext</code> against which the tracking
     *        is done.
     * @param filter The <code>ctkLDAPSearchFilter</code> to select the services to be
     *        tracked.
     * @param pCustomizer The customizer object to call when services are added,
     *        modified, or removed in this <code>ctkServiceTracker</code>. If
     *        customizer is null, then this <code>ctkServiceTracker</code> will be
     *        used as the <code>ctkServiceTrackerCustomizer</code> and this
     *        <code>ctkServiceTracker</code> will call the
     *        <code>ctkServiceTrackerCustomizer</code> methods on itself.
     */
    QTKServiceTracker(QTKPluginContext *pContext, const QTKLDAPSearchFilter &filter,
                      QTKServiceTrackerCustomizer<T> *pCustomizer = nullptr);

    /**
     * @brief QTKServiceTracker
     * Create a <code>ctkServiceTracker</code> on the class template
     * argument S.
     *
     * <p>
     * Services registered under the interface name of the class template
     * argument S will be tracked by this <code>ctkServiceTracker</code>.
     *
     * @param pContext The <code>ctkPluginContext</code> against which the tracking
     *        is done.
     * @param pCustomizer The customizer object to call when services are added,
     *        modified, or removed in this <code>ctkServiceTracker</code>. If
     *        customizer is null, then this <code>ctkServiceTracker</code> will be
     *        used as the <code>ctkServiceTrackerCustomizer</code> and this
     *        <code>ctkServiceTracker</code> will call the
     *        <code>ctkServiceTrackerCustomizer</code> methods on itself.
     */
    QTKServiceTracker(QTKPluginContext *pContext, QTKServiceTrackerCustomizer<T> *pCustomizer = nullptr);
    ~QTKServiceTracker();

    /**
     * @brief open
     * Open this <code>ctkServiceTracker</code> and begin tracking services.
     *
     * <p>
     * Services which match the search criteria specified when this
     * <code>ctkServiceTracker</code> was created are now tracked by this
     * <code>ctkServiceTracker</code>.
     *
     * @throws ctkIllegalStateException If the <code>ctkPluginContext</code>
     *         with which this <code>ctkServiceTracker</code> was created is no
     *         longer valid.
     */
    virtual void open();

    /**
     * @brief close
     * Close this <code>ctkServiceTracker</code>.
     *
     * <p>
     * This method should be called when this <code>ctkServiceTracker</code> should
     * end the tracking of services.
     *
     * <p>
     * This implementation calls getServiceReferences() to get the list
     * of tracked services to remove.
     */
    virtual void close();

    /**
     * @brief waitForService
     * Wait for at least one service to be tracked by this
     * <code>ctkServiceTracker</code>. This method will also return when this
     * <code>ctkServiceTracker</code> is closed.
     *
     * <p>
     * It is strongly recommended that <code>waitForService</code> is not used
     * during the calling of the <code>ctkPluginActivator</code> methods.
     * <code>ctkPluginActivator</code> methods are expected to complete in a short
     * period of time.
     *
     * <p>
     * This implementation calls getService() to determine if a service
     * is being tracked.
     *
     * @param ulTimeout The time interval in milliseconds to wait. If zero, the
     *        method will wait indefinitely.
     * @return Returns the result of getService().
     */
    virtual T waitForService(unsigned long ulTimeout);

    /**
     * @brief getServiceReferences
     * Return a list of <code>ctkServiceReference</code>s for all services being
     * tracked by this <code>ctkServiceTracker</code>.
     *
     * @return List of <code>ctkServiceReference</code>s.
     */
    virtual QList<QTKServiceReference> getServiceReferences() const;

    /**
     * @brief getServiceReference
     * Returns a <code>ctkServiceReference</code> for one of the services being
     * tracked by this <code>ctkServiceTracker</code>.
     *
     * <p>
     * If multiple services are being tracked, the service with the highest
     * ranking (as specified in its <code>service.ranking</code> property) is
     * returned. If there is a tie in ranking, the service with the lowest
     * service ID (as specified in its <code>service.id</code> property); that
     * is, the service that was registered first is returned. This is the same
     * algorithm used by <code>ctkPluginContext::getServiceReference()</code>.
     *
     * <p>
     * This implementation calls getServiceReferences() to get the list
     * of references for the tracked services.
     *
     * @return A <code>ctkServiceReference</code> for a tracked service.
     * @throws ctkServiceException if no services are being tracked.
     */
    virtual QTKServiceReference getServiceReference() const;

    /**
     * @brief getService
     * Returns the service object for the specified
     * <code>ctkServiceReference</code> if the specified referenced service is
     * being tracked by this <code>ctkServiceTracker</code>.
     *
     * @param serviceRef The reference to the desired service.
     * @return A service object or <code>null</code> if the service referenced
     *         by the specified <code>ctkServiceReference</code> is not being
     *         tracked.
     */
    virtual T getService(const QTKServiceReference &serviceRef) const;

    /**
     * @brief getServices
     * Return a list of service objects for all services being tracked by this
     * <code>ctkServiceTracker</code>.
     *
     * <p>
     * This implementation calls getServiceReferences() to get the list
     * of references for the tracked services and then calls
     * getService(const ctkServiceReference&) for each reference to get the
     * tracked service object.
     *
     * @return A list of service objects or an empty list if no services
     *         are being tracked.
     */
    virtual QList<T> getServices() const;

    /**
     * @brief getService
     * Returns a service object for one of the services being tracked by this
     * <code>ctkServiceTracker</code>.
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
     * @brief remove
     * Remove a service from this <code>ctkServiceTracker</code>.
     *
     * The specified service will be removed from this
     * <code>ctkServiceTracker</code>. If the specified service was being tracked
     * then the <code>ctkServiceTrackerCustomizer::removedService</code> method will
     * be called for that service.
     *
     * @param serviceRef The reference to the service to be removed.
     */
    virtual void remove(const QTKServiceReference &serviceRef);

    /**
     * @brief size
     * Return the number of services being tracked by this
     * <code>ctkServiceTracker</code>.
     *
     * @return The number of services being tracked.
     */
    virtual int size() const;

    /**
     * @brief getTrackingCount
     * Returns the tracking count for this <code>ctkServiceTracker</code>.
     *
     * The tracking count is initialized to 0 when this
     * <code>ctkServiceTracker</code> is opened. Every time a service is added,
     * modified or removed from this <code>ctkServiceTracker</code>, the tracking
     * count is incremented.
     *
     * <p>
     * The tracking count can be used to determine if this
     * <code>ctkServiceTracker</code> has added, modified or removed a service by
     * comparing a tracking count value previously collected with the current
     * tracking count value. If the value has not changed, then no service has
     * been added, modified or removed from this <code>ctkServiceTracker</code>
     * since the previous tracking count was collected.
     *
     * @return The tracking count for this <code>ctkServiceTracker</code> or -1 if
     *         this <code>ctkServiceTracker</code> is not open.
     */
    virtual int getTrackingCount() const;

    /**
     * @brief getTracked
     * Return a sorted <code>QMap</code> of the <code>ctkServiceReference</code>s and
     * service objects for all services being tracked by this
     * <code>ctkServiceTracker</code>. The map is sorted in natural order
     * of <code>ctkServiceReference</code>. That is, the last entry is the service
     * with the highest ranking and the lowest service id.
     *
     * @return A <code>QMap</code> with the <code>ctkServiceReference</code>s
     *         and service objects for all services being tracked by this
     *         <code>ctkServiceTracker</code>. If no services are being tracked,
     *         then the returned map is empty.
     */
    virtual QMap<QTKServiceReference, T> getTracked() const;

    /**
     * @brief isEmpty
     * Return if this <code>ctkServiceTracker</code> is empty.
     *
     * @return <code>true</code> if this <code>ctkServiceTracker</code> is not tracking any
     *         services.
     */
    virtual bool isEmpty() const;

protected:
    /**
     * @brief addingService
     * Default implementation of the
     * <code>ctkServiceTrackerCustomizer::addingService</code> method.
     *
     * <p>
     * This method is only called when this <code>ctkServiceTracker</code> has been
     * constructed with a <code>null</code> ctkServiceTrackerCustomizer argument.
     *
     * <p>
     * This implementation returns the result of calling <code>getService</code>
     * on the <code>ctkPluginContext</code> with which this
     * <code>ctkServiceTracker</code> was created passing the specified
     * <code>ctkServiceReference</code>.
     * <p>
     * This method can be overridden in a subclass to customize the service
     * object to be tracked for the service being added. In that case, take care
     * not to rely on the default implementation of
     * \link removedService(const ctkServiceReference&, T service) removedService\endlink
     * to unget the service.
     *
     * @param serviceRef The reference to the service being added to this
     *        <code>ctkServiceTracker</code>.
     * @return The service object to be tracked for the service added to this
     *         <code>ctlServiceTracker</code>.
     * @see ctkServiceTrackerCustomizer::addingService(const ctkServiceReference&)
     */
    T addingService(const QTKServiceReference &serviceRef);

    /**
     * @brief modifiedService
     * Default implementation of the
     * <code>ctkServiceTrackerCustomizer::modifiedService</code> method.
     *
     * <p>
     * This method is only called when this <code>ctkServiceTracker</code> has been
     * constructed with a <code>null</code> ctkServiceTrackerCustomizer argument.
     *
     * <p>
     * This implementation does nothing.
     *
     * @param serviceRef The reference to modified service.
     * @param service The service object for the modified service.
     * @see ctkServiceTrackerCustomizer::modifiedService(const ctkServiceReference&, QObject*)
     */
    void modifiedService(const QTKServiceReference &serviceRef, T service);

    /**
     * @brief removedService
     * Default implementation of the
     * <code>ctkServiceTrackerCustomizer::removedService</code> method.
     *
     * <p>
     * This method is only called when this <code>ctkServiceTracker</code> has been
     * constructed with a <code>null</code> ctkServiceTrackerCustomizer argument.
     *
     * <p>
     * This implementation calls <code>ungetService</code>, on the
     * <code>ctkPluginContext</code> with which this <code>ctkServiceTracker</code>
     * was created, passing the specified <code>ctkServiceReference</code>.
     * <p>
     * This method can be overridden in a subclass. If the default
     * implementation of \link addingService(const ctkServiceReference&) addingService\endlink
     * method was used, this method must unget the service.
     *
     * @param serviceRef The reference to removed service.
     * @param service The service object for the removed service.
     * @see ctkServiceTrackerCustomizer::removedService(const ServiceReference&, QObject*)
     */
    void removedService(const QTKServiceReference &serviceRef, T service);

private:
    typedef QTKServiceTracker<S,T> ServiceTracker;
    typedef QTKTrackedService<S,T> TrackedService;
    typedef QTKServiceTrackerPrivate<S,T> ServiceTrackerPrivate;
    typedef QTKServiceTrackerCustomizer<T> ServiceTrackerCustomizer;

    friend class QTKTrackedService<S,T>;
    friend class QTKServiceTrackerPrivate<S,T>;

    inline ServiceTrackerPrivate* d_func() {
        return reinterpret_cast<ServiceTrackerPrivate*>(qGetPtrHelper(d_ptr));
    }

    inline const ServiceTrackerPrivate* d_func() const {
        return reinterpret_cast<const ServiceTrackerPrivate*>(qGetPtrHelper(d_ptr));
    }

    const QScopedPointer<ServiceTrackerPrivate> d_ptr;
};

template<class S, class T>
QTKServiceTracker<S,T>::~QTKServiceTracker()
{
}

template<class S, class T>
QTKServiceTracker<S,T>::QTKServiceTracker(QTKPluginContext *pContext,
                                          const QTKServiceReference &serviceRef,
                                          ServiceTrackerCustomizer *pCustomizer)
    : d_ptr(new ServiceTrackerPrivate(this, pContext, serviceRef, pCustomizer))
{
}

template<class S, class T>
QTKServiceTracker<S,T>::QTKServiceTracker(QTKPluginContext* pContext, const QString& strClazz,
                                          ServiceTrackerCustomizer* pCustomizer)
    : d_ptr(new ServiceTrackerPrivate(this, pContext, strClazz, pCustomizer))
{
}

template<class S, class T>
QTKServiceTracker<S,T>::QTKServiceTracker(QTKPluginContext* pContext, const QTKLDAPSearchFilter& filter,
                                          ServiceTrackerCustomizer* pCustomizer)
    : d_ptr(new ServiceTrackerPrivate(this, pContext, filter, pCustomizer))
{
}

template<class S, class T>
QTKServiceTracker<S,T>::QTKServiceTracker(QTKPluginContext *pContext, QTKServiceTrackerCustomizer<T> *pCustomizer)
    : d_ptr(new ServiceTrackerPrivate(this, pContext, qobject_interface_iid<S>(), pCustomizer))
{
    const char *pClazz = qobject_interface_iid<S>();
    if (nullptr == pClazz) {
        throw QTKServiceException("The service interface class has no Q_DECLARE_INTERFACE macro");
    }
}


template<class S, class T>
void QTKServiceTracker<S,T>::open()
{
    Q_D(ServiceTracker);
    QSharedPointer<TrackedService> pTrackedService;
    {
        QMutexLocker locker(&d->m_mutex);
        if (d->m_trackedService) {
            return;
        }

        if (d->sm_bDebugFlag) {
            qDebug() << "QTKServiceTracker<S,T>::open: " << d->m_filter;
        }

        pTrackedService = QSharedPointer<TrackedService>(new TrackedService(this, d->m_pCustomizer));
        {
            QMutexLocker trackedServiceLocker(pTrackedService.data());
            try {
                d->m_pContext->connectServiceListener(pTrackedService.data(), "serviceChanged", d->m_strListenerFilter);
                QList<QTKServiceReference> listServiceRefs;
                if (!d->m_strTrackClass.isEmpty()) {
                    listServiceRefs = d->getInitialReferences(d->m_strTrackClass, QString());
                } else {
                    if (!d->m_trackReference.getPlugin().isNull()) {
                        listServiceRefs.push_back(d->m_trackReference);
                    } else { /* user supplied filter */
                        listServiceRefs = d->getInitialReferences(QString(),
                                                                  (d->m_strListenerFilter.isNull()) ? d->m_filter.toString() : d->m_strListenerFilter);
                    }
                }
                /* set tracked with the initial references */
                pTrackedService->setInitial(listServiceRefs);
            } catch (const QTKInvalidArgumentException &exception) {
                throw QTKRuntimeException(QString("unexpected QTKInvalidArgumentException exception: %1").arg(exception.what()));
            }
        }
        d->m_trackedService = pTrackedService;
    }
    /* Call tracked outside of synchronized region */
    pTrackedService->trackInitial(); /* process the initial references */
}

template<class S, class T>
void QTKServiceTracker<S,T>::close()
{
    Q_D(ServiceTracker);
    QSharedPointer<TrackedService> pTrackedService;
    QList<QTKServiceReference> listServiceRefs;
    {
        QMutexLocker locker(&d->m_mutex);
        pTrackedService = d->m_trackedService;
        if (pTrackedService.isNull()) {
            return;
        }
        if (d->sm_bDebugFlag) {
            qDebug() << "QTKServiceTracker<S,T>::close:" << d->m_filter;
        }
        pTrackedService->close();
        listServiceRefs = getServiceReferences();
        d->m_trackedService.clear();;
        try {
            d->m_pContext->disconnectServiceListener(pTrackedService.data(), "serviceChanged");
        } catch (const QTKIllegalStateException &exception) {
            Q_UNUSED(exception)
            /* In case the context was stopped. */
        }
    }
    d->modified(); /* clear the cache */
    {
        QMutexLocker trackedServiceLocker(pTrackedService.data());
        pTrackedService->wakeAll(); /* wake up any waiters */
    }
    foreach (QTKServiceReference serviceRef, listServiceRefs) {
        pTrackedService->untrack(serviceRef, QTKServiceEvent());
    }

    if (d->sm_bDebugFlag) {
        QMutexLocker locker(&d->m_mutex);
        if ((d->m_cachedReference.getPlugin().isNull()) && (d->m_cachedService == 0)) {
            qDebug() << "QTKServiceTracker<S,T>::close[cached cleared]:"
                     << d->m_filter;
        }
    }
}

template<class S, class T>
T QTKServiceTracker<S,T>::waitForService(unsigned long ulTimeout)
{
    Q_D(ServiceTracker);
    T object = getService();
    while (object == 0) {
        QSharedPointer<TrackedService> trackedService = d->tracked();
        if (trackedService.isNull()) { /* if ServiceTracker is not open */
            return 0;
        }
        {
            QMutexLocker trackedServiceLocker(trackedService.data());
            if (trackedService->size() == 0) {
                trackedService->wait(ulTimeout);
            }
        }
        object = getService();
        if (ulTimeout > 0) {
            return object;
        }
    }
    return object;
}

template<class S, class T>
QList<QTKServiceReference> QTKServiceTracker<S,T>::getServiceReferences() const
{
    Q_D(const ServiceTracker);
    QSharedPointer<TrackedService> trackedService = d->tracked();
    if (trackedService.isNull()) { /* if ServiceTracker is not open */
        return QList<QTKServiceReference>();
    }
    {
        QMutexLocker trackedServiceLocker(trackedService.data());
        return d->getServiceReferences_unlocked(trackedService.data());
    }
}

template<class S, class T>
QTKServiceReference QTKServiceTracker<S,T>::getServiceReference() const
{
    Q_D(const ServiceTracker);
    QTKServiceReference serviceRef(0);
    {
        QMutexLocker locker(&d->m_mutex);
        serviceRef = d->m_cachedReference;
    }
    if (!serviceRef.getPlugin().isNull()) {
        if (d->sm_bDebugFlag) {
            qDebug() << "QTKServiceTracker<S,T>::getServiceReference[cached]:"
                     << d->m_filter;
        }
        return serviceRef;
    }
    if (d->sm_bDebugFlag) {
        qDebug() << "QTKServiceTracker<S,T>::getServiceReference:" << d->m_filter;
    }
    QList<QTKServiceReference> listServiceRefs = this->getServiceReferences();
    int iLength = listServiceRefs.size();
    if (0 == iLength) { /* if no service is being tracked */
        throw QTKServiceException("No service is being tracked");
    }
    int iIndex = 0;
    if (iLength > 1) { /* if more than one service, select highest ranking */
        QVarLengthArray<int, 10> rankings(iLength);
        int iCount = 0;
        int iMaxRanking = std::numeric_limits<int>::min();
        for (int i = 0; i < iLength; i++) {
            bool bOk = false;
            int iRanking = listServiceRefs[i].getProperty(QTKPluginConstants::SERVICE_RANKING).toInt(&bOk);
            if (!bOk) {
                iRanking = 0;
            }

            rankings[i] = iRanking;
            if (iRanking > iMaxRanking) {
                iIndex = i;
                iMaxRanking = iRanking;
                iCount = 1;
            } else {
                if (iRanking == iMaxRanking) {
                    iCount++;
                }
            }
        }
        if (iCount > 1) { /* if still more than one service, select lowest id */
            qlonglong llMinId = std::numeric_limits<qlonglong>::max();
            for (int i = 0; i < iLength; i++) {
                if (rankings[i] == iMaxRanking) {
                    qlonglong llId = listServiceRefs[i].getProperty(QTKPluginConstants::SERVICE_ID).toLongLong();
                    if (llId < llMinId) {
                        iIndex = i;
                        llMinId = llId;
                    }
                }
            }
        }
    }
    {
        QMutexLocker locker(&d->m_mutex);
        d->m_cachedReference = listServiceRefs[iIndex];
        return d->m_cachedReference;
    }
}

template<class S, class T>
T QTKServiceTracker<S,T>::getService(const QTKServiceReference &serviceRef) const
{
    Q_D(const ServiceTracker);
    QSharedPointer<TrackedService> trackedService = d->tracked();
    if (trackedService.isNull()) { /* if ServiceTracker is not open */
        return 0;
    }
    {
        QMutexLocker trackedServiceLocker(trackedService.data());
        return trackedService->getCustomizedObject(serviceRef);
    }
}

template<class S, class T>
QList<T> QTKServiceTracker<S,T>::getServices() const
{
    Q_D(const ServiceTracker);
    QSharedPointer<TrackedService> trackedService = d->tracked();
    if (trackedService.isNull()) { /* if ServiceTracker is not open */
        return QList<T>();
    }
    {
        QMutexLocker trackedServiceLocker(trackedService.data());
        QList<QTKServiceReference> listServiceRefs = d->getServiceReferences_unlocked(trackedService.data());
        QList<T> objects;
        foreach (QTKServiceReference serviceRef, listServiceRefs) {
            //objects << getService(ref);
            objects << trackedService->getCustomizedObject(serviceRef);
        }
        return objects;
    }
}

template<class S, class T>
T QTKServiceTracker<S,T>::getService() const
{
    Q_D(const ServiceTracker);
    T service = d->m_cachedService;
    if (service != 0) {
        if (d->sm_bDebugFlag) {
            qDebug() << "QTKServiceTracker<S,T>::getService[cached]:"
                     << d->m_filter;
        }
        return service;
    }
    if (d->sm_bDebugFlag) {
        qDebug() << "QTKServiceTracker<S,T>::getService:" << d->m_filter;
    }

    try {
        QTKServiceReference serviceRef = this->getServiceReference();
        if (serviceRef.getPlugin().isNull()) {
            return 0;
        }
        return d->m_cachedService = getService(serviceRef);
    } catch (const QTKServiceException &) {
        return 0;
    }
}

template<class S, class T>
void QTKServiceTracker<S,T>::remove(const QTKServiceReference &serviceRef)
{
    Q_D(ServiceTracker);
    QSharedPointer<TrackedService> trackedService = d->tracked();
    if (trackedService.isNull()) { /* if ServiceTracker is not open */
        return;
    }
    trackedService->untrack(serviceRef, QTKServiceEvent());
}

template<class S, class T>
int QTKServiceTracker<S,T>::size() const
{
    Q_D(const ServiceTracker);
    QSharedPointer<TrackedService> trackedService = d->tracked();
    if (trackedService.isNull()) { /* if ServiceTracker is not open */
        return 0;
    }
    {
        QMutexLocker trackedServiceLocker(trackedService.data());
        return trackedService->size();
    }
}

template<class S, class T>
int QTKServiceTracker<S,T>::getTrackingCount() const
{
    Q_D(const ServiceTracker);
    QSharedPointer<TrackedService> trackedService = d->tracked();
    if (trackedService.isNull()) { /* if ServiceTracker is not open */
        return -1;
    }
    {
        QMutexLocker trackedServiceLocker(trackedService.data());
        return trackedService->getTrackingCount();
    }
}

template<class S, class T>
QMap<QTKServiceReference, T> QTKServiceTracker<S,T>::getTracked() const
{
    QMap<QTKServiceReference, T> map;
    Q_D(const ServiceTracker);
    QSharedPointer<TrackedService> trackedService = d->tracked();
    if (trackedService.isNull()) { /* if ServiceTracker is not open */
        return map;
    }
    {
        QMutexLocker trackedServiceLocker(trackedService.data());
        return trackedService->copyEntries(map);
    }
}

template<class S, class T>
bool QTKServiceTracker<S,T>::isEmpty() const
{
    Q_D(const ServiceTracker);
    QSharedPointer<TrackedService> trackedService = d->tracked();
    if (trackedService.isNull()) { /* if ServiceTracker is not open */
        return true;
    }
    {
        QMutexLocker trackedServiceLocker(trackedService.data());
        return trackedService->isEmpty();
    }
}

template<class S, class T>
T QTKServiceTracker<S,T>::addingService(const QTKServiceReference &serviceRef)
{
    Q_D(ServiceTracker);
    return qobject_cast<T>(d->m_pContext->getService(serviceRef));
}

template<class S, class T>
void QTKServiceTracker<S,T>::modifiedService(const QTKServiceReference &serviceRef, T service)
{
    Q_UNUSED(serviceRef)
    Q_UNUSED(service)
    /* do nothing */
}

template<class S, class T>
void QTKServiceTracker<S,T>::removedService(const QTKServiceReference &serviceRef, T service)
{
    Q_UNUSED(service)
    Q_D(ServiceTracker);
    d->m_pContext->ungetService(serviceRef);
}


/**
 * @brief QTKServiceTrackerPrivate
 */
template<class S, class T>
class QTKServiceTrackerPrivate
{
public:
    QTKServiceTrackerPrivate(QTKServiceTracker<S,T> *pServiceTracker, QTKPluginContext *pContext,
                             const QTKServiceReference &serviceRef,
                             QTKServiceTrackerCustomizer<T> *pCustomizer);

    QTKServiceTrackerPrivate(QTKServiceTracker<S,T> *pServiceTracker, QTKPluginContext *pContext,
                             const QString &strClazz, QTKServiceTrackerCustomizer<T> *pCustomizer);

    QTKServiceTrackerPrivate(QTKServiceTracker<S,T> *pServiceTracker, QTKPluginContext *pContext,
                             const QTKLDAPSearchFilter &filter,
                             QTKServiceTrackerCustomizer<T> *pCustomizer);

    ~QTKServiceTrackerPrivate();


    /**
     * Returns the list of initial <code>QTKServiceReference</code>s that will be
     * tracked by this <code>QTKServiceTracker</code>.
     *
     * @param className The class name with which the service was registered, or
     *        <code>null</code> for all services.
     * @param filterString The filter criteria or <code>null</code> for all
     *        services.
     * @return The list of initial <code>QTKServiceReference</code>s.
     * @throws QTKInvalidArgumentException If the specified filterString has an
     *         invalid syntax.
     */
    QList<QTKServiceReference> getInitialReferences(const QString &strClassName,
                                                    const QString &strFilterString);

    QList<QTKServiceReference> getServiceReferences_unlocked(QTKTrackedService<S,T> *pServiceTracker) const;

    /**
     * @brief tracked
     * Accessor method for the current QTKTrackedService object. This method is only
     * intended to be used by the unsynchronized methods which do not modify the
     * trackedService field.
     *
     * @return The current Tracked object.
     */
    QSharedPointer<QTKTrackedService<S,T> > tracked() const;

    /**
     * @brief modified
     * Called by the QTKTrackedService object whenever the set of tracked services is
     * modified. Clears the cache.
     *
     * This method must not be synchronized since it is called by QTKTrackedService while
     * QTKTrackedService is synchronized. We don't want synchronization interactions
     * between the listener thread and the user thread.
     */
    void modified();

    /**
     * @brief sm_bDebugFlag
     * set this to true to compile in debug messages
     */
    static const bool sm_bDebugFlag; //	= false;

    /**
     * @brief m_pContext
     * The Plugin Context used by this <code>QTKServiceTracker</code>.
     */
    QTKPluginContext* const	m_pContext;

    /**
     * @brief m_filter
     * The filter used by this <code>QTKServiceTracker</code> which specifies the
     * search criteria for the services to track.
     */
    QTKLDAPSearchFilter	m_filter;

    /**
     * @brief m_pCustomizer
     * The <code>QTKServiceTrackerCustomizer</code> for this tracker.
     */
    QTKServiceTrackerCustomizer<T> *m_pCustomizer;

    /**
     * @brief m_strListenerFilter
     * Filter string for use when adding the ServiceListener. If this field is
     * set, then certain optimizations can be taken since we don't have a user
     * supplied filter.
     */
    QString m_strListenerFilter;

    /**
     * @brief m_strTrackClass
     * Class name to be tracked. If this field is set, then we are tracking by
     * class name.
     */
    QString m_strTrackClass;

    /**
     * @brief m_trackReference
     * Reference to be tracked. If this field is set, then we are tracking a
     * single QTKServiceReference.
     */
    QTKServiceReference	m_trackReference;

    /**
     * @brief m_trackedService
     * Tracked services: <code>QTKServiceReference</code> -> customized Object and
     * <code>QTKServiceSlotEntry</code> object
     */
    QSharedPointer<QTKTrackedService<S,T> > m_trackedService;

    /**
     * @brief m_cachedReference
     * Cached QTKServiceReference for getServiceReference.
     */
    mutable QTKServiceReference m_cachedReference;

    /**
     * @brief m_cachedService
     * Cached service object for getService.
     *
     * This field is volatile since it is accessed by multiple threads.
     */
    mutable T volatile m_cachedService;

    mutable QMutex m_mutex;

private:
    inline QTKServiceTracker<S,T>* q_func() {
        return static_cast<QTKServiceTracker<S,T> *>(q_ptr);
    }

    inline const QTKServiceTracker<S,T>* q_func() const {
        return static_cast<const QTKServiceTracker<S,T> *>(q_ptr);
    }

    friend class QTKServiceTracker<S,T>;

    QTKServiceTracker<S,T> * const q_ptr;
};

template<class S, class T>
const bool QTKServiceTrackerPrivate<S,T>::sm_bDebugFlag = false;

template<class S, class T>
QTKServiceTrackerPrivate<S,T>::QTKServiceTrackerPrivate(QTKServiceTracker<S,T> *pServiceTracker, QTKPluginContext *pContext,
                                                        const QTKServiceReference &serviceRef,
                                                        QTKServiceTrackerCustomizer<T> *pCustomizer)
    : m_pContext(pContext),
      m_pCustomizer(pCustomizer),
      m_trackReference(serviceRef),
      m_trackedService(nullptr),
      m_cachedReference(nullptr),
      m_cachedService(nullptr),
      q_ptr(pServiceTracker)
{
    m_pCustomizer = pCustomizer ? pCustomizer : q_func();
    m_strListenerFilter = QString("(") + QTKPluginConstants::SERVICE_ID +
            "=" + serviceRef.getProperty(QTKPluginConstants::SERVICE_ID).toString() + ")";
    try {
        m_filter = QTKLDAPSearchFilter(m_strListenerFilter);
    } catch (const QTKInvalidArgumentException &exception) {
        QTKInvalidArgumentException invalidException(QString("unexpected QTKInvalidArgumentException exception: %1").arg(exception.what()));
        throw invalidException;
    }
}

template<class S, class T>
QTKServiceTrackerPrivate<S,T>::QTKServiceTrackerPrivate(QTKServiceTracker<S,T> *pServiceTracker,
                                                        QTKPluginContext *pContext, const QString &strClazz,
                                                        QTKServiceTrackerCustomizer<T> *pCustomizer)
    : m_pContext(pContext),
      m_pCustomizer(pCustomizer),
      m_strTrackClass(strClazz),
      m_trackReference(nullptr),
      m_trackedService(nullptr),
      m_cachedReference(nullptr),
      m_cachedService(nullptr),
      q_ptr(pServiceTracker)
{
    m_pCustomizer = pCustomizer ? pCustomizer : q_func();
    m_strListenerFilter = QString("(") + QTKPluginConstants::OBJECT_CLASS + "=" + strClazz + ")";
    try {
        m_filter = QTKLDAPSearchFilter(m_strListenerFilter);
    } catch (const QTKInvalidArgumentException &exception) {
        QTKInvalidArgumentException invalidException(QString("unexpected QTKInvalidArgumentException exception: %1").arg(exception.what()));
        throw invalidException;
    }
}

template<class S, class T>
QTKServiceTrackerPrivate<S,T>::QTKServiceTrackerPrivate(QTKServiceTracker<S,T> *pServiceTracker,
                                                        QTKPluginContext *pContext, const QTKLDAPSearchFilter &filter,
                                                        QTKServiceTrackerCustomizer<T> *pCustomizer)
    : m_pContext(pContext),
      m_filter(filter),
      m_pCustomizer(pCustomizer),
      m_strListenerFilter(filter.toString()),
      m_trackReference(nullptr),
      m_trackedService(nullptr),
      m_cachedReference(nullptr),
      m_cachedService(nullptr),
      q_ptr(pServiceTracker)
{
    m_pCustomizer = pCustomizer ? pCustomizer : q_func();
    if (nullptr == pContext) {
        throw QTKInvalidArgumentException("The plugin context cannot be null.");
    }
}

template<class S, class T>
QTKServiceTrackerPrivate<S,T>::~QTKServiceTrackerPrivate()
{

}

template<class S, class T>
QList<QTKServiceReference> QTKServiceTrackerPrivate<S,T>::getInitialReferences(const QString &strClassName,
                                                                               const QString &strFilterString)
{
    return m_pContext->getServiceReferences(strClassName, strFilterString);
}

template<class S, class T>
QList<QTKServiceReference> QTKServiceTrackerPrivate<S,T>::getServiceReferences_unlocked(QTKTrackedService<S, T> *pServiceTracker) const
{
    if (pServiceTracker->size() == 0) {
        return QList<QTKServiceReference>();
    }
    return pServiceTracker->getTracked();
}

template<class S, class T>
QSharedPointer<QTKTrackedService<S,T> > QTKServiceTrackerPrivate<S,T>::tracked() const
{
    return m_trackedService;
}

template<class S, class T>
void QTKServiceTrackerPrivate<S,T>::modified()
{
    m_cachedReference = 0; /* clear cached value */
    m_cachedService = 0; /* clear cached value */
    if (sm_bDebugFlag) {
        qDebug() << "QTKServiceTracker::modified:" << m_filter;
    }
}

template<class S, class T>
class QTKTrackedService : public QTKTrackedServiceListener,
        public QTKPluginAbstractTracked<QTKServiceReference, T, QTKServiceEvent>
{
public:
    QTKTrackedService(QTKServiceTracker<S,T> *pServiceTracker,
                      QTKServiceTrackerCustomizer<T> *pCustomizer);

    void serviceChanged(const QTKServiceEvent &event);

private:
    typedef QTKPluginAbstractTracked<QTKServiceReference, T, QTKServiceEvent> Superclass;

    void modified();
    T customizerAdding(QTKServiceReference item, const QTKServiceEvent &related);
    void customizerModified(QTKServiceReference item, const QTKServiceEvent &related, T object);
    void customizerRemoved(QTKServiceReference item, const QTKServiceEvent &related, T object);

    QTKServiceTracker<S,T> *m_pServiceTracker;
    QTKServiceTrackerCustomizer<T> *m_pCustomizer;
};

template<class S, class T>
QTKTrackedService<S,T>::QTKTrackedService(QTKServiceTracker<S,T> *pServiceTracker,
                                          QTKServiceTrackerCustomizer<T> *pCustomizer)
    : m_pServiceTracker(pServiceTracker),
      m_pCustomizer(pCustomizer)
{

}

template<class S, class T>
void QTKTrackedService<S,T>::serviceChanged(const QTKServiceEvent &event)
{
    if (this->m_bClosed) {
        return;
    }

    QTKServiceReference serviceRef = event.getServiceReference();
    if (m_pServiceTracker->d_func()->sm_bDebugFlag) {
        qDebug() << "QTKTrackedService::serviceChanged["
                 << event.getType() << "]: " << serviceRef;
    }

    switch (event.getType())
    {
    case QTKServiceEvent::Type_Registered:
    case QTKServiceEvent::Type_Modified:
    {
        if (!m_pServiceTracker->d_func()->m_strListenerFilter.isNull()) { // service listener added with filter
            this->track(serviceRef, event);
        } else { // service listener added without filter
            if (m_pServiceTracker->d_func()->m_filter.match(serviceRef)) {
                this->track(serviceRef, event);
            } else {
                this->untrack(serviceRef, event);
            }
        }
        break;
    }
    case QTKServiceEvent::Type_ModifiedEndMatch:
    case QTKServiceEvent::Type_Unregistering:
    {
        this->untrack(serviceRef, event);
        break;
    }
    }
}

template<class S, class T>
void QTKTrackedService<S,T>::modified()
{
    Superclass::modified(); /* increment the modification count */
    m_pServiceTracker->d_func()->modified();
}

template<class S, class T>
T QTKTrackedService<S,T>::customizerAdding(QTKServiceReference item,
                                           const QTKServiceEvent &related)
{
    Q_UNUSED(related)
    return m_pCustomizer->addingService(item);
}

template<class S, class T>
void QTKTrackedService<S,T>::customizerModified(QTKServiceReference item,
                                                const QTKServiceEvent &related,
                                                T object)
{
    Q_UNUSED(related)
    m_pCustomizer->modifiedService(item, object);
}

template<class S, class T>
void QTKTrackedService<S,T>::customizerRemoved(QTKServiceReference item,
                                               const QTKServiceEvent &related,
                                               T object)
{
    Q_UNUSED(related)
    m_pCustomizer->removedService(item, object);
}

QTK_PLUGINFRAMEWORK_END_NAMESPACE

#endif // QTKSERVICETRACKER_H
