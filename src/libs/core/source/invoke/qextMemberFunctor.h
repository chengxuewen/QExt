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
 * QExtFunction<void, int> slot = qextMemberFunctor(my_foo, &foo::bar);
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
 * QExtFunction<void, int> slot = qextMemberFunctor(my_foo, &foo::bar);
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
 * QExtFunction<void, int> slot = qextMemberFunctor1<int>(my_foo, &foo::bar);
 * @endcode
 *
 * \ingroup qextfunctors
 */

namespace QExtPrivate
{

    /** QExtMemberFunctor7 wraps  methods with 7 argument(s).
 * Use the convenience function qextMemberFunctor() to create an instance of QExtMemberFunctor7.
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
    template<
            typename T_return,
            typename T_obj,
            typename T_arg1,
            typename T_arg2,
            typename T_arg3,
            typename T_arg4,
            typename T_arg5,
            typename T_arg6,
            typename T_arg7>
    class QExtMemberFunctor7 : public QExtFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7);
        typedef T_return Return;

        // Constructs an invalid functor.
        QExtMemberFunctor7() : m_funcPtr(QEXT_DECL_NULLPTR) {}

        /** Constructs a QExtMemberFunctor7 object that wraps the passed method.
     * \param func Pointer to method will be invoked from operator()().
     */
        QExtMemberFunctor7(Function func) : m_funcPtr(func) {}

        QExtMemberFunctor7(const QExtMemberFunctor7 &other) : m_funcPtr(other.m_funcPtr) {}

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
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3,
                typename QExtTypeTrait<T_arg4>::Take arg4,
                typename QExtTypeTrait<T_arg5>::Take arg5,
                typename QExtTypeTrait<T_arg6>::Take arg6,
                typename QExtTypeTrait<T_arg7>::Take arg7) const
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
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3,
                typename QExtTypeTrait<T_arg4>::Take arg4,
                typename QExtTypeTrait<T_arg5>::Take arg5,
                typename QExtTypeTrait<T_arg6>::Take arg6,
                typename QExtTypeTrait<T_arg7>::Take arg7) const
        {
            return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        }

    protected:
        Function m_funcPtr;
    };

    /** QExtMemberFunctor6 wraps  methods with 6 argument(s).
 * Use the convenience function qextMemberFunctor() to create an instance of QExtMemberFunctor6.
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
    template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    class QExtMemberFunctor6 : public QExtFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6);
        typedef T_return Return;

        // Constructs an invalid functor.
        QExtMemberFunctor6() : m_funcPtr(QEXT_DECL_NULLPTR) {}

        /** Constructs a QExtMemberFunctor6 object that wraps the passed method.
     * \param func Pointer to method will be invoked from operator()().
     */
        QExtMemberFunctor6(Function func) : m_funcPtr(func) {}

        QExtMemberFunctor6(const QExtMemberFunctor6 &other) : m_funcPtr(other.m_funcPtr) {}

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
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3,
                typename QExtTypeTrait<T_arg4>::Take arg4,
                typename QExtTypeTrait<T_arg5>::Take arg5,
                typename QExtTypeTrait<T_arg6>::Take arg6) const
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
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3,
                typename QExtTypeTrait<T_arg4>::Take arg4,
                typename QExtTypeTrait<T_arg5>::Take arg5,
                typename QExtTypeTrait<T_arg6>::Take arg6) const
        {
            return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4, arg5, arg6);
        }

    protected:
        Function m_funcPtr;
    };

    /** QExtMemberFunctor5 wraps  methods with 5 argument(s).
 * Use the convenience function qextMemberFunctor() to create an instance of QExtMemberFunctor5.
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
    template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    class QExtMemberFunctor5 : public QExtFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5);
        typedef T_return Return;

        // Constructs an invalid functor.
        QExtMemberFunctor5() : m_funcPtr(QEXT_DECL_NULLPTR) {}

        /** Constructs a QExtMemberFunctor5 object that wraps the passed method.
     * \param func Pointer to method will be invoked from operator()().
     */
        QExtMemberFunctor5(Function func) : m_funcPtr(func) {}

        QExtMemberFunctor5(const QExtMemberFunctor5 &other) : m_funcPtr(other.m_funcPtr) {}

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
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3,
                typename QExtTypeTrait<T_arg4>::Take arg4,
                typename QExtTypeTrait<T_arg5>::Take arg5) const
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
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3,
                typename QExtTypeTrait<T_arg4>::Take arg4,
                typename QExtTypeTrait<T_arg5>::Take arg5) const
        {
            return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4, arg5);
        }

    protected:
        Function m_funcPtr;
    };

    /** QExtMemberFunctor4 wraps  methods with 4 argument(s).
 * Use the convenience function qextMemberFunctor() to create an instance of QExtMemberFunctor4.
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
    template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    class QExtMemberFunctor4 : public QExtFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1, T_arg2, T_arg3, T_arg4);
        typedef T_return Return;

        // Constructs an invalid functor.
        QExtMemberFunctor4() : m_funcPtr(QEXT_DECL_NULLPTR) {}

        /** Constructs a QExtMemberFunctor4 object that wraps the passed method.
     * \param func Pointer to method will be invoked from operator()().
     */
        QExtMemberFunctor4(Function func) : m_funcPtr(func) {}

        QExtMemberFunctor4(const QExtMemberFunctor4 &other) : m_funcPtr(other.m_funcPtr) {}

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
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3,
                typename QExtTypeTrait<T_arg4>::Take arg4) const
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
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3,
                typename QExtTypeTrait<T_arg4>::Take arg4) const
        {
            return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4);
        }

    protected:
        Function m_funcPtr;
    };

    /** QExtMemberFunctor3 wraps  methods with 3 argument(s).
 * Use the convenience function qextMemberFunctor() to create an instance of QExtMemberFunctor3.
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
    template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
    class QExtMemberFunctor3 : public QExtFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1, T_arg2, T_arg3);
        typedef T_return Return;

        // Constructs an invalid functor.
        QExtMemberFunctor3() : m_funcPtr(QEXT_DECL_NULLPTR) {}

        /** Constructs a QExtMemberFunctor3 object that wraps the passed method.
     * \param func Pointer to method will be invoked from operator()().
     */
        QExtMemberFunctor3(Function func) : m_funcPtr(func) {}

        QExtMemberFunctor3(const QExtMemberFunctor3 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped method operating on the passed instance.
     * \param obj Pointer to instance the method should operate on.
     * \param arg1 Argument to be passed on to the method.
     * \param arg2 Argument to be passed on to the method.
     * \param arg3 Argument to be passed on to the method.
     * \return The return value of the method invocation.
     */
        T_return operator()(
                T_obj *obj, typename QExtTypeTrait<T_arg1>::Take arg1, typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3) const
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
                T_obj &obj, typename QExtTypeTrait<T_arg1>::Take arg1, typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3) const
        {
            return (obj.*m_funcPtr)(arg1, arg2, arg3);
        }

    protected:
        Function m_funcPtr;
    };

    /** QExtMemberFunctor2 wraps  methods with 2 argument(s).
 * Use the convenience function qextMemberFunctor() to create an instance of QExtMemberFunctor2.
 *
 * The following template arguments are used:
 * - @e T_arg1 Argument type used in the definition of operator()().
 * - @e T_arg2 Argument type used in the definition of operator()().
 * - @e T_return The return type of operator()().
 * - @e T_obj The object type.
 *
 * \ingroup qextMemberFunctor
 */
    template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
    class QExtMemberFunctor2 : public QExtFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1, T_arg2);
        typedef T_return Return;

        // Constructs an invalid functor.
        QExtMemberFunctor2() : m_funcPtr(QEXT_DECL_NULLPTR) {}

        /** Constructs a QExtMemberFunctor2 object that wraps the passed method.
     * \param func Pointer to method will be invoked from operator()().
     */
        QExtMemberFunctor2(Function func) : m_funcPtr(func) {}

        QExtMemberFunctor2(const QExtMemberFunctor2 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped method operating on the passed instance.
     * \param obj Pointer to instance the method should operate on.
     * \param arg1 Argument to be passed on to the method.
     * \param arg2 Argument to be passed on to the method.
     * \return The return value of the method invocation.
     */
        T_return operator()(T_obj *obj, typename QExtTypeTrait<T_arg1>::Take arg1,
                            typename QExtTypeTrait<T_arg2>::Take arg2) const
        {
            return (obj->*(this->m_funcPtr))(arg1, arg2);
        }

        /** Execute the wrapped method operating on the passed instance.
     * \param obj Reference to instance the method should operate on.
     * \param arg1 Argument to be passed on to the method.
     * \param arg2 Argument to be passed on to the method.
     * \return The return value of the method invocation.
     */
        T_return operator()(T_obj &obj, typename QExtTypeTrait<T_arg1>::Take arg1,
                            typename QExtTypeTrait<T_arg2>::Take arg2) const
        {
            return (obj.*m_funcPtr)(arg1, arg2);
        }

    protected:
        Function m_funcPtr;
    };

    /** QExtMemberFunctor1 wraps  methods with 1 argument(s).
 * Use the convenience function qextMemberFunctor() to create an instance of QExtMemberFunctor1.
 *
 * The following template arguments are used:
 * - @e T_arg1 Argument type used in the definition of operator()().
 * - @e T_return The return type of operator()().
 * - @e T_obj The object type.
 *
 * \ingroup qextMemberFunctor
 */
    template<typename T_return, typename T_obj, typename T_arg1>
    class QExtMemberFunctor1 : public QExtFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1);
        typedef T_return Return;

        // Constructs an invalid functor.
        QExtMemberFunctor1() : m_funcPtr(QEXT_DECL_NULLPTR) {}

        /** Constructs a QExtMemberFunctor1 object that wraps the passed method.
     * \param func Pointer to method will be invoked from operator()().
     */
        QExtMemberFunctor1(Function func) : m_funcPtr(func) {}

        QExtMemberFunctor1(const QExtMemberFunctor1 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped method operating on the passed instance.
     * \param obj Pointer to instance the method should operate on.
     * \param arg1 Argument to be passed on to the method.
     * \return The return value of the method invocation.
     */
        T_return operator()(T_obj *obj, typename QExtTypeTrait<T_arg1>::Take arg1) const
        {
            return (obj->*(this->m_funcPtr))(arg1);
        }

        /** Execute the wrapped method operating on the passed instance.
     * \param obj Reference to instance the method should operate on.
     * \param arg1 Argument to be passed on to the method.
     * \return The return value of the method invocation.
     */
        T_return operator()(T_obj &obj, typename QExtTypeTrait<T_arg1>::Take arg1) const
        {
            return (obj.*m_funcPtr)(arg1);
        }

    protected:
        Function m_funcPtr;
    };

    /** QExtMemberFunctor0 wraps  methods with 0 argument(s).
 * Use the convenience function qextMemberFunctor() to create an instance of QExtMemberFunctor0.
 *
 * The following template arguments are used:
 * - @e T_return The return type of operator()().
 * - @e T_obj The object type.
 *
 * \ingroup qextMemberFunctor
 */
    template<typename T_return, typename T_obj>
    class QExtMemberFunctor0 : public QExtFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)();
        typedef T_return Return;

        // Constructs an invalid functor.
        QExtMemberFunctor0() : m_funcPtr(QEXT_DECL_NULLPTR) {}

        /** Constructs a QExtMemberFunctor0 object that wraps the passed method.
     * \param func Pointer to method will be invoked from operator()().
     */
        QExtMemberFunctor0(Function func) : m_funcPtr(func) {}

        QExtMemberFunctor0(const QExtMemberFunctor0 &other) : m_funcPtr(other.m_funcPtr) {}

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

    /** QExtConstMemberFunctor7 wraps const methods with 7 argument(s).
 * Use the convenience function qextMemberFunctor() to create an instance of QExtConstMemberFunctor7.
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
    template<
            typename T_return,
            typename T_obj,
            typename T_arg1,
            typename T_arg2,
            typename T_arg3,
            typename T_arg4,
            typename T_arg5,
            typename T_arg6,
            typename T_arg7>
    class QExtConstMemberFunctor7 : public QExtFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const;
        typedef T_return Return;

        // Constructs an invalid functor.
        QExtConstMemberFunctor7() : m_funcPtr(QEXT_DECL_NULLPTR) {}

        /** Constructs a QExtConstMemberFunctor7 object that wraps the passed method.
     * \param func Pointer to method will be invoked from operator()().
     */
        QExtConstMemberFunctor7(Function func) : m_funcPtr(func) {}

        QExtConstMemberFunctor7(const QExtConstMemberFunctor7 &other) : m_funcPtr(other.m_funcPtr) {}

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
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3,
                typename QExtTypeTrait<T_arg4>::Take arg4,
                typename QExtTypeTrait<T_arg5>::Take arg5,
                typename QExtTypeTrait<T_arg6>::Take arg6,
                typename QExtTypeTrait<T_arg7>::Take arg7) const
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
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3,
                typename QExtTypeTrait<T_arg4>::Take arg4,
                typename QExtTypeTrait<T_arg5>::Take arg5,
                typename QExtTypeTrait<T_arg6>::Take arg6,
                typename QExtTypeTrait<T_arg7>::Take arg7) const
        {
            return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        }

    protected:
        Function m_funcPtr;
    };

    /** QExtConstMemberFunctor6 wraps const methods with 6 argument(s).
 * Use the convenience function qextMemberFunctor() to create an instance of QExtConstMemberFunctor6.
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
    template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    class QExtConstMemberFunctor6 : public QExtFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const;
        typedef T_return Return;

        // Constructs an invalid functor.
        QExtConstMemberFunctor6() : m_funcPtr(QEXT_DECL_NULLPTR) {}

        /** Constructs a QExtConstMemberFunctor6 object that wraps the passed method.
     * \param func Pointer to method will be invoked from operator()().
     */
        QExtConstMemberFunctor6(Function func) : m_funcPtr(func) {}

        QExtConstMemberFunctor6(const QExtConstMemberFunctor6 &other) : m_funcPtr(other.m_funcPtr) {}

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
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3,
                typename QExtTypeTrait<T_arg4>::Take arg4,
                typename QExtTypeTrait<T_arg5>::Take arg5,
                typename QExtTypeTrait<T_arg6>::Take arg6) const
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
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3,
                typename QExtTypeTrait<T_arg4>::Take arg4,
                typename QExtTypeTrait<T_arg5>::Take arg5,
                typename QExtTypeTrait<T_arg6>::Take arg6) const
        {
            return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4, arg5, arg6);
        }

    protected:
        Function m_funcPtr;
    };

    /** QExtConstMemberFunctor5 wraps const methods with 5 argument(s).
 * Use the convenience function qextMemberFunctor() to create an instance of QExtConstMemberFunctor5.
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
    template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    class QExtConstMemberFunctor5 : public QExtFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const;
        typedef T_return Return;

        // Constructs an invalid functor.
        QExtConstMemberFunctor5() : m_funcPtr(QEXT_DECL_NULLPTR) {}

        /** Constructs a QExtConstMemberFunctor5 object that wraps the passed method.
     * \param func Pointer to method will be invoked from operator()().
     */
        QExtConstMemberFunctor5(Function func) : m_funcPtr(func) {}

        QExtConstMemberFunctor5(const QExtConstMemberFunctor5 &other) : m_funcPtr(other.m_funcPtr) {}

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
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3,
                typename QExtTypeTrait<T_arg4>::Take arg4,
                typename QExtTypeTrait<T_arg5>::Take arg5) const
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
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3,
                typename QExtTypeTrait<T_arg4>::Take arg4,
                typename QExtTypeTrait<T_arg5>::Take arg5) const
        {
            return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4, arg5);
        }

    protected:
        Function m_funcPtr;
    };

    /** QExtConstMemberFunctor4 wraps const methods with 4 argument(s).
 * Use the convenience function qextMemberFunctor() to create an instance of QExtConstMemberFunctor4.
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
    template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    class QExtConstMemberFunctor4 : public QExtFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1, T_arg2, T_arg3, T_arg4) const;
        typedef T_return Return;

        // Constructs an invalid functor.
        QExtConstMemberFunctor4() : m_funcPtr(QEXT_DECL_NULLPTR) {}

        /** Constructs a QExtConstMemberFunctor4 object that wraps the passed method.
     * \param func Pointer to method will be invoked from operator()().
     */
        QExtConstMemberFunctor4(Function func) : m_funcPtr(func) {}

        QExtConstMemberFunctor4(const QExtConstMemberFunctor4 &other) : m_funcPtr(other.m_funcPtr) {}

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
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3,
                typename QExtTypeTrait<T_arg4>::Take arg4) const
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
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3,
                typename QExtTypeTrait<T_arg4>::Take arg4) const
        {
            return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4);
        }

    protected:
        Function m_funcPtr;
    };

    /** QExtConstMemberFunctor3 wraps const methods with 3 argument(s).
 * Use the convenience function qextMemberFunctor() to create an instance of QExtConstMemberFunctor3.
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
    template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
    class QExtConstMemberFunctor3 : public QExtFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1, T_arg2, T_arg3) const;
        typedef T_return Return;

        // Constructs an invalid functor.
        QExtConstMemberFunctor3() : m_funcPtr(QEXT_DECL_NULLPTR) {}

        /** Constructs a QExtConstMemberFunctor3 object that wraps the passed method.
     * \param func Pointer to method will be invoked from operator()().
     */
        QExtConstMemberFunctor3(Function func) : m_funcPtr(func) {}

        QExtConstMemberFunctor3(const QExtConstMemberFunctor3 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped method operating on the passed instance.
     * \param obj Pointer to instance the method should operate on.
     * \param arg1 Argument to be passed on to the method.
     * \param arg2 Argument to be passed on to the method.
     * \param arg3 Argument to be passed on to the method.
     * \return The return value of the method invocation.
     */
        T_return operator()(
                const T_obj *obj,
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3) const
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
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3) const
        {
            return (obj.*m_funcPtr)(arg1, arg2, arg3);
        }

    protected:
        Function m_funcPtr;
    };

    /** QExtConstMemberFunctor2 wraps const methods with 2 argument(s).
 * Use the convenience function qextMemberFunctor() to create an instance of QExtConstMemberFunctor2.
 *
 * The following template arguments are used:
 * - @e T_arg1 Argument type used in the definition of operator()().
 * - @e T_arg2 Argument type used in the definition of operator()().
 * - @e T_return The return type of operator()().
 * - @e T_obj The object type.
 *
 * \ingroup qextMemberFunctor
 */
    template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
    class QExtConstMemberFunctor2 : public QExtFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1, T_arg2) const;
        typedef T_return Return;

        // Constructs an invalid functor.
        QExtConstMemberFunctor2() : m_funcPtr(QEXT_DECL_NULLPTR) {}

        /** Constructs a QExtConstMemberFunctor2 object that wraps the passed method.
     * \param func Pointer to method will be invoked from operator()().
     */
        QExtConstMemberFunctor2(Function func) : m_funcPtr(func) {}

        QExtConstMemberFunctor2(const QExtConstMemberFunctor2 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped method operating on the passed instance.
     * \param obj Pointer to instance the method should operate on.
     * \param arg1 Argument to be passed on to the method.
     * \param arg2 Argument to be passed on to the method.
     * \return The return value of the method invocation.
     */
        T_return operator()(const T_obj *obj, typename QExtTypeTrait<T_arg1>::Take arg1,
                            typename QExtTypeTrait<T_arg2>::Take arg2) const
        {
            return (obj->*(this->m_funcPtr))(arg1, arg2);
        }

        /** Execute the wrapped method operating on the passed instance.
     * \param obj Reference to instance the method should operate on.
     * \param arg1 Argument to be passed on to the method.
     * \param arg2 Argument to be passed on to the method.
     * \return The return value of the method invocation.
     */
        T_return operator()(const T_obj &obj, typename QExtTypeTrait<T_arg1>::Take arg1,
                            typename QExtTypeTrait<T_arg2>::Take arg2) const
        {
            return (obj.*m_funcPtr)(arg1, arg2);
        }

    protected:
        Function m_funcPtr;
    };

    /** QExtConstMemberFunctor1 wraps const methods with 1 argument(s).
 * Use the convenience function qextMemberFunctor() to create an instance of QExtConstMemberFunctor1.
 *
 * The following template arguments are used:
 * - @e T_arg1 Argument type used in the definition of operator()().
 * - @e T_return The return type of operator()().
 * - @e T_obj The object type.
 *
 * \ingroup qextMemberFunctor
 */
    template<typename T_return, typename T_obj, typename T_arg1>
    class QExtConstMemberFunctor1 : public QExtFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1) const;
        typedef T_return Return;

        // Constructs an invalid functor.
        QExtConstMemberFunctor1() : m_funcPtr(QEXT_DECL_NULLPTR) {}

        /** Constructs a QExtConstMemberFunctor1 object that wraps the passed method.
     * \param func Pointer to method will be invoked from operator()().
     */
        QExtConstMemberFunctor1(Function func) : m_funcPtr(func) {}

        QExtConstMemberFunctor1(const QExtConstMemberFunctor1 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped method operating on the passed instance.
     * \param obj Pointer to instance the method should operate on.
     * \param arg1 Argument to be passed on to the method.
     * \return The return value of the method invocation.
     */
        T_return operator()(const T_obj *obj, typename QExtTypeTrait<T_arg1>::Take arg1) const
        {
            return (obj->*(this->m_funcPtr))(arg1);
        }

        /** Execute the wrapped method operating on the passed instance.
     * \param obj Reference to instance the method should operate on.
     * \param arg1 Argument to be passed on to the method.
     * \return The return value of the method invocation.
     */
        T_return operator()(const T_obj &obj, typename QExtTypeTrait<T_arg1>::Take arg1) const
        {
            return (obj.*m_funcPtr)(arg1);
        }

    protected:
        Function m_funcPtr;
    };

    /** QExtConstMemberFunctor0 wraps const methods with 0 argument(s).
 * Use the convenience function qextMemberFunctor() to create an instance of QExtConstMemberFunctor0.
 *
 * The following template arguments are used:
 * - @e T_return The return type of operator()().
 * - @e T_obj The object type.
 *
 * \ingroup qextMemberFunctor
 */
    template<typename T_return, typename T_obj>
    class QExtConstMemberFunctor0 : public QExtFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)() const;
        typedef T_return Return;

        // Constructs an invalid functor.
        QExtConstMemberFunctor0() : m_funcPtr(QEXT_DECL_NULLPTR) {}

        /** Constructs a QExtConstMemberFunctor0 object that wraps the passed method.
     * \param func Pointer to method will be invoked from operator()().
     */
        QExtConstMemberFunctor0(Function func) : m_funcPtr(func) {}

        QExtConstMemberFunctor0(const QExtConstMemberFunctor0 &other) : m_funcPtr(other.m_funcPtr) {}

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

    /** QExtVolatileMemberFunctor7 wraps volatile methods with 7 argument(s).
     * Use the convenience function qextMemberFunctor() to create an instance of QExtVolatileMemberFunctor7.
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
    template<
            typename T_return,
            typename T_obj,
            typename T_arg1,
            typename T_arg2,
            typename T_arg3,
            typename T_arg4,
            typename T_arg5,
            typename T_arg6,
            typename T_arg7>
    class QExtVolatileMemberFunctor7 : public QExtFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) volatile;
        typedef T_return Return;

        // Constructs an invalid functor.
        QExtVolatileMemberFunctor7() : m_funcPtr(QEXT_DECL_NULLPTR) {}

        /** Constructs a QExtVolatileMemberFunctor7 object that wraps the passed method.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtVolatileMemberFunctor7(Function func) : m_funcPtr(func) {}

        QExtVolatileMemberFunctor7(const QExtVolatileMemberFunctor7 &other) : m_funcPtr(other.m_funcPtr) {}

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
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3,
                typename QExtTypeTrait<T_arg4>::Take arg4,
                typename QExtTypeTrait<T_arg5>::Take arg5,
                typename QExtTypeTrait<T_arg6>::Take arg6,
                typename QExtTypeTrait<T_arg7>::Take arg7) const
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
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3,
                typename QExtTypeTrait<T_arg4>::Take arg4,
                typename QExtTypeTrait<T_arg5>::Take arg5,
                typename QExtTypeTrait<T_arg6>::Take arg6,
                typename QExtTypeTrait<T_arg7>::Take arg7) const
        {
            return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        }

    protected:
        Function m_funcPtr;
    };

    /** QExtVolatileMemberFunctor6 wraps volatile methods with 6 argument(s).
     * Use the convenience function qextMemberFunctor() to create an instance of QExtVolatileMemberFunctor6.
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
    template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    class QExtVolatileMemberFunctor6 : public QExtFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) volatile;
        typedef T_return Return;

        // Constructs an invalid functor.
        QExtVolatileMemberFunctor6() : m_funcPtr(QEXT_DECL_NULLPTR) {}

        /** Constructs a QExtVolatileMemberFunctor6 object that wraps the passed method.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtVolatileMemberFunctor6(Function func) : m_funcPtr(func) {}

        QExtVolatileMemberFunctor6(const QExtVolatileMemberFunctor6 &other) : m_funcPtr(other.m_funcPtr) {}

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
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3,
                typename QExtTypeTrait<T_arg4>::Take arg4,
                typename QExtTypeTrait<T_arg5>::Take arg5,
                typename QExtTypeTrait<T_arg6>::Take arg6) const
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
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3,
                typename QExtTypeTrait<T_arg4>::Take arg4,
                typename QExtTypeTrait<T_arg5>::Take arg5,
                typename QExtTypeTrait<T_arg6>::Take arg6) const
        {
            return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4, arg5, arg6);
        }

    protected:
        Function m_funcPtr;
    };

    /** QExtVolatileMemberFunctor5 wraps volatile methods with 5 argument(s).
     * Use the convenience function qextMemberFunctor() to create an instance of QExtVolatileMemberFunctor5.
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
    template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    class QExtVolatileMemberFunctor5 : public QExtFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) volatile;
        typedef T_return Return;

        // Constructs an invalid functor.
        QExtVolatileMemberFunctor5() : m_funcPtr(QEXT_DECL_NULLPTR) {}

        /** Constructs a QExtVolatileMemberFunctor5 object that wraps the passed method.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtVolatileMemberFunctor5(Function func) : m_funcPtr(func) {}

        QExtVolatileMemberFunctor5(const QExtVolatileMemberFunctor5 &other) : m_funcPtr(other.m_funcPtr) {}

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
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3,
                typename QExtTypeTrait<T_arg4>::Take arg4,
                typename QExtTypeTrait<T_arg5>::Take arg5) const
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
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3,
                typename QExtTypeTrait<T_arg4>::Take arg4,
                typename QExtTypeTrait<T_arg5>::Take arg5) const
        {
            return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4, arg5);
        }

    protected:
        Function m_funcPtr;
    };

    /** QExtVolatileMemberFunctor4 wraps volatile methods with 4 argument(s).
     * Use the convenience function qextMemberFunctor() to create an instance of QExtVolatileMemberFunctor4.
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
    template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    class QExtVolatileMemberFunctor4 : public QExtFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1, T_arg2, T_arg3, T_arg4) volatile;
        typedef T_return Return;

        // Constructs an invalid functor.
        QExtVolatileMemberFunctor4() : m_funcPtr(QEXT_DECL_NULLPTR) {}

        /** Constructs a QExtVolatileMemberFunctor4 object that wraps the passed method.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtVolatileMemberFunctor4(Function func) : m_funcPtr(func) {}

        QExtVolatileMemberFunctor4(const QExtVolatileMemberFunctor4 &other) : m_funcPtr(other.m_funcPtr) {}

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
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3,
                typename QExtTypeTrait<T_arg4>::Take arg4) const
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
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3,
                typename QExtTypeTrait<T_arg4>::Take arg4) const
        {
            return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4);
        }

    protected:
        Function m_funcPtr;
    };

    /** QExtVolatileMemberFunctor3 wraps volatile methods with 3 argument(s).
     * Use the convenience function qextMemberFunctor() to create an instance of QExtVolatileMemberFunctor3.
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
    template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
    class QExtVolatileMemberFunctor3 : public QExtFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1, T_arg2, T_arg3) volatile;
        typedef T_return Return;

        // Constructs an invalid functor.
        QExtVolatileMemberFunctor3() : m_funcPtr(QEXT_DECL_NULLPTR) {}

        /** Constructs a QExtVolatileMemberFunctor3 object that wraps the passed method.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtVolatileMemberFunctor3(Function func) : m_funcPtr(func) {}

        QExtVolatileMemberFunctor3(const QExtVolatileMemberFunctor3 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped method operating on the passed instance.
         * \param obj Pointer to instance the method should operate on.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(
                T_obj *obj, typename QExtTypeTrait<T_arg1>::Take arg1, typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3) const
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
                T_obj &obj, typename QExtTypeTrait<T_arg1>::Take arg1, typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3) const
        {
            return (obj.*m_funcPtr)(arg1, arg2, arg3);
        }

    protected:
        Function m_funcPtr;
    };

    /** QExtVolatileMemberFunctor2 wraps volatile methods with 2 argument(s).
     * Use the convenience function qextMemberFunctor() to create an instance of QExtVolatileMemberFunctor2.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_arg2 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
    class QExtVolatileMemberFunctor2 : public QExtFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1, T_arg2) volatile;
        typedef T_return Return;

        // Constructs an invalid functor.
        QExtVolatileMemberFunctor2() : m_funcPtr(QEXT_DECL_NULLPTR) {}

        /** Constructs a QExtVolatileMemberFunctor2 object that wraps the passed method.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtVolatileMemberFunctor2(Function func) : m_funcPtr(func) {}

        QExtVolatileMemberFunctor2(const QExtVolatileMemberFunctor2 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped method operating on the passed instance.
         * \param obj Pointer to instance the method should operate on.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(T_obj *obj, typename QExtTypeTrait<T_arg1>::Take arg1,
                            typename QExtTypeTrait<T_arg2>::Take arg2) const
        {
            return (obj->*(this->m_funcPtr))(arg1, arg2);
        }

        /** Execute the wrapped method operating on the passed instance.
         * \param obj Reference to instance the method should operate on.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(T_obj &obj, typename QExtTypeTrait<T_arg1>::Take arg1,
                            typename QExtTypeTrait<T_arg2>::Take arg2) const
        {
            return (obj.*m_funcPtr)(arg1, arg2);
        }

    protected:
        Function m_funcPtr;
    };

    /** QExtVolatileMemberFunctor1 wraps volatile methods with 1 argument(s).
     * Use the convenience function qextMemberFunctor() to create an instance of QExtVolatileMemberFunctor1.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template<typename T_return, typename T_obj, typename T_arg1>
    class QExtVolatileMemberFunctor1 : public QExtFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1) volatile;
        typedef T_return Return;

        // Constructs an invalid functor.
        QExtVolatileMemberFunctor1() : m_funcPtr(QEXT_DECL_NULLPTR) {}

        /** Constructs a QExtVolatileMemberFunctor1 object that wraps the passed method.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtVolatileMemberFunctor1(Function func) : m_funcPtr(func) {}

        QExtVolatileMemberFunctor1(const QExtVolatileMemberFunctor1 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped method operating on the passed instance.
         * \param obj Pointer to instance the method should operate on.
         * \param arg1 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(T_obj *obj, typename QExtTypeTrait<T_arg1>::Take arg1) const
        {
            return (obj->*(this->m_funcPtr))(arg1);
        }

        /** Execute the wrapped method operating on the passed instance.
         * \param obj Reference to instance the method should operate on.
         * \param arg1 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(T_obj &obj, typename QExtTypeTrait<T_arg1>::Take arg1) const
        {
            return (obj.*m_funcPtr)(arg1);
        }

    protected:
        Function m_funcPtr;
    };

    /** QExtVolatileMemberFunctor0 wraps volatile methods with 0 argument(s).
     * Use the convenience function qextMemberFunctor() to create an instance of QExtVolatileMemberFunctor0.
     *
     * The following template arguments are used:
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template<typename T_return, typename T_obj>
    class QExtVolatileMemberFunctor0 : public QExtFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)() volatile;
        typedef T_return Return;

        // Constructs an invalid functor.
        QExtVolatileMemberFunctor0() : m_funcPtr(QEXT_DECL_NULLPTR) {}

        /** Constructs a QExtVolatileMemberFunctor0 object that wraps the passed method.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtVolatileMemberFunctor0(Function func) : m_funcPtr(func) {}

        QExtVolatileMemberFunctor0(const QExtVolatileMemberFunctor0 &other) : m_funcPtr(other.m_funcPtr) {}

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

    /** QExtConstVolatileMemberFunctor7 wraps const volatile methods with 7 argument(s).
     * Use the convenience function qextMemberFunctor() to create an instance of QExtConstVolatileMemberFunctor7.
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
    template<
            typename T_return,
            typename T_obj,
            typename T_arg1,
            typename T_arg2,
            typename T_arg3,
            typename T_arg4,
            typename T_arg5,
            typename T_arg6,
            typename T_arg7>
    class QExtConstVolatileMemberFunctor7 : public QExtFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const volatile;
        typedef T_return Return;

        // Constructs an invalid functor.
        QExtConstVolatileMemberFunctor7() : m_funcPtr(QEXT_DECL_NULLPTR) {}

        /** Constructs a QExtConstVolatileMemberFunctor7 object that wraps the passed method.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtConstVolatileMemberFunctor7(Function func) : m_funcPtr(func) {}

        QExtConstVolatileMemberFunctor7(const QExtConstVolatileMemberFunctor7 &other) : m_funcPtr(other.m_funcPtr) {}

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
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3,
                typename QExtTypeTrait<T_arg4>::Take arg4,
                typename QExtTypeTrait<T_arg5>::Take arg5,
                typename QExtTypeTrait<T_arg6>::Take arg6,
                typename QExtTypeTrait<T_arg7>::Take arg7) const
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
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3,
                typename QExtTypeTrait<T_arg4>::Take arg4,
                typename QExtTypeTrait<T_arg5>::Take arg5,
                typename QExtTypeTrait<T_arg6>::Take arg6,
                typename QExtTypeTrait<T_arg7>::Take arg7) const
        {
            return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        }

    protected:
        Function m_funcPtr;
    };

    /** QExtConstVolatileMemberFunctor6 wraps const volatile methods with 6 argument(s).
     * Use the convenience function qextMemberFunctor() to create an instance of QExtConstVolatileMemberFunctor6.
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
    template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    class QExtConstVolatileMemberFunctor6 : public QExtFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const volatile;
        typedef T_return Return;

        // Constructs an invalid functor.
        QExtConstVolatileMemberFunctor6() : m_funcPtr(QEXT_DECL_NULLPTR) {}

        /** Constructs a QExtConstVolatileMemberFunctor6 object that wraps the passed method.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtConstVolatileMemberFunctor6(Function func) : m_funcPtr(func) {}

        QExtConstVolatileMemberFunctor6(const QExtConstVolatileMemberFunctor6 &other) : m_funcPtr(other.m_funcPtr) {}

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
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3,
                typename QExtTypeTrait<T_arg4>::Take arg4,
                typename QExtTypeTrait<T_arg5>::Take arg5,
                typename QExtTypeTrait<T_arg6>::Take arg6) const
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
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3,
                typename QExtTypeTrait<T_arg4>::Take arg4,
                typename QExtTypeTrait<T_arg5>::Take arg5,
                typename QExtTypeTrait<T_arg6>::Take arg6) const
        {
            return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4, arg5, arg6);
        }

    protected:
        Function m_funcPtr;
    };

    /** QExtConstVolatileMemberFunctor5 wraps const volatile methods with 5 argument(s).
     * Use the convenience function qextMemberFunctor() to create an instance of QExtConstVolatileMemberFunctor5.
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
    template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    class QExtConstVolatileMemberFunctor5 : public QExtFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const volatile;
        typedef T_return Return;

        // Constructs an invalid functor.
        QExtConstVolatileMemberFunctor5() : m_funcPtr(QEXT_DECL_NULLPTR) {}

        /** Constructs a QExtConstVolatileMemberFunctor5 object that wraps the passed method.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtConstVolatileMemberFunctor5(Function func) : m_funcPtr(func) {}

        QExtConstVolatileMemberFunctor5(const QExtConstVolatileMemberFunctor5 &other) : m_funcPtr(other.m_funcPtr) {}

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
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3,
                typename QExtTypeTrait<T_arg4>::Take arg4,
                typename QExtTypeTrait<T_arg5>::Take arg5) const
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
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3,
                typename QExtTypeTrait<T_arg4>::Take arg4,
                typename QExtTypeTrait<T_arg5>::Take arg5) const
        {
            return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4, arg5);
        }

    protected:
        Function m_funcPtr;
    };

    /** QExtConstVolatileMemberFunctor4 wraps const volatile methods with 4 argument(s).
     * Use the convenience function qextMemberFunctor() to create an instance of QExtConstVolatileMemberFunctor4.
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
    template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    class QExtConstVolatileMemberFunctor4 : public QExtFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1, T_arg2, T_arg3, T_arg4) const volatile;
        typedef T_return Return;

        // Constructs an invalid functor.
        QExtConstVolatileMemberFunctor4() : m_funcPtr(QEXT_DECL_NULLPTR) {}

        /** Constructs a QExtConstVolatileMemberFunctor4 object that wraps the passed method.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtConstVolatileMemberFunctor4(Function func) : m_funcPtr(func) {}

        QExtConstVolatileMemberFunctor4(const QExtConstVolatileMemberFunctor4 &other) : m_funcPtr(other.m_funcPtr) {}

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
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3,
                typename QExtTypeTrait<T_arg4>::Take arg4) const
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
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3,
                typename QExtTypeTrait<T_arg4>::Take arg4) const
        {
            return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4);
        }

    protected:
        Function m_funcPtr;
    };

    /** QExtConstVolatileMemberFunctor3 wraps const volatile methods with 3 argument(s).
     * Use the convenience function qextMemberFunctor() to create an instance of QExtConstVolatileMemberFunctor3.
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
    template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
    class QExtConstVolatileMemberFunctor3 : public QExtFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1, T_arg2, T_arg3) const volatile;
        typedef T_return Return;

        // Constructs an invalid functor.
        QExtConstVolatileMemberFunctor3() : m_funcPtr(QEXT_DECL_NULLPTR) {}

        /** Constructs a QExtConstVolatileMemberFunctor3 object that wraps the passed method.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtConstVolatileMemberFunctor3(Function func) : m_funcPtr(func) {}

        QExtConstVolatileMemberFunctor3(const QExtConstVolatileMemberFunctor3 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped method operating on the passed instance.
         * \param obj Pointer to instance the method should operate on.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(
                const T_obj *obj,
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3) const
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
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3) const
        {
            return (obj.*m_funcPtr)(arg1, arg2, arg3);
        }

    protected:
        Function m_funcPtr;
    };

    /** QExtConstVolatileMemberFunctor2 wraps const volatile methods with 2 argument(s).
     * Use the convenience function qextMemberFunctor() to create an instance of QExtConstVolatileMemberFunctor2.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_arg2 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
    class QExtConstVolatileMemberFunctor2 : public QExtFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1, T_arg2) const volatile;
        typedef T_return Return;

        // Constructs an invalid functor.
        QExtConstVolatileMemberFunctor2() : m_funcPtr(QEXT_DECL_NULLPTR) {}

        /** Constructs a QExtConstVolatileMemberFunctor2 object that wraps the passed method.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtConstVolatileMemberFunctor2(Function func) : m_funcPtr(func) {}

        QExtConstVolatileMemberFunctor2(const QExtConstVolatileMemberFunctor2 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped method operating on the passed instance.
         * \param obj Pointer to instance the method should operate on.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(const T_obj *obj, typename QExtTypeTrait<T_arg1>::Take arg1,
                            typename QExtTypeTrait<T_arg2>::Take arg2) const
        {
            return (obj->*(this->m_funcPtr))(arg1, arg2);
        }

        /** Execute the wrapped method operating on the passed instance.
         * \param obj Reference to instance the method should operate on.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(const T_obj &obj, typename QExtTypeTrait<T_arg1>::Take arg1,
                            typename QExtTypeTrait<T_arg2>::Take arg2) const
        {
            return (obj.*m_funcPtr)(arg1, arg2);
        }

    protected:
        Function m_funcPtr;
    };

    /** QExtConstVolatileMemberFunctor1 wraps const volatile methods with 1 argument(s).
     * Use the convenience function qextMemberFunctor() to create an instance of QExtConstVolatileMemberFunctor1.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template<typename T_return, typename T_obj, typename T_arg1>
    class QExtConstVolatileMemberFunctor1 : public QExtFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)(T_arg1) const volatile;
        typedef T_return Return;

        // Constructs an invalid functor.
        QExtConstVolatileMemberFunctor1() : m_funcPtr(QEXT_DECL_NULLPTR) {}

        /** Constructs a QExtConstVolatileMemberFunctor1 object that wraps the passed method.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtConstVolatileMemberFunctor1(Function func) : m_funcPtr(func) {}

        QExtConstVolatileMemberFunctor1(const QExtConstVolatileMemberFunctor1 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped method operating on the passed instance.
         * \param obj Pointer to instance the method should operate on.
         * \param arg1 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(const T_obj *obj, typename QExtTypeTrait<T_arg1>::Take arg1) const
        {
            return (obj->*(this->m_funcPtr))(arg1);
        }

        /** Execute the wrapped method operating on the passed instance.
         * \param obj Reference to instance the method should operate on.
         * \param arg1 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(const T_obj &obj, typename QExtTypeTrait<T_arg1>::Take arg1) const
        {
            return (obj.*m_funcPtr)(arg1);
        }

    protected:
        Function m_funcPtr;
    };

    /** QExtConstVolatileMemberFunctor0 wraps const volatile methods with 0 argument(s).
     * Use the convenience function qextMemberFunctor() to create an instance of QExtConstVolatileMemberFunctor0.
     *
     * The following template arguments are used:
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template<typename T_return, typename T_obj>
    class QExtConstVolatileMemberFunctor0 : public QExtFunctorBase
    {
    public:
        typedef T_return (T_obj::*Function)() const volatile;
        typedef T_return Return;

        // Constructs an invalid functor.
        QExtConstVolatileMemberFunctor0() : m_funcPtr(QEXT_DECL_NULLPTR) {}

        /** Constructs a QExtConstVolatileMemberFunctor0 object that wraps the passed method.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtConstVolatileMemberFunctor0(Function func) : m_funcPtr(func) {}

        QExtConstVolatileMemberFunctor0(const QExtConstVolatileMemberFunctor0 &other) : m_funcPtr(other.m_funcPtr) {}

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

    /** QExtBoundMemberFunctor7 encapsulates a  method with 7 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QExtBoundMemberFunctor7.
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
    template<
            typename T_return,
            typename T_obj,
            typename T_arg1,
            typename T_arg2,
            typename T_arg3,
            typename T_arg4,
            typename T_arg5,
            typename T_arg6,
            typename T_arg7>
    class QExtBoundMemberFunctor7
            : public QExtMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
    {
        typedef QExtMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QExtBoundMemberFunctor7 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundMemberFunctor7(T_obj *obj, Function func) : Base(func), m_obj(*obj) {}

        /** Constructs a QExtBoundMemberFunctor7 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundMemberFunctor7(T_obj &obj, Function func) : Base(func), m_obj(obj) {}

        QExtBoundMemberFunctor7(const QExtBoundMemberFunctor7 &other) : Base(other.m_funcPtr), m_obj(other.m_obj) {}

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
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3,
                typename QExtTypeTrait<T_arg4>::Take arg4,
                typename QExtTypeTrait<T_arg5>::Take arg5,
                typename QExtTypeTrait<T_arg6>::Take arg6,
                typename QExtTypeTrait<T_arg7>::Take arg7) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QExtLimitReference<T_obj> m_obj;
    };

    /** QExtBoundMemberFunctor6 encapsulates a  method with 6 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QExtBoundMemberFunctor6.
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
    template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    class QExtBoundMemberFunctor6
            : public QExtMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
    {
        typedef QExtMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QExtBoundMemberFunctor6 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundMemberFunctor6(T_obj *obj, Function func) : Base(func), m_obj(*obj) {}

        /** Constructs a QExtBoundMemberFunctor6 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundMemberFunctor6(T_obj &obj, Function func) : Base(func), m_obj(obj) {}

        QExtBoundMemberFunctor6(const QExtBoundMemberFunctor6 &other) : Base(other.m_funcPtr), m_obj(other.m_obj) {}

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
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3,
                typename QExtTypeTrait<T_arg4>::Take arg4,
                typename QExtTypeTrait<T_arg5>::Take arg5,
                typename QExtTypeTrait<T_arg6>::Take arg6) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QExtLimitReference<T_obj> m_obj;
    };

    /** QExtBoundMemberFunctor5 encapsulates a  method with 5 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QExtBoundMemberFunctor5.
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
    template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    class QExtBoundMemberFunctor5 : public QExtMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
    {
        typedef QExtMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QExtBoundMemberFunctor5 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundMemberFunctor5(T_obj *obj, Function func) : Base(func), m_obj(*obj) {}

        /** Constructs a QExtBoundMemberFunctor5 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundMemberFunctor5(T_obj &obj, Function func) : Base(func), m_obj(obj) {}

        QExtBoundMemberFunctor5(const QExtBoundMemberFunctor5 &other) : Base(other.m_funcPtr), m_obj(other.m_obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \param arg4 Argument to be passed on to the method.
         * \param arg5 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3,
                typename QExtTypeTrait<T_arg4>::Take arg4,
                typename QExtTypeTrait<T_arg5>::Take arg5) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QExtLimitReference<T_obj> m_obj;
    };

    /** QExtBoundMemberFunctor4 encapsulates a  method with 4 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QExtBoundMemberFunctor4.
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
    template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    class QExtBoundMemberFunctor4 : public QExtMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
    {
        typedef QExtMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QExtBoundMemberFunctor4 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundMemberFunctor4(T_obj *obj, Function func) : Base(func), m_obj(*obj) {}

        /** Constructs a QExtBoundMemberFunctor4 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundMemberFunctor4(T_obj &obj, Function func) : Base(func), m_obj(obj) {}

        QExtBoundMemberFunctor4(const QExtBoundMemberFunctor4 &other) : Base(other.m_funcPtr), m_obj(other.m_obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \param arg4 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3,
                typename QExtTypeTrait<T_arg4>::Take arg4) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QExtLimitReference<T_obj> m_obj;
    };

    /** QExtBoundMemberFunctor3 encapsulates a  method with 3 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QExtBoundMemberFunctor3.
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
    template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
    class QExtBoundMemberFunctor3 : public QExtMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
    {
        typedef QExtMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QExtBoundMemberFunctor3 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundMemberFunctor3(T_obj *obj, Function func) : Base(func), m_obj(*obj) {}

        /** Constructs a QExtBoundMemberFunctor3 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundMemberFunctor3(T_obj &obj, Function func) : Base(func), m_obj(obj) {}

        QExtBoundMemberFunctor3(const QExtBoundMemberFunctor3 &other) : Base(other.m_funcPtr), m_obj(other.m_obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return
        operator()(typename QExtTypeTrait<T_arg1>::Take arg1, typename QExtTypeTrait<T_arg2>::Take arg2,
                   typename QExtTypeTrait<T_arg3>::Take arg3) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QExtLimitReference<T_obj> m_obj;
    };

    /** QExtBoundMemberFunctor2 encapsulates a  method with 2 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QExtBoundMemberFunctor2.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_arg2 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
    class QExtBoundMemberFunctor2 : public QExtMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
    {
        typedef QExtMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QExtBoundMemberFunctor2 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundMemberFunctor2(T_obj *obj, Function func) : Base(func), m_obj(*obj) {}

        /** Constructs a QExtBoundMemberFunctor2 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundMemberFunctor2(T_obj &obj, Function func) : Base(func), m_obj(obj) {}

        QExtBoundMemberFunctor2(const QExtBoundMemberFunctor2 &other) : Base(other.m_funcPtr), m_obj(other.m_obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(typename QExtTypeTrait<T_arg1>::Take arg1, typename QExtTypeTrait<T_arg2>::Take arg2) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QExtLimitReference<T_obj> m_obj;
    };

    /** QExtBoundMemberFunctor1 encapsulates a  method with 1 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QExtBoundMemberFunctor1.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template<typename T_return, typename T_obj, typename T_arg1>
    class QExtBoundMemberFunctor1 : public QExtMemberFunctor1<T_return, T_obj, T_arg1>
    {
        typedef QExtMemberFunctor1<T_return, T_obj, T_arg1> Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QExtBoundMemberFunctor1 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundMemberFunctor1(T_obj *obj, Function func) : Base(func), m_obj(*obj) {}

        /** Constructs a QExtBoundMemberFunctor1 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundMemberFunctor1(T_obj &obj, Function func) : Base(func), m_obj(obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \param arg1 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(typename QExtTypeTrait<T_arg1>::Take arg1) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QExtLimitReference<T_obj> m_obj;
    };

    /** QExtBoundMemberFunctor0 encapsulates a  method with 0 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QExtBoundMemberFunctor0.
     *
     * The following template arguments are used:
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template<typename T_return, typename T_obj>
    class QExtBoundMemberFunctor0 : public QExtMemberFunctor0<T_return, T_obj>
    {
        typedef QExtMemberFunctor0<T_return, T_obj> Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QExtBoundMemberFunctor0 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundMemberFunctor0(T_obj *obj, Function func) : Base(func), m_obj(*obj) {}

        /** Constructs a QExtBoundMemberFunctor0 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundMemberFunctor0(T_obj &obj, Function func) : Base(func), m_obj(obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \return The return value of the method invocation.
         */
        T_return operator()() const
        {
            return (m_obj.invoke().*(this->m_funcPtr))();
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QExtLimitReference<T_obj> m_obj;
    };

    /** QExtBoundConstMemberFunctor7 encapsulates a const method with 7 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QExtBoundConstMemberFunctor7.
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
    template<
            typename T_return,
            typename T_obj,
            typename T_arg1,
            typename T_arg2,
            typename T_arg3,
            typename T_arg4,
            typename T_arg5,
            typename T_arg6,
            typename T_arg7>
    class QExtBoundConstMemberFunctor7
            : public QExtConstMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
    {
        typedef QExtConstMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QExtBoundConstMemberFunctor7 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundConstMemberFunctor7(const T_obj *obj, Function func) : Base(func), m_obj(*obj) {}

        /** Constructs a QExtBoundConstMemberFunctor7 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundConstMemberFunctor7(const T_obj &obj, Function func) : Base(func), m_obj(obj) {}

        QExtBoundConstMemberFunctor7(const QExtBoundConstMemberFunctor7 &other) : Base(other.m_funcPtr), m_obj(
                other.m_obj) {}

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
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3,
                typename QExtTypeTrait<T_arg4>::Take arg4,
                typename QExtTypeTrait<T_arg5>::Take arg5,
                typename QExtTypeTrait<T_arg6>::Take arg6,
                typename QExtTypeTrait<T_arg7>::Take arg7) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QExtConstLimitReference<T_obj> m_obj;
    };

    /** QExtBoundConstMemberFunctor6 encapsulates a const method with 6 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QExtBoundConstMemberFunctor6.
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
    template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    class QExtBoundConstMemberFunctor6
            : public QExtConstMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
    {
        typedef QExtConstMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QExtBoundConstMemberFunctor6 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundConstMemberFunctor6(const T_obj *obj, Function func) : Base(func), m_obj(*obj) {}

        /** Constructs a QExtBoundConstMemberFunctor6 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundConstMemberFunctor6(const T_obj &obj, Function func) : Base(func), m_obj(obj) {}

        QExtBoundConstMemberFunctor6(const QExtBoundConstMemberFunctor6 &other) : Base(other.m_funcPtr), m_obj(
                other.m_obj) {}

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
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3,
                typename QExtTypeTrait<T_arg4>::Take arg4,
                typename QExtTypeTrait<T_arg5>::Take arg5,
                typename QExtTypeTrait<T_arg6>::Take arg6) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QExtConstLimitReference<T_obj> m_obj;
    };

    /** QExtBoundConstMemberFunctor5 encapsulates a const method with 5 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QExtBoundConstMemberFunctor5.
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
    template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    class QExtBoundConstMemberFunctor5
            : public QExtConstMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
    {
        typedef QExtConstMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QExtBoundConstMemberFunctor5 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundConstMemberFunctor5(const T_obj *obj, Function func) : Base(func), m_obj(*obj) {}

        /** Constructs a QExtBoundConstMemberFunctor5 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundConstMemberFunctor5(const T_obj &obj, Function func) : Base(func), m_obj(obj) {}

        QExtBoundConstMemberFunctor5(const QExtBoundConstMemberFunctor5 &other) : Base(other.m_funcPtr), m_obj(
                other.m_obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \param arg4 Argument to be passed on to the method.
         * \param arg5 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3,
                typename QExtTypeTrait<T_arg4>::Take arg4,
                typename QExtTypeTrait<T_arg5>::Take arg5) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QExtConstLimitReference<T_obj> m_obj;
    };

    /** QExtBoundConstMemberFunctor4 encapsulates a const method with 4 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QExtBoundConstMemberFunctor4.
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
    template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    class QExtBoundConstMemberFunctor4 : public QExtConstMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
    {
        typedef QExtConstMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QExtBoundConstMemberFunctor4 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundConstMemberFunctor4(const T_obj *obj, Function func) : Base(func), m_obj(*obj) {}

        /** Constructs a QExtBoundConstMemberFunctor4 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundConstMemberFunctor4(const T_obj &obj, Function func) : Base(func), m_obj(obj) {}

        QExtBoundConstMemberFunctor4(const QExtBoundConstMemberFunctor4 &other) : Base(other.m_funcPtr), m_obj(
                other.m_obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \param arg4 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3,
                typename QExtTypeTrait<T_arg4>::Take arg4) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QExtConstLimitReference<T_obj> m_obj;
    };

    /** QExtBoundConstMemberFunctor3 encapsulates a const method with 3 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QExtBoundConstMemberFunctor3.
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
    template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
    class QExtBoundConstMemberFunctor3 : public QExtConstMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
    {
        typedef QExtConstMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QExtBoundConstMemberFunctor3 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundConstMemberFunctor3(const T_obj *obj, Function func) : Base(func), m_obj(*obj) {}

        /** Constructs a QExtBoundConstMemberFunctor3 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundConstMemberFunctor3(const T_obj &obj, Function func) : Base(func), m_obj(obj) {}

        QExtBoundConstMemberFunctor3(const QExtBoundConstMemberFunctor3 &other) : Base(other.m_funcPtr), m_obj(
                other.m_obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return
        operator()(typename QExtTypeTrait<T_arg1>::Take arg1, typename QExtTypeTrait<T_arg2>::Take arg2,
                   typename QExtTypeTrait<T_arg3>::Take arg3) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QExtConstLimitReference<T_obj> m_obj;
    };

    /** QExtBoundConstMemberFunctor2 encapsulates a const method with 2 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QExtBoundConstMemberFunctor2.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_arg2 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
    class QExtBoundConstMemberFunctor2 : public QExtConstMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
    {
        typedef QExtConstMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QExtBoundConstMemberFunctor2 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundConstMemberFunctor2(const T_obj *obj, Function func) : Base(func), m_obj(*obj) {}

        /** Constructs a QExtBoundConstMemberFunctor2 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundConstMemberFunctor2(const T_obj &obj, Function func) : Base(func), m_obj(obj) {}

        QExtBoundConstMemberFunctor2(const QExtBoundConstMemberFunctor2 &other) : Base(other.m_funcPtr), m_obj(
                other.m_obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(typename QExtTypeTrait<T_arg1>::Take arg1, typename QExtTypeTrait<T_arg2>::Take arg2) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QExtConstLimitReference<T_obj> m_obj;
    };

    /** QExtBoundConstMemberFunctor1 encapsulates a const method with 1 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QExtBoundConstMemberFunctor1.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template<typename T_return, typename T_obj, typename T_arg1>
    class QExtBoundConstMemberFunctor1 : public QExtConstMemberFunctor1<T_return, T_obj, T_arg1>
    {
        typedef QExtConstMemberFunctor1<T_return, T_obj, T_arg1> Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QExtBoundConstMemberFunctor1 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundConstMemberFunctor1(const T_obj *obj, Function func) : Base(func), m_obj(*obj) {}

        /** Constructs a QExtBoundConstMemberFunctor1 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundConstMemberFunctor1(const T_obj &obj, Function func) : Base(func), m_obj(obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \param arg1 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(typename QExtTypeTrait<T_arg1>::Take arg1) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QExtConstLimitReference<T_obj> m_obj;
    };

    /** QExtBoundConstMemberFunctor0 encapsulates a const method with 0 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QExtBoundConstMemberFunctor0.
     *
     * The following template arguments are used:
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template<typename T_return, typename T_obj>
    class QExtBoundConstMemberFunctor0 : public QExtConstMemberFunctor0<T_return, T_obj>
    {
        typedef QExtConstMemberFunctor0<T_return, T_obj> Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QExtBoundConstMemberFunctor0 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundConstMemberFunctor0(const T_obj *obj, Function func) : Base(func), m_obj(*obj) {}

        /** Constructs a QExtBoundConstMemberFunctor0 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundConstMemberFunctor0(const T_obj &obj, Function func) : Base(func), m_obj(obj) {}

        QExtBoundConstMemberFunctor0(const QExtBoundConstMemberFunctor0 &other) : Base(other.m_funcPtr), m_obj(
                other.m_obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \return The return value of the method invocation.
         */
        T_return operator()() const
        {
            return (m_obj.invoke().*(this->m_funcPtr))();
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QExtConstLimitReference<T_obj> m_obj;
    };

    /** QExtBoundVolatileMemberFunctor7 encapsulates a volatile method with 7 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QExtBoundVolatileMemberFunctor7.
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
    template<
            typename T_return,
            typename T_obj,
            typename T_arg1,
            typename T_arg2,
            typename T_arg3,
            typename T_arg4,
            typename T_arg5,
            typename T_arg6,
            typename T_arg7>
    class QExtBoundVolatileMemberFunctor7
            : public QExtVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
    {
        typedef QExtVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QExtBoundVolatileMemberFunctor7 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundVolatileMemberFunctor7(T_obj *obj, Function func) : Base(func), m_obj(*obj) {}

        /** Constructs a QExtBoundVolatileMemberFunctor7 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundVolatileMemberFunctor7(T_obj &obj, Function func) : Base(func), m_obj(obj) {}

        QExtBoundVolatileMemberFunctor7(const QExtBoundVolatileMemberFunctor7 &other) : Base(other.m_funcPtr), m_obj(
                other.m_obj) {}

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
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3,
                typename QExtTypeTrait<T_arg4>::Take arg4,
                typename QExtTypeTrait<T_arg5>::Take arg5,
                typename QExtTypeTrait<T_arg6>::Take arg6,
                typename QExtTypeTrait<T_arg7>::Take arg7) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QExtVolatileLimitReference<T_obj> m_obj;
    };

    /** QExtBoundVolatileMemberFunctor6 encapsulates a volatile method with 6 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QExtBoundVolatileMemberFunctor6.
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
    template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    class QExtBoundVolatileMemberFunctor6
            : public QExtVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
    {
        typedef QExtVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QExtBoundVolatileMemberFunctor6 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundVolatileMemberFunctor6(T_obj *obj, Function func) : Base(func), m_obj(*obj) {}

        /** Constructs a QExtBoundVolatileMemberFunctor6 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundVolatileMemberFunctor6(T_obj &obj, Function func) : Base(func), m_obj(obj) {}

        QExtBoundVolatileMemberFunctor6(const QExtBoundVolatileMemberFunctor6 &other) : Base(other.m_funcPtr), m_obj(
                other.m_obj) {}

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
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3,
                typename QExtTypeTrait<T_arg4>::Take arg4,
                typename QExtTypeTrait<T_arg5>::Take arg5,
                typename QExtTypeTrait<T_arg6>::Take arg6) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QExtVolatileLimitReference<T_obj> m_obj;
    };

    /** QExtBoundVolatileMemberFunctor5 encapsulates a volatile method with 5 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QExtBoundVolatileMemberFunctor5.
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
    template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    class QExtBoundVolatileMemberFunctor5
            : public QExtVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
    {
        typedef QExtVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QExtBoundVolatileMemberFunctor5 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundVolatileMemberFunctor5(T_obj *obj, Function func) : Base(func), m_obj(*obj) {}

        /** Constructs a QExtBoundVolatileMemberFunctor5 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundVolatileMemberFunctor5(T_obj &obj, Function func) : Base(func), m_obj(obj) {}

        QExtBoundVolatileMemberFunctor5(const QExtBoundVolatileMemberFunctor5 &other) : Base(other.m_funcPtr), m_obj(
                other.m_obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \param arg4 Argument to be passed on to the method.
         * \param arg5 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3,
                typename QExtTypeTrait<T_arg4>::Take arg4,
                typename QExtTypeTrait<T_arg5>::Take arg5) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QExtVolatileLimitReference<T_obj> m_obj;
    };

    /** QExtBoundVolatileMemberFunctor4 encapsulates a volatile method with 4 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QExtBoundVolatileMemberFunctor4.
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
    template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    class QExtBoundVolatileMemberFunctor4
            : public QExtVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
    {
        typedef QExtVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QExtBoundVolatileMemberFunctor4 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundVolatileMemberFunctor4(T_obj *obj, Function func) : Base(func), m_obj(*obj) {}

        /** Constructs a QExtBoundVolatileMemberFunctor4 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundVolatileMemberFunctor4(T_obj &obj, Function func) : Base(func), m_obj(obj) {}

        QExtBoundVolatileMemberFunctor4(const QExtBoundVolatileMemberFunctor4 &other) : Base(other.m_funcPtr), m_obj(
                other.m_obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \param arg4 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3,
                typename QExtTypeTrait<T_arg4>::Take arg4) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QExtVolatileLimitReference<T_obj> m_obj;
    };

    /** QExtBoundVolatileMemberFunctor3 encapsulates a volatile method with 3 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QExtBoundVolatileMemberFunctor3.
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
    template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
    class QExtBoundVolatileMemberFunctor3 : public QExtVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
    {
        typedef QExtVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QExtBoundVolatileMemberFunctor3 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundVolatileMemberFunctor3(T_obj *obj, Function func) : Base(func), m_obj(*obj) {}

        /** Constructs a QExtBoundVolatileMemberFunctor3 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundVolatileMemberFunctor3(T_obj &obj, Function func) : Base(func), m_obj(obj) {}

        QExtBoundVolatileMemberFunctor3(const QExtBoundVolatileMemberFunctor3 &other) : Base(other.m_funcPtr), m_obj(
                other.m_obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return
        operator()(typename QExtTypeTrait<T_arg1>::Take arg1, typename QExtTypeTrait<T_arg2>::Take arg2,
                   typename QExtTypeTrait<T_arg3>::Take arg3) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QExtVolatileLimitReference<T_obj> m_obj;
    };

    /** QExtBoundVolatileMemberFunctor2 encapsulates a volatile method with 2 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QExtBoundVolatileMemberFunctor2.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_arg2 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
    class QExtBoundVolatileMemberFunctor2 : public QExtVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
    {
        typedef QExtVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QExtBoundVolatileMemberFunctor2 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundVolatileMemberFunctor2(T_obj *obj, Function func) : Base(func), m_obj(*obj) {}

        /** Constructs a QExtBoundVolatileMemberFunctor2 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundVolatileMemberFunctor2(T_obj &obj, Function func) : Base(func), m_obj(obj) {}

        QExtBoundVolatileMemberFunctor2(const QExtBoundVolatileMemberFunctor2 &other) : Base(other.m_funcPtr), m_obj(
                other.m_obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(typename QExtTypeTrait<T_arg1>::Take arg1, typename QExtTypeTrait<T_arg2>::Take arg2) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QExtVolatileLimitReference<T_obj> m_obj;
    };

    /** QExtBoundVolatileMemberFunctor1 encapsulates a volatile method with 1 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QExtBoundVolatileMemberFunctor1.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template<typename T_return, typename T_obj, typename T_arg1>
    class QExtBoundVolatileMemberFunctor1 : public QExtVolatileMemberFunctor1<T_return, T_obj, T_arg1>
    {
        typedef QExtVolatileMemberFunctor1<T_return, T_obj, T_arg1> Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QExtBoundVolatileMemberFunctor1 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundVolatileMemberFunctor1(T_obj *obj, Function func) : Base(func), m_obj(*obj) {}

        /** Constructs a QExtBoundVolatileMemberFunctor1 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundVolatileMemberFunctor1(T_obj &obj, Function func) : Base(func), m_obj(obj) {}

        QExtBoundVolatileMemberFunctor1(const QExtBoundVolatileMemberFunctor1 &other) : Base(other.m_funcPtr), m_obj(
                other.m_obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \param arg1 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(typename QExtTypeTrait<T_arg1>::Take arg1) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QExtVolatileLimitReference<T_obj> m_obj;
    };

    /** QExtBoundVolatileMemberFunctor0 encapsulates a volatile method with 0 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QExtBoundVolatileMemberFunctor0.
     *
     * The following template arguments are used:
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template<typename T_return, typename T_obj>
    class QExtBoundVolatileMemberFunctor0 : public QExtVolatileMemberFunctor0<T_return, T_obj>
    {
        typedef QExtVolatileMemberFunctor0<T_return, T_obj> Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QExtBoundVolatileMemberFunctor0 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundVolatileMemberFunctor0(T_obj *obj, Function func) : Base(func), m_obj(*obj) {}

        /** Constructs a QExtBoundVolatileMemberFunctor0 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundVolatileMemberFunctor0(T_obj &obj, Function func) : Base(func), m_obj(obj) {}

        QExtBoundVolatileMemberFunctor0(const QExtBoundVolatileMemberFunctor0 &other) : Base(other.m_funcPtr), m_obj(
                other.m_obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \return The return value of the method invocation.
         */
        T_return operator()() const
        {
            return (m_obj.invoke().*(this->m_funcPtr))();
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QExtVolatileLimitReference<T_obj> m_obj;
    };

    /** QExtBoundConstVolatileMemberFunctor7 encapsulates a const volatile method with 7 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QExtBoundConstVolatileMemberFunctor7.
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
    template<
            typename T_return,
            typename T_obj,
            typename T_arg1,
            typename T_arg2,
            typename T_arg3,
            typename T_arg4,
            typename T_arg5,
            typename T_arg6,
            typename T_arg7>
    class QExtBoundConstVolatileMemberFunctor7
            : public QExtConstVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
    {
        typedef QExtConstVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QExtBoundConstVolatileMemberFunctor7 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundConstVolatileMemberFunctor7(const T_obj *obj, Function func) : Base(func), m_obj(*obj) {}

        /** Constructs a QExtBoundConstVolatileMemberFunctor7 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundConstVolatileMemberFunctor7(const T_obj &obj, Function func) : Base(func), m_obj(obj) {}

        QExtBoundConstVolatileMemberFunctor7(const QExtBoundConstVolatileMemberFunctor7 &other) : Base(other.m_funcPtr)
                                                                                                  , m_obj(
                        other.m_obj) {}

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
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3,
                typename QExtTypeTrait<T_arg4>::Take arg4,
                typename QExtTypeTrait<T_arg5>::Take arg5,
                typename QExtTypeTrait<T_arg6>::Take arg6,
                typename QExtTypeTrait<T_arg7>::Take arg7) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QExtConstVolatileLimitReference<T_obj> m_obj;
    };

    /** QExtBoundConstVolatileMemberFunctor6 encapsulates a const volatile method with 6 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QExtBoundConstVolatileMemberFunctor6.
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
    template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    class QExtBoundConstVolatileMemberFunctor6
            : public QExtConstVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
    {
        typedef QExtConstVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QExtBoundConstVolatileMemberFunctor6 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundConstVolatileMemberFunctor6(const T_obj *obj, Function func) : Base(func), m_obj(*obj) {}

        /** Constructs a QExtBoundConstVolatileMemberFunctor6 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundConstVolatileMemberFunctor6(const T_obj &obj, Function func) : Base(func), m_obj(obj) {}

        QExtBoundConstVolatileMemberFunctor6(const QExtBoundConstVolatileMemberFunctor6 &other) : Base(other.m_funcPtr)
                                                                                                  , m_obj(
                        other.m_obj) {}

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
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3,
                typename QExtTypeTrait<T_arg4>::Take arg4,
                typename QExtTypeTrait<T_arg5>::Take arg5,
                typename QExtTypeTrait<T_arg6>::Take arg6) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QExtConstVolatileLimitReference<T_obj> m_obj;
    };

    /** QExtBoundConstVolatileMemberFunctor5 encapsulates a const volatile method with 5 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QExtBoundConstVolatileMemberFunctor5.
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
    template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    class QExtBoundConstVolatileMemberFunctor5
            : public QExtConstVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
    {
        typedef QExtConstVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QExtBoundConstVolatileMemberFunctor5 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundConstVolatileMemberFunctor5(const T_obj *obj, Function func) : Base(func), m_obj(*obj) {}

        /** Constructs a QExtBoundConstVolatileMemberFunctor5 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundConstVolatileMemberFunctor5(const T_obj &obj, Function func) : Base(func), m_obj(obj) {}

        QExtBoundConstVolatileMemberFunctor5(const QExtBoundConstVolatileMemberFunctor5 &other) : Base(other.m_funcPtr)
                                                                                                  , m_obj(
                        other.m_obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \param arg4 Argument to be passed on to the method.
         * \param arg5 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3,
                typename QExtTypeTrait<T_arg4>::Take arg4,
                typename QExtTypeTrait<T_arg5>::Take arg5) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QExtConstVolatileLimitReference<T_obj> m_obj;
    };

    /** QExtBoundConstVolatileMemberFunctor4 encapsulates a const volatile method with 4 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QExtBoundConstVolatileMemberFunctor4.
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
    template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    class QExtBoundConstVolatileMemberFunctor4
            : public QExtConstVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
    {
        typedef QExtConstVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QExtBoundConstVolatileMemberFunctor4 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundConstVolatileMemberFunctor4(const T_obj *obj, Function func) : Base(func), m_obj(*obj) {}

        /** Constructs a QExtBoundConstVolatileMemberFunctor4 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundConstVolatileMemberFunctor4(const T_obj &obj, Function func) : Base(func), m_obj(obj) {}

        QExtBoundConstVolatileMemberFunctor4(const QExtBoundConstVolatileMemberFunctor4 &other) : Base(other.m_funcPtr)
                                                                                                  , m_obj(
                        other.m_obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \param arg4 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(
                typename QExtTypeTrait<T_arg1>::Take arg1,
                typename QExtTypeTrait<T_arg2>::Take arg2,
                typename QExtTypeTrait<T_arg3>::Take arg3,
                typename QExtTypeTrait<T_arg4>::Take arg4) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QExtConstVolatileLimitReference<T_obj> m_obj;
    };

    /** QExtBoundConstVolatileMemberFunctor3 encapsulates a const volatile method with 3 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QExtBoundConstVolatileMemberFunctor3.
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
    template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
    class QExtBoundConstVolatileMemberFunctor3
            : public QExtConstVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
    {
        typedef QExtConstVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QExtBoundConstVolatileMemberFunctor3 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundConstVolatileMemberFunctor3(const T_obj *obj, Function func) : Base(func), m_obj(*obj) {}

        /** Constructs a QExtBoundConstVolatileMemberFunctor3 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundConstVolatileMemberFunctor3(const T_obj &obj, Function func) : Base(func), m_obj(obj) {}

        QExtBoundConstVolatileMemberFunctor3(const QExtBoundConstVolatileMemberFunctor3 &other) : Base(other.m_funcPtr)
                                                                                                  , m_obj(
                        other.m_obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \param arg3 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return
        operator()(typename QExtTypeTrait<T_arg1>::Take arg1, typename QExtTypeTrait<T_arg2>::Take arg2,
                   typename QExtTypeTrait<T_arg3>::Take arg3) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QExtConstVolatileLimitReference<T_obj> m_obj;
    };

    /** QExtBoundConstVolatileMemberFunctor2 encapsulates a const volatile method with 2 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QExtBoundConstVolatileMemberFunctor2.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_arg2 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
    class QExtBoundConstVolatileMemberFunctor2 : public QExtConstVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
    {
        typedef QExtConstVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QExtBoundConstVolatileMemberFunctor2 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundConstVolatileMemberFunctor2(const T_obj *obj, Function func) : Base(func), m_obj(*obj) {}

        /** Constructs a QExtBoundConstVolatileMemberFunctor2 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundConstVolatileMemberFunctor2(const T_obj &obj, Function func) : Base(func), m_obj(obj) {}

        QExtBoundConstVolatileMemberFunctor2(const QExtBoundConstVolatileMemberFunctor2 &other) : Base(other.m_funcPtr)
                                                                                                  , m_obj(
                        other.m_obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \param arg1 Argument to be passed on to the method.
         * \param arg2 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(typename QExtTypeTrait<T_arg1>::Take arg1, typename QExtTypeTrait<T_arg2>::Take arg2) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QExtConstVolatileLimitReference<T_obj> m_obj;
    };

    /** QExtBoundConstVolatileMemberFunctor1 encapsulates a const volatile method with 1 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QExtBoundConstVolatileMemberFunctor1.
     *
     * The following template arguments are used:
     * - @e T_arg1 Argument type used in the definition of operator()().
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template<typename T_return, typename T_obj, typename T_arg1>
    class QExtBoundConstVolatileMemberFunctor1 : public QExtConstVolatileMemberFunctor1<T_return, T_obj, T_arg1>
    {
        typedef QExtConstVolatileMemberFunctor1<T_return, T_obj, T_arg1> Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QExtBoundConstVolatileMemberFunctor1 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundConstVolatileMemberFunctor1(const T_obj *obj, Function func) : Base(func), m_obj(*obj) {}

        /** Constructs a QExtBoundConstVolatileMemberFunctor1 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundConstVolatileMemberFunctor1(const T_obj &obj, Function func) : Base(func), m_obj(obj) {}

        QExtBoundConstVolatileMemberFunctor1(const QExtBoundConstVolatileMemberFunctor1 &other) : Base(other.m_funcPtr)
                                                                                                  , m_obj(
                        other.m_obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \param arg1 Argument to be passed on to the method.
         * \return The return value of the method invocation.
         */
        T_return operator()(typename QExtTypeTrait<T_arg1>::Take arg1) const
        {
            return (m_obj.invoke().*(this->m_funcPtr))(arg1);
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QExtConstVolatileLimitReference<T_obj> m_obj;
    };

    /** QExtBoundConstVolatileMemberFunctor0 encapsulates a const volatile method with 0 arguments and an object instance.
     * Use the convenience function qextMemberFunctor() to create an instance of QExtBoundConstVolatileMemberFunctor0.
     *
     * The following template arguments are used:
     * - @e T_return The return type of operator()().
     * - @e T_obj The object type.
     *
     * \ingroup qextMemberFunctor
     */
    template<typename T_return, typename T_obj>
    class QExtBoundConstVolatileMemberFunctor0 : public QExtConstVolatileMemberFunctor0<T_return, T_obj>
    {
        typedef QExtConstVolatileMemberFunctor0<T_return, T_obj> Base;

    public:
        typedef typename Base::Function Function;
        typedef typename Base::Return Return;

        /** Constructs a QExtBoundConstVolatileMemberFunctor0 object that wraps the passed method.
         * \param obj Pointer to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundConstVolatileMemberFunctor0(const T_obj *obj, Function func) : Base(func), m_obj(*obj) {}

        /** Constructs a QExtBoundConstVolatileMemberFunctor0 object that wraps the passed method.
         * \param obj Reference to instance the method will operate on.
         * \param func Pointer to method will be invoked from operator()().
         */
        QExtBoundConstVolatileMemberFunctor0(const T_obj &obj, Function func) : Base(func), m_obj(obj) {}

        QExtBoundConstVolatileMemberFunctor0(const QExtBoundConstVolatileMemberFunctor0 &other) : Base(other.m_funcPtr)
                                                                                                  , m_obj(
                        other.m_obj) {}

        /** Execute the wrapped method operating on the stored instance.
         * \return The return value of the method invocation.
         */
        T_return operator()() const
        {
            return (m_obj.invoke().*(this->m_funcPtr))();
        }

        // Reference to stored object instance.
        // This is the handler object, such as TheObject in void TheObject::signal_handler().
        QExtConstVolatileLimitReference<T_obj> m_obj;
    };

} // namespace QExtPrivate




template<
        typename T_return,
        typename T_obj,
        typename T_arg1 = QExtNil,
        typename T_arg2 = QExtNil,
        typename T_arg3 = QExtNil,
        typename T_arg4 = QExtNil,
        typename T_arg5 = QExtNil,
        typename T_arg6 = QExtNil,
        typename T_arg7 = QExtNil>
class QExtMemberFunctor
        : public QExtPrivate::QExtMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
{
    typedef QExtPrivate::QExtMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtMemberFunctor() {}

    QExtMemberFunctor(Function func) : Base(func) {}

    QExtMemberFunctor(const QExtMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(
            T_obj *obj,
            typename QExtTypeTrait<T_arg1>::Take arg1,
            typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3,
            typename QExtTypeTrait<T_arg4>::Take arg4,
            typename QExtTypeTrait<T_arg5>::Take arg5,
            typename QExtTypeTrait<T_arg6>::Take arg6,
            typename QExtTypeTrait<T_arg7>::Take arg7) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    T_return operator()(
            T_obj &obj,
            typename QExtTypeTrait<T_arg1>::Take arg1,
            typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3,
            typename QExtTypeTrait<T_arg4>::Take arg4,
            typename QExtTypeTrait<T_arg5>::Take arg5,
            typename QExtTypeTrait<T_arg6>::Take arg6,
            typename QExtTypeTrait<T_arg7>::Take arg7) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
class QExtMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QExtNil>
        : public QExtPrivate::QExtMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
{
    typedef QExtPrivate::QExtMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtMemberFunctor() {}

    QExtMemberFunctor(Function func) : Base(func) {}

    QExtMemberFunctor(const QExtMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(
            T_obj *obj,
            typename QExtTypeTrait<T_arg1>::Take arg1,
            typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3,
            typename QExtTypeTrait<T_arg4>::Take arg4,
            typename QExtTypeTrait<T_arg5>::Take arg5,
            typename QExtTypeTrait<T_arg6>::Take arg6) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4, arg5, arg6);
    }

    T_return operator()(
            T_obj &obj,
            typename QExtTypeTrait<T_arg1>::Take arg1,
            typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3,
            typename QExtTypeTrait<T_arg4>::Take arg4,
            typename QExtTypeTrait<T_arg5>::Take arg5,
            typename QExtTypeTrait<T_arg6>::Take arg6) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class QExtMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QExtNil, QExtNil>
        : public QExtPrivate::QExtMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
{
    typedef QExtPrivate::QExtMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtMemberFunctor() {}

    QExtMemberFunctor(Function func) : Base(func) {}

    QExtMemberFunctor(const QExtMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(
            T_obj *obj,
            typename QExtTypeTrait<T_arg1>::Take arg1,
            typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3,
            typename QExtTypeTrait<T_arg4>::Take arg4,
            typename QExtTypeTrait<T_arg5>::Take arg5) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4, arg5);
    }

    T_return operator()(
            T_obj &obj,
            typename QExtTypeTrait<T_arg1>::Take arg1,
            typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3,
            typename QExtTypeTrait<T_arg4>::Take arg4,
            typename QExtTypeTrait<T_arg5>::Take arg5) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4, arg5);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class QExtMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, QExtNil, QExtNil, QExtNil>
        : public QExtPrivate::QExtMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
{
    typedef QExtPrivate::QExtMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtMemberFunctor() {}

    QExtMemberFunctor(Function func) : Base(func) {}

    QExtMemberFunctor(const QExtMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(
            T_obj *obj,
            typename QExtTypeTrait<T_arg1>::Take arg1,
            typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3,
            typename QExtTypeTrait<T_arg4>::Take arg4) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4);
    }

    T_return operator()(
            T_obj &obj,
            typename QExtTypeTrait<T_arg1>::Take arg1,
            typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3,
            typename QExtTypeTrait<T_arg4>::Take arg4) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
class QExtMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, QExtNil, QExtNil, QExtNil, QExtNil>
        : public QExtPrivate::QExtMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
{
    typedef QExtPrivate::QExtMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtMemberFunctor() {}

    QExtMemberFunctor(Function func) : Base(func) {}

    QExtMemberFunctor(const QExtMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(
            T_obj *obj, typename QExtTypeTrait<T_arg1>::Take arg1, typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3) const
    {
        return Base::operator()(obj, arg1, arg2, arg3);
    }

    T_return operator()(
            T_obj &obj, typename QExtTypeTrait<T_arg1>::Take arg1, typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3) const
    {
        return Base::operator()(obj, arg1, arg2, arg3);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
class QExtMemberFunctor<T_return, T_obj, T_arg1, T_arg2, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
        : public QExtPrivate::QExtMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
{
    typedef QExtPrivate::QExtMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtMemberFunctor() {}

    QExtMemberFunctor(Function func) : Base(func) {}

    QExtMemberFunctor(const QExtMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return
    operator()(T_obj *obj, typename QExtTypeTrait<T_arg1>::Take arg1, typename QExtTypeTrait<T_arg2>::Take arg2) const
    {
        return Base::operator()(obj, arg1, arg2);
    }

    T_return
    operator()(T_obj &obj, typename QExtTypeTrait<T_arg1>::Take arg1, typename QExtTypeTrait<T_arg2>::Take arg2) const
    {
        return Base::operator()(obj, arg1, arg2);
    }
};

template<typename T_return, typename T_obj, typename T_arg1>
class QExtMemberFunctor<T_return, T_obj, T_arg1, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
        : public QExtPrivate::QExtMemberFunctor1<T_return, T_obj, T_arg1>
{
    typedef QExtPrivate::QExtMemberFunctor1<T_return, T_obj, T_arg1> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtMemberFunctor() {}

    QExtMemberFunctor(Function func) : Base(func) {}

    QExtMemberFunctor(const QExtMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(T_obj *obj, typename QExtTypeTrait<T_arg1>::Take arg1) const
    {
        return Base::operator()(obj, arg1);
    }

    T_return operator()(T_obj &obj, typename QExtTypeTrait<T_arg1>::Take arg1) const
    {
        return Base::operator()(obj, arg1);
    }
};

template<typename T_return, typename T_obj>
class QExtMemberFunctor<T_return, T_obj, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
        : public QExtPrivate::QExtMemberFunctor0<T_return, T_obj>
{
public:
    typedef QExtPrivate::QExtMemberFunctor0<T_return, T_obj> Base;
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtMemberFunctor() {}

    QExtMemberFunctor(Function func) : Base(func) {}

    QExtMemberFunctor(const QExtMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(T_obj *obj) const
    {
        return Base::operator()(obj);
    }

    T_return operator()(T_obj &obj) const
    {
        return Base::operator()(obj);
    }
};

template<
        typename T_return,
        typename T_obj,
        typename T_arg1 = QExtNil,
        typename T_arg2 = QExtNil,
        typename T_arg3 = QExtNil,
        typename T_arg4 = QExtNil,
        typename T_arg5 = QExtNil,
        typename T_arg6 = QExtNil,
        typename T_arg7 = QExtNil>
class QExtConstMemberFunctor
        : public QExtPrivate::QExtConstMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
{
    typedef QExtPrivate::QExtConstMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtConstMemberFunctor() {}

    QExtConstMemberFunctor(Function func) : Base(func) {}

    QExtConstMemberFunctor(const QExtConstMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(
            const T_obj *obj,
            typename QExtTypeTrait<T_arg1>::Take arg1,
            typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3,
            typename QExtTypeTrait<T_arg4>::Take arg4,
            typename QExtTypeTrait<T_arg5>::Take arg5,
            typename QExtTypeTrait<T_arg6>::Take arg6,
            typename QExtTypeTrait<T_arg7>::Take arg7) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    T_return operator()(
            const T_obj &obj,
            typename QExtTypeTrait<T_arg1>::Take arg1,
            typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3,
            typename QExtTypeTrait<T_arg4>::Take arg4,
            typename QExtTypeTrait<T_arg5>::Take arg5,
            typename QExtTypeTrait<T_arg6>::Take arg6,
            typename QExtTypeTrait<T_arg7>::Take arg7) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
class QExtConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QExtNil>
        : public QExtPrivate::QExtConstMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
{
    typedef QExtPrivate::QExtConstMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtConstMemberFunctor() {}

    QExtConstMemberFunctor(Function func) : Base(func) {}

    QExtConstMemberFunctor(const QExtConstMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(
            const T_obj *obj,
            typename QExtTypeTrait<T_arg1>::Take arg1,
            typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3,
            typename QExtTypeTrait<T_arg4>::Take arg4,
            typename QExtTypeTrait<T_arg5>::Take arg5,
            typename QExtTypeTrait<T_arg6>::Take arg6) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4, arg5, arg6);
    }

    T_return operator()(
            const T_obj &obj,
            typename QExtTypeTrait<T_arg1>::Take arg1,
            typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3,
            typename QExtTypeTrait<T_arg4>::Take arg4,
            typename QExtTypeTrait<T_arg5>::Take arg5,
            typename QExtTypeTrait<T_arg6>::Take arg6) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class QExtConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QExtNil, QExtNil>
        : public QExtPrivate::QExtConstMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
{
    typedef QExtPrivate::QExtConstMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtConstMemberFunctor() {}

    QExtConstMemberFunctor(Function func) : Base(func) {}

    QExtConstMemberFunctor(const QExtConstMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(
            const T_obj *obj,
            typename QExtTypeTrait<T_arg1>::Take arg1,
            typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3,
            typename QExtTypeTrait<T_arg4>::Take arg4,
            typename QExtTypeTrait<T_arg5>::Take arg5) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4, arg5);
    }

    T_return operator()(
            const T_obj &obj,
            typename QExtTypeTrait<T_arg1>::Take arg1,
            typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3,
            typename QExtTypeTrait<T_arg4>::Take arg4,
            typename QExtTypeTrait<T_arg5>::Take arg5) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4, arg5);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class QExtConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, QExtNil, QExtNil, QExtNil>
        : public QExtPrivate::QExtConstMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
{
    typedef QExtPrivate::QExtConstMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtConstMemberFunctor() {}

    QExtConstMemberFunctor(Function func) : Base(func) {}

    QExtConstMemberFunctor(const QExtConstMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(
            const T_obj *obj,
            typename QExtTypeTrait<T_arg1>::Take arg1,
            typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3,
            typename QExtTypeTrait<T_arg4>::Take arg4) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4);
    }

    T_return operator()(
            const T_obj &obj,
            typename QExtTypeTrait<T_arg1>::Take arg1,
            typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3,
            typename QExtTypeTrait<T_arg4>::Take arg4) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
class QExtConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, QExtNil, QExtNil, QExtNil, QExtNil>
        : public QExtPrivate::QExtConstMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
{
    typedef QExtPrivate::QExtConstMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtConstMemberFunctor() {}

    QExtConstMemberFunctor(Function func) : Base(func) {}

    QExtConstMemberFunctor(const QExtConstMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(
            const T_obj *obj, typename QExtTypeTrait<T_arg1>::Take arg1, typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3) const
    {
        return Base::operator()(obj, arg1, arg2, arg3);
    }

    T_return operator()(
            const T_obj &obj, typename QExtTypeTrait<T_arg1>::Take arg1, typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3) const
    {
        return Base::operator()(obj, arg1, arg2, arg3);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
class QExtConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
        : public QExtPrivate::QExtConstMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
{
    typedef QExtPrivate::QExtConstMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtConstMemberFunctor() {}

    QExtConstMemberFunctor(Function func) : Base(func) {}

    QExtConstMemberFunctor(const QExtConstMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(const T_obj *obj, typename QExtTypeTrait<T_arg1>::Take arg1,
                        typename QExtTypeTrait<T_arg2>::Take arg2) const
    {
        return Base::operator()(obj, arg1, arg2);
    }

    T_return operator()(const T_obj &obj, typename QExtTypeTrait<T_arg1>::Take arg1,
                        typename QExtTypeTrait<T_arg2>::Take arg2) const
    {
        return Base::operator()(obj, arg1, arg2);
    }
};

template<typename T_return, typename T_obj, typename T_arg1>
class QExtConstMemberFunctor<T_return, T_obj, T_arg1, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
        : public QExtPrivate::QExtConstMemberFunctor1<T_return, T_obj, T_arg1>
{
    typedef QExtPrivate::QExtConstMemberFunctor1<T_return, T_obj, T_arg1> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtConstMemberFunctor() {}

    QExtConstMemberFunctor(Function func) : Base(func) {}

    QExtConstMemberFunctor(const QExtConstMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(const T_obj *obj, typename QExtTypeTrait<T_arg1>::Take arg1) const
    {
        return Base::operator()(obj, arg1);
    }

    T_return operator()(const T_obj &obj, typename QExtTypeTrait<T_arg1>::Take arg1) const
    {
        return Base::operator()(obj, arg1);
    }
};

template<typename T_return, typename T_obj>
class QExtConstMemberFunctor<T_return, T_obj, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
        : public QExtPrivate::QExtConstMemberFunctor0<T_return, T_obj>
{
    typedef QExtPrivate::QExtConstMemberFunctor0<T_return, T_obj> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtConstMemberFunctor() {}

    QExtConstMemberFunctor(Function func) : Base(func) {}

    QExtConstMemberFunctor(const QExtConstMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(const T_obj *obj) const
    {
        return Base::operator()(obj);
    }

    T_return operator()(const T_obj &obj) const
    {
        return Base::operator()(obj);
    }
};

template<
        typename T_return,
        typename T_obj,
        typename T_arg1 = QExtNil,
        typename T_arg2 = QExtNil,
        typename T_arg3 = QExtNil,
        typename T_arg4 = QExtNil,
        typename T_arg5 = QExtNil,
        typename T_arg6 = QExtNil,
        typename T_arg7 = QExtNil>
class QExtVolatileMemberFunctor
        : public QExtPrivate::QExtVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
{
    typedef QExtPrivate::QExtVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtVolatileMemberFunctor() {}

    QExtVolatileMemberFunctor(Function func) : Base(func) {}

    QExtVolatileMemberFunctor(const QExtVolatileMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(
            T_obj *obj,
            typename QExtTypeTrait<T_arg1>::Take arg1,
            typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3,
            typename QExtTypeTrait<T_arg4>::Take arg4,
            typename QExtTypeTrait<T_arg5>::Take arg5,
            typename QExtTypeTrait<T_arg6>::Take arg6,
            typename QExtTypeTrait<T_arg7>::Take arg7) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    T_return operator()(
            T_obj &obj,
            typename QExtTypeTrait<T_arg1>::Take arg1,
            typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3,
            typename QExtTypeTrait<T_arg4>::Take arg4,
            typename QExtTypeTrait<T_arg5>::Take arg5,
            typename QExtTypeTrait<T_arg6>::Take arg6,
            typename QExtTypeTrait<T_arg7>::Take arg7) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
class QExtVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QExtNil>
        : public QExtPrivate::QExtVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
{
    typedef QExtPrivate::QExtVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtVolatileMemberFunctor() {}

    QExtVolatileMemberFunctor(Function func) : Base(func) {}

    QExtVolatileMemberFunctor(const QExtVolatileMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(
            T_obj *obj,
            typename QExtTypeTrait<T_arg1>::Take arg1,
            typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3,
            typename QExtTypeTrait<T_arg4>::Take arg4,
            typename QExtTypeTrait<T_arg5>::Take arg5,
            typename QExtTypeTrait<T_arg6>::Take arg6) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4, arg5, arg6);
    }

    T_return operator()(
            T_obj &obj,
            typename QExtTypeTrait<T_arg1>::Take arg1,
            typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3,
            typename QExtTypeTrait<T_arg4>::Take arg4,
            typename QExtTypeTrait<T_arg5>::Take arg5,
            typename QExtTypeTrait<T_arg6>::Take arg6) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class QExtVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QExtNil, QExtNil>
        : public QExtPrivate::QExtVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
{
    typedef QExtPrivate::QExtVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtVolatileMemberFunctor() {}

    QExtVolatileMemberFunctor(Function func) : Base(func) {}

    QExtVolatileMemberFunctor(const QExtVolatileMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(
            T_obj *obj,
            typename QExtTypeTrait<T_arg1>::Take arg1,
            typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3,
            typename QExtTypeTrait<T_arg4>::Take arg4,
            typename QExtTypeTrait<T_arg5>::Take arg5) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4, arg5);
    }

    T_return operator()(
            T_obj &obj,
            typename QExtTypeTrait<T_arg1>::Take arg1,
            typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3,
            typename QExtTypeTrait<T_arg4>::Take arg4,
            typename QExtTypeTrait<T_arg5>::Take arg5) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4, arg5);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class QExtVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, QExtNil, QExtNil, QExtNil>
        : public QExtPrivate::QExtVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
{
    typedef QExtPrivate::QExtVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtVolatileMemberFunctor() {}

    QExtVolatileMemberFunctor(Function func) : Base(func) {}

    QExtVolatileMemberFunctor(const QExtVolatileMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(
            T_obj *obj,
            typename QExtTypeTrait<T_arg1>::Take arg1,
            typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3,
            typename QExtTypeTrait<T_arg4>::Take arg4) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4);
    }

    T_return operator()(
            T_obj &obj,
            typename QExtTypeTrait<T_arg1>::Take arg1,
            typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3,
            typename QExtTypeTrait<T_arg4>::Take arg4) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
class QExtVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, QExtNil, QExtNil, QExtNil, QExtNil>
        : public QExtPrivate::QExtVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
{
    typedef QExtPrivate::QExtVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtVolatileMemberFunctor() {}

    QExtVolatileMemberFunctor(Function func) : Base(func) {}

    QExtVolatileMemberFunctor(const QExtVolatileMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(
            T_obj *obj, typename QExtTypeTrait<T_arg1>::Take arg1, typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3) const
    {
        return Base::operator()(obj, arg1, arg2, arg3);
    }

    T_return operator()(
            T_obj &obj, typename QExtTypeTrait<T_arg1>::Take arg1, typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3) const
    {
        return Base::operator()(obj, arg1, arg2, arg3);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
class QExtVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
        : public QExtPrivate::QExtVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
{
    typedef QExtPrivate::QExtVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtVolatileMemberFunctor() {}

    QExtVolatileMemberFunctor(Function func) : Base(func) {}

    QExtVolatileMemberFunctor(const QExtVolatileMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return
    operator()(T_obj *obj, typename QExtTypeTrait<T_arg1>::Take arg1, typename QExtTypeTrait<T_arg2>::Take arg2) const
    {
        return Base::operator()(obj, arg1, arg2);
    }

    T_return
    operator()(T_obj &obj, typename QExtTypeTrait<T_arg1>::Take arg1, typename QExtTypeTrait<T_arg2>::Take arg2) const
    {
        return Base::operator()(obj, arg1, arg2);
    }
};

template<typename T_return, typename T_obj, typename T_arg1>
class QExtVolatileMemberFunctor<T_return, T_obj, T_arg1, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
        : public QExtPrivate::QExtVolatileMemberFunctor1<T_return, T_obj, T_arg1>
{
    typedef QExtPrivate::QExtVolatileMemberFunctor1<T_return, T_obj, T_arg1> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtVolatileMemberFunctor() {}

    QExtVolatileMemberFunctor(Function func) : Base(func) {}

    QExtVolatileMemberFunctor(const QExtVolatileMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(T_obj *obj, typename QExtTypeTrait<T_arg1>::Take arg1) const
    {
        return Base::operator()(obj, arg1);
    }

    T_return operator()(T_obj &obj, typename QExtTypeTrait<T_arg1>::Take arg1) const
    {
        return Base::operator()(obj, arg1);
    }
};

template<typename T_return, typename T_obj>
class QExtVolatileMemberFunctor<T_return, T_obj, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
        : public QExtPrivate::QExtVolatileMemberFunctor0<T_return, T_obj>
{
    typedef QExtPrivate::QExtVolatileMemberFunctor0<T_return, T_obj> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtVolatileMemberFunctor() {}

    QExtVolatileMemberFunctor(Function func) : Base(func) {}

    QExtVolatileMemberFunctor(const QExtVolatileMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(T_obj *obj) const
    {
        return Base::operator()(obj);
    }

    T_return operator()(T_obj &obj) const
    {
        return Base::operator()(obj);
    }
};

template<
        typename T_return,
        typename T_obj,
        typename T_arg1 = QExtNil,
        typename T_arg2 = QExtNil,
        typename T_arg3 = QExtNil,
        typename T_arg4 = QExtNil,
        typename T_arg5 = QExtNil,
        typename T_arg6 = QExtNil,
        typename T_arg7 = QExtNil>
class QExtConstVolatileMemberFunctor
        : public QExtPrivate::QExtConstVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
{
    typedef QExtPrivate::QExtConstVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtConstVolatileMemberFunctor() {}

    QExtConstVolatileMemberFunctor(Function func) : Base(func) {}

    QExtConstVolatileMemberFunctor(const QExtConstVolatileMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(
            const T_obj *obj,
            typename QExtTypeTrait<T_arg1>::Take arg1,
            typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3,
            typename QExtTypeTrait<T_arg4>::Take arg4,
            typename QExtTypeTrait<T_arg5>::Take arg5,
            typename QExtTypeTrait<T_arg6>::Take arg6,
            typename QExtTypeTrait<T_arg7>::Take arg7) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    T_return operator()(
            const T_obj &obj,
            typename QExtTypeTrait<T_arg1>::Take arg1,
            typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3,
            typename QExtTypeTrait<T_arg4>::Take arg4,
            typename QExtTypeTrait<T_arg5>::Take arg5,
            typename QExtTypeTrait<T_arg6>::Take arg6,
            typename QExtTypeTrait<T_arg7>::Take arg7) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
class QExtConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QExtNil>
        : public QExtPrivate::QExtConstVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
{
    typedef QExtPrivate::QExtConstVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtConstVolatileMemberFunctor() {}

    QExtConstVolatileMemberFunctor(Function func) : Base(func) {}

    QExtConstVolatileMemberFunctor(const QExtConstVolatileMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(
            const T_obj *obj,
            typename QExtTypeTrait<T_arg1>::Take arg1,
            typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3,
            typename QExtTypeTrait<T_arg4>::Take arg4,
            typename QExtTypeTrait<T_arg5>::Take arg5,
            typename QExtTypeTrait<T_arg6>::Take arg6) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4, arg5, arg6);
    }

    T_return operator()(
            const T_obj &obj,
            typename QExtTypeTrait<T_arg1>::Take arg1,
            typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3,
            typename QExtTypeTrait<T_arg4>::Take arg4,
            typename QExtTypeTrait<T_arg5>::Take arg5,
            typename QExtTypeTrait<T_arg6>::Take arg6) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class QExtConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QExtNil, QExtNil>
        : public QExtPrivate::QExtConstVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
{
    typedef QExtPrivate::QExtConstVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtConstVolatileMemberFunctor() {}

    QExtConstVolatileMemberFunctor(Function func) : Base(func) {}

    QExtConstVolatileMemberFunctor(const QExtConstVolatileMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(
            const T_obj *obj,
            typename QExtTypeTrait<T_arg1>::Take arg1,
            typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3,
            typename QExtTypeTrait<T_arg4>::Take arg4,
            typename QExtTypeTrait<T_arg5>::Take arg5) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4, arg5);
    }

    T_return operator()(
            const T_obj &obj,
            typename QExtTypeTrait<T_arg1>::Take arg1,
            typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3,
            typename QExtTypeTrait<T_arg4>::Take arg4,
            typename QExtTypeTrait<T_arg5>::Take arg5) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4, arg5);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class QExtConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, QExtNil, QExtNil, QExtNil>
        : public QExtPrivate::QExtConstVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
{
    typedef QExtPrivate::QExtConstVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtConstVolatileMemberFunctor() {}

    QExtConstVolatileMemberFunctor(Function func) : Base(func) {}

    QExtConstVolatileMemberFunctor(const QExtConstVolatileMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(
            const T_obj *obj,
            typename QExtTypeTrait<T_arg1>::Take arg1,
            typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3,
            typename QExtTypeTrait<T_arg4>::Take arg4) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4);
    }

    T_return operator()(
            const T_obj &obj,
            typename QExtTypeTrait<T_arg1>::Take arg1,
            typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3,
            typename QExtTypeTrait<T_arg4>::Take arg4) const
    {
        return Base::operator()(obj, arg1, arg2, arg3, arg4);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
class QExtConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, QExtNil, QExtNil, QExtNil, QExtNil>
        : public QExtPrivate::QExtConstVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
{
    typedef QExtPrivate::QExtConstVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtConstVolatileMemberFunctor() {}

    QExtConstVolatileMemberFunctor(Function func) : Base(func) {}

    QExtConstVolatileMemberFunctor(const QExtConstVolatileMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(
            const T_obj *obj, typename QExtTypeTrait<T_arg1>::Take arg1, typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3) const
    {
        return Base::operator()(obj, arg1, arg2, arg3);
    }

    T_return operator()(
            const T_obj &obj, typename QExtTypeTrait<T_arg1>::Take arg1, typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3) const
    {
        return Base::operator()(obj, arg1, arg2, arg3);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
class QExtConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
        : public QExtPrivate::QExtConstVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
{
    typedef QExtPrivate::QExtConstVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtConstVolatileMemberFunctor() {}

    QExtConstVolatileMemberFunctor(Function func) : Base(func) {}

    QExtConstVolatileMemberFunctor(const QExtConstVolatileMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(const T_obj *obj, typename QExtTypeTrait<T_arg1>::Take arg1,
                        typename QExtTypeTrait<T_arg2>::Take arg2) const
    {
        return Base::operator()(obj, arg1, arg2);
    }

    T_return operator()(const T_obj &obj, typename QExtTypeTrait<T_arg1>::Take arg1,
                        typename QExtTypeTrait<T_arg2>::Take arg2) const
    {
        return Base::operator()(obj, arg1, arg2);
    }
};

template<typename T_return, typename T_obj, typename T_arg1>
class QExtConstVolatileMemberFunctor<T_return, T_obj, T_arg1, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
        : public QExtPrivate::QExtConstVolatileMemberFunctor1<T_return, T_obj, T_arg1>
{
    typedef QExtPrivate::QExtConstVolatileMemberFunctor1<T_return, T_obj, T_arg1> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtConstVolatileMemberFunctor() {}

    QExtConstVolatileMemberFunctor(Function func) : Base(func) {}

    QExtConstVolatileMemberFunctor(const QExtConstVolatileMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(const T_obj *obj, typename QExtTypeTrait<T_arg1>::Take arg1) const
    {
        return Base::operator()(obj, arg1);
    }

    T_return operator()(const T_obj &obj, typename QExtTypeTrait<T_arg1>::Take arg1) const
    {
        return Base::operator()(obj, arg1);
    }
};

template<typename T_return, typename T_obj>
class QExtConstVolatileMemberFunctor<T_return, T_obj, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
        : public QExtPrivate::QExtConstVolatileMemberFunctor0<T_return, T_obj>
{
    typedef QExtPrivate::QExtConstVolatileMemberFunctor0<T_return, T_obj> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtConstVolatileMemberFunctor() {}

    QExtConstVolatileMemberFunctor(Function func) : Base(func) {}

    QExtConstVolatileMemberFunctor(const QExtConstVolatileMemberFunctor &other) : Base(other.m_funcPtr) {}

    T_return operator()(const T_obj *obj) const
    {
        return Base::operator()(obj);
    }

    T_return operator()(const T_obj &obj) const
    {
        return Base::operator()(obj);
    }
};

template<
        typename T_return,
        typename T_obj,
        typename T_arg1 = QExtNil,
        typename T_arg2 = QExtNil,
        typename T_arg3 = QExtNil,
        typename T_arg4 = QExtNil,
        typename T_arg5 = QExtNil,
        typename T_arg6 = QExtNil,
        typename T_arg7 = QExtNil>
class QExtBoundMemberFunctor
        : public QExtPrivate::QExtBoundMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
{
    typedef QExtPrivate::QExtBoundMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtBoundMemberFunctor(T_obj *obj, Function func) : Base(obj, func) {}

    QExtBoundMemberFunctor(T_obj &obj, Function func) : Base(obj, func) {}

    QExtBoundMemberFunctor(const QExtBoundMemberFunctor &other) : Base(other) {}

    T_return operator()(
            typename QExtTypeTrait<T_arg1>::Take arg1,
            typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3,
            typename QExtTypeTrait<T_arg4>::Take arg4,
            typename QExtTypeTrait<T_arg5>::Take arg5,
            typename QExtTypeTrait<T_arg6>::Take arg6,
            typename QExtTypeTrait<T_arg7>::Take arg7) const
    {
        return Base::operator()(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

template<
        typename T_return,
        typename T_obj,
        typename T_arg1,
        typename T_arg2,
        typename T_arg3,
        typename T_arg4,
        typename T_arg5,
        typename T_arg6,
        typename T_arg7>
struct QExtVisitor<QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> >
{
    template<typename T_action>
    static void
    doVisitEach(const T_action &action,
                const QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
class QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QExtNil>
        : public QExtPrivate::QExtBoundMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
{
    typedef QExtPrivate::QExtBoundMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtBoundMemberFunctor(T_obj *obj, Function func) : Base(obj, func) {}

    QExtBoundMemberFunctor(T_obj &obj, Function func) : Base(obj, func) {}

    QExtBoundMemberFunctor(const QExtBoundMemberFunctor &other) : Base(other) {}

    T_return operator()(
            typename QExtTypeTrait<T_arg1>::Take arg1,
            typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3,
            typename QExtTypeTrait<T_arg4>::Take arg4,
            typename QExtTypeTrait<T_arg5>::Take arg5,
            typename QExtTypeTrait<T_arg6>::Take arg6) const
    {
        return Base::operator()(arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
struct QExtVisitor<QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> >
{
    template<typename T_action>
    static void doVisitEach(const T_action &action,
                            const QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QExtNil, QExtNil>
        : public QExtPrivate::QExtBoundMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
{
    typedef QExtPrivate::QExtBoundMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtBoundMemberFunctor(T_obj *obj, Function func) : Base(obj, func) {}

    QExtBoundMemberFunctor(T_obj &obj, Function func) : Base(obj, func) {}

    QExtBoundMemberFunctor(const QExtBoundMemberFunctor &other) : Base(other) {}

    T_return operator()(
            typename QExtTypeTrait<T_arg1>::Take arg1,
            typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3,
            typename QExtTypeTrait<T_arg4>::Take arg4,
            typename QExtTypeTrait<T_arg5>::Take arg5) const
    {
        return Base::operator()(arg1, arg2, arg3, arg4, arg5);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
struct QExtVisitor<QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> >
{
    template<typename T_action>
    static void doVisitEach(const T_action &action,
                            const QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, QExtNil, QExtNil, QExtNil>
        : public QExtPrivate::QExtBoundMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
{
    typedef QExtPrivate::QExtBoundMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtBoundMemberFunctor(T_obj *obj, Function func) : Base(obj, func) {}

    QExtBoundMemberFunctor(T_obj &obj, Function func) : Base(obj, func) {}

    QExtBoundMemberFunctor(const QExtBoundMemberFunctor &other) : Base(other) {}

    T_return operator()(
            typename QExtTypeTrait<T_arg1>::Take arg1,
            typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3,
            typename QExtTypeTrait<T_arg4>::Take arg4) const
    {
        return Base::operator()(arg1, arg2, arg3, arg4);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
struct QExtVisitor<QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> >
{
    template<typename T_action>
    static void doVisitEach(const T_action &action,
                            const QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
class QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, QExtNil, QExtNil, QExtNil, QExtNil>
        : public QExtPrivate::QExtBoundMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
{
    typedef QExtPrivate::QExtBoundMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtBoundMemberFunctor(T_obj *obj, Function func) : Base(obj, func) {}

    QExtBoundMemberFunctor(T_obj &obj, Function func) : Base(obj, func) {}

    QExtBoundMemberFunctor(const QExtBoundMemberFunctor &other) : Base(other) {}

    T_return operator()(typename QExtTypeTrait<T_arg1>::Take arg1, typename QExtTypeTrait<T_arg2>::Take arg2,
                        typename QExtTypeTrait<T_arg3>::Take arg3) const
    {
        return Base::operator()(arg1, arg2, arg3);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
struct QExtVisitor<QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3> >
{
    template<typename T_action>
    static void
    doVisitEach(const T_action &action, const QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3> &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
class QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
        : public QExtPrivate::QExtBoundMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
{
    typedef QExtPrivate::QExtBoundMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtBoundMemberFunctor(T_obj *obj, Function func) : Base(obj, func) {}

    QExtBoundMemberFunctor(T_obj &obj, Function func) : Base(obj, func) {}

    QExtBoundMemberFunctor(const QExtBoundMemberFunctor &other) : Base(other) {}

    T_return operator()(typename QExtTypeTrait<T_arg1>::Take arg1, typename QExtTypeTrait<T_arg2>::Take arg2) const
    {
        return Base::operator()(arg1, arg2);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
struct QExtVisitor<QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2> >
{
    template<typename T_action>
    static void
    doVisitEach(const T_action &action, const QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2> &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template<typename T_return, typename T_obj, typename T_arg1>
class QExtBoundMemberFunctor<T_return, T_obj, T_arg1, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
        : public QExtPrivate::QExtBoundMemberFunctor1<T_return, T_obj, T_arg1>
{
    typedef QExtPrivate::QExtBoundMemberFunctor1<T_return, T_obj, T_arg1> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtBoundMemberFunctor(T_obj *obj, Function func) : Base(obj, func) {}

    QExtBoundMemberFunctor(T_obj &obj, Function func) : Base(obj, func) {}

    QExtBoundMemberFunctor(const QExtBoundMemberFunctor &other) : Base(other) {}

    T_return operator()(typename QExtTypeTrait<T_arg1>::Take arg1) const
    {
        return Base::operator()(arg1);
    }
};

template<typename T_return, typename T_obj, typename T_arg1>
struct QExtVisitor<QExtBoundMemberFunctor<T_return, T_obj, T_arg1> >
{
    template<typename T_action>
    static void doVisitEach(const T_action &action, const QExtBoundMemberFunctor<T_return, T_obj, T_arg1> &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template<typename T_return, typename T_obj>
class QExtBoundMemberFunctor<T_return, T_obj, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
        : public QExtPrivate::QExtBoundMemberFunctor0<T_return, T_obj>
{
    typedef QExtPrivate::QExtBoundMemberFunctor0<T_return, T_obj> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtBoundMemberFunctor(T_obj *obj, Function func) : Base(obj, func) {}

    QExtBoundMemberFunctor(T_obj &obj, Function func) : Base(obj, func) {}

    QExtBoundMemberFunctor(const QExtBoundMemberFunctor &other) : Base(other) {}

    T_return operator()() const
    {
        return Base::operator()();
    }
};

template<typename T_return, typename T_obj>
struct QExtVisitor<QExtBoundMemberFunctor<T_return, T_obj> >
{
    template<typename T_action>
    static void doVisitEach(const T_action &action, const QExtBoundMemberFunctor<T_return, T_obj> &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template<
        typename T_return,
        typename T_obj,
        typename T_arg1 = QExtNil,
        typename T_arg2 = QExtNil,
        typename T_arg3 = QExtNil,
        typename T_arg4 = QExtNil,
        typename T_arg5 = QExtNil,
        typename T_arg6 = QExtNil,
        typename T_arg7 = QExtNil>
class QExtBoundConstMemberFunctor
        : public QExtPrivate::QExtBoundConstMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
{
    typedef QExtPrivate::QExtBoundConstMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtBoundConstMemberFunctor(const T_obj *obj, Function func) : Base(obj, func) {}

    QExtBoundConstMemberFunctor(const T_obj &obj, Function func) : Base(obj, func) {}

    QExtBoundConstMemberFunctor(const QExtBoundConstMemberFunctor &other) : Base(other) {}

    T_return operator()(
            typename QExtTypeTrait<T_arg1>::Take arg1,
            typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3,
            typename QExtTypeTrait<T_arg4>::Take arg4,
            typename QExtTypeTrait<T_arg5>::Take arg5,
            typename QExtTypeTrait<T_arg6>::Take arg6,
            typename QExtTypeTrait<T_arg7>::Take arg7) const
    {
        return Base::operator()(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

template<
        typename T_return,
        typename T_obj,
        typename T_arg1,
        typename T_arg2,
        typename T_arg3,
        typename T_arg4,
        typename T_arg5,
        typename T_arg6,
        typename T_arg7>
struct QExtVisitor<QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> >
{
    template<typename T_action>
    static void
    doVisitEach(const T_action &action,
                const QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
class QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QExtNil>
        : public QExtPrivate::QExtBoundConstMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
{
    typedef QExtPrivate::QExtBoundConstMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtBoundConstMemberFunctor(const T_obj *obj, Function func) : Base(obj, func) {}

    QExtBoundConstMemberFunctor(const T_obj &obj, Function func) : Base(obj, func) {}

    QExtBoundConstMemberFunctor(const QExtBoundConstMemberFunctor &other) : Base(other) {}

    T_return operator()(
            typename QExtTypeTrait<T_arg1>::Take arg1,
            typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3,
            typename QExtTypeTrait<T_arg4>::Take arg4,
            typename QExtTypeTrait<T_arg5>::Take arg5,
            typename QExtTypeTrait<T_arg6>::Take arg6) const
    {
        return Base::operator()(arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
struct QExtVisitor<QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> >
{
    template<typename T_action>
    static void doVisitEach(const T_action &action,
                            const QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QExtNil, QExtNil>
        : public QExtPrivate::QExtBoundConstMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
{
    typedef QExtPrivate::QExtBoundConstMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtBoundConstMemberFunctor(const T_obj *obj, Function func) : Base(obj, func) {}

    QExtBoundConstMemberFunctor(const T_obj &obj, Function func) : Base(obj, func) {}

    QExtBoundConstMemberFunctor(const QExtBoundConstMemberFunctor &other) : Base(other) {}

    T_return operator()(
            typename QExtTypeTrait<T_arg1>::Take arg1,
            typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3,
            typename QExtTypeTrait<T_arg4>::Take arg4,
            typename QExtTypeTrait<T_arg5>::Take arg5) const
    {
        return Base::operator()(arg1, arg2, arg3, arg4, arg5);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
struct QExtVisitor<QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> >
{
    template<typename T_action>
    static void doVisitEach(const T_action &action,
                            const QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, QExtNil, QExtNil, QExtNil>
        : public QExtPrivate::QExtBoundConstMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
{
    typedef QExtPrivate::QExtBoundConstMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtBoundConstMemberFunctor(const T_obj *obj, Function func) : Base(obj, func) {}

    QExtBoundConstMemberFunctor(const T_obj &obj, Function func) : Base(obj, func) {}

    QExtBoundConstMemberFunctor(const QExtBoundConstMemberFunctor &other) : Base(other) {}

    T_return operator()(
            typename QExtTypeTrait<T_arg1>::Take arg1,
            typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3,
            typename QExtTypeTrait<T_arg4>::Take arg4) const
    {
        return Base::operator()(arg1, arg2, arg3, arg4);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
struct QExtVisitor<QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> >
{
    template<typename T_action>
    static void doVisitEach(const T_action &action,
                            const QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
class QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, QExtNil, QExtNil, QExtNil, QExtNil>
        : public QExtPrivate::QExtBoundConstMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
{
    typedef QExtPrivate::QExtBoundConstMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtBoundConstMemberFunctor(const T_obj *obj, Function func) : Base(obj, func) {}

    QExtBoundConstMemberFunctor(const T_obj &obj, Function func) : Base(obj, func) {}

    QExtBoundConstMemberFunctor(const QExtBoundConstMemberFunctor &other) : Base(other) {}

    T_return operator()(typename QExtTypeTrait<T_arg1>::Take arg1, typename QExtTypeTrait<T_arg2>::Take arg2,
                        typename QExtTypeTrait<T_arg3>::Take arg3) const
    {
        return Base::operator()(arg1, arg2, arg3);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
struct QExtVisitor<QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3> >
{
    template<typename T_action>
    static void doVisitEach(const T_action &action,
                            const QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3> &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
class QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
        : public QExtPrivate::QExtBoundConstMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
{
    typedef QExtPrivate::QExtBoundConstMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtBoundConstMemberFunctor(const T_obj *obj, Function func) : Base(obj, func) {}

    QExtBoundConstMemberFunctor(const T_obj &obj, Function func) : Base(obj, func) {}

    QExtBoundConstMemberFunctor(const QExtBoundConstMemberFunctor &other) : Base(other) {}

    T_return operator()(typename QExtTypeTrait<T_arg1>::Take arg1, typename QExtTypeTrait<T_arg2>::Take arg2) const
    {
        return Base::operator()(arg1, arg2);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
struct QExtVisitor<QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2> >
{
    template<typename T_action>
    static void
    doVisitEach(const T_action &action, const QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2> &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template<typename T_return, typename T_obj, typename T_arg1>
class QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
        : public QExtPrivate::QExtBoundConstMemberFunctor1<T_return, T_obj, T_arg1>
{
    typedef QExtPrivate::QExtBoundConstMemberFunctor1<T_return, T_obj, T_arg1> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtBoundConstMemberFunctor(const T_obj *obj, Function func) : Base(obj, func) {}

    QExtBoundConstMemberFunctor(const T_obj &obj, Function func) : Base(obj, func) {}

    QExtBoundConstMemberFunctor(const QExtBoundConstMemberFunctor &other) : Base(other) {}

    T_return operator()(typename QExtTypeTrait<T_arg1>::Take arg1) const
    {
        return Base::operator()(arg1);
    }
};

template<typename T_return, typename T_obj, typename T_arg1>
struct QExtVisitor<QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1> >
{
    template<typename T_action>
    static void doVisitEach(const T_action &action, const QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1> &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template<typename T_return, typename T_obj>
class QExtBoundConstMemberFunctor<T_return, T_obj, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
        : public QExtPrivate::QExtBoundConstMemberFunctor0<T_return, T_obj>
{
    typedef QExtPrivate::QExtBoundConstMemberFunctor0<T_return, T_obj> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtBoundConstMemberFunctor(const T_obj *obj, Function func) : Base(obj, func) {}

    QExtBoundConstMemberFunctor(const T_obj &obj, Function func) : Base(obj, func) {}

    QExtBoundConstMemberFunctor(const QExtBoundConstMemberFunctor &other) : Base(other) {}

    T_return operator()() const
    {
        return Base::operator()();
    }
};

template<typename T_return, typename T_obj>
struct QExtVisitor<QExtBoundConstMemberFunctor<T_return, T_obj> >
{
    template<typename T_action>
    static void doVisitEach(const T_action &action, const QExtBoundConstMemberFunctor<T_return, T_obj> &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template<
        typename T_return,
        typename T_obj,
        typename T_arg1 = QExtNil,
        typename T_arg2 = QExtNil,
        typename T_arg3 = QExtNil,
        typename T_arg4 = QExtNil,
        typename T_arg5 = QExtNil,
        typename T_arg6 = QExtNil,
        typename T_arg7 = QExtNil>
class QExtBoundVolatileMemberFunctor
        : public QExtPrivate::QExtBoundVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
{
    typedef QExtPrivate::QExtBoundVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtBoundVolatileMemberFunctor(T_obj *obj, Function func) : Base(obj, func) {}

    QExtBoundVolatileMemberFunctor(T_obj &obj, Function func) : Base(obj, func) {}

    QExtBoundVolatileMemberFunctor(const QExtBoundVolatileMemberFunctor &other) : Base(other) {}

    T_return operator()(
            typename QExtTypeTrait<T_arg1>::Take arg1,
            typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3,
            typename QExtTypeTrait<T_arg4>::Take arg4,
            typename QExtTypeTrait<T_arg5>::Take arg5,
            typename QExtTypeTrait<T_arg6>::Take arg6,
            typename QExtTypeTrait<T_arg7>::Take arg7) const
    {
        return Base::operator()(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

template<
        typename T_return,
        typename T_obj,
        typename T_arg1,
        typename T_arg2,
        typename T_arg3,
        typename T_arg4,
        typename T_arg5,
        typename T_arg6,
        typename T_arg7>
struct QExtVisitor<QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> >
{
    template<typename T_action>
    static void
    doVisitEach(const T_action &action,
                const QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
class QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QExtNil>
        : public QExtPrivate::QExtBoundVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
{
    typedef QExtPrivate::QExtBoundVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtBoundVolatileMemberFunctor(T_obj *obj, Function func) : Base(obj, func) {}

    QExtBoundVolatileMemberFunctor(T_obj &obj, Function func) : Base(obj, func) {}

    QExtBoundVolatileMemberFunctor(const QExtBoundVolatileMemberFunctor &other) : Base(other) {}

    T_return operator()(
            typename QExtTypeTrait<T_arg1>::Take arg1,
            typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3,
            typename QExtTypeTrait<T_arg4>::Take arg4,
            typename QExtTypeTrait<T_arg5>::Take arg5,
            typename QExtTypeTrait<T_arg6>::Take arg6) const
    {
        return Base::operator()(arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
struct QExtVisitor<QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> >
{
    template<typename T_action>
    static void
    doVisitEach(const T_action &action,
                const QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QExtNil, QExtNil>
        : public QExtPrivate::QExtBoundVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
{
    typedef QExtPrivate::QExtBoundVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtBoundVolatileMemberFunctor(T_obj *obj, Function func) : Base(obj, func) {}

    QExtBoundVolatileMemberFunctor(T_obj &obj, Function func) : Base(obj, func) {}

    QExtBoundVolatileMemberFunctor(const QExtBoundVolatileMemberFunctor &other) : Base(other) {}

    T_return operator()(
            typename QExtTypeTrait<T_arg1>::Take arg1,
            typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3,
            typename QExtTypeTrait<T_arg4>::Take arg4,
            typename QExtTypeTrait<T_arg5>::Take arg5) const
    {
        return Base::operator()(arg1, arg2, arg3, arg4, arg5);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
struct QExtVisitor<QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> >
{
    template<typename T_action>
    static void doVisitEach(const T_action &action,
                            const QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, QExtNil, QExtNil, QExtNil>
        : public QExtPrivate::QExtBoundVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
{
    typedef QExtPrivate::QExtBoundVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtBoundVolatileMemberFunctor(T_obj *obj, Function func) : Base(obj, func) {}

    QExtBoundVolatileMemberFunctor(T_obj &obj, Function func) : Base(obj, func) {}

    QExtBoundVolatileMemberFunctor(const QExtBoundVolatileMemberFunctor &other) : Base(other) {}

    T_return operator()(
            typename QExtTypeTrait<T_arg1>::Take arg1,
            typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3,
            typename QExtTypeTrait<T_arg4>::Take arg4) const
    {
        return Base::operator()(arg1, arg2, arg3, arg4);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
struct QExtVisitor<QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> >
{
    template<typename T_action>
    static void doVisitEach(const T_action &action,
                            const QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
class QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, QExtNil, QExtNil, QExtNil, QExtNil>
        : public QExtPrivate::QExtBoundVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
{
    typedef QExtPrivate::QExtBoundVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtBoundVolatileMemberFunctor(T_obj *obj, Function func) : Base(obj, func) {}

    QExtBoundVolatileMemberFunctor(T_obj &obj, Function func) : Base(obj, func) {}

    QExtBoundVolatileMemberFunctor(const QExtBoundVolatileMemberFunctor &other) : Base(other) {}

    T_return operator()(typename QExtTypeTrait<T_arg1>::Take arg1, typename QExtTypeTrait<T_arg2>::Take arg2,
                        typename QExtTypeTrait<T_arg3>::Take arg3) const
    {
        return Base::operator()(arg1, arg2, arg3);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
struct QExtVisitor<QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3> >
{
    template<typename T_action>
    static void doVisitEach(const T_action &action,
                            const QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3> &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
class QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
        : public QExtPrivate::QExtBoundVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
{
    typedef QExtPrivate::QExtBoundVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtBoundVolatileMemberFunctor(T_obj *obj, Function func) : Base(obj, func) {}

    QExtBoundVolatileMemberFunctor(T_obj &obj, Function func) : Base(obj, func) {}

    QExtBoundVolatileMemberFunctor(const QExtBoundVolatileMemberFunctor &other) : Base(other) {}

    T_return operator()(typename QExtTypeTrait<T_arg1>::Take arg1, typename QExtTypeTrait<T_arg2>::Take arg2) const
    {
        return Base::operator()(arg1, arg2);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
struct QExtVisitor<QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2> >
{
    template<typename T_action>
    static void
    doVisitEach(const T_action &action, const QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2> &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template<typename T_return, typename T_obj, typename T_arg1>
class QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
        : public QExtPrivate::QExtBoundVolatileMemberFunctor1<T_return, T_obj, T_arg1>
{
    typedef QExtPrivate::QExtBoundVolatileMemberFunctor1<T_return, T_obj, T_arg1> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtBoundVolatileMemberFunctor(T_obj *obj, Function func) : Base(obj, func) {}

    QExtBoundVolatileMemberFunctor(T_obj &obj, Function func) : Base(obj, func) {}

    QExtBoundVolatileMemberFunctor(const QExtBoundVolatileMemberFunctor &other) : Base(other) {}

    T_return operator()(typename QExtTypeTrait<T_arg1>::Take arg1) const
    {
        return Base::operator()(arg1);
    }
};

template<typename T_return, typename T_obj, typename T_arg1>
struct QExtVisitor<QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1> >
{
    template<typename T_action>
    static void
    doVisitEach(const T_action &action, const QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1> &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template<typename T_return, typename T_obj>
class QExtBoundVolatileMemberFunctor<T_return, T_obj, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
        : public QExtPrivate::QExtBoundVolatileMemberFunctor0<T_return, T_obj>
{
    typedef QExtPrivate::QExtBoundVolatileMemberFunctor0<T_return, T_obj> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtBoundVolatileMemberFunctor(T_obj *obj, Function func) : Base(obj, func) {}

    QExtBoundVolatileMemberFunctor(T_obj &obj, Function func) : Base(obj, func) {}

    QExtBoundVolatileMemberFunctor(const QExtBoundVolatileMemberFunctor &other) : Base(other) {}

    T_return operator()() const
    {
        return Base::operator()();
    }
};

template<typename T_return, typename T_obj>
struct QExtVisitor<QExtBoundVolatileMemberFunctor<T_return, T_obj> >
{
    template<typename T_action>
    static void doVisitEach(const T_action &action, const QExtBoundVolatileMemberFunctor<T_return, T_obj> &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template<
        typename T_return,
        typename T_obj,
        typename T_arg1 = QExtNil,
        typename T_arg2 = QExtNil,
        typename T_arg3 = QExtNil,
        typename T_arg4 = QExtNil,
        typename T_arg5 = QExtNil,
        typename T_arg6 = QExtNil,
        typename T_arg7 = QExtNil>
class QExtBoundConstVolatileMemberFunctor
        : public QExtPrivate::QExtBoundConstVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
{
    typedef QExtPrivate::QExtBoundConstVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtBoundConstVolatileMemberFunctor(const T_obj *obj, Function func) : Base(obj, func) {}

    QExtBoundConstVolatileMemberFunctor(const T_obj &obj, Function func) : Base(obj, func) {}

    QExtBoundConstVolatileMemberFunctor(const QExtBoundConstVolatileMemberFunctor &other) : Base(other) {}

    T_return operator()(
            typename QExtTypeTrait<T_arg1>::Take arg1,
            typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3,
            typename QExtTypeTrait<T_arg4>::Take arg4,
            typename QExtTypeTrait<T_arg5>::Take arg5,
            typename QExtTypeTrait<T_arg6>::Take arg6,
            typename QExtTypeTrait<T_arg7>::Take arg7) const
    {
        return Base::operator()(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

template<
        typename T_return,
        typename T_obj,
        typename T_arg1,
        typename T_arg2,
        typename T_arg3,
        typename T_arg4,
        typename T_arg5,
        typename T_arg6,
        typename T_arg7>
struct QExtVisitor<QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> >
{
    template<typename T_action>
    static void doVisitEach(
            const T_action &action,
            const QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
class QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QExtNil>
        : public QExtPrivate::QExtBoundConstVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
{
    typedef QExtPrivate::QExtBoundConstVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtBoundConstVolatileMemberFunctor(const T_obj *obj, Function func) : Base(obj, func) {}

    QExtBoundConstVolatileMemberFunctor(const T_obj &obj, Function func) : Base(obj, func) {}

    QExtBoundConstVolatileMemberFunctor(const QExtBoundConstVolatileMemberFunctor &other) : Base(other) {}

    T_return operator()(
            typename QExtTypeTrait<T_arg1>::Take arg1,
            typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3,
            typename QExtTypeTrait<T_arg4>::Take arg4,
            typename QExtTypeTrait<T_arg5>::Take arg5,
            typename QExtTypeTrait<T_arg6>::Take arg6) const
    {
        return Base::operator()(arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
struct QExtVisitor<QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> >
{
    template<typename T_action>
    static void
    doVisitEach(const T_action &action,
                const QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QExtNil, QExtNil>
        : public QExtPrivate::QExtBoundConstVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
{
    typedef QExtPrivate::QExtBoundConstVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtBoundConstVolatileMemberFunctor(const T_obj *obj, Function func) : Base(obj, func) {}

    QExtBoundConstVolatileMemberFunctor(const T_obj &obj, Function func) : Base(obj, func) {}

    QExtBoundConstVolatileMemberFunctor(const QExtBoundConstVolatileMemberFunctor &other) : Base(other) {}

    T_return operator()(
            typename QExtTypeTrait<T_arg1>::Take arg1,
            typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3,
            typename QExtTypeTrait<T_arg4>::Take arg4,
            typename QExtTypeTrait<T_arg5>::Take arg5) const
    {
        return Base::operator()(arg1, arg2, arg3, arg4, arg5);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
struct QExtVisitor<QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> >
{
    template<typename T_action>
    static void doVisitEach(const T_action &action,
                            const QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, QExtNil, QExtNil, QExtNil>
        : public QExtPrivate::QExtBoundConstVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
{
    typedef QExtPrivate::QExtBoundConstVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtBoundConstVolatileMemberFunctor(const T_obj *obj, Function func) : Base(obj, func) {}

    QExtBoundConstVolatileMemberFunctor(const T_obj &obj, Function func) : Base(obj, func) {}

    QExtBoundConstVolatileMemberFunctor(const QExtBoundConstVolatileMemberFunctor &other) : Base(other) {}

    T_return operator()(
            typename QExtTypeTrait<T_arg1>::Take arg1,
            typename QExtTypeTrait<T_arg2>::Take arg2,
            typename QExtTypeTrait<T_arg3>::Take arg3,
            typename QExtTypeTrait<T_arg4>::Take arg4) const
    {
        return Base::operator()(arg1, arg2, arg3, arg4);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
struct QExtVisitor<QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> >
{
    template<typename T_action>
    static void doVisitEach(const T_action &action,
                            const QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
class QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, QExtNil, QExtNil, QExtNil, QExtNil>
        : public QExtPrivate::QExtBoundConstVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
{
    typedef QExtPrivate::QExtBoundConstVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtBoundConstVolatileMemberFunctor(const T_obj *obj, Function func) : Base(obj, func) {}

    QExtBoundConstVolatileMemberFunctor(const T_obj &obj, Function func) : Base(obj, func) {}

    QExtBoundConstVolatileMemberFunctor(const QExtBoundConstVolatileMemberFunctor &other) : Base(other) {}

    T_return operator()(typename QExtTypeTrait<T_arg1>::Take arg1, typename QExtTypeTrait<T_arg2>::Take arg2,
                        typename QExtTypeTrait<T_arg3>::Take arg3) const
    {
        return Base::operator()(arg1, arg2, arg3);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
struct QExtVisitor<QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3> >
{
    template<typename T_action>
    static void doVisitEach(const T_action &action,
                            const QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3> &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
class QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
        : public QExtPrivate::QExtBoundConstVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
{
    typedef QExtPrivate::QExtBoundConstVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtBoundConstVolatileMemberFunctor(const T_obj *obj, Function func) : Base(obj, func) {}

    QExtBoundConstVolatileMemberFunctor(const T_obj &obj, Function func) : Base(obj, func) {}

    QExtBoundConstVolatileMemberFunctor(const QExtBoundConstVolatileMemberFunctor &other) : Base(other) {}

    T_return operator()(typename QExtTypeTrait<T_arg1>::Take arg1, typename QExtTypeTrait<T_arg2>::Take arg2) const
    {
        return Base::operator()(arg1, arg2);
    }
};

template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
struct QExtVisitor<QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2> >
{
    template<typename T_action>
    static void doVisitEach(const T_action &action,
                            const QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2> &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template<typename T_return, typename T_obj, typename T_arg1>
class QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
        : public QExtPrivate::QExtBoundConstVolatileMemberFunctor1<T_return, T_obj, T_arg1>
{
    typedef QExtPrivate::QExtBoundConstVolatileMemberFunctor1<T_return, T_obj, T_arg1> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtBoundConstVolatileMemberFunctor(const T_obj *obj, Function func) : Base(obj, func) {}

    QExtBoundConstVolatileMemberFunctor(const T_obj &obj, Function func) : Base(obj, func) {}

    QExtBoundConstVolatileMemberFunctor(const QExtBoundConstVolatileMemberFunctor &other) : Base(other) {}

    T_return operator()(typename QExtTypeTrait<T_arg1>::Take arg1) const
    {
        return Base::operator()(arg1);
    }
};

template<typename T_return, typename T_obj, typename T_arg1>
struct QExtVisitor<QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1> >
{
    template<typename T_action>
    static void
    doVisitEach(const T_action &action, const QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1> &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

template<typename T_return, typename T_obj>
class QExtBoundConstVolatileMemberFunctor<T_return, T_obj, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
        : public QExtPrivate::QExtBoundConstVolatileMemberFunctor0<T_return, T_obj>
{
    typedef QExtPrivate::QExtBoundConstVolatileMemberFunctor0<T_return, T_obj> Base;

public:
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtBoundConstVolatileMemberFunctor(const T_obj *obj, Function func) : Base(obj, func) {}

    QExtBoundConstVolatileMemberFunctor(const T_obj &obj, Function func) : Base(obj, func) {}

    QExtBoundConstVolatileMemberFunctor(const QExtBoundConstVolatileMemberFunctor &other) : Base(other) {}

    T_return operator()() const
    {
        return Base::operator()();
    }
};

template<typename T_return, typename T_obj>
struct QExtVisitor<QExtBoundConstVolatileMemberFunctor<T_return, T_obj> >
{
    template<typename T_action>
    static void doVisitEach(const T_action &action, const QExtBoundConstVolatileMemberFunctor<T_return, T_obj> &target)
    {
        qextVisitEach(action, target.m_obj);
    }
};

/** Creates a functor of type QExtMemberFunctor which wraps a method with 7 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<
        typename T_return,
        typename T_obj,
        typename T_arg1,
        typename T_arg2,
        typename T_arg3,
        typename T_arg4,
        typename T_arg5,
        typename T_arg6,
        typename T_arg7>
inline QExtMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7))
{
    return QExtMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(func);
}

/** Creates a functor of type QExtMemberFunctor which wraps a method with 6 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
inline QExtMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6))
{
    return QExtMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(func);
}

/** Creates a functor of type QExtMemberFunctor which wraps a method with 5 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QExtMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5))
{
    return QExtMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(func);
}

/** Creates a functor of type QExtMemberFunctor which wraps a method with 4 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QExtMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4))
{
    return QExtMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(func);
}

/** Creates a functor of type QExtMemberFunctor which wraps a method with 3 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
inline QExtMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3))
{
    return QExtMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>(func);
}

/** Creates a functor of type QExtMemberFunctor which wraps a method with 2 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QExtMemberFunctor<T_return, T_obj, T_arg1, T_arg2> qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2))
{
    return QExtMemberFunctor<T_return, T_obj, T_arg1, T_arg2>(func);
}

/** Creates a functor of type QExtMemberFunctor which wraps a method with 1 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1>
inline QExtMemberFunctor<T_return, T_obj, T_arg1> qextMemberFunctor(T_return (T_obj::*func)(T_arg1))
{
    return QExtMemberFunctor<T_return, T_obj, T_arg1>(func);
}

/** Creates a functor of type QExtMemberFunctor which wraps a method with no args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj>
inline QExtMemberFunctor<T_return, T_obj> qextMemberFunctor(T_return (T_obj::*func)())
{
    return QExtMemberFunctor<T_return, T_obj>(func);
}

/** Creates a functor of type QExtConstMemberFunctor which wraps a const method with 7 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<
        typename T_return,
        typename T_obj,
        typename T_arg1,
        typename T_arg2,
        typename T_arg3,
        typename T_arg4,
        typename T_arg5,
        typename T_arg6,
        typename T_arg7>
inline QExtConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const)
{
    return QExtConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(func);
}

/** Creates a functor of type QExtConstMemberFunctor which wraps a const method with 6 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
inline QExtConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const)
{
    return QExtConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(func);
}

/** Creates a functor of type QExtConstMemberFunctor which wraps a const method with 5 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QExtConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const)
{
    return QExtConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(func);
}

/** Creates a functor of type QExtConstMemberFunctor which wraps a const method with 4 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QExtConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4) const)
{
    return QExtConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(func);
}

/** Creates a functor of type QExtConstMemberFunctor which wraps a const method with 3 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
inline QExtConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3) const)
{
    return QExtConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>(func);
}

/** Creates a functor of type QExtConstMemberFunctor which wraps a const method with 2 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QExtConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2) const)
{
    return QExtConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2>(func);
}

/** Creates a functor of type QExtConstMemberFunctor which wraps a const method with 1 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1>
inline QExtConstMemberFunctor<T_return, T_obj, T_arg1> qextMemberFunctor(T_return (T_obj::*func)(T_arg1) const)
{
    return QExtConstMemberFunctor<T_return, T_obj, T_arg1>(func);
}

/** Creates a functor of type QExtConstMemberFunctor which wraps a const method with no args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj>
inline QExtConstMemberFunctor<T_return, T_obj> qextMemberFunctor(T_return (T_obj::*func)() const)
{
    return QExtConstMemberFunctor<T_return, T_obj>(func);
}

/** Creates a functor of type QExtVolatileMemberFunctor which wraps a volatile method with 7 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<
        typename T_return,
        typename T_obj,
        typename T_arg1,
        typename T_arg2,
        typename T_arg3,
        typename T_arg4,
        typename T_arg5,
        typename T_arg6,
        typename T_arg7>
inline QExtVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) volatile)
{
    return QExtVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(func);
}

/** Creates a functor of type QExtVolatileMemberFunctor which wraps a volatile method with 6 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
inline QExtVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) volatile)
{
    return QExtVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(func);
}

/** Creates a functor of type QExtVolatileMemberFunctor which wraps a volatile method with 5 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QExtVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) volatile)
{
    return QExtVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(func);
}

/** Creates a functor of type QExtVolatileMemberFunctor which wraps a volatile method with 4 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QExtVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4) volatile)
{
    return QExtVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(func);
}

/** Creates a functor of type QExtVolatileMemberFunctor which wraps a volatile method with 3 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
inline QExtVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3) volatile)
{
    return QExtVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>(func);
}

/** Creates a functor of type QExtVolatileMemberFunctor which wraps a volatile method with 2 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QExtVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2) volatile)
{
    return QExtVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>(func);
}

/** Creates a functor of type QExtVolatileMemberFunctor which wraps a volatile method with 1 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1>
inline QExtVolatileMemberFunctor<T_return, T_obj, T_arg1> qextMemberFunctor(T_return (T_obj::*func)(T_arg1) volatile)
{
    return QExtVolatileMemberFunctor<T_return, T_obj, T_arg1>(func);
}

/** Creates a functor of type QExtVolatileMemberFunctor which wraps a volatile method with no args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj>
inline QExtVolatileMemberFunctor<T_return, T_obj> qextMemberFunctor(T_return (T_obj::*func)() volatile)
{
    return QExtVolatileMemberFunctor<T_return, T_obj>(func);
}

/** Creates a functor of type QExtConstVolatileMemberFunctor which wraps a const volatile method with 7 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<
        typename T_return,
        typename T_obj,
        typename T_arg1,
        typename T_arg2,
        typename T_arg3,
        typename T_arg4,
        typename T_arg5,
        typename T_arg6,
        typename T_arg7>
inline QExtConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const volatile)
{
    return QExtConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(
            func);
}

/** Creates a functor of type QExtConstVolatileMemberFunctor which wraps a const volatile method with 6 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
inline QExtConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const volatile)
{
    return QExtConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(func);
}

/** Creates a functor of type QExtConstVolatileMemberFunctor which wraps a const volatile method with 5 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QExtConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const volatile)
{
    return QExtConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(func);
}

/** Creates a functor of type QExtConstVolatileMemberFunctor which wraps a const volatile method with 4 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QExtConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4)
const volatile)
{
    return QExtConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(func);
}

/** Creates a functor of type QExtConstVolatileMemberFunctor which wraps a const volatile method with 3 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
inline QExtConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3) const volatile)
{
    return QExtConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>(func);
}

/** Creates a functor of type QExtConstVolatileMemberFunctor which wraps a const volatile method with 2 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QExtConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2) const volatile)
{
    return QExtConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>(func);
}

/** Creates a functor of type QExtConstVolatileMemberFunctor which wraps a const volatile method with 1 args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1>
inline QExtConstVolatileMemberFunctor<T_return, T_obj, T_arg1>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1) const volatile)
{
    return QExtConstVolatileMemberFunctor<T_return, T_obj, T_arg1>(func);
}

/** Creates a functor of type QExtConstVolatileMemberFunctor which wraps a const volatile method with no args.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj>
inline QExtConstVolatileMemberFunctor<T_return, T_obj> qextMemberFunctor(T_return (T_obj::*func)() const volatile)
{
    return QExtConstVolatileMemberFunctor<T_return, T_obj>(func);
}

/** Creates a functor of type QExtBoundMemberFunctor0 which encapsulates a method and an object instance with 7 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<
        typename T_return,
        typename T_obj,
        typename T_arg1,
        typename T_arg2,
        typename T_arg3,
        typename T_arg4,
        typename T_arg5,
        typename T_arg6,
        typename T_arg7>
inline QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7))
{
    return QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(obj, func);
}

/** Creates a functor of type QExtBoundMemberFunctor which encapsulates a method and an object instance with 7 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<
        typename T_return,
        typename T_obj,
        typename T_arg1,
        typename T_arg2,
        typename T_arg3,
        typename T_arg4,
        typename T_arg5,
        typename T_arg6,
        typename T_arg7>
inline QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7))
{
    return QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(obj, func);
}

/** Creates a functor of type QExtBoundMemberFunctor0 which encapsulates a method and an object instance with 6 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
inline QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6))
{
    return QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(obj, func);
}

/** Creates a functor of type QExtBoundMemberFunctor which encapsulates a method and an object instance with 6 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
inline QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6))
{
    return QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(obj, func);
}

/** Creates a functor of type QExtBoundMemberFunctor0 which encapsulates a method and an object instance with 5 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5))
{
    return QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(obj, func);
}

/** Creates a functor of type QExtBoundMemberFunctor which encapsulates a method and an object instance with 5 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5))
{
    return QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(obj, func);
}

/** Creates a functor of type QExtBoundMemberFunctor0 which encapsulates a method and an object instance with 4 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4))
{
    return QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(obj, func);
}

/** Creates a functor of type QExtBoundMemberFunctor which encapsulates a method and an object instance with 4 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4))
{
    return QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(obj, func);
}

/** Creates a functor of type QExtBoundMemberFunctor0 which encapsulates a method and an object instance with 3 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
inline QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3))
{
    return QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>(obj, func);
}

/** Creates a functor of type QExtBoundMemberFunctor which encapsulates a method and an object instance with 3 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
inline QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3))
{
    return QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>(obj, func);
}

/** Creates a functor of type QExtBoundMemberFunctor0 which encapsulates a method and an object instance with 2 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2))
{
    return QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2>(obj, func);
}

/** Creates a functor of type QExtBoundMemberFunctor which encapsulates a method and an object instance with 2 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2))
{
    return QExtBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2>(obj, func);
}

/** Creates a functor of type QExtBoundMemberFunctor0 which encapsulates a method and an object instance with 1 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1>
inline QExtBoundMemberFunctor<T_return, T_obj, T_arg1> qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1))
{
    return QExtBoundMemberFunctor<T_return, T_obj, T_arg1>(obj, func);
}

/** Creates a functor of type QExtBoundMemberFunctor which encapsulates a method and an object instance with 1 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1>
inline QExtBoundMemberFunctor<T_return, T_obj, T_arg1> qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1))
{
    return QExtBoundMemberFunctor<T_return, T_obj, T_arg1>(obj, func);
}

/** Creates a functor of type QExtBoundMemberFunctor0 which encapsulates a method and an object instance with no args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj>
inline QExtBoundMemberFunctor<T_return, T_obj> qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)())
{
    return QExtBoundMemberFunctor<T_return, T_obj>(obj, func);
}

/** Creates a functor of type QExtBoundMemberFunctor which encapsulates a method and an object instance with no args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj>
inline QExtBoundMemberFunctor<T_return, T_obj> qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)())
{
    return QExtBoundMemberFunctor<T_return, T_obj>(obj, func);
}

/** Creates a functor of type QExtBoundConstMemberFunctor which encapsulates a method and an object instance with 7 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<
        typename T_return,
        typename T_obj,
        typename T_arg1,
        typename T_arg2,
        typename T_arg3,
        typename T_arg4,
        typename T_arg5,
        typename T_arg6,
        typename T_arg7>
inline QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const)
{
    return QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(obj,
                                                                                                                func);
}

/** Creates a functor of type QExtBoundConstMemberFunctor which encapsulates a method and an object instance with 7 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<
        typename T_return,
        typename T_obj,
        typename T_arg1,
        typename T_arg2,
        typename T_arg3,
        typename T_arg4,
        typename T_arg5,
        typename T_arg6,
        typename T_arg7>
inline QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const)
{
    return QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(obj,
                                                                                                                func);
}

/** Creates a functor of type QExtBoundConstMemberFunctor which encapsulates a method and an object instance with 6 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
inline QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const)
{
    return QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(obj, func);
}

/** Creates a functor of type QExtBoundConstMemberFunctor which encapsulates a method and an object instance with 6 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
inline QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const)
{
    return QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(obj, func);
}

/** Creates a functor of type QExtBoundConstMemberFunctor which encapsulates a method and an object instance with 5 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const)
{
    return QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(obj, func);
}

/** Creates a functor of type QExtBoundConstMemberFunctor which encapsulates a method and an object instance with 5 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const)
{
    return QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(obj, func);
}

/** Creates a functor of type QExtBoundConstMemberFunctor which encapsulates a method and an object instance with 4 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4) const)
{
    return QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(obj, func);
}

/** Creates a functor of type QExtBoundConstMemberFunctor which encapsulates a method and an object instance with 4 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4) const)
{
    return QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(obj, func);
}

/** Creates a functor of type QExtBoundConstMemberFunctor which encapsulates a method and an object instance with 3 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
inline QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3) const)
{
    return QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>(obj, func);
}

/** Creates a functor of type QExtBoundConstMemberFunctor which encapsulates a method and an object instance with 3 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
inline QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3) const)
{
    return QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>(obj, func);
}

/** Creates a functor of type QExtBoundConstMemberFunctor which encapsulates a method and an object instance with 2 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2) const)
{
    return QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2>(obj, func);
}

/** Creates a functor of type QExtBoundConstMemberFunctor which encapsulates a method and an object instance with 2 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2) const)
{
    return QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2>(obj, func);
}

/** Creates a functor of type QExtBoundConstMemberFunctor which encapsulates a method and an object instance with 1 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1>
inline QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1>
qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1) const)
{
    return QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1>(obj, func);
}

/** Creates a functor of type QExtBoundConstMemberFunctor which encapsulates a method and an object instance with 1 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1>
inline QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1>
qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1) const)
{
    return QExtBoundConstMemberFunctor<T_return, T_obj, T_arg1>(obj, func);
}

/** Creates a functor of type QExtBoundConstMemberFunctor which encapsulates a method and an object instance with no args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj>
inline QExtBoundConstMemberFunctor<T_return, T_obj> qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)() const)
{
    return QExtBoundConstMemberFunctor<T_return, T_obj>(obj, func);
}

/** Creates a functor of type QExtBoundConstMemberFunctor which encapsulates a method and an object instance with no args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj>
inline QExtBoundConstMemberFunctor<T_return, T_obj> qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)() const)
{
    return QExtBoundConstMemberFunctor<T_return, T_obj>(obj, func);
}

/** Creates a functor of type QExtBoundVolatileMemberFunctor which encapsulates a method and an object instance with 7 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<
        typename T_return,
        typename T_obj,
        typename T_arg1,
        typename T_arg2,
        typename T_arg3,
        typename T_arg4,
        typename T_arg5,
        typename T_arg6,
        typename T_arg7>
inline QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) volatile)
{
    return QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(obj,
                                                                                                                   func);
}

/** Creates a functor of type QExtBoundVolatileMemberFunctor which encapsulates a method and an object instance with 7 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<
        typename T_return,
        typename T_obj,
        typename T_arg1,
        typename T_arg2,
        typename T_arg3,
        typename T_arg4,
        typename T_arg5,
        typename T_arg6,
        typename T_arg7>
inline QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) volatile)
{
    return QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(obj,
                                                                                                                   func);
}

/** Creates a functor of type QExtBoundVolatileMemberFunctor which encapsulates a method and an object instance with 6 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
inline QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) volatile)
{
    return QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(obj, func);
}

/** Creates a functor of type QExtBoundVolatileMemberFunctor which encapsulates a method and an object instance with 6 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
inline QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) volatile)
{
    return QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(obj, func);
}

/** Creates a functor of type QExtBoundVolatileMemberFunctor which encapsulates a method and an object instance with 5 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) volatile)
{
    return QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(obj, func);
}

/** Creates a functor of type QExtBoundVolatileMemberFunctor which encapsulates a method and an object instance with 5 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) volatile)
{
    return QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(obj, func);
}

/** Creates a functor of type QExtBoundVolatileMemberFunctor which encapsulates a method and an object instance with 4 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4) volatile)
{
    return QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(obj, func);
}

/** Creates a functor of type QExtBoundVolatileMemberFunctor which encapsulates a method and an object instance with 4 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4) volatile)
{
    return QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(obj, func);
}

/** Creates a functor of type QExtBoundVolatileMemberFunctor which encapsulates a method and an object instance with 3 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
inline QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3) volatile)
{
    return QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>(obj, func);
}

/** Creates a functor of type QExtBoundVolatileMemberFunctor which encapsulates a method and an object instance with 3 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
inline QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3) volatile)
{
    return QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>(obj, func);
}

/** Creates a functor of type QExtBoundVolatileMemberFunctor which encapsulates a method and an object instance with 2 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2) volatile)
{
    return QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>(obj, func);
}

/** Creates a functor of type QExtBoundVolatileMemberFunctor which encapsulates a method and an object instance with 2 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2) volatile)
{
    return QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>(obj, func);
}

/** Creates a functor of type QExtBoundVolatileMemberFunctor which encapsulates a method and an object instance with 1 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1>
inline QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1>
qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1) volatile)
{
    return QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1>(obj, func);
}

/** Creates a functor of type QExtBoundVolatileMemberFunctor which encapsulates a method and an object instance with 1 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1>
inline QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1>
qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1) volatile)
{
    return QExtBoundVolatileMemberFunctor<T_return, T_obj, T_arg1>(obj, func);
}

/** Creates a functor of type QExtBoundVolatileMemberFunctor which encapsulates a method and an object instance with no args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj>
inline QExtBoundVolatileMemberFunctor<T_return, T_obj> qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)() volatile)
{
    return QExtBoundVolatileMemberFunctor<T_return, T_obj>(obj, func);
}

/** Creates a functor of type QExtBoundVolatileMemberFunctor which encapsulates a method and an object instance with no args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj>
inline QExtBoundVolatileMemberFunctor<T_return, T_obj> qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)() volatile)
{
    return QExtBoundVolatileMemberFunctor<T_return, T_obj>(obj, func);
}

/** Creates a functor of type QExtBoundConstVolatileMemberFunctor which encapsulates a method and an object instance with 7 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<
        typename T_return,
        typename T_obj,
        typename T_arg1,
        typename T_arg2,
        typename T_arg3,
        typename T_arg4,
        typename T_arg5,
        typename T_arg6,
        typename T_arg7>
inline QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor(T_obj *obj,
                  T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const volatile)
{
    return QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(
            obj, func);
}

/** Creates a functor of type QExtBoundConstVolatileMemberFunctor which encapsulates a method and an object instance with 7 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<
        typename T_return,
        typename T_obj,
        typename T_arg1,
        typename T_arg2,
        typename T_arg3,
        typename T_arg4,
        typename T_arg5,
        typename T_arg6,
        typename T_arg7>
inline QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor(T_obj &obj,
                  T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const volatile)
{
    return QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(
            obj, func);
}

/** Creates a functor of type QExtBoundConstVolatileMemberFunctor which encapsulates a method and an object instance with 6 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
inline QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const volatile)
{
    return QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(obj,
                                                                                                                func);
}

/** Creates a functor of type QExtBoundConstVolatileMemberFunctor which encapsulates a method and an object instance with 6 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
inline QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const volatile)
{
    return QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(obj,
                                                                                                                func);
}

/** Creates a functor of type QExtBoundConstVolatileMemberFunctor which encapsulates a method and an object instance with 5 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const volatile)
{
    return QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(obj, func);
}

/** Creates a functor of type QExtBoundConstVolatileMemberFunctor which encapsulates a method and an object instance with 5 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const volatile)
{
    return QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(obj, func);
}

/** Creates a functor of type QExtBoundConstVolatileMemberFunctor which encapsulates a method and an object instance with 4 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4) const volatile)
{
    return QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(obj, func);
}

/** Creates a functor of type QExtBoundConstVolatileMemberFunctor which encapsulates a method and an object instance with 4 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4) const volatile)
{
    return QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(obj, func);
}

/** Creates a functor of type QExtBoundConstVolatileMemberFunctor which encapsulates a method and an object instance with 3 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
inline QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3) const volatile)
{
    return QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>(obj, func);
}

/** Creates a functor of type QExtBoundConstVolatileMemberFunctor which encapsulates a method and an object instance with 3 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
inline QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3) const volatile)
{
    return QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>(obj, func);
}

/** Creates a functor of type QExtBoundConstVolatileMemberFunctor which encapsulates a method and an object instance with 2 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2) const volatile)
{
    return QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>(obj, func);
}

/** Creates a functor of type QExtBoundConstVolatileMemberFunctor which encapsulates a method and an object instance with 2 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2) const volatile)
{
    return QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>(obj, func);
}

/** Creates a functor of type QExtBoundConstVolatileMemberFunctor which encapsulates a method and an object instance with 1 args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1>
inline QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1>
qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)(T_arg1) const volatile)
{
    return QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1>(obj, func);
}

/** Creates a functor of type QExtBoundConstVolatileMemberFunctor which encapsulates a method and an object instance with 1 args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj, typename T_arg1>
inline QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1>
qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)(T_arg1) const volatile)
{
    return QExtBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1>(obj, func);
}

/** Creates a functor of type QExtBoundConstVolatileMemberFunctor which encapsulates a method and an object instance with no args.
 * \param obj Pointer to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj>
inline QExtBoundConstVolatileMemberFunctor<T_return, T_obj>
qextMemberFunctor(T_obj *obj, T_return (T_obj::*func)() const volatile)
{
    return QExtBoundConstVolatileMemberFunctor<T_return, T_obj>(obj, func);
}

/** Creates a functor of type QExtBoundConstVolatileMemberFunctor which encapsulates a method and an object instance with no args.
 * \param obj Reference to object instance the functor should operate on.
 * \param func Pointer to method that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextMemberFunctor
 */
template<typename T_return, typename T_obj>
inline QExtBoundConstVolatileMemberFunctor<T_return, T_obj>
qextMemberFunctor(T_obj &obj, T_return (T_obj::*func)() const volatile)
{
    return QExtBoundConstVolatileMemberFunctor<T_return, T_obj>(obj, func);
}


#endif // _QEXTMEMBERFUNCTOR_H
