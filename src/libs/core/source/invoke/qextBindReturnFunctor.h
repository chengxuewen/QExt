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

/** AdaptorType that fixes the return value of the wrapped functor.
 * Use the convenience function qextBindReturnFunctor() to create an instance of QExtBindReturnFunctor.
 *
 * The following template arguments are used:
 * - @e T_return Type of the fixed return value.
 * - @e T_functor Type of the functor to wrap.
 *
 * \ingroup qextBindFunctor
 */
template <typename T_return, typename T_functor>
struct QExtBindReturnFunctor : public QExtAdapts<T_functor>
{
    template <typename T_arg1 = void, typename T_arg2 = void>
    struct ReturnTypeDeduce
    {
        typedef typename QEXTUnwrapReference<T_return>::Type Type;
    };
    typedef typename QEXTUnwrapReference<T_return>::Type ResultType;

    /** Constructs a bind_return_functor object that fixes the return value to @p returnValue.
     * \param functor Functor to invoke from operator()().
     * \param returnValue Value to return from operator()().
     */
    QExtBindReturnFunctor(typename QExtTypeTrait<T_functor>::Take functor, typename QExtTypeTrait<T_return>::Take returnValue)
        : QExtAdapts<T_functor>(functor), m_returnValue(returnValue) {}
    QExtBindReturnFunctor(const QExtBindReturnFunctor &other)
        : QExtAdapts<T_functor>(other), m_returnValue(other.m_returnValue) {}

    /** Invokes the wrapped functor dropping its return value.
     * \return The fixed return value.
     */
    typename QEXTUnwrapReference<T_return>::Type
    operator()()
    {
        this->m_functor();
        return m_returnValue.invoke();
    }

    /** Invokes the wrapped functor passing on the arguments.
     * \param arg1 Argument to be passed on to the functor.
     * \return The fixed return value.
     */
    template <typename T_arg1>
    typename QEXTUnwrapReference<T_return>::Type
    operator()(T_arg1 arg1)
    {
        this->m_functor.template operator() <
        typename QExtTypeTrait<T_arg1>::Pass > (arg1);
        return m_returnValue.invoke();
    }

    /** Invokes the wrapped functor passing on the arguments.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \return The fixed return value.
     */
    template <typename T_arg1, typename T_arg2>
    typename QEXTUnwrapReference<T_return>::Type
    operator()(T_arg1 arg1, T_arg2 arg2)
    {
        this->m_functor.template operator() <
        typename QExtTypeTrait<T_arg1>::Pass,
                 typename QExtTypeTrait<T_arg2>::Pass > (arg1, arg2);
        return m_returnValue.invoke();
    }

    /** Invokes the wrapped functor passing on the arguments.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \param arg3 Argument to be passed on to the functor.
     * \return The fixed return value.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3>
    typename QEXTUnwrapReference<T_return>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3)
    {
        this->m_functor.template operator() <
        typename QExtTypeTrait<T_arg1>::Pass,
                 typename QExtTypeTrait<T_arg2>::Pass,
                 typename QExtTypeTrait<T_arg3>::Pass > (arg1, arg2, arg3);
        return m_returnValue.invoke();
    }

    /** Invokes the wrapped functor passing on the arguments.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \param arg3 Argument to be passed on to the functor.
     * \param arg4 Argument to be passed on to the functor.
     * \return The fixed return value.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename QEXTUnwrapReference<T_return>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4)
    {
        this->m_functor.template operator() <
        typename QExtTypeTrait<T_arg1>::Pass,
                 typename QExtTypeTrait<T_arg2>::Pass,
                 typename QExtTypeTrait<T_arg3>::Pass,
                 typename QExtTypeTrait<T_arg4>::Pass > (arg1, arg2, arg3, arg4);
        return m_returnValue.invoke();
    }

    /** Invokes the wrapped functor passing on the arguments.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \param arg3 Argument to be passed on to the functor.
     * \param arg4 Argument to be passed on to the functor.
     * \param arg5 Argument to be passed on to the functor.
     * \return The fixed return value.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename QEXTUnwrapReference<T_return>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5)
    {
        this->m_functor.template operator() <
        typename QExtTypeTrait<T_arg1>::Pass,
                 typename QExtTypeTrait<T_arg2>::Pass,
                 typename QExtTypeTrait<T_arg3>::Pass,
                 typename QExtTypeTrait<T_arg4>::Pass,
                 typename QExtTypeTrait<T_arg5>::Pass > (arg1, arg2, arg3, arg4, arg5);
        return m_returnValue.invoke();
    }

    /** Invokes the wrapped functor passing on the arguments.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \param arg3 Argument to be passed on to the functor.
     * \param arg4 Argument to be passed on to the functor.
     * \param arg5 Argument to be passed on to the functor.
     * \param arg6 Argument to be passed on to the functor.
     * \return The fixed return value.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename QEXTUnwrapReference<T_return>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6)
    {
        this->m_functor.template operator() <
        typename QExtTypeTrait<T_arg1>::Pass,
                 typename QExtTypeTrait<T_arg2>::Pass,
                 typename QExtTypeTrait<T_arg3>::Pass,
                 typename QExtTypeTrait<T_arg4>::Pass,
                 typename QExtTypeTrait<T_arg5>::Pass,
                 typename QExtTypeTrait<T_arg6>::Pass > (arg1, arg2, arg3, arg4, arg5, arg6);
        return m_returnValue.invoke();
    }

    /** Invokes the wrapped functor passing on the arguments.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \param arg3 Argument to be passed on to the functor.
     * \param arg4 Argument to be passed on to the functor.
     * \param arg5 Argument to be passed on to the functor.
     * \param arg6 Argument to be passed on to the functor.
     * \param arg7 Argument to be passed on to the functor.
     * \return The fixed return value.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    typename QEXTUnwrapReference<T_return>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7)
    {
        this->m_functor.template operator() <
        typename QExtTypeTrait<T_arg1>::Pass,
                 typename QExtTypeTrait<T_arg2>::Pass,
                 typename QExtTypeTrait<T_arg3>::Pass,
                 typename QExtTypeTrait<T_arg4>::Pass,
                 typename QExtTypeTrait<T_arg5>::Pass,
                 typename QExtTypeTrait<T_arg6>::Pass,
                 typename QExtTypeTrait<T_arg7>::Pass > (arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        return m_returnValue.invoke();
    }

    // The fixed return value.
    QExtBoundArgument<T_return> m_returnValue;
};


//template specialization of visitor<>::do_visit_each<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for QExtBindReturnFunctor performs a functor on the
 * functor and on the object instance stored in the QExtBindReturnFunctor object.
 *
 * \ingroup qextBindFunctor
 */
template <typename T_return, typename T_functor>
struct QExtVisitor<QExtBindReturnFunctor<T_return, T_functor> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QExtBindReturnFunctor<T_return, T_functor> &target)
    {
        qextVisitEach(action, target.m_returnValue);
        qextVisitEach(action, target.m_functor);
    }
};

/** Creates an adaptor of type QExtBindReturnFunctor which fixes the return value of the passed functor to the passed argument.
 *
 * \param functor Functor that should be wrapped.
 * \param returnValue Argument to fix the return value of @e functor to.
 * \return AdaptorType that executes @e functor on invokation and returns @e returnValue.
 *
 * \ingroup qextBindFunctor
 */
template <typename T_return, typename T_functor>
QExtBindReturnFunctor<T_return, T_functor>
qextBindReturnFunctor(const T_functor &functor, T_return returnValue)
{
    return QExtBindReturnFunctor<T_return, T_functor>(functor, returnValue);
}

#endif // _QEXTBINDRETURNFUNCTOR_H
