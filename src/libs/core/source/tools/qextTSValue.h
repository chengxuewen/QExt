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
template <typename T, typename D>
static void qextTSValueStore(T &value, const D &data)
{
    value = data;
}
template <typename T>
static void qextTSValueStore(T &value, const T &data)
{
    value = data;
}
#if QEXT_CC_STD_11
template <typename D>
static void qextTSValueStore(std::atomic<D> &value, const D &data)
{
    value.store(data);
}
#endif
template <typename D>
static void qextTSValueStore(QAtomicInt &value, const D &data)
{
    value.storeRelease(data);
}
template <typename D>
static void qextTSValueStore(QExtConcurrent<D> &value, const D &data)
{
    value.set(data);
}
template <typename D>
static void qextTSValueStore(QAtomicPointer<QExtRemovePointer<D> > &value, const D &data)
{
    value.storeRelease(data);
}
template <typename D>
static void qextTSValueStore(QPair<D, qint64> &value, const D &data)
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

    QExtTSValue() : m_timeout(0) {}
    QExtTSValue(const Self &other) : m_value(other.m_value), m_timeout(other.m_timeout) {}
    QExtTSValue(const T &val, TS timeout = 0) : m_value(Value(val, 0)), m_timeout(timeout) {}
    template <typename Data>
    QExtTSValue(const Data &data, TS timeout = 0) : m_timeout(timeout) { detail::qextTSValueStore(m_value, data); }
    virtual ~QExtTSValue() {}

    T operator=(const T &value) QEXT_NOEXCEPT
    {
        this->set(detail::qextTSValueLoad(value));
        return detail::qextTSValueLoad(value);
    }
    template <typename Data>
    Data operator=(const Data &data) QEXT_NOEXCEPT
    {
        detail::qextTSValueStore(m_value.first, detail::qextTSValueLoad(data));
        return detail::qextTSValueLoad(data);
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

    T *operator->() QEXT_NOEXCEPT
    {
        return &m_value.first;
    }
    const T *operator->() const QEXT_NOEXCEPT
    {
        return &m_value.first;
    }

    TS timeoutTime() const { return m_timeout; }
    void setTimeoutTime(TS time) { m_timeout = time; }

    T get() const { return detail::qextTSValueLoad(m_value); }
    void set(T val) { detail::qextTSValueStore(m_value, val); }
    template <typename Data>
    void set(const Data &val) { detail::qextTSValueStore(m_value, val); }
    void reset(const T &val, TS now) const { detail::qextTSValueStore(m_value, val); m_value.second = now; }
    template <typename Data>
    void reset(const Data &val, TS now) const { detail::qextTSValueStore(m_value, val); m_value.second = now; }

    template <typename D>
    bool isValueEqual(const D &data)
    {
        return detail::qextTSValueLoad(m_value) == detail::qextTSValueLoad(data);
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
            return detail::qextTSValueLoad(m_value) != newVal;
        }
        return false;
    }

    static bool checkOutdated(TS past, TS now, TS timeout = 0)
    {
        return now <= 0 || timeout <= 0 || now - past >= timeout;
    }

private:
    TS m_timeout;
    mutable Value m_value;
};

#endif // _QEXTTSVALUE_H
