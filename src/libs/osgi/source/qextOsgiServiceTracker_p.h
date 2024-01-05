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


#ifndef _QEXTOSGISERVICETRACKERPRIVATE_H
#define _QEXTOSGISERVICETRACKERPRIVATE_H

#include <qextOsgiServiceReference.h>
#include <qextOsgiLDAPSearchFilter.h>

#include <QMutex>
#include <QSharedPointer>

/**
 * \ingroup PluginFramework
 */
template<class S, class T>
class QExtOsgiServiceTrackerPrivate
{

public:

    QExtOsgiServiceTrackerPrivate(QExtOsgiServiceTracker<S,T>* st,
                             QExtOsgiPluginContext* context,
                             const QExtOsgiServiceReference& reference,
                             QExtOsgiServiceTrackerCustomizer<T>* customizer);

    QExtOsgiServiceTrackerPrivate(QExtOsgiServiceTracker<S,T>* st,
                             QExtOsgiPluginContext* context, const QString& clazz,
                             QExtOsgiServiceTrackerCustomizer<T>* customizer);

    QExtOsgiServiceTrackerPrivate(
        QExtOsgiServiceTracker<S,T>* st,
        QExtOsgiPluginContext* context, const QExtOsgiLDAPSearchFilter& filter,
        QExtOsgiServiceTrackerCustomizer<T>* customizer);

    ~QExtOsgiServiceTrackerPrivate();

    /**
   * Returns the list of initial <code>QExtOsgiServiceReference</code>s that will be
   * tracked by this <code>QExtOsgiServiceTracker</code>.
   *
   * @param className The class name with which the service was registered, or
   *        <code>null</code> for all services.
   * @param filterString The filter criteria or <code>null</code> for all
   *        services.
   * @return The list of initial <code>QExtOsgiServiceReference</code>s.
   * @throws QExtInvalidArgumentException If the specified filterString has an
   *         invalid syntax.
   */
    QList<QExtOsgiServiceReference> getInitialReferences(const QString& className,
                                                    const QString& filterString);

    QList<QExtOsgiServiceReference> getServiceReferences_unlocked(QExtOsgiTrackedService<S,T>* t) const;

    /* set this to true to compile in debug messages */
    static const bool	DEBUG_FLAG; //	= false;

    /**
   * The Plugin Context used by this <code>QExtOsgiServiceTracker</code>.
   */
    QExtOsgiPluginContext* const	context;

    /**
   * The filter used by this <code>QExtOsgiServiceTracker</code> which specifies the
   * search criteria for the services to track.
   */
    QExtOsgiLDAPSearchFilter	filter;

    /**
   * The <code>QExtOsgiServiceTrackerCustomizer</code> for this tracker.
   */
    QExtOsgiServiceTrackerCustomizer<T>* customizer;

    /**
   * Filter string for use when adding the ServiceListener. If this field is
   * set, then certain optimizations can be taken since we don't have a user
   * supplied filter.
   */
    QString listenerFilter;

    /**
   * Class name to be tracked. If this field is set, then we are tracking by
   * class name.
   */
    QString trackClass;

    /**
   * Reference to be tracked. If this field is set, then we are tracking a
   * single QExtOsgiServiceReference.
   */
    QExtOsgiServiceReference	trackReference;

    /**
   * Tracked services: <code>QExtOsgiServiceReference</code> -> customized Object and
   * <code>QExtOsgiServiceSlotEntry</code> object
   */
    QSharedPointer<QExtOsgiTrackedService<S,T> > trackedService;

    /**
   * Accessor method for the current QExtOsgiTrackedService object. This method is only
   * intended to be used by the unsynchronized methods which do not modify the
   * trackedService field.
   *
   * @return The current Tracked object.
   */
    QSharedPointer<QExtOsgiTrackedService<S,T> > tracked() const;

    /**
   * Called by the QExtOsgiTrackedService object whenever the set of tracked services is
   * modified. Clears the cache.
   */
    /*
   * This method must not be synchronized since it is called by QExtOsgiTrackedService while
   * QExtOsgiTrackedService is synchronized. We don't want synchronization interactions
   * between the listener thread and the user thread.
   */
    void modified();

    /**
   * Cached QExtOsgiServiceReference for getServiceReference.
   */
    mutable QExtOsgiServiceReference cachedReference;

    /**
   * Cached service object for getService.
   *
   * This field is volatile since it is accessed by multiple threads.
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


#include "qextOsgiTrackedService_p.h"

#include "qextOsgiPluginContext.h"
#include "qextOsgiPluginConstants.h"
#include "qextOsgiLDAPSearchFilter.h"

//----------------------------------------------------------------------------
template<class S, class T>
const bool QExtOsgiServiceTrackerPrivate<S,T>::DEBUG_FLAG = false;

//----------------------------------------------------------------------------
template<class S, class T>
QExtOsgiServiceTrackerPrivate<S,T>::QExtOsgiServiceTrackerPrivate(
    QExtOsgiServiceTracker<S,T>* st, QExtOsgiPluginContext* context,
    const QExtOsgiServiceReference& reference,
    QExtOsgiServiceTrackerCustomizer<T>* customizer)
    : context(context), customizer(customizer), trackReference(reference),
    trackedService(0), cachedReference(0), cachedService(0), q_ptr(st)
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
        /*
     * we could only get this exception if the ServiceReference was
     * invalid
     */
        QExtInvalidArgumentException ia(QString("unexpected QExtInvalidArgumentException exception: %1").arg(e.what()));
        throw ia;
    }
}

//----------------------------------------------------------------------------
template<class S, class T>
QExtOsgiServiceTrackerPrivate<S,T>::QExtOsgiServiceTrackerPrivate(
    QExtOsgiServiceTracker<S,T>* st,
    QExtOsgiPluginContext* context, const QString& clazz,
    QExtOsgiServiceTrackerCustomizer<T>* customizer)
    : context(context), customizer(customizer), trackClass(clazz),
    trackReference(0), trackedService(0), cachedReference(0),
    cachedService(0), q_ptr(st)
{
    this->customizer = customizer ? customizer : q_func();
    this->listenerFilter = QString("(") + QExtOsgiPluginConstants::OBJECTCLASS + "="
                           + clazz + ")";
    try
    {
        this->filter = QExtOsgiLDAPSearchFilter(listenerFilter);
    }
    catch (const QExtInvalidArgumentException& e)
    {
        /*
     * we could only get this exception if the clazz argument was
     * malformed
     */
        QExtInvalidArgumentException ia(
            QString("unexpected QExtInvalidArgumentException exception: %1").arg(e.what()));
        throw ia;
    }
}

//----------------------------------------------------------------------------
template<class S, class T>
QExtOsgiServiceTrackerPrivate<S,T>::QExtOsgiServiceTrackerPrivate(
    QExtOsgiServiceTracker<S,T>* st,
    QExtOsgiPluginContext* context, const QExtOsgiLDAPSearchFilter& filter,
    QExtOsgiServiceTrackerCustomizer<T>* customizer)
    : context(context), filter(filter), customizer(customizer),
    listenerFilter(filter.toString()), trackReference(0),
    trackedService(0), cachedReference(0), cachedService(0), q_ptr(st)
{
    this->customizer = customizer ? customizer : q_func();
    if (context == 0)
    {
        throw QExtInvalidArgumentException("The plugin context cannot be null.");
    }
}

//----------------------------------------------------------------------------
template<class S, class T>
QExtOsgiServiceTrackerPrivate<S,T>::~QExtOsgiServiceTrackerPrivate()
{

}

//----------------------------------------------------------------------------
template<class S, class T>
QList<QExtOsgiServiceReference> QExtOsgiServiceTrackerPrivate<S,T>::getInitialReferences(const QString& className,
                                                                                const QString& filterString)
{
    return context->getServiceReferences(className, filterString);
}

//----------------------------------------------------------------------------
template<class S, class T>
QList<QExtOsgiServiceReference> QExtOsgiServiceTrackerPrivate<S,T>::getServiceReferences_unlocked(QExtOsgiTrackedService<S,T>* t) const
{
    if (t->size() == 0)
    {
        return QList<QExtOsgiServiceReference>();
    }
    return t->getTracked();
}

//----------------------------------------------------------------------------
template<class S, class T>
QSharedPointer<QExtOsgiTrackedService<S,T> > QExtOsgiServiceTrackerPrivate<S,T>::tracked() const
{
    return trackedService;
}

//----------------------------------------------------------------------------
template<class S, class T>
void QExtOsgiServiceTrackerPrivate<S,T>::modified()
{
    cachedReference = 0; /* clear cached value */
    cachedService = 0; /* clear cached value */
    if (DEBUG_FLAG)
    {
        qDebug() << "qextOsgiServiceTracker::modified:" << filter;
    }
}


#endif // CTKSERVICETRACKERPRIVATE_H
