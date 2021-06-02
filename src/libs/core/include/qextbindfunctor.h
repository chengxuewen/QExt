#ifndef QEXTBINDFUNCTOR_H
#define QEXTBINDFUNCTOR_H

#include <qextadaptortrait.h>
#include <qextboundargument.h>


namespace qextinternal {

template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
struct QEXTCountVoid
{
    static const int value = 0;
};

template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
struct QEXTCountVoid<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, void>
{
    static const int value = 1;
};

template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
struct QEXTCountVoid<T_arg1, T_arg2, T_arg3, T_arg4,T_arg5, void, void>
{
    static const int value = 2;
};

template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
struct QEXTCountVoid<T_arg1, T_arg2, T_arg3, T_arg4, void, void, void>
{
    static const int value = 3;
};

template <typename T_arg1, typename T_arg2,class T_arg3>
struct QEXTCountVoid<T_arg1, T_arg2, T_arg3, void, void, void, void>
{
    static const int value = 4;
};

template <typename T_arg1, typename T_arg2>
struct QEXTCountVoid<T_arg1, T_arg2, void, void, void, void, void>
{
    static const int value = 5;
};

template <typename T_arg1>
struct QEXTCountVoid<T_arg1, void, void, void, void, void, void>
{
    static const int value = 6;
};

template <>
struct QEXTCountVoid<void, void, void, void, void, void, void>
{
    static const int value = 7;
};

} /* namespace qextinternal */



/** @defgroup qextBindFunctor qextBindFunctor(), bind_return()
 * qextBindFunctor() alters an arbitrary functor by fixing arguments to certain values.
 * Up to 7 arguments can be bound at a time.
 * For single argument binding, overloads of qextBindFunctor() are provided that let you
 * specify the zero-based position of the argument to fix with the first template parameter.
 * (A value of @p -1 fixes the last argument so qextBindFunctor<-1>() gives the same result as qextBindFunctor().)
 * The types of the arguments can optionally be specified if not deduced.
 *
 * @par Examples:
 * @code
 * void foo(int, int, int);
 * // single argument binding ...
 * qextBindFunctor(&foo,1)(2,3);     //fixes the last (third) argument and calls foo(2,3,1)
 * qextBindFunctor<-1>(&foo,1)(2,3); //same as qextBindFunctor(&foo,1)(2,3) (calls foo(2,3,1))
 * qextBindFunctor<0>(&foo,1)(2,3);  //fixes the first argument and calls foo(1,2,3)
 * qextBindFunctor<1>(&foo,1)(2,3);  //fixes the second argument and calls foo(2,1,3)
 * qextBindFunctor<2>(&foo,1)(2,3);  //fixes the third argument and calls foo(2,3,1)
 * // multi argument binding ...
 * qextBindFunctor(&foo,1,2)(3);     //fixes the last two arguments and calls foo(3,1,2)
 * qextBindFunctor(&foo,1,2,3)();    //fixes all three arguments and calls foo(1,2,3)
 * @endcode
 *
 * The functor qextBindFunctor() returns can be passed into
 * QEXTSignal::connect() directly.
 *
 * @par Example:
 * @code
 * QEXTSignal<void> some_signal;
 * void foo(int);
 * some_signal.connect(qextBindFunctor(&foo,1));
 * @endcode
 *
 * qextBindReturnFunctor() alters an arbitrary functor by
 * fixing its return value to a certain value.
 *
 * @par Example:
 * @code
 * void foo();
 * std::cout << qextBindReturnFunctor(&foo, 5)(); // calls foo() and returns 5
 * @endcode
 *
 * You can qextBindFunctor references to functors by passing the objects through
 * the qextReferenceWrapper() helper function.
 *
 * @par Example:
 * @code
 * int some_int;
 * QEXTSignal<void> some_signal;
 * void foo(int&);
 * some_signal.connect(qextBindFunctor(&foo, qextReferenceWrapper(some_int)));
 * @endcode
 *
 * If you qextBindFunctor an object of a QEXTTrackable derived type to a functor
 * by reference, a slot assigned to the qextBindFunctor adaptor is cleared automatically
 * when the object goes out of scope.
 *
 * @par Example:
 * @code
 * struct bar : public QEXTTrackable {} some_bar;
 * QEXTSignal<void> some_signal;
 * void foo(bar&);
 * some_signal.connect(qextBindFunctor(&foo,qextReferenceWrapper(some_bar)));
 *   // disconnected automatically if some_bar goes out of scope
 * @endcode
 *
 * For a more powerful version of this functionality see the lambda
 * library adaptor qextLambdaGroup() which can qextBindFunctor, hide and reorder
 * arguments arbitrarily. Although qextLambdaGroup() is more flexible,
 * qextBindFunctor() provides a means of binding parameters when the total
 * number of parameters called is variable.
 *
 * @ingroup adaptors
 */



/** Adaptor that binds an argument to the wrapped functor.
 * Use the convenience function qextBindFunctor() to create an instance of qextBindFunctor.
 *
 * The following template arguments are used:
 * - @e I_location Zero-based position of the argument to fix (@p -1 for the last argument).
 * - @e T_type1 Type of the 1st bound argument.
 * - @e T_type2 Type of the 2nd bound argument.
 * - @e T_type3 Type of the 3rd bound argument.
 * - @e T_type4 Type of the 4th bound argument.
 * - @e T_type5 Type of the 5th bound argument.
 * - @e T_type6 Type of the 6th bound argument.
 * - @e T_type7 Type of the 7th bound argument.
 * - @e T_functor Type of the functor to wrap.
 *
 * @ingroup qextBindFunctor
 */
template <int I_location, typename T_functor,
          typename T_type1 = QEXTNil, typename T_type2 = QEXTNil, typename T_type3 = QEXTNil,
          typename T_type4 = QEXTNil, typename T_type5 = QEXTNil, typename T_type6 = QEXTNil, typename T_type7 = QEXTNil> struct QEXTBindFunctor;


/** Adaptor that binds an argument to the wrapped functor.
 * This template specialization fixes the 1st argument of the wrapped functor.
 *
 * @ingroup qextBindFunctor
 */
template <typename T_functor, typename T_bound>
struct QEXTBindFunctor<0, T_functor, T_bound, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil> : public QEXTAdapts<T_functor>
{
    typedef typename QEXTAdapts<T_functor>::AdaptorType AdaptorType;

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void,
              typename T_arg7 = void>
    struct ResultTypeDeduce
    {
        typedef typename AdaptorType::template ResultTypeDeduce<
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<T_arg3>::Pass,
        typename QEXTTypeTrait<T_arg4>::Pass,
        typename QEXTTypeTrait<T_arg5>::Pass,
        typename QEXTTypeTrait<T_arg6>::Pass>::Type Type;
    };
    typedef typename AdaptorType::ResultType  ResultType;

    /** Invokes the wrapped functor passing on the bound argument only.
     * @return The return value of the functor invocation.
     */
    ResultType operator()() {
        //Note: The AIX compiler sometimes gives linker errors if we do not define this in the class.
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass>
                (m_bound.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 1st argument.
     * @param arg1 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1>
    typename ResultTypeDeduce<T_arg1>::Type
    operator()(T_arg1 arg1) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
                typename QEXTTypeTrait<T_arg1>::Pass>
                (m_bound.invoke(), arg1);
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 1st argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2>
    typename ResultTypeDeduce<T_arg1, T_arg2>::Type
    operator()(T_arg1 arg1, T_arg2 arg2) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass>
                (m_bound.invoke(), arg1, arg2);
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 1st argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass>
                (m_bound.invoke(), arg1, arg2, arg3);
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 1st argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass>
                (m_bound.invoke(), arg1, arg2, arg3, arg4);
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 1st argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass>
                (m_bound.invoke(), arg1, arg2, arg3, arg4, arg5);
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 1st argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @param arg6 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass,
                typename QEXTTypeTrait<T_arg6>::Pass>
                (m_bound.invoke(), arg1, arg2, arg3, arg4, arg5, arg6);
    }

    /** Constructs a bind_functor object that binds an argument to the passed functor.
     * @param func Functor to invoke from operator()().
     * @param bound Argument to qextBindFunctor to the functor.
     */
    QEXTBindFunctor(typename QEXTTypeTrait<T_functor>::Take func,
                    typename QEXTTypeTrait<T_bound>::Take bound)
        : QEXTAdapts<T_functor>(func), m_bound(bound) {}

    // The argument bound to the functor.
    QEXTBoundArgument<T_bound> m_bound;
};

/** Adaptor that binds an argument to the wrapped functor.
 * This template specialization fixes the 2nd argument of the wrapped functor.
 *
 * @ingroup qextBindFunctor
 */
template <typename T_functor, typename T_bound>
struct QEXTBindFunctor<1, T_functor, T_bound, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil> : public QEXTAdapts<T_functor>
{
    typedef typename QEXTAdapts<T_functor>::AdaptorType AdaptorType;

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ResultTypeDeduce
    {
        typedef typename AdaptorType::template ResultTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<T_arg3>::Pass,
        typename QEXTTypeTrait<T_arg4>::Pass,
        typename QEXTTypeTrait<T_arg5>::Pass,
        typename QEXTTypeTrait<T_arg6>::Pass>::Type Type;
    };
    typedef typename AdaptorType::ResultType  ResultType;


    /** Invokes the wrapped functor passing on the bound argument only.
     * @return The return value of the functor invocation.
     */
    ResultType
    operator()() {
        //Note: The AIX compiler sometimes gives linker errors if we do not define this in the class.
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass>
                (m_bound.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 2nd argument.
     * @param arg1 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1>
    typename ResultTypeDeduce<T_arg1>::Type
    operator()(T_arg1 arg1) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass>
                (arg1, m_bound.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 2nd argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2>
    typename ResultTypeDeduce<T_arg1, T_arg2>::Type
    operator()(T_arg1 arg1, T_arg2 arg2) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass>
                (arg1, m_bound.invoke(), arg2);
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 2nd argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass>
                (arg1, m_bound.invoke(), arg2, arg3);
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 2nd argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass>
                (arg1, m_bound.invoke(), arg2, arg3, arg4);
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 2nd argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass>
                (arg1, m_bound.invoke(), arg2, arg3, arg4, arg5);
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 2nd argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @param arg6 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass,
                typename QEXTTypeTrait<T_arg6>::Pass>
                (arg1, m_bound.invoke(), arg2, arg3, arg4, arg5, arg6);
    }

    /** Constructs a bind_functor object that binds an argument to the passed functor.
     * @param func Functor to invoke from operator()().
     * @param bound Argument to qextBindFunctor to the functor.
     */
    QEXTBindFunctor(typename QEXTTypeTrait<T_functor>::Take func,
                    typename QEXTTypeTrait<T_bound>::Take bound)
        : QEXTAdapts<T_functor>(func), m_bound(bound) {}

    // The argument bound to the functor.
    QEXTBoundArgument<T_bound> m_bound;
};


/** Adaptor that binds an argument to the wrapped functor.
 * This template specialization fixes the 3rd argument of the wrapped functor.
 *
 * @ingroup qextBindFunctor
 */
template <typename T_functor, typename T_bound>
struct QEXTBindFunctor<2, T_functor, T_bound, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil> : public QEXTAdapts<T_functor>
{
    typedef typename QEXTAdapts<T_functor>::AdaptorType AdaptorType;

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ResultTypeDeduce
    {
        typedef typename AdaptorType::template ResultTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
        typename QEXTTypeTrait<T_arg3>::Pass,
        typename QEXTTypeTrait<T_arg4>::Pass,
        typename QEXTTypeTrait<T_arg5>::Pass,
        typename QEXTTypeTrait<T_arg6>::Pass>::Type Type;
    };
    typedef typename AdaptorType::ResultType  ResultType;

    /** Invokes the wrapped functor passing on the bound argument only.
     * @return The return value of the functor invocation.
     */
    ResultType
    operator()() {
        //Note: The AIX compiler sometimes gives linker errors if we do not define this in the class.
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass>
                (m_bound.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 3rd argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2>
    typename ResultTypeDeduce<T_arg1, T_arg2>::Type
    operator()(T_arg1 arg1, T_arg2 arg2) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass>
                (arg1, arg2, m_bound.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 3rd argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass>
                (arg1, arg2, m_bound.invoke(), arg3);
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 3rd argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass>
                (arg1, arg2, m_bound.invoke(), arg3, arg4);
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 3rd argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass>
                (arg1, arg2, m_bound.invoke(), arg3, arg4, arg5);
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 3rd argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @param arg6 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass,
                typename QEXTTypeTrait<T_arg6>::Pass>
                (arg1, arg2, m_bound.invoke(), arg3, arg4, arg5, arg6);
    }

    /** Constructs a bind_functor object that binds an argument to the passed functor.
     * @param func Functor to invoke from operator()().
     * @param bound Argument to qextBindFunctor to the functor.
     */
    QEXTBindFunctor(typename QEXTTypeTrait<T_functor>::Take func, typename QEXTTypeTrait<T_bound>::Take bound)
        : QEXTAdapts<T_functor>(func), m_bound(bound) {}

    // The argument bound to the functor.
    QEXTBoundArgument<T_bound> m_bound;
};


/** Adaptor that binds an argument to the wrapped functor.
 * This template specialization fixes the 4th argument of the wrapped functor.
 *
 * @ingroup qextBindFunctor
 */
template <typename T_functor, typename T_bound>
struct QEXTBindFunctor<3, T_functor, T_bound, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil> : public QEXTAdapts<T_functor>
{
    typedef typename QEXTAdapts<T_functor>::AdaptorType AdaptorType;

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ResultTypeDeduce
    {
        typedef typename AdaptorType::template ResultTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<T_arg3>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
        typename QEXTTypeTrait<T_arg4>::Pass,
        typename QEXTTypeTrait<T_arg5>::Pass,
        typename QEXTTypeTrait<T_arg6>::Pass>::Type Type;
    };
    typedef typename AdaptorType::ResultType  ResultType;


    /** Invokes the wrapped functor passing on the bound argument only.
     * @return The return value of the functor invocation.
     */
    ResultType
    operator()() {
        //Note: The AIX compiler sometimes gives linker errors if we do not define this in the class.
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass>
                (m_bound.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 4th argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass>
                (arg1, arg2, arg3, m_bound.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 4th argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass>
                (arg1, arg2, arg3, m_bound.invoke(), arg4);
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 4th argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass>
                (arg1, arg2, arg3, m_bound.invoke(), arg4, arg5);
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 4th argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @param arg6 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass,
                typename QEXTTypeTrait<T_arg6>::Pass>
                (arg1, arg2, arg3, m_bound.invoke(), arg4, arg5, arg6);
    }

    /** Constructs a bind_functor object that binds an argument to the passed functor.
     * @param func Functor to invoke from operator()().
     * @param bound Argument to qextBindFunctor to the functor.
     */
    QEXTBindFunctor(typename QEXTTypeTrait<T_functor>::Take func, typename QEXTTypeTrait<T_bound>::Take bound)
        : QEXTAdapts<T_functor>(func), m_bound(bound) {}

    // The argument bound to the functor.
    QEXTBoundArgument<T_bound> m_bound;
};

/** Adaptor that binds an argument to the wrapped functor.
 * This template specialization fixes the 5th argument of the wrapped functor.
 *
 * @ingroup qextBindFunctor
 */
template <typename T_functor, typename T_bound>
struct QEXTBindFunctor<4, T_functor, T_bound, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil> : public QEXTAdapts<T_functor>
{
    typedef typename QEXTAdapts<T_functor>::AdaptorType AdaptorType;

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ResultTypeDeduce
    {
        typedef typename AdaptorType::template ResultTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<T_arg3>::Pass,
        typename QEXTTypeTrait<T_arg4>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
        typename QEXTTypeTrait<T_arg5>::Pass,
        typename QEXTTypeTrait<T_arg6>::Pass>::Type Type;
    };
    typedef typename AdaptorType::ResultType  ResultType;

    /** Invokes the wrapped functor passing on the bound argument only.
     * @return The return value of the functor invocation.
     */
    ResultType
    operator()() {
        //Note: The AIX compiler sometimes gives linker errors if we do not define this in the class.
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass>
                (m_bound.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 5th argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass>
                (arg1, arg2, arg3, arg4, m_bound.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 5th argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass>
                (arg1, arg2, arg3, arg4, m_bound.invoke(), arg5);
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 5th argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @param arg6 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass,
                typename QEXTTypeTrait<T_arg6>::Pass>
                (arg1, arg2, arg3, arg4, m_bound.invoke(), arg5, arg6);
    }

    /** Constructs a bind_functor object that binds an argument to the passed functor.
     * @param func Functor to invoke from operator()().
     * @param bound Argument to qextBindFunctor to the functor.
     */
    QEXTBindFunctor(typename QEXTTypeTrait<T_functor>::Take func, typename QEXTTypeTrait<T_bound>::Take bound)
        : QEXTAdapts<T_functor>(func), m_bound(bound) {}

    // The argument bound to the functor.
    QEXTBoundArgument<T_bound> m_bound;
};


/** Adaptor that binds an argument to the wrapped functor.
 * This template specialization fixes the 6th argument of the wrapped functor.
 *
 * @ingroup qextBindFunctor
 */
template <typename T_functor, typename T_bound>
struct QEXTBindFunctor<5, T_functor, T_bound, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil> : public QEXTAdapts<T_functor>
{
    typedef typename QEXTAdapts<T_functor>::AdaptorType AdaptorType;

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ResultTypeDeduce
    {
        typedef typename AdaptorType::template ResultTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<T_arg3>::Pass,
        typename QEXTTypeTrait<T_arg4>::Pass,
        typename QEXTTypeTrait<T_arg5>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
        typename QEXTTypeTrait<T_arg6>::Pass>::Type Type;
    };
    typedef typename AdaptorType::ResultType  ResultType;


    /** Invokes the wrapped functor passing on the bound argument only.
     * @return The return value of the functor invocation.
     */
    ResultType
    operator()() {
        //Note: The AIX compiler sometimes gives linker errors if we do not define this in the class.
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass>
                (m_bound.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 6th argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass>
                (arg1, arg2, arg3, arg4, arg5, m_bound.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 6th argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @param arg6 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
                typename QEXTTypeTrait<T_arg6>::Pass>
                (arg1, arg2, arg3, arg4, arg5, m_bound.invoke(), arg6);
    }

    /** Constructs a bind_functor object that binds an argument to the passed functor.
     * @param func Functor to invoke from operator()().
     * @param bound Argument to qextBindFunctor to the functor.
     */
    QEXTBindFunctor(typename QEXTTypeTrait<T_functor>::Take func, typename QEXTTypeTrait<T_bound>::Take bound)
        : QEXTAdapts<T_functor>(func), m_bound(bound) {}

    // The argument bound to the functor.
    QEXTBoundArgument<T_bound> m_bound;
};


/** Adaptor that binds an argument to the wrapped functor.
 * This template specialization fixes the 7th argument of the wrapped functor.
 *
 * @ingroup qextBindFunctor
 */
template <typename T_functor, typename T_bound>
struct QEXTBindFunctor<6, T_functor, T_bound, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil> : public QEXTAdapts<T_functor>
{
    typedef typename QEXTAdapts<T_functor>::AdaptorType AdaptorType;

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ResultTypeDeduce
    {
        typedef typename AdaptorType::template ResultTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<T_arg3>::Pass,
        typename QEXTTypeTrait<T_arg4>::Pass,
        typename QEXTTypeTrait<T_arg5>::Pass,
        typename QEXTTypeTrait<T_arg6>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass>::Type Type;
    };
    typedef typename AdaptorType::ResultType  ResultType;

    /** Invokes the wrapped functor passing on the bound argument only.
     * @return The return value of the functor invocation.
     */
    ResultType
    operator()() {
        //Note: The AIX compiler sometimes gives linker errors if we do not define this in the class.
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass>
                (m_bound.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 7th argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @param arg6 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass,
                typename QEXTTypeTrait<T_arg6>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass>
                (arg1, arg2, arg3, arg4, arg5, arg6, m_bound.invoke());
    }

    /** Constructs a bind_functor object that binds an argument to the passed functor.
     * @param func Functor to invoke from operator()().
     * @param bound Argument to qextBindFunctor to the functor.
     */
    QEXTBindFunctor(typename QEXTTypeTrait<T_functor>::Take func, typename QEXTTypeTrait<T_bound>::Take bound)
        : QEXTAdapts<T_functor>(func), m_bound(bound) {}

    // The argument bound to the functor.
    QEXTBoundArgument<T_bound> m_bound;
};

//template specialization of QEXTVisitor<>::doVisitEach<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for qextBindFunctor performs a functor on the
 * functor and on the object instances stored in the qextBindFunctor object.
 *
 * @ingroup qextBindFunctor
 */
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

/** Adaptor that binds 1 argument(s) to the wrapped functor.
 * This template specialization fixes the last 1 argument(s) of the wrapped functor.
 *
 * @ingroup qextBindFunctor
 */
template <typename T_functor, typename T_type1>
struct QEXTBindFunctor<-1, T_functor, T_type1, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil> : public QEXTAdapts<T_functor>
{
    typedef typename QEXTAdapts<T_functor>::AdaptorType AdaptorType;

    template <int count,
              typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalResultTypeDeduce
    {
        typedef typename AdaptorType::template ResultTypeDeduce<
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
    struct InternalResultTypeDeduce<2, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
    {
        typedef typename AdaptorType::template ResultTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<T_arg3>::Pass,
        typename QEXTTypeTrait<T_arg4>::Pass,
        typename QEXTTypeTrait<T_arg5>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass>::Type Type;
    };

    template <typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalResultTypeDeduce<3, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
    {
        typedef typename AdaptorType::template ResultTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<T_arg3>::Pass,
        typename QEXTTypeTrait<T_arg4>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass>::Type Type;
    };

    template <typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalResultTypeDeduce<4, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
    {
        typedef typename AdaptorType::template ResultTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<T_arg3>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass>::Type Type;
    };

    template <typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalResultTypeDeduce<5, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
    {
        typedef typename AdaptorType::template ResultTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass>::Type Type;
    };

    template <typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalResultTypeDeduce<6, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
    {
        typedef typename AdaptorType::template ResultTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass>::Type Type;
    };

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ResultTypeDeduce
    {
        typedef typename InternalResultTypeDeduce<
        qextinternal::QEXTCountVoid<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::value,
        T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type Type;
    };

    typedef typename AdaptorType::ResultType  ResultType;


    /** Invokes the wrapped functor passing on the bound argument only.
     * @return The return value of the functor invocation.
     */
    ResultType
    operator()() {
        //Note: The AIX compiler sometimes gives linker errors if we do not define this in the class.
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass>
                (m_bound1.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * The last 1 argument(s) are fixed.
     * @param arg1 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1>
    typename ResultTypeDeduce<T_arg1>::Type
    operator()(T_arg1 arg1) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass>
                (arg1, m_bound1.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * The last 1 argument(s) are fixed.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2>
    typename ResultTypeDeduce<T_arg1, T_arg2>::Type
    operator()(T_arg1 arg1, T_arg2 arg2) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass>
                (arg1, arg2, m_bound1.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * The last 1 argument(s) are fixed.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass>
                (arg1, arg2, arg3, m_bound1.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * The last 1 argument(s) are fixed.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass>
                (arg1, arg2, arg3, arg4, m_bound1.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * The last 1 argument(s) are fixed.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass>
                (arg1, arg2, arg3, arg4, arg5, m_bound1.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * The last 1 argument(s) are fixed.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @param arg6 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass,
                typename QEXTTypeTrait<T_arg6>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass>
                (arg1, arg2, arg3, arg4, arg5, arg6, m_bound1.invoke());
    }

    /** Constructs a bind_functor object that binds an argument to the passed functor.
     * @param func Functor to invoke from operator()().
     * @param bound1 Argument to qextBindFunctor to the functor.
     */
    QEXTBindFunctor(typename QEXTTypeTrait<T_functor>::Take func, typename QEXTTypeTrait<T_type1>::Take bound1)
        : QEXTAdapts<T_functor>(func), m_bound1(bound1) {}

    // The argument bound to the functor.
    QEXTBoundArgument<T_type1> m_bound1;
};

//template specialization of QEXTVisitor<>::doVisitEach<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for qextBindFunctor performs a functor on the
 * functor and on the object instances stored in the qextBindFunctor object.
 *
 * @ingroup qextBindFunctor
 */
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


/** Adaptor that binds 2 argument(s) to the wrapped functor.
 * This template specialization fixes the last 2 argument(s) of the wrapped functor.
 *
 * @ingroup qextBindFunctor
 */
template <typename T_functor, typename T_type1, typename T_type2>
struct QEXTBindFunctor<-1, T_functor, T_type1, T_type2, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil> : public QEXTAdapts<T_functor>
{
    typedef typename QEXTAdapts<T_functor>::AdaptorType AdaptorType;

    template <int count,
              typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalResultTypeDeduce
    {
        typedef typename AdaptorType::template ResultTypeDeduce<
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
    struct InternalResultTypeDeduce<3, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
    {
        typedef typename AdaptorType::template ResultTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<T_arg3>::Pass,
        typename QEXTTypeTrait<T_arg4>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass>::Type Type;
    };

    template <typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalResultTypeDeduce<4, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
    { typedef typename AdaptorType::template ResultTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<T_arg3>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass>::Type Type;
    };

    template <typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalResultTypeDeduce<5, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
    {
        typedef typename AdaptorType::template ResultTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass>::Type Type;
    };

    template <typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalResultTypeDeduce<6, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
    {
        typedef typename AdaptorType::template ResultTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass>::Type Type;
    };

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ResultTypeDeduce
    {
        typedef typename InternalResultTypeDeduce<
        qextinternal::QEXTCountVoid<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::value,
        T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type Type;
    };
    typedef typename AdaptorType::ResultType  ResultType;


    /** Invokes the wrapped functor passing on the bound argument only.
     * @return The return value of the functor invocation.
     */
    ResultType
    operator()() {
        //Note: The AIX compiler sometimes gives linker errors if we do not define this in the class.
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass>
                (m_bound1.invoke(), m_bound2.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * The last 2 argument(s) are fixed.
     * @param arg1 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1>
    typename ResultTypeDeduce<T_arg1>::Type
    operator()(T_arg1 arg1) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass>
                (arg1, m_bound1.invoke(), m_bound2.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * The last 2 argument(s) are fixed.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2>
    typename ResultTypeDeduce<T_arg1, T_arg2>::Type
    operator()(T_arg1 arg1, T_arg2 arg2) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass>
                (arg1, arg2, m_bound1.invoke(), m_bound2.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * The last 2 argument(s) are fixed.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass>
                (arg1, arg2, arg3, m_bound1.invoke(), m_bound2.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * The last 2 argument(s) are fixed.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass>
                (arg1, arg2, arg3, arg4, m_bound1.invoke(), m_bound2.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * The last 2 argument(s) are fixed.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass>
                (arg1, arg2, arg3, arg4, arg5, m_bound1.invoke(), m_bound2.invoke());
    }

    /** Constructs a bind_functor object that binds an argument to the passed functor.
     * @param func Functor to invoke from operator()().
     * @param bound1 Argument to qextBindFunctor to the functor.
     * @param bound2 Argument to qextBindFunctor to the functor.
     */
    QEXTBindFunctor(typename QEXTTypeTrait<T_functor>::Take func,
                    typename QEXTTypeTrait<T_type1>::Take bound1,
                    typename QEXTTypeTrait<T_type2>::Take bound2)
        : QEXTAdapts<T_functor>(func), m_bound1(bound1), m_bound2(bound2) {}

    // The argument bound to the functor.
    QEXTBoundArgument<T_type1> m_bound1;
    QEXTBoundArgument<T_type2> m_bound2;
};


//template specialization of QEXTVisitor<>::doVisitEach<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for qextBindFunctor performs a functor on the
 * functor and on the object instances stored in the qextBindFunctor object.
 *
 * @ingroup qextBindFunctor
 */
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


/** Adaptor that binds 3 argument(s) to the wrapped functor.
 * This template specialization fixes the last 3 argument(s) of the wrapped functor.
 *
 * @ingroup qextBindFunctor
 */
template <typename T_functor, typename T_type1, typename T_type2, typename T_type3>
struct QEXTBindFunctor<-1, T_functor, T_type1, T_type2, T_type3, QEXTNil, QEXTNil, QEXTNil, QEXTNil> : public QEXTAdapts<T_functor>
{
    typedef typename QEXTAdapts<T_functor>::AdaptorType AdaptorType;

    template <int count,
              typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalResultTypeDeduce
    {
        typedef typename AdaptorType::template ResultTypeDeduce<
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
    struct InternalResultTypeDeduce<4, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
    {
        typedef typename AdaptorType::template ResultTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<T_arg3>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass>::Type Type;
    };

    template <typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalResultTypeDeduce<5, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
    {
        typedef typename AdaptorType::template ResultTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass>::Type Type;
    };

    template <typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalResultTypeDeduce<6, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
    {
        typedef typename AdaptorType::template ResultTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass>::Type Type;
    };

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ResultTypeDeduce
    {
        typedef typename InternalResultTypeDeduce<
        qextinternal::QEXTCountVoid<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::value,
        T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type Type;
    };
    typedef typename AdaptorType::ResultType  ResultType;

    /** Invokes the wrapped functor passing on the bound argument only.
     * @return The return value of the functor invocation.
     */
    ResultType
    operator()() {
        //Note: The AIX compiler sometimes gives linker errors if we do not define this in the class.
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass>
                (m_bound1.invoke(), m_bound2.invoke(), m_bound3.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * The last 3 argument(s) are fixed.
     * @param arg1 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1>
    typename ResultTypeDeduce<T_arg1>::Type
    operator()(T_arg1 arg1) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass>
                (arg1, m_bound1.invoke(), m_bound2.invoke(), m_bound3.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * The last 3 argument(s) are fixed.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2>
    typename ResultTypeDeduce<T_arg1, T_arg2>::Type
    operator()(T_arg1 arg1, T_arg2 arg2) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass>
                (arg1, arg2, m_bound1.invoke(), m_bound2.invoke(), m_bound3.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * The last 3 argument(s) are fixed.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass>
                (arg1, arg2, arg3, m_bound1.invoke(), m_bound2.invoke(), m_bound3.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * The last 3 argument(s) are fixed.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) {
        return this->m_functor(arg1, arg2, arg3, arg4, m_bound1.invoke(), m_bound2.invoke(), m_bound3.invoke());
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass>
                (arg1, arg2, arg3, arg4, m_bound1.invoke(), m_bound2.invoke(), m_bound3.invoke());
    }

    /** Constructs a bind_functor object that binds an argument to the passed functor.
     * @param func Functor to invoke from operator()().
     * @param bound1 Argument to qextBindFunctor to the functor.
     * @param bound2 Argument to qextBindFunctor to the functor.
     * @param bound3 Argument to qextBindFunctor to the functor.
     */
    QEXTBindFunctor(typename QEXTTypeTrait<T_functor>::Take func,
                    typename QEXTTypeTrait<T_type1>::Take bound1,
                    typename QEXTTypeTrait<T_type2>::Take bound2,
                    typename QEXTTypeTrait<T_type3>::Take bound3)
        : QEXTAdapts<T_functor>(func), m_bound1(bound1), m_bound2(bound2), m_bound3(bound3) {}

    // The argument bound to the functor.
    QEXTBoundArgument<T_type1> m_bound1;
    QEXTBoundArgument<T_type2> m_bound2;
    QEXTBoundArgument<T_type3> m_bound3;
};


//template specialization of QEXTVisitor<>::doVisitEach<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for qextBindFunctor performs a functor on the
 * functor and on the object instances stored in the qextBindFunctor object.
 *
 * @ingroup qextBindFunctor
 */
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


/** Adaptor that binds 4 argument(s) to the wrapped functor.
 * This template specialization fixes the last 4 argument(s) of the wrapped functor.
 *
 * @ingroup qextBindFunctor
 */
template <typename T_functor,
          typename T_type1, typename T_type2, typename T_type3, typename T_type4>
struct QEXTBindFunctor<-1, T_functor, T_type1, T_type2, T_type3, T_type4, QEXTNil, QEXTNil, QEXTNil> : public QEXTAdapts<T_functor>
{
    typedef typename QEXTAdapts<T_functor>::AdaptorType AdaptorType;

    template <int count,
              typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalResultTypeDeduce
    {
        typedef typename AdaptorType::template ResultTypeDeduce<
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
    struct InternalResultTypeDeduce<5, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
    {
        typedef typename AdaptorType::template ResultTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type4>::Type>::Pass>::Type Type;
    };

    template <typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalResultTypeDeduce<6, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
    {
        typedef typename AdaptorType::template ResultTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type4>::Type>::Pass>::Type Type;
    };

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ResultTypeDeduce
    {
        typedef typename InternalResultTypeDeduce<
        qextinternal::QEXTCountVoid<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::value,
        T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type Type;
    };
    typedef typename AdaptorType::ResultType  ResultType;

    /** Invokes the wrapped functor passing on the bound argument only.
     * @return The return value of the functor invocation.
     */
    ResultType
    operator()() {
        //Note: The AIX compiler sometimes gives linker errors if we do not define this in the class.
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type4>::Type>::Pass>
                (m_bound1.invoke(), m_bound2.invoke(), m_bound3.invoke(), m_bound4.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * The last 4 argument(s) are fixed.
     * @param arg1 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1>
    typename ResultTypeDeduce<T_arg1>::Type
    operator()(T_arg1 arg1) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type4>::Type>::Pass>
                (arg1, m_bound1.invoke(), m_bound2.invoke(), m_bound3.invoke(), m_bound4.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * The last 4 argument(s) are fixed.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2>
    typename ResultTypeDeduce<T_arg1, T_arg2>::Type
    operator()(T_arg1 arg1, T_arg2 arg2) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type4>::Type>::Pass>
                (arg1, arg2, m_bound1.invoke(), m_bound2.invoke(), m_bound3.invoke(), m_bound4.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * The last 4 argument(s) are fixed.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type4>::Type>::Pass>
                (arg1, arg2, arg3, m_bound1.invoke(), m_bound2.invoke(), m_bound3.invoke(), m_bound4.invoke());
    }

    /** Constructs a bind_functor object that binds an argument to the passed functor.
     * @param func Functor to invoke from operator()().
     * @param bound1 Argument to qextBindFunctor to the functor.
     * @param bound2 Argument to qextBindFunctor to the functor.
     * @param bound3 Argument to qextBindFunctor to the functor.
     * @param bound4 Argument to qextBindFunctor to the functor.
     */
    QEXTBindFunctor(typename QEXTTypeTrait<T_functor>::Take func,
                    typename QEXTTypeTrait<T_type1>::Take bound1,
                    typename QEXTTypeTrait<T_type2>::Take bound2,
                    typename QEXTTypeTrait<T_type3>::Take bound3,
                    typename QEXTTypeTrait<T_type4>::Take bound4)
        : QEXTAdapts<T_functor>(func), m_bound1(bound1), m_bound2(bound2), m_bound3(bound3), m_bound4(bound4) {}

    // The argument bound to the functor.
    QEXTBoundArgument<T_type1> m_bound1;
    QEXTBoundArgument<T_type2> m_bound2;
    QEXTBoundArgument<T_type3> m_bound3;
    QEXTBoundArgument<T_type4> m_bound4;
};


//template specialization of QEXTVisitor<>::doVisitEach<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for qextBindFunctor performs a functor on the
 * functor and on the object instances stored in the qextBindFunctor object.
 *
 * @ingroup qextBindFunctor
 */
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

/** Adaptor that binds 5 argument(s) to the wrapped functor.
 * This template specialization fixes the last 5 argument(s) of the wrapped functor.
 *
 * @ingroup qextBindFunctor
 */
template <typename T_functor,
          typename T_type1, typename T_type2, typename T_type3, typename T_type4, typename T_type5>
struct QEXTBindFunctor<-1, T_functor, T_type1, T_type2, T_type3, T_type4, T_type5, QEXTNil, QEXTNil> : public QEXTAdapts<T_functor>
{
    typedef typename QEXTAdapts<T_functor>::AdaptorType AdaptorType;

    template <int count,
              typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalResultTypeDeduce
    {
        typedef typename AdaptorType::template ResultTypeDeduce<
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
    struct InternalResultTypeDeduce<6, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
    {
        typedef typename AdaptorType::template ResultTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type4>::Type>::Pass,
        typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type5>::Type>::Pass>::Type Type;
    };

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ResultTypeDeduce
    {
        typedef typename InternalResultTypeDeduce<
        qextinternal::QEXTCountVoid<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::value,
        T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type Type;
    };
    typedef typename AdaptorType::ResultType  ResultType;

    /** Invokes the wrapped functor passing on the bound argument only.
     * @return The return value of the functor invocation.
     */
    ResultType
    operator()() {
        //Note: The AIX compiler sometimes gives linker errors if we do not define this in the class.
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type4>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type5>::Type>::Pass>
                (m_bound1.invoke(), m_bound2.invoke(), m_bound3.invoke(), m_bound4.invoke(), m_bound5.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * The last 5 argument(s) are fixed.
     * @param arg1 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1>
    typename ResultTypeDeduce<T_arg1>::Type
    operator()(T_arg1 arg1) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type4>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type5>::Type>::Pass>
                (arg1, m_bound1.invoke(), m_bound2.invoke(), m_bound3.invoke(), m_bound4.invoke(), m_bound5.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * The last 5 argument(s) are fixed.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2>
    typename ResultTypeDeduce<T_arg1, T_arg2>::Type
    operator()(T_arg1 arg1, T_arg2 arg2) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type4>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type5>::Type>::Pass>
                (arg1, arg2, m_bound1.invoke(), m_bound2.invoke(), m_bound3.invoke(), m_bound4.invoke(), m_bound5.invoke());
    }

    /** Constructs a bind_functor object that binds an argument to the passed functor.
     * @param func Functor to invoke from operator()().
     * @param bound1 Argument to qextBindFunctor to the functor.
     * @param bound2 Argument to qextBindFunctor to the functor.
     * @param bound3 Argument to qextBindFunctor to the functor.
     * @param bound4 Argument to qextBindFunctor to the functor.
     * @param bound5 Argument to qextBindFunctor to the functor.
     */
    QEXTBindFunctor(typename QEXTTypeTrait<T_functor>::Take func,
                    typename QEXTTypeTrait<T_type1>::Take bound1,
                    typename QEXTTypeTrait<T_type2>::Take bound2,
                    typename QEXTTypeTrait<T_type3>::Take bound3,
                    typename QEXTTypeTrait<T_type4>::Take bound4,
                    typename QEXTTypeTrait<T_type5>::Take bound5)
        : QEXTAdapts<T_functor>(func), m_bound1(bound1), m_bound2(bound2), m_bound3(bound3), m_bound4(bound4), m_bound5(bound5) {}

    // The argument bound to the functor.
    QEXTBoundArgument<T_type1> m_bound1;
    QEXTBoundArgument<T_type2> m_bound2;
    QEXTBoundArgument<T_type3> m_bound3;
    QEXTBoundArgument<T_type4> m_bound4;
    QEXTBoundArgument<T_type5> m_bound5;
};


//template specialization of QEXTVisitor<>::doVisitEach<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for qextBindFunctor performs a functor on the
 * functor and on the object instances stored in the qextBindFunctor object.
 *
 * @ingroup qextBindFunctor
 */
template <typename T_functor,
          typename T_type1, typename T_type2, typename T_type3, typename T_type4, typename T_type5>
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


/** Adaptor that binds 6 argument(s) to the wrapped functor.
 * This template specialization fixes the last 6 argument(s) of the wrapped functor.
 *
 * @ingroup qextBindFunctor
 */
template <typename T_functor,
          typename T_type1, typename T_type2, typename T_type3,
          typename T_type4, typename T_type5, typename T_type6>
struct QEXTBindFunctor<-1, T_functor, T_type1, T_type2, T_type3, T_type4, T_type5, T_type6, QEXTNil> : public QEXTAdapts<T_functor>
{
    typedef typename QEXTAdapts<T_functor>::AdaptorType AdaptorType;

    template <int count,
              typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalResultTypeDeduce
    {
        typedef typename AdaptorType::template ResultTypeDeduce<
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
    struct ResultTypeDeduce
    {
        typedef typename InternalResultTypeDeduce<
        qextinternal::QEXTCountVoid<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::value,
        T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type Type;
    };
    typedef typename AdaptorType::ResultType  ResultType;

    /** Invokes the wrapped functor passing on the bound argument only.
     * @return The return value of the functor invocation.
     */
    ResultType
    operator()() {
        //Note: The AIX compiler sometimes gives linker errors if we do not define this in the class.
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type4>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type5>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type6>::Type>::Pass>
                (m_bound1.invoke(), m_bound2.invoke(), m_bound3.invoke(), m_bound4.invoke(), m_bound5.invoke(), m_bound6.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * The last 6 argument(s) are fixed.
     * @param arg1 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1>
    typename ResultTypeDeduce<T_arg1>::Type
    operator()(T_arg1 arg1) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type4>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type5>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type6>::Type>::Pass>
                (arg1, m_bound1.invoke(), m_bound2.invoke(), m_bound3.invoke(), m_bound4.invoke(), m_bound5.invoke(), m_bound6.invoke());
    }

    /** Constructs a bind_functor object that binds an argument to the passed functor.
     * @param func Functor to invoke from operator()().
     * @param bound1 Argument to qextBindFunctor to the functor.
     * @param bound2 Argument to qextBindFunctor to the functor.
     * @param bound3 Argument to qextBindFunctor to the functor.
     * @param bound4 Argument to qextBindFunctor to the functor.
     * @param bound5 Argument to qextBindFunctor to the functor.
     * @param bound6 Argument to qextBindFunctor to the functor.
     */
    QEXTBindFunctor(typename QEXTTypeTrait<T_functor>::Take func,
                    typename QEXTTypeTrait<T_type1>::Take bound1,
                    typename QEXTTypeTrait<T_type2>::Take bound2,
                    typename QEXTTypeTrait<T_type3>::Take bound3,
                    typename QEXTTypeTrait<T_type4>::Take bound4,
                    typename QEXTTypeTrait<T_type5>::Take bound5,
                    typename QEXTTypeTrait<T_type6>::Take bound6)
        : QEXTAdapts<T_functor>(func),
          m_bound1(bound1), m_bound2(bound2), m_bound3(bound3),
          m_bound4(bound4), m_bound5(bound5), m_bound6(bound6) {}

    // The argument bound to the functor.
    QEXTBoundArgument<T_type1> m_bound1;
    QEXTBoundArgument<T_type2> m_bound2;
    QEXTBoundArgument<T_type3> m_bound3;
    QEXTBoundArgument<T_type4> m_bound4;
    QEXTBoundArgument<T_type5> m_bound5;
    QEXTBoundArgument<T_type6> m_bound6;
};


//template specialization of QEXTVisitor<>::doVisitEach<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for qextBindFunctor performs a functor on the
 * functor and on the object instances stored in the qextBindFunctor object.
 *
 * @ingroup qextBindFunctor
 */
template <typename T_functor,
          typename T_type1, typename T_type2, typename T_type3,
          typename T_type4, typename T_type5, typename T_type6>
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


/** Adaptor that binds 7 argument(s) to the wrapped functor.
 * This template specialization fixes the last 7 argument(s) of the wrapped functor.
 *
 * @ingroup qextBindFunctor
 */
template <typename T_functor,
          typename T_type1, typename T_type2, typename T_type3,
          typename T_type4, typename T_type5, typename T_type6, typename T_type7>
struct QEXTBindFunctor<-1, T_functor, T_type1, T_type2, T_type3, T_type4, T_type5, T_type6, T_type7> : public QEXTAdapts<T_functor>
{
    typedef typename QEXTAdapts<T_functor>::AdaptorType AdaptorType;

    template <int count,
              typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalResultTypeDeduce
    {
        typedef typename AdaptorType::template ResultTypeDeduce<
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
    struct ResultTypeDeduce
    {
        typedef typename InternalResultTypeDeduce<
        qextinternal::QEXTCountVoid<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::value,
        T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type Type;
    };
    typedef typename AdaptorType::ResultType  ResultType;

    /** Invokes the wrapped functor passing on the bound argument only.
     * @return The return value of the functor invocation.
     */
    ResultType
    operator()() {
        //Note: The AIX compiler sometimes gives linker errors if we do not define this in the class.
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type4>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type5>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type6>::Type>::Pass,
                typename QEXTTypeTrait<typename QEXTUnwrapReference<T_type7>::Type>::Pass>
                (m_bound1.invoke(), m_bound2.invoke(), m_bound3.invoke(), m_bound4.invoke(), m_bound5.invoke(), m_bound6.invoke(), m_bound7.invoke());
    }


    /** Constructs a bind_functor object that binds an argument to the passed functor.
     * @param func Functor to invoke from operator()().
     * @param bound1 Argument to qextBindFunctor to the functor.
     * @param bound2 Argument to qextBindFunctor to the functor.
     * @param bound3 Argument to qextBindFunctor to the functor.
     * @param bound4 Argument to qextBindFunctor to the functor.
     * @param bound5 Argument to qextBindFunctor to the functor.
     * @param bound6 Argument to qextBindFunctor to the functor.
     * @param bound7 Argument to qextBindFunctor to the functor.
     */
    QEXTBindFunctor(typename QEXTTypeTrait<T_functor>::Take func,
                    typename QEXTTypeTrait<T_type1>::Take bound1,
                    typename QEXTTypeTrait<T_type2>::Take bound2,
                    typename QEXTTypeTrait<T_type3>::Take bound3,
                    typename QEXTTypeTrait<T_type4>::Take bound4,
                    typename QEXTTypeTrait<T_type5>::Take bound5,
                    typename QEXTTypeTrait<T_type6>::Take bound6,
                    typename QEXTTypeTrait<T_type7>::Take bound7)
        : QEXTAdapts<T_functor>(func),
          m_bound1(bound1), m_bound2(bound2), m_bound3(bound3),
          m_bound4(bound4), m_bound5(bound5), m_bound6(bound6), m_bound7(bound7) {}

    // The argument bound to the functor.
    QEXTBoundArgument<T_type1> m_bound1;
    QEXTBoundArgument<T_type2> m_bound2;
    QEXTBoundArgument<T_type3> m_bound3;
    QEXTBoundArgument<T_type4> m_bound4;
    QEXTBoundArgument<T_type5> m_bound5;
    QEXTBoundArgument<T_type6> m_bound6;
    QEXTBoundArgument<T_type7> m_bound7;
};


//template specialization of QEXTVisitor<>::doVisitEach<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for qextBindFunctor performs a functor on the
 * functor and on the object instances stored in the qextBindFunctor object.
 *
 * @ingroup qextBindFunctor
 */
template <typename T_functor,
          typename T_type1, typename T_type2, typename T_type3,
          typename T_type4, typename T_type5, typename T_type6, typename T_type7>
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



/** Creates an adaptor of type qextBindFunctor which binds the passed argument to the passed functor.
 * The optional template argument @e I_location specifies the zero-based
 * position of the argument to be fixed (@p -1 stands for the last argument).
 *
 * @param func Functor that should be wrapped.
 * @param bound1 Argument to qextBindFunctor to @e func.
 * @return Adaptor that executes @e func with the bound argument on invokation.
 *
 * @ingroup qextBindFunctor
 */
template <int I_location, typename T_functor, typename T_type1>
inline QEXTBindFunctor<I_location, T_functor, T_type1>
qextBindFunctor(const T_functor &func, T_type1 bound1) {
    return QEXTBindFunctor<I_location, T_functor, T_type1>(func, bound1);
}


/** Creates an adaptor of type qextBindFunctor which fixes the last 1 argument(s) of the passed functor.
 * This function overload fixes the last 1 argument(s) of @e func.
 *
 * @param func Functor that should be wrapped.
 * @param bound1 Argument to qextBindFunctor to @e func.
 * @return Adaptor that executes func with the bound argument on invokation.
 *
 * @ingroup qextBindFunctor
 */
template <typename T_functor, typename T_type1>
inline QEXTBindFunctor<-1, T_functor, T_type1>
qextBindFunctor(const T_functor &func, T_type1 bound1) {
    return QEXTBindFunctor<-1, T_functor, T_type1>(func, bound1);
}


/** Creates an adaptor of type qextBindFunctor which fixes the last 2 argument(s) of the passed functor.
 * This function overload fixes the last 2 argument(s) of @e func.
 *
 * @param func Functor that should be wrapped.
 * @param bound1 Argument to qextBindFunctor to @e func.
 * @param bound2 Argument to qextBindFunctor to @e func.
 * @return Adaptor that executes func with the bound argument on invokation.
 *
 * @ingroup qextBindFunctor
 */
template <typename T_functor, typename T_type1, typename T_type2>
inline QEXTBindFunctor<-1, T_functor, T_type1, T_type2>
qextBindFunctor(const T_functor &func, T_type1 bound1, T_type2 bound2) {
    return QEXTBindFunctor<-1, T_functor, T_type1, T_type2>(func, bound1, bound2);
}


/** Creates an adaptor of type qextBindFunctor which fixes the last 3 argument(s) of the passed functor.
 * This function overload fixes the last 3 argument(s) of @e func.
 *
 * @param func Functor that should be wrapped.
 * @param bound1 Argument to qextBindFunctor to @e func.
 * @param bound2 Argument to qextBindFunctor to @e func.
 * @param bound3 Argument to qextBindFunctor to @e func.
 * @return Adaptor that executes func with the bound argument on invokation.
 *
 * @ingroup qextBindFunctor
 */
template <typename T_functor, typename T_type1, typename T_type2, typename T_type3>
inline QEXTBindFunctor<-1, T_functor, T_type1, T_type2, T_type3>
qextBindFunctor(const T_functor &func, T_type1 bound1, T_type2 bound2, T_type3 bound3) {
    return QEXTBindFunctor<-1, T_functor, T_type1, T_type2, T_type3>(func, bound1, bound2, bound3);
}


/** Creates an adaptor of type qextBindFunctor which fixes the last 4 argument(s) of the passed functor.
 * This function overload fixes the last 4 argument(s) of @e func.
 *
 * @param func Functor that should be wrapped.
 * @param bound1 Argument to qextBindFunctor to @e func.
 * @param bound2 Argument to qextBindFunctor to @e func.
 * @param bound3 Argument to qextBindFunctor to @e func.
 * @param bound4 Argument to qextBindFunctor to @e func.
 * @return Adaptor that executes func with the bound argument on invokation.
 *
 * @ingroup qextBindFunctor
 */
template <typename T_functor, typename T_type1, typename T_type2, typename T_type3, typename T_type4>
inline QEXTBindFunctor<-1, T_functor, T_type1, T_type2, T_type3, T_type4>
qextBindFunctor(const T_functor &func, T_type1 bound1, T_type2 bound2, T_type3 bound3, T_type4 bound4) {
    return QEXTBindFunctor<-1, T_functor, T_type1, T_type2, T_type3, T_type4>(func, bound1, bound2, bound3, bound4);
}


/** Creates an adaptor of type qextBindFunctor which fixes the last 5 argument(s) of the passed functor.
 * This function overload fixes the last 5 argument(s) of @e func.
 *
 * @param func Functor that should be wrapped.
 * @param bound1 Argument to qextBindFunctor to @e func.
 * @param bound2 Argument to qextBindFunctor to @e func.
 * @param bound3 Argument to qextBindFunctor to @e func.
 * @param bound4 Argument to qextBindFunctor to @e func.
 * @param bound5 Argument to qextBindFunctor to @e func.
 * @return Adaptor that executes func with the bound argument on invokation.
 *
 * @ingroup qextBindFunctor
 */
template <typename T_functor,
          typename T_type1, typename T_type2, typename T_type3, typename T_type4, typename T_type5>
inline QEXTBindFunctor<-1, T_functor, T_type1, T_type2, T_type3, T_type4, T_type5>
qextBindFunctor(const T_functor &func, T_type1 bound1, T_type2 bound2, T_type3 bound3, T_type4 bound4, T_type5 bound5) {
    return QEXTBindFunctor<-1, T_functor, T_type1, T_type2, T_type3, T_type4, T_type5>(func, bound1, bound2, bound3, bound4, bound5);
}


/** Creates an adaptor of type qextBindFunctor which fixes the last 6 argument(s) of the passed functor.
 * This function overload fixes the last 6 argument(s) of @e func.
 *
 * @param func Functor that should be wrapped.
 * @param bound1 Argument to qextBindFunctor to @e func.
 * @param bound2 Argument to qextBindFunctor to @e func.
 * @param bound3 Argument to qextBindFunctor to @e func.
 * @param bound4 Argument to qextBindFunctor to @e func.
 * @param bound5 Argument to qextBindFunctor to @e func.
 * @param bound6 Argument to qextBindFunctor to @e func.
 * @return Adaptor that executes func with the bound argument on invokation.
 *
 * @ingroup qextBindFunctor
 */
template <typename T_functor,
          typename T_type1, typename T_type2, typename T_type3,
          typename T_type4, typename T_type5, typename T_type6>
inline QEXTBindFunctor<-1, T_functor, T_type1, T_type2, T_type3, T_type4, T_type5, T_type6>
qextBindFunctor(const T_functor &func, T_type1 bound1, T_type2 bound2, T_type3 bound3, T_type4 bound4, T_type5 bound5, T_type6 bound6) {
    return QEXTBindFunctor<-1, T_functor, T_type1, T_type2, T_type3, T_type4, T_type5, T_type6>(func, bound1, bound2, bound3, bound4, bound5, bound6);
}


/** Creates an adaptor of type qextBindFunctor which fixes the last 7 argument(s) of the passed functor.
 * This function overload fixes the last 7 argument(s) of @e func.
 *
 * @param func Functor that should be wrapped.
 * @param bound1 Argument to qextBindFunctor to @e func.
 * @param bound2 Argument to qextBindFunctor to @e func.
 * @param bound3 Argument to qextBindFunctor to @e func.
 * @param bound4 Argument to qextBindFunctor to @e func.
 * @param bound5 Argument to qextBindFunctor to @e func.
 * @param bound6 Argument to qextBindFunctor to @e func.
 * @param bound7 Argument to qextBindFunctor to @e func.
 * @return Adaptor that executes func with the bound argument on invokation.
 *
 * @ingroup qextBindFunctor
 */
template <typename T_functor,
          typename T_type1, typename T_type2, typename T_type3,
          typename T_type4, typename T_type5, typename T_type6, typename T_type7>
inline QEXTBindFunctor<-1, T_functor, T_type1, T_type2, T_type3, T_type4, T_type5, T_type6, T_type7>
qextBindFunctor(const T_functor &func, T_type1 bound1, T_type2 bound2, T_type3 bound3, T_type4 bound4, T_type5 bound5, T_type6 bound6, T_type7 bound7) {
    return QEXTBindFunctor<-1, T_functor, T_type1, T_type2, T_type3, T_type4, T_type5, T_type6, T_type7>(func, bound1, bound2, bound3, bound4, bound5, bound6, bound7);
}


#endif // QEXTBINDFUNCTOR_H
