#include "qtkeainterruptiblethread_p.h"
#include "qtkeainterruptedexception_p.h"

#include <QRunnable>
#include <QDebug>

QTKEAInterruptibleThread::QTKEAInterruptibleThread(QTKEARunnable *pCommand, QObject *pParent)
    : QThread(pParent),
      m_pCommand(pCommand)
{
    this->setObjectName(QString("QTKEAInterruptibleThread") + QString::number(reinterpret_cast<qint64>(pCommand)));
}

void QTKEAInterruptibleThread::run()
{
    if (m_pCommand) {
        const bool bAutoDelete = m_pCommand->autoDelete();
        m_pCommand->run();
        if (bAutoDelete && !--m_pCommand->m_iRef) {
            delete m_pCommand;
        }
    } else {
        QThread::run();
    }
}

QTKEAInterruptibleThread* QTKEAInterruptibleThread::currentThread()
{
    return qobject_cast<QTKEAInterruptibleThread*>(QThread::currentThread());
}

void QTKEAInterruptibleThread::wait(QMutex *pMutex, QWaitCondition *pWaitCond, unsigned long ulTime)
{
    m_currWaitCond.testAndSetOrdered(0, pWaitCond);
    m_isWaiting.testAndSetOrdered(0,1);
    pWaitCond->wait(pMutex, ulTime == 0 ? ULONG_MAX : ulTime);
    m_isWaiting.testAndSetOrdered(1,0);
    m_currWaitCond.fetchAndStoreOrdered(0);

    if (m_interrupted.fetchAndAddOrdered(0)) {
        m_interrupted.testAndSetOrdered(1, 0);
        throw QTKEAInterruptedException();
    }
}

void QTKEAInterruptibleThread::join()
{
    this->QThread::wait();
}

void QTKEAInterruptibleThread::interrupt()
{
    if (m_isWaiting.fetchAndAddOrdered(0) && this->isRunning()) {
        m_interrupted.testAndSetOrdered(0, 1);
        if (QWaitCondition *pWaitCond = m_currWaitCond.fetchAndStoreOrdered(0)) {
            pWaitCond->wakeAll();
        }
    } else {
        if (this->isRunning()) {
            m_interrupted.testAndSetOrdered(0, 1);
        }
    }
}

bool QTKEAInterruptibleThread::interrupted()
{
    if (QTKEAInterruptibleThread *pThread = qobject_cast<QTKEAInterruptibleThread*>(QThread::currentThread())) {
        return pThread->m_interrupted.fetchAndStoreOrdered(0);
    }
    return false;
}

bool QTKEAInterruptibleThread::isInterrupted() const
{
    return m_interrupted.fetchAndAddOrdered(0);
}
