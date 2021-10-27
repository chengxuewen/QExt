#ifndef _QEXTTCPCLIENT_P_H
#define _QEXTTCPCLIENT_P_H

#include <qextTcpGlobal.h>
#include <qextTcpPacketTransceiver_p.h>

#include <QScopedPointer>
#include <QSharedPointer>
#include <QThread>
#include <QMutex>
#include <QMap>

class QEXTTcpSocket;
class QEXTTcpFactory;
class QEXTTcpTaskPool;
class QEXTTcpPacketDispatcher;
class QEXTTcpPacketParserInterface;
class QEXTTcpClient;
class QEXT_TCP_API QEXTTcpClientPrivate : public QEXTTcpPacketTransceiverPrivate
{
public:
    explicit QEXTTcpClientPrivate(QEXTTcpClient *q);
    ~QEXTTcpClientPrivate();

    mutable QMutex m_socketMutex;
    int m_maxTaskThreadCount;
    QSharedPointer<QEXTTcpSocket> m_socket;
    QSharedPointer<QThread> m_socketThread;
    QSharedPointer<QEXTTcpFactory> m_tcpFactory;

private:
    QEXT_DECL_PUBLIC(QEXTTcpClient)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpClientPrivate)
};



#endif // _QEXTTCPCLIENT_P_H
