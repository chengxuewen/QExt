#ifndef _QEXTTCPCLIENT_P_H
#define _QEXTTCPCLIENT_P_H

#include <qextTcpClient.h>
#include <private/qextTcpPacketTransceiver_p.h>

#include <QScopedPointer>
#include <QSharedPointer>
#include <QThread>
#include <QMutex>
#include <QMap>

class QExtTcpSocket;
class QExtTcpFactory;
class QExtTcpTaskPool;
class QExtTcpPacketDispatcher;
class QExtTcpPacketParserInterface;
class QExtTcpClient;
class QEXT_TCP_API QExtTcpClientPrivate : public QExtTcpPacketTransceiverPrivate
{
public:
    explicit QExtTcpClientPrivate(QExtTcpClient *q);
    ~QExtTcpClientPrivate();

    mutable QMutex m_socketMutex;
    int m_maxTaskThreadCount;
    QSharedPointer<QExtTcpSocket> m_socket;
    QSharedPointer<QThread> m_socketThread;
    QSharedPointer<QExtTcpFactory> m_tcpFactory;

private:
    Q_DECLARE_PUBLIC(QExtTcpClient)
    Q_DISABLE_COPY(QExtTcpClientPrivate)
};


#endif // _QEXTTCPCLIENT_P_H
