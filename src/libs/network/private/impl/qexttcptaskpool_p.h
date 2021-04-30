#ifndef QEXTTCPTASKPOOL_P_H
#define QEXTTCPTASKPOOL_P_H

#include <qextobject_p.h>
#include <qextid.h>

#include <qextnetworkglobal.h>

#include <QHash>
#include <QMutex>
#include <QQueue>

class QEXTTcpPacketParserBase;
class QEXTTcpTaskBase;
class QEXTTcpTaskPool;
class QEXT_NETWORK_API QEXTTcpTaskPoolPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTTcpTaskPoolPrivate(QEXTTcpTaskPool *qq);
    ~QEXTTcpTaskPoolPrivate();

    mutable QMutex m_taskMutex;
    QHash<QEXTId, QEXTTcpTaskBase *> m_unfinishedTaskMap;
    QList<QEXTTcpTaskBase *> m_finishedTaskList;
    QQueue<QEXTTcpTaskBase *> m_taskQueue;
    QSet<QEXTTcpTaskBase *> m_expiredTasksSet;

    mutable QMutex m_packetParserMutex;
    QScopedPointer<QEXTTcpPacketParserBase> m_packetParser;

private:
    QEXT_DECLARE_PUBLIC(QEXTTcpTaskPool)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpTaskPoolPrivate)
};

#endif // QEXTTCPTASKPOOL_P_H
