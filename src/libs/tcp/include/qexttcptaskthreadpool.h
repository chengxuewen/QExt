#ifndef QEXTTCPTASKTHREADPOOL_H
#define QEXTTCPTASKTHREADPOOL_H

#include <qexttcpglobal.h>
#include <qexttcpabstractthreadpool.h>



class QEXTTcpAbstractTask;
class QEXTTcpAbstractTaskPool;
class QEXTTcpAbstractThread;
class QEXTTcpTaskThreadPoolPrivate;
class QEXT_TCP_API QEXTTcpTaskThreadPool : public QEXTTcpAbstractThreadPool
{
    Q_OBJECT
public:
    explicit QEXTTcpTaskThreadPool(QObject *parent = QEXT_NULLPTR);
    ~QEXTTcpTaskThreadPool();

    void setTcpThreadIdle(QEXTTcpAbstractThread *thread) QEXT_OVERRIDE;

    void removeThread() QEXT_OVERRIDE;
    void addThread() QEXT_OVERRIDE;

    void setTaskPool(QSharedPointer<QEXTTcpAbstractTaskPool> taskPool) QEXT_OVERRIDE;

public Q_SLOTS:
    void dispatchThreadHandleTask();

private:
    QEXT_DECLARE_PRIVATE(QEXTTcpTaskThreadPool)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpTaskThreadPool)
};



#endif // QEXTTCPTASKTHREADPOOL_H
