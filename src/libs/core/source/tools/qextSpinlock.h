#ifndef _QEXTSPINLOCK_H
#define _QEXTSPINLOCK_H

#include <qextGlobal.h>

#include <QAtomicInt>

class QExtSpinLock
{
public:
    struct Locker
    {
        QEXT_DISABLE_COPY_MOVE(Locker)
        Locker(QExtSpinLock &lock) : spinLock(lock) { spinLock.lock(); }
        ~Locker() { spinLock.unlock(); }
        void unlock() { spinLock.unlock(); }
        void relock() { spinLock.lock(); }
        QExtSpinLock &spinLock;
    };

    QExtSpinLock() : m_flag(false) {}
    virtual ~QExtSpinLock() {}

    void lock()
    {
        while (!m_flag.testAndSetOrdered(false, true)) { }
    }

    void unlock()
    {
        m_flag.fetchAndStoreOrdered(0);
    }

private:
    QAtomicInt m_flag;
    QEXT_DISABLE_COPY_MOVE(QExtSpinLock)
};


#endif // _QEXTSPINLOCK_H
