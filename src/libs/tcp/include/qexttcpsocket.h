#ifndef QEXTTCPSOCKET_H
#define QEXTTCPSOCKET_H

#include <qextobject.h>
#include <qextid.h>

#include <qexttcpglobal.h>

#include <QTcpSocket>



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
        TransferError_TaskPoolNotExist,
        TransferError_Unknown
    };

    explicit QEXTTcpSocket(QObject *parent = QEXT_NULLPTR);
    QEXTTcpSocket(QEXTTcpSocketPrivate &dd, QObject *parent = QEXT_NULLPTR);
    ~QEXTTcpSocket();

    QEXTId identityId() const;

    static QString transferErrorString(int error);

Q_SIGNALS:
    void transferError(const QEXTTcpSocket::TransferErrorType &error);

public Q_SLOTS:
    virtual void updateIdentityId() = 0;

private:
    QEXT_DECLARE_PRIVATE(QEXTTcpSocket)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpSocket)
};



#endif // QEXTTCPSOCKET_H
