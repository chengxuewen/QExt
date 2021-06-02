#ifndef QEXTLAMBDAGROUP_H
#define QEXTLAMBDAGROUP_H

#include <qextlambdabase.h>
#include <qextfunctortrait.h>
#include <qextadaptortrait.h>


/** @defgroup group qextLambdaGroup()
 * qextLambdaGroup() alters an arbitrary functor by rebuilding its arguments from one or more lambda expressions.
 * For each parameter that should be passed to the wrapped functor, one lambda expression
 * has to be passed into qextLambdaGroup(). Lambda selectors can be used as placeholders for the
 * arguments passed into the new functor. Arguments that don't have a placeholder in one
 * of the lambda expressions are dropped.
 *
 * If you have a C++11 compiler, a C++11 lambda expression and/or %std::bind() is
 * often a good alternative to qextLambdaGroup(). Such alternatives are shown in the
 * following examples, marked with the comment <tt>//C++11</tt>.
 *
 * @par Examples:
 * @code
 * void foo(int, int);
 * int bar(int);
 * // argument binding ...
 * qextLambdaGroup(&foo,10,qextLambdaSelectors::_1)(20); //fixes the first argument and calls foo(10,20)
 * std::bind(&foo, 10, std::placeholders::_1)(20); //C++11
 * qextLambdaGroup(&foo,qextLambdaSelectors::_1,30)(40); //fixes the second argument and calls foo(40,30)
 * std::bind(&foo, std::placeholders::_1, 30)(40); //C++11
 * // argument reordering ...
 * qextLambdaGroup(&foo,qextLambdaSelectors::_2,qextLambdaSelectors::_1)(1,2); //calls foo(2,1)
 * std::bind(&foo, std::placeholders::_2, std::placeholders::_1)(1,2); //C++11
 * // argument hiding ...
 * qextLambdaGroup(&foo,qextLambdaSelectors::_1,qextLambdaSelectors::_2)(1,2,3); //calls foo(1,2)
 * std::bind(&foo, std::placeholders::_1, std::placeholders::_2)(1,2,3); //C++11
 * // functor composition ...
 * qextLambdaGroup(&foo,qextLambdaSelectors::_1,qextLambdaGroup(&bar,qextLambdaSelectors::_2))(1,2); //calls foo(1,bar(2))
 * std::bind(&foo,  std::placeholders::_1, std::bind(&bar, std::placeholders::_2))(1,2); //C++11
 * // algebraic expressions ...
 * qextLambdaGroup(&foo,qextLambdaSelectors::_1*qextLambdaSelectors::_2,qextLambdaSelectors::_1/qextLambdaSelectors::_2)(6,3); //calls foo(6*3,6/3)
 * [] (int x, int y) { foo(x*y, x/y); }(6,3); //C++11
 * @endcode
 *
 * The functor qextLambdaGroup() returns can be passed into QEXTSignal::connect() directly.
 * A C++11 lambda expression can be passed into QEXTSignal::connect() directly,
 * if either it returns <tt>void</tt>, or you use #QEXT_FUNCTORS_DEDUCE_RESULT_TYPE_WITH_DECLTYPE.
 *
 * @par Example:
 * @code
 * QEXTSignal<void,int,int> some_signal;
 * void foo(int);
 * some_signal.connect(qextLambdaGroup(&foo,qextLambdaSelectors::_2));
 * some_signal.connect([](int, int y) { foo(y); }); //C++11
 * @endcode
 *
 * Like in qextBindFunctor(), you can bind references to functors by passing the objects
 * through the qextReferenceWrapper() helper function.
 *
 * @par Example:
 * @code
 * int some_int;
 * QEXTSignal<void> some_signal;
 * void foo(int&);
 * some_signal.connect(qextLambdaGroup(&foo,qextReferenceWrapper(some_int)));
 * some_signal.connect([&some_int](){ foo(some_int); }); //C++11
 * @endcode
 *
 * If you bind an object of a QEXTTrackable derived type to a functor
 * by reference, a slot assigned to the group adaptor is cleared automatically
 * when the object goes out of scope.
 *
 * If you bind an object of a QEXTTrackable derived type to a C++11 lambda expression
 * by reference, a slot assigned to the lambda expression is cleared automatically
 * when the object goes out of scope only if you use qextTrackObjectFunctor().
 *
 * @par Example:
 * @code
 * struct bar : public QEXTTrackable {} some_bar;
 * QEXTSignal<void> some_signal;
 * void foo(bar&);
 * some_signal.connect(qextLambdaGroup(&foo,qextReferenceWrapper(some_bar)));
 *   // disconnected automatically if some_bar goes out of scope
 * some_signal.connect([&some_bar](){ foo(some_bar); }); //C++11
 *   // NOT disconnected automatically if some_bar goes out of scope
 * some_signal.connect(qextTrackObjectFunctor([&some_bar](){ foo(some_bar); }, some_bar)); //C++11
 *   // disconnected automatically if some_bar goes out of scope
 * @endcode
 *
 * @deprecated Use C++11 lambda expressions or %std::bind() instead.
 *
 * @ingroup adaptors lambdas
 */


/** QEXTLambdaGroup1 wraps a functor and rebuilds its arguments from 1 lambda expressions.
 * Use the convenience function qextLambdaGroup() to create an instance of QEXTLambdaGroup1.
 *
 * @deprecated Use C++11 lambda expressions or %std::bind() instead.
 *
 * @ingroup qextLambdas
 */
template <typename T_functor, typename T_type1>
struct QEXTLambdaGroup1 : public QEXTLambdaBase
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


    QEXTLambdaGroup1(typename QEXTTypeTrait<T_functor>::Take func, typename QEXTTypeTrait<T_type1>::Take arg1)
        : m_value1(arg1), m_functor(func) {}

    Value1Type m_value1;
    mutable FunctorType m_functor;
};


//template specialization of QEXTVisitor<>::doVisitEach<>(action, functor):
template <typename T_functor, typename T_type1>
struct QEXTVisitor<QEXTLambdaGroup1<T_functor, T_type1> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTLambdaGroup1<T_functor, T_type1> &target) {
        qextVisitEach(action, target.m_value1);
        qextVisitEach(action, target.m_functor);
    }
};

/** QEXTLambdaGroup2 wraps a functor and rebuilds its arguments from 2 lambda expressions.
 * Use the convenience function qextLambdaGroup() to create an instance of QEXTLambdaGroup2.
 *
 * @deprecated Use C++11 lambda expressions or %std::bind() instead.
 *
 * @ingroup qextLambdas
 */
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

/** QEXTLambdaGroup3 wraps a functor and rebuilds its arguments from 3 lambda expressions.
 * Use the convenience function qextLambdaGroup() to create an instance of QEXTLambdaGroup3.
 *
 * @deprecated Use C++11 lambda expressions or %std::bind() instead.
 *
 * @ingroup qextLambdas
 */
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

/** Alters an arbitrary functor by rebuilding its arguments from 1 lambda expressions.
 *
 * @deprecated Use C++11 lambda expressions or %std::bind() instead.
 *
 * @ingroup qextLambdas
 */
template <typename T_functor, typename T_type1>
QEXTLambda<QEXTLambdaGroup1<T_functor, typename QEXTUnwrapReference<T_type1>::Type> >
qextLambdaGroup(const T_functor &func, T_type1 arg1) {
    typedef QEXTLambdaGroup1<T_functor, typename QEXTUnwrapReference<T_type1>::Type> T_lambda;
    return QEXTLambda<T_lambda>(T_lambda(func, arg1));
}

/** Alters an arbitrary functor by rebuilding its arguments from 2 lambda expressions.
 *
 * @deprecated Use C++11 lambda expressions or %std::bind() instead.
 *
 * @ingroup qextLambdas
 */
template <typename T_functor, typename T_type1, typename T_type2>
QEXTLambda<QEXTLambdaGroup2<T_functor, typename QEXTUnwrapReference<T_type1>::Type, typename QEXTUnwrapReference<T_type2>::Type> >
qextLambdaGroup(const T_functor &func, T_type1 arg1, T_type2 arg2) {
    typedef QEXTLambdaGroup2<T_functor, typename QEXTUnwrapReference<T_type1>::Type, typename QEXTUnwrapReference<T_type2>::Type> T_lambda;
    return QEXTLambda<T_lambda>(T_lambda(func, arg1, arg2));
}

/** Alters an arbitrary functor by rebuilding its arguments from 3 lambda expressions.
 *
 * @deprecated Use C++11 lambda expressions or %std::bind() instead.
 *
 * @ingroup qextLambdas
 */
template <typename T_functor, typename T_type1, typename T_type2, typename T_type3>
QEXTLambda<QEXTLambdaGroup3<T_functor, typename QEXTUnwrapReference<T_type1>::Type, typename QEXTUnwrapReference<T_type2>::Type, typename QEXTUnwrapReference<T_type3>::Type> >
qextLambdaGroup(const T_functor &func, T_type1 arg1, T_type2 arg2, T_type3 arg3) {
    typedef QEXTLambdaGroup3<T_functor, typename QEXTUnwrapReference<T_type1>::Type, typename QEXTUnwrapReference<T_type2>::Type, typename QEXTUnwrapReference<T_type3>::Type> T_lambda;
    return QEXTLambda<T_lambda>(T_lambda(func, arg1, arg2, arg3));
}


#endif // QEXTLAMBDAGROUP_H
