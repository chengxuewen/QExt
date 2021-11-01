#ifndef QTKEACYCLICBARRIER_P_H
#define QTKEACYCLICBARRIER_P_H

#include <QMutex>
#include <QWaitCondition>

class QTKEARunnable;

class QTKEACyclicBarrier
{
public:
    QTKEACyclicBarrier(int iParties, QTKEARunnable *pCommand = nullptr);

    QTKEARunnable *setBarrierCommand(QTKEARunnable *pCommand);

    bool broken() const;

    void restart();

    int parties() const;

    int barrier();

    int attemptBarrier(long lMsecs);

protected:
    int doBarrier(bool bTimed, long lMsecs);

protected:
    const int m_iParties;
    bool m_bBroken;
    QTKEARunnable *m_pBarrierCommand;
    int m_iCount; // number of parties still waiting
    int m_iResets; // incremented on each release
    mutable QMutex m_mutex;
    mutable QMutex m_monitor;
    QWaitCondition m_waitCond;
};

#endif // QTKEACYCLICBARRIER_P_H
