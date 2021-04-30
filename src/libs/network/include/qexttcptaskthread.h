#ifndef QEXTTCPTASKTHREAD_H
#define QEXTTCPTASKTHREAD_H

#include <qextnetworkglobal.h>
#include <qexttcpthreadbase.h>
#include <qexttcptaskbase.h>

class QEXTTcpTaskPoolBase;
class QEXTTcpTaskBase;
class QEXTTcpTaskThreadPool;
class QEXTTcpTaskThreadPrivate;
class QEXT_NETWORK_API QEXTTcpTaskThread : public QEXTTcpThreadBase
{
    Q_OBJECT
public:
    explicit QEXTTcpTaskThread(QEXTTcpTaskThreadPool *threadPool);
    ~QEXTTcpTaskThread();

    void quit() QEXT_OVERRIDE;
    QEXTTcpThreadPoolBase *tcpThreadPool() const QEXT_OVERRIDE;

Q_SIGNALS:
    void taskErrorString(const QString &error);

public Q_SLOTS:
    void fetchTask();

private:
    QEXT_DECLARE_PRIVATE(QEXTTcpTaskThread)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpTaskThread)
};

#endif // QEXTTCPTASKTHREAD_H
