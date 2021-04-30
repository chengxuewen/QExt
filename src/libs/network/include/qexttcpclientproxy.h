#ifndef QEXTTCPCLIENTPROXY_H
#define QEXTTCPCLIENTPROXY_H

#include <qextobject.h>

#include <qextnetworkglobal.h>

#include <QObject>

class QEXTTcpClient;
class QEXTTcpTaskBase;
class QEXTTcpPacketBase;
class QEXTTcpClientSocket;
class QEXTTcpPacketParserBase;
class QEXTTcpClientProxyPrivate;
class QEXT_NETWORK_API QEXTTcpClientProxy : public QObject, public QEXTObject
{
    Q_OBJECT
public:
    explicit QEXTTcpClientProxy(QObject *parent = QEXT_NULLPTR);
    QEXTTcpClientProxy(QEXTTcpClientProxyPrivate &dd, QObject *parent = QEXT_NULLPTR);
    ~QEXTTcpClientProxy();

    QString name() const;

    QEXTTcpClientSocket *socket() const;
    void setSocket(QEXTTcpClientSocket *socket);

    QEXTTcpPacketBase *sendPacket() const;
    void cancelWait();

    QEXTTcpPacketParserBase *packetParser() const;
    virtual void setPacketParser(QEXTTcpPacketParserBase *packetParser);

    void enqueuePacket(QEXTTcpPacketBase *packet);
    QEXTTcpPacketBase *dequeuePacket();

    bool sendSyncRequestPacket(QEXTTcpPacketBase *send, QEXTTcpPacketBase **rcv);
    bool sendRequestPacket(QEXTTcpPacketBase *send);
    bool sendReplyPacket(QEXTTcpPacketBase *send);
    bool sendNotifyPacket(QEXTTcpPacketBase *send);

Q_SIGNALS:
    void newReceivePacketReady();
    void newSendPacketReady(QEXTTcpPacketBase *packet);

protected Q_SLOTS:
    void setName(const QString &name);

private:
    QEXT_DECLARE_PRIVATE(QEXTTcpClientProxy)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpClientProxy)
};

#endif // QEXTTCPCLIENTPROXY_H
