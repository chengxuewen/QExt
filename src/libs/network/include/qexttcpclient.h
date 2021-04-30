#ifndef QEXTTCPCLIENT_H
#define QEXTTCPCLIENT_H

#include <qextobject.h>

#include <qextnetworkglobal.h>
#include <qexttcpclientproxy.h>
#include <qexttcpclientsocket.h>
#include <qexttcppacketbase.h>

#include <QTcpSocket>

class QEXTTcpClientProxy;
class QEXTTcpClientSocket;
class QEXTTcpTaskPoolBase;
class QEXTTcpPacketDispatcherBase;
class QEXTTcpPacketParserBase;
class QEXTTcpClientPrivate;
class QEXT_NETWORK_API QEXTTcpClient : public QEXTTcpClientProxy
{
    Q_OBJECT
public:
    QEXTTcpClient(QObject *parent = QEXT_NULLPTR);
    QEXTTcpClient(QEXTTcpPacketParserBase *packetParser, QObject *parent = QEXT_NULLPTR);
    QEXTTcpClient(QEXTTcpPacketParserBase *packetParser, QEXTTcpPacketDispatcherBase *packetDispatcher, QObject *parent = QEXT_NULLPTR);
    QEXTTcpClient(QEXTTcpClientPrivate &dd, QObject *parent = QEXT_NULLPTR);
    QEXTTcpClient(QEXTTcpClientPrivate &dd, QEXTTcpPacketParserBase *packetParser, QObject *parent = QEXT_NULLPTR);
    QEXTTcpClient(QEXTTcpClientPrivate &dd, QEXTTcpPacketParserBase *packetParser, QEXTTcpPacketDispatcherBase *packetDispatcher, QObject *parent = QEXT_NULLPTR);
    ~QEXTTcpClient();

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

    bool sendProxySyncRequestPacket(QEXTTcpPacketBase *send, QEXTTcpPacketBase **rcv, const QString &proxyName);
    bool sendProxyRequestPacket(QEXTTcpPacketBase *send, const QString &proxyName);
    bool sendProxyReplyPacket(QEXTTcpPacketBase *send, const QString &proxyName);
    bool sendProxyNotifyPacket(QEXTTcpPacketBase *send, const QString &proxyName);

    QEXTTcpPacketDispatcherBase *packetDispatcher() const;
    void setPacketDispatcher(QEXTTcpPacketDispatcherBase *dispatcher);

    void setPacketParser(QEXTTcpPacketParserBase *packetParser) QEXT_OVERRIDE;

Q_SIGNALS:
    void tryToConnect();
    void tryToClose();
    void tryToAbort();

    void socketConnected();
    void socketDisconnected();
    void socketError(const QAbstractSocket::SocketError &error);
    void transferError(const QEXTTcpSocket::TransferErrorType &error);

private:
    QEXT_DECLARE_PRIVATE(QEXTTcpClient)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpClient)
};

#endif // QEXTTCPCLIENT_H
