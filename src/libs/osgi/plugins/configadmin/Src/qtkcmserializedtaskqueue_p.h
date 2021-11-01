#ifndef QTKCMSERIALIZEDTASKQUEUE_P_H
#define QTKCMSERIALIZEDTASKQUEUE_P_H

#include <QList>
#include <QThread>
#include <QWaitCondition>
#include <QMutex>

class QRunnable;

/**
 * QTKCMSerializedTaskQueue is a utility class that will allow asynchronous but serialized execution of tasks
 */
class QTKCMSerializedTaskQueue : public QObject
{
    Q_OBJECT

public:
    QTKCMSerializedTaskQueue(const QString& queueName);
    ~QTKCMSerializedTaskQueue();

    void put(QRunnable* newTask);

protected Q_SLOTS:
    void runTasks();

protected:
    QRunnable* nextTask(int maxWait);

private:
    static const int MAX_WAIT; // = 5000
    QList<QRunnable*> tasks;
    QThread thread;
    QMutex mutex;
    QWaitCondition waitForTask;
};

#endif // QTKCMSERIALIZEDTASKQUEUE_P_H
