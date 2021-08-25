#ifndef QEXTTCPCLIENTSOCKET_H
#define QEXTTCPCLIENTSOCKET_H

#include <qexttcpsocket.h>



class QEXTTcpAbstractPacket;
class QEXTTcpAbstractPacketParser;
class QEXTTcpAbstractPacketDispatcher;
class QEXTTcpClientSocketPrivate;
class QEXT_TCP_API QEXTTcpClientSocket : public QEXTTcpSocket
{
    Q_OBJECT
public:
    explicit QEXTTcpClientSocket(QObject *parent = QEXT_DECL_NULLPTR);
    ~QEXTTcpClientSocket();

    QEXTTcpAbstractPacketParser *packetParser() const;
    void setPacketParser(QEXTTcpAbstractPacketParser *packetParser);

    QEXTTcpAbstractPacketDispatcher *packetDispatcher() const;
    void setPacketDispatcher(QEXTTcpAbstractPacketDispatcher *packetDispatcher);

    QString serverAddress() const;
    quint16 serverPort() const;

Q_SIGNALS:
    void packetNotDispatched(QEXTTcpAbstractPacket *packet);

public Q_SLOTS:
    void updateIdentityId() QEXT_DECL_OVERRIDE;

    void connectToServer();
    void closeSocket();
    void abortSocket();

    void setServerAddress(const QString &ipAddr);
    void setServerPort(quint16 port);

    void enqueueSendPacket(QEXTTcpAbstractPacket *packet);

protected Q_SLOTS:
    void readPacket();
    void sendPacket();

private:
    QEXT_DECL_PRIVATE(QEXTTcpClientSocket)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpClientSocket)
};



#endif // QEXTTCPCLIENTSOCKET_H
