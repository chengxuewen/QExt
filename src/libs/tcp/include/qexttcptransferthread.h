#ifndef QEXTTCPTRANSFERTHREAD_H
#define QEXTTCPTRANSFERTHREAD_H

#include <qexttcpglobal.h>
#include <qexttcpabstractthread.h>
#include <qexttcpsocket.h>

#include <QQueue>



class QEXTTcpServerSocket;
class QEXTTcpAbstractPacket;
class QEXTTcpAbstractPacketParser;
class QEXTTcpTransferThreadPool;
class QEXTTcpTransferThreadPrivate;
class QEXT_TCP_API QEXTTcpTransferThread : public QEXTTcpAbstractThread
{
    Q_OBJECT
public:
    explicit QEXTTcpTransferThread(QEXTTcpTransferThreadPool *threadPool);
    ~QEXTTcpTransferThread();

    void quit() QEXT_OVERRIDE;
    QEXTTcpAbstractThreadPool *tcpThreadPool() const QEXT_OVERRIDE;

    QQueue<QEXTTcpAbstractPacket *> allSendPacketsQueue() const;
    QSet<QEXTTcpServerSocket *> allSocketsSet() const;
    int socketCount() const;

Q_SIGNALS:
    void socketConnected(QEXTTcpServerSocket *socket);
    void socketDisconnected(QEXTTcpServerSocket *socket);

    void socketMessage(QEXTTcpServerSocket *socket, const QString &msg);
    void socketError(QEXTTcpServerSocket *socket, QAbstractSocket::SocketError error);
    void transferError(const QEXTTcpSocket::TransferErrorType &error);

public Q_SLOTS:
    void enqueueSendPacket(QObject *threadObj, QEXTTcpAbstractPacket *packet);
    void addServerSocket(QObject *threadObj, QEXTTcpServerSocket *socket, const QList<QEXTTcpAbstractPacket *> &packetList);

protected Q_SLOTS:
    void readPacket();
    void sendPacket();

    void handleSocketClosed();
    void handleSocketError(QAbstractSocket::SocketError socketError);
    void incomingConnection(QObject *threadObj, QEXTSocketDescriptor socketDescriptor);

private:
    QEXT_DECLARE_PRIVATE(QEXTTcpTransferThread)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpTransferThread)
};



#endif // QEXTTCPTRANSFERTHREAD_H
