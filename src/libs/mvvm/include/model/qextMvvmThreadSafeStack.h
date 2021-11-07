#ifndef _QEXTMVVMTHREADSAFESTACK_H
#define _QEXTMVVMTHREADSAFESTACK_H

#include <qextMvvmGlobal.h>

#include <QMutexLocker>
#include <QWaitCondition>
#include <QAtomicInt>
#include <QStack>
#include <QMutex>

#include <stdexcept>
#include <thread>

//! @file threadsafestack.h
//! @brief Thread-safe stack borrowed from Anthony Williams, C++ Concurrency in Action, Second
//! edition.


struct empty_stack : public std::exception {
    const char* what() const noexcept { return "Empty stack"; }
};

//! @class QEXTMvvmThreadSafeStack
//! @brief Thread-safe stack borrowed from Anthony Williams, C++ Concurrency in Action, Second
//! edition.

template <typename T> class QEXTMvvmThreadSafeStack
{
private:
    QStack<T> data;
    mutable QMutex m;
    QWaitCondition data_condition;
    QAtomicInt in_waiting_state{1};

public:
    QEXTMvvmThreadSafeStack() {}
    ~QEXTMvvmThreadSafeStack() { stop(); }
    QEXTMvvmThreadSafeStack(const QEXTMvvmThreadSafeStack& other)
    {
        QMutexLocker lock(&m);
        data = other.data;
    }
    QEXTMvvmThreadSafeStack& operator=(const QEXTMvvmThreadSafeStack& other) = delete;

    void push(T new_value)
    {
        QMutexLocker lock(&m);
        data.push(new_value);
        data_condition.notify_one();
    }

    //! Updates top value in a stack.

    void update_top(T new_value)
    {
        QMutexLocker lock(&m);
        if (!data.empty())
            data.pop();
        data.push(new_value);
        data_condition.notify_one();
    }

    void wait_and_pop(T& value)
    {
        QMutexLocker lock(&m);
        data_condition.wait(lock, [this] { return !data.empty() || !in_waiting_state; });
        if (data.empty())
            throw empty_stack();
        value = data.top();
        data.pop();
    }

    std::shared_ptr<T> wait_and_pop()
    {
        QMutexLocker lock(&m);
//        data_condition.wait(&m, [this] { return !data.empty() || !in_waiting_state; });
        if (data.empty())
            throw empty_stack();
        std::shared_ptr<T> const res(std::make_shared<T>(data.top()));
        data.pop();
        return res;
    }

    bool try_pop(T& value)
    {
        QMutexLocker lock(&m);
        if (data.empty())
            return false;
        value = data.top();
        data.pop();
        return true;
    }

    std::shared_ptr<T> try_pop()
    {
        QMutexLocker lock(&m);
        if (data.empty())
            return std::shared_ptr<T>();
        std::shared_ptr<T> res(std::make_shared<T>(data.top()));
        data.pop();
        return res;
    }

    bool empty() const
    {
        QMutexLocker lock(m);
        return data.empty();
    }

    //! Terminates waiting in wait_and_pop methods.

    void stop()
    {
        QMutexLocker lock(&m);
        in_waiting_state = false;
        data_condition.notify_all();
    }
};


#endif // _QEXTMVVMTHREADSAFESTACK_H
