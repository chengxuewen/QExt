#ifndef QEXTTCPTHREADBASE_P_H
#define QEXTTCPTHREADBASE_P_H

#include <qextobject_p.h>

#include <qextnetworkglobal.h>
#include <qexttcpthreadbase.h>

#include <QPointer>
#include <QSharedPointer>
#include <QTimer>
#include <QVector>
#include <QMap>
#include <QMutex>
#include <QList>
#include <QReadWriteLock>

class QEXTTcpPacketParserBase;
class QEXTTcpThreadPoolBase;
class QEXTTcpTaskPoolBase;
class QEXTTcpThreadBase;
class QEXT_NETWORK_API QEXTTcpThreadBasePrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTTcpThreadBasePrivate(QEXTTcpThreadBase *qq);
    ~QEXTTcpThreadBasePrivate();

    void updateRunningFlag(bool isRunning);
    quint16 loadAverageTypeSecondNum(const QEXTTcpThreadBase::LoadAverageType &type) const;

    QPointer<QEXTTcpThreadPoolBase> m_threadPool;

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
    QSharedPointer<QEXTTcpTaskPoolBase> m_taskPool;

    mutable QMutex m_packetParserMutex;
    QScopedPointer<QEXTTcpPacketParserBase> m_packetParser;

private:
    QEXT_DECLARE_PUBLIC(QEXTTcpThreadBase)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpThreadBasePrivate)
};

#endif // QEXTTCPTHREADBASE_P_H
