#ifndef _QEXTMEMORY_H
#define _QEXTMEMORY_H

#include <qextTypeTrait.h>

#include <QSharedPointer>

#if QEXT_CC_STD_11
template<typename T_obj,
         typename... Types>
static inline QSharedPointer<T_obj> qextMakeShared(Types&&... args)
{
    return QSharedPointer<T_obj>(new T_obj(std::forward<Types>(args)...));
}
#else
template<typename T_obj,
         typename T_arg1,
         typename T_arg2,
         typename T_arg3,
         typename T_arg4,
         typename T_arg5,
         typename T_arg6,
         typename T_arg7,
         typename T_arg8,
         typename T_arg9>
static inline QSharedPointer<T_obj> qextMakeShared(typename QExtTypeTrait<T_arg1>::Take arg1,
                                                   typename QExtTypeTrait<T_arg2>::Take arg2,
                                                   typename QExtTypeTrait<T_arg3>::Take arg3,
                                                   typename QExtTypeTrait<T_arg4>::Take arg4,
                                                   typename QExtTypeTrait<T_arg4>::Take arg5,
                                                   typename QExtTypeTrait<T_arg4>::Take arg6,
                                                   typename QExtTypeTrait<T_arg4>::Take arg7,
                                                   typename QExtTypeTrait<T_arg4>::Take arg8,
                                                   typename QExtTypeTrait<T_arg4>::Take arg9)
{
    return QSharedPointer<T_obj>(new T_obj(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9));
}

template<typename T_obj,
         typename T_arg1,
         typename T_arg2,
         typename T_arg3,
         typename T_arg4,
         typename T_arg5,
         typename T_arg6,
         typename T_arg7,
         typename T_arg8>
static inline QSharedPointer<T_obj> qextMakeShared(typename QExtTypeTrait<T_arg1>::Take arg1,
                                                   typename QExtTypeTrait<T_arg2>::Take arg2,
                                                   typename QExtTypeTrait<T_arg3>::Take arg3,
                                                   typename QExtTypeTrait<T_arg4>::Take arg4,
                                                   typename QExtTypeTrait<T_arg4>::Take arg5,
                                                   typename QExtTypeTrait<T_arg4>::Take arg6,
                                                   typename QExtTypeTrait<T_arg4>::Take arg7,
                                                   typename QExtTypeTrait<T_arg4>::Take arg8)
{
    return QSharedPointer<T_obj>(new T_obj(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8));
}

template<typename T_obj,
         typename T_arg1,
         typename T_arg2,
         typename T_arg3,
         typename T_arg4,
         typename T_arg5,
         typename T_arg6,
         typename T_arg7>
static inline QSharedPointer<T_obj> qextMakeShared(typename QExtTypeTrait<T_arg1>::Take arg1,
                                                   typename QExtTypeTrait<T_arg2>::Take arg2,
                                                   typename QExtTypeTrait<T_arg3>::Take arg3,
                                                   typename QExtTypeTrait<T_arg4>::Take arg4,
                                                   typename QExtTypeTrait<T_arg4>::Take arg5,
                                                   typename QExtTypeTrait<T_arg4>::Take arg6,
                                                   typename QExtTypeTrait<T_arg4>::Take arg7)
{
    return QSharedPointer<T_obj>(new T_obj(arg1, arg2, arg3, arg4, arg5, arg6, arg7));
}

template<typename T_obj,
         typename T_arg1,
         typename T_arg2,
         typename T_arg3,
         typename T_arg4,
         typename T_arg5,
         typename T_arg6>
static inline QSharedPointer<T_obj> qextMakeShared(typename QExtTypeTrait< T_arg1 >::Take arg1,
                                                   typename QExtTypeTrait< T_arg2 >::Take arg2,
                                                   typename QExtTypeTrait< T_arg3 >::Take arg3,
                                                   typename QExtTypeTrait< T_arg4 >::Take arg4,
                                                   typename QExtTypeTrait< T_arg4 >::Take arg5,
                                                   typename QExtTypeTrait< T_arg4 >::Take arg6)
{
    return QSharedPointer<T_obj>(new T_obj(arg1, arg2, arg3, arg4, arg5, arg6));
}

template<typename T_obj,
         typename T_arg1,
         typename T_arg2,
         typename T_arg3,
         typename T_arg4,
         typename T_arg5>
static inline QSharedPointer<T_obj> qextMakeShared(typename QExtTypeTrait<T_arg1>::Take arg1,
                                                   typename QExtTypeTrait<T_arg2>::Take arg2,
                                                   typename QExtTypeTrait<T_arg3>::Take arg3,
                                                   typename QExtTypeTrait<T_arg4>::Take arg4,
                                                   typename QExtTypeTrait<T_arg4>::Take arg5)
{
    return QSharedPointer<T_obj>(new T_obj(arg1, arg2, arg3, arg4, arg5));
}

template<typename T_obj,
         typename T_arg1,
         typename T_arg2,
         typename T_arg3,
         typename T_arg4>
static inline QSharedPointer<T_obj> qextMakeShared(typename QExtTypeTrait<T_arg1>::Take arg1,
                                                   typename QExtTypeTrait<T_arg2>::Take arg2,
                                                   typename QExtTypeTrait<T_arg3>::Take arg3,
                                                   typename QExtTypeTrait<T_arg4>::Take arg4)
{
    return QSharedPointer<T_obj>(new T_obj(arg1, arg2, arg3, arg4));
}

template<typename T_obj,
         typename T_arg1,
         typename T_arg2,
         typename T_arg3>
static inline QSharedPointer<T_obj> qextMakeShared(typename QExtTypeTrait<T_arg1>::Take arg1,
                                                   typename QExtTypeTrait<T_arg2>::Take arg2,
                                                   typename QExtTypeTrait<T_arg3>::Take arg3)
{
    return QSharedPointer<T_obj>(new T_obj(arg1, arg2, arg3));
}

template<typename T_obj,
         typename T_arg1,
         typename T_arg2>
static inline QSharedPointer<T_obj> qextMakeShared(typename QExtTypeTrait<T_arg1>::Take arg1,
                                                   typename QExtTypeTrait<T_arg2>::Take arg2)
{
    return QSharedPointer<T_obj>(new T_obj(arg1, arg2));
}

template<typename T_obj,
         typename T_arg1>
static inline QSharedPointer<T_obj> qextMakeShared(typename QExtTypeTrait<T_arg1>::Take arg1)
{
    return QSharedPointer<T_obj>(new T_obj(arg1));
}

template<typename T_obj,
         typename T_arg1>
static inline QSharedPointer<T_obj> qextMakeShared(T_arg1 arg1)
{
    return QSharedPointer<T_obj>(new T_obj(arg1));
}

template<typename T_obj>
static inline QSharedPointer<T_obj> qextMakeShared()
{
    return QSharedPointer<T_obj>(new T_obj());
}
#endif

#endif // _QEXTMEMORY_H
