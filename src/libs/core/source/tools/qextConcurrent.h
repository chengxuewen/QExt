#ifndef _QEXTCONCURRENT_H
#define _QEXTCONCURRENT_H

#include <qextSpinlock.h>
#include <qextTypeTrait.h>

template <typename T>
class QExtConcurrent
{
public:
    typedef T Type;
    typedef QExtConcurrent<T> Self;
    typedef T(*SetCallbackFunc)(const T &);
    typedef T(*SetWithUserDataCallbackFunc)(const T &, void *userData);

    QExtConcurrent() {}
    QExtConcurrent(const T &value) : m_value(value) {}
    QExtConcurrent(const Self &other) : m_value(other.get()) {}
    virtual ~QExtConcurrent() {}

    QExtConcurrent &operator=(const QExtConcurrent &other)
    {
        if (this != &other)
        {
            this->set(other.get());
        }
        return *this;
    }

    friend inline bool operator==(const QExtConcurrent &v1, const QExtConcurrent &v2) QEXT_NOEXCEPT
    {
        return v1.get() == v2.get();
    }
    friend inline bool operator!=(const QExtConcurrent &v1, const QExtConcurrent &v2) QEXT_NOEXCEPT
    {
        return !(v1.get() == v2.get());
    }

    T *operator->() QEXT_NOEXCEPT
    {
        return &m_value;
    }
    const T *operator->() const QEXT_NOEXCEPT
    {
        return &m_value;
    }
    T get() const
    {
        QExtSpinLock::Locker locker(m_spinlock);
        return m_value;
    }
    void set(const T &value)
    {
        QExtSpinLock::Locker locker(m_spinlock);
        m_value = value;
    }
    T exchange(const T &value)
    {
        QExtSpinLock::Locker locker(m_spinlock);
        T &oldVal = m_value;
        m_value = value;
        return oldVal;
    }
    bool compare_exchange(T *expected, const T &desired)
    {
        QExtSpinLock::Locker locker(m_spinlock);
        if (*expected == desired)
        {
            *expected = m_value;
            m_value = desired;
            return true;
        }
        return false;
    }
    bool test_set(const T &expected, const T &desired)
    {
        QExtSpinLock::Locker locker(m_spinlock);
        if (expected == desired)
        {
            m_value = desired;
            return true;
        }
        return false;
    }
    T fetch_set(SetCallbackFunc func)
    {
        QExtSpinLock::Locker locker(m_spinlock);
        T &oldVal = m_value;
        if (func)
        {
            m_value = func(m_value);
        }
        return oldVal;
    }
    T fetch_set(SetWithUserDataCallbackFunc func, void *userData)
    {
        QExtSpinLock::Locker locker(m_spinlock);
        T &oldVal = m_value;
        if (func)
        {
            m_value = func(m_value, userData);
        }
        return oldVal;
    }

protected:
    T m_value;
    mutable QExtSpinLock m_spinlock;
};

template <typename T>
class QExtConcurrentArithmetic : public QExtConcurrent<T>
{
public:
    typedef T Type;
    typedef QExtConcurrent<T> Base;
    typedef QExtConcurrentArithmetic Self;
    QEXT_STATIC_ASSERT_X(QExtIsArithmetic<T>::value, "QExtConcurrentArithmetic requires an arithmetic type");

    QExtConcurrentArithmetic(const T &value) : Base(value) {}
    QExtConcurrentArithmetic(const Self &other) : Base(other.get()) {}

    T fetch_add(T val) { return this->fetch_set(addValue, &val); }
    T fetch_sub(T val) { return this->fetch_set(subValue, &val); }

    Type operator++() QEXT_NOTHROW { return this->fetch_add(1) + 1; }
    Type operator--() QEXT_NOTHROW { return this->fetch_sub(1) - 1; }
    Type operator+=(T val) QEXT_NOTHROW { return this->fetch_add(val) + val; }
    Type operator-=(T val) QEXT_NOTHROW { return this->fetch_sub(val) - val; }

private:
    static T addValue(const T &value, void *userData) { return value + *reinterpret_cast<T *>(userData); }
    static T subValue(const T &value, void *userData) { return value - *reinterpret_cast<T *>(userData); }
};
typedef QExtConcurrentArithmetic<double> QExtConcurrentDouble;
typedef QExtConcurrentArithmetic<float> QExtConcurrentFloat;

template <typename T>
class QExtConcurrentIntegral : public QExtConcurrentArithmetic<T>
{
public:
    typedef T Type;
    typedef QExtConcurrentArithmetic<T> Base;
    typedef QExtConcurrentIntegral Self;
    QEXT_STATIC_ASSERT_X(QExtIsIntegral<T>::value, "QExtConcurrentIntegral requires an integral type");

    QExtConcurrentIntegral(const T &value) : Base(value) {}
    QExtConcurrentIntegral(const Self &other) : Base(other.get()) {}

    T fetch_or(const T &val) { return this->fetch_set(orValue, &val); }
    T fetch_xor(const T &val) { return this->fetch_set(xorValue, &val); }
    T fetch_and(const T &val) { return this->fetch_set(andValue, &val); }

    Type operator|=(const T &val) QEXT_NOTHROW { return this->fetch_or(val) | val; }
    Type operator^=(const T &val) QEXT_NOTHROW { return this->fetch_xor(val) ^ val; }
    Type operator&=(const T &val) QEXT_NOTHROW { return this->fetch_and(val) & val; }

private:
    static T orValue(const T &value, void *userData) { return value | *reinterpret_cast<T *>(userData); }
    static T xorValue(const T &value, void *userData) { return value ^ *reinterpret_cast<T *>(userData); }
    static T andValue(const T &value, void *userData) { return value & *reinterpret_cast<T *>(userData); }
};
typedef QExtConcurrentArithmetic<unsigned char> QExtConcurrentUChar;
typedef QExtConcurrentArithmetic<unsigned short> QExtConcurrentUShort;
typedef QExtConcurrentArithmetic<unsigned int> QExtConcurrentUInt;
typedef QExtConcurrentArithmetic<unsigned long> QExtConcurrentULong;
typedef QExtConcurrentArithmetic<char> QExtConcurrentChar;
typedef QExtConcurrentArithmetic<short> QExtConcurrentShort;
typedef QExtConcurrentArithmetic<int> QExtConcurrentInt;
typedef QExtConcurrentArithmetic<long> QExtConcurrentLong;
typedef QExtConcurrentArithmetic<bool> QExtConcurrentBool;
typedef QExtConcurrentArithmetic<qint64> QExtConcurrentInt64;
typedef QExtConcurrentArithmetic<quint64> QExtConcurrentUInt64;

#endif // _QEXTCONCURRENT_H
