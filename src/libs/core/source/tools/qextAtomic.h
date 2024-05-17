#ifndef _QEXTATOMIC_H
#define _QEXTATOMIC_H

#include <qextGlobal.h>

#include <QAtomicPointer>

class QExtAtomicDouble
{
public:
    QExtAtomicDouble() : m_atomic(0) { }
    QExtAtomicDouble(const QExtAtomicDouble &other) : m_atomic(doubleToInt64Ptr(other.loadRelaxed())) {}
    QExtAtomicDouble(double value) : m_atomic(doubleToInt64Ptr(value)) {}
    virtual ~QExtAtomicDouble() {}

    operator double() const QEXT_NOEXCEPT { return this->loadAcquire(); }
    double operator=(double newValue) noexcept { this->storeRelease(newValue); return newValue; }
    QExtAtomicDouble &operator=(const QExtAtomicDouble &other)
    {
        if (this != &other)
        {
            this->storeRelease(other.loadAcquire());
        }
        return *this;
    }

    friend inline QEXT_CONSTEXPR bool operator==(const QExtAtomicDouble &a1, const QExtAtomicDouble &a2) noexcept
    {
        return a1.loadAcquire() == a2.loadAcquire();
    }
    friend inline QEXT_CONSTEXPR bool operator!=(const QExtAtomicDouble &a1, const QExtAtomicDouble &a2) noexcept
    {
        return a1.loadAcquire() != a2.loadAcquire();
    }

    double loadRelaxed() const { return doubleFromInt64Ptr(m_atomic.loadRelaxed()); }
    double loadAcquire() const { return doubleFromInt64Ptr(m_atomic.loadAcquire()); }

    void storeRelaxed(double value) { m_atomic.storeRelaxed(doubleToInt64Ptr(value)); }
    void storeRelease(double value) { m_atomic.storeRelease(doubleToInt64Ptr(value)); }

    double fetchAndStoreRelaxed(double value)
    {
        return doubleFromInt64Ptr(m_atomic.fetchAndStoreRelaxed(doubleToInt64Ptr(value)));
    }
    double fetchAndStoreAcquire(double value)
    {
        return doubleFromInt64Ptr(m_atomic.fetchAndStoreAcquire(doubleToInt64Ptr(value)));
    }
    double fetchAndStoreRelease(double value)
    {
        return doubleFromInt64Ptr(m_atomic.fetchAndStoreRelease(doubleToInt64Ptr(value)));
    }
    double fetchAndStoreOrdered(double value)
    {
        return doubleFromInt64Ptr(m_atomic.fetchAndStoreOrdered(doubleToInt64Ptr(value)));
    }

    bool testAndSetRelaxed(double expectedValue, double newValue)
    {
        return m_atomic.testAndSetRelaxed(doubleToInt64Ptr(expectedValue), doubleToInt64Ptr(newValue));
    }
    bool testAndSetAcquire(double expectedValue, double newValue)
    {
        return m_atomic.testAndSetAcquire(doubleToInt64Ptr(expectedValue), doubleToInt64Ptr(newValue));
    }
    bool testAndSetRelease(double expectedValue, double newValue)
    {
        return m_atomic.testAndSetRelease(doubleToInt64Ptr(expectedValue), doubleToInt64Ptr(newValue));
    }
    bool testAndSetOrdered(double expectedValue, double newValue)
    {
        return m_atomic.testAndSetOrdered(doubleToInt64Ptr(expectedValue), doubleToInt64Ptr(newValue));
    }

    bool testAndSetRelaxed(double expectedValue, double newValue, double &currentValue)
    {
        qint64 *intVal = 0;
        bool ret = m_atomic.testAndSetRelaxed(doubleToInt64Ptr(expectedValue), doubleToInt64Ptr(newValue), intVal);
        currentValue = doubleFromInt64Ptr(intVal);
        return ret;
    }
    bool testAndSetAcquire(double expectedValue, double newValue, double &currentValue)
    {
        qint64 *intVal = 0;
        bool ret = m_atomic.testAndSetAcquire(doubleToInt64Ptr(expectedValue), doubleToInt64Ptr(newValue), intVal);
        currentValue = doubleFromInt64Ptr(intVal);
        return ret;
    }
    bool testAndSetRelease(double expectedValue, double newValue, double &currentValue)
    {
        qint64 *intVal = 0;
        bool ret = m_atomic.testAndSetRelease(doubleToInt64Ptr(expectedValue), doubleToInt64Ptr(newValue), intVal);
        currentValue = doubleFromInt64Ptr(intVal);
        return ret;
    }
    bool testAndSetOrdered(double expectedValue, double newValue, double &currentValue)
    {
        qint64 *intVal = 0;
        bool ret = m_atomic.testAndSetOrdered(doubleToInt64Ptr(expectedValue), doubleToInt64Ptr(newValue), intVal);
        currentValue = doubleFromInt64Ptr(intVal);
        return ret;
    }

    static double doubleFromInt64Ptr(qint64 *intVal)
    {
        return doubleFromInt64(reinterpret_cast<qint64>(intVal));
    }
    static double doubleFromInt64(qint64 intVal)
    {
        double dblValue = 0;
        memcpy(&dblValue, &intVal, qMin(sizeof(dblValue), sizeof(intVal)));
        return dblValue;
    }

    static qint64 *doubleToInt64Ptr(double dblValue)
    {
        return reinterpret_cast<qint64 *>(doubleToInt64(dblValue));
    }
    static qint64 doubleToInt64(double dblValue)
    {
        qint64 intVal = 0;
        memcpy(&intVal, &dblValue, qMin(sizeof(intVal), sizeof(dblValue)));
        return intVal;
    }

private:
    QAtomicPointer<qint64> m_atomic;
};

#endif // _QEXTATOMIC_H
