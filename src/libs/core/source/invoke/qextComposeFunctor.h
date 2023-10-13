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

#ifndef _QEXTCOMPOSEFUNCTOR_H
#define _QEXTCOMPOSEFUNCTOR_H

#include <qextAdaptorTrait.h>
#include <qextReturnTypeDeduce.h>



/** @defgroup compose qextComposeFunctor()
 * qextComposeFunctor() combines two or three arbitrary functors.
 * On invokation, parameters are passed on to one or two getter functor(s).
 * The return value(s) are then passed on to the setter function.
 *
 * @par Examples:
 * @code
 * float square_root(float a)  { return sqrtf(a); }
 * float sum(float a, float b) { return a+b; }
 * std::cout << qextComposeFunctor(&square_root, &sum)(9, 16); // calls square_root(sum(3,6))
 * std::cout << qextComposeFunctor(&sum, &square_root, &square_root)(9); // calls sum(square_root(9), square_root(9))
 * @endcode
 *
 * The functor qextComposeFunctor() returns can be passed directly into
 * QExtSignal::connect().
 *
 * @par Example:
 * @code
 * QExtSignal<float,float,float> some_signal;
 * some_signal.connect(qextComposeFunctor(&square_root, &sum));
 * @endcode
 *
 * For a more powerful version of this functionality see the lambda
 * library adaptor qextLambdaGroup() which can bind, hide and reorder
 * arguments arbitrarily. Although qextLambdaGroup() is more flexible,
 * qextBindFunctor() provides a means of binding parameters when the total
 * number of parameters called is variable.
 *
 * \ingroup adaptors
 */

/** Adaptor that combines three functors.
 * Use the convenience function qextComposeFunctor() to create an instance of QExtCompose3Functor.
 *
 * The following template arguments are used:
 * - @e T_setter Type of the setter functor to wrap.
 * - @e T_getter1 Type of the first getter functor to wrap.
 * - @e T_getter2 Type of the second getter functor to wrap.
 * - @e T_getter3 Type of the third getter functor to wrap.
 *
 * \ingroup qextComposeFunctor
 */
template<typename T_setter, typename T_getter1, typename T_getter2, typename T_getter3>
struct QExtCompose3Functor : public QExtAdapts<T_setter>
{
    typedef typename QExtAdapts<T_setter>::Adaptor Adaptor;
    typedef T_setter Setter;
    typedef T_getter1 Getter1;
    typedef T_getter2 Getter2;
    typedef T_getter3 Getter3;

    template<
            typename T_arg1 = void,
            typename T_arg2 = void,
            typename T_arg3 = void,
            typename T_arg4 = void,
            typename T_arg5 = void,
            typename T_arg6 = void,
            typename T_arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename Adaptor::template ReturnTypeDeduce<
                typename QExtReturnTypeDeduce<T_getter1, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type,
                typename QExtReturnTypeDeduce<T_getter2, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type,
                typename QExtReturnTypeDeduce<T_getter3, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type>::Type Return;
    };

    typedef typename Adaptor::Return Return;

    QExtCompose3Functor(const T_setter &setter, const T_getter1 &getter1, const T_getter2 &getter2,
                        const T_getter3 &getter3)
            : QExtAdapts<T_setter>(setter), m_getter1(getter1), m_getter2(getter2), m_getter3(getter3)
    {
    }

    QExtCompose3Functor(const QExtCompose3Functor &other)
            : QExtAdapts<T_setter>(other), m_getter1(other.m_getter1), m_getter2(other.m_getter2), m_getter3(
            other.m_getter3)
    {
    }

    QExtCompose3Functor &operator=(const QExtCompose3Functor &other)
    {
        if (this != &other)
        {
            m_getter1 = other.m_getter1;
            m_getter2 = other.m_getter2;
            m_getter3 = other.m_getter3;
        }
        return *this;
    }

    bool operator==(const QExtCompose3Functor &other) const
    {
        return m_getter1 == other.m_getter1 && m_getter2 == other.m_getter2 && m_getter3 == other.m_getter3;
    }

    Return operator()()
    {
        return this->m_functor.template operator()<
                typename QExtReturnTypeDeduce<T_getter1>::Type,
                typename QExtReturnTypeDeduce<T_getter2>::Type,
                typename QExtReturnTypeDeduce<T_getter3>::Type>(m_getter1(), m_getter2(), m_getter3());
    }

    template<typename T_arg1>
    typename ReturnTypeDeduce<T_arg1>::Type operator()(T_arg1 arg1)
    {
        return this->m_functor.template operator()<
                typename QExtReturnTypeDeduce<T_getter1, T_arg1>::Type,
                typename QExtReturnTypeDeduce<T_getter2, T_arg1>::Type,
                typename QExtReturnTypeDeduce<T_getter3, T_arg1>::Type>(m_getter1(arg1), m_getter2(arg1),
                                                                        m_getter3(arg1));
    }

    template<typename T_arg1, typename T_arg2>
    typename ReturnTypeDeduce<T_arg1, T_arg2>::Type operator()(T_arg1 arg1, T_arg2 arg2)
    {
        return this->m_functor.template operator()<
                typename QExtReturnTypeDeduce<T_getter1, T_arg1, T_arg2>::Type,
                typename QExtReturnTypeDeduce<T_getter2, T_arg1, T_arg2>::Type,
                typename QExtReturnTypeDeduce<T_getter3, T_arg1, T_arg2>::Type>(m_getter1(arg1, arg2),
                                                                                m_getter2(arg1, arg2),
                                                                                m_getter3(arg1, arg2));
    }

    template<typename T_arg1, typename T_arg2, typename T_arg3>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3>::Type operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3)
    {
        return this->m_functor.template operator()<
                typename QExtReturnTypeDeduce<T_getter1, T_arg1, T_arg2, T_arg3>::Type,
                typename QExtReturnTypeDeduce<T_getter2, T_arg1, T_arg2, T_arg3>::Type,
                typename QExtReturnTypeDeduce<T_getter3, T_arg1, T_arg2, T_arg3>::Type>(
                m_getter1(arg1, arg2, arg3), m_getter2(arg1, arg2, arg3), m_getter3(arg1, arg2, arg3));
    }

    template<typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4)
    {
        return this->m_functor.template operator()<
                typename QExtReturnTypeDeduce<T_getter1, T_arg1, T_arg2, T_arg3, T_arg4>::Type,
                typename QExtReturnTypeDeduce<T_getter2, T_arg1, T_arg2, T_arg3, T_arg4>::Type,
                typename QExtReturnTypeDeduce<T_getter3, T_arg1, T_arg2, T_arg3, T_arg4>::Type>(
                m_getter1(arg1, arg2, arg3, arg4), m_getter2(arg1, arg2, arg3, arg4),
                m_getter3(arg1, arg2, arg3, arg4));
    }

    template<typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5)
    {
        return this->m_functor.template operator()<
                typename QExtReturnTypeDeduce<T_getter1, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type,
                typename QExtReturnTypeDeduce<T_getter2, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type,
                typename QExtReturnTypeDeduce<T_getter3, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type>(
                m_getter1(arg1, arg2, arg3, arg4, arg5), m_getter2(arg1, arg2, arg3, arg4, arg5),
                m_getter3(arg1, arg2, arg3, arg4, arg5));
    }

    template<typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6)
    {
        return this->m_functor.template operator()<
                typename QExtReturnTypeDeduce<T_getter1, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type,
                typename QExtReturnTypeDeduce<T_getter2, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type,
                typename QExtReturnTypeDeduce<T_getter3, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type>(
                m_getter1(arg1, arg2, arg3, arg4, arg5, arg6), m_getter2(arg1, arg2, arg3, arg4, arg5, arg6),
                m_getter3(arg1, arg2, arg3, arg4, arg5, arg6));
    }

    template<typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7)
    {
        return this->m_functor.template operator()<
                typename QExtReturnTypeDeduce<T_getter1, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type,
                typename QExtReturnTypeDeduce<T_getter2, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type,
                typename QExtReturnTypeDeduce<T_getter3, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type>(
                m_getter1(arg1, arg2, arg3, arg4, arg5, arg6, arg7),
                m_getter2(arg1, arg2, arg3, arg4, arg5, arg6, arg7),
                m_getter3(arg1, arg2, arg3, arg4, arg5, arg6, arg7));
    }

    Getter1 m_getter1;
    Getter2 m_getter2;
    Getter3 m_getter3;
};

//template specialization of visitor<>::do_visit_each<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for QExtCompose3Functor performs a functor on the
 * functors stored in the QExtCompose3Functor object.
 *
 * \ingroup qextComposeFunctor
 */
template<typename T_setter, typename T_getter1, typename T_getter2, typename T_getter3>
struct QExtVisitor<QExtCompose3Functor<T_setter, T_getter1, T_getter2, T_getter3> >
{
    template<typename T_action>
    static void
    doVisitEach(const T_action &action, const QExtCompose3Functor<T_setter, T_getter1, T_getter2, T_getter3> &target)
    {
        qextVisitEach(action, target.m_functor);
        qextVisitEach(action, target.m_getter1);
        qextVisitEach(action, target.m_getter2);
        qextVisitEach(action, target.m_getter3);
    }
};

/** Adaptor that combines three functors.
 * Use the convenience function qextComposeFunctor() to create an instance of QExtCompose2Functor.
 *
 * The following template arguments are used:
 * - @e T_setter Type of the setter functor to wrap.
 * - @e T_getter1 Type of the first getter functor to wrap.
 * - @e T_getter2 Type of the second getter functor to wrap.
 *
 * \ingroup qextComposeFunctor
 */
template<typename T_setter, typename T_getter1, typename T_getter2>
struct QExtCompose2Functor : public QExtAdapts<T_setter>
{
    typedef typename QExtAdapts<T_setter>::Adaptor Adaptor;
    typedef T_setter Setter;
    typedef T_getter1 Getter1;
    typedef T_getter2 Getter2;

    template<
            typename T_arg1 = void,
            typename T_arg2 = void,
            typename T_arg3 = void,
            typename T_arg4 = void,
            typename T_arg5 = void,
            typename T_arg6 = void,
            typename T_arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename Adaptor::template ReturnTypeDeduce<
                typename QExtReturnTypeDeduce<T_getter1, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type,
                typename QExtReturnTypeDeduce<T_getter2, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type>::Type Return;
    };

    typedef typename Adaptor::Return Return;

    /** Constructs a QExtCompose2Functor object that combines the passed functors.
     * \param setter Functor that receives the return values of the invokation of @e getter1 and @e getter2.
     * \param getter1 Functor to invoke from operator()().
     * \param getter2 Functor to invoke from operator()().
     */
    QExtCompose2Functor(const T_setter &setter, const T_getter1 &getter1, const T_getter2 &getter2)
            : QExtAdapts<T_setter>(setter), m_getter1(getter1), m_getter2(getter2)
    {
    }

    QExtCompose2Functor(const QExtCompose2Functor &other) : QExtAdapts<T_setter>(other), m_getter1(other.m_getter1)
                                                            , m_getter2(other.m_getter2) {}

    Return operator()()
    {
        return this->m_functor.template operator()<typename QExtReturnTypeDeduce<T_getter1>::Type, typename QExtReturnTypeDeduce<T_getter2>::Type>(
                m_getter1(), m_getter2());
    }

    template<typename T_arg1>
    typename ReturnTypeDeduce<T_arg1>::Type operator()(T_arg1 arg1)
    {
        return this->m_functor
                .template operator()<typename QExtReturnTypeDeduce<T_getter1, T_arg1>::Type, typename QExtReturnTypeDeduce<T_getter2, T_arg1>::Type>(
                        m_getter1(arg1), m_getter2(arg1));
    }

    template<typename T_arg1, typename T_arg2>
    typename ReturnTypeDeduce<T_arg1, T_arg2>::Type operator()(T_arg1 arg1, T_arg2 arg2)
    {
        return this->m_functor.template
                operator()<typename QExtReturnTypeDeduce<T_getter1, T_arg1, T_arg2>::Type, typename QExtReturnTypeDeduce<T_getter2, T_arg1, T_arg2>::Type>(
                m_getter1(arg1, arg2), m_getter2(arg1, arg2));
    }

    template<typename T_arg1, typename T_arg2, typename T_arg3>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3>::Type operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3)
    {
        return this->m_functor.template operator()<
                typename QExtReturnTypeDeduce<T_getter1, T_arg1, T_arg2, T_arg3>::Type,
                typename QExtReturnTypeDeduce<T_getter2, T_arg1, T_arg2, T_arg3>::Type>(m_getter1(arg1, arg2, arg3),
                                                                                        m_getter2(arg1, arg2, arg3));
    }

    template<typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4)
    {
        return this->m_functor.template operator()<
                typename QExtReturnTypeDeduce<T_getter1, T_arg1, T_arg2, T_arg3, T_arg4>::Type,
                typename QExtReturnTypeDeduce<T_getter2, T_arg1, T_arg2, T_arg3, T_arg4>::Type>(
                m_getter1(arg1, arg2, arg3, arg4), m_getter2(arg1, arg2, arg3, arg4));
    }

    template<typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5)
    {
        return this->m_functor.template operator()<
                typename QExtReturnTypeDeduce<T_getter1, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type,
                typename QExtReturnTypeDeduce<T_getter2, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type>(
                m_getter1(arg1, arg2, arg3, arg4, arg5), m_getter2(arg1, arg2, arg3, arg4, arg5));
    }

    template<typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6)
    {
        return this->m_functor.template operator()<
                typename QExtReturnTypeDeduce<T_getter1, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type,
                typename QExtReturnTypeDeduce<T_getter2, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type>(
                m_getter1(arg1, arg2, arg3, arg4, arg5, arg6), m_getter2(arg1, arg2, arg3, arg4, arg5, arg6));
    }

    template<typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7)
    {
        return this->m_functor.template operator()<
                typename QExtReturnTypeDeduce<T_getter1, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type,
                typename QExtReturnTypeDeduce<T_getter2, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type>(
                m_getter1(arg1, arg2, arg3, arg4, arg5, arg6, arg7),
                m_getter2(arg1, arg2, arg3, arg4, arg5, arg6, arg7));
    }

    Getter1 m_getter1;
    Getter2 m_getter2;
};

//template specialization of visitor<>::do_visit_each<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for QExtCompose2Functor performs a functor on the
 * functors stored in the QExtCompose2Functor object.
 *
 * \ingroup qextComposeFunctor
 */
template<typename T_setter, typename T_getter1, typename T_getter2>
struct QExtVisitor<QExtCompose2Functor<T_setter, T_getter1, T_getter2> >
{
    template<typename T_action>
    static void doVisitEach(const T_action &action, const QExtCompose2Functor<T_setter, T_getter1, T_getter2> &target)
    {
        qextVisitEach(action, target.m_functor);
        qextVisitEach(action, target.m_getter1);
        qextVisitEach(action, target.m_getter2);
    }
};

/** Adaptor that combines two functors.
 * Use the convenience function qextComposeFunctor() to create an instance of QExtCompose1Functor.
 *
 * The following template arguments are used:
 * - @e T_setter Type of the setter functor to wrap.
 * - @e T_getter Type of the getter functor to wrap.
 *
 * \ingroup qextComposeFunctor
 */
template<typename T_setter, typename T_getter>
struct QExtCompose1Functor : public QExtAdapts<T_setter>
{
    typedef typename QExtAdapts<T_setter>::Adaptor Adaptor;
    typedef T_setter Setter;
    typedef T_getter Getter;

    template<
            typename T_arg1 = void,
            typename T_arg2 = void,
            typename T_arg3 = void,
            typename T_arg4 = void,
            typename T_arg5 = void,
            typename T_arg6 = void,
            typename T_arg7 = void>
    struct ReturnTypeDeduce
    {
        typedef typename Adaptor::template ReturnTypeDeduce<
                typename QExtReturnTypeDeduce<T_getter, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type>::Type Type;
    };

    typedef typename Adaptor::Return Return;

    /** Constructs a compose1_functor object that combines the passed functors.
     * \param setter Functor that receives the return values of the invokation of @e getter1 and @e getter2.
     * \param getter Functor to invoke from operator()().
     */
    QExtCompose1Functor(const T_setter &setter, const T_getter &getter) : QExtAdapts<T_setter>(setter), m_getter(
            getter) {}

    QExtCompose1Functor(const QExtCompose1Functor &other) : QExtAdapts<T_setter>(other), m_getter(other.m_getter) {}

    Return operator()()
    {
        return this->m_functor(m_getter());
    }

    template<typename T_arg1>
    typename ReturnTypeDeduce<T_arg1>::Type operator()(T_arg1 arg1)
    {
        return this->m_functor.template operator()<typename QExtReturnTypeDeduce<T_getter, T_arg1>::Type>(
                m_getter(arg1));
    }

    template<typename T_arg1, typename T_arg2>
    typename ReturnTypeDeduce<T_arg1, T_arg2>::Type operator()(T_arg1 arg1, T_arg2 arg2)
    {
        return this->m_functor.template operator()<typename QExtReturnTypeDeduce<T_getter, T_arg1, T_arg2>::Type>(
                m_getter(arg1, arg2));
    }

    template<typename T_arg1, typename T_arg2, typename T_arg3>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3>::Type operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3)
    {
        return this->m_functor.template operator()<typename QExtReturnTypeDeduce<T_getter, T_arg1, T_arg2, T_arg3>::Type>(
                m_getter(arg1, arg2, arg3));
    }

    template<typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4)
    {
        return this->m_functor.template operator()<typename QExtReturnTypeDeduce<T_getter, T_arg1, T_arg2, T_arg3, T_arg4>::Type>(
                m_getter(arg1, arg2, arg3, arg4));
    }

    template<typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5)
    {
        return this->m_functor.template operator()<typename QExtReturnTypeDeduce<T_getter, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type>(
                m_getter(arg1, arg2, arg3, arg4, arg5));
    }

    template<typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6)
    {
        return this->m_functor.template operator()<typename QExtReturnTypeDeduce<T_getter, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type>(
                m_getter(arg1, arg2, arg3, arg4, arg5, arg6));
    }

    template<typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7)
    {
        return this->m_functor.template operator()<typename QExtReturnTypeDeduce<T_getter, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type>(
                m_getter(arg1, arg2, arg3, arg4, arg5, arg6, arg7));
    }

    Getter m_getter;
};

//template specialization of visitor<>::do_visit_each<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for QExtCompose1Functor performs a functor on the
 * functors stored in the QExtCompose1Functor object.
 *
 * \ingroup qextComposeFunctor
 */
template<typename T_setter, typename T_getter>
struct QExtVisitor<QExtCompose1Functor<T_setter, T_getter> >
{
    template<typename T_action>
    static void doVisitEach(const T_action &action, const QExtCompose1Functor<T_setter, T_getter> &target)
    {
        qextVisitEach(action, target.m_functor);
        qextVisitEach(action, target.m_getter);
    }
};

/** Creates an adaptor of type QExtCompose3Functor which combines three functors.
 *
 * \param setter Functor that receives the return values of the invokation of @e getter1 and @e getter2 and @e getter3.
 * \param getter1 Functor to invoke from operator()().
 * \param getter2 Functor to invoke from operator()().
 * \param getter3 Functor to invoke from operator()().
 * \return Adaptor that executes @e setter with the values return from invokation of @e getter1 and @e getter2.
 *
 * \ingroup qextComposeFunctor
 */
template<typename T_setter, typename T_getter1, typename T_getter2, typename T_getter3>
inline QExtCompose3Functor<T_setter, T_getter1, T_getter2, T_getter3>
qextComposeFunctor(const T_setter &setter, const T_getter1 &getter1, const T_getter2 &getter2, const T_getter3 &getter3)
{
    return QExtCompose3Functor<T_setter, T_getter1, T_getter2, T_getter3>(setter, getter1, getter2, getter3);
}

/** Creates an adaptor of type QExtCompose2Functor which combines three functors.
 *
 * \param setter Functor that receives the return values of the invokation of @e getter1 and @e getter2.
 * \param getter1 Functor to invoke from operator()().
 * \param getter2 Functor to invoke from operator()().
 * \return Adaptor that executes @e setter with the values return from invokation of @e getter1 and @e getter2.
 *
 * \ingroup qextComposeFunctor
 */
template<typename T_setter, typename T_getter1, typename T_getter2>
inline QExtCompose2Functor<T_setter, T_getter1, T_getter2>
qextComposeFunctor(const T_setter &setter, const T_getter1 &getter1, const T_getter2 &getter2)
{
    return QExtCompose2Functor<T_setter, T_getter1, T_getter2>(setter, getter1, getter2);
}

/** Creates an adaptor of type QExtCompose1Functor which combines two functors.
 *
 * \param setter Functor that receives the return value of the invokation of @e getter.
 * \param getter Functor to invoke from operator()().
 * \return Adaptor that executes @e setter with the value returned from invokation of @e getter.
 *
 * \ingroup qextComposeFunctor
 */
template<typename T_setter, typename T_getter>
inline QExtCompose1Functor<T_setter, T_getter> qextComposeFunctor(const T_setter &setter, const T_getter &getter)
{
    return QExtCompose1Functor<T_setter, T_getter>(setter, getter);
}


#endif // _QEXTCOMPOSEFUNCTOR_H
