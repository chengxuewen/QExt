#include "qtkearendezvous_p.h"
#include "qtkeabrokenbarrierexception_p.h"
#include "qtkeatimeoutexception_p.h"

QTKEARendezvous::QTKEARendezvous()
    : QTKEACyclicBarrier(2),
      m_timedout()
{
}

void QTKEARendezvous::waitForRendezvous()
{
    if (m_timedout.fetchAndAddOrdered(0)) {
        // if we have timed out, we return immediately
        return;
    }
    try {
        this->barrier();
    } catch (const QTKEABrokenBarrierException &) {
    }
}

void QTKEARendezvous::waitAttemptForRendezvous(long lTimeout)
{
    try {
        this->attemptBarrier(lTimeout);
        this->restart();
    } catch (const QTKEABrokenBarrierException &) {
    } catch (const QTKEATimeoutException &e) {
        m_timedout.testAndSetOrdered(0, 1);
        throw e;
    }
}
