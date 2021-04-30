#ifndef QEXTTCPTRANSFERTHREADPOOL_P_H
#define QEXTTCPTRANSFERTHREADPOOL_P_H

#include <qextobject_p.h>
#include <qextid.h>

#include <qextnetworkglobal.h>
#include <qexttcpthreadpoolbase_p.h>
#include <qexttcptransferthread.h>

#include <QMutex>
#include <QWaitCondition>
#include <QPointer>
#include <QThreadPool>

class QEXTTcpServer;
class QEXTTcpPacketParserBase;
class QEXTTcpTransferThreadPool;
class QEXT_NETWORK_API QEXTTcpTransferThreadPoolPrivate : public QEXTTcpThreadPoolBasePrivate
{
public:
    explicit QEXTTcpTransferThreadPoolPrivate(QEXTTcpTransferThreadPool *qq);
    ~QEXTTcpTransferThreadPoolPrivate();

    void handleThreadConnection(QEXTTcpTransferThread *thread, bool connect);

    QHash<QEXTId, QEXTTcpTransferThread *> m_socketTransferThreadMap;
    QScopedPointer<QEXTTcpPacketParserBase> m_packetParser;

private:
    QEXT_DECLARE_PUBLIC(QEXTTcpTransferThreadPool)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpTransferThreadPoolPrivate)
};

#endif // QEXTTCPTRANSFERTHREADPOOL_P_H
