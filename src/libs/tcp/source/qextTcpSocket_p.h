#ifndef _QEXTTCPSOCKET_P_H
#define _QEXTTCPSOCKET_P_H

#include <qextTcpPacketInterface.h>
#include <qextTcpPacketParserInterface.h>
#include <qextTcpPacketDispatcher.h>
#include <qextTcpSocket.h>
#include <qextId.h>

#include <QQueue>
#include <QMutex>
#include <QPointer>
#include <QThread>

class QEXTTcpSocket;
class QEXT_TCP_API QEXTTcpSocketPrivate
{
public:
    explicit QEXTTcpSocketPrivate(QEXTTcpSocket *q);
    virtual ~QEXTTcpSocketPrivate();

    QEXTTcpSocket * const q_ptr;

    mutable QMutex m_packetMutex;
    QQueue<QSharedPointer<QEXTTcpPacketInterface> > m_sendPacketQueue;

    mutable QMutex m_packetParserMutex;
    QSharedPointer<QEXTTcpPacketParserInterface> m_packetParser;

    mutable QMutex m_packetDispatcherMutex;
    QSharedPointer<QEXTTcpPacketDispatcher> m_packetDispatcher;

    QSharedPointer<QThread> m_workThread;

    QString m_peerAddress;
    quint16 m_peerPort;
    QEXTId m_identityId;
    static int sm_id;

private:
    Q_DECLARE_PUBLIC(QEXTTcpSocket)
    Q_DISABLE_COPY(QEXTTcpSocketPrivate)
};



#endif // _QEXTTCPSOCKET_P_H
