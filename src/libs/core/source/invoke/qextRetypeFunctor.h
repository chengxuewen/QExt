/*************************************************************************************
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
*************************************************************************************/

#ifndef _QEXTRETYPEFUNCTOR_H
#define _QEXTRETYPEFUNCTOR_H

#include <qextAdaptorTrait.h>
#include <qextRetypeReturnFunctor.h>
#include <qextMemberFunctor.h>
#include <qextPointerFunctor.h>
#include <qextFunction.h>


/** @defgroup retype qextRetypeFunctor(), qextRetypeReturnFunctor()
 * qextRetypeFunctor() alters a QExtPointerFunctor, a QExtMemberFunctor or a QExtFunction
 * in that it makes C-style casts to the functor's parameter types
 * of all parameters passed through operator()().
 *
 * Use this adaptor for inline conversion between numeric or other simple types.
 * @par Example:
 * @code
 * void foo(int);
 * qextRetypeFunctor(qextPointerFunctor(&foo))(5.7F); // calls foo(5)
 * @endcode
 *
 * The functor that qextRetypeFunctor() returns can be passed directly into
 * QExtSignal::connect().
 *
 * @par Example:
 * @code
 * QExtSignal<void,float> some_signal;
 * void foo(int);
 * some_signal.connect(qextRetypeFunctor(qextPointerFunctor(&foo)));
 * @endcode
 *
 * This adaptor builds an exception in that it only works on QExtPointerFunctor,
 * qextMemberFunctor and QExtFunction because it needs sophisticated information about
 * the parameter types that cannot be deduced from arbitrary functor types.
 *
 * qextRetypeReturnFunctor() alters the return type of an arbitrary functor.
 * Like in qextRetypeFunctor() a C-style cast is performed. Usage qextRetypeReturnFunctor() is
 * not restricted to QExt functor types but you need to
 * specify the new return type as a template parameter.
 *
 * @par Example:
 * @code
 * float foo();
 * std::cout << qextRetypeReturnFunctor<int>(&foo)(); // converts foo's return value to an integer
 * @endcode
 *
 * \ingroup adaptors
 */


/** Adaptor that performs C-style casts on the parameters passed on to the functor.
 * Use the convenience function qextRetypeFunctor() to create an instance of retype_functor.
 *
 * The following template arguments are used:
 * - @e T_functor Type of the functor to wrap.
 * - @e T_type1 Type of @e T_functor's 1th argument.
 * - @e T_type2 Type of @e T_functor's 2th argument.
 * - @e T_type3 Type of @e T_functor's 3th argument.
 * - @e T_type4 Type of @e T_functor's 4th argument.
 * - @e T_type5 Type of @e T_functor's 5th argument.
 * - @e T_type6 Type of @e T_functor's 6th argument.
 * - @e T_type7 Type of @e T_functor's 7th argument.
 *
 * \ingroup retype
 */
template <typename T_functor,
          typename T_type1 = QExtNil, typename T_type2 = QExtNil, typename T_type3 = QExtNil,
          typename T_type4 = QExtNil, typename T_type5 = QExtNil, typename T_type6 = QExtNil, typename T_type7 = QExtNil>
struct QExtRetypeFunctor : public QExtAdapts<T_functor>
{
    typedef typename QExtAdapts<T_functor>::Adaptor Adaptor;

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
            typename QExtTypeTrait<T_arg7>::Pass >::Type Type;
    };

    typedef typename QExtAdapts<T_functor>::Return   Return;

    Return operator()()
    {
        return this->m_functor();
    }

    template <typename T_arg1>
    typename ReturnTypeDeduce<T_arg1>::Type
    operator()(T_arg1 arg1)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<T_type1>::Take >
               (static_cast<T_type1>(arg1));
    }


    template <typename T_arg1, typename T_arg2>
    typename ReturnTypeDeduce<T_arg1, T_arg2>::Type
    operator()(T_arg1 arg1, T_arg2 arg2)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<T_type1>::Take,
               typename QExtTypeTrait<T_type2>::Take >
               (static_cast<T_type1>(arg1), static_cast<T_type2>(arg2));
    }



    template <typename T_arg1, typename T_arg2, typename T_arg3>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<T_type1>::Take,
               typename QExtTypeTrait<T_type2>::Take,
               typename QExtTypeTrait<T_type3>::Take >
               (static_cast<T_type1>(arg1), static_cast<T_type2>(arg2), static_cast<T_type3>(arg3));
    }



    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<T_type1>::Take,
               typename QExtTypeTrait<T_type2>::Take,
               typename QExtTypeTrait<T_type3>::Take,
               typename QExtTypeTrait<T_type4>::Take >
               (static_cast<T_type1>(arg1), static_cast<T_type2>(arg2), static_cast<T_type3>(arg3), static_cast<T_type4>(arg4));
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<T_type1>::Take,
               typename QExtTypeTrait<T_type2>::Take,
               typename QExtTypeTrait<T_type3>::Take,
               typename QExtTypeTrait<T_type4>::Take,
               typename QExtTypeTrait<T_type5>::Take >
               (static_cast<T_type1>(arg1), static_cast<T_type2>(arg2), static_cast<T_type3>(arg3),
                static_cast<T_type4>(arg4), static_cast<T_type5>(arg5));
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<T_type1>::Take,
               typename QExtTypeTrait<T_type2>::Take,
               typename QExtTypeTrait<T_type3>::Take,
               typename QExtTypeTrait<T_type4>::Take,
               typename QExtTypeTrait<T_type5>::Take,
               typename QExtTypeTrait<T_type6>::Take >
               (static_cast<T_type1>(arg1), static_cast<T_type2>(arg2), static_cast<T_type3>(arg3),
                static_cast<T_type4>(arg4), static_cast<T_type5>(arg5), static_cast<T_type6>(arg6));
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7)
    {
        return this->m_functor.template operator () <
               typename QExtTypeTrait<T_type1>::Take,
               typename QExtTypeTrait<T_type2>::Take,
               typename QExtTypeTrait<T_type3>::Take,
               typename QExtTypeTrait<T_type4>::Take,
               typename QExtTypeTrait<T_type5>::Take,
               typename QExtTypeTrait<T_type6>::Take,
               typename QExtTypeTrait<T_type7>::Take >
               (static_cast<T_type1>(arg1), static_cast<T_type2>(arg2), static_cast<T_type3>(arg3),
                static_cast<T_type4>(arg4), static_cast<T_type5>(arg5), static_cast<T_type6>(arg6), static_cast<T_type7>(arg7));
    }


    /** Constructs a retype_functor object that performs C-style casts on the parameters passed on to the functor.
     * \param functor Functor to invoke from operator()().
     */
    explicit QExtRetypeFunctor(typename QExtTypeTrait<T_functor>::Take functor)
        : QExtAdapts<T_functor>(functor) {}
};


//template specialization of visitor<>::do_visit_each<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for qextRetypeFunctor performs a functor on the
 * functor stored in the qextRetypeFunctor object.
 *
 * \ingroup retype
 */
template <typename T_functor,
          typename T_type1, typename T_type2, typename T_type3,
          typename T_type4, typename T_type5, typename T_type6, typename T_type7>
struct QExtVisitor<QExtRetypeFunctor<T_functor, T_type1, T_type2, T_type3, T_type4, T_type5, T_type6, T_type7> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QExtRetypeFunctor<T_functor, T_type1, T_type2, T_type3, T_type4, T_type5, T_type6, T_type7> &target)
    {
        qextVisitEach(action, target.m_functor);
    }
};

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtFunction.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QExtRetypeFunctor<QExtFunction<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
qextRetypeFunctor(const QExtFunction<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> &functor)
{
    return QExtRetypeFunctor<QExtFunction<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on qextPointerFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return>
inline QExtRetypeFunctor<QExtPointerFunctor<T_return> >
qextRetypeFunctor(const QExtPointerFunctor<T_return> &functor)
{
    return QExtRetypeFunctor<QExtPointerFunctor<T_return> >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on qextPointerFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_arg1>
inline QExtRetypeFunctor<QExtPointerFunctor<T_return, T_arg1>, T_arg1 >
qextRetypeFunctor(const QExtPointerFunctor<T_return, T_arg1> &functor)
{
    return QExtRetypeFunctor<QExtPointerFunctor<T_return, T_arg1>, T_arg1 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on qextPointerFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_arg1, typename T_arg2>
inline QExtRetypeFunctor<QExtPointerFunctor<T_return, T_arg1, T_arg2>, T_arg1, T_arg2 >
qextRetypeFunctor(const QExtPointerFunctor<T_return, T_arg1, T_arg2> &functor)
{
    return QExtRetypeFunctor<QExtPointerFunctor<T_return, T_arg1, T_arg2>, T_arg1, T_arg2 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on qextPointerFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3>
inline QExtRetypeFunctor<QExtPointerFunctor<T_return, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >
qextRetypeFunctor(const QExtPointerFunctor<T_return, T_arg1, T_arg2, T_arg3> &functor)
{
    return QExtRetypeFunctor<QExtPointerFunctor<T_return, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on qextPointerFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QExtRetypeFunctor<QExtPointerFunctor<T_return, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >
qextRetypeFunctor(const QExtPointerFunctor<T_return, T_arg1, T_arg2, T_arg3, T_arg4> &functor)
{
    return QExtRetypeFunctor<QExtPointerFunctor<T_return, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on qextPointerFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QExtRetypeFunctor<QExtPointerFunctor<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
qextRetypeFunctor(const QExtPointerFunctor<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> &functor)
{
    return QExtRetypeFunctor<QExtPointerFunctor<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on qextPointerFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
inline QExtRetypeFunctor<QExtPointerFunctor<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
qextRetypeFunctor(const QExtPointerFunctor<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> &functor)
{
    return QExtRetypeFunctor<QExtPointerFunctor<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on qextPointerFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QExtRetypeFunctor<QExtPointerFunctor<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
qextRetypeFunctor(const QExtPointerFunctor<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> &functor)
{
    return QExtRetypeFunctor<QExtPointerFunctor<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on qextMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj>
inline QExtRetypeFunctor<QExtMemberFunctor<T_return, T_obj> >
qextRetypeFunctor(const QExtMemberFunctor<T_return, T_obj> &functor)
{
    return QExtRetypeFunctor<QExtMemberFunctor<T_return, T_obj> >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on qextMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1>
inline QExtRetypeFunctor<QExtMemberFunctor<T_return, T_obj, T_arg1>, T_arg1 >
qextRetypeFunctor(const QExtMemberFunctor<T_return, T_obj, T_arg1> &functor)
{
    return QExtRetypeFunctor<QExtMemberFunctor<T_return, T_obj, T_arg1>, T_arg1 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on qextMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QExtRetypeFunctor<QExtMemberFunctor<T_return, T_obj, T_arg1, T_arg2>, T_arg1, T_arg2 >
qextRetypeFunctor(const QExtMemberFunctor<T_return, T_obj, T_arg1, T_arg2> &functor)
{
    return QExtRetypeFunctor<QExtMemberFunctor<T_return, T_obj, T_arg1, T_arg2>, T_arg1, T_arg2 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on qextMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
inline QExtRetypeFunctor<QExtMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >
qextRetypeFunctor(const QExtMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3> &functor)
{
    return QExtRetypeFunctor<QExtMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on qextMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QExtRetypeFunctor<QExtMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >
qextRetypeFunctor(const QExtMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> &functor)
{
    return QExtRetypeFunctor<QExtMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on qextMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QExtRetypeFunctor<QExtMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
qextRetypeFunctor(const QExtMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> &functor)
{
    return QExtRetypeFunctor<QExtMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on qextMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
inline QExtRetypeFunctor<QExtMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
qextRetypeFunctor(const QExtMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> &functor)
{
    return QExtRetypeFunctor<QExtMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on qextMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QExtRetypeFunctor<QExtMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
qextRetypeFunctor(const QExtMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> &functor)
{
    return QExtRetypeFunctor<QExtMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtConstMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj>
inline QExtRetypeFunctor<QExtConstMemberFunctor<T_return, T_obj> >
qextRetypeFunctor(const QExtConstMemberFunctor<T_return, T_obj> &functor)
{
    return QExtRetypeFunctor<QExtConstMemberFunctor<T_return, T_obj> >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtConstMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1>
inline QExtRetypeFunctor<QExtConstMemberFunctor<T_return, T_obj, T_arg1>, T_arg1 >
qextRetypeFunctor(const QExtConstMemberFunctor<T_return, T_obj, T_arg1> &functor)
{
    return QExtRetypeFunctor<QExtConstMemberFunctor<T_return, T_obj, T_arg1>, T_arg1 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtConstMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QExtRetypeFunctor<QExtConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2>, T_arg1, T_arg2 >
qextRetypeFunctor(const QExtConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2> &functor)
{
    return QExtRetypeFunctor<QExtConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2>, T_arg1, T_arg2 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtConstMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
inline QExtRetypeFunctor<QExtConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >
qextRetypeFunctor(const QExtConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3> &functor)
{
    return QExtRetypeFunctor<QExtConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtConstMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QExtRetypeFunctor<QExtConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >
qextRetypeFunctor(const QExtConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> &functor)
{
    return QExtRetypeFunctor<QExtConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtConstMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QExtRetypeFunctor<QExtConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
qextRetypeFunctor(const QExtConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> &functor)
{
    return QExtRetypeFunctor<QExtConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtConstMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
inline QExtRetypeFunctor<QExtConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
qextRetypeFunctor(const QExtConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> &functor)
{
    return QExtRetypeFunctor<QExtConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtConstMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QExtRetypeFunctor<QExtConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
qextRetypeFunctor(const QExtConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> &functor)
{
    return QExtRetypeFunctor<QExtConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtVolatileMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj>
inline QExtRetypeFunctor<QExtVolatileMemberFunctor<T_return, T_obj> >
qextRetypeFunctor(const QExtVolatileMemberFunctor<T_return, T_obj> &functor)
{
    return QExtRetypeFunctor<QExtVolatileMemberFunctor<T_return, T_obj> >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtVolatileMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1>
inline QExtRetypeFunctor<QExtVolatileMemberFunctor<T_return, T_obj, T_arg1>, T_arg1 >
qextRetypeFunctor(const QExtVolatileMemberFunctor<T_return, T_obj, T_arg1> &functor)
{
    return QExtRetypeFunctor<QExtVolatileMemberFunctor<T_return, T_obj, T_arg1>, T_arg1 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtVolatileMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QExtRetypeFunctor<QExtVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>, T_arg1, T_arg2 >
qextRetypeFunctor(const QExtVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2> &functor)
{
    return QExtRetypeFunctor<QExtVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>, T_arg1, T_arg2 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtVolatileMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
inline QExtRetypeFunctor<QExtVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >
qextRetypeFunctor(const QExtVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3> &functor)
{
    return QExtRetypeFunctor<QExtVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtVolatileMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QExtRetypeFunctor<QExtVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >
qextRetypeFunctor(const QExtVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> &functor)
{
    return QExtRetypeFunctor<QExtVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtVolatileMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QExtRetypeFunctor<QExtVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
qextRetypeFunctor(const QExtVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> &functor)
{
    return QExtRetypeFunctor<QExtVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtVolatileMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
inline QExtRetypeFunctor<QExtVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
qextRetypeFunctor(const QExtVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> &functor)
{
    return QExtRetypeFunctor<QExtVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtVolatileMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QExtRetypeFunctor<QExtVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
qextRetypeFunctor(const QExtVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> &functor)
{
    return QExtRetypeFunctor<QExtVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtConstVolatileMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj>
inline QExtRetypeFunctor<QExtConstVolatileMemberFunctor<T_return, T_obj> >
qextRetypeFunctor(const QExtConstVolatileMemberFunctor<T_return, T_obj> &functor)
{
    return QExtRetypeFunctor<QExtConstVolatileMemberFunctor<T_return, T_obj> >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtConstVolatileMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1>
inline QExtRetypeFunctor<QExtConstVolatileMemberFunctor<T_return, T_obj, T_arg1>, T_arg1 >
qextRetypeFunctor(const QExtConstVolatileMemberFunctor<T_return, T_obj, T_arg1> &functor)
{
    return QExtRetypeFunctor<QExtConstVolatileMemberFunctor<T_return, T_obj, T_arg1>, T_arg1 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtConstVolatileMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QExtRetypeFunctor<QExtConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>, T_arg1, T_arg2 >
qextRetypeFunctor(const QExtConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2> &functor)
{
    return QExtRetypeFunctor<QExtConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>, T_arg1, T_arg2 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtConstVolatileMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
inline QExtRetypeFunctor<QExtConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >
qextRetypeFunctor(const QExtConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3> &functor)
{
    return QExtRetypeFunctor<QExtConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtConstVolatileMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QExtRetypeFunctor<QExtConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >
qextRetypeFunctor(const QExtConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> &functor)
{
    return QExtRetypeFunctor<QExtConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtConstVolatileMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QExtRetypeFunctor<QExtConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
qextRetypeFunctor(const QExtConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> &functor)
{
    return QExtRetypeFunctor<QExtConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtConstVolatileMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
inline QExtRetypeFunctor<QExtConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
qextRetypeFunctor(const QExtConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> &functor)
{
    return QExtRetypeFunctor<QExtConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtConstVolatileMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QExtRetypeFunctor<QExtConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
qextRetypeFunctor(const QExtConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> &functor)
{
    return QExtRetypeFunctor<QExtConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtBoundMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj>
inline QExtRetypeFunctor<QExtBoundMemberFunctor<T_return, T_obj> >
qextRetypeFunctor(const QExtBoundMemberFunctor<T_return, T_obj> &functor)
{
    return QExtRetypeFunctor<QExtBoundMemberFunctor<T_return, T_obj> >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtBoundMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1>
inline QExtRetypeFunctor<QExtBoundMemberFunctor<T_return, T_obj, T_arg1>, T_arg1 >
qextRetypeFunctor(const QExtBoundMemberFunctor<T_return, T_obj, T_arg1> &functor)
{
    return QExtRetypeFunctor<QExtBoundMemberFunctor<T_return, T_obj, T_arg1>, T_arg1 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtBoundMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QExtRetypeFunctor<QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2>, T_arg1, T_arg2 >
qextRetypeFunctor(const QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2> &functor)
{
    return QExtRetypeFunctor<QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2>, T_arg1, T_arg2 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtBoundMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
inline QExtRetypeFunctor<QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >
qextRetypeFunctor(const QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3> &functor)
{
    return QExtRetypeFunctor<QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtBoundMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QExtRetypeFunctor<QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >
qextRetypeFunctor(const QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> &functor)
{
    return QExtRetypeFunctor<QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtBoundMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QExtRetypeFunctor<QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
qextRetypeFunctor(const QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> &functor)
{
    return QExtRetypeFunctor<QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtBoundMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
inline QExtRetypeFunctor<QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
qextRetypeFunctor(const QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> &functor)
{
    return QExtRetypeFunctor<QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtBoundMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QExtRetypeFunctor<QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
qextRetypeFunctor(const QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> &functor)
{
    return QExtRetypeFunctor<QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtBoundConstMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj>
inline QExtRetypeFunctor<QExtBoundConstMemberFunctor<T_return, T_obj> >
qextRetypeFunctor(const QExtBoundConstMemberFunctor<T_return, T_obj> &functor)
{
    return QExtRetypeFunctor<QExtBoundConstMemberFunctor<T_return, T_obj> >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtBoundConstMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1>
inline QExtRetypeFunctor<QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1>, T_arg1 >
qextRetypeFunctor(const QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1> &functor)
{
    return QExtRetypeFunctor<QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1>, T_arg1 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtBoundConstMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QExtRetypeFunctor<QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2>, T_arg1, T_arg2 >
qextRetypeFunctor(const QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2> &functor)
{
    return QExtRetypeFunctor<QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2>, T_arg1, T_arg2 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtBoundConstMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
inline QExtRetypeFunctor<QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >
qextRetypeFunctor(const QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3> &functor)
{
    return QExtRetypeFunctor<QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtBoundConstMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QExtRetypeFunctor<QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >
qextRetypeFunctor(const QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> &functor)
{
    return QExtRetypeFunctor<QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtBoundConstMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QExtRetypeFunctor<QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
qextRetypeFunctor(const QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> &functor)
{
    return QExtRetypeFunctor<QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtBoundConstMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
inline QExtRetypeFunctor<QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
qextRetypeFunctor(const QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> &functor)
{
    return QExtRetypeFunctor<QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtBoundConstMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QExtRetypeFunctor<QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
qextRetypeFunctor(const QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> &functor)
{
    return QExtRetypeFunctor<QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtBoundVolatileMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj>
inline QExtRetypeFunctor<QExtBoundVolatileMemberFunctor<T_return, T_obj> >
qextRetypeFunctor(const QExtBoundVolatileMemberFunctor<T_return, T_obj> &functor)
{
    return QExtRetypeFunctor<QExtBoundVolatileMemberFunctor<T_return, T_obj> >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtBoundVolatileMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1>
inline QExtRetypeFunctor<QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1>, T_arg1 >
qextRetypeFunctor(const QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1> &functor)
{
    return QExtRetypeFunctor<QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1>, T_arg1 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtBoundVolatileMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QExtRetypeFunctor<QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>, T_arg1, T_arg2 >
qextRetypeFunctor(const QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2> &functor)
{
    return QExtRetypeFunctor<QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>, T_arg1, T_arg2 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtBoundVolatileMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
inline QExtRetypeFunctor<QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >
qextRetypeFunctor(const QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3> &functor)
{
    return QExtRetypeFunctor<QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtBoundVolatileMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QExtRetypeFunctor<QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >
qextRetypeFunctor(const QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> &functor)
{
    return QExtRetypeFunctor<QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtBoundVolatileMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QExtRetypeFunctor<QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
qextRetypeFunctor(const QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> &functor)
{
    return QExtRetypeFunctor<QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtBoundVolatileMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
inline QExtRetypeFunctor<QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
qextRetypeFunctor(const QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> &functor)
{
    return QExtRetypeFunctor<QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtBoundVolatileMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QExtRetypeFunctor<QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
qextRetypeFunctor(const QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> &functor)
{
    return QExtRetypeFunctor<QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtBoundConstVolatileMemberFunctor7.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj>
inline QExtRetypeFunctor<QExtBoundConstVolatileMemberFunctor<T_return, T_obj> >
qextRetypeFunctor(const QExtBoundConstVolatileMemberFunctor<T_return, T_obj> &functor)
{
    return QExtRetypeFunctor<QExtBoundConstVolatileMemberFunctor<T_return, T_obj> >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtBoundConstVolatileMemberFunctor7.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1>
inline QExtRetypeFunctor<QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1>, T_arg1 >
qextRetypeFunctor(const QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1> &functor)
{
    return QExtRetypeFunctor<QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1>, T_arg1 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtBoundConstVolatileMemberFunctor7.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QExtRetypeFunctor<QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>, T_arg1, T_arg2 >
qextRetypeFunctor(const QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2> &functor)
{
    return QExtRetypeFunctor<QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>, T_arg1, T_arg2 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtBoundConstVolatileMemberFunctor7.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
inline QExtRetypeFunctor<QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >
qextRetypeFunctor(const QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3> &functor)
{
    return QExtRetypeFunctor<QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtBoundConstVolatileMemberFunctor7.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QExtRetypeFunctor<QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >
qextRetypeFunctor(const QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> &functor)
{
    return QExtRetypeFunctor<QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtBoundConstVolatileMemberFunctor7.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QExtRetypeFunctor<QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
qextRetypeFunctor(const QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> &functor)
{
    return QExtRetypeFunctor<QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtBoundConstVolatileMemberFunctor7.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
inline QExtRetypeFunctor<QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
qextRetypeFunctor(const QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> &functor)
{
    return QExtRetypeFunctor<QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QExtBoundConstVolatileMemberFunctor7.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QExtRetypeFunctor<QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
qextRetypeFunctor(const QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> &functor)
{
    return QExtRetypeFunctor<QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(functor);
}



#endif // _QEXTRETYPEFUNCTOR_H
