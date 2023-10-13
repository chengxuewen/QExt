#ifndef _QEXTTCPCLIENT_H
#define _QEXTTCPCLIENT_H

#include <qextTcpGlobal.h>
#include <qextTcpSocket.h>
#include <qextTcpPacketTransceiver.h>

#include <QTcpSocket>

class QExtTcpTask;
class QExtTcpSocket;
class QExtTcpFactory;
class QExtTcpClientProxy;
class QExtTcpPacketDispatcher;
class QExtTcpPacketParserInterface;
class QExtTcpClientPrivate;
class QEXT_TCP_API QExtTcpClient : public QExtTcpPacketTransceiver
{
Q_OBJECT
    Q_DISABLE_COPY(QExtTcpClient)

    QEXT_DECL_PRIVATE_D(dd_ptr, QExtTcpClient)
public:
    QExtTcpClient();
    QExtTcpClient(const QSharedPointer<QExtTcpFactory> &tcpFactory);
    QExtTcpClient(QExtTcpClientPrivate *d);
    QExtTcpClient(QExtTcpClientPrivate *d, const QSharedPointer<QExtTcpFactory> &tcpFactory);
    ~QExtTcpClient();

    QSharedPointer<QExtTcpSocket> socket() const;
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
    void runTask(QExtTcpTask *task);
    QSharedPointer<QExtTcpFactory> tcpFactory() const;
    void setTcpFactory(const QSharedPointer<QExtTcpFactory> tcpFactory);

    QExtTcpPacketDispatcher *packetDispatcher() const;
    void setPacketDispatcher(const QSharedPointer<QExtTcpPacketDispatcher> &dispatcher);

Q_SIGNALS:
    void tryToConnect(const QString &ipAddress, quint16 port);
    void tryToClose();
    void tryToAbort();

    void socketConnected();
    void socketDisconnected();
    void socketStateChanged(QAbstractSocket::SocketState state);
    void socketError(QAbstractSocket::SocketError error);
    void transferError(QExtTcpSocket::TransferErrorType error);

protected:
    void initClient();
};

#endif // _QEXTTCPCLIENT_H
