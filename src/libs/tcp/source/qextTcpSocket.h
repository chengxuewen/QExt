#ifndef _QEXTTCPSOCKET_H
#define _QEXTTCPSOCKET_H

#include <qextTagId.h>

#include <qextTcpGlobal.h>

#include <QSharedPointer>
#include <QTcpSocket>
#include <QPointer>
#include <QThread>

class QExtTcpPacketInterface;
class QExtTcpPacketDispatcher;
class QExtTcpPacketParserInterface;
class QExtTcpSocketPrivate;
class QEXT_TCP_API QExtTcpSocket : public QTcpSocket
{
    Q_OBJECT
    Q_DISABLE_COPY(QExtTcpSocket)
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtTcpSocket)
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

    QExtTcpSocket();
    QExtTcpSocket(const QSharedPointer<QExtTcpPacketParserInterface> &packetParser);
    QExtTcpSocket(QExtTcpSocketPrivate *d, const QSharedPointer<QExtTcpPacketParserInterface> &packetParser);
    ~QExtTcpSocket();

    QSharedPointer<QExtTcpPacketParserInterface> packetParser() const;
    void setPacketParser(const QSharedPointer<QExtTcpPacketParserInterface> &packetParser);

    QSharedPointer<QExtTcpPacketDispatcher> packetDispatcher() const;
    void setPacketDispatcher(const QSharedPointer<QExtTcpPacketDispatcher> &packetDispatcher);

    QSharedPointer<QThread> workThread() const;
    QSharedPointer<QThread> detachWorkThread();
    void attatchWorkThread(const QSharedPointer<QThread> &thread);

    void enqueueSendPacket(const QSharedPointer<QExtTcpPacketInterface> &packet);

    bool isConnected() const;
    QExtTagId identityId() const;
    static QString transferErrorText(int error);

Q_SIGNALS:
    void newPacketSend(const QString &data);
    void newPacketReceived(const QString &data);
    void transferErrorString(const QString &error);
    void transferError(const QExtTcpSocket::TransferErrorType &error);

public Q_SLOTS:
    QExtTagId updateIdentityId();
    void sendPacket();

    void connectToServer(const QString &ipAddress, quint16 port);
    void closeSocket();
    void abortSocket();

protected Q_SLOTS:
    void readPacket();

protected:
    QScopedPointer<QExtTcpSocketPrivate> dd_ptr;
};


#endif // _QEXTTCPSOCKET_H
