#ifndef QEXTCALLBACK_H
#define QEXTCALLBACK_H

#include <qextglobal.h>
#include <qextargument.h>

#include <typeinfo>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>


class QEXT_CORE_API QEXTAbstractCallback
{
public:
    typedef void (QEXTAbstractCallback::*_MemFunc)();
    typedef void (*_Func)();

    QEXTAbstractCallback() : m_func(QEXT_NULLPTR), m_caller(QEXT_NULLPTR), m_size(0) {}
    QEXTAbstractCallback(const QEXTAbstractCallback &src) {
        m_size = src.m_size;
        m_func = src.m_func;
        m_caller = (void*)src.m_caller;
        if (src.m_caller) {
            memcpy(m_memFunc, src.m_memFunc, src.m_size);
        }
    }
    QEXTAbstractCallback(const void *caller, const void *func, size_t size) {
        m_size = size;
        if (caller) {
            m_caller = (void*)caller;
            memcpy(m_memFunc, func, size);
        } else {
            m_func = func;
        }
    }

    bool isNull() {
        return !m_func && !m_caller;
    }

    union {
        const void *m_func;
        char m_memFunc[sizeof(_MemFunc)];
    };

    size_t m_size;
    void *m_caller;
};



template <typename T_return>
class QEXT_CORE_API QEXTCallback0 : public QEXTAbstractCallback
{
public:
    QEXTCallback0(const void* caller, const void *func, size_t size)
        : QEXTAbstractCallback(caller, func, size) {}
    QEXTCallback0(const QEXTCallback0 &src)
        : QEXTAbstractCallback(src) {}
    QEXTCallback0() {}
};



template <typename T_return, typename T_arg1>
class QEXT_CORE_API QEXTCallback1 : public QEXTAbstractCallback
{
public:
    QEXTCallback1(const void* caller, const void *func, size_t size)
        : QEXTAbstractCallback(caller, func, size) {}
    QEXTCallback1(const QEXTCallback1 &src)
        : QEXTAbstractCallback(src) {}
    QEXTCallback1() {}
};



template <typename T_return, typename T_arg1, typename T_arg2>
class QEXT_CORE_API QEXTCallback2 : public QEXTAbstractCallback
{
public:
    QEXTCallback2(const void* caller, const void *func, size_t size)
        : QEXTAbstractCallback(caller, func, size) {}
    QEXTCallback2(const QEXTCallback2 &src)
        : QEXTAbstractCallback(src) {}
    QEXTCallback2() {}
};



template <typename T_return, typename T_arg1 = QEXTNil, typename T_arg2 = QEXTNil>
class QEXT_CORE_API QEXTCallback
        : public QEXTCallback2<T_return, T_arg1, T_arg2>
{
public:
    typedef T_return (*Callback)(const QEXTAbstractCallback &, T_arg1, T_arg2);

    QEXTCallback(Callback callback, const void* caller, const void *func, size_t size)
        : QEXTCallback2<T_return, T_arg1, T_arg2>(caller, func, size), m_callback(callback) {}
    QEXTCallback(const QEXTCallback &src)
        : QEXTCallback2<T_return, T_arg1, T_arg2>(src), m_callback(src.m_callback) {}
    QEXTCallback() {}

    T_return operator()(T_arg1 arg1, T_arg2 arg2) const {
        return m_callback(*this, arg1, arg2);
    }

    Callback m_callback;
};



template <typename T_return, typename T_arg1>
class QEXT_CORE_API QEXTCallback<T_return, T_arg1, QEXTNil>
        : public QEXTCallback1<T_return, T_arg1>
{
public:
    typedef T_return (*Callback)(const QEXTAbstractCallback &, T_arg1);

    QEXTCallback(Callback callback, const void* caller, const void *func, size_t size)
        : QEXTCallback1<T_return, T_arg1>(caller, func, size), m_callback(callback) {}
    QEXTCallback(const QEXTCallback &src)
        : QEXTCallback1<T_return, T_arg1>(src), m_callback(src.m_callback) {}
    QEXTCallback() {}

    T_return operator()(T_arg1 arg1) const {
        return m_callback(*this, arg1);
    }

    Callback m_callback;
};



template <typename T_return>
class QEXT_CORE_API QEXTCallback<T_return, QEXTNil, QEXTNil>
        : public QEXTCallback0<T_return>
{
public:
    typedef T_return (*Callback)(const QEXTAbstractCallback &);

    QEXTCallback(Callback callback, const void* caller, const void *func, size_t size)
        : QEXTCallback0<T_return>(caller, func, size), m_callback(callback) {}
    QEXTCallback(const QEXTCallback &src)
        : QEXTCallback0<T_return>(src), m_callback(src.m_callback) {}
    QEXTCallback() {}

    T_return operator()() const {
        return m_callback(*this);
    }

    Callback m_callback;
};



template <typename T_return, typename T_func, typename T_arg1 = QEXTNil, typename T_arg2 = QEXTNil>
class QEXTFunctionCallback
        : public QEXTCallback<T_return, T_arg1, T_arg2>
{
public:
    QEXTFunctionCallback(T_func func)
        : QEXTCallback<T_return, T_arg1, T_arg2>(callback, QEXT_NULLPTR, (const void*)func, 0) {}
    QEXTFunctionCallback(const QEXTFunctionCallback &src)
        : QEXTCallback<T_return, T_arg1, T_arg2>(src) {}
    QEXTFunctionCallback() {}

    static T_return callback(const QEXTAbstractCallback &functor, T_arg1 arg1, T_arg1 arg2) {
        return (T_func(functor.m_func))(arg1, arg2);
    }
};



template <typename T_return, typename T_func, typename T_arg1>
class QEXTFunctionCallback<T_return, T_func, T_arg1, QEXTNil>
        : public QEXTCallback<T_return, T_arg1>
{
public:
    QEXTFunctionCallback(T_func func)
        : QEXTCallback<T_return, T_arg1>(callback, QEXT_NULLPTR, (const void*)func, 0) {}
    QEXTFunctionCallback(const QEXTFunctionCallback &src)
        : QEXTCallback<T_return, T_arg1>(src) {}
    QEXTFunctionCallback() {}

    static T_return callback(const QEXTAbstractCallback &functor, T_arg1 arg1) {
        return (T_func(functor.m_func))(arg1);
    }
};



template <typename T_return, typename T_func>
class QEXTFunctionCallback<T_return, T_func, QEXTNil, QEXTNil>
        : public QEXTCallback<T_return>
{
public:
    QEXTFunctionCallback(T_func func)
        : QEXTCallback<T_return>(callback, QEXT_NULLPTR, (const void*)func, 0) {}
    QEXTFunctionCallback(const QEXTFunctionCallback &src)
        : QEXTCallback<T_return>(src) {}
    QEXTFunctionCallback() {}

    static T_return callback(const QEXTAbstractCallback &functor) {
        return (T_func(functor.m_func))();
    }
};



template <typename T_return, typename T_caller, typename T_func, typename T_arg1 = QEXTNil, typename T_arg2 = QEXTNil>
class QEXTMemberFunctionCallback
        : public QEXTCallback<T_return, T_arg1, T_arg2>
{
public:
    QEXTMemberFunctionCallback(T_caller &caller, const T_func &func)
        : QEXTCallback<T_return, T_arg1, T_arg2>(callback, &caller, &func, sizeof(func)) {}
    QEXTMemberFunctionCallback(const QEXTMemberFunctionCallback &src)
        : QEXTCallback<T_return, T_arg1, T_arg2>(src) {}
    QEXTMemberFunctionCallback() {}

    static T_return callback(const QEXTAbstractCallback &functor, T_arg1 arg1, T_arg1 arg2) {
        T_caller *caller = (T_caller*)functor.m_caller;
        T_func &func(*(T_func*)(void*)(functor.m_memFunc));
        return (caller->*func)(arg1, arg2);
    }
};


template <typename T_return, typename T_caller, typename T_func, typename T_arg1>
class QEXTMemberFunctionCallback<T_return, T_caller, T_func, T_arg1>
        : public QEXTCallback<T_return, T_arg1>
{
public:
    QEXTMemberFunctionCallback(T_caller &caller, const T_func &func)
        : QEXTCallback<T_return, T_arg1>(callback, &caller, &func, sizeof(func)) {}
    QEXTMemberFunctionCallback(const QEXTMemberFunctionCallback &src)
        : QEXTCallback<T_return, T_arg1>(src) {}
    QEXTMemberFunctionCallback() {}

    static T_return callback(const QEXTAbstractCallback &functor, T_arg1 arg1) {
        T_caller *caller = (T_caller*)functor.m_caller;
        T_func &func(*(T_func*)(void*)(functor.m_memFunc));
        return (caller->*func)(arg1);
    }
};



template <typename T_return, typename T_caller, typename T_func>
class QEXTMemberFunctionCallback<T_return, T_caller, T_func>
        : public QEXTCallback<T_return>
{
public:
    QEXTMemberFunctionCallback(T_caller &caller, const T_func &func)
        : QEXTCallback<T_return>(callback, &caller, &func, sizeof(func)) {}
    QEXTMemberFunctionCallback(const QEXTMemberFunctionCallback &src)
        : QEXTCallback<T_return>(src) {}
    QEXTMemberFunctionCallback() {}

    static T_return callback(const QEXTAbstractCallback &functor) {
        T_caller *caller = (T_caller*)functor.m_caller;
        T_func &func(*(T_func*)(void*)(functor.m_memFunc));
        return (caller->*func)();
    }
};



template <typename T_return, typename T_func, typename T_arg1, typename T_arg2>
inline QEXTFunctionCallback<T_return, T_func (*)(T_arg1, T_arg2), T_arg1, T_arg2>
qextGenerateCallback(QEXTCallback<T_return, T_arg1, T_arg2>*, T_func (*fct)(T_arg1, T_arg2))
{
    return QEXTFunctionCallback<T_return, T_func (*)(T_arg1, T_arg2), T_arg1, T_arg2>(fct);
}



template <typename T_return, typename T_func, typename T_arg1>
inline QEXTFunctionCallback<T_return, T_func (*)(T_arg1), T_arg1>
qextGenerateCallback(QEXTCallback<T_return, T_arg1>*, T_func (*fct)(T_arg1))
{
    return QEXTFunctionCallback<T_return, T_func (*)(T_arg1), T_arg1>(fct);
}



template <typename T_return, typename T_func>
inline QEXTFunctionCallback<T_return, T_func (*)()>
qextGenerateCallback(QEXTCallback<T_return>*, T_func (*fct)())
{
    return QEXTFunctionCallback<T_return, T_func (*)()>(fct);
}



template <typename T_return, typename T_caller, typename T_func, typename T_call, typename T_arg1, typename T_arg2>
inline QEXTMemberFunctionCallback<T_return, T_caller, T_func (T_call::*)(T_arg1, T_arg2), T_arg1, T_arg2>
qextGenerateCallback(QEXTCallback<T_return, T_arg1, T_arg2>*, T_caller &caller, T_func (T_call::*const& func)(T_arg1, T_arg2))
{
    typedef T_func (T_call::*MemFunc)(T_arg1, T_arg2);
    return QEXTMemberFunctionCallback<T_return, T_caller, MemFunc, T_arg1, T_arg2>(caller, func);
}



template <typename T_return, typename T_caller, typename T_func, typename T_call, typename T_arg1>
inline QEXTMemberFunctionCallback<T_return, T_caller, T_func (T_call::*)(T_arg1), T_arg1>
qextGenerateCallback(QEXTCallback<T_return, T_arg1>*, T_caller &caller, T_func (T_call::*const& func)(T_arg1))
{
    typedef T_func (T_call::*MemFunc)(T_arg1);
    return QEXTMemberFunctionCallback<T_return, T_caller, MemFunc, T_arg1>(caller, func);
}



template <typename T_return, typename T_caller, typename T_func, typename T_call>
inline QEXTMemberFunctionCallback<T_return, T_caller, T_func (T_call::*)()>
qextGenerateCallback(QEXTCallback<T_return>*, T_caller &caller, T_func (T_call::*const& func)())
{
    typedef T_func (T_call::*MemFunc)();
    return QEXTMemberFunctionCallback<T_return, T_caller, MemFunc>(caller, func);
}




#endif // QEXTCALLBACK_H
