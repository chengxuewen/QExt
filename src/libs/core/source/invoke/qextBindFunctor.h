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

namespace QExtPrivate
{

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct QExtCountVoid
    {
        static const int value = 0;
    };

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    struct QExtCountVoid<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, void>
    {
        static const int value = 1;
    };

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    struct QExtCountVoid<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, void, void>
    {
        static const int value = 2;
    };

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    struct QExtCountVoid<T_arg1, T_arg2, T_arg3, T_arg4, void, void, void>
    {
        static const int value = 3;
    };

    template <typename T_arg1, typename T_arg2, class T_arg3>
    struct QExtCountVoid<T_arg1, T_arg2, T_arg3, void, void, void, void>
    {
        static const int value = 4;
    };

    template <typename T_arg1, typename T_arg2>
    struct QExtCountVoid<T_arg1, T_arg2, void, void, void, void, void>
    {
        static const int value = 5;
    };

    template <typename T_arg1>
    struct QExtCountVoid<T_arg1, void, void, void, void, void, void>
    {
        static const int value = 6;
    };

    template <>
    struct QExtCountVoid<void, void, void, void, void, void, void>
    {
        static const int value = 7;
    };

} /* namespace QExtPrivate */



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
 *
 * \ingroup adaptors
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
 * \ingroup qextBindFunctor
 */
template <int I_location, typename T_functor,
          typename T_type1 = QExtNil, typename T_type2 = QExtNil, typename T_type3 = QExtNil,
          typename T_type4 = QExtNil, typename T_type5 = QExtNil, typename T_type6 = QExtNil, typename T_type7 = QExtNil> struct QExtBindFunctor;


/** Adaptor that binds an argument to the wrapped functor.
 * This template specialization fixes the 1st argument of the wrapped functor.
 *
 * \ingroup qextBindFunctor
 */
template <typename T_functor, typename T_bound>
struct QExtBindFunctor<0, T_functor, T_bound, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil> : public QExtAdapts<T_functor>
{
    typedef QExtAdapts<T_functor>                     Base;
    typedef typename QExtAdapts<T_functor>::Adaptor   Adaptor;

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void,
              typename T_arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename Adaptor::template ReturnTypeDeduce <
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
            typename QExtTypeTrait<T_arg1>::Pass,
            typename QExtTypeTrait<T_arg2>::Pass,
            typename QExtTypeTrait<T_arg3>::Pass,
            typename QExtTypeTrait<T_arg4>::Pass,
            typename QExtTypeTrait<T_arg5>::Pass,
            typename QExtTypeTrait<T_arg6>::Pass >::Type Type;
    };
    typedef typename Adaptor::Return  Return;

    /** Constructs a bind_functor object that binds an argument to the passed functor.
     * \param func Functor to invoke from operator()().
     * \param bound Argument to qextBindFunctor to the functor.
     */
    QExtBindFunctor(typename QExtTypeTrait<T_functor>::Take func,
                  typename QExtTypeTrait<T_bound>::Take bound)
        : QExtAdapts<T_functor>(func), m_bound(bound) {}

    /** Invokes the wrapped functor passing on the bound argument only.
     * \return The return value of the functor invocation.
     */
    Return operator()()
    {
        //Note: The AIX compiler sometimes gives linker errors if we do not define this in the class.
        return this->m_functor.template operator () <
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass >
               (m_bound.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 1st argument.
     * \param arg1 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template <typename T_arg1>
    typename ReturnTypeDeduce<T_arg1>::Type
    operator()(T_arg1 arg1)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
               typename QExtTypeTrait<T_arg1>::Pass >
               (m_bound.invoke(), arg1);
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 1st argument.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2>
    typename ReturnTypeDeduce<T_arg1, T_arg2>::Type
    operator()(T_arg1 arg1, T_arg2 arg2)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
               typename QExtTypeTrait<T_arg1>::Pass,
               typename QExtTypeTrait<T_arg2>::Pass >
               (m_bound.invoke(), arg1, arg2);
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 1st argument.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \param arg3 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
               typename QExtTypeTrait<T_arg1>::Pass,
               typename QExtTypeTrait<T_arg2>::Pass,
               typename QExtTypeTrait<T_arg3>::Pass >
               (m_bound.invoke(), arg1, arg2, arg3);
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 1st argument.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \param arg3 Argument to be passed on to the functor.
     * \param arg4 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
               typename QExtTypeTrait<T_arg1>::Pass,
               typename QExtTypeTrait<T_arg2>::Pass,
               typename QExtTypeTrait<T_arg3>::Pass,
               typename QExtTypeTrait<T_arg4>::Pass >
               (m_bound.invoke(), arg1, arg2, arg3, arg4);
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 1st argument.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \param arg3 Argument to be passed on to the functor.
     * \param arg4 Argument to be passed on to the functor.
     * \param arg5 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
               typename QExtTypeTrait<T_arg1>::Pass,
               typename QExtTypeTrait<T_arg2>::Pass,
               typename QExtTypeTrait<T_arg3>::Pass,
               typename QExtTypeTrait<T_arg4>::Pass,
               typename QExtTypeTrait<T_arg5>::Pass >
               (m_bound.invoke(), arg1, arg2, arg3, arg4, arg5);
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 1st argument.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \param arg3 Argument to be passed on to the functor.
     * \param arg4 Argument to be passed on to the functor.
     * \param arg5 Argument to be passed on to the functor.
     * \param arg6 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
               typename QExtTypeTrait<T_arg1>::Pass,
               typename QExtTypeTrait<T_arg2>::Pass,
               typename QExtTypeTrait<T_arg3>::Pass,
               typename QExtTypeTrait<T_arg4>::Pass,
               typename QExtTypeTrait<T_arg5>::Pass,
               typename QExtTypeTrait<T_arg6>::Pass >
               (m_bound.invoke(), arg1, arg2, arg3, arg4, arg5, arg6);
    }

    // The argument bound to the functor.
    QExtBoundArgument<T_bound> m_bound;
};

/** Adaptor that binds an argument to the wrapped functor.
 * This template specialization fixes the 2nd argument of the wrapped functor.
 *
 * \ingroup qextBindFunctor
 */
template <typename T_functor, typename T_bound>
struct QExtBindFunctor<1, T_functor, T_bound, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil> : public QExtAdapts<T_functor>
{
    typedef QExtAdapts<T_functor>                         Base;
    typedef typename QExtAdapts<T_functor>::Adaptor       Adaptor;

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename Adaptor::template ReturnTypeDeduce <
            typename QExtTypeTrait<T_arg1>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
            typename QExtTypeTrait<T_arg2>::Pass,
            typename QExtTypeTrait<T_arg3>::Pass,
            typename QExtTypeTrait<T_arg4>::Pass,
            typename QExtTypeTrait<T_arg5>::Pass,
            typename QExtTypeTrait<T_arg6>::Pass >::Type Type;
    };
    typedef typename Adaptor::Return  Return;

    /** Constructs a bind_functor object that binds an argument to the passed functor.
     * \param func Functor to invoke from operator()().
     * \param bound Argument to qextBindFunctor to the functor.
     */
    QExtBindFunctor(typename QExtTypeTrait<T_functor>::Take func,
                  typename QExtTypeTrait<T_bound>::Take bound)
        : QExtAdapts<T_functor>(func), m_bound(bound) {}

    /** Invokes the wrapped functor passing on the bound argument only.
     * \return The return value of the functor invocation.
     */
    Return
    operator()()
    {
        //Note: The AIX compiler sometimes gives linker errors if we do not define this in the class.
        return this->m_functor.template operator () <
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass >
               (m_bound.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 2nd argument.
     * \param arg1 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template <typename T_arg1>
    typename ReturnTypeDeduce<T_arg1>::Type
    operator()(T_arg1 arg1)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<T_arg1>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass >
               (arg1, m_bound.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 2nd argument.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2>
    typename ReturnTypeDeduce<T_arg1, T_arg2>::Type
    operator()(T_arg1 arg1, T_arg2 arg2)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<T_arg1>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
               typename QExtTypeTrait<T_arg2>::Pass >
               (arg1, m_bound.invoke(), arg2);
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 2nd argument.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \param arg3 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<T_arg1>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
               typename QExtTypeTrait<T_arg2>::Pass,
               typename QExtTypeTrait<T_arg3>::Pass >
               (arg1, m_bound.invoke(), arg2, arg3);
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 2nd argument.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \param arg3 Argument to be passed on to the functor.
     * \param arg4 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<T_arg1>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
               typename QExtTypeTrait<T_arg2>::Pass,
               typename QExtTypeTrait<T_arg3>::Pass,
               typename QExtTypeTrait<T_arg4>::Pass >
               (arg1, m_bound.invoke(), arg2, arg3, arg4);
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 2nd argument.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \param arg3 Argument to be passed on to the functor.
     * \param arg4 Argument to be passed on to the functor.
     * \param arg5 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<T_arg1>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
               typename QExtTypeTrait<T_arg2>::Pass,
               typename QExtTypeTrait<T_arg3>::Pass,
               typename QExtTypeTrait<T_arg4>::Pass,
               typename QExtTypeTrait<T_arg5>::Pass >
               (arg1, m_bound.invoke(), arg2, arg3, arg4, arg5);
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 2nd argument.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \param arg3 Argument to be passed on to the functor.
     * \param arg4 Argument to be passed on to the functor.
     * \param arg5 Argument to be passed on to the functor.
     * \param arg6 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<T_arg1>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
               typename QExtTypeTrait<T_arg2>::Pass,
               typename QExtTypeTrait<T_arg3>::Pass,
               typename QExtTypeTrait<T_arg4>::Pass,
               typename QExtTypeTrait<T_arg5>::Pass,
               typename QExtTypeTrait<T_arg6>::Pass >
               (arg1, m_bound.invoke(), arg2, arg3, arg4, arg5, arg6);
    }

    // The argument bound to the functor.
    QExtBoundArgument<T_bound> m_bound;
};


/** Adaptor that binds an argument to the wrapped functor.
 * This template specialization fixes the 3rd argument of the wrapped functor.
 *
 * \ingroup qextBindFunctor
 */
template <typename T_functor, typename T_bound>
struct QExtBindFunctor<2, T_functor, T_bound, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil> : public QExtAdapts<T_functor>
{
    typedef QExtAdapts<T_functor>                         Base;
    typedef typename QExtAdapts<T_functor>::Adaptor       Adaptor;

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename Adaptor::template ReturnTypeDeduce <
            typename QExtTypeTrait<T_arg1>::Pass,
            typename QExtTypeTrait<T_arg2>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
            typename QExtTypeTrait<T_arg3>::Pass,
            typename QExtTypeTrait<T_arg4>::Pass,
            typename QExtTypeTrait<T_arg5>::Pass,
            typename QExtTypeTrait<T_arg6>::Pass >::Type Type;
    };
    typedef typename Adaptor::Return  Return;

    /** Constructs a bind_functor object that binds an argument to the passed functor.
     * \param func Functor to invoke from operator()().
     * \param bound Argument to qextBindFunctor to the functor.
     */
    QExtBindFunctor(typename QExtTypeTrait<T_functor>::Take func, typename QExtTypeTrait<T_bound>::Take bound)
        : QExtAdapts<T_functor>(func), m_bound(bound) {}

    /** Invokes the wrapped functor passing on the bound argument only.
     * \return The return value of the functor invocation.
     */
    Return
    operator()()
    {
        //Note: The AIX compiler sometimes gives linker errors if we do not define this in the class.
        return this->m_functor.template operator () <
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass >
               (m_bound.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 3rd argument.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2>
    typename ReturnTypeDeduce<T_arg1, T_arg2>::Type
    operator()(T_arg1 arg1, T_arg2 arg2)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<T_arg1>::Pass,
               typename QExtTypeTrait<T_arg2>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass >
               (arg1, arg2, m_bound.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 3rd argument.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \param arg3 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<T_arg1>::Pass,
               typename QExtTypeTrait<T_arg2>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
               typename QExtTypeTrait<T_arg3>::Pass >
               (arg1, arg2, m_bound.invoke(), arg3);
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 3rd argument.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \param arg3 Argument to be passed on to the functor.
     * \param arg4 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<T_arg1>::Pass,
               typename QExtTypeTrait<T_arg2>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
               typename QExtTypeTrait<T_arg3>::Pass,
               typename QExtTypeTrait<T_arg4>::Pass >
               (arg1, arg2, m_bound.invoke(), arg3, arg4);
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 3rd argument.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \param arg3 Argument to be passed on to the functor.
     * \param arg4 Argument to be passed on to the functor.
     * \param arg5 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<T_arg1>::Pass,
               typename QExtTypeTrait<T_arg2>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
               typename QExtTypeTrait<T_arg3>::Pass,
               typename QExtTypeTrait<T_arg4>::Pass,
               typename QExtTypeTrait<T_arg5>::Pass >
               (arg1, arg2, m_bound.invoke(), arg3, arg4, arg5);
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 3rd argument.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \param arg3 Argument to be passed on to the functor.
     * \param arg4 Argument to be passed on to the functor.
     * \param arg5 Argument to be passed on to the functor.
     * \param arg6 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<T_arg1>::Pass,
               typename QExtTypeTrait<T_arg2>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
               typename QExtTypeTrait<T_arg3>::Pass,
               typename QExtTypeTrait<T_arg4>::Pass,
               typename QExtTypeTrait<T_arg5>::Pass,
               typename QExtTypeTrait<T_arg6>::Pass >
               (arg1, arg2, m_bound.invoke(), arg3, arg4, arg5, arg6);
    }

    // The argument bound to the functor.
    QExtBoundArgument<T_bound> m_bound;
};


/** Adaptor that binds an argument to the wrapped functor.
 * This template specialization fixes the 4th argument of the wrapped functor.
 *
 * \ingroup qextBindFunctor
 */
template <typename T_functor, typename T_bound>
struct QExtBindFunctor<3, T_functor, T_bound, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil> : public QExtAdapts<T_functor>
{
    typedef QExtAdapts<T_functor>                         Base;
    typedef typename QExtAdapts<T_functor>::Adaptor       Adaptor;

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename Adaptor::template ReturnTypeDeduce <
            typename QExtTypeTrait<T_arg1>::Pass,
            typename QExtTypeTrait<T_arg2>::Pass,
            typename QExtTypeTrait<T_arg3>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
            typename QExtTypeTrait<T_arg4>::Pass,
            typename QExtTypeTrait<T_arg5>::Pass,
            typename QExtTypeTrait<T_arg6>::Pass >::Type Type;
    };
    typedef typename Adaptor::Return  Return;

    /** Constructs a bind_functor object that binds an argument to the passed functor.
     * \param func Functor to invoke from operator()().
     * \param bound Argument to qextBindFunctor to the functor.
     */
    QExtBindFunctor(typename QExtTypeTrait<T_functor>::Take func, typename QExtTypeTrait<T_bound>::Take bound)
        : QExtAdapts<T_functor>(func), m_bound(bound) {}

    /** Invokes the wrapped functor passing on the bound argument only.
     * \return The return value of the functor invocation.
     */
    Return
    operator()()
    {
        //Note: The AIX compiler sometimes gives linker errors if we do not define this in the class.
        return this->m_functor.template operator () <
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass >
               (m_bound.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 4th argument.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \param arg3 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<T_arg1>::Pass,
               typename QExtTypeTrait<T_arg2>::Pass,
               typename QExtTypeTrait<T_arg3>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass >
               (arg1, arg2, arg3, m_bound.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 4th argument.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \param arg3 Argument to be passed on to the functor.
     * \param arg4 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<T_arg1>::Pass,
               typename QExtTypeTrait<T_arg2>::Pass,
               typename QExtTypeTrait<T_arg3>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
               typename QExtTypeTrait<T_arg4>::Pass >
               (arg1, arg2, arg3, m_bound.invoke(), arg4);
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 4th argument.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \param arg3 Argument to be passed on to the functor.
     * \param arg4 Argument to be passed on to the functor.
     * \param arg5 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<T_arg1>::Pass,
               typename QExtTypeTrait<T_arg2>::Pass,
               typename QExtTypeTrait<T_arg3>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
               typename QExtTypeTrait<T_arg4>::Pass,
               typename QExtTypeTrait<T_arg5>::Pass >
               (arg1, arg2, arg3, m_bound.invoke(), arg4, arg5);
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 4th argument.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \param arg3 Argument to be passed on to the functor.
     * \param arg4 Argument to be passed on to the functor.
     * \param arg5 Argument to be passed on to the functor.
     * \param arg6 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<T_arg1>::Pass,
               typename QExtTypeTrait<T_arg2>::Pass,
               typename QExtTypeTrait<T_arg3>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
               typename QExtTypeTrait<T_arg4>::Pass,
               typename QExtTypeTrait<T_arg5>::Pass,
               typename QExtTypeTrait<T_arg6>::Pass >
               (arg1, arg2, arg3, m_bound.invoke(), arg4, arg5, arg6);
    }

    // The argument bound to the functor.
    QExtBoundArgument<T_bound> m_bound;
};

/** Adaptor that binds an argument to the wrapped functor.
 * This template specialization fixes the 5th argument of the wrapped functor.
 *
 * \ingroup qextBindFunctor
 */
template <typename T_functor, typename T_bound>
struct QExtBindFunctor<4, T_functor, T_bound, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil> : public QExtAdapts<T_functor>
{
    typedef QExtAdapts<T_functor>                         Base;
    typedef typename QExtAdapts<T_functor>::Adaptor       Adaptor;

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename Adaptor::template ReturnTypeDeduce <
            typename QExtTypeTrait<T_arg1>::Pass,
            typename QExtTypeTrait<T_arg2>::Pass,
            typename QExtTypeTrait<T_arg3>::Pass,
            typename QExtTypeTrait<T_arg4>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
            typename QExtTypeTrait<T_arg5>::Pass,
            typename QExtTypeTrait<T_arg6>::Pass >::Type Type;
    };
    typedef typename Adaptor::Return  Return;

    /** Constructs a bind_functor object that binds an argument to the passed functor.
     * \param func Functor to invoke from operator()().
     * \param bound Argument to qextBindFunctor to the functor.
     */
    QExtBindFunctor(typename QExtTypeTrait<T_functor>::Take func, typename QExtTypeTrait<T_bound>::Take bound)
        : QExtAdapts<T_functor>(func), m_bound(bound) {}

    /** Invokes the wrapped functor passing on the bound argument only.
     * \return The return value of the functor invocation.
     */
    Return
    operator()()
    {
        //Note: The AIX compiler sometimes gives linker errors if we do not define this in the class.
        return this->m_functor.template operator () <
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass >
               (m_bound.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 5th argument.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \param arg3 Argument to be passed on to the functor.
     * \param arg4 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<T_arg1>::Pass,
               typename QExtTypeTrait<T_arg2>::Pass,
               typename QExtTypeTrait<T_arg3>::Pass,
               typename QExtTypeTrait<T_arg4>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass >
               (arg1, arg2, arg3, arg4, m_bound.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 5th argument.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \param arg3 Argument to be passed on to the functor.
     * \param arg4 Argument to be passed on to the functor.
     * \param arg5 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<T_arg1>::Pass,
               typename QExtTypeTrait<T_arg2>::Pass,
               typename QExtTypeTrait<T_arg3>::Pass,
               typename QExtTypeTrait<T_arg4>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
               typename QExtTypeTrait<T_arg5>::Pass >
               (arg1, arg2, arg3, arg4, m_bound.invoke(), arg5);
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 5th argument.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \param arg3 Argument to be passed on to the functor.
     * \param arg4 Argument to be passed on to the functor.
     * \param arg5 Argument to be passed on to the functor.
     * \param arg6 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<T_arg1>::Pass,
               typename QExtTypeTrait<T_arg2>::Pass,
               typename QExtTypeTrait<T_arg3>::Pass,
               typename QExtTypeTrait<T_arg4>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
               typename QExtTypeTrait<T_arg5>::Pass,
               typename QExtTypeTrait<T_arg6>::Pass >
               (arg1, arg2, arg3, arg4, m_bound.invoke(), arg5, arg6);
    }

    // The argument bound to the functor.
    QExtBoundArgument<T_bound> m_bound;
};


/** Adaptor that binds an argument to the wrapped functor.
 * This template specialization fixes the 6th argument of the wrapped functor.
 *
 * \ingroup qextBindFunctor
 */
template <typename T_functor, typename T_bound>
struct QExtBindFunctor<5, T_functor, T_bound, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil> : public QExtAdapts<T_functor>
{
    typedef QExtAdapts<T_functor>                         Base;
    typedef typename QExtAdapts<T_functor>::Adaptor       Adaptor;

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename Adaptor::template ReturnTypeDeduce <
            typename QExtTypeTrait<T_arg1>::Pass,
            typename QExtTypeTrait<T_arg2>::Pass,
            typename QExtTypeTrait<T_arg3>::Pass,
            typename QExtTypeTrait<T_arg4>::Pass,
            typename QExtTypeTrait<T_arg5>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
            typename QExtTypeTrait<T_arg6>::Pass >::Type Type;
    };
    typedef typename Adaptor::Return  Return;

    /** Constructs a bind_functor object that binds an argument to the passed functor.
     * \param func Functor to invoke from operator()().
     * \param bound Argument to qextBindFunctor to the functor.
     */
    QExtBindFunctor(typename QExtTypeTrait<T_functor>::Take func, typename QExtTypeTrait<T_bound>::Take bound)
        : QExtAdapts<T_functor>(func), m_bound(bound) {}

    /** Invokes the wrapped functor passing on the bound argument only.
     * \return The return value of the functor invocation.
     */
    Return
    operator()()
    {
        //Note: The AIX compiler sometimes gives linker errors if we do not define this in the class.
        return this->m_functor.template operator () <
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass >
               (m_bound.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 6th argument.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \param arg3 Argument to be passed on to the functor.
     * \param arg4 Argument to be passed on to the functor.
     * \param arg5 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<T_arg1>::Pass,
               typename QExtTypeTrait<T_arg2>::Pass,
               typename QExtTypeTrait<T_arg3>::Pass,
               typename QExtTypeTrait<T_arg4>::Pass,
               typename QExtTypeTrait<T_arg5>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass >
               (arg1, arg2, arg3, arg4, arg5, m_bound.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 6th argument.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \param arg3 Argument to be passed on to the functor.
     * \param arg4 Argument to be passed on to the functor.
     * \param arg5 Argument to be passed on to the functor.
     * \param arg6 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<T_arg1>::Pass,
               typename QExtTypeTrait<T_arg2>::Pass,
               typename QExtTypeTrait<T_arg3>::Pass,
               typename QExtTypeTrait<T_arg4>::Pass,
               typename QExtTypeTrait<T_arg5>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass,
               typename QExtTypeTrait<T_arg6>::Pass >
               (arg1, arg2, arg3, arg4, arg5, m_bound.invoke(), arg6);
    }

    // The argument bound to the functor.
    QExtBoundArgument<T_bound> m_bound;
};


/** Adaptor that binds an argument to the wrapped functor.
 * This template specialization fixes the 7th argument of the wrapped functor.
 *
 * \ingroup qextBindFunctor
 */
template <typename T_functor, typename T_bound>
struct QExtBindFunctor<6, T_functor, T_bound, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil> : public QExtAdapts<T_functor>
{
    typedef QExtAdapts<T_functor>                         Base;
    typedef typename QExtAdapts<T_functor>::Adaptor       Adaptor;

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename Adaptor::template ReturnTypeDeduce <
            typename QExtTypeTrait<T_arg1>::Pass,
            typename QExtTypeTrait<T_arg2>::Pass,
            typename QExtTypeTrait<T_arg3>::Pass,
            typename QExtTypeTrait<T_arg4>::Pass,
            typename QExtTypeTrait<T_arg5>::Pass,
            typename QExtTypeTrait<T_arg6>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass >::Type Type;
    };
    typedef typename Adaptor::Return  Return;

    /** Constructs a bind_functor object that binds an argument to the passed functor.
     * \param func Functor to invoke from operator()().
     * \param bound Argument to qextBindFunctor to the functor.
     */
    QExtBindFunctor(typename QExtTypeTrait<T_functor>::Take func, typename QExtTypeTrait<T_bound>::Take bound)
        : QExtAdapts<T_functor>(func), m_bound(bound) {}

    /** Invokes the wrapped functor passing on the bound argument only.
     * \return The return value of the functor invocation.
     */
    Return
    operator()()
    {
        //Note: The AIX compiler sometimes gives linker errors if we do not define this in the class.
        return this->m_functor.template operator () <
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass >
               (m_bound.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * m_bound is passed as the 7th argument.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \param arg3 Argument to be passed on to the functor.
     * \param arg4 Argument to be passed on to the functor.
     * \param arg5 Argument to be passed on to the functor.
     * \param arg6 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<T_arg1>::Pass,
               typename QExtTypeTrait<T_arg2>::Pass,
               typename QExtTypeTrait<T_arg3>::Pass,
               typename QExtTypeTrait<T_arg4>::Pass,
               typename QExtTypeTrait<T_arg5>::Pass,
               typename QExtTypeTrait<T_arg6>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_bound>::Type>::Pass >
               (arg1, arg2, arg3, arg4, arg5, arg6, m_bound.invoke());
    }

    // The argument bound to the functor.
    QExtBoundArgument<T_bound> m_bound;
};

//template specialization of QExtVisitor<>::doVisitEach<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for qextBindFunctor performs a functor on the
 * functor and on the object instances stored in the qextBindFunctor object.
 *
 * \ingroup qextBindFunctor
 */
template <int T_loc, typename T_functor, typename T_bound>
struct QExtVisitor<QExtBindFunctor<T_loc, T_functor, T_bound> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QExtBindFunctor<T_loc, T_functor, T_bound> &target)
    {
        qextVisitEach(action, target.m_functor);
        qextVisitEach(action, target.m_bound);
    }
};

/** Adaptor that binds 1 argument(s) to the wrapped functor.
 * This template specialization fixes the last 1 argument(s) of the wrapped functor.
 *
 * \ingroup qextBindFunctor
 */
template <typename T_functor, typename T_type1>
struct QExtBindFunctor<-1, T_functor, T_type1, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil > : public QExtAdapts<T_functor>
{
    typedef QExtAdapts<T_functor>                         Base;
    typedef typename QExtAdapts<T_functor>::Adaptor       Adaptor;

    template <int count,
              typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalReturnTypeDeduce
    {
        typedef typename Adaptor::template ReturnTypeDeduce <
            typename QExtTypeTrait<T_arg1>::Pass,
            typename QExtTypeTrait<T_arg2>::Pass,
            typename QExtTypeTrait<T_arg3>::Pass,
            typename QExtTypeTrait<T_arg4>::Pass,
            typename QExtTypeTrait<T_arg5>::Pass,
            typename QExtTypeTrait<T_arg6>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass >::Type Type;
    };

    template <typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalReturnTypeDeduce<2, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
    {
        typedef typename Adaptor::template ReturnTypeDeduce <
            typename QExtTypeTrait<T_arg1>::Pass,
            typename QExtTypeTrait<T_arg2>::Pass,
            typename QExtTypeTrait<T_arg3>::Pass,
            typename QExtTypeTrait<T_arg4>::Pass,
            typename QExtTypeTrait<T_arg5>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass >::Type Type;
    };

    template <typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalReturnTypeDeduce<3, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
    {
        typedef typename Adaptor::template ReturnTypeDeduce <
            typename QExtTypeTrait<T_arg1>::Pass,
            typename QExtTypeTrait<T_arg2>::Pass,
            typename QExtTypeTrait<T_arg3>::Pass,
            typename QExtTypeTrait<T_arg4>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass >::Type Type;
    };

    template <typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalReturnTypeDeduce<4, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
    {
        typedef typename Adaptor::template ReturnTypeDeduce <
            typename QExtTypeTrait<T_arg1>::Pass,
            typename QExtTypeTrait<T_arg2>::Pass,
            typename QExtTypeTrait<T_arg3>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass >::Type Type;
    };

    template <typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalReturnTypeDeduce<5, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
    {
        typedef typename Adaptor::template ReturnTypeDeduce <
            typename QExtTypeTrait<T_arg1>::Pass,
            typename QExtTypeTrait<T_arg2>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass >::Type Type;
    };

    template <typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalReturnTypeDeduce<6, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
    {
        typedef typename Adaptor::template ReturnTypeDeduce <
            typename QExtTypeTrait<T_arg1>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass >::Type Type;
    };

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename InternalReturnTypeDeduce <
        QExtPrivate::QExtCountVoid<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::value,
               T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >::Type Type;
    };

    typedef typename Adaptor::Return  Return;

    /** Constructs a bind_functor object that binds an argument to the passed functor.
     * \param func Functor to invoke from operator()().
     * \param bound1 Argument to qextBindFunctor to the functor.
     */
    QExtBindFunctor(typename QExtTypeTrait<T_functor>::Take func, typename QExtTypeTrait<T_type1>::Take bound1)
        : QExtAdapts<T_functor>(func), m_bound1(bound1) {}

    /** Invokes the wrapped functor passing on the bound argument only.
     * \return The return value of the functor invocation.
     */
    Return
    operator()()
    {
        //Note: The AIX compiler sometimes gives linker errors if we do not define this in the class.
        return this->m_functor.template operator () <
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass >
               (m_bound1.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * The last 1 argument(s) are fixed.
     * \param arg1 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template <typename T_arg1>
    typename ReturnTypeDeduce<T_arg1>::Type
    operator()(T_arg1 arg1)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<T_arg1>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass >
               (arg1, m_bound1.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * The last 1 argument(s) are fixed.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2>
    typename ReturnTypeDeduce<T_arg1, T_arg2>::Type
    operator()(T_arg1 arg1, T_arg2 arg2)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<T_arg1>::Pass,
               typename QExtTypeTrait<T_arg2>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass >
               (arg1, arg2, m_bound1.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * The last 1 argument(s) are fixed.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \param arg3 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<T_arg1>::Pass,
               typename QExtTypeTrait<T_arg2>::Pass,
               typename QExtTypeTrait<T_arg3>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass >
               (arg1, arg2, arg3, m_bound1.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * The last 1 argument(s) are fixed.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \param arg3 Argument to be passed on to the functor.
     * \param arg4 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<T_arg1>::Pass,
               typename QExtTypeTrait<T_arg2>::Pass,
               typename QExtTypeTrait<T_arg3>::Pass,
               typename QExtTypeTrait<T_arg4>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass >
               (arg1, arg2, arg3, arg4, m_bound1.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * The last 1 argument(s) are fixed.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \param arg3 Argument to be passed on to the functor.
     * \param arg4 Argument to be passed on to the functor.
     * \param arg5 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<T_arg1>::Pass,
               typename QExtTypeTrait<T_arg2>::Pass,
               typename QExtTypeTrait<T_arg3>::Pass,
               typename QExtTypeTrait<T_arg4>::Pass,
               typename QExtTypeTrait<T_arg5>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass >
               (arg1, arg2, arg3, arg4, arg5, m_bound1.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * The last 1 argument(s) are fixed.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \param arg3 Argument to be passed on to the functor.
     * \param arg4 Argument to be passed on to the functor.
     * \param arg5 Argument to be passed on to the functor.
     * \param arg6 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<T_arg1>::Pass,
               typename QExtTypeTrait<T_arg2>::Pass,
               typename QExtTypeTrait<T_arg3>::Pass,
               typename QExtTypeTrait<T_arg4>::Pass,
               typename QExtTypeTrait<T_arg5>::Pass,
               typename QExtTypeTrait<T_arg6>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass >
               (arg1, arg2, arg3, arg4, arg5, arg6, m_bound1.invoke());
    }

    // The argument bound to the functor.
    QExtBoundArgument<T_type1> m_bound1;
};

//template specialization of QExtVisitor<>::doVisitEach<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for qextBindFunctor performs a functor on the
 * functor and on the object instances stored in the qextBindFunctor object.
 *
 * \ingroup qextBindFunctor
 */
template <typename T_functor, typename T_type1>
struct QExtVisitor<QExtBindFunctor<-1, T_functor, T_type1> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QExtBindFunctor<-1, T_functor,  T_type1 > &target)
    {
        qextVisitEach(action, target.m_functor);
        qextVisitEach(action, target.m_bound1);
    }
};


/** Adaptor that binds 2 argument(s) to the wrapped functor.
 * This template specialization fixes the last 2 argument(s) of the wrapped functor.
 *
 * \ingroup qextBindFunctor
 */
template <typename T_functor, typename T_type1, typename T_type2>
struct QExtBindFunctor<-1, T_functor, T_type1, T_type2, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil > : public QExtAdapts<T_functor>
{
    typedef QExtAdapts<T_functor>                         Base;
    typedef typename QExtAdapts<T_functor>::Adaptor   Adaptor;

    template <int count,
              typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalReturnTypeDeduce
    {
        typedef typename Adaptor::template ReturnTypeDeduce <
            typename QExtTypeTrait<T_arg1>::Pass,
            typename QExtTypeTrait<T_arg2>::Pass,
            typename QExtTypeTrait<T_arg3>::Pass,
            typename QExtTypeTrait<T_arg4>::Pass,
            typename QExtTypeTrait<T_arg5>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass >::Type Type;
    };

    template <typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalReturnTypeDeduce<3, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
    {
        typedef typename Adaptor::template ReturnTypeDeduce <
            typename QExtTypeTrait<T_arg1>::Pass,
            typename QExtTypeTrait<T_arg2>::Pass,
            typename QExtTypeTrait<T_arg3>::Pass,
            typename QExtTypeTrait<T_arg4>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass >::Type Type;
    };

    template <typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalReturnTypeDeduce<4, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
    {
        typedef typename Adaptor::template ReturnTypeDeduce <
            typename QExtTypeTrait<T_arg1>::Pass,
            typename QExtTypeTrait<T_arg2>::Pass,
            typename QExtTypeTrait<T_arg3>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass >::Type Type;
    };

    template <typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalReturnTypeDeduce<5, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
    {
        typedef typename Adaptor::template ReturnTypeDeduce <
            typename QExtTypeTrait<T_arg1>::Pass,
            typename QExtTypeTrait<T_arg2>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass >::Type Type;
    };

    template <typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalReturnTypeDeduce<6, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
    {
        typedef typename Adaptor::template ReturnTypeDeduce <
            typename QExtTypeTrait<T_arg1>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass >::Type Type;
    };

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename InternalReturnTypeDeduce <
        QExtPrivate::QExtCountVoid<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::value,
               T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >::Type Type;
    };
    typedef typename Adaptor::Return  Return;

    /** Constructs a bind_functor object that binds an argument to the passed functor.
     * \param func Functor to invoke from operator()().
     * \param bound1 Argument to qextBindFunctor to the functor.
     * \param bound2 Argument to qextBindFunctor to the functor.
     */
    QExtBindFunctor(typename QExtTypeTrait<T_functor>::Take func,
                  typename QExtTypeTrait<T_type1>::Take bound1,
                  typename QExtTypeTrait<T_type2>::Take bound2)
        : QExtAdapts<T_functor>(func), m_bound1(bound1), m_bound2(bound2) {}

    /** Invokes the wrapped functor passing on the bound argument only.
     * \return The return value of the functor invocation.
     */
    Return
    operator()()
    {
        //Note: The AIX compiler sometimes gives linker errors if we do not define this in the class.
        return this->m_functor.template operator () <
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass >
               (m_bound1.invoke(), m_bound2.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * The last 2 argument(s) are fixed.
     * \param arg1 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template <typename T_arg1>
    typename ReturnTypeDeduce<T_arg1>::Type
    operator()(T_arg1 arg1)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<T_arg1>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass >
               (arg1, m_bound1.invoke(), m_bound2.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * The last 2 argument(s) are fixed.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2>
    typename ReturnTypeDeduce<T_arg1, T_arg2>::Type
    operator()(T_arg1 arg1, T_arg2 arg2)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<T_arg1>::Pass,
               typename QExtTypeTrait<T_arg2>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass >
               (arg1, arg2, m_bound1.invoke(), m_bound2.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * The last 2 argument(s) are fixed.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \param arg3 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<T_arg1>::Pass,
               typename QExtTypeTrait<T_arg2>::Pass,
               typename QExtTypeTrait<T_arg3>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass >
               (arg1, arg2, arg3, m_bound1.invoke(), m_bound2.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * The last 2 argument(s) are fixed.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \param arg3 Argument to be passed on to the functor.
     * \param arg4 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<T_arg1>::Pass,
               typename QExtTypeTrait<T_arg2>::Pass,
               typename QExtTypeTrait<T_arg3>::Pass,
               typename QExtTypeTrait<T_arg4>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass >
               (arg1, arg2, arg3, arg4, m_bound1.invoke(), m_bound2.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * The last 2 argument(s) are fixed.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \param arg3 Argument to be passed on to the functor.
     * \param arg4 Argument to be passed on to the functor.
     * \param arg5 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<T_arg1>::Pass,
               typename QExtTypeTrait<T_arg2>::Pass,
               typename QExtTypeTrait<T_arg3>::Pass,
               typename QExtTypeTrait<T_arg4>::Pass,
               typename QExtTypeTrait<T_arg5>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass >
               (arg1, arg2, arg3, arg4, arg5, m_bound1.invoke(), m_bound2.invoke());
    }

    // The argument bound to the functor.
    QExtBoundArgument<T_type1> m_bound1;
    QExtBoundArgument<T_type2> m_bound2;
};


//template specialization of QExtVisitor<>::doVisitEach<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for qextBindFunctor performs a functor on the
 * functor and on the object instances stored in the qextBindFunctor object.
 *
 * \ingroup qextBindFunctor
 */
template <typename T_functor, typename T_type1, typename T_type2>
struct QExtVisitor < QExtBindFunctor<-1, T_functor, T_type1, T_type2 > >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QExtBindFunctor<-1, T_functor,  T_type1, T_type2 > &target)
    {
        qextVisitEach(action, target.m_functor);
        qextVisitEach(action, target.m_bound1);
        qextVisitEach(action, target.m_bound2);
    }
};


/** Adaptor that binds 3 argument(s) to the wrapped functor.
 * This template specialization fixes the last 3 argument(s) of the wrapped functor.
 *
 * \ingroup qextBindFunctor
 */
template <typename T_functor, typename T_type1, typename T_type2, typename T_type3>
struct QExtBindFunctor<-1, T_functor, T_type1, T_type2, T_type3, QExtNil, QExtNil, QExtNil, QExtNil > : public QExtAdapts<T_functor>
{
    typedef QExtAdapts<T_functor>                         Base;
    typedef typename QExtAdapts<T_functor>::Adaptor       Adaptor;

    template <int count,
              typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalReturnTypeDeduce
    {
        typedef typename Adaptor::template ReturnTypeDeduce <
            typename QExtTypeTrait<T_arg1>::Pass,
            typename QExtTypeTrait<T_arg2>::Pass,
            typename QExtTypeTrait<T_arg3>::Pass,
            typename QExtTypeTrait<T_arg4>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass >::Type Type;
    };

    template <typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalReturnTypeDeduce<4, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
    {
        typedef typename Adaptor::template ReturnTypeDeduce <
            typename QExtTypeTrait<T_arg1>::Pass,
            typename QExtTypeTrait<T_arg2>::Pass,
            typename QExtTypeTrait<T_arg3>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass >::Type Type;
    };

    template <typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalReturnTypeDeduce<5, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
    {
        typedef typename Adaptor::template ReturnTypeDeduce <
            typename QExtTypeTrait<T_arg1>::Pass,
            typename QExtTypeTrait<T_arg2>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass >::Type Type;
    };

    template <typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalReturnTypeDeduce<6, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
    {
        typedef typename Adaptor::template ReturnTypeDeduce <
            typename QExtTypeTrait<T_arg1>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass >::Type Type;
    };

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename InternalReturnTypeDeduce <
        QExtPrivate::QExtCountVoid<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::value,
               T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >::Type Type;
    };
    typedef typename Adaptor::Return  Return;

    /** Constructs a bind_functor object that binds an argument to the passed functor.
     * \param func Functor to invoke from operator()().
     * \param bound1 Argument to qextBindFunctor to the functor.
     * \param bound2 Argument to qextBindFunctor to the functor.
     * \param bound3 Argument to qextBindFunctor to the functor.
     */
    QExtBindFunctor(typename QExtTypeTrait<T_functor>::Take func,
                  typename QExtTypeTrait<T_type1>::Take bound1,
                  typename QExtTypeTrait<T_type2>::Take bound2,
                  typename QExtTypeTrait<T_type3>::Take bound3)
        : QExtAdapts<T_functor>(func), m_bound1(bound1), m_bound2(bound2), m_bound3(bound3) {}

    /** Invokes the wrapped functor passing on the bound argument only.
     * \return The return value of the functor invocation.
     */
    Return
    operator()()
    {
        //Note: The AIX compiler sometimes gives linker errors if we do not define this in the class.
        return this->m_functor.template operator () <
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass >
               (m_bound1.invoke(), m_bound2.invoke(), m_bound3.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * The last 3 argument(s) are fixed.
     * \param arg1 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template <typename T_arg1>
    typename ReturnTypeDeduce<T_arg1>::Type
    operator()(T_arg1 arg1)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<T_arg1>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass >
               (arg1, m_bound1.invoke(), m_bound2.invoke(), m_bound3.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * The last 3 argument(s) are fixed.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2>
    typename ReturnTypeDeduce<T_arg1, T_arg2>::Type
    operator()(T_arg1 arg1, T_arg2 arg2)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<T_arg1>::Pass,
               typename QExtTypeTrait<T_arg2>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass >
               (arg1, arg2, m_bound1.invoke(), m_bound2.invoke(), m_bound3.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * The last 3 argument(s) are fixed.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \param arg3 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<T_arg1>::Pass,
               typename QExtTypeTrait<T_arg2>::Pass,
               typename QExtTypeTrait<T_arg3>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass >
               (arg1, arg2, arg3, m_bound1.invoke(), m_bound2.invoke(), m_bound3.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * The last 3 argument(s) are fixed.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \param arg3 Argument to be passed on to the functor.
     * \param arg4 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4)
    {
        return this->m_functor(arg1, arg2, arg3, arg4, m_bound1.invoke(), m_bound2.invoke(), m_bound3.invoke());
        return this->m_functor.template operator () <
               typename QExtTypeTrait<T_arg1>::Pass,
               typename QExtTypeTrait<T_arg2>::Pass,
               typename QExtTypeTrait<T_arg3>::Pass,
               typename QExtTypeTrait<T_arg4>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass >
               (arg1, arg2, arg3, arg4, m_bound1.invoke(), m_bound2.invoke(), m_bound3.invoke());
    }

    // The argument bound to the functor.
    QExtBoundArgument<T_type1> m_bound1;
    QExtBoundArgument<T_type2> m_bound2;
    QExtBoundArgument<T_type3> m_bound3;
};


//template specialization of QExtVisitor<>::doVisitEach<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for qextBindFunctor performs a functor on the
 * functor and on the object instances stored in the qextBindFunctor object.
 *
 * \ingroup qextBindFunctor
 */
template <typename T_functor, typename T_type1, typename T_type2, typename T_type3>
struct QExtVisitor<QExtBindFunctor<-1, T_functor, T_type1, T_type2, T_type3 > >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QExtBindFunctor<-1, T_functor,  T_type1, T_type2, T_type3 > &target)
    {
        qextVisitEach(action, target.m_functor);
        qextVisitEach(action, target.m_bound1);
        qextVisitEach(action, target.m_bound2);
        qextVisitEach(action, target.m_bound3);
    }
};


/** Adaptor that binds 4 argument(s) to the wrapped functor.
 * This template specialization fixes the last 4 argument(s) of the wrapped functor.
 *
 * \ingroup qextBindFunctor
 */
template <typename T_functor,
          typename T_type1, typename T_type2, typename T_type3, typename T_type4>
struct QExtBindFunctor<-1, T_functor, T_type1, T_type2, T_type3, T_type4, QExtNil, QExtNil, QExtNil > : public QExtAdapts<T_functor>
{
    typedef QExtAdapts<T_functor>                         Base;
    typedef typename QExtAdapts<T_functor>::Adaptor       Adaptor;

    template <int count,
              typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalReturnTypeDeduce
    {
        typedef typename Adaptor::template ReturnTypeDeduce <
            typename QExtTypeTrait<T_arg1>::Pass,
            typename QExtTypeTrait<T_arg2>::Pass,
            typename QExtTypeTrait<T_arg3>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type4>::Type>::Pass >::Type Type;
    };

    template <typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalReturnTypeDeduce<5, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
    {
        typedef typename Adaptor::template ReturnTypeDeduce <
            typename QExtTypeTrait<T_arg1>::Pass,
            typename QExtTypeTrait<T_arg2>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type4>::Type>::Pass >::Type Type;
    };

    template <typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalReturnTypeDeduce<6, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
    {
        typedef typename Adaptor::template ReturnTypeDeduce <
            typename QExtTypeTrait<T_arg1>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type4>::Type>::Pass >::Type Type;
    };

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename InternalReturnTypeDeduce <
        QExtPrivate::QExtCountVoid<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::value,
               T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >::Type Type;
    };
    typedef typename Adaptor::Return  Return;

    /** Constructs a bind_functor object that binds an argument to the passed functor.
     * \param func Functor to invoke from operator()().
     * \param bound1 Argument to qextBindFunctor to the functor.
     * \param bound2 Argument to qextBindFunctor to the functor.
     * \param bound3 Argument to qextBindFunctor to the functor.
     * \param bound4 Argument to qextBindFunctor to the functor.
     */
    QExtBindFunctor(typename QExtTypeTrait<T_functor>::Take func,
                  typename QExtTypeTrait<T_type1>::Take bound1,
                  typename QExtTypeTrait<T_type2>::Take bound2,
                  typename QExtTypeTrait<T_type3>::Take bound3,
                  typename QExtTypeTrait<T_type4>::Take bound4)
        : QExtAdapts<T_functor>(func), m_bound1(bound1), m_bound2(bound2), m_bound3(bound3), m_bound4(bound4) {}

    /** Invokes the wrapped functor passing on the bound argument only.
     * \return The return value of the functor invocation.
     */
    Return
    operator()()
    {
        //Note: The AIX compiler sometimes gives linker errors if we do not define this in the class.
        return this->m_functor.template operator () <
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type4>::Type>::Pass >
               (m_bound1.invoke(), m_bound2.invoke(), m_bound3.invoke(), m_bound4.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * The last 4 argument(s) are fixed.
     * \param arg1 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template <typename T_arg1>
    typename ReturnTypeDeduce<T_arg1>::Type
    operator()(T_arg1 arg1)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<T_arg1>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type4>::Type>::Pass >
               (arg1, m_bound1.invoke(), m_bound2.invoke(), m_bound3.invoke(), m_bound4.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * The last 4 argument(s) are fixed.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2>
    typename ReturnTypeDeduce<T_arg1, T_arg2>::Type
    operator()(T_arg1 arg1, T_arg2 arg2)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<T_arg1>::Pass,
               typename QExtTypeTrait<T_arg2>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type4>::Type>::Pass >
               (arg1, arg2, m_bound1.invoke(), m_bound2.invoke(), m_bound3.invoke(), m_bound4.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * The last 4 argument(s) are fixed.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \param arg3 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<T_arg1>::Pass,
               typename QExtTypeTrait<T_arg2>::Pass,
               typename QExtTypeTrait<T_arg3>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type4>::Type>::Pass >
               (arg1, arg2, arg3, m_bound1.invoke(), m_bound2.invoke(), m_bound3.invoke(), m_bound4.invoke());
    }

    // The argument bound to the functor.
    QExtBoundArgument<T_type1> m_bound1;
    QExtBoundArgument<T_type2> m_bound2;
    QExtBoundArgument<T_type3> m_bound3;
    QExtBoundArgument<T_type4> m_bound4;
};


//template specialization of QExtVisitor<>::doVisitEach<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for qextBindFunctor performs a functor on the
 * functor and on the object instances stored in the qextBindFunctor object.
 *
 * \ingroup qextBindFunctor
 */
template <typename T_functor, typename T_type1, typename T_type2, typename T_type3, typename T_type4>
struct QExtVisitor<QExtBindFunctor<-1, T_functor, T_type1, T_type2, T_type3, T_type4> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QExtBindFunctor<-1, T_functor,  T_type1, T_type2, T_type3, T_type4 > &target)
    {
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
 * \ingroup qextBindFunctor
 */
template <typename T_functor,
          typename T_type1, typename T_type2, typename T_type3, typename T_type4, typename T_type5>
struct QExtBindFunctor<-1, T_functor, T_type1, T_type2, T_type3, T_type4, T_type5, QExtNil, QExtNil > : public QExtAdapts<T_functor>
{
    typedef QExtAdapts<T_functor>                         Base;
    typedef typename QExtAdapts<T_functor>::Adaptor   Adaptor;

    template <int count,
              typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalReturnTypeDeduce
    {
        typedef typename Adaptor::template ReturnTypeDeduce <
            typename QExtTypeTrait<T_arg1>::Pass,
            typename QExtTypeTrait<T_arg2>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type4>::Type>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type5>::Type>::Pass >::Type Type;
    };

    template <typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalReturnTypeDeduce<6, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
    {
        typedef typename Adaptor::template ReturnTypeDeduce <
            typename QExtTypeTrait<T_arg1>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type4>::Type>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type5>::Type>::Pass >::Type Type;
    };

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename InternalReturnTypeDeduce <
        QExtPrivate::QExtCountVoid<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::value,
               T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >::Type Type;
    };
    typedef typename Adaptor::Return  Return;

    /** Constructs a bind_functor object that binds an argument to the passed functor.
     * \param func Functor to invoke from operator()().
     * \param bound1 Argument to qextBindFunctor to the functor.
     * \param bound2 Argument to qextBindFunctor to the functor.
     * \param bound3 Argument to qextBindFunctor to the functor.
     * \param bound4 Argument to qextBindFunctor to the functor.
     * \param bound5 Argument to qextBindFunctor to the functor.
     */
    QExtBindFunctor(typename QExtTypeTrait<T_functor>::Take func,
                  typename QExtTypeTrait<T_type1>::Take bound1,
                  typename QExtTypeTrait<T_type2>::Take bound2,
                  typename QExtTypeTrait<T_type3>::Take bound3,
                  typename QExtTypeTrait<T_type4>::Take bound4,
                  typename QExtTypeTrait<T_type5>::Take bound5)
        : QExtAdapts<T_functor>(func), m_bound1(bound1), m_bound2(bound2), m_bound3(bound3), m_bound4(bound4), m_bound5(bound5) {}

    /** Invokes the wrapped functor passing on the bound argument only.
     * \return The return value of the functor invocation.
     */
    Return
    operator()()
    {
        //Note: The AIX compiler sometimes gives linker errors if we do not define this in the class.
        return this->m_functor.template operator () <
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type4>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type5>::Type>::Pass >
               (m_bound1.invoke(), m_bound2.invoke(), m_bound3.invoke(), m_bound4.invoke(), m_bound5.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * The last 5 argument(s) are fixed.
     * \param arg1 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template <typename T_arg1>
    typename ReturnTypeDeduce<T_arg1>::Type
    operator()(T_arg1 arg1)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<T_arg1>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type4>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type5>::Type>::Pass >
               (arg1, m_bound1.invoke(), m_bound2.invoke(), m_bound3.invoke(), m_bound4.invoke(), m_bound5.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * The last 5 argument(s) are fixed.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2>
    typename ReturnTypeDeduce<T_arg1, T_arg2>::Type
    operator()(T_arg1 arg1, T_arg2 arg2)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<T_arg1>::Pass,
               typename QExtTypeTrait<T_arg2>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type4>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type5>::Type>::Pass >
               (arg1, arg2, m_bound1.invoke(), m_bound2.invoke(), m_bound3.invoke(), m_bound4.invoke(), m_bound5.invoke());
    }

    // The argument bound to the functor.
    QExtBoundArgument<T_type1> m_bound1;
    QExtBoundArgument<T_type2> m_bound2;
    QExtBoundArgument<T_type3> m_bound3;
    QExtBoundArgument<T_type4> m_bound4;
    QExtBoundArgument<T_type5> m_bound5;
};


//template specialization of QExtVisitor<>::doVisitEach<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for qextBindFunctor performs a functor on the
 * functor and on the object instances stored in the qextBindFunctor object.
 *
 * \ingroup qextBindFunctor
 */
template <typename T_functor,
          typename T_type1, typename T_type2, typename T_type3, typename T_type4, typename T_type5>
struct QExtVisitor<QExtBindFunctor<-1, T_functor, T_type1, T_type2, T_type3, T_type4, T_type5> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QExtBindFunctor<-1, T_functor,  T_type1, T_type2, T_type3, T_type4, T_type5 > & target)
    {
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
 * \ingroup qextBindFunctor
 */
template <typename T_functor,
          typename T_type1, typename T_type2, typename T_type3,
          typename T_type4, typename T_type5, typename T_type6>
struct QExtBindFunctor<-1, T_functor, T_type1, T_type2, T_type3, T_type4, T_type5, T_type6, QExtNil >
        : public QExtAdapts<T_functor>
{
    typedef QExtAdapts<T_functor>                         Base;
    typedef typename QExtAdapts<T_functor>::Adaptor       Adaptor;

    template <int count,
              typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalReturnTypeDeduce
    {
        typedef typename Adaptor::template ReturnTypeDeduce <
            typename QExtTypeTrait<T_arg1>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type4>::Type>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type5>::Type>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type6>::Type>::Pass >::Type Type;
    };

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename InternalReturnTypeDeduce <
        QExtPrivate::QExtCountVoid<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::value,
               T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >::Type Type;
    };
    typedef typename Adaptor::Return  Return;

    /** Constructs a bind_functor object that binds an argument to the passed functor.
     * \param func Functor to invoke from operator()().
     * \param bound1 Argument to qextBindFunctor to the functor.
     * \param bound2 Argument to qextBindFunctor to the functor.
     * \param bound3 Argument to qextBindFunctor to the functor.
     * \param bound4 Argument to qextBindFunctor to the functor.
     * \param bound5 Argument to qextBindFunctor to the functor.
     * \param bound6 Argument to qextBindFunctor to the functor.
     */
    QExtBindFunctor(typename QExtTypeTrait<T_functor>::Take func,
                  typename QExtTypeTrait<T_type1>::Take bound1,
                  typename QExtTypeTrait<T_type2>::Take bound2,
                  typename QExtTypeTrait<T_type3>::Take bound3,
                  typename QExtTypeTrait<T_type4>::Take bound4,
                  typename QExtTypeTrait<T_type5>::Take bound5,
                  typename QExtTypeTrait<T_type6>::Take bound6)
        : QExtAdapts<T_functor>(func),
          m_bound1(bound1), m_bound2(bound2), m_bound3(bound3),
          m_bound4(bound4), m_bound5(bound5), m_bound6(bound6) {}

    /** Invokes the wrapped functor passing on the bound argument only.
     * \return The return value of the functor invocation.
     */
    Return
    operator()()
    {
        //Note: The AIX compiler sometimes gives linker errors if we do not define this in the class.
        return this->m_functor.template operator () <
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type4>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type5>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type6>::Type>::Pass >
               (m_bound1.invoke(), m_bound2.invoke(), m_bound3.invoke(), m_bound4.invoke(), m_bound5.invoke(), m_bound6.invoke());
    }

    /** Invokes the wrapped functor passing on the arguments.
     * The last 6 argument(s) are fixed.
     * \param arg1 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template <typename T_arg1>
    typename ReturnTypeDeduce<T_arg1>::Type
    operator()(T_arg1 arg1)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<T_arg1>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type4>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type5>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type6>::Type>::Pass >
               (arg1, m_bound1.invoke(), m_bound2.invoke(), m_bound3.invoke(), m_bound4.invoke(), m_bound5.invoke(), m_bound6.invoke());
    }

    // The argument bound to the functor.
    QExtBoundArgument<T_type1> m_bound1;
    QExtBoundArgument<T_type2> m_bound2;
    QExtBoundArgument<T_type3> m_bound3;
    QExtBoundArgument<T_type4> m_bound4;
    QExtBoundArgument<T_type5> m_bound5;
    QExtBoundArgument<T_type6> m_bound6;
};


//template specialization of QExtVisitor<>::doVisitEach<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for qextBindFunctor performs a functor on the
 * functor and on the object instances stored in the qextBindFunctor object.
 *
 * \ingroup qextBindFunctor
 */
template <typename T_functor,
          typename T_type1, typename T_type2, typename T_type3,
          typename T_type4, typename T_type5, typename T_type6>
struct QExtVisitor<QExtBindFunctor< -1, T_functor, T_type1, T_type2, T_type3, T_type4, T_type5, T_type6> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QExtBindFunctor<-1, T_functor,  T_type1, T_type2, T_type3, T_type4, T_type5, T_type6 > &target)
    {
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
 * \ingroup qextBindFunctor
 */
template <typename T_functor,
          typename T_type1, typename T_type2, typename T_type3,
          typename T_type4, typename T_type5, typename T_type6, typename T_type7>
struct QExtBindFunctor<-1, T_functor, T_type1, T_type2, T_type3, T_type4, T_type5, T_type6, T_type7>
        : public QExtAdapts<T_functor>
{
    typedef QExtAdapts<T_functor>                         Base;
    typedef typename QExtAdapts<T_functor>::Adaptor       Adaptor;

    template <int count,
              typename T_arg1, typename T_arg2, typename T_arg3,
              typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    struct InternalReturnTypeDeduce
    {
        typedef typename Adaptor::template ReturnTypeDeduce <
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type4>::Type>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type5>::Type>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type6>::Type>::Pass,
            typename QExtTypeTrait<typename QEXTUnwrapReference<T_type7>::Type>::Pass >::Type Type;
    };

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename InternalReturnTypeDeduce <
        QExtPrivate::QExtCountVoid<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::value,
               T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >::Type Type;
    };
    typedef typename Adaptor::Return  Return;

    /** Constructs a bind_functor object that binds an argument to the passed functor.
     * \param func Functor to invoke from operator()().
     * \param bound1 Argument to qextBindFunctor to the functor.
     * \param bound2 Argument to qextBindFunctor to the functor.
     * \param bound3 Argument to qextBindFunctor to the functor.
     * \param bound4 Argument to qextBindFunctor to the functor.
     * \param bound5 Argument to qextBindFunctor to the functor.
     * \param bound6 Argument to qextBindFunctor to the functor.
     * \param bound7 Argument to qextBindFunctor to the functor.
     */
    QExtBindFunctor(typename QExtTypeTrait<T_functor>::Take func,
                  typename QExtTypeTrait<T_type1>::Take bound1,
                  typename QExtTypeTrait<T_type2>::Take bound2,
                  typename QExtTypeTrait<T_type3>::Take bound3,
                  typename QExtTypeTrait<T_type4>::Take bound4,
                  typename QExtTypeTrait<T_type5>::Take bound5,
                  typename QExtTypeTrait<T_type6>::Take bound6,
                  typename QExtTypeTrait<T_type7>::Take bound7)
        : QExtAdapts<T_functor>(func),
          m_bound1(bound1), m_bound2(bound2), m_bound3(bound3),
          m_bound4(bound4), m_bound5(bound5), m_bound6(bound6), m_bound7(bound7) {}

    /** Invokes the wrapped functor passing on the bound argument only.
     * \return The return value of the functor invocation.
     */
    Return
    operator()()
    {
        //Note: The AIX compiler sometimes gives linker errors if we do not define this in the class.
        return this->m_functor.template operator () <
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type1>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type2>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type3>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type4>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type5>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type6>::Type>::Pass,
               typename QExtTypeTrait<typename QEXTUnwrapReference<T_type7>::Type>::Pass >
               (m_bound1.invoke(), m_bound2.invoke(), m_bound3.invoke(), m_bound4.invoke(), m_bound5.invoke(), m_bound6.invoke(), m_bound7.invoke());
    }

    // The argument bound to the functor.
    QExtBoundArgument<T_type1> m_bound1;
    QExtBoundArgument<T_type2> m_bound2;
    QExtBoundArgument<T_type3> m_bound3;
    QExtBoundArgument<T_type4> m_bound4;
    QExtBoundArgument<T_type5> m_bound5;
    QExtBoundArgument<T_type6> m_bound6;
    QExtBoundArgument<T_type7> m_bound7;
};


//template specialization of QExtVisitor<>::doVisitEach<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for qextBindFunctor performs a functor on the
 * functor and on the object instances stored in the qextBindFunctor object.
 *
 * \ingroup qextBindFunctor
 */
template <typename T_functor,
          typename T_type1, typename T_type2, typename T_type3,
          typename T_type4, typename T_type5, typename T_type6, typename T_type7>
struct QExtVisitor<QExtBindFunctor<-1, T_functor, T_type1, T_type2, T_type3, T_type4, T_type5, T_type6, T_type7 > >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QExtBindFunctor<-1, T_functor,  T_type1, T_type2, T_type3, T_type4, T_type5, T_type6, T_type7 > &target)
    {
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
 * \param func Functor that should be wrapped.
 * \param bound1 Argument to qextBindFunctor to @e func.
 * \return Adaptor that executes @e func with the bound argument on invokation.
 *
 * \ingroup qextBindFunctor
 */
template <int I_location, typename T_functor, typename T_type1>
inline QExtBindFunctor<I_location, T_functor, T_type1>
qextBindFunctor(const T_functor &func, T_type1 bound1)
{
    return QExtBindFunctor<I_location, T_functor, T_type1>(func, bound1);
}


/** Creates an adaptor of type qextBindFunctor which fixes the last 1 argument(s) of the passed functor.
 * This function overload fixes the last 1 argument(s) of @e func.
 *
 * \param func Functor that should be wrapped.
 * \param bound1 Argument to qextBindFunctor to @e func.
 * \return Adaptor that executes func with the bound argument on invokation.
 *
 * \ingroup qextBindFunctor
 */
template <typename T_functor, typename T_type1>
inline QExtBindFunctor<-1, T_functor, T_type1 >
qextBindFunctor(const T_functor &func, T_type1 bound1)
{
    return QExtBindFunctor<-1, T_functor, T_type1 > (func, bound1);
}


/** Creates an adaptor of type qextBindFunctor which fixes the last 2 argument(s) of the passed functor.
 * This function overload fixes the last 2 argument(s) of @e func.
 *
 * \param func Functor that should be wrapped.
 * \param bound1 Argument to qextBindFunctor to @e func.
 * \param bound2 Argument to qextBindFunctor to @e func.
 * \return Adaptor that executes func with the bound argument on invokation.
 *
 * \ingroup qextBindFunctor
 */
template <typename T_functor, typename T_type1, typename T_type2>
inline QExtBindFunctor<-1, T_functor, T_type1, T_type2 >
qextBindFunctor(const T_functor &func, T_type1 bound1, T_type2 bound2)
{
    return QExtBindFunctor<-1, T_functor, T_type1, T_type2 > (func, bound1, bound2);
}


/** Creates an adaptor of type qextBindFunctor which fixes the last 3 argument(s) of the passed functor.
 * This function overload fixes the last 3 argument(s) of @e func.
 *
 * \param func Functor that should be wrapped.
 * \param bound1 Argument to qextBindFunctor to @e func.
 * \param bound2 Argument to qextBindFunctor to @e func.
 * \param bound3 Argument to qextBindFunctor to @e func.
 * \return Adaptor that executes func with the bound argument on invokation.
 *
 * \ingroup qextBindFunctor
 */
template <typename T_functor, typename T_type1, typename T_type2, typename T_type3>
inline QExtBindFunctor<-1, T_functor, T_type1, T_type2, T_type3 >
qextBindFunctor(const T_functor &func, T_type1 bound1, T_type2 bound2, T_type3 bound3)
{
    return QExtBindFunctor<-1, T_functor, T_type1, T_type2, T_type3 > (func, bound1, bound2, bound3);
}


/** Creates an adaptor of type qextBindFunctor which fixes the last 4 argument(s) of the passed functor.
 * This function overload fixes the last 4 argument(s) of @e func.
 *
 * \param func Functor that should be wrapped.
 * \param bound1 Argument to qextBindFunctor to @e func.
 * \param bound2 Argument to qextBindFunctor to @e func.
 * \param bound3 Argument to qextBindFunctor to @e func.
 * \param bound4 Argument to qextBindFunctor to @e func.
 * \return Adaptor that executes func with the bound argument on invokation.
 *
 * \ingroup qextBindFunctor
 */
template <typename T_functor, typename T_type1, typename T_type2, typename T_type3, typename T_type4>
inline QExtBindFunctor<-1, T_functor, T_type1, T_type2, T_type3, T_type4 >
qextBindFunctor(const T_functor &func, T_type1 bound1, T_type2 bound2, T_type3 bound3, T_type4 bound4)
{
    return QExtBindFunctor<-1, T_functor, T_type1, T_type2, T_type3, T_type4 > (func, bound1, bound2, bound3, bound4);
}


/** Creates an adaptor of type qextBindFunctor which fixes the last 5 argument(s) of the passed functor.
 * This function overload fixes the last 5 argument(s) of @e func.
 *
 * \param func Functor that should be wrapped.
 * \param bound1 Argument to qextBindFunctor to @e func.
 * \param bound2 Argument to qextBindFunctor to @e func.
 * \param bound3 Argument to qextBindFunctor to @e func.
 * \param bound4 Argument to qextBindFunctor to @e func.
 * \param bound5 Argument to qextBindFunctor to @e func.
 * \return Adaptor that executes func with the bound argument on invokation.
 *
 * \ingroup qextBindFunctor
 */
template <typename T_functor,
          typename T_type1, typename T_type2, typename T_type3, typename T_type4, typename T_type5>
inline QExtBindFunctor<-1, T_functor, T_type1, T_type2, T_type3, T_type4, T_type5 >
qextBindFunctor(const T_functor &func, T_type1 bound1, T_type2 bound2, T_type3 bound3, T_type4 bound4, T_type5 bound5)
{
    return QExtBindFunctor<-1, T_functor, T_type1, T_type2, T_type3, T_type4, T_type5 > (func, bound1, bound2, bound3, bound4, bound5);
}


/** Creates an adaptor of type qextBindFunctor which fixes the last 6 argument(s) of the passed functor.
 * This function overload fixes the last 6 argument(s) of @e func.
 *
 * \param func Functor that should be wrapped.
 * \param bound1 Argument to qextBindFunctor to @e func.
 * \param bound2 Argument to qextBindFunctor to @e func.
 * \param bound3 Argument to qextBindFunctor to @e func.
 * \param bound4 Argument to qextBindFunctor to @e func.
 * \param bound5 Argument to qextBindFunctor to @e func.
 * \param bound6 Argument to qextBindFunctor to @e func.
 * \return Adaptor that executes func with the bound argument on invokation.
 *
 * \ingroup qextBindFunctor
 */
template <typename T_functor,
          typename T_type1, typename T_type2, typename T_type3,
          typename T_type4, typename T_type5, typename T_type6>
inline QExtBindFunctor<-1, T_functor, T_type1, T_type2, T_type3, T_type4, T_type5, T_type6 >
qextBindFunctor(const T_functor &func, T_type1 bound1, T_type2 bound2, T_type3 bound3, T_type4 bound4, T_type5 bound5, T_type6 bound6)
{
    return QExtBindFunctor<-1, T_functor, T_type1, T_type2, T_type3, T_type4, T_type5, T_type6 > (func, bound1, bound2, bound3, bound4, bound5, bound6);
}


/** Creates an adaptor of type qextBindFunctor which fixes the last 7 argument(s) of the passed functor.
 * This function overload fixes the last 7 argument(s) of @e func.
 *
 * \param func Functor that should be wrapped.
 * \param bound1 Argument to qextBindFunctor to @e func.
 * \param bound2 Argument to qextBindFunctor to @e func.
 * \param bound3 Argument to qextBindFunctor to @e func.
 * \param bound4 Argument to qextBindFunctor to @e func.
 * \param bound5 Argument to qextBindFunctor to @e func.
 * \param bound6 Argument to qextBindFunctor to @e func.
 * \param bound7 Argument to qextBindFunctor to @e func.
 * \return Adaptor that executes func with the bound argument on invokation.
 *
 * \ingroup qextBindFunctor
 */
template <typename T_functor,
          typename T_type1, typename T_type2, typename T_type3,
          typename T_type4, typename T_type5, typename T_type6, typename T_type7>
inline QExtBindFunctor<-1, T_functor, T_type1, T_type2, T_type3, T_type4, T_type5, T_type6, T_type7>
qextBindFunctor(const T_functor &func, T_type1 bound1, T_type2 bound2, T_type3 bound3, T_type4 bound4, T_type5 bound5, T_type6 bound6, T_type7 bound7)
{
    return QExtBindFunctor<-1, T_functor, T_type1, T_type2, T_type3, T_type4, T_type5, T_type6, T_type7 > (func, bound1, bound2, bound3, bound4, bound5, bound6, bound7);
}

#endif // _QEXTBINDFUNCTOR_H
