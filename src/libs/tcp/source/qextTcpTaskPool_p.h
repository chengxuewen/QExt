#ifndef _QEXTTCPTASKPOOL_P_H
#define _QEXTTCPTASKPOOL_P_H

#include <qextTcpTaskPool.h>
#include <qextId.h>

#include <QSet>
#include <QMap>
#include <QQueue>
#include <QMutex>
#include <QPointer>
#include <QThreadPool>
#include <QWeakPointer>

class QExtTcpPacketDispatcher;
class QExtTcpTask;
class QExtTcpTaskPool;
class QEXT_TCP_API QExtTcpTaskPoolPrivate
{
public:
    explicit QExtTcpTaskPoolPrivate(QExtTcpTaskPool *q);
    virtual ~QExtTcpTaskPoolPrivate();

    QExtTcpTaskPool * const q_ptr;

    mutable QMutex m_mutex;
    QThreadPool m_threadPool;
    QPointer<QExtTcpPacketDispatcher> m_packetDispatcher;
    QQueue<QExtTcpTask *> m_waitingTaskQueue;
    QSet<QExtTcpTask *> m_runningTaskSet;
    QMap<quint64, QExtTcpTask *> m_idToTaskMap;
    QMap<quint64, QExtId> m_idToIdentityIdMap;

private:
    Q_DECLARE_PUBLIC(QExtTcpTaskPool)
    Q_DISABLE_COPY(QExtTcpTaskPoolPrivate)
};

#endif // _QEXTTCPTASKPOOL_P_H
