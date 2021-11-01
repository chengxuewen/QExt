#include "qtkeacyclicbarrier_p.h"
#include "qtkeatimeoutexception_p.h"
#include "qtkeabrokenbarrierexception_p.h"
#include "../dispatch/qtkeainterruptiblethread_p.h"
#include "../dispatch/qtkeainterruptedexception_p.h"

#include <QTKCore/QTKHighPrecisionTimer>

#include <QRunnable>
#include <QDebug>

QTKEACyclicBarrier::QTKEACyclicBarrier(int iParties, QTKEARunnable *pCommand)
    : m_iParties(iParties),
      m_bBroken(false),
      m_pBarrierCommand(pCommand),
      m_iCount(iParties),
      m_iResets(0)
{
    if (iParties <= 0) {
        throw QTKInvalidArgumentException("parties cannot be negative");
    }
    if (m_pBarrierCommand) {
        ++m_pBarrierCommand->m_iRef;
    }
}

QTKEARunnable *QTKEACyclicBarrier::setBarrierCommand(QTKEARunnable *pCommand)
{
    QMutexLocker lock(&m_mutex);
    QTKEARunnable *pOld = m_pBarrierCommand;
    --pOld->m_iRef;
    m_pBarrierCommand = pCommand;
    ++m_pBarrierCommand->m_iRef;
    return pOld;
}

bool QTKEACyclicBarrier::broken() const
{
    QMutexLocker lock(&m_mutex);
    return m_bBroken;
}

void QTKEACyclicBarrier::restart()
{
    QMutexLocker lock(&m_mutex);
    m_bBroken = false;
    ++m_iResets;
    m_iCount = m_iParties;
    m_waitCond.wakeAll();
}

int QTKEACyclicBarrier::parties() const
{
    return m_iParties;
}

int QTKEACyclicBarrier::barrier()
{
    return this->doBarrier(false, 0);
}

int QTKEACyclicBarrier::attemptBarrier(long lMsecs)
{
    return this->doBarrier(true, lMsecs);
}

int QTKEACyclicBarrier::doBarrier(bool bTimed, long lMsecs)
{
    QMutexLocker lock(&m_mutex);
    int iIndex = --m_iCount;

    QTKEAInterruptibleThread *pCurrThread = QTKEAInterruptibleThread::currentThread();
    Q_ASSERT(pCurrThread != 0); // QTKEACyclicBarrier can only be used with QTKEAInterruptibleThread

    if (m_bBroken) {
        throw QTKEABrokenBarrierException(iIndex);
    } else if (QTKEAInterruptibleThread::interrupted()) {
        m_bBroken = true;
        m_waitCond.wakeAll();
        throw QTKEAInterruptedException();
    } else if (iIndex == 0) { // tripped
        m_iCount = m_iParties;
        ++m_iResets;
        m_waitCond.wakeAll();
        try {
            if (m_pBarrierCommand) {
                const bool bAutoDelete = m_pBarrierCommand->autoDelete();
                m_pBarrierCommand->run();
                if (bAutoDelete && !--m_pBarrierCommand->m_iRef) {
                    delete m_pBarrierCommand;
                }
            }
            return 0;
        } catch (...) {
            m_bBroken = true;
            return 0;
        }
    } else if (bTimed && lMsecs <= 0) {
        m_bBroken = true;
        m_waitCond.wakeAll();
        throw QTKEATimeoutException(lMsecs);
    } else { // wait until next reset
        int iResets = m_iResets;
        QTKHighPrecisionTimer timer;
        timer.start();
        qint64 liWaitTime = static_cast<qint64>(lMsecs);
        forever {
            try {
                pCurrThread->wait(&m_mutex, &m_waitCond, liWaitTime);
            } catch (const QTKEAInterruptedException &e) {
                m_mutex.lock();
                // Only claim that broken if interrupted before reset
                if (m_iResets == iResets) {
                    m_bBroken = true;
                    m_waitCond.wakeAll();
                    throw e;
                } else {
                    pCurrThread->interrupt(); // propagate
                }
            }

            if (m_bBroken) {
                throw QTKEABrokenBarrierException(iIndex);
            } else if (iResets != m_iResets) {
                return iIndex;
            } else if (bTimed) {
                liWaitTime = static_cast<qint64>(lMsecs) - timer.elapsedMilli();
                if  (liWaitTime <= 0) {
                    m_bBroken = true;
                    m_waitCond.wakeAll();
                    throw QTKEATimeoutException(lMsecs);
                }
            }
        }
    }
    return 0; // will never be reached
}
