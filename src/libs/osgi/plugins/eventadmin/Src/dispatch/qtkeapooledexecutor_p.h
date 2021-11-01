#ifndef QTKEAPOOLEDEXECUTOR_P_H
#define QTKEAPOOLEDEXECUTOR_P_H

#include "qtkeathreadfactoryuser_p.h"

#include <QHash>
#include <QRunnable>
#include <QWaitCondition>

struct QTKEAChannel;
class QTKEAInterruptibleThread;

class QTKEAPooledExecutor : public QTKEAThreadFactoryUser
{
public:
    struct BlockedExecutionHandler {
        virtual ~BlockedExecutionHandler() {}

        virtual bool blockedAction(QTKEARunnable *pCommand) = 0;
    };

    QTKEAPooledExecutor(QTKEAChannel *pChannel, int iMaxPoolSize = DEFAULT_MAXIMUMPOOLSIZE);
    ~QTKEAPooledExecutor();

    int getMaximumPoolSize() const;
    void setMaximumPoolSize(int iNewMaximum);
    int getMinimumPoolSize() const;
    void setMinimumPoolSize(int iNewMinimum);
    int getPoolSize() const;
    long getKeepAliveTime() const;
    void setKeepAliveTime(long lMsecs);

    BlockedExecutionHandler* getBlockedExecutionHandler() const;
    void setBlockedExecutionHandler(BlockedExecutionHandler *pHandler);

    int createThreads(int iNumberOfThreads);
    void interruptAll();
    void shutdownNow();
    void shutdownNow(BlockedExecutionHandler *pHandler);
    void shutdownAfterProcessingCurrentlyQueuedTasks();
    void shutdownAfterProcessingCurrentlyQueuedTasks(BlockedExecutionHandler *pHandler);

    bool isTerminatedAfterShutdown() const;
    bool awaitTerminationAfterShutdown(long lMaxWaitTime) const;
    void awaitTerminationAfterShutdown() const;

    QList<QTKEARunnable *> drain();

    void runWhenBlocked();
    void waitWhenBlocked();
    void discardWhenBlocked();
    void abortWhenBlocked();
    void discardOldestWhenBlocked();
    void execute(QTKEARunnable *pCommand);

    static const int DEFAULT_MAXIMUMPOOLSIZE; // = std::numeric_limits<int>::max()

    static const int  DEFAULT_MINIMUMPOOLSIZE; // = 1

    static const long DEFAULT_KEEPALIVETIME; // = 60 * 1000

protected:
    class Worker : public QTKEARunnable
    {
    public:
        Worker(QTKEAPooledExecutor *pPooledExecutor, QTKEARunnable *pFirstTask);

        void run();

    protected:
        QTKEARunnable *m_pFirstTask;

    private:

        QTKEAPooledExecutor *m_pPooledExecutor;
    };

    struct RunWhenBlocked : public BlockedExecutionHandler
    {
        bool blockedAction(QTKEARunnable *pCommand);
    };

    struct WaitWhenBlocked : public BlockedExecutionHandler
    {
        WaitWhenBlocked(QTKEAPooledExecutor *pPooledExecutor);

        bool blockedAction(QTKEARunnable *pCommand);

    private:
        QTKEAPooledExecutor *m_pPooledExecutor;
    };

    struct DiscardWhenBlocked : public BlockedExecutionHandler
    {
        bool blockedAction(QTKEARunnable *pCommand);
    };

    struct AbortWhenBlocked : public BlockedExecutionHandler
    {
        bool blockedAction(QTKEARunnable *pCommand);
    };

    struct DiscardOldestWhenBlocked : public BlockedExecutionHandler
    {
        DiscardOldestWhenBlocked(QTKEAPooledExecutor *pPooledExecutor);

        bool blockedAction(QTKEARunnable *pCommand);

    private:
        QTKEAPooledExecutor *m_pPooledExecutor;
    };

    void addThread(QTKEARunnable *pCommand);
    void workerDone(Worker *pWorker);
    QTKEARunnable *getTask();

    WaitWhenBlocked m_waitWhenBlocked;
    DiscardWhenBlocked m_discardWhenBlocked;
    AbortWhenBlocked m_abortWhenBlocked;
    RunWhenBlocked m_runWhenBlocked;
    DiscardOldestWhenBlocked m_discardOldestWhenBlocked;

protected:
    mutable QMutex m_shutdownMutex;
    mutable QWaitCondition m_waitCond;

    int m_iMaximumPoolSize;
    int m_iMinimumPoolSize;
    int m_iPoolSize;
    long m_lKeepAliveTime;
    bool m_bShutdown;
    QTKEAChannel *m_pHandOff;
    QHash<Worker *, QTKEAInterruptibleThread *> m_mapThreads;
    QList<QTKEAInterruptibleThread *> m_listStoppedThreads;
    BlockedExecutionHandler *m_pBlockedExecutionHandler;
};

#endif // QTKEAPOOLEDEXECUTOR_P_H
