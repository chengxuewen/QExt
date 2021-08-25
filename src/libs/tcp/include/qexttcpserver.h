#ifndef QEXTTCPSERVER_H
#define QEXTTCPSERVER_H

#include <qextobject.h>

#include <qexttcpglobal.h>
#include <qexttcpabstractpacket.h>
#include <qexttcptransferthread.h>
#include <qexttcpabstracttask.h>
#include <qexttcpabstractpacket.h>

#include <QTcpServer>



class QEXTTcpServerSocket;
class QEXTTcpServerPrivate;
class QEXT_TCP_API QEXTTcpServer : public QTcpServer, public QEXTObject
{
    Q_OBJECT
public:
    QEXTTcpServer(QObject *parent = QEXT_DECL_NULLPTR);
    QEXTTcpServer(QEXTTcpAbstractPacketParser *packetParser, QObject *parent = QEXT_DECL_NULLPTR);
    QEXTTcpServer(QEXTTcpAbstractPacketParser *packetParser, QEXTTcpAbstractTaskPool *taskPool, QObject *parent = QEXT_DECL_NULLPTR);
    QEXTTcpServer(QEXTTcpServerPrivate &dd, QObject *parent = QEXT_DECL_NULLPTR);
    QEXTTcpServer(QEXTTcpServerPrivate &dd, QEXTTcpAbstractPacketParser *packetParser, QObject *parent = QEXT_DECL_NULLPTR);
    QEXTTcpServer(QEXTTcpServerPrivate &dd, QEXTTcpAbstractPacketParser *packetParser, QEXTTcpAbstractTaskPool *taskPool, QObject *parent = QEXT_DECL_NULLPTR);
    ~QEXTTcpServer();

    int allSocketCount() const;
    int maxSocketCount() const;
    void setMaxSocketCount(int maxSocketCount);

    QEXTTcpAbstractPacketParser *packetParser() const;
    void setPacketParser(QEXTTcpAbstractPacketParser *packetParser);

    QEXTTcpAbstractTaskPool *taskPool() const;
    void setTaskPool(QEXTTcpAbstractTaskPool *taskPool);

Q_SIGNALS:
    void transferError(const QEXTTcpSocket::TransferErrorType &error);
    void socketError(const QEXTId &socketId, const QAbstractSocket::SocketError &error);
    void socketMessage(const QEXTId &socketId, const QString &msg);
    void connectionRequest(QEXTSocketDescriptor socketDescriptor);

protected Q_SLOTS:
    void handleSocketMessage(QEXTTcpServerSocket *socket, const QString &msg);
    void handleSocketConnected(QEXTTcpServerSocket *socket);
    void handleSocketDisconnected(QEXTTcpServerSocket *socket);
    void handleSocketError(QEXTTcpServerSocket *socket, QAbstractSocket::SocketError error);

protected:
    void incomingConnection(QEXTSocketDescriptor socketDescriptor) QEXT_DECL_OVERRIDE;

private:
    QEXT_DECL_PRIVATE(QEXTTcpServer)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpServer)
};



#endif // QEXTTCPSERVER_H
