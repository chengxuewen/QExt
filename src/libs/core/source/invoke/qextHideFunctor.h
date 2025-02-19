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

/**
 * @defgroup qextMakeHideFunctor qextMakeHideFunctor(), hide_return()
 * qextMakeHideFunctor() alters an arbitrary functor in that it adds a parameter whose value is ignored on invocation of
 * the returned functor.
 * Thus you can discard one argument of a signal.
 *
 * You may optionally specify the zero-based position of the parameter to ignore as a template argument.
 * The default is to ignore the last parameter.
 * (A value of @p -1 adds a parameter at the end so qextMakeHideFunctor<-1>() gives the same result as qextMakeHideFunctor().)
 *
 * The type of the parameter can optionally be specified if not deduced.
 *
 * @par Examples:
 * @code
 * void foo(int, int);
 * // single argument hiding ...
 * qextMakeHideFunctor(&foo)(1,2,3);     // adds a dummy parameter at the back and calls foo(1,2)
 * qextMakeHideFunctor<-1>(&foo)(1,2,3); // same as qextMakeHideFunctor(&foo)(1,2,3) (calls foo(1,2))
 * qextMakeHideFunctor<0>(&foo)(1,2,3);  // adds a dummy parameter at the beginning and calls foo(2,3)
 * qextMakeHideFunctor<1>(&foo)(1,2,3);  // adds a dummy parameter in the middle and calls foo(1,3)
 * qextMakeHideFunctor<2>(&foo)(1,2,3);  // adds a dummy parameter at the back and calls foo(1,2)
 * @endcode
 *
 * The functor qextMakeHideFunctor() returns can be directly passed into
 * signal::connect().
 *
 * @par Example:
 * @code
 * signal<void,int> some_signal;
 * void foo();
 * some_signal.connect(qextMakeHideFunctor(&foo));
 * @endcode
 *
 * qextMakeHideFunctor() can be nested in order to discard multiple arguments.
 * @par Example:
 * @code
 * // multiple argument hiding ...
 * qextMakeHideFunctor(qextMakeHideFunctor(&foo))(1,2,3,4); // adds two dummy parameters at the back and calls foo(1,2)
 * @endcode
 *
 * qextHideReturnFunctor() alters an arbitrary functor by dropping its return value, thus converting it to a void functor.
 *
 * For a more powerful version of this functionality see the lambda library adaptor group() which can bind,
 * qextMakeHideFunctor and reorder arguments arbitrarily. Although group() is more flexible,
 * qextMakeHideFunctor() provides a means of hiding parameters when the total number of parameters called is variable.
 */



/**
 * @brief AdaptorType that adds a dummy parameter to the wrapped functor.
 * Use the convenience function qextMakeHideFunctor() to create an instance of QExtHideFunctor.
 *
 * The following template arguments are used:
 * @e I_location Zero-based position of the dummy parameter (@p -1 for the last parameter).
 * @e T_type Type of the dummy parameter.
 * @e Functor Type of the functor to wrap.
*/
template<int I_location, class Functor>
struct QExtHideFunctor;

/**
 * @brief AdaptorType that adds a dummy parameter to the wrapped functor.
 * This template specialization ignores the value of the last parameter in operator()().
 */
template<class Functor>
struct QExtHideFunctor<-1, Functor> : public QExtAdapts<Functor>
{
    typedef typename QExtAdapts<Functor>::AdaptorType AdaptorType;

    template<class Arg1 = void,
             class Arg2 = void,
             class Arg3 = void,
             class Arg4 = void,
             class Arg5 = void,
             class Arg6 = void,
             class Arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename AdaptorType::template ReturnTypeDeduce<typename QExtTypeTrait<Arg1>::Pass,
                                                                typename QExtTypeTrait<Arg2>::Pass,
                                                                typename QExtTypeTrait<Arg3>::Pass,
                                                                typename QExtTypeTrait<Arg4>::Pass,
                                                                typename QExtTypeTrait<Arg5>::Pass,
                                                                typename QExtTypeTrait<Arg6>::Pass>::Type Type;
    };

    typedef typename AdaptorType::ResultType ResultType;

    /**
     * @brief Constructs a hide_functor object that adds a dummy parameter to the passed functor.
     * @param func Functor to invoke from operator()().
     */
    explicit QExtHideFunctor(const Functor &func) : QExtAdapts<Functor>(func) {}

    QExtHideFunctor(const QExtHideFunctor &other) : QExtAdapts<Functor>(other) {}

    /**
     * @brief Invokes the wrapped functor ignoring the only argument.
     * @param arg1 Argument to be ignored.
     * @return The return value of the functor invocation.
     */
    template<class Arg1>
    typename ReturnTypeDeduce<Arg1>::Type
    operator()(Arg1)
    {
        return this->mFunctor();
    }

    /**
     * @brief Invokes the wrapped functor, ignoring the last argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be ignored.
     * @return The return value of the functor invocation.
     */
    template<class Arg1, class Arg2>
    typename ReturnTypeDeduce<Arg1, Arg2>::Type
    operator()(Arg1 arg1, Arg2)
    {
        return this->mFunctor.template operator()<typename QExtTypeTrait<Arg1>::Pass>(arg1);
    }

    /**
     * @brief Invokes the wrapped functor, ignoring the last argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be ignored.
     * @return The return value of the functor invocation.
     */
    template<class Arg1, class Arg2, class Arg3>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3)
    {
        return this->mFunctor.template operator()<typename QExtTypeTrait<Arg1>::Pass,
                                                  typename QExtTypeTrait<Arg2>::Pass>(arg1, arg2);
    }

    /**
     * @brief Invokes the wrapped functor, ignoring the last argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be ignored.
     * @return The return value of the functor invocation.
     */
    template<class Arg1, class Arg2, class Arg3, class Arg4>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4)
    {
        return this->mFunctor.template operator()<typename QExtTypeTrait<Arg1>::Pass,
                                                  typename QExtTypeTrait<Arg2>::Pass,
                                                  typename QExtTypeTrait<Arg3>::Pass>(arg1, arg2, arg3);
    }

    /**
     * @brief Invokes the wrapped functor, ignoring the last argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be ignored.
     * @return The return value of the functor invocation.
     */
    template<class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4, Arg5>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5)
    {
        return this->mFunctor.template operator()<typename QExtTypeTrait<Arg1>::Pass,
                                                  typename QExtTypeTrait<Arg2>::Pass,
                                                  typename QExtTypeTrait<Arg3>::Pass,
                                                  typename QExtTypeTrait<Arg4>::Pass>(arg1, arg2, arg3, arg4);
    }

    /**
     * @brief Invokes the wrapped functor, ignoring the last argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @param arg6 Argument to be ignored.
     * @return The return value of the functor invocation.
     */
    template<class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6)
    {
        return this->mFunctor.template operator()<typename QExtTypeTrait<Arg1>::Pass,
                                                  typename QExtTypeTrait<Arg2>::Pass,
                                                  typename QExtTypeTrait<Arg3>::Pass,
                                                  typename QExtTypeTrait<Arg4>::Pass,
                                                  typename QExtTypeTrait<Arg5>::Pass>(arg1, arg2, arg3, arg4, arg5);
    }

    /**
     * @brief Invokes the wrapped functor, ignoring the last argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @param arg6 Argument to be passed on to the functor.
     * @param arg7 Argument to be ignored.
     * @return The return value of the functor invocation.
     */
    template<class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6, Arg7)
    {
        return this->mFunctor.template operator()<typename QExtTypeTrait<Arg1>::Pass,
                                                  typename QExtTypeTrait<Arg2>::Pass,
                                                  typename QExtTypeTrait<Arg3>::Pass,
                                                  typename QExtTypeTrait<Arg4>::Pass,
                                                  typename QExtTypeTrait<Arg5>::Pass,
                                                  typename QExtTypeTrait<Arg6>::Pass>(arg1, arg2, arg3, arg4, arg5,
                                                                                      arg6);
    }
};

/**
 * @brief AdaptorType that adds a dummy parameter to the wrapped functor.
 * This template specialization ignores the value of the 1st parameter in operator()().
 */
template<class Functor>
struct QExtHideFunctor<0, Functor> : public QExtAdapts<Functor>
{
    typedef typename QExtAdapts<Functor>::AdaptorType AdaptorType;

    template<class Arg1 = void,
             class Arg2 = void,
             class Arg3 = void,
             class Arg4 = void,
             class Arg5 = void,
             class Arg6 = void,
             class Arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename AdaptorType::template ReturnTypeDeduce<typename QExtTypeTrait<Arg2>::Pass,
                                                                typename QExtTypeTrait<Arg3>::Pass,
                                                                typename QExtTypeTrait<Arg4>::Pass,
                                                                typename QExtTypeTrait<Arg5>::Pass,
                                                                typename QExtTypeTrait<Arg6>::Pass,
                                                                typename QExtTypeTrait<Arg7>::Pass>::Type Type;
    };

    typedef typename AdaptorType::ResultType ResultType;

    /**
     * @brief Constructs a hide_functor object that adds a dummy parameter to the passed functor.
     * @param func Functor to invoke from operator()().
     */
    explicit QExtHideFunctor(const Functor &func) : QExtAdapts<Functor>(func) {}

    QExtHideFunctor(const QExtHideFunctor &other) : QExtAdapts<Functor>(other) {}

    /**
     * @brief Invokes the wrapped functor ignoring the only argument.
     * @param arg1 Argument to be ignored.
     * @return The return value of the functor invocation.
     */
    template<class Arg1>
    typename ReturnTypeDeduce<Arg1>::Type
    operator()(Arg1)
    {
        return this->mFunctor();
    }

    /**
     * @brief Invokes the wrapped functor, ignoring the 1st argument.
     * @param arg1 Argument to be ignored.
     * @param arg2 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template<class Arg1, class Arg2>
    typename ReturnTypeDeduce<Arg1, Arg2>::Type
    operator()(Arg1, Arg2 arg2)
    {
        return this->mFunctor.template operator()<typename QExtTypeTrait<Arg2>::Pass>(arg2);
    }

    /**
     * @brief Invokes the wrapped functor, ignoring the 1st argument.
     * @param arg1 Argument to be ignored.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template<class Arg1, class Arg2, class Arg3>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3>::Type
    operator()(Arg1, Arg2 arg2, Arg3 arg3)
    {
        return this->mFunctor.template operator()<typename QExtTypeTrait<Arg2>::Pass,
                                                  typename QExtTypeTrait<Arg3>::Pass>(arg2, arg3);
    }

    /**
     * @brief Invokes the wrapped functor, ignoring the 1st argument.
     * @param arg1 Argument to be ignored.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template<class Arg1, class Arg2, class Arg3, class Arg4>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4>::Type
    operator()(Arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4)
    {
        return this->mFunctor.template operator()<typename QExtTypeTrait<Arg2>::Pass,
                                                  typename QExtTypeTrait<Arg3>::Pass,
                                                  typename QExtTypeTrait<Arg4>::Pass>(arg2, arg3, arg4);
    }

    /**
     * @brief Invokes the wrapped functor, ignoring the 1st argument.
     * @param arg1 Argument to be ignored.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template<class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4, Arg5>::Type
    operator()(Arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5)
    {
        return this->mFunctor.template operator()<typename QExtTypeTrait<Arg2>::Pass,
                                                  typename QExtTypeTrait<Arg3>::Pass,
                                                  typename QExtTypeTrait<Arg4>::Pass,
                                                  typename QExtTypeTrait<Arg5>::Pass>(arg2, arg3, arg4, arg5);
    }

    /**
     * @brief Invokes the wrapped functor, ignoring the 1st argument.
     * @param arg1 Argument to be ignored.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @param arg6 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template<class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>::Type
    operator()(Arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6)
    {
        return this->mFunctor.template operator()<typename QExtTypeTrait<Arg2>::Pass,
                                                  typename QExtTypeTrait<Arg3>::Pass,
                                                  typename QExtTypeTrait<Arg4>::Pass,
                                                  typename QExtTypeTrait<Arg5>::Pass,
                                                  typename QExtTypeTrait<Arg6>::Pass>(arg2, arg3, arg4, arg5, arg6);
    }

    /**
     * @brief Invokes the wrapped functor, ignoring the 1st argument.
     * @param arg1 Argument to be ignored.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @param arg6 Argument to be passed on to the functor.
     * @param arg7 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template<class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>::Type
    operator()(Arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6, Arg7 arg7)
    {
        return this->mFunctor.template operator()<typename QExtTypeTrait<Arg2>::Pass,
                                                  typename QExtTypeTrait<Arg3>::Pass,
                                                  typename QExtTypeTrait<Arg4>::Pass,
                                                  typename QExtTypeTrait<Arg5>::Pass,
                                                  typename QExtTypeTrait<Arg6>::Pass,
                                                  typename QExtTypeTrait<Arg7>::Pass>(arg2, arg3, arg4, arg5, arg6,
                                                                                      arg7);
    }
};

/**
 * @brief AdaptorType that adds a dummy parameter to the wrapped functor.
 * This template specialization ignores the value of the 2nd parameter in operator()().
 */
template<class Functor>
struct QExtHideFunctor<1, Functor> : public QExtAdapts<Functor>
{
    typedef typename QExtAdapts<Functor>::AdaptorType AdaptorType;

    template<class Arg1 = void,
             class Arg2 = void,
             class Arg3 = void,
             class Arg4 = void,
             class Arg5 = void,
             class Arg6 = void,
             class Arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename AdaptorType::template ReturnTypeDeduce<typename QExtTypeTrait<Arg1>::Pass,
                                                                typename QExtTypeTrait<Arg3>::Pass,
                                                                typename QExtTypeTrait<Arg4>::Pass,
                                                                typename QExtTypeTrait<Arg5>::Pass,
                                                                typename QExtTypeTrait<Arg6>::Pass,
                                                                typename QExtTypeTrait<Arg7>::Pass>::Type Type;
    };

    typedef typename AdaptorType::ResultType ResultType;

    /**
     * @brief Constructs a hide_functor object that adds a dummy parameter to the passed functor.
     * @param func Functor to invoke from operator()().
     */
    explicit QExtHideFunctor(const Functor &func) : QExtAdapts<Functor>(func) {}

    QExtHideFunctor(const QExtHideFunctor &other) : QExtAdapts<Functor>(other) {}

    /**
     * @brief Invokes the wrapped functor, ignoring the 2nd argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be ignored.
     * @return The return value of the functor invocation.
     */
    template<class Arg1, class Arg2>
    typename ReturnTypeDeduce<Arg1, Arg2>::Type
    operator()(Arg1 arg1, Arg2)
    {
        return this->mFunctor.template operator()<typename QExtTypeTrait<Arg1>::Pass>(arg1);
    }

    /**
     * @brief Invokes the wrapped functor, ignoring the 2nd argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be ignored.
     * @param arg3 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template<class Arg1, class Arg2, class Arg3>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3>::Type
    operator()(Arg1 arg1, Arg2, Arg3 arg3)
    {
        return this->mFunctor.template operator()<typename QExtTypeTrait<Arg1>::Pass,
                                                  typename QExtTypeTrait<Arg3>::Pass>(arg1, arg3);
    }

    /**
     * @brief Invokes the wrapped functor, ignoring the 2nd argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be ignored.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template<class Arg1, class Arg2, class Arg3, class Arg4>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4>::Type
    operator()(Arg1 arg1, Arg2, Arg3 arg3, Arg4 arg4)
    {
        return this->mFunctor.template operator()<typename QExtTypeTrait<Arg1>::Pass,
                                                  typename QExtTypeTrait<Arg3>::Pass,
                                                  typename QExtTypeTrait<Arg4>::Pass>(arg1, arg3, arg4);
    }

    /**
     * @brief Invokes the wrapped functor, ignoring the 2nd argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be ignored.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template<class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4, Arg5>::Type
    operator()(Arg1 arg1, Arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5)
    {
        return this->mFunctor.template operator()<typename QExtTypeTrait<Arg1>::Pass,
                                                  typename QExtTypeTrait<Arg3>::Pass,
                                                  typename QExtTypeTrait<Arg4>::Pass,
                                                  typename QExtTypeTrait<Arg5>::Pass>(arg1, arg3, arg4, arg5);
    }

    /**
     * @brief Invokes the wrapped functor, ignoring the 2nd argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be ignored.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @param arg6 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template<class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>::Type
    operator()(Arg1 arg1, Arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6)
    {
        return this->mFunctor.template operator()<typename QExtTypeTrait<Arg1>::Pass,
                                                  typename QExtTypeTrait<Arg3>::Pass,
                                                  typename QExtTypeTrait<Arg4>::Pass,
                                                  typename QExtTypeTrait<Arg5>::Pass,
                                                  typename QExtTypeTrait<Arg6>::Pass>(arg1, arg3, arg4, arg5, arg6);
    }

    /**
     * @brief Invokes the wrapped functor, ignoring the 2nd argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be ignored.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @param arg6 Argument to be passed on to the functor.
     * @param arg7 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template<class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>::Type
    operator()(Arg1 arg1, Arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6, Arg7 arg7)
    {
        return this->mFunctor.template operator()<typename QExtTypeTrait<Arg1>::Pass,
                                                  typename QExtTypeTrait<Arg3>::Pass,
                                                  typename QExtTypeTrait<Arg4>::Pass,
                                                  typename QExtTypeTrait<Arg5>::Pass,
                                                  typename QExtTypeTrait<Arg6>::Pass,
                                                  typename QExtTypeTrait<Arg7>::Pass>(arg1, arg3, arg4, arg5, arg6,
                                                                                      arg7);
    }
};

/**
 * @brief AdaptorType that adds a dummy parameter to the wrapped functor.
 * This template specialization ignores the value of the 3rd parameter in operator()().
 */
template<class Functor>
struct QExtHideFunctor<2, Functor> : public QExtAdapts<Functor>
{
    typedef typename QExtAdapts<Functor>::AdaptorType AdaptorType;

    template<class Arg1 = void,
             class Arg2 = void,
             class Arg3 = void,
             class Arg4 = void,
             class Arg5 = void,
             class Arg6 = void,
             class Arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename AdaptorType::template ReturnTypeDeduce<typename QExtTypeTrait<Arg1>::Pass,
                                                                typename QExtTypeTrait<Arg2>::Pass,
                                                                typename QExtTypeTrait<Arg4>::Pass,
                                                                typename QExtTypeTrait<Arg5>::Pass,
                                                                typename QExtTypeTrait<Arg6>::Pass,
                                                                typename QExtTypeTrait<Arg7>::Pass>::Type Type;
    };
    typedef typename AdaptorType::ResultType ResultType;

    /**
     * @brief Constructs a hide_functor object that adds a dummy parameter to the passed functor.
     * @param func Functor to invoke from operator()().
     */
    explicit QExtHideFunctor(const Functor &func) : QExtAdapts<Functor>(func) {}

    QExtHideFunctor(const QExtHideFunctor &other) : QExtAdapts<Functor>(other) {}

    /**
     * @brief Invokes the wrapped functor, ignoring the 3rd argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be ignored.
     * @return The return value of the functor invocation.
     */
    template<class Arg1, class Arg2, class Arg3>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3)
    {
        return this->mFunctor.template operator()<typename QExtTypeTrait<Arg1>::Pass,
                                                  typename QExtTypeTrait<Arg2>::Pass>(arg1, arg2);
    }

    /**
     * @brief Invokes the wrapped functor, ignoring the 3rd argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be ignored.
     * @param arg4 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template<class Arg1, class Arg2, class Arg3, class Arg4>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3, Arg4 arg4)
    {
        return this->mFunctor.template operator()<typename QExtTypeTrait<Arg1>::Pass,
                                                  typename QExtTypeTrait<Arg2>::Pass,
                                                  typename QExtTypeTrait<Arg4>::Pass>(arg1, arg2, arg4);
    }

    /**
     * @brief Invokes the wrapped functor, ignoring the 3rd argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be ignored.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template<class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4, Arg5>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3, Arg4 arg4, Arg5 arg5)
    {
        return this->mFunctor.template operator()<typename QExtTypeTrait<Arg1>::Pass,
                                                  typename QExtTypeTrait<Arg2>::Pass,
                                                  typename QExtTypeTrait<Arg4>::Pass,
                                                  typename QExtTypeTrait<Arg5>::Pass>(arg1, arg2, arg4, arg5);
    }

    /**
     * @brief Invokes the wrapped functor, ignoring the 3rd argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be ignored.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @param arg6 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template<class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6)
    {
        return this->mFunctor.template operator()<typename QExtTypeTrait<Arg1>::Pass,
                                                  typename QExtTypeTrait<Arg2>::Pass,
                                                  typename QExtTypeTrait<Arg4>::Pass,
                                                  typename QExtTypeTrait<Arg5>::Pass,
                                                  typename QExtTypeTrait<Arg6>::Pass>(arg1, arg2, arg4, arg5, arg6);
    }

    /**
     * @brief Invokes the wrapped functor, ignoring the 3rd argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be ignored.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @param arg6 Argument to be passed on to the functor.
     * @param arg7 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template<class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6, Arg7 arg7)
    {
        return this->mFunctor.template operator()<typename QExtTypeTrait<Arg1>::Pass,
                                                  typename QExtTypeTrait<Arg2>::Pass,
                                                  typename QExtTypeTrait<Arg4>::Pass,
                                                  typename QExtTypeTrait<Arg5>::Pass,
                                                  typename QExtTypeTrait<Arg6>::Pass,
                                                  typename QExtTypeTrait<Arg7>::Pass>(arg1, arg2, arg4, arg5, arg6,
                                                                                      arg7);
    }
};

/**
 * @brief AdaptorType that adds a dummy parameter to the wrapped functor.
 * This template specialization ignores the value of the 4th parameter in operator()().
 */
template<class Functor>
struct QExtHideFunctor<3, Functor> : public QExtAdapts<Functor>
{
    typedef typename QExtAdapts<Functor>::AdaptorType AdaptorType;

    template<class Arg1 = void,
             class Arg2 = void,
             class Arg3 = void,
             class Arg4 = void,
             class Arg5 = void,
             class Arg6 = void,
             class Arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename AdaptorType::template ReturnTypeDeduce<typename QExtTypeTrait<Arg1>::Pass,
                                                                typename QExtTypeTrait<Arg2>::Pass,
                                                                typename QExtTypeTrait<Arg3>::Pass,
                                                                typename QExtTypeTrait<Arg5>::Pass,
                                                                typename QExtTypeTrait<Arg6>::Pass,
                                                                typename QExtTypeTrait<Arg7>::Pass>::Type Type;
    };
    typedef typename AdaptorType::ResultType ResultType;

    /**
     * @brief Constructs a hide_functor object that adds a dummy parameter to the passed functor.
     * @param func Functor to invoke from operator()().
     */
    explicit QExtHideFunctor(const Functor &func) : QExtAdapts<Functor>(func) {}

    QExtHideFunctor(const QExtHideFunctor &other) : QExtAdapts<Functor>(other) {}

    /**
     * @brief Invokes the wrapped functor, ignoring the 4th argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be ignored.
     * @return The return value of the functor invocation.
     */
    template<class Arg1, class Arg2, class Arg3, class Arg4>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4)
    {
        return this->mFunctor.template operator()<typename QExtTypeTrait<Arg1>::Pass,
                                                  typename QExtTypeTrait<Arg2>::Pass,
                                                  typename QExtTypeTrait<Arg3>::Pass>(arg1, arg2, arg3);
    }

    /**
     * @brief Invokes the wrapped functor, ignoring the 4th argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be ignored.
     * @param arg5 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template<class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4, Arg5>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4, Arg5 arg5)
    {
        return this->mFunctor.template operator()<typename QExtTypeTrait<Arg1>::Pass,
                                                  typename QExtTypeTrait<Arg2>::Pass,
                                                  typename QExtTypeTrait<Arg3>::Pass,
                                                  typename QExtTypeTrait<Arg5>::Pass>(arg1, arg2, arg3, arg5);
    }

    /**
     * @brief Invokes the wrapped functor, ignoring the 4th argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be ignored.
     * @param arg5 Argument to be passed on to the functor.
     * @param arg6 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template<class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4, Arg5 arg5, Arg6 arg6)
    {
        return this->mFunctor.template operator()<typename QExtTypeTrait<Arg1>::Pass,
                                                  typename QExtTypeTrait<Arg2>::Pass,
                                                  typename QExtTypeTrait<Arg3>::Pass,
                                                  typename QExtTypeTrait<Arg5>::Pass,
                                                  typename QExtTypeTrait<Arg6>::Pass>(arg1, arg2, arg3, arg5, arg6);
    }

    /**
     * @brief Invokes the wrapped functor, ignoring the 4th argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be ignored.
     * @param arg5 Argument to be passed on to the functor.
     * @param arg6 Argument to be passed on to the functor.
     * @param arg7 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template<class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4, Arg5 arg5, Arg6 arg6, Arg7 arg7)
    {
        return this->mFunctor.template operator()<typename QExtTypeTrait<Arg1>::Pass,
                                                  typename QExtTypeTrait<Arg2>::Pass,
                                                  typename QExtTypeTrait<Arg3>::Pass,
                                                  typename QExtTypeTrait<Arg5>::Pass,
                                                  typename QExtTypeTrait<Arg6>::Pass,
                                                  typename QExtTypeTrait<Arg7>::Pass>(arg1, arg2, arg3, arg5, arg6,
                                                                                      arg7);
    }
};

/**
 * @brief AdaptorType that adds a dummy parameter to the wrapped functor.
 * This template specialization ignores the value of the 5th parameter in operator()().
 */
template<class Functor>
struct QExtHideFunctor<4, Functor> : public QExtAdapts<Functor>
{
    typedef typename QExtAdapts<Functor>::AdaptorType AdaptorType;

    template<class Arg1 = void,
             class Arg2 = void,
             class Arg3 = void,
             class Arg4 = void,
             class Arg5 = void,
             class Arg6 = void,
             class Arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename AdaptorType::template ReturnTypeDeduce<typename QExtTypeTrait<Arg1>::Pass,
                                                                typename QExtTypeTrait<Arg2>::Pass,
                                                                typename QExtTypeTrait<Arg3>::Pass,
                                                                typename QExtTypeTrait<Arg4>::Pass,
                                                                typename QExtTypeTrait<Arg6>::Pass,
                                                                typename QExtTypeTrait<Arg7>::Pass>::Type Type;
    };
    typedef typename AdaptorType::ResultType ResultType;

    /**
     * @brief Constructs a hide_functor object that adds a dummy parameter to the passed functor.
     * @param func Functor to invoke from operator()().
     */
    explicit QExtHideFunctor(const Functor &func) : QExtAdapts<Functor>(func) {}

    QExtHideFunctor(const QExtHideFunctor &other) : QExtAdapts<Functor>(other) {}

    /**
     * @brief Invokes the wrapped functor, ignoring the 5th argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be ignored.
     * @return The return value of the functor invocation.
     */
    template<class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4, Arg5>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5)
    {
        return this->mFunctor.template operator()<typename QExtTypeTrait<Arg1>::Pass,
                                                  typename QExtTypeTrait<Arg2>::Pass,
                                                  typename QExtTypeTrait<Arg3>::Pass,
                                                  typename QExtTypeTrait<Arg4>::Pass>(arg1, arg2, arg3, arg4);
    }

    /**
     * @brief Invokes the wrapped functor, ignoring the 5th argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be ignored.
     * @param arg6 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template<class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5, Arg6 arg6)
    {
        return this->mFunctor.template operator()<typename QExtTypeTrait<Arg1>::Pass,
                                                  typename QExtTypeTrait<Arg2>::Pass,
                                                  typename QExtTypeTrait<Arg3>::Pass,
                                                  typename QExtTypeTrait<Arg4>::Pass,
                                                  typename QExtTypeTrait<Arg6>::Pass>(arg1, arg2, arg3, arg4, arg6);
    }

    /**
     * @brief Invokes the wrapped functor, ignoring the 5th argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be ignored.
     * @param arg6 Argument to be passed on to the functor.
     * @param arg7 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template<class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5, Arg6 arg6, Arg7 arg7)
    {
        return this->mFunctor.template operator()<typename QExtTypeTrait<Arg1>::Pass,
                                                  typename QExtTypeTrait<Arg2>::Pass,
                                                  typename QExtTypeTrait<Arg3>::Pass,
                                                  typename QExtTypeTrait<Arg4>::Pass,
                                                  typename QExtTypeTrait<Arg6>::Pass,
                                                  typename QExtTypeTrait<Arg7>::Pass>(arg1, arg2, arg3, arg4, arg6,
                                                                                      arg7);
    }
};

/**
 * @brief AdaptorType that adds a dummy parameter to the wrapped functor.
 * This template specialization ignores the value of the 6th parameter in operator()().
 */
template<class Functor>
struct QExtHideFunctor<5, Functor> : public QExtAdapts<Functor>
{
    typedef typename QExtAdapts<Functor>::AdaptorType AdaptorType;

    template<class Arg1 = void,
             class Arg2 = void,
             class Arg3 = void,
             class Arg4 = void,
             class Arg5 = void,
             class Arg6 = void,
             class Arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename AdaptorType::template ReturnTypeDeduce<typename QExtTypeTrait<Arg1>::Pass,
                                                                typename QExtTypeTrait<Arg2>::Pass,
                                                                typename QExtTypeTrait<Arg3>::Pass,
                                                                typename QExtTypeTrait<Arg4>::Pass,
                                                                typename QExtTypeTrait<Arg5>::Pass,
                                                                typename QExtTypeTrait<Arg7>::Pass>::Type Type;
    };
    typedef typename AdaptorType::ResultType ResultType;

    /**
     * @brief Constructs a hide_functor object that adds a dummy parameter to the passed functor.
     * @param func Functor to invoke from operator()().
     */
    explicit QExtHideFunctor(const Functor &func) : QExtAdapts<Functor>(func) {}

    QExtHideFunctor(const QExtHideFunctor &other) : QExtAdapts<Functor>(other) {}

    /**
     * @brief Invokes the wrapped functor, ignoring the 6th argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @param arg6 Argument to be ignored.
     * @return The return value of the functor invocation.
     */
    template<class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6)
    {
        return this->mFunctor.template operator()<typename QExtTypeTrait<Arg1>::Pass,
                                                  typename QExtTypeTrait<Arg2>::Pass,
                                                  typename QExtTypeTrait<Arg3>::Pass,
                                                  typename QExtTypeTrait<Arg4>::Pass,
                                                  typename QExtTypeTrait<Arg5>::Pass>(arg1, arg2, arg3, arg4, arg5);
    }

    /**
     * @brief Invokes the wrapped functor, ignoring the 6th argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @param arg6 Argument to be ignored.
     * @param arg7 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template<class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6, Arg7 arg7)
    {
        return this->mFunctor.template operator()<typename QExtTypeTrait<Arg1>::Pass,
                                                  typename QExtTypeTrait<Arg2>::Pass,
                                                  typename QExtTypeTrait<Arg3>::Pass,
                                                  typename QExtTypeTrait<Arg4>::Pass,
                                                  typename QExtTypeTrait<Arg5>::Pass,
                                                  typename QExtTypeTrait<Arg7>::Pass>(arg1, arg2, arg3, arg4, arg5,
                                                                                      arg7);
    }
};

/**
 * @brief AdaptorType that adds a dummy parameter to the wrapped functor.
 * This template specialization ignores the value of the 7th parameter in operator()().
 */
template<class Functor>
struct QExtHideFunctor<6, Functor> : public QExtAdapts<Functor>
{
    typedef typename QExtAdapts<Functor>::AdaptorType AdaptorType;

    template<class Arg1 = void,
             class Arg2 = void,
             class Arg3 = void,
             class Arg4 = void,
             class Arg5 = void,
             class Arg6 = void,
             class Arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename AdaptorType::template ReturnTypeDeduce<typename QExtTypeTrait<Arg1>::Pass,
                                                                typename QExtTypeTrait<Arg2>::Pass,
                                                                typename QExtTypeTrait<Arg3>::Pass,
                                                                typename QExtTypeTrait<Arg4>::Pass,
                                                                typename QExtTypeTrait<Arg5>::Pass,
                                                                typename QExtTypeTrait<Arg6>::Pass>::Type Type;
    };
    typedef typename AdaptorType::ResultType ResultType;

    /**
     * @brief Constructs a hide_functor object that adds a dummy parameter to the passed functor.
     * @param func Functor to invoke from operator()().
     */
    explicit QExtHideFunctor(const Functor &func) : QExtAdapts<Functor>(func) {}

    QExtHideFunctor(const QExtHideFunctor &other) : QExtAdapts<Functor>(other) {}

    /**
     * @brief Invokes the wrapped functor, ignoring the 7th argument.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @param arg6 Argument to be passed on to the functor.
     * @param arg7 Argument to be ignored.
     * @return The return value of the functor invocation.
     */
    template<class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
    typename ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6, Arg7)
    {
        return this->mFunctor.template operator()<typename QExtTypeTrait<Arg1>::Pass,
                                                  typename QExtTypeTrait<Arg2>::Pass,
                                                  typename QExtTypeTrait<Arg3>::Pass,
                                                  typename QExtTypeTrait<Arg4>::Pass,
                                                  typename QExtTypeTrait<Arg5>::Pass,
                                                  typename QExtTypeTrait<Arg6>::Pass>(arg1, arg2, arg3, arg4, arg5,
                                                                                      arg6);
    }
};

/**
 * @brief Performs a functor on each of the targets of a functor.
 * The function overload for QExtHideFunctor performs a functor on the
 * functor stored in the QExtHideFunctor object.
 */
template<int I_location, class Functor>
struct QExtVisitor<QExtHideFunctor<I_location, Functor> >
{
    template<class T_action>
    static void doVisitEach(const T_action &action, const QExtHideFunctor<I_location, Functor> &target)
    {
        qextVisitEach(action, target.mFunctor);
    }
};

/**
 * @brief Creates an adaptor of type QExtHideFunctor which adds a dummy parameter to the passed functor.
 * The optional template argument @e I_location specifies the zero-based
 * position of the dummy parameter in the returned functor (@p -1 stands for the last parameter).
 *
 * @param func Functor that should be wrapped.
 * @return AdaptorType that executes @e func, ignoring the value of the dummy parameter.
 */
template<int I_location, class Functor>
inline QExtHideFunctor<I_location, Functor>
qextMakeHideFunctor(const Functor &func)
{
    return QExtHideFunctor<I_location, Functor>(func);
}

/**
 * @brief Creates an adaptor of type QExtHideFunctor which adds a dummy parameter to the passed functor.
 * This overload adds a dummy parameter at the back of the functor's parameter list.
 *
 * @param func Functor that should be wrapped.
 * @return AdaptorType that executes @e func, ignoring the value of the last parameter.
 */
template<class Functor>
inline QExtHideFunctor<-1, Functor>
qextMakeHideFunctor(const Functor &func)
{
    return QExtHideFunctor<-1, Functor>(func);
}

#endif // _QEXTHIDEFUNCTOR_H
