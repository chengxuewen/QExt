#include "qtkealinkedqueue_p.h"
#include "qtkeainterruptiblethread_p.h"
#include "qtkeainterruptedexception_p.h"

#include <QTKCore/QTKHighPrecisionTimer>

QTKEALinkedQueue::QTKEALinkedQueue()
    : m_pHeadNode(new QTKEALinkedNode()),
      m_pLastNode(m_pHeadNode),
      m_iWaitingForTake(0)
{

}

QTKEALinkedQueue::~QTKEALinkedQueue()
{
    delete m_pHeadNode;
}

void QTKEALinkedQueue::put(QTKEARunnable *pValue)
{
    if (nullptr == pValue) {
        throw QTKInvalidArgumentException("QRunnable cannot be null");
    }
    if (QTKEAInterruptibleThread::interrupted()) {
        throw QTKEAInterruptedException();
    }
    this->insert(pValue);
}

bool QTKEALinkedQueue::offer(QTKEARunnable *pValue, long lMsecs)
{
    Q_UNUSED(lMsecs)

    if (nullptr == pValue) {
        throw QTKInvalidArgumentException("QRunnable cannot be null");
    }
    if (QTKEAInterruptibleThread::interrupted()) {
        throw QTKEAInterruptedException();
    }
    this->insert(pValue);
    return true;
}

QTKEARunnable* QTKEALinkedQueue::take()
{
    if (QTKEAInterruptibleThread::interrupted()) {
        throw QTKEAInterruptedException();
    }
    // try to extract. If fail, then enter wait-based retry loop
    QTKEARunnable *pValue = extract();
    if (pValue != 0) {
        return pValue;
    } else {
        {
            QMutexLocker mutexLocker(&m_putLock);
            try {
                ++m_iWaitingForTake;
                forever {
                    pValue = this->extract();
                    if (nullptr != pValue) {
                        --m_iWaitingForTake;
                        return pValue;
                    } else {
                        QTKEAInterruptibleThread::currentThread()->wait(&m_putLock, &m_putLockWait);
                    }
                }
            } catch(const QTKEAInterruptedException &e) {
                --m_iWaitingForTake;
                if (pValue && pValue->autoDelete() && !--pValue->m_iRef) {
                    delete pValue;
                }
                m_putLockWait.wakeOne();
                throw e;
            }
        }
    }
}

QTKEARunnable *QTKEALinkedQueue::peek() const
{
    QMutexLocker mutexLocker(&m_headLock);
    QTKEALinkedNode *pFirst = m_pHeadNode->m_pNext;
    if (pFirst) {
        return pFirst->m_pValue;
    } else {
        return nullptr;
    }
}

bool QTKEALinkedQueue::isEmpty() const
{
    QMutexLocker l(&m_headLock);
    return !(m_pHeadNode->m_pNext);
}

QTKEARunnable* QTKEALinkedQueue::poll(long lMsecs)
{
    if (QTKEAInterruptibleThread::interrupted()) throw QTKEAInterruptedException();
    QTKEARunnable* x = extract();
    if (x != 0)
        return x;
    else
    {
        QMutexLocker l(&m_putLock);
        try {
            qint64 waitTime = static_cast<qint64>(lMsecs);
            QTKHighPrecisionTimer t;
            t.start();
            ++m_iWaitingForTake;
            forever
            {
                x = extract();
                if (x != 0 || waitTime <= 0)
                {
                    --m_iWaitingForTake;
                    return x;
                }
                else
                {
                    QTKEAInterruptibleThread::currentThread()->wait(&m_putLock, &m_putLockWait, waitTime);
                    waitTime = static_cast<qint64>(lMsecs) - t.elapsedMilli();
                }
            }
        }
        catch(const QTKEAInterruptedException& ex)
        {
            --m_iWaitingForTake;
            if (x && x->autoDelete() && !--x->m_iRef) delete x;
            m_putLockWait.wakeOne();
            throw ex;
        }
    }
}

void QTKEALinkedQueue::insert(QTKEARunnable* pValue)
{
    QMutexLocker l(&m_putLock);
    QTKEALinkedNode* p = new QTKEALinkedNode(pValue);
    {
        QMutexLocker l2(&m_lastLock);
        m_pLastNode->m_pNext = p;
        m_pLastNode = p;
    }
    if (m_iWaitingForTake > 0)
    {
        m_putLockWait.wakeOne();
    }
}

QTKEARunnable* QTKEALinkedQueue::extract()
{
    QMutexLocker lock(&m_mutex);
    {
        QMutexLocker l(&m_headLock);
        QTKEARunnable* x = 0;
        QTKEALinkedNode* first(m_pHeadNode->m_pNext);
        if (first)
        {
            x = first->m_pValue;
            first->m_pValue = 0;
            delete m_pHeadNode;
            m_pHeadNode = first;
        }
        return x;
    }
}
