#ifndef _QEXTSPINLOCK_H
#define _QEXTSPINLOCK_H

#include <qextGlobal.h>
#include <qextDateTimeUtils.h>

#include <QDebug>
#include <QAtomicInt>

#define QEXT_SPINLOCK_DLOCK(lock, timeout) \
    do { \
        const auto elapsed = (lock).lockElapsed(); \
        if (elapsed > (timeout)) { \
            qDebug() << QString("%1:%2 unlock timeout %3us").arg(QEXT_STRFUNC).arg(__LINE__).arg(elapsed); \
        } \
    } while(0)
#define QEXT_SPINLOCK_DUNLOCK(lock, timeout) \
    do { \
        const auto elapsed = (lock).unlockElapsed(); \
        if (elapsed > (timeout)) { \
            qDebug() << QString("%1:%2 unlock timeout %3us").arg(QEXT_STRFUNC).arg(__LINE__).arg(elapsed); \
        } \
    } while(0)
#define QEXT_SPINLOCK_DLOCKER(lock, timeout) \
    QExtDSpinLock::DLocker locker(lock, timeout, QEXT_STRFUNC, __LINE__)

#define QEXT_SPINLOCK_LOCK(x) do { (x).lock(); } while(0)
#define QEXT_SPINLOCK_UNLOCK(x) do { (x).unlock(); } while(0)
#define QEXT_SPINLOCK_LOCKER(x) QExtSpinLock::Locker locker(x)

class QExtSpinLock
{
public:
    struct Locker
    {
        QEXT_DECLARE_DISABLE_COPY_MOVE(Locker)
        Locker(QExtSpinLock &lock) : spinLock(lock) { spinLock.lock(); }
        virtual ~Locker() { spinLock.unlock(); }
        virtual void unlock() { spinLock.unlock(); }
        virtual void relock() { spinLock.lock(); }
        QExtSpinLock &spinLock;
    };

    QExtSpinLock() : mFlag(false) {}
    virtual ~QExtSpinLock() {}

    QEXT_FORCE_INLINE void lock()
    {
        while (!mFlag.testAndSetOrdered(false, true)) { }
    }
    QEXT_FORCE_INLINE void unlock()
    {
        mFlag.fetchAndStoreOrdered(0);
    }

private:
    QAtomicInt mFlag;
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtSpinLock)
};

class QExtDSpinLock : public QExtSpinLock
{
public:
    struct DLocker
    {
        QEXT_DECLARE_DISABLE_COPY_MOVE(DLocker)
        DLocker(QExtDSpinLock &lock, qint64 timeout, const char *func, qint64 line)
            : spinLock(lock), mTimeout(timeout), mFunc(func), mElapsed(0), mLine(line)
        {
            mElapsed = spinLock.lockElapsed();
            if (mTimeout > 0 && mElapsed > mTimeout)
            {
                qDebug() << QString("%1:%2 lock timeout %3us").arg(mFunc).arg(mLine).arg(mElapsed);
            }
        }
        virtual ~DLocker()
        {
            mElapsed = spinLock.unlockElapsed();
            if (mTimeout > 0 && mElapsed > mTimeout)
            {
                qDebug() << QString("%1:%2 lock&unlock timeout %3us").arg(mFunc).arg(mLine).arg(mElapsed);
            }
        }
        void unlock()
        {
            mElapsed = spinLock.unlockElapsed();
            if (mTimeout > 0 && mElapsed > mTimeout)
            {
                qDebug() << QString("%1:%2 lock&unlock timeout %3us").arg(mFunc).arg(mLine).arg(mElapsed);
            }
        }
        void relock()
        {
            mElapsed = spinLock.lockElapsed();
            if (mTimeout > 0 && mElapsed > mTimeout)
            {
                qDebug() << QString("%1:%2 relock timeout %3us").arg(mFunc).arg(mLine).arg(mElapsed);
            }
        }
        qint64 elapsed() const { return mElapsed; }
        QExtDSpinLock &spinLock;
    private:
        const qint64 mTimeout;
        const char *mFunc;
        qint64 mElapsed;
        qint64 mLine;
    };

    QExtDSpinLock() : mTimestamp(0) {}
    ~QExtDSpinLock() QEXT_OVERRIDE {}

    QEXT_FORCE_INLINE qint64 lockElapsed()
    {
        const qint64 ts = QExtDateTimeUtils::usecsTimeSinceEpoch();
        QExtSpinLock::lock();
        mTimestamp = QExtDateTimeUtils::usecsTimeSinceEpoch();
        return mTimestamp - ts;
    }

    QEXT_FORCE_INLINE qint64 unlockElapsed()
    {
        const qint64 elapsed = QExtDateTimeUtils::usecsTimeSinceEpoch() - mTimestamp;
        QExtSpinLock::unlock();
        return elapsed;
    }

private:
    qint64 mTimestamp;
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtDSpinLock)
};

#endif // _QEXTSPINLOCK_H
