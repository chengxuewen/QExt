#ifndef QEXTTCPCLIENT_H
#define QEXTTCPCLIENT_H

#include <qextobject.h>

#include <qexttcpglobal.h>
#include <qexttcpclientproxy.h>
#include <qexttcpclientsocket.h>
#include <qexttcpabstractpacket.h>

#include <QTcpSocket>



class QEXTTcpClientProxy;
class QEXTTcpClientSocket;
class QEXTTcpAbstractTaskPool;
class QEXTTcpAbstractPacketDispatcher;
class QEXTTcpAbstractPacketParser;
class QEXTTcpClientPrivate;
class QEXT_TCP_API QEXTTcpClient : public QEXTTcpClientProxy
{
    Q_OBJECT
public:
    QEXTTcpClient(QObject *parent = QEXT_DECL_NULLPTR);
    QEXTTcpClient(QEXTTcpAbstractPacketParser *packetParser, QObject *parent = QEXT_DECL_NULLPTR);
    QEXTTcpClient(QEXTTcpAbstractPacketParser *packetParser, QEXTTcpAbstractPacketDispatcher *packetDispatcher, QObject *parent = QEXT_DECL_NULLPTR);
    QEXTTcpClient(QEXTTcpClientPrivate &dd, QObject *parent = QEXT_DECL_NULLPTR);
    QEXTTcpClient(QEXTTcpClientPrivate &dd, QEXTTcpAbstractPacketParser *packetParser, QObject *parent = QEXT_DECL_NULLPTR);
    QEXTTcpClient(QEXTTcpClientPrivate &dd, QEXTTcpAbstractPacketParser *packetParser, QEXTTcpAbstractPacketDispatcher *packetDispatcher, QObject *parent = QEXT_DECL_NULLPTR);
    ~QEXTTcpClient();

    QAbstractSocket::SocketState socketState() const;
    bool isSocketConnected() const;
    void startConnection(const QString &ipAddr = "", quint16 port = 0);
    void closeConnection();
    void abortConnection();

    QString serverAddress() const;
    quint16 serverPort() const;

    QList<QEXTTcpClientProxy *> allProxies() const;
    QEXTTcpClientProxy *proxy(const QString &name) const;
    bool addProxy(QEXTTcpClientProxy *proxy);
    int removeProxy(QEXTTcpClientProxy *proxy);
    int removeProxy(const QString &name);

    bool sendProxySyncRequestPacket(QEXTTcpAbstractPacket *send, QEXTTcpAbstractPacket **rcv, const QString &proxyName);
    bool sendProxyRequestPacket(QEXTTcpAbstractPacket *send, const QString &proxyName);
    bool sendProxyReplyPacket(QEXTTcpAbstractPacket *send, const QString &proxyName);
    bool sendProxyNotifyPacket(QEXTTcpAbstractPacket *send, const QString &proxyName);

    QEXTTcpAbstractPacketDispatcher *packetDispatcher() const;
    void setPacketDispatcher(QEXTTcpAbstractPacketDispatcher *dispatcher);

    void setPacketParser(QEXTTcpAbstractPacketParser *packetParser) QEXT_DECL_OVERRIDE;

Q_SIGNALS:
    void tryToConnect();
    void tryToClose();
    void tryToAbort();

    void socketConnected();
    void socketDisconnected();
    void socketStateChanged(QAbstractSocket::SocketState state);
    void socketError(QAbstractSocket::SocketError error);
    void transferError(QEXTTcpSocket::TransferErrorType error);

private:
    QEXT_DECL_PRIVATE(QEXTTcpClient)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpClient)
};



#endif // QEXTTCPCLIENT_H
