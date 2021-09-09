#ifndef QEXTTCPSOCKET_H
#define QEXTTCPSOCKET_H

#include <qextObject.h>
#include <qextid.h>

#include <qextTcpGlobal.h>

#include <QSharedPointer>
#include <QTcpSocket>
#include <QPointer>
#include <QThread>

class QEXTTcpPacketInterface;
class QEXTTcpPacketDispatcher;
class QEXTTcpPacketParserInterface;
class QEXTTcpSocketPrivate;
class QEXT_TCP_API QEXTTcpSocket : public QTcpSocket, public QEXTObject
{
    Q_OBJECT
public:
    enum TransferErrorType {
        TransferError_SocketError = 0,
        TransferError_SocketNotFound,
        TransferError_SocketNotConnected,
        TransferError_PacketParserNotExist,
        TransferError_PacketParserReadFailed,
        TransferError_PacketParserWriteFailed,
        TransferError_PacketDispatcherNotExist,
        TransferError_PacketTransceiverNotExist,
        TransferError_TaskPoolNotExist,
        TransferError_Unknown
    };

    QEXTTcpSocket();
    QEXTTcpSocket(const QSharedPointer<QEXTTcpPacketParserInterface> &packetParser);
    QEXTTcpSocket(QEXTTcpSocketPrivate &dd, const QSharedPointer<QEXTTcpPacketParserInterface> &packetParser);
    ~QEXTTcpSocket();

    QSharedPointer<QEXTTcpPacketParserInterface> packetParser() const;
    void setPacketParser(const QSharedPointer<QEXTTcpPacketParserInterface> &packetParser);

    QSharedPointer<QEXTTcpPacketDispatcher> packetDispatcher() const;
    void setPacketDispatcher(const QSharedPointer<QEXTTcpPacketDispatcher> &packetDispatcher);

    QSharedPointer<QThread> workThread() const;
    QSharedPointer<QThread> detachWorkThread();
    void attatchWorkThread(const QSharedPointer<QThread> &thread);

    void enqueueSendPacket(const QSharedPointer<QEXTTcpPacketInterface> &packet);

    bool isConnected() const;
    QEXTId identityId() const;
    static QString transferErrorText(int error);

Q_SIGNALS:
    void newPacketSend(const QString &data);
    void newPacketReceived(const QString &data);
    void transferErrorString(const QString &error);
    void transferError(const QEXTTcpSocket::TransferErrorType &error);

public Q_SLOTS:
    QEXTId updateIdentityId();
    void sendPacket();

    void connectToServer(const QString &ipAddress, quint16 port);
    void closeSocket();
    void abortSocket();

protected Q_SLOTS:
    void readPacket();

private:
    QEXT_DECL_PRIVATE(QEXTTcpSocket)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpSocket)
};


#endif // QEXTTCPSOCKET_H
