#ifndef QEXTADAPTORTRAIT_H
#define QEXTADAPTORTRAIT_H

#include <qextfunctortrait.h>
#include <qextresulttypededuce.h>
#include <qextvisitor.h>

template <typename T_functor> struct QEXTAdapts;

template <typename T_functor>
struct QEXTAdaptorFunctor : public QEXTAdaptorBase
{
    typedef typename QEXTFunctorTrait<T_functor>::ResultType ResultType;

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ResultTypeDeduce
    {
        typedef typename QEXTResultTypeDeduce<T_functor, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type Type;
    };

    ResultType operator()() const {
        return m_functor();
    }

    template <typename T_arg1>
    typename ResultTypeDeduce<T_arg1>::Type
    operator()(T_arg1 arg1) const {
        return m_functor(arg1);
    }

    template <typename T_arg1, typename T_arg2>
    typename ResultTypeDeduce<T_arg1, T_arg2>::Type
    operator()(T_arg1 arg1, T_arg2 arg2) const {
        return m_functor(arg1, arg2);
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) const {
        return m_functor(arg1, arg2, arg3);
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) const {
        return m_functor(arg1, arg2, arg3, arg4);
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) const {
        return m_functor(arg1, arg2, arg3, arg4, arg5);
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) const {
        return m_functor(arg1, arg2, arg3, arg4, arg5, arg6);
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7) const {
        return m_functor(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    QEXTAdaptorFunctor() {}
    explicit QEXTAdaptorFunctor(const T_functor &functor) : m_functor(functor) {}
    template <typename T_type>
    explicit QEXTAdaptorFunctor(const T_type &Type) : m_functor(Type) {}

    mutable T_functor m_functor;
};

template <typename T_functor>
struct QEXTVisitor<QEXTAdaptorFunctor<T_functor> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTAdaptorFunctor<T_functor> &target) {
        qextVisitEach(action, target.m_functor);
    }
};

template <typename T_functor, bool I_isadaptor = QEXTBaseAndDerivedTester<QEXTAdaptorBase, T_functor>::value> struct QEXTAdaptorTrait;

template <typename T_functor>
struct QEXTAdaptorTrait<T_functor, true>
{
    typedef typename T_functor::ResultType ResultType;
    typedef T_functor FunctorType;
    typedef T_functor AdaptorType;
};


template <typename T_functor>
struct QEXTAdaptorTrait<T_functor, false>
{
    typedef typename QEXTFunctorTrait<T_functor>::ResultType ResultType;
    typedef typename QEXTFunctorTrait<T_functor>::FunctorType FunctorType;
    typedef QEXTAdaptorFunctor<FunctorType> AdaptorType;
};


template <typename T_functor>
struct QEXTAdapts : public QEXTAdaptorBase
{
    typedef typename QEXTAdaptorTrait<T_functor>::ResultType  ResultType;
    typedef typename QEXTAdaptorTrait<T_functor>::AdaptorType AdaptorType;

    explicit QEXTAdapts(const T_functor &functor) : m_functor(functor) {}

    mutable AdaptorType m_functor;
};

#endif // QEXTADAPTORTRAIT_H
