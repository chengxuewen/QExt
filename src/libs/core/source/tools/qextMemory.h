#ifndef _QEXTMEMORY_H
#define _QEXTMEMORY_H

#include <qextTypeTrait.h>

#include <QSharedPointer>
#include <QScopedPointer>

#if QEXT_CC_STD_11
#   include <memory>
#   define QExtWeakPointer std::weak_ptr
#   define QExtSharedPointer std::shared_ptr
#   define QExtUniquePointer std::unique_ptr
template <typename T>
inline QExtSharedPointer<T> qextMakeSharedRef(const QExtWeakPointer<T> &p) { return p.lock(); }
template <typename T>
inline QExtWeakPointer<T> qextMakeWeakRef(const QExtSharedPointer<T> &p) { return QExtWeakPointer<T>(p); }
template <typename T, typename U>
QExtSharedPointer<T> qextDynamicPointerCast(const QExtSharedPointer<U> &r) { return dynamic_pointer_cast<T, U>(r); }
#else
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



#if !QEXT_USE_VARIADIC_TEMPLATES
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
#if __GNUC__ == 4 && __GNUC_MINOR__ <= 6
    // G++ 4.6 has an ICE when you have no arguments
    static inline UniquePointer make()
    {
        return UniquePointer(new T[N]);
    }
};
} // namespace detail
template <typename T, typename... Args>
inline typename detail::QExtUniquePointerHelper<T>::UniquePointer qextMakeUnique(Args&&... args)
{
    return detail::QExtUniquePointerHelper<T>::make(std::forward<Args>(args)...);
}
#endif
#else
/**
 * @brief qextMakeShared
 * @return
 */
template<typename Obj,
         typename Arg1,
         typename Arg2,
         typename Arg3,
         typename Arg4,
         typename Arg5,
         typename Arg6,
         typename Arg7,
         typename Arg8,
         typename Arg9>
static inline QExtSharedPointer<Obj> qextMakeShared(typename QExtTypeTrait<Arg1>::Take arg1,
                                                    typename QExtTypeTrait<Arg2>::Take arg2,
                                                    typename QExtTypeTrait<Arg3>::Take arg3,
                                                    typename QExtTypeTrait<Arg4>::Take arg4,
                                                    typename QExtTypeTrait<Arg4>::Take arg5,
                                                    typename QExtTypeTrait<Arg4>::Take arg6,
                                                    typename QExtTypeTrait<Arg4>::Take arg7,
                                                    typename QExtTypeTrait<Arg4>::Take arg8,
                                                    typename QExtTypeTrait<Arg4>::Take arg9)
{
    return QExtSharedPointer<Obj>(new Obj(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9));
}

template<typename Obj,
         typename Arg1,
         typename Arg2,
         typename Arg3,
         typename Arg4,
         typename Arg5,
         typename Arg6,
         typename Arg7,
         typename Arg8>
static inline QExtSharedPointer<Obj> qextMakeShared(typename QExtTypeTrait<Arg1>::Take arg1,
                                                    typename QExtTypeTrait<Arg2>::Take arg2,
                                                    typename QExtTypeTrait<Arg3>::Take arg3,
                                                    typename QExtTypeTrait<Arg4>::Take arg4,
                                                    typename QExtTypeTrait<Arg4>::Take arg5,
                                                    typename QExtTypeTrait<Arg4>::Take arg6,
                                                    typename QExtTypeTrait<Arg4>::Take arg7,
                                                    typename QExtTypeTrait<Arg4>::Take arg8)
{
    return QExtSharedPointer<Obj>(new Obj(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8));
}

template<typename Obj,
         typename Arg1,
         typename Arg2,
         typename Arg3,
         typename Arg4,
         typename Arg5,
         typename Arg6,
         typename Arg7>
static inline QExtSharedPointer<Obj> qextMakeShared(typename QExtTypeTrait<Arg1>::Take arg1,
                                                    typename QExtTypeTrait<Arg2>::Take arg2,
                                                    typename QExtTypeTrait<Arg3>::Take arg3,
                                                    typename QExtTypeTrait<Arg4>::Take arg4,
                                                    typename QExtTypeTrait<Arg4>::Take arg5,
                                                    typename QExtTypeTrait<Arg4>::Take arg6,
                                                    typename QExtTypeTrait<Arg4>::Take arg7)
{
    return QExtSharedPointer<Obj>(new Obj(arg1, arg2, arg3, arg4, arg5, arg6, arg7));
}

template<typename Obj,
         typename Arg1,
         typename Arg2,
         typename Arg3,
         typename Arg4,
         typename Arg5,
         typename Arg6>
static inline QExtSharedPointer<Obj> qextMakeShared(typename QExtTypeTrait< Arg1 >::Take arg1,
                                                    typename QExtTypeTrait< Arg2 >::Take arg2,
                                                    typename QExtTypeTrait< Arg3 >::Take arg3,
                                                    typename QExtTypeTrait< Arg4 >::Take arg4,
                                                    typename QExtTypeTrait< Arg4 >::Take arg5,
                                                    typename QExtTypeTrait< Arg4 >::Take arg6)
{
    return QExtSharedPointer<Obj>(new Obj(arg1, arg2, arg3, arg4, arg5, arg6));
}

template<typename Obj,
         typename Arg1,
         typename Arg2,
         typename Arg3,
         typename Arg4,
         typename Arg5>
static inline QExtSharedPointer<Obj> qextMakeShared(typename QExtTypeTrait<Arg1>::Take arg1,
                                                    typename QExtTypeTrait<Arg2>::Take arg2,
                                                    typename QExtTypeTrait<Arg3>::Take arg3,
                                                    typename QExtTypeTrait<Arg4>::Take arg4,
                                                    typename QExtTypeTrait<Arg4>::Take arg5)
{
    return QExtSharedPointer<Obj>(new Obj(arg1, arg2, arg3, arg4, arg5));
}

template<typename Obj,
         typename Arg1,
         typename Arg2,
         typename Arg3,
         typename Arg4>
static inline QExtSharedPointer<Obj> qextMakeShared(typename QExtTypeTrait<Arg1>::Take arg1,
                                                    typename QExtTypeTrait<Arg2>::Take arg2,
                                                    typename QExtTypeTrait<Arg3>::Take arg3,
                                                    typename QExtTypeTrait<Arg4>::Take arg4)
{
    return QExtSharedPointer<Obj>(new Obj(arg1, arg2, arg3, arg4));
}

template<typename Obj,
         typename Arg1,
         typename Arg2,
         typename Arg3>
static inline QExtSharedPointer<Obj> qextMakeShared(typename QExtTypeTrait<Arg1>::Take arg1,
                                                    typename QExtTypeTrait<Arg2>::Take arg2,
                                                    typename QExtTypeTrait<Arg3>::Take arg3)
{
    return QExtSharedPointer<Obj>(new Obj(arg1, arg2, arg3));
}

template<typename Obj,
         typename Arg1,
         typename Arg2>
static inline QExtSharedPointer<Obj> qextMakeShared(typename QExtTypeTrait<Arg1>::Take arg1,
                                                    typename QExtTypeTrait<Arg2>::Take arg2)
{
    return QExtSharedPointer<Obj>(new Obj(arg1, arg2));
}

template<typename Obj,
         typename Arg1>
static inline QExtSharedPointer<Obj> qextMakeShared(typename QExtTypeTrait<Arg1>::Take arg1)
{
    return QExtSharedPointer<Obj>(new Obj(arg1));
}

template<typename Obj,
         typename Arg1>
static inline QExtSharedPointer<Obj> qextMakeShared(Arg1 arg1)
{
    return QExtSharedPointer<Obj>(new Obj(arg1));
}

template<typename Obj>
static inline QExtSharedPointer<Obj> qextMakeShared()
{
    return QExtSharedPointer<Obj>(new Obj());
}

/**
 * @brief qextMakeScoped
 * @return
 */
template<typename Obj,
         typename Arg1,
         typename Arg2,
         typename Arg3,
         typename Arg4,
         typename Arg5,
         typename Arg6,
         typename Arg7,
         typename Arg8,
         typename Arg9>
static inline QExtScopedPointer<Obj> qextMakeScoped(typename QExtTypeTrait<Arg1>::Take arg1,
                                                    typename QExtTypeTrait<Arg2>::Take arg2,
                                                    typename QExtTypeTrait<Arg3>::Take arg3,
                                                    typename QExtTypeTrait<Arg4>::Take arg4,
                                                    typename QExtTypeTrait<Arg4>::Take arg5,
                                                    typename QExtTypeTrait<Arg4>::Take arg6,
                                                    typename QExtTypeTrait<Arg4>::Take arg7,
                                                    typename QExtTypeTrait<Arg4>::Take arg8,
                                                    typename QExtTypeTrait<Arg4>::Take arg9)
{
    return QExtScopedPointer<Obj>(new Obj(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9));
}

template<typename Obj,
         typename Arg1,
         typename Arg2,
         typename Arg3,
         typename Arg4,
         typename Arg5,
         typename Arg6,
         typename Arg7,
         typename Arg8>
static inline QExtScopedPointer<Obj> qextMakeScoped(typename QExtTypeTrait<Arg1>::Take arg1,
                                                    typename QExtTypeTrait<Arg2>::Take arg2,
                                                    typename QExtTypeTrait<Arg3>::Take arg3,
                                                    typename QExtTypeTrait<Arg4>::Take arg4,
                                                    typename QExtTypeTrait<Arg4>::Take arg5,
                                                    typename QExtTypeTrait<Arg4>::Take arg6,
                                                    typename QExtTypeTrait<Arg4>::Take arg7,
                                                    typename QExtTypeTrait<Arg4>::Take arg8)
{
    return QExtScopedPointer<Obj>(new Obj(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8));
}

template<typename Obj,
         typename Arg1,
         typename Arg2,
         typename Arg3,
         typename Arg4,
         typename Arg5,
         typename Arg6,
         typename Arg7>
static inline QExtScopedPointer<Obj> qextMakeScoped(typename QExtTypeTrait<Arg1>::Take arg1,
                                                    typename QExtTypeTrait<Arg2>::Take arg2,
                                                    typename QExtTypeTrait<Arg3>::Take arg3,
                                                    typename QExtTypeTrait<Arg4>::Take arg4,
                                                    typename QExtTypeTrait<Arg4>::Take arg5,
                                                    typename QExtTypeTrait<Arg4>::Take arg6,
                                                    typename QExtTypeTrait<Arg4>::Take arg7)
{
    return QExtScopedPointer<Obj>(new Obj(arg1, arg2, arg3, arg4, arg5, arg6, arg7));
}

template<typename Obj,
         typename Arg1,
         typename Arg2,
         typename Arg3,
         typename Arg4,
         typename Arg5,
         typename Arg6>
static inline QExtScopedPointer<Obj> qextMakeScoped(typename QExtTypeTrait< Arg1 >::Take arg1,
                                                    typename QExtTypeTrait< Arg2 >::Take arg2,
                                                    typename QExtTypeTrait< Arg3 >::Take arg3,
                                                    typename QExtTypeTrait< Arg4 >::Take arg4,
                                                    typename QExtTypeTrait< Arg4 >::Take arg5,
                                                    typename QExtTypeTrait< Arg4 >::Take arg6)
{
    return QExtScopedPointer<Obj>(new Obj(arg1, arg2, arg3, arg4, arg5, arg6));
}

template<typename Obj,
         typename Arg1,
         typename Arg2,
         typename Arg3,
         typename Arg4,
         typename Arg5>
static inline QExtScopedPointer<Obj> qextMakeScoped(typename QExtTypeTrait<Arg1>::Take arg1,
                                                    typename QExtTypeTrait<Arg2>::Take arg2,
                                                    typename QExtTypeTrait<Arg3>::Take arg3,
                                                    typename QExtTypeTrait<Arg4>::Take arg4,
                                                    typename QExtTypeTrait<Arg4>::Take arg5)
{
    return QExtScopedPointer<Obj>(new Obj(arg1, arg2, arg3, arg4, arg5));
}

template<typename Obj,
         typename Arg1,
         typename Arg2,
         typename Arg3,
         typename Arg4>
static inline QExtScopedPointer<Obj> qextMakeScoped(typename QExtTypeTrait<Arg1>::Take arg1,
                                                    typename QExtTypeTrait<Arg2>::Take arg2,
                                                    typename QExtTypeTrait<Arg3>::Take arg3,
                                                    typename QExtTypeTrait<Arg4>::Take arg4)
{
    return QExtScopedPointer<Obj>(new Obj(arg1, arg2, arg3, arg4));
}

template<typename Obj,
         typename Arg1,
         typename Arg2,
         typename Arg3>
static inline QExtScopedPointer<Obj> qextMakeScoped(typename QExtTypeTrait<Arg1>::Take arg1,
                                                    typename QExtTypeTrait<Arg2>::Take arg2,
                                                    typename QExtTypeTrait<Arg3>::Take arg3)
{
    return QExtScopedPointer<Obj>(new Obj(arg1, arg2, arg3));
}

template<typename Obj,
         typename Arg1,
         typename Arg2>
static inline QExtScopedPointer<Obj> qextMakeScoped(typename QExtTypeTrait<Arg1>::Take arg1,
                                                    typename QExtTypeTrait<Arg2>::Take arg2)
{
    return QExtScopedPointer<Obj>(new Obj(arg1, arg2));
}

template<typename Obj,
         typename Arg1>
static inline QExtScopedPointer<Obj> qextMakeScoped(typename QExtTypeTrait<Arg1>::Take arg1)
{
    return QExtScopedPointer<Obj>(new Obj(arg1));
}

template<typename Obj>
static inline QExtScopedPointer<Obj> qextMakeScoped()
{
    return QExtScopedPointer<Obj>(new Obj());
}
#endif

#endif // _QEXTMEMORY_H
