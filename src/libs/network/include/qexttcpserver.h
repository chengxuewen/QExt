#ifndef QEXTTCPSERVER_H
#define QEXTTCPSERVER_H

#include <qextobject.h>

#include <qextnetworkglobal.h>
#include <qexttcppacketbase.h>
#include <qexttcptransferthread.h>
#include <qexttcptaskbase.h>
#include <qexttcppacketbase.h>

#include <QTcpServer>

class QEXTTcpServerSocket;
class QEXTTcpServerPrivate;
class QEXT_NETWORK_API QEXTTcpServer : public QTcpServer, public QEXTObject
{
    Q_OBJECT
public:
    QEXTTcpServer(QObject *parent = QEXT_NULLPTR);
    QEXTTcpServer(QEXTTcpPacketParserBase *packetParser, QObject *parent = QEXT_NULLPTR);
    QEXTTcpServer(QEXTTcpPacketParserBase *packetParser, QEXTTcpTaskPoolBase *taskPool, QObject *parent = QEXT_NULLPTR);
    QEXTTcpServer(QEXTTcpServerPrivate &dd, QObject *parent = QEXT_NULLPTR);
    QEXTTcpServer(QEXTTcpServerPrivate &dd, QEXTTcpPacketParserBase *packetParser, QObject *parent = QEXT_NULLPTR);
    QEXTTcpServer(QEXTTcpServerPrivate &dd, QEXTTcpPacketParserBase *packetParser, QEXTTcpTaskPoolBase *taskPool, QObject *parent = QEXT_NULLPTR);
    ~QEXTTcpServer();

    int allSocketCount() const;
    int maxSocketCount() const;
    void setMaxSocketCount(int maxSocketCount);

    QEXTTcpPacketParserBase *packetParser() const;
    void setPacketParser(QEXTTcpPacketParserBase *packetParser);

    QEXTTcpTaskPoolBase *taskPool() const;
    void setTaskPool(QEXTTcpTaskPoolBase *taskPool);

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
    void incomingConnection(QEXTSocketDescriptor socketDescriptor) QEXT_OVERRIDE;

private:
    QEXT_DECLARE_PRIVATE(QEXTTcpServer)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpServer)
};

#endif // QEXTTCPSERVER_H
