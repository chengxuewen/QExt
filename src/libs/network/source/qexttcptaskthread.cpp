#include <qexttcptaskthread.h>
#include <qexttcptaskthread_p.h>
#include <qexttcptaskthreadpool.h>
#include <qexttcptaskbase.h>

#include <QDebug>
#include <QThread>

QEXTTcpTaskThreadPrivate::QEXTTcpTaskThreadPrivate(QEXTTcpTaskThread *qq)
    : QEXTTcpThreadBasePrivate(qq)
{

}

QEXTTcpTaskThreadPrivate::~QEXTTcpTaskThreadPrivate()
{

}



QEXTTcpTaskThread::QEXTTcpTaskThread(QEXTTcpTaskThreadPool *threadPool)
    : QEXTTcpThreadBase(*(new QEXTTcpTaskThreadPrivate(this)), threadPool)
{

}


QEXTTcpTaskThread::~QEXTTcpTaskThread()
{

}

void QEXTTcpTaskThread::quit()
{
    QEXT_D(QEXTTcpTaskThread);
    QWriteLocker writeLocker(&d->m_quitLock);
    if (!d->m_isQuit) {
        d->m_isQuit = true;
    }
}

QEXTTcpThreadPoolBase *QEXTTcpTaskThread::tcpThreadPool() const
{
    QEXT_DC(QEXTTcpTaskThread);
    return d->m_threadPool.data();
}

void QEXTTcpTaskThread::fetchTask()
{
    if (!this->isQuit()) {
        QEXT_D(QEXTTcpTaskThread);
        QMutexLocker mutexLocker(&d->m_taskPoolMutex);
        qDebug() << "QEXTTcpTaskThread::fetchTask():thread=" << this->thread();
        qDebug() << "QEXTTcpTaskThread::fetchTask():loadAverage=" << this->loadAverage();
        if (!d->m_taskPool.isNull()) {
            QEXTTcpTaskBase *task = d->m_taskPool->dequeueTask();
            if (task) {
                qDebug() << "QEXTTcpTaskThread::fetchTask():task=" << task;
                d->updateRunningFlag(true);
                d->m_threadPool->setTcpThreadWorking(this);
                if (!task->run()) {
                    emit this->taskErrorString(task->errorString());
                }
                d->m_taskPool->recoveryTask(task);
                d->m_threadPool->setTcpThreadIdle(this);
                d->updateRunningFlag(false);
            }
        } else {
            qCritical() << "QEXTTcpTaskThread::fetchTask():m_taskPool.isNull()";
        }
        if (this->isQuit()) {
            connect(this, SIGNAL(destroyed(QObject*)), this->thread(), SLOT(deleteLater()));
            this->thread()->quit();
            this->thread()->wait();
            this->deleteLater();
        }
    }
}
