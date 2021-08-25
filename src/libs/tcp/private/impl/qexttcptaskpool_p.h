#ifndef QEXTTCPTASKPOOL_P_H
#define QEXTTCPTASKPOOL_P_H

#include <qextobject_p.h>
#include <qextid.h>

#include <qexttcpglobal.h>

#include <QHash>
#include <QMutex>
#include <QQueue>



class QEXTTcpAbstractPacketParser;
class QEXTTcpAbstractTask;
class QEXTTcpTaskPool;
class QEXT_TCP_API QEXTTcpTaskPoolPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTTcpTaskPoolPrivate(QEXTTcpTaskPool *qq);
    ~QEXTTcpTaskPoolPrivate();

    mutable QMutex m_taskMutex;
    QHash<QEXTId, QEXTTcpAbstractTask *> m_unfinishedTaskMap;
    QList<QEXTTcpAbstractTask *> m_finishedTaskList;
    QQueue<QEXTTcpAbstractTask *> m_taskQueue;
    QSet<QEXTTcpAbstractTask *> m_expiredTasksSet;

    mutable QMutex m_packetParserMutex;
    QScopedPointer<QEXTTcpAbstractPacketParser> m_packetParser;

private:
    QEXT_DECL_PUBLIC(QEXTTcpTaskPool)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpTaskPoolPrivate)
};



#endif // QEXTTCPTASKPOOL_P_H
