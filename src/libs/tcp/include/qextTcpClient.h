#ifndef _QEXTTCPCLIENT_H
#define _QEXTTCPCLIENT_H

#include <qextTcpGlobal.h>
#include <qextTcpSocket.h>
#include <qextTcpPacketTransceiver.h>

#include <QTcpSocket>

class QEXTTcpTask;
class QEXTTcpSocket;
class QEXTTcpFactory;
class QEXTTcpClientProxy;
class QEXTTcpPacketDispatcher;
class QEXTTcpPacketParserInterface;
class QEXTTcpClientPrivate;
class QEXT_TCP_API QEXTTcpClient : public QEXTTcpPacketTransceiver
{
    Q_OBJECT
public:
    QEXTTcpClient();
    QEXTTcpClient(const QSharedPointer<QEXTTcpFactory> &tcpFactory);
    QEXTTcpClient(QEXTTcpClientPrivate *d);
    QEXTTcpClient(QEXTTcpClientPrivate *d, const QSharedPointer<QEXTTcpFactory> &tcpFactory);
    ~QEXTTcpClient();

    QSharedPointer<QEXTTcpSocket> socket() const;
    QAbstractSocket::SocketState socketState() const;
    bool isSocketConnected() const;
    void startConnection(const QString &ipAddr = "", quint16 port = 0);
    void closeConnection();
    void abortConnection();

    QString serverAddress() const;
    quint16 serverPort() const;

    int maxTaskThreadCount() const;
    void setMaxTaskThreadCount(int maxThreadCount);

    void runTask(int function);
    void runTask(QEXTTcpTask *task);
    QSharedPointer<QEXTTcpFactory> tcpFactory() const;
    void setTcpFactory(const QSharedPointer<QEXTTcpFactory> tcpFactory);

    QEXTTcpPacketDispatcher *packetDispatcher() const;
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

#endif // _QEXTTCPCLIENT_H
