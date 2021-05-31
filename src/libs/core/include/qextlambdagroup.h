#ifndef QEXTLAMBDAGROUP_H
#define QEXTLAMBDAGROUP_H

#include <qextlambdabase.h>
#include <qextfunctortrait.h>
#include <qextadaptortrait.h>

template <typename T_functor, typename T_type1>
struct LambdaGroup1 : public QEXTLambdaBase
{
    typedef typename QEXTFunctorTrait<T_functor>::ResultType ResultType;
    typedef typename QEXTLambda<T_type1>::LambdaType   Value1Type;
    typedef typename QEXTAdaptorTrait<T_functor>::AdaptorType FunctorType;


    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ResultTypeDeduce
    {
        typedef typename FunctorType::template ResultTypeDeduce<
        typename Value1Type::template ResultTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<T_arg3>::Pass,
        typename QEXTTypeTrait<T_arg4>::Pass,
        typename QEXTTypeTrait<T_arg5>::Pass,
        typename QEXTTypeTrait<T_arg6>::Pass,
        typename QEXTTypeTrait<T_arg7>::Pass>::Type>::Type Type;
    };


    ResultType
    operator ()() const {
        return m_functor(m_value1());
    }

    template <typename T_arg1>
    typename ResultTypeDeduce<T_arg1>::Type
    operator() (T_arg1 arg1) const
    {
        return this->m_functor.template operator ()<
                typename Value1Type::template ResultTypeDeduce<T_arg1>::Type>(
                    this->m_value1.template operator ()<
                    typename QEXTTypeTrait<T_arg1>::Pass>(arg1));
    }


    template <typename T_arg1, typename T_arg2>
    typename ResultTypeDeduce<T_arg1, T_arg2>::Type
    operator() (T_arg1 arg1, T_arg2 arg2) const {
        return this->m_functor.template operator ()<
                typename Value1Type::template ResultTypeDeduce<T_arg1,T_arg2>::Type>(
                    this->m_value1.template operator ()<
                    typename QEXTTypeTrait<T_arg1>::Pass,
                    typename QEXTTypeTrait<T_arg2>::Pass>(arg1, arg2));
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3>::Type
    operator() (T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) const {
        return this->m_functor.template operator ()<
                typename Value1Type::template ResultTypeDeduce<T_arg1,T_arg2,T_arg3>::Type>(
                    this->m_value1.template operator ()<
                    typename QEXTTypeTrait<T_arg1>::Pass,
                    typename QEXTTypeTrait<T_arg2>::Pass,
                    typename QEXTTypeTrait<T_arg3>::Pass>(arg1, arg2, arg3));
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator() (T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) const {
        return this->m_functor.template operator ()<
                typename Value1Type::template ResultTypeDeduce<T_arg1,T_arg2,T_arg3,T_arg4>::Type>(
                    this->m_value1.template operator ()<
                    typename QEXTTypeTrait<T_arg1>::Pass,
                    typename QEXTTypeTrait<T_arg2>::Pass,
                    typename QEXTTypeTrait<T_arg3>::Pass,
                    typename QEXTTypeTrait<T_arg4>::Pass>(arg1, arg2, arg3, arg4));
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator() (T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) const {
        return this->m_functor.template operator ()<
                typename Value1Type::template ResultTypeDeduce<T_arg1,T_arg2,T_arg3,T_arg4,T_arg5>::Type>(
                    this->m_value1.template operator ()<
                    typename QEXTTypeTrait<T_arg1>::Pass,
                    typename QEXTTypeTrait<T_arg2>::Pass,
                    typename QEXTTypeTrait<T_arg3>::Pass,
                    typename QEXTTypeTrait<T_arg4>::Pass,
                    typename QEXTTypeTrait<T_arg5>::Pass>(arg1, arg2, arg3, arg4, arg5));
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator() (T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) const {
        return this->m_functor.template operator ()<
                typename Value1Type::template ResultTypeDeduce<T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6>::Type>(
                    this->m_value1.template operator ()<
                    typename QEXTTypeTrait<T_arg1>::Pass,
                    typename QEXTTypeTrait<T_arg2>::Pass,
                    typename QEXTTypeTrait<T_arg3>::Pass,
                    typename QEXTTypeTrait<T_arg4>::Pass,
                    typename QEXTTypeTrait<T_arg5>::Pass,
                    typename QEXTTypeTrait<T_arg6>::Pass>(arg1, arg2, arg3, arg4, arg5, arg6));
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type
    operator() (T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7) const {
        return this->m_functor.template operator ()<
                typename Value1Type::template ResultTypeDeduce<T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6,T_arg7>::Type>(
                    this->m_value1.template operator ()<
                    typename QEXTTypeTrait<T_arg1>::Pass,
                    typename QEXTTypeTrait<T_arg2>::Pass,
                    typename QEXTTypeTrait<T_arg3>::Pass,
                    typename QEXTTypeTrait<T_arg4>::Pass,
                    typename QEXTTypeTrait<T_arg5>::Pass,
                    typename QEXTTypeTrait<T_arg6>::Pass,
                    typename QEXTTypeTrait<T_arg7>::Pass>(arg1, arg2, arg3, arg4, arg5, arg6, arg7));
    }


    LambdaGroup1(typename QEXTTypeTrait<T_functor>::Take func, typename QEXTTypeTrait<T_type1>::Take arg1)
        : m_value1(arg1), m_functor(func) {}

    Value1Type m_value1;
    mutable FunctorType m_functor;
};


//template specialization of QEXTVisitor<>::doVisitEach<>(action, functor):
template <typename T_functor, typename T_type1>
struct QEXTVisitor<LambdaGroup1<T_functor, T_type1> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const LambdaGroup1<T_functor, T_type1> &target) {
        qextVisitEach(action, target.m_value1);
        qextVisitEach(action, target.m_functor);
    }
};

template <typename T_functor, typename T_type1, typename T_type2>
struct QEXTLambdaGroup2 : public QEXTLambdaBase
{
    typedef typename QEXTFunctorTrait<T_functor>::ResultType    ResultType;
    typedef typename QEXTLambda<T_type1>::LambdaType            Value1Type;
    typedef typename QEXTLambda<T_type2>::LambdaType            Value2Type;
    typedef typename QEXTAdaptorTrait<T_functor>::AdaptorType   FunctorType;


    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ResultTypeDeduce
    {
        typedef typename FunctorType::template ResultTypeDeduce<
        typename Value1Type::template ResultTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<T_arg3>::Pass,
        typename QEXTTypeTrait<T_arg4>::Pass,
        typename QEXTTypeTrait<T_arg5>::Pass,
        typename QEXTTypeTrait<T_arg6>::Pass,
        typename QEXTTypeTrait<T_arg7>::Pass>::Type,
        typename Value2Type::template ResultTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<T_arg3>::Pass,
        typename QEXTTypeTrait<T_arg4>::Pass,
        typename QEXTTypeTrait<T_arg5>::Pass,
        typename QEXTTypeTrait<T_arg6>::Pass,
        typename QEXTTypeTrait<T_arg7>::Pass>::Type>::Type Type;
    };


    ResultType
    operator ()() const {
        return m_functor(m_value1(), m_value2());
    }

    template <typename T_arg1>
    typename ResultTypeDeduce<T_arg1>::Type
    operator() (T_arg1 arg1) const {
        return this->m_functor.template operator ()<
                typename Value1Type::template ResultTypeDeduce<T_arg1>::Type,
                typename Value2Type::template ResultTypeDeduce<T_arg1>::Type>(
                    this->m_value1.template operator ()<
                    typename QEXTTypeTrait<T_arg1>::Pass>(arg1),
                    this->m_value2.template operator ()<
                    typename QEXTTypeTrait<T_arg1>::Pass>(arg1));
    }


    template <typename T_arg1, typename T_arg2>
    typename ResultTypeDeduce<T_arg1, T_arg2>::Type
    operator() (T_arg1 arg1, T_arg2 arg2) const {
        return this->m_functor.template operator ()<
                typename Value1Type::template ResultTypeDeduce<T_arg1,T_arg2>::Type,
                typename Value2Type::template ResultTypeDeduce<T_arg1,T_arg2>::Type>(
                    this->m_value1.template operator ()<
                    typename QEXTTypeTrait<T_arg1>::Pass,
                    typename QEXTTypeTrait<T_arg2>::Pass>(arg1, arg2),
                    this->m_value2.template operator ()<
                    typename QEXTTypeTrait<T_arg1>::Pass,
                    typename QEXTTypeTrait<T_arg2>::Pass>(arg1, arg2));
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3>::Type
    operator() (T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) const {
        return this->m_functor.template operator ()<
                typename Value1Type::template ResultTypeDeduce<T_arg1,T_arg2,T_arg3>::Type,
                typename Value2Type::template ResultTypeDeduce<T_arg1,T_arg2,T_arg3>::Type>(
                    this->m_value1.template operator ()<
                    typename QEXTTypeTrait<T_arg1>::Pass,
                    typename QEXTTypeTrait<T_arg2>::Pass,
                    typename QEXTTypeTrait<T_arg3>::Pass>(arg1, arg2, arg3),
                    this->m_value2.template operator ()<
                    typename QEXTTypeTrait<T_arg1>::Pass,
                    typename QEXTTypeTrait<T_arg2>::Pass,
                    typename QEXTTypeTrait<T_arg3>::Pass>(arg1, arg2, arg3));
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator() (T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) const {
        return this->m_functor.template operator ()<
                typename Value1Type::template ResultTypeDeduce<T_arg1,T_arg2,T_arg3,T_arg4>::Type,
                typename Value2Type::template ResultTypeDeduce<T_arg1,T_arg2,T_arg3,T_arg4>::Type>(
                    this->m_value1.template operator ()<
                    typename QEXTTypeTrait<T_arg1>::Pass,
                    typename QEXTTypeTrait<T_arg2>::Pass,
                    typename QEXTTypeTrait<T_arg3>::Pass,
                    typename QEXTTypeTrait<T_arg4>::Pass>(arg1, arg2, arg3, arg4),
                    this->m_value2.template operator ()<
                    typename QEXTTypeTrait<T_arg1>::Pass,
                    typename QEXTTypeTrait<T_arg2>::Pass,
                    typename QEXTTypeTrait<T_arg3>::Pass,
                    typename QEXTTypeTrait<T_arg4>::Pass>(arg1, arg2, arg3, arg4));
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator() (T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) const {
        return this->m_functor.template operator ()<
                typename Value1Type::template ResultTypeDeduce<T_arg1,T_arg2,T_arg3,T_arg4,T_arg5>::Type,
                typename Value2Type::template ResultTypeDeduce<T_arg1,T_arg2,T_arg3,T_arg4,T_arg5>::Type>(
                    this->m_value1.template operator ()<
                    typename QEXTTypeTrait<T_arg1>::Pass,
                    typename QEXTTypeTrait<T_arg2>::Pass,
                    typename QEXTTypeTrait<T_arg3>::Pass,
                    typename QEXTTypeTrait<T_arg4>::Pass,
                    typename QEXTTypeTrait<T_arg5>::Pass>(arg1, arg2, arg3, arg4, arg5),
                    this->m_value2.template operator ()<
                    typename QEXTTypeTrait<T_arg1>::Pass,
                    typename QEXTTypeTrait<T_arg2>::Pass,
                    typename QEXTTypeTrait<T_arg3>::Pass,
                    typename QEXTTypeTrait<T_arg4>::Pass,
                    typename QEXTTypeTrait<T_arg5>::Pass>(arg1, arg2, arg3, arg4, arg5));
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator() (T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) const {
        return this->m_functor.template operator ()<
                typename Value1Type::template ResultTypeDeduce<T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6>::Type,
                typename Value2Type::template ResultTypeDeduce<T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6>::Type>(
                    this->m_value1.template operator ()<
                    typename QEXTTypeTrait<T_arg1>::Pass,
                    typename QEXTTypeTrait<T_arg2>::Pass,
                    typename QEXTTypeTrait<T_arg3>::Pass,
                    typename QEXTTypeTrait<T_arg4>::Pass,
                    typename QEXTTypeTrait<T_arg5>::Pass,
                    typename QEXTTypeTrait<T_arg6>::Pass>(arg1, arg2, arg3, arg4, arg5, arg6),
                    this->m_value2.template operator ()<
                    typename QEXTTypeTrait<T_arg1>::Pass,
                    typename QEXTTypeTrait<T_arg2>::Pass,
                    typename QEXTTypeTrait<T_arg3>::Pass,
                    typename QEXTTypeTrait<T_arg4>::Pass,
                    typename QEXTTypeTrait<T_arg5>::Pass,
                    typename QEXTTypeTrait<T_arg6>::Pass>(arg1, arg2, arg3, arg4, arg5, arg6));
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type
    operator() (T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7) const {
        return this->m_functor.template operator ()<
                typename Value1Type::template ResultTypeDeduce<T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6,T_arg7>::Type,
                typename Value2Type::template ResultTypeDeduce<T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6,T_arg7>::Type>(
                    this->m_value1.template operator ()<
                    typename QEXTTypeTrait<T_arg1>::Pass,
                    typename QEXTTypeTrait<T_arg2>::Pass,
                    typename QEXTTypeTrait<T_arg3>::Pass,
                    typename QEXTTypeTrait<T_arg4>::Pass,
                    typename QEXTTypeTrait<T_arg5>::Pass,
                    typename QEXTTypeTrait<T_arg6>::Pass,
                    typename QEXTTypeTrait<T_arg7>::Pass>(arg1, arg2, arg3, arg4, arg5, arg6, arg7),
                    this->m_value2.template operator ()<
                    typename QEXTTypeTrait<T_arg1>::Pass,
                    typename QEXTTypeTrait<T_arg2>::Pass,
                    typename QEXTTypeTrait<T_arg3>::Pass,
                    typename QEXTTypeTrait<T_arg4>::Pass,
                    typename QEXTTypeTrait<T_arg5>::Pass,
                    typename QEXTTypeTrait<T_arg6>::Pass,
                    typename QEXTTypeTrait<T_arg7>::Pass>(arg1, arg2, arg3, arg4, arg5, arg6, arg7));
    }


    QEXTLambdaGroup2(typename QEXTTypeTrait<T_functor>::Take func,
                     typename QEXTTypeTrait<T_type1>::Take arg1,
                     typename QEXTTypeTrait<T_type2>::Take arg2)
        : m_value1(arg1), m_value2(arg2), m_functor(func) {}

    Value1Type m_value1;
    Value2Type m_value2;
    mutable FunctorType m_functor;
};


//template specialization of QEXTVisitor<>::doVisitEach<>(action, functor):
template <typename T_functor, typename T_type1, typename T_type2>
struct QEXTVisitor<QEXTLambdaGroup2<T_functor, T_type1, T_type2> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTLambdaGroup2<T_functor, T_type1, T_type2> &target) {
        qextVisitEach(action, target.m_value1);
        qextVisitEach(action, target.m_value2);
        qextVisitEach(action, target.m_functor);
    }
};

template <typename T_functor, typename T_type1, typename T_type2, typename T_type3>
struct QEXTLambdaGroup3 : public QEXTLambdaBase
{
    typedef typename QEXTFunctorTrait<T_functor>::ResultType    ResultType;
    typedef typename QEXTLambda<T_type1>::LambdaType            Value1Type;
    typedef typename QEXTLambda<T_type2>::LambdaType            Value2Type;
    typedef typename QEXTLambda<T_type3>::LambdaType            Value3Type;
    typedef typename QEXTAdaptorTrait<T_functor>::AdaptorType   FunctorType;


    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ResultTypeDeduce
    {
        typedef typename FunctorType::template ResultTypeDeduce<
        typename Value1Type::template ResultTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<T_arg3>::Pass,
        typename QEXTTypeTrait<T_arg4>::Pass,
        typename QEXTTypeTrait<T_arg5>::Pass,
        typename QEXTTypeTrait<T_arg6>::Pass,
        typename QEXTTypeTrait<T_arg7>::Pass>::Type,
        typename Value2Type::template ResultTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<T_arg3>::Pass,
        typename QEXTTypeTrait<T_arg4>::Pass,
        typename QEXTTypeTrait<T_arg5>::Pass,
        typename QEXTTypeTrait<T_arg6>::Pass,
        typename QEXTTypeTrait<T_arg7>::Pass>::Type,
        typename Value3Type::template ResultTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<T_arg3>::Pass,
        typename QEXTTypeTrait<T_arg4>::Pass,
        typename QEXTTypeTrait<T_arg5>::Pass,
        typename QEXTTypeTrait<T_arg6>::Pass,
        typename QEXTTypeTrait<T_arg7>::Pass>::Type>::Type Type;
    };


    ResultType
    operator ()() const {
        return m_functor(m_value1(), m_value2(), m_value3());
    }

    template <typename T_arg1>
    typename ResultTypeDeduce<T_arg1>::Type
    operator() (T_arg1 arg1) const {
        return this->m_functor.template operator ()<
                typename Value1Type::template ResultTypeDeduce<T_arg1>::Type,
                typename Value2Type::template ResultTypeDeduce<T_arg1>::Type,
                typename Value3Type::template ResultTypeDeduce<T_arg1>::Type>(
                    this->m_value1.template operator ()<
                    typename QEXTTypeTrait<T_arg1>::Pass>(arg1),
                    this->m_value2.template operator ()<
                    typename QEXTTypeTrait<T_arg1>::Pass>(arg1),
                    this->m_value3.template operator ()<
                    typename QEXTTypeTrait<T_arg1>::Pass>(arg1));
    }

    template <typename T_arg1, typename T_arg2>
    typename ResultTypeDeduce<T_arg1, T_arg2>::Type
    operator() (T_arg1 arg1, T_arg2 arg2) const {
        return this->m_functor.template operator ()<
                typename Value1Type::template ResultTypeDeduce<T_arg1,T_arg2>::Type,
                typename Value2Type::template ResultTypeDeduce<T_arg1,T_arg2>::Type,
                typename Value3Type::template ResultTypeDeduce<T_arg1,T_arg2>::Type>(
                    this->m_value1.template operator ()<
                    typename QEXTTypeTrait<T_arg1>::Pass,
                    typename QEXTTypeTrait<T_arg2>::Pass>(arg1, arg2),
                    this->m_value2.template operator ()<
                    typename QEXTTypeTrait<T_arg1>::Pass,
                    typename QEXTTypeTrait<T_arg2>::Pass>(arg1, arg2),
                    this->m_value3.template operator ()<
                    typename QEXTTypeTrait<T_arg1>::Pass,
                    typename QEXTTypeTrait<T_arg2>::Pass>(arg1, arg2));
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3>::Type
    operator() (T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) const {
        return this->m_functor.template operator ()<
                typename Value1Type::template ResultTypeDeduce<T_arg1,T_arg2,T_arg3>::Type,
                typename Value2Type::template ResultTypeDeduce<T_arg1,T_arg2,T_arg3>::Type,
                typename Value3Type::template ResultTypeDeduce<T_arg1,T_arg2,T_arg3>::Type>(
                    this->m_value1.template operator ()<
                    typename QEXTTypeTrait<T_arg1>::Pass,
                    typename QEXTTypeTrait<T_arg2>::Pass,
                    typename QEXTTypeTrait<T_arg3>::Pass>(arg1, arg2, arg3),
                    this->m_value2.template operator ()<
                    typename QEXTTypeTrait<T_arg1>::Pass,
                    typename QEXTTypeTrait<T_arg2>::Pass,
                    typename QEXTTypeTrait<T_arg3>::Pass>(arg1, arg2, arg3),
                    this->m_value3.template operator ()<
                    typename QEXTTypeTrait<T_arg1>::Pass,
                    typename QEXTTypeTrait<T_arg2>::Pass,
                    typename QEXTTypeTrait<T_arg3>::Pass>(arg1, arg2, arg3));
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator() (T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) const {
        return this->m_functor.template operator ()<
                typename Value1Type::template ResultTypeDeduce<T_arg1,T_arg2,T_arg3,T_arg4>::Type,
                typename Value2Type::template ResultTypeDeduce<T_arg1,T_arg2,T_arg3,T_arg4>::Type,
                typename Value3Type::template ResultTypeDeduce<T_arg1,T_arg2,T_arg3,T_arg4>::Type>(
                    this->m_value1.template operator ()<
                    typename QEXTTypeTrait<T_arg1>::Pass,
                    typename QEXTTypeTrait<T_arg2>::Pass,
                    typename QEXTTypeTrait<T_arg3>::Pass,
                    typename QEXTTypeTrait<T_arg4>::Pass>(arg1, arg2, arg3, arg4),
                    this->m_value2.template operator ()<
                    typename QEXTTypeTrait<T_arg1>::Pass,
                    typename QEXTTypeTrait<T_arg2>::Pass,
                    typename QEXTTypeTrait<T_arg3>::Pass,
                    typename QEXTTypeTrait<T_arg4>::Pass>(arg1, arg2, arg3, arg4),
                    this->m_value3.template operator ()<
                    typename QEXTTypeTrait<T_arg1>::Pass,
                    typename QEXTTypeTrait<T_arg2>::Pass,
                    typename QEXTTypeTrait<T_arg3>::Pass,
                    typename QEXTTypeTrait<T_arg4>::Pass>(arg1, arg2, arg3, arg4));
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator() (T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) const {
        return this->m_functor.template operator ()<
                typename Value1Type::template ResultTypeDeduce<T_arg1,T_arg2,T_arg3,T_arg4,T_arg5>::Type,
                typename Value2Type::template ResultTypeDeduce<T_arg1,T_arg2,T_arg3,T_arg4,T_arg5>::Type,
                typename Value3Type::template ResultTypeDeduce<T_arg1,T_arg2,T_arg3,T_arg4,T_arg5>::Type>(
                    this->m_value1.template operator ()<
                    typename QEXTTypeTrait<T_arg1>::Pass,
                    typename QEXTTypeTrait<T_arg2>::Pass,
                    typename QEXTTypeTrait<T_arg3>::Pass,
                    typename QEXTTypeTrait<T_arg4>::Pass,
                    typename QEXTTypeTrait<T_arg5>::Pass>(arg1, arg2, arg3, arg4, arg5),
                    this->m_value2.template operator ()<
                    typename QEXTTypeTrait<T_arg1>::Pass,
                    typename QEXTTypeTrait<T_arg2>::Pass,
                    typename QEXTTypeTrait<T_arg3>::Pass,
                    typename QEXTTypeTrait<T_arg4>::Pass,
                    typename QEXTTypeTrait<T_arg5>::Pass>(arg1, arg2, arg3, arg4, arg5),
                    this->m_value3.template operator ()<
                    typename QEXTTypeTrait<T_arg1>::Pass,
                    typename QEXTTypeTrait<T_arg2>::Pass,
                    typename QEXTTypeTrait<T_arg3>::Pass,
                    typename QEXTTypeTrait<T_arg4>::Pass,
                    typename QEXTTypeTrait<T_arg5>::Pass>(arg1, arg2, arg3, arg4, arg5));
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator() (T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) const {
        return this->m_functor.template operator ()<
                typename Value1Type::template ResultTypeDeduce<T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6>::Type,
                typename Value2Type::template ResultTypeDeduce<T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6>::Type,
                typename Value3Type::template ResultTypeDeduce<T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6>::Type>(
                    this->m_value1.template operator ()<
                    typename QEXTTypeTrait<T_arg1>::Pass,
                    typename QEXTTypeTrait<T_arg2>::Pass,
                    typename QEXTTypeTrait<T_arg3>::Pass,
                    typename QEXTTypeTrait<T_arg4>::Pass,
                    typename QEXTTypeTrait<T_arg5>::Pass,
                    typename QEXTTypeTrait<T_arg6>::Pass>(arg1, arg2, arg3, arg4, arg5, arg6),
                    this->m_value2.template operator ()<
                    typename QEXTTypeTrait<T_arg1>::Pass,
                    typename QEXTTypeTrait<T_arg2>::Pass,
                    typename QEXTTypeTrait<T_arg3>::Pass,
                    typename QEXTTypeTrait<T_arg4>::Pass,
                    typename QEXTTypeTrait<T_arg5>::Pass,
                    typename QEXTTypeTrait<T_arg6>::Pass>(arg1, arg2, arg3, arg4, arg5, arg6),
                    this->m_value3.template operator ()<
                    typename QEXTTypeTrait<T_arg1>::Pass,
                    typename QEXTTypeTrait<T_arg2>::Pass,
                    typename QEXTTypeTrait<T_arg3>::Pass,
                    typename QEXTTypeTrait<T_arg4>::Pass,
                    typename QEXTTypeTrait<T_arg5>::Pass,
                    typename QEXTTypeTrait<T_arg6>::Pass>(arg1, arg2, arg3, arg4, arg5, arg6));
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type
    operator() (T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7) const {
        return this->m_functor.template operator ()<
                typename Value1Type::template ResultTypeDeduce<T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6,T_arg7>::Type,
                typename Value2Type::template ResultTypeDeduce<T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6,T_arg7>::Type,
                typename Value3Type::template ResultTypeDeduce<T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6,T_arg7>::Type>(
                    this->m_value1.template operator ()<
                    typename QEXTTypeTrait<T_arg1>::Pass,
                    typename QEXTTypeTrait<T_arg2>::Pass,
                    typename QEXTTypeTrait<T_arg3>::Pass,
                    typename QEXTTypeTrait<T_arg4>::Pass,
                    typename QEXTTypeTrait<T_arg5>::Pass,
                    typename QEXTTypeTrait<T_arg6>::Pass,
                    typename QEXTTypeTrait<T_arg7>::Pass>(arg1, arg2, arg3, arg4, arg5, arg6, arg7),
                    this->m_value2.template operator ()<
                    typename QEXTTypeTrait<T_arg1>::Pass,
                    typename QEXTTypeTrait<T_arg2>::Pass,
                    typename QEXTTypeTrait<T_arg3>::Pass,
                    typename QEXTTypeTrait<T_arg4>::Pass,
                    typename QEXTTypeTrait<T_arg5>::Pass,
                    typename QEXTTypeTrait<T_arg6>::Pass,
                    typename QEXTTypeTrait<T_arg7>::Pass>(arg1, arg2, arg3, arg4, arg5, arg6, arg7),
                    this->m_value3.template operator ()<
                    typename QEXTTypeTrait<T_arg1>::Pass,
                    typename QEXTTypeTrait<T_arg2>::Pass,
                    typename QEXTTypeTrait<T_arg3>::Pass,
                    typename QEXTTypeTrait<T_arg4>::Pass,
                    typename QEXTTypeTrait<T_arg5>::Pass,
                    typename QEXTTypeTrait<T_arg6>::Pass,
                    typename QEXTTypeTrait<T_arg7>::Pass>(arg1, arg2, arg3, arg4, arg5, arg6, arg7));
    }


    QEXTLambdaGroup3(typename QEXTTypeTrait<T_functor>::Take func,
                     typename QEXTTypeTrait<T_type1>::Take arg1,
                     typename QEXTTypeTrait<T_type2>::Take arg2,
                     typename QEXTTypeTrait<T_type3>::Take arg3)
        : m_value1(arg1), m_value2(arg2), m_value3(arg3), m_functor(func) {}

    Value1Type m_value1;
    Value2Type m_value2;
    Value3Type m_value3;
    mutable FunctorType m_functor;
};


//template specialization of QEXTVisitor<>::doVisitEach<>(action, functor):
template <typename T_functor, typename T_type1, typename T_type2, typename T_type3>
struct QEXTVisitor<QEXTLambdaGroup3<T_functor, T_type1, T_type2, T_type3> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTLambdaGroup3<T_functor, T_type1, T_type2, T_type3> &target) {
        qextVisitEach(action, target.m_value1);
        qextVisitEach(action, target.m_value2);
        qextVisitEach(action, target.m_value3);
        qextVisitEach(action, target.m_functor);
    }
};

template <typename T_functor, typename T_type1>
QEXTLambda<LambdaGroup1<T_functor, typename QEXTUnwrapReference<T_type1>::Type> >
qextLambdaGroup(const T_functor &func, T_type1 arg1) {
    typedef LambdaGroup1<T_functor, typename QEXTUnwrapReference<T_type1>::Type> T_lambda;
    return QEXTLambda<T_lambda>(T_lambda(func, arg1));
}

template <typename T_functor, typename T_type1, typename T_type2>
QEXTLambda<QEXTLambdaGroup2<T_functor, typename QEXTUnwrapReference<T_type1>::Type, typename QEXTUnwrapReference<T_type2>::Type> >
qextLambdaGroup(const T_functor &func, T_type1 arg1, T_type2 arg2) {
    typedef QEXTLambdaGroup2<T_functor, typename QEXTUnwrapReference<T_type1>::Type, typename QEXTUnwrapReference<T_type2>::Type> T_lambda;
    return QEXTLambda<T_lambda>(T_lambda(func, arg1, arg2));
}

template <typename T_functor, typename T_type1, typename T_type2, typename T_type3>
QEXTLambda<QEXTLambdaGroup3<T_functor, typename QEXTUnwrapReference<T_type1>::Type, typename QEXTUnwrapReference<T_type2>::Type, typename QEXTUnwrapReference<T_type3>::Type> >
qextLambdaGroup(const T_functor &func, T_type1 arg1, T_type2 arg2, T_type3 arg3) {
    typedef QEXTLambdaGroup3<T_functor, typename QEXTUnwrapReference<T_type1>::Type, typename QEXTUnwrapReference<T_type2>::Type, typename QEXTUnwrapReference<T_type3>::Type> T_lambda;
    return QEXTLambda<T_lambda>(T_lambda(func, arg1, arg2, arg3));
}


#endif // QEXTLAMBDAGROUP_H
