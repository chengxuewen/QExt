#ifndef QEXTTCPTHREADPOOLBASE_P_H
#define QEXTTCPTHREADPOOLBASE_P_H

#include <qextobject_p.h>

#include <qextnetworkglobal.h>

#include <QMap>
#include <QSet>
#include <QQueue>
#include <QMutex>
#include <QPointer>
#include <QSharedPointer>

class QEXTTcpServer;
class QEXTTcpTaskPoolBase;
class QEXTTcpThreadBase;
class QEXTTcpThreadPoolBase;
class QEXTTcpPacketParserBase;
class QEXT_NETWORK_API QEXTTcpThreadPoolBasePrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTTcpThreadPoolBasePrivate(QEXTTcpThreadPoolBase *qq);
    ~QEXTTcpThreadPoolBasePrivate();

    mutable QMutex m_taskPoolMutex;
    QSharedPointer<QEXTTcpTaskPoolBase> m_taskPool;

    mutable QMutex m_packetParserMutex;
    QScopedPointer<QEXTTcpPacketParserBase> m_packetParser;

    mutable QMutex m_threadMutex;
    QSet<QEXTTcpThreadBase *> m_allThreadsSet;
    QSet<QEXTTcpThreadBase *> m_workingThreadsSet;
    QQueue<QEXTTcpThreadBase *> m_idleThreadsQueue;
    QMap<QEXTTcpThreadBase *, QThread *> m_threadMap;

private:
    QEXT_DECLARE_PUBLIC(QEXTTcpThreadPoolBase)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpThreadPoolBasePrivate)
};

#endif // QEXTTCPTHREADPOOLBASE_P_H
