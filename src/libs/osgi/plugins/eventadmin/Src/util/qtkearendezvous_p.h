#ifndef QTKEARENDEZVOUS_P_H
#define QTKEARENDEZVOUS_P_H

#include "qtkeacyclicbarrier_p.h"

#include <QAtomicInt>

class QTKEARendezvous : public QTKEACyclicBarrier
{
public:
    QTKEARendezvous();

    void waitForRendezvous();

    void waitAttemptForRendezvous(long lTimeout);

private:
    mutable QAtomicInt m_timedout;
};

#endif // QTKEARENDEZVOUS_P_H
