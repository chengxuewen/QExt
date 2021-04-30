#ifndef QEXTTCPCLIENTSOCKET_H
#define QEXTTCPCLIENTSOCKET_H

#include <qexttcpsocket.h>

class QEXTTcpPacketBase;
class QEXTTcpPacketParserBase;
class QEXTTcpPacketDispatcherBase;
class QEXTTcpClientSocketPrivate;
class QEXT_NETWORK_API QEXTTcpClientSocket : public QEXTTcpSocket
{
    Q_OBJECT
public:
    explicit QEXTTcpClientSocket(QObject *parent = QEXT_NULLPTR);
    ~QEXTTcpClientSocket();

    QEXTTcpPacketParserBase *packetParser() const;
    void setPacketParser(QEXTTcpPacketParserBase *packetParser);

    QEXTTcpPacketDispatcherBase *packetDispatcher() const;
    void setPacketDispatcher(QEXTTcpPacketDispatcherBase *packetDispatcher);

    QString serverAddress() const;
    quint16 serverPort() const;

Q_SIGNALS:
    void packetNotDispatched(QEXTTcpPacketBase *packet);

public Q_SLOTS:
    void updateIdentityId() QEXT_OVERRIDE;

    void connectToServer();
    void closeSocket();
    void abortSocket();

    void setServerAddress(const QString &ipAddr);
    void setServerPort(quint16 port);

    void enqueueSendPacket(QEXTTcpPacketBase *packet);

protected Q_SLOTS:
    void readPacket();
    void sendPacket();

private:
    QEXT_DECLARE_PRIVATE(QEXTTcpClientSocket)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpClientSocket)
};


#endif // QEXTTCPCLIENTSOCKET_H
