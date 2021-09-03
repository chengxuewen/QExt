#ifndef QEXTTCPCLIENT_H
#define QEXTTCPCLIENT_H

#include <qextobject.h>

#include <qextTcpGlobal.h>
#include <qextTcpSocket.h>
#include <qextTcpPacketTransceiver.h>

#include <QTcpSocket>

class QEXTTcpSocket;
class QEXTTcpClientProxy;
class QEXTTcpPacketDispatcher;
class QEXTTcpPacketParserInterface;
class QEXTTcpClientPrivate;
class QEXT_TCP_API QEXTTcpClient : public QEXTTcpPacketTransceiver
{
    Q_OBJECT
public:
    QEXTTcpClient();
    QEXTTcpClient(const QSharedPointer<QEXTTcpPacketParserInterface> &packetParser);
    QEXTTcpClient(const QSharedPointer<QEXTTcpPacketDispatcher> &dispatcher);
    QEXTTcpClient(const QSharedPointer<QEXTTcpPacketParserInterface> &packetParser,
                  const QSharedPointer<QEXTTcpPacketDispatcher> &dispatcher);
    QEXTTcpClient(QEXTTcpClientPrivate &dd);
    QEXTTcpClient(QEXTTcpClientPrivate &dd,
                  const QSharedPointer<QEXTTcpPacketDispatcher> &dispatcher);
    QEXTTcpClient(QEXTTcpClientPrivate &dd,
                  const QSharedPointer<QEXTTcpPacketParserInterface> &packetParser);
    QEXTTcpClient(QEXTTcpClientPrivate &dd,
                  const QSharedPointer<QEXTTcpPacketParserInterface> &packetParser,
                  const QSharedPointer<QEXTTcpPacketDispatcher> &dispatcher);
    ~QEXTTcpClient();

    QSharedPointer<QEXTTcpSocket> socket() const;
    QAbstractSocket::SocketState socketState() const;
    bool isSocketConnected() const;
    void startConnection(const QString &ipAddr = "", quint16 port = 0);
    void closeConnection();
    void abortConnection();

    QString serverAddress() const;
    quint16 serverPort() const;

    QSharedPointer<QEXTTcpPacketParserInterface> packetParser() const;
    void setPacketParser(const QSharedPointer<QEXTTcpPacketParserInterface> packetParser);

    QSharedPointer<QEXTTcpPacketDispatcher> packetDispatcher() const;
    void setPacketDispatcher(const QSharedPointer<QEXTTcpPacketDispatcher> &dispatcher);

Q_SIGNALS:
    void tryToConnect(const QString &ipAddress, quint16 port);
    void tryToClose();
    void tryToAbort();

    void socketConnected();
    void socketDisconnected();
    void socketStateChanged(QAbstractSocket::SocketState state);
    void socketError(QAbstractSocket::SocketError error);
    void transferError(QEXTTcpSocket::TransferErrorType error);

protected:
    void initClient();

private:
    QEXT_DECL_PRIVATE(QEXTTcpClient)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpClient)
};

#endif // QEXTTCPCLIENT_H
