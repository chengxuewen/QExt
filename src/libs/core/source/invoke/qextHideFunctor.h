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

#ifndef _QEXTHIDEFUNCTOR_H
#define _QEXTHIDEFUNCTOR_H

#include <qextAdaptorTrait.h>
#include <qextVisitor.h>



/** @defgroup qextHideFunctor qextHideFunctor(), hide_return()
* qextHideFunctor() alters an arbitrary functor in that it adds a parameter
* whose value is ignored on invocation of the returned functor.
* Thus you can discard one argument of a signal.
*
* You may optionally specify the zero-based position of the parameter
* to ignore as a template argument. The default is to ignore the last
* parameter.
* (A value of @p -1 adds a parameter at the end so qextHideFunctor<-1>() gives the same result as qextHideFunctor().)
*
* The type of the parameter can optionally be specified if not deduced.
*
* @par Examples:
* @code
* void foo(int, int);
* // single argument hiding ...
* qextHideFunctor(&foo)(1,2,3);     // adds a dummy parameter at the back and calls foo(1,2)
* qextHideFunctor<-1>(&foo)(1,2,3); // same as qextHideFunctor(&foo)(1,2,3) (calls foo(1,2))
* qextHideFunctor<0>(&foo)(1,2,3);  // adds a dummy parameter at the beginning and calls foo(2,3)
* qextHideFunctor<1>(&foo)(1,2,3);  // adds a dummy parameter in the middle and calls foo(1,3)
* qextHideFunctor<2>(&foo)(1,2,3);  // adds a dummy parameter at the back and calls foo(1,2)
* @endcode
*
* The functor qextHideFunctor() returns can be directly passed into
* signal::connect().
*
* @par Example:
* @code
* signal<void,int> some_signal;
* void foo();
* some_signal.connect(qextHideFunctor(&foo));
* @endcode
*
* qextHideFunctor() can be nested in order to discard multiple arguments.
* @par Example:
* @code
* // multiple argument hiding ...
* qextHideFunctor(qextHideFunctor(&foo))(1,2,3,4); // adds two dummy parameters at the back and calls foo(1,2)
* @endcode

* qextHideReturnFunctor() alters an arbitrary functor by
* dropping its return value, thus converting it to a void functor.
*
* For a more powerful version of this functionality see the lambda
* library adaptor group() which can bind, qextHideFunctor and reorder
* arguments arbitrarily. Although group() is more flexible,
* qextHideFunctor() provides a means of hiding parameters when the total
* number of parameters called is variable.
*
* \ingroup adaptors
*/



/** AdaptorType that adds a dummy parameter to the wrapped functor.
* Use the convenience function qextHideFunctor() to create an instance of QExtHideFunctor.
*
* The following template arguments are used:
* - @e I_location Zero-based position of the dummy parameter (@p -1 for the last parameter).
* - @e T_type Type of the dummy parameter.
* - @e T_functor Type of the functor to wrap.
*
* \ingroup qextHideFunctor
*/
template<int I_location, typename T_functor>
struct QExtHideFunctor;

/** AdaptorType that adds a dummy parameter to the wrapped functor.
* This template specialization ignores the value of the last parameter in operator()().
*
* \ingroup qextHideFunctor
*/
template<typename T_functor>
struct QExtHideFunctor<-1, T_functor> : public QExtAdapts<T_functor>
{
    typedef typename QExtAdapts<T_functor>::AdaptorType AdaptorType;

    template<typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
            typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename AdaptorType::template ReturnTypeDeduce<
                typename QExtTypeTrait<T_arg1>::Pass,
                typename QExtTypeTrait<T_arg2>::Pass,
                typename QExtTypeTrait<T_arg3>::Pass,
                typename QExtTypeTrait<T_arg4>::Pass,
                typename QExtTypeTrait<T_arg5>::Pass,
                typename QExtTypeTrait<T_arg6>::Pass>::Type Type;
    };

    typedef typename AdaptorType::ResultType ResultType;

    /** Constructs a hide_functor object that adds a dummy parameter to the passed functor.
    * \param func Functor to invoke from operator()().
    */
    explicit QExtHideFunctor(const T_functor &func) : QExtAdapts<T_functor>(func) {}

    QExtHideFunctor(const QExtHideFunctor &other) : QExtAdapts<T_functor>(other) {}

    /** Invokes the wrapped functor ignoring the only argument.
    * \param arg1 Argument to be ignored.
    * \return The return value of the functor invocation.
    */
    template<typename T_arg1>
    typename ReturnTypeDeduce<T_arg1>::Type
    operator()(T_arg1)
    {
        return this->m_functor();
    }

    /** Invokes the wrapped functor, ignoring the last argument.
    * \param arg1 Argument to be passed on to the functor.
    * \param arg2 Argument to be ignored.
    * \return The return value of the functor invocation.
    */
    template<typename T_arg1, typename T_arg2>
    typename ReturnTypeDeduce<T_arg1, T_arg2>::Type
    operator()(T_arg1 arg1, T_arg2)
    {
        return this->m_functor.template operator()<
                typename QExtTypeTrait<T_arg1>::Pass>
                (arg1);
    }

    /** Invokes the wrapped functor, ignoring the last argument.
    * \param arg1 Argument to be passed on to the functor.
    * \param arg2 Argument to be passed on to the functor.
    * \param arg3 Argument to be ignored.
    * \return The return value of the functor invocation.
    */
    template<typename T_arg1, typename T_arg2, typename T_arg3>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3)
    {
        return this->m_functor.template operator()<
                typename QExtTypeTrait<T_arg1>::Pass,
                typename QExtTypeTrait<T_arg2>::Pass>
                (arg1, arg2);
    }

    /** Invokes the wrapped functor, ignoring the last argument.
    * \param arg1 Argument to be passed on to the functor.
    * \param arg2 Argument to be passed on to the functor.
    * \param arg3 Argument to be passed on to the functor.
    * \param arg4 Argument to be ignored.
    * \return The return value of the functor invocation.
    */
    template<typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4)
    {
        return this->m_functor.template operator()<
                typename QExtTypeTrait<T_arg1>::Pass,
                typename QExtTypeTrait<T_arg2>::Pass,
                typename QExtTypeTrait<T_arg3>::Pass>
                (arg1, arg2, arg3);
    }

    /** Invokes the wrapped functor, ignoring the last argument.
    * \param arg1 Argument to be passed on to the functor.
    * \param arg2 Argument to be passed on to the functor.
    * \param arg3 Argument to be passed on to the functor.
    * \param arg4 Argument to be passed on to the functor.
    * \param arg5 Argument to be ignored.
    * \return The return value of the functor invocation.
    */
    template<typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5)
    {
        return this->m_functor.template operator()<
                typename QExtTypeTrait<T_arg1>::Pass,
                typename QExtTypeTrait<T_arg2>::Pass,
                typename QExtTypeTrait<T_arg3>::Pass,
                typename QExtTypeTrait<T_arg4>::Pass>
                (arg1, arg2, arg3, arg4);
    }

    /** Invokes the wrapped functor, ignoring the last argument.
    * \param arg1 Argument to be passed on to the functor.
    * \param arg2 Argument to be passed on to the functor.
    * \param arg3 Argument to be passed on to the functor.
    * \param arg4 Argument to be passed on to the functor.
    * \param arg5 Argument to be passed on to the functor.
    * \param arg6 Argument to be ignored.
    * \return The return value of the functor invocation.
    */
    template<typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6)
    {
        return this->m_functor.template operator()<
                typename QExtTypeTrait<T_arg1>::Pass,
                typename QExtTypeTrait<T_arg2>::Pass,
                typename QExtTypeTrait<T_arg3>::Pass,
                typename QExtTypeTrait<T_arg4>::Pass,
                typename QExtTypeTrait<T_arg5>::Pass>
                (arg1, arg2, arg3, arg4, arg5);
    }

    /** Invokes the wrapped functor, ignoring the last argument.
    * \param arg1 Argument to be passed on to the functor.
    * \param arg2 Argument to be passed on to the functor.
    * \param arg3 Argument to be passed on to the functor.
    * \param arg4 Argument to be passed on to the functor.
    * \param arg5 Argument to be passed on to the functor.
    * \param arg6 Argument to be passed on to the functor.
    * \param arg7 Argument to be ignored.
    * \return The return value of the functor invocation.
    */
    template<typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7)
    {
        return this->m_functor.template operator()<
                typename QExtTypeTrait<T_arg1>::Pass,
                typename QExtTypeTrait<T_arg2>::Pass,
                typename QExtTypeTrait<T_arg3>::Pass,
                typename QExtTypeTrait<T_arg4>::Pass,
                typename QExtTypeTrait<T_arg5>::Pass,
                typename QExtTypeTrait<T_arg6>::Pass>
                (arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

/** AdaptorType that adds a dummy parameter to the wrapped functor.
* This template specialization ignores the value of the 1st parameter in operator()().
*
* \ingroup qextHideFunctor
*/
template<typename T_functor>
struct QExtHideFunctor<0, T_functor> : public QExtAdapts<T_functor>
{
    typedef typename QExtAdapts<T_functor>::AdaptorType AdaptorType;

    template<typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
            typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename AdaptorType::template ReturnTypeDeduce<
                typename QExtTypeTrait<T_arg2>::Pass,
                typename QExtTypeTrait<T_arg3>::Pass,
                typename QExtTypeTrait<T_arg4>::Pass,
                typename QExtTypeTrait<T_arg5>::Pass,
                typename QExtTypeTrait<T_arg6>::Pass,
                typename QExtTypeTrait<T_arg7>::Pass>::Type Type;
    };

    typedef typename AdaptorType::ResultType ResultType;

    /** Constructs a hide_functor object that adds a dummy parameter to the passed functor.
    * \param func Functor to invoke from operator()().
    */
    explicit QExtHideFunctor(const T_functor &func) : QExtAdapts<T_functor>(func) {}

    QExtHideFunctor(const QExtHideFunctor &other) : QExtAdapts<T_functor>(other) {}

    /** Invokes the wrapped functor ignoring the only argument.
    * \param arg1 Argument to be ignored.
    * \return The return value of the functor invocation.
    */
    template<typename T_arg1>
    typename ReturnTypeDeduce<T_arg1>::Type
    operator()(T_arg1)
    {
        return this->m_functor();
    }

    /** Invokes the wrapped functor, ignoring the 1st argument.
    * \param arg1 Argument to be ignored.
    * \param arg2 Argument to be passed on to the functor.
    * \return The return value of the functor invocation.
    */
    template<typename T_arg1, typename T_arg2>
    typename ReturnTypeDeduce<T_arg1, T_arg2>::Type
    operator()(T_arg1, T_arg2 arg2)
    {
        return this->m_functor.template operator()<
                typename QExtTypeTrait<T_arg2>::Pass>
                (arg2);
    }

    /** Invokes the wrapped functor, ignoring the 1st argument.
    * \param arg1 Argument to be ignored.
    * \param arg2 Argument to be passed on to the functor.
    * \param arg3 Argument to be passed on to the functor.
    * \return The return value of the functor invocation.
    */
    template<typename T_arg1, typename T_arg2, typename T_arg3>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3>::Type
    operator()(T_arg1, T_arg2 arg2, T_arg3 arg3)
    {
        return this->m_functor.template operator()<
                typename QExtTypeTrait<T_arg2>::Pass,
                typename QExtTypeTrait<T_arg3>::Pass>
                (arg2, arg3);
    }

    /** Invokes the wrapped functor, ignoring the 1st argument.
    * \param arg1 Argument to be ignored.
    * \param arg2 Argument to be passed on to the functor.
    * \param arg3 Argument to be passed on to the functor.
    * \param arg4 Argument to be passed on to the functor.
    * \return The return value of the functor invocation.
    */
    template<typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator()(T_arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4)
    {
        return this->m_functor.template operator()<
                typename QExtTypeTrait<T_arg2>::Pass,
                typename QExtTypeTrait<T_arg3>::Pass,
                typename QExtTypeTrait<T_arg4>::Pass>
                (arg2, arg3, arg4);
    }

    /** Invokes the wrapped functor, ignoring the 1st argument.
    * \param arg1 Argument to be ignored.
    * \param arg2 Argument to be passed on to the functor.
    * \param arg3 Argument to be passed on to the functor.
    * \param arg4 Argument to be passed on to the functor.
    * \param arg5 Argument to be passed on to the functor.
    * \return The return value of the functor invocation.
    */
    template<typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator()(T_arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5)
    {
        return this->m_functor.template operator()<
                typename QExtTypeTrait<T_arg2>::Pass,
                typename QExtTypeTrait<T_arg3>::Pass,
                typename QExtTypeTrait<T_arg4>::Pass,
                typename QExtTypeTrait<T_arg5>::Pass>
                (arg2, arg3, arg4, arg5);
    }

    /** Invokes the wrapped functor, ignoring the 1st argument.
    * \param arg1 Argument to be ignored.
    * \param arg2 Argument to be passed on to the functor.
    * \param arg3 Argument to be passed on to the functor.
    * \param arg4 Argument to be passed on to the functor.
    * \param arg5 Argument to be passed on to the functor.
    * \param arg6 Argument to be passed on to the functor.
    * \return The return value of the functor invocation.
    */
    template<typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator()(T_arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6)
    {
        return this->m_functor.template operator()<
                typename QExtTypeTrait<T_arg2>::Pass,
                typename QExtTypeTrait<T_arg3>::Pass,
                typename QExtTypeTrait<T_arg4>::Pass,
                typename QExtTypeTrait<T_arg5>::Pass,
                typename QExtTypeTrait<T_arg6>::Pass>
                (arg2, arg3, arg4, arg5, arg6);
    }

    /** Invokes the wrapped functor, ignoring the 1st argument.
    * \param arg1 Argument to be ignored.
    * \param arg2 Argument to be passed on to the functor.
    * \param arg3 Argument to be passed on to the functor.
    * \param arg4 Argument to be passed on to the functor.
    * \param arg5 Argument to be passed on to the functor.
    * \param arg6 Argument to be passed on to the functor.
    * \param arg7 Argument to be passed on to the functor.
    * \return The return value of the functor invocation.
    */
    template<typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type
    operator()(T_arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7)
    {
        return this->m_functor.template operator()<
                typename QExtTypeTrait<T_arg2>::Pass,
                typename QExtTypeTrait<T_arg3>::Pass,
                typename QExtTypeTrait<T_arg4>::Pass,
                typename QExtTypeTrait<T_arg5>::Pass,
                typename QExtTypeTrait<T_arg6>::Pass,
                typename QExtTypeTrait<T_arg7>::Pass>
                (arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

/** AdaptorType that adds a dummy parameter to the wrapped functor.
* This template specialization ignores the value of the 2nd parameter in operator()().
*
* \ingroup qextHideFunctor
*/
template<typename T_functor>
struct QExtHideFunctor<1, T_functor> : public QExtAdapts<T_functor>
{
    typedef typename QExtAdapts<T_functor>::AdaptorType AdaptorType;

    template<typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
            typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename AdaptorType::template ReturnTypeDeduce<
                typename QExtTypeTrait<T_arg1>::Pass,
                typename QExtTypeTrait<T_arg3>::Pass,
                typename QExtTypeTrait<T_arg4>::Pass,
                typename QExtTypeTrait<T_arg5>::Pass,
                typename QExtTypeTrait<T_arg6>::Pass,
                typename QExtTypeTrait<T_arg7>::Pass>::Type Type;
    };

    typedef typename AdaptorType::ResultType ResultType;

    /** Constructs a hide_functor object that adds a dummy parameter to the passed functor.
    * \param func Functor to invoke from operator()().
    */
    explicit QExtHideFunctor(const T_functor &func) : QExtAdapts<T_functor>(func) {}

    QExtHideFunctor(const QExtHideFunctor &other) : QExtAdapts<T_functor>(other) {}

    /** Invokes the wrapped functor, ignoring the 2nd argument.
    * \param arg1 Argument to be passed on to the functor.
    * \param arg2 Argument to be ignored.
    * \return The return value of the functor invocation.
    */
    template<typename T_arg1, typename T_arg2>
    typename ReturnTypeDeduce<T_arg1, T_arg2>::Type
    operator()(T_arg1 arg1, T_arg2)
    {
        return this->m_functor.template operator()<
                typename QExtTypeTrait<T_arg1>::Pass>
                (arg1);
    }

    /** Invokes the wrapped functor, ignoring the 2nd argument.
    * \param arg1 Argument to be passed on to the functor.
    * \param arg2 Argument to be ignored.
    * \param arg3 Argument to be passed on to the functor.
    * \return The return value of the functor invocation.
    */
    template<typename T_arg1, typename T_arg2, typename T_arg3>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3>::Type
    operator()(T_arg1 arg1, T_arg2, T_arg3 arg3)
    {
        return this->m_functor.template operator()<
                typename QExtTypeTrait<T_arg1>::Pass,
                typename QExtTypeTrait<T_arg3>::Pass>
                (arg1, arg3);
    }

    /** Invokes the wrapped functor, ignoring the 2nd argument.
    * \param arg1 Argument to be passed on to the functor.
    * \param arg2 Argument to be ignored.
    * \param arg3 Argument to be passed on to the functor.
    * \param arg4 Argument to be passed on to the functor.
    * \return The return value of the functor invocation.
    */
    template<typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator()(T_arg1 arg1, T_arg2, T_arg3 arg3, T_arg4 arg4)
    {
        return this->m_functor.template operator()<
                typename QExtTypeTrait<T_arg1>::Pass,
                typename QExtTypeTrait<T_arg3>::Pass,
                typename QExtTypeTrait<T_arg4>::Pass>
                (arg1, arg3, arg4);
    }

    /** Invokes the wrapped functor, ignoring the 2nd argument.
    * \param arg1 Argument to be passed on to the functor.
    * \param arg2 Argument to be ignored.
    * \param arg3 Argument to be passed on to the functor.
    * \param arg4 Argument to be passed on to the functor.
    * \param arg5 Argument to be passed on to the functor.
    * \return The return value of the functor invocation.
    */
    template<typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator()(T_arg1 arg1, T_arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5)
    {
        return this->m_functor.template operator()<
                typename QExtTypeTrait<T_arg1>::Pass,
                typename QExtTypeTrait<T_arg3>::Pass,
                typename QExtTypeTrait<T_arg4>::Pass,
                typename QExtTypeTrait<T_arg5>::Pass>
                (arg1, arg3, arg4, arg5);
    }

    /** Invokes the wrapped functor, ignoring the 2nd argument.
    * \param arg1 Argument to be passed on to the functor.
    * \param arg2 Argument to be ignored.
    * \param arg3 Argument to be passed on to the functor.
    * \param arg4 Argument to be passed on to the functor.
    * \param arg5 Argument to be passed on to the functor.
    * \param arg6 Argument to be passed on to the functor.
    * \return The return value of the functor invocation.
    */
    template<typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator()(T_arg1 arg1, T_arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6)
    {
        return this->m_functor.template operator()<
                typename QExtTypeTrait<T_arg1>::Pass,
                typename QExtTypeTrait<T_arg3>::Pass,
                typename QExtTypeTrait<T_arg4>::Pass,
                typename QExtTypeTrait<T_arg5>::Pass,
                typename QExtTypeTrait<T_arg6>::Pass>
                (arg1, arg3, arg4, arg5, arg6);
    }

    /** Invokes the wrapped functor, ignoring the 2nd argument.
    * \param arg1 Argument to be passed on to the functor.
    * \param arg2 Argument to be ignored.
    * \param arg3 Argument to be passed on to the functor.
    * \param arg4 Argument to be passed on to the functor.
    * \param arg5 Argument to be passed on to the functor.
    * \param arg6 Argument to be passed on to the functor.
    * \param arg7 Argument to be passed on to the functor.
    * \return The return value of the functor invocation.
    */
    template<typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type
    operator()(T_arg1 arg1, T_arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7)
    {
        return this->m_functor.template operator()<
                typename QExtTypeTrait<T_arg1>::Pass,
                typename QExtTypeTrait<T_arg3>::Pass,
                typename QExtTypeTrait<T_arg4>::Pass,
                typename QExtTypeTrait<T_arg5>::Pass,
                typename QExtTypeTrait<T_arg6>::Pass,
                typename QExtTypeTrait<T_arg7>::Pass>
                (arg1, arg3, arg4, arg5, arg6, arg7);
    }
};

/** AdaptorType that adds a dummy parameter to the wrapped functor.
* This template specialization ignores the value of the 3rd parameter in operator()().
*
* \ingroup qextHideFunctor
*/
template<typename T_functor>
struct QExtHideFunctor<2, T_functor> : public QExtAdapts<T_functor>
{
    typedef typename QExtAdapts<T_functor>::AdaptorType AdaptorType;

    template<typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
            typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename AdaptorType::template ReturnTypeDeduce<
                typename QExtTypeTrait<T_arg1>::Pass,
                typename QExtTypeTrait<T_arg2>::Pass,
                typename QExtTypeTrait<T_arg4>::Pass,
                typename QExtTypeTrait<T_arg5>::Pass,
                typename QExtTypeTrait<T_arg6>::Pass,
                typename QExtTypeTrait<T_arg7>::Pass>::Type Type;
    };
    typedef typename AdaptorType::ResultType ResultType;

    /** Constructs a hide_functor object that adds a dummy parameter to the passed functor.
    * \param func Functor to invoke from operator()().
    */
    explicit QExtHideFunctor(const T_functor &func) : QExtAdapts<T_functor>(func) {}

    QExtHideFunctor(const QExtHideFunctor &other) : QExtAdapts<T_functor>(other) {}

    /** Invokes the wrapped functor, ignoring the 3rd argument.
    * \param arg1 Argument to be passed on to the functor.
    * \param arg2 Argument to be passed on to the functor.
    * \param arg3 Argument to be ignored.
    * \return The return value of the functor invocation.
    */
    template<typename T_arg1, typename T_arg2, typename T_arg3>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3)
    {
        return this->m_functor.template operator()<
                typename QExtTypeTrait<T_arg1>::Pass,
                typename QExtTypeTrait<T_arg2>::Pass>
                (arg1, arg2);
    }

    /** Invokes the wrapped functor, ignoring the 3rd argument.
    * \param arg1 Argument to be passed on to the functor.
    * \param arg2 Argument to be passed on to the functor.
    * \param arg3 Argument to be ignored.
    * \param arg4 Argument to be passed on to the functor.
    * \return The return value of the functor invocation.
    */
    template<typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3, T_arg4 arg4)
    {
        return this->m_functor.template operator()<
                typename QExtTypeTrait<T_arg1>::Pass,
                typename QExtTypeTrait<T_arg2>::Pass,
                typename QExtTypeTrait<T_arg4>::Pass>
                (arg1, arg2, arg4);
    }

    /** Invokes the wrapped functor, ignoring the 3rd argument.
    * \param arg1 Argument to be passed on to the functor.
    * \param arg2 Argument to be passed on to the functor.
    * \param arg3 Argument to be ignored.
    * \param arg4 Argument to be passed on to the functor.
    * \param arg5 Argument to be passed on to the functor.
    * \return The return value of the functor invocation.
    */
    template<typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3, T_arg4 arg4, T_arg5 arg5)
    {
        return this->m_functor.template operator()<
                typename QExtTypeTrait<T_arg1>::Pass,
                typename QExtTypeTrait<T_arg2>::Pass,
                typename QExtTypeTrait<T_arg4>::Pass,
                typename QExtTypeTrait<T_arg5>::Pass>
                (arg1, arg2, arg4, arg5);
    }

    /** Invokes the wrapped functor, ignoring the 3rd argument.
    * \param arg1 Argument to be passed on to the functor.
    * \param arg2 Argument to be passed on to the functor.
    * \param arg3 Argument to be ignored.
    * \param arg4 Argument to be passed on to the functor.
    * \param arg5 Argument to be passed on to the functor.
    * \param arg6 Argument to be passed on to the functor.
    * \return The return value of the functor invocation.
    */
    template<typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6)
    {
        return this->m_functor.template operator()<
                typename QExtTypeTrait<T_arg1>::Pass,
                typename QExtTypeTrait<T_arg2>::Pass,
                typename QExtTypeTrait<T_arg4>::Pass,
                typename QExtTypeTrait<T_arg5>::Pass,
                typename QExtTypeTrait<T_arg6>::Pass>
                (arg1, arg2, arg4, arg5, arg6);
    }

    /** Invokes the wrapped functor, ignoring the 3rd argument.
    * \param arg1 Argument to be passed on to the functor.
    * \param arg2 Argument to be passed on to the functor.
    * \param arg3 Argument to be ignored.
    * \param arg4 Argument to be passed on to the functor.
    * \param arg5 Argument to be passed on to the functor.
    * \param arg6 Argument to be passed on to the functor.
    * \param arg7 Argument to be passed on to the functor.
    * \return The return value of the functor invocation.
    */
    template<typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7)
    {
        return this->m_functor.template operator()<
                typename QExtTypeTrait<T_arg1>::Pass,
                typename QExtTypeTrait<T_arg2>::Pass,
                typename QExtTypeTrait<T_arg4>::Pass,
                typename QExtTypeTrait<T_arg5>::Pass,
                typename QExtTypeTrait<T_arg6>::Pass,
                typename QExtTypeTrait<T_arg7>::Pass>
                (arg1, arg2, arg4, arg5, arg6, arg7);
    }
};

/** AdaptorType that adds a dummy parameter to the wrapped functor.
* This template specialization ignores the value of the 4th parameter in operator()().
*
* \ingroup qextHideFunctor
*/
template<typename T_functor>
struct QExtHideFunctor<3, T_functor> : public QExtAdapts<T_functor>
{
    typedef typename QExtAdapts<T_functor>::AdaptorType AdaptorType;

    template<typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void, typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename AdaptorType::template ReturnTypeDeduce<
                typename QExtTypeTrait<T_arg1>::Pass,
                typename QExtTypeTrait<T_arg2>::Pass,
                typename QExtTypeTrait<T_arg3>::Pass,
                typename QExtTypeTrait<T_arg5>::Pass,
                typename QExtTypeTrait<T_arg6>::Pass,
                typename QExtTypeTrait<T_arg7>::Pass>::Type Type;
    };
    typedef typename AdaptorType::ResultType ResultType;

    /** Constructs a hide_functor object that adds a dummy parameter to the passed functor.
    * \param func Functor to invoke from operator()().
    */
    explicit QExtHideFunctor(const T_functor &func) : QExtAdapts<T_functor>(func) {}

    QExtHideFunctor(const QExtHideFunctor &other) : QExtAdapts<T_functor>(other) {}

    /** Invokes the wrapped functor, ignoring the 4th argument.
    * \param arg1 Argument to be passed on to the functor.
    * \param arg2 Argument to be passed on to the functor.
    * \param arg3 Argument to be passed on to the functor.
    * \param arg4 Argument to be ignored.
    * \return The return value of the functor invocation.
    */
    template<typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4)
    {
        return this->m_functor.template operator()<
                typename QExtTypeTrait<T_arg1>::Pass,
                typename QExtTypeTrait<T_arg2>::Pass,
                typename QExtTypeTrait<T_arg3>::Pass>
                (arg1, arg2, arg3);
    }

    /** Invokes the wrapped functor, ignoring the 4th argument.
    * \param arg1 Argument to be passed on to the functor.
    * \param arg2 Argument to be passed on to the functor.
    * \param arg3 Argument to be passed on to the functor.
    * \param arg4 Argument to be ignored.
    * \param arg5 Argument to be passed on to the functor.
    * \return The return value of the functor invocation.
    */
    template<typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4, T_arg5 arg5)
    {
        return this->m_functor.template operator()<
                typename QExtTypeTrait<T_arg1>::Pass,
                typename QExtTypeTrait<T_arg2>::Pass,
                typename QExtTypeTrait<T_arg3>::Pass,
                typename QExtTypeTrait<T_arg5>::Pass>
                (arg1, arg2, arg3, arg5);
    }

    /** Invokes the wrapped functor, ignoring the 4th argument.
    * \param arg1 Argument to be passed on to the functor.
    * \param arg2 Argument to be passed on to the functor.
    * \param arg3 Argument to be passed on to the functor.
    * \param arg4 Argument to be ignored.
    * \param arg5 Argument to be passed on to the functor.
    * \param arg6 Argument to be passed on to the functor.
    * \return The return value of the functor invocation.
    */
    template<typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4, T_arg5 arg5, T_arg6 arg6)
    {
        return this->m_functor.template operator()<
                typename QExtTypeTrait<T_arg1>::Pass,
                typename QExtTypeTrait<T_arg2>::Pass,
                typename QExtTypeTrait<T_arg3>::Pass,
                typename QExtTypeTrait<T_arg5>::Pass,
                typename QExtTypeTrait<T_arg6>::Pass>
                (arg1, arg2, arg3, arg5, arg6);
    }

    /** Invokes the wrapped functor, ignoring the 4th argument.
    * \param arg1 Argument to be passed on to the functor.
    * \param arg2 Argument to be passed on to the functor.
    * \param arg3 Argument to be passed on to the functor.
    * \param arg4 Argument to be ignored.
    * \param arg5 Argument to be passed on to the functor.
    * \param arg6 Argument to be passed on to the functor.
    * \param arg7 Argument to be passed on to the functor.
    * \return The return value of the functor invocation.
    */
    template<typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7)
    {
        return this->m_functor.template operator()<
                typename QExtTypeTrait<T_arg1>::Pass,
                typename QExtTypeTrait<T_arg2>::Pass,
                typename QExtTypeTrait<T_arg3>::Pass,
                typename QExtTypeTrait<T_arg5>::Pass,
                typename QExtTypeTrait<T_arg6>::Pass,
                typename QExtTypeTrait<T_arg7>::Pass>
                (arg1, arg2, arg3, arg5, arg6, arg7);
    }
};

/** AdaptorType that adds a dummy parameter to the wrapped functor.
* This template specialization ignores the value of the 5th parameter in operator()().
*
* \ingroup qextHideFunctor
*/
template<typename T_functor>
struct QExtHideFunctor<4, T_functor> : public QExtAdapts<T_functor>
{
    typedef typename QExtAdapts<T_functor>::AdaptorType AdaptorType;

    template<typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
            typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename AdaptorType::template ReturnTypeDeduce<
                typename QExtTypeTrait<T_arg1>::Pass,
                typename QExtTypeTrait<T_arg2>::Pass,
                typename QExtTypeTrait<T_arg3>::Pass,
                typename QExtTypeTrait<T_arg4>::Pass,
                typename QExtTypeTrait<T_arg6>::Pass,
                typename QExtTypeTrait<T_arg7>::Pass>::Type Type;
    };
    typedef typename AdaptorType::ResultType ResultType;

    /** Constructs a hide_functor object that adds a dummy parameter to the passed functor.
    * \param func Functor to invoke from operator()().
    */
    explicit QExtHideFunctor(const T_functor &func) : QExtAdapts<T_functor>(func) {}

    QExtHideFunctor(const QExtHideFunctor &other) : QExtAdapts<T_functor>(other) {}

    /** Invokes the wrapped functor, ignoring the 5th argument.
    * \param arg1 Argument to be passed on to the functor.
    * \param arg2 Argument to be passed on to the functor.
    * \param arg3 Argument to be passed on to the functor.
    * \param arg4 Argument to be passed on to the functor.
    * \param arg5 Argument to be ignored.
    * \return The return value of the functor invocation.
    */
    template<typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5)
    {
        return this->m_functor.template operator()<
                typename QExtTypeTrait<T_arg1>::Pass,
                typename QExtTypeTrait<T_arg2>::Pass,
                typename QExtTypeTrait<T_arg3>::Pass,
                typename QExtTypeTrait<T_arg4>::Pass>
                (arg1, arg2, arg3, arg4);
    }

    /** Invokes the wrapped functor, ignoring the 5th argument.
    * \param arg1 Argument to be passed on to the functor.
    * \param arg2 Argument to be passed on to the functor.
    * \param arg3 Argument to be passed on to the functor.
    * \param arg4 Argument to be passed on to the functor.
    * \param arg5 Argument to be ignored.
    * \param arg6 Argument to be passed on to the functor.
    * \return The return value of the functor invocation.
    */
    template<typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5, T_arg6 arg6)
    {
        return this->m_functor.template operator()<
                typename QExtTypeTrait<T_arg1>::Pass,
                typename QExtTypeTrait<T_arg2>::Pass,
                typename QExtTypeTrait<T_arg3>::Pass,
                typename QExtTypeTrait<T_arg4>::Pass,
                typename QExtTypeTrait<T_arg6>::Pass>
                (arg1, arg2, arg3, arg4, arg6);
    }

    /** Invokes the wrapped functor, ignoring the 5th argument.
    * \param arg1 Argument to be passed on to the functor.
    * \param arg2 Argument to be passed on to the functor.
    * \param arg3 Argument to be passed on to the functor.
    * \param arg4 Argument to be passed on to the functor.
    * \param arg5 Argument to be ignored.
    * \param arg6 Argument to be passed on to the functor.
    * \param arg7 Argument to be passed on to the functor.
    * \return The return value of the functor invocation.
    */
    template<typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5, T_arg6 arg6, T_arg7 arg7)
    {
        return this->m_functor.template operator()<
                typename QExtTypeTrait<T_arg1>::Pass,
                typename QExtTypeTrait<T_arg2>::Pass,
                typename QExtTypeTrait<T_arg3>::Pass,
                typename QExtTypeTrait<T_arg4>::Pass,
                typename QExtTypeTrait<T_arg6>::Pass,
                typename QExtTypeTrait<T_arg7>::Pass>
                (arg1, arg2, arg3, arg4, arg6, arg7);
    }
};

/** AdaptorType that adds a dummy parameter to the wrapped functor.
* This template specialization ignores the value of the 6th parameter in operator()().
*
* \ingroup qextHideFunctor
*/
template<typename T_functor>
struct QExtHideFunctor<5, T_functor> : public QExtAdapts<T_functor>
{
    typedef typename QExtAdapts<T_functor>::AdaptorType AdaptorType;

    template<typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
            typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename AdaptorType::template ReturnTypeDeduce<
                typename QExtTypeTrait<T_arg1>::Pass,
                typename QExtTypeTrait<T_arg2>::Pass,
                typename QExtTypeTrait<T_arg3>::Pass,
                typename QExtTypeTrait<T_arg4>::Pass,
                typename QExtTypeTrait<T_arg5>::Pass,
                typename QExtTypeTrait<T_arg7>::Pass>::Type Type;
    };
    typedef typename AdaptorType::ResultType ResultType;

    /** Constructs a hide_functor object that adds a dummy parameter to the passed functor.
    * \param func Functor to invoke from operator()().
    */
    explicit QExtHideFunctor(const T_functor &func) : QExtAdapts<T_functor>(func) {}

    QExtHideFunctor(const QExtHideFunctor &other) : QExtAdapts<T_functor>(other) {}

    /** Invokes the wrapped functor, ignoring the 6th argument.
    * \param arg1 Argument to be passed on to the functor.
    * \param arg2 Argument to be passed on to the functor.
    * \param arg3 Argument to be passed on to the functor.
    * \param arg4 Argument to be passed on to the functor.
    * \param arg5 Argument to be passed on to the functor.
    * \param arg6 Argument to be ignored.
    * \return The return value of the functor invocation.
    */
    template<typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6)
    {
        return this->m_functor.template operator()<
                typename QExtTypeTrait<T_arg1>::Pass,
                typename QExtTypeTrait<T_arg2>::Pass,
                typename QExtTypeTrait<T_arg3>::Pass,
                typename QExtTypeTrait<T_arg4>::Pass,
                typename QExtTypeTrait<T_arg5>::Pass>
                (arg1, arg2, arg3, arg4, arg5);
    }

    /** Invokes the wrapped functor, ignoring the 6th argument.
    * \param arg1 Argument to be passed on to the functor.
    * \param arg2 Argument to be passed on to the functor.
    * \param arg3 Argument to be passed on to the functor.
    * \param arg4 Argument to be passed on to the functor.
    * \param arg5 Argument to be passed on to the functor.
    * \param arg6 Argument to be ignored.
    * \param arg7 Argument to be passed on to the functor.
    * \return The return value of the functor invocation.
    */
    template<typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6, T_arg7 arg7)
    {
        return this->m_functor.template operator()<
                typename QExtTypeTrait<T_arg1>::Pass,
                typename QExtTypeTrait<T_arg2>::Pass,
                typename QExtTypeTrait<T_arg3>::Pass,
                typename QExtTypeTrait<T_arg4>::Pass,
                typename QExtTypeTrait<T_arg5>::Pass,
                typename QExtTypeTrait<T_arg7>::Pass>
                (arg1, arg2, arg3, arg4, arg5, arg7);
    }
};

/** AdaptorType that adds a dummy parameter to the wrapped functor.
* This template specialization ignores the value of the 7th parameter in operator()().
*
* \ingroup qextHideFunctor
*/
template<typename T_functor>
struct QExtHideFunctor<6, T_functor> : public QExtAdapts<T_functor>
{
    typedef typename QExtAdapts<T_functor>::AdaptorType AdaptorType;

    template<typename T_arg1 = void,
            typename T_arg2 = void, typename T_arg3 = void,
            typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename AdaptorType::template ReturnTypeDeduce<
                typename QExtTypeTrait<T_arg1>::Pass,
                typename QExtTypeTrait<T_arg2>::Pass,
                typename QExtTypeTrait<T_arg3>::Pass,
                typename QExtTypeTrait<T_arg4>::Pass,
                typename QExtTypeTrait<T_arg5>::Pass,
                typename QExtTypeTrait<T_arg6>::Pass>::Type Type;
    };
    typedef typename AdaptorType::ResultType ResultType;

    /** Constructs a hide_functor object that adds a dummy parameter to the passed functor.
    * \param func Functor to invoke from operator()().
    */
    explicit QExtHideFunctor(const T_functor &func) : QExtAdapts<T_functor>(func) {}

    QExtHideFunctor(const QExtHideFunctor &other) : QExtAdapts<T_functor>(other) {}

    /** Invokes the wrapped functor, ignoring the 7th argument.
    * \param arg1 Argument to be passed on to the functor.
    * \param arg2 Argument to be passed on to the functor.
    * \param arg3 Argument to be passed on to the functor.
    * \param arg4 Argument to be passed on to the functor.
    * \param arg5 Argument to be passed on to the functor.
    * \param arg6 Argument to be passed on to the functor.
    * \param arg7 Argument to be ignored.
    * \return The return value of the functor invocation.
    */
    template<typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7)
    {
        return this->m_functor.template operator()<
                typename QExtTypeTrait<T_arg1>::Pass,
                typename QExtTypeTrait<T_arg2>::Pass,
                typename QExtTypeTrait<T_arg3>::Pass,
                typename QExtTypeTrait<T_arg4>::Pass,
                typename QExtTypeTrait<T_arg5>::Pass,
                typename QExtTypeTrait<T_arg6>::Pass>
                (arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

//template specialization of visitor<>::do_visit_each<>(action, functor):
/** Performs a functor on each of the targets of a functor.
* The function overload for QExtHideFunctor performs a functor on the
* functor stored in the QExtHideFunctor object.
*
* \ingroup qextHideFunctor
*/
template<int I_location, typename T_functor>
struct QExtVisitor<QExtHideFunctor<I_location, T_functor> >
{
    template<typename T_action>
    static void doVisitEach(const T_action &action,
                            const QExtHideFunctor<I_location, T_functor> &target)
    {
        qextVisitEach(action, target.m_functor);
    }
};

/** Creates an adaptor of type QExtHideFunctor which adds a dummy parameter to the passed functor.
* The optional template argument @e I_location specifies the zero-based
* position of the dummy parameter in the returned functor (@p -1 stands for the last parameter).
*
* \param func Functor that should be wrapped.
* \return AdaptorType that executes @e func, ignoring the value of the dummy parameter.
*
* \ingroup qextHideFunctor
*/
template<int I_location, typename T_functor>
inline QExtHideFunctor<I_location, T_functor>
qextHideFunctor(const T_functor &func)
{
    return QExtHideFunctor<I_location, T_functor>(func);
}

/** Creates an adaptor of type QExtHideFunctor which adds a dummy parameter to the passed functor.
* This overload adds a dummy parameter at the back of the functor's parameter list.
*
* \param func Functor that should be wrapped.
* \return AdaptorType that executes @e func, ignoring the value of the last parameter.
*
* \ingroup qextHideFunctor
*/
template<typename T_functor>
inline QExtHideFunctor<-1, T_functor>
qextHideFunctor(const T_functor &func)
{
    return QExtHideFunctor<-1, T_functor>(func);
}


#endif // _QEXTHIDEFUNCTOR_H
