#ifndef _QEXTTCPSERVER_P_H
#define _QEXTTCPSERVER_P_H

#include <qextTcpServer.h>
#include <qextTcpSocket.h>

#include <QSharedPointer>
#include <QMutex>
#include <QMap>
#include <QThread>
#include <QSet>
#include <QPointer>
#include <QQueue>

class QExtTcpFactory;
class QExtTcpTaskPool;
class QExtTcpTaskThreadPool;
class QExtTcpPacketParserInterface;
class QExtTcpPacketDispatcherFactory;
class QExtTcpServer;
class QEXT_TCP_API QExtTcpServerPrivate
{
public:
    explicit QExtTcpServerPrivate(QExtTcpServer *q);
    virtual ~QExtTcpServerPrivate();

    void initServer();

    QExtTcpServer * const q_ptr;

    mutable QMutex m_socketMutex;
    QHostAddress m_address;
    quint16 m_port;
    size_t m_maxSocketConnectionCount;
    size_t m_maxTaskThreadCount;
    QSet<QSharedPointer<QExtTcpSocket> > m_allTcpSocketSet;
    QMap<QExtId, QSharedPointer<QExtTcpSocket> > m_idToTcpSocketMap;
    QMap<QExtId, QSharedPointer<QExtTcpPacketDispatcher> > m_idToTcpPacketDispatcher;
    QQueue<QSharedPointer<QThread> > m_socketWorkThreadQueue;

    QSharedPointer<QExtTcpFactory> m_tcpFactory;
    QThread m_socketThread;

private:
    Q_DECLARE_PUBLIC(QExtTcpServer)
    Q_DISABLE_COPY(QExtTcpServerPrivate)
};



#endif // _QEXTTCPSERVER_P_H
