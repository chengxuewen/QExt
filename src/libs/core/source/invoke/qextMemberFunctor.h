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

#ifndef _QEXTMEMBERFUNCTOR_H
#define _QEXTMEMBERFUNCTOR_H

#include <qextFunctorTrait.h>
#include <qextGlobal.h>
#include <qextLimitReference.h>



/** @defgroup qextMemberFunctor qextMemberFunctor()
 * qextMemberFunctor() is used to convert a pointer to a method to a functor.
 *
 * Optionally, a reference or pointer to an object can be bound to the functor.
 * Note that only if the object type inherits from QObject is
 * the slot automatically cleared when the object goes out of scope!
 *
 * If the member function pointer is to an overloaded type, you must specify
 * the types using template arguments starting with the first argument.
 * It is not necessary to supply the return type.
 *
 * @par Example:
 * @code
 * struct foo : public QObject
 * {
 *   void bar(int) {}
 * };
 * foo my_foo;
 * QEXTFunction<void, int> slot = qextMemberFunctor(my_foo, &foo::bar);
 * @endcode
 *
 * For const methods qextMemberFunctor() takes a const reference or pointer to an object.
 *
 * @par Example:
 * @code
 * struct foo : public QObject
 * {
 *   void bar(int) const {}
 * };
 * const foo my_foo;
 * QEXTFunction<void, int> slot = qextMemberFunctor(my_foo, &foo::bar);
 * @endcode
 *
 * Use qextMemberFunctor#() if there is an ambiguity as to the number of arguments.
 *
 * @par Example:
 * @code
 * struct foo : public QObject
 * {
 *   void bar(int) {}
 *   void bar(float) {}
 *   void bar(int, int) {}
 * };
 * foo my_foo;
 * QEXTFunction<void, int> slot = qextMemberFunctor1<int>(my_foo, &foo::bar);
 * @endcode
 *
 * \ingroup qextfunctors
 */

namespace qextPrivate
{

    /** QEXTMemberFunctor7 wraps  methods with 7 argument(s).
 * Use the convenience function qextMemberFunctor() to create an instance of QEXTMemberFunctor7.
 *
 * The following template arguments are used:
 * - @e T_arg1 Argument type used in the definition of operator()().
 * - @e T_arg2 Argument type used in the definition of operator()().
 * - @e T_arg3 Argument type used in the definition of operator()().
 * - @e T_arg4 Argument type used in the definition of operator()().
 * - @e T_arg5 Argument type used in the definition of operator()().
 * - @e T_arg6 Argument type used in the definition of operator()().
 * - @e T_arg7 Argument type used in the definition of operator()().
 * - @e T_return The return type of operator()().
 * - @e T_obj The object type.
 *
 * \ingroup qextMemberFunctor
 */
    template <
        typename T_return,
        typename T_obj,
        typename T_arg1,
        typename T_arg2,
        typename T_arg3,
        typename T_arg4,
        typename T_arg5,
        typename T_arg6,
        typename T_arg7 >
    class QEXTMemberFunctor7 : public QEXTFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7);
        typedef T_return Return;

        // Constructs an invalid functor.
        QEXTMemberFunctor7() : m_funcPtr(QEXT_DECL_NULLPTR) {}
        /** Constructs a QEXTMemberFunctor7 object that wraps the passed method.
     * \param func Pointer to method will be invoked from operator()().
     */
        QEXTMemberFunctor7(Function func) : m_funcPtr(func) {}
        QEXTMemberFunctor7(const QEXTMemberFunctor7 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped method operating on the passed instance.
     * \param obj Pointer to instance the method should operate on.
     * \param arg1 Argument to be passed on to the method.
     * \param arg2 Argument to be passed on to the method.
     * \param arg3 Argument to be passed on to the method.
     * \param arg4 Argument to be passed on to the method.
     * \param arg5 Argument to be passed on to the method.
     * \param arg6 Argument to be passed on to the method.
     * \param arg7 Argument to be passed on to the method.
     * \return The return value of the method invocation.
     */
        T_return operator()(
            T_obj *obj,
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4,
            typename QEXTTypeTrait< T_arg5 >::Take arg5,
            typename QEXTTypeTrait< T_arg6 >::Take arg6,
            typename QEXTTypeTrait< T_arg7 >::Take arg7) const
        {
            return (obj->*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        }

        /** Execute the wrapped method operating on the passed instance.
     * \param obj Reference to instance the method should operate on.
     * \param arg1 Argument to be passed on to the method.
     * \param arg2 Argument to be passed on to the method.
     * \param arg3 Argument to be passed on to the method.
     * \param arg4 Argument to be passed on to the method.
     * \param arg5 Argument to be passed on to the method.
     * \param arg6 Argument to be passed on to the method.
     * \param arg7 Argument to be passed on to the method.
     * \return The return value of the method invocation.
     */
        T_return operator()(
            T_obj &obj,
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4,
            typename QEXTTypeTrait< T_arg5 >::Take arg5,
            typename QEXTTypeTrait< T_arg6 >::Take arg6,
            typename QEXTTypeTrait< T_arg7 >::Take arg7) const
        {
            return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        }

    protected:
        Function m_funcPtr;
    };

    /** QEXTMemberFunctor6 wraps  methods with 6 argument(s).
 * Use the convenience function qextMemberFunctor() to create an instance of QEXTMemberFunctor6.
 *
 * The following template arguments are used:
 * - @e T_arg1 Argument type used in the definition of operator()().
 * - @e T_arg2 Argument type used in the definition of operator()().
 * - @e T_arg3 Argument type used in the definition of operator()().
 * - @e T_arg4 Argument type used in the definition of operator()().
 * - @e T_arg5 Argument type used in the definition of operator()().
 * - @e T_arg6 Argument type used in the definition of operator()().
 * - @e T_return The return type of operator()().
 * - @e T_obj The object type.
 *
 * \ingroup qextMemberFunctor
 */
    template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
    class QEXTMemberFunctor6 : public QEXTFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6);
        typedef T_return Return;

        // Constructs an invalid functor.
        QEXTMemberFunctor6() : m_funcPtr(QEXT_DECL_NULLPTR) {}
        /** Constructs a QEXTMemberFunctor6 object that wraps the passed method.
     * \param func Pointer to method will be invoked from operator()().
     */
        QEXTMemberFunctor6(Function func) : m_funcPtr(func) {}
        QEXTMemberFunctor6(const QEXTMemberFunctor6 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped method operating on the passed instance.
     * \param obj Pointer to instance the method should operate on.
     * \param arg1 Argument to be passed on to the method.
     * \param arg2 Argument to be passed on to the method.
     * \param arg3 Argument to be passed on to the method.
     * \param arg4 Argument to be passed on to the method.
     * \param arg5 Argument to be passed on to the method.
     * \param arg6 Argument to be passed on to the method.
     * \return The return value of the method invocation.
     */
        T_return operator()(
            T_obj *obj,
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4,
            typename QEXTTypeTrait< T_arg5 >::Take arg5,
            typename QEXTTypeTrait< T_arg6 >::Take arg6) const
        {
            return (obj->*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6);
        }

        /** Execute the wrapped method operating on the passed instance.
     * \param obj Reference to instance the method should operate on.
     * \param arg1 Argument to be passed on to the method.
     * \param arg2 Argument to be passed on to the method.
     * \param arg3 Argument to be passed on to the method.
     * \param arg4 Argument to be passed on to the method.
     * \param arg5 Argument to be passed on to the method.
     * \param arg6 Argument to be passed on to the method.
     * \return The return value of the method invocation.
     */
        T_return operator()(
            T_obj &obj,
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4,
            typename QEXTTypeTrait< T_arg5 >::Take arg5,
            typename QEXTTypeTrait< T_arg6 >::Take arg6) const
        {
            return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4, arg5, arg6);
        }

    protected:
        Function m_funcPtr;
    };

    /** QEXTMemberFunctor5 wraps  methods with 5 argument(s).
 * Use the convenience function qextMemberFunctor() to create an instance of QEXTMemberFunctor5.
 *
 * The following template arguments are used:
 * - @e T_arg1 Argument type used in the definition of operator()().
 * - @e T_arg2 Argument type used in the definition of operator()().
 * - @e T_arg3 Argument type used in the definition of operator()().
 * - @e T_arg4 Argument type used in the definition of operator()().
 * - @e T_arg5 Argument type used in the definition of operator()().
 * - @e T_return The return type of operator()().
 * - @e T_obj The object type.
 *
 * \ingroup qextMemberFunctor
 */
    template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
    class QEXTMemberFunctor5 : public QEXTFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5);
        typedef T_return Return;

        // Constructs an invalid functor.
        QEXTMemberFunctor5() : m_funcPtr(QEXT_DECL_NULLPTR) {}
        /** Constructs a QEXTMemberFunctor5 object that wraps the passed method.
     * \param func Pointer to method will be invoked from operator()().
     */
        QEXTMemberFunctor5(Function func) : m_funcPtr(func) {}
        QEXTMemberFunctor5(const QEXTMemberFunctor5 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped method operating on the passed instance.
     * \param obj Pointer to instance the method should operate on.
     * \param arg1 Argument to be passed on to the method.
     * \param arg2 Argument to be passed on to the method.
     * \param arg3 Argument to be passed on to the method.
     * \param arg4 Argument to be passed on to the method.
     * \param arg5 Argument to be passed on to the method.
     * \return The return value of the method invocation.
     */
        T_return operator()(
            T_obj *obj,
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4,
            typename QEXTTypeTrait< T_arg5 >::Take arg5) const
        {
            return (obj->*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5);
        }

        /** Execute the wrapped method operating on the passed instance.
     * \param obj Reference to instance the method should operate on.
     * \param arg1 Argument to be passed on to the method.
     * \param arg2 Argument to be passed on to the method.
     * \param arg3 Argument to be passed on to the method.
     * \param arg4 Argument to be passed on to the method.
     * \param arg5 Argument to be passed on to the method.
     * \return The return value of the method invocation.
     */
        T_return operator()(
            T_obj &obj,
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4,
            typename QEXTTypeTrait< T_arg5 >::Take arg5) const
        {
            return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4, arg5);
        }

    protected:
        Function m_funcPtr;
    };

    /** QEXTMemberFunctor4 wraps  methods with 4 argument(s).
 * Use the convenience function qextMemberFunctor() to create an instance of QEXTMemberFunctor4.
 *
 * The following template arguments are used:
 * - @e T_arg1 Argument type used in the definition of operator()().
 * - @e T_arg2 Argument type used in the definition of operator()().
 * - @e T_arg3 Argument type used in the definition of operator()().
 * - @e T_arg4 Argument type used in the definition of operator()().
 * - @e T_return The return type of operator()().
 * - @e T_obj The object type.
 *
 * \ingroup qextMemberFunctor
 */
    template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
    class QEXTMemberFunctor4 : public QEXTFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1, T_arg2, T_arg3, T_arg4);
        typedef T_return Return;

        // Constructs an invalid functor.
        QEXTMemberFunctor4() : m_funcPtr(QEXT_DECL_NULLPTR) {}
        /** Constructs a QEXTMemberFunctor4 object that wraps the passed method.
     * \param func Pointer to method will be invoked from operator()().
     */
        QEXTMemberFunctor4(Function func) : m_funcPtr(func) {}
        QEXTMemberFunctor4(const QEXTMemberFunctor4 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped method operating on the passed instance.
     * \param obj Pointer to instance the method should operate on.
     * \param arg1 Argument to be passed on to the method.
     * \param arg2 Argument to be passed on to the method.
     * \param arg3 Argument to be passed on to the method.
     * \param arg4 Argument to be passed on to the method.
     * \return The return value of the method invocation.
     */
        T_return operator()(
            T_obj *obj,
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4) const
        {
            return (obj->*(this->m_funcPtr))(arg1, arg2, arg3, arg4);
        }

        /** Execute the wrapped method operating on the passed instance.
     * \param obj Reference to instance the method should operate on.
     * \param arg1 Argument to be passed on to the method.
     * \param arg2 Argument to be passed on to the method.
     * \param arg3 Argument to be passed on to the method.
     * \param arg4 Argument to be passed on to the method.
     * \return The return value of the method invocation.
     */
        T_return operator()(
            T_obj &obj,
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4) const
        {
            return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4);
        }

    protected:
        Function m_funcPtr;
    };

    /** QEXTMemberFunctor3 wraps  methods with 3 argument(s).
 * Use the convenience function qextMemberFunctor() to create an instance of QEXTMemberFunctor3.
 *
 * The following template arguments are used:
 * - @e T_arg1 Argument type used in the definition of operator()().
 * - @e T_arg2 Argument type used in the definition of operator()().
 * - @e T_arg3 Argument type used in the definition of operator()().
 * - @e T_return The return type of operator()().
 * - @e T_obj The object type.
 *
 * \ingroup qextMemberFunctor
 */
    template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3 >
    class QEXTMemberFunctor3 : public QEXTFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1, T_arg2, T_arg3);
        typedef T_return Return;

        // Constructs an invalid functor.
        QEXTMemberFunctor3() : m_funcPtr(QEXT_DECL_NULLPTR) {}
        /** Constructs a QEXTMemberFunctor3 object that wraps the passed method.
     * \param func Pointer to method will be invoked from operator()().
     */
        QEXTMemberFunctor3(Function func) : m_funcPtr(func) {}
        QEXTMemberFunctor3(const QEXTMemberFunctor3 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped method operating on the passed instance.
     * \param obj Pointer to instance the method should operate on.
     * \param arg1 Argument to be passed on to the method.
     * \param arg2 Argument to be passed on to the method.
     * \param arg3 Argument to be passed on to the method.
     * \return The return value of the method invocation.
     */
        T_return operator()(
            T_obj *obj, typename QEXTTypeTrait< T_arg1 >::Take arg1, typename QEXTTypeTrait< T_arg2 >::Take arg2, typename QEXTTypeTrait< T_arg3 >::Take arg3) const
        {
            return (obj->*(this->m_funcPtr))(arg1, arg2, arg3);
        }

        /** Execute the wrapped method operating on the passed instance.
     * \param obj Reference to instance the method should operate on.
     * \param arg1 Argument to be passed on to the method.
     * \param arg2 Argument to be passed on to the method.
     * \param arg3 Argument to be passed on to the method.
     * \return The return value of the method invocation.
     */
        T_return operator()(
            T_obj &obj, typename QEXTTypeTrait< T_arg1 >::Take arg1, typename QEXTTypeTrait< T_arg2 >::Take arg2, typename QEXTTypeTrait< T_arg3 >::Take arg3) const
        {
            return (obj.*m_funcPtr)(arg1, arg2, arg3);
        }

    protected:
        Function m_funcPtr;
    };

    /** QEXTMemberFunctor2 wraps  methods with 2 argument(s).
 * Use the convenience function qextMemberFunctor() to create an instance of QEXTMemberFunctor2.
 *
 * The following template arguments are used:
 * - @e T_arg1 Argument type used in the definition of operator()().
 * - @e T_arg2 Argument type used in the definition of operator()().
 * - @e T_return The return type of operator()().
 * - @e T_obj The object type.
 *
 * \ingroup qextMemberFunctor
 */
    template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2 >
    class QEXTMemberFunctor2 : public QEXTFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1, T_arg2);
        typedef T_return Return;

        // Constructs an invalid functor.
        QEXTMemberFunctor2() : m_funcPtr(QEXT_DECL_NULLPTR) {}
        /** Constructs a QEXTMemberFunctor2 object that wraps the passed method.
     * \param func Pointer to method will be invoked from operator()().
     */
        QEXTMemberFunctor2(Function func) : m_funcPtr(func) {}
        QEXTMemberFunctor2(const QEXTMemberFunctor2 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped method operating on the passed instance.
     * \param obj Pointer to instance the method should operate on.
     * \param arg1 Argument to be passed on to the method.
     * \param arg2 Argument to be passed on to the method.
     * \return The return value of the method invocation.
     */
        T_return operator()(T_obj *obj, typename QEXTTypeTrait< T_arg1 >::Take arg1, typename QEXTTypeTrait< T_arg2 >::Take arg2) const
        {
            return (obj->*(this->m_funcPtr))(arg1, arg2);
        }

        /** Execute the wrapped method operating on the passed instance.
     * \param obj Reference to instance the method should operate on.
     * \param arg1 Argument to be passed on to the method.
     * \param arg2 Argument to be passed on to the method.
     * \return The return value of the method invocation.
     */
        T_return operator()(T_obj &obj, typename QEXTTypeTrait< T_arg1 >::Take arg1, typename QEXTTypeTrait< T_arg2 >::Take arg2) const
        {
            return (obj.*m_funcPtr)(arg1, arg2);
        }

    protected:
        Function m_funcPtr;
    };

    /** QEXTMemberFunctor1 wraps  methods with 1 argument(s).
 * Use the convenience function qextMemberFunctor() to create an instance of QEXTMemberFunctor1.
 *
 * The following template arguments are used:
 * - @e T_arg1 Argument type used in the definition of operator()().
 * - @e T_return The return type of operator()().
 * - @e T_obj The object type.
 *
 * \ingroup qextMemberFunctor
 */
    template < typename T_return, typename T_obj, typename T_arg1 >
    class QEXTMemberFunctor1 : public QEXTFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1);
        typedef T_return Return;

        // Constructs an invalid functor.
        QEXTMemberFunctor1() : m_funcPtr(QEXT_DECL_NULLPTR) {}
        /** Constructs a QEXTMemberFunctor1 object that wraps the passed method.
     * \param func Pointer to method will be invoked from operator()().
     */
        QEXTMemberFunctor1(Function func) : m_funcPtr(func) {}
        QEXTMemberFunctor1(const QEXTMemberFunctor1 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped method operating on the passed instance.
     * \param obj Pointer to instance the method should operate on.
     * \param arg1 Argument to be passed on to the method.
     * \return The return value of the method invocation.
     */
        T_return operator()(T_obj *obj, typename QEXTTypeTrait< T_arg1 >::Take arg1) const
        {
            return (obj->*(this->m_funcPtr))(arg1);
        }

        /** Execute the wrapped method operating on the passed instance.
     * \param obj Reference to instance the method should operate on.
     * \param arg1 Argument to be passed on to the method.
     * \return The return value of the method invocation.
     */
        T_return operator()(T_obj &obj, typename QEXTTypeTrait< T_arg1 >::Take arg1) const
        {
            return (obj.*m_funcPtr)(arg1);
        }

    protected:
        Function m_funcPtr;
    };

    /** QEXTMemberFunctor0 wraps  methods with 0 argument(s).
 * Use the convenience function qextMemberFunctor() to create an instance of QEXTMemberFunctor0.
 *
 * The following template arguments are used:
 * - @e T_return The return type of operator()().
 * - @e T_obj The object type.
 *
 * \ingroup qextMemberFunctor
 */
    template < typename T_return, typename T_obj >
    class QEXTMemberFunctor0 : public QEXTFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)();
        typedef T_return Return;

        // Constructs an invalid functor.
        QEXTMemberFunctor0() : m_funcPtr(QEXT_DECL_NULLPTR) {}
        /** Constructs a QEXTMemberFunctor0 object that wraps the passed method.
     * \param func Pointer to method will be invoked from operator()().
     */
        QEXTMemberFunctor0(Function func) : m_funcPtr(func) {}
        QEXTMemberFunctor0(const QEXTMemberFunctor0 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped method operating on the passed instance.
     * \param obj Pointer to instance the method should operate on.
     * \return The return value of the method invocation.
     */
        T_return operator()(T_obj *obj) const
        {
            return (obj->*(this->m_funcPtr))();
        }

        /** Execute the wrapped method operating on the passed instance.
     * \param obj Reference to instance the method should operate on.
     * \return The return value of the method invocation.
     */
        T_return operator()(T_obj &obj) const
        {
            return (obj.*m_funcPtr)();
        }

    protected:
        Function m_funcPtr;
    };

    /** QEXTConstMemberFunctor7 wraps const methods with 7 argument(s).
 * Use the convenience function qextMemberFunctor() to create an instance of QEXTConstMemberFunctor7.
 *
 * The following template arguments are used:
 * - @e T_arg1 Argument type used in the definition of operator()().
 * - @e T_arg2 Argument type used in the definition of operator()().
 * - @e T_arg3 Argument type used in the definition of operator()().
 * - @e T_arg4 Argument type used in the definition of operator()().
 * - @e T_arg5 Argument type used in the definition of operator()().
 * - @e T_arg6 Argument type used in the definition of operator()().
 * - @e T_arg7 Argument type used in the definition of operator()().
 * - @e T_return The return type of operator()().
 * - @e T_obj The object type.
 *
 * \ingroup qextMemberFunctor
 */
    template <
        typename T_return,
        typename T_obj,
        typename T_arg1,
        typename T_arg2,
        typename T_arg3,
        typename T_arg4,
        typename T_arg5,
        typename T_arg6,
        typename T_arg7 >
    class QEXTConstMemberFunctor7 : public QEXTFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const;
        typedef T_return Return;

        // Constructs an invalid functor.
        QEXTConstMemberFunctor7() : m_funcPtr(QEXT_DECL_NULLPTR) {}
        /** Constructs a QEXTConstMemberFunctor7 object that wraps the passed method.
     * \param func Pointer to method will be invoked from operator()().
     */
        QEXTConstMemberFunctor7(Function func) : m_funcPtr(func) {}
        QEXTConstMemberFunctor7(const QEXTConstMemberFunctor7 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped method operating on the passed instance.
     * \param obj Pointer to instance the method should operate on.
     * \param arg1 Argument to be passed on to the method.
     * \param arg2 Argument to be passed on to the method.
     * \param arg3 Argument to be passed on to the method.
     * \param arg4 Argument to be passed on to the method.
     * \param arg5 Argument to be passed on to the method.
     * \param arg6 Argument to be passed on to the method.
     * \param arg7 Argument to be passed on to the method.
     * \return The return value of the method invocation.
     */
        T_return operator()(
            const T_obj *obj,
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4,
            typename QEXTTypeTrait< T_arg5 >::Take arg5,
            typename QEXTTypeTrait< T_arg6 >::Take arg6,
            typename QEXTTypeTrait< T_arg7 >::Take arg7) const
        {
            return (obj->*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        }

        /** Execute the wrapped method operating on the passed instance.
     * \param obj Reference to instance the method should operate on.
     * \param arg1 Argument to be passed on to the method.
     * \param arg2 Argument to be passed on to the method.
     * \param arg3 Argument to be passed on to the method.
     * \param arg4 Argument to be passed on to the method.
     * \param arg5 Argument to be passed on to the method.
     * \param arg6 Argument to be passed on to the method.
     * \param arg7 Argument to be passed on to the method.
     * \return The return value of the method invocation.
     */
        T_return operator()(
            const T_obj &obj,
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4,
            typename QEXTTypeTrait< T_arg5 >::Take arg5,
            typename QEXTTypeTrait< T_arg6 >::Take arg6,
            typename QEXTTypeTrait< T_arg7 >::Take arg7) const
        {
            return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        }

    protected:
        Function m_funcPtr;
    };

    /** QEXTConstMemberFunctor6 wraps const methods with 6 argument(s).
 * Use the convenience function qextMemberFunctor() to create an instance of QEXTConstMemberFunctor6.
 *
 * The following template arguments are used:
 * - @e T_arg1 Argument type used in the definition of operator()().
 * - @e T_arg2 Argument type used in the definition of operator()().
 * - @e T_arg3 Argument type used in the definition of operator()().
 * - @e T_arg4 Argument type used in the definition of operator()().
 * - @e T_arg5 Argument type used in the definition of operator()().
 * - @e T_arg6 Argument type used in the definition of operator()().
 * - @e T_return The return type of operator()().
 * - @e T_obj The object type.
 *
 * \ingroup qextMemberFunctor
 */
    template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
    class QEXTConstMemberFunctor6 : public QEXTFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const;
        typedef T_return Return;

        // Constructs an invalid functor.
        QEXTConstMemberFunctor6() : m_funcPtr(QEXT_DECL_NULLPTR) {}
        /** Constructs a QEXTConstMemberFunctor6 object that wraps the passed method.
     * \param func Pointer to method will be invoked from operator()().
     */
        QEXTConstMemberFunctor6(Function func) : m_funcPtr(func) {}
        QEXTConstMemberFunctor6(const QEXTConstMemberFunctor6 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped method operating on the passed instance.
     * \param obj Pointer to instance the method should operate on.
     * \param arg1 Argument to be passed on to the method.
     * \param arg2 Argument to be passed on to the method.
     * \param arg3 Argument to be passed on to the method.
     * \param arg4 Argument to be passed on to the method.
     * \param arg5 Argument to be passed on to the method.
     * \param arg6 Argument to be passed on to the method.
     * \return The return value of the method invocation.
     */
        T_return operator()(
            const T_obj *obj,
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4,
            typename QEXTTypeTrait< T_arg5 >::Take arg5,
            typename QEXTTypeTrait< T_arg6 >::Take arg6) const
        {
            return (obj->*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6);
        }

        /** Execute the wrapped method operating on the passed instance.
     * \param obj Reference to instance the method should operate on.
     * \param arg1 Argument to be passed on to the method.
     * \param arg2 Argument to be passed on to the method.
     * \param arg3 Argument to be passed on to the method.
     * \param arg4 Argument to be passed on to the method.
     * \param arg5 Argument to be passed on to the method.
     * \param arg6 Argument to be passed on to the method.
     * \return The return value of the method invocation.
     */
        T_return operator()(
            const T_obj &obj,
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4,
            typename QEXTTypeTrait< T_arg5 >::Take arg5,
            typename QEXTTypeTrait< T_arg6 >::Take arg6) const
        {
            return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4, arg5, arg6);
        }

    protected:
        Function m_funcPtr;
    };

    /** QEXTConstMemberFunctor5 wraps const methods with 5 argument(s).
 * Use the convenience function qextMemberFunctor() to create an instance of QEXTConstMemberFunctor5.
 *
 * The following template arguments are used:
 * - @e T_arg1 Argument type used in the definition of operator()().
 * - @e T_arg2 Argument type used in the definition of operator()().
 * - @e T_arg3 Argument type used in the definition of operator()().
 * - @e T_arg4 Argument type used in the definition of operator()().
 * - @e T_arg5 Argument type used in the definition of operator()().
 * - @e T_return The return type of operator()().
 * - @e T_obj The object type.
 *
 * \ingroup qextMemberFunctor
 */
    template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
    class QEXTConstMemberFunctor5 : public QEXTFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const;
        typedef T_return Return;

        // Constructs an invalid functor.
        QEXTConstMemberFunctor5() : m_funcPtr(QEXT_DECL_NULLPTR) {}
        /** Constructs a QEXTConstMemberFunctor5 object that wraps the passed method.
     * \param func Pointer to method will be invoked from operator()().
     */
        QEXTConstMemberFunctor5(Function func) : m_funcPtr(func) {}
        QEXTConstMemberFunctor5(const QEXTConstMemberFunctor5 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped method operating on the passed instance.
     * \param obj Pointer to instance the method should operate on.
     * \param arg1 Argument to be passed on to the method.
     * \param arg2 Argument to be passed on to the method.
     * \param arg3 Argument to be passed on to the method.
     * \param arg4 Argument to be passed on to the method.
     * \param arg5 Argument to be passed on to the method.
     * \return The return value of the method invocation.
     */
        T_return operator()(
            const T_obj *obj,
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4,
            typename QEXTTypeTrait< T_arg5 >::Take arg5) const
        {
            return (obj->*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5);
        }

        /** Execute the wrapped method operating on the passed instance.
     * \param obj Reference to instance the method should operate on.
     * \param arg1 Argument to be passed on to the method.
     * \param arg2 Argument to be passed on to the method.
     * \param arg3 Argument to be passed on to the method.
     * \param arg4 Argument to be passed on to the method.
     * \param arg5 Argument to be passed on to the method.
     * \return The return value of the method invocation.
     */
        T_return operator()(
            const T_obj &obj,
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4,
            typename QEXTTypeTrait< T_arg5 >::Take arg5) const
        {
            return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4, arg5);
        }

    protected:
        Function m_funcPtr;
    };

    /** QEXTConstMemberFunctor4 wraps const methods with 4 argument(s).
 * Use the convenience function qextMemberFunctor() to create an instance of QEXTConstMemberFunctor4.
 *
 * The following template arguments are used:
 * - @e T_arg1 Argument type used in the definition of operator()().
 * - @e T_arg2 Argument type used in the definition of operator()().
 * - @e T_arg3 Argument type used in the definition of operator()().
 * - @e T_arg4 Argument type used in the definition of operator()().
 * - @e T_return The return type of operator()().
 * - @e T_obj The object type.
 *
 * \ingroup qextMemberFunctor
 */
    template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
    class QEXTConstMemberFunctor4 : public QEXTFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1, T_arg2, T_arg3, T_arg4) const;
        typedef T_return Return;

        // Constructs an invalid functor.
        QEXTConstMemberFunctor4() : m_funcPtr(QEXT_DECL_NULLPTR) {}
        /** Constructs a QEXTConstMemberFunctor4 object that wraps the passed method.
     * \param func Pointer to method will be invoked from operator()().
     */
        QEXTConstMemberFunctor4(Function func) : m_funcPtr(func) {}
        QEXTConstMemberFunctor4(const QEXTConstMemberFunctor4 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped method operating on the passed instance.
     * \param obj Pointer to instance the method should operate on.
     * \param arg1 Argument to be passed on to the method.
     * \param arg2 Argument to be passed on to the method.
     * \param arg3 Argument to be passed on to the method.
     * \param arg4 Argument to be passed on to the method.
     * \return The return value of the method invocation.
     */
        T_return operator()(
            const T_obj *obj,
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4) const
        {
            return (obj->*(this->m_funcPtr))(arg1, arg2, arg3, arg4);
        }

        /** Execute the wrapped method operating on the passed instance.
     * \param obj Reference to instance the method should operate on.
     * \param arg1 Argument to be passed on to the method.
     * \param arg2 Argument to be passed on to the method.
     * \param arg3 Argument to be passed on to the method.
     * \param arg4 Argument to be passed on to the method.
     * \return The return value of the method invocation.
     */
        T_return operator()(
            const T_obj &obj,
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4) const
        {
            return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4);
        }

    protected:
        Function m_funcPtr;
    };

    /** QEXTConstMemberFunctor3 wraps const methods with 3 argument(s).
 * Use the convenience function qextMemberFunctor() to create an instance of QEXTConstMemberFunctor3.
 *
 * The following template arguments are used:
 * - @e T_arg1 Argument type used in the definition of operator()().
 * - @e T_arg2 Argument type used in the definition of operator()().
 * - @e T_arg3 Argument type used in the definition of operator()().
 * - @e T_return The return type of operator()().
 * - @e T_obj The object type.
 *
 * \ingroup qextMemberFunctor
 */
    template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3 >
    class QEXTConstMemberFunctor3 : public QEXTFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1, T_arg2, T_arg3) const;
        typedef T_return Return;

        // Constructs an invalid functor.
        QEXTConstMemberFunctor3() : m_funcPtr(QEXT_DECL_NULLPTR) {}
        /** Constructs a QEXTConstMemberFunctor3 object that wraps the passed method.
     * \param func Pointer to method will be invoked from operator()().
     */
        QEXTConstMemberFunctor3(Function func) : m_funcPtr(func) {}
        QEXTConstMemberFunctor3(const QEXTConstMemberFunctor3 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped method operating on the passed instance.
     * \param obj Pointer to instance the method should operate on.
     * \param arg1 Argument to be passed on to the method.
     * \param arg2 Argument to be passed on to the method.
     * \param arg3 Argument to be passed on to the method.
     * \return The return value of the method invocation.
     */
        T_return operator()(
            const T_obj *obj,
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3) const
        {
            return (obj->*(this->m_funcPtr))(arg1, arg2, arg3);
        }

        /** Execute the wrapped method operating on the passed instance.
     * \param obj Reference to instance the method should operate on.
     * \param arg1 Argument to be passed on to the method.
     * \param arg2 Argument to be passed on to the method.
     * \param arg3 Argument to be passed on to the method.
     * \return The return value of the method invocation.
     */
        T_return operator()(
            const T_obj &obj,
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3) const
        {
            return (obj.*m_funcPtr)(arg1, arg2, arg3);
        }

    protected:
        Function m_funcPtr;
    };

    /** QEXTConstMemberFunctor2 wraps const methods with 2 argument(s).
 * Use the convenience function qextMemberFunctor() to create an instance of QEXTConstMemberFunctor2.
 *
 * The following template arguments are used:
 * - @e T_arg1 Argument type used in the definition of operator()().
 * - @e T_arg2 Argument type used in the definition of operator()().
 * - @e T_return The return type of operator()().
 * - @e T_obj The object type.
 *
 * \ingroup qextMemberFunctor
 */
    template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2 >
    class QEXTConstMemberFunctor2 : public QEXTFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1, T_arg2) const;
        typedef T_return Return;

        // Constructs an invalid functor.
        QEXTConstMemberFunctor2() : m_funcPtr(QEXT_DECL_NULLPTR) {}
        /** Constructs a QEXTConstMemberFunctor2 object that wraps the passed method.
     * \param func Pointer to method will be invoked from operator()().
     */
        QEXTConstMemberFunctor2(Function func) : m_funcPtr(func) {}
        QEXTConstMemberFunctor2(const QEXTConstMemberFunctor2 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped method operating on the passed instance.
     * \param obj Pointer to instance the method should operate on.
     * \param arg1 Argument to be passed on to the method.
     * \param arg2 Argument to be passed on to the method.
     * \return The return value of the method invocation.
     */
        T_return operator()(const T_obj *obj, typename QEXTTypeTrait< T_arg1 >::Take arg1, typename QEXTTypeTrait< T_arg2 >::Take arg2) const
        {
            return (obj->*(this->m_funcPtr))(arg1, arg2);
        }

        /** Execute the wrapped method operating on the passed instance.
     * \param obj Reference to instance the method should operate on.
     * \param arg1 Argument to be passed on to the method.
     * \param arg2 Argument to be passed on to the method.
     * \return The return value of the method invocation.
     */
        T_return operator()(const T_obj &obj, typename QEXTTypeTrait< T_arg1 >::Take arg1, typename QEXTTypeTrait< T_arg2 >::Take arg2) const
        {
            return (obj.*m_funcPtr)(arg1, arg2);
        }

    protected:
        Function m_funcPtr;
    };

    /** QEXTConstMemberFunctor1 wraps const methods with 1 argument(s).
 * Use the convenience function qextMemberFunctor() to create an instance of QEXTConstMemberFunctor1.
 *
 * The following template arguments are used:
 * - @e T_arg1 Argument type used in the definition of operator()().
 * - @e T_return The return type of operator()().
 * - @e T_obj The object type.
 *
 * \ingroup qextMemberFunctor
 */
    template < typename T_return, typename T_obj, typename T_arg1 >
    class QEXTConstMemberFunctor1 : public QEXTFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1) const;
        typedef T_return Return;

        // Constructs an invalid functor.
        QEXTConstMemberFunctor1() : m_funcPtr(QEXT_DECL_NULLPTR) {}
        /** Constructs a QEXTConstMemberFunctor1 object that wraps the passed method.
     * \param func Pointer to method will be invoked from operator()().
     */
        QEXTConstMemberFunctor1(Function func) : m_funcPtr(func) {}
        QEXTConstMemberFunctor1(const QEXTConstMemberFunctor1 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped method operating on the passed instance.
     * \param obj Pointer to instance the method should operate on.
     * \param arg1 Argument to be passed on to the method.
     * \return The return value of the method invocation.
     */
        T_return operator()(const T_obj *obj, typename QEXTTypeTrait< T_arg1 >::Take arg1) const
        {
            return (obj->*(this->m_funcPtr))(arg1);
        }

        /** Execute the wrapped method operating on the passed instance.
     * \param obj Reference to instance the method should operate on.
     * \param arg1 Argument to be passed on to the method.
     * \return The return value of the method invocation.
     */
        T_return operator()(const T_obj &obj, typename QEXTTypeTrait< T_arg1 >::Take arg1) const
        {
            return (obj.*m_funcPtr)(arg1);
        }

    protected:
        Function m_funcPtr;
    };

    /** QEXTConstMemberFunctor0 wraps const methods with 0 argument(s).
 * Use the convenience function qextMemberFunctor() to create an instance of QEXTConstMemberFunctor0.
 *
 * The following template arguments are used:
 * - @e T_return The return type of operator()().
 * - @e T_obj The object type.
 *
 * \ingroup qextMemberFunctor
 */
    template < typename T_return, typename T_obj >
    class QEXTConstMemberFunctor0 : public QEXTFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)() const;
        typedef T_return Return;

        // Constructs an invalid functor.
        QEXTConstMemberFunctor0() : m_funcPtr(QEXT_DECL_NULLPTR) {}
        /** Constructs a QEXTConstMemberFunctor0 object that wraps the passed method.
     * \param func Pointer to method will be invoked from operator()().
     */
        QEXTConstMemberFunctor0(Function func) : m_funcPtr(func) {}
        QEXTConstMemberFunctor0(const QEXTConstMemberFunctor0 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped method operating on the passed instance.
     * \param obj Pointer to instance the method should operate on.
     * \return The return value of the method invocation.
     */
        T_return operator()(const T_obj *obj) const
        {
            return (obj->*(this->m_funcPtr))();
        }

        /** Execute the wrapped method operating on the passed instance.
     * \param obj Reference to instance the method should operate on.
     * \return The return value of the method invocation.
     */
        T_return operator()(const T_obj &obj) const
        {
            return (obj.*m_funcPtr)();
        }

    protected:
        Function m_funcPtr;
    };

    /** QEXTVolatileMemberFunctor7 wraps volatile methods with 7 argument(s).
     * Use the convenience function qextMemberFunctor() to create an instance of QEXTVolatileMemberFunctor7.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_arg2 Argument type used in the definition of operator()().
     * - @e T_arg3 Argument type used in the definition of operator()().
     * - @e T_arg4 Argument type used in the definition of operator()().
     * - @e T_arg5 Argument type used in the definition of operator()().
     * - @e T_arg6 Argument type used in the definition of operator()().
     * - @e T_arg7 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template <
        typename T_return,
        typename T_obj,
        typename T_arg1,
        typename T_arg2,
        typename T_arg3,
        typename T_arg4,
        typename T_arg5,
        typename T_arg6,
        typename T_arg7 >
    class QEXTVolatileMemberFunctor7 : public QEXTFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) volatile;
        typedef T_return Return;

        // Constructs an invalid functor.
        QEXTVolatileMemberFunctor7() : m_funcPtr(QEXT_DECL_NULLPTR) {}
        /** Constructs a QEXTVolatileMemberFunctor7 object that wraps the passed method.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTVolatileMemberFunctor7(Function func) : m_funcPtr(func) {}
        QEXTVolatileMemberFunctor7(const QEXTVolatileMemberFunctor7 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped method operating on the passed instance.
         * \param obj Pointer to instance the method should operate on.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \param arg4 Argument to be passed on to the method.
         * \param arg5 Argument to be passed on to the method.
         * \param arg6 Argument to be passed on to the method.
         * \param arg7 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(
            T_obj *obj,
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4,
            typename QEXTTypeTrait< T_arg5 >::Take arg5,
            typename QEXTTypeTrait< T_arg6 >::Take arg6,
            typename QEXTTypeTrait< T_arg7 >::Take arg7) const
        {
            return (obj->*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        }

        /** Execute the wrapped method operating on the passed instance.
         * \param obj Reference to instance the method should operate on.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \param arg4 Argument to be passed on to the method.
         * \param arg5 Argument to be passed on to the method.
         * \param arg6 Argument to be passed on to the method.
         * \param arg7 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(
            T_obj &obj,
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4,
            typename QEXTTypeTrait< T_arg5 >::Take arg5,
            typename QEXTTypeTrait< T_arg6 >::Take arg6,
            typename QEXTTypeTrait< T_arg7 >::Take arg7) const
        {
            return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        }

    protected:
        Function m_funcPtr;
    };

    /** QEXTVolatileMemberFunctor6 wraps volatile methods with 6 argument(s).
     * Use the convenience function qextMemberFunctor() to create an instance of QEXTVolatileMemberFunctor6.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_arg2 Argument type used in the definition of operator()().
     * - @e T_arg3 Argument type used in the definition of operator()().
     * - @e T_arg4 Argument type used in the definition of operator()().
     * - @e T_arg5 Argument type used in the definition of operator()().
     * - @e T_arg6 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
    class QEXTVolatileMemberFunctor6 : public QEXTFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) volatile;
        typedef T_return Return;

        // Constructs an invalid functor.
        QEXTVolatileMemberFunctor6() : m_funcPtr(QEXT_DECL_NULLPTR) {}
        /** Constructs a QEXTVolatileMemberFunctor6 object that wraps the passed method.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTVolatileMemberFunctor6(Function func) : m_funcPtr(func) {}
        QEXTVolatileMemberFunctor6(const QEXTVolatileMemberFunctor6 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped method operating on the passed instance.
         * \param obj Pointer to instance the method should operate on.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \param arg4 Argument to be passed on to the method.
         * \param arg5 Argument to be passed on to the method.
         * \param arg6 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(
            T_obj *obj,
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4,
            typename QEXTTypeTrait< T_arg5 >::Take arg5,
            typename QEXTTypeTrait< T_arg6 >::Take arg6) const
        {
            return (obj->*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6);
        }

        /** Execute the wrapped method operating on the passed instance.
         * \param obj Reference to instance the method should operate on.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \param arg4 Argument to be passed on to the method.
         * \param arg5 Argument to be passed on to the method.
         * \param arg6 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(
            T_obj &obj,
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4,
            typename QEXTTypeTrait< T_arg5 >::Take arg5,
            typename QEXTTypeTrait< T_arg6 >::Take arg6) const
        {
            return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4, arg5, arg6);
        }

    protected:
        Function m_funcPtr;
    };

    /** QEXTVolatileMemberFunctor5 wraps volatile methods with 5 argument(s).
     * Use the convenience function qextMemberFunctor() to create an instance of QEXTVolatileMemberFunctor5.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_arg2 Argument type used in the definition of operator()().
     * - @e T_arg3 Argument type used in the definition of operator()().
     * - @e T_arg4 Argument type used in the definition of operator()().
     * - @e T_arg5 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
    class QEXTVolatileMemberFunctor5 : public QEXTFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) volatile;
        typedef T_return Return;

        // Constructs an invalid functor.
        QEXTVolatileMemberFunctor5() : m_funcPtr(QEXT_DECL_NULLPTR) {}
        /** Constructs a QEXTVolatileMemberFunctor5 object that wraps the passed method.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTVolatileMemberFunctor5(Function func) : m_funcPtr(func) {}
        QEXTVolatileMemberFunctor5(const QEXTVolatileMemberFunctor5 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped method operating on the passed instance.
         * \param obj Pointer to instance the method should operate on.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \param arg4 Argument to be passed on to the method.
         * \param arg5 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(
            T_obj *obj,
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4,
            typename QEXTTypeTrait< T_arg5 >::Take arg5) const
        {
            return (obj->*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5);
        }

        /** Execute the wrapped method operating on the passed instance.
         * \param obj Reference to instance the method should operate on.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \param arg4 Argument to be passed on to the method.
         * \param arg5 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(
            T_obj &obj,
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4,
            typename QEXTTypeTrait< T_arg5 >::Take arg5) const
        {
            return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4, arg5);
        }

    protected:
        Function m_funcPtr;
    };

    /** QEXTVolatileMemberFunctor4 wraps volatile methods with 4 argument(s).
     * Use the convenience function qextMemberFunctor() to create an instance of QEXTVolatileMemberFunctor4.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_arg2 Argument type used in the definition of operator()().
     * - @e T_arg3 Argument type used in the definition of operator()().
     * - @e T_arg4 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
    class QEXTVolatileMemberFunctor4 : public QEXTFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1, T_arg2, T_arg3, T_arg4) volatile;
        typedef T_return Return;

        // Constructs an invalid functor.
        QEXTVolatileMemberFunctor4() : m_funcPtr(QEXT_DECL_NULLPTR) {}
        /** Constructs a QEXTVolatileMemberFunctor4 object that wraps the passed method.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTVolatileMemberFunctor4(Function func) : m_funcPtr(func) {}
        QEXTVolatileMemberFunctor4(const QEXTVolatileMemberFunctor4 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped method operating on the passed instance.
         * \param obj Pointer to instance the method should operate on.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \param arg4 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(
            T_obj *obj,
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4) const
        {
            return (obj->*(this->m_funcPtr))(arg1, arg2, arg3, arg4);
        }

        /** Execute the wrapped method operating on the passed instance.
         * \param obj Reference to instance the method should operate on.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \param arg4 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(
            T_obj &obj,
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4) const
        {
            return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4);
        }

    protected:
        Function m_funcPtr;
    };

    /** QEXTVolatileMemberFunctor3 wraps volatile methods with 3 argument(s).
     * Use the convenience function qextMemberFunctor() to create an instance of QEXTVolatileMemberFunctor3.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_arg2 Argument type used in the definition of operator()().
     * - @e T_arg3 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3 >
    class QEXTVolatileMemberFunctor3 : public QEXTFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1, T_arg2, T_arg3) volatile;
        typedef T_return Return;

        // Constructs an invalid functor.
        QEXTVolatileMemberFunctor3() : m_funcPtr(QEXT_DECL_NULLPTR) {}
        /** Constructs a QEXTVolatileMemberFunctor3 object that wraps the passed method.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTVolatileMemberFunctor3(Function func) : m_funcPtr(func) {}
        QEXTVolatileMemberFunctor3(const QEXTVolatileMemberFunctor3 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped method operating on the passed instance.
         * \param obj Pointer to instance the method should operate on.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(
            T_obj *obj, typename QEXTTypeTrait< T_arg1 >::Take arg1, typename QEXTTypeTrait< T_arg2 >::Take arg2, typename QEXTTypeTrait< T_arg3 >::Take arg3) const
        {
            return (obj->*(this->m_funcPtr))(arg1, arg2, arg3);
        }

        /** Execute the wrapped method operating on the passed instance.
         * \param obj Reference to instance the method should operate on.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(
            T_obj &obj, typename QEXTTypeTrait< T_arg1 >::Take arg1, typename QEXTTypeTrait< T_arg2 >::Take arg2, typename QEXTTypeTrait< T_arg3 >::Take arg3) const
        {
            return (obj.*m_funcPtr)(arg1, arg2, arg3);
        }

    protected:
        Function m_funcPtr;
    };

    /** QEXTVolatileMemberFunctor2 wraps volatile methods with 2 argument(s).
     * Use the convenience function qextMemberFunctor() to create an instance of QEXTVolatileMemberFunctor2.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_arg2 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2 >
    class QEXTVolatileMemberFunctor2 : public QEXTFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1, T_arg2) volatile;
        typedef T_return Return;

        // Constructs an invalid functor.
        QEXTVolatileMemberFunctor2() : m_funcPtr(QEXT_DECL_NULLPTR) {}
        /** Constructs a QEXTVolatileMemberFunctor2 object that wraps the passed method.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTVolatileMemberFunctor2(Function func) : m_funcPtr(func) {}
        QEXTVolatileMemberFunctor2(const QEXTVolatileMemberFunctor2 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped method operating on the passed instance.
         * \param obj Pointer to instance the method should operate on.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(T_obj *obj, typename QEXTTypeTrait< T_arg1 >::Take arg1, typename QEXTTypeTrait< T_arg2 >::Take arg2) const
        {
            return (obj->*(this->m_funcPtr))(arg1, arg2);
        }

        /** Execute the wrapped method operating on the passed instance.
         * \param obj Reference to instance the method should operate on.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(T_obj &obj, typename QEXTTypeTrait< T_arg1 >::Take arg1, typename QEXTTypeTrait< T_arg2 >::Take arg2) const
        {
            return (obj.*m_funcPtr)(arg1, arg2);
        }

    protected:
        Function m_funcPtr;
    };

    /** QEXTVolatileMemberFunctor1 wraps volatile methods with 1 argument(s).
     * Use the convenience function qextMemberFunctor() to create an instance of QEXTVolatileMemberFunctor1.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template < typename T_return, typename T_obj, typename T_arg1 >
    class QEXTVolatileMemberFunctor1 : public QEXTFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1) volatile;
        typedef T_return Return;

        // Constructs an invalid functor.
        QEXTVolatileMemberFunctor1() : m_funcPtr(QEXT_DECL_NULLPTR) {}
        /** Constructs a QEXTVolatileMemberFunctor1 object that wraps the passed method.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTVolatileMemberFunctor1(Function func) : m_funcPtr(func) {}
        QEXTVolatileMemberFunctor1(const QEXTVolatileMemberFunctor1 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped method operating on the passed instance.
         * \param obj Pointer to instance the method should operate on.
         * \param arg1 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(T_obj *obj, typename QEXTTypeTrait< T_arg1 >::Take arg1) const
        {
            return (obj->*(this->m_funcPtr))(arg1);
        }

        /** Execute the wrapped method operating on the passed instance.
         * \param obj Reference to instance the method should operate on.
         * \param arg1 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(T_obj &obj, typename QEXTTypeTrait< T_arg1 >::Take arg1) const
        {
            return (obj.*m_funcPtr)(arg1);
        }

    protected:
        Function m_funcPtr;
    };

    /** QEXTVolatileMemberFunctor0 wraps volatile methods with 0 argument(s).
     * Use the convenience function qextMemberFunctor() to create an instance of QEXTVolatileMemberFunctor0.
     *
     * The following template arguments are used:
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template < typename T_return, typename T_obj >
    class QEXTVolatileMemberFunctor0 : public QEXTFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)() volatile;
        typedef T_return Return;

        // Constructs an invalid functor.
        QEXTVolatileMemberFunctor0() : m_funcPtr(QEXT_DECL_NULLPTR) {}
        /** Constructs a QEXTVolatileMemberFunctor0 object that wraps the passed method.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTVolatileMemberFunctor0(Function func) : m_funcPtr(func) {}
        QEXTVolatileMemberFunctor0(const QEXTVolatileMemberFunctor0 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped method operating on the passed instance.
         * \param obj Pointer to instance the method should operate on.
         * \return The return value of the method invocation.
         */
        T_return operator()(T_obj *obj) const
        {
            return (obj->*(this->m_funcPtr))();
        }

        /** Execute the wrapped method operating on the passed instance.
         * \param obj Reference to instance the method should operate on.
         * \return The return value of the method invocation.
         */
        T_return operator()(T_obj &obj) const
        {
            return (obj.*m_funcPtr)();
        }

    protected:
        Function m_funcPtr;
    };

    /** QEXTConstVolatileMemberFunctor7 wraps const volatile methods with 7 argument(s).
     * Use the convenience function qextMemberFunctor() to create an instance of QEXTConstVolatileMemberFunctor7.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_arg2 Argument type used in the definition of operator()().
     * - @e T_arg3 Argument type used in the definition of operator()().
     * - @e T_arg4 Argument type used in the definition of operator()().
     * - @e T_arg5 Argument type used in the definition of operator()().
     * - @e T_arg6 Argument type used in the definition of operator()().
     * - @e T_arg7 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template <
        typename T_return,
        typename T_obj,
        typename T_arg1,
        typename T_arg2,
        typename T_arg3,
        typename T_arg4,
        typename T_arg5,
        typename T_arg6,
        typename T_arg7 >
    class QEXTConstVolatileMemberFunctor7 : public QEXTFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const volatile;
        typedef T_return Return;

        // Constructs an invalid functor.
        QEXTConstVolatileMemberFunctor7() : m_funcPtr(QEXT_DECL_NULLPTR) {}
        /** Constructs a QEXTConstVolatileMemberFunctor7 object that wraps the passed method.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTConstVolatileMemberFunctor7(Function func) : m_funcPtr(func) {}
        QEXTConstVolatileMemberFunctor7(const QEXTConstVolatileMemberFunctor7 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped method operating on the passed instance.
         * \param obj Pointer to instance the method should operate on.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \param arg4 Argument to be passed on to the method.
         * \param arg5 Argument to be passed on to the method.
         * \param arg6 Argument to be passed on to the method.
         * \param arg7 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(
            const T_obj *obj,
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4,
            typename QEXTTypeTrait< T_arg5 >::Take arg5,
            typename QEXTTypeTrait< T_arg6 >::Take arg6,
            typename QEXTTypeTrait< T_arg7 >::Take arg7) const
        {
            return (obj->*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        }

        /** Execute the wrapped method operating on the passed instance.
         * \param obj Reference to instance the method should operate on.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \param arg4 Argument to be passed on to the method.
         * \param arg5 Argument to be passed on to the method.
         * \param arg6 Argument to be passed on to the method.
         * \param arg7 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(
            const T_obj &obj,
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4,
            typename QEXTTypeTrait< T_arg5 >::Take arg5,
            typename QEXTTypeTrait< T_arg6 >::Take arg6,
            typename QEXTTypeTrait< T_arg7 >::Take arg7) const
        {
            return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        }

    protected:
        Function m_funcPtr;
    };

    /** QEXTConstVolatileMemberFunctor6 wraps const volatile methods with 6 argument(s).
     * Use the convenience function qextMemberFunctor() to create an instance of QEXTConstVolatileMemberFunctor6.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_arg2 Argument type used in the definition of operator()().
     * - @e T_arg3 Argument type used in the definition of operator()().
     * - @e T_arg4 Argument type used in the definition of operator()().
     * - @e T_arg5 Argument type used in the definition of operator()().
     * - @e T_arg6 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
    class QEXTConstVolatileMemberFunctor6 : public QEXTFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const volatile;
        typedef T_return Return;

        // Constructs an invalid functor.
        QEXTConstVolatileMemberFunctor6() : m_funcPtr(QEXT_DECL_NULLPTR) {}
        /** Constructs a QEXTConstVolatileMemberFunctor6 object that wraps the passed method.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTConstVolatileMemberFunctor6(Function func) : m_funcPtr(func) {}
        QEXTConstVolatileMemberFunctor6(const QEXTConstVolatileMemberFunctor6 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped method operating on the passed instance.
         * \param obj Pointer to instance the method should operate on.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \param arg4 Argument to be passed on to the method.
         * \param arg5 Argument to be passed on to the method.
         * \param arg6 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(
            const T_obj *obj,
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4,
            typename QEXTTypeTrait< T_arg5 >::Take arg5,
            typename QEXTTypeTrait< T_arg6 >::Take arg6) const
        {
            return (obj->*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6);
        }

        /** Execute the wrapped method operating on the passed instance.
         * \param obj Reference to instance the method should operate on.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \param arg4 Argument to be passed on to the method.
         * \param arg5 Argument to be passed on to the method.
         * \param arg6 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(
            const T_obj &obj,
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4,
            typename QEXTTypeTrait< T_arg5 >::Take arg5,
            typename QEXTTypeTrait< T_arg6 >::Take arg6) const
        {
            return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4, arg5, arg6);
        }

    protected:
        Function m_funcPtr;
    };

    /** QEXTConstVolatileMemberFunctor5 wraps const volatile methods with 5 argument(s).
     * Use the convenience function qextMemberFunctor() to create an instance of QEXTConstVolatileMemberFunctor5.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_arg2 Argument type used in the definition of operator()().
     * - @e T_arg3 Argument type used in the definition of operator()().
     * - @e T_arg4 Argument type used in the definition of operator()().
     * - @e T_arg5 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
    class QEXTConstVolatileMemberFunctor5 : public QEXTFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const volatile;
        typedef T_return Return;

        // Constructs an invalid functor.
        QEXTConstVolatileMemberFunctor5() : m_funcPtr(QEXT_DECL_NULLPTR) {}
        /** Constructs a QEXTConstVolatileMemberFunctor5 object that wraps the passed method.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTConstVolatileMemberFunctor5(Function func) : m_funcPtr(func) {}
        QEXTConstVolatileMemberFunctor5(const QEXTConstVolatileMemberFunctor5 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped method operating on the passed instance.
         * \param obj Pointer to instance the method should operate on.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \param arg4 Argument to be passed on to the method.
         * \param arg5 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(
            const T_obj *obj,
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4,
            typename QEXTTypeTrait< T_arg5 >::Take arg5) const
        {
            return (obj->*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5);
        }

        /** Execute the wrapped method operating on the passed instance.
         * \param obj Reference to instance the method should operate on.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \param arg4 Argument to be passed on to the method.
         * \param arg5 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(
            const T_obj &obj,
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4,
            typename QEXTTypeTrait< T_arg5 >::Take arg5) const
        {
            return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4, arg5);
        }

    protected:
        Function m_funcPtr;
    };

    /** QEXTConstVolatileMemberFunctor4 wraps const volatile methods with 4 argument(s).
     * Use the convenience function qextMemberFunctor() to create an instance of QEXTConstVolatileMemberFunctor4.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_arg2 Argument type used in the definition of operator()().
     * - @e T_arg3 Argument type used in the definition of operator()().
     * - @e T_arg4 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
    class QEXTConstVolatileMemberFunctor4 : public QEXTFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1, T_arg2, T_arg3, T_arg4) const volatile;
        typedef T_return Return;

        // Constructs an invalid functor.
        QEXTConstVolatileMemberFunctor4() : m_funcPtr(QEXT_DECL_NULLPTR) {}
        /** Constructs a QEXTConstVolatileMemberFunctor4 object that wraps the passed method.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTConstVolatileMemberFunctor4(Function func) : m_funcPtr(func) {}
        QEXTConstVolatileMemberFunctor4(const QEXTConstVolatileMemberFunctor4 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped method operating on the passed instance.
         * \param obj Pointer to instance the method should operate on.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \param arg4 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(
            const T_obj *obj,
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4) const
        {
            return (obj->*(this->m_funcPtr))(arg1, arg2, arg3, arg4);
        }

        /** Execute the wrapped method operating on the passed instance.
         * \param obj Reference to instance the method should operate on.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \param arg4 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(
            const T_obj &obj,
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4) const
        {
            return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4);
        }

    protected:
        Function m_funcPtr;
    };

    /** QEXTConstVolatileMemberFunctor3 wraps const volatile methods with 3 argument(s).
     * Use the convenience function qextMemberFunctor() to create an instance of QEXTConstVolatileMemberFunctor3.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_arg2 Argument type used in the definition of operator()().
     * - @e T_arg3 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3 >
    class QEXTConstVolatileMemberFunctor3 : public QEXTFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1, T_arg2, T_arg3) const volatile;
        typedef T_return Return;

        // Constructs an invalid functor.
        QEXTConstVolatileMemberFunctor3() : m_funcPtr(QEXT_DECL_NULLPTR) {}
        /** Constructs a QEXTConstVolatileMemberFunctor3 object that wraps the passed method.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTConstVolatileMemberFunctor3(Function func) : m_funcPtr(func) {}
        QEXTConstVolatileMemberFunctor3(const QEXTConstVolatileMemberFunctor3 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped method operating on the passed instance.
         * \param obj Pointer to instance the method should operate on.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(
            const T_obj *obj,
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3) const
        {
            return (obj->*(this->m_funcPtr))(arg1, arg2, arg3);
        }

        /** Execute the wrapped method operating on the passed instance.
         * \param obj Reference to instance the method should operate on.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(
            const T_obj &obj,
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3) const
        {
            return (obj.*m_funcPtr)(arg1, arg2, arg3);
        }

    protected:
        Function m_funcPtr;
    };

    /** QEXTConstVolatileMemberFunctor2 wraps const volatile methods with 2 argument(s).
     * Use the convenience function qextMemberFunctor() to create an instance of QEXTConstVolatileMemberFunctor2.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_arg2 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2 >
    class QEXTConstVolatileMemberFunctor2 : public QEXTFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1, T_arg2) const volatile;
        typedef T_return Return;

        // Constructs an invalid functor.
        QEXTConstVolatileMemberFunctor2() : m_funcPtr(QEXT_DECL_NULLPTR) {}
        /** Constructs a QEXTConstVolatileMemberFunctor2 object that wraps the passed method.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTConstVolatileMemberFunctor2(Function func) : m_funcPtr(func) {}
        QEXTConstVolatileMemberFunctor2(const QEXTConstVolatileMemberFunctor2 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped method operating on the passed instance.
         * \param obj Pointer to instance the method should operate on.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(const T_obj *obj, typename QEXTTypeTrait< T_arg1 >::Take arg1, typename QEXTTypeTrait< T_arg2 >::Take arg2) const
        {
            return (obj->*(this->m_funcPtr))(arg1, arg2);
        }

        /** Execute the wrapped method operating on the passed instance.
         * \param obj Reference to instance the method should operate on.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(const T_obj &obj, typename QEXTTypeTrait< T_arg1 >::Take arg1, typename QEXTTypeTrait< T_arg2 >::Take arg2) const
        {
            return (obj.*m_funcPtr)(arg1, arg2);
        }

    protected:
        Function m_funcPtr;
    };

    /** QEXTConstVolatileMemberFunctor1 wraps const volatile methods with 1 argument(s).
     * Use the convenience function qextMemberFunctor() to create an instance of QEXTConstVolatileMemberFunctor1.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template < typename T_return, typename T_obj, typename T_arg1 >
    class QEXTConstVolatileMemberFunctor1 : public QEXTFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1) const volatile;
        typedef T_return Return;

        // Constructs an invalid functor.
        QEXTConstVolatileMemberFunctor1() : m_funcPtr(QEXT_DECL_NULLPTR) {}
        /** Constructs a QEXTConstVolatileMemberFunctor1 object that wraps the passed method.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTConstVolatileMemberFunctor1(Function func) : m_funcPtr(func) {}
        QEXTConstVolatileMemberFunctor1(const QEXTConstVolatileMemberFunctor1 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped method operating on the passed instance.
         * \param obj Pointer to instance the method should operate on.
         * \param arg1 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(const T_obj *obj, typename QEXTTypeTrait< T_arg1 >::Take arg1) const
        {
            return (obj->*(this->m_funcPtr))(arg1);
        }

        /** Execute the wrapped method operating on the passed instance.
         * \param obj Reference to instance the method should operate on.
         * \param arg1 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(const T_obj &obj, typename QEXTTypeTrait< T_arg1 >::Take arg1) const
        {
            return (obj.*m_funcPtr)(arg1);
        }

    protected:
        Function m_funcPtr;
    };

    /** QEXTConstVolatileMemberFunctor0 wraps const volatile methods with 0 argument(s).
     * Use the convenience function qextMemberFunctor() to create an instance of QEXTConstVolatileMemberFunctor0.
     *
     * The following template arguments are used:
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template < typename T_return, typename T_obj >
    class QEXTConstVolatileMemberFunctor0 : public QEXTFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)() const volatile;
        typedef T_return Return;

        // Constructs an invalid functor.
        QEXTConstVolatileMemberFunctor0() : m_funcPtr(QEXT_DECL_NULLPTR) {}
        /** Constructs a QEXTConstVolatileMemberFunctor0 object that wraps the passed method.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTConstVolatileMemberFunctor0(Function func) : m_funcPtr(func) {}
        QEXTConstVolatileMemberFunctor0(const QEXTConstVolatileMemberFunctor0 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped method operating on the passed instance.
         * \param obj Pointer to instance the method should operate on.
         * \return The return value of the method invocation.
         */
        T_return operator()(const T_obj *obj) const
        {
            return (obj->*(this->m_funcPtr))();
        }

        /** Execute the wrapped method operating on the passed instance.
         * \param obj Reference to instance the method should operate on.
         * \return The return value of the method invocation.
         */
        T_return operator()(const T_obj &obj) const
        {
            return (obj.*m_funcPtr)();
        }

    protected:
        Function m_funcPtr;
    };

    /** QEXTBoundMemberFunctor7 encapsulates a  method with 7 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QEXTBoundMemberFunctor7.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_arg2 Argument type used in the definition of operator()().
     * - @e T_arg3 Argument type used in the definition of operator()().
     * - @e T_arg4 Argument type used in the definition of operator()().
     * - @e T_arg5 Argument type used in the definition of operator()().
     * - @e T_arg6 Argument type used in the definition of operator()().
     * - @e T_arg7 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template <
        typename T_return,
        typename T_obj,
        typename T_arg1,
        typename T_arg2,
        typename T_arg3,
        typename T_arg4,
        typename T_arg5,
        typename T_arg6,
        typename T_arg7 >
    class QEXTBoundMemberFunctor7 : public QEXTMemberFunctor7< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
    {
        typedef QEXTMemberFunctor7< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 > Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QEXTBoundMemberFunctor7 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundMemberFunctor7(T_obj *obj, Function func) : Base(func), m_obj(*obj) {}
        /** Constructs a QEXTBoundMemberFunctor7 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundMemberFunctor7(T_obj &obj, Function func) : Base(func), m_obj(obj) {}
        QEXTBoundMemberFunctor7(const QEXTBoundMemberFunctor7 &other) : Base(other.m_funcPtr), m_obj(other.m_obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \param arg4 Argument to be passed on to the method.
         * \param arg5 Argument to be passed on to the method.
         * \param arg6 Argument to be passed on to the method.
         * \param arg7 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4,
            typename QEXTTypeTrait< T_arg5 >::Take arg5,
            typename QEXTTypeTrait< T_arg6 >::Take arg6,
            typename QEXTTypeTrait< T_arg7 >::Take arg7) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QEXTLimitReference< T_obj > m_obj;
    };


    /** QEXTBoundMemberFunctor6 encapsulates a  method with 6 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QEXTBoundMemberFunctor6.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_arg2 Argument type used in the definition of operator()().
     * - @e T_arg3 Argument type used in the definition of operator()().
     * - @e T_arg4 Argument type used in the definition of operator()().
     * - @e T_arg5 Argument type used in the definition of operator()().
     * - @e T_arg6 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
    class QEXTBoundMemberFunctor6 : public QEXTMemberFunctor6< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
    {
        typedef QEXTMemberFunctor6< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 > Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QEXTBoundMemberFunctor6 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundMemberFunctor6(T_obj *obj, Function func) : Base(func), m_obj(*obj) {}
        /** Constructs a QEXTBoundMemberFunctor6 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundMemberFunctor6(T_obj &obj, Function func) : Base(func), m_obj(obj) {}
        QEXTBoundMemberFunctor6(const QEXTBoundMemberFunctor6 &other) : Base(other.m_funcPtr), m_obj(other.m_obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \param arg4 Argument to be passed on to the method.
         * \param arg5 Argument to be passed on to the method.
         * \param arg6 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4,
            typename QEXTTypeTrait< T_arg5 >::Take arg5,
            typename QEXTTypeTrait< T_arg6 >::Take arg6) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QEXTLimitReference< T_obj > m_obj;
    };

    /** QEXTBoundMemberFunctor5 encapsulates a  method with 5 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QEXTBoundMemberFunctor5.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_arg2 Argument type used in the definition of operator()().
     * - @e T_arg3 Argument type used in the definition of operator()().
     * - @e T_arg4 Argument type used in the definition of operator()().
     * - @e T_arg5 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
    class QEXTBoundMemberFunctor5 : public QEXTMemberFunctor5< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
    {
        typedef QEXTMemberFunctor5< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 > Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QEXTBoundMemberFunctor5 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundMemberFunctor5(T_obj *obj, Function func) : Base(func), m_obj(*obj) {}
        /** Constructs a QEXTBoundMemberFunctor5 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundMemberFunctor5(T_obj &obj, Function func) : Base(func), m_obj(obj) {}
        QEXTBoundMemberFunctor5(const QEXTBoundMemberFunctor5 &other) : Base(other.m_funcPtr), m_obj(other.m_obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \param arg4 Argument to be passed on to the method.
         * \param arg5 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4,
            typename QEXTTypeTrait< T_arg5 >::Take arg5) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QEXTLimitReference< T_obj > m_obj;
    };

    /** QEXTBoundMemberFunctor4 encapsulates a  method with 4 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QEXTBoundMemberFunctor4.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_arg2 Argument type used in the definition of operator()().
     * - @e T_arg3 Argument type used in the definition of operator()().
     * - @e T_arg4 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
    class QEXTBoundMemberFunctor4 : public QEXTMemberFunctor4< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >
    {
        typedef QEXTMemberFunctor4< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 > Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QEXTBoundMemberFunctor4 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundMemberFunctor4(T_obj *obj, Function func) : Base(func), m_obj(*obj) {}
        /** Constructs a QEXTBoundMemberFunctor4 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundMemberFunctor4(T_obj &obj, Function func) : Base(func), m_obj(obj) {}
        QEXTBoundMemberFunctor4(const QEXTBoundMemberFunctor4 &other) : Base(other.m_funcPtr), m_obj(other.m_obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \param arg4 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QEXTLimitReference< T_obj > m_obj;
    };

    /** QEXTBoundMemberFunctor3 encapsulates a  method with 3 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QEXTBoundMemberFunctor3.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_arg2 Argument type used in the definition of operator()().
     * - @e T_arg3 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3 >
    class QEXTBoundMemberFunctor3 : public QEXTMemberFunctor3< T_return, T_obj, T_arg1, T_arg2, T_arg3 >
    {
        typedef QEXTMemberFunctor3< T_return, T_obj, T_arg1, T_arg2, T_arg3 > Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QEXTBoundMemberFunctor3 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundMemberFunctor3(T_obj *obj, Function func) : Base(func), m_obj(*obj) {}
        /** Constructs a QEXTBoundMemberFunctor3 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundMemberFunctor3(T_obj &obj, Function func) : Base(func), m_obj(obj) {}
        QEXTBoundMemberFunctor3(const QEXTBoundMemberFunctor3 &other) : Base(other.m_funcPtr), m_obj(other.m_obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return
        operator()(typename QEXTTypeTrait< T_arg1 >::Take arg1, typename QEXTTypeTrait< T_arg2 >::Take arg2, typename QEXTTypeTrait< T_arg3 >::Take arg3) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QEXTLimitReference< T_obj > m_obj;
    };

    /** QEXTBoundMemberFunctor2 encapsulates a  method with 2 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QEXTBoundMemberFunctor2.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_arg2 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2 >
    class QEXTBoundMemberFunctor2 : public QEXTMemberFunctor2< T_return, T_obj, T_arg1, T_arg2 >
    {
        typedef QEXTMemberFunctor2< T_return, T_obj, T_arg1, T_arg2 > Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QEXTBoundMemberFunctor2 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundMemberFunctor2(T_obj *obj, Function func) : Base(func), m_obj(*obj) {}
        /** Constructs a QEXTBoundMemberFunctor2 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundMemberFunctor2(T_obj &obj, Function func) : Base(func), m_obj(obj) {}
        QEXTBoundMemberFunctor2(const QEXTBoundMemberFunctor2 &other) : Base(other.m_funcPtr), m_obj(other.m_obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(typename QEXTTypeTrait< T_arg1 >::Take arg1, typename QEXTTypeTrait< T_arg2 >::Take arg2) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QEXTLimitReference< T_obj > m_obj;
    };

    /** QEXTBoundMemberFunctor1 encapsulates a  method with 1 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QEXTBoundMemberFunctor1.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template < typename T_return, typename T_obj, typename T_arg1 >
    class QEXTBoundMemberFunctor1 : public QEXTMemberFunctor1< T_return, T_obj, T_arg1 >
    {
        typedef QEXTMemberFunctor1< T_return, T_obj, T_arg1 > Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QEXTBoundMemberFunctor1 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundMemberFunctor1(T_obj *obj, Function func) : Base(func), m_obj(*obj) {}
        /** Constructs a QEXTBoundMemberFunctor1 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundMemberFunctor1(T_obj &obj, Function func) : Base(func), m_obj(obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \param arg1 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(typename QEXTTypeTrait< T_arg1 >::Take arg1) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QEXTLimitReference< T_obj > m_obj;
    };

    /** QEXTBoundMemberFunctor0 encapsulates a  method with 0 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QEXTBoundMemberFunctor0.
     *
     * The following template arguments are used:
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template < typename T_return, typename T_obj >
    class QEXTBoundMemberFunctor0 : public QEXTMemberFunctor0< T_return, T_obj >
    {
        typedef QEXTMemberFunctor0< T_return, T_obj > Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QEXTBoundMemberFunctor0 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundMemberFunctor0(T_obj *obj, Function func) : Base(func), m_obj(*obj) {}
        /** Constructs a QEXTBoundMemberFunctor0 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundMemberFunctor0(T_obj &obj, Function func) : Base(func), m_obj(obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \return The return value of the method invocation.
         */
        T_return operator()() const
        {
            return (m_obj.invoke().*(this->m_funcPtr))();
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QEXTLimitReference< T_obj > m_obj;
    };

    /** QEXTBoundConstMemberFunctor7 encapsulates a const method with 7 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QEXTBoundConstMemberFunctor7.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_arg2 Argument type used in the definition of operator()().
     * - @e T_arg3 Argument type used in the definition of operator()().
     * - @e T_arg4 Argument type used in the definition of operator()().
     * - @e T_arg5 Argument type used in the definition of operator()().
     * - @e T_arg6 Argument type used in the definition of operator()().
     * - @e T_arg7 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template <
        typename T_return,
        typename T_obj,
        typename T_arg1,
        typename T_arg2,
        typename T_arg3,
        typename T_arg4,
        typename T_arg5,
        typename T_arg6,
        typename T_arg7 >
    class QEXTBoundConstMemberFunctor7 : public QEXTConstMemberFunctor7< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
    {
        typedef QEXTConstMemberFunctor7< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 > Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QEXTBoundConstMemberFunctor7 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundConstMemberFunctor7(const T_obj *obj, Function func) : Base(func), m_obj(*obj) {}
        /** Constructs a QEXTBoundConstMemberFunctor7 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundConstMemberFunctor7(const T_obj &obj, Function func) : Base(func), m_obj(obj) {}
        QEXTBoundConstMemberFunctor7(const QEXTBoundConstMemberFunctor7 &other) : Base(other.m_funcPtr), m_obj(other.m_obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \param arg4 Argument to be passed on to the method.
         * \param arg5 Argument to be passed on to the method.
         * \param arg6 Argument to be passed on to the method.
         * \param arg7 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4,
            typename QEXTTypeTrait< T_arg5 >::Take arg5,
            typename QEXTTypeTrait< T_arg6 >::Take arg6,
            typename QEXTTypeTrait< T_arg7 >::Take arg7) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QEXTConstLimitReference< T_obj > m_obj;
    };

    /** QEXTBoundConstMemberFunctor6 encapsulates a const method with 6 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QEXTBoundConstMemberFunctor6.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_arg2 Argument type used in the definition of operator()().
     * - @e T_arg3 Argument type used in the definition of operator()().
     * - @e T_arg4 Argument type used in the definition of operator()().
     * - @e T_arg5 Argument type used in the definition of operator()().
     * - @e T_arg6 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
    class QEXTBoundConstMemberFunctor6 : public QEXTConstMemberFunctor6< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
    {
        typedef QEXTConstMemberFunctor6< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 > Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QEXTBoundConstMemberFunctor6 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundConstMemberFunctor6(const T_obj *obj, Function func) : Base(func), m_obj(*obj) {}
        /** Constructs a QEXTBoundConstMemberFunctor6 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundConstMemberFunctor6(const T_obj &obj, Function func) : Base(func), m_obj(obj) {}
        QEXTBoundConstMemberFunctor6(const QEXTBoundConstMemberFunctor6 &other) : Base(other.m_funcPtr), m_obj(other.m_obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \param arg4 Argument to be passed on to the method.
         * \param arg5 Argument to be passed on to the method.
         * \param arg6 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4,
            typename QEXTTypeTrait< T_arg5 >::Take arg5,
            typename QEXTTypeTrait< T_arg6 >::Take arg6) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QEXTConstLimitReference< T_obj > m_obj;
    };

    /** QEXTBoundConstMemberFunctor5 encapsulates a const method with 5 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QEXTBoundConstMemberFunctor5.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_arg2 Argument type used in the definition of operator()().
     * - @e T_arg3 Argument type used in the definition of operator()().
     * - @e T_arg4 Argument type used in the definition of operator()().
     * - @e T_arg5 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
    class QEXTBoundConstMemberFunctor5 : public QEXTConstMemberFunctor5< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
    {
        typedef QEXTConstMemberFunctor5< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 > Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QEXTBoundConstMemberFunctor5 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundConstMemberFunctor5(const T_obj *obj, Function func) : Base(func), m_obj(*obj) {}
        /** Constructs a QEXTBoundConstMemberFunctor5 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundConstMemberFunctor5(const T_obj &obj, Function func) : Base(func), m_obj(obj) {}
        QEXTBoundConstMemberFunctor5(const QEXTBoundConstMemberFunctor5 &other) : Base(other.m_funcPtr), m_obj(other.m_obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \param arg4 Argument to be passed on to the method.
         * \param arg5 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4,
            typename QEXTTypeTrait< T_arg5 >::Take arg5) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QEXTConstLimitReference< T_obj > m_obj;
    };

    /** QEXTBoundConstMemberFunctor4 encapsulates a const method with 4 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QEXTBoundConstMemberFunctor4.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_arg2 Argument type used in the definition of operator()().
     * - @e T_arg3 Argument type used in the definition of operator()().
     * - @e T_arg4 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
    class QEXTBoundConstMemberFunctor4 : public QEXTConstMemberFunctor4< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >
    {
        typedef QEXTConstMemberFunctor4< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 > Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QEXTBoundConstMemberFunctor4 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundConstMemberFunctor4(const T_obj *obj, Function func) : Base(func), m_obj(*obj) {}
        /** Constructs a QEXTBoundConstMemberFunctor4 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundConstMemberFunctor4(const T_obj &obj, Function func) : Base(func), m_obj(obj) {}
        QEXTBoundConstMemberFunctor4(const QEXTBoundConstMemberFunctor4 &other) : Base(other.m_funcPtr), m_obj(other.m_obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \param arg4 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QEXTConstLimitReference< T_obj > m_obj;
    };

    /** QEXTBoundConstMemberFunctor3 encapsulates a const method with 3 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QEXTBoundConstMemberFunctor3.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_arg2 Argument type used in the definition of operator()().
     * - @e T_arg3 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3 >
    class QEXTBoundConstMemberFunctor3 : public QEXTConstMemberFunctor3< T_return, T_obj, T_arg1, T_arg2, T_arg3 >
    {
        typedef QEXTConstMemberFunctor3< T_return, T_obj, T_arg1, T_arg2, T_arg3 > Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QEXTBoundConstMemberFunctor3 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundConstMemberFunctor3(const T_obj *obj, Function func) : Base(func), m_obj(*obj) {}
        /** Constructs a QEXTBoundConstMemberFunctor3 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundConstMemberFunctor3(const T_obj &obj, Function func) : Base(func), m_obj(obj) {}
        QEXTBoundConstMemberFunctor3(const QEXTBoundConstMemberFunctor3 &other) : Base(other.m_funcPtr), m_obj(other.m_obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return
        operator()(typename QEXTTypeTrait< T_arg1 >::Take arg1, typename QEXTTypeTrait< T_arg2 >::Take arg2, typename QEXTTypeTrait< T_arg3 >::Take arg3) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QEXTConstLimitReference< T_obj > m_obj;
    };

    /** QEXTBoundConstMemberFunctor2 encapsulates a const method with 2 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QEXTBoundConstMemberFunctor2.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_arg2 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2 >
    class QEXTBoundConstMemberFunctor2 : public QEXTConstMemberFunctor2< T_return, T_obj, T_arg1, T_arg2 >
    {
        typedef QEXTConstMemberFunctor2< T_return, T_obj, T_arg1, T_arg2 > Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QEXTBoundConstMemberFunctor2 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundConstMemberFunctor2(const T_obj *obj, Function func) : Base(func), m_obj(*obj) {}
        /** Constructs a QEXTBoundConstMemberFunctor2 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundConstMemberFunctor2(const T_obj &obj, Function func) : Base(func), m_obj(obj) {}
        QEXTBoundConstMemberFunctor2(const QEXTBoundConstMemberFunctor2 &other) : Base(other.m_funcPtr), m_obj(other.m_obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(typename QEXTTypeTrait< T_arg1 >::Take arg1, typename QEXTTypeTrait< T_arg2 >::Take arg2) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QEXTConstLimitReference< T_obj > m_obj;
    };

    /** QEXTBoundConstMemberFunctor1 encapsulates a const method with 1 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QEXTBoundConstMemberFunctor1.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template < typename T_return, typename T_obj, typename T_arg1 >
    class QEXTBoundConstMemberFunctor1 : public QEXTConstMemberFunctor1< T_return, T_obj, T_arg1 >
    {
        typedef QEXTConstMemberFunctor1< T_return, T_obj, T_arg1 > Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QEXTBoundConstMemberFunctor1 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundConstMemberFunctor1(const T_obj *obj, Function func) : Base(func), m_obj(*obj) {}
        /** Constructs a QEXTBoundConstMemberFunctor1 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundConstMemberFunctor1(const T_obj &obj, Function func) : Base(func), m_obj(obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \param arg1 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(typename QEXTTypeTrait< T_arg1 >::Take arg1) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QEXTConstLimitReference< T_obj > m_obj;
    };

    /** QEXTBoundConstMemberFunctor0 encapsulates a const method with 0 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QEXTBoundConstMemberFunctor0.
     *
     * The following template arguments are used:
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template < typename T_return, typename T_obj >
    class QEXTBoundConstMemberFunctor0 : public QEXTConstMemberFunctor0< T_return, T_obj >
    {
        typedef QEXTConstMemberFunctor0< T_return, T_obj > Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QEXTBoundConstMemberFunctor0 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundConstMemberFunctor0(const T_obj *obj, Function func) : Base(func), m_obj(*obj) {}
        /** Constructs a QEXTBoundConstMemberFunctor0 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundConstMemberFunctor0(const T_obj &obj, Function func) : Base(func), m_obj(obj) {}
        QEXTBoundConstMemberFunctor0(const QEXTBoundConstMemberFunctor0 &other) : Base(other.m_funcPtr), m_obj(other.m_obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \return The return value of the method invocation.
         */
        T_return operator()() const
        {
            return (m_obj.invoke().*(this->m_funcPtr))();
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QEXTConstLimitReference< T_obj > m_obj;
    };

    /** QEXTBoundVolatileMemberFunctor7 encapsulates a volatile method with 7 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QEXTBoundVolatileMemberFunctor7.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_arg2 Argument type used in the definition of operator()().
     * - @e T_arg3 Argument type used in the definition of operator()().
     * - @e T_arg4 Argument type used in the definition of operator()().
     * - @e T_arg5 Argument type used in the definition of operator()().
     * - @e T_arg6 Argument type used in the definition of operator()().
     * - @e T_arg7 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template <
        typename T_return,
        typename T_obj,
        typename T_arg1,
        typename T_arg2,
        typename T_arg3,
        typename T_arg4,
        typename T_arg5,
        typename T_arg6,
        typename T_arg7 >
    class QEXTBoundVolatileMemberFunctor7 : public QEXTVolatileMemberFunctor7< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
    {
        typedef QEXTVolatileMemberFunctor7< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 > Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QEXTBoundVolatileMemberFunctor7 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundVolatileMemberFunctor7(T_obj *obj, Function func) : Base(func), m_obj(*obj) {}
        /** Constructs a QEXTBoundVolatileMemberFunctor7 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundVolatileMemberFunctor7(T_obj &obj, Function func) : Base(func), m_obj(obj) {}
        QEXTBoundVolatileMemberFunctor7(const QEXTBoundVolatileMemberFunctor7 &other) : Base(other.m_funcPtr), m_obj(other.m_obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \param arg4 Argument to be passed on to the method.
         * \param arg5 Argument to be passed on to the method.
         * \param arg6 Argument to be passed on to the method.
         * \param arg7 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4,
            typename QEXTTypeTrait< T_arg5 >::Take arg5,
            typename QEXTTypeTrait< T_arg6 >::Take arg6,
            typename QEXTTypeTrait< T_arg7 >::Take arg7) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QEXTVolatileLimitReference< T_obj > m_obj;
    };

    /** QEXTBoundVolatileMemberFunctor6 encapsulates a volatile method with 6 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QEXTBoundVolatileMemberFunctor6.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_arg2 Argument type used in the definition of operator()().
     * - @e T_arg3 Argument type used in the definition of operator()().
     * - @e T_arg4 Argument type used in the definition of operator()().
     * - @e T_arg5 Argument type used in the definition of operator()().
     * - @e T_arg6 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
    class QEXTBoundVolatileMemberFunctor6 : public QEXTVolatileMemberFunctor6< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
    {
        typedef QEXTVolatileMemberFunctor6< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 > Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QEXTBoundVolatileMemberFunctor6 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundVolatileMemberFunctor6(T_obj *obj, Function func) : Base(func), m_obj(*obj) {}
        /** Constructs a QEXTBoundVolatileMemberFunctor6 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundVolatileMemberFunctor6(T_obj &obj, Function func) : Base(func), m_obj(obj) {}
        QEXTBoundVolatileMemberFunctor6(const QEXTBoundVolatileMemberFunctor6 &other) : Base(other.m_funcPtr), m_obj(other.m_obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \param arg4 Argument to be passed on to the method.
         * \param arg5 Argument to be passed on to the method.
         * \param arg6 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4,
            typename QEXTTypeTrait< T_arg5 >::Take arg5,
            typename QEXTTypeTrait< T_arg6 >::Take arg6) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QEXTVolatileLimitReference< T_obj > m_obj;
    };

    /** QEXTBoundVolatileMemberFunctor5 encapsulates a volatile method with 5 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QEXTBoundVolatileMemberFunctor5.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_arg2 Argument type used in the definition of operator()().
     * - @e T_arg3 Argument type used in the definition of operator()().
     * - @e T_arg4 Argument type used in the definition of operator()().
     * - @e T_arg5 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
    class QEXTBoundVolatileMemberFunctor5 : public QEXTVolatileMemberFunctor5< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
    {
        typedef QEXTVolatileMemberFunctor5< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 > Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QEXTBoundVolatileMemberFunctor5 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundVolatileMemberFunctor5(T_obj *obj, Function func) : Base(func), m_obj(*obj) {}
        /** Constructs a QEXTBoundVolatileMemberFunctor5 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundVolatileMemberFunctor5(T_obj &obj, Function func) : Base(func), m_obj(obj) {}
        QEXTBoundVolatileMemberFunctor5(const QEXTBoundVolatileMemberFunctor5 &other) : Base(other.m_funcPtr), m_obj(other.m_obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \param arg4 Argument to be passed on to the method.
         * \param arg5 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4,
            typename QEXTTypeTrait< T_arg5 >::Take arg5) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QEXTVolatileLimitReference< T_obj > m_obj;
    };

    /** QEXTBoundVolatileMemberFunctor4 encapsulates a volatile method with 4 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QEXTBoundVolatileMemberFunctor4.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_arg2 Argument type used in the definition of operator()().
     * - @e T_arg3 Argument type used in the definition of operator()().
     * - @e T_arg4 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
    class QEXTBoundVolatileMemberFunctor4 : public QEXTVolatileMemberFunctor4< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >
    {
        typedef QEXTVolatileMemberFunctor4< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 > Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QEXTBoundVolatileMemberFunctor4 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundVolatileMemberFunctor4(T_obj *obj, Function func) : Base(func), m_obj(*obj) {}
        /** Constructs a QEXTBoundVolatileMemberFunctor4 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundVolatileMemberFunctor4(T_obj &obj, Function func) : Base(func), m_obj(obj) {}
        QEXTBoundVolatileMemberFunctor4(const QEXTBoundVolatileMemberFunctor4 &other) : Base(other.m_funcPtr), m_obj(other.m_obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \param arg4 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QEXTVolatileLimitReference< T_obj > m_obj;
    };

    /** QEXTBoundVolatileMemberFunctor3 encapsulates a volatile method with 3 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QEXTBoundVolatileMemberFunctor3.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_arg2 Argument type used in the definition of operator()().
     * - @e T_arg3 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3 >
    class QEXTBoundVolatileMemberFunctor3 : public QEXTVolatileMemberFunctor3< T_return, T_obj, T_arg1, T_arg2, T_arg3 >
    {
        typedef QEXTVolatileMemberFunctor3< T_return, T_obj, T_arg1, T_arg2, T_arg3 > Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QEXTBoundVolatileMemberFunctor3 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundVolatileMemberFunctor3(T_obj *obj, Function func) : Base(func), m_obj(*obj) {}
        /** Constructs a QEXTBoundVolatileMemberFunctor3 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundVolatileMemberFunctor3(T_obj &obj, Function func) : Base(func), m_obj(obj) {}
        QEXTBoundVolatileMemberFunctor3(const QEXTBoundVolatileMemberFunctor3 &other) : Base(other.m_funcPtr), m_obj(other.m_obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return
        operator()(typename QEXTTypeTrait< T_arg1 >::Take arg1, typename QEXTTypeTrait< T_arg2 >::Take arg2, typename QEXTTypeTrait< T_arg3 >::Take arg3) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QEXTVolatileLimitReference< T_obj > m_obj;
    };

    /** QEXTBoundVolatileMemberFunctor2 encapsulates a volatile method with 2 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QEXTBoundVolatileMemberFunctor2.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_arg2 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2 >
    class QEXTBoundVolatileMemberFunctor2 : public QEXTVolatileMemberFunctor2< T_return, T_obj, T_arg1, T_arg2 >
    {
        typedef QEXTVolatileMemberFunctor2< T_return, T_obj, T_arg1, T_arg2 > Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QEXTBoundVolatileMemberFunctor2 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundVolatileMemberFunctor2(T_obj *obj, Function func) : Base(func), m_obj(*obj) {}
        /** Constructs a QEXTBoundVolatileMemberFunctor2 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundVolatileMemberFunctor2(T_obj &obj, Function func) : Base(func), m_obj(obj) {}
        QEXTBoundVolatileMemberFunctor2(const QEXTBoundVolatileMemberFunctor2 &other) : Base(other.m_funcPtr), m_obj(other.m_obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(typename QEXTTypeTrait< T_arg1 >::Take arg1, typename QEXTTypeTrait< T_arg2 >::Take arg2) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QEXTVolatileLimitReference< T_obj > m_obj;
    };

    /** QEXTBoundVolatileMemberFunctor1 encapsulates a volatile method with 1 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QEXTBoundVolatileMemberFunctor1.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template < typename T_return, typename T_obj, typename T_arg1 >
    class QEXTBoundVolatileMemberFunctor1 : public QEXTVolatileMemberFunctor1< T_return, T_obj, T_arg1 >
    {
        typedef QEXTVolatileMemberFunctor1< T_return, T_obj, T_arg1 > Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QEXTBoundVolatileMemberFunctor1 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundVolatileMemberFunctor1(T_obj *obj, Function func) : Base(func), m_obj(*obj) {}
        /** Constructs a QEXTBoundVolatileMemberFunctor1 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundVolatileMemberFunctor1(T_obj &obj, Function func) : Base(func), m_obj(obj) {}
        QEXTBoundVolatileMemberFunctor1(const QEXTBoundVolatileMemberFunctor1 &other) : Base(other.m_funcPtr), m_obj(other.m_obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \param arg1 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(typename QEXTTypeTrait< T_arg1 >::Take arg1) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QEXTVolatileLimitReference< T_obj > m_obj;
    };

    /** QEXTBoundVolatileMemberFunctor0 encapsulates a volatile method with 0 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QEXTBoundVolatileMemberFunctor0.
     *
     * The following template arguments are used:
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template < typename T_return, typename T_obj >
    class QEXTBoundVolatileMemberFunctor0 : public QEXTVolatileMemberFunctor0< T_return, T_obj >
    {
        typedef QEXTVolatileMemberFunctor0< T_return, T_obj > Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QEXTBoundVolatileMemberFunctor0 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundVolatileMemberFunctor0(T_obj *obj, Function func) : Base(func), m_obj(*obj) {}
        /** Constructs a QEXTBoundVolatileMemberFunctor0 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundVolatileMemberFunctor0(T_obj &obj, Function func) : Base(func), m_obj(obj) {}
        QEXTBoundVolatileMemberFunctor0(const QEXTBoundVolatileMemberFunctor0 &other) : Base(other.m_funcPtr), m_obj(other.m_obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \return The return value of the method invocation.
         */
        T_return operator()() const
        {
            return (m_obj.invoke().*(this->m_funcPtr))();
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QEXTVolatileLimitReference< T_obj > m_obj;
    };

    /** QEXTBoundConstVolatileMemberFunctor7 encapsulates a const volatile method with 7 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QEXTBoundConstVolatileMemberFunctor7.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_arg2 Argument type used in the definition of operator()().
     * - @e T_arg3 Argument type used in the definition of operator()().
     * - @e T_arg4 Argument type used in the definition of operator()().
     * - @e T_arg5 Argument type used in the definition of operator()().
     * - @e T_arg6 Argument type used in the definition of operator()().
     * - @e T_arg7 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template <
        typename T_return,
        typename T_obj,
        typename T_arg1,
        typename T_arg2,
        typename T_arg3,
        typename T_arg4,
        typename T_arg5,
        typename T_arg6,
        typename T_arg7 >
    class QEXTBoundConstVolatileMemberFunctor7 : public QEXTConstVolatileMemberFunctor7< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
    {
        typedef QEXTConstVolatileMemberFunctor7< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 > Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QEXTBoundConstVolatileMemberFunctor7 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundConstVolatileMemberFunctor7(const T_obj *obj, Function func) : Base(func), m_obj(*obj) {}
        /** Constructs a QEXTBoundConstVolatileMemberFunctor7 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundConstVolatileMemberFunctor7(const T_obj &obj, Function func) : Base(func), m_obj(obj) {}
        QEXTBoundConstVolatileMemberFunctor7(const QEXTBoundConstVolatileMemberFunctor7 &other) : Base(other.m_funcPtr), m_obj(other.m_obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \param arg4 Argument to be passed on to the method.
         * \param arg5 Argument to be passed on to the method.
         * \param arg6 Argument to be passed on to the method.
         * \param arg7 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4,
            typename QEXTTypeTrait< T_arg5 >::Take arg5,
            typename QEXTTypeTrait< T_arg6 >::Take arg6,
            typename QEXTTypeTrait< T_arg7 >::Take arg7) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QEXTConstVolatileLimitReference< T_obj > m_obj;
    };

    /** QEXTBoundConstVolatileMemberFunctor6 encapsulates a const volatile method with 6 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QEXTBoundConstVolatileMemberFunctor6.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_arg2 Argument type used in the definition of operator()().
     * - @e T_arg3 Argument type used in the definition of operator()().
     * - @e T_arg4 Argument type used in the definition of operator()().
     * - @e T_arg5 Argument type used in the definition of operator()().
     * - @e T_arg6 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
    class QEXTBoundConstVolatileMemberFunctor6 : public QEXTConstVolatileMemberFunctor6< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
    {
        typedef QEXTConstVolatileMemberFunctor6< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 > Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QEXTBoundConstVolatileMemberFunctor6 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundConstVolatileMemberFunctor6(const T_obj *obj, Function func) : Base(func), m_obj(*obj) {}
        /** Constructs a QEXTBoundConstVolatileMemberFunctor6 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundConstVolatileMemberFunctor6(const T_obj &obj, Function func) : Base(func), m_obj(obj) {}
        QEXTBoundConstVolatileMemberFunctor6(const QEXTBoundConstVolatileMemberFunctor6 &other) : Base(other.m_funcPtr), m_obj(other.m_obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \param arg4 Argument to be passed on to the method.
         * \param arg5 Argument to be passed on to the method.
         * \param arg6 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4,
            typename QEXTTypeTrait< T_arg5 >::Take arg5,
            typename QEXTTypeTrait< T_arg6 >::Take arg6) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QEXTConstVolatileLimitReference< T_obj > m_obj;
    };

    /** QEXTBoundConstVolatileMemberFunctor5 encapsulates a const volatile method with 5 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QEXTBoundConstVolatileMemberFunctor5.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_arg2 Argument type used in the definition of operator()().
     * - @e T_arg3 Argument type used in the definition of operator()().
     * - @e T_arg4 Argument type used in the definition of operator()().
     * - @e T_arg5 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
    class QEXTBoundConstVolatileMemberFunctor5 : public QEXTConstVolatileMemberFunctor5< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
    {
        typedef QEXTConstVolatileMemberFunctor5< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 > Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QEXTBoundConstVolatileMemberFunctor5 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundConstVolatileMemberFunctor5(const T_obj *obj, Function func) : Base(func), m_obj(*obj) {}
        /** Constructs a QEXTBoundConstVolatileMemberFunctor5 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundConstVolatileMemberFunctor5(const T_obj &obj, Function func) : Base(func), m_obj(obj) {}
        QEXTBoundConstVolatileMemberFunctor5(const QEXTBoundConstVolatileMemberFunctor5 &other) : Base(other.m_funcPtr), m_obj(other.m_obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \param arg4 Argument to be passed on to the method.
         * \param arg5 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4,
            typename QEXTTypeTrait< T_arg5 >::Take arg5) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QEXTConstVolatileLimitReference< T_obj > m_obj;
    };

    /** QEXTBoundConstVolatileMemberFunctor4 encapsulates a const volatile method with 4 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QEXTBoundConstVolatileMemberFunctor4.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_arg2 Argument type used in the definition of operator()().
     * - @e T_arg3 Argument type used in the definition of operator()().
     * - @e T_arg4 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
    class QEXTBoundConstVolatileMemberFunctor4 : public QEXTConstVolatileMemberFunctor4< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >
    {
        typedef QEXTConstVolatileMemberFunctor4< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 > Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QEXTBoundConstVolatileMemberFunctor4 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundConstVolatileMemberFunctor4(const T_obj *obj, Function func) : Base(func), m_obj(*obj) {}
        /** Constructs a QEXTBoundConstVolatileMemberFunctor4 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundConstVolatileMemberFunctor4(const T_obj &obj, Function func) : Base(func), m_obj(obj) {}
        QEXTBoundConstVolatileMemberFunctor4(const QEXTBoundConstVolatileMemberFunctor4 &other) : Base(other.m_funcPtr), m_obj(other.m_obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \param arg4 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QEXTConstVolatileLimitReference< T_obj > m_obj;
    };

    /** QEXTBoundConstVolatileMemberFunctor3 encapsulates a const volatile method with 3 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QEXTBoundConstVolatileMemberFunctor3.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_arg2 Argument type used in the definition of operator()().
     * - @e T_arg3 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3 >
    class QEXTBoundConstVolatileMemberFunctor3 : public QEXTConstVolatileMemberFunctor3< T_return, T_obj, T_arg1, T_arg2, T_arg3 >
    {
        typedef QEXTConstVolatileMemberFunctor3< T_return, T_obj, T_arg1, T_arg2, T_arg3 > Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QEXTBoundConstVolatileMemberFunctor3 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundConstVolatileMemberFunctor3(const T_obj *obj, Function func) : Base(func), m_obj(*obj) {}
        /** Constructs a QEXTBoundConstVolatileMemberFunctor3 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundConstVolatileMemberFunctor3(const T_obj &obj, Function func) : Base(func), m_obj(obj) {}
        QEXTBoundConstVolatileMemberFunctor3(const QEXTBoundConstVolatileMemberFunctor3 &other) : Base(other.m_funcPtr), m_obj(other.m_obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return
        operator()(typename QEXTTypeTrait< T_arg1 >::Take arg1, typename QEXTTypeTrait< T_arg2 >::Take arg2, typename QEXTTypeTrait< T_arg3 >::Take arg3) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QEXTConstVolatileLimitReference< T_obj > m_obj;
    };

    /** QEXTBoundConstVolatileMemberFunctor2 encapsulates a const volatile method with 2 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QEXTBoundConstVolatileMemberFunctor2.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_arg2 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2 >
    class QEXTBoundConstVolatileMemberFunctor2 : public QEXTConstVolatileMemberFunctor2< T_return, T_obj, T_arg1, T_arg2 >
    {
        typedef QEXTConstVolatileMemberFunctor2< T_return, T_obj, T_arg1, T_arg2 > Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QEXTBoundConstVolatileMemberFunctor2 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundConstVolatileMemberFunctor2(const T_obj *obj, Function func) : Base(func), m_obj(*obj) {}
        /** Constructs a QEXTBoundConstVolatileMemberFunctor2 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundConstVolatileMemberFunctor2(const T_obj &obj, Function func) : Base(func), m_obj(obj) {}
        QEXTBoundConstVolatileMemberFunctor2(const QEXTBoundConstVolatileMemberFunctor2 &other) : Base(other.m_funcPtr), m_obj(other.m_obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(typename QEXTTypeTrait< T_arg1 >::Take arg1, typename QEXTTypeTrait< T_arg2 >::Take arg2) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QEXTConstVolatileLimitReference< T_obj > m_obj;
    };

    /** QEXTBoundConstVolatileMemberFunctor1 encapsulates a const volatile method with 1 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QEXTBoundConstVolatileMemberFunctor1.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template < typename T_return, typename T_obj, typename T_arg1 >
    class QEXTBoundConstVolatileMemberFunctor1 : public QEXTConstVolatileMemberFunctor1< T_return, T_obj, T_arg1 >
    {
        typedef QEXTConstVolatileMemberFunctor1< T_return, T_obj, T_arg1 > Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QEXTBoundConstVolatileMemberFunctor1 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundConstVolatileMemberFunctor1(const T_obj *obj, Function func) : Base(func), m_obj(*obj) {}
        /** Constructs a QEXTBoundConstVolatileMemberFunctor1 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundConstVolatileMemberFunctor1(const T_obj &obj, Function func) : Base(func), m_obj(obj) {}
        QEXTBoundConstVolatileMemberFunctor1(const QEXTBoundConstVolatileMemberFunctor1 &other) : Base(other.m_funcPtr), m_obj(other.m_obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \param arg1 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(typename QEXTTypeTrait< T_arg1 >::Take arg1) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QEXTConstVolatileLimitReference< T_obj > m_obj;
    };

    /** QEXTBoundConstVolatileMemberFunctor0 encapsulates a const volatile method with 0 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QEXTBoundConstVolatileMemberFunctor0.
     *
     * The following template arguments are used:
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template < typename T_return, typename T_obj >
    class QEXTBoundConstVolatileMemberFunctor0 : public QEXTConstVolatileMemberFunctor0< T_return, T_obj >
    {
        typedef QEXTConstVolatileMemberFunctor0< T_return, T_obj > Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QEXTBoundConstVolatileMemberFunctor0 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundConstVolatileMemberFunctor0(const T_obj *obj, Function func) : Base(func), m_obj(*obj) {}
        /** Constructs a QEXTBoundConstVolatileMemberFunctor0 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QEXTBoundConstVolatileMemberFunctor0(const T_obj &obj, Function func) : Base(func), m_obj(obj) {}
        QEXTBoundConstVolatileMemberFunctor0(const QEXTBoundConstVolatileMemberFunctor0 &other) : Base(other.m_funcPtr), m_obj(other.m_obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \return The return value of the method invocation.
         */
        T_return operator()() const
        {
            return (m_obj.invoke().*(this->m_funcPtr))();
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QEXTConstVolatileLimitReference< T_obj > m_obj;
    };

} // namespace qextPrivate




template <
    typename T_return,
    typename T_obj,
    typename T_arg1 = QEXTNil,
    typename T_arg2 = QEXTNil,
    typename T_arg3 = QEXTNil,
    typename T_arg4 = QEXTNil,
    typename T_arg5 = QEXTNil,
    typename T_arg6 = QEXTNil,
    typename T_arg7 = QEXTNil >
class QEXTMemberFunctor : public qextPrivate::QEXTMemberFunctor7< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
{
    typedef qextPrivate::QEXTMemberFunctor7< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTMemberFunctor() {}
    QEXTMemberFunctor(Function func) : Base(func) {}
    QEXTMemberFunctor(const QEXTMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(
        T_obj *obj,
        typename QEXTTypeTrait< T_arg1 >::Take arg1,
        typename QEXTTypeTrait< T_arg2 >::Take arg2,
        typename QEXTTypeTrait< T_arg3 >::Take arg3,
        typename QEXTTypeTrait< T_arg4 >::Take arg4,
        typename QEXTTypeTrait< T_arg5 >::Take arg5,
        typename QEXTTypeTrait< T_arg6 >::Take arg6,
        typename QEXTTypeTrait< T_arg7 >::Take arg7) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    T_return operator()(
        T_obj &obj,
        typename QEXTTypeTrait< T_arg1 >::Take arg1,
        typename QEXTTypeTrait< T_arg2 >::Take arg2,
        typename QEXTTypeTrait< T_arg3 >::Take arg3,
        typename QEXTTypeTrait< T_arg4 >::Take arg4,
        typename QEXTTypeTrait< T_arg5 >::Take arg5,
        typename QEXTTypeTrait< T_arg6 >::Take arg6,
        typename QEXTTypeTrait< T_arg7 >::Take arg7) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
class QEXTMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QEXTNil >
    : public qextPrivate::QEXTMemberFunctor6< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
{
    typedef qextPrivate::QEXTMemberFunctor6< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTMemberFunctor() {}
    QEXTMemberFunctor(Function func) : Base(func) {}
    QEXTMemberFunctor(const QEXTMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(
        T_obj *obj,
        typename QEXTTypeTrait< T_arg1 >::Take arg1,
        typename QEXTTypeTrait< T_arg2 >::Take arg2,
        typename QEXTTypeTrait< T_arg3 >::Take arg3,
        typename QEXTTypeTrait< T_arg4 >::Take arg4,
        typename QEXTTypeTrait< T_arg5 >::Take arg5,
        typename QEXTTypeTrait< T_arg6 >::Take arg6) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4, arg5, arg6);
    }

    T_return operator()(
        T_obj &obj,
        typename QEXTTypeTrait< T_arg1 >::Take arg1,
        typename QEXTTypeTrait< T_arg2 >::Take arg2,
        typename QEXTTypeTrait< T_arg3 >::Take arg3,
        typename QEXTTypeTrait< T_arg4 >::Take arg4,
        typename QEXTTypeTrait< T_arg5 >::Take arg5,
        typename QEXTTypeTrait< T_arg6 >::Take arg6) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
class QEXTMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QEXTNil, QEXTNil >
    : public qextPrivate::QEXTMemberFunctor5< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
{
    typedef qextPrivate::QEXTMemberFunctor5< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTMemberFunctor() {}
    QEXTMemberFunctor(Function func) : Base(func) {}
    QEXTMemberFunctor(const QEXTMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(
        T_obj *obj,
        typename QEXTTypeTrait< T_arg1 >::Take arg1,
        typename QEXTTypeTrait< T_arg2 >::Take arg2,
        typename QEXTTypeTrait< T_arg3 >::Take arg3,
        typename QEXTTypeTrait< T_arg4 >::Take arg4,
        typename QEXTTypeTrait< T_arg5 >::Take arg5) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4, arg5);
    }

    T_return operator()(
        T_obj &obj,
        typename QEXTTypeTrait< T_arg1 >::Take arg1,
        typename QEXTTypeTrait< T_arg2 >::Take arg2,
        typename QEXTTypeTrait< T_arg3 >::Take arg3,
        typename QEXTTypeTrait< T_arg4 >::Take arg4,
        typename QEXTTypeTrait< T_arg5 >::Take arg5) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4, arg5);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
class QEXTMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, QEXTNil, QEXTNil, QEXTNil >
    : public qextPrivate::QEXTMemberFunctor4< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >
{
    typedef qextPrivate::QEXTMemberFunctor4< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTMemberFunctor() {}
    QEXTMemberFunctor(Function func) : Base(func) {}
    QEXTMemberFunctor(const QEXTMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(
        T_obj *obj,
        typename QEXTTypeTrait< T_arg1 >::Take arg1,
        typename QEXTTypeTrait< T_arg2 >::Take arg2,
        typename QEXTTypeTrait< T_arg3 >::Take arg3,
        typename QEXTTypeTrait< T_arg4 >::Take arg4) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4);
    }

    T_return operator()(
        T_obj &obj,
        typename QEXTTypeTrait< T_arg1 >::Take arg1,
        typename QEXTTypeTrait< T_arg2 >::Take arg2,
        typename QEXTTypeTrait< T_arg3 >::Take arg3,
        typename QEXTTypeTrait< T_arg4 >::Take arg4) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3 >
class QEXTMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, QEXTNil, QEXTNil, QEXTNil, QEXTNil >
    : public qextPrivate::QEXTMemberFunctor3< T_return, T_obj, T_arg1, T_arg2, T_arg3 >
{
    typedef qextPrivate::QEXTMemberFunctor3< T_return, T_obj, T_arg1, T_arg2, T_arg3 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTMemberFunctor() {}
    QEXTMemberFunctor(Function func) : Base(func) {}
    QEXTMemberFunctor(const QEXTMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(
        T_obj *obj, typename QEXTTypeTrait< T_arg1 >::Take arg1, typename QEXTTypeTrait< T_arg2 >::Take arg2, typename QEXTTypeTrait< T_arg3 >::Take arg3) const
    {
        return Base::operator()(obj, arg1, arg2, arg3);
    }

    T_return operator()(
        T_obj &obj, typename QEXTTypeTrait< T_arg1 >::Take arg1, typename QEXTTypeTrait< T_arg2 >::Take arg2, typename QEXTTypeTrait< T_arg3 >::Take arg3) const
    {
        return Base::operator()(obj, arg1, arg2, arg3);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2 >
class QEXTMemberFunctor< T_return, T_obj, T_arg1, T_arg2, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil > : public qextPrivate::QEXTMemberFunctor2< T_return, T_obj, T_arg1, T_arg2 >
{
    typedef qextPrivate::QEXTMemberFunctor2< T_return, T_obj, T_arg1, T_arg2 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTMemberFunctor() {}
    QEXTMemberFunctor(Function func) : Base(func) {}
    QEXTMemberFunctor(const QEXTMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(T_obj *obj, typename QEXTTypeTrait< T_arg1 >::Take arg1, typename QEXTTypeTrait< T_arg2 >::Take arg2) const
    {
        return Base::operator()(obj, arg1, arg2);
    }

    T_return operator()(T_obj &obj, typename QEXTTypeTrait< T_arg1 >::Take arg1, typename QEXTTypeTrait< T_arg2 >::Take arg2) const
    {
        return Base::operator()(obj, arg1, arg2);
    }
};

template < typename T_return, typename T_obj, typename T_arg1 >
class QEXTMemberFunctor< T_return, T_obj, T_arg1, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil > : public qextPrivate::QEXTMemberFunctor1< T_return, T_obj, T_arg1 >
{
    typedef qextPrivate::QEXTMemberFunctor1< T_return, T_obj, T_arg1 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTMemberFunctor() {}
    QEXTMemberFunctor(Function func) : Base(func) {}
    QEXTMemberFunctor(const QEXTMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(T_obj *obj, typename QEXTTypeTrait< T_arg1 >::Take arg1) const
    {
        return Base::operator()(obj, arg1);
    }

    T_return operator()(T_obj &obj, typename QEXTTypeTrait< T_arg1 >::Take arg1) const
    {
        return Base::operator()(obj, arg1);
    }
};

template < typename T_return, typename T_obj >
class QEXTMemberFunctor< T_return, T_obj, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil > : public qextPrivate::QEXTMemberFunctor0< T_return, T_obj >
{
public:
    typedef qextPrivate::QEXTMemberFunctor0< T_return, T_obj > Base;
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTMemberFunctor() {}
    QEXTMemberFunctor(Function func) : Base(func) {}
    QEXTMemberFunctor(const QEXTMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(T_obj *obj) const
    {
        return Base::operator()(obj);
    }

    T_return operator()(T_obj &obj) const
    {
        return Base::operator()(obj);
    }
};

template <
    typename T_return,
    typename T_obj,
    typename T_arg1 = QEXTNil,
    typename T_arg2 = QEXTNil,
    typename T_arg3 = QEXTNil,
    typename T_arg4 = QEXTNil,
    typename T_arg5 = QEXTNil,
    typename T_arg6 = QEXTNil,
    typename T_arg7 = QEXTNil >
class QEXTConstMemberFunctor : public qextPrivate::QEXTConstMemberFunctor7< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
{
    typedef qextPrivate::QEXTConstMemberFunctor7< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTConstMemberFunctor() {}
    QEXTConstMemberFunctor(Function func) : Base(func) {}
    QEXTConstMemberFunctor(const QEXTConstMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(
        const T_obj *obj,
        typename QEXTTypeTrait< T_arg1 >::Take arg1,
        typename QEXTTypeTrait< T_arg2 >::Take arg2,
        typename QEXTTypeTrait< T_arg3 >::Take arg3,
        typename QEXTTypeTrait< T_arg4 >::Take arg4,
        typename QEXTTypeTrait< T_arg5 >::Take arg5,
        typename QEXTTypeTrait< T_arg6 >::Take arg6,
        typename QEXTTypeTrait< T_arg7 >::Take arg7) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    T_return operator()(
        const T_obj &obj,
        typename QEXTTypeTrait< T_arg1 >::Take arg1,
        typename QEXTTypeTrait< T_arg2 >::Take arg2,
        typename QEXTTypeTrait< T_arg3 >::Take arg3,
        typename QEXTTypeTrait< T_arg4 >::Take arg4,
        typename QEXTTypeTrait< T_arg5 >::Take arg5,
        typename QEXTTypeTrait< T_arg6 >::Take arg6,
        typename QEXTTypeTrait< T_arg7 >::Take arg7) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
class QEXTConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QEXTNil >
    : public qextPrivate::QEXTConstMemberFunctor6< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
{
    typedef qextPrivate::QEXTConstMemberFunctor6< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTConstMemberFunctor() {}
    QEXTConstMemberFunctor(Function func) : Base(func) {}
    QEXTConstMemberFunctor(const QEXTConstMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(
        const T_obj *obj,
        typename QEXTTypeTrait< T_arg1 >::Take arg1,
        typename QEXTTypeTrait< T_arg2 >::Take arg2,
        typename QEXTTypeTrait< T_arg3 >::Take arg3,
        typename QEXTTypeTrait< T_arg4 >::Take arg4,
        typename QEXTTypeTrait< T_arg5 >::Take arg5,
        typename QEXTTypeTrait< T_arg6 >::Take arg6) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4, arg5, arg6);
    }

    T_return operator()(
        const T_obj &obj,
        typename QEXTTypeTrait< T_arg1 >::Take arg1,
        typename QEXTTypeTrait< T_arg2 >::Take arg2,
        typename QEXTTypeTrait< T_arg3 >::Take arg3,
        typename QEXTTypeTrait< T_arg4 >::Take arg4,
        typename QEXTTypeTrait< T_arg5 >::Take arg5,
        typename QEXTTypeTrait< T_arg6 >::Take arg6) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
class QEXTConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QEXTNil, QEXTNil >
    : public qextPrivate::QEXTConstMemberFunctor5< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
{
    typedef qextPrivate::QEXTConstMemberFunctor5< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTConstMemberFunctor() {}
    QEXTConstMemberFunctor(Function func) : Base(func) {}
    QEXTConstMemberFunctor(const QEXTConstMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(
        const T_obj *obj,
        typename QEXTTypeTrait< T_arg1 >::Take arg1,
        typename QEXTTypeTrait< T_arg2 >::Take arg2,
        typename QEXTTypeTrait< T_arg3 >::Take arg3,
        typename QEXTTypeTrait< T_arg4 >::Take arg4,
        typename QEXTTypeTrait< T_arg5 >::Take arg5) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4, arg5);
    }

    T_return operator()(
        const T_obj &obj,
        typename QEXTTypeTrait< T_arg1 >::Take arg1,
        typename QEXTTypeTrait< T_arg2 >::Take arg2,
        typename QEXTTypeTrait< T_arg3 >::Take arg3,
        typename QEXTTypeTrait< T_arg4 >::Take arg4,
        typename QEXTTypeTrait< T_arg5 >::Take arg5) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4, arg5);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
class QEXTConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, QEXTNil, QEXTNil, QEXTNil >
    : public qextPrivate::QEXTConstMemberFunctor4< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >
{
    typedef qextPrivate::QEXTConstMemberFunctor4< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTConstMemberFunctor() {}
    QEXTConstMemberFunctor(Function func) : Base(func) {}
    QEXTConstMemberFunctor(const QEXTConstMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(
        const T_obj *obj,
        typename QEXTTypeTrait< T_arg1 >::Take arg1,
        typename QEXTTypeTrait< T_arg2 >::Take arg2,
        typename QEXTTypeTrait< T_arg3 >::Take arg3,
        typename QEXTTypeTrait< T_arg4 >::Take arg4) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4);
    }

    T_return operator()(
        const T_obj &obj,
        typename QEXTTypeTrait< T_arg1 >::Take arg1,
        typename QEXTTypeTrait< T_arg2 >::Take arg2,
        typename QEXTTypeTrait< T_arg3 >::Take arg3,
        typename QEXTTypeTrait< T_arg4 >::Take arg4) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3 >
class QEXTConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, QEXTNil, QEXTNil, QEXTNil, QEXTNil >
    : public qextPrivate::QEXTConstMemberFunctor3< T_return, T_obj, T_arg1, T_arg2, T_arg3 >
{
    typedef qextPrivate::QEXTConstMemberFunctor3< T_return, T_obj, T_arg1, T_arg2, T_arg3 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTConstMemberFunctor() {}
    QEXTConstMemberFunctor(Function func) : Base(func) {}
    QEXTConstMemberFunctor(const QEXTConstMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(
        const T_obj *obj, typename QEXTTypeTrait< T_arg1 >::Take arg1, typename QEXTTypeTrait< T_arg2 >::Take arg2, typename QEXTTypeTrait< T_arg3 >::Take arg3) const
    {
        return Base::operator()(obj, arg1, arg2, arg3);
    }

    T_return operator()(
        const T_obj &obj, typename QEXTTypeTrait< T_arg1 >::Take arg1, typename QEXTTypeTrait< T_arg2 >::Take arg2, typename QEXTTypeTrait< T_arg3 >::Take arg3) const
    {
        return Base::operator()(obj, arg1, arg2, arg3);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2 >
class QEXTConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil >
    : public qextPrivate::QEXTConstMemberFunctor2< T_return, T_obj, T_arg1, T_arg2 >
{
    typedef qextPrivate::QEXTConstMemberFunctor2< T_return, T_obj, T_arg1, T_arg2 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTConstMemberFunctor() {}
    QEXTConstMemberFunctor(Function func) : Base(func) {}
    QEXTConstMemberFunctor(const QEXTConstMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(const T_obj *obj, typename QEXTTypeTrait< T_arg1 >::Take arg1, typename QEXTTypeTrait< T_arg2 >::Take arg2) const
    {
        return Base::operator()(obj, arg1, arg2);
    }

    T_return operator()(const T_obj &obj, typename QEXTTypeTrait< T_arg1 >::Take arg1, typename QEXTTypeTrait< T_arg2 >::Take arg2) const
    {
        return Base::operator()(obj, arg1, arg2);
    }
};

template < typename T_return, typename T_obj, typename T_arg1 >
class QEXTConstMemberFunctor< T_return, T_obj, T_arg1, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil > : public qextPrivate::QEXTConstMemberFunctor1< T_return, T_obj, T_arg1 >
{
    typedef qextPrivate::QEXTConstMemberFunctor1< T_return, T_obj, T_arg1 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTConstMemberFunctor() {}
    QEXTConstMemberFunctor(Function func) : Base(func) {}
    QEXTConstMemberFunctor(const QEXTConstMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(const T_obj *obj, typename QEXTTypeTrait< T_arg1 >::Take arg1) const
    {
        return Base::operator()(obj, arg1);
    }

    T_return operator()(const T_obj &obj, typename QEXTTypeTrait< T_arg1 >::Take arg1) const
    {
        return Base::operator()(obj, arg1);
    }
};

template < typename T_return, typename T_obj >
class QEXTConstMemberFunctor< T_return, T_obj, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil > : public qextPrivate::QEXTConstMemberFunctor0< T_return, T_obj >
{
    typedef qextPrivate::QEXTConstMemberFunctor0< T_return, T_obj > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTConstMemberFunctor() {}
    QEXTConstMemberFunctor(Function func) : Base(func) {}
    QEXTConstMemberFunctor(const QEXTConstMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(const T_obj *obj) const
    {
        return Base::operator()(obj);
    }

    T_return operator()(const T_obj &obj) const
    {
        return Base::operator()(obj);
    }
};

template <
    typename T_return,
    typename T_obj,
    typename T_arg1 = QEXTNil,
    typename T_arg2 = QEXTNil,
    typename T_arg3 = QEXTNil,
    typename T_arg4 = QEXTNil,
    typename T_arg5 = QEXTNil,
    typename T_arg6 = QEXTNil,
    typename T_arg7 = QEXTNil >
class QEXTVolatileMemberFunctor : public qextPrivate::QEXTVolatileMemberFunctor7< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
{
    typedef qextPrivate::QEXTVolatileMemberFunctor7< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTVolatileMemberFunctor() {}
    QEXTVolatileMemberFunctor(Function func) : Base(func) {}
    QEXTVolatileMemberFunctor(const QEXTVolatileMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(
        T_obj *obj,
        typename QEXTTypeTrait< T_arg1 >::Take arg1,
        typename QEXTTypeTrait< T_arg2 >::Take arg2,
        typename QEXTTypeTrait< T_arg3 >::Take arg3,
        typename QEXTTypeTrait< T_arg4 >::Take arg4,
        typename QEXTTypeTrait< T_arg5 >::Take arg5,
        typename QEXTTypeTrait< T_arg6 >::Take arg6,
        typename QEXTTypeTrait< T_arg7 >::Take arg7) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    T_return operator()(
        T_obj &obj,
        typename QEXTTypeTrait< T_arg1 >::Take arg1,
        typename QEXTTypeTrait< T_arg2 >::Take arg2,
        typename QEXTTypeTrait< T_arg3 >::Take arg3,
        typename QEXTTypeTrait< T_arg4 >::Take arg4,
        typename QEXTTypeTrait< T_arg5 >::Take arg5,
        typename QEXTTypeTrait< T_arg6 >::Take arg6,
        typename QEXTTypeTrait< T_arg7 >::Take arg7) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
class QEXTVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QEXTNil >
    : public qextPrivate::QEXTVolatileMemberFunctor6< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
{
    typedef qextPrivate::QEXTVolatileMemberFunctor6< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTVolatileMemberFunctor() {}
    QEXTVolatileMemberFunctor(Function func) : Base(func) {}
    QEXTVolatileMemberFunctor(const QEXTVolatileMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(
        T_obj *obj,
        typename QEXTTypeTrait< T_arg1 >::Take arg1,
        typename QEXTTypeTrait< T_arg2 >::Take arg2,
        typename QEXTTypeTrait< T_arg3 >::Take arg3,
        typename QEXTTypeTrait< T_arg4 >::Take arg4,
        typename QEXTTypeTrait< T_arg5 >::Take arg5,
        typename QEXTTypeTrait< T_arg6 >::Take arg6) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4, arg5, arg6);
    }

    T_return operator()(
        T_obj &obj,
        typename QEXTTypeTrait< T_arg1 >::Take arg1,
        typename QEXTTypeTrait< T_arg2 >::Take arg2,
        typename QEXTTypeTrait< T_arg3 >::Take arg3,
        typename QEXTTypeTrait< T_arg4 >::Take arg4,
        typename QEXTTypeTrait< T_arg5 >::Take arg5,
        typename QEXTTypeTrait< T_arg6 >::Take arg6) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
class QEXTVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QEXTNil, QEXTNil >
    : public qextPrivate::QEXTVolatileMemberFunctor5< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
{
    typedef qextPrivate::QEXTVolatileMemberFunctor5< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTVolatileMemberFunctor() {}
    QEXTVolatileMemberFunctor(Function func) : Base(func) {}
    QEXTVolatileMemberFunctor(const QEXTVolatileMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(
        T_obj *obj,
        typename QEXTTypeTrait< T_arg1 >::Take arg1,
        typename QEXTTypeTrait< T_arg2 >::Take arg2,
        typename QEXTTypeTrait< T_arg3 >::Take arg3,
        typename QEXTTypeTrait< T_arg4 >::Take arg4,
        typename QEXTTypeTrait< T_arg5 >::Take arg5) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4, arg5);
    }

    T_return operator()(
        T_obj &obj,
        typename QEXTTypeTrait< T_arg1 >::Take arg1,
        typename QEXTTypeTrait< T_arg2 >::Take arg2,
        typename QEXTTypeTrait< T_arg3 >::Take arg3,
        typename QEXTTypeTrait< T_arg4 >::Take arg4,
        typename QEXTTypeTrait< T_arg5 >::Take arg5) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4, arg5);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
class QEXTVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, QEXTNil, QEXTNil, QEXTNil >
    : public qextPrivate::QEXTVolatileMemberFunctor4< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >
{
    typedef qextPrivate::QEXTVolatileMemberFunctor4< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTVolatileMemberFunctor() {}
    QEXTVolatileMemberFunctor(Function func) : Base(func) {}
    QEXTVolatileMemberFunctor(const QEXTVolatileMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(
        T_obj *obj,
        typename QEXTTypeTrait< T_arg1 >::Take arg1,
        typename QEXTTypeTrait< T_arg2 >::Take arg2,
        typename QEXTTypeTrait< T_arg3 >::Take arg3,
        typename QEXTTypeTrait< T_arg4 >::Take arg4) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4);
    }

    T_return operator()(
        T_obj &obj,
        typename QEXTTypeTrait< T_arg1 >::Take arg1,
        typename QEXTTypeTrait< T_arg2 >::Take arg2,
        typename QEXTTypeTrait< T_arg3 >::Take arg3,
        typename QEXTTypeTrait< T_arg4 >::Take arg4) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3 >
class QEXTVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, QEXTNil, QEXTNil, QEXTNil, QEXTNil >
    : public qextPrivate::QEXTVolatileMemberFunctor3< T_return, T_obj, T_arg1, T_arg2, T_arg3 >
{
    typedef qextPrivate::QEXTVolatileMemberFunctor3< T_return, T_obj, T_arg1, T_arg2, T_arg3 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTVolatileMemberFunctor() {}
    QEXTVolatileMemberFunctor(Function func) : Base(func) {}
    QEXTVolatileMemberFunctor(const QEXTVolatileMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(
        T_obj *obj, typename QEXTTypeTrait< T_arg1 >::Take arg1, typename QEXTTypeTrait< T_arg2 >::Take arg2, typename QEXTTypeTrait< T_arg3 >::Take arg3) const
    {
        return Base::operator()(obj, arg1, arg2, arg3);
    }

    T_return operator()(
        T_obj &obj, typename QEXTTypeTrait< T_arg1 >::Take arg1, typename QEXTTypeTrait< T_arg2 >::Take arg2, typename QEXTTypeTrait< T_arg3 >::Take arg3) const
    {
        return Base::operator()(obj, arg1, arg2, arg3);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2 >
class QEXTVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil >
    : public qextPrivate::QEXTVolatileMemberFunctor2< T_return, T_obj, T_arg1, T_arg2 >
{
    typedef qextPrivate::QEXTVolatileMemberFunctor2< T_return, T_obj, T_arg1, T_arg2 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTVolatileMemberFunctor() {}
    QEXTVolatileMemberFunctor(Function func) : Base(func) {}
    QEXTVolatileMemberFunctor(const QEXTVolatileMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(T_obj *obj, typename QEXTTypeTrait< T_arg1 >::Take arg1, typename QEXTTypeTrait< T_arg2 >::Take arg2) const
    {
        return Base::operator()(obj, arg1, arg2);
    }

    T_return operator()(T_obj &obj, typename QEXTTypeTrait< T_arg1 >::Take arg1, typename QEXTTypeTrait< T_arg2 >::Take arg2) const
    {
        return Base::operator()(obj, arg1, arg2);
    }
};

template < typename T_return, typename T_obj, typename T_arg1 >
class QEXTVolatileMemberFunctor< T_return, T_obj, T_arg1, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil > : public qextPrivate::QEXTVolatileMemberFunctor1< T_return, T_obj, T_arg1 >
{
    typedef qextPrivate::QEXTVolatileMemberFunctor1< T_return, T_obj, T_arg1 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTVolatileMemberFunctor() {}
    QEXTVolatileMemberFunctor(Function func) : Base(func) {}
    QEXTVolatileMemberFunctor(const QEXTVolatileMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(T_obj *obj, typename QEXTTypeTrait< T_arg1 >::Take arg1) const
    {
        return Base::operator()(obj, arg1);
    }

    T_return operator()(T_obj &obj, typename QEXTTypeTrait< T_arg1 >::Take arg1) const
    {
        return Base::operator()(obj, arg1);
    }
};

template < typename T_return, typename T_obj >
class QEXTVolatileMemberFunctor< T_return, T_obj, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil > : public qextPrivate::QEXTVolatileMemberFunctor0< T_return, T_obj >
{
    typedef qextPrivate::QEXTVolatileMemberFunctor0< T_return, T_obj > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTVolatileMemberFunctor() {}
    QEXTVolatileMemberFunctor(Function func) : Base(func) {}
    QEXTVolatileMemberFunctor(const QEXTVolatileMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(T_obj *obj) const
    {
        return Base::operator()(obj);
    }

    T_return operator()(T_obj &obj) const
    {
        return Base::operator()(obj);
    }
};

template <
    typename T_return,
    typename T_obj,
    typename T_arg1 = QEXTNil,
    typename T_arg2 = QEXTNil,
    typename T_arg3 = QEXTNil,
    typename T_arg4 = QEXTNil,
    typename T_arg5 = QEXTNil,
    typename T_arg6 = QEXTNil,
    typename T_arg7 = QEXTNil >
class QEXTConstVolatileMemberFunctor : public qextPrivate::QEXTConstVolatileMemberFunctor7< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
{
    typedef qextPrivate::QEXTConstVolatileMemberFunctor7< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTConstVolatileMemberFunctor() {}
    QEXTConstVolatileMemberFunctor(Function func) : Base(func) {}
    QEXTConstVolatileMemberFunctor(const QEXTConstVolatileMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(
        const T_obj *obj,
        typename QEXTTypeTrait< T_arg1 >::Take arg1,
        typename QEXTTypeTrait< T_arg2 >::Take arg2,
        typename QEXTTypeTrait< T_arg3 >::Take arg3,
        typename QEXTTypeTrait< T_arg4 >::Take arg4,
        typename QEXTTypeTrait< T_arg5 >::Take arg5,
        typename QEXTTypeTrait< T_arg6 >::Take arg6,
        typename QEXTTypeTrait< T_arg7 >::Take arg7) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    T_return operator()(
        const T_obj &obj,
        typename QEXTTypeTrait< T_arg1 >::Take arg1,
        typename QEXTTypeTrait< T_arg2 >::Take arg2,
        typename QEXTTypeTrait< T_arg3 >::Take arg3,
        typename QEXTTypeTrait< T_arg4 >::Take arg4,
        typename QEXTTypeTrait< T_arg5 >::Take arg5,
        typename QEXTTypeTrait< T_arg6 >::Take arg6,
        typename QEXTTypeTrait< T_arg7 >::Take arg7) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
class QEXTConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QEXTNil >
    : public qextPrivate::QEXTConstVolatileMemberFunctor6< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
{
    typedef qextPrivate::QEXTConstVolatileMemberFunctor6< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTConstVolatileMemberFunctor() {}
    QEXTConstVolatileMemberFunctor(Function func) : Base(func) {}
    QEXTConstVolatileMemberFunctor(const QEXTConstVolatileMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(
        const T_obj *obj,
        typename QEXTTypeTrait< T_arg1 >::Take arg1,
        typename QEXTTypeTrait< T_arg2 >::Take arg2,
        typename QEXTTypeTrait< T_arg3 >::Take arg3,
        typename QEXTTypeTrait< T_arg4 >::Take arg4,
        typename QEXTTypeTrait< T_arg5 >::Take arg5,
        typename QEXTTypeTrait< T_arg6 >::Take arg6) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4, arg5, arg6);
    }

    T_return operator()(
        const T_obj &obj,
        typename QEXTTypeTrait< T_arg1 >::Take arg1,
        typename QEXTTypeTrait< T_arg2 >::Take arg2,
        typename QEXTTypeTrait< T_arg3 >::Take arg3,
        typename QEXTTypeTrait< T_arg4 >::Take arg4,
        typename QEXTTypeTrait< T_arg5 >::Take arg5,
        typename QEXTTypeTrait< T_arg6 >::Take arg6) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
class QEXTConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QEXTNil, QEXTNil >
    : public qextPrivate::QEXTConstVolatileMemberFunctor5< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
{
    typedef qextPrivate::QEXTConstVolatileMemberFunctor5< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTConstVolatileMemberFunctor() {}
    QEXTConstVolatileMemberFunctor(Function func) : Base(func) {}
    QEXTConstVolatileMemberFunctor(const QEXTConstVolatileMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(
        const T_obj *obj,
        typename QEXTTypeTrait< T_arg1 >::Take arg1,
        typename QEXTTypeTrait< T_arg2 >::Take arg2,
        typename QEXTTypeTrait< T_arg3 >::Take arg3,
        typename QEXTTypeTrait< T_arg4 >::Take arg4,
        typename QEXTTypeTrait< T_arg5 >::Take arg5) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4, arg5);
    }

    T_return operator()(
        const T_obj &obj,
        typename QEXTTypeTrait< T_arg1 >::Take arg1,
        typename QEXTTypeTrait< T_arg2 >::Take arg2,
        typename QEXTTypeTrait< T_arg3 >::Take arg3,
        typename QEXTTypeTrait< T_arg4 >::Take arg4,
        typename QEXTTypeTrait< T_arg5 >::Take arg5) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4, arg5);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
class QEXTConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, QEXTNil, QEXTNil, QEXTNil >
    : public qextPrivate::QEXTConstVolatileMemberFunctor4< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >
{
    typedef qextPrivate::QEXTConstVolatileMemberFunctor4< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTConstVolatileMemberFunctor() {}
    QEXTConstVolatileMemberFunctor(Function func) : Base(func) {}
    QEXTConstVolatileMemberFunctor(const QEXTConstVolatileMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(
        const T_obj *obj,
        typename QEXTTypeTrait< T_arg1 >::Take arg1,
        typename QEXTTypeTrait< T_arg2 >::Take arg2,
        typename QEXTTypeTrait< T_arg3 >::Take arg3,
        typename QEXTTypeTrait< T_arg4 >::Take arg4) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4);
    }

    T_return operator()(
        const T_obj &obj,
        typename QEXTTypeTrait< T_arg1 >::Take arg1,
        typename QEXTTypeTrait< T_arg2 >::Take arg2,
        typename QEXTTypeTrait< T_arg3 >::Take arg3,
        typename QEXTTypeTrait< T_arg4 >::Take arg4) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3 >
class QEXTConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, QEXTNil, QEXTNil, QEXTNil, QEXTNil >
    : public qextPrivate::QEXTConstVolatileMemberFunctor3< T_return, T_obj, T_arg1, T_arg2, T_arg3 >
{
    typedef qextPrivate::QEXTConstVolatileMemberFunctor3< T_return, T_obj, T_arg1, T_arg2, T_arg3 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTConstVolatileMemberFunctor() {}
    QEXTConstVolatileMemberFunctor(Function func) : Base(func) {}
    QEXTConstVolatileMemberFunctor(const QEXTConstVolatileMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(
        const T_obj *obj, typename QEXTTypeTrait< T_arg1 >::Take arg1, typename QEXTTypeTrait< T_arg2 >::Take arg2, typename QEXTTypeTrait< T_arg3 >::Take arg3) const
    {
        return Base::operator()(obj, arg1, arg2, arg3);
    }

    T_return operator()(
        const T_obj &obj, typename QEXTTypeTrait< T_arg1 >::Take arg1, typename QEXTTypeTrait< T_arg2 >::Take arg2, typename QEXTTypeTrait< T_arg3 >::Take arg3) const
    {
        return Base::operator()(obj, arg1, arg2, arg3);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2 >
class QEXTConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil >
    : public qextPrivate::QEXTConstVolatileMemberFunctor2< T_return, T_obj, T_arg1, T_arg2 >
{
    typedef qextPrivate::QEXTConstVolatileMemberFunctor2< T_return, T_obj, T_arg1, T_arg2 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTConstVolatileMemberFunctor() {}
    QEXTConstVolatileMemberFunctor(Function func) : Base(func) {}
    QEXTConstVolatileMemberFunctor(const QEXTConstVolatileMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(const T_obj *obj, typename QEXTTypeTrait< T_arg1 >::Take arg1, typename QEXTTypeTrait< T_arg2 >::Take arg2) const
    {
        return Base::operator()(obj, arg1, arg2);
    }

    T_return operator()(const T_obj &obj, typename QEXTTypeTrait< T_arg1 >::Take arg1, typename QEXTTypeTrait< T_arg2 >::Take arg2) const
    {
        return Base::operator()(obj, arg1, arg2);
    }
};

template < typename T_return, typename T_obj, typename T_arg1 >
class QEXTConstVolatileMemberFunctor< T_return, T_obj, T_arg1, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil >
    : public qextPrivate::QEXTConstVolatileMemberFunctor1< T_return, T_obj, T_arg1 >
{
    typedef qextPrivate::QEXTConstVolatileMemberFunctor1< T_return, T_obj, T_arg1 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTConstVolatileMemberFunctor() {}
    QEXTConstVolatileMemberFunctor(Function func) : Base(func) {}
    QEXTConstVolatileMemberFunctor(const QEXTConstVolatileMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(const T_obj *obj, typename QEXTTypeTrait< T_arg1 >::Take arg1) const
    {
        return Base::operator()(obj, arg1);
    }

    T_return operator()(const T_obj &obj, typename QEXTTypeTrait< T_arg1 >::Take arg1) const
    {
        return Base::operator()(obj, arg1);
    }
};

template < typename T_return, typename T_obj >
class QEXTConstVolatileMemberFunctor< T_return, T_obj, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil > : public qextPrivate::QEXTConstVolatileMemberFunctor0< T_return, T_obj >
{
    typedef qextPrivate::QEXTConstVolatileMemberFunctor0< T_return, T_obj > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTConstVolatileMemberFunctor() {}
    QEXTConstVolatileMemberFunctor(Function func) : Base(func) {}
    QEXTConstVolatileMemberFunctor(const QEXTConstVolatileMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(const T_obj *obj) const
    {
        return Base::operator()(obj);
    }

    T_return operator()(const T_obj &obj) const
    {
        return Base::operator()(obj);
    }
};

template <
    typename T_return,
    typename T_obj,
    typename T_arg1 = QEXTNil,
    typename T_arg2 = QEXTNil,
    typename T_arg3 = QEXTNil,
    typename T_arg4 = QEXTNil,
    typename T_arg5 = QEXTNil,
    typename T_arg6 = QEXTNil,
    typename T_arg7 = QEXTNil >
class QEXTBoundMemberFunctor : public qextPrivate::QEXTBoundMemberFunctor7< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
{
    typedef qextPrivate::QEXTBoundMemberFunctor7< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTBoundMemberFunctor(T_obj *obj, Function func) : Base(obj, func) {}
    QEXTBoundMemberFunctor(T_obj &obj, Function func) : Base(obj, func) {}
    QEXTBoundMemberFunctor(const QEXTBoundMemberFunctor &other) : Base(other) {}

    T_return operator()(
        typename QEXTTypeTrait< T_arg1 >::Take arg1,
        typename QEXTTypeTrait< T_arg2 >::Take arg2,
        typename QEXTTypeTrait< T_arg3 >::Take arg3,
        typename QEXTTypeTrait< T_arg4 >::Take arg4,
        typename QEXTTypeTrait< T_arg5 >::Take arg5,
        typename QEXTTypeTrait< T_arg6 >::Take arg6,
        typename QEXTTypeTrait< T_arg7 >::Take arg7) const
    {
        return Base::operator()(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

template <
    typename T_return,
    typename T_obj,
    typename T_arg1,
    typename T_arg2,
    typename T_arg3,
    typename T_arg4,
    typename T_arg5,
    typename T_arg6,
    typename T_arg7 >
struct QEXTVisitor< QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 > >
{
    template < typename T_action >
    static void
    doVisitEach(const T_action &action, const QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 > &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
class QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QEXTNil >
    : public qextPrivate::QEXTBoundMemberFunctor6< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
{
    typedef qextPrivate::QEXTBoundMemberFunctor6< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTBoundMemberFunctor(T_obj *obj, Function func) : Base(obj, func) {}
    QEXTBoundMemberFunctor(T_obj &obj, Function func) : Base(obj, func) {}
    QEXTBoundMemberFunctor(const QEXTBoundMemberFunctor &other) : Base(other) {}

    T_return operator()(
        typename QEXTTypeTrait< T_arg1 >::Take arg1,
        typename QEXTTypeTrait< T_arg2 >::Take arg2,
        typename QEXTTypeTrait< T_arg3 >::Take arg3,
        typename QEXTTypeTrait< T_arg4 >::Take arg4,
        typename QEXTTypeTrait< T_arg5 >::Take arg5,
        typename QEXTTypeTrait< T_arg6 >::Take arg6) const
    {
        return Base::operator()(arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
struct QEXTVisitor< QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 > >
{
    template < typename T_action >
    static void doVisitEach(const T_action &action, const QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 > &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
class QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QEXTNil, QEXTNil >
    : public qextPrivate::QEXTBoundMemberFunctor5< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
{
    typedef qextPrivate::QEXTBoundMemberFunctor5< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTBoundMemberFunctor(T_obj *obj, Function func) : Base(obj, func) {}
    QEXTBoundMemberFunctor(T_obj &obj, Function func) : Base(obj, func) {}
    QEXTBoundMemberFunctor(const QEXTBoundMemberFunctor &other) : Base(other) {}

    T_return operator()(
        typename QEXTTypeTrait< T_arg1 >::Take arg1,
        typename QEXTTypeTrait< T_arg2 >::Take arg2,
        typename QEXTTypeTrait< T_arg3 >::Take arg3,
        typename QEXTTypeTrait< T_arg4 >::Take arg4,
        typename QEXTTypeTrait< T_arg5 >::Take arg5) const
    {
        return Base::operator()(arg1, arg2, arg3, arg4, arg5);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
struct QEXTVisitor< QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 > >
{
    template < typename T_action >
    static void doVisitEach(const T_action &action, const QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 > &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
class QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, QEXTNil, QEXTNil, QEXTNil >
    : public qextPrivate::QEXTBoundMemberFunctor4< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >
{
    typedef qextPrivate::QEXTBoundMemberFunctor4< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTBoundMemberFunctor(T_obj *obj, Function func) : Base(obj, func) {}
    QEXTBoundMemberFunctor(T_obj &obj, Function func) : Base(obj, func) {}
    QEXTBoundMemberFunctor(const QEXTBoundMemberFunctor &other) : Base(other) {}

    T_return operator()(
        typename QEXTTypeTrait< T_arg1 >::Take arg1,
        typename QEXTTypeTrait< T_arg2 >::Take arg2,
        typename QEXTTypeTrait< T_arg3 >::Take arg3,
        typename QEXTTypeTrait< T_arg4 >::Take arg4) const
    {
        return Base::operator()(arg1, arg2, arg3, arg4);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
struct QEXTVisitor< QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 > >
{
    template < typename T_action >
    static void doVisitEach(const T_action &action, const QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 > &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3 >
class QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, QEXTNil, QEXTNil, QEXTNil, QEXTNil >
    : public qextPrivate::QEXTBoundMemberFunctor3< T_return, T_obj, T_arg1, T_arg2, T_arg3 >
{
    typedef qextPrivate::QEXTBoundMemberFunctor3< T_return, T_obj, T_arg1, T_arg2, T_arg3 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTBoundMemberFunctor(T_obj *obj, Function func) : Base(obj, func) {}
    QEXTBoundMemberFunctor(T_obj &obj, Function func) : Base(obj, func) {}
    QEXTBoundMemberFunctor(const QEXTBoundMemberFunctor &other) : Base(other) {}

    T_return operator()(typename QEXTTypeTrait< T_arg1 >::Take arg1, typename QEXTTypeTrait< T_arg2 >::Take arg2, typename QEXTTypeTrait< T_arg3 >::Take arg3) const
    {
        return Base::operator()(arg1, arg2, arg3);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3 >
struct QEXTVisitor< QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 > >
{
    template < typename T_action >
    static void doVisitEach(const T_action &action, const QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 > &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2 >
class QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil >
    : public qextPrivate::QEXTBoundMemberFunctor2< T_return, T_obj, T_arg1, T_arg2 >
{
    typedef qextPrivate::QEXTBoundMemberFunctor2< T_return, T_obj, T_arg1, T_arg2 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTBoundMemberFunctor(T_obj *obj, Function func) : Base(obj, func) {}
    QEXTBoundMemberFunctor(T_obj &obj, Function func) : Base(obj, func) {}
    QEXTBoundMemberFunctor(const QEXTBoundMemberFunctor &other) : Base(other) {}

    T_return operator()(typename QEXTTypeTrait< T_arg1 >::Take arg1, typename QEXTTypeTrait< T_arg2 >::Take arg2) const
    {
        return Base::operator()(arg1, arg2);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2 >
struct QEXTVisitor< QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2 > >
{
    template < typename T_action >
    static void doVisitEach(const T_action &action, const QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2 > &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template < typename T_return, typename T_obj, typename T_arg1 >
class QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil > : public qextPrivate::QEXTBoundMemberFunctor1< T_return, T_obj, T_arg1 >
{
    typedef qextPrivate::QEXTBoundMemberFunctor1< T_return, T_obj, T_arg1 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTBoundMemberFunctor(T_obj *obj, Function func) : Base(obj, func) {}
    QEXTBoundMemberFunctor(T_obj &obj, Function func) : Base(obj, func) {}
    QEXTBoundMemberFunctor(const QEXTBoundMemberFunctor &other) : Base(other) {}

    T_return operator()(typename QEXTTypeTrait< T_arg1 >::Take arg1) const
    {
        return Base::operator()(arg1);
    }
};

template < typename T_return, typename T_obj, typename T_arg1 >
struct QEXTVisitor< QEXTBoundMemberFunctor< T_return, T_obj, T_arg1 > >
{
    template < typename T_action >
    static void doVisitEach(const T_action &action, const QEXTBoundMemberFunctor< T_return, T_obj, T_arg1 > &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template < typename T_return, typename T_obj >
class QEXTBoundMemberFunctor< T_return, T_obj, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil > : public qextPrivate::QEXTBoundMemberFunctor0< T_return, T_obj >
{
    typedef qextPrivate::QEXTBoundMemberFunctor0< T_return, T_obj > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTBoundMemberFunctor(T_obj *obj, Function func) : Base(obj, func) {}
    QEXTBoundMemberFunctor(T_obj &obj, Function func) : Base(obj, func) {}
    QEXTBoundMemberFunctor(const QEXTBoundMemberFunctor &other) : Base(other) {}

    T_return operator()() const
    {
        return Base::operator()();
    }
};

template < typename T_return, typename T_obj >
struct QEXTVisitor< QEXTBoundMemberFunctor< T_return, T_obj > >
{
    template < typename T_action >
    static void doVisitEach(const T_action &action, const QEXTBoundMemberFunctor< T_return, T_obj > &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template <
    typename T_return,
    typename T_obj,
    typename T_arg1 = QEXTNil,
    typename T_arg2 = QEXTNil,
    typename T_arg3 = QEXTNil,
    typename T_arg4 = QEXTNil,
    typename T_arg5 = QEXTNil,
    typename T_arg6 = QEXTNil,
    typename T_arg7 = QEXTNil >
class QEXTBoundConstMemberFunctor : public qextPrivate::QEXTBoundConstMemberFunctor7< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
{
    typedef qextPrivate::QEXTBoundConstMemberFunctor7< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTBoundConstMemberFunctor(const T_obj *obj, Function func) : Base(obj, func) {}
    QEXTBoundConstMemberFunctor(const T_obj &obj, Function func) : Base(obj, func) {}
    QEXTBoundConstMemberFunctor(const QEXTBoundConstMemberFunctor &other) : Base(other) {}

    T_return operator()(
        typename QEXTTypeTrait< T_arg1 >::Take arg1,
        typename QEXTTypeTrait< T_arg2 >::Take arg2,
        typename QEXTTypeTrait< T_arg3 >::Take arg3,
        typename QEXTTypeTrait< T_arg4 >::Take arg4,
        typename QEXTTypeTrait< T_arg5 >::Take arg5,
        typename QEXTTypeTrait< T_arg6 >::Take arg6,
        typename QEXTTypeTrait< T_arg7 >::Take arg7) const
    {
        return Base::operator()(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

template <
    typename T_return,
    typename T_obj,
    typename T_arg1,
    typename T_arg2,
    typename T_arg3,
    typename T_arg4,
    typename T_arg5,
    typename T_arg6,
    typename T_arg7 >
struct QEXTVisitor< QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 > >
{
    template < typename T_action >
    static void
    doVisitEach(const T_action &action, const QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 > &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
class QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QEXTNil >
    : public qextPrivate::QEXTBoundConstMemberFunctor6< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
{
    typedef qextPrivate::QEXTBoundConstMemberFunctor6< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTBoundConstMemberFunctor(const T_obj *obj, Function func) : Base(obj, func) {}
    QEXTBoundConstMemberFunctor(const T_obj &obj, Function func) : Base(obj, func) {}
    QEXTBoundConstMemberFunctor(const QEXTBoundConstMemberFunctor &other) : Base(other) {}

    T_return operator()(
        typename QEXTTypeTrait< T_arg1 >::Take arg1,
        typename QEXTTypeTrait< T_arg2 >::Take arg2,
        typename QEXTTypeTrait< T_arg3 >::Take arg3,
        typename QEXTTypeTrait< T_arg4 >::Take arg4,
        typename QEXTTypeTrait< T_arg5 >::Take arg5,
        typename QEXTTypeTrait< T_arg6 >::Take arg6) const
    {
        return Base::operator()(arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
struct QEXTVisitor< QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 > >
{
    template < typename T_action >
    static void doVisitEach(const T_action &action, const QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 > &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
class QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QEXTNil, QEXTNil >
    : public qextPrivate::QEXTBoundConstMemberFunctor5< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
{
    typedef qextPrivate::QEXTBoundConstMemberFunctor5< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTBoundConstMemberFunctor(const T_obj *obj, Function func) : Base(obj, func) {}
    QEXTBoundConstMemberFunctor(const T_obj &obj, Function func) : Base(obj, func) {}
    QEXTBoundConstMemberFunctor(const QEXTBoundConstMemberFunctor &other) : Base(other) {}

    T_return operator()(
        typename QEXTTypeTrait< T_arg1 >::Take arg1,
        typename QEXTTypeTrait< T_arg2 >::Take arg2,
        typename QEXTTypeTrait< T_arg3 >::Take arg3,
        typename QEXTTypeTrait< T_arg4 >::Take arg4,
        typename QEXTTypeTrait< T_arg5 >::Take arg5) const
    {
        return Base::operator()(arg1, arg2, arg3, arg4, arg5);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
struct QEXTVisitor< QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 > >
{
    template < typename T_action >
    static void doVisitEach(const T_action &action, const QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 > &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
class QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, QEXTNil, QEXTNil, QEXTNil >
    : public qextPrivate::QEXTBoundConstMemberFunctor4< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >
{
    typedef qextPrivate::QEXTBoundConstMemberFunctor4< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTBoundConstMemberFunctor(const T_obj *obj, Function func) : Base(obj, func) {}
    QEXTBoundConstMemberFunctor(const T_obj &obj, Function func) : Base(obj, func) {}
    QEXTBoundConstMemberFunctor(const QEXTBoundConstMemberFunctor &other) : Base(other) {}

    T_return operator()(
        typename QEXTTypeTrait< T_arg1 >::Take arg1,
        typename QEXTTypeTrait< T_arg2 >::Take arg2,
        typename QEXTTypeTrait< T_arg3 >::Take arg3,
        typename QEXTTypeTrait< T_arg4 >::Take arg4) const
    {
        return Base::operator()(arg1, arg2, arg3, arg4);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
struct QEXTVisitor< QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 > >
{
    template < typename T_action >
    static void doVisitEach(const T_action &action, const QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 > &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3 >
class QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, QEXTNil, QEXTNil, QEXTNil, QEXTNil >
    : public qextPrivate::QEXTBoundConstMemberFunctor3< T_return, T_obj, T_arg1, T_arg2, T_arg3 >
{
    typedef qextPrivate::QEXTBoundConstMemberFunctor3< T_return, T_obj, T_arg1, T_arg2, T_arg3 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTBoundConstMemberFunctor(const T_obj *obj, Function func) : Base(obj, func) {}
    QEXTBoundConstMemberFunctor(const T_obj &obj, Function func) : Base(obj, func) {}
    QEXTBoundConstMemberFunctor(const QEXTBoundConstMemberFunctor &other) : Base(other) {}

    T_return operator()(typename QEXTTypeTrait< T_arg1 >::Take arg1, typename QEXTTypeTrait< T_arg2 >::Take arg2, typename QEXTTypeTrait< T_arg3 >::Take arg3) const
    {
        return Base::operator()(arg1, arg2, arg3);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3 >
struct QEXTVisitor< QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 > >
{
    template < typename T_action >
    static void doVisitEach(const T_action &action, const QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 > &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2 >
class QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil >
    : public qextPrivate::QEXTBoundConstMemberFunctor2< T_return, T_obj, T_arg1, T_arg2 >
{
    typedef qextPrivate::QEXTBoundConstMemberFunctor2< T_return, T_obj, T_arg1, T_arg2 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTBoundConstMemberFunctor(const T_obj *obj, Function func) : Base(obj, func) {}
    QEXTBoundConstMemberFunctor(const T_obj &obj, Function func) : Base(obj, func) {}
    QEXTBoundConstMemberFunctor(const QEXTBoundConstMemberFunctor &other) : Base(other) {}

    T_return operator()(typename QEXTTypeTrait< T_arg1 >::Take arg1, typename QEXTTypeTrait< T_arg2 >::Take arg2) const
    {
        return Base::operator()(arg1, arg2);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2 >
struct QEXTVisitor< QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2 > >
{
    template < typename T_action >
    static void doVisitEach(const T_action &action, const QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2 > &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template < typename T_return, typename T_obj, typename T_arg1 >
class QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil >
    : public qextPrivate::QEXTBoundConstMemberFunctor1< T_return, T_obj, T_arg1 >
{
    typedef qextPrivate::QEXTBoundConstMemberFunctor1< T_return, T_obj, T_arg1 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTBoundConstMemberFunctor(const T_obj *obj, Function func) : Base(obj, func) {}
    QEXTBoundConstMemberFunctor(const T_obj &obj, Function func) : Base(obj, func) {}
    QEXTBoundConstMemberFunctor(const QEXTBoundConstMemberFunctor &other) : Base(other) {}

    T_return operator()(typename QEXTTypeTrait< T_arg1 >::Take arg1) const
    {
        return Base::operator()(arg1);
    }
};

template < typename T_return, typename T_obj, typename T_arg1 >
struct QEXTVisitor< QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1 > >
{
    template < typename T_action >
    static void doVisitEach(const T_action &action, const QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1 > &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template < typename T_return, typename T_obj >
class QEXTBoundConstMemberFunctor< T_return, T_obj, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil > : public qextPrivate::QEXTBoundConstMemberFunctor0< T_return, T_obj >
{
    typedef qextPrivate::QEXTBoundConstMemberFunctor0< T_return, T_obj > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTBoundConstMemberFunctor(const T_obj *obj, Function func) : Base(obj, func) {}
    QEXTBoundConstMemberFunctor(const T_obj &obj, Function func) : Base(obj, func) {}
    QEXTBoundConstMemberFunctor(const QEXTBoundConstMemberFunctor &other) : Base(other) {}

    T_return operator()() const
    {
        return Base::operator()();
    }
};

template < typename T_return, typename T_obj >
struct QEXTVisitor< QEXTBoundConstMemberFunctor< T_return, T_obj > >
{
    template < typename T_action >
    static void doVisitEach(const T_action &action, const QEXTBoundConstMemberFunctor< T_return, T_obj > &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template <
    typename T_return,
    typename T_obj,
    typename T_arg1 = QEXTNil,
    typename T_arg2 = QEXTNil,
    typename T_arg3 = QEXTNil,
    typename T_arg4 = QEXTNil,
    typename T_arg5 = QEXTNil,
    typename T_arg6 = QEXTNil,
    typename T_arg7 = QEXTNil >
class QEXTBoundVolatileMemberFunctor : public qextPrivate::QEXTBoundVolatileMemberFunctor7< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
{
    typedef qextPrivate::QEXTBoundVolatileMemberFunctor7< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTBoundVolatileMemberFunctor(T_obj *obj, Function func) : Base(obj, func) {}
    QEXTBoundVolatileMemberFunctor(T_obj &obj, Function func) : Base(obj, func) {}
    QEXTBoundVolatileMemberFunctor(const QEXTBoundVolatileMemberFunctor &other) : Base(other) {}

    T_return operator()(
        typename QEXTTypeTrait< T_arg1 >::Take arg1,
        typename QEXTTypeTrait< T_arg2 >::Take arg2,
        typename QEXTTypeTrait< T_arg3 >::Take arg3,
        typename QEXTTypeTrait< T_arg4 >::Take arg4,
        typename QEXTTypeTrait< T_arg5 >::Take arg5,
        typename QEXTTypeTrait< T_arg6 >::Take arg6,
        typename QEXTTypeTrait< T_arg7 >::Take arg7) const
    {
        return Base::operator()(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

template <
    typename T_return,
    typename T_obj,
    typename T_arg1,
    typename T_arg2,
    typename T_arg3,
    typename T_arg4,
    typename T_arg5,
    typename T_arg6,
    typename T_arg7 >
struct QEXTVisitor< QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 > >
{
    template < typename T_action >
    static void
    doVisitEach(const T_action &action, const QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 > &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
class QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QEXTNil >
    : public qextPrivate::QEXTBoundVolatileMemberFunctor6< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
{
    typedef qextPrivate::QEXTBoundVolatileMemberFunctor6< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTBoundVolatileMemberFunctor(T_obj *obj, Function func) : Base(obj, func) {}
    QEXTBoundVolatileMemberFunctor(T_obj &obj, Function func) : Base(obj, func) {}
    QEXTBoundVolatileMemberFunctor(const QEXTBoundVolatileMemberFunctor &other) : Base(other) {}

    T_return operator()(
        typename QEXTTypeTrait< T_arg1 >::Take arg1,
        typename QEXTTypeTrait< T_arg2 >::Take arg2,
        typename QEXTTypeTrait< T_arg3 >::Take arg3,
        typename QEXTTypeTrait< T_arg4 >::Take arg4,
        typename QEXTTypeTrait< T_arg5 >::Take arg5,
        typename QEXTTypeTrait< T_arg6 >::Take arg6) const
    {
        return Base::operator()(arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
struct QEXTVisitor< QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 > >
{
    template < typename T_action >
    static void
    doVisitEach(const T_action &action, const QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 > &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
class QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QEXTNil, QEXTNil >
    : public qextPrivate::QEXTBoundVolatileMemberFunctor5< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
{
    typedef qextPrivate::QEXTBoundVolatileMemberFunctor5< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTBoundVolatileMemberFunctor(T_obj *obj, Function func) : Base(obj, func) {}
    QEXTBoundVolatileMemberFunctor(T_obj &obj, Function func) : Base(obj, func) {}
    QEXTBoundVolatileMemberFunctor(const QEXTBoundVolatileMemberFunctor &other) : Base(other) {}

    T_return operator()(
        typename QEXTTypeTrait< T_arg1 >::Take arg1,
        typename QEXTTypeTrait< T_arg2 >::Take arg2,
        typename QEXTTypeTrait< T_arg3 >::Take arg3,
        typename QEXTTypeTrait< T_arg4 >::Take arg4,
        typename QEXTTypeTrait< T_arg5 >::Take arg5) const
    {
        return Base::operator()(arg1, arg2, arg3, arg4, arg5);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
struct QEXTVisitor< QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 > >
{
    template < typename T_action >
    static void doVisitEach(const T_action &action, const QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 > &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
class QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, QEXTNil, QEXTNil, QEXTNil >
    : public qextPrivate::QEXTBoundVolatileMemberFunctor4< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >
{
    typedef qextPrivate::QEXTBoundVolatileMemberFunctor4< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTBoundVolatileMemberFunctor(T_obj *obj, Function func) : Base(obj, func) {}
    QEXTBoundVolatileMemberFunctor(T_obj &obj, Function func) : Base(obj, func) {}
    QEXTBoundVolatileMemberFunctor(const QEXTBoundVolatileMemberFunctor &other) : Base(other) {}

    T_return operator()(
        typename QEXTTypeTrait< T_arg1 >::Take arg1,
        typename QEXTTypeTrait< T_arg2 >::Take arg2,
        typename QEXTTypeTrait< T_arg3 >::Take arg3,
        typename QEXTTypeTrait< T_arg4 >::Take arg4) const
    {
        return Base::operator()(arg1, arg2, arg3, arg4);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
struct QEXTVisitor< QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 > >
{
    template < typename T_action >
    static void doVisitEach(const T_action &action, const QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 > &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3 >
class QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, QEXTNil, QEXTNil, QEXTNil, QEXTNil >
    : public qextPrivate::QEXTBoundVolatileMemberFunctor3< T_return, T_obj, T_arg1, T_arg2, T_arg3 >
{
    typedef qextPrivate::QEXTBoundVolatileMemberFunctor3< T_return, T_obj, T_arg1, T_arg2, T_arg3 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTBoundVolatileMemberFunctor(T_obj *obj, Function func) : Base(obj, func) {}
    QEXTBoundVolatileMemberFunctor(T_obj &obj, Function func) : Base(obj, func) {}
    QEXTBoundVolatileMemberFunctor(const QEXTBoundVolatileMemberFunctor &other) : Base(other) {}

    T_return operator()(typename QEXTTypeTrait< T_arg1 >::Take arg1, typename QEXTTypeTrait< T_arg2 >::Take arg2, typename QEXTTypeTrait< T_arg3 >::Take arg3) const
    {
        return Base::operator()(arg1, arg2, arg3);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3 >
struct QEXTVisitor< QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 > >
{
    template < typename T_action >
    static void doVisitEach(const T_action &action, const QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 > &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2 >
class QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil >
    : public qextPrivate::QEXTBoundVolatileMemberFunctor2< T_return, T_obj, T_arg1, T_arg2 >
{
    typedef qextPrivate::QEXTBoundVolatileMemberFunctor2< T_return, T_obj, T_arg1, T_arg2 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTBoundVolatileMemberFunctor(T_obj *obj, Function func) : Base(obj, func) {}
    QEXTBoundVolatileMemberFunctor(T_obj &obj, Function func) : Base(obj, func) {}
    QEXTBoundVolatileMemberFunctor(const QEXTBoundVolatileMemberFunctor &other) : Base(other) {}

    T_return operator()(typename QEXTTypeTrait< T_arg1 >::Take arg1, typename QEXTTypeTrait< T_arg2 >::Take arg2) const
    {
        return Base::operator()(arg1, arg2);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2 >
struct QEXTVisitor< QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2 > >
{
    template < typename T_action >
    static void doVisitEach(const T_action &action, const QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2 > &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template < typename T_return, typename T_obj, typename T_arg1 >
class QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil >
    : public qextPrivate::QEXTBoundVolatileMemberFunctor1< T_return, T_obj, T_arg1 >
{
    typedef qextPrivate::QEXTBoundVolatileMemberFunctor1< T_return, T_obj, T_arg1 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTBoundVolatileMemberFunctor(T_obj *obj, Function func) : Base(obj, func) {}
    QEXTBoundVolatileMemberFunctor(T_obj &obj, Function func) : Base(obj, func) {}
    QEXTBoundVolatileMemberFunctor(const QEXTBoundVolatileMemberFunctor &other) : Base(other) {}

    T_return operator()(typename QEXTTypeTrait< T_arg1 >::Take arg1) const
    {
        return Base::operator()(arg1);
    }
};

template < typename T_return, typename T_obj, typename T_arg1 >
struct QEXTVisitor< QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1 > >
{
    template < typename T_action >
    static void doVisitEach(const T_action &action, const QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1 > &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template < typename T_return, typename T_obj >
class QEXTBoundVolatileMemberFunctor< T_return, T_obj, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil > : public qextPrivate::QEXTBoundVolatileMemberFunctor0< T_return, T_obj >
{
    typedef qextPrivate::QEXTBoundVolatileMemberFunctor0< T_return, T_obj > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTBoundVolatileMemberFunctor(T_obj *obj, Function func) : Base(obj, func) {}
    QEXTBoundVolatileMemberFunctor(T_obj &obj, Function func) : Base(obj, func) {}
    QEXTBoundVolatileMemberFunctor(const QEXTBoundVolatileMemberFunctor &other) : Base(other) {}

    T_return operator()() const
    {
        return Base::operator()();
    }
};

template < typename T_return, typename T_obj >
struct QEXTVisitor< QEXTBoundVolatileMemberFunctor< T_return, T_obj > >
{
    template < typename T_action >
    static void doVisitEach(const T_action &action, const QEXTBoundVolatileMemberFunctor< T_return, T_obj > &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template <
    typename T_return,
    typename T_obj,
    typename T_arg1 = QEXTNil,
    typename T_arg2 = QEXTNil,
    typename T_arg3 = QEXTNil,
    typename T_arg4 = QEXTNil,
    typename T_arg5 = QEXTNil,
    typename T_arg6 = QEXTNil,
    typename T_arg7 = QEXTNil >
class QEXTBoundConstVolatileMemberFunctor : public qextPrivate::QEXTBoundConstVolatileMemberFunctor7< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
{
    typedef qextPrivate::QEXTBoundConstVolatileMemberFunctor7< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTBoundConstVolatileMemberFunctor(const T_obj *obj, Function func) : Base(obj, func) {}
    QEXTBoundConstVolatileMemberFunctor(const T_obj &obj, Function func) : Base(obj, func) {}
    QEXTBoundConstVolatileMemberFunctor(const QEXTBoundConstVolatileMemberFunctor &other) : Base(other) {}

    T_return operator()(
        typename QEXTTypeTrait< T_arg1 >::Take arg1,
        typename QEXTTypeTrait< T_arg2 >::Take arg2,
        typename QEXTTypeTrait< T_arg3 >::Take arg3,
        typename QEXTTypeTrait< T_arg4 >::Take arg4,
        typename QEXTTypeTrait< T_arg5 >::Take arg5,
        typename QEXTTypeTrait< T_arg6 >::Take arg6,
        typename QEXTTypeTrait< T_arg7 >::Take arg7) const
    {
        return Base::operator()(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

template <
    typename T_return,
    typename T_obj,
    typename T_arg1,
    typename T_arg2,
    typename T_arg3,
    typename T_arg4,
    typename T_arg5,
    typename T_arg6,
    typename T_arg7 >
struct QEXTVisitor< QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 > >
{
    template < typename T_action >
    static void doVisitEach(
        const T_action &action, const QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 > &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
class QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QEXTNil >
    : public qextPrivate::QEXTBoundConstVolatileMemberFunctor6< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
{
    typedef qextPrivate::QEXTBoundConstVolatileMemberFunctor6< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTBoundConstVolatileMemberFunctor(const T_obj *obj, Function func) : Base(obj, func) {}
    QEXTBoundConstVolatileMemberFunctor(const T_obj &obj, Function func) : Base(obj, func) {}
    QEXTBoundConstVolatileMemberFunctor(const QEXTBoundConstVolatileMemberFunctor &other) : Base(other) {}

    T_return operator()(
        typename QEXTTypeTrait< T_arg1 >::Take arg1,
        typename QEXTTypeTrait< T_arg2 >::Take arg2,
        typename QEXTTypeTrait< T_arg3 >::Take arg3,
        typename QEXTTypeTrait< T_arg4 >::Take arg4,
        typename QEXTTypeTrait< T_arg5 >::Take arg5,
        typename QEXTTypeTrait< T_arg6 >::Take arg6) const
    {
        return Base::operator()(arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
struct QEXTVisitor< QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 > >
{
    template < typename T_action >
    static void
    doVisitEach(const T_action &action, const QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 > &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
class QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QEXTNil, QEXTNil >
    : public qextPrivate::QEXTBoundConstVolatileMemberFunctor5< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
{
    typedef qextPrivate::QEXTBoundConstVolatileMemberFunctor5< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTBoundConstVolatileMemberFunctor(const T_obj *obj, Function func) : Base(obj, func) {}
    QEXTBoundConstVolatileMemberFunctor(const T_obj &obj, Function func) : Base(obj, func) {}
    QEXTBoundConstVolatileMemberFunctor(const QEXTBoundConstVolatileMemberFunctor &other) : Base(other) {}

    T_return operator()(
        typename QEXTTypeTrait< T_arg1 >::Take arg1,
        typename QEXTTypeTrait< T_arg2 >::Take arg2,
        typename QEXTTypeTrait< T_arg3 >::Take arg3,
        typename QEXTTypeTrait< T_arg4 >::Take arg4,
        typename QEXTTypeTrait< T_arg5 >::Take arg5) const
    {
        return Base::operator()(arg1, arg2, arg3, arg4, arg5);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
struct QEXTVisitor< QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 > >
{
    template < typename T_action >
    static void doVisitEach(const T_action &action, const QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 > &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
class QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, QEXTNil, QEXTNil, QEXTNil >
    : public qextPrivate::QEXTBoundConstVolatileMemberFunctor4< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >
{
    typedef qextPrivate::QEXTBoundConstVolatileMemberFunctor4< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTBoundConstVolatileMemberFunctor(const T_obj *obj, Function func) : Base(obj, func) {}
    QEXTBoundConstVolatileMemberFunctor(const T_obj &obj, Function func) : Base(obj, func) {}
    QEXTBoundConstVolatileMemberFunctor(const QEXTBoundConstVolatileMemberFunctor &other) : Base(other) {}

    T_return operator()(
        typename QEXTTypeTrait< T_arg1 >::Take arg1,
        typename QEXTTypeTrait< T_arg2 >::Take arg2,
        typename QEXTTypeTrait< T_arg3 >::Take arg3,
        typename QEXTTypeTrait< T_arg4 >::Take arg4) const
    {
        return Base::operator()(arg1, arg2, arg3, arg4);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
struct QEXTVisitor< QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 > >
{
    template < typename T_action >
    static void doVisitEach(const T_action &action, const QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 > &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3 >
class QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, QEXTNil, QEXTNil, QEXTNil, QEXTNil >
    : public qextPrivate::QEXTBoundConstVolatileMemberFunctor3< T_return, T_obj, T_arg1, T_arg2, T_arg3 >
{
    typedef qextPrivate::QEXTBoundConstVolatileMemberFunctor3< T_return, T_obj, T_arg1, T_arg2, T_arg3 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTBoundConstVolatileMemberFunctor(const T_obj *obj, Function func) : Base(obj, func) {}
    QEXTBoundConstVolatileMemberFunctor(const T_obj &obj, Function func) : Base(obj, func) {}
    QEXTBoundConstVolatileMemberFunctor(const QEXTBoundConstVolatileMemberFunctor &other) : Base(other) {}

    T_return operator()(typename QEXTTypeTrait< T_arg1 >::Take arg1, typename QEXTTypeTrait< T_arg2 >::Take arg2, typename QEXTTypeTrait< T_arg3 >::Take arg3) const
    {
        return Base::operator()(arg1, arg2, arg3);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3 >
struct QEXTVisitor< QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 > >
{
    template < typename T_action >
    static void doVisitEach(const T_action &action, const QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 > &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2 >
class QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil >
    : public qextPrivate::QEXTBoundConstVolatileMemberFunctor2< T_return, T_obj, T_arg1, T_arg2 >
{
    typedef qextPrivate::QEXTBoundConstVolatileMemberFunctor2< T_return, T_obj, T_arg1, T_arg2 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTBoundConstVolatileMemberFunctor(const T_obj *obj, Function func) : Base(obj, func) {}
    QEXTBoundConstVolatileMemberFunctor(const T_obj &obj, Function func) : Base(obj, func) {}
    QEXTBoundConstVolatileMemberFunctor(const QEXTBoundConstVolatileMemberFunctor &other) : Base(other) {}

    T_return operator()(typename QEXTTypeTrait< T_arg1 >::Take arg1, typename QEXTTypeTrait< T_arg2 >::Take arg2) const
    {
        return Base::operator()(arg1, arg2);
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2 >
struct QEXTVisitor< QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2 > >
{
    template < typename T_action >
    static void doVisitEach(const T_action &action, const QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2 > &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template < typename T_return, typename T_obj, typename T_arg1 >
class QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil >
    : public qextPrivate::QEXTBoundConstVolatileMemberFunctor1< T_return, T_obj, T_arg1 >
{
    typedef qextPrivate::QEXTBoundConstVolatileMemberFunctor1< T_return, T_obj, T_arg1 > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTBoundConstVolatileMemberFunctor(const T_obj *obj, Function func) : Base(obj, func) {}
    QEXTBoundConstVolatileMemberFunctor(const T_obj &obj, Function func) : Base(obj, func) {}
    QEXTBoundConstVolatileMemberFunctor(const QEXTBoundConstVolatileMemberFunctor &other) : Base(other) {}

    T_return operator()(typename QEXTTypeTrait< T_arg1 >::Take arg1) const
    {
        return Base::operator()(arg1);
    }
};

template < typename T_return, typename T_obj, typename T_arg1 >
struct QEXTVisitor< QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1 > >
{
    template < typename T_action >
    static void doVisitEach(const T_action &action, const QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1 > &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template < typename T_return, typename T_obj >
class QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil >
    : public qextPrivate::QEXTBoundConstVolatileMemberFunctor0< T_return, T_obj >
{
    typedef qextPrivate::QEXTBoundConstVolatileMemberFunctor0< T_return, T_obj > Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTBoundConstVolatileMemberFunctor(const T_obj *obj, Function func) : Base(obj, func) {}
    QEXTBoundConstVolatileMemberFunctor(const T_obj &obj, Function func) : Base(obj, func) {}
    QEXTBoundConstVolatileMemberFunctor(const QEXTBoundConstVolatileMemberFunctor &other) : Base(other) {}

    T_return operator()() const
    {
        return Base::operator()();
    }
};

template < typename T_return, typename T_obj >
struct QEXTVisitor< QEXTBoundConstVolatileMemberFunctor< T_return, T_obj > >
{
    template < typename T_action >
    static void doVisitEach(const T_action &action, const QEXTBoundConstVolatileMemberFunctor< T_return, T_obj > &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

/** Creates a functor of type QEXTMemberFunctor which wraps a method with 7 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template <
    typename T_return,
    typename T_obj,
    typename T_arg1,
    typename T_arg2,
    typename T_arg3,
    typename T_arg4,
    typename T_arg5,
    typename T_arg6,
    typename T_arg7 >
inline QEXTMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
    qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7))
{
    return QEXTMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(func);
}

/** Creates a functor of type QEXTMemberFunctor which wraps a method with 6 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
inline QEXTMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
    qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6))
{
    return QEXTMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(func);
}

/** Creates a functor of type QEXTMemberFunctor which wraps a method with 5 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
inline QEXTMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
    qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5))
{
    return QEXTMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(func);
}

/** Creates a functor of type QEXTMemberFunctor which wraps a method with 4 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
inline QEXTMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 > qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4))
{
    return QEXTMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >(func);
}

/** Creates a functor of type QEXTMemberFunctor which wraps a method with 3 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3 >
inline QEXTMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 > qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3))
{
    return QEXTMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 >(func);
}

/** Creates a functor of type QEXTMemberFunctor which wraps a method with 2 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2 >
inline QEXTMemberFunctor< T_return, T_obj, T_arg1, T_arg2 > qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2))
{
    return QEXTMemberFunctor< T_return, T_obj, T_arg1, T_arg2 >(func);
}

/** Creates a functor of type QEXTMemberFunctor which wraps a method with 1 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1 >
inline QEXTMemberFunctor< T_return, T_obj, T_arg1 > qextMemberFunctor(T_return (T_obj::*func)(T_arg1))
{
    return QEXTMemberFunctor< T_return, T_obj, T_arg1 >(func);
}

/** Creates a functor of type QEXTMemberFunctor which wraps a method with no args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj >
inline QEXTMemberFunctor< T_return, T_obj > qextMemberFunctor(T_return (T_obj::*func)())
{
    return QEXTMemberFunctor< T_return, T_obj >(func);
}

/** Creates a functor of type QEXTConstMemberFunctor which wraps a const method with 7 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template <
    typename T_return,
    typename T_obj,
    typename T_arg1,
    typename T_arg2,
    typename T_arg3,
    typename T_arg4,
    typename T_arg5,
    typename T_arg6,
    typename T_arg7 >
inline QEXTConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const)
{
    return QEXTConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(func);
}

/** Creates a functor of type QEXTConstMemberFunctor which wraps a const method with 6 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
inline QEXTConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const)
{
    return QEXTConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(func);
}

/** Creates a functor of type QEXTConstMemberFunctor which wraps a const method with 5 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
inline QEXTConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const)
{
    return QEXTConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(func);
}

/** Creates a functor of type QEXTConstMemberFunctor which wraps a const method with 4 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
inline QEXTConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 > qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4) const)
{
    return QEXTConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >(func);
}

/** Creates a functor of type QEXTConstMemberFunctor which wraps a const method with 3 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3 >
inline QEXTConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 > qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3) const)
{
    return QEXTConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 >(func);
}

/** Creates a functor of type QEXTConstMemberFunctor which wraps a const method with 2 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2 >
inline QEXTConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2 > qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2) const)
{
    return QEXTConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2 >(func);
}

/** Creates a functor of type QEXTConstMemberFunctor which wraps a const method with 1 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1 >
inline QEXTConstMemberFunctor< T_return, T_obj, T_arg1 > qextMemberFunctor(T_return (T_obj::*func)(T_arg1) const)
{
    return QEXTConstMemberFunctor< T_return, T_obj, T_arg1 >(func);
}

/** Creates a functor of type QEXTConstMemberFunctor which wraps a const method with no args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj >
inline QEXTConstMemberFunctor< T_return, T_obj > qextMemberFunctor(T_return (T_obj::*func)() const)
{
    return QEXTConstMemberFunctor< T_return, T_obj >(func);
}

/** Creates a functor of type QEXTVolatileMemberFunctor which wraps a volatile method with 7 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template <
    typename T_return,
    typename T_obj,
    typename T_arg1,
    typename T_arg2,
    typename T_arg3,
    typename T_arg4,
    typename T_arg5,
    typename T_arg6,
    typename T_arg7 >
inline QEXTVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
    qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) volatile)
{
    return QEXTVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(func);
}

/** Creates a functor of type QEXTVolatileMemberFunctor which wraps a volatile method with 6 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
inline QEXTVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
    qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) volatile)
{
    return QEXTVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(func);
}

/** Creates a functor of type QEXTVolatileMemberFunctor which wraps a volatile method with 5 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
inline QEXTVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
    qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) volatile)
{
    return QEXTVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(func);
}

/** Creates a functor of type QEXTVolatileMemberFunctor which wraps a volatile method with 4 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
inline QEXTVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >
    qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4) volatile)
{
    return QEXTVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >(func);
}

/** Creates a functor of type QEXTVolatileMemberFunctor which wraps a volatile method with 3 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3 >
inline QEXTVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 > qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3) volatile)
{
    return QEXTVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 >(func);
}

/** Creates a functor of type QEXTVolatileMemberFunctor which wraps a volatile method with 2 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2 >
inline QEXTVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2 > qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2) volatile)
{
    return QEXTVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2 >(func);
}

/** Creates a functor of type QEXTVolatileMemberFunctor which wraps a volatile method with 1 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1 >
inline QEXTVolatileMemberFunctor< T_return, T_obj, T_arg1 > qextMemberFunctor(T_return (T_obj::*func)(T_arg1) volatile)
{
    return QEXTVolatileMemberFunctor< T_return, T_obj, T_arg1 >(func);
}

/** Creates a functor of type QEXTVolatileMemberFunctor which wraps a volatile method with no args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj >
inline QEXTVolatileMemberFunctor< T_return, T_obj > qextMemberFunctor(T_return (T_obj::*func)() volatile)
{
    return QEXTVolatileMemberFunctor< T_return, T_obj >(func);
}

/** Creates a functor of type QEXTConstVolatileMemberFunctor which wraps a const volatile method with 7 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template <
    typename T_return,
    typename T_obj,
    typename T_arg1,
    typename T_arg2,
    typename T_arg3,
    typename T_arg4,
    typename T_arg5,
    typename T_arg6,
    typename T_arg7 >
inline QEXTConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const volatile)
{
    return QEXTConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(func);
}

/** Creates a functor of type QEXTConstVolatileMemberFunctor which wraps a const volatile method with 6 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
inline QEXTConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const volatile)
{
    return QEXTConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(func);
}

/** Creates a functor of type QEXTConstVolatileMemberFunctor which wraps a const volatile method with 5 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
inline QEXTConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const volatile)
{
    return QEXTConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(func);
}

/** Creates a functor of type QEXTConstVolatileMemberFunctor which wraps a const volatile method with 4 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
inline QEXTConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 > qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4)
                                                                                                           const volatile)
{
    return QEXTConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >(func);
}

/** Creates a functor of type QEXTConstVolatileMemberFunctor which wraps a const volatile method with 3 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3 >
inline QEXTConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 > qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3) const volatile)
{
    return QEXTConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 >(func);
}

/** Creates a functor of type QEXTConstVolatileMemberFunctor which wraps a const volatile method with 2 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2 >
inline QEXTConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2 > qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2) const volatile)
{
    return QEXTConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2 >(func);
}

/** Creates a functor of type QEXTConstVolatileMemberFunctor which wraps a const volatile method with 1 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1 >
inline QEXTConstVolatileMemberFunctor< T_return, T_obj, T_arg1 > qextMemberFunctor(T_return (T_obj::*func)(T_arg1) const volatile)
{
    return QEXTConstVolatileMemberFunctor< T_return, T_obj, T_arg1 >(func);
}

/** Creates a functor of type QEXTConstVolatileMemberFunctor which wraps a const volatile method with no args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj >
inline QEXTConstVolatileMemberFunctor< T_return, T_obj > qextMemberFunctor(T_return (T_obj::*func)() const volatile)
{
    return QEXTConstVolatileMemberFunctor< T_return, T_obj >(func);
}

/** Creates a functor of type QEXTBoundMemberFunctor0 which encapsulates a method and an object instance with 7 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template <
    typename T_return,
    typename T_obj,
    typename T_arg1,
    typename T_arg2,
    typename T_arg3,
    typename T_arg4,
    typename T_arg5,
    typename T_arg6,
    typename T_arg7 >
inline QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7))
{
    return QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(obj, func);
}

/** Creates a functor of type QEXTBoundMemberFunctor which encapsulates a method and an object instance with 7 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template <
    typename T_return,
    typename T_obj,
    typename T_arg1,
    typename T_arg2,
    typename T_arg3,
    typename T_arg4,
    typename T_arg5,
    typename T_arg6,
    typename T_arg7 >
inline QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7))
{
    return QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(obj, func);
}

/** Creates a functor of type QEXTBoundMemberFunctor0 which encapsulates a method and an object instance with 6 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
inline QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6))
{
    return QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(obj, func);
}

/** Creates a functor of type QEXTBoundMemberFunctor which encapsulates a method and an object instance with 6 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
inline QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6))
{
    return QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(obj, func);
}

/** Creates a functor of type QEXTBoundMemberFunctor0 which encapsulates a method and an object instance with 5 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
inline QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5))
{
    return QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(obj, func);
}

/** Creates a functor of type QEXTBoundMemberFunctor which encapsulates a method and an object instance with 5 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
inline QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5))
{
    return QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(obj, func);
}

/** Creates a functor of type QEXTBoundMemberFunctor0 which encapsulates a method and an object instance with 4 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
inline QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >
qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4))
{
    return QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >(obj, func);
}

/** Creates a functor of type QEXTBoundMemberFunctor which encapsulates a method and an object instance with 4 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
inline QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >
qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4))
{
    return QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >(obj, func);
}

/** Creates a functor of type QEXTBoundMemberFunctor0 which encapsulates a method and an object instance with 3 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3 >
inline QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 > qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3))
{
    return QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 >(obj, func);
}

/** Creates a functor of type QEXTBoundMemberFunctor which encapsulates a method and an object instance with 3 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3 >
inline QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 > qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3))
{
    return QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 >(obj, func);
}

/** Creates a functor of type QEXTBoundMemberFunctor0 which encapsulates a method and an object instance with 2 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2 >
inline QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2 > qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2))
{
    return QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2 >(obj, func);
}

/** Creates a functor of type QEXTBoundMemberFunctor which encapsulates a method and an object instance with 2 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2 >
inline QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2 > qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2))
{
    return QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2 >(obj, func);
}

/** Creates a functor of type QEXTBoundMemberFunctor0 which encapsulates a method and an object instance with 1 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1 >
inline QEXTBoundMemberFunctor< T_return, T_obj, T_arg1 > qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1))
{
    return QEXTBoundMemberFunctor< T_return, T_obj, T_arg1 >(obj, func);
}

/** Creates a functor of type QEXTBoundMemberFunctor which encapsulates a method and an object instance with 1 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1 >
inline QEXTBoundMemberFunctor< T_return, T_obj, T_arg1 > qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1))
{
    return QEXTBoundMemberFunctor< T_return, T_obj, T_arg1 >(obj, func);
}

/** Creates a functor of type QEXTBoundMemberFunctor0 which encapsulates a method and an object instance with no args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj >
inline QEXTBoundMemberFunctor< T_return, T_obj > qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)())
{
    return QEXTBoundMemberFunctor< T_return, T_obj >(obj, func);
}

/** Creates a functor of type QEXTBoundMemberFunctor which encapsulates a method and an object instance with no args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj >
inline QEXTBoundMemberFunctor< T_return, T_obj > qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)())
{
    return QEXTBoundMemberFunctor< T_return, T_obj >(obj, func);
}

/** Creates a functor of type QEXTBoundConstMemberFunctor which encapsulates a method and an object instance with 7 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template <
    typename T_return,
    typename T_obj,
    typename T_arg1,
    typename T_arg2,
    typename T_arg3,
    typename T_arg4,
    typename T_arg5,
    typename T_arg6,
    typename T_arg7 >
inline QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const)
{
    return QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(obj, func);
}

/** Creates a functor of type QEXTBoundConstMemberFunctor which encapsulates a method and an object instance with 7 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template <
    typename T_return,
    typename T_obj,
    typename T_arg1,
    typename T_arg2,
    typename T_arg3,
    typename T_arg4,
    typename T_arg5,
    typename T_arg6,
    typename T_arg7 >
inline QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const)
{
    return QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(obj, func);
}

/** Creates a functor of type QEXTBoundConstMemberFunctor which encapsulates a method and an object instance with 6 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
inline QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const)
{
    return QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(obj, func);
}

/** Creates a functor of type QEXTBoundConstMemberFunctor which encapsulates a method and an object instance with 6 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
inline QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const)
{
    return QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(obj, func);
}

/** Creates a functor of type QEXTBoundConstMemberFunctor which encapsulates a method and an object instance with 5 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
inline QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const)
{
    return QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(obj, func);
}

/** Creates a functor of type QEXTBoundConstMemberFunctor which encapsulates a method and an object instance with 5 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
inline QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const)
{
    return QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(obj, func);
}

/** Creates a functor of type QEXTBoundConstMemberFunctor which encapsulates a method and an object instance with 4 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
inline QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >
qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4) const)
{
    return QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >(obj, func);
}

/** Creates a functor of type QEXTBoundConstMemberFunctor which encapsulates a method and an object instance with 4 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
inline QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >
qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4) const)
{
    return QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >(obj, func);
}

/** Creates a functor of type QEXTBoundConstMemberFunctor which encapsulates a method and an object instance with 3 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3 >
inline QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 > qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3) const)
{
    return QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 >(obj, func);
}

/** Creates a functor of type QEXTBoundConstMemberFunctor which encapsulates a method and an object instance with 3 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3 >
inline QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 > qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3) const)
{
    return QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 >(obj, func);
}

/** Creates a functor of type QEXTBoundConstMemberFunctor which encapsulates a method and an object instance with 2 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2 >
inline QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2 > qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2) const)
{
    return QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2 >(obj, func);
}

/** Creates a functor of type QEXTBoundConstMemberFunctor which encapsulates a method and an object instance with 2 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2 >
inline QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2 > qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2) const)
{
    return QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2 >(obj, func);
}

/** Creates a functor of type QEXTBoundConstMemberFunctor which encapsulates a method and an object instance with 1 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1 >
inline QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1 > qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1) const)
{
    return QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1 >(obj, func);
}

/** Creates a functor of type QEXTBoundConstMemberFunctor which encapsulates a method and an object instance with 1 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1 >
inline QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1 > qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1) const)
{
    return QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1 >(obj, func);
}

/** Creates a functor of type QEXTBoundConstMemberFunctor which encapsulates a method and an object instance with no args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj >
inline QEXTBoundConstMemberFunctor< T_return, T_obj > qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)() const)
{
    return QEXTBoundConstMemberFunctor< T_return, T_obj >(obj, func);
}

/** Creates a functor of type QEXTBoundConstMemberFunctor which encapsulates a method and an object instance with no args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj >
inline QEXTBoundConstMemberFunctor< T_return, T_obj > qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)() const)
{
    return QEXTBoundConstMemberFunctor< T_return, T_obj >(obj, func);
}

/** Creates a functor of type QEXTBoundVolatileMemberFunctor which encapsulates a method and an object instance with 7 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template <
    typename T_return,
    typename T_obj,
    typename T_arg1,
    typename T_arg2,
    typename T_arg3,
    typename T_arg4,
    typename T_arg5,
    typename T_arg6,
    typename T_arg7 >
inline QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) volatile)
{
    return QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(obj, func);
}

/** Creates a functor of type QEXTBoundVolatileMemberFunctor which encapsulates a method and an object instance with 7 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template <
    typename T_return,
    typename T_obj,
    typename T_arg1,
    typename T_arg2,
    typename T_arg3,
    typename T_arg4,
    typename T_arg5,
    typename T_arg6,
    typename T_arg7 >
inline QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) volatile)
{
    return QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(obj, func);
}

/** Creates a functor of type QEXTBoundVolatileMemberFunctor which encapsulates a method and an object instance with 6 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
inline QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) volatile)
{
    return QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(obj, func);
}

/** Creates a functor of type QEXTBoundVolatileMemberFunctor which encapsulates a method and an object instance with 6 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
inline QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) volatile)
{
    return QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(obj, func);
}

/** Creates a functor of type QEXTBoundVolatileMemberFunctor which encapsulates a method and an object instance with 5 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
inline QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) volatile)
{
    return QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(obj, func);
}

/** Creates a functor of type QEXTBoundVolatileMemberFunctor which encapsulates a method and an object instance with 5 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
inline QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) volatile)
{
    return QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(obj, func);
}

/** Creates a functor of type QEXTBoundVolatileMemberFunctor which encapsulates a method and an object instance with 4 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
inline QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >
qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4) volatile)
{
    return QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >(obj, func);
}

/** Creates a functor of type QEXTBoundVolatileMemberFunctor which encapsulates a method and an object instance with 4 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
inline QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >
qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4) volatile)
{
    return QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >(obj, func);
}

/** Creates a functor of type QEXTBoundVolatileMemberFunctor which encapsulates a method and an object instance with 3 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3 >
inline QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 >
qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3) volatile)
{
    return QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 >(obj, func);
}

/** Creates a functor of type QEXTBoundVolatileMemberFunctor which encapsulates a method and an object instance with 3 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3 >
inline QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 >
qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3) volatile)
{
    return QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 >(obj, func);
}

/** Creates a functor of type QEXTBoundVolatileMemberFunctor which encapsulates a method and an object instance with 2 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2 >
inline QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2 > qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2) volatile)
{
    return QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2 >(obj, func);
}

/** Creates a functor of type QEXTBoundVolatileMemberFunctor which encapsulates a method and an object instance with 2 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2 >
inline QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2 > qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2) volatile)
{
    return QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2 >(obj, func);
}

/** Creates a functor of type QEXTBoundVolatileMemberFunctor which encapsulates a method and an object instance with 1 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1 >
inline QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1 > qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1) volatile)
{
    return QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1 >(obj, func);
}

/** Creates a functor of type QEXTBoundVolatileMemberFunctor which encapsulates a method and an object instance with 1 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1 >
inline QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1 > qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1) volatile)
{
    return QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1 >(obj, func);
}

/** Creates a functor of type QEXTBoundVolatileMemberFunctor which encapsulates a method and an object instance with no args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj >
inline QEXTBoundVolatileMemberFunctor< T_return, T_obj > qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)() volatile)
{
    return QEXTBoundVolatileMemberFunctor< T_return, T_obj >(obj, func);
}

/** Creates a functor of type QEXTBoundVolatileMemberFunctor which encapsulates a method and an object instance with no args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj >
inline QEXTBoundVolatileMemberFunctor< T_return, T_obj > qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)() volatile)
{
    return QEXTBoundVolatileMemberFunctor< T_return, T_obj >(obj, func);
}

/** Creates a functor of type QEXTBoundConstVolatileMemberFunctor which encapsulates a method and an object instance with 7 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template <
    typename T_return,
    typename T_obj,
    typename T_arg1,
    typename T_arg2,
    typename T_arg3,
    typename T_arg4,
    typename T_arg5,
    typename T_arg6,
    typename T_arg7 >
inline QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const volatile)
{
    return QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(obj, func);
}

/** Creates a functor of type QEXTBoundConstVolatileMemberFunctor which encapsulates a method and an object instance with 7 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template <
    typename T_return,
    typename T_obj,
    typename T_arg1,
    typename T_arg2,
    typename T_arg3,
    typename T_arg4,
    typename T_arg5,
    typename T_arg6,
    typename T_arg7 >
inline QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const volatile)
{
    return QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(obj, func);
}

/** Creates a functor of type QEXTBoundConstVolatileMemberFunctor which encapsulates a method and an object instance with 6 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
inline QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const volatile)
{
    return QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(obj, func);
}

/** Creates a functor of type QEXTBoundConstVolatileMemberFunctor which encapsulates a method and an object instance with 6 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
inline QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const volatile)
{
    return QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(obj, func);
}

/** Creates a functor of type QEXTBoundConstVolatileMemberFunctor which encapsulates a method and an object instance with 5 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
inline QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const volatile)
{
    return QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(obj, func);
}

/** Creates a functor of type QEXTBoundConstVolatileMemberFunctor which encapsulates a method and an object instance with 5 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
inline QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const volatile)
{
    return QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(obj, func);
}

/** Creates a functor of type QEXTBoundConstVolatileMemberFunctor which encapsulates a method and an object instance with 4 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
inline QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >
qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4) const volatile)
{
    return QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >(obj, func);
}

/** Creates a functor of type QEXTBoundConstVolatileMemberFunctor which encapsulates a method and an object instance with 4 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
inline QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >
qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4) const volatile)
{
    return QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >(obj, func);
}

/** Creates a functor of type QEXTBoundConstVolatileMemberFunctor which encapsulates a method and an object instance with 3 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3 >
inline QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 >
qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3) const volatile)
{
    return QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 >(obj, func);
}

/** Creates a functor of type QEXTBoundConstVolatileMemberFunctor which encapsulates a method and an object instance with 3 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3 >
inline QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 >
qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3) const volatile)
{
    return QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 >(obj, func);
}

/** Creates a functor of type QEXTBoundConstVolatileMemberFunctor which encapsulates a method and an object instance with 2 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2 >
inline QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2 > qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2) const volatile)
{
    return QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2 >(obj, func);
}

/** Creates a functor of type QEXTBoundConstVolatileMemberFunctor which encapsulates a method and an object instance with 2 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2 >
inline QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2 > qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2) const volatile)
{
    return QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2 >(obj, func);
}

/** Creates a functor of type QEXTBoundConstVolatileMemberFunctor which encapsulates a method and an object instance with 1 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1 >
inline QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1 > qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1) const volatile)
{
    return QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1 >(obj, func);
}

/** Creates a functor of type QEXTBoundConstVolatileMemberFunctor which encapsulates a method and an object instance with 1 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj, typename T_arg1 >
inline QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1 > qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1) const volatile)
{
    return QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1 >(obj, func);
}

/** Creates a functor of type QEXTBoundConstVolatileMemberFunctor which encapsulates a method and an object instance with no args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj >
inline QEXTBoundConstVolatileMemberFunctor< T_return, T_obj > qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)() const volatile)
{
    return QEXTBoundConstVolatileMemberFunctor< T_return, T_obj >(obj, func);
}

/** Creates a functor of type QEXTBoundConstVolatileMemberFunctor which encapsulates a method and an object instance with no args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template < typename T_return, typename T_obj >
inline QEXTBoundConstVolatileMemberFunctor< T_return, T_obj > qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)() const volatile)
{
    return QEXTBoundConstVolatileMemberFunctor< T_return, T_obj >(obj, func);
}



#endif // _QEXTMEMBERFUNCTOR_H
