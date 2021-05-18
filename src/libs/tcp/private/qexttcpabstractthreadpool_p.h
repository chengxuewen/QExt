#ifndef QEXTTCPABSTRACTTHREADPOOL_P_H
#define QEXTTCPABSTRACTTHREADPOOL_P_H

#include <qextobject_p.h>

#include <qexttcpglobal.h>

#include <QMap>
#include <QSet>
#include <QQueue>
#include <QMutex>
#include <QPointer>
#include <QSharedPointer>



class QEXTTcpServer;
class QEXTTcpAbstractTaskPool;
class QEXTTcpAbstractThread;
class QEXTTcpAbstractThreadPool;
class QEXTTcpAbstractPacketParser;
class QEXT_TCP_API QEXTTcpAbstractThreadPoolPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTTcpAbstractThreadPoolPrivate(QEXTTcpAbstractThreadPool *qq);
    ~QEXTTcpAbstractThreadPoolPrivate();

    mutable QMutex m_taskPoolMutex;
    QSharedPointer<QEXTTcpAbstractTaskPool> m_taskPool;

    mutable QMutex m_packetParserMutex;
    QScopedPointer<QEXTTcpAbstractPacketParser> m_packetParser;

    mutable QMutex m_threadMutex;
    QSet<QEXTTcpAbstractThread *> m_allThreadsSet;
    QSet<QEXTTcpAbstractThread *> m_workingThreadsSet;
    QQueue<QEXTTcpAbstractThread *> m_idleThreadsQueue;
    QMap<QEXTTcpAbstractThread *, QThread *> m_threadMap;

private:
    QEXT_DECLARE_PUBLIC(QEXTTcpAbstractThreadPool)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpAbstractThreadPoolPrivate)
};



#endif // QEXTTCPABSTRACTTHREADPOOL_P_H
