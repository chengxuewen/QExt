#ifndef QEXTTCPTASKTHREADPOOL_P_H
#define QEXTTCPTASKTHREADPOOL_P_H

#include <qexttcpglobal.h>
#include <qexttcpabstractthreadpool_p.h>

#include <QMutex>
#include <QVector>
#include <QQueue>
#include <QMap>
#include <QSet>



class QEXTTcpAbstractTaskPool;
class QEXTTcpAbstractTask;
class QEXTTcpTaskThread;
class QEXTTcpTaskThreadPool;
class QEXT_TCP_API QEXTTcpTaskThreadPoolPrivate : public QEXTTcpAbstractThreadPoolPrivate
{
public:
    explicit QEXTTcpTaskThreadPoolPrivate(QEXTTcpTaskThreadPool *qq);
    ~QEXTTcpTaskThreadPoolPrivate();

private:
    QEXT_DECL_PUBLIC(QEXTTcpTaskThreadPool)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpTaskThreadPoolPrivate)
};



#endif // QEXTTCPTASKTHREADPOOL_P_H
