#ifndef QEXTFUNCTORTRAIT_H
#define QEXTFUNCTORTRAIT_H

#include <qextglobal.h>
#include <qexttypetrait.h>

struct QEXTFunctorBase {};

template <typename T_functor, bool I_derives_functor_base = QEXTBaseAndDerivedTester<QEXTFunctorBase, T_functor>::value>
struct QEXTFunctorTrait
{
    typedef void ResultType;
    typedef T_functor FunctorType;
};

template <typename T_functor>
struct QEXTFunctorTrait<T_functor, true>
{
    typedef typename T_functor::ResultType ResultType;
    typedef T_functor FunctorType;
};


template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3> class QEXTFunctor3;
template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3>
struct QEXTFunctorTrait<T_return (*)(T_arg1, T_arg2, T_arg3), false>
{
    typedef T_return ResultType;
    typedef QEXTFunctor3<T_return, T_arg1, T_arg2, T_arg3> FunctorType;
};

template <typename T_return, typename T_arg1, typename T_arg2> class QEXTFunctor2;
template <typename T_return, typename T_arg1, typename T_arg2>
struct QEXTFunctorTrait<T_return (*)(T_arg1, T_arg2), false>
{
    typedef T_return ResultType;
    typedef QEXTFunctor2<T_return, T_arg1, T_arg2> FunctorType;
};

template <typename T_return, typename T_arg1> class QEXTFunctor1;
template <typename T_return, typename T_arg1>
struct QEXTFunctorTrait<T_return (*)(T_arg1), false>
{
    typedef T_return ResultType;
    typedef QEXTFunctor1<T_return, T_arg1> FunctorType;
};

template <typename T_return> class QEXTFunctor0;
template <typename T_return>
struct QEXTFunctorTrait<T_return (*)(), false>
{
    typedef T_return ResultType;
    typedef QEXTFunctor0<T_return> FunctorType;
};




template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3> class QEXTMemberFunctor3;
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3> class QEXTConstMemFunctor3;
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
struct QEXTFunctorTrait<T_return (T_obj::*)(T_arg1, T_arg2, T_arg3), false>
{
    typedef T_return ResultType;
    typedef QEXTMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> FunctorType;
};
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
struct QEXTFunctorTrait<T_return (T_obj::*)(T_arg1, T_arg2, T_arg3) const, false>
{
    typedef T_return ResultType;
    typedef QEXTConstMemFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> FunctorType;
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2> class QEXTMemberFunctor2;
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2> class QEXTConstMemFunctor2;
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
struct QEXTFunctorTrait<T_return (T_obj::*)(T_arg1, T_arg2), false>
{
    typedef T_return ResultType;
    typedef QEXTMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> FunctorType;
};
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
struct QEXTFunctorTrait<T_return (T_obj::*)(T_arg1, T_arg2) const, false>
{
    typedef T_return ResultType;
    typedef QEXTConstMemFunctor2<T_return, T_obj, T_arg1, T_arg2> FunctorType;
};

template <typename T_return, typename T_obj, typename T_arg1> class QEXTMemberFunctor1;
template <typename T_return, typename T_obj, typename T_arg1> class QEXTConstMemFunctor1;
template <typename T_return, typename T_obj, typename T_arg1>
struct QEXTFunctorTrait<T_return (T_obj::*)(T_arg1), false>
{
    typedef T_return ResultType;
    typedef QEXTMemberFunctor1<T_return, T_obj, T_arg1> FunctorType;
};
template <typename T_return, typename T_obj, typename T_arg1>
struct QEXTFunctorTrait<T_return (T_obj::*)(T_arg1) const, false>
{
    typedef T_return ResultType;
    typedef QEXTConstMemFunctor1<T_return, T_obj, T_arg1> FunctorType;
};

template <typename T_return, typename T_obj> class QEXTMemberFunctor0;
template <typename T_return, typename T_obj> class QEXTConstMemFunctor0;
template <typename T_return, typename T_obj>
struct QEXTFunctorTrait<T_return (T_obj::*)(), false>
{
    typedef T_return ResultType;
    typedef QEXTMemberFunctor0<T_return, T_obj> FunctorType;
};
template <typename T_return, typename T_obj>
struct QEXTFunctorTrait<T_return (T_obj::*)() const, false>
{
    typedef T_return ResultType;
    typedef QEXTConstMemFunctor0<T_return, T_obj> FunctorType;
};

#endif // QEXTFUNCTORTRAIT_H
