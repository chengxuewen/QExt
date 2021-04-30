#ifndef QEXTTCPTASKBASE_H
#define QEXTTCPTASKBASE_H

#include <qextnetworkglobal.h>
#include <qexttcppacketbase.h>

class QEXTTcpTaskPoolBase;
class QEXTTcpTaskBasePrivate;
class QEXT_NETWORK_API QEXTTcpTaskBase : public QEXTObject
{
public:
    QEXTTcpTaskBase(QEXTTcpTaskPoolBase *taskPool, QObject *parent = QEXT_NULLPTR);
    QEXTTcpTaskBase(QEXTTcpTaskBasePrivate &dd, QEXTTcpTaskPoolBase *taskPool, QObject *parent = QEXT_NULLPTR);
    ~QEXTTcpTaskBase();

    QEXTTcpTaskPoolBase *taskPool() const;
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
    QEXT_DECLARE_PRIVATE(QEXTTcpTaskBase)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpTaskBase)
};


class QEXT_NETWORK_API QEXTTcpTaskPoolBase : public QObject
{
    Q_OBJECT
public:
    QEXTTcpTaskPoolBase(QObject *parent = QEXT_NULLPTR) : QObject(parent) {}
    ~QEXTTcpTaskPoolBase() {}

    virtual bool isTaskEmpty() const = 0;
    virtual int taskCount() const = 0;
    virtual QEXTTcpTaskBase *dequeueTask() = 0;

    virtual QList<QEXTTcpTaskBase *> allUnfinishedTasks() const = 0;
    virtual QList<QEXTTcpTaskBase *> allExpiredTasks() const = 0;

    virtual QEXTTcpPacketParserBase *packetParser() const = 0;
    virtual void setPacketParser(QEXTTcpPacketParserBase *packetParser) = 0;

    virtual void enqueuePacket(QEXTTcpPacketBase *packet) = 0;
    virtual void sendPacket(QEXTTcpPacketBase *packet) = 0;
    virtual void recoveryTask(QEXTTcpTaskBase *task) = 0;

Q_SIGNALS:
    void newTaskReady();
    void newPacketReady(QEXTTcpPacketBase *packet);
};

#endif // QEXTTCPTASKBASE_H
