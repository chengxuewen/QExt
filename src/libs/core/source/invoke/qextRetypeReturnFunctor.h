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

#ifndef _QEXTRETYPERETURNFUNCTOR_H
#define _QEXTRETYPERETURNFUNCTOR_H

#include <qextAdaptorTrait.h>



/** Adaptor that performs a C-style cast on the return value of a functor.
 * Use the convenience function qextRetypeReturnFunctor() to create an instance of QExtRetypeReturnFunctor.
 *
 * The following template arguments are used:
 * - @e T_return Target type of the C-style cast.
 * - @e T_functor Type of the functor to wrap.
 *
 * \ingroup retype
 */
template < typename T_return, typename T_functor >
struct QExtRetypeReturnFunctor : public QExtAdapts< T_functor >
{

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
        typedef T_return Type;
    };

    typedef T_return Return;

    T_return operator()()
    {
        T_return(this->m_functor());
    }

    template < typename T_arg1 >
    inline T_return operator()(T_arg1 arg1)
    {
        return T_return(this->m_functor.template operator()< typename QExtTypeTrait< T_arg1 >::Pass >(arg1));
    }

    template < typename T_arg1, typename T_arg2 >
    inline T_return operator()(T_arg1 arg1, T_arg2 arg2)
    {
        return T_return(this->m_functor.template operator()< typename QExtTypeTrait< T_arg1 >::Pass, typename QExtTypeTrait< T_arg2 >::Pass >(arg1, arg2));
    }

    template < typename T_arg1, typename T_arg2, typename T_arg3 >
    inline T_return operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3)
    {
        return T_return(
            this->m_functor.template
            operator()< typename QExtTypeTrait< T_arg1 >::Pass, typename QExtTypeTrait< T_arg2 >::Pass, typename QExtTypeTrait< T_arg3 >::Pass >(arg1, arg2, arg3));
    }

    template < typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
    inline T_return operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4)
    {
        return T_return(this->m_functor.template operator()<
                        typename QExtTypeTrait< T_arg1 >::Pass,
                        typename QExtTypeTrait< T_arg2 >::Pass,
                        typename QExtTypeTrait< T_arg3 >::Pass,
                        typename QExtTypeTrait< T_arg4 >::Pass >(arg1, arg2, arg3, arg4));
    }

    template < typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
    inline T_return operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5)
    {
        return T_return(this->m_functor.template operator()<
                        typename QExtTypeTrait< T_arg1 >::Pass,
                        typename QExtTypeTrait< T_arg2 >::Pass,
                        typename QExtTypeTrait< T_arg3 >::Pass,
                        typename QExtTypeTrait< T_arg4 >::Pass,
                        typename QExtTypeTrait< T_arg5 >::Pass >(arg1, arg2, arg3, arg4, arg5));
    }

    template < typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
    inline T_return operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6)
    {
        return T_return(this->m_functor.template operator()<
                        typename QExtTypeTrait< T_arg1 >::Pass,
                        typename QExtTypeTrait< T_arg2 >::Pass,
                        typename QExtTypeTrait< T_arg3 >::Pass,
                        typename QExtTypeTrait< T_arg4 >::Pass,
                        typename QExtTypeTrait< T_arg5 >::Pass,
                        typename QExtTypeTrait< T_arg6 >::Pass >(arg1, arg2, arg3, arg4, arg5, arg6));
    }

    template < typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7 >
    inline T_return operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7)
    {
        return T_return(this->m_functor.template operator()<
                        typename QExtTypeTrait< T_arg1 >::Pass,
                        typename QExtTypeTrait< T_arg2 >::Pass,
                        typename QExtTypeTrait< T_arg3 >::Pass,
                        typename QExtTypeTrait< T_arg4 >::Pass,
                        typename QExtTypeTrait< T_arg5 >::Pass,
                        typename QExtTypeTrait< T_arg6 >::Pass,
                        typename QExtTypeTrait< T_arg7 >::Pass >(arg1, arg2, arg3, arg4, arg5, arg6, arg7));
    }

    QExtRetypeReturnFunctor() {}

    /** Constructs a QExtRetypeReturnFunctor object that perform a C-style cast on the return value of the passed functor.
     * \param functor Functor to invoke from operator()().
     */
    explicit QExtRetypeReturnFunctor(typename QExtTypeTrait< T_functor >::Take functor) : QExtAdapts< T_functor >(functor) {}
};

/** Adaptor that performs a C-style cast on the return value of a functor.
 * This template specialization is for a void return. It drops the return value of the functor it invokes.
 * Use the convenience function qextHideReturnFunctor() to create an instance of qextHideReturnFunctor<void>.
 *
 * \ingroup retype
 */
/* The void specialization is needed because of explicit cast to T_return.
 */
template < typename T_functor >
struct QExtRetypeReturnFunctor< void, T_functor > : public QExtAdapts< T_functor >
{

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
        typedef void Type;
    };

    typedef void Return;

    void operator()()
    {
        this->m_functor();
    }

    template < typename T_arg1 >
    inline void operator()(T_arg1 arg1)
    {
        this->m_functor.template operator()< typename QExtTypeTrait< T_arg1 >::Pass >(arg1);
    }

    template < typename T_arg1, typename T_arg2 >
    inline void operator()(T_arg1 arg1, T_arg2 arg2)
    {
        this->m_functor.template operator()< typename QExtTypeTrait< T_arg1 >::Pass, typename QExtTypeTrait< T_arg2 >::Pass >(arg1, arg2);
    }

    template < typename T_arg1, typename T_arg2, typename T_arg3 >
    inline void operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3)
    {
        this->m_functor.template operator()< typename QExtTypeTrait< T_arg1 >::Pass, typename QExtTypeTrait< T_arg2 >::Pass, typename QExtTypeTrait< T_arg3 >::Pass >(
            arg1, arg2, arg3);
    }

    template < typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
    inline void operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4)
    {
        this->m_functor.template operator()<
            typename QExtTypeTrait< T_arg1 >::Pass,
            typename QExtTypeTrait< T_arg2 >::Pass,
            typename QExtTypeTrait< T_arg3 >::Pass,
            typename QExtTypeTrait< T_arg4 >::Pass >(arg1, arg2, arg3, arg4);
    }

    template < typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
    inline void operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5)
    {
        this->m_functor.template operator()<
            typename QExtTypeTrait< T_arg1 >::Pass,
            typename QExtTypeTrait< T_arg2 >::Pass,
            typename QExtTypeTrait< T_arg3 >::Pass,
            typename QExtTypeTrait< T_arg4 >::Pass,
            typename QExtTypeTrait< T_arg5 >::Pass >(arg1, arg2, arg3, arg4, arg5);
    }

    template < typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
    inline void operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6)
    {
        this->m_functor.template operator()<
            typename QExtTypeTrait< T_arg1 >::Pass,
            typename QExtTypeTrait< T_arg2 >::Pass,
            typename QExtTypeTrait< T_arg3 >::Pass,
            typename QExtTypeTrait< T_arg4 >::Pass,
            typename QExtTypeTrait< T_arg5 >::Pass,
            typename QExtTypeTrait< T_arg6 >::Pass >(arg1, arg2, arg3, arg4, arg5, arg6);
    }

    template < typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7 >
    inline void operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7)
    {
        this->m_functor.template operator()<
            typename QExtTypeTrait< T_arg1 >::Pass,
            typename QExtTypeTrait< T_arg2 >::Pass,
            typename QExtTypeTrait< T_arg3 >::Pass,
            typename QExtTypeTrait< T_arg4 >::Pass,
            typename QExtTypeTrait< T_arg5 >::Pass,
            typename QExtTypeTrait< T_arg6 >::Pass,
            typename QExtTypeTrait< T_arg7 >::Pass >(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    QExtRetypeReturnFunctor() {}
    QExtRetypeReturnFunctor(typename QExtTypeTrait< T_functor >::Take functor) : QExtAdapts< T_functor >(functor) {}
};

//template specialization of QExtVisitor<>::doVisitEach<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for qextHideReturnFunctor performs a functor on the
 * functor stored in the qextHideReturnFunctor object.
 *
 * \ingroup retype
 */
template < typename T_return, typename T_functor >
struct QExtVisitor< QExtRetypeReturnFunctor< T_return, T_functor > >
{
    template < typename T_action >
    static void doVisitEach(const T_action &action, const QExtRetypeReturnFunctor< T_return, T_functor > &target)
    {
        qextVisitEach(action, target.m_functor);
    }
};

/** Creates an adaptor of type qextHideReturnFunctor which performs a C-style cast on the return value of the passed functor.
 * The template argument @e T_return specifies the target type of the cast.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor performing a C-style cast on the return value.
 *
 * \ingroup retype
 */
template < typename T_return, typename T_functor >
inline QExtRetypeReturnFunctor< T_return, T_functor > qextRetypeReturnFunctor(const T_functor &functor)
{
    return QExtRetypeReturnFunctor< T_return, T_functor >(functor);
}

/** Creates an adaptor of type qextHideReturnFunctor which drops the return value of the passed functor.
 *
 * \param functor Functor that should be wrapped.
 * \return Adaptor that executes @e functor dropping its return value.
 *
 * \ingroup hide
 */
template < typename T_functor >
inline QExtRetypeReturnFunctor< void, T_functor > qextHideReturnFunctor(const T_functor &functor)
{
    return QExtRetypeReturnFunctor< void, T_functor >(functor);
}



#endif // _QEXTRETYPERETURNFUNCTOR_H
