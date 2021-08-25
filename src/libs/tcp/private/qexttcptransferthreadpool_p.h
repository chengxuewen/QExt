#ifndef QEXTTCPTRANSFERTHREADPOOL_P_H
#define QEXTTCPTRANSFERTHREADPOOL_P_H

#include <qextobject_p.h>
#include <qextid.h>

#include <qexttcpglobal.h>
#include <qexttcpabstractthreadpool_p.h>
#include <qexttcptransferthread.h>

#include <QMutex>
#include <QWaitCondition>
#include <QPointer>
#include <QThreadPool>



class QEXTTcpServer;
class QEXTTcpAbstractPacketParser;
class QEXTTcpTransferThreadPool;
class QEXT_TCP_API QEXTTcpTransferThreadPoolPrivate : public QEXTTcpAbstractThreadPoolPrivate
{
public:
    explicit QEXTTcpTransferThreadPoolPrivate(QEXTTcpTransferThreadPool *qq);
    ~QEXTTcpTransferThreadPoolPrivate();

    void handleThreadConnection(QEXTTcpTransferThread *thread, bool connect);

    QHash<QEXTId, QEXTTcpTransferThread *> m_socketTransferThreadMap;
    QScopedPointer<QEXTTcpAbstractPacketParser> m_packetParser;

private:
    QEXT_DECL_PUBLIC(QEXTTcpTransferThreadPool)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpTransferThreadPoolPrivate)
};



#endif // QEXTTCPTRANSFERTHREADPOOL_P_H
