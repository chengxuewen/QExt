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

#ifndef _QEXTADAPTORTRAIT_H
#define _QEXTADAPTORTRAIT_H

#include <qextReturnTypeDeduce.h>
#include <qextFunctorTrait.h>
#include <qextVisitor.h>

template < class Functor >
struct QExtAdapts;

/**
 * @defgroup adaptors Adaptors
 * Adaptors are functors that alter the signature of a functor's
 * operator()().
 *
 * The adaptor types are created with qextBindFunctor(), qextBindReturnFunctor(), qextMakeHideFunctor(), qextHideReturnFunctor(),
 * qextRetypeReturnFunctor(), qextRetypeFunctor(), qextComposeFunctor(), qextTrackObjectFunctor()
 * and qextLambdaGroup().
 *
 * You can easily derive your own adaptor type from QExtAdapts.
 */

/**
 * @brief Converts an arbitrary functor into an adaptor type.
 * All adaptor types have
 * a <tt>template operator()</tt> member of every argument count they support.
 * These functions in turn invoke a stored adaptor's
 * <tt>template operator()</tt>, processing the arguments and return value in a characteristic manner.
 * Explicit function template instantiation is used to pass type hints thus saving copy costs.
 *
 * QExtAdaptorFunctor is a glue between adaptors and arbitrary functors that just passes on the arguments.
 * You won't use this type directly.
 *
 * The template argument @e Functor determines the type of stored functor.
 */
template < class Functor >
struct QExtAdaptorFunctor : public QExtAdaptorBase
{
    typedef typename QExtFunctorTrait< Functor >::ResultType ResultType;

    template<class Arg1 = void,
             class Arg2 = void,
             class Arg3 = void,
             class Arg4 = void,
             class Arg5 = void,
             class Arg6 = void,
             class Arg7 = void >
    struct ReturnTypeDeduce
    {
        typedef typename QExtReturnTypeDeduce< Functor, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7 >::Type Type;
    };

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * @return The return value of the functor invocation.
     */
    ResultType operator()() const
    {
        return mFunctor();
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * @param arg1 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template < class Arg1 >
    typename ReturnTypeDeduce< Arg1 >::Type
    operator()(Arg1 arg1) const
    {
        return mFunctor(arg1);
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template < class Arg1, class Arg2 >
    typename ReturnTypeDeduce< Arg1, Arg2 >::Type
    operator()(Arg1 arg1, Arg2 arg2) const
    {
        return mFunctor(arg1, arg2);
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template < class Arg1, class Arg2, class Arg3 >
    typename ReturnTypeDeduce< Arg1, Arg2, Arg3 >::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3) const
    {
        return mFunctor(arg1, arg2, arg3);
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template < class Arg1, class Arg2, class Arg3, class Arg4 >
    typename ReturnTypeDeduce< Arg1, Arg2, Arg3, Arg4 >::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4) const
    {
        return mFunctor(arg1, arg2, arg3, arg4);
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template < class Arg1, class Arg2, class Arg3, class Arg4, class Arg5 >
    typename ReturnTypeDeduce< Arg1, Arg2, Arg3, Arg4, Arg5 >::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5) const
    {
        return mFunctor(arg1, arg2, arg3, arg4, arg5);
    }

    /**
     * @brief Invokes the wrapped functor passing on the arguments.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @param arg6 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template < class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6 >
    typename ReturnTypeDeduce< Arg1, Arg2, Arg3, Arg4, Arg5, Arg6 >::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6) const
    {
        return mFunctor(arg1, arg2, arg3, arg4, arg5, arg6);
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
     * @return The return value of the functor invocation.
     */
    template < class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7 >
    typename ReturnTypeDeduce< Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7 >::Type
    operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6, Arg7 arg7) const
    {
        return mFunctor(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    /**
     * @brief Constructs an invalid functor.
     */
    QExtAdaptorFunctor() {}

    /**
     * @brief Constructs an adaptor_functor object that wraps the passed functor.
     * @param functor Functor to invoke from operator()().
     */
    explicit QExtAdaptorFunctor(const Functor &functor) : mFunctor(functor) {}

    template < class XType >
    /**
     * @brief Constructs an adaptor_functor object that wraps the passed (member) function pointer.
     * @param type Pointer to function or class method to invoke from operator()().
     */
    explicit QExtAdaptorFunctor(const XType &type) : mFunctor(type)
    {
    }

    /// Functor that is invoked from operator()().
    mutable Functor mFunctor;
};

/**
 * @brief Performs a functor on each of the targets of a functor.
 * The function overload for QExtAdaptorFunctor performs a functor on the functor stored in the
 * QExtAdaptorFunctor object.
 */
template < class Functor >
struct QExtVisitor< QExtAdaptorFunctor< Functor > >
{
    template < class Action >
    static void doVisitEach(const Action &action, const QExtAdaptorFunctor< Functor > &target)
    {
        qextVisitEach(action, target.mFunctor);
    }
};

/**
 * @brief Trait that specifies what is the adaptor version of a functor type.
 * Template specializations for QExtAdaptorBase derived functors, for function pointers and for class methods
 * are provided.
 *
 * The template argument @e Functor is the functor type to convert.
 * @e I_isadaptor indicates whether @e Functor inherits from QExtAdaptorBase.
 */
template < class Functor, bool I_isadaptor = QExtIsBaseOf< QExtAdaptorBase, Functor >::value >
struct QExtAdaptorTrait;

/**
 * @brief Trait that specifies what is the adaptor version of a functor type.
 * This template specialization is used for types that inherit from adaptor_base.
 * AdaptorType is equal to @p Functor in this case.
 */
template < class Functor >
struct QExtAdaptorTrait< Functor, true >
{
    typedef typename Functor::ResultType ResultType;
    typedef Functor FunctorType;
    typedef Functor AdaptorType;
};

/**
 * @brief Trait that specifies what is the adaptor version of a functor type.
 * This template specialization is used for arbitrary functors, for function pointers and for class methods
 * are provided.
 * The latter are converted into @p QExtPointerFunctor or @p QExtMemberFunctor types.
 * AdaptorType is equal to @p AdaptorFunctor<Functor>.
 */
template < class Functor >
struct QExtAdaptorTrait< Functor, false >
{
    typedef typename QExtFunctorTrait< Functor >::ResultType ResultType;
    typedef typename QExtFunctorTrait< Functor >::FunctorType FunctorType;
    typedef QExtAdaptorFunctor< FunctorType > AdaptorType;
};

/**
 * @brief Base type for adaptors.
 * QExtAdapts wraps adaptors, functors, function pointers and class methods.
 * It contains a single member functor which is always a QExtAdaptorBase.
 * The typedef AdaptorType defines the exact type that is used to store the adaptor, functor, function pointer or
 * class method passed into the constructor.
 * It differs from @a Functor unless @a Functor inherits from QExtAdaptorBase.
 *
 * @par Example of a simple adaptor:
 * @code
 * namespace my_ns
 * {
 * template <typename Functor>
 * struct MYAdaptor : public QExtAdapts<Functor>
 * {
 *   template <class Arg1 = void, class Arg2 = void>
 *   struct ReturnTypeDeduce
 *   {
 *      typedef typename QExtReturnTypeDeduce<Functor, Arg1, Arg2>::Type Type;
 *   };
 *   typedef typename QExtFunctorTrait<Functor>::ResultType   ResultType;
 *
 *   ResultType operator()() const;
 *
 *   template <class Arg1>
 *   typename ReturnTypeDeduce<Arg1>::Type operator()(Arg1 arg1) const;
 *
 *   template <class Arg1, class Arg2>
 *   typename ReturnTypeDeduce<Arg1, Arg2>::Type operator()(Arg1 arg1, Arg2 arg2) const;
 *
 *   // Constructs a MYAdaptor object that wraps the passed functor.
 *   // Initializes QExtAdapts<Functor>::mFunctor, which is invoked from operator()().
 *   explicit MYAdaptor(const Functor &functor) : QExtAdapts<Functor>(functor) {}
 * };
 * } // end namespace my_ns
 *
 * // Specialization of QExtVisitor for MYAdaptor.
 * template <typename Functor>
 * struct QExtVisitor<my_ns::MYAdaptor<Functor> >
 * {
 *   template <typename Action>
 *   static void doVisitEach(const Action &action, const my_ns::MYAdaptor<Functor> &target)
 *   {
 *     qextVisitEach(action, target.mFunctor);
 *   }
 * };
 * @endcode
 *
 * If you implement your own adaptor, you must also provide your specialization of QExtVisitor<>::doVisitEach<>() that
 * will forward the call to the functor(s) your adapter is wrapping. Otherwise, pointers stored within the functor
 * won't be invalidated when a QObject object is destroyed and you can end up executing callbacks on destroyed objects.
 */
template < class Functor >
struct QExtAdapts : public QExtAdaptorBase
{
    typedef typename QExtAdaptorTrait< Functor >::ResultType ResultType;
    typedef typename QExtAdaptorTrait< Functor >::AdaptorType AdaptorType;

    /**
     * @brief Constructs an adaptor that wraps the passed functor.
     * @param functor FunctorType to invoke from operator()().
     */
    explicit QExtAdapts(const Functor &functor) : mFunctor(functor) {}

    mutable AdaptorType mFunctor; // AdaptorType that is invoked from operator()().
};

#endif // _QEXTADAPTORTRAIT_H
