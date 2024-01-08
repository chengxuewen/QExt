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


#ifndef _QEXTOSGIPLUGINABSTRACTTRACKED_H
#define _QEXTOSGIPLUGINABSTRACTTRACKED_H

#include <qextUtils.h>

#include <QHash>
#include <QMutex>
#include <QWaitCondition>
#if (QT_VERSION >= QT_VERSION_CHECK(5, 15, 0))
#   include <list>
#else
#   include <QLinkedList>
#endif
#include <QVariant>
#include <QDebug>


/**
 * \ingroup PluginFramework
 *
 * Abstract class to track items. If a Tracker is reused (closed then reopened),
 * then a new QExtOsgiPluginAbstractTracked object is used. This class acts as a map of tracked
 * item -> customized object. Subclasses of this class will act as the listener
 * object for the tracker. This class is used to synchronize access to the
 * tracked items. This is not a public class. It is only for use by the
 * implementation of the Tracker class.
 *
 * @tparam S The tracked item. It is the key.
 * @tparam T The value mapped to the tracked item.
 * @tparam R The reason the tracked item is  being tracked or untracked.
 * @ThreadSafe
 */
template<class S, class T, class R>
class QExtOsgiPluginAbstractTracked : public QMutex
{

public:

    /* set this to true to compile in debug messages */
    static const bool DEBUG_FLAG; // = false;

    /**
   * QExtOsgiPluginAbstractTracked constructor.
   */
    QExtOsgiPluginAbstractTracked();

    virtual ~QExtOsgiPluginAbstractTracked();

    bool wait(unsigned long timeout);
    void wakeAll();

    /**
   * Set initial list of items into tracker before events begin to be
   * received.
   *
   * This method must be called from Tracker's open method while synchronized
   * on this object in the same synchronized block as the add listener call.
   *
   * @param list The initial list of items to be tracked. <code>null</code>
   *        entries in the list are ignored.
   * @GuardedBy this
   */
    void setInitial(const QList<S>& list);

    /**
   * Track the initial list of items. This is called after events can begin to
   * be received.
   *
   * This method must be called from Tracker's open method while not
   * synchronized on this object after the add listener call.
   *
   */
    void trackInitial();

    /**
   * Called by the owning Tracker object when it is closed.
   */
    void close();

    /**
   * Begin to track an item.
   *
   * @param item S to be tracked.
   * @param related Action related object.
   */
    void track(S item, R related);

    /**
   * Discontinue tracking the item.
   *
   * @param item S to be untracked.
   * @param related Action related object.
   */
    void untrack(S item, R related);

    /**
   * Returns the number of tracked items.
   *
   * @return The number of tracked items.
   *
   * @GuardedBy this
   */
    int size() const;

    /**
   * Returns if the tracker is empty.
   *
   * @return Whether the tracker is empty.
   *
   * @GuardedBy this
   */
    bool isEmpty() const;

    /**
   * Return the customized object for the specified item
   *
   * @param item The item to lookup in the map
   * @return The customized object for the specified item.
   *
   * @GuardedBy this
   */
    T getCustomizedObject(S item) const;

    /**
   * Return the list of tracked items.
   *
   * @return The tracked items.
   * @GuardedBy this
   */
    QList<S> getTracked() const;

    /**
   * Increment the modification count. If this method is overridden, the
   * overriding method MUST call this method to increment the tracking count.
   *
   * @GuardedBy this
   */
    virtual void modified();

    /**
   * Returns the tracking count for this <code>ServiceTracker</code> object.
   *
   * The tracking count is initialized to 0 when this object is opened. Every
   * time an item is added, modified or removed from this object the tracking
   * count is incremented.
   *
   * @GuardedBy this
   * @return The tracking count for this object.
   */
    int getTrackingCount() const;

    /**
   * Copy the tracked items and associated values into the specified map.
   *
   * @param map The map into which to copy the tracked items and associated
   *        values. This map must not be a user provided map so that user code
   *        is not executed while synchronized on this.
   * @return The specified map.
   * @GuardedBy this
   */
    QMap<S,T> copyEntries(QMap<S,T>& map) const;

    /**
   * Call the specific customizer adding method. This method must not be
   * called while synchronized on this object.
   *
   * @param item S to be tracked.
   * @param related Action related object.
   * @return Customized object for the tracked item or <code>null</code> if
   *         the item is not to be tracked.
   */
    virtual T customizerAdding(S item, const R& related) = 0;

    /**
   * Call the specific customizer modified method. This method must not be
   * called while synchronized on this object.
   *
   * @param item Tracked item.
   * @param related Action related object.
   * @param object Customized object for the tracked item.
   */
    virtual void customizerModified(S item, const R& related,
                                    T object) = 0;

    /**
   * Call the specific customizer removed method. This method must not be
   * called while synchronized on this object.
   *
   * @param item Tracked item.
   * @param related Action related object.
   * @param object Customized object for the tracked item.
   */
    virtual void customizerRemoved(S item, const R& related,
                                   T object) = 0;

    /**
   * List of items in the process of being added. This is used to deal with
   * nesting of events. Since events may be synchronously delivered, events
   * can be nested. For example, when processing the adding of a service and
   * the customizer causes the service to be unregistered, notification to the
   * nested call to untrack that the service was unregistered can be made to
   * the track method.
   *
   * Since the QList implementation is not synchronized, all access to
   * this list must be protected by the same synchronized object for
   * thread-safety.
   *
   * @GuardedBy this
   */
    QList<S> adding;

    /**
   * true if the tracked object is closed.
   *
   * This field is volatile because it is set by one thread and read by
   * another.
   */
    volatile bool	closed;

    /**
   * Initial list of items for the tracker. This is used to correctly process
   * the initial items which could be modified before they are tracked. This
   * is necessary since the initial set of tracked items are not "announced"
   * by events and therefore the event which makes the item untracked could be
   * delivered before we track the item.
   *
   * An item must not be in both the initial and adding lists at the same
   * time. An item must be moved from the initial list to the adding list
   * "atomically" before we begin tracking it.
   *
   * Since the LinkedList implementation is not synchronized, all access to
   * this list must be protected by the same synchronized object for
   * thread-safety.
   *
   * @GuardedBy this
   */
#if (QT_VERSION >= QT_VERSION_CHECK(5, 15, 0))
    std::list<S>	    initial;
#else
    QLinkedList<S>	initial;
#endif

    /**
   * Common logic to add an item to the tracker used by track and
   * trackInitial. The specified item must have been placed in the adding list
   * before calling this method.
   *
   * @param item S to be tracked.
   * @param related Action related object.
   */
    void trackAdding(S item, R related);

private:

    QWaitCondition waitCond;

    /**
   * Map of tracked items to customized objects.
   *
   * @GuardedBy this
   */
    QHash<S, T> tracked;

    /**
   * Modification count. This field is initialized to zero and incremented by
   * modified.
   *
   * @GuardedBy this
   */
    QAtomicInt trackingCount;

    bool customizerAddingFinal(S item, const T& custom);

};



//----------------------------------------------------------------------------
template<class S, class T, class R>
const bool QExtOsgiPluginAbstractTracked<S,T,R>::DEBUG_FLAG = false;

//----------------------------------------------------------------------------
template<class S, class T, class R>
QExtOsgiPluginAbstractTracked<S,T,R>::QExtOsgiPluginAbstractTracked()
{
    closed = false;
}

//----------------------------------------------------------------------------
template<class S, class T, class R>
QExtOsgiPluginAbstractTracked<S,T,R>::~QExtOsgiPluginAbstractTracked()
{

}

//----------------------------------------------------------------------------
template<class S, class T, class R>
bool QExtOsgiPluginAbstractTracked<S,T,R>::wait(unsigned long timeout)
{
    return waitCond.wait(this, timeout);
}

//----------------------------------------------------------------------------
template<class S, class T, class R>
void QExtOsgiPluginAbstractTracked<S,T,R>::wakeAll()
{
    waitCond.wakeAll();
}

//----------------------------------------------------------------------------
template<class S, class T, class R>
void QExtOsgiPluginAbstractTracked<S,T,R>::setInitial(const QList<S>& list)
{
    foreach (S item, list)
    {
        if (DEBUG_FLAG)
        {
            qDebug() << "qextOsgiPluginAbstractTracked::setInitial:" << item;
        }
        initial.push_back(item);
    }
}

//----------------------------------------------------------------------------
template<class S, class T, class R>
void QExtOsgiPluginAbstractTracked<S,T,R>::trackInitial()
{
    while (true)
    {
        S item(0);
        {
            QMutexLocker lock(this);
            if (closed || (initial.size() == 0))
            {
                /*
         * if there are no more initial items
         */
                return; /* we are done */
            }
            /*
       * move the first item from the initial list to the adding list
       * within this synchronized block.
       */
            item = qext::takeFirst(initial);
            if (tracked.value(item))
            {
                /* if we are already tracking this item */
                if (DEBUG_FLAG)
                {
                    qDebug() << "qextOsgiPluginAbstractTracked::trackInitial[already tracked]: " << item;
                }
                continue; /* skip this item */
            }
            if (adding.contains(item))
            {
                /*
         * if this item is already in the process of being added.
         */
                if (DEBUG_FLAG)
                {
                    qDebug() << "qextOsgiPluginAbstractTracked::trackInitial[already adding]: " << item;
                }
                continue; /* skip this item */
            }
            adding.push_back(item);
        }
        if (DEBUG_FLAG)
        {
            qDebug() << "qextOsgiPluginAbstractTracked::trackInitial: " << item;
        }
        trackAdding(item, R());
        /*
     * Begin tracking it. We call trackAdding
     * since we have already put the item in the
     * adding list.
     */
    }
}

//----------------------------------------------------------------------------
template<class S, class T, class R>
void QExtOsgiPluginAbstractTracked<S,T,R>::close()
{
    closed = true;
}

//----------------------------------------------------------------------------
template<class S, class T, class R>
void QExtOsgiPluginAbstractTracked<S,T,R>::track(S item, R related)
{
    T object(0);
    {
        QMutexLocker lock(this);
        if (closed)
        {
            return;
        }
        object = tracked.value(item);
        if (!object)
        { /* we are not tracking the item */
            if (adding.contains(item))
            {
                /* if this item is already in the process of being added. */
                if (DEBUG_FLAG)
                {
                    qDebug() << "qextOsgiPluginAbstractTracked::track[already adding]: " << item;
                }
                return;
            }
            adding.push_back(item); /* mark this item is being added */
        }
        else
        { /* we are currently tracking this item */
            if (DEBUG_FLAG)
            {
                qDebug() << "qextOsgiPluginAbstractTracked::track[modified]: " << item;
            }
            modified(); /* increment modification count */
        }
    }

    if (!object)
    { /* we are not tracking the item */
        trackAdding(item, related);
    }
    else
    {
        /* Call customizer outside of synchronized region */
        customizerModified(item, related, object);
        /*
     * If the customizer throws an unchecked exception, it is safe to
     * let it propagate
     */
    }
}

//----------------------------------------------------------------------------
template<class S, class T, class R>
void QExtOsgiPluginAbstractTracked<S,T,R>::untrack(S item, R related)
{
    T object(0);
    {
        QMutexLocker lock(this);
        if (qext::removeOne<S>(initial, item))
        { /* if this item is already in the list
       * of initial references to process
       */
            if (DEBUG_FLAG)
            {
                qDebug() << "qextOsgiPluginAbstractTracked::untrack[removed from initial]: " << item;
            }
            return; /* we have removed it from the list and it will not be
               * processed
               */
        }

        if (adding.removeOne(item))
        { /* if the item is in the process of
       * being added
       */
            if (DEBUG_FLAG)
            {
                qDebug() << "qextOsgiPluginAbstractTracked::untrack[being added]: " << item;
            }
            return; /*
           * in case the item is untracked while in the process of
           * adding
           */
        }
        object = tracked.take(item); /*
                     * must remove from tracker before
                     * calling customizer callback
                     */
        if (!object)
        { /* are we actually tracking the item */
            return;
        }
        modified(); /* increment modification count */
    }
    if (DEBUG_FLAG)
    {
        qDebug() << "qextOsgiPluginAbstractTracked::untrack[removed]: " << item;
    }
    /* Call customizer outside of synchronized region */
    customizerRemoved(item, related, object);
    /*
   * If the customizer throws an unchecked exception, it is safe to let it
   * propagate
   */
}

//----------------------------------------------------------------------------
template<class S, class T, class R>
int QExtOsgiPluginAbstractTracked<S,T,R>::size() const
{
    return tracked.size();
}

//----------------------------------------------------------------------------
template<class S, class T, class R>
bool QExtOsgiPluginAbstractTracked<S,T,R>::isEmpty() const
{
    return tracked.isEmpty();
}

//----------------------------------------------------------------------------
template<class S, class T, class R>
T QExtOsgiPluginAbstractTracked<S,T,R>::getCustomizedObject(S item) const
{
    return tracked.value(item);
}

//----------------------------------------------------------------------------
template<class S, class T, class R>
QList<S> QExtOsgiPluginAbstractTracked<S,T,R>::getTracked() const
{
    return tracked.keys();
}

//----------------------------------------------------------------------------
template<class S, class T, class R>
void QExtOsgiPluginAbstractTracked<S,T,R>::modified()
{
    trackingCount.ref();
}

//----------------------------------------------------------------------------
template<class S, class T, class R>
int QExtOsgiPluginAbstractTracked<S,T,R>::getTrackingCount() const
{
#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
    return trackingCount;
#elif QT_VERSION < QT_VERSION_CHECK(5,14,0)
    return trackingCount.load();
#else
    return trackingCount.loadRelaxed();
#endif
}

//----------------------------------------------------------------------------
template<class S, class T, class R>
QMap<S,T> QExtOsgiPluginAbstractTracked<S,T,R>::copyEntries(QMap<S,T>& map) const
{
    typename QHash<S,T>::ConstIterator end = tracked.end();
    for (typename QHash<S,T>::ConstIterator it = tracked.begin();
         it != end; ++it)
    {
        map.insert(it.key(), it.value());
    }
    return map;
}

//----------------------------------------------------------------------------
template<class S, class T, class R>
bool QExtOsgiPluginAbstractTracked<S,T,R>::customizerAddingFinal(S item, const T& custom)
{
    QMutexLocker lock(this);
    if (adding.removeOne(item) && !closed)
    {
        /*
     * if the item was not untracked during the customizer
     * callback
     */
        if (custom)
        {
            tracked.insert(item, custom);
            modified(); /* increment modification count */
            waitCond.wakeAll(); /* notify any waiters */
        }
        return false;
    }
    else
    {
        return true;
    }
}

//----------------------------------------------------------------------------
template<class S, class T, class R>
void QExtOsgiPluginAbstractTracked<S,T,R>::trackAdding(S item, R related)
{
    if (DEBUG_FLAG)
    {
        qDebug() << "qextOsgiPluginAbstractTracked::trackAdding:" << item;
    }
    T object(0);
    bool becameUntracked = false;
    /* Call customizer outside of synchronized region */
    try
    {
        object = customizerAdding(item, related);
        becameUntracked = this->customizerAddingFinal(item, object);
    }
    catch (...)
    {
        /*
     * If the customizer throws an exception, it will
     * propagate after the cleanup code.
     */
        this->customizerAddingFinal(item, object);
        throw;
    }

    /*
   * The item became untracked during the customizer callback.
   */
    if (becameUntracked && object)
    {
        if (DEBUG_FLAG)
        {
            qDebug() << "qextOsgiPluginAbstractTracked::trackAdding[removed]: " << item;
        }
        /* Call customizer outside of synchronized region */
        customizerRemoved(item, related, object);
        /*
     * If the customizer throws an unchecked exception, it is safe to
     * let it propagate
     */
    }
}


#endif // _QEXTOSGIPLUGINABSTRACTTRACKED_H
