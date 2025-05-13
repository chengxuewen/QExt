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
        QEXT_DISABLE_COPY_MOVE(Locker)
        Locker(QExtSpinLock &lock) : spinLock(lock) { spinLock.lock(); }
        virtual ~Locker() { spinLock.unlock(); }
        virtual void unlock() { spinLock.unlock(); }
        virtual void relock() { spinLock.lock(); }
        QExtSpinLock &spinLock;
    };

    QExtSpinLock() : m_flag(false) {}
    virtual ~QExtSpinLock() {}

    QEXT_FORCE_INLINE void lock()
    {
        while (!m_flag.testAndSetOrdered(false, true)) { }
    }
    QEXT_FORCE_INLINE void unlock()
    {
        m_flag.fetchAndStoreOrdered(0);
    }

private:
    QAtomicInt m_flag;
    QEXT_DISABLE_COPY_MOVE(QExtSpinLock)
};

class QExtDSpinLock : public QExtSpinLock
{
public:
    struct DLocker
    {
        QEXT_DISABLE_COPY_MOVE(DLocker)
        DLocker(QExtDSpinLock &lock, qint64 timeout, const char *func, qint64 line)
            : spinLock(lock), m_timeout(timeout), m_elapsed(0), m_func(func), m_line(line)
        {
            m_elapsed = spinLock.lockElapsed();
            if (m_timeout > 0 && m_elapsed > m_timeout)
            {
                qDebug() << QString("%1:%2 lock timeout %3us").arg(m_func).arg(m_line).arg(m_elapsed);
            }
        }
        virtual ~DLocker()
        {
            m_elapsed = spinLock.unlockElapsed();
            if (m_timeout > 0 && m_elapsed > m_timeout)
            {
                qDebug() << QString("%1:%2 lock&unlock timeout %3us").arg(m_func).arg(m_line).arg(m_elapsed);
            }
        }
        void unlock()
        {
            m_elapsed = spinLock.unlockElapsed();
            if (m_timeout > 0 && m_elapsed > m_timeout)
            {
                qDebug() << QString("%1:%2 lock&unlock timeout %3us").arg(m_func).arg(m_line).arg(m_elapsed);
            }
        }
        void relock()
        {
            m_elapsed = spinLock.lockElapsed();
            if (m_timeout > 0 && m_elapsed > m_timeout)
            {
                qDebug() << QString("%1:%2 relock timeout %3us").arg(m_func).arg(m_line).arg(m_elapsed);
            }
        }
        qint64 elapsed() const { return m_elapsed; }
        QExtDSpinLock &spinLock;
    private:
        const qint64 m_timeout;
        qint64 m_elapsed;
        const char *m_func;
        qint64 m_line;
    };

    QExtDSpinLock() : m_timestamp(0) {}
    ~QExtDSpinLock() QEXT_OVERRIDE {}

    QEXT_FORCE_INLINE qint64 lockElapsed()
    {
        const qint64 ts = QExtDateTimeUtils::usecsTimeSinceEpoch();
        QExtSpinLock::lock();
        m_timestamp = QExtDateTimeUtils::usecsTimeSinceEpoch();
        return m_timestamp - ts;
    }

    QEXT_FORCE_INLINE qint64 unlockElapsed()
    {
        const qint64 elapsed = QExtDateTimeUtils::usecsTimeSinceEpoch() - m_timestamp;
        QExtSpinLock::unlock();
        return elapsed;
    }

private:
    qint64 m_timestamp;
    QEXT_DISABLE_COPY_MOVE(QExtDSpinLock)
};

#endif // _QEXTSPINLOCK_H
