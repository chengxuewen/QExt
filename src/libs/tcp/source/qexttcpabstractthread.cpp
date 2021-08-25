#include <qexttcpabstractthread.h>
#include <qexttcpabstractthread_p.h>
#include <qexttcpabstractthreadpool.h>
#include <qexttcpabstracttask.h>

#include <QThread>
#include <QDateTime>
#include <QReadLocker>
#include <QWriteLocker>



QEXTTcpAbstractThreadPrivate::QEXTTcpAbstractThreadPrivate(QEXTTcpAbstractThread *qq)
    : QEXTObjectPrivate(qq)
{
    m_runningFlag = false;
    m_isQuit = false;
    m_runningTime = 0;
    m_runningStartTimestamp = 0;
    m_loadAverageTimer.reset(new QTimer);
}

QEXTTcpAbstractThreadPrivate::~QEXTTcpAbstractThreadPrivate()
{

}

void QEXTTcpAbstractThreadPrivate::updateRunningFlag(bool isRunning)
{
    m_runningLock.lockForWrite();
    m_runningFlag = isRunning;
    quint64 currentMSecsSinceEpoch = QDateTime::currentDateTime().toMSecsSinceEpoch();
    if (isRunning) {
        m_runningStartTimestamp = currentMSecsSinceEpoch;
    } else {
        m_runningTime += currentMSecsSinceEpoch - m_runningStartTimestamp;
        m_runningStartTimestamp = 0;
    }
    m_runningLock.unlock();
}

quint16 QEXTTcpAbstractThreadPrivate::loadAverageTypeSecondNum(const QEXTTcpAbstractThread::LoadAverageType &type) const
{
    switch (type) {
    case QEXTTcpAbstractThread::LoadAverage_1Minute: return 30;
    case QEXTTcpAbstractThread::LoadAverage_5Minute: return 150;
    case QEXTTcpAbstractThread::LoadAverage_15Minute: return 450;
    case QEXTTcpAbstractThread::LoadAverage_30Minute: return 900;
    case QEXTTcpAbstractThread::LoadAverage_1Hour: return 1800;
    default: break;
    }
    return 0;
}



QEXTTcpAbstractThread::QEXTTcpAbstractThread(QEXTTcpAbstractThreadPrivate &dd, QEXTTcpAbstractThreadPool *threadPool)
    : QObject(QEXT_DECL_NULLPTR), QEXTObject(dd)
{
    QEXT_DECL_D(QEXTTcpAbstractThread);
    d->m_threadPool = threadPool;
    d->m_loadAverageTimer->setInterval(2000);
    connect(d->m_loadAverageTimer.data(), SIGNAL(timeout()), this, SLOT(loadAverageTimerTimeout()));
    d->m_loadAverageTimer->start();
}

QEXTTcpAbstractThread::~QEXTTcpAbstractThread()
{

}

bool QEXTTcpAbstractThread::isBusy() const
{
    QEXT_DECL_DC(QEXTTcpAbstractThread);
    QReadLocker readLocker(&d->m_runningLock);
    return d->m_runningFlag;
}

bool QEXTTcpAbstractThread::isQuit() const
{
    QEXT_DECL_DC(QEXTTcpAbstractThread);
    QReadLocker readLocker(&d->m_quitLock);
    return d->m_isQuit;
}

double QEXTTcpAbstractThread::loadAverage(QEXTTcpAbstractThread::LoadAverageType type) const
{
    QEXT_DECL_DC(QEXTTcpAbstractThread);
    d->m_loadAverageLock.lockForRead();
    int loadAverageNum = d->loadAverageTypeSecondNum(type);
    int runningNum = d->m_perSecondRunningTimeList.size();
    double runningTime = 0;
    runningNum = qMin(runningNum, loadAverageNum);
    if (0 == runningNum) {
        d->m_runningLock.lockForRead();
        loadAverageNum = 1;
        if (d->m_runningFlag) {
            runningTime = QDateTime::currentDateTime().toMSecsSinceEpoch() - d->m_runningStartTimestamp;
        }
        d->m_runningLock.unlock();
    } else {
        for (int i = runningNum - 1; i >= 0; --i) {
            runningTime += d->m_perSecondRunningTimeList.at(i);
        }
    }
    d->m_loadAverageLock.unlock();
    return runningTime / (runningNum * 2000.0);
}

QEXTTcpAbstractPacketParser *QEXTTcpAbstractThread::packetParser() const
{
    QEXT_DECL_DC(QEXTTcpAbstractThread);
    QMutexLocker mutexLocker(&d->m_packetParserMutex);
    return d->m_packetParser.data();
}

QEXTTcpAbstractTaskPool *QEXTTcpAbstractThread::taskPool() const
{
    QEXT_DECL_DC(QEXTTcpAbstractThread);
    QMutexLocker mutexLocker(&d->m_taskPoolMutex);
    return d->m_taskPool.data();
}

void QEXTTcpAbstractThread::setPacketParser(QEXTTcpAbstractPacketParser *packetParser)
{
    QEXT_DECL_D(QEXTTcpAbstractThread);
    QMutexLocker mutexLocker(&d->m_packetParserMutex);
    if (packetParser && packetParser != d->m_packetParser.data()) {
        d->m_packetParser.reset(packetParser);
    }
}

void QEXTTcpAbstractThread::setTaskPool(QSharedPointer<QEXTTcpAbstractTaskPool> taskPool)
{
    QEXT_DECL_D(QEXTTcpAbstractThread);
    QMutexLocker mutexLocker(&d->m_taskPoolMutex);
    if (!taskPool.isNull() && taskPool != d->m_taskPool) {
        d->m_taskPool = taskPool;
    }
}

void QEXTTcpAbstractThread::loadAverageTimerTimeout()
{
    QEXT_DECL_D(QEXTTcpAbstractThread);
    d->m_runningLock.lockForWrite();
    quint16 runningTime = d->m_runningTime;
    d->m_runningTime = 0;
    if (d->m_runningFlag) {
        quint64 currentMSecsSinceEpoch = QDateTime::currentDateTime().toMSecsSinceEpoch();
        runningTime += currentMSecsSinceEpoch - d->m_runningStartTimestamp;
        d->m_runningStartTimestamp = currentMSecsSinceEpoch;
    }
    d->m_runningLock.unlock();

    d->m_loadAverageLock.lockForWrite();
    d->m_perSecondRunningTimeList.append(runningTime);
    if (d->m_perSecondRunningTimeList.size() > d->loadAverageTypeSecondNum(QEXTTcpAbstractThread::LoadAverage_1Hour)) {
        d->m_perSecondRunningTimeList.removeFirst();
    }
    d->m_loadAverageLock.unlock();
}
