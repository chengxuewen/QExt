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
    QExtConcurrent(const T &value) : mValue(value) {}
    QExtConcurrent(const Self &other) : mValue(other.get()) {}
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
        return v1.compare(v2);
    }
    friend inline bool operator!=(const QExtConcurrent &v1, const QExtConcurrent &v2) QEXT_NOEXCEPT
    {
        return !v1.compare(v2);
    }

    T *data() QEXT_NOEXCEPT
    {
        return &mValue;
    }
    const T *data() const QEXT_NOEXCEPT
    {
        return &mValue;
    }
    T &value() QEXT_NOEXCEPT
    {
        return mValue;
    }
    const T &value() const QEXT_NOEXCEPT
    {
        return mValue;
    }
    T *operator->() QEXT_NOEXCEPT
    {
        return &mValue;
    }
    const T *operator->() const QEXT_NOEXCEPT
    {
        return &mValue;
    }

    T get() const
    {
        QExtSpinLock::Locker locker(mSpinlock);
        return mValue;
    }
    void set(const T &value)
    {
        QExtSpinLock::Locker locker(mSpinlock);
        mValue = value;
    }
    bool reset(const T &value)
    {
        QExtSpinLock::Locker locker(mSpinlock);
        if (value != mValue)
        {
            mValue = value;
            return true;
        }
        return false;
    }
    bool compare(const T &data) const
    {
        QExtSpinLock::Locker locker(mSpinlock);
        return this->mValue == data;
    }
    bool compare(const Self &other) const
    {
        QExtSpinLock::Locker locker(mSpinlock);
        return this != &other && this->mValue == other.mValue;
    }
    T exchange(const T &value)
    {
        QExtSpinLock::Locker locker(mSpinlock);
        T &oldVal = mValue;
        mValue = value;
        return oldVal;
    }
    bool compareExchange(T *expected, const T &desired)
    {
        QExtSpinLock::Locker locker(mSpinlock);
        if (*expected == desired)
        {
            *expected = mValue;
            mValue = desired;
            return true;
        }
        return false;
    }
    bool testSet(const T &expected, const T &desired)
    {
        QExtSpinLock::Locker locker(mSpinlock);
        if (expected == desired)
        {
            mValue = desired;
            return true;
        }
        return false;
    }
    T fetchSet(SetCallbackFunc func)
    {
        QExtSpinLock::Locker locker(mSpinlock);
        T &oldVal = mValue;
        if (func)
        {
            mValue = func(mValue);
        }
        return oldVal;
    }
    T fetchSet(SetWithUserDataCallbackFunc func, void *userData)
    {
        QExtSpinLock::Locker locker(mSpinlock);
        T &oldVal = mValue;
        if (func)
        {
            mValue = func(mValue, userData);
        }
        return oldVal;
    }

protected:
    T mValue;
    mutable QExtSpinLock mSpinlock;
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

    T fetchAdd(T val) { return this->fetchSet(addValue, &val); }
    T fetchSub(T val) { return this->fetchSet(subValue, &val); }

    Type operator++() QEXT_NOTHROW { return this->fetchAdd(1) + 1; }
    Type operator--() QEXT_NOTHROW { return this->fetchSub(1) - 1; }
    Type operator+=(T val) QEXT_NOTHROW { return this->fetchAdd(val) + val; }
    Type operator-=(T val) QEXT_NOTHROW { return this->fetchSub(val) - val; }

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

    T fetchOr(const T &val) { return this->fetchSet(orValue, &val); }
    T fetchXor(const T &val) { return this->fetchSet(xorValue, &val); }
    T fetchAnd(const T &val) { return this->fetchSet(andValue, &val); }

    Type operator|=(const T &val) QEXT_NOTHROW { return this->fetchOr(val) | val; }
    Type operator^=(const T &val) QEXT_NOTHROW { return this->fetchXor(val) ^ val; }
    Type operator&=(const T &val) QEXT_NOTHROW { return this->fetchAnd(val) & val; }

private:
    static T orValue(const T &value, void *userData) { return value | *reinterpret_cast<T *>(userData); }
    static T xorValue(const T &value, void *userData) { return value ^ *reinterpret_cast<T *>(userData); }
    static T andValue(const T &value, void *userData) { return value & *reinterpret_cast<T *>(userData); }
};
typedef QExtConcurrentIntegral<unsigned char> QExtConcurrentUChar;
typedef QExtConcurrentIntegral<unsigned short> QExtConcurrentUShort;
typedef QExtConcurrentIntegral<unsigned int> QExtConcurrentUInt;
typedef QExtConcurrentIntegral<unsigned long> QExtConcurrentULong;
typedef QExtConcurrentIntegral<char> QExtConcurrentChar;
typedef QExtConcurrentIntegral<short> QExtConcurrentShort;
typedef QExtConcurrentIntegral<int> QExtConcurrentInt;
typedef QExtConcurrentIntegral<long> QExtConcurrentLong;
typedef QExtConcurrentIntegral<bool> QExtConcurrentBool;
typedef QExtConcurrentIntegral<qint64> QExtConcurrentInt64;
typedef QExtConcurrentIntegral<quint64> QExtConcurrentUInt64;

#endif // _QEXTCONCURRENT_H
