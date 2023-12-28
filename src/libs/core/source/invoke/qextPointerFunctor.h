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

#ifndef _QEXTFUNCTORPOINTER_H
#define _QEXTFUNCTORPOINTER_H

#include <qextFunctorTrait.h>
#include <qextGlobal.h>



namespace QExtPrivate
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
 * QExtFunction<void, int> slot = qextPointerFunctor(&foo);
 * @endcode
 *
 * Use qextPointerFunctor#() if there is an ambiguity as to the number of arguments.
 *
 * @par Example:
 * @code
 * void foo(int) {}  // choose this one
 * void foo(float) {}
 * void foo(int, int) {}
 * QExtFunction<void, long> slot = qextPointerFunctor<int>(&foo);
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

    /** QExtPointerFunctor7 wraps existing non-member functions with 7 argument(s).
 * Use the convenience function qextPointerFunctor() to create an instance of QExtPointerFunctor7.
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
    class QExtPointerFunctor7 : public QExtFunctorBase
    {
    public:
        typedef T_return (*Function)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7);
        typedef T_return Return;

        // Constructs an invalid functor.
        QExtPointerFunctor7() : m_funcPtr(QEXT_NULLPTR) {}
        /** Constructs a QExtPointerFunctor7 object that wraps an existing function.
     * \param func Pointer to function that will be invoked from operator()().
     */
        QExtPointerFunctor7(Function func) : m_funcPtr(func) {}
        QExtPointerFunctor7(const QExtPointerFunctor7 &other) : m_funcPtr(other.m_funcPtr) {}

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
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4,
            typename QExtTypeTrait< T_arg5 >::Take arg5,
            typename QExtTypeTrait< T_arg6 >::Take arg6,
            typename QExtTypeTrait< T_arg7 >::Take arg7) const
        {
            return m_funcPtr(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        }

    protected:
        Function m_funcPtr;
    };

    /** QExtPointerFunctor6 wraps existing non-member functions with 6 argument(s).
 * Use the convenience function qextPointerFunctor() to create an instance of QExtPointerFunctor6.
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
    class QExtPointerFunctor6 : public QExtFunctorBase
    {
    public:
        typedef T_return (*Function)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6);
        typedef T_return Return;

        // Constructs an invalid functor.
        QExtPointerFunctor6() : m_funcPtr(QEXT_NULLPTR) {}
        /** Constructs a QExtPointerFunctor6 object that wraps an existing function.
     * \param func Pointer to function that will be invoked from operator()().
     */
        QExtPointerFunctor6(Function func) : m_funcPtr(func) {}
        QExtPointerFunctor6(const QExtPointerFunctor6 &other) : m_funcPtr(other.m_funcPtr) {}

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
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4,
            typename QExtTypeTrait< T_arg5 >::Take arg5,
            typename QExtTypeTrait< T_arg6 >::Take arg6) const
        {
            return m_funcPtr(arg1, arg2, arg3, arg4, arg5, arg6);
        }

    protected:
        Function m_funcPtr;
    };

    /** QExtPointerFunctor5 wraps existing non-member functions with 5 argument(s).
 * Use the convenience function qextPointerFunctor() to create an instance of QExtPointerFunctor5.
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
    class QExtPointerFunctor5 : public QExtFunctorBase
    {
    public:
        typedef T_return (*Function)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5);
        typedef T_return Return;

        // Constructs an invalid functor.
        QExtPointerFunctor5() : m_funcPtr(QEXT_NULLPTR) {}
        /** Constructs a QExtPointerFunctor5 object that wraps an existing function.
     * \param func Pointer to function that will be invoked from operator()().
     */
        QExtPointerFunctor5(Function func) : m_funcPtr(func) {}
        QExtPointerFunctor5(const QExtPointerFunctor5 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped function.
     * \param arg1 Argument to be passed on to the function.
     * \param arg2 Argument to be passed on to the function.
     * \param arg3 Argument to be passed on to the function.
     * \param arg4 Argument to be passed on to the function.
     * \param arg5 Argument to be passed on to the function.
     * \return The return value of the function invocation.
     */
        T_return operator()(
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4,
            typename QExtTypeTrait< T_arg5 >::Take arg5) const
        {
            return m_funcPtr(arg1, arg2, arg3, arg4, arg5);
        }

    protected:
        Function m_funcPtr;
    };

    /** QExtPointerFunctor4 wraps existing non-member functions with 4 argument(s).
 * Use the convenience function qextPointerFunctor() to create an instance of QExtPointerFunctor4.
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
    class QExtPointerFunctor4 : public QExtFunctorBase
    {
    public:
        typedef T_return (*Function)(T_arg1, T_arg2, T_arg3, T_arg4);
        typedef T_return Return;

        // Constructs an invalid functor.
        QExtPointerFunctor4() : m_funcPtr(QEXT_NULLPTR) {}
        /** Constructs a QExtPointerFunctor4 object that wraps an existing function.
     * \param func Pointer to function that will be invoked from operator()().
     */
        QExtPointerFunctor4(Function func) : m_funcPtr(func) {}
        QExtPointerFunctor4(const QExtPointerFunctor4 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped function.
     * \param arg1 Argument to be passed on to the function.
     * \param arg2 Argument to be passed on to the function.
     * \param arg3 Argument to be passed on to the function.
     * \param arg4 Argument to be passed on to the function.
     * \return The return value of the function invocation.
     */
        T_return operator()(
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4) const
        {
            return m_funcPtr(arg1, arg2, arg3, arg4);
        }

    protected:
        Function m_funcPtr;
    };

    /** QExtPointerFunctor3 wraps existing non-member functions with 3 argument(s).
 * Use the convenience function qextPointerFunctor() to create an instance of QExtPointerFunctor3.
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
    class QExtPointerFunctor3 : public QExtFunctorBase
    {
    public:
        typedef T_return (*Function)(T_arg1, T_arg2, T_arg3);
        typedef T_return Return;

        // Constructs an invalid functor.
        QExtPointerFunctor3() : m_funcPtr(QEXT_NULLPTR) {}
        /** Constructs a QExtPointerFunctor3 object that wraps an existing function.
     * \param func Pointer to function that will be invoked from operator()().
     */
        QExtPointerFunctor3(Function func) : m_funcPtr(func) {}
        QExtPointerFunctor3(const QExtPointerFunctor3 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped function.
     * \param arg1 Argument to be passed on to the function.
     * \param arg2 Argument to be passed on to the function.
     * \param arg3 Argument to be passed on to the function.
     * \return The return value of the function invocation.
     */
        T_return
        operator()(typename QExtTypeTrait< T_arg1 >::Take arg1, typename QExtTypeTrait< T_arg2 >::Take arg2, typename QExtTypeTrait< T_arg3 >::Take arg3) const
        {
            return m_funcPtr(arg1, arg2, arg3);
        }

    protected:
        Function m_funcPtr;
    };

    /** QExtPointerFunctor2 wraps existing non-member functions with 2 argument(s).
 * Use the convenience function qextPointerFunctor() to create an instance of QExtPointerFunctor2.
 *
 * The following template arguments are used:
 * - @e T_arg1 Argument type used in the definition of operator()().
 * - @e T_arg2 Argument type used in the definition of operator()().
 * - @e T_return The return type of operator()().
 *
 * \ingroup qextPointerFunctor
 */
    template < typename T_return, typename T_arg1, typename T_arg2 >
    class QExtPointerFunctor2 : public QExtFunctorBase
    {
    public:
        typedef T_return (*Function)(T_arg1, T_arg2);
        typedef T_return Return;

        // Constructs an invalid functor.
        QExtPointerFunctor2() : m_funcPtr(QEXT_NULLPTR) {}
        /** Constructs a QExtPointerFunctor2 object that wraps an existing function.
     * \param func Pointer to function that will be invoked from operator()().
     */
        QExtPointerFunctor2(Function func) : m_funcPtr(func) {}
        QExtPointerFunctor2(const QExtPointerFunctor2 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped function.
     * \param arg1 Argument to be passed on to the function.
     * \param arg2 Argument to be passed on to the function.
     * \return The return value of the function invocation.
     */
        T_return operator()(typename QExtTypeTrait< T_arg1 >::Take arg1, typename QExtTypeTrait< T_arg2 >::Take arg2) const
        {
            return m_funcPtr(arg1, arg2);
        }

    protected:
        Function m_funcPtr;
    };

    /** QExtPointerFunctor1 wraps existing non-member functions with 1 argument(s).
 * Use the convenience function qextPointerFunctor() to create an instance of QExtPointerFunctor1.
 *
 * The following template arguments are used:
 * - @e T_arg1 Argument type used in the definition of operator()().
 * - @e T_return The return type of operator()().
 *
 * \ingroup qextPointerFunctor
 */
    template < typename T_return, typename T_arg1 >
    class QExtPointerFunctor1 : public QExtFunctorBase
    {
    public:
        typedef T_return (*Function)(T_arg1);
        typedef T_return Return;

        // Constructs an invalid functor.
        QExtPointerFunctor1() : m_funcPtr(QEXT_NULLPTR) {}
        /** Constructs a QExtPointerFunctor1 object that wraps an existing function.
     * \param func Pointer to function that will be invoked from operator()().
     */
        QExtPointerFunctor1(Function func) : m_funcPtr(func) {}
        QExtPointerFunctor1(const QExtPointerFunctor1 &other) : m_funcPtr(other.m_funcPtr) {}

        /** Execute the wrapped function.
     * \param arg1 Argument to be passed on to the function.
     * \return The return value of the function invocation.
     */
        T_return operator()(typename QExtTypeTrait< T_arg1 >::Take arg1) const
        {
            return m_funcPtr(arg1);
        }

    protected:
        Function m_funcPtr;
    };

    /** QExtPointerFunctor0 wraps existing non-member functions with 0 argument(s).
 * Use the convenience function qextPointerFunctor() to create an instance of QExtPointerFunctor0.
 *
 * The following template arguments are used:
 * - @e T_return The return type of operator()().
 *
 * \ingroup qextPointerFunctor
 */
    template < typename T_return >
    class QExtPointerFunctor0 : public QExtFunctorBase
    {
    public:
        typedef T_return (*Function)();
        typedef T_return Return;

        QExtPointerFunctor0() : m_funcPtr(QEXT_NULLPTR) {}
        /** Constructs a QExtPointerFunctor0 object that wraps an existing function.
     * \param func Pointer to function that will be invoked from operator()().
     */
        QExtPointerFunctor0(Function func) : m_funcPtr(func) {}
        QExtPointerFunctor0(const QExtPointerFunctor0 &other) : m_funcPtr(other.m_funcPtr) {}

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

} // namespace QExtPrivate

/** Convenience wrapper for the numbered QExtPointerFunctor# templates.
 * QExtPointerFunctor itself is a functor or to be more precise a closure. It contains
 * a single, arbitrary functor (or closure) that is executed in operator()().
 *
 * The template arguments determine the function signature of operator()():
 * - @e T_return The return type of operator()().
 * - @e T_arg1 Argument type used in the definition of operator()(). The default @p QExtNil means no argument.
 * - @e T_arg2 Argument type used in the definition of operator()(). The default @p QExtNil means no argument.
 * - @e T_arg3 Argument type used in the definition of operator()(). The default @p QExtNil means no argument.
 * - @e T_arg4 Argument type used in the definition of operator()(). The default @p QExtNil means no argument.
 * - @e T_arg5 Argument type used in the definition of operator()(). The default @p QExtNil means no argument.
 * - @e T_arg6 Argument type used in the definition of operator()(). The default @p QExtNil means no argument.
 * - @e T_arg7 Argument type used in the definition of operator()(). The default @p QExtNil means no argument.
 *
 * \ingroup qextPointerFunctor
 */
template <
    typename T_return,
    typename T_arg1 = QExtNil,
    typename T_arg2 = QExtNil,
    typename T_arg3 = QExtNil,
    typename T_arg4 = QExtNil,
    typename T_arg5 = QExtNil,
    typename T_arg6 = QExtNil,
    typename T_arg7 = QExtNil >
class QExtPointerFunctor : public QExtPrivate::QExtPointerFunctor7< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
{
public:
    typedef QExtPrivate::QExtPointerFunctor7< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 > Base;
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtPointerFunctor() {}
    QExtPointerFunctor(Function func) : Base(func) {}
    QExtPointerFunctor(const QExtPointerFunctor &other) : Base(other.m_funcPtr) {}

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
        typename QExtTypeTrait< T_arg1 >::Take arg1,
        typename QExtTypeTrait< T_arg2 >::Take arg2,
        typename QExtTypeTrait< T_arg3 >::Take arg3,
        typename QExtTypeTrait< T_arg4 >::Take arg4,
        typename QExtTypeTrait< T_arg5 >::Take arg5,
        typename QExtTypeTrait< T_arg6 >::Take arg6,
        typename QExtTypeTrait< T_arg7 >::Take arg7) const
    {
        return Base::operator()(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

/** Convenience wrapper for the numbered QExtPointerFunctor# templates.
 * See the base class for useful methods.
 * This is the template specialization of the unnumbered QExtPointerFunctor
 * template for 6 argument(s), specialized for different numbers of arguments
 * This is possible because the template has default (QExtNil) template types.
 */
template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
class QExtPointerFunctor< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QExtNil >
    : public QExtPrivate::QExtPointerFunctor6< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
{
public:
    typedef QExtPrivate::QExtPointerFunctor6< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 > Base;
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtPointerFunctor() {}
    QExtPointerFunctor(Function func) : Base(func) {}
    QExtPointerFunctor(const QExtPointerFunctor &other) : Base(other.m_funcPtr) {}

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
        typename QExtTypeTrait< T_arg1 >::Take arg1,
        typename QExtTypeTrait< T_arg2 >::Take arg2,
        typename QExtTypeTrait< T_arg3 >::Take arg3,
        typename QExtTypeTrait< T_arg4 >::Take arg4,
        typename QExtTypeTrait< T_arg5 >::Take arg5,
        typename QExtTypeTrait< T_arg6 >::Take arg6) const
    {
        return Base::operator()(arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

/** Convenience wrapper for the numbered QExtPointerFunctor# templates.
 * See the base class for useful methods.
 * This is the template specialization of the unnumbered QExtPointerFunctor
 * template for 5 argument(s), specialized for different numbers of arguments
 * This is possible because the template has default (QExtNil) template types.
 */
template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
class QExtPointerFunctor< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QExtNil, QExtNil >
    : public QExtPrivate::QExtPointerFunctor5< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
{
public:
    typedef QExtPrivate::QExtPointerFunctor5< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 > Base;
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtPointerFunctor() {}
    QExtPointerFunctor(Function func) : Base(func) {}
    QExtPointerFunctor(const QExtPointerFunctor &other) : Base(other.m_funcPtr) {}

    /** Invoke the contained functor unless slot is in blocking state.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \param arg3 Argument to be passed on to the functor.
     * \param arg4 Argument to be passed on to the functor.
     * \param arg5 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    T_return operator()(
        typename QExtTypeTrait< T_arg1 >::Take arg1,
        typename QExtTypeTrait< T_arg2 >::Take arg2,
        typename QExtTypeTrait< T_arg3 >::Take arg3,
        typename QExtTypeTrait< T_arg4 >::Take arg4,
        typename QExtTypeTrait< T_arg5 >::Take arg5) const
    {
        return Base::operator()(arg1, arg2, arg3, arg4, arg5);
    }
};

/** Convenience wrapper for the numbered QExtPointerFunctor# templates.
 * See the base class for useful methods.
 * This is the template specialization of the unnumbered QExtPointerFunctor
 * template for 4 argument(s), specialized for different numbers of arguments
 * This is possible because the template has default (QExtNil) template types.
 */
template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
class QExtPointerFunctor< T_return, T_arg1, T_arg2, T_arg3, T_arg4, QExtNil, QExtNil, QExtNil >
    : public QExtPrivate::QExtPointerFunctor4< T_return, T_arg1, T_arg2, T_arg3, T_arg4 >
{
public:
    typedef QExtPrivate::QExtPointerFunctor4< T_return, T_arg1, T_arg2, T_arg3, T_arg4 > Base;
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtPointerFunctor() {}
    QExtPointerFunctor(Function func) : Base(func) {}
    QExtPointerFunctor(const QExtPointerFunctor &other) : Base(other.m_funcPtr) {}

    /** Invoke the contained functor unless slot is in blocking state.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \param arg3 Argument to be passed on to the functor.
     * \param arg4 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    T_return operator()(
        typename QExtTypeTrait< T_arg1 >::Take arg1,
        typename QExtTypeTrait< T_arg2 >::Take arg2,
        typename QExtTypeTrait< T_arg3 >::Take arg3,
        typename QExtTypeTrait< T_arg4 >::Take arg4) const
    {
        return Base::operator()(arg1, arg2, arg3, arg4);
    }
};

/** Convenience wrapper for the numbered QExtPointerFunctor# templates.
 * See the base class for useful methods.
 * This is the template specialization of the unnumbered QExtPointerFunctor
 * template for 3 argument(s), specialized for different numbers of arguments
 * This is possible because the template has default (QExtNil) template types.
 */
template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3 >
class QExtPointerFunctor< T_return, T_arg1, T_arg2, T_arg3, QExtNil, QExtNil, QExtNil, QExtNil > : public QExtPrivate::QExtPointerFunctor3< T_return, T_arg1, T_arg2, T_arg3 >
{
public:
    typedef QExtPrivate::QExtPointerFunctor3< T_return, T_arg1, T_arg2, T_arg3 > Base;
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtPointerFunctor() {}
    QExtPointerFunctor(Function func) : Base(func) {}
    QExtPointerFunctor(const QExtPointerFunctor &other) : Base(other.m_funcPtr) {}

    /** Invoke the contained functor unless slot is in blocking state.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \param arg3 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    T_return operator()(typename QExtTypeTrait< T_arg1 >::Take arg1, typename QExtTypeTrait< T_arg2 >::Take arg2, typename QExtTypeTrait< T_arg3 >::Take arg3) const
    {
        return Base::operator()(arg1, arg2, arg3);
    }
};

/** Convenience wrapper for the numbered QExtPointerFunctor# templates.
 * See the base class for useful methods.
 * This is the template specialization of the unnumbered QExtPointerFunctor
 * template for 2 argument(s), specialized for different numbers of arguments
 * This is possible because the template has default (QExtNil) template types.
 */
template < typename T_return, typename T_arg1, typename T_arg2 >
class QExtPointerFunctor< T_return, T_arg1, T_arg2, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil > : public QExtPrivate::QExtPointerFunctor2< T_return, T_arg1, T_arg2 >
{
public:
    typedef QExtPrivate::QExtPointerFunctor2< T_return, T_arg1, T_arg2 > Base;
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtPointerFunctor() {}
    QExtPointerFunctor(Function func) : Base(func) {}
    QExtPointerFunctor(const QExtPointerFunctor &other) : Base(other.m_funcPtr) {}

    /** Invoke the contained functor unless slot is in blocking state.
     * \param arg1 Argument to be passed on to the functor.
     * \param arg2 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    T_return operator()(typename QExtTypeTrait< T_arg1 >::Take arg1, typename QExtTypeTrait< T_arg2 >::Take arg2) const
    {
        return Base::operator()(arg1, arg2);
    }
};

/** Convenience wrapper for the numbered QExtPointerFunctor# templates.
 * See the base class for useful methods.
 * This is the template specialization of the unnumbered QExtPointerFunctor
 * template for 1 argument(s), specialized for different numbers of arguments
 * This is possible because the template has default (QExtNil) template types.
 */
template < typename T_return, typename T_arg1 >
class QExtPointerFunctor< T_return, T_arg1, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil > : public QExtPrivate::QExtPointerFunctor1< T_return, T_arg1 >
{
public:
    typedef QExtPrivate::QExtPointerFunctor1< T_return, T_arg1 > Base;
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtPointerFunctor() {}
    QExtPointerFunctor(Function func) : Base(func) {}
    QExtPointerFunctor(const QExtPointerFunctor &other) : Base(other.m_funcPtr) {}

    /** Invoke the contained functor unless slot is in blocking state.
     * \param arg1 Argument to be passed on to the functor.
     * \return The return value of the functor invocation.
     */
    T_return operator()(typename QExtTypeTrait< T_arg1 >::Take arg1) const
    {
        return Base::operator()(arg1);
    }
};

/** Convenience wrapper for the numbered QExtPointerFunctor# templates.
 * See the base class for useful methods.
 * This is the template specialization of the unnumbered QExtPointerFunctor
 * template for 0 argument(s), specialized for different numbers of arguments
 * This is possible because the template has default (QExtNil) template types.
 */
template < typename T_return >
class QExtPointerFunctor< T_return, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil > : public QExtPrivate::QExtPointerFunctor0< T_return >
{
public:
    typedef QExtPrivate::QExtPointerFunctor0< T_return > Base;
    typedef typename Base::Function Function;
    typedef typename Base::Return Return;

    QExtPointerFunctor() {}
    QExtPointerFunctor(Function func) : Base(func) {}
    QExtPointerFunctor(const QExtPointerFunctor &other) : Base(other.m_funcPtr) {}

    /** Invoke the contained functor unless slot is in blocking state.
     * \return The return value of the functor invocation.
     */
    T_return operator()() const
    {
        return Base::operator()();
    }
};

// unnumbered qextPointerFunctor
/** Creates a functor of type QExtPointerFunctor7 which wraps an existing non-member function.
 * \param func Pointer to function that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextPointerFunctor
 */
template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7 >
inline QExtPointerFunctor< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
    qextPointerFunctor(T_return (*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7))
{
    return QExtPointerFunctor< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(func);
}

/** Creates a functor of type QExtPointerFunctor6 which wraps an existing non-member function.
 * \param func Pointer to function that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextPointerFunctor
 */
template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
inline QExtPointerFunctor< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
    qextPointerFunctor(T_return (*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6))
{
    return QExtPointerFunctor< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(func);
}

/** Creates a functor of type QExtPointerFunctor5 which wraps an existing non-member function.
 * \param func Pointer to function that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextPointerFunctor
 */
template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
inline QExtPointerFunctor< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 > qextPointerFunctor(T_return (*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5))
{
    return QExtPointerFunctor< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(func);
}

/** Creates a functor of type QExtPointerFunctor4 which wraps an existing non-member function.
 * \param func Pointer to function that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextPointerFunctor
 */
template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
inline QExtPointerFunctor< T_return, T_arg1, T_arg2, T_arg3, T_arg4 > qextPointerFunctor(T_return (*func)(T_arg1, T_arg2, T_arg3, T_arg4))
{
    return QExtPointerFunctor< T_return, T_arg1, T_arg2, T_arg3, T_arg4 >(func);
}

/** Creates a functor of type QExtPointerFunctor3 which wraps an existing non-member function.
 * \param func Pointer to function that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextPointerFunctor
 */
template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3 >
inline QExtPointerFunctor< T_return, T_arg1, T_arg2, T_arg3 > qextPointerFunctor(T_return (*func)(T_arg1, T_arg2, T_arg3))
{
    return QExtPointerFunctor< T_return, T_arg1, T_arg2, T_arg3 >(func);
}

/** Creates a functor of type QExtPointerFunctor2 which wraps an existing non-member function.
 * \param func Pointer to function that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextPointerFunctor
 */
template < typename T_return, typename T_arg1, typename T_arg2 >
inline QExtPointerFunctor< T_return, T_arg1, T_arg2 > qextPointerFunctor(T_return (*func)(T_arg1, T_arg2))
{
    return QExtPointerFunctor< T_return, T_arg1, T_arg2 >(func);
}

/** Creates a functor of type QExtPointerFunctor1 which wraps an existing non-member function.
 * \param func Pointer to function that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextPointerFunctor
 */
template < typename T_return, typename T_arg1 >
inline QExtPointerFunctor< T_return, T_arg1 > qextPointerFunctor(T_return (*func)(T_arg1))
{
    return QExtPointerFunctor< T_return, T_arg1 >(func);
}

/** Creates a functor of type QExtPointerFunctor0 which wraps an existing non-member function.
 * \param func Pointer to function that should be wrapped.
 * \return Functor that executes @e func on invokation.
 *
 * \ingroup qextPointerFunctor
 */
template < typename T_return >
inline QExtPointerFunctor< T_return > qextPointerFunctor(T_return (*func)())
{
    return QExtPointerFunctor< T_return >(func);
}



#endif // _QEXTFUNCTORPOINTER_H
