#ifndef _QEXTMEMORY_H
#define _QEXTMEMORY_H

#include <qextTypeTrait.h>

#include <QSharedPointer>
#include <QScopedPointer>

#define QExtSharedPointer QSharedPointer
#define QExtScopedPointer QScopedPointer

#if QEXT_USE_VARIADIC_TEMPLATES
template<typename Obj, typename... Args>
static inline QExtSharedPointer<Obj> qextMakeShared(Args&&... args)
{
    return QExtSharedPointer<Obj>(new Obj(std::forward<Args>(args)...));
}
template<typename Obj, typename... Args>
static inline QExtScopedPointer<Obj> qextMakeScoped(Args&&... args)
{
    return QExtScopedPointer<Obj>(new Obj(std::forward<Args>(args)...));
}
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
