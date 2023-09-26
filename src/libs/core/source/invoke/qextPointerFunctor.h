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

#ifndef _QEXTFUNCTORPOINTER_H
#define _QEXTFUNCTORPOINTER_H

#include <qextFunctorTrait.h>
#include <qextGlobal.h>



namespace qextPrivate
{

    /** @defgroup qextPointerFunctor qextPointerFunctor()
 * qextPointerFunctor() is used to convert a pointer to a function to a functor.
 * If the function pointer is to an overloaded type, you must specify
 * the types using template arguments starting with the first argument.
 * It is not necessary to supply the return type.
 *
 * @par Example:
 * @code
 * void foo(int) {}
 * QEXTFunction<void, int> slot = qextPointerFunctor(&foo);
 * @endcode
 *
 * Use qextPointerFunctor#() if there is an ambiguity as to the number of arguments.
 *
 * @par Example:
 * @code
 * void foo(int) {}  // choose this one
 * void foo(float) {}
 * void foo(int, int) {}
 * QEXTFunction<void, long> slot = qextPointerFunctor<int>(&foo);
 * @endcode
 *
 * qextPointerFunctor() can also be used to convert a pointer to a static member
 * function to a functor, like so:
 *
 * @par Example:
 * @code
 * struct foo
 * {
 *   static void bar(int) {}
 * };
 * QEXTlot<void, int> slot = qextPointerFunctor(&foo::bar);
 * @endcode
 *
 * \ingroup qextfunctors
 */

    /** QEXTPointerFunctor7 wraps existing non-member functions with 7 argument(s).
 * Use the convenience function qextPointerFunctor() to create an instance of QEXTPointerFunctor7.
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
 *
 * \ingroup qextPointerFunctor
 */
    template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7 >
    class QEXTPointerFunctor7 : public QEXTFunctorBase
    {
    public:
        typedef T_return (*Function)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7);
        typedef T_return Return;

        // Constructs an invalid functor.
        QEXTPointerFunctor7() : m_funcPtr(QEXT_DECL_NULLPTR) {}
        /** Constructs a QEXTPointerFunctor7 object that wraps an existing function.
     * \param func Pointer to function that will be invoked from operator()().
     */
        QEXTPointerFunctor7(Function func) : m_funcPtr(func) {}
        QEXTPointerFunctor7(const QEXTPointerFunctor7 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped function.
     * \param arg1 Argument to be passed on to the function.
     * \param arg2 Argument to be passed on to the function.
     * \param arg3 Argument to be passed on to the function.
     * \param arg4 Argument to be passed on to the function.
     * \param arg5 Argument to be passed on to the function.
     * \param arg6 Argument to be passed on to the function.
     * \param arg7 Argument to be passed on to the function.
     * \return The return value of the function invocation.
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
            return m_funcPtr(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        }

    protected:
        Function m_funcPtr;
    };

    /** QEXTPointerFunctor6 wraps existing non-member functions with 6 argument(s).
 * Use the convenience function qextPointerFunctor() to create an instance of QEXTPointerFunctor6.
 *
 * The following template arguments are used:
 * - @e T_arg1 Argument type used in the definition of operator()().
 * - @e T_arg2 Argument type used in the definition of operator()().
 * - @e T_arg3 Argument type used in the definition of operator()().
 * - @e T_arg4 Argument type used in the definition of operator()().
 * - @e T_arg5 Argument type used in the definition of operator()().
 * - @e T_arg6 Argument type used in the definition of operator()().
 * - @e T_return The return type of operator()().
 *
 * \ingroup qextPointerFunctor
 */
    template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
    class QEXTPointerFunctor6 : public QEXTFunctorBase
    {
    public:
        typedef T_return (*Function)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6);
        typedef T_return Return;

        // Constructs an invalid functor.
        QEXTPointerFunctor6() : m_funcPtr(QEXT_DECL_NULLPTR) {}
        /** Constructs a QEXTPointerFunctor6 object that wraps an existing function.
     * \param func Pointer to function that will be invoked from operator()().
     */
        QEXTPointerFunctor6(Function func) : m_funcPtr(func) {}
        QEXTPointerFunctor6(const QEXTPointerFunctor6 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped function.
     * \param arg1 Argument to be passed on to the function.
     * \param arg2 Argument to be passed on to the function.
     * \param arg3 Argument to be passed on to the function.
     * \param arg4 Argument to be passed on to the function.
     * \param arg5 Argument to be passed on to the function.
     * \param arg6 Argument to be passed on to the function.
     * \return The return value of the function invocation.
     */
        T_return operator()(
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4,
            typename QEXTTypeTrait< T_arg5 >::Take arg5,
            typename QEXTTypeTrait< T_arg6 >::Take arg6) const
        {
            return m_funcPtr(arg1, arg2, arg3, arg4, arg5, arg6);
        }

    protected:
        Function m_funcPtr;
    };

    /** QEXTPointerFunctor5 wraps existing non-member functions with 5 argument(s).
 * Use the convenience function qextPointerFunctor() to create an instance of QEXTPointerFunctor5.
 *
 * The following template arguments are used:
 * - @e T_arg1 Argument type used in the definition of operator()().
 * - @e T_arg2 Argument type used in the definition of operator()().
 * - @e T_arg3 Argument type used in the definition of operator()().
 * - @e T_arg4 Argument type used in the definition of operator()().
 * - @e T_arg5 Argument type used in the definition of operator()().
 * - @e T_return The return type of operator()().
 *
 * \ingroup qextPointerFunctor
 */
    template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
    class QEXTPointerFunctor5 : public QEXTFunctorBase
    {
    public:
        typedef T_return (*Function)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5);
        typedef T_return Return;

        // Constructs an invalid functor.
        QEXTPointerFunctor5() : m_funcPtr(QEXT_DECL_NULLPTR) {}
        /** Constructs a QEXTPointerFunctor5 object that wraps an existing function.
     * \param func Pointer to function that will be invoked from operator()().
     */
        QEXTPointerFunctor5(Function func) : m_funcPtr(func) {}
        QEXTPointerFunctor5(const QEXTPointerFunctor5 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped function.
     * \param arg1 Argument to be passed on to the function.
     * \param arg2 Argument to be passed on to the function.
     * \param arg3 Argument to be passed on to the function.
     * \param arg4 Argument to be passed on to the function.
     * \param arg5 Argument to be passed on to the function.
     * \return The return value of the function invocation.
     */
        T_return operator()(
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4,
            typename QEXTTypeTrait< T_arg5 >::Take arg5) const
        {
            return m_funcPtr(arg1, arg2, arg3, arg4, arg5);
        }

    protected:
        Function m_funcPtr;
    };

    /** QEXTPointerFunctor4 wraps existing non-member functions with 4 argument(s).
 * Use the convenience function qextPointerFunctor() to create an instance of QEXTPointerFunctor4.
 *
 * The following template arguments are used:
 * - @e T_arg1 Argument type used in the definition of operator()().
 * - @e T_arg2 Argument type used in the definition of operator()().
 * - @e T_arg3 Argument type used in the definition of operator()().
 * - @e T_arg4 Argument type used in the definition of operator()().
 * - @e T_return The return type of operator()().
 *
 * \ingroup qextPointerFunctor
 */
    template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
    class QEXTPointerFunctor4 : public QEXTFunctorBase
    {
    public:
        typedef T_return (*Function)(T_arg1, T_arg2, T_arg3, T_arg4);
        typedef T_return Return;

        // Constructs an invalid functor.
        QEXTPointerFunctor4() : m_funcPtr(QEXT_DECL_NULLPTR) {}
        /** Constructs a QEXTPointerFunctor4 object that wraps an existing function.
     * \param func Pointer to function that will be invoked from operator()().
     */
        QEXTPointerFunctor4(Function func) : m_funcPtr(func) {}
        QEXTPointerFunctor4(const QEXTPointerFunctor4 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped function.
     * \param arg1 Argument to be passed on to the function.
     * \param arg2 Argument to be passed on to the function.
     * \param arg3 Argument to be passed on to the function.
     * \param arg4 Argument to be passed on to the function.
     * \return The return value of the function invocation.
     */
        T_return operator()(
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4) const
        {
            return m_funcPtr(arg1, arg2, arg3, arg4);
        }

    protected:
        Function m_funcPtr;
    };

    /** QEXTPointerFunctor3 wraps existing non-member functions with 3 argument(s).
 * Use the convenience function qextPointerFunctor() to create an instance of QEXTPointerFunctor3.
 *
 * The following template arguments are used:
 * - @e T_arg1 Argument type used in the definition of operator()().
 * - @e T_arg2 Argument type used in the definition of operator()().
 * - @e T_arg3 Argument type used in the definition of operator()().
 * - @e T_return The return type of operator()().
 *
 * \ingroup qextPointerFunctor
 */
    template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3 >
    class QEXTPointerFunctor3 : public QEXTFunctorBase
    {
    public:
        typedef T_return (*Function)(T_arg1, T_arg2, T_arg3);
        typedef T_return Return;

        // Constructs an invalid functor.
        QEXTPointerFunctor3() : m_funcPtr(QEXT_DECL_NULLPTR) {}
        /** Constructs a QEXTPointerFunctor3 object that wraps an existing function.
     * \param func Pointer to function that will be invoked from operator()().
     */
        QEXTPointerFunctor3(Function func) : m_funcPtr(func) {}
        QEXTPointerFunctor3(const QEXTPointerFunctor3 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped function.
     * \param arg1 Argument to be passed on to the function.
     * \param arg2 Argument to be passed on to the function.
     * \param arg3 Argument to be passed on to the function.
     * \return The return value of the function invocation.
     */
        T_return
        operator()(typename QEXTTypeTrait< T_arg1 >::Take arg1, typename QEXTTypeTrait< T_arg2 >::Take arg2, typename QEXTTypeTrait< T_arg3 >::Take arg3) const
        {
            return m_funcPtr(arg1, arg2, arg3);
        }

    protected:
        Function m_funcPtr;
    };

    /** QEXTPointerFunctor2 wraps existing non-member functions with 2 argument(s).
 * Use the convenience function qextPointerFunctor() to create an instance of QEXTPointerFunctor2.
 *
 * The following template arguments are used:
 * - @e T_arg1 Argument type used in the definition of operator()().
 * - @e T_arg2 Argument type used in the definition of operator()().
 * - @e T_return The return type of operator()().
 *
 * \ingroup qextPointerFunctor
 */
    template < typename T_return, typename T_arg1, typename T_arg2 >
    class QEXTPointerFunctor2 : public QEXTFunctorBase
    {
    public:
        typedef T_return (*Function)(T_arg1, T_arg2);
        typedef T_return Return;

        // Constructs an invalid functor.
        QEXTPointerFunctor2() : m_funcPtr(QEXT_DECL_NULLPTR) {}
        /** Constructs a QEXTPointerFunctor2 object that wraps an existing function.
     * \param func Pointer to function that will be invoked from operator()().
     */
        QEXTPointerFunctor2(Function func) : m_funcPtr(func) {}
        QEXTPointerFunctor2(const QEXTPointerFunctor2 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped function.
     * \param arg1 Argument to be passed on to the function.
     * \param arg2 Argument to be passed on to the function.
     * \return The return value of the function invocation.
     */
        T_return operator()(typename QEXTTypeTrait< T_arg1 >::Take arg1, typename QEXTTypeTrait< T_arg2 >::Take arg2) const
        {
            return m_funcPtr(arg1, arg2);
        }

    protected:
        Function m_funcPtr;
    };

    /** QEXTPointerFunctor1 wraps existing non-member functions with 1 argument(s).
 * Use the convenience function qextPointerFunctor() to create an instance of QEXTPointerFunctor1.
 *
 * The following template arguments are used:
 * - @e T_arg1 Argument type used in the definition of operator()().
 * - @e T_return The return type of operator()().
 *
 * \ingroup qextPointerFunctor
 */
    template < typename T_return, typename T_arg1 >
    class QEXTPointerFunctor1 : public QEXTFunctorBase
    {
    public:
        typedef T_return (*Function)(T_arg1);
        typedef T_return Return;

        // Constructs an invalid functor.
        QEXTPointerFunctor1() : m_funcPtr(QEXT_DECL_NULLPTR) {}
        /** Constructs a QEXTPointerFunctor1 object that wraps an existing function.
     * \param func Pointer to function that will be invoked from operator()().
     */
        QEXTPointerFunctor1(Function func) : m_funcPtr(func) {}
        QEXTPointerFunctor1(const QEXTPointerFunctor1 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped function.
     * \param arg1 Argument to be passed on to the function.
     * \return The return value of the function invocation.
     */
        T_return operator()(typename QEXTTypeTrait< T_arg1 >::Take arg1) const
        {
            return m_funcPtr(arg1);
        }

    protected:
        Function m_funcPtr;
    };

    /** QEXTPointerFunctor0 wraps existing non-member functions with 0 argument(s).
 * Use the convenience function qextPointerFunctor() to create an instance of QEXTPointerFunctor0.
 *
 * The following template arguments are used:
 * - @e T_return The return type of operator()().
 *
 * \ingroup qextPointerFunctor
 */
    template < typename T_return >
    class QEXTPointerFunctor0 : public QEXTFunctorBase
    {
    public:
        typedef T_return (*Function)();
        typedef T_return Return;

        QEXTPointerFunctor0() : m_funcPtr(QEXT_DECL_NULLPTR) {}
        /** Constructs a QEXTPointerFunctor0 object that wraps an existing function.
     * \param func Pointer to function that will be invoked from operator()().
     */
        QEXTPointerFunctor0(Function func) : m_funcPtr(func) {}
        QEXTPointerFunctor0(const QEXTPointerFunctor0 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped function.
     * \return The return value of the function invocation.
     */
        T_return operator()() const
        {
            return m_funcPtr();
        }

    protected:
        Function m_funcPtr;
    };

} // namespace qextPrivate

/** Convenience wrapper for the numbered QEXTPointerFunctor# templates.
 * QEXTPointerFunctor itself is a functor or to be more precise a closure. It contains
 * a single, arbitrary functor (or closure) that is executed in operator()().
 *
 * The template arguments determine the function signature of operator()():
 * - @e T_return The return type of operator()().
 * - @e T_arg1 Argument type used in the definition of operator()(). The default @p QEXTNil means no argument.
 * - @e T_arg2 Argument type used in the definition of operator()(). The default @p QEXTNil means no argument.
 * - @e T_arg3 Argument type used in the definition of operator()(). The default @p QEXTNil means no argument.
 * - @e T_arg4 Argument type used in the definition of operator()(). The default @p QEXTNil means no argument.
 * - @e T_arg5 Argument type used in the definition of operator()(). The default @p QEXTNil means no argument.
 * - @e T_arg6 Argument type used in the definition of operator()(). The default @p QEXTNil means no argument.
 * - @e T_arg7 Argument type used in the definition of operator()(). The default @p QEXTNil means no argument.
 *
 * \ingroup qextPointerFunctor
 */
template <
    typename T_return,
    typename T_arg1 = QEXTNil,
    typename T_arg2 = QEXTNil,
    typename T_arg3 = QEXTNil,
    typename T_arg4 = QEXTNil,
    typename T_arg5 = QEXTNil,
    typename T_arg6 = QEXTNil,
    typename T_arg7 = QEXTNil >
class QEXTPointerFunctor : public qextPrivate::QEXTPointerFunctor7< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
{
public:
    typedef qextPrivate::QEXTPointerFunctor7< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 > Base;
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTPointerFunctor() {}
    QEXTPointerFunctor(Function func) : Base(func) {}
    QEXTPointerFunctor(const QEXTPointerFunctor &other) : Base(other.m_funcPtr) {}

    /** Invoke the contained functor.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \param arg3 Argument to be passed on to the functor.
     * \param arg4 Argument to be passed on to the functor.
     * \param arg5 Argument to be passed on to the functor.
     * \param arg6 Argument to be passed on to the functor.
     * \param arg7 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
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
        return Base::operator()(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

/** Convenience wrapper for the numbered QEXTPointerFunctor# templates.
 * See the base class for useful methods.
 * This is the template specialization of the unnumbered QEXTPointerFunctor
 * template for 6 argument(s), specialized for different numbers of arguments
 * This is possible because the template has default (QEXTNil) template types.
 */
template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
class QEXTPointerFunctor< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QEXTNil >
    : public qextPrivate::QEXTPointerFunctor6< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
{
public:
    typedef qextPrivate::QEXTPointerFunctor6< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 > Base;
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTPointerFunctor() {}
    QEXTPointerFunctor(Function func) : Base(func) {}
    QEXTPointerFunctor(const QEXTPointerFunctor &other) : Base(other.m_funcPtr) {}

    /** Invoke the contained functor unless slot is in blocking state.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \param arg3 Argument to be passed on to the functor.
     * \param arg4 Argument to be passed on to the functor.
     * \param arg5 Argument to be passed on to the functor.
     * \param arg6 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
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

/** Convenience wrapper for the numbered QEXTPointerFunctor# templates.
 * See the base class for useful methods.
 * This is the template specialization of the unnumbered QEXTPointerFunctor
 * template for 5 argument(s), specialized for different numbers of arguments
 * This is possible because the template has default (QEXTNil) template types.
 */
template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
class QEXTPointerFunctor< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QEXTNil, QEXTNil >
    : public qextPrivate::QEXTPointerFunctor5< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
{
public:
    typedef qextPrivate::QEXTPointerFunctor5< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 > Base;
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTPointerFunctor() {}
    QEXTPointerFunctor(Function func) : Base(func) {}
    QEXTPointerFunctor(const QEXTPointerFunctor &other) : Base(other.m_funcPtr) {}

    /** Invoke the contained functor unless slot is in blocking state.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \param arg3 Argument to be passed on to the functor.
     * \param arg4 Argument to be passed on to the functor.
     * \param arg5 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
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

/** Convenience wrapper for the numbered QEXTPointerFunctor# templates.
 * See the base class for useful methods.
 * This is the template specialization of the unnumbered QEXTPointerFunctor
 * template for 4 argument(s), specialized for different numbers of arguments
 * This is possible because the template has default (QEXTNil) template types.
 */
template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
class QEXTPointerFunctor< T_return, T_arg1, T_arg2, T_arg3, T_arg4, QEXTNil, QEXTNil, QEXTNil >
    : public qextPrivate::QEXTPointerFunctor4< T_return, T_arg1, T_arg2, T_arg3, T_arg4 >
{
public:
    typedef qextPrivate::QEXTPointerFunctor4< T_return, T_arg1, T_arg2, T_arg3, T_arg4 > Base;
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTPointerFunctor() {}
    QEXTPointerFunctor(Function func) : Base(func) {}
    QEXTPointerFunctor(const QEXTPointerFunctor &other) : Base(other.m_funcPtr) {}

    /** Invoke the contained functor unless slot is in blocking state.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \param arg3 Argument to be passed on to the functor.
     * \param arg4 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    T_return operator()(
        typename QEXTTypeTrait< T_arg1 >::Take arg1,
        typename QEXTTypeTrait< T_arg2 >::Take arg2,
        typename QEXTTypeTrait< T_arg3 >::Take arg3,
        typename QEXTTypeTrait< T_arg4 >::Take arg4) const
    {
        return Base::operator()(arg1, arg2, arg3, arg4);
    }
};

/** Convenience wrapper for the numbered QEXTPointerFunctor# templates.
 * See the base class for useful methods.
 * This is the template specialization of the unnumbered QEXTPointerFunctor
 * template for 3 argument(s), specialized for different numbers of arguments
 * This is possible because the template has default (QEXTNil) template types.
 */
template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3 >
class QEXTPointerFunctor< T_return, T_arg1, T_arg2, T_arg3, QEXTNil, QEXTNil, QEXTNil, QEXTNil > : public qextPrivate::QEXTPointerFunctor3< T_return, T_arg1, T_arg2, T_arg3 >
{
public:
    typedef qextPrivate::QEXTPointerFunctor3< T_return, T_arg1, T_arg2, T_arg3 > Base;
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTPointerFunctor() {}
    QEXTPointerFunctor(Function func) : Base(func) {}
    QEXTPointerFunctor(const QEXTPointerFunctor &other) : Base(other.m_funcPtr) {}

    /** Invoke the contained functor unless slot is in blocking state.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \param arg3 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    T_return operator()(typename QEXTTypeTrait< T_arg1 >::Take arg1, typename QEXTTypeTrait< T_arg2 >::Take arg2, typename QEXTTypeTrait< T_arg3 >::Take arg3) const
    {
        return Base::operator()(arg1, arg2, arg3);
    }
};

/** Convenience wrapper for the numbered QEXTPointerFunctor# templates.
 * See the base class for useful methods.
 * This is the template specialization of the unnumbered QEXTPointerFunctor
 * template for 2 argument(s), specialized for different numbers of arguments
 * This is possible because the template has default (QEXTNil) template types.
 */
template < typename T_return, typename T_arg1, typename T_arg2 >
class QEXTPointerFunctor< T_return, T_arg1, T_arg2, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil > : public qextPrivate::QEXTPointerFunctor2< T_return, T_arg1, T_arg2 >
{
public:
    typedef qextPrivate::QEXTPointerFunctor2< T_return, T_arg1, T_arg2 > Base;
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTPointerFunctor() {}
    QEXTPointerFunctor(Function func) : Base(func) {}
    QEXTPointerFunctor(const QEXTPointerFunctor &other) : Base(other.m_funcPtr) {}

    /** Invoke the contained functor unless slot is in blocking state.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    T_return operator()(typename QEXTTypeTrait< T_arg1 >::Take arg1, typename QEXTTypeTrait< T_arg2 >::Take arg2) const
    {
        return Base::operator()(arg1, arg2);
    }
};

/** Convenience wrapper for the numbered QEXTPointerFunctor# templates.
 * See the base class for useful methods.
 * This is the template specialization of the unnumbered QEXTPointerFunctor
 * template for 1 argument(s), specialized for different numbers of arguments
 * This is possible because the template has default (QEXTNil) template types.
 */
template < typename T_return, typename T_arg1 >
class QEXTPointerFunctor< T_return, T_arg1, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil > : public qextPrivate::QEXTPointerFunctor1< T_return, T_arg1 >
{
public:
    typedef qextPrivate::QEXTPointerFunctor1< T_return, T_arg1 > Base;
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTPointerFunctor() {}
    QEXTPointerFunctor(Function func) : Base(func) {}
    QEXTPointerFunctor(const QEXTPointerFunctor &other) : Base(other.m_funcPtr) {}

    /** Invoke the contained functor unless slot is in blocking state.
     * \param arg1 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    T_return operator()(typename QEXTTypeTrait< T_arg1 >::Take arg1) const
    {
        return Base::operator()(arg1);
    }
};

/** Convenience wrapper for the numbered QEXTPointerFunctor# templates.
 * See the base class for useful methods.
 * This is the template specialization of the unnumbered QEXTPointerFunctor
 * template for 0 argument(s), specialized for different numbers of arguments
 * This is possible because the template has default (QEXTNil) template types.
 */
template < typename T_return >
class QEXTPointerFunctor< T_return, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil > : public qextPrivate::QEXTPointerFunctor0< T_return >
{
public:
    typedef qextPrivate::QEXTPointerFunctor0< T_return > Base;
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QEXTPointerFunctor() {}
    QEXTPointerFunctor(Function func) : Base(func) {}
    QEXTPointerFunctor(const QEXTPointerFunctor &other) : Base(other.m_funcPtr) {}

    /** Invoke the contained functor unless slot is in blocking state.
     * \return The return value of the functor invocation.
     */
    T_return operator()() const
    {
        return Base::operator()();
    }
};

// unnumbered qextPointerFunctor
/** Creates a functor of type QEXTPointerFunctor7 which wraps an existing non-member function.
 * \param func Pointer to function that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextPointerFunctor
 */
template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7 >
inline QEXTPointerFunctor< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
    qextPointerFunctor(T_return (*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7))
{
    return QEXTPointerFunctor< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(func);
}

/** Creates a functor of type QEXTPointerFunctor6 which wraps an existing non-member function.
 * \param func Pointer to function that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextPointerFunctor
 */
template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
inline QEXTPointerFunctor< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
    qextPointerFunctor(T_return (*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6))
{
    return QEXTPointerFunctor< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(func);
}

/** Creates a functor of type QEXTPointerFunctor5 which wraps an existing non-member function.
 * \param func Pointer to function that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextPointerFunctor
 */
template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
inline QEXTPointerFunctor< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 > qextPointerFunctor(T_return (*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5))
{
    return QEXTPointerFunctor< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(func);
}

/** Creates a functor of type QEXTPointerFunctor4 which wraps an existing non-member function.
 * \param func Pointer to function that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextPointerFunctor
 */
template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
inline QEXTPointerFunctor< T_return, T_arg1, T_arg2, T_arg3, T_arg4 > qextPointerFunctor(T_return (*func)(T_arg1, T_arg2, T_arg3, T_arg4))
{
    return QEXTPointerFunctor< T_return, T_arg1, T_arg2, T_arg3, T_arg4 >(func);
}

/** Creates a functor of type QEXTPointerFunctor3 which wraps an existing non-member function.
 * \param func Pointer to function that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextPointerFunctor
 */
template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3 >
inline QEXTPointerFunctor< T_return, T_arg1, T_arg2, T_arg3 > qextPointerFunctor(T_return (*func)(T_arg1, T_arg2, T_arg3))
{
    return QEXTPointerFunctor< T_return, T_arg1, T_arg2, T_arg3 >(func);
}

/** Creates a functor of type QEXTPointerFunctor2 which wraps an existing non-member function.
 * \param func Pointer to function that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextPointerFunctor
 */
template < typename T_return, typename T_arg1, typename T_arg2 >
inline QEXTPointerFunctor< T_return, T_arg1, T_arg2 > qextPointerFunctor(T_return (*func)(T_arg1, T_arg2))
{
    return QEXTPointerFunctor< T_return, T_arg1, T_arg2 >(func);
}

/** Creates a functor of type QEXTPointerFunctor1 which wraps an existing non-member function.
 * \param func Pointer to function that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextPointerFunctor
 */
template < typename T_return, typename T_arg1 >
inline QEXTPointerFunctor< T_return, T_arg1 > qextPointerFunctor(T_return (*func)(T_arg1))
{
    return QEXTPointerFunctor< T_return, T_arg1 >(func);
}

/** Creates a functor of type QEXTPointerFunctor0 which wraps an existing non-member function.
 * \param func Pointer to function that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextPointerFunctor
 */
template < typename T_return >
inline QEXTPointerFunctor< T_return > qextPointerFunctor(T_return (*func)())
{
    return QEXTPointerFunctor< T_return >(func);
}



#endif // _QEXTFUNCTORPOINTER_H
