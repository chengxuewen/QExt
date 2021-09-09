#ifndef QEXTTCPSERVER_P_H
#define QEXTTCPSERVER_P_H

#include <qextTcpGlobal.h>
#include <qextTcpSocket.h>

#include <qextObject_p.h>

#include <QSharedPointer>
#include <QMutex>
#include <QMap>
#include <QThread>
#include <QSet>
#include <QPointer>
#include <QQueue>

class QEXTTcpTaskPool;
class QEXTTcpTaskThreadPool;
class QEXTTcpPacketParserInterface;
class QEXTTcpPacketDispatcherFactory;
class QEXTTcpServer;
class QEXT_TCP_API QEXTTcpServerPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTTcpServerPrivate(QEXTTcpServer *qq);
    ~QEXTTcpServerPrivate();

    void initServer();

    mutable QMutex m_socketMutex;
    int m_maxTcpSocketCount;
    QSet<QSharedPointer<QEXTTcpSocket> > m_allTcpSocketSet;
    QMap<QEXTId, QSharedPointer<QEXTTcpSocket> > m_idToTcpSocketMap;
    QQueue<QSharedPointer<QThread> > m_socketWorkThreadQueue;

    QSharedPointer<QEXTTcpPacketParserInterface> m_packetParser;
    QSharedPointer<QEXTTcpPacketDispatcherFactory> m_packetDispatcherFactory;

    QThread m_socketThread;

private:
    QEXT_DECL_PUBLIC(QEXTTcpServer)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpServerPrivate)
};



#endif // QEXTTCPSERVER_P_H
