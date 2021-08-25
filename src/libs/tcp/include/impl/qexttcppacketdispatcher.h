#ifndef QEXTTCPPACKETDISPATCHER_H
#define QEXTTCPPACKETDISPATCHER_H

#include <qextobject.h>

#include <qexttcpglobal.h>
#include <qexttcpabstractpacket.h>

#include <QObject>



class QEXTTcpClient;
class QEXTTcpClientProxy;
class QEXTTcpAbstractPacket;
class QEXTTcpPacketDispatcherPrivate;
class QEXT_TCP_API QEXTTcpPacketDispatcher : public QEXTTcpAbstractPacketDispatcher, public QEXTObject
{
    Q_OBJECT
public:
    QEXTTcpPacketDispatcher(QObject *parent = QEXT_DECL_NULLPTR);
    QEXTTcpPacketDispatcher(QEXTTcpPacketDispatcherPrivate &dd, QObject *parent = QEXT_DECL_NULLPTR);
    QEXTTcpPacketDispatcher(QEXTTcpClient *client, QObject *parent = QEXT_DECL_NULLPTR);
    QEXTTcpPacketDispatcher(QEXTTcpPacketDispatcherPrivate &dd, QEXTTcpClient *client, QObject *parent = QEXT_DECL_NULLPTR);
    ~QEXTTcpPacketDispatcher();

    QEXTTcpClient *tcpClient() const QEXT_DECL_OVERRIDE;
    void setTcpClient(QEXTTcpClient *client) QEXT_DECL_OVERRIDE;

    QList<QEXTTcpClientProxy *> allTcpClientProxyList() const QEXT_DECL_OVERRIDE;

    QEXTTcpAbstractPacket *dequeuePacket() QEXT_DECL_OVERRIDE;
    void enqueuePacket(QEXTTcpAbstractPacket *packet) QEXT_DECL_OVERRIDE;
    int packetsCount() const QEXT_DECL_OVERRIDE;

protected Q_SLOTS:
    void dispatchPacket() QEXT_DECL_OVERRIDE;

private:
    QEXT_DECL_PRIVATE(QEXTTcpPacketDispatcher)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpPacketDispatcher)
};



#endif // QEXTTCPPACKETDISPATCHER_H
