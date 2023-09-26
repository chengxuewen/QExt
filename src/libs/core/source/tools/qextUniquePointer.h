// clang-format off
// clang-format off
#ifndef _QEXTUNIQUEPOINTER_H
#define _QEXTUNIQUEPOINTER_H

#include <qextGlobal.h>
#include <qextTypeTrait.h>

#include <stdlib.h>



template <typename T>
struct QEXTUniquePointerDeleter
{
    inline void operator()(T *pointer)
    {
        // Enforce a complete type.
        typedef char IsIncompleteType[ sizeof(T) ? 1 : -1 ];
        (void) sizeof(IsIncompleteType);

        delete pointer;
    }
};

template <typename T, typename Deleter = QEXTUniquePointerDeleter<T> >
class QEXTUniquePointer
{
public:
    typedef T *Pointer;

    explicit QEXTUniquePointer(T *p = QEXT_DECL_NULLPTR) QEXT_DECL_NOEXCEPT
        : d(p), deleter(Deleter())
    {
    }

    QEXTUniquePointer(T *p, const Deleter &d) QEXT_DECL_NOEXCEPT
        : d(p), deleter(d)
    {
    }

    QEXTUniquePointer(const QEXTUniquePointer &other)
    {
        d = other.d;
        deleter = other.deleter;
        QEXTUniquePointer &oth = const_cast<QEXTUniquePointer &>(other);
        oth.d = QEXT_DECL_NULLPTR;
    }

    virtual ~QEXTUniquePointer()
    {
        if (d)
        {
            T *oldD = d;
            d = QEXT_DECL_NULLPTR;
            deleter(oldD);
        }
    }

    QEXTUniquePointer &operator=(const QEXTUniquePointer &other)
    {
        if (this != &other)
        {
            if (d)
            {
                T *oldD = d;
                d = QEXT_DECL_NULLPTR;
                deleter(oldD);
            }
            d = other.d;
            deleter = other.deleter;
            QEXTUniquePointer &oth = const_cast<QEXTUniquePointer &>(other);
            oth.d = QEXT_DECL_NULLPTR;
        }
        return *this;
    }

    bool operator==(const QEXTUniquePointer &other) const
    {
        return d == other.d;
    }

    bool operator!=(const QEXTUniquePointer &other) const
    {
        return !(*this == other);
    }

    T &operator*() const
    {
        assert(d);
        return *d;
    }

    T *operator->() const QEXT_DECL_NOEXCEPT
    {
        return d;
    }

    bool operator!() const QEXT_DECL_NOEXCEPT
    {
        return !d;
    }

    operator bool() const
    {
        return !this->isNull();
    }

    T *data() const QEXT_DECL_NOEXCEPT
    {
        return d;
    }

    T *get() const QEXT_DECL_NOEXCEPT
    {
        return d;
    }

    bool isNull() const QEXT_DECL_NOEXCEPT
    {
        return !d;
    }

    void reset(T *other = QEXT_DECL_NULLPTR) QEXT_DECL_NOEXCEPT
    {
        if (d != other)
        {
            T *oldD = d;
            d = other;
            deleter(oldD);
        }
    }

    T *take() QEXT_DECL_NOEXCEPT
    {
        T *oldD = d;
        d = QEXT_DECL_NULLPTR;
        return oldD;
    }

    void swap(QEXTUniquePointer &other) QEXT_DECL_NOEXCEPT
    {
        std::swap(d, other.d);
        std::swap(deleter, other.deleter);
    }

    friend void swap(QEXTUniquePointer<T, Deleter> &p1, QEXTUniquePointer<T, Deleter> &p2) QEXT_DECL_NOEXCEPT
    {
        p1.swap(p2);
    }

protected:
    T *d;
    Deleter deleter;
};



template <typename T>
struct QEXTUniqueArrayPointerDeleter
{
    inline void operator()(T *pointer)
    {
        // Enforce a complete type.
        typedef char IsIncompleteType[ sizeof(T) ? 1 : -1 ];
        (void) sizeof(IsIncompleteType);

        delete[] pointer;
    }
};

struct QEXTUniquePodPointerDeleter
{
    static inline void cleanup(void *pointer)
    {
        if (pointer)
        {
            free(pointer);
        }
    }
};


namespace qextPrivate
{
template <typename X, typename Y> struct QEXTUniqueArrayEnsureSameType;
template <typename X> struct QEXTUniqueArrayEnsureSameType<X, X>
{
    typedef X *Type;
};
template <typename X> struct QEXTUniqueArrayEnsureSameType<const X, X>
{
    typedef X *Type;
};
}

template <typename T, typename Deleter = QEXTUniqueArrayPointerDeleter<T> >
class QEXTUniqueArrayPointer : public QEXTUniquePointer<T, Deleter>
{
public:
    inline QEXTUniqueArrayPointer() : QEXTUniquePointer<T, Deleter>(QEXT_DECL_NULLPTR) {}

    template <typename D>
    explicit inline QEXTUniqueArrayPointer(D *p, typename qextPrivate::QEXTUniqueArrayEnsureSameType<T, D>::Type = 0)
        : QEXTUniquePointer<T, Deleter>(p)
    {
    }

    template <typename D>
    inline QEXTUniqueArrayPointer(D *p, const Deleter &d, typename qextPrivate::QEXTUniqueArrayEnsureSameType<T, D>::Type = 0)
        : QEXTUniquePointer<T, Deleter>(p, d)
    {
    }

    QEXTUniqueArrayPointer(const QEXTUniqueArrayPointer &other)
        : QEXTUniquePointer<T, Deleter>(other)
    {
    }

    QEXTUniqueArrayPointer &operator=(const QEXTUniqueArrayPointer &other)
    {
        if (this != &other)
        {
            QEXTUniquePointer<T, Deleter>::operator=(other);
        }
        return *this;
    }

    bool operator==(const QEXTUniqueArrayPointer &other) const
    {
        return QEXTUniquePointer<T, Deleter>::operator ==(other);
    }

    bool operator!=(const QEXTUniqueArrayPointer &other) const
    {
        return QEXTUniquePointer<T, Deleter>::operator !=(other);
    }

    inline T &operator[](int i)
    {
        return this->d[i];
    }

    inline const T &operator[](int i) const
    {
        return this->d[i];
    }

    void swap(QEXTUniqueArrayPointer &other) QEXT_DECL_NOEXCEPT // prevent QEXTScopedPointer <->QEXTScopedArrayPointer swaps
    {
        QEXTUniquePointer<T, Deleter>::swap(other);
    }

    friend void swap(QEXTUniqueArrayPointer<T, Deleter> &p1, QEXTUniqueArrayPointer<T, Deleter> &p2) QEXT_DECL_NOEXCEPT
    {
        p1.swap(p2);
    }

private:
    explicit inline QEXTUniqueArrayPointer(void *)
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

// clang-format on

// clang-format on
