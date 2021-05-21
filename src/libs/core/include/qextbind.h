#ifndef QEXTBIND_H
#define QEXTBIND_H

#include <qextadaptortrait.h>
#include <qextboundargument.h>


namespace qextinternal {

template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
struct QEXTCountVoid
{ static const int value = 0; };
template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
struct QEXTCountVoid<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, void>
{ static const int value = 1; };
template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
struct QEXTCountVoid<T_arg1, T_arg2, T_arg3, T_arg4,T_arg5, void, void>
{ static const int value = 2; };
template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
struct QEXTCountVoid<T_arg1, T_arg2, T_arg3, T_arg4, void, void, void>
{ static const int value = 3; };
template <typename T_arg1, typename T_arg2,class T_arg3>
struct QEXTCountVoid<T_arg1, T_arg2, T_arg3, void, void, void, void>
{ static const int value = 4; };
template <typename T_arg1, typename T_arg2>
struct QEXTCountVoid<T_arg1, T_arg2, void, void, void, void, void>
{ static const int value = 5; };
template <typename T_arg1>
struct QEXTCountVoid<T_arg1, void, void, void, void, void, void>
{ static const int value = 6; };
template <>
struct QEXTCountVoid<void, void, void, void, void, void, void>
{ static const int value = 7; };

} /* namespace qextinternal */

template <int I_location, typename T_functor,
          typename T_type1 = QEXTNil, typename T_type2 = QEXTNil, typename T_type3 = QEXTNil,
          typename T_type4 = QEXTNil, typename T_type5 = QEXTNil, typename T_type6 = QEXTNil,
          typename T_type7 = QEXTNil> struct QEXTBindFunctor;

template <typename T_functor, typename T_bound>
struct QEXTBindFunctor<0, T_functor, T_bound, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil> : public QEXTAdapts<T_functor>
{
    typedef typename QEXTAdapts<T_functor>::AdaptorType AdaptorType;

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void,
              typename T_arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename AdaptorType::template ReturnTypeDeduce<
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<T_arg3>::Pass,
        typename QEXTTypeTrait<T_arg4>::Pass,
        typename QEXTTypeTrait<T_arg5>::Pass,
        typename QEXTTypeTrait<T_arg6>::Pass>::Type Type;
    };
    typedef typename AdaptorType::ResultType  ResultType;

    ResultType operator()() {
        return this->m_functor(m_bound.invoke());
    }

    template <typename T_arg1>
    typename ReturnTypeDeduce<T_arg1>::Type
    operator()(T_arg1 arg1) {
        return this->m_functor(m_bound.invoke(), arg1);
    }

    template <typename T_arg1, typename T_arg2>
    typename ReturnTypeDeduce<T_arg1, T_arg2>::Type
    operator()(T_arg1 arg1, T_arg2 arg2) {
        return this->m_functor(m_bound.invoke(), arg1, arg2);
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) {
        return this->m_functor(m_bound.invoke(), arg1, arg2, arg3);
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) {
        return this->m_functor(m_bound.invoke(), arg1, arg2, arg3, arg4);
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) {
        return this->m_functor(m_bound.invoke(), arg1, arg2, arg3, arg4, arg5);
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) {
        return this->m_functor(m_bound.invoke(), arg1, arg2, arg3, arg4, arg5, arg6);
    }

    QEXTBindFunctor(typename QEXTTypeTrait<T_functor>::Take func, typename QEXTTypeTrait<T_bound>::Take bound)
        : QEXTAdapts<T_functor>(func), m_bound(bound) {}

    QEXTBoundArgument<T_bound> m_bound;
};


template <typename T_functor, typename T_bound>
struct QEXTBindFunctor<1, T_functor, T_bound, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil> : public QEXTAdapts<T_functor>
{
    typedef typename QEXTAdapts<T_functor>::AdaptorType AdaptorType;

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename AdaptorType::template ReturnTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<T_arg3>::Pass,
        typename QEXTTypeTrait<T_arg4>::Pass,
        typename QEXTTypeTrait<T_arg5>::Pass,
        typename QEXTTypeTrait<T_arg6>::Pass>::Type Type;
    };
    typedef typename AdaptorType::ResultType  ResultType;


    ResultType
    operator()() {
        return this->m_functor(m_bound.invoke());
    }

    template <typename T_arg1>
    typename ReturnTypeDeduce<T_arg1>::Type
    operator()(T_arg1 arg1) {
        return this->m_functor(arg1, m_bound.invoke());
    }

    template <typename T_arg1, typename T_arg2>
    typename ReturnTypeDeduce<T_arg1, T_arg2>::Type
    operator()(T_arg1 arg1, T_arg2 arg2) {
        return this->m_functor(arg1, m_bound.invoke(), arg2);
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) {
        return this->m_functor(arg1, m_bound.invoke(), arg2, arg3);
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) {
        return this->m_functor(arg1, m_bound.invoke(), arg2, arg3, arg4);
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) {
        return this->m_functor(arg1, m_bound.invoke(), arg2, arg3, arg4, arg5);
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) {
        return this->m_functor(arg1, m_bound.invoke(), arg2, arg3, arg4, arg5, arg6);
    }

    QEXTBindFunctor(typename QEXTTypeTrait<T_functor>::Take func, typename QEXTTypeTrait<T_bound>::Take bound)
        : QEXTAdapts<T_functor>(func), m_bound(bound) {}

    /// The argument bound to the functor.
    QEXTBoundArgument<T_bound> m_bound;
};


template <typename T_functor, typename T_bound>
struct QEXTBindFunctor<2, T_functor, T_bound, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil> : public QEXTAdapts<T_functor>
{
    typedef typename QEXTAdapts<T_functor>::AdaptorType AdaptorType;

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename AdaptorType::template ReturnTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
        typename QEXTTypeTrait<T_arg3>::Pass,
        typename QEXTTypeTrait<T_arg4>::Pass,
        typename QEXTTypeTrait<T_arg5>::Pass,
        typename QEXTTypeTrait<T_arg6>::Pass>::Type Type;
    };
    typedef typename AdaptorType::ResultType  ResultType;

    ResultType
    operator()() {
        return this->m_functor(m_bound.invoke());
    }

    template <typename T_arg1, typename T_arg2>
    typename ReturnTypeDeduce<T_arg1, T_arg2>::Type
    operator()(T_arg1 arg1, T_arg2 arg2) {
        return this->m_functor(arg1, arg2, m_bound.invoke());
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) {
        return this->m_functor(arg1, arg2, m_bound.invoke(), arg3);
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) {
        return this->m_functor(arg1, arg2, m_bound.invoke(), arg3, arg4);
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) {
        return this->m_functor(arg1, arg2, m_bound.invoke(), arg3, arg4, arg5);
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) {
        return this->m_functor(arg1, arg2, m_bound.invoke(), arg3, arg4, arg5, arg6);
    }


    QEXTBindFunctor(typename QEXTTypeTrait<T_functor>::Take func, typename QEXTTypeTrait<T_bound>::Take bound)
        : QEXTAdapts<T_functor>(func), m_bound(bound) {}

    /// The argument bound to the functor.
    QEXTBoundArgument<T_bound> m_bound;
};


template <typename T_functor, typename T_bound>
struct QEXTBindFunctor<3, T_functor, T_bound, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil> : public QEXTAdapts<T_functor>
{
    typedef typename QEXTAdapts<T_functor>::AdaptorType AdaptorType;

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename AdaptorType::template ReturnTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<T_arg3>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
        typename QEXTTypeTrait<T_arg4>::Pass,
        typename QEXTTypeTrait<T_arg5>::Pass,
        typename QEXTTypeTrait<T_arg6>::Pass>::Type Type;
    };
    typedef typename AdaptorType::ResultType  ResultType;


    ResultType
    operator()() {
        return this->m_functor(m_bound.invoke());
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) {
        return this->m_functor(arg1, arg2, arg3, m_bound.invoke());
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) {
        return this->m_functor(arg1, arg2, arg3, m_bound.invoke(), arg4);
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) {
        return this->m_functor(arg1, arg2, arg3, m_bound.invoke(), arg4, arg5);
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) {
        return this->m_functor(arg1, arg2, arg3, m_bound.invoke(), arg4, arg5, arg6);
    }

    QEXTBindFunctor(typename QEXTTypeTrait<T_functor>::Take func, typename QEXTTypeTrait<T_bound>::Take bound)
        : QEXTAdapts<T_functor>(func), m_bound(bound) {}

    /// The argument bound to the functor.
    QEXTBoundArgument<T_bound> m_bound;
};

template <typename T_functor, typename T_bound>
struct QEXTBindFunctor<4, T_functor, T_bound, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil> : public QEXTAdapts<T_functor>
{
    typedef typename QEXTAdapts<T_functor>::AdaptorType AdaptorType;

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename AdaptorType::template ReturnTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<T_arg3>::Pass,
        typename QEXTTypeTrait<T_arg4>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
        typename QEXTTypeTrait<T_arg5>::Pass,
        typename QEXTTypeTrait<T_arg6>::Pass>::Type Type;
    };
    typedef typename AdaptorType::ResultType  ResultType;

    ResultType
    operator()() {
        return this->m_functor(m_bound.invoke());
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) {
        return this->m_functor(arg1, arg2, arg3, arg4, m_bound.invoke());
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) {
        return this->m_functor(arg1, arg2, arg3, arg4, m_bound.invoke(), arg5);
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) {
        return this->m_functor(arg1, arg2, arg3, arg4, m_bound.invoke(), arg5, arg6);
    }


    QEXTBindFunctor(typename QEXTTypeTrait<T_functor>::Take func, typename QEXTTypeTrait<T_bound>::Take bound)
        : QEXTAdapts<T_functor>(func), m_bound(bound) {}

    QEXTBoundArgument<T_bound> m_bound;
};


template <typename T_functor, typename T_bound>
struct QEXTBindFunctor<5, T_functor, T_bound, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil> : public QEXTAdapts<T_functor>
{
    typedef typename QEXTAdapts<T_functor>::AdaptorType AdaptorType;

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename AdaptorType::template ReturnTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<T_arg3>::Pass,
        typename QEXTTypeTrait<T_arg4>::Pass,
        typename QEXTTypeTrait<T_arg5>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
        typename QEXTTypeTrait<T_arg6>::Pass>::Type Type;
    };
    typedef typename AdaptorType::ResultType  ResultType;


    ResultType
    operator()() {
        return this->m_functor(m_bound.invoke());
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) {
        return this->m_functor(arg1, arg2, arg3, arg4, arg5, m_bound.invoke());
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) {
        return this->m_functor(arg1, arg2, arg3, arg4, arg5, m_bound.invoke(), arg6);
    }

    QEXTBindFunctor(typename QEXTTypeTrait<T_functor>::Take func, typename QEXTTypeTrait<T_bound>::Take bound)
        : QEXTAdapts<T_functor>(func), m_bound(bound) {}

    /// The argument bound to the functor.
    QEXTBoundArgument<T_bound> m_bound;
};


template <typename T_functor, typename T_bound>
struct QEXTBindFunctor<6, T_functor, T_bound, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil> : public QEXTAdapts<T_functor>
{
    typedef typename QEXTAdapts<T_functor>::AdaptorType AdaptorType;

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename AdaptorType::template ReturnTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<T_arg3>::Pass,
        typename QEXTTypeTrait<T_arg4>::Pass,
        typename QEXTTypeTrait<T_arg5>::Pass,
        typename QEXTTypeTrait<T_arg6>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass>::Type Type;
    };
    typedef typename AdaptorType::ResultType  ResultType;

    ResultType
    operator()() {
        return this->m_functor(m_bound.invoke());
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) {
        return this->m_functor(arg1, arg2, arg3, arg4, arg5, arg6, m_bound.invoke());
    }

    QEXTBindFunctor(typename QEXTTypeTrait<T_functor>::Take func, typename QEXTTypeTrait<T_bound>::Take bound)
        : QEXTAdapts<T_functor>(func), m_bound(bound) {}

    /// The argument bound to the functor.
    QEXTBoundArgument<T_bound> m_bound;
};

template <int T_loc, typename T_functor, typename T_bound>
struct QEXTVisitor<QEXTBindFunctor<T_loc, T_functor, T_bound> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBindFunctor<T_loc, T_functor, T_bound> &target) {
        qextVisitEach(action, target.m_functor);
        qextVisitEach(action, target.m_bound);
    }
};

template <typename T_functor, typename T_type1>
struct QEXTBindFunctor<-1, T_functor, T_type1, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil> : public QEXTAdapts<T_functor>
{
    typedef typename QEXTAdapts<T_functor>::AdaptorType AdaptorType;

    template <int count,
              typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalReturnTypeDeduce
    {
        typedef typename AdaptorType::template ReturnTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<T_arg3>::Pass,
        typename QEXTTypeTrait<T_arg4>::Pass,
        typename QEXTTypeTrait<T_arg5>::Pass,
        typename QEXTTypeTrait<T_arg6>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass>::Type Type;
    };

    template <typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalReturnTypeDeduce<2, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
    {
        typedef typename AdaptorType::template ReturnTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<T_arg3>::Pass,
        typename QEXTTypeTrait<T_arg4>::Pass,
        typename QEXTTypeTrait<T_arg5>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass>::Type Type;
    };

    template <typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalReturnTypeDeduce<3, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
    {
        typedef typename AdaptorType::template ReturnTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<T_arg3>::Pass,
        typename QEXTTypeTrait<T_arg4>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass>::Type Type;
    };

    template <typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalReturnTypeDeduce<4, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
    {
        typedef typename AdaptorType::template ReturnTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<T_arg3>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass>::Type Type;
    };

    template <typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalReturnTypeDeduce<5, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
    {
        typedef typename AdaptorType::template ReturnTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass>::Type Type;
    };

    template <typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalReturnTypeDeduce<6, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
    {
        typedef typename AdaptorType::template ReturnTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass>::Type Type;
    };

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename InternalReturnTypeDeduce<
        qextinternal::QEXTCountVoid<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::value,
        T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type Type;
    };

    typedef typename AdaptorType::ResultType  ResultType;


    ResultType
    operator()() {
        return this->m_functor(m_bound1.invoke());
    }

    template <typename T_arg1>
    typename ReturnTypeDeduce<T_arg1>::Type
    operator()(T_arg1 arg1) {
        return this->m_functor(arg1, m_bound1.invoke());
    }

    template <typename T_arg1, typename T_arg2>
    typename ReturnTypeDeduce<T_arg1, T_arg2>::Type
    operator()(T_arg1 arg1, T_arg2 arg2) {
        return this->m_functor(arg1, arg2, m_bound1.invoke());
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) {
        return this->m_functor(arg1, arg2, arg3, m_bound1.invoke());
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) {
        return this->m_functor(arg1, arg2, arg3, arg4, m_bound1.invoke());
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) {
        return this->m_functor(arg1, arg2, arg3, arg4, arg5, m_bound1.invoke());
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) {
        return this->m_functor(arg1, arg2, arg3, arg4, arg5, arg6, m_bound1.invoke());
    }

    QEXTBindFunctor(typename QEXTTypeTrait<T_functor>::Take func, typename QEXTTypeTrait<T_type1>::Take bound1)
        : QEXTAdapts<T_functor>(func), m_bound1(bound1) {}

    /// The argument bound to the functor.
    QEXTBoundArgument<T_type1> m_bound1;
};

template <typename T_functor, typename T_type1>
struct QEXTVisitor<QEXTBindFunctor<-1, T_functor, T_type1> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBindFunctor<-1, T_functor,  T_type1> &target) {
        qextVisitEach(action, target.m_functor);
        qextVisitEach(action, target.m_bound1);
    }
};


template <typename T_functor, typename T_type1, typename T_type2>
struct QEXTBindFunctor<-1, T_functor, T_type1, T_type2, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil> : public QEXTAdapts<T_functor>
{
    typedef typename QEXTAdapts<T_functor>::AdaptorType AdaptorType;

    template <int count,
              typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalReturnTypeDeduce
    {
        typedef typename AdaptorType::template ReturnTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<T_arg3>::Pass,
        typename QEXTTypeTrait<T_arg4>::Pass,
        typename QEXTTypeTrait<T_arg5>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass>::Type Type;
    };

    template <typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalReturnTypeDeduce<3, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
    {
        typedef typename AdaptorType::template ReturnTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<T_arg3>::Pass,
        typename QEXTTypeTrait<T_arg4>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass>::Type Type;
    };

    template <typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalReturnTypeDeduce<4, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
    { typedef typename AdaptorType::template ReturnTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<T_arg3>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass>::Type Type;
    };

    template <typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalReturnTypeDeduce<5, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
    {
        typedef typename AdaptorType::template ReturnTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass>::Type Type;
    };

    template <typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalReturnTypeDeduce<6, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
    {
        typedef typename AdaptorType::template ReturnTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass>::Type Type;
    };

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename InternalReturnTypeDeduce<
        qextinternal::QEXTCountVoid<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::value,
        T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type Type;
    };
    typedef typename AdaptorType::ResultType  ResultType;


    ResultType
    operator()() {
        return this->m_functor(m_bound1.invoke(), m_bound2.invoke());
    }


    template <typename T_arg1>
    typename ReturnTypeDeduce<T_arg1>::Type
    operator()(T_arg1 arg1) {
        return this->m_functor(arg1, m_bound1.invoke(), m_bound2.invoke());
    }

    template <typename T_arg1, typename T_arg2>
    typename ReturnTypeDeduce<T_arg1, T_arg2>::Type
    operator()(T_arg1 arg1, T_arg2 arg2) {
        return this->m_functor(arg1, arg2, m_bound1.invoke(), m_bound2.invoke());
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) {
        return this->m_functor(arg1, arg2, arg3, m_bound1.invoke(), m_bound2.invoke());
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) {
        return this->m_functor(arg1, arg2, arg3, arg4, m_bound1.invoke(), m_bound2.invoke());
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) {
        return this->m_functor(arg1, arg2, arg3, arg4, arg5, m_bound1.invoke(), m_bound2.invoke());
    }

    QEXTBindFunctor(typename QEXTTypeTrait<T_functor>::Take func, typename QEXTTypeTrait<T_type1>::Take bound1,
                    typename QEXTTypeTrait<T_type2>::Take bound2)
        : QEXTAdapts<T_functor>(func), m_bound1(bound1), m_bound2(bound2) {}

    /// The argument bound to the functor.
    QEXTBoundArgument<T_type1> m_bound1;
    QEXTBoundArgument<T_type2> m_bound2;
};


template <typename T_functor, typename T_type1, typename T_type2>
struct QEXTVisitor<QEXTBindFunctor<-1, T_functor, T_type1, T_type2> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBindFunctor<-1, T_functor,  T_type1, T_type2> &target) {
        qextVisitEach(action, target.m_functor);
        qextVisitEach(action, target.m_bound1);
        qextVisitEach(action, target.m_bound2);
    }
};


template <typename T_functor, typename T_type1, typename T_type2, typename T_type3>
struct QEXTBindFunctor<-1, T_functor, T_type1, T_type2, T_type3, QEXTNil, QEXTNil, QEXTNil, QEXTNil> : public QEXTAdapts<T_functor>
{
    typedef typename QEXTAdapts<T_functor>::AdaptorType AdaptorType;

    template <int count,
              typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalReturnTypeDeduce
    {
        typedef typename AdaptorType::template ReturnTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<T_arg3>::Pass,
        typename QEXTTypeTrait<T_arg4>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass>::Type Type;
    };

    template <typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalReturnTypeDeduce<4, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
    {
        typedef typename AdaptorType::template ReturnTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<T_arg3>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass>::Type Type;
    };

    template <typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalReturnTypeDeduce<5, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
    {
        typedef typename AdaptorType::template ReturnTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass>::Type Type;
    };

    template <typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalReturnTypeDeduce<6, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
    {
        typedef typename AdaptorType::template ReturnTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass>::Type Type;
    };

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename InternalReturnTypeDeduce<
        qextinternal::QEXTCountVoid<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::value,
        T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type Type;
    };
    typedef typename AdaptorType::ResultType  ResultType;

    ResultType
    operator()() {
        return this->m_functor(m_bound1.invoke(), m_bound2.invoke(), m_bound3.invoke());
    }

    template <typename T_arg1>
    typename ReturnTypeDeduce<T_arg1>::Type
    operator()(T_arg1 arg1) {
        return this->m_functor(arg1, m_bound1.invoke(), m_bound2.invoke(), m_bound3.invoke());
    }

    template <typename T_arg1, typename T_arg2>
    typename ReturnTypeDeduce<T_arg1, T_arg2>::Type
    operator()(T_arg1 arg1, T_arg2 arg2) {
        return this->m_functor(arg1, arg2, m_bound1.invoke(), m_bound2.invoke(), m_bound3.invoke());
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) {
        return this->m_functor(arg1, arg2, arg3, m_bound1.invoke(), m_bound2.invoke(), m_bound3.invoke());
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) {
        return this->m_functor(arg1, arg2, arg3, arg4, m_bound1.invoke(), m_bound2.invoke(), m_bound3.invoke());
    }

    QEXTBindFunctor(typename QEXTTypeTrait<T_functor>::Take func, typename QEXTTypeTrait<T_type1>::Take bound1,
                    typename QEXTTypeTrait<T_type2>::Take bound2, typename QEXTTypeTrait<T_type3>::Take bound3)
        : QEXTAdapts<T_functor>(func), m_bound1(bound1), m_bound2(bound2), m_bound3(bound3) {}

    /// The argument bound to the functor.
    QEXTBoundArgument<T_type1> m_bound1;
    QEXTBoundArgument<T_type2> m_bound2;
    QEXTBoundArgument<T_type3> m_bound3;
};


template <typename T_functor, typename T_type1, typename T_type2, typename T_type3>
struct QEXTVisitor<QEXTBindFunctor<-1, T_functor, T_type1, T_type2, T_type3> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBindFunctor<-1, T_functor,  T_type1, T_type2, T_type3> &target) {
        qextVisitEach(action, target.m_functor);
        qextVisitEach(action, target.m_bound1);
        qextVisitEach(action, target.m_bound2);
        qextVisitEach(action, target.m_bound3);
    }
};


template <typename T_functor, typename T_type1, typename T_type2, typename T_type3, typename T_type4>
struct QEXTBindFunctor<-1, T_functor, T_type1, T_type2, T_type3, T_type4, QEXTNil, QEXTNil, QEXTNil> : public QEXTAdapts<T_functor>
{
    typedef typename QEXTAdapts<T_functor>::AdaptorType AdaptorType;

    template <int count,
              typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalReturnTypeDeduce
    {
        typedef typename AdaptorType::template ReturnTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<T_arg3>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type4>::Type>::Pass>::Type Type;
    };

    template <typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalReturnTypeDeduce<5, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
    {
        typedef typename AdaptorType::template ReturnTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type4>::Type>::Pass>::Type Type;
    };

    template <typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalReturnTypeDeduce<6, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
    {
        typedef typename AdaptorType::template ReturnTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type4>::Type>::Pass>::Type Type;
    };

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename InternalReturnTypeDeduce<
        qextinternal::QEXTCountVoid<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::value,
        T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type Type;
    };
    typedef typename AdaptorType::ResultType  ResultType;

    ResultType
    operator()() {
        return this->m_functor(m_bound1.invoke(), m_bound2.invoke(), m_bound3.invoke(), m_bound4.invoke());
    }

    template <typename T_arg1>
    typename ReturnTypeDeduce<T_arg1>::Type
    operator()(T_arg1 arg1) {
        return this->m_functor(arg1, m_bound1.invoke(), m_bound2.invoke(), m_bound3.invoke(), m_bound4.invoke());
    }

    template <typename T_arg1, typename T_arg2>
    typename ReturnTypeDeduce<T_arg1, T_arg2>::Type
    operator()(T_arg1 arg1, T_arg2 arg2) {
        return this->m_functor(arg1, arg2, m_bound1.invoke(), m_bound2.invoke(), m_bound3.invoke(), m_bound4.invoke());
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) {
        return this->m_functor(arg1, arg2, arg3, m_bound1.invoke(), m_bound2.invoke(), m_bound3.invoke(), m_bound4.invoke());
    }

    QEXTBindFunctor(typename QEXTTypeTrait<T_functor>::Take func, typename QEXTTypeTrait<T_type1>::Take bound1,
                    typename QEXTTypeTrait<T_type2>::Take bound2, typename QEXTTypeTrait<T_type3>::Take bound3,
                    typename QEXTTypeTrait<T_type4>::Take bound4)
        : QEXTAdapts<T_functor>(func), m_bound1(bound1), m_bound2(bound2), m_bound3(bound3), m_bound4(bound4) {}

    QEXTBoundArgument<T_type1> m_bound1;
    QEXTBoundArgument<T_type2> m_bound2;
    QEXTBoundArgument<T_type3> m_bound3;
    QEXTBoundArgument<T_type4> m_bound4;
};


template <typename T_functor, typename T_type1, typename T_type2, typename T_type3, typename T_type4>
struct QEXTVisitor<QEXTBindFunctor<-1, T_functor, T_type1, T_type2, T_type3, T_type4> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBindFunctor<-1, T_functor,  T_type1, T_type2, T_type3, T_type4> &target) {
        qextVisitEach(action, target.m_functor);
        qextVisitEach(action, target.m_bound1);
        qextVisitEach(action, target.m_bound2);
        qextVisitEach(action, target.m_bound3);
        qextVisitEach(action, target.m_bound4);
    }
};

template <typename T_functor, typename T_type1, typename T_type2, typename T_type3, typename T_type4, typename T_type5>
struct QEXTBindFunctor<-1, T_functor, T_type1, T_type2, T_type3, T_type4, T_type5, QEXTNil, QEXTNil> : public QEXTAdapts<T_functor>
{
    typedef typename QEXTAdapts<T_functor>::AdaptorType AdaptorType;

    template <int count,
              typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalReturnTypeDeduce
    {
        typedef typename AdaptorType::template ReturnTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type4>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type5>::Type>::Pass>::Type Type;
    };

    template <typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalReturnTypeDeduce<6, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
    {
        typedef typename AdaptorType::template ReturnTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type4>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type5>::Type>::Pass>::Type Type;
    };

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename InternalReturnTypeDeduce<
        qextinternal::QEXTCountVoid<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::value,
        T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type Type;
    };
    typedef typename AdaptorType::ResultType  ResultType;

    ResultType
    operator()() {
        return this->m_functor(m_bound1.invoke(), m_bound2.invoke(), m_bound3.invoke(), m_bound4.invoke(), m_bound5.invoke());
    }

    template <typename T_arg1>
    typename ReturnTypeDeduce<T_arg1>::Type
    operator()(T_arg1 arg1) {
        return this->m_functor(arg1, m_bound1.invoke(), m_bound2.invoke(), m_bound3.invoke(), m_bound4.invoke(), m_bound5.invoke());
    }

    template <typename T_arg1, typename T_arg2>
    typename ReturnTypeDeduce<T_arg1, T_arg2>::Type
    operator()(T_arg1 arg1, T_arg2 arg2) {
        return this->m_functor(arg1, arg2, m_bound1.invoke(), m_bound2.invoke(), m_bound3.invoke(), m_bound4.invoke(), m_bound5.invoke());
    }

    QEXTBindFunctor(typename QEXTTypeTrait<T_functor>::Take func, typename QEXTTypeTrait<T_type1>::Take bound1,
                    typename QEXTTypeTrait<T_type2>::Take bound2, typename QEXTTypeTrait<T_type3>::Take bound3,
                    typename QEXTTypeTrait<T_type4>::Take bound4, typename QEXTTypeTrait<T_type5>::Take bound5)
        : QEXTAdapts<T_functor>(func), m_bound1(bound1), m_bound2(bound2), m_bound3(bound3), m_bound4(bound4), m_bound5(bound5) {}

    QEXTBoundArgument<T_type1> m_bound1;
    QEXTBoundArgument<T_type2> m_bound2;
    QEXTBoundArgument<T_type3> m_bound3;
    QEXTBoundArgument<T_type4> m_bound4;
    QEXTBoundArgument<T_type5> m_bound5;
};


template <typename T_functor, typename T_type1, typename T_type2, typename T_type3, typename T_type4, typename T_type5>
struct QEXTVisitor<QEXTBindFunctor<-1, T_functor, T_type1, T_type2, T_type3, T_type4, T_type5> >
{
    template <typename T_action>
    static void doVisitEach(const T_action& action,
                            const QEXTBindFunctor<-1, T_functor,  T_type1, T_type2, T_type3, T_type4, T_type5>& target) {
        qextVisitEach(action, target.m_functor);
        qextVisitEach(action, target.m_bound1);
        qextVisitEach(action, target.m_bound2);
        qextVisitEach(action, target.m_bound3);
        qextVisitEach(action, target.m_bound4);
        qextVisitEach(action, target.m_bound5);
    }
};


template <typename T_functor, typename T_type1, typename T_type2, typename T_type3, typename T_type4, typename T_type5, typename T_type6>
struct QEXTBindFunctor<-1, T_functor, T_type1, T_type2, T_type3, T_type4, T_type5, T_type6, QEXTNil> : public QEXTAdapts<T_functor>
{
    typedef typename QEXTAdapts<T_functor>::AdaptorType AdaptorType;

    template <int count,
              typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalReturnTypeDeduce
    {
        typedef typename AdaptorType::template ReturnTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type4>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type5>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type6>::Type>::Pass>::Type Type;
    };

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename InternalReturnTypeDeduce<
        qextinternal::QEXTCountVoid<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::value,
        T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type Type;
    };
    typedef typename AdaptorType::ResultType  ResultType;

    ResultType
    operator()() {
        return this->m_functor(m_bound1.invoke(), m_bound2.invoke(), m_bound3.invoke(),
                               m_bound4.invoke(), m_bound5.invoke(), m_bound6.invoke());
    }

    template <typename T_arg1>
    typename ReturnTypeDeduce<T_arg1>::Type
    operator()(T_arg1 arg1) {
        return this->m_functor(arg1, m_bound1.invoke(), m_bound2.invoke(), m_bound3.invoke(),
                               m_bound4.invoke(), m_bound5.invoke(), m_bound6.invoke());
    }

    QEXTBindFunctor(typename QEXTTypeTrait<T_functor>::Take func, typename QEXTTypeTrait<T_type1>::Take bound1,
                    typename QEXTTypeTrait<T_type2>::Take bound2, typename QEXTTypeTrait<T_type3>::Take bound3,
                    typename QEXTTypeTrait<T_type4>::Take bound4, typename QEXTTypeTrait<T_type5>::Take bound5,
                    typename QEXTTypeTrait<T_type6>::Take bound6)
        : QEXTAdapts<T_functor>(func),
          m_bound1(bound1), m_bound2(bound2), m_bound3(bound3),
          m_bound4(bound4), m_bound5(bound5), m_bound6(bound6) {}

    QEXTBoundArgument<T_type1> m_bound1;
    QEXTBoundArgument<T_type2> m_bound2;
    QEXTBoundArgument<T_type3> m_bound3;
    QEXTBoundArgument<T_type4> m_bound4;
    QEXTBoundArgument<T_type5> m_bound5;
    QEXTBoundArgument<T_type6> m_bound6;
};


template <typename T_functor, typename T_type1, typename T_type2, typename T_type3, typename T_type4, typename T_type5, typename T_type6>
struct QEXTVisitor<QEXTBindFunctor<-1, T_functor, T_type1, T_type2, T_type3, T_type4, T_type5, T_type6> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBindFunctor<-1, T_functor,  T_type1, T_type2, T_type3, T_type4, T_type5, T_type6> &target) {
        qextVisitEach(action, target.m_functor);
        qextVisitEach(action, target.m_bound1);
        qextVisitEach(action, target.m_bound2);
        qextVisitEach(action, target.m_bound3);
        qextVisitEach(action, target.m_bound4);
        qextVisitEach(action, target.m_bound5);
        qextVisitEach(action, target.m_bound6);
    }
};


template <typename T_functor, typename T_type1, typename T_type2, typename T_type3,
          typename T_type4, typename T_type5, typename T_type6, typename T_type7>
struct QEXTBindFunctor<-1, T_functor, T_type1, T_type2, T_type3, T_type4, T_type5, T_type6, T_type7> : public QEXTAdapts<T_functor>
{
    typedef typename QEXTAdapts<T_functor>::AdaptorType AdaptorType;

    template <int count,
              typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalReturnTypeDeduce
    {
        typedef typename AdaptorType::template ReturnTypeDeduce<
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type4>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type5>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type6>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type7>::Type>::Pass>::Type Type;
    };

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename InternalReturnTypeDeduce<
        qextinternal::QEXTCountVoid<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::value,
        T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type Type;
    };
    typedef typename AdaptorType::ResultType  ResultType;

    ResultType
    operator()() {
        return this->m_functor(m_bound1.invoke(), m_bound2.invoke(), m_bound3.invoke(),
                               m_bound4.invoke(), m_bound5.invoke(), m_bound6.invoke(), m_bound7.invoke());
    }


    QEXTBindFunctor(typename QEXTTypeTrait<T_functor>::Take func, typename QEXTTypeTrait<T_type1>::Take bound1,
                    typename QEXTTypeTrait<T_type2>::Take bound2, typename QEXTTypeTrait<T_type3>::Take bound3,
                    typename QEXTTypeTrait<T_type4>::Take bound4, typename QEXTTypeTrait<T_type5>::Take bound5,
                    typename QEXTTypeTrait<T_type6>::Take bound6, typename QEXTTypeTrait<T_type7>::Take bound7)
        : QEXTAdapts<T_functor>(func),
          m_bound1(bound1), m_bound2(bound2), m_bound3(bound3),
          m_bound4(bound4), m_bound5(bound5), m_bound6(bound6), m_bound7(bound7) {}

    /// The argument bound to the functor.
    QEXTBoundArgument<T_type1> m_bound1;
    QEXTBoundArgument<T_type2> m_bound2;
    QEXTBoundArgument<T_type3> m_bound3;
    QEXTBoundArgument<T_type4> m_bound4;
    QEXTBoundArgument<T_type5> m_bound5;
    QEXTBoundArgument<T_type6> m_bound6;
    QEXTBoundArgument<T_type7> m_bound7;
};


template <typename T_functor, typename T_type1, typename T_type2, typename T_type3, typename T_type4, typename T_type5, typename T_type6, typename T_type7>
struct QEXTVisitor<QEXTBindFunctor<-1, T_functor, T_type1, T_type2, T_type3, T_type4, T_type5, T_type6, T_type7> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBindFunctor<-1, T_functor,  T_type1, T_type2, T_type3, T_type4, T_type5, T_type6, T_type7> &target) {
        qextVisitEach(action, target.m_functor);
        qextVisitEach(action, target.m_bound1);
        qextVisitEach(action, target.m_bound2);
        qextVisitEach(action, target.m_bound3);
        qextVisitEach(action, target.m_bound4);
        qextVisitEach(action, target.m_bound5);
        qextVisitEach(action, target.m_bound6);
        qextVisitEach(action, target.m_bound7);
    }
};



template <int I_location, typename T_bound1, typename T_functor>
inline QEXTBindFunctor<I_location, T_functor, T_bound1>
qextBind(const T_functor &func, T_bound1 bound1) {
    return QEXTBindFunctor<I_location, T_functor, T_bound1>(func, bound1);
}


template <typename T_type1, typename T_functor>
inline QEXTBindFunctor<-1, T_functor, T_type1>
qextBind(const T_functor &func, T_type1 bound1) {
    return QEXTBindFunctor<-1, T_functor, T_type1>(func, bound1);
}


template <typename T_type1, typename T_type2, typename T_functor>
inline QEXTBindFunctor<-1, T_functor, T_type1, T_type2>
qextBind(const T_functor &func, T_type1 bound1, T_type2 bound2) {
    return QEXTBindFunctor<-1, T_functor, T_type1, T_type2>(func, bound1, bound2);
}


template <typename T_type1, typename T_type2, typename T_type3, typename T_functor>
inline QEXTBindFunctor<-1, T_functor, T_type1, T_type2, T_type3>
qextBind(const T_functor &func, T_type1 bound1, T_type2 bound2, T_type3 bound3) {
    return QEXTBindFunctor<-1, T_functor, T_type1, T_type2, T_type3>(func, bound1, bound2, bound3);
}


template <typename T_type1, typename T_type2, typename T_type3, typename T_type4, typename T_functor>
inline QEXTBindFunctor<-1, T_functor, T_type1, T_type2, T_type3, T_type4>
qextBind(const T_functor &func, T_type1 bound1, T_type2 bound2, T_type3 bound3, T_type4 bound4) {
    return QEXTBindFunctor<-1, T_functor, T_type1, T_type2, T_type3, T_type4>(func, bound1, bound2, bound3, bound4);
}


template <typename T_type1, typename T_type2, typename T_type3, typename T_type4, typename T_type5, typename T_functor>
inline QEXTBindFunctor<-1, T_functor, T_type1, T_type2, T_type3, T_type4, T_type5>
qextBind(const T_functor &func, T_type1 bound1, T_type2 bound2, T_type3 bound3, T_type4 bound4, T_type5 bound5) {
    return QEXTBindFunctor<-1, T_functor, T_type1, T_type2, T_type3, T_type4, T_type5>(func, bound1, bound2, bound3, bound4, bound5);
}


template <typename T_type1, typename T_type2, typename T_type3, typename T_type4, typename T_type5, typename T_type6, typename T_functor>
inline QEXTBindFunctor<-1, T_functor, T_type1, T_type2, T_type3, T_type4, T_type5, T_type6>
qextBind(const T_functor &func, T_type1 bound1, T_type2 bound2, T_type3 bound3, T_type4 bound4, T_type5 bound5, T_type6 bound6) {
    return QEXTBindFunctor<-1, T_functor, T_type1, T_type2, T_type3, T_type4, T_type5, T_type6>(func, bound1, bound2, bound3, bound4, bound5, bound6);
}


template <typename T_type1, typename T_type2, typename T_type3, typename T_type4, typename T_type5, typename T_type6, typename T_type7, typename T_functor>
inline QEXTBindFunctor<-1, T_functor, T_type1, T_type2, T_type3, T_type4, T_type5, T_type6, T_type7>
qextBind(const T_functor &func, T_type1 bound1, T_type2 bound2, T_type3 bound3, T_type4 bound4, T_type5 bound5, T_type6 bound6, T_type7 bound7) {
    return QEXTBindFunctor<-1, T_functor, T_type1, T_type2, T_type3, T_type4, T_type5, T_type6, T_type7>(func, bound1, bound2, bound3, bound4, bound5, bound6, bound7);
}


#endif // QEXTBIND_H
