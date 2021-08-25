#ifndef QEXTTCPABSTRACTTHREAD_P_H
#define QEXTTCPABSTRACTTHREAD_P_H

#include <qextobject_p.h>

#include <qexttcpglobal.h>
#include <qexttcpabstractthread.h>

#include <QPointer>
#include <QSharedPointer>
#include <QTimer>
#include <QVector>
#include <QMap>
#include <QMutex>
#include <QList>
#include <QReadWriteLock>



class QEXTTcpAbstractPacketParser;
class QEXTTcpAbstractThreadPool;
class QEXTTcpAbstractTaskPool;
class QEXTTcpAbstractThread;
class QEXT_TCP_API QEXTTcpAbstractThreadPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTTcpAbstractThreadPrivate(QEXTTcpAbstractThread *qq);
    ~QEXTTcpAbstractThreadPrivate();

    void updateRunningFlag(bool isRunning);
    quint16 loadAverageTypeSecondNum(const QEXTTcpAbstractThread::LoadAverageType &type) const;

    QPointer<QEXTTcpAbstractThreadPool> m_threadPool;

    mutable QReadWriteLock m_quitLock;
    bool m_isQuit;

    mutable QReadWriteLock m_runningLock;
    bool m_runningFlag;
    quint16 m_runningTime;
    quint64 m_runningStartTimestamp;

    mutable QReadWriteLock m_loadAverageLock;
    QList<quint16> m_perSecondRunningTimeList;
    QScopedPointer<QTimer> m_loadAverageTimer;

    mutable QMutex m_taskPoolMutex;
    QSharedPointer<QEXTTcpAbstractTaskPool> m_taskPool;

    mutable QMutex m_packetParserMutex;
    QScopedPointer<QEXTTcpAbstractPacketParser> m_packetParser;

private:
    QEXT_DECL_PUBLIC(QEXTTcpAbstractThread)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpAbstractThreadPrivate)
};



#endif // QEXTTCPABSTRACTTHREAD_P_H
