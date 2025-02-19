/****************************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2021 ChengXueWen. Contact: 1398831004@qq.com
** Copyright 2002, The libsigc++ Development Team
**
** License: MIT License
**
** Permission is hereby granted, free of charge, to any person obtaining
** a copy of this software and associated documentation files (the "Software"),
** to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense,
** and/or sell copies of the Software, and to permit persons to whom the
** Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in
** all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
** SOFTWARE.
**
****************************************************************************************************************************/

#ifndef _QEXTBINDFUNCTOR_H
#define _QEXTBINDFUNCTOR_H

#include <qextAdaptorTrait.h>
#include <qextBoundArgument.h>

namespace detail
{
template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
struct QExtCountVoid
{
    static const int value = 0;
};

template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
struct QExtCountVoid<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, void>
{
    static const int value = 1;
};

template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
struct QExtCountVoid<Arg1, Arg2, Arg3, Arg4, Arg5, void, void>
{
    static const int value = 2;
};

template <class Arg1, class Arg2, class Arg3, class Arg4>
struct QExtCountVoid<Arg1, Arg2, Arg3, Arg4, void, void, void>
{
    static const int value = 3;
};

template <class Arg1, class Arg2, class Arg3>
struct QExtCountVoid<Arg1, Arg2, Arg3, void, void, void, void>
{
    static const int value = 4;
};

template <class Arg1, class Arg2>
struct QExtCountVoid<Arg1, Arg2, void, void, void, void, void>
{
    static const int value = 5;
};

template <class Arg1>
struct QExtCountVoid<Arg1, void, void, void, void, void, void>
{
    static const int value = 6;
};

template <>
struct QExtCountVoid<void, void, void, void, void, void, void>
{
    static const int value = 7;
};

} // namespace detail

/**
 * @defgroup qextBindFunctor qextBindFunctor(), bind_return()
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
 * QExtSignal::connect() directly.
 *
 * @par Example:
 * @code
 * QExtSignal<void> some_signal;
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
 * QExtSignal<void> some_signal;
 * void foo(int&);
 * some_signal.connect(qextBindFunctor(&foo, qextReferenceWrapper(some_int)));
 * @endcode
 *
 * If you qextBindFunctor an object of a QObject derived type to a functor
 * by reference, a slot assigned to the qextBindFunctor adaptor is cleared automatically
 * when the object goes out of scope.
 *
 * @par Example:
 * @code
 * struct bar : public QObject {} some_bar;
 * QExtSignal<void> some_signal;
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
 */

/**
 * @brief AdaptorType that binds an argument to the wrapped functor.
 * Use the convenience function qextBindFunctor() to create an instance of qextBindFunctor.
 *
 * The following template arguments are used:
 * - @e I_location Zero-based position of the argument to fix (@p -1 for the last argument).
 * - @e T1 Type of the 1st bound argument.
 * - @e T_type2 Type of the 2nd bound argument.
 * - @e T_type3 Type of the 3rd bound argument.
 * - @e T_type4 Type of the 4th bound argument.
 * - @e T_type5 Type of the 5th bound argument.
 * - @e T_type6 Type of the 6th bound argument.
 * - @e T_type7 Type of the 7th bound argument.
 * - @e Functor Type of the functor to wrap.
 */
template <int I_location,
         class Functor,
         class T1 = QExtNil,
         class T2 = QExtNil,
         class T3 = QExtNil,
         class T4 = QExtNil,
         class T5 = QExtNil,
         class T6 = QExtNil,
         class T7 = QExtNil>
struct QExtBindFunctor;

/**
 * @brief daptorType that binds an argument to the wrapped functor.
 */
template <class Functor, class Bound>
struct QExtBindFunctor<0, Functor, Bound, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
    : public QExtAdapts<Functor>
{
    typedef QExtAdapts<Functor>                         BaseType;
    typedef typename QExtUnwrapReference<Bound>::Type   BoundType;
    typedef typename QExtAdapts<Functor>::AdaptorType   AdaptorType;

    template<class Arg1 = void,
             class Arg2 = void,
             class Arg3 = void,
             class Arg4 = void,
             class Arg5 = void,
             class Arg6 = void,
             class Arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename AdaptorType::template ReturnTypeDeduce <typename QExtTypeTrait<BoundType>::Pass,
                                                                typename QExtTypeTrait<Arg1>::Pass,
                                                                typename QExtTypeTrait<Arg2>::Pass,
                                                                typename QExtTypeTrait<Arg3>::Pass,
                                                                typename QExtTypeTrait<Arg4>::Pass,
                                                                typename QExtTypeTrait<Arg5>::Pass,
                                                                typename QExtTypeTrait<Arg6>::Pass >::Type Type;
    };
    typedef typename AdaptorType::ResultType ResultType;

    /**
     * @brief Constructs a bind_functor object that binds an argument to the passed functor.
     * @param func Functor to invoke from operator()().
     * @param bound Argument to qextBindFunctor to the functor.
     */
    QExtBindFunctor(typename QExtTypeTrait<Functor>::Take func,
                    typename QExtTypeTrait<Bound>::Take bound)
        : QExtAdapts<Functor>(func), mBound(bound) {}

    /**
     * @brief Invokes the wrapped functor passing on the bound argument only.
     * @return The return value of the functor invocation.
     */
    ResultType operator()()
    {
        //Note: The AIX compiler sometimes gives linker errors if we do not define this in the class.
        return this->mFunctor.template operator()<typename QExtTypeTrait<BoundType>::Pass>(mBound.invoke());
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * mBound is passed as the 1st argument.
     * @param arg1 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <class Arg1>
    typename ReturnTypeDeduce<Arg1>::Type
    operator()(Arg1 arg1)
    {
        return this->mFunctor.template operator()<typename QExtTypeTrait<BoundType>::Pass,
                                                  typename QExtTypeTrait<Arg1>::Pass>(mBound.invoke(), arg1);
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * mBound is passed as the 1st argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <class Arg1, class Arg2>
    typename ReturnTypeDeduce<Arg1, Arg2>::Type
    operator()(Arg1 arg1, Arg2 arg2)
    {
        return this->mFunctor.template operator()<typename QExtTypeTrait<BoundType>::Pass,
                                                  typename QExtTypeTrait<Arg1>::Pass,
                                                  typename QExtTypeTrait<Arg2>::Pass>(mBound.invoke(), arg1, arg2);
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * mBound is passed as the 1st argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <class Arg1, class Arg2, class Arg3>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3)
    {
        return this->mFunctor.template operator()<typename QExtTypeTrait<BoundType>::Pass,
                                                  typename QExtTypeTrait<Arg1>::Pass,
                                                  typename QExtTypeTrait<Arg2>::Pass,
                                                  typename QExtTypeTrait<Arg3>::Pass>(mBound.invoke(),
                                                                                      arg1, arg2, arg3);
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * mBound is passed as the 1st argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <class Arg1, class Arg2, class Arg3, class Arg4>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4)
    {
        return this->mFunctor.template operator()<typename QExtTypeTrait<BoundType>::Pass,
                                                  typename QExtTypeTrait<Arg1>::Pass,
                                                  typename QExtTypeTrait<Arg2>::Pass,
                                                  typename QExtTypeTrait<Arg3>::Pass,
                                                  typename QExtTypeTrait<Arg4>::Pass>(mBound.invoke(),
                                                                                      arg1, arg2, arg3, arg4);
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * mBound is passed as the 1st argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4, Arg5>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5)
    {
        return this->mFunctor.template operator()<typename QExtTypeTrait<BoundType>::Pass,
                                                  typename QExtTypeTrait<Arg1>::Pass,
                                                  typename QExtTypeTrait<Arg2>::Pass,
                                                  typename QExtTypeTrait<Arg3>::Pass,
                                                  typename QExtTypeTrait<Arg4>::Pass,
                                                  typename QExtTypeTrait<Arg5>::Pass>(mBound.invoke(),
                                                                                      arg1, arg2, arg3, arg4, arg5);
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * mBound is passed as the 1st argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @param arg6 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6)
    {
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<BoundType>::Pass,
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<Arg3>::Pass,
            typename QExtTypeTrait<Arg4>::Pass,
            typename QExtTypeTrait<Arg5>::Pass,
            typename QExtTypeTrait<Arg6>::Pass >
            (mBound.invoke(), arg1, arg2, arg3, arg4, arg5, arg6);
    }

    // The argument bound to the functor.
    QExtBoundArgument<Bound> mBound;
};

/** AdaptorType that binds an argument to the wrapped functor.
 * This template specialization fixes the 2nd argument of the wrapped functor.
 *
 * \ingroup qextBindFunctor
 */
template<typename Functor, typename Bound>
struct QExtBindFunctor<1, Functor, Bound, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
    : public QExtAdapts<Functor>
{
    typedef QExtAdapts<Functor>                             BaseType;
    typedef typename QExtUnwrapReference<Bound>::Type       BoundType;
    typedef typename QExtAdapts<Functor>::AdaptorType       AdaptorType;

    template<class Arg1 = void,
             class Arg2 = void,
             class Arg3 = void,
             class Arg4 = void,
             class Arg5 = void,
             class Arg6 = void,
             class Arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename AdaptorType::template ReturnTypeDeduce <typename QExtTypeTrait<Arg1>::Pass,
                                                                typename QExtTypeTrait<BoundType>::Pass,
                                                                typename QExtTypeTrait<Arg2>::Pass,
                                                                typename QExtTypeTrait<Arg3>::Pass,
                                                                typename QExtTypeTrait<Arg4>::Pass,
                                                                typename QExtTypeTrait<Arg5>::Pass,
                                                                typename QExtTypeTrait<Arg6>::Pass >::Type Type;
    };
    typedef typename AdaptorType::ResultType  ResultType;

    /** Constructs a bind_functor object that binds an argument to the passed functor.
     * @param func Functor to invoke from operator()().
     * @param bound Argument to qextBindFunctor to the functor.
     */
    QExtBindFunctor(typename QExtTypeTrait<Functor>::Take func,
                    typename QExtTypeTrait<Bound>::Take bound)
        : QExtAdapts<Functor>(func), mBound(bound) {}

    /**
     * @brief Invokes the wrapped functor passing on the bound argument only.
     * @return The return value of the functor invocation.
     */
    ResultType
    operator()()
    {
        //Note: The AIX compiler sometimes gives linker errors if we do not define this in the class.
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<BoundType>::Pass >
            (mBound.invoke());
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * mBound is passed as the 2nd argument.
     * @param arg1 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <class Arg1>
    typename ReturnTypeDeduce<Arg1>::Type
    operator()(Arg1 arg1)
    {
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<BoundType>::Pass >
            (arg1, mBound.invoke());
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * mBound is passed as the 2nd argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <class Arg1, class Arg2>
    typename ReturnTypeDeduce<Arg1, Arg2>::Type
    operator()(Arg1 arg1, Arg2 arg2)
    {
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<BoundType>::Pass,
            typename QExtTypeTrait<Arg2>::Pass >
            (arg1, mBound.invoke(), arg2);
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * mBound is passed as the 2nd argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <class Arg1, class Arg2, class Arg3>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3)
    {
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<BoundType>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<Arg3>::Pass >
            (arg1, mBound.invoke(), arg2, arg3);
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * mBound is passed as the 2nd argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <class Arg1, class Arg2, class Arg3, class Arg4>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4)
    {
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<BoundType>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<Arg3>::Pass,
            typename QExtTypeTrait<Arg4>::Pass >
            (arg1, mBound.invoke(), arg2, arg3, arg4);
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * mBound is passed as the 2nd argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4, Arg5>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5)
    {
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<BoundType>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<Arg3>::Pass,
            typename QExtTypeTrait<Arg4>::Pass,
            typename QExtTypeTrait<Arg5>::Pass >
            (arg1, mBound.invoke(), arg2, arg3, arg4, arg5);
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * mBound is passed as the 2nd argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @param arg6 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6)
    {
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<BoundType>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<Arg3>::Pass,
            typename QExtTypeTrait<Arg4>::Pass,
            typename QExtTypeTrait<Arg5>::Pass,
            typename QExtTypeTrait<Arg6>::Pass >
            (arg1, mBound.invoke(), arg2, arg3, arg4, arg5, arg6);
    }

    // The argument bound to the functor.
    QExtBoundArgument<Bound> mBound;
};


/** AdaptorType that binds an argument to the wrapped functor.
 * This template specialization fixes the 3rd argument of the wrapped functor.
 *
 * \ingroup qextBindFunctor
 */
template <typename Functor, typename Bound>
struct QExtBindFunctor<2, Functor, Bound, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil> : public QExtAdapts<Functor>
{
    typedef QExtAdapts<Functor>                         BaseType;
    typedef typename QExtUnwrapReference<Bound>::Type   BoundType;
    typedef typename QExtAdapts<Functor>::AdaptorType       AdaptorType;

    template <class Arg1 = void, class Arg2 = void, class Arg3 = void,
             class Arg4 = void, class Arg5 = void, class Arg6 = void, class Arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename AdaptorType::template ReturnTypeDeduce <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<BoundType>::Pass,
            typename QExtTypeTrait<Arg3>::Pass,
            typename QExtTypeTrait<Arg4>::Pass,
            typename QExtTypeTrait<Arg5>::Pass,
            typename QExtTypeTrait<Arg6>::Pass >::Type Type;
    };
    typedef typename AdaptorType::ResultType  ResultType;

    /** Constructs a bind_functor object that binds an argument to the passed functor.
     * @param func Functor to invoke from operator()().
     * @param bound Argument to qextBindFunctor to the functor.
     */
    QExtBindFunctor(typename QExtTypeTrait<Functor>::Take func, typename QExtTypeTrait<Bound>::Take bound)
        : QExtAdapts<Functor>(func), mBound(bound) {}

    /**
     * @brief Invokes the wrapped functor passing on the bound argument only.
     * @return The return value of the functor invocation.
     */
    ResultType
    operator()()
    {
        //Note: The AIX compiler sometimes gives linker errors if we do not define this in the class.
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<BoundType>::Pass >
            (mBound.invoke());
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * mBound is passed as the 3rd argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <class Arg1, class Arg2>
    typename ReturnTypeDeduce<Arg1, Arg2>::Type
    operator()(Arg1 arg1, Arg2 arg2)
    {
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<BoundType>::Pass >
            (arg1, arg2, mBound.invoke());
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * mBound is passed as the 3rd argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <class Arg1, class Arg2, class Arg3>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3)
    {
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<BoundType>::Pass,
            typename QExtTypeTrait<Arg3>::Pass >
            (arg1, arg2, mBound.invoke(), arg3);
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * mBound is passed as the 3rd argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <class Arg1, class Arg2, class Arg3, class Arg4>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4)
    {
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<BoundType>::Pass,
            typename QExtTypeTrait<Arg3>::Pass,
            typename QExtTypeTrait<Arg4>::Pass >
            (arg1, arg2, mBound.invoke(), arg3, arg4);
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * mBound is passed as the 3rd argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4, Arg5>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5)
    {
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<BoundType>::Pass,
            typename QExtTypeTrait<Arg3>::Pass,
            typename QExtTypeTrait<Arg4>::Pass,
            typename QExtTypeTrait<Arg5>::Pass >
            (arg1, arg2, mBound.invoke(), arg3, arg4, arg5);
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * mBound is passed as the 3rd argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @param arg6 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6)
    {
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<BoundType>::Pass,
            typename QExtTypeTrait<Arg3>::Pass,
            typename QExtTypeTrait<Arg4>::Pass,
            typename QExtTypeTrait<Arg5>::Pass,
            typename QExtTypeTrait<Arg6>::Pass >
            (arg1, arg2, mBound.invoke(), arg3, arg4, arg5, arg6);
    }

    // The argument bound to the functor.
    QExtBoundArgument<Bound> mBound;
};


/** AdaptorType that binds an argument to the wrapped functor.
 * This template specialization fixes the 4th argument of the wrapped functor.
 *
 * \ingroup qextBindFunctor
 */
template <typename Functor, typename Bound>
struct QExtBindFunctor<3, Functor, Bound, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil> : public QExtAdapts<Functor>
{
    typedef QExtAdapts<Functor>                         BaseType;
    typedef typename QExtUnwrapReference<Bound>::Type   BoundType;
    typedef typename QExtAdapts<Functor>::AdaptorType       AdaptorType;

    template <class Arg1 = void, class Arg2 = void, class Arg3 = void,
             class Arg4 = void, class Arg5 = void, class Arg6 = void, class Arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename AdaptorType::template ReturnTypeDeduce <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<Arg3>::Pass,
            typename QExtTypeTrait<BoundType>::Pass,
            typename QExtTypeTrait<Arg4>::Pass,
            typename QExtTypeTrait<Arg5>::Pass,
            typename QExtTypeTrait<Arg6>::Pass >::Type Type;
    };
    typedef typename AdaptorType::ResultType  ResultType;

    /** Constructs a bind_functor object that binds an argument to the passed functor.
     * @param func Functor to invoke from operator()().
     * @param bound Argument to qextBindFunctor to the functor.
     */
    QExtBindFunctor(typename QExtTypeTrait<Functor>::Take func, typename QExtTypeTrait<Bound>::Take bound)
        : QExtAdapts<Functor>(func), mBound(bound) {}

    /**
     * @brief Invokes the wrapped functor passing on the bound argument only.
     * @return The return value of the functor invocation.
     */
    ResultType
    operator()()
    {
        //Note: The AIX compiler sometimes gives linker errors if we do not define this in the class.
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<BoundType>::Pass >
            (mBound.invoke());
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * mBound is passed as the 4th argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <class Arg1, class Arg2, class Arg3>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3)
    {
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<Arg3>::Pass,
            typename QExtTypeTrait<BoundType>::Pass >
            (arg1, arg2, arg3, mBound.invoke());
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * mBound is passed as the 4th argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <class Arg1, class Arg2, class Arg3, class Arg4>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4)
    {
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<Arg3>::Pass,
            typename QExtTypeTrait<BoundType>::Pass,
            typename QExtTypeTrait<Arg4>::Pass >
            (arg1, arg2, arg3, mBound.invoke(), arg4);
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * mBound is passed as the 4th argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4, Arg5>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5)
    {
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<Arg3>::Pass,
            typename QExtTypeTrait<BoundType>::Pass,
            typename QExtTypeTrait<Arg4>::Pass,
            typename QExtTypeTrait<Arg5>::Pass >
            (arg1, arg2, arg3, mBound.invoke(), arg4, arg5);
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * mBound is passed as the 4th argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @param arg6 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6)
    {
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<Arg3>::Pass,
            typename QExtTypeTrait<BoundType>::Pass,
            typename QExtTypeTrait<Arg4>::Pass,
            typename QExtTypeTrait<Arg5>::Pass,
            typename QExtTypeTrait<Arg6>::Pass >
            (arg1, arg2, arg3, mBound.invoke(), arg4, arg5, arg6);
    }

    // The argument bound to the functor.
    QExtBoundArgument<Bound> mBound;
};

/** AdaptorType that binds an argument to the wrapped functor.
 * This template specialization fixes the 5th argument of the wrapped functor.
 *
 * \ingroup qextBindFunctor
 */
template <typename Functor, typename Bound>
struct QExtBindFunctor<4, Functor, Bound, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil> : public QExtAdapts<Functor>
{
    typedef QExtAdapts<Functor>                         BaseType;
    typedef typename QExtUnwrapReference<Bound>::Type   BoundType;
    typedef typename QExtAdapts<Functor>::AdaptorType       AdaptorType;

    template <class Arg1 = void, class Arg2 = void, class Arg3 = void,
             class Arg4 = void, class Arg5 = void, class Arg6 = void, class Arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename AdaptorType::template ReturnTypeDeduce <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<Arg3>::Pass,
            typename QExtTypeTrait<Arg4>::Pass,
            typename QExtTypeTrait<BoundType>::Pass,
            typename QExtTypeTrait<Arg5>::Pass,
            typename QExtTypeTrait<Arg6>::Pass >::Type Type;
    };
    typedef typename AdaptorType::ResultType ResultType;

    /** Constructs a bind_functor object that binds an argument to the passed functor.
     * @param func Functor to invoke from operator()().
     * @param bound Argument to qextBindFunctor to the functor.
     */
    QExtBindFunctor(typename QExtTypeTrait<Functor>::Take func, typename QExtTypeTrait<Bound>::Take bound)
        : QExtAdapts<Functor>(func), mBound(bound) {}

    /**
     * @brief Invokes the wrapped functor passing on the bound argument only.
     * @return The return value of the functor invocation.
     */
    ResultType
    operator()()
    {
        //Note: The AIX compiler sometimes gives linker errors if we do not define this in the class.
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<BoundType>::Pass >
            (mBound.invoke());
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * mBound is passed as the 5th argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <class Arg1, class Arg2, class Arg3, class Arg4>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4)
    {
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<Arg3>::Pass,
            typename QExtTypeTrait<Arg4>::Pass,
            typename QExtTypeTrait<BoundType>::Pass >
            (arg1, arg2, arg3, arg4, mBound.invoke());
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * mBound is passed as the 5th argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4, Arg5>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5)
    {
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<Arg3>::Pass,
            typename QExtTypeTrait<Arg4>::Pass,
            typename QExtTypeTrait<BoundType>::Pass,
            typename QExtTypeTrait<Arg5>::Pass >
            (arg1, arg2, arg3, arg4, mBound.invoke(), arg5);
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * mBound is passed as the 5th argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @param arg6 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6)
    {
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<Arg3>::Pass,
            typename QExtTypeTrait<Arg4>::Pass,
            typename QExtTypeTrait<BoundType>::Pass,
            typename QExtTypeTrait<Arg5>::Pass,
            typename QExtTypeTrait<Arg6>::Pass >
            (arg1, arg2, arg3, arg4, mBound.invoke(), arg5, arg6);
    }

    // The argument bound to the functor.
    QExtBoundArgument<Bound> mBound;
};


/** AdaptorType that binds an argument to the wrapped functor.
 * This template specialization fixes the 6th argument of the wrapped functor.
 *
 * \ingroup qextBindFunctor
 */
template <typename Functor, typename Bound>
struct QExtBindFunctor<5, Functor, Bound, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil> : public QExtAdapts<Functor>
{
    typedef QExtAdapts<Functor>                         BaseType;
    typedef typename QExtUnwrapReference<Bound>::Type   BoundType;
    typedef typename QExtAdapts<Functor>::AdaptorType       AdaptorType;

    template <class Arg1 = void, class Arg2 = void, class Arg3 = void,
             class Arg4 = void, class Arg5 = void, class Arg6 = void, class Arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename AdaptorType::template ReturnTypeDeduce <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<Arg3>::Pass,
            typename QExtTypeTrait<Arg4>::Pass,
            typename QExtTypeTrait<Arg5>::Pass,
            typename QExtTypeTrait<BoundType>::Pass,
            typename QExtTypeTrait<Arg6>::Pass >::Type Type;
    };
    typedef typename AdaptorType::ResultType  ResultType;

    /** Constructs a bind_functor object that binds an argument to the passed functor.
     * @param func Functor to invoke from operator()().
     * @param bound Argument to qextBindFunctor to the functor.
     */
    QExtBindFunctor(typename QExtTypeTrait<Functor>::Take func, typename QExtTypeTrait<Bound>::Take bound)
        : QExtAdapts<Functor>(func), mBound(bound) {}

    /**
     * @brief Invokes the wrapped functor passing on the bound argument only.
     * @return The return value of the functor invocation.
     */
    ResultType
    operator()()
    {
        //Note: The AIX compiler sometimes gives linker errors if we do not define this in the class.
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<BoundType>::Pass >
            (mBound.invoke());
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * mBound is passed as the 6th argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4, Arg5>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5)
    {
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<Arg3>::Pass,
            typename QExtTypeTrait<Arg4>::Pass,
            typename QExtTypeTrait<Arg5>::Pass,
            typename QExtTypeTrait<BoundType>::Pass >
            (arg1, arg2, arg3, arg4, arg5, mBound.invoke());
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * mBound is passed as the 6th argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @param arg6 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6)
    {
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<Arg3>::Pass,
            typename QExtTypeTrait<Arg4>::Pass,
            typename QExtTypeTrait<Arg5>::Pass,
            typename QExtTypeTrait<BoundType>::Pass,
            typename QExtTypeTrait<Arg6>::Pass >
            (arg1, arg2, arg3, arg4, arg5, mBound.invoke(), arg6);
    }

    // The argument bound to the functor.
    QExtBoundArgument<Bound> mBound;
};


/** AdaptorType that binds an argument to the wrapped functor.
 * This template specialization fixes the 7th argument of the wrapped functor.
 *
 * \ingroup qextBindFunctor
 */
template <typename Functor, typename Bound>
struct QExtBindFunctor<6, Functor, Bound, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil> : public QExtAdapts<Functor>
{
    typedef QExtAdapts<Functor>                         BaseType;
    typedef typename QExtUnwrapReference<Bound>::Type   BoundType;
    typedef typename QExtAdapts<Functor>::AdaptorType       AdaptorType;

    template <class Arg1 = void, class Arg2 = void, class Arg3 = void,
             class Arg4 = void, class Arg5 = void, class Arg6 = void, class Arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename AdaptorType::template ReturnTypeDeduce <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<Arg3>::Pass,
            typename QExtTypeTrait<Arg4>::Pass,
            typename QExtTypeTrait<Arg5>::Pass,
            typename QExtTypeTrait<Arg6>::Pass,
            typename QExtTypeTrait<BoundType>::Pass >::Type Type;
    };
    typedef typename AdaptorType::ResultType ResultType;

    /** Constructs a bind_functor object that binds an argument to the passed functor.
     * @param func Functor to invoke from operator()().
     * @param bound Argument to qextBindFunctor to the functor.
     */
    QExtBindFunctor(typename QExtTypeTrait<Functor>::Take func, typename QExtTypeTrait<Bound>::Take bound)
        : QExtAdapts<Functor>(func), mBound(bound) {}

    /**
     * @brief Invokes the wrapped functor passing on the bound argument only.
     * @return The return value of the functor invocation.
     */
    ResultType
    operator()()
    {
        //Note: The AIX compiler sometimes gives linker errors if we do not define this in the class.
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<BoundType>::Pass >
            (mBound.invoke());
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * mBound is passed as the 7th argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @param arg6 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6)
    {
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<Arg3>::Pass,
            typename QExtTypeTrait<Arg4>::Pass,
            typename QExtTypeTrait<Arg5>::Pass,
            typename QExtTypeTrait<Arg6>::Pass,
            typename QExtTypeTrait<BoundType>::Pass >
            (arg1, arg2, arg3, arg4, arg5, arg6, mBound.invoke());
    }

    // The argument bound to the functor.
    QExtBoundArgument<Bound> mBound;
};

//template specialization of QExtVisitor<>::doVisitEach<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for qextBindFunctor performs a functor on the
 * functor and on the object instances stored in the qextBindFunctor object.
 *
 * \ingroup qextBindFunctor
 */
template <int T_loc, typename Functor, typename Bound>
struct QExtVisitor<QExtBindFunctor<T_loc, Functor, Bound> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QExtBindFunctor<T_loc, Functor, Bound> &target)
    {
        qextVisitEach(action, target.mFunctor);
        qextVisitEach(action, target.mBound);
    }
};

/** AdaptorType that binds 1 argument(s) to the wrapped functor.
 * This template specialization fixes the last 1 argument(s) of the wrapped functor.
 *
 * \ingroup qextBindFunctor
 */
template <typename Functor, typename T1>
struct QExtBindFunctor<-1, Functor, T1, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil > : public QExtAdapts<Functor>
{
    typedef QExtAdapts<Functor>                         BaseType;
    typedef typename QExtUnwrapReference<T1>::Type      T1Type;
    typedef typename QExtAdapts<Functor>::AdaptorType       AdaptorType;

    template <int count,
             class Arg1, class Arg2, class Arg3,
             class Arg4, class Arg5, class Arg6, class Arg7>
    struct InternalReturnTypeDeduce
    {
        typedef typename AdaptorType::template ReturnTypeDeduce <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<Arg3>::Pass,
            typename QExtTypeTrait<Arg4>::Pass,
            typename QExtTypeTrait<Arg5>::Pass,
            typename QExtTypeTrait<Arg6>::Pass,
            typename QExtTypeTrait<T1Type>::Pass >::Type Type;
    };

    template <class Arg1, class Arg2, class Arg3,
             class Arg4, class Arg5, class Arg6, class Arg7>
    struct InternalReturnTypeDeduce<2, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>
    {
        typedef typename AdaptorType::template ReturnTypeDeduce <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<Arg3>::Pass,
            typename QExtTypeTrait<Arg4>::Pass,
            typename QExtTypeTrait<Arg5>::Pass,
            typename QExtTypeTrait<T1Type>::Pass >::Type Type;
    };

    template <class Arg1, class Arg2, class Arg3,
             class Arg4, class Arg5, class Arg6, class Arg7>
    struct InternalReturnTypeDeduce<3, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>
    {
        typedef typename AdaptorType::template ReturnTypeDeduce <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<Arg3>::Pass,
            typename QExtTypeTrait<Arg4>::Pass,
            typename QExtTypeTrait<T1Type>::Pass >::Type Type;
    };

    template <class Arg1, class Arg2, class Arg3,
             class Arg4, class Arg5, class Arg6, class Arg7>
    struct InternalReturnTypeDeduce<4, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>
    {
        typedef typename AdaptorType::template ReturnTypeDeduce <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<Arg3>::Pass,
            typename QExtTypeTrait<T1Type>::Pass >::Type Type;
    };

    template <class Arg1, class Arg2, class Arg3,
             class Arg4, class Arg5, class Arg6, class Arg7>
    struct InternalReturnTypeDeduce<5, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>
    {
        typedef typename AdaptorType::template ReturnTypeDeduce <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<T1Type>::Pass >::Type Type;
    };

    template <class Arg1, class Arg2, class Arg3,
             class Arg4, class Arg5, class Arg6, class Arg7>
    struct InternalReturnTypeDeduce<6, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>
    {
        typedef typename AdaptorType::template ReturnTypeDeduce <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<T1Type>::Pass >::Type Type;
    };

    template <class Arg1 = void, class Arg2 = void, class Arg3 = void,
             class Arg4 = void, class Arg5 = void, class Arg6 = void, class Arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename InternalReturnTypeDeduce<detail::QExtCountVoid<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>::value,
                                                  Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7 >::Type Type;
    };

    typedef typename AdaptorType::ResultType ResultType;

    /** Constructs a bind_functor object that binds an argument to the passed functor.
     * @param func Functor to invoke from operator()().
     * @param bound1 Argument to qextBindFunctor to the functor.
     */
    QExtBindFunctor(typename QExtTypeTrait<Functor>::Take func, typename QExtTypeTrait<T1>::Take bound1)
        : QExtAdapts<Functor>(func), mBound1(bound1) {}

    /**
     * @brief Invokes the wrapped functor passing on the bound argument only.
     * @return The return value of the functor invocation.
     */
    ResultType
    operator()()
    {
        //Note: The AIX compiler sometimes gives linker errors if we do not define this in the class.
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<typename QExtUnwrapReference<T1>::Type>::Pass >
            (mBound1.invoke());
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * The last 1 argument(s) are fixed.
     * @param arg1 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <class Arg1>
    typename ReturnTypeDeduce<Arg1>::Type
    operator()(Arg1 arg1)
    {
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T1>::Type>::Pass >
            (arg1, mBound1.invoke());
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * The last 1 argument(s) are fixed.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <class Arg1, class Arg2>
    typename ReturnTypeDeduce<Arg1, Arg2>::Type
    operator()(Arg1 arg1, Arg2 arg2)
    {
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T1>::Type>::Pass >
            (arg1, arg2, mBound1.invoke());
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * The last 1 argument(s) are fixed.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <class Arg1, class Arg2, class Arg3>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3)
    {
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<Arg3>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T1>::Type>::Pass >
            (arg1, arg2, arg3, mBound1.invoke());
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * The last 1 argument(s) are fixed.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <class Arg1, class Arg2, class Arg3, class Arg4>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4)
    {
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<Arg3>::Pass,
            typename QExtTypeTrait<Arg4>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T1>::Type>::Pass >
            (arg1, arg2, arg3, arg4, mBound1.invoke());
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * The last 1 argument(s) are fixed.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4, Arg5>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5)
    {
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<Arg3>::Pass,
            typename QExtTypeTrait<Arg4>::Pass,
            typename QExtTypeTrait<Arg5>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T1>::Type>::Pass >
            (arg1, arg2, arg3, arg4, arg5, mBound1.invoke());
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * The last 1 argument(s) are fixed.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @param arg6 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6)
    {
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<Arg3>::Pass,
            typename QExtTypeTrait<Arg4>::Pass,
            typename QExtTypeTrait<Arg5>::Pass,
            typename QExtTypeTrait<Arg6>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T1>::Type>::Pass >
            (arg1, arg2, arg3, arg4, arg5, arg6, mBound1.invoke());
    }

    // The argument bound to the functor.
    QExtBoundArgument<T1> mBound1;
};

//template specialization of QExtVisitor<>::doVisitEach<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for qextBindFunctor performs a functor on the
 * functor and on the object instances stored in the qextBindFunctor object.
 *
 * \ingroup qextBindFunctor
 */
template <typename Functor, typename T1>
struct QExtVisitor<QExtBindFunctor<-1, Functor, T1> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QExtBindFunctor<-1, Functor,  T1 > &target)
    {
        qextVisitEach(action, target.mFunctor);
        qextVisitEach(action, target.mBound1);
    }
};


/** AdaptorType that binds 2 argument(s) to the wrapped functor.
 * This template specialization fixes the last 2 argument(s) of the wrapped functor.
 *
 * \ingroup qextBindFunctor
 */
template <typename Functor, typename T1, typename T_type2>
struct QExtBindFunctor<-1, Functor, T1, T_type2, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil > : public QExtAdapts<Functor>
{
    typedef QExtAdapts<Functor>                         BaseType;
    typedef typename QExtAdapts<Functor>::AdaptorType   AdaptorType;

    template <int count,
             class Arg1, class Arg2, class Arg3,
             class Arg4, class Arg5, class Arg6, class Arg7>
    struct InternalReturnTypeDeduce
    {
        typedef typename AdaptorType::template ReturnTypeDeduce <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<Arg3>::Pass,
            typename QExtTypeTrait<Arg4>::Pass,
            typename QExtTypeTrait<Arg5>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T1>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type2>::Type>::Pass >::Type Type;
    };

    template <class Arg1, class Arg2, class Arg3,
             class Arg4, class Arg5, class Arg6, class Arg7>
    struct InternalReturnTypeDeduce<3, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>
    {
        typedef typename AdaptorType::template ReturnTypeDeduce <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<Arg3>::Pass,
            typename QExtTypeTrait<Arg4>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T1>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type2>::Type>::Pass >::Type Type;
    };

    template <class Arg1, class Arg2, class Arg3,
             class Arg4, class Arg5, class Arg6, class Arg7>
    struct InternalReturnTypeDeduce<4, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>
    {
        typedef typename AdaptorType::template ReturnTypeDeduce <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<Arg3>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T1>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type2>::Type>::Pass >::Type Type;
    };

    template <class Arg1, class Arg2, class Arg3,
             class Arg4, class Arg5, class Arg6, class Arg7>
    struct InternalReturnTypeDeduce<5, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>
    {
        typedef typename AdaptorType::template ReturnTypeDeduce <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T1>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type2>::Type>::Pass >::Type Type;
    };

    template <class Arg1, class Arg2, class Arg3,
             class Arg4, class Arg5, class Arg6, class Arg7>
    struct InternalReturnTypeDeduce<6, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>
    {
        typedef typename AdaptorType::template ReturnTypeDeduce <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T1>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type2>::Type>::Pass >::Type Type;
    };

    template <class Arg1 = void, class Arg2 = void, class Arg3 = void,
             class Arg4 = void, class Arg5 = void, class Arg6 = void, class Arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename InternalReturnTypeDeduce <
            detail::QExtCountVoid<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>::value,
            Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7 >::Type Type;
    };
    typedef typename AdaptorType::ResultType ResultType;

    /** Constructs a bind_functor object that binds an argument to the passed functor.
     * @param func Functor to invoke from operator()().
     * @param bound1 Argument to qextBindFunctor to the functor.
     * @param bound2 Argument to qextBindFunctor to the functor.
     */
    QExtBindFunctor(typename QExtTypeTrait<Functor>::Take func,
                    typename QExtTypeTrait<T1>::Take bound1,
                    typename QExtTypeTrait<T_type2>::Take bound2)
        : QExtAdapts<Functor>(func), mBound1(bound1), mBound2(bound2) {}

    /**
     * @brief Invokes the wrapped functor passing on the bound argument only.
     * @return The return value of the functor invocation.
     */
    ResultType
    operator()()
    {
        //Note: The AIX compiler sometimes gives linker errors if we do not define this in the class.
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<typename QExtUnwrapReference<T1>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type2>::Type>::Pass >
            (mBound1.invoke(), mBound2.invoke());
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * The last 2 argument(s) are fixed.
     * @param arg1 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <class Arg1>
    typename ReturnTypeDeduce<Arg1>::Type
    operator()(Arg1 arg1)
    {
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T1>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type2>::Type>::Pass >
            (arg1, mBound1.invoke(), mBound2.invoke());
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * The last 2 argument(s) are fixed.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <class Arg1, class Arg2>
    typename ReturnTypeDeduce<Arg1, Arg2>::Type
    operator()(Arg1 arg1, Arg2 arg2)
    {
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T1>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type2>::Type>::Pass >
            (arg1, arg2, mBound1.invoke(), mBound2.invoke());
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * The last 2 argument(s) are fixed.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <class Arg1, class Arg2, class Arg3>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3)
    {
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<Arg3>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T1>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type2>::Type>::Pass >
            (arg1, arg2, arg3, mBound1.invoke(), mBound2.invoke());
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * The last 2 argument(s) are fixed.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <class Arg1, class Arg2, class Arg3, class Arg4>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4)
    {
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<Arg3>::Pass,
            typename QExtTypeTrait<Arg4>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T1>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type2>::Type>::Pass >
            (arg1, arg2, arg3, arg4, mBound1.invoke(), mBound2.invoke());
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * The last 2 argument(s) are fixed.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4, Arg5>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5)
    {
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<Arg3>::Pass,
            typename QExtTypeTrait<Arg4>::Pass,
            typename QExtTypeTrait<Arg5>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T1>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type2>::Type>::Pass >
            (arg1, arg2, arg3, arg4, arg5, mBound1.invoke(), mBound2.invoke());
    }

    // The argument bound to the functor.
    QExtBoundArgument<T1> mBound1;
    QExtBoundArgument<T_type2> mBound2;
};


//template specialization of QExtVisitor<>::doVisitEach<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for qextBindFunctor performs a functor on the
 * functor and on the object instances stored in the qextBindFunctor object.
 *
 * \ingroup qextBindFunctor
 */
template <typename Functor, typename T1, typename T_type2>
struct QExtVisitor < QExtBindFunctor<-1, Functor, T1, T_type2 > >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QExtBindFunctor<-1, Functor,  T1, T_type2 > &target)
    {
        qextVisitEach(action, target.mFunctor);
        qextVisitEach(action, target.mBound1);
        qextVisitEach(action, target.mBound2);
    }
};


/** AdaptorType that binds 3 argument(s) to the wrapped functor.
 * This template specialization fixes the last 3 argument(s) of the wrapped functor.
 *
 * \ingroup qextBindFunctor
 */
template <typename Functor, typename T1, typename T_type2, typename T_type3>
struct QExtBindFunctor<-1, Functor, T1, T_type2, T_type3, QExtNil, QExtNil, QExtNil, QExtNil > : public QExtAdapts<Functor>
{
    typedef QExtAdapts<Functor>                         BaseType;
    typedef typename QExtAdapts<Functor>::AdaptorType       AdaptorType;

    template <int count,
             class Arg1, class Arg2, class Arg3,
             class Arg4, class Arg5, class Arg6, class Arg7>
    struct InternalReturnTypeDeduce
    {
        typedef typename AdaptorType::template ReturnTypeDeduce <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<Arg3>::Pass,
            typename QExtTypeTrait<Arg4>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T1>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type2>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type3>::Type>::Pass >::Type Type;
    };

    template <class Arg1, class Arg2, class Arg3,
             class Arg4, class Arg5, class Arg6, class Arg7>
    struct InternalReturnTypeDeduce<4, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>
    {
        typedef typename AdaptorType::template ReturnTypeDeduce <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<Arg3>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T1>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type2>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type3>::Type>::Pass >::Type Type;
    };

    template <class Arg1, class Arg2, class Arg3,
             class Arg4, class Arg5, class Arg6, class Arg7>
    struct InternalReturnTypeDeduce<5, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>
    {
        typedef typename AdaptorType::template ReturnTypeDeduce <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T1>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type2>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type3>::Type>::Pass >::Type Type;
    };

    template <class Arg1, class Arg2, class Arg3,
             class Arg4, class Arg5, class Arg6, class Arg7>
    struct InternalReturnTypeDeduce<6, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>
    {
        typedef typename AdaptorType::template ReturnTypeDeduce <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T1>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type2>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type3>::Type>::Pass >::Type Type;
    };

    template <class Arg1 = void, class Arg2 = void, class Arg3 = void,
             class Arg4 = void, class Arg5 = void, class Arg6 = void, class Arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename InternalReturnTypeDeduce <
            detail::QExtCountVoid<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>::value,
            Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7 >::Type Type;
    };
    typedef typename AdaptorType::ResultType ResultType;

    /** Constructs a bind_functor object that binds an argument to the passed functor.
     * @param func Functor to invoke from operator()().
     * @param bound1 Argument to qextBindFunctor to the functor.
     * @param bound2 Argument to qextBindFunctor to the functor.
     * @param bound3 Argument to qextBindFunctor to the functor.
     */
    QExtBindFunctor(typename QExtTypeTrait<Functor>::Take func,
                    typename QExtTypeTrait<T1>::Take bound1,
                    typename QExtTypeTrait<T_type2>::Take bound2,
                    typename QExtTypeTrait<T_type3>::Take bound3)
        : QExtAdapts<Functor>(func), mBound1(bound1), mBound2(bound2), mBound3(bound3) {}

    /**
     * @brief Invokes the wrapped functor passing on the bound argument only.
     * @return The return value of the functor invocation.
     */
    ResultType
    operator()()
    {
        //Note: The AIX compiler sometimes gives linker errors if we do not define this in the class.
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<typename QExtUnwrapReference<T1>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type2>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type3>::Type>::Pass >
            (mBound1.invoke(), mBound2.invoke(), mBound3.invoke());
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * The last 3 argument(s) are fixed.
     * @param arg1 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <class Arg1>
    typename ReturnTypeDeduce<Arg1>::Type
    operator()(Arg1 arg1)
    {
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T1>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type2>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type3>::Type>::Pass >
            (arg1, mBound1.invoke(), mBound2.invoke(), mBound3.invoke());
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * The last 3 argument(s) are fixed.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <class Arg1, class Arg2>
    typename ReturnTypeDeduce<Arg1, Arg2>::Type
    operator()(Arg1 arg1, Arg2 arg2)
    {
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T1>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type2>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type3>::Type>::Pass >
            (arg1, arg2, mBound1.invoke(), mBound2.invoke(), mBound3.invoke());
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * The last 3 argument(s) are fixed.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <class Arg1, class Arg2, class Arg3>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3)
    {
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<Arg3>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T1>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type2>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type3>::Type>::Pass >
            (arg1, arg2, arg3, mBound1.invoke(), mBound2.invoke(), mBound3.invoke());
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * The last 3 argument(s) are fixed.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <class Arg1, class Arg2, class Arg3, class Arg4>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4)
    {
        return this->mFunctor(arg1, arg2, arg3, arg4, mBound1.invoke(), mBound2.invoke(), mBound3.invoke());
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<Arg3>::Pass,
            typename QExtTypeTrait<Arg4>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T1>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type2>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type3>::Type>::Pass >
            (arg1, arg2, arg3, arg4, mBound1.invoke(), mBound2.invoke(), mBound3.invoke());
    }

    // The argument bound to the functor.
    QExtBoundArgument<T1> mBound1;
    QExtBoundArgument<T_type2> mBound2;
    QExtBoundArgument<T_type3> mBound3;
};


//template specialization of QExtVisitor<>::doVisitEach<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for qextBindFunctor performs a functor on the
 * functor and on the object instances stored in the qextBindFunctor object.
 *
 * \ingroup qextBindFunctor
 */
template <typename Functor, typename T1, typename T_type2, typename T_type3>
struct QExtVisitor<QExtBindFunctor<-1, Functor, T1, T_type2, T_type3 > >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QExtBindFunctor<-1, Functor,  T1, T_type2, T_type3 > &target)
    {
        qextVisitEach(action, target.mFunctor);
        qextVisitEach(action, target.mBound1);
        qextVisitEach(action, target.mBound2);
        qextVisitEach(action, target.mBound3);
    }
};


/** AdaptorType that binds 4 argument(s) to the wrapped functor.
 * This template specialization fixes the last 4 argument(s) of the wrapped functor.
 *
 * \ingroup qextBindFunctor
 */
template <typename Functor,
         typename T1, typename T_type2, typename T_type3, typename T_type4>
struct QExtBindFunctor<-1, Functor, T1, T_type2, T_type3, T_type4, QExtNil, QExtNil, QExtNil > : public QExtAdapts<Functor>
{
    typedef QExtAdapts<Functor>                         BaseType;
    typedef typename QExtAdapts<Functor>::AdaptorType       AdaptorType;

    template <int count,
             class Arg1, class Arg2, class Arg3,
             class Arg4, class Arg5, class Arg6, class Arg7>
    struct InternalReturnTypeDeduce
    {
        typedef typename AdaptorType::template ReturnTypeDeduce <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<Arg3>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T1>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type2>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type3>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type4>::Type>::Pass >::Type Type;
    };

    template <class Arg1, class Arg2, class Arg3,
             class Arg4, class Arg5, class Arg6, class Arg7>
    struct InternalReturnTypeDeduce<5, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>
    {
        typedef typename AdaptorType::template ReturnTypeDeduce <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T1>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type2>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type3>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type4>::Type>::Pass >::Type Type;
    };

    template <class Arg1, class Arg2, class Arg3,
             class Arg4, class Arg5, class Arg6, class Arg7>
    struct InternalReturnTypeDeduce<6, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>
    {
        typedef typename AdaptorType::template ReturnTypeDeduce <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T1>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type2>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type3>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type4>::Type>::Pass >::Type Type;
    };

    template <class Arg1 = void, class Arg2 = void, class Arg3 = void,
             class Arg4 = void, class Arg5 = void, class Arg6 = void, class Arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename InternalReturnTypeDeduce <
            detail::QExtCountVoid<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>::value,
            Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7 >::Type Type;
    };
    typedef typename AdaptorType::ResultType ResultType;

    /** Constructs a bind_functor object that binds an argument to the passed functor.
     * @param func Functor to invoke from operator()().
     * @param bound1 Argument to qextBindFunctor to the functor.
     * @param bound2 Argument to qextBindFunctor to the functor.
     * @param bound3 Argument to qextBindFunctor to the functor.
     * @param bound4 Argument to qextBindFunctor to the functor.
     */
    QExtBindFunctor(typename QExtTypeTrait<Functor>::Take func,
                    typename QExtTypeTrait<T1>::Take bound1,
                    typename QExtTypeTrait<T_type2>::Take bound2,
                    typename QExtTypeTrait<T_type3>::Take bound3,
                    typename QExtTypeTrait<T_type4>::Take bound4)
        : QExtAdapts<Functor>(func), mBound1(bound1), mBound2(bound2), mBound3(bound3), mBound4(bound4) {}

    /**
     * @brief Invokes the wrapped functor passing on the bound argument only.
     * @return The return value of the functor invocation.
     */
    ResultType
    operator()()
    {
        //Note: The AIX compiler sometimes gives linker errors if we do not define this in the class.
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<typename QExtUnwrapReference<T1>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type2>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type3>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type4>::Type>::Pass >
            (mBound1.invoke(), mBound2.invoke(), mBound3.invoke(), mBound4.invoke());
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * The last 4 argument(s) are fixed.
     * @param arg1 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <class Arg1>
    typename ReturnTypeDeduce<Arg1>::Type
    operator()(Arg1 arg1)
    {
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T1>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type2>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type3>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type4>::Type>::Pass >
            (arg1, mBound1.invoke(), mBound2.invoke(), mBound3.invoke(), mBound4.invoke());
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * The last 4 argument(s) are fixed.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <class Arg1, class Arg2>
    typename ReturnTypeDeduce<Arg1, Arg2>::Type
    operator()(Arg1 arg1, Arg2 arg2)
    {
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T1>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type2>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type3>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type4>::Type>::Pass >
            (arg1, arg2, mBound1.invoke(), mBound2.invoke(), mBound3.invoke(), mBound4.invoke());
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * The last 4 argument(s) are fixed.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <class Arg1, class Arg2, class Arg3>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3)
    {
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<Arg3>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T1>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type2>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type3>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type4>::Type>::Pass >
            (arg1, arg2, arg3, mBound1.invoke(), mBound2.invoke(), mBound3.invoke(), mBound4.invoke());
    }

    // The argument bound to the functor.
    QExtBoundArgument<T1> mBound1;
    QExtBoundArgument<T_type2> mBound2;
    QExtBoundArgument<T_type3> mBound3;
    QExtBoundArgument<T_type4> mBound4;
};


//template specialization of QExtVisitor<>::doVisitEach<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for qextBindFunctor performs a functor on the
 * functor and on the object instances stored in the qextBindFunctor object.
 *
 * \ingroup qextBindFunctor
 */
template <typename Functor, typename T1, typename T_type2, typename T_type3, typename T_type4>
struct QExtVisitor<QExtBindFunctor<-1, Functor, T1, T_type2, T_type3, T_type4> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QExtBindFunctor<-1, Functor,  T1, T_type2, T_type3, T_type4 > &target)
    {
        qextVisitEach(action, target.mFunctor);
        qextVisitEach(action, target.mBound1);
        qextVisitEach(action, target.mBound2);
        qextVisitEach(action, target.mBound3);
        qextVisitEach(action, target.mBound4);
    }
};

/** AdaptorType that binds 5 argument(s) to the wrapped functor.
 * This template specialization fixes the last 5 argument(s) of the wrapped functor.
 *
 * \ingroup qextBindFunctor
 */
template <typename Functor,
         typename T1, typename T_type2, typename T_type3, typename T_type4, typename T_type5>
struct QExtBindFunctor<-1, Functor, T1, T_type2, T_type3, T_type4, T_type5, QExtNil, QExtNil > : public QExtAdapts<Functor>
{
    typedef QExtAdapts<Functor>                         BaseType;
    typedef typename QExtAdapts<Functor>::AdaptorType   AdaptorType;

    template <int count,
             class Arg1, class Arg2, class Arg3,
             class Arg4, class Arg5, class Arg6, class Arg7>
    struct InternalReturnTypeDeduce
    {
        typedef typename AdaptorType::template ReturnTypeDeduce <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T1>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type2>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type3>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type4>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type5>::Type>::Pass >::Type Type;
    };

    template <class Arg1, class Arg2, class Arg3,
             class Arg4, class Arg5, class Arg6, class Arg7>
    struct InternalReturnTypeDeduce<6, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>
    {
        typedef typename AdaptorType::template ReturnTypeDeduce <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T1>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type2>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type3>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type4>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type5>::Type>::Pass >::Type Type;
    };

    template <class Arg1 = void, class Arg2 = void, class Arg3 = void,
             class Arg4 = void, class Arg5 = void, class Arg6 = void, class Arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename InternalReturnTypeDeduce <
            detail::QExtCountVoid<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>::value,
            Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7 >::Type Type;
    };
    typedef typename AdaptorType::ResultType ResultType;

    /** Constructs a bind_functor object that binds an argument to the passed functor.
     * @param func Functor to invoke from operator()().
     * @param bound1 Argument to qextBindFunctor to the functor.
     * @param bound2 Argument to qextBindFunctor to the functor.
     * @param bound3 Argument to qextBindFunctor to the functor.
     * @param bound4 Argument to qextBindFunctor to the functor.
     * @param bound5 Argument to qextBindFunctor to the functor.
     */
    QExtBindFunctor(typename QExtTypeTrait<Functor>::Take func,
                    typename QExtTypeTrait<T1>::Take bound1,
                    typename QExtTypeTrait<T_type2>::Take bound2,
                    typename QExtTypeTrait<T_type3>::Take bound3,
                    typename QExtTypeTrait<T_type4>::Take bound4,
                    typename QExtTypeTrait<T_type5>::Take bound5)
        : QExtAdapts<Functor>(func), mBound1(bound1), mBound2(bound2), mBound3(bound3), mBound4(bound4), mBound5(bound5) {}

    /**
     * @brief Invokes the wrapped functor passing on the bound argument only.
     * @return The return value of the functor invocation.
     */
    ResultType
    operator()()
    {
        //Note: The AIX compiler sometimes gives linker errors if we do not define this in the class.
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<typename QExtUnwrapReference<T1>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type2>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type3>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type4>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type5>::Type>::Pass >
            (mBound1.invoke(), mBound2.invoke(), mBound3.invoke(), mBound4.invoke(), mBound5.invoke());
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * The last 5 argument(s) are fixed.
     * @param arg1 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <class Arg1>
    typename ReturnTypeDeduce<Arg1>::Type
    operator()(Arg1 arg1)
    {
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T1>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type2>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type3>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type4>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type5>::Type>::Pass >
            (arg1, mBound1.invoke(), mBound2.invoke(), mBound3.invoke(), mBound4.invoke(), mBound5.invoke());
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * The last 5 argument(s) are fixed.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <class Arg1, class Arg2>
    typename ReturnTypeDeduce<Arg1, Arg2>::Type
    operator()(Arg1 arg1, Arg2 arg2)
    {
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<Arg2>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T1>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type2>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type3>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type4>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type5>::Type>::Pass >
            (arg1, arg2, mBound1.invoke(), mBound2.invoke(), mBound3.invoke(), mBound4.invoke(), mBound5.invoke());
    }

    // The argument bound to the functor.
    QExtBoundArgument<T1> mBound1;
    QExtBoundArgument<T_type2> mBound2;
    QExtBoundArgument<T_type3> mBound3;
    QExtBoundArgument<T_type4> mBound4;
    QExtBoundArgument<T_type5> mBound5;
};


//template specialization of QExtVisitor<>::doVisitEach<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for qextBindFunctor performs a functor on the
 * functor and on the object instances stored in the qextBindFunctor object.
 *
 * \ingroup qextBindFunctor
 */
template <typename Functor,
         typename T1, typename T_type2, typename T_type3, typename T_type4, typename T_type5>
struct QExtVisitor<QExtBindFunctor<-1, Functor, T1, T_type2, T_type3, T_type4, T_type5> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QExtBindFunctor<-1, Functor,  T1, T_type2, T_type3, T_type4, T_type5 > & target)
    {
        qextVisitEach(action, target.mFunctor);
        qextVisitEach(action, target.mBound1);
        qextVisitEach(action, target.mBound2);
        qextVisitEach(action, target.mBound3);
        qextVisitEach(action, target.mBound4);
        qextVisitEach(action, target.mBound5);
    }
};


/** AdaptorType that binds 6 argument(s) to the wrapped functor.
 * This template specialization fixes the last 6 argument(s) of the wrapped functor.
 *
 * \ingroup qextBindFunctor
 */
template <typename Functor,
         typename T1, typename T_type2, typename T_type3,
         typename T_type4, typename T_type5, typename T_type6>
struct QExtBindFunctor<-1, Functor, T1, T_type2, T_type3, T_type4, T_type5, T_type6, QExtNil >
    : public QExtAdapts<Functor>
{
    typedef QExtAdapts<Functor>                         BaseType;
    typedef typename QExtAdapts<Functor>::AdaptorType       AdaptorType;

    template <int count,
             class Arg1, class Arg2, class Arg3,
             class Arg4, class Arg5, class Arg6, class Arg7>
    struct InternalReturnTypeDeduce
    {
        typedef typename AdaptorType::template ReturnTypeDeduce <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T1>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type2>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type3>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type4>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type5>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type6>::Type>::Pass >::Type Type;
    };

    template <class Arg1 = void, class Arg2 = void, class Arg3 = void,
             class Arg4 = void, class Arg5 = void, class Arg6 = void, class Arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename InternalReturnTypeDeduce <
            detail::QExtCountVoid<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>::value,
            Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7 >::Type Type;
    };
    typedef typename AdaptorType::ResultType ResultType;

    /** Constructs a bind_functor object that binds an argument to the passed functor.
     * @param func Functor to invoke from operator()().
     * @param bound1 Argument to qextBindFunctor to the functor.
     * @param bound2 Argument to qextBindFunctor to the functor.
     * @param bound3 Argument to qextBindFunctor to the functor.
     * @param bound4 Argument to qextBindFunctor to the functor.
     * @param bound5 Argument to qextBindFunctor to the functor.
     * @param bound6 Argument to qextBindFunctor to the functor.
     */
    QExtBindFunctor(typename QExtTypeTrait<Functor>::Take func,
                    typename QExtTypeTrait<T1>::Take bound1,
                    typename QExtTypeTrait<T_type2>::Take bound2,
                    typename QExtTypeTrait<T_type3>::Take bound3,
                    typename QExtTypeTrait<T_type4>::Take bound4,
                    typename QExtTypeTrait<T_type5>::Take bound5,
                    typename QExtTypeTrait<T_type6>::Take bound6)
        : QExtAdapts<Functor>(func),
        mBound1(bound1), mBound2(bound2), mBound3(bound3),
        mBound4(bound4), mBound5(bound5), mBound6(bound6) {}

    /**
     * @brief Invokes the wrapped functor passing on the bound argument only.
     * @return The return value of the functor invocation.
     */
    ResultType
    operator()()
    {
        //Note: The AIX compiler sometimes gives linker errors if we do not define this in the class.
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<typename QExtUnwrapReference<T1>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type2>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type3>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type4>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type5>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type6>::Type>::Pass >
            (mBound1.invoke(), mBound2.invoke(), mBound3.invoke(), mBound4.invoke(), mBound5.invoke(), mBound6.invoke());
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * The last 6 argument(s) are fixed.
     * @param arg1 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <class Arg1>
    typename ReturnTypeDeduce<Arg1>::Type
    operator()(Arg1 arg1)
    {
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<Arg1>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T1>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type2>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type3>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type4>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type5>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type6>::Type>::Pass >
            (arg1, mBound1.invoke(), mBound2.invoke(), mBound3.invoke(), mBound4.invoke(), mBound5.invoke(), mBound6.invoke());
    }

    // The argument bound to the functor.
    QExtBoundArgument<T1> mBound1;
    QExtBoundArgument<T_type2> mBound2;
    QExtBoundArgument<T_type3> mBound3;
    QExtBoundArgument<T_type4> mBound4;
    QExtBoundArgument<T_type5> mBound5;
    QExtBoundArgument<T_type6> mBound6;
};


//template specialization of QExtVisitor<>::doVisitEach<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for qextBindFunctor performs a functor on the
 * functor and on the object instances stored in the qextBindFunctor object.
 *
 * \ingroup qextBindFunctor
 */
template <typename Functor,
         typename T1, typename T_type2, typename T_type3,
         typename T_type4, typename T_type5, typename T_type6>
struct QExtVisitor<QExtBindFunctor< -1, Functor, T1, T_type2, T_type3, T_type4, T_type5, T_type6> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QExtBindFunctor<-1, Functor,  T1, T_type2, T_type3, T_type4, T_type5, T_type6 > &target)
    {
        qextVisitEach(action, target.mFunctor);
        qextVisitEach(action, target.mBound1);
        qextVisitEach(action, target.mBound2);
        qextVisitEach(action, target.mBound3);
        qextVisitEach(action, target.mBound4);
        qextVisitEach(action, target.mBound5);
        qextVisitEach(action, target.mBound6);
    }
};


/** AdaptorType that binds 7 argument(s) to the wrapped functor.
 * This template specialization fixes the last 7 argument(s) of the wrapped functor.
 *
 * \ingroup qextBindFunctor
 */
template <typename Functor,
         typename T1, typename T_type2, typename T_type3,
         typename T_type4, typename T_type5, typename T_type6, typename T_type7>
struct QExtBindFunctor<-1, Functor, T1, T_type2, T_type3, T_type4, T_type5, T_type6, T_type7>
    : public QExtAdapts<Functor>
{
    typedef QExtAdapts<Functor>                         BaseType;
    typedef typename QExtAdapts<Functor>::AdaptorType       AdaptorType;

    template <int count,
             class Arg1, class Arg2, class Arg3,
             class Arg4, class Arg5, class Arg6, class Arg7>
    struct InternalReturnTypeDeduce
    {
        typedef typename AdaptorType::template ReturnTypeDeduce <
            typename QExtTypeTrait<typename QExtUnwrapReference<T1>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type2>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type3>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type4>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type5>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type6>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type7>::Type>::Pass >::Type Type;
    };

    template <class Arg1 = void, class Arg2 = void, class Arg3 = void,
             class Arg4 = void, class Arg5 = void, class Arg6 = void, class Arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename InternalReturnTypeDeduce <
            detail::QExtCountVoid<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>::value,
            Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7 >::Type Type;
    };
    typedef typename AdaptorType::ResultType ResultType;

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
    QExtBindFunctor(typename QExtTypeTrait<Functor>::Take func,
                    typename QExtTypeTrait<T1>::Take bound1,
                    typename QExtTypeTrait<T_type2>::Take bound2,
                    typename QExtTypeTrait<T_type3>::Take bound3,
                    typename QExtTypeTrait<T_type4>::Take bound4,
                    typename QExtTypeTrait<T_type5>::Take bound5,
                    typename QExtTypeTrait<T_type6>::Take bound6,
                    typename QExtTypeTrait<T_type7>::Take bound7)
        : QExtAdapts<Functor>(func),
        mBound1(bound1), mBound2(bound2), mBound3(bound3),
        mBound4(bound4), mBound5(bound5), mBound6(bound6), mBound7(bound7) {}

    /**
     * @brief Invokes the wrapped functor passing on the bound argument only.
     * @return The return value of the functor invocation.
     */
    ResultType
    operator()()
    {
        //Note: The AIX compiler sometimes gives linker errors if we do not define this in the class.
        return this->mFunctor.template operator () <
            typename QExtTypeTrait<typename QExtUnwrapReference<T1>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type2>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type3>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type4>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type5>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type6>::Type>::Pass,
            typename QExtTypeTrait<typename QExtUnwrapReference<T_type7>::Type>::Pass >
            (mBound1.invoke(), mBound2.invoke(), mBound3.invoke(), mBound4.invoke(), mBound5.invoke(), mBound6.invoke(), mBound7.invoke());
    }

    // The argument bound to the functor.
    QExtBoundArgument<T1> mBound1;
    QExtBoundArgument<T_type2> mBound2;
    QExtBoundArgument<T_type3> mBound3;
    QExtBoundArgument<T_type4> mBound4;
    QExtBoundArgument<T_type5> mBound5;
    QExtBoundArgument<T_type6> mBound6;
    QExtBoundArgument<T_type7> mBound7;
};


//template specialization of QExtVisitor<>::doVisitEach<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for qextBindFunctor performs a functor on the
 * functor and on the object instances stored in the qextBindFunctor object.
 *
 * \ingroup qextBindFunctor
 */
template <typename Functor,
         typename T1, typename T_type2, typename T_type3,
         typename T_type4, typename T_type5, typename T_type6, typename T_type7>
struct QExtVisitor<QExtBindFunctor<-1, Functor, T1, T_type2, T_type3, T_type4, T_type5, T_type6, T_type7 > >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QExtBindFunctor<-1, Functor,  T1, T_type2, T_type3, T_type4, T_type5, T_type6, T_type7 > &target)
    {
        qextVisitEach(action, target.mFunctor);
        qextVisitEach(action, target.mBound1);
        qextVisitEach(action, target.mBound2);
        qextVisitEach(action, target.mBound3);
        qextVisitEach(action, target.mBound4);
        qextVisitEach(action, target.mBound5);
        qextVisitEach(action, target.mBound6);
        qextVisitEach(action, target.mBound7);
    }
};



/** Creates an adaptor of type qextBindFunctor which binds the passed argument to the passed functor.
 * The optional template argument @e I_location specifies the zero-based
 * position of the argument to be fixed (@p -1 stands for the last argument).
 *
 * @param func Functor that should be wrapped.
 * @param bound1 Argument to qextBindFunctor to @e func.
 * @return AdaptorType that executes @e func with the bound argument on invokation.
 *
 * \ingroup qextBindFunctor
 */
template <int I_location, typename Functor, typename T1>
inline QExtBindFunctor<I_location, Functor, T1>
qextBindFunctor(const Functor &func, T1 bound1)
{
    return QExtBindFunctor<I_location, Functor, T1>(func, bound1);
}


/** Creates an adaptor of type qextBindFunctor which fixes the last 1 argument(s) of the passed functor.
 * This function overload fixes the last 1 argument(s) of @e func.
 *
 * @param func Functor that should be wrapped.
 * @param bound1 Argument to qextBindFunctor to @e func.
 * @return AdaptorType that executes func with the bound argument on invokation.
 *
 * \ingroup qextBindFunctor
 */
template <typename Functor, typename T1>
inline QExtBindFunctor<-1, Functor, T1 >
qextBindFunctor(const Functor &func, T1 bound1)
{
    return QExtBindFunctor<-1, Functor, T1 > (func, bound1);
}


/** Creates an adaptor of type qextBindFunctor which fixes the last 2 argument(s) of the passed functor.
 * This function overload fixes the last 2 argument(s) of @e func.
 *
 * @param func Functor that should be wrapped.
 * @param bound1 Argument to qextBindFunctor to @e func.
 * @param bound2 Argument to qextBindFunctor to @e func.
 * @return AdaptorType that executes func with the bound argument on invokation.
 *
 * \ingroup qextBindFunctor
 */
template <typename Functor, typename T1, typename T_type2>
inline QExtBindFunctor<-1, Functor, T1, T_type2 >
qextBindFunctor(const Functor &func, T1 bound1, T_type2 bound2)
{
    return QExtBindFunctor<-1, Functor, T1, T_type2 > (func, bound1, bound2);
}


/** Creates an adaptor of type qextBindFunctor which fixes the last 3 argument(s) of the passed functor.
 * This function overload fixes the last 3 argument(s) of @e func.
 *
 * @param func Functor that should be wrapped.
 * @param bound1 Argument to qextBindFunctor to @e func.
 * @param bound2 Argument to qextBindFunctor to @e func.
 * @param bound3 Argument to qextBindFunctor to @e func.
 * @return AdaptorType that executes func with the bound argument on invokation.
 *
 * \ingroup qextBindFunctor
 */
template <typename Functor, typename T1, typename T_type2, typename T_type3>
inline QExtBindFunctor<-1, Functor, T1, T_type2, T_type3 >
qextBindFunctor(const Functor &func, T1 bound1, T_type2 bound2, T_type3 bound3)
{
    return QExtBindFunctor<-1, Functor, T1, T_type2, T_type3 > (func, bound1, bound2, bound3);
}


/** Creates an adaptor of type qextBindFunctor which fixes the last 4 argument(s) of the passed functor.
 * This function overload fixes the last 4 argument(s) of @e func.
 *
 * @param func Functor that should be wrapped.
 * @param bound1 Argument to qextBindFunctor to @e func.
 * @param bound2 Argument to qextBindFunctor to @e func.
 * @param bound3 Argument to qextBindFunctor to @e func.
 * @param bound4 Argument to qextBindFunctor to @e func.
 * @return AdaptorType that executes func with the bound argument on invokation.
 *
 * \ingroup qextBindFunctor
 */
template <typename Functor, typename T1, typename T_type2, typename T_type3, typename T_type4>
inline QExtBindFunctor<-1, Functor, T1, T_type2, T_type3, T_type4 >
qextBindFunctor(const Functor &func, T1 bound1, T_type2 bound2, T_type3 bound3, T_type4 bound4)
{
    return QExtBindFunctor<-1, Functor, T1, T_type2, T_type3, T_type4 > (func, bound1, bound2, bound3, bound4);
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
 * @return AdaptorType that executes func with the bound argument on invokation.
 *
 * \ingroup qextBindFunctor
 */
template <typename Functor,
         typename T1, typename T_type2, typename T_type3, typename T_type4, typename T_type5>
inline QExtBindFunctor<-1, Functor, T1, T_type2, T_type3, T_type4, T_type5 >
qextBindFunctor(const Functor &func, T1 bound1, T_type2 bound2, T_type3 bound3, T_type4 bound4, T_type5 bound5)
{
    return QExtBindFunctor<-1, Functor, T1, T_type2, T_type3, T_type4, T_type5 > (func, bound1, bound2, bound3, bound4, bound5);
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
 * @return AdaptorType that executes func with the bound argument on invokation.
 *
 * \ingroup qextBindFunctor
 */
template <typename Functor,
         typename T1, typename T_type2, typename T_type3,
         typename T_type4, typename T_type5, typename T_type6>
inline QExtBindFunctor<-1, Functor, T1, T_type2, T_type3, T_type4, T_type5, T_type6 >
qextBindFunctor(const Functor &func, T1 bound1, T_type2 bound2, T_type3 bound3, T_type4 bound4, T_type5 bound5, T_type6 bound6)
{
    return QExtBindFunctor<-1, Functor, T1, T_type2, T_type3, T_type4, T_type5, T_type6 > (func, bound1, bound2, bound3, bound4, bound5, bound6);
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
 * @return AdaptorType that executes func with the bound argument on invokation.
 *
 * \ingroup qextBindFunctor
 */
template <typename Functor,
         typename T1, typename T_type2, typename T_type3,
         typename T_type4, typename T_type5, typename T_type6, typename T_type7>
inline QExtBindFunctor<-1, Functor, T1, T_type2, T_type3, T_type4, T_type5, T_type6, T_type7>
qextBindFunctor(const Functor &func, T1 bound1, T_type2 bound2, T_type3 bound3, T_type4 bound4, T_type5 bound5, T_type6 bound6, T_type7 bound7)
{
    return QExtBindFunctor<-1, Functor, T1, T_type2, T_type3, T_type4, T_type5, T_type6, T_type7 > (func, bound1, bound2, bound3, bound4, bound5, bound6, bound7);
}

#endif // _QEXTBINDFUNCTOR_H
