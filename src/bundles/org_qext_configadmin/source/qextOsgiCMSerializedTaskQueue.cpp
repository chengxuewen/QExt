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


#include "qextOsgiCMSerializedTaskQueue_p.h"

#include <QRunnable>
#include <QDebug>

const int QExtOsgiCMSerializedTaskQueue::MAX_WAIT = 5000;

QExtOsgiCMSerializedTaskQueue::QExtOsgiCMSerializedTaskQueue(const QString& queueName)
{
    thread.setObjectName(queueName);
    moveToThread(&thread);
    connect(&thread, SIGNAL(started()), SLOT(runTasks()));
}

QExtOsgiCMSerializedTaskQueue::~QExtOsgiCMSerializedTaskQueue()
{
    thread.quit();
    waitForTask.wakeAll();
    thread.wait();
}

void QExtOsgiCMSerializedTaskQueue::put(QRunnable* newTask)
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

void QExtOsgiCMSerializedTaskQueue::runTasks()
{
    QRunnable* task = nextTask(MAX_WAIT);
    while (task != 0)
    {
        task->run();
        delete task;
        task = nextTask(MAX_WAIT);
    }
}

QRunnable* QExtOsgiCMSerializedTaskQueue::nextTask(int maxWait)
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
