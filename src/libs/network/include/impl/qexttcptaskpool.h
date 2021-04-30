#ifndef QEXTTCPTASKPOOL_H
#define QEXTTCPTASKPOOL_H

#include <qextobject.h>

#include <qextnetworkglobal.h>
#include <qexttcptaskbase.h>

class QEXTTcpTaskPoolPrivate;
class QEXT_NETWORK_API QEXTTcpTaskPool : public QEXTTcpTaskPoolBase, public QEXTObject
{
    Q_OBJECT
public:
    QEXTTcpTaskPool(QObject *parent = QEXT_NULLPTR);
    QEXTTcpTaskPool(QEXTTcpPacketParserBase *packetParser, QObject *parent = QEXT_NULLPTR);
    ~QEXTTcpTaskPool();

    bool isTaskEmpty() const QEXT_OVERRIDE;
    int taskCount() const QEXT_OVERRIDE;
    QEXTTcpTaskBase *dequeueTask() QEXT_OVERRIDE;

    QList<QEXTTcpTaskBase *> allUnfinishedTasks() const QEXT_OVERRIDE;
    QList<QEXTTcpTaskBase *> allExpiredTasks() const QEXT_OVERRIDE;

    QEXTTcpPacketParserBase *packetParser() const QEXT_OVERRIDE;
    void setPacketParser(QEXTTcpPacketParserBase *packetParser) QEXT_OVERRIDE;

    void enqueuePacket(QEXTTcpPacketBase *packet) QEXT_OVERRIDE;
    void sendPacket(QEXTTcpPacketBase *packet) QEXT_OVERRIDE;
    void recoveryTask(QEXTTcpTaskBase *task) QEXT_OVERRIDE;

private:
    QEXT_DECLARE_PRIVATE(QEXTTcpTaskPool)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpTaskPool)
};

#endif // QEXTTCPTASKPOOL_H
