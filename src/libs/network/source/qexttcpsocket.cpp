#include <qexttcpsocket.h>
#include <qexttcpsocket_p.h>

#include <QDebug>

int QEXTTcpSocketPrivate::sm_id = 0;

QEXTTcpSocketPrivate::QEXTTcpSocketPrivate(QEXTTcpSocket *qq)
    : QEXTObjectPrivate(qq)
{
    sm_id++;
}

QEXTTcpSocketPrivate::~QEXTTcpSocketPrivate()
{

}



QEXTTcpSocket::QEXTTcpSocket(QObject *parent)
    : QTcpSocket(parent), QEXTObject(*(new QEXTTcpSocketPrivate(this)))
{
    qRegisterMetaType<QAbstractSocket::SocketError>("QAbstractSocket::SocketError");
    qRegisterMetaType<QEXTTcpSocket::TransferErrorType>("QEXTTcpSocket::TransferErrorType");
}

QEXTTcpSocket::QEXTTcpSocket(QEXTTcpSocketPrivate &dd, QObject *parent)
    : QTcpSocket(parent), QEXTObject(dd)
{

}

QEXTTcpSocket::~QEXTTcpSocket()
{

}

QEXTId QEXTTcpSocket::identityId() const
{
    QEXT_DC(QEXTTcpSocket);
    return d->m_identityId;
}

QString QEXTTcpSocket::transferErrorString(int error)
{
    switch (error) {
    case TransferError_SocketError: return tr("Socket error");
    case TransferError_SocketNotFound: return tr("Socket not found");
    case TransferError_SocketNotConnected: return tr("Socket not connected");
    case TransferError_PacketParserNotExist: return tr("Packet parser not exist");
    case TransferError_PacketParserReadFailed: return tr("Packet parser read failed");
    case TransferError_PacketParserWriteFailed: return tr("Packet parser write failed");
    case TransferError_PacketDispatcherNotExist: return tr("Packet dispatcher not exist");
    case TransferError_TaskPoolNotExist: return tr("Task pool not exist");
    default: break;
    }
    return "";
}
