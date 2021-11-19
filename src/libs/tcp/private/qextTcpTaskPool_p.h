#ifndef _QEXTTCPTASKPOOL_P_H
#define _QEXTTCPTASKPOOL_P_H

#include <qextTcpGlobal.h>
#include <qextId.h>

#include <QSet>
#include <QMap>
#include <QQueue>
#include <QMutex>
#include <QPointer>
#include <QThreadPool>
#include <QWeakPointer>

class QEXTTcpPacketDispatcher;
class QEXTTcpTask;
class QEXTTcpTaskPool;
class QEXT_TCP_API QEXTTcpTaskPoolPrivate
{
public:
    explicit QEXTTcpTaskPoolPrivate(QEXTTcpTaskPool *q);
    virtual ~QEXTTcpTaskPoolPrivate();

    QEXTTcpTaskPool * const q_ptr;

    mutable QMutex m_mutex;
    QThreadPool m_threadPool;
    QPointer<QEXTTcpPacketDispatcher> m_packetDispatcher;
    QQueue<QEXTTcpTask *> m_waitingTaskQueue;
    QSet<QEXTTcpTask *> m_runningTaskSet;
    QMap<quint64, QEXTTcpTask *> m_idToTaskMap;
    QMap<quint64, QEXTId> m_idToIdentityIdMap;

private:
    Q_DECLARE_PUBLIC(QEXTTcpTaskPool)
    QEXT_DECL_DISABLE_COPY(QEXTTcpTaskPoolPrivate)
};

#endif // _QEXTTCPTASKPOOL_P_H
