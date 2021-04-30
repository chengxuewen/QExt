#ifndef QEXTTCPTRANSFERTHREADPOOL_H
#define QEXTTCPTRANSFERTHREADPOOL_H

#include <qextnetworkglobal.h>
#include <qexttcpthreadpoolbase.h>
#include <qexttcptransferthread.h>

#include <QObject>
#include <QTcpSocket>

class QEXTTcpServerSocket;
class QEXTTcpPacketBase;
class QEXTTcpPacketParserBase;
class QEXTTcpTransferThreadPoolPrivate;
class QEXT_NETWORK_API QEXTTcpTransferThreadPool : public QEXTTcpThreadPoolBase
{
    Q_OBJECT
public:
    explicit QEXTTcpTransferThreadPool(QObject *parent = QEXT_NULLPTR);
    ~QEXTTcpTransferThreadPool();

    void removeThread() QEXT_OVERRIDE;
    void addThread() QEXT_OVERRIDE;

    void setTaskPool(QSharedPointer<QEXTTcpTaskPoolBase> taskPool) QEXT_OVERRIDE;

    void addSocket(QEXTTcpServerSocket *socket, QEXTTcpTransferThread *thread);
    void removeSocket(QEXTTcpServerSocket *socket, QEXTTcpTransferThread *thread);

Q_SIGNALS:
    void establishConnectionInThread(QObject *threadObj, QEXTSocketDescriptor socketDescriptor);
    void addPacketToThread(QObject *threadObj, QEXTTcpPacketBase *packet);
    void addSocketToThread(QObject *threadObj, QEXTTcpServerSocket *socket, const QList<QEXTTcpPacketBase *> &packetList);

    void socketMessage(QEXTTcpServerSocket *socket, const QString &msg);
    void socketError(QEXTTcpServerSocket *socket, QAbstractSocket::SocketError error);

    void socketConnected(QEXTTcpServerSocket *socket);
    void socketDisconnected(QEXTTcpServerSocket *socket);

    void transferError(QEXTTcpSocket::TransferErrorType error);

protected Q_SLOTS:
    void establishConnection(QEXTSocketDescriptor socketDescriptor);
    void dispatchPacketToThread(QEXTTcpPacketBase *packet);
    void dispatchSocketToThread(QEXTTcpServerSocket *socket, const QList<QEXTTcpPacketBase *> &packetList);

private:
    QEXT_DECLARE_PRIVATE(QEXTTcpTransferThreadPool)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpTransferThreadPool)
};

#endif // QEXTTCPTRANSFERTHREADPOOL_H
