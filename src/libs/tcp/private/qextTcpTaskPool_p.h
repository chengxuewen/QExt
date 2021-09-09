#ifndef QEXTTCPTASKPOOL_P_H
#define QEXTTCPTASKPOOL_P_H

#include <qextTcpGlobal.h>

#include <qextObject_p.h>
#include <qextid.h>

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
class QEXT_TCP_API QEXTTcpTaskPoolPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTTcpTaskPoolPrivate(QEXTTcpTaskPool *qq);
    ~QEXTTcpTaskPoolPrivate();

    mutable QMutex m_mutex;
    QThreadPool m_threadPool;
    QPointer<QEXTTcpPacketDispatcher> m_packetDispatcher;
    QQueue<QEXTTcpTask *> m_waitingTaskQueue;
    QSet<QEXTTcpTask *> m_runningTaskSet;
    QMap<quint64, QEXTTcpTask *> m_idToTaskMap;
    QMap<quint64, QEXTId> m_idToIdentityIdMap;

private:
    QEXT_DECL_PUBLIC(QEXTTcpTaskPool)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpTaskPoolPrivate)
};

#endif // QEXTTCPTASKPOOL_P_H
