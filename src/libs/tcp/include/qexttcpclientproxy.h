#ifndef QEXTTCPCLIENTPROXY_H
#define QEXTTCPCLIENTPROXY_H

#include <qextobject.h>

#include <qexttcpglobal.h>

#include <QObject>



class QEXTTcpClient;
class QEXTTcpAbstractTask;
class QEXTTcpAbstractPacket;
class QEXTTcpClientSocket;
class QEXTTcpAbstractPacketParser;
class QEXTTcpClientProxyPrivate;
class QEXT_TCP_API QEXTTcpClientProxy : public QObject, public QEXTObject
{
    Q_OBJECT
public:
    explicit QEXTTcpClientProxy(QObject *parent = QEXT_DECL_NULLPTR);
    QEXTTcpClientProxy(QEXTTcpClientProxyPrivate &dd, QObject *parent = QEXT_DECL_NULLPTR);
    ~QEXTTcpClientProxy();

    QString name() const;

    QEXTTcpClientSocket *socket() const;
    void setSocket(QEXTTcpClientSocket *socket);

    QEXTTcpAbstractPacket *sendPacket() const;
    void cancelWait();

    QEXTTcpAbstractPacketParser *packetParser() const;
    virtual void setPacketParser(QEXTTcpAbstractPacketParser *packetParser);

    void enqueuePacket(QEXTTcpAbstractPacket *packet);
    QEXTTcpAbstractPacket *dequeuePacket();

    bool sendSyncRequestPacket(QEXTTcpAbstractPacket *send, QEXTTcpAbstractPacket **rcv);
    bool sendRequestPacket(QEXTTcpAbstractPacket *send);
    bool sendReplyPacket(QEXTTcpAbstractPacket *send);
    bool sendNotifyPacket(QEXTTcpAbstractPacket *send);

Q_SIGNALS:
    void newReceivePacketReady();
    void newSendPacketReady(QEXTTcpAbstractPacket *packet);

protected Q_SLOTS:
    void setName(const QString &name);

private:
    QEXT_DECL_PRIVATE(QEXTTcpClientProxy)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpClientProxy)
};



#endif // QEXTTCPCLIENTPROXY_H
