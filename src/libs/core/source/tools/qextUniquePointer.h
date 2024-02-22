#ifndef _QEXTUNIQUEPOINTER_H
#define _QEXTUNIQUEPOINTER_H

#include <qextGlobal.h>
#include <qextTypeTrait.h>

#include <stdlib.h>


template<typename T>
struct QExtUniquePointerDeleter
{
    inline void operator()(T *pointer)
    {
        // Enforce a complete type.
        typedef char IsIncompleteType[sizeof(T) ? 1 : -1];
        (void) sizeof(IsIncompleteType);

        delete pointer;
    }
};

template<typename T, typename Deleter = QExtUniquePointerDeleter<T> >
class QExtUniquePointer
{
public:
    typedef T *Pointer;

    explicit QExtUniquePointer(T *p = QEXT_NULLPTR) QEXT_NOEXCEPT : d(p), deleter(Deleter()) { }

    QExtUniquePointer(T *p, const Deleter &d) QEXT_NOEXCEPT : d(p), deleter(d) { }

    QExtUniquePointer(const QExtUniquePointer &other)
    {
        d = other.d;
        deleter = other.deleter;
        QExtUniquePointer &oth = const_cast<QExtUniquePointer &>(other);
        oth.d = QEXT_NULLPTR;
    }

    virtual ~QExtUniquePointer()
    {
        if (d)
        {
            T *oldD = d;
            d = QEXT_NULLPTR;
            deleter(oldD);
        }
    }

    QExtUniquePointer &operator=(const QExtUniquePointer &other)
    {
        if (this != &other)
        {
            if (d)
            {
                T *oldD = d;
                d = QEXT_NULLPTR;
                deleter(oldD);
            }
            d = other.d;
            deleter = other.deleter;
            QExtUniquePointer &oth = const_cast<QExtUniquePointer &>(other);
            oth.d = QEXT_NULLPTR;
        }
        return *this;
    }

    bool operator==(const QExtUniquePointer &other) const
    {
        return d == other.d;
    }

    bool operator!=(const QExtUniquePointer &other) const
    {
        return !(*this == other);
    }

    T &operator*() const
    {
        assert(d);
        return *d;
    }

    T *operator->() const QEXT_NOEXCEPT
    {
        return d;
    }

    bool operator!() const QEXT_NOEXCEPT
    {
        return !d;
    }

    operator bool() const
    {
        return !this->isNull();
    }

    T *data() const QEXT_NOEXCEPT
    {
        return d;
    }

    T *get() const QEXT_NOEXCEPT
    {
        return d;
    }

    bool isNull() const QEXT_NOEXCEPT
    {
        return !d;
    }

    void reset(T *other = QEXT_NULLPTR) QEXT_NOEXCEPT
    {
        if (d != other)
        {
            T *oldD = d;
            d = other;
            deleter(oldD);
        }
    }

    T *take() QEXT_NOEXCEPT
    {
        T *oldD = d;
        d = QEXT_NULLPTR;
        return oldD;
    }

    void swap(QExtUniquePointer &other) QEXT_NOEXCEPT
    {
        std::swap(d, other.d);
        std::swap(deleter, other.deleter);
    }

    friend void swap(QExtUniquePointer<T, Deleter> &p1, QExtUniquePointer<T, Deleter> &p2) QEXT_NOEXCEPT
    {
        p1.swap(p2);
    }

protected:
    T *d;
    Deleter deleter;
};

template<typename T>
struct QExtUniqueArrayPointerDeleter
{
    inline void operator()(T *pointer)
    {
        // Enforce a complete type.
        typedef char IsIncompleteType[sizeof(T) ? 1 : -1];
        (void) sizeof(IsIncompleteType);

        delete[] pointer;
    }
};

struct QExtUniquePodPointerDeleter
{
    static inline void cleanup(void *pointer)
    {
        if (pointer)
        {
            free(pointer);
        }
    }
};

namespace QExtPrivate
{
    template<typename X, typename Y>
    struct QExtUniqueArrayEnsureSameType;
    template<typename X>
    struct QExtUniqueArrayEnsureSameType<X, X>
    {
        typedef X *Type;
    };
    template<typename X>
    struct QExtUniqueArrayEnsureSameType<const X, X>
    {
        typedef X *Type;
    };
}

template<typename T, typename Deleter = QExtUniqueArrayPointerDeleter<T> >
class QExtUniqueArrayPointer : public QExtUniquePointer<T, Deleter>
{
public:
    inline QExtUniqueArrayPointer() : QExtUniquePointer<T, Deleter>(QEXT_NULLPTR) {}

    template<typename D>
    explicit inline QExtUniqueArrayPointer(D *p, typename QExtPrivate::QExtUniqueArrayEnsureSameType<T, D>::Type = 0)
            : QExtUniquePointer<T, Deleter>(p)
    {
    }

    template<typename D>
    inline
    QExtUniqueArrayPointer(D *p, const Deleter &d, typename QExtPrivate::QExtUniqueArrayEnsureSameType<T, D>::Type = 0)
            : QExtUniquePointer<T, Deleter>(p, d)
    {
    }

    QExtUniqueArrayPointer(const QExtUniqueArrayPointer &other)
            : QExtUniquePointer<T, Deleter>(other)
    {
    }

    QExtUniqueArrayPointer &operator=(const QExtUniqueArrayPointer &other)
    {
        if (this != &other)
        {
            QExtUniquePointer<T, Deleter>::operator=(other);
        }
        return *this;
    }

    bool operator==(const QExtUniqueArrayPointer &other) const
    {
        return QExtUniquePointer<T, Deleter>::operator==(other);
    }

    bool operator!=(const QExtUniqueArrayPointer &other) const
    {
        return QExtUniquePointer<T, Deleter>::operator!=(other);
    }

    inline T &operator[](int i)
    {
        return this->d[i];
    }

    inline const T &operator[](int i) const
    {
        return this->d[i];
    }

    // prevent QEXTScopedPointer <->QEXTScopedArrayPointer swaps
    void swap(QExtUniqueArrayPointer &other) QEXT_NOEXCEPT
    {
        QExtUniquePointer<T, Deleter>::swap(other);
    }

    friend void swap(QExtUniqueArrayPointer<T, Deleter> &p1, QExtUniqueArrayPointer<T, Deleter> &p2) QEXT_NOEXCEPT
    {
        p1.swap(p2);
    }

private:
    explicit inline QExtUniqueArrayPointer(void *)
    {
        // Enforce the same type.

        // If you get a compile error here, make sure you declare
        // QScopedArrayPointer with the same template type as you pass to the
        // constructor. See also the QScopedPointer documentation.

        // Storing a scalar array as a pointer to a different type is not
        // allowed and results in undefined behavior.
    }
};


#endif // _QEXTUNIQUEPOINTER_H
