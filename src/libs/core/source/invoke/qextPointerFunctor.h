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



namespace detail
{

/** @defgroup qextMakeFunctor qextMakeFunctor()
 * qextMakeFunctor() is used to convert a pointer to a function to a functor.
 * If the function pointer is to an overloaded type, you must specify
 * the types using template arguments starting with the first argument.
 * It is not necessary to supply the return type.
 *
 * @par Example:
 * @code
 * void foo(int) {}
 * QExtFunction<void, int> slot = qextMakeFunctor(&foo);
 * @endcode
 *
 * Use qextMakeFunctor#() if there is an ambiguity as to the number of arguments.
 *
 * @par Example:
 * @code
 * void foo(int) {}  // choose this one
 * void foo(float) {}
 * void foo(int, int) {}
 * QExtFunction<void, long> slot = qextMakeFunctor<int>(&foo);
 * @endcode
 *
 * qextMakeFunctor() can also be used to convert a pointer to a static member
 * function to a functor, like so:
 *
 * @par Example:
 * @code
 * struct foo
 * {
 *   static void bar(int) {}
 * };
 * QEXTlot<void, int> slot = qextMakeFunctor(&foo::bar);
 * @endcode
 */

/** QExtPointerFunctor7 wraps existing non-member functions with 7 argument(s).
 * Use the convenience function qextMakeFunctor() to create an instance of QExtPointerFunctor7.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Arg2 Argument type used in the definition of operator()().
 * - @e Arg3 Argument type used in the definition of operator()().
 * - @e Arg4 Argument type used in the definition of operator()().
 * - @e Arg5 Argument type used in the definition of operator()().
 * - @e Arg6 Argument type used in the definition of operator()().
 * - @e Arg7 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 */
template < class Return, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7 >
class QExtPointerFunctor7 : public QExtFunctorBase
{
public:
    typedef Return (*FunctionType)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7);
    typedef Return ResultType;

    /**
     * @brief Constructs an invalid functor.
     */
    QExtPointerFunctor7() : mFuncPtr(QEXT_NULLPTR) {}

    /** Constructs a QExtPointerFunctor7 object that wraps an existing function.
     * @param func Pointer to function that will be invoked from operator()().
     */
    QExtPointerFunctor7(FunctionType func) : mFuncPtr(func) {}

    QExtPointerFunctor7(const QExtPointerFunctor7 &other) : mFuncPtr(other.mFuncPtr) {}

    /** Execute the wrapped function.
     * @param arg1 Argument to be passed on to the function.
     * @param arg2 Argument to be passed on to the function.
     * @param arg3 Argument to be passed on to the function.
     * @param arg4 Argument to be passed on to the function.
     * @param arg5 Argument to be passed on to the function.
     * @param arg6 Argument to be passed on to the function.
     * @param arg7 Argument to be passed on to the function.
     * @return The return value of the function invocation.
     */
    Return operator()(typename QExtTypeTrait< Arg1 >::Take arg1,
                      typename QExtTypeTrait< Arg2 >::Take arg2,
                      typename QExtTypeTrait< Arg3 >::Take arg3,
                      typename QExtTypeTrait< Arg4 >::Take arg4,
                      typename QExtTypeTrait< Arg5 >::Take arg5,
                      typename QExtTypeTrait< Arg6 >::Take arg6,
                      typename QExtTypeTrait< Arg7 >::Take arg7) const
    {
        return mFuncPtr(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

protected:
    FunctionType mFuncPtr;
};

/** QExtPointerFunctor6 wraps existing non-member functions with 6 argument(s).
 * Use the convenience function qextMakeFunctor() to create an instance of QExtPointerFunctor6.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Arg2 Argument type used in the definition of operator()().
 * - @e Arg3 Argument type used in the definition of operator()().
 * - @e Arg4 Argument type used in the definition of operator()().
 * - @e Arg5 Argument type used in the definition of operator()().
 * - @e Arg6 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 */
template < class Return, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6 >
class QExtPointerFunctor6 : public QExtFunctorBase
{
public:
    typedef Return (*FunctionType)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6);
    typedef Return ResultType;

    /**
     * @brief Constructs an invalid functor.
     */
    QExtPointerFunctor6() : mFuncPtr(QEXT_NULLPTR) {}

    /**
     * @brief Constructs a QExtPointerFunctor6 object that wraps an existing function.
     * @param func Pointer to function that will be invoked from operator()().
     */
    QExtPointerFunctor6(FunctionType func) : mFuncPtr(func) {}

    QExtPointerFunctor6(const QExtPointerFunctor6 &other) : mFuncPtr(other.mFuncPtr) {}

    /**
     * @brief Execute the wrapped function.
     * @param arg1 Argument to be passed on to the function.
     * @param arg2 Argument to be passed on to the function.
     * @param arg3 Argument to be passed on to the function.
     * @param arg4 Argument to be passed on to the function.
     * @param arg5 Argument to be passed on to the function.
     * @param arg6 Argument to be passed on to the function.
     * @return The return value of the function invocation.
     */
    Return operator()(typename QExtTypeTrait< Arg1 >::Take arg1,
                      typename QExtTypeTrait< Arg2 >::Take arg2,
                      typename QExtTypeTrait< Arg3 >::Take arg3,
                      typename QExtTypeTrait< Arg4 >::Take arg4,
                      typename QExtTypeTrait< Arg5 >::Take arg5,
                      typename QExtTypeTrait< Arg6 >::Take arg6) const
    {
        return mFuncPtr(arg1, arg2, arg3, arg4, arg5, arg6);
    }

protected:
    FunctionType mFuncPtr;
};

/**
 * @brief QExtPointerFunctor5 wraps existing non-member functions with 5 argument(s).
 * Use the convenience function qextMakeFunctor() to create an instance of QExtPointerFunctor5.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Arg2 Argument type used in the definition of operator()().
 * - @e Arg3 Argument type used in the definition of operator()().
 * - @e Arg4 Argument type used in the definition of operator()().
 * - @e Arg5 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 */
template < class Return, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5 >
class QExtPointerFunctor5 : public QExtFunctorBase
{
public:
    typedef Return (*FunctionType)(Arg1, Arg2, Arg3, Arg4, Arg5);
    typedef Return ResultType;

    /**
     * @brief Constructs an invalid functor.
     */
    QExtPointerFunctor5() : mFuncPtr(QEXT_NULLPTR) {}

    /**
     * @brief Constructs a QExtPointerFunctor5 object that wraps an existing function.
     * @param func Pointer to function that will be invoked from operator()().
     */
    QExtPointerFunctor5(FunctionType func) : mFuncPtr(func) {}

    QExtPointerFunctor5(const QExtPointerFunctor5 &other) : mFuncPtr(other.mFuncPtr) {}

    /**
     * @brief Execute the wrapped function.
     * @param arg1 Argument to be passed on to the function.
     * @param arg2 Argument to be passed on to the function.
     * @param arg3 Argument to be passed on to the function.
     * @param arg4 Argument to be passed on to the function.
     * @param arg5 Argument to be passed on to the function.
     * @return The return value of the function invocation.
     */
    Return operator()(typename QExtTypeTrait< Arg1 >::Take arg1,
                      typename QExtTypeTrait< Arg2 >::Take arg2,
                      typename QExtTypeTrait< Arg3 >::Take arg3,
                      typename QExtTypeTrait< Arg4 >::Take arg4,
                      typename QExtTypeTrait< Arg5 >::Take arg5) const
    {
        return mFuncPtr(arg1, arg2, arg3, arg4, arg5);
    }

protected:
    FunctionType mFuncPtr;
};

/**
 * @brief QExtPointerFunctor4 wraps existing non-member functions with 4 argument(s).
 * Use the convenience function qextMakeFunctor() to create an instance of QExtPointerFunctor4.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Arg2 Argument type used in the definition of operator()().
 * - @e Arg3 Argument type used in the definition of operator()().
 * - @e Arg4 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 */
template < class Return, class Arg1, class Arg2, class Arg3, class Arg4 >
class QExtPointerFunctor4 : public QExtFunctorBase
{
public:
    typedef Return (*FunctionType)(Arg1, Arg2, Arg3, Arg4);
    typedef Return ResultType;

    /**
     * @brief Constructs an invalid functor.
     */
    QExtPointerFunctor4() : mFuncPtr(QEXT_NULLPTR) {}

    /**
     * @brief Constructs a QExtPointerFunctor4 object that wraps an existing function.
     * @param func Pointer to function that will be invoked from operator()().
     */
    QExtPointerFunctor4(FunctionType func) : mFuncPtr(func) {}

    QExtPointerFunctor4(const QExtPointerFunctor4 &other) : mFuncPtr(other.mFuncPtr) {}

    /**
     * @brief Execute the wrapped function.
     * @param arg1 Argument to be passed on to the function.
     * @param arg2 Argument to be passed on to the function.
     * @param arg3 Argument to be passed on to the function.
     * @param arg4 Argument to be passed on to the function.
     * @return The return value of the function invocation.
     */
    Return operator()(typename QExtTypeTrait< Arg1 >::Take arg1,
                      typename QExtTypeTrait< Arg2 >::Take arg2,
                      typename QExtTypeTrait< Arg3 >::Take arg3,
                      typename QExtTypeTrait< Arg4 >::Take arg4) const
    {
        return mFuncPtr(arg1, arg2, arg3, arg4);
    }

protected:
    FunctionType mFuncPtr;
};

/**
 * @brief QExtPointerFunctor3 wraps existing non-member functions with 3 argument(s).
 * Use the convenience function qextMakeFunctor() to create an instance of QExtPointerFunctor3.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Arg2 Argument type used in the definition of operator()().
 * - @e Arg3 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 */
template < class Return, class Arg1, class Arg2, class Arg3 >
class QExtPointerFunctor3 : public QExtFunctorBase
{
public:
    typedef Return (*FunctionType)(Arg1, Arg2, Arg3);
    typedef Return ResultType;

    /**
     * @brief Constructs an invalid functor.
     */
    QExtPointerFunctor3() : mFuncPtr(QEXT_NULLPTR) {}

    /**
     * @brief Constructs a QExtPointerFunctor3 object that wraps an existing function.
     * @param func Pointer to function that will be invoked from operator()().
     */
    QExtPointerFunctor3(FunctionType func) : mFuncPtr(func) {}

    QExtPointerFunctor3(const QExtPointerFunctor3 &other) : mFuncPtr(other.mFuncPtr) {}

    /** Execute the wrapped function.
     * @param arg1 Argument to be passed on to the function.
     * @param arg2 Argument to be passed on to the function.
     * @param arg3 Argument to be passed on to the function.
     * @return The return value of the function invocation.
     */
    Return operator()(typename QExtTypeTrait< Arg1 >::Take arg1,
                      typename QExtTypeTrait< Arg2 >::Take arg2,
                      typename QExtTypeTrait< Arg3 >::Take arg3) const
    {
        return mFuncPtr(arg1, arg2, arg3);
    }

protected:
    FunctionType mFuncPtr;
};

/**
 * @brief QExtPointerFunctor2 wraps existing non-member functions with 2 argument(s).
 * Use the convenience function qextMakeFunctor() to create an instance of QExtPointerFunctor2.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Arg2 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 */
template < class Return, class Arg1, class Arg2 >
class QExtPointerFunctor2 : public QExtFunctorBase
{
public:
    typedef Return (*FunctionType)(Arg1, Arg2);
    typedef Return ResultType;

    /**
     * @brief Constructs an invalid functor.
     */
    QExtPointerFunctor2() : mFuncPtr(QEXT_NULLPTR) {}

    /**
     * @brief Constructs a QExtPointerFunctor2 object that wraps an existing function.
     * @param func Pointer to function that will be invoked from operator()().
     */
    QExtPointerFunctor2(FunctionType func) : mFuncPtr(func) {}

    QExtPointerFunctor2(const QExtPointerFunctor2 &other) : mFuncPtr(other.mFuncPtr) {}

    /**
     * @brief Execute the wrapped function.
     * @param arg1 Argument to be passed on to the function.
     * @param arg2 Argument to be passed on to the function.
     * @return The return value of the function invocation.
     */
    Return operator()(typename QExtTypeTrait< Arg1 >::Take arg1,
                      typename QExtTypeTrait< Arg2 >::Take arg2) const
    {
        return mFuncPtr(arg1, arg2);
    }

protected:
    FunctionType mFuncPtr;
};

/**
 * @brief QExtPointerFunctor1 wraps existing non-member functions with 1 argument(s).
 * Use the convenience function qextMakeFunctor() to create an instance of QExtPointerFunctor1.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 */
template < class Return, class Arg1 >
class QExtPointerFunctor1 : public QExtFunctorBase
{
public:
    typedef Return (*FunctionType)(Arg1);
    typedef Return ResultType;

    /**
     * @brief Constructs an invalid functor.
     */
    QExtPointerFunctor1() : mFuncPtr(QEXT_NULLPTR) {}

    /**
     * @brief Constructs a QExtPointerFunctor1 object that wraps an existing function.
     * @param func Pointer to function that will be invoked from operator()().
     */
    QExtPointerFunctor1(FunctionType func) : mFuncPtr(func) {}

    QExtPointerFunctor1(const QExtPointerFunctor1 &other) : mFuncPtr(other.mFuncPtr) {}

    /**
     * @brief Execute the wrapped function.
     * @param arg1 Argument to be passed on to the function.
     * @return The return value of the function invocation.
     */
    Return operator()(typename QExtTypeTrait< Arg1 >::Take arg1) const
    {
        return mFuncPtr(arg1);
    }

protected:
    FunctionType mFuncPtr;
};

/**
 * @brief QExtPointerFunctor0 wraps existing non-member functions with 0 argument(s).
 * Use the convenience function qextMakeFunctor() to create an instance of QExtPointerFunctor0.
 *
 * The following template arguments are used:
 * - @e Return The return type of operator()().
 */
template < class Return >
class QExtPointerFunctor0 : public QExtFunctorBase
{
public:
    typedef Return (*FunctionType)();
    typedef Return ResultType;

    /**
     * @brief Constructs an invalid functor.
     */
    QExtPointerFunctor0() : mFuncPtr(QEXT_NULLPTR) {}

    /**
     * @brief Constructs a QExtPointerFunctor0 object that wraps an existing function.
     * @param func Pointer to function that will be invoked from operator()().
     */
    QExtPointerFunctor0(FunctionType func) : mFuncPtr(func) {}

    QExtPointerFunctor0(const QExtPointerFunctor0 &other) : mFuncPtr(other.mFuncPtr) {}

    /**
     * @brief Execute the wrapped function.
     * @return The return value of the function invocation.
     */
    Return operator()() const
    {
        return mFuncPtr();
    }

protected:
    FunctionType mFuncPtr;
};

} // namespace detail

/**
 * @brief Convenience wrapper for the numbered QExtPointerFunctor# templates.
 * QExtPointerFunctor itself is a functor or to be more precise a closure.
 * It contains a single, arbitrary functor (or closure) that is executed in operator()().
 *
 * The template arguments determine the function signature of operator()():
 * - @e Return The return type of operator()().
 * - @e Arg1 Argument type used in the definition of operator()(). The default @p QExtNil means no argument.
 * - @e Arg2 Argument type used in the definition of operator()(). The default @p QExtNil means no argument.
 * - @e Arg3 Argument type used in the definition of operator()(). The default @p QExtNil means no argument.
 * - @e Arg4 Argument type used in the definition of operator()(). The default @p QExtNil means no argument.
 * - @e Arg5 Argument type used in the definition of operator()(). The default @p QExtNil means no argument.
 * - @e Arg6 Argument type used in the definition of operator()(). The default @p QExtNil means no argument.
 * - @e Arg7 Argument type used in the definition of operator()(). The default @p QExtNil means no argument.
 */
template <
    class Return,
    class Arg1 = QExtNil,
    class Arg2 = QExtNil,
    class Arg3 = QExtNil,
    class Arg4 = QExtNil,
    class Arg5 = QExtNil,
    class Arg6 = QExtNil,
    class Arg7 = QExtNil >
class QExtPointerFunctor : public detail::QExtPointerFunctor7< Return, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7 >
{
public:
    typedef detail::QExtPointerFunctor7< Return, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7 > BaseType;
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtPointerFunctor() {}
    QExtPointerFunctor(FunctionType func) : BaseType(func) {}
    QExtPointerFunctor(const QExtPointerFunctor &other) : BaseType(other.mFuncPtr) {}

    /**
     * @brief Invoke the contained functor.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @param arg6 Argument to be passed on to the functor.
     * @param arg7 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    Return operator()(typename QExtTypeTrait< Arg1 >::Take arg1,
                      typename QExtTypeTrait< Arg2 >::Take arg2,
                      typename QExtTypeTrait< Arg3 >::Take arg3,
                      typename QExtTypeTrait< Arg4 >::Take arg4,
                      typename QExtTypeTrait< Arg5 >::Take arg5,
                      typename QExtTypeTrait< Arg6 >::Take arg6,
                      typename QExtTypeTrait< Arg7 >::Take arg7) const
    {
        return BaseType::operator()(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

/**
 * @brief Convenience wrapper for the numbered QExtPointerFunctor# templates.
 * See the base class for useful methods.
 * This is the template specialization of the unnumbered QExtPointerFunctor
 * template for 6 argument(s), specialized for different numbers of arguments
 * This is possible because the template has default (QExtNil) template types.
 */
template < class Return, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6 >
class QExtPointerFunctor< Return, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, QExtNil >
    : public detail::QExtPointerFunctor6< Return, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6 >
{
public:
    typedef detail::QExtPointerFunctor6< Return, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6 > BaseType;
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtPointerFunctor() {}
    QExtPointerFunctor(FunctionType func) : BaseType(func) {}
    QExtPointerFunctor(const QExtPointerFunctor &other) : BaseType(other.mFuncPtr) {}

    /**
     * @brief Invoke the contained functor unless slot is in blocking state.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @param arg6 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    Return operator()(typename QExtTypeTrait< Arg1 >::Take arg1,
                      typename QExtTypeTrait< Arg2 >::Take arg2,
                      typename QExtTypeTrait< Arg3 >::Take arg3,
                      typename QExtTypeTrait< Arg4 >::Take arg4,
                      typename QExtTypeTrait< Arg5 >::Take arg5,
                      typename QExtTypeTrait< Arg6 >::Take arg6) const
    {
        return BaseType::operator()(arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

/**
 * @brief Convenience wrapper for the numbered QExtPointerFunctor# templates.
 * See the base class for useful methods.
 * This is the template specialization of the unnumbered QExtPointerFunctor
 * template for 5 argument(s), specialized for different numbers of arguments
 * This is possible because the template has default (QExtNil) template types.
 */
template < class Return, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5 >
class QExtPointerFunctor< Return, Arg1, Arg2, Arg3, Arg4, Arg5, QExtNil, QExtNil >
    : public detail::QExtPointerFunctor5< Return, Arg1, Arg2, Arg3, Arg4, Arg5 >
{
public:
    typedef detail::QExtPointerFunctor5< Return, Arg1, Arg2, Arg3, Arg4, Arg5 > BaseType;
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtPointerFunctor() {}
    QExtPointerFunctor(FunctionType func) : BaseType(func) {}
    QExtPointerFunctor(const QExtPointerFunctor &other) : BaseType(other.mFuncPtr) {}

    /**
     * @brief Invoke the contained functor unless slot is in blocking state.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    Return operator()(typename QExtTypeTrait< Arg1 >::Take arg1,
                      typename QExtTypeTrait< Arg2 >::Take arg2,
                      typename QExtTypeTrait< Arg3 >::Take arg3,
                      typename QExtTypeTrait< Arg4 >::Take arg4,
                      typename QExtTypeTrait< Arg5 >::Take arg5) const
    {
        return BaseType::operator()(arg1, arg2, arg3, arg4, arg5);
    }
};

/**
 * @brief Convenience wrapper for the numbered QExtPointerFunctor# templates.
 * See the base class for useful methods.
 * This is the template specialization of the unnumbered QExtPointerFunctor
 * template for 4 argument(s), specialized for different numbers of arguments
 * This is possible because the template has default (QExtNil) template types.
 */
template < class Return, class Arg1, class Arg2, class Arg3, class Arg4 >
class QExtPointerFunctor< Return, Arg1, Arg2, Arg3, Arg4, QExtNil, QExtNil, QExtNil >
    : public detail::QExtPointerFunctor4< Return, Arg1, Arg2, Arg3, Arg4 >
{
public:
    typedef detail::QExtPointerFunctor4< Return, Arg1, Arg2, Arg3, Arg4 > BaseType;
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtPointerFunctor() {}
    QExtPointerFunctor(FunctionType func) : BaseType(func) {}
    QExtPointerFunctor(const QExtPointerFunctor &other) : BaseType(other.mFuncPtr) {}

    /**
     * @brief Invoke the contained functor unless slot is in blocking state.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    Return operator()(typename QExtTypeTrait< Arg1 >::Take arg1,
                      typename QExtTypeTrait< Arg2 >::Take arg2,
                      typename QExtTypeTrait< Arg3 >::Take arg3,
                      typename QExtTypeTrait< Arg4 >::Take arg4) const
    {
        return BaseType::operator()(arg1, arg2, arg3, arg4);
    }
};

/**
 * @brief Convenience wrapper for the numbered QExtPointerFunctor# templates.
 * See the base class for useful methods.
 * This is the template specialization of the unnumbered QExtPointerFunctor
 * template for 3 argument(s), specialized for different numbers of arguments
 * This is possible because the template has default (QExtNil) template types.
 */
template < class Return, class Arg1, class Arg2, class Arg3 >
class QExtPointerFunctor< Return, Arg1, Arg2, Arg3, QExtNil, QExtNil, QExtNil, QExtNil >
    : public detail::QExtPointerFunctor3< Return, Arg1, Arg2, Arg3 >
{
public:
    typedef detail::QExtPointerFunctor3< Return, Arg1, Arg2, Arg3 > BaseType;
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtPointerFunctor() {}
    QExtPointerFunctor(FunctionType func) : BaseType(func) {}
    QExtPointerFunctor(const QExtPointerFunctor &other) : BaseType(other.mFuncPtr) {}

    /**
     * @brief Invoke the contained functor unless slot is in blocking state.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    Return operator()(typename QExtTypeTrait< Arg1 >::Take arg1,
                      typename QExtTypeTrait< Arg2 >::Take arg2,
                      typename QExtTypeTrait< Arg3 >::Take arg3) const
    {
        return BaseType::operator()(arg1, arg2, arg3);
    }
};

/**
 * @brief Convenience wrapper for the numbered QExtPointerFunctor# templates.
 * See the base class for useful methods.
 * This is the template specialization of the unnumbered QExtPointerFunctor
 * template for 2 argument(s), specialized for different numbers of arguments
 * This is possible because the template has default (QExtNil) template types.
 */
template < class Return, class Arg1, class Arg2 >
class QExtPointerFunctor< Return, Arg1, Arg2, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil >
    : public detail::QExtPointerFunctor2< Return, Arg1, Arg2 >
{
public:
    typedef detail::QExtPointerFunctor2< Return, Arg1, Arg2 > BaseType;
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtPointerFunctor() {}
    QExtPointerFunctor(FunctionType func) : BaseType(func) {}
    QExtPointerFunctor(const QExtPointerFunctor &other) : BaseType(other.mFuncPtr) {}

    /**
     * @brief Invoke the contained functor unless slot is in blocking state.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    Return operator()(typename QExtTypeTrait< Arg1 >::Take arg1,
                      typename QExtTypeTrait< Arg2 >::Take arg2) const
    {
        return BaseType::operator()(arg1, arg2);
    }
};

/**
 * @brief Convenience wrapper for the numbered QExtPointerFunctor# templates.
 * See the base class for useful methods.
 * This is the template specialization of the unnumbered QExtPointerFunctor
 * template for 1 argument(s), specialized for different numbers of arguments
 * This is possible because the template has default (QExtNil) template types.
 */
template < class Return, class Arg1 >
class QExtPointerFunctor< Return, Arg1, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil >
    : public detail::QExtPointerFunctor1< Return, Arg1 >
{
public:
    typedef detail::QExtPointerFunctor1< Return, Arg1 > BaseType;
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtPointerFunctor() {}
    QExtPointerFunctor(FunctionType func) : BaseType(func) {}
    QExtPointerFunctor(const QExtPointerFunctor &other) : BaseType(other.mFuncPtr) {}

    /**
     * @brief Invoke the contained functor unless slot is in blocking state.
     * @param arg1 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    Return operator()(typename QExtTypeTrait< Arg1 >::Take arg1) const
    {
        return BaseType::operator()(arg1);
    }
};

/**
 * @brief Convenience wrapper for the numbered QExtPointerFunctor# templates.
 * See the base class for useful methods.
 * This is the template specialization of the unnumbered QExtPointerFunctor
 * template for 0 argument(s), specialized for different numbers of arguments
 * This is possible because the template has default (QExtNil) template types.
 */
template < class Return >
class QExtPointerFunctor< Return, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil >
    : public detail::QExtPointerFunctor0< Return >
{
public:
    typedef detail::QExtPointerFunctor0< Return > BaseType;
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtPointerFunctor() {}
    QExtPointerFunctor(FunctionType func) : BaseType(func) {}
    QExtPointerFunctor(const QExtPointerFunctor &other) : BaseType(other.mFuncPtr) {}

    /**
     * @brief Invoke the contained functor unless slot is in blocking state.
     * @return The return value of the functor invocation.
     */
    Return operator()() const
    {
        return BaseType::operator()();
    }
};

/**
 * @brief Creates a functor of type QExtPointerFunctor7 which wraps an existing non-member function.
 * @param func Pointer to function that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template < class Return, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7 >
inline QExtPointerFunctor< Return, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7 >
qextMakeFunctor(Return (*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7))
{
    return QExtPointerFunctor< Return, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7 >(func);
}

/**
 * @brief Creates a functor of type QExtPointerFunctor6 which wraps an existing non-member function.
 * @param func Pointer to function that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template < class Return, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6 >
inline QExtPointerFunctor< Return, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6 >
qextMakeFunctor(Return (*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6))
{
    return QExtPointerFunctor< Return, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6 >(func);
}

/**
 * @brief Creates a functor of type QExtPointerFunctor5 which wraps an existing non-member function.
 * @param func Pointer to function that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template < class Return, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5 >
inline QExtPointerFunctor< Return, Arg1, Arg2, Arg3, Arg4, Arg5 >
qextMakeFunctor(Return (*func)(Arg1, Arg2, Arg3, Arg4, Arg5))
{
    return QExtPointerFunctor< Return, Arg1, Arg2, Arg3, Arg4, Arg5 >(func);
}

/**
 * @brief Creates a functor of type QExtPointerFunctor4 which wraps an existing non-member function.
 * @param func Pointer to function that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template < class Return, class Arg1, class Arg2, class Arg3, class Arg4 >
inline QExtPointerFunctor< Return, Arg1, Arg2, Arg3, Arg4 >
qextMakeFunctor(Return (*func)(Arg1, Arg2, Arg3, Arg4))
{
    return QExtPointerFunctor< Return, Arg1, Arg2, Arg3, Arg4 >(func);
}

/**
 * @brief Creates a functor of type QExtPointerFunctor3 which wraps an existing non-member function.
 * @param func Pointer to function that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template < class Return, class Arg1, class Arg2, class Arg3 >
inline QExtPointerFunctor< Return, Arg1, Arg2, Arg3 >
qextMakeFunctor(Return (*func)(Arg1, Arg2, Arg3))
{
    return QExtPointerFunctor< Return, Arg1, Arg2, Arg3 >(func);
}

/**
 * @brief Creates a functor of type QExtPointerFunctor2 which wraps an existing non-member function.
 * @param func Pointer to function that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template < class Return, class Arg1, class Arg2 >
inline QExtPointerFunctor< Return, Arg1, Arg2 >
qextMakeFunctor(Return (*func)(Arg1, Arg2))
{
    return QExtPointerFunctor< Return, Arg1, Arg2 >(func);
}

/**
 * @brief Creates a functor of type QExtPointerFunctor1 which wraps an existing non-member function.
 * @param func Pointer to function that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template < class Return, class Arg1 >
inline QExtPointerFunctor< Return, Arg1 >
qextMakeFunctor(Return (*func)(Arg1))
{
    return QExtPointerFunctor< Return, Arg1 >(func);
}

/**
 * @brief Creates a functor of type QExtPointerFunctor0 which wraps an existing non-member function.
 * @param func Pointer to function that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template < class Return >
inline QExtPointerFunctor< Return >
qextMakeFunctor(Return (*func)())
{
    return QExtPointerFunctor< Return >(func);
}

#endif // _QEXTFUNCTORPOINTER_H
