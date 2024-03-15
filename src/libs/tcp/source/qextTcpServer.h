#ifndef _QEXTTCPSERVER_H
#define _QEXTTCPSERVER_H

#include <qextTcpGlobal.h>
#include <qextTcpTask.h>
#include <qextTcpPacketDispatcher.h>

#include <QTcpServer>

class QExtTcpFactory;
class QExtTcpServerPrivate;
class QEXT_TCP_API QExtTcpServer : public QTcpServer
{
    Q_OBJECT
    Q_DISABLE_COPY(QExtTcpServer)
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtTcpServer)
public:
    QExtTcpServer();
    QExtTcpServer(const QSharedPointer<QExtTcpFactory> &tcpFactory);
    QExtTcpServer(QExtTcpServerPrivate *d);
    QExtTcpServer(QExtTcpServerPrivate *d, const QSharedPointer<QExtTcpFactory> &tcpFactory);
    ~QExtTcpServer();

    size_t allSocketCount() const;

    size_t maxSocketConnectionCount() const;
    void setMaxSocketConnectionCount(size_t count);

    size_t maxTaskThreadCount() const;
    void setMaxTaskThreadCount(size_t count);

    void runTask(int function);
    void runTask(QExtTcpTask *task);
    QSharedPointer<QExtTcpFactory> tcpFactory() const;
    void setTcpFactory(const QSharedPointer<QExtTcpFactory> &tcpFactory);

Q_SIGNALS:
    void serverMessage(const QString &msg);
    void socketError(const QSharedPointer<QExtTcpSocket> &socket, const QAbstractSocket::SocketError &error);
    void socketTransferError(const QSharedPointer<QExtTcpSocket> &socket, const QExtTcpSocket::TransferErrorType &error);
    void socketConnected(const QSharedPointer<QExtTcpSocket> &socket);
    void socketDisconnected(const QSharedPointer<QExtTcpSocket> &socket);

protected Q_SLOTS:
    void onSocketDisconnected();
    void onSocketError(QAbstractSocket::SocketError error);
    void onSocketTransferError(QExtTcpSocket::TransferErrorType error);

protected:
    void incomingConnection(QExtSocketDescriptor socketDescriptor) QEXT_OVERRIDE;

    QScopedPointer<QExtTcpServerPrivate> dd_ptr;
};

#endif // _QEXTTCPSERVER_H
