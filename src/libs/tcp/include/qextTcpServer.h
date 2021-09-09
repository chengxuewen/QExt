#ifndef QEXTTCPSERVER_H
#define QEXTTCPSERVER_H

#include <qextTcpGlobal.h>
#include <qextTcpTask.h>
#include <qextTcpPacketDispatcher.h>

#include <qextObject.h>

#include <QTcpServer>

class QEXTTcpServerPrivate;
class QEXT_TCP_API QEXTTcpServer : public QTcpServer, public QEXTObject
{
    Q_OBJECT
public:
    QEXTTcpServer();
    QEXTTcpServer(const QSharedPointer<QEXTTcpPacketParserInterface> &packetParser);
    QEXTTcpServer(const QSharedPointer<QEXTTcpPacketParserInterface> &packetParser,
                  const QSharedPointer<QEXTTcpPacketDispatcherFactory> &dispatcherFactory);
    QEXTTcpServer(QEXTTcpServerPrivate &dd);
    ~QEXTTcpServer();

    int allSocketCount() const;
    int maxSocketCount() const;
    void setMaxSocketCount(int maxSocketCount);

    QSharedPointer<QEXTTcpPacketParserInterface> packetParser() const;
    void setPacketParser(const QSharedPointer<QEXTTcpPacketParserInterface> &packetParser);

    QSharedPointer<QEXTTcpPacketDispatcherFactory> packetDispatcherFactory() const;
    void setPacketDispatcherFactory(const QSharedPointer<QEXTTcpPacketDispatcherFactory> &dispatcherFactory);

Q_SIGNALS:
    void serverMessage(const QString &msg);
    void socketError(const QSharedPointer<QEXTTcpSocket> &socket, const QAbstractSocket::SocketError &error);
    void socketTransferError(const QSharedPointer<QEXTTcpSocket> &socket, const QEXTTcpSocket::TransferErrorType &error);
    void socketConnected(const QSharedPointer<QEXTTcpSocket> &socket);
    void socketDisconnected(const QSharedPointer<QEXTTcpSocket> &socket);

protected Q_SLOTS:
    void onSocketDisconnected();
    void onSocketError(QAbstractSocket::SocketError error);
    void onSocketTransferError(QEXTTcpSocket::TransferErrorType error);

protected:
    void incomingConnection(QEXTSocketDescriptor socketDescriptor) QEXT_DECL_OVERRIDE;

private:
    QEXT_DECL_PRIVATE(QEXTTcpServer)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpServer)
};

#endif // QEXTTCPSERVER_H
