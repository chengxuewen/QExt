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

class QExtTcpSocket;
class QEXT_TCP_API QExtTcpSocketPrivate
{
public:
    explicit QExtTcpSocketPrivate(QExtTcpSocket *q);
    virtual ~QExtTcpSocketPrivate();

    QExtTcpSocket * const q_ptr;

    mutable QMutex m_packetMutex;
    QQueue<QSharedPointer<QExtTcpPacketInterface> > m_sendPacketQueue;

    mutable QMutex m_packetParserMutex;
    QSharedPointer<QExtTcpPacketParserInterface> m_packetParser;

    mutable QMutex m_packetDispatcherMutex;
    QSharedPointer<QExtTcpPacketDispatcher> m_packetDispatcher;

    QSharedPointer<QThread> m_workThread;

    QString m_peerAddress;
    quint16 m_peerPort;
    QExtId m_identityId;
    static int sm_id;

private:
    Q_DECLARE_PUBLIC(QExtTcpSocket)
    Q_DISABLE_COPY(QExtTcpSocketPrivate)
};



#endif // _QEXTTCPSOCKET_P_H
