#ifndef QTKEASYNCMASTERTHREAD_P_H
#define QTKEASYNCMASTERTHREAD_P_H

#include "qtkeainterruptiblethread_p.h"

class QTKEASyncMasterThread : public QObject
{
    Q_OBJECT

public:
    QTKEASyncMasterThread();

    void syncRun(QRunnable *pCommand);

    void stop();

public Q_SLOTS:
    void runCommand();

private:
    QTKEAInterruptibleThread m_thread;
    QRunnable *m_pCommand;
    QMutex m_mutex;
    QWaitCondition m_waitCond;
};

#endif // QTKEASYNCMASTERTHREAD_P_H
