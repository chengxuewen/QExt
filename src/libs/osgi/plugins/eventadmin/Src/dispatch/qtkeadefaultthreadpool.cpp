#include "qtkeadefaultthreadpool_p.h"
#include "qtkealinkedqueue_p.h"
#include "qtkeainterruptedexception_p.h"
#include "../qtkeventadminactivator_p.h"
#include "../tasks/qtkeasyncthread_p.h"

struct QTKEASyncThreadFactory : public QTKEAThreadFactory
{
    QTKEAInterruptibleThread *newThread(QTKEARunnable *pCommand) {
        QTKEAInterruptibleThread *pThread = new QTKEASyncThread(pCommand);
        //thread->setPriority(QThread::NormalPriority);
        //thread->setDaemon(true);
        return pThread;
    }
};

struct QTKEAAsyncThreadFactory : public QTKEAThreadFactory
{
    QTKEAInterruptibleThread *newThread(QTKEARunnable *pCommand) {
        QTKEAInterruptibleThread *pThread = new QTKEAInterruptibleThread(pCommand);
        //thread->setPriority(QThread::NormalPriority);
        //thread->setDaemon(false);
        return pThread;
    }
};

QTKEADefaultThreadPool::QTKEADefaultThreadPool(int iPoolSize, bool bSyncThreads)
    : QTKEAPooledExecutor(new QTKEALinkedQueue())
{
    if (bSyncThreads) {
        delete this->setThreadFactory(new QTKEASyncThreadFactory());
    } else {
        delete this->setThreadFactory(new QTKEAAsyncThreadFactory());
    }

    this->configure(iPoolSize);
    this->setKeepAliveTime(60000);
    this->runWhenBlocked();
}

void QTKEADefaultThreadPool::configure(int iPoolSize)
{
    this->setMinimumPoolSize(iPoolSize);
    this->setMaximumPoolSize(iPoolSize + 10);
}

void QTKEADefaultThreadPool::close()
{
    this->shutdownNow();

    try {
        this->awaitTerminationAfterShutdown();
    } catch (const QTKEAInterruptedException &) {
        // ignore this
    }
}

void QTKEADefaultThreadPool::executeTask(QTKEARunnable *pTask)
{
    try {
        this->execute(pTask);
    } catch (const std::exception &e) {
        QTK_WARN_EXC(QTKEventAdminActivator::getLogService(), &e) << "Exception: " << e.what();
        // ignore this
    }
}
