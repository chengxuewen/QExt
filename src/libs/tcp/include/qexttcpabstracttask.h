#ifndef QEXTTCPABSTRACTTASK_H
#define QEXTTCPABSTRACTTASK_H

#include <qexttcpglobal.h>
#include <qexttcpabstractpacket.h>



class QEXTTcpAbstractTaskPool;
class QEXTTcpAbstractTaskPrivate;
class QEXT_TCP_API QEXTTcpAbstractTask : public QEXTObject
{
public:
    QEXTTcpAbstractTask(QEXTTcpAbstractTaskPool *taskPool, QObject *parent = QEXT_NULLPTR);
    QEXTTcpAbstractTask(QEXTTcpAbstractTaskPrivate &dd, QEXTTcpAbstractTaskPool *taskPool, QObject *parent = QEXT_NULLPTR);
    ~QEXTTcpAbstractTask();

    QEXTTcpAbstractTaskPool *taskPool() const;
    quint64 id() const;
    QDateTime timestamp() const;

    bool isFinished() const;
    bool isErrored() const;
    QString errorString() const;

    virtual bool run() = 0;

protected:
    virtual void setErrorString(const QString &string);
    virtual void setFinished(const bool &finished);

private:
    QEXT_DECLARE_PRIVATE(QEXTTcpAbstractTask)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpAbstractTask)
};


class QEXT_TCP_API QEXTTcpAbstractTaskPool : public QObject
{
    Q_OBJECT
public:
    QEXTTcpAbstractTaskPool(QObject *parent = QEXT_NULLPTR) : QObject(parent) {}
    ~QEXTTcpAbstractTaskPool() {}

    virtual bool isTaskEmpty() const = 0;
    virtual int taskCount() const = 0;

    virtual QList<QEXTTcpAbstractTask *> allUnfinishedTasks() const = 0;
    virtual QList<QEXTTcpAbstractTask *> allExpiredTasks() const = 0;

    virtual QEXTTcpAbstractPacketParser *packetParser() const = 0;
    virtual void setPacketParser(QEXTTcpAbstractPacketParser *packetParser) = 0;

    virtual void parsePacket(QEXTTcpAbstractPacket *packet) = 0;
    virtual void sendPacket(QEXTTcpAbstractPacket *packet) = 0;

    virtual void enqueueTask(QEXTTcpAbstractTask *task) = 0;
    virtual QEXTTcpAbstractTask *dequeueTask() = 0;
    virtual void recoveryTask(QEXTTcpAbstractTask *task) = 0;

Q_SIGNALS:
    void newTaskReady();
    void newPacketReady(QEXTTcpAbstractPacket *packet);
};



#endif // QEXTTCPABSTRACTTASK_H
