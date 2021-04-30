#ifndef QEXTTCPTASKTHREADPOOL_P_H
#define QEXTTCPTASKTHREADPOOL_P_H

#include <qextnetworkglobal.h>
#include <qexttcpthreadpoolbase_p.h>

#include <QMutex>
#include <QVector>
#include <QQueue>
#include <QMap>
#include <QSet>

class QEXTTcpTaskPoolBase;
class QEXTTcpTaskBase;
class QEXTTcpTaskThread;
class QEXTTcpTaskThreadPool;
class QEXT_NETWORK_API QEXTTcpTaskThreadPoolPrivate : public QEXTTcpThreadPoolBasePrivate
{
public:
    explicit QEXTTcpTaskThreadPoolPrivate(QEXTTcpTaskThreadPool *qq);
    ~QEXTTcpTaskThreadPoolPrivate();

private:
    QEXT_DECLARE_PUBLIC(QEXTTcpTaskThreadPool)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpTaskThreadPoolPrivate)
};

#endif // QEXTTCPTASKTHREADPOOL_P_H
