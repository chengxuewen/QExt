#ifndef QEXTTCPTASKTHREADPOOL_H
#define QEXTTCPTASKTHREADPOOL_H

#include <qextnetworkglobal.h>
#include <qexttcpthreadpoolbase.h>

class QEXTTcpTaskBase;
class QEXTTcpTaskPoolBase;
class QEXTTcpThreadBase;
class QEXTTcpTaskThreadPoolPrivate;
class QEXT_NETWORK_API QEXTTcpTaskThreadPool : public QEXTTcpThreadPoolBase
{
    Q_OBJECT
public:
    explicit QEXTTcpTaskThreadPool(QObject *parent = QEXT_NULLPTR);
    ~QEXTTcpTaskThreadPool();

    void setTcpThreadIdle(QEXTTcpThreadBase *thread) QEXT_OVERRIDE;

    void removeThread() QEXT_OVERRIDE;
    void addThread() QEXT_OVERRIDE;

    void setTaskPool(QSharedPointer<QEXTTcpTaskPoolBase> taskPool) QEXT_OVERRIDE;

public Q_SLOTS:
    void dispatchThreadHandleTask();

private:
    QEXT_DECLARE_PRIVATE(QEXTTcpTaskThreadPool)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpTaskThreadPool)
};

#endif // QEXTTCPTASKTHREADPOOL_H
