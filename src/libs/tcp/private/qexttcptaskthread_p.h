#ifndef QEXTTCPTASKTHREAD_P_H
#define QEXTTCPTASKTHREAD_P_H

#include <qexttcpglobal.h>
#include <qexttcpabstractthread_p.h>

#include <QPointer>
#include <QMutex>
#include <QWaitCondition>



class QEXTTcpAbstractTaskPool;
class QEXTTcpTaskThreadPool;
class QEXTTcpTaskThread;
class QEXT_TCP_API QEXTTcpTaskThreadPrivate : public QEXTTcpAbstractThreadPrivate
{
public:
    explicit QEXTTcpTaskThreadPrivate(QEXTTcpTaskThread *qq);
    ~QEXTTcpTaskThreadPrivate();

private:
    QEXT_DECLARE_PUBLIC(QEXTTcpTaskThread)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpTaskThreadPrivate)
};



#endif // QEXTTCPTASKTHREAD_P_H
