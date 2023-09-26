/*************************************************************************************
**
** Library: QEXT
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
*************************************************************************************/

#ifndef _QEXTADAPTORTRAIT_H
#define _QEXTADAPTORTRAIT_H

#include <qextFunctorTrait.h>
#include <qextReturnTypeDeduce.h>
#include <qextVisitor.h>

template < typename T_functor >
struct QEXTAdapts;

/** @defgroup adaptors Adaptors
 * Adaptors are functors that alter the signature of a functor's
 * operator()().
 *
 * The adaptor types are created with qextBindFunctor(), qextBindReturnFunctor(), qextHideFunctor(), qextHideReturnFunctor(),
 * qextRetypeReturnFunctor(), qextRetypeFunctor(), qextComposeFunctor(), qextTrackObjectFunctor()
 * and qextLambdaGroup().
 *
 * You can easily derive your own adaptor type from QEXTAdapts.
 */

/** Converts an arbitrary functor into an adaptor type.
 * All adaptor types have
 * a <tt>template operator()</tt> member of every argument count
 * they support. These functions in turn invoke a stored adaptor's
 * <tt>template operator()</tt>, processing the arguments and return
 * value in a characteristic manner. Explicit function template
 * instantiation is used to pass type hints thus saving copy costs.
 *
 * adaptor_functor is a glue between adaptors and arbitrary functors
 * that just passes on the arguments. You won't use this type directly.
 *
 * The template argument @e T_functor determines the type of stored
 * functor.
 *
 * \ingroup QEXTAdapts
 */
template < typename T_functor >
struct QEXTAdaptorFunctor : public QEXTAdaptorBase
{
    typedef typename QEXTFunctorTrait< T_functor >::Return Return;

    template <
        typename T_arg1 = void,
        typename T_arg2 = void,
        typename T_arg3 = void,
        typename T_arg4 = void,
        typename T_arg5 = void,
        typename T_arg6 = void,
        typename T_arg7 = void >
    struct ReturnTypeDeduce
    {
        typedef typename QEXTReturnTypeDeduce< T_functor, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >::Type Type;
    };

    /** Invokes the wrapped functor passing on the arguments.
     * \return The return value of the functor invocation.
     */
    Return operator()() const
    {
        return m_functor();
    }

    /** Invokes the wrapped functor passing on the arguments.
     * \param arg1 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template < typename T_arg1 >
    typename ReturnTypeDeduce< T_arg1 >::Type operator()(T_arg1 arg1) const
    {
        return m_functor(arg1);
    }

    /** Invokes the wrapped functor passing on the arguments.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template < typename T_arg1, typename T_arg2 >
    typename ReturnTypeDeduce< T_arg1, T_arg2 >::Type operator()(T_arg1 arg1, T_arg2 arg2) const
    {
        return m_functor(arg1, arg2);
    }

    /** Invokes the wrapped functor passing on the arguments.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \param arg3 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template < typename T_arg1, typename T_arg2, typename T_arg3 >
    typename ReturnTypeDeduce< T_arg1, T_arg2, T_arg3 >::Type operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) const
    {
        return m_functor(arg1, arg2, arg3);
    }

    /** Invokes the wrapped functor passing on the arguments.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \param arg3 Argument to be passed on to the functor.
     * \param arg4 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template < typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
    typename ReturnTypeDeduce< T_arg1, T_arg2, T_arg3, T_arg4 >::Type operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) const
    {
        return m_functor(arg1, arg2, arg3, arg4);
    }

    /** Invokes the wrapped functor passing on the arguments.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \param arg3 Argument to be passed on to the functor.
     * \param arg4 Argument to be passed on to the functor.
     * \param arg5 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template < typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
    typename ReturnTypeDeduce< T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >::Type operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) const
    {
        return m_functor(arg1, arg2, arg3, arg4, arg5);
    }

    /** Invokes the wrapped functor passing on the arguments.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \param arg3 Argument to be passed on to the functor.
     * \param arg4 Argument to be passed on to the functor.
     * \param arg5 Argument to be passed on to the functor.
     * \param arg6 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template < typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
    typename ReturnTypeDeduce< T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) const
    {
        return m_functor(arg1, arg2, arg3, arg4, arg5, arg6);
    }

    /** Invokes the wrapped functor passing on the arguments.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \param arg3 Argument to be passed on to the functor.
     * \param arg4 Argument to be passed on to the functor.
     * \param arg5 Argument to be passed on to the functor.
     * \param arg6 Argument to be passed on to the functor.
     * \param arg7 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    template < typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7 >
    typename ReturnTypeDeduce< T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7) const
    {
        return m_functor(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    // Constructs an invalid functor.
    QEXTAdaptorFunctor() {}
    /** Constructs an adaptor_functor object that wraps the passed functor.
     * \param functor Functor to invoke from operator()().
     */
    explicit QEXTAdaptorFunctor(const T_functor &functor) : m_functor(functor) {}
    template < typename T_type >
    /** Constructs an adaptor_functor object that wraps the passed (member)
     * function pointer.
     * \param type Pointer to function or class method to invoke from operator()().
     */
    explicit QEXTAdaptorFunctor(const T_type &type) : m_functor(type)
    {
    }

    /// Functor that is invoked from operator()().
    mutable T_functor m_functor;
};

/** Performs a functor on each of the targets of a functor.
 * The function overload for QEXTAdaptorFunctor performs a functor
 * on the functor stored in the QEXTAdaptorFunctor object.
 *
 * \ingroup QEXTAdapts
 */
template < typename T_functor >
struct QEXTVisitor< QEXTAdaptorFunctor< T_functor > >
{
    template < typename T_action >
    static void doVisitEach(const T_action &action, const QEXTAdaptorFunctor< T_functor > &target)
    {
        qextVisitEach(action, target.m_functor);
    }
};

/** Trait that specifies what is the adaptor version of a functor type.
 * Template specializations for QEXTAdaptorBase derived functors,
 * for function pointers and for class methods are provided.
 *
 * The template argument @e T_functor is the functor type to convert.
 * @e I_isadaptor indicates whether @e T_functor inherits from QEXTAdaptorBase.
 *
 * \ingroup QEXTAdapts
 */
template < typename T_functor, bool I_isadaptor = QEXTIsBaseOf< QEXTAdaptorBase, T_functor >::value >
struct QEXTAdaptorTrait;

/** Trait that specifies what is the adaptor version of a functor type.
 * This template specialization is used for types that inherit from adaptor_base.
 * Adaptor is equal to @p T_functor in this case.
 */
template < typename T_functor >
struct QEXTAdaptorTrait< T_functor, true >
{
    typedef typename T_functor::Return Return;
    typedef T_functor Functor;
    typedef T_functor Adaptor;
};

/** Trait that specifies what is the adaptor version of a functor type.
 * This template specialization is used for arbitrary functors,
 * for function pointers and for class methods are provided.
 * The latter are converted into @p QEXTPointerFunctor or @p QEXTMemberFunctor types.
 * Adaptor is equal to @p AdaptorFunctor<Functor>.
 */
template < typename T_functor >
struct QEXTAdaptorTrait< T_functor, false >
{
    typedef typename QEXTFunctorTrait< T_functor >::Return Return;
    typedef typename QEXTFunctorTrait< T_functor >::Functor Functor;
    typedef QEXTAdaptorFunctor< Functor > Adaptor;
};

/** Base type for adaptors.
 * QEXTAdapts wraps adaptors, functors, function pointers and class methods.
 * It contains a single member functor which is always a QEXTAdaptorBase.
 * The typedef Adaptor defines the exact type that is used
 * to store the adaptor, functor, function pointer or class method passed
 * into the constructor. It differs from @a T_functor unless @a T_functor
 * inherits from QEXTAdaptorBase.
 *
 * @par Example of a simple adaptor:
 * @code
 * namespace my_ns
 * {
 * template <typename T_functor>
 * struct my_adaptor : public QEXTAdapts<T_functor>
 * {
 *   template <typename T_arg1 = void, typename T_arg2 = void>
 *   struct ReturnTypeDeduce
 *   { typedef typename QEXTReturnTypeDeduce<T_functor, T_arg1, T_arg2>::Type Type; };
 *   typedef typename QEXTFunctorTrait<T_functor>::Return   Return;
 *   //
 *   result_type
 *   operator()() const;
 *   //
 *   template <typename T_arg1>
 *   typename ReturnTypeDeduce<T_arg1>::Type
 *   operator()(T_arg1 arg1) const;
 *   //
 *   template <typename T_arg1, class T_arg2>
 *   typename ReturnTypeDeduce<T_arg1, T_arg2>::Type
 *   operator()(T_arg1 arg1, T_arg2 arg2) const;
 *   //
 *   // Constructs a my_adaptor object that wraps the passed functor.
 *   // Initializes QEXTAdapts<T_functor>::m_functor, which is invoked from operator()().
 *   explicit my_adaptor(const T_functor &functor)
 *     : QEXTAdapts<T_functor>(functor) {}
 * };
 * } // end namespace my_ns
 * //
 * // Specialization of QEXTVisitor for my_adaptor.
 *
 * template <typename T_functor>
 * struct QEXTVisitor<my_ns::my_adaptor<T_functor> >
 * {
 *   template <typename T_action>
 *   static void doVisitEach(const T_action &action,
 *                             const my_ns::my_adaptor<T_functor> &target)
 *   {
 *     qextVisitEach(action, target.m_functor);
 *   }
 * };
 * @endcode
 *
 * If you implement your own adaptor, you must also provide your specialization
 * of QEXTVisitor<>::doVisitEach<>() that will forward the call to the functor(s)
 * your adapter is wrapping. Otherwise, pointers stored within the functor won't be
 * invalidated when a QObject object is destroyed and you can end up
 * executing callbacks on destroyed objects.
 *
 *
 * \ingroup QEXTAdapts
 */
template < typename T_functor >
struct QEXTAdapts : public QEXTAdaptorBase
{
    typedef typename QEXTAdaptorTrait< T_functor >::Return Return;
    typedef typename QEXTAdaptorTrait< T_functor >::Adaptor Adaptor;

    /** Constructs an adaptor that wraps the passed functor.
     * \param functor Functor to invoke from operator()().
     */
    explicit QEXTAdapts(const T_functor &functor) : m_functor(functor) {}

    // Adaptor that is invoked from operator()().
    mutable Adaptor m_functor;
};

#endif // _QEXTADAPTORTRAIT_H
