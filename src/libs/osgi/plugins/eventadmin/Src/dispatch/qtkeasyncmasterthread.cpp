#include "qtkeasyncmasterthread_p.h"

#include <QRunnable>
#include <QDebug>

QTKEASyncMasterThread::QTKEASyncMasterThread()
    : m_pCommand(nullptr)
{
    m_thread.setObjectName("QTKEASyncMasterThread");
    moveToThread(&m_thread);
    m_thread.start();
}

void QTKEASyncMasterThread::syncRun(QRunnable *pCommand)
{
    if (QTKEAInterruptibleThread::currentThread() != &m_thread) {
        QMutexLocker lock(&m_mutex);
        m_pCommand = pCommand;
        QMetaObject::invokeMethod(this, "runCommand", Qt::QueuedConnection);
        m_waitCond.wait(&m_mutex);
    } else {
        qWarning() << "This method is not intended to be called from thread" << m_thread.objectName();
    }
}

void QTKEASyncMasterThread::runCommand()
{
    if (m_pCommand) {
        QMutexLocker lock(&m_mutex);
        m_pCommand->run();
        m_waitCond.wakeOne();
    }
}

void QTKEASyncMasterThread::stop()
{
    m_thread.quit();
    m_thread.join();
}
