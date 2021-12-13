#ifndef _QEXTTCPSERVER_H
#define _QEXTTCPSERVER_H

#include <qextTcpGlobal.h>
#include <qextTcpTask.h>
#include <qextTcpPacketDispatcher.h>

#include <QTcpServer>

class QEXTTcpFactory;
class QEXTTcpServerPrivate;
class QEXT_TCP_API QEXTTcpServer : public QTcpServer
{
    Q_OBJECT
    Q_DISABLE_COPY(QEXTTcpServer)
    QEXT_DECL_PRIVATE_D(dd_ptr, QEXTTcpServer)
public:
    QEXTTcpServer();
    QEXTTcpServer(const QSharedPointer<QEXTTcpFactory> &tcpFactory);
    QEXTTcpServer(QEXTTcpServerPrivate *d);
    QEXTTcpServer(QEXTTcpServerPrivate *d, const QSharedPointer<QEXTTcpFactory> &tcpFactory);
    ~QEXTTcpServer();

    size_t allSocketCount() const;

    size_t maxSocketConnectionCount() const;
    void setMaxSocketConnectionCount(size_t count);

    size_t maxTaskThreadCount() const;
    void setMaxTaskThreadCount(size_t count);

    void runTask(int function);
    void runTask(QEXTTcpTask *task);
    QSharedPointer<QEXTTcpFactory> tcpFactory() const;
    void setTcpFactory(const QSharedPointer<QEXTTcpFactory> &tcpFactory);

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

    QScopedPointer<QEXTTcpServerPrivate> dd_ptr;
};

#endif // _QEXTTCPSERVER_H
