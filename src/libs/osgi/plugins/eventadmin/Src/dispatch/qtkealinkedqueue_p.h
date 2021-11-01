#ifndef QTKEALINKEDQUEUE_P_H
#define QTKEALINKEDQUEUE_P_H

#include "qtkeachannel_p.h"
#include "qtkeainterruptiblethread_p.h"

#include <QMutex>
#include <QWaitCondition>

/** A standard linked list node used in various queue classes **/
struct QTKEALinkedNode
{
    QTKEALinkedNode(QTKEARunnable *bValue = nullptr)
        : m_pValue(bValue),
          m_pNext(nullptr)
    {
        if (bValue && bValue->autoDelete()) {
            ++bValue->m_iRef;
        }
    }

    QTKEALinkedNode(QTKEARunnable *bValue, QTKEALinkedNode *bNext)
        : m_pValue(bValue),
          m_pNext(bNext)
    {
        if (bValue && bValue->autoDelete()) {
            ++bValue->m_iRef;
        }
    }

    ~QTKEALinkedNode()
    {
        if (m_pValue && m_pValue->autoDelete()) {
            --m_pValue->m_iRef;
        }
    }

    QTKEARunnable *m_pValue;
    QTKEALinkedNode *m_pNext;
};

/**
 * A linked list based channel implementation.
 * The algorithm avoids contention between puts
 * and takes when the queue is not empty.
 * Normally a put and a take can proceed simultaneously.
 * (Although it does not allow multiple concurrent puts or takes.)
 * This class tends to perform more efficently than
 * other QTKEAChannel implementations in producer/consumer
 * applications.
 */
class QTKEALinkedQueue : public QTKEAChannel
{
public:
    QTKEALinkedQueue();
    ~QTKEALinkedQueue();

    void put(QTKEARunnable *pValue);

    bool offer(QTKEARunnable *pValue, long lMsecs);

    QTKEARunnable *take();

    QTKEARunnable *peek() const;

    bool isEmpty() const;

    QTKEARunnable *poll(long lMsecs);

protected:
    /** Main mechanics for put/offer **/
    void insert(QTKEARunnable *pValue);

    /** Main mechanics for take/poll **/
    QTKEARunnable *extract();

protected:
    /**
   * Dummy header node of list. The first actual node, if it exists, is always
   * at head_->next. After each take, the old first node becomes the head.
   **/
    QTKEALinkedNode *m_pHeadNode;

    mutable QMutex m_headLock;
    QMutex m_mutex;

    /**
   * Helper monitor for managing access to last node.
   **/
    QMutex m_putLock;
    QWaitCondition m_putLockWait;

    /**
   * The last node of list. put() appends to list, so modifies last_
   **/
    QTKEALinkedNode *m_pLastNode;
    QMutex m_lastLock;

    /**
   * The number of threads waiting for a take.
   * Notifications are provided in put only if greater than zero.
   * The bookkeeping is worth it here since in reasonably balanced
   * usages, the notifications will hardly ever be necessary, so
   * the call overhead to notify can be eliminated.
   **/
    int m_iWaitingForTake;
};

#endif // QTKEALINKEDQUEUE_P_H
