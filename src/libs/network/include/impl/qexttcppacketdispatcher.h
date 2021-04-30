#ifndef QEXTTCPPACKETDISPATCHER_H
#define QEXTTCPPACKETDISPATCHER_H

#include <qextobject.h>

#include <qextnetworkglobal.h>
#include <qexttcppacketbase.h>

#include <QObject>

class QEXTTcpClient;
class QEXTTcpClientProxy;
class QEXTTcpPacketBase;
class QEXTTcpPacketDispatcherPrivate;
class QEXT_NETWORK_API QEXTTcpPacketDispatcher : public QEXTTcpPacketDispatcherBase, public QEXTObject
{
    Q_OBJECT
public:
    QEXTTcpPacketDispatcher(QObject *parent = QEXT_NULLPTR);
    QEXTTcpPacketDispatcher(QEXTTcpPacketDispatcherPrivate &dd, QObject *parent = QEXT_NULLPTR);
    QEXTTcpPacketDispatcher(QEXTTcpClient *client, QObject *parent = QEXT_NULLPTR);
    QEXTTcpPacketDispatcher(QEXTTcpPacketDispatcherPrivate &dd, QEXTTcpClient *client, QObject *parent = QEXT_NULLPTR);
    ~QEXTTcpPacketDispatcher();

    QEXTTcpClient *tcpClient() const QEXT_OVERRIDE;
    void setTcpClient(QEXTTcpClient *client) QEXT_OVERRIDE;

    QList<QEXTTcpClientProxy *> allTcpClientProxyList() const QEXT_OVERRIDE;

    QEXTTcpPacketBase *dequeuePacket() QEXT_OVERRIDE;
    void enqueuePacket(QEXTTcpPacketBase *packet) QEXT_OVERRIDE;
    int packetsCount() const QEXT_OVERRIDE;

protected Q_SLOTS:
    void dispatchPacket() QEXT_OVERRIDE;

private:
    QEXT_DECLARE_PRIVATE(QEXTTcpPacketDispatcher)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpPacketDispatcher)
};

#endif // QEXTTCPPACKETDISPATCHER_H
