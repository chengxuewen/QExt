#ifndef QEXTTCPSERVER_P_H
#define QEXTTCPSERVER_P_H

#include <qextobject_p.h>

#include <qexttcpglobal.h>
#include <qexttcpserversocket.h>

#include <QSharedPointer>
#include <QMutex>
#include <QMap>
#include <QSet>
#include <QPointer>



class QEXTTcpAbstractTaskPool;
class QEXTTcpAbstractPacketParser;
class QEXTTcpTaskThreadPool;
class QEXTTcpTransferThreadPool;
class QEXTTcpServer;
class QEXT_TCP_API QEXTTcpServerPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTTcpServerPrivate(QEXTTcpServer *qq);
    ~QEXTTcpServerPrivate();

    void initServer();

    mutable QMutex m_socketMutex;
    int m_maxTcpSocketCount;
    QSet<QEXTTcpServerSocket *> m_allTcpSocketSet;
    QSet<QEXTTcpServerSocket *> m_invalidTcpSocketSet;
    QScopedPointer<QEXTTcpTransferThreadPool> m_transferThreadPool;
    QScopedPointer<QEXTTcpTaskThreadPool> m_taskThreadPool;
    QScopedPointer<QEXTTcpAbstractPacketParser> m_packetParser;

    QSharedPointer<QEXTTcpAbstractTaskPool> m_taskPool;
    QScopedPointer<QThread> m_taskPoolThread;

private:
    QEXT_DECLARE_PUBLIC(QEXTTcpServer)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpServerPrivate)
};



#endif // QEXTTCPSERVER_P_H
