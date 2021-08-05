#ifndef QEXTTCPTASKPOOL_H
#define QEXTTCPTASKPOOL_H

#include <qextobject.h>

#include <qexttcpglobal.h>
#include <qexttcpabstracttask.h>



class QEXTTcpTaskPoolPrivate;
class QEXT_TCP_API QEXTTcpTaskPool : public QEXTTcpAbstractTaskPool, public QEXTObject
{
    Q_OBJECT
public:
    QEXTTcpTaskPool(QObject *parent = QEXT_NULLPTR);
    QEXTTcpTaskPool(QEXTTcpAbstractPacketParser *packetParser, QObject *parent = QEXT_NULLPTR);
    ~QEXTTcpTaskPool();

    bool isTaskEmpty() const QEXT_OVERRIDE;
    int taskCount() const QEXT_OVERRIDE;

    QList<QEXTTcpAbstractTask *> allUnfinishedTasks() const QEXT_OVERRIDE;
    QList<QEXTTcpAbstractTask *> allExpiredTasks() const QEXT_OVERRIDE;

    QEXTTcpAbstractPacketParser *packetParser() const QEXT_OVERRIDE;
    void setPacketParser(QEXTTcpAbstractPacketParser *packetParser) QEXT_OVERRIDE;

    void parsePacket(QEXTTcpAbstractPacket *packet) QEXT_OVERRIDE;
    void sendPacket(QEXTTcpAbstractPacket *packet) QEXT_OVERRIDE;

    void enqueueTask(QEXTTcpAbstractTask *task) QEXT_OVERRIDE;
    QEXTTcpAbstractTask *dequeueTask() QEXT_OVERRIDE;
    void recoveryTask(QEXTTcpAbstractTask *task) QEXT_OVERRIDE;

private:
    QEXT_DECLARE_PRIVATE(QEXTTcpTaskPool)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpTaskPool)
};



#endif // QEXTTCPTASKPOOL_H
