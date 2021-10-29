#ifndef _QEXTTCPSERVER_P_H
#define _QEXTTCPSERVER_P_H

#include <qextTcpGlobal.h>
#include <qextTcpSocket.h>

#include <QSharedPointer>
#include <QMutex>
#include <QMap>
#include <QThread>
#include <QSet>
#include <QPointer>
#include <QQueue>

class QEXTTcpFactory;
class QEXTTcpTaskPool;
class QEXTTcpTaskThreadPool;
class QEXTTcpPacketParserInterface;
class QEXTTcpPacketDispatcherFactory;
class QEXTTcpServer;
class QEXT_TCP_API QEXTTcpServerPrivate
{
public:
    explicit QEXTTcpServerPrivate(QEXTTcpServer *q);
    virtual ~QEXTTcpServerPrivate();

    void initServer();

    QEXTTcpServer * const q_ptr;

    mutable QMutex m_socketMutex;
    QHostAddress m_address;
    quint16 m_port;
    size_t m_maxSocketConnectionCount;
    size_t m_maxTaskThreadCount;
    QSet<QSharedPointer<QEXTTcpSocket> > m_allTcpSocketSet;
    QMap<QEXTId, QSharedPointer<QEXTTcpSocket> > m_idToTcpSocketMap;
    QMap<QEXTId, QSharedPointer<QEXTTcpPacketDispatcher> > m_idToTcpPacketDispatcher;
    QQueue<QSharedPointer<QThread> > m_socketWorkThreadQueue;

    QSharedPointer<QEXTTcpFactory> m_tcpFactory;
    QThread m_socketThread;

private:
    QEXT_DECL_PUBLIC(QEXTTcpServer)
    QEXT_DECL_DISABLE_COPY(QEXTTcpServerPrivate)
};



#endif // _QEXTTCPSERVER_P_H
