#ifndef QEXTTCPTASKTHREAD_P_H
#define QEXTTCPTASKTHREAD_P_H

#include <qextnetworkglobal.h>
#include <qexttcpthreadbase_p.h>

#include <QPointer>
#include <QMutex>
#include <QWaitCondition>

class QEXTTcpTaskPoolBase;
class QEXTTcpTaskThreadPool;
class QEXTTcpTaskThread;
class QEXT_NETWORK_API QEXTTcpTaskThreadPrivate : public QEXTTcpThreadBasePrivate
{
public:
    explicit QEXTTcpTaskThreadPrivate(QEXTTcpTaskThread *qq);
    ~QEXTTcpTaskThreadPrivate();

private:
    QEXT_DECLARE_PUBLIC(QEXTTcpTaskThread)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpTaskThreadPrivate)
};

#endif // QEXTTCPTASKTHREAD_P_H
