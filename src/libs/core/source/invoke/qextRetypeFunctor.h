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
 * qextRetypeFunctor() alters a QEXTPointerFunctor, a QEXTMemberFunctor or a QEXTFunction
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
 * QEXTSignal::connect().
 *
 * @par Example:
 * @code
 * QEXTSignal<void,float> some_signal;
 * void foo(int);
 * some_signal.connect(qextRetypeFunctor(qextPointerFunctor(&foo)));
 * @endcode
 *
 * This adaptor builds an exception in that it only works on QEXTPointerFunctor,
 * qextMemberFunctor and QEXTFunction because it needs sophisticated information about
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
          typename T_type1 = QEXTNil, typename T_type2 = QEXTNil, typename T_type3 = QEXTNil,
          typename T_type4 = QEXTNil, typename T_type5 = QEXTNil, typename T_type6 = QEXTNil, typename T_type7 = QEXTNil>
struct QEXTRetypeFunctor : public QEXTAdapts<T_functor>
{
    typedef typename QEXTAdapts<T_functor>::Adaptor Adaptor;

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename Adaptor::template ReturnTypeDeduce <
            typename QEXTTypeTrait<T_arg1>::Pass,
            typename QEXTTypeTrait<T_arg2>::Pass,
            typename QEXTTypeTrait<T_arg3>::Pass,
            typename QEXTTypeTrait<T_arg4>::Pass,
            typename QEXTTypeTrait<T_arg5>::Pass,
            typename QEXTTypeTrait<T_arg6>::Pass,
            typename QEXTTypeTrait<T_arg7>::Pass >::Type Type;
    };

    typedef typename QEXTAdapts<T_functor>::Return   Return;

    Return operator()()
    {
        return this->m_functor();
    }

    template <typename T_arg1>
    typename ReturnTypeDeduce<T_arg1>::Type
    operator()(T_arg1 arg1)
    {
        return this->m_functor.template operator () <
               typename QEXTTypeTrait<T_type1>::Take >
               (static_cast<T_type1>(arg1));
    }


    template <typename T_arg1, typename T_arg2>
    typename ReturnTypeDeduce<T_arg1, T_arg2>::Type
    operator()(T_arg1 arg1, T_arg2 arg2)
    {
        return this->m_functor.template operator () <
               typename QEXTTypeTrait<T_type1>::Take,
               typename QEXTTypeTrait<T_type2>::Take >
               (static_cast<T_type1>(arg1), static_cast<T_type2>(arg2));
    }



    template <typename T_arg1, typename T_arg2, typename T_arg3>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3)
    {
        return this->m_functor.template operator () <
               typename QEXTTypeTrait<T_type1>::Take,
               typename QEXTTypeTrait<T_type2>::Take,
               typename QEXTTypeTrait<T_type3>::Take >
               (static_cast<T_type1>(arg1), static_cast<T_type2>(arg2), static_cast<T_type3>(arg3));
    }



    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4)
    {
        return this->m_functor.template operator () <
               typename QEXTTypeTrait<T_type1>::Take,
               typename QEXTTypeTrait<T_type2>::Take,
               typename QEXTTypeTrait<T_type3>::Take,
               typename QEXTTypeTrait<T_type4>::Take >
               (static_cast<T_type1>(arg1), static_cast<T_type2>(arg2), static_cast<T_type3>(arg3), static_cast<T_type4>(arg4));
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5)
    {
        return this->m_functor.template operator () <
               typename QEXTTypeTrait<T_type1>::Take,
               typename QEXTTypeTrait<T_type2>::Take,
               typename QEXTTypeTrait<T_type3>::Take,
               typename QEXTTypeTrait<T_type4>::Take,
               typename QEXTTypeTrait<T_type5>::Take >
               (static_cast<T_type1>(arg1), static_cast<T_type2>(arg2), static_cast<T_type3>(arg3),
                static_cast<T_type4>(arg4), static_cast<T_type5>(arg5));
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6)
    {
        return this->m_functor.template operator () <
               typename QEXTTypeTrait<T_type1>::Take,
               typename QEXTTypeTrait<T_type2>::Take,
               typename QEXTTypeTrait<T_type3>::Take,
               typename QEXTTypeTrait<T_type4>::Take,
               typename QEXTTypeTrait<T_type5>::Take,
               typename QEXTTypeTrait<T_type6>::Take >
               (static_cast<T_type1>(arg1), static_cast<T_type2>(arg2), static_cast<T_type3>(arg3),
                static_cast<T_type4>(arg4), static_cast<T_type5>(arg5), static_cast<T_type6>(arg6));
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7)
    {
        return this->m_functor.template operator () <
               typename QEXTTypeTrait<T_type1>::Take,
               typename QEXTTypeTrait<T_type2>::Take,
               typename QEXTTypeTrait<T_type3>::Take,
               typename QEXTTypeTrait<T_type4>::Take,
               typename QEXTTypeTrait<T_type5>::Take,
               typename QEXTTypeTrait<T_type6>::Take,
               typename QEXTTypeTrait<T_type7>::Take >
               (static_cast<T_type1>(arg1), static_cast<T_type2>(arg2), static_cast<T_type3>(arg3),
                static_cast<T_type4>(arg4), static_cast<T_type5>(arg5), static_cast<T_type6>(arg6), static_cast<T_type7>(arg7));
    }


    /** Constructs a retype_functor object that performs C-style casts on the parameters passed on to the functor.
     * \param functor Functor to invoke from operator()().
     */
    explicit QEXTRetypeFunctor(typename QEXTTypeTrait<T_functor>::Take functor)
        : QEXTAdapts<T_functor>(functor) {}
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
struct QEXTVisitor<QEXTRetypeFunctor<T_functor, T_type1, T_type2, T_type3, T_type4, T_type5, T_type6, T_type7> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTRetypeFunctor<T_functor, T_type1, T_type2, T_type3, T_type4, T_type5, T_type6, T_type7> &target)
    {
        qextVisitEach(action, target.m_functor);
    }
};

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTFunction.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTRetypeFunctor<QEXTFunction<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
qextRetypeFunctor(const QEXTFunction<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> &functor)
{
    return QEXTRetypeFunctor<QEXTFunction<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(functor);
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
inline QEXTRetypeFunctor<QEXTPointerFunctor<T_return> >
qextRetypeFunctor(const QEXTPointerFunctor<T_return> &functor)
{
    return QEXTRetypeFunctor<QEXTPointerFunctor<T_return> >(functor);
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
inline QEXTRetypeFunctor<QEXTPointerFunctor<T_return, T_arg1>, T_arg1 >
qextRetypeFunctor(const QEXTPointerFunctor<T_return, T_arg1> &functor)
{
    return QEXTRetypeFunctor<QEXTPointerFunctor<T_return, T_arg1>, T_arg1 >(functor);
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
inline QEXTRetypeFunctor<QEXTPointerFunctor<T_return, T_arg1, T_arg2>, T_arg1, T_arg2 >
qextRetypeFunctor(const QEXTPointerFunctor<T_return, T_arg1, T_arg2> &functor)
{
    return QEXTRetypeFunctor<QEXTPointerFunctor<T_return, T_arg1, T_arg2>, T_arg1, T_arg2 >(functor);
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
inline QEXTRetypeFunctor<QEXTPointerFunctor<T_return, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >
qextRetypeFunctor(const QEXTPointerFunctor<T_return, T_arg1, T_arg2, T_arg3> &functor)
{
    return QEXTRetypeFunctor<QEXTPointerFunctor<T_return, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >(functor);
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
inline QEXTRetypeFunctor<QEXTPointerFunctor<T_return, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >
qextRetypeFunctor(const QEXTPointerFunctor<T_return, T_arg1, T_arg2, T_arg3, T_arg4> &functor)
{
    return QEXTRetypeFunctor<QEXTPointerFunctor<T_return, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >(functor);
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
inline QEXTRetypeFunctor<QEXTPointerFunctor<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
qextRetypeFunctor(const QEXTPointerFunctor<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> &functor)
{
    return QEXTRetypeFunctor<QEXTPointerFunctor<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(functor);
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
inline QEXTRetypeFunctor<QEXTPointerFunctor<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
qextRetypeFunctor(const QEXTPointerFunctor<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> &functor)
{
    return QEXTRetypeFunctor<QEXTPointerFunctor<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(functor);
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
inline QEXTRetypeFunctor<QEXTPointerFunctor<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
qextRetypeFunctor(const QEXTPointerFunctor<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> &functor)
{
    return QEXTRetypeFunctor<QEXTPointerFunctor<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(functor);
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
inline QEXTRetypeFunctor<QEXTMemberFunctor<T_return, T_obj> >
qextRetypeFunctor(const QEXTMemberFunctor<T_return, T_obj> &functor)
{
    return QEXTRetypeFunctor<QEXTMemberFunctor<T_return, T_obj> >(functor);
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
inline QEXTRetypeFunctor<QEXTMemberFunctor<T_return, T_obj, T_arg1>, T_arg1 >
qextRetypeFunctor(const QEXTMemberFunctor<T_return, T_obj, T_arg1> &functor)
{
    return QEXTRetypeFunctor<QEXTMemberFunctor<T_return, T_obj, T_arg1>, T_arg1 >(functor);
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
inline QEXTRetypeFunctor<QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2>, T_arg1, T_arg2 >
qextRetypeFunctor(const QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2> &functor)
{
    return QEXTRetypeFunctor<QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2>, T_arg1, T_arg2 >(functor);
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
inline QEXTRetypeFunctor<QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >
qextRetypeFunctor(const QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3> &functor)
{
    return QEXTRetypeFunctor<QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >(functor);
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
inline QEXTRetypeFunctor<QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >
qextRetypeFunctor(const QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> &functor)
{
    return QEXTRetypeFunctor<QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >(functor);
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
inline QEXTRetypeFunctor<QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
qextRetypeFunctor(const QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> &functor)
{
    return QEXTRetypeFunctor<QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(functor);
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
inline QEXTRetypeFunctor<QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
qextRetypeFunctor(const QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> &functor)
{
    return QEXTRetypeFunctor<QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(functor);
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
inline QEXTRetypeFunctor<QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
qextRetypeFunctor(const QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> &functor)
{
    return QEXTRetypeFunctor<QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTConstMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj>
inline QEXTRetypeFunctor<QEXTConstMemberFunctor<T_return, T_obj> >
qextRetypeFunctor(const QEXTConstMemberFunctor<T_return, T_obj> &functor)
{
    return QEXTRetypeFunctor<QEXTConstMemberFunctor<T_return, T_obj> >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTConstMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1>
inline QEXTRetypeFunctor<QEXTConstMemberFunctor<T_return, T_obj, T_arg1>, T_arg1 >
qextRetypeFunctor(const QEXTConstMemberFunctor<T_return, T_obj, T_arg1> &functor)
{
    return QEXTRetypeFunctor<QEXTConstMemberFunctor<T_return, T_obj, T_arg1>, T_arg1 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTConstMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QEXTRetypeFunctor<QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2>, T_arg1, T_arg2 >
qextRetypeFunctor(const QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2> &functor)
{
    return QEXTRetypeFunctor<QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2>, T_arg1, T_arg2 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTConstMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTRetypeFunctor<QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >
qextRetypeFunctor(const QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3> &functor)
{
    return QEXTRetypeFunctor<QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTConstMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTRetypeFunctor<QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >
qextRetypeFunctor(const QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> &functor)
{
    return QEXTRetypeFunctor<QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTConstMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTRetypeFunctor<QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
qextRetypeFunctor(const QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> &functor)
{
    return QEXTRetypeFunctor<QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTConstMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTRetypeFunctor<QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
qextRetypeFunctor(const QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> &functor)
{
    return QEXTRetypeFunctor<QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTConstMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTRetypeFunctor<QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
qextRetypeFunctor(const QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> &functor)
{
    return QEXTRetypeFunctor<QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTVolatileMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj>
inline QEXTRetypeFunctor<QEXTVolatileMemberFunctor<T_return, T_obj> >
qextRetypeFunctor(const QEXTVolatileMemberFunctor<T_return, T_obj> &functor)
{
    return QEXTRetypeFunctor<QEXTVolatileMemberFunctor<T_return, T_obj> >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTVolatileMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1>
inline QEXTRetypeFunctor<QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1>, T_arg1 >
qextRetypeFunctor(const QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1> &functor)
{
    return QEXTRetypeFunctor<QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1>, T_arg1 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTVolatileMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QEXTRetypeFunctor<QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>, T_arg1, T_arg2 >
qextRetypeFunctor(const QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2> &functor)
{
    return QEXTRetypeFunctor<QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>, T_arg1, T_arg2 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTVolatileMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTRetypeFunctor<QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >
qextRetypeFunctor(const QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3> &functor)
{
    return QEXTRetypeFunctor<QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTVolatileMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTRetypeFunctor<QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >
qextRetypeFunctor(const QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> &functor)
{
    return QEXTRetypeFunctor<QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTVolatileMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTRetypeFunctor<QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
qextRetypeFunctor(const QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> &functor)
{
    return QEXTRetypeFunctor<QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTVolatileMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTRetypeFunctor<QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
qextRetypeFunctor(const QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> &functor)
{
    return QEXTRetypeFunctor<QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTVolatileMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTRetypeFunctor<QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
qextRetypeFunctor(const QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> &functor)
{
    return QEXTRetypeFunctor<QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTConstVolatileMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj>
inline QEXTRetypeFunctor<QEXTConstVolatileMemberFunctor<T_return, T_obj> >
qextRetypeFunctor(const QEXTConstVolatileMemberFunctor<T_return, T_obj> &functor)
{
    return QEXTRetypeFunctor<QEXTConstVolatileMemberFunctor<T_return, T_obj> >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTConstVolatileMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1>
inline QEXTRetypeFunctor<QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1>, T_arg1 >
qextRetypeFunctor(const QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1> &functor)
{
    return QEXTRetypeFunctor<QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1>, T_arg1 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTConstVolatileMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QEXTRetypeFunctor<QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>, T_arg1, T_arg2 >
qextRetypeFunctor(const QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2> &functor)
{
    return QEXTRetypeFunctor<QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>, T_arg1, T_arg2 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTConstVolatileMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTRetypeFunctor<QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >
qextRetypeFunctor(const QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3> &functor)
{
    return QEXTRetypeFunctor<QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTConstVolatileMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTRetypeFunctor<QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >
qextRetypeFunctor(const QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> &functor)
{
    return QEXTRetypeFunctor<QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTConstVolatileMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTRetypeFunctor<QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
qextRetypeFunctor(const QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> &functor)
{
    return QEXTRetypeFunctor<QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTConstVolatileMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTRetypeFunctor<QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
qextRetypeFunctor(const QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> &functor)
{
    return QEXTRetypeFunctor<QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTConstVolatileMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTRetypeFunctor<QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
qextRetypeFunctor(const QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> &functor)
{
    return QEXTRetypeFunctor<QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj>
inline QEXTRetypeFunctor<QEXTBoundMemberFunctor<T_return, T_obj> >
qextRetypeFunctor(const QEXTBoundMemberFunctor<T_return, T_obj> &functor)
{
    return QEXTRetypeFunctor<QEXTBoundMemberFunctor<T_return, T_obj> >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1>
inline QEXTRetypeFunctor<QEXTBoundMemberFunctor<T_return, T_obj, T_arg1>, T_arg1 >
qextRetypeFunctor(const QEXTBoundMemberFunctor<T_return, T_obj, T_arg1> &functor)
{
    return QEXTRetypeFunctor<QEXTBoundMemberFunctor<T_return, T_obj, T_arg1>, T_arg1 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QEXTRetypeFunctor<QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2>, T_arg1, T_arg2 >
qextRetypeFunctor(const QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2> &functor)
{
    return QEXTRetypeFunctor<QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2>, T_arg1, T_arg2 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTRetypeFunctor<QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >
qextRetypeFunctor(const QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3> &functor)
{
    return QEXTRetypeFunctor<QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTRetypeFunctor<QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >
qextRetypeFunctor(const QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> &functor)
{
    return QEXTRetypeFunctor<QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTRetypeFunctor<QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
qextRetypeFunctor(const QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> &functor)
{
    return QEXTRetypeFunctor<QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTRetypeFunctor<QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
qextRetypeFunctor(const QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> &functor)
{
    return QEXTRetypeFunctor<QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTRetypeFunctor<QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
qextRetypeFunctor(const QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> &functor)
{
    return QEXTRetypeFunctor<QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundConstMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj>
inline QEXTRetypeFunctor<QEXTBoundConstMemberFunctor<T_return, T_obj> >
qextRetypeFunctor(const QEXTBoundConstMemberFunctor<T_return, T_obj> &functor)
{
    return QEXTRetypeFunctor<QEXTBoundConstMemberFunctor<T_return, T_obj> >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundConstMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1>
inline QEXTRetypeFunctor<QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1>, T_arg1 >
qextRetypeFunctor(const QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1> &functor)
{
    return QEXTRetypeFunctor<QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1>, T_arg1 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundConstMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QEXTRetypeFunctor<QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2>, T_arg1, T_arg2 >
qextRetypeFunctor(const QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2> &functor)
{
    return QEXTRetypeFunctor<QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2>, T_arg1, T_arg2 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundConstMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTRetypeFunctor<QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >
qextRetypeFunctor(const QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3> &functor)
{
    return QEXTRetypeFunctor<QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundConstMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTRetypeFunctor<QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >
qextRetypeFunctor(const QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> &functor)
{
    return QEXTRetypeFunctor<QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundConstMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTRetypeFunctor<QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
qextRetypeFunctor(const QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> &functor)
{
    return QEXTRetypeFunctor<QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundConstMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTRetypeFunctor<QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
qextRetypeFunctor(const QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> &functor)
{
    return QEXTRetypeFunctor<QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundConstMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTRetypeFunctor<QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
qextRetypeFunctor(const QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> &functor)
{
    return QEXTRetypeFunctor<QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundVolatileMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj>
inline QEXTRetypeFunctor<QEXTBoundVolatileMemberFunctor<T_return, T_obj> >
qextRetypeFunctor(const QEXTBoundVolatileMemberFunctor<T_return, T_obj> &functor)
{
    return QEXTRetypeFunctor<QEXTBoundVolatileMemberFunctor<T_return, T_obj> >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundVolatileMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1>
inline QEXTRetypeFunctor<QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1>, T_arg1 >
qextRetypeFunctor(const QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1> &functor)
{
    return QEXTRetypeFunctor<QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1>, T_arg1 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundVolatileMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QEXTRetypeFunctor<QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>, T_arg1, T_arg2 >
qextRetypeFunctor(const QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2> &functor)
{
    return QEXTRetypeFunctor<QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>, T_arg1, T_arg2 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundVolatileMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTRetypeFunctor<QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >
qextRetypeFunctor(const QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3> &functor)
{
    return QEXTRetypeFunctor<QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundVolatileMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTRetypeFunctor<QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >
qextRetypeFunctor(const QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> &functor)
{
    return QEXTRetypeFunctor<QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundVolatileMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTRetypeFunctor<QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
qextRetypeFunctor(const QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> &functor)
{
    return QEXTRetypeFunctor<QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundVolatileMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTRetypeFunctor<QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
qextRetypeFunctor(const QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> &functor)
{
    return QEXTRetypeFunctor<QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundVolatileMemberFunctor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTRetypeFunctor<QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
qextRetypeFunctor(const QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> &functor)
{
    return QEXTRetypeFunctor<QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundConstVolatileMemberFunctor7.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj>
inline QEXTRetypeFunctor<QEXTBoundConstVolatileMemberFunctor<T_return, T_obj> >
qextRetypeFunctor(const QEXTBoundConstVolatileMemberFunctor<T_return, T_obj> &functor)
{
    return QEXTRetypeFunctor<QEXTBoundConstVolatileMemberFunctor<T_return, T_obj> >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundConstVolatileMemberFunctor7.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1>
inline QEXTRetypeFunctor<QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1>, T_arg1 >
qextRetypeFunctor(const QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1> &functor)
{
    return QEXTRetypeFunctor<QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1>, T_arg1 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundConstVolatileMemberFunctor7.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QEXTRetypeFunctor<QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>, T_arg1, T_arg2 >
qextRetypeFunctor(const QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2> &functor)
{
    return QEXTRetypeFunctor<QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>, T_arg1, T_arg2 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundConstVolatileMemberFunctor7.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTRetypeFunctor<QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >
qextRetypeFunctor(const QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3> &functor)
{
    return QEXTRetypeFunctor<QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundConstVolatileMemberFunctor7.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTRetypeFunctor<QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >
qextRetypeFunctor(const QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> &functor)
{
    return QEXTRetypeFunctor<QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundConstVolatileMemberFunctor7.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTRetypeFunctor<QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
qextRetypeFunctor(const QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> &functor)
{
    return QEXTRetypeFunctor<QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundConstVolatileMemberFunctor7.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTRetypeFunctor<QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
qextRetypeFunctor(const QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> &functor)
{
    return QEXTRetypeFunctor<QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundConstVolatileMemberFunctor7.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * \ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTRetypeFunctor<QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
qextRetypeFunctor(const QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> &functor)
{
    return QEXTRetypeFunctor<QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(functor);
}



#endif // _QEXTRETYPEFUNCTOR_H
