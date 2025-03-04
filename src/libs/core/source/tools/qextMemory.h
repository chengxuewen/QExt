/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2025~present ChengXueWen.
**
** License: MIT License
**
** Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
** documentation files (the "Software"), to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
** and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all copies or substantial portions
** of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
** CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
** IN THE SOFTWARE.
**
***********************************************************************************************************************/

#ifndef _QEXTMEMORY_H
#define _QEXTMEMORY_H

#include <qextTypeTrait.h>

#include <QSharedPointer>
#include <QScopedPointer>

#if QEXT_CC_STD_11 && QEXT_CC_FEATURE_VARIADIC_TEMPLATES
#   include <memory>
#   define QExtWeakPointer std::weak_ptr
#   define QExtSharedPointer std::shared_ptr
namespace detail
{
// helper to construct a non-array unique_ptr
template <typename T>
struct QExtMakeSharedHelper
{
    typedef QExtSharedPointer<T> SharedPointer;

    template <typename... Args>
    static inline SharedPointer make(Args&&... args)
    {
        return SharedPointer(new T(std::forward<Args>(args)...));
    }
};
} // namespace detail
template <typename T, typename... Args>
inline typename detail::QExtMakeSharedHelper<T>::SharedPointer
qextMakeShared(Args&&... args)
{
    return detail::QExtMakeSharedHelper<T>::make(std::forward<Args>(args)...);
}
template <typename T, typename U>
inline QExtSharedPointer<T>
qextDynamicPointerCast(const QExtSharedPointer<U> &r)
{
    return std::dynamic_pointer_cast<T, U>(r);
}
template <typename T>
inline QExtSharedPointer<T>
qextMakeSharedRef(const QExtWeakPointer<T> &p)
{
    return p.lock();
}
template <typename T>
inline QExtWeakPointer<T>
qextMakeWeakRef(const QExtSharedPointer<T> &p)
{
    return QExtWeakPointer<T>(p);
}


#   define QExtUniquePointer std::unique_ptr
namespace detail
{
// helper to construct a non-array UniquePointer
template <typename T>
struct QExtUniquePointerHelper
{
    typedef QExtUniquePointer<T> UniquePointer;

    template <typename... Args>
    static inline UniquePointer make(Args&&... args)
    {
        return UniquePointer(new T(std::forward<Args>(args)...));
    }
};
// helper to construct an array UniquePointer
template<typename T>
struct QExtUniquePointerHelper<T[]>
{
    typedef QExtUniquePointer<T[]> UniquePointer;

    template <typename... Args>
    static inline UniquePointer make(Args&&... args) {
        return UniquePointer(new T[sizeof...(Args)]{std::forward<Args>(args)...});
    }
};
// helper to construct an array UniquePointer with specified extent
template<typename T, std::size_t N>
struct QExtUniquePointerHelper<T[N]>
{
    typedef QExtUniquePointer<T[]> UniquePointer;

    template <typename... Args>
    static inline UniquePointer make(Args&&... args)
    {
        static_assert(N >= sizeof...(Args),
                      "For make_unique<T[N]> N must be as largs as the number of arguments");
        return UniquePointer(new T[N]{std::forward<Args>(args)...});
    }
#   if __GNUC__ == 4 && __GNUC_MINOR__ <= 6
    // G++ 4.6 has an ICE when you have no arguments
    static inline UniquePointer make()
    {
        return UniquePointer(new T[N]);
    }
#   endif
};
} // namespace detail
template <typename T, typename... Args>
inline typename detail::QExtUniquePointerHelper<T>::UniquePointer
qextMakeUnique(Args&&... args)
{
    return detail::QExtUniquePointerHelper<T>::make(std::forward<Args>(args)...);
}
#else
#   define QExtWeakPointer QWeakPointer
#   define QExtSharedPointer QSharedPointer
template <typename T>
QExtSharedPointer<T>
qextMakeShared()
{
    return QExtSharedPointer<T>(new T);
}
template <class T, class Arg1>
QExtSharedPointer<T>
qextMakeShared(Arg1 arg1)
{
    return QExtSharedPointer<T>(new T(arg1));
}
template <class T, class Arg1, class Arg2>
QExtSharedPointer<T>
qextMakeShared(Arg1 arg1, Arg2 arg2)
{
    return QExtSharedPointer<T>(new T(arg1, arg2));
}
template <class T, class Arg1, class Arg2, class Arg3>
QExtSharedPointer<T>
qextMakeShared(Arg1 arg1, Arg2 arg2, Arg3 arg3)
{
    return QExtSharedPointer<T>(new T(arg1, arg2, arg3));
}
template <class T, class Arg1, class Arg2, class Arg3, class Arg4>
QExtSharedPointer<T>
qextMakeShared(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4)
{
    return QExtSharedPointer<T>(new T(arg1, arg2, arg3, arg4));
}
template <class T, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
QExtSharedPointer<T>
qextMakeShared(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5)
{
    return QExtSharedPointer<T>(new T(arg1, arg2, arg3, arg4, arg5));
}
template <class T, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
QExtSharedPointer<T>
qextMakeShared(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6, Arg7 arg7)
{
    return QExtSharedPointer<T>(new T(arg1, arg2, arg3, arg4, arg5, arg6, arg7));
}
template <typename T, typename U>
inline QExtSharedPointer<T>
qextDynamicPointerCast(const QExtSharedPointer<U> &r)
{
    return r.template dynamicCast<T>();
}
template <typename T>
inline QExtSharedPointer<T>
qextMakeSharedRef(const QExtWeakPointer<T> &p)
{
    return p.lock();
}
template <typename T>
inline QExtWeakPointer<T>
qextMakeWeakRef(const QExtSharedPointer<T> &p)
{
    return p.toWeakRef();
}


namespace detail
{
template <typename T, typename Cleanup = QScopedPointerArrayDeleter<T> >
class QExtUniquePointerImpl : public QScopedArrayPointer<T, Cleanup>
{
public:
    typedef QScopedArrayPointer<T, Cleanup> BaseType;
    QExtUniquePointerImpl() : BaseType() {}
    QExtUniquePointerImpl(T *p = QEXT_NULLPTR) : BaseType(p) {}
    template <typename D>
    QExtUniquePointerImpl(D *p = QEXT_NULLPTR) : QScopedArrayPointer<D>(p) {}
    QExtUniquePointerImpl(BaseType &other) { this->swap(other); }
};
} // namespace detail
#define QExtUniquePointer detail::QExtUniquePointerImpl

#endif

#endif // _QEXTMEMORY_H
