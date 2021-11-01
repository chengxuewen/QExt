#include "qtkcmserializedtaskqueue_p.h"

#include <QRunnable>
#include <QDebug>

const int QTKCMSerializedTaskQueue::MAX_WAIT = 5000;

QTKCMSerializedTaskQueue::QTKCMSerializedTaskQueue(const QString& queueName)
{
    thread.setObjectName(queueName);
    moveToThread(&thread);
    connect(&thread, SIGNAL(started()), SLOT(runTasks()));
}

QTKCMSerializedTaskQueue::~QTKCMSerializedTaskQueue()
{
    thread.quit();
    waitForTask.wakeAll();
    thread.wait();
}

void QTKCMSerializedTaskQueue::put(QRunnable* newTask)
{
    {
        QMutexLocker lock(&mutex);
        tasks.push_back(newTask);
    }
    if (!thread.isRunning())
    {
        thread.start();
    }
    else
    {
        waitForTask.wakeAll();
    }
}

void QTKCMSerializedTaskQueue::runTasks() {
    QRunnable* task = nextTask(MAX_WAIT);
    while (task != 0)
    {
        task->run();
        delete task;
        task = nextTask(MAX_WAIT);
    }
}

QRunnable* QTKCMSerializedTaskQueue::nextTask(int maxWait)
{
    QMutexLocker lock(&mutex);
    if (tasks.isEmpty())
    {
        waitForTask.wait(&mutex, maxWait);
        if (tasks.isEmpty())
        {
            thread.quit();
            return 0;
        }
    }
    return tasks.takeFirst();
}
