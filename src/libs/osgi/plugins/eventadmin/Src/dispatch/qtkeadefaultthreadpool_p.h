#ifndef QTKEADEFAULTTHREADPOOL_P_H
#define QTKEADEFAULTTHREADPOOL_P_H

#include "qtkeapooledexecutor_p.h"

class QTKEADefaultThreadPool : public QTKEAPooledExecutor
{
public:
    QTKEADefaultThreadPool(int iPoolSize, bool bSyncThreads);

    void configure(int iPoolSize);
    void close();
    void executeTask(QTKEARunnable *pTask);
};

#endif // QTKEADEFAULTTHREADPOOL_P_H
