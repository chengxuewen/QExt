#ifndef _QEXTTSVALUE_H
#define _QEXTTSVALUE_H

#include <qextGlobal.h>
#include <qextTypeTrait.h>
#include <qextConcurrent.h>

#include <QPair>
#if QEXT_CC_STD_11
#   include <atomic>
#endif

namespace detail
{
/* load */
template <typename T>
static T qextTSValueLoad(const T &value)
{
    return value;
}
#if QEXT_CC_STD_11
template <typename T>
static T qextTSValueLoad(const std::atomic<T> &value)
{
    return value.load();
}
#endif
template <typename T>
static int qextTSValueLoad(const QAtomicInt &value)
{
    return value.loadAcquire();
}
template <typename T>
static T qextTSValueLoad(const QExtConcurrent<T> &value)
{
    return value.get();
}
template <typename T>
static T qextTSValueLoad(const QAtomicPointer<QExtRemovePointer<T> > &value)
{
    return value.loadAcquire();
}
template <typename T>
static T qextTSValueLoad(const QPair<T, qint64> &value)
{
    return qextTSValueLoad(value.first);
}
/* store */
template <typename T>
static void qextTSValueStore(T &value, const T &data)
{
    value = data;
}
#if QEXT_CC_STD_11
template <typename T>
static void qextTSValueStore(std::atomic<T> &value, const T &data)
{
    value.store(data);
}
#endif
template <typename T>
static void qextTSValueStore(QAtomicInt &value, const int &data)
{
    value.storeRelease(data);
}
template <typename T>
static void qextTSValueStore(QExtConcurrent<T> &value, const T &data)
{
    value.set(data);
}
template <typename T>
static void qextTSValueStore(QAtomicPointer<QExtRemovePointer<T> > &value, const T &data)
{
    value.storeRelease(data);
}
template <typename T>
static void qextTSValueStore(QPair<T, qint64> &value, const T &data)
{
    qextTSValueStore(value.first, data);
}
template <typename T, typename Data>
static void qextTSValueStore(QPair<T, qint64> &value, const Data &data)
{
    qextTSValueStore(value.first, data);
}
}

template <typename T>
class QExtTSValue
{
public:
    typedef qint64 TS;
    typedef QPair<T, TS> Value;
    typedef QExtTSValue<T> Self;

    QExtTSValue() {}
    QExtTSValue(const T &val) : m_value(Value(0, val)), m_timeout(0) {}
    QExtTSValue(const T &val, TS timeout = 0) : m_value(Value(0, val)), m_timeout(timeout) {}
    QExtTSValue(const Self &other) : m_value(other.m_value), m_timeout(other.m_timeout) {}
    virtual ~QExtTSValue() {}

    T operator=(const T &value) QEXT_NOEXCEPT
    {
        this->set(detail::qextTSValueLoad(value));
        return detail::qextTSValueLoad(value);
    }
    Self &operator=(const Self &other)
    {
        if (this != &other)
        {
            m_value = other.m_value;
            m_timeout = other.m_timeout;
        }
        return *this;
    }
    friend inline bool operator==(const Self &v1, const Self &v2) QEXT_NOEXCEPT
    {
        return v1.m_value == v2.m_value && v1.m_timeout == v2.m_timeout;
    }
    friend inline bool operator!=(const Self &v1, const Self &v2) QEXT_NOEXCEPT
    {
        return v1.m_value != v2.m_value;
    }

    TS timeoutTime() const { return m_timeout; }
    void setTimeoutTime(TS time) { m_timeout = time; }

    T get() const { return detail::qextTSValueLoad(m_value); }
    void set(T val) { detail::qextTSValueStore(m_value, val); }
    template <typename Data>
    void set(const Data &val) { detail::qextTSValueStore(m_value, val); }
    void reset(const T &val, TS now) const { detail::qextTSValueStore(m_value, val); m_value.second = now; }

    bool isValueEqual(const T &newVal)
    {
        return detail::qextTSValueLoad(m_value) == newVal;
    }
    bool isValueEqual(const Self &other)
    {
        return this != &other && detail::qextTSValueLoad(m_value) == detail::qextTSValueLoad(other.m_value);
    }
    bool isValueOutdated(TS now, TS timeout = -1)
    {
        return checkOutdated(m_value.second, now, timeout >= 0 ? timeout : m_timeout);
    }
    bool isValueChanged(const T &newVal, TS now, TS timeout = -1)
    {
        if (this->isValueOutdated(now, timeout))
        {
            return detail::qextTSValueLoad(m_value) ;
        }
        return detail::qextTSValueLoad(m_value) != newVal;
    }

    static bool checkOutdated(TS past, TS now, TS timeout = 0)
    {
        return now <= 0 || timeout <= 0 || now - past >= timeout;
    }

private:
    Value m_value;
    TS m_timeout;
};

#endif // _QEXTTSVALUE_H
