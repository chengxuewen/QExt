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

#ifndef _QEXTBINDRETURNFUNCTOR_H
#define _QEXTBINDRETURNFUNCTOR_H

#include <qextAdaptorTrait.h>
#include <qextBoundArgument.h>
#include <qextReferenceWrapper.h>

/**
 * @brief AdaptorType that fixes the return value of the wrapped functor.
 * Use the convenience function qextBindReturnFunctor() to create an instance of QExtBindReturnFunctor.
 *
 * The following template arguments are used:
 * @tparam Return Type of the fixed return value.
 * @tparam Functor Type of the functor to wrap.
 */
template <class Return, class Functor>
struct QExtBindReturnFunctor : public QExtAdapts<Functor>
{
    template <class Arg1 = void, class Arg2 = void>
    struct ReturnTypeDeduce
    {
        typedef typename QExtUnwrapReference<Return>::Type Type;
    };
    typedef typename QExtUnwrapReference<Return>::Type ResultType;

    /** Constructs a bind_return_functor object that fixes the return value to @p returnValue.
     * @param functor Functor to invoke from operator()().
     * @param returnValue Value to return from operator()().
     */
    QExtBindReturnFunctor(typename QExtTypeTrait<Functor>::Take functor, typename QExtTypeTrait<Return>::Take returnValue)
        : QExtAdapts<Functor>(functor), mReturnValue(returnValue) {}
    QExtBindReturnFunctor(const QExtBindReturnFunctor &other)
        : QExtAdapts<Functor>(other), mReturnValue(other.mReturnValue) {}

    /**
     * @brief Invokes the wrapped functor dropping its return value.
     * @return The fixed return value.
     */
    typename QExtUnwrapReference<Return>::Type
    operator()()
    {
        this->mFunctor();
        return mReturnValue.invoke();
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * @param arg1 Argument to be passed on to the functor.
     * @return The fixed return value.
     */
    template <class Arg1>
    typename QExtUnwrapReference<Return>::Type
    operator()(Arg1 arg1)
    {
        this->mFunctor.template operator()<typename QExtTypeTrait<Arg1>::Pass>(arg1);
        return mReturnValue.invoke();
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @return The fixed return value.
     */
    template <class Arg1, class Arg2>
    typename QExtUnwrapReference<Return>::Type
    operator()(Arg1 arg1, Arg2 arg2)
    {
        this->mFunctor.template operator()<typename QExtTypeTrait<Arg1>::Pass,
                                           typename QExtTypeTrait<Arg2>::Pass>(arg1, arg2);
        return mReturnValue.invoke();
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @return The fixed return value.
     */
    template <class Arg1, class Arg2, class Arg3>
    typename QExtUnwrapReference<Return>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3)
    {
        this->mFunctor.template operator()<typename QExtTypeTrait<Arg1>::Pass,
                                           typename QExtTypeTrait<Arg2>::Pass,
                                           typename QExtTypeTrait<Arg3>::Pass>(arg1, arg2, arg3);
        return mReturnValue.invoke();
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @return The fixed return value.
     */
    template <class Arg1, class Arg2, class Arg3, class Arg4>
    typename QExtUnwrapReference<Return>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4)
    {
        this->mFunctor.template operator()<typename QExtTypeTrait<Arg1>::Pass,
                                           typename QExtTypeTrait<Arg2>::Pass,
                                           typename QExtTypeTrait<Arg3>::Pass,
                                           typename QExtTypeTrait<Arg4>::Pass>(arg1, arg2, arg3, arg4);
        return mReturnValue.invoke();
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @return The fixed return value.
     */
    template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
    typename QExtUnwrapReference<Return>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5)
    {
        this->mFunctor.template operator()<typename QExtTypeTrait<Arg1>::Pass,
                                           typename QExtTypeTrait<Arg2>::Pass,
                                           typename QExtTypeTrait<Arg3>::Pass,
                                           typename QExtTypeTrait<Arg4>::Pass,
                                           typename QExtTypeTrait<Arg5>::Pass>(arg1, arg2, arg3, arg4, arg5);
        return mReturnValue.invoke();
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @param arg6 Argument to be passed on to the functor.
     * @return The fixed return value.
     */
    template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
    typename QExtUnwrapReference<Return>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6)
    {
        this->mFunctor.template operator()<typename QExtTypeTrait<Arg1>::Pass,
                                           typename QExtTypeTrait<Arg2>::Pass,
                                           typename QExtTypeTrait<Arg3>::Pass,
                                           typename QExtTypeTrait<Arg4>::Pass,
                                           typename QExtTypeTrait<Arg5>::Pass,
                                           typename QExtTypeTrait<Arg6>::Pass>(arg1, arg2, arg3, arg4, arg5, arg6);
        return mReturnValue.invoke();
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @param arg6 Argument to be passed on to the functor.
     * @param arg7 Argument to be passed on to the functor.
     * @return The fixed return value.
     */
    template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
    typename QExtUnwrapReference<Return>::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6, Arg7 arg7)
    {
        this->mFunctor.template operator()<typename QExtTypeTrait<Arg1>::Pass,
                                           typename QExtTypeTrait<Arg2>::Pass,
                                           typename QExtTypeTrait<Arg3>::Pass,
                                           typename QExtTypeTrait<Arg4>::Pass,
                                           typename QExtTypeTrait<Arg5>::Pass,
                                           typename QExtTypeTrait<Arg6>::Pass,
                                           typename QExtTypeTrait<Arg7>::Pass>(arg1, arg2, arg3, arg4, arg5, arg6,
                                                                               arg7);
        return mReturnValue.invoke();
    }

    QExtBoundArgument<Return> mReturnValue; // The fixed return value.
};

/**
 * @brief Performs a functor on each of the targets of a functor.
 * The function overload for QExtBindReturnFunctor performs a functor on the
 * functor and on the object instance stored in the QExtBindReturnFunctor object.
 */
template <class Return, class Functor>
struct QExtVisitor<QExtBindReturnFunctor<Return, Functor> >
{
    typedef QExtBindReturnFunctor<Return, Functor> TargetType;
    template <class Action>
    static void doVisitEach(const Action &action, const TargetType &target)
    {
        qextVisitEach(action, target.mReturnValue);
        qextVisitEach(action, target.mFunctor);
    }
};

/**
 * @brief Creates an adaptor of type QExtBindReturnFunctor which fixes the return value of the passed functor to
 * the passed argument.
 * @param functor Functor that should be wrapped.
 * @param returnValue Argument to fix the return value of @e functor to.
 * @return AdaptorType that executes @e functor on invokation and returns @e returnValue.
 */
template <class Return, class Functor>
QExtBindReturnFunctor<Return, Functor>
qextBindReturnFunctor(const Functor &functor, Return returnValue)
{
    return QExtBindReturnFunctor<Return, Functor>(functor, returnValue);
}

#endif // _QEXTBINDRETURNFUNCTOR_H
