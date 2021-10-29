#ifndef _QEXTGUINULLABLEVALUE_H
#define _QEXTGUINULLABLEVALUE_H

template<typename T>
struct QEXTGuiNullableValue
{
    QEXTGuiNullableValue()
        : isNull(true), value(T()) {}
    QEXTGuiNullableValue(const QEXTGuiNullableValue<T> &o)
        : isNull(o.isNull), value(o.value) {}
    QEXTGuiNullableValue(const T &t)
        : isNull(false), value(t) {}
    QEXTGuiNullableValue<T> &operator=(const T &t)
    {
        isNull = false;
        value = t;
        return *this;
    }
    QEXTGuiNullableValue<T> &operator=(const QEXTGuiNullableValue<T> &o)
    {
        isNull = o.isNull;
        value = o.value;
        return *this;
    }
    operator T() const
    {
        return value;
    }

    void invalidate()
    {
        isNull = true;
    }
    bool isValid() const
    {
        return !isNull;
    }


    bool isNull;
    T value;
};

#endif // _QEXTGUINULLABLEVALUE_H
