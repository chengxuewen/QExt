#ifndef QEXTTCPTASKTHREAD_H
#define QEXTTCPTASKTHREAD_H

#include <qexttcpglobal.h>
#include <qexttcpabstractthread.h>
#include <qexttcpabstracttask.h>



class QEXTTcpAbstractTaskPool;
class QEXTTcpAbstractTask;
class QEXTTcpTaskThreadPool;
class QEXTTcpTaskThreadPrivate;
class QEXT_TCP_API QEXTTcpTaskThread : public QEXTTcpAbstractThread
{
    Q_OBJECT
public:
    explicit QEXTTcpTaskThread(QEXTTcpTaskThreadPool *threadPool);
    ~QEXTTcpTaskThread();

    void quit() QEXT_DECL_OVERRIDE;
    QEXTTcpAbstractThreadPool *tcpThreadPool() const QEXT_DECL_OVERRIDE;

Q_SIGNALS:
    void taskErrorString(const QString &error);

public Q_SLOTS:
    void fetchTask();

private:
    QEXT_DECL_PRIVATE(QEXTTcpTaskThread)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpTaskThread)
};



#endif // QEXTTCPTASKTHREAD_H
