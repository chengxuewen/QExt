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

#ifndef QTKPLUGINABSTRACTTRACKED_P_H
#define QTKPLUGINABSTRACTTRACKED_P_H

#include "qtkpluginframework_global.h"

#include <QHash>
#include <QMutex>
#include <QWaitCondition>
#include <QLinkedList>
#include <QVariant>
#include <QDebug>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

/**
 * @ingroup QTKPluginFramework
 * Abstract class to track items. If a Tracker is reused (closed then reopened),
 * then a new QTKPluginAbstractTracked object is used. This class acts as a map of tracked
 * item -> customized object. Subclasses of this class will act as the listener
 * object for the tracker. This class is used to synchronize access to the
 * tracked items. This is not a public class. It is only for use by the
 * implementation of the Tracker class.
 *
 * @param S The tracked item. It is the key.
 * @param T The value mapped to the tracked item.
 * @param R The reason the tracked item is  being tracked or untracked.
 * @remarks This template class is thread safe.
 */
template<class S, class T, class R>
        class QTKPluginAbstractTracked : public QMutex
{
public:
    /**
     * @brief QTKPluginAbstractTracked
     * QTKPluginAbstractTracked constructor.
     */
    QTKPluginAbstractTracked();
    virtual ~QTKPluginAbstractTracked();

    bool wait(unsigned long ulTimeout);
    void wakeAll();

    /**
     * @brief setInitial
     * Set initial list of items into tracker before events begin to be
     * received.
     *
     * This method must be called from Tracker's open method while synchronized
     * on this object in the same synchronized block as the add listener call.
     *
     * @param list The initial list of items to be tracked. <code>null</code>
     *        entries in the list are ignored.
     */
    void setInitial(const QList<S> &list);

    /**
     * @brief trackInitial
     * Track the initial list of items. This is called after events can begin to
     * be received.
     *
     * This method must be called from Tracker's open method while not
     * synchronized on this object after the add listener call.
     */
    void trackInitial();

    /**
     * @brief close
     * Called by the owning Tracker object when it is closed.
     */
    void close();

    /**
     * @brief track
     * Begin to track an item.
     *
     * @param item S to be tracked.
     * @param related Action related object.
     */
    void track(S item, R related);

    /**
     * @brief untrack
     * Discontinue tracking the item.
     *
     * @param item S to be untracked.
     * @param related Action related object.
     */
    void untrack(S item, R related);

    /**
     * @brief size
     * Returns the number of tracked items.
     *
     * @return The number of tracked items.
     */
    int size() const;

    /**
     * @brief isEmpty
     * Returns if the tracker is empty.
     *
     * @return Whether the tracker is empty.
     */
    bool isEmpty() const;

    /**
     * @brief getCustomizedObject
     * Return the customized object for the specified item
     *
     * @param item The item to lookup in the map
     * @return The customized object for the specified item.
     */
    T getCustomizedObject(S item) const;

    /**
     * @brief getTracked
     * Return the list of tracked items.
     *
     * @return The tracked items.
     */
    QList<S> getTracked() const;

    /**
     * @brief getTrackingCount
     * Returns the tracking count for this <code>ServiceTracker</code> object.
     *
     * The tracking count is initialized to 0 when this object is opened. Every
     * time an item is added, modified or removed from this object the tracking
     * count is incremented.
     *
     * @return The tracking count for this object.
     */
    int getTrackingCount() const;

    /**
     * @brief trackAdding
     * Common logic to add an item to the tracker used by track and
     * trackInitial. The specified item must have been placed in the adding list
     * before calling this method.
     *
     * @param item S to be tracked.
     * @param related Action related object.
     */
    void trackAdding(S item, R related);

    /**
     * @brief copyEntries
     * Copy the tracked items and associated values into the specified map.
     *
     * @param map The map into which to copy the tracked items and associated
     *        values. This map must not be a user provided map so that user code
     *        is not executed while synchronized on this.
     * @return The specified map.
     */
    QMap<S,T> copyEntries(QMap<S,T> &map) const;

    /**
     * @brief modified
     * Increment the modification count. If this method is overridden, the
     * overriding method MUST call this method to increment the tracking count.
     */
    virtual void modified();

    /**
     * @brief customizerAdding
     * Call the specific customizer adding method. This method must not be
     * called while synchronized on this object.
     *
     * @param item S to be tracked.
     * @param related Action related object.
     * @return Customized object for the tracked item or <code>null</code> if
     *         the item is not to be tracked.
     */
    virtual T customizerAdding(S item, const R &related) = 0;

    /**
     * @brief customizerModified
     * Call the specific customizer modified method. This method must not be
     * called while synchronized on this object.
     *
     * @param item Tracked item.
     * @param related Action related object.
     * @param object Customized object for the tracked item.
     */
    virtual void customizerModified(S item, const R &related, T object) = 0;

    /**
     * @brief customizerRemoved
     * Call the specific customizer removed method. This method must not be
     * called while synchronized on this object.
     *
     * @param item Tracked item.
     * @param related Action related object.
     * @param object Customized object for the tracked item.
     */
    virtual void customizerRemoved(S item, const R &related, T object) = 0;

    /**
     * @brief m_listAdding
     * List of items in the process of being added. This is used to deal with
     * nesting of events. Since events may be synchronously delivered, events
     * can be nested. For example, when processing the adding of a service and
     * the customizer causes the service to be unregistered, notification to the
     * nested call to untrack that the service was unregistered can be made to
     * the track method.
     *
     * Since the QList implementation is not synchronized, all access to this
     * list must be protected by the same synchronized object for thread-safety.
     */
    QList<S> m_listAdding;

    /**
     * @brief m_bClosed
     * true if the tracked object is closed.
     *
     * This field is volatile because it is set by one thread and read by another.
     */
    volatile bool m_bClosed;

    /**
     * @brief m_listInitial
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
     */
    QLinkedList<S> m_listInitial;

    /**
     * @brief sm_bDebugFlag
     * set this to true to compile in debug messages
     */
    static const bool sm_bDebugFlag; // = false;

private:
    bool customizerAddingFinal(S item, const T &custom);

    QWaitCondition m_waitCondition;

    /**
     * @brief m_mapTracked
     * Map of tracked items to customized objects.
     */
    QHash<S, T> m_mapTracked;

    /**
     * @brief m_trackingCount
     * Modification count. This field is initialized to zero and incremented by modified.
     */
    QAtomicInt m_trackingCount;
};

template<class S, class T, class R>
const bool QTKPluginAbstractTracked<S,T,R>::sm_bDebugFlag = false;

template<class S, class T, class R>
QTKPluginAbstractTracked<S,T,R>::QTKPluginAbstractTracked()
{
    m_bClosed = false;
}

template<class S, class T, class R>
QTKPluginAbstractTracked<S,T,R>::~QTKPluginAbstractTracked()
{

}

template<class S, class T, class R>
bool QTKPluginAbstractTracked<S,T,R>::wait(unsigned long ulTimeout)
{
    return m_waitCondition.wait(this, ulTimeout);
}

template<class S, class T, class R>
void QTKPluginAbstractTracked<S,T,R>::wakeAll()
{
    m_waitCondition.wakeAll();
}

template<class S, class T, class R>
void QTKPluginAbstractTracked<S,T,R>::setInitial(const QList<S> &list)
{
    foreach (S item, list) {
        if (sm_bDebugFlag) {
            qDebug() << "QTKPluginAbstractTracked::setInitial:" << item;
        }
        m_listInitial.push_back(item);
    }
}

template<class S, class T, class R>
void QTKPluginAbstractTracked<S,T,R>::trackInitial()
{
    while (true) {
        S item(0);
        {
            QMutexLocker lock(this);
            if (m_bClosed || (m_listInitial.size() == 0)) {
                return; /* we are done */
            }

            item = m_listInitial.takeFirst();
            if (m_mapTracked.value(item)) {
                if (sm_bDebugFlag) {
                    qDebug() << "QTKPluginAbstractTracked::trackInitial[already tracked]: " << item;
                }
                continue; /* skip this item */
            }
            if (m_listAdding.contains(item)) {
                if (sm_bDebugFlag) {
                    qDebug() << "QTKPluginAbstractTracked::trackInitial[already adding]: " << item;
                }
                continue; /* skip this item */
            }
            m_listAdding.push_back(item);
        }
        if (sm_bDebugFlag) {
            qDebug() << "QTKPluginAbstractTracked::trackInitial: " << item;
        }
        this->trackAdding(item, R());
    }
}

template<class S, class T, class R>
void QTKPluginAbstractTracked<S,T,R>::close()
{
    m_bClosed = true;
}

template<class S, class T, class R>
void QTKPluginAbstractTracked<S,T,R>::track(S item, R related)
{
    T object(0);
    {
        QMutexLocker lock(this);
        if (m_bClosed) {
            return;
        }
        object = m_mapTracked.value(item);
        if (!object) { /* we are not tracking the item */
            if (m_listAdding.contains(item)) {
                /* if this item is already in the process of being added. */
                if (sm_bDebugFlag) {
                    qDebug() << "QTKPluginAbstractTracked::track[already adding]: " << item;
                }
                return;
            }
            m_listAdding.push_back(item); /* mark this item is being added */
        } else { /* we are currently tracking this item */
            if (sm_bDebugFlag) {
                qDebug() << "QTKPluginAbstractTracked::track[modified]: " << item;
            }
            this->modified(); /* increment modification count */
        }
    }

    if (!object) { /* we are not tracking the item */
        this->trackAdding(item, related);
    } else {
        this->customizerModified(item, related, object);
    }
}

/**
 *
 */
template<class S, class T, class R>
void QTKPluginAbstractTracked<S,T,R>::untrack(S item, R related)
{
    T object(0);
    {
        QMutexLocker lock(this);
        if (m_listInitial.removeOne(item)) {
            if (sm_bDebugFlag) {
                qDebug() << "QTKPluginAbstractTracked::untrack[removed from initial]: " << item;
            }
            return;
        }

        if (m_listAdding.removeOne(item)) {
            if (sm_bDebugFlag) {
                qDebug() << "QTKPluginAbstractTracked::untrack[being added]: " << item;
            }
            return;
        }
        object = m_mapTracked.take(item);
        if (!object) {
            return;
        }
        this->modified();
    }
    if (sm_bDebugFlag) {
        qDebug() << "QTKPluginAbstractTracked::untrack[removed]: " << item;
    }
    this->customizerRemoved(item, related, object);
}

template<class S, class T, class R>
int QTKPluginAbstractTracked<S,T,R>::size() const
{
    return m_mapTracked.size();
}

template<class S, class T, class R>
bool QTKPluginAbstractTracked<S,T,R>::isEmpty() const
{
    return m_mapTracked.isEmpty();
}

template<class S, class T, class R>
T QTKPluginAbstractTracked<S,T,R>::getCustomizedObject(S item) const
{
    return m_mapTracked.value(item);
}

template<class S, class T, class R>
QList<S> QTKPluginAbstractTracked<S,T,R>::getTracked() const
{
    return m_mapTracked.keys();
}

template<class S, class T, class R>
void QTKPluginAbstractTracked<S,T,R>::modified()
{
    m_trackingCount.ref();
}

template<class S, class T, class R>
int QTKPluginAbstractTracked<S,T,R>::getTrackingCount() const
{
#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
    return trackingCount;
#else
    return m_trackingCount.load();
#endif
}

template<class S, class T, class R>
QMap<S,T> QTKPluginAbstractTracked<S,T,R>::copyEntries(QMap<S,T> &map) const
{
    typename QHash<S,T>::ConstIterator end = m_mapTracked.end();
    for (typename QHash<S,T>::ConstIterator it = m_mapTracked.begin(); it != end; ++it) {
        map.insert(it.key(), it.value());
    }
    return map;
}

template<class S, class T, class R>
bool QTKPluginAbstractTracked<S,T,R>::customizerAddingFinal(S item, const T &custom)
{
    QMutexLocker lock(this);
    if (m_listAdding.removeOne(item) && !m_bClosed) {
        if (custom) {
            m_mapTracked.insert(item, custom);
            this->modified(); /* increment modification count */
            m_waitCondition.wakeAll(); /* notify any waiters */
        }
        return false;
    }else {
        return true;
    }
}

template<class S, class T, class R>
void QTKPluginAbstractTracked<S,T,R>::trackAdding(S item, R related)
{
    if (sm_bDebugFlag) {
        qDebug() << "QTKPluginAbstractTracked::trackAdding:" << item;
    }
    T object(0);
    bool bBecameUntracked = false;
    try {
        object = customizerAdding(item, related);
        bBecameUntracked = this->customizerAddingFinal(item, object);
    } catch (...) {
        this->customizerAddingFinal(item, object);
        throw;
    }

    if (bBecameUntracked && object) {
        if (sm_bDebugFlag) {
            qDebug() << "QTKPluginAbstractTracked::trackAdding[removed]: " << item;
        }
        this->customizerRemoved(item, related, object);
    }
}

QTK_PLUGINFRAMEWORK_END_NAMESPACE

#endif // QTKPLUGINABSTRACTTRACKED_P_H
