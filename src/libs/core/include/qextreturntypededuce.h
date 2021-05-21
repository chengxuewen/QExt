#ifndef QEXTRETURNTYPEDEDUCE_H
#define QEXTRETURNTYPEDEDUCE_H

#include <qextfunctortrait.h>
#include <qexttypetrait.h>

struct QEXTAdaptorBase : public QEXTFunctorBase {};

template <typename T_functor,
          typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
          typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void,
          bool I_derives_adaptor_base = QEXTBaseAndDerivedTester<QEXTAdaptorBase, T_functor>::value>
struct QEXTReturnTypeDeduce
{
    typedef typename QEXTFunctorTrait<T_functor>::ResultType Type;
};

template <typename T_functor>
struct QEXTReturnTypeDeduce<T_functor, void, void, void, void, void, void, void, true>
{
    typedef typename T_functor::template QEXTReturnTypeDeduce<>::Type Type;
};

template <typename T_functor, typename T_arg1>
struct QEXTReturnTypeDeduce<T_functor, T_arg1, void, void, void, void, void, void, true>
{
    typedef typename T_functor::template QEXTReturnTypeDeduce<T_arg1>::Type Type;
};


template <typename T_functor, typename T_arg1, typename T_arg2>
struct QEXTReturnTypeDeduce<T_functor, T_arg1, T_arg2, void, void, void, void, void, true>
{
    typedef typename T_functor::template QEXTReturnTypeDeduce<T_arg1, T_arg2>::Type Type;
};

template <typename T_functor, typename T_arg1, typename T_arg2, typename T_arg3>
struct QEXTReturnTypeDeduce<T_functor, T_arg1, T_arg2, T_arg3, void, void, void, void, true>
{
    typedef typename T_functor::template QEXTReturnTypeDeduce<T_arg1, T_arg2, T_arg3>::Type Type;
};

template <typename T_functor, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
struct QEXTReturnTypeDeduce<T_functor, T_arg1, T_arg2, T_arg3, T_arg4, void, void, void, true>
{
    typedef typename T_functor::template QEXTReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type Type;
};

template <typename T_functor, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
struct QEXTReturnTypeDeduce<T_functor, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, void, void, true>
{
    typedef typename T_functor::template QEXTReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type Type;
};

template <typename T_functor, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
struct QEXTReturnTypeDeduce<T_functor, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, void, true>
{
    typedef typename T_functor::template QEXTReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type Type;
};

template <typename T_functor, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
struct QEXTReturnTypeDeduce<T_functor, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, true>
{
    typedef typename T_functor::template QEXTReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type Type;
};


#endif // QEXTRETURNTYPEDEDUCE_H
