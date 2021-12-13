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

#ifndef _QEXTLAMBDABASE_H
#define _QEXTLAMBDABASE_H

#include <qextAdaptorTrait.h>
#include <qextTypeTrait.h>
#include <qextVisitor.h>
#include <qextReferenceWrapper.h>



/** @defgroup lambdas qextLambda
 * QEXT lambdas ships with basic lambda functionality and the qextLambdaGroup adaptor,
 * which uses lambdas to transform a functor's parameter list.
 *
 * The lambda selectors qextLambdaSelectors::_1, qextLambdaSelectors::_2, ..., qextLambdaSelectors::_7 are used to select the
 * first, second, ..., seventh argument from a list.
 *
 * @par Examples:
 * @code
 * std::cout << qextLambdaSelectors::_1(10,20,30); // returns 10
 * std::cout << qextLambdaSelectors::_2(10,20,30); // returns 20
 * @endcode
 *
 * Operators are defined so that, for example, lambda selectors can be used as
 * placeholders in arithmetic expressions.
 *
 * @par Examples:
 * @code
 * std::cout << (qextLambdaSelectors::_1 + 5)(3); // returns (3 + 5)
 * std::cout << (qextLambdaSelectors::_1 * qextLambdaSelectors::_2)(7,10); // returns (7 * 10)
 * @endcode
 *
 * If your compiler supports C++11 lambda expressions, they are often a good
 * alternative to QEXT lambda expressions. The following examples are
 * equivalent to the previous ones.
 * @code
 * [] (int x, int, int) -> int { return x; }(10,20,30); // returns 10
 * [] (int, int y, int) -> int { return y; }(10,20,30); // returns 20
 * [] (int x) -> int { return x + 5; }(3); // returns (3 + 5)
 * [] (int x, int y) -> int { return x * y; }(7,10); // returns (7 * 10)
 * @endcode
 *
 * @deprecated Use C++11 lambda expressions or %std::bind() instead.
 */

/** A hint to the compiler.
 * All lambda types publically inherit from this hint.
 *
 * @deprecated Use C++11 lambda expressions instead.
 *
 * \ingroup qextLambda
 */
struct QEXTLambdaBase : public QEXTAdaptorBase {};

// Forward declaration of lambda.
template <typename T_type> struct QEXTLambda;

namespace qextPrivate
{

    /** Abstracts lambda functionality.
     * Objects of this type store a value that may be of type lambda itself.
     * In this case, operator()() executes the lambda (a lambda is always a functor at the same time).
     * Otherwise, operator()() simply returns the stored value.
     *
     * @deprecated Use C++11 lambda expressions instead.
     *
     * \ingroup qextLambda
     */
    template <typename T_type, bool I_islambda = QEXTIsBaseOf<QEXTLambdaBase, T_type>::value> struct QEXTLambdaCore;


    /** Abstracts lambda functionality (template specialization for lambda values).
     *
     * @deprecated Use C++11 lambda expressions instead.
     *
     * \ingroup qextLambda
     */
    template <typename T_type>
    struct QEXTLambdaCore<T_type, true> : public QEXTLambdaBase
    {
        template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
                  typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
        struct ReturnTypeDeduce
        {
            typedef typename T_type::template ReturnTypeDeduce <
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass,
                typename QEXTTypeTrait<T_arg6>::Pass,
                typename QEXTTypeTrait<T_arg7>::Pass >::Type Type;
        };

        typedef typename T_type::Return   Return;
        typedef T_type Lambda;

        Return
        operator()() const
        {
            return m_value();
        }

        template <typename T_arg1>
        typename ReturnTypeDeduce<T_arg1>::Type
        operator ()(T_arg1 arg1) const
        {
            return m_value.template operator () <
                   typename QEXTTypeTrait<T_arg1>::Pass >
                   (arg1);
        }


        template <typename T_arg1, typename T_arg2>
        typename ReturnTypeDeduce<T_arg1, T_arg2>::Type
        operator ()(T_arg1 arg1, T_arg2 arg2) const
        {
            return m_value.template operator () <
                   typename QEXTTypeTrait<T_arg1>::Pass,
                   typename QEXTTypeTrait<T_arg2>::Pass >
                   (arg1, arg2);
        }


        template <typename T_arg1, typename T_arg2, typename T_arg3>
        typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3>::Type
        operator ()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) const
        {
            return m_value.template operator () <
                   typename QEXTTypeTrait<T_arg1>::Pass,
                   typename QEXTTypeTrait<T_arg2>::Pass,
                   typename QEXTTypeTrait<T_arg3>::Pass >
                   (arg1, arg2, arg3);
        }


        template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
        typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
        operator ()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) const
        {
            return m_value.template operator () <
                   typename QEXTTypeTrait<T_arg1>::Pass,
                   typename QEXTTypeTrait<T_arg2>::Pass,
                   typename QEXTTypeTrait<T_arg3>::Pass,
                   typename QEXTTypeTrait<T_arg4>::Pass >
                   (arg1, arg2, arg3, arg4);
        }


        template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
        typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
        operator ()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) const
        {
            return m_value.template operator () <
                   typename QEXTTypeTrait<T_arg1>::Pass,
                   typename QEXTTypeTrait<T_arg2>::Pass,
                   typename QEXTTypeTrait<T_arg3>::Pass,
                   typename QEXTTypeTrait<T_arg4>::Pass,
                   typename QEXTTypeTrait<T_arg5>::Pass >
                   (arg1, arg2, arg3, arg4, arg5);
        }


        template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
        typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
        operator ()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) const
        {
            return m_value.template operator () <
                   typename QEXTTypeTrait<T_arg1>::Pass,
                   typename QEXTTypeTrait<T_arg2>::Pass,
                   typename QEXTTypeTrait<T_arg3>::Pass,
                   typename QEXTTypeTrait<T_arg4>::Pass,
                   typename QEXTTypeTrait<T_arg5>::Pass,
                   typename QEXTTypeTrait<T_arg6>::Pass >
                   (arg1, arg2, arg3, arg4, arg5, arg6);
        }


        template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
        typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type
        operator ()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7) const
        {
            return m_value.template operator () <
                   typename QEXTTypeTrait<T_arg1>::Pass,
                   typename QEXTTypeTrait<T_arg2>::Pass,
                   typename QEXTTypeTrait<T_arg3>::Pass,
                   typename QEXTTypeTrait<T_arg4>::Pass,
                   typename QEXTTypeTrait<T_arg5>::Pass,
                   typename QEXTTypeTrait<T_arg6>::Pass,
                   typename QEXTTypeTrait<T_arg7>::Pass >
                   (arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        }

        QEXTLambdaCore() {}

        explicit QEXTLambdaCore(const T_type &value)
            : m_value(value) {}

        T_type m_value;
    };




    /** Abstracts lambda functionality (template specialization for other value types).
     *
     * @deprecated Use C++11 lambda expressions instead.
     *
     * \ingroup qextLambda
     */
    template <typename T_type>
    struct QEXTLambdaCore<T_type, false> : public QEXTLambdaBase
    {
        template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
                  typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
        struct ReturnTypeDeduce
        {
            typedef T_type Type;
        };
        typedef T_type Return; // all operator() overloads return T_type.
        typedef QEXTLambda<T_type> Lambda;

        Return operator()() const
        {
            return m_value;
        }

        template <typename T_arg1>
        Return operator ()(T_arg1) const
        {
            return m_value;
        }

        template <typename T_arg1, typename T_arg2>
        Return operator ()(T_arg1, T_arg2) const
        {
            return m_value;
        }

        template <typename T_arg1, typename T_arg2, typename T_arg3>
        Return operator ()(T_arg1, T_arg2, T_arg3) const
        {
            return m_value;
        }

        template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
        Return operator ()(T_arg1, T_arg2, T_arg3, T_arg4) const
        {
            return m_value;
        }

        template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
        Return operator ()(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const
        {
            return m_value;
        }

        template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
        Return operator ()(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const
        {
            return m_value;
        }

        template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
        Return operator ()(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const
        {
            return m_value;
        }

        explicit QEXTLambdaCore(typename QEXTTypeTrait<T_type>::Take value)
            : m_value(value) {}

        T_type m_value;
    };

} /* namespace qextPrivate */


//template specialization of visitor<>::do_visit_each<>(action, functor):
template <typename T_functor, bool I_islambda>
struct QEXTVisitor<qextPrivate::QEXTLambdaCore<T_functor, I_islambda> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const qextPrivate::QEXTLambdaCore<T_functor, I_islambda> &target)
    {
        qextVisitEach(action, target.m_value);
    }
};

// forward declarations for lambda operators other<subscript> and other<assign>
template <typename T_type>
struct QEXTLambdaOther;
struct QEXTLambdaSubscript;
struct QEXTLambdaAssign;

template <typename T_action, typename T_type1, typename T_type2>
struct QEXTLambdaOperator;

template <typename T_type>
struct QEXTUnwrapLambdaType;


/** Gets the object stored inside a lambda object.
 * Returns the object passed as argument, if it is not of type lambda.
 *
 * @deprecated Use C++11 lambda expressions instead of libsigc++ lambdas.
 *
 * \ingroup qextLambda
 */
template <typename T_type>
T_type &qextUnwrapLambdaValue(T_type &arg)
{
    return arg;
}

/** Gets the object stored inside a lambda object.
 * Returns the object passed as argument, if it is not of type lambda.
 *
 * @deprecated Use C++11 lambda expressions instead of libsigc++ lambdas.
 *
 * \ingroup qextLambda
 */
template <typename T_type>
const T_type &qextUnwrapLambdaValue(const T_type &arg)
{
    return arg;
}

/** Gets the object stored inside a lambda object.
 *
 * @deprecated Use C++11 lambda expressions instead of libsigc++ lambdas.
 *
 * \ingroup qextLambda
 */
template <typename T_type>
const T_type &qextUnwrapLambdaValue(const QEXTLambda<T_type> &arg)
{
    return arg.m_value;
}



/** Lambda type.
 * Objects of this type store a value that may be of type lambda itself.
 * In this case, operator()() executes the lambda (a lambda is always a functor at the same time).
 * Otherwise, operator()() simply returns the stored value.
 * The assign and subscript operators are defined to return a lambda operator.
 *
 * @deprecated Use C++11 lambda expressions instead.
 *
 * \ingroup qextLambda
 */
template <typename T_type>
struct QEXTLambda : public qextPrivate::QEXTLambdaCore<T_type>
{
    typedef QEXTLambda<T_type> Self;

    QEXTLambda() {}

    QEXTLambda(typename QEXTTypeTrait<T_type>::Take value)
        : qextPrivate::QEXTLambdaCore<T_type>(value) {}

    // operators for QEXTLambdaOther<QEXTLambdaSubscript>
    template <typename T_arg>
    QEXTLambda<QEXTLambdaOperator<QEXTLambdaOther<QEXTLambdaSubscript>, Self, typename QEXTUnwrapLambdaType<T_arg>::Type> >
    operator [] (const T_arg &arg) const
    {
        typedef QEXTLambdaOperator<QEXTLambdaOther<QEXTLambdaSubscript>, Self, typename QEXTUnwrapLambdaType<T_arg>::Type> LambdaOperatorType;
        return QEXTLambda<LambdaOperatorType>(LambdaOperatorType(this->m_value, qextUnwrapLambdaValue(arg)));
    }

    // operators for QEXTLambdaOther<QEXTLambdaAssign>
    template <typename T_arg>
    QEXTLambda<QEXTLambdaOperator<QEXTLambdaOther<QEXTLambdaAssign>, Self, typename QEXTUnwrapLambdaType<T_arg>::Type> >
    operator = (const T_arg &arg) const
    {
        typedef QEXTLambdaOperator<QEXTLambdaOther<QEXTLambdaAssign>, Self, typename QEXTUnwrapLambdaType<T_arg>::Type> LambdaOperatorType;
        return QEXTLambda<LambdaOperatorType>(LambdaOperatorType(this->m_value, qextUnwrapLambdaValue(arg)));
    }
};

//template specialization of QEXTVisitor<>::doVisitEach<>(action, functor):
template <typename T_type>
struct QEXTVisitor<QEXTLambda<T_type> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTLambda<T_type> &target)
    {
        qextVisitEach(action, target.m_value);
    }
};

/** Converts a reference into a lambda object.
 * qextLambda creates a 0-ary functor, returning the value of a referenced variable.
 *
 * @par Example:
 * @code
 * int main(int argc, char* argv)
 * {
 *   int data;
 *   QEXTSignal<int> readValue;
 *
 *   readValue.connect(qextLambda(data));
 *
 *   data = 3;
 *   std::cout << readValue() << std::endl; //Prints 3.
 *
 *   data = 5;
 *   std::cout << readValue() << std::endl; //Prints 5.
 * }
 * @endcode
 *
 * If your compiler supports C++11 lambda expressions, and you use the macro
 * #QEXT_FUNCTORS_DEDUCE_RESULT_TYPE_WITH_DECLTYPE, you can replace
 * @code
 * readValue.connect(qextLambda(data));
 * @endcode
 * in the example by
 * @code
 * readValue.connect([&data] () -> int { return data; });
 * @endcode
 *
 * @deprecated Use C++11 lambda expressions instead of libsigc++ lambdas.
 *
 * \ingroup qextLambda
 */
template <typename T_type>
QEXTLambda<T_type &> qextLambda(T_type &value)
{
    return QEXTLambda<T_type &>(value);
}

/** Converts a constant reference into a lambda object.
 *
 * @deprecated Use C++11 lambda expressions instead of qextLambda().
 *
 * \ingroup qextLambda
 */
template <typename T_type>
QEXTLambda<const T_type &> qextLambda(const T_type &value)
{
    return QEXTLambda<const T_type &>(value);
}

/** Deduces the type of the object stored in an object of the passed lambda type.
 * If the type passed as template argument is not of lambda type,
 * type is defined to QEXTUnwrapReference<T_type>::Type.
 *
 * @deprecated Use C++11 lambda expressions instead of qextLambda().
 *
 * \ingroup qextLambda
 */
template <typename T_type>
struct QEXTUnwrapLambdaType
{
    typedef typename QEXTUnwrapReference<T_type>::Type Type;
};

/** Deduces the type of the object stored in an object of the passed lambda type.
 *
 * @deprecated Use C++11 lambda expressions instead of qextLambda().
 *
 * \ingroup qextLambda
 */
template <typename T_type>
struct QEXTUnwrapLambdaType<QEXTLambda<T_type> >
{
    typedef T_type Type;
};



#endif // _QEXTLAMBDABASE_H
