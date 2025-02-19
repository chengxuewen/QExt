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

#ifndef _QEXTMEMBERFUNCTOR_H
#define _QEXTMEMBERFUNCTOR_H

#include <qextGlobal.h>
#include <qextFunctorTrait.h>
#include <qextLimitReference.h>


/**
 * @defgroup qextMemberFunctor qextMakeFunctor()
 * qextMakeFunctor() is used to convert a pointer to a method to a functor.
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
 * QExtFunction<void, int> slot = qextMakeFunctor(my_foo, &foo::bar);
 * @endcode
 *
 * For const methods qextMakeFunctor() takes a const reference or pointer to an object.
 *
 * @par Example:
 * @code
 * struct foo : public QObject
 * {
 *   void bar(int) const {}
 * };
 * const foo my_foo;
 * QExtFunction<void, int> slot = qextMakeFunctor(my_foo, &foo::bar);
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
 */

namespace detail
{
/**
 * @brief QExtMemberFunctor7 wraps  methods with 7 argument(s).
 * Use the convenience function qextMakeFunctor() to create an instance of QExtMemberFunctor7.
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
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
class QExtMemberFunctor7 : public QExtFunctorBase
{
public:
    typedef Return (Obj::*FunctionType)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7);
    typedef Return ResultType;

    /**
     * @brief Constructs an invalid functor.
     */
    QExtMemberFunctor7() : mFuncPtr(QEXT_NULLPTR) {}

    /**
     * @brief Constructs a QExtMemberFunctor7 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtMemberFunctor7(FunctionType func) : mFuncPtr(func) {}

    QExtMemberFunctor7(const QExtMemberFunctor7 &other) : mFuncPtr(other.mFuncPtr) {}

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @param arg6 Argument to be passed on to the method.
     * @param arg7 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(Obj *obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5,
                      typename QExtTypeTrait<Arg6>::Take arg6,
                      typename QExtTypeTrait<Arg7>::Take arg7) const
    {
        return (obj->*(this->mFuncPtr))(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @param arg6 Argument to be passed on to the method.
     * @param arg7 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(Obj &obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5,
                      typename QExtTypeTrait<Arg6>::Take arg6,
                      typename QExtTypeTrait<Arg7>::Take arg7) const
    {
        return (obj.*mFuncPtr)(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

protected:
    FunctionType mFuncPtr;
};

/**
 * @brief QExtMemberFunctor6 wraps  methods with 6 argument(s).
 * Use the convenience function qextMakeFunctor() to create an instance of QExtMemberFunctor6.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Arg2 Argument type used in the definition of operator()().
 * - @e Arg3 Argument type used in the definition of operator()().
 * - @e Arg4 Argument type used in the definition of operator()().
 * - @e Arg5 Argument type used in the definition of operator()().
 * - @e Arg6 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
class QExtMemberFunctor6 : public QExtFunctorBase
{
public:
    typedef Return (Obj::*FunctionType)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6);
    typedef Return ResultType;

    /**
     * @brief Constructs an invalid functor.
     */
    QExtMemberFunctor6() : mFuncPtr(QEXT_NULLPTR) {}

    /**
     * @brief Constructs a QExtMemberFunctor6 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtMemberFunctor6(FunctionType func) : mFuncPtr(func) {}

    QExtMemberFunctor6(const QExtMemberFunctor6 &other) : mFuncPtr(other.mFuncPtr) {}

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @param arg6 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(Obj *obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5,
                      typename QExtTypeTrait<Arg6>::Take arg6) const
    {
        return (obj->*(this->mFuncPtr))(arg1, arg2, arg3, arg4, arg5, arg6);
    }

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @param arg6 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(Obj &obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5,
                      typename QExtTypeTrait<Arg6>::Take arg6) const
    {
        return (obj.*mFuncPtr)(arg1, arg2, arg3, arg4, arg5, arg6);
    }

protected:
    FunctionType mFuncPtr;
};

/**
 * @brief QExtMemberFunctor5 wraps  methods with 5 argument(s).
 * Use the convenience function qextMakeFunctor() to create an instance of QExtMemberFunctor5.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Arg2 Argument type used in the definition of operator()().
 * - @e Arg3 Argument type used in the definition of operator()().
 * - @e Arg4 Argument type used in the definition of operator()().
 * - @e Arg5 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
class QExtMemberFunctor5 : public QExtFunctorBase
{
public:
    typedef Return (Obj::*FunctionType)(Arg1, Arg2, Arg3, Arg4, Arg5);
    typedef Return ResultType;

    /**
     * @brief Constructs an invalid functor.
     */
    QExtMemberFunctor5() : mFuncPtr(QEXT_NULLPTR) {}

    /**
     * @brief Constructs a QExtMemberFunctor5 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtMemberFunctor5(FunctionType func) : mFuncPtr(func) {}

    QExtMemberFunctor5(const QExtMemberFunctor5 &other) : mFuncPtr(other.mFuncPtr) {}

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(Obj *obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5) const
    {
        return (obj->*(this->mFuncPtr))(arg1, arg2, arg3, arg4, arg5);
    }

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(Obj &obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5) const
    {
        return (obj.*mFuncPtr)(arg1, arg2, arg3, arg4, arg5);
    }

protected:
    FunctionType mFuncPtr;
};

/**
 * @brief QExtMemberFunctor4 wraps  methods with 4 argument(s).
 * Use the convenience function qextMakeFunctor() to create an instance of QExtMemberFunctor4.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Arg2 Argument type used in the definition of operator()().
 * - @e Arg3 Argument type used in the definition of operator()().
 * - @e Arg4 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4>
class QExtMemberFunctor4 : public QExtFunctorBase
{
public:
    typedef Return (Obj::*FunctionType)(Arg1, Arg2, Arg3, Arg4);
    typedef Return ResultType;

    /**
     * @brief Constructs an invalid functor.
     */
    QExtMemberFunctor4() : mFuncPtr(QEXT_NULLPTR) {}

    /**
     * @brief Constructs a QExtMemberFunctor4 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtMemberFunctor4(FunctionType func) : mFuncPtr(func) {}

    QExtMemberFunctor4(const QExtMemberFunctor4 &other) : mFuncPtr(other.mFuncPtr) {}

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(Obj *obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4) const
    {
        return (obj->*(this->mFuncPtr))(arg1, arg2, arg3, arg4);
    }

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(Obj &obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4) const
    {
        return (obj.*mFuncPtr)(arg1, arg2, arg3, arg4);
    }

protected:
    FunctionType mFuncPtr;
};

/**
 * @brief QExtMemberFunctor3 wraps  methods with 3 argument(s).
 * Use the convenience function qextMakeFunctor() to create an instance of QExtMemberFunctor3.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Arg2 Argument type used in the definition of operator()().
 * - @e Arg3 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3>
class QExtMemberFunctor3 : public QExtFunctorBase
{
public:
    typedef Return (Obj::*FunctionType)(Arg1, Arg2, Arg3);
    typedef Return ResultType;

    /**
     * @brief Constructs an invalid functor.
     */
    QExtMemberFunctor3() : mFuncPtr(QEXT_NULLPTR) {}

    /**
     * @brief Constructs a QExtMemberFunctor3 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtMemberFunctor3(FunctionType func) : mFuncPtr(func) {}

    QExtMemberFunctor3(const QExtMemberFunctor3 &other) : mFuncPtr(other.mFuncPtr) {}

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(Obj *obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3) const
    {
        return (obj->*(this->mFuncPtr))(arg1, arg2, arg3);
    }

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(Obj &obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3) const
    {
        return (obj.*mFuncPtr)(arg1, arg2, arg3);
    }

protected:
    FunctionType mFuncPtr;
};

/**
 * @brief QExtMemberFunctor2 wraps  methods with 2 argument(s).
 * Use the convenience function qextMakeFunctor() to create an instance of QExtMemberFunctor2.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Arg2 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1, class Arg2>
class QExtMemberFunctor2 : public QExtFunctorBase
{
public:
    typedef Return (Obj::*FunctionType)(Arg1, Arg2);
    typedef Return ResultType;

    /**
     * @brief Constructs an invalid functor.
     */
    QExtMemberFunctor2() : mFuncPtr(QEXT_NULLPTR) {}

    /**
     * @brief Constructs a QExtMemberFunctor2 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtMemberFunctor2(FunctionType func) : mFuncPtr(func) {}

    QExtMemberFunctor2(const QExtMemberFunctor2 &other) : mFuncPtr(other.mFuncPtr) {}

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(Obj *obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2) const
    {
        return (obj->*(this->mFuncPtr))(arg1, arg2);
    }

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(Obj &obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2) const
    {
        return (obj.*mFuncPtr)(arg1, arg2);
    }

protected:
    FunctionType mFuncPtr;
};

/**
 * @brief QExtMemberFunctor1 wraps  methods with 1 argument(s).
 * Use the convenience function qextMakeFunctor() to create an instance of QExtMemberFunctor1.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1>
class QExtMemberFunctor1 : public QExtFunctorBase
{
public:
    typedef Return (Obj::*FunctionType)(Arg1);
    typedef Return ResultType;

    /**
     * @brief Constructs an invalid functor.
     */
    QExtMemberFunctor1() : mFuncPtr(QEXT_NULLPTR) {}

    /**
     * @brief Constructs a QExtMemberFunctor1 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtMemberFunctor1(FunctionType func) : mFuncPtr(func) {}

    QExtMemberFunctor1(const QExtMemberFunctor1 &other) : mFuncPtr(other.mFuncPtr) {}

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(Obj *obj, typename QExtTypeTrait<Arg1>::Take arg1) const
    {
        return (obj->*(this->mFuncPtr))(arg1);
    }

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(Obj &obj, typename QExtTypeTrait<Arg1>::Take arg1) const
    {
        return (obj.*mFuncPtr)(arg1);
    }

protected:
    FunctionType mFuncPtr;
};

/**
 * @brief QExtMemberFunctor0 wraps  methods with 0 argument(s).
 * Use the convenience function qextMakeFunctor() to create an instance of QExtMemberFunctor0.
 *
 * The following template arguments are used:
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj>
class QExtMemberFunctor0 : public QExtFunctorBase
{
public:
    typedef Return (Obj::*FunctionType)();
    typedef Return ResultType;

    /**
     * @brief Constructs an invalid functor.
     */
    QExtMemberFunctor0() : mFuncPtr(QEXT_NULLPTR) {}

    /**
     * @brief Constructs a QExtMemberFunctor0 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtMemberFunctor0(FunctionType func) : mFuncPtr(func) {}

    QExtMemberFunctor0(const QExtMemberFunctor0 &other) : mFuncPtr(other.mFuncPtr) {}

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @return The return value of the method invocation.
     */
    Return operator()(Obj *obj) const
    {
        return (obj->*(this->mFuncPtr))();
    }

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @return The return value of the method invocation.
     */
    Return operator()(Obj &obj) const
    {
        return (obj.*mFuncPtr)();
    }

protected:
    FunctionType mFuncPtr;
};

/**
 * @brief QExtConstMemberFunctor7 wraps const methods with 7 argument(s).
 * Use the convenience function qextMakeFunctor() to create an instance of QExtConstMemberFunctor7.
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
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
class QExtConstMemberFunctor7 : public QExtFunctorBase
{
public:
    typedef Return (Obj::*FunctionType)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7) const;
    typedef Return ResultType;

    /**
     * @brief Constructs an invalid functor.
     */
    QExtConstMemberFunctor7() : mFuncPtr(QEXT_NULLPTR) {}

    /**
     * @brief Constructs a QExtConstMemberFunctor7 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtConstMemberFunctor7(FunctionType func) : mFuncPtr(func) {}

    QExtConstMemberFunctor7(const QExtConstMemberFunctor7 &other) : mFuncPtr(other.mFuncPtr) {}

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @param arg6 Argument to be passed on to the method.
     * @param arg7 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(const Obj *obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5,
                      typename QExtTypeTrait<Arg6>::Take arg6,
                      typename QExtTypeTrait<Arg7>::Take arg7) const
    {
        return (obj->*(this->mFuncPtr))(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @param arg6 Argument to be passed on to the method.
     * @param arg7 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(const Obj &obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5,
                      typename QExtTypeTrait<Arg6>::Take arg6,
                      typename QExtTypeTrait<Arg7>::Take arg7) const
    {
        return (obj.*mFuncPtr)(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

protected:
    FunctionType mFuncPtr;
};

/**
 * @brief QExtConstMemberFunctor6 wraps const methods with 6 argument(s).
 * Use the convenience function qextMakeFunctor() to create an instance of QExtConstMemberFunctor6.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Arg2 Argument type used in the definition of operator()().
 * - @e Arg3 Argument type used in the definition of operator()().
 * - @e Arg4 Argument type used in the definition of operator()().
 * - @e Arg5 Argument type used in the definition of operator()().
 * - @e Arg6 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
class QExtConstMemberFunctor6 : public QExtFunctorBase
{
public:
    typedef Return (Obj::*FunctionType)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6) const;
    typedef Return ResultType;

    /**
     * @brief Constructs an invalid functor.
     */
    QExtConstMemberFunctor6() : mFuncPtr(QEXT_NULLPTR) {}

    /**
     * @brief Constructs a QExtConstMemberFunctor6 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtConstMemberFunctor6(FunctionType func) : mFuncPtr(func) {}

    QExtConstMemberFunctor6(const QExtConstMemberFunctor6 &other) : mFuncPtr(other.mFuncPtr) {}

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @param arg6 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(const Obj *obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5,
                      typename QExtTypeTrait<Arg6>::Take arg6) const
    {
        return (obj->*(this->mFuncPtr))(arg1, arg2, arg3, arg4, arg5, arg6);
    }

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @param arg6 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(const Obj &obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5,
                      typename QExtTypeTrait<Arg6>::Take arg6) const
    {
        return (obj.*mFuncPtr)(arg1, arg2, arg3, arg4, arg5, arg6);
    }

protected:
    FunctionType mFuncPtr;
};

/**
 * @brief QExtConstMemberFunctor5 wraps const methods with 5 argument(s).
 * Use the convenience function qextMakeFunctor() to create an instance of QExtConstMemberFunctor5.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Arg2 Argument type used in the definition of operator()().
 * - @e Arg3 Argument type used in the definition of operator()().
 * - @e Arg4 Argument type used in the definition of operator()().
 * - @e Arg5 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
class QExtConstMemberFunctor5 : public QExtFunctorBase
{
public:
    typedef Return (Obj::*FunctionType)(Arg1, Arg2, Arg3, Arg4, Arg5) const;
    typedef Return ResultType;

    /**
     * @brief Constructs an invalid functor.
     */
    QExtConstMemberFunctor5() : mFuncPtr(QEXT_NULLPTR) {}

    /**
     * @brief Constructs a QExtConstMemberFunctor5 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtConstMemberFunctor5(FunctionType func) : mFuncPtr(func) {}

    QExtConstMemberFunctor5(const QExtConstMemberFunctor5 &other) : mFuncPtr(other.mFuncPtr) {}

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(const Obj *obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5) const
    {
        return (obj->*(this->mFuncPtr))(arg1, arg2, arg3, arg4, arg5);
    }

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(const Obj &obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5) const
    {
        return (obj.*mFuncPtr)(arg1, arg2, arg3, arg4, arg5);
    }

protected:
    FunctionType mFuncPtr;
};

/**
 * @brief QExtConstMemberFunctor4 wraps const methods with 4 argument(s).
 * Use the convenience function qextMakeFunctor() to create an instance of QExtConstMemberFunctor4.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Arg2 Argument type used in the definition of operator()().
 * - @e Arg3 Argument type used in the definition of operator()().
 * - @e Arg4 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4>
class QExtConstMemberFunctor4 : public QExtFunctorBase
{
public:
    typedef Return (Obj::*FunctionType)(Arg1, Arg2, Arg3, Arg4) const;
    typedef Return ResultType;

    /**
     * @brief Constructs an invalid functor.
     */
    QExtConstMemberFunctor4() : mFuncPtr(QEXT_NULLPTR) {}

    /**
     * @brief Constructs a QExtConstMemberFunctor4 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtConstMemberFunctor4(FunctionType func) : mFuncPtr(func) {}

    QExtConstMemberFunctor4(const QExtConstMemberFunctor4 &other) : mFuncPtr(other.mFuncPtr) {}

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(const Obj *obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4) const
    {
        return (obj->*(this->mFuncPtr))(arg1, arg2, arg3, arg4);
    }

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(const Obj &obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4) const
    {
        return (obj.*mFuncPtr)(arg1, arg2, arg3, arg4);
    }

protected:
    FunctionType mFuncPtr;
};

/**
 * @brief QExtConstMemberFunctor3 wraps const methods with 3 argument(s).
 * Use the convenience function qextMakeFunctor() to create an instance of QExtConstMemberFunctor3.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Arg2 Argument type used in the definition of operator()().
 * - @e Arg3 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3>
class QExtConstMemberFunctor3 : public QExtFunctorBase
{
public:
    typedef Return (Obj::*FunctionType)(Arg1, Arg2, Arg3) const;
    typedef Return ResultType;

    /**
     * @brief Constructs an invalid functor.
     */
    QExtConstMemberFunctor3() : mFuncPtr(QEXT_NULLPTR) {}

    /**
     * @brief Constructs a QExtConstMemberFunctor3 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtConstMemberFunctor3(FunctionType func) : mFuncPtr(func) {}

    QExtConstMemberFunctor3(const QExtConstMemberFunctor3 &other) : mFuncPtr(other.mFuncPtr) {}

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(const Obj *obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3) const
    {
        return (obj->*(this->mFuncPtr))(arg1, arg2, arg3);
    }

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(const Obj &obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3) const
    {
        return (obj.*mFuncPtr)(arg1, arg2, arg3);
    }

protected:
    FunctionType mFuncPtr;
};

/**
 * @brief QExtConstMemberFunctor2 wraps const methods with 2 argument(s).
 * Use the convenience function qextMakeFunctor() to create an instance of QExtConstMemberFunctor2.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Arg2 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1, class Arg2>
class QExtConstMemberFunctor2 : public QExtFunctorBase
{
public:
    typedef Return (Obj::*FunctionType)(Arg1, Arg2) const;
    typedef Return ResultType;

    /**
     * @brief Constructs an invalid functor.
     */
    QExtConstMemberFunctor2() : mFuncPtr(QEXT_NULLPTR) {}

    /**
     * @brief Constructs a QExtConstMemberFunctor2 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtConstMemberFunctor2(FunctionType func) : mFuncPtr(func) {}

    QExtConstMemberFunctor2(const QExtConstMemberFunctor2 &other) : mFuncPtr(other.mFuncPtr) {}

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(const Obj *obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2) const
    {
        return (obj->*(this->mFuncPtr))(arg1, arg2);
    }

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(const Obj &obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2) const
    {
        return (obj.*mFuncPtr)(arg1, arg2);
    }

protected:
    FunctionType mFuncPtr;
};

/**
 * @brief QExtConstMemberFunctor1 wraps const methods with 1 argument(s).
 * Use the convenience function qextMakeFunctor() to create an instance of QExtConstMemberFunctor1.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1>
class QExtConstMemberFunctor1 : public QExtFunctorBase
{
public:
    typedef Return (Obj::*FunctionType)(Arg1) const;
    typedef Return ResultType;

    /**
     * @brief Constructs an invalid functor.
     */
    QExtConstMemberFunctor1() : mFuncPtr(QEXT_NULLPTR) {}

    /**
     * @brief Constructs a QExtConstMemberFunctor1 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtConstMemberFunctor1(FunctionType func) : mFuncPtr(func) {}

    QExtConstMemberFunctor1(const QExtConstMemberFunctor1 &other) : mFuncPtr(other.mFuncPtr) {}

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(const Obj *obj, typename QExtTypeTrait<Arg1>::Take arg1) const
    {
        return (obj->*(this->mFuncPtr))(arg1);
    }

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(const Obj &obj, typename QExtTypeTrait<Arg1>::Take arg1) const
    {
        return (obj.*mFuncPtr)(arg1);
    }

protected:
    FunctionType mFuncPtr;
};

/**
 * @brief QExtConstMemberFunctor0 wraps const methods with 0 argument(s).
 * Use the convenience function qextMakeFunctor() to create an instance of QExtConstMemberFunctor0.
 *
 * The following template arguments are used:
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj>
class QExtConstMemberFunctor0 : public QExtFunctorBase
{
public:
    typedef Return (Obj::*FunctionType)() const;
    typedef Return ResultType;

    /**
     * @brief Constructs an invalid functor.
     */
    QExtConstMemberFunctor0() : mFuncPtr(QEXT_NULLPTR) {}

    /**
     * @brief Constructs a QExtConstMemberFunctor0 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtConstMemberFunctor0(FunctionType func) : mFuncPtr(func) {}

    QExtConstMemberFunctor0(const QExtConstMemberFunctor0 &other) : mFuncPtr(other.mFuncPtr) {}

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @return The return value of the method invocation.
     */
    Return operator()(const Obj *obj) const
    {
        return (obj->*(this->mFuncPtr))();
    }

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @return The return value of the method invocation.
     */
    Return operator()(const Obj &obj) const
    {
        return (obj.*mFuncPtr)();
    }

protected:
    FunctionType mFuncPtr;
};

/**
 * @brief QExtVolatileMemberFunctor7 wraps volatile methods with 7 argument(s).
 * Use the convenience function qextMakeFunctor() to create an instance of QExtVolatileMemberFunctor7.
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
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
class QExtVolatileMemberFunctor7 : public QExtFunctorBase
{
public:
    typedef Return (Obj::*FunctionType)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7) volatile;
    typedef Return ResultType;

    /**
     * @brief Constructs an invalid functor.
     */
    QExtVolatileMemberFunctor7() : mFuncPtr(QEXT_NULLPTR) {}

    /**
     * @brief Constructs a QExtVolatileMemberFunctor7 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtVolatileMemberFunctor7(FunctionType func) : mFuncPtr(func) {}

    QExtVolatileMemberFunctor7(const QExtVolatileMemberFunctor7 &other) : mFuncPtr(other.mFuncPtr) {}

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @param arg6 Argument to be passed on to the method.
     * @param arg7 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(Obj *obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5,
                      typename QExtTypeTrait<Arg6>::Take arg6,
                      typename QExtTypeTrait<Arg7>::Take arg7) const
    {
        return (obj->*(this->mFuncPtr))(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @param arg6 Argument to be passed on to the method.
     * @param arg7 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(Obj &obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5,
                      typename QExtTypeTrait<Arg6>::Take arg6,
                      typename QExtTypeTrait<Arg7>::Take arg7) const
    {
        return (obj.*mFuncPtr)(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

protected:
    FunctionType mFuncPtr;
};

/**
 * @brief QExtVolatileMemberFunctor6 wraps volatile methods with 6 argument(s).
 * Use the convenience function qextMakeFunctor() to create an instance of QExtVolatileMemberFunctor6.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Arg2 Argument type used in the definition of operator()().
 * - @e Arg3 Argument type used in the definition of operator()().
 * - @e Arg4 Argument type used in the definition of operator()().
 * - @e Arg5 Argument type used in the definition of operator()().
 * - @e Arg6 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
class QExtVolatileMemberFunctor6 : public QExtFunctorBase
{
public:
    typedef Return (Obj::*FunctionType)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6) volatile;
    typedef Return ResultType;

    /**
     * @brief Constructs an invalid functor.
     */
    QExtVolatileMemberFunctor6() : mFuncPtr(QEXT_NULLPTR) {}

    /**
     * @brief Constructs a QExtVolatileMemberFunctor6 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtVolatileMemberFunctor6(FunctionType func) : mFuncPtr(func) {}

    QExtVolatileMemberFunctor6(const QExtVolatileMemberFunctor6 &other) : mFuncPtr(other.mFuncPtr) {}

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @param arg6 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(Obj *obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5,
                      typename QExtTypeTrait<Arg6>::Take arg6) const
    {
        return (obj->*(this->mFuncPtr))(arg1, arg2, arg3, arg4, arg5, arg6);
    }

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @param arg6 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(Obj &obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5,
                      typename QExtTypeTrait<Arg6>::Take arg6) const
    {
        return (obj.*mFuncPtr)(arg1, arg2, arg3, arg4, arg5, arg6);
    }

protected:
    FunctionType mFuncPtr;
};

/**
 * @brief QExtVolatileMemberFunctor5 wraps volatile methods with 5 argument(s).
 * Use the convenience function qextMakeFunctor() to create an instance of QExtVolatileMemberFunctor5.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Arg2 Argument type used in the definition of operator()().
 * - @e Arg3 Argument type used in the definition of operator()().
 * - @e Arg4 Argument type used in the definition of operator()().
 * - @e Arg5 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
class QExtVolatileMemberFunctor5 : public QExtFunctorBase
{
public:
    typedef Return (Obj::*FunctionType)(Arg1, Arg2, Arg3, Arg4, Arg5) volatile;
    typedef Return ResultType;

    /**
     * @brief Constructs an invalid functor.
     */
    QExtVolatileMemberFunctor5() : mFuncPtr(QEXT_NULLPTR) {}

    /**
     * @brief Constructs a QExtVolatileMemberFunctor5 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtVolatileMemberFunctor5(FunctionType func) : mFuncPtr(func) {}

    QExtVolatileMemberFunctor5(const QExtVolatileMemberFunctor5 &other) : mFuncPtr(other.mFuncPtr) {}

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(Obj *obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5) const
    {
        return (obj->*(this->mFuncPtr))(arg1, arg2, arg3, arg4, arg5);
    }

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(Obj &obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5) const
    {
        return (obj.*mFuncPtr)(arg1, arg2, arg3, arg4, arg5);
    }

protected:
    FunctionType mFuncPtr;
};

/**
 * @brief QExtVolatileMemberFunctor4 wraps volatile methods with 4 argument(s).
 * Use the convenience function qextMakeFunctor() to create an instance of QExtVolatileMemberFunctor4.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Arg2 Argument type used in the definition of operator()().
 * - @e Arg3 Argument type used in the definition of operator()().
 * - @e Arg4 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4>
class QExtVolatileMemberFunctor4 : public QExtFunctorBase
{
public:
    typedef Return (Obj::*FunctionType)(Arg1, Arg2, Arg3, Arg4) volatile;
    typedef Return ResultType;

    /**
     * @brief Constructs an invalid functor.
     */
    QExtVolatileMemberFunctor4() : mFuncPtr(QEXT_NULLPTR) {}

    /**
     * @brief Constructs a QExtVolatileMemberFunctor4 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtVolatileMemberFunctor4(FunctionType func) : mFuncPtr(func) {}

    QExtVolatileMemberFunctor4(const QExtVolatileMemberFunctor4 &other) : mFuncPtr(other.mFuncPtr) {}

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(Obj *obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4) const
    {
        return (obj->*(this->mFuncPtr))(arg1, arg2, arg3, arg4);
    }

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(Obj &obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4) const
    {
        return (obj.*mFuncPtr)(arg1, arg2, arg3, arg4);
    }

protected:
    FunctionType mFuncPtr;
};

/**
 * @brief QExtVolatileMemberFunctor3 wraps volatile methods with 3 argument(s).
 * Use the convenience function qextMakeFunctor() to create an instance of QExtVolatileMemberFunctor3.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Arg2 Argument type used in the definition of operator()().
 * - @e Arg3 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3>
class QExtVolatileMemberFunctor3 : public QExtFunctorBase
{
public:
    typedef Return (Obj::*FunctionType)(Arg1, Arg2, Arg3) volatile;
    typedef Return ResultType;

    /**
     * @brief Constructs an invalid functor.
     */
    QExtVolatileMemberFunctor3() : mFuncPtr(QEXT_NULLPTR) {}

    /**
     * @brief Constructs a QExtVolatileMemberFunctor3 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtVolatileMemberFunctor3(FunctionType func) : mFuncPtr(func) {}

    QExtVolatileMemberFunctor3(const QExtVolatileMemberFunctor3 &other) : mFuncPtr(other.mFuncPtr) {}

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(Obj *obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3) const
    {
        return (obj->*(this->mFuncPtr))(arg1, arg2, arg3);
    }

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(Obj &obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3) const
    {
        return (obj.*mFuncPtr)(arg1, arg2, arg3);
    }

protected:
    FunctionType mFuncPtr;
};

/**
 * @brief QExtVolatileMemberFunctor2 wraps volatile methods with 2 argument(s).
 * Use the convenience function qextMakeFunctor() to create an instance of QExtVolatileMemberFunctor2.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Arg2 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1, class Arg2>
class QExtVolatileMemberFunctor2 : public QExtFunctorBase
{
public:
    typedef Return (Obj::*FunctionType)(Arg1, Arg2) volatile;
    typedef Return ResultType;

    /**
     * @brief Constructs an invalid functor.
     */
    QExtVolatileMemberFunctor2() : mFuncPtr(QEXT_NULLPTR) {}

    /**
     * @brief Constructs a QExtVolatileMemberFunctor2 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtVolatileMemberFunctor2(FunctionType func) : mFuncPtr(func) {}

    QExtVolatileMemberFunctor2(const QExtVolatileMemberFunctor2 &other) : mFuncPtr(other.mFuncPtr) {}

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(Obj *obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2) const
    {
        return (obj->*(this->mFuncPtr))(arg1, arg2);
    }

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(Obj &obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2) const
    {
        return (obj.*mFuncPtr)(arg1, arg2);
    }

protected:
    FunctionType mFuncPtr;
};

/**
 * @brief QExtVolatileMemberFunctor1 wraps volatile methods with 1 argument(s).
 * Use the convenience function qextMakeFunctor() to create an instance of QExtVolatileMemberFunctor1.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1>
class QExtVolatileMemberFunctor1 : public QExtFunctorBase
{
public:
    typedef Return (Obj::*FunctionType)(Arg1) volatile;
    typedef Return ResultType;

    /**
     * @brief Constructs an invalid functor.
     */
    QExtVolatileMemberFunctor1() : mFuncPtr(QEXT_NULLPTR) {}

    /**
     * @brief Constructs a QExtVolatileMemberFunctor1 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtVolatileMemberFunctor1(FunctionType func) : mFuncPtr(func) {}

    QExtVolatileMemberFunctor1(const QExtVolatileMemberFunctor1 &other) : mFuncPtr(other.mFuncPtr) {}

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(Obj *obj, typename QExtTypeTrait<Arg1>::Take arg1) const
    {
        return (obj->*(this->mFuncPtr))(arg1);
    }

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(Obj &obj, typename QExtTypeTrait<Arg1>::Take arg1) const
    {
        return (obj.*mFuncPtr)(arg1);
    }

protected:
    FunctionType mFuncPtr;
};

/**
 * @brief QExtVolatileMemberFunctor0 wraps volatile methods with 0 argument(s).
 * Use the convenience function qextMakeFunctor() to create an instance of QExtVolatileMemberFunctor0.
 *
 * The following template arguments are used:
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj>
class QExtVolatileMemberFunctor0 : public QExtFunctorBase
{
public:
    typedef Return (Obj::*FunctionType)() volatile;
    typedef Return ResultType;

    /**
     * @brief Constructs an invalid functor.
     */
    QExtVolatileMemberFunctor0() : mFuncPtr(QEXT_NULLPTR) {}

    /**
     * @brief Constructs a QExtVolatileMemberFunctor0 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtVolatileMemberFunctor0(FunctionType func) : mFuncPtr(func) {}

    QExtVolatileMemberFunctor0(const QExtVolatileMemberFunctor0 &other) : mFuncPtr(other.mFuncPtr) {}

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @return The return value of the method invocation.
     */
    Return operator()(Obj *obj) const
    {
        return (obj->*(this->mFuncPtr))();
    }

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @return The return value of the method invocation.
     */
    Return operator()(Obj &obj) const
    {
        return (obj.*mFuncPtr)();
    }

protected:
    FunctionType mFuncPtr;
};

/**
 * @brief QExtConstVolatileMemberFunctor7 wraps const volatile methods with 7 argument(s).
 * Use the convenience function qextMakeFunctor() to create an instance of QExtConstVolatileMemberFunctor7.
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
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
class QExtConstVolatileMemberFunctor7 : public QExtFunctorBase
{
public:
    typedef Return (Obj::*FunctionType)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7) const volatile;
    typedef Return ResultType;

    /**
     * @brief Constructs an invalid functor.
     */
    QExtConstVolatileMemberFunctor7() : mFuncPtr(QEXT_NULLPTR) {}

    /**
     * @brief Constructs a QExtConstVolatileMemberFunctor7 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtConstVolatileMemberFunctor7(FunctionType func) : mFuncPtr(func) {}

    QExtConstVolatileMemberFunctor7(const QExtConstVolatileMemberFunctor7 &other) : mFuncPtr(other.mFuncPtr) {}

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @param arg6 Argument to be passed on to the method.
     * @param arg7 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(const Obj *obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5,
                      typename QExtTypeTrait<Arg6>::Take arg6,
                      typename QExtTypeTrait<Arg7>::Take arg7) const
    {
        return (obj->*(this->mFuncPtr))(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @param arg6 Argument to be passed on to the method.
     * @param arg7 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(const Obj &obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5,
                      typename QExtTypeTrait<Arg6>::Take arg6,
                      typename QExtTypeTrait<Arg7>::Take arg7) const
    {
        return (obj.*mFuncPtr)(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

protected:
    FunctionType mFuncPtr;
};

/**
 * @brief QExtConstVolatileMemberFunctor6 wraps const volatile methods with 6 argument(s).
 * Use the convenience function qextMakeFunctor() to create an instance of QExtConstVolatileMemberFunctor6.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Arg2 Argument type used in the definition of operator()().
 * - @e Arg3 Argument type used in the definition of operator()().
 * - @e Arg4 Argument type used in the definition of operator()().
 * - @e Arg5 Argument type used in the definition of operator()().
 * - @e Arg6 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
class QExtConstVolatileMemberFunctor6 : public QExtFunctorBase
{
public:
    typedef Return (Obj::*FunctionType)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6) const volatile;
    typedef Return ResultType;

    /**
     * @brief Constructs an invalid functor.
     */
    QExtConstVolatileMemberFunctor6() : mFuncPtr(QEXT_NULLPTR) {}

    /**
     * @brief Constructs a QExtConstVolatileMemberFunctor6 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtConstVolatileMemberFunctor6(FunctionType func) : mFuncPtr(func) {}

    QExtConstVolatileMemberFunctor6(const QExtConstVolatileMemberFunctor6 &other) : mFuncPtr(other.mFuncPtr) {}

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @param arg6 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(const Obj *obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5,
                      typename QExtTypeTrait<Arg6>::Take arg6) const
    {
        return (obj->*(this->mFuncPtr))(arg1, arg2, arg3, arg4, arg5, arg6);
    }

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @param arg6 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(const Obj &obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5,
                      typename QExtTypeTrait<Arg6>::Take arg6) const
    {
        return (obj.*mFuncPtr)(arg1, arg2, arg3, arg4, arg5, arg6);
    }

protected:
    FunctionType mFuncPtr;
};

/**
 * @brief QExtConstVolatileMemberFunctor5 wraps const volatile methods with 5 argument(s).
 * Use the convenience function qextMakeFunctor() to create an instance of QExtConstVolatileMemberFunctor5.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Arg2 Argument type used in the definition of operator()().
 * - @e Arg3 Argument type used in the definition of operator()().
 * - @e Arg4 Argument type used in the definition of operator()().
 * - @e Arg5 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
class QExtConstVolatileMemberFunctor5 : public QExtFunctorBase
{
public:
    typedef Return (Obj::*FunctionType)(Arg1, Arg2, Arg3, Arg4, Arg5) const volatile;
    typedef Return ResultType;

    /**
     * @brief Constructs an invalid functor.
     */
    QExtConstVolatileMemberFunctor5() : mFuncPtr(QEXT_NULLPTR) {}

    /**
     * @brief Constructs a QExtConstVolatileMemberFunctor5 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtConstVolatileMemberFunctor5(FunctionType func) : mFuncPtr(func) {}

    QExtConstVolatileMemberFunctor5(const QExtConstVolatileMemberFunctor5 &other) : mFuncPtr(other.mFuncPtr) {}

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(const Obj *obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5) const
    {
        return (obj->*(this->mFuncPtr))(arg1, arg2, arg3, arg4, arg5);
    }

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(const Obj &obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5) const
    {
        return (obj.*mFuncPtr)(arg1, arg2, arg3, arg4, arg5);
    }

protected:
    FunctionType mFuncPtr;
};

/**
 * @brief QExtConstVolatileMemberFunctor4 wraps const volatile methods with 4 argument(s).
 * Use the convenience function qextMakeFunctor() to create an instance of QExtConstVolatileMemberFunctor4.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Arg2 Argument type used in the definition of operator()().
 * - @e Arg3 Argument type used in the definition of operator()().
 * - @e Arg4 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4>
class QExtConstVolatileMemberFunctor4 : public QExtFunctorBase
{
public:
    typedef Return (Obj::*FunctionType)(Arg1, Arg2, Arg3, Arg4) const volatile;
    typedef Return ResultType;

    /**
     * @brief Constructs an invalid functor.
     */
    QExtConstVolatileMemberFunctor4() : mFuncPtr(QEXT_NULLPTR) {}

    /**
     * @brief Constructs a QExtConstVolatileMemberFunctor4 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtConstVolatileMemberFunctor4(FunctionType func) : mFuncPtr(func) {}

    QExtConstVolatileMemberFunctor4(const QExtConstVolatileMemberFunctor4 &other) : mFuncPtr(other.mFuncPtr) {}

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(const Obj *obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4) const
    {
        return (obj->*(this->mFuncPtr))(arg1, arg2, arg3, arg4);
    }

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(const Obj &obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4) const
    {
        return (obj.*mFuncPtr)(arg1, arg2, arg3, arg4);
    }

protected:
    FunctionType mFuncPtr;
};

/**
 * @brief QExtConstVolatileMemberFunctor3 wraps const volatile methods with 3 argument(s).
 * Use the convenience function qextMakeFunctor() to create an instance of QExtConstVolatileMemberFunctor3.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Arg2 Argument type used in the definition of operator()().
 * - @e Arg3 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3>
class QExtConstVolatileMemberFunctor3 : public QExtFunctorBase
{
public:
    typedef Return (Obj::*FunctionType)(Arg1, Arg2, Arg3) const volatile;
    typedef Return ResultType;

    /**
     * @brief Constructs an invalid functor.
     */
    QExtConstVolatileMemberFunctor3() : mFuncPtr(QEXT_NULLPTR) {}

    /**
     * @brief Constructs a QExtConstVolatileMemberFunctor3 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtConstVolatileMemberFunctor3(FunctionType func) : mFuncPtr(func) {}

    QExtConstVolatileMemberFunctor3(const QExtConstVolatileMemberFunctor3 &other) : mFuncPtr(other.mFuncPtr) {}

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(const Obj *obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3) const
    {
        return (obj->*(this->mFuncPtr))(arg1, arg2, arg3);
    }

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(const Obj &obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3) const
    {
        return (obj.*mFuncPtr)(arg1, arg2, arg3);
    }

protected:
    FunctionType mFuncPtr;
};

/**
 * @brief QExtConstVolatileMemberFunctor2 wraps const volatile methods with 2 argument(s).
 * Use the convenience function qextMakeFunctor() to create an instance of QExtConstVolatileMemberFunctor2.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Arg2 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1, class Arg2>
class QExtConstVolatileMemberFunctor2 : public QExtFunctorBase
{
public:
    typedef Return (Obj::*FunctionType)(Arg1, Arg2) const volatile;
    typedef Return ResultType;

    /**
     * @brief Constructs an invalid functor.
     */
    QExtConstVolatileMemberFunctor2() : mFuncPtr(QEXT_NULLPTR) {}

    /**
     * @brief Constructs a QExtConstVolatileMemberFunctor2 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtConstVolatileMemberFunctor2(FunctionType func) : mFuncPtr(func) {}

    QExtConstVolatileMemberFunctor2(const QExtConstVolatileMemberFunctor2 &other) : mFuncPtr(other.mFuncPtr) {}

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(const Obj *obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2) const
    {
        return (obj->*(this->mFuncPtr))(arg1, arg2);
    }

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(const Obj &obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2) const
    {
        return (obj.*mFuncPtr)(arg1, arg2);
    }

protected:
    FunctionType mFuncPtr;
};

/**
 * @brief QExtConstVolatileMemberFunctor1 wraps const volatile methods with 1 argument(s).
 * Use the convenience function qextMakeFunctor() to create an instance of QExtConstVolatileMemberFunctor1.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1>
class QExtConstVolatileMemberFunctor1 : public QExtFunctorBase
{
public:
    typedef Return (Obj::*FunctionType)(Arg1) const volatile;
    typedef Return ResultType;

    /**
     * @brief Constructs an invalid functor.
     */
    QExtConstVolatileMemberFunctor1() : mFuncPtr(QEXT_NULLPTR) {}

    /**
     * @brief Constructs a QExtConstVolatileMemberFunctor1 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtConstVolatileMemberFunctor1(FunctionType func) : mFuncPtr(func) {}

    QExtConstVolatileMemberFunctor1(const QExtConstVolatileMemberFunctor1 &other) : mFuncPtr(other.mFuncPtr) {}

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(const Obj *obj, typename QExtTypeTrait<Arg1>::Take arg1) const
    {
        return (obj->*(this->mFuncPtr))(arg1);
    }

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(const Obj &obj, typename QExtTypeTrait<Arg1>::Take arg1) const
    {
        return (obj.*mFuncPtr)(arg1);
    }

protected:
    FunctionType mFuncPtr;
};

/**
 * @brief QExtConstVolatileMemberFunctor0 wraps const volatile methods with 0 argument(s).
 * Use the convenience function qextMakeFunctor() to create an instance of QExtConstVolatileMemberFunctor0.
 *
 * The following template arguments are used:
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj>
class QExtConstVolatileMemberFunctor0 : public QExtFunctorBase
{
public:
    typedef Return (Obj::*FunctionType)() const volatile;
    typedef Return ResultType;

    /**
     * @brief Constructs an invalid functor.
     */
    QExtConstVolatileMemberFunctor0() : mFuncPtr(QEXT_NULLPTR) {}

    /**
     * @brief Constructs a QExtConstVolatileMemberFunctor0 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtConstVolatileMemberFunctor0(FunctionType func) : mFuncPtr(func) {}

    QExtConstVolatileMemberFunctor0(const QExtConstVolatileMemberFunctor0 &other) : mFuncPtr(other.mFuncPtr) {}

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @return The return value of the method invocation.
     */
    Return operator()(const Obj *obj) const
    {
        return (obj->*(this->mFuncPtr))();
    }

    /**
     * @brief Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @return The return value of the method invocation.
     */
    Return operator()(const Obj &obj) const
    {
        return (obj.*mFuncPtr)();
    }

protected:
    FunctionType mFuncPtr;
};

/**
 * @brief QExtBoundMemberFunctor7 encapsulates a  method with 7 arguments and an object instance.
 * Use the convenience function qextMakeFunctor() to create an instance of QExtBoundMemberFunctor7.
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
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
class QExtBoundMemberFunctor7
        : public QExtMemberFunctor7<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>
{
    typedef QExtMemberFunctor7<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /**
     * @brief Constructs a QExtBoundMemberFunctor7 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundMemberFunctor7(Obj *obj, FunctionType func) : BaseType(func), mObj(*obj) {}

    /**
     * @brief Constructs a QExtBoundMemberFunctor7 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundMemberFunctor7(Obj &obj, FunctionType func) : BaseType(func), mObj(obj) {}

    QExtBoundMemberFunctor7(const QExtBoundMemberFunctor7 &other) : BaseType(other.mFuncPtr), mObj(other.mObj) {}

    /**
     * @brief Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @param arg6 Argument to be passed on to the method.
     * @param arg7 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5,
                      typename QExtTypeTrait<Arg6>::Take arg6,
                      typename QExtTypeTrait<Arg7>::Take arg7) const
    {
        return (mObj.invoke().*(this->mFuncPtr))(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QExtLimitReference<Obj> mObj;
};

/**
 * @brief QExtBoundMemberFunctor6 encapsulates a  method with 6 arguments and an object instance.
 * Use the convenience function qextMakeFunctor() to create an instance of QExtBoundMemberFunctor6.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Arg2 Argument type used in the definition of operator()().
 * - @e Arg3 Argument type used in the definition of operator()().
 * - @e Arg4 Argument type used in the definition of operator()().
 * - @e Arg5 Argument type used in the definition of operator()().
 * - @e Arg6 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
class QExtBoundMemberFunctor6
        : public QExtMemberFunctor6<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>
{
    typedef QExtMemberFunctor6<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /**
     * @brief Constructs a QExtBoundMemberFunctor6 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundMemberFunctor6(Obj *obj, FunctionType func) : BaseType(func), mObj(*obj) {}

    /**
     * @brief Constructs a QExtBoundMemberFunctor6 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundMemberFunctor6(Obj &obj, FunctionType func) : BaseType(func), mObj(obj) {}

    QExtBoundMemberFunctor6(const QExtBoundMemberFunctor6 &other) : BaseType(other.mFuncPtr), mObj(other.mObj) {}

    /**
     * @brief Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @param arg6 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5,
                      typename QExtTypeTrait<Arg6>::Take arg6) const
    {
        return (mObj.invoke().*(this->mFuncPtr))(arg1, arg2, arg3, arg4, arg5, arg6);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QExtLimitReference<Obj> mObj;
};

/**
 * @brief QExtBoundMemberFunctor5 encapsulates a  method with 5 arguments and an object instance.
 * Use the convenience function qextMakeFunctor() to create an instance of QExtBoundMemberFunctor5.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Arg2 Argument type used in the definition of operator()().
 * - @e Arg3 Argument type used in the definition of operator()().
 * - @e Arg4 Argument type used in the definition of operator()().
 * - @e Arg5 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
class QExtBoundMemberFunctor5 : public QExtMemberFunctor5<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5>
{
    typedef QExtMemberFunctor5<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /**
     * @brief Constructs a QExtBoundMemberFunctor5 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundMemberFunctor5(Obj *obj, FunctionType func) : BaseType(func), mObj(*obj) {}

    /**
     * @brief Constructs a QExtBoundMemberFunctor5 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundMemberFunctor5(Obj &obj, FunctionType func) : BaseType(func), mObj(obj) {}

    QExtBoundMemberFunctor5(const QExtBoundMemberFunctor5 &other) : BaseType(other.mFuncPtr), mObj(other.mObj) {}

    /**
     * @brief Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5) const
    {
        return (mObj.invoke().*(this->mFuncPtr))(arg1, arg2, arg3, arg4, arg5);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QExtLimitReference<Obj> mObj;
};

/**
 * @brief QExtBoundMemberFunctor4 encapsulates a  method with 4 arguments and an object instance.
 * Use the convenience function qextMakeFunctor() to create an instance of QExtBoundMemberFunctor4.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Arg2 Argument type used in the definition of operator()().
 * - @e Arg3 Argument type used in the definition of operator()().
 * - @e Arg4 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4>
class QExtBoundMemberFunctor4 : public QExtMemberFunctor4<Return, Obj, Arg1, Arg2, Arg3, Arg4>
{
    typedef QExtMemberFunctor4<Return, Obj, Arg1, Arg2, Arg3, Arg4> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /**
     * @brief Constructs a QExtBoundMemberFunctor4 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundMemberFunctor4(Obj *obj, FunctionType func) : BaseType(func), mObj(*obj) {}

    /**
     * @brief Constructs a QExtBoundMemberFunctor4 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundMemberFunctor4(Obj &obj, FunctionType func) : BaseType(func), mObj(obj) {}

    QExtBoundMemberFunctor4(const QExtBoundMemberFunctor4 &other) : BaseType(other.mFuncPtr), mObj(other.mObj) {}

    /**
     * @brief Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4) const
    {
        return (mObj.invoke().*(this->mFuncPtr))(arg1, arg2, arg3, arg4);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QExtLimitReference<Obj> mObj;
};

/**
 * @brief QExtBoundMemberFunctor3 encapsulates a  method with 3 arguments and an object instance.
 * Use the convenience function qextMakeFunctor() to create an instance of QExtBoundMemberFunctor3.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Arg2 Argument type used in the definition of operator()().
 * - @e Arg3 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3>
class QExtBoundMemberFunctor3 : public QExtMemberFunctor3<Return, Obj, Arg1, Arg2, Arg3>
{
    typedef QExtMemberFunctor3<Return, Obj, Arg1, Arg2, Arg3> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /**
     * @brief Constructs a QExtBoundMemberFunctor3 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundMemberFunctor3(Obj *obj, FunctionType func) : BaseType(func), mObj(*obj) {}

    /**
     * @brief Constructs a QExtBoundMemberFunctor3 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundMemberFunctor3(Obj &obj, FunctionType func) : BaseType(func), mObj(obj) {}

    QExtBoundMemberFunctor3(const QExtBoundMemberFunctor3 &other) : BaseType(other.mFuncPtr), mObj(other.mObj) {}

    /**
     * @brief Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3) const
    {
        return (mObj.invoke().*(this->mFuncPtr))(arg1, arg2, arg3);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QExtLimitReference<Obj> mObj;
};

/**
 * @brief QExtBoundMemberFunctor2 encapsulates a  method with 2 arguments and an object instance.
 * Use the convenience function qextMakeFunctor() to create an instance of QExtBoundMemberFunctor2.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Arg2 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1, class Arg2>
class QExtBoundMemberFunctor2 : public QExtMemberFunctor2<Return, Obj, Arg1, Arg2>
{
    typedef QExtMemberFunctor2<Return, Obj, Arg1, Arg2> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /**
     * @brief Constructs a QExtBoundMemberFunctor2 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundMemberFunctor2(Obj *obj, FunctionType func) : BaseType(func), mObj(*obj) {}

    /**
     * @brief Constructs a QExtBoundMemberFunctor2 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundMemberFunctor2(Obj &obj, FunctionType func) : BaseType(func), mObj(obj) {}

    QExtBoundMemberFunctor2(const QExtBoundMemberFunctor2 &other) : BaseType(other.mFuncPtr), mObj(other.mObj) {}

    /**
     * @brief Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2) const
    {
        return (mObj.invoke().*(this->mFuncPtr))(arg1, arg2);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QExtLimitReference<Obj> mObj;
};

/**
 * @brief QExtBoundMemberFunctor1 encapsulates a  method with 1 arguments and an object instance.
 * Use the convenience function qextMakeFunctor() to create an instance of QExtBoundMemberFunctor1.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1>
class QExtBoundMemberFunctor1 : public QExtMemberFunctor1<Return, Obj, Arg1>
{
    typedef QExtMemberFunctor1<Return, Obj, Arg1> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /**
     * @brief Constructs a QExtBoundMemberFunctor1 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundMemberFunctor1(Obj *obj, FunctionType func) : BaseType(func), mObj(*obj) {}

    /**
     * @brief Constructs a QExtBoundMemberFunctor1 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundMemberFunctor1(Obj &obj, FunctionType func) : BaseType(func), mObj(obj) {}

    /**
     * @brief Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1) const
    {
        return (mObj.invoke().*(this->mFuncPtr))(arg1);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QExtLimitReference<Obj> mObj;
};

/**
 * @brief QExtBoundMemberFunctor0 encapsulates a  method with 0 arguments and an object instance.
 * Use the convenience function qextMakeFunctor() to create an instance of QExtBoundMemberFunctor0.
 *
 * The following template arguments are used:
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj>
class QExtBoundMemberFunctor0 : public QExtMemberFunctor0<Return, Obj>
{
    typedef QExtMemberFunctor0<Return, Obj> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /**
     * @brief Constructs a QExtBoundMemberFunctor0 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundMemberFunctor0(Obj *obj, FunctionType func) : BaseType(func), mObj(*obj) {}

    /**
     * @brief Constructs a QExtBoundMemberFunctor0 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundMemberFunctor0(Obj &obj, FunctionType func) : BaseType(func), mObj(obj) {}

    /**
     * @brief Execute the wrapped method operating on the stored instance.
     * @return The return value of the method invocation.
     */
    Return operator()() const
    {
        return (mObj.invoke().*(this->mFuncPtr))();
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QExtLimitReference<Obj> mObj;
};

/**
 * @brief QExtBoundConstMemberFunctor7 encapsulates a const method with 7 arguments and an object instance.
 * Use the convenience function qextMakeFunctor() to create an instance of QExtBoundConstMemberFunctor7.
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
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
class QExtBoundConstMemberFunctor7
        : public QExtConstMemberFunctor7<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>
{
    typedef QExtConstMemberFunctor7<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /**
     * @brief Constructs a QExtBoundConstMemberFunctor7 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundConstMemberFunctor7(const Obj *obj, FunctionType func) : BaseType(func), mObj(*obj) {}

    /**
     * @brief Constructs a QExtBoundConstMemberFunctor7 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundConstMemberFunctor7(const Obj &obj, FunctionType func) : BaseType(func), mObj(obj) {}

    QExtBoundConstMemberFunctor7(const QExtBoundConstMemberFunctor7 &other)
        : BaseType(other.mFuncPtr), mObj(other.mObj) {}

    /**
     * @brief Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @param arg6 Argument to be passed on to the method.
     * @param arg7 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5,
                      typename QExtTypeTrait<Arg6>::Take arg6,
                      typename QExtTypeTrait<Arg7>::Take arg7) const
    {
        return (mObj.invoke().*(this->mFuncPtr))(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QExtConstLimitReference<Obj> mObj;
};

/**
 * @brief QExtBoundConstMemberFunctor6 encapsulates a const method with 6 arguments and an object instance.
 * Use the convenience function qextMakeFunctor() to create an instance of QExtBoundConstMemberFunctor6.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Arg2 Argument type used in the definition of operator()().
 * - @e Arg3 Argument type used in the definition of operator()().
 * - @e Arg4 Argument type used in the definition of operator()().
 * - @e Arg5 Argument type used in the definition of operator()().
 * - @e Arg6 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
class QExtBoundConstMemberFunctor6
        : public QExtConstMemberFunctor6<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>
{
    typedef QExtConstMemberFunctor6<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /**
     * @brief Constructs a QExtBoundConstMemberFunctor6 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundConstMemberFunctor6(const Obj *obj, FunctionType func) : BaseType(func), mObj(*obj) {}

    /**
     * @brief Constructs a QExtBoundConstMemberFunctor6 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundConstMemberFunctor6(const Obj &obj, FunctionType func) : BaseType(func), mObj(obj) {}

    QExtBoundConstMemberFunctor6(const QExtBoundConstMemberFunctor6 &other)
        : BaseType(other.mFuncPtr), mObj(other.mObj) {}

    /**
     * @brief Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @param arg6 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5,
                      typename QExtTypeTrait<Arg6>::Take arg6) const
    {
        return (mObj.invoke().*(this->mFuncPtr))(arg1, arg2, arg3, arg4, arg5, arg6);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QExtConstLimitReference<Obj> mObj;
};

/**
 * @brief QExtBoundConstMemberFunctor5 encapsulates a const method with 5 arguments and an object instance.
 * Use the convenience function qextMakeFunctor() to create an instance of QExtBoundConstMemberFunctor5.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Arg2 Argument type used in the definition of operator()().
 * - @e Arg3 Argument type used in the definition of operator()().
 * - @e Arg4 Argument type used in the definition of operator()().
 * - @e Arg5 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
class QExtBoundConstMemberFunctor5
        : public QExtConstMemberFunctor5<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5>
{
    typedef QExtConstMemberFunctor5<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /**
     * @brief Constructs a QExtBoundConstMemberFunctor5 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundConstMemberFunctor5(const Obj *obj, FunctionType func) : BaseType(func), mObj(*obj) {}

    /**
     * @brief Constructs a QExtBoundConstMemberFunctor5 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundConstMemberFunctor5(const Obj &obj, FunctionType func) : BaseType(func), mObj(obj) {}

    QExtBoundConstMemberFunctor5(const QExtBoundConstMemberFunctor5 &other)
        : BaseType(other.mFuncPtr), mObj(other.mObj) {}

    /**
     * @brief Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5) const
    {
        return (mObj.invoke().*(this->mFuncPtr))(arg1, arg2, arg3, arg4, arg5);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QExtConstLimitReference<Obj> mObj;
};

/**
 * @brief QExtBoundConstMemberFunctor4 encapsulates a const method with 4 arguments and an object instance.
 * Use the convenience function qextMakeFunctor() to create an instance of QExtBoundConstMemberFunctor4.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Arg2 Argument type used in the definition of operator()().
 * - @e Arg3 Argument type used in the definition of operator()().
 * - @e Arg4 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4>
class QExtBoundConstMemberFunctor4 : public QExtConstMemberFunctor4<Return, Obj, Arg1, Arg2, Arg3, Arg4>
{
    typedef QExtConstMemberFunctor4<Return, Obj, Arg1, Arg2, Arg3, Arg4> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /**
     * @brief Constructs a QExtBoundConstMemberFunctor4 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundConstMemberFunctor4(const Obj *obj, FunctionType func) : BaseType(func), mObj(*obj) {}

    /**
     * @brief Constructs a QExtBoundConstMemberFunctor4 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundConstMemberFunctor4(const Obj &obj, FunctionType func) : BaseType(func), mObj(obj) {}

    QExtBoundConstMemberFunctor4(const QExtBoundConstMemberFunctor4 &other)
        : BaseType(other.mFuncPtr), mObj(other.mObj) {}

    /**
     * @brief Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4) const
    {
        return (mObj.invoke().*(this->mFuncPtr))(arg1, arg2, arg3, arg4);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QExtConstLimitReference<Obj> mObj;
};

/**
 * @brief QExtBoundConstMemberFunctor3 encapsulates a const method with 3 arguments and an object instance.
 * Use the convenience function qextMakeFunctor() to create an instance of QExtBoundConstMemberFunctor3.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Arg2 Argument type used in the definition of operator()().
 * - @e Arg3 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3>
class QExtBoundConstMemberFunctor3 : public QExtConstMemberFunctor3<Return, Obj, Arg1, Arg2, Arg3>
{
    typedef QExtConstMemberFunctor3<Return, Obj, Arg1, Arg2, Arg3> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /**
     * @brief Constructs a QExtBoundConstMemberFunctor3 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundConstMemberFunctor3(const Obj *obj, FunctionType func) : BaseType(func), mObj(*obj) {}

    /**
     * @brief Constructs a QExtBoundConstMemberFunctor3 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundConstMemberFunctor3(const Obj &obj, FunctionType func) : BaseType(func), mObj(obj) {}

    QExtBoundConstMemberFunctor3(const QExtBoundConstMemberFunctor3 &other)
        : BaseType(other.mFuncPtr), mObj(other.mObj) {}

    /**
     * @brief Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3) const
    {
        return (mObj.invoke().*(this->mFuncPtr))(arg1, arg2, arg3);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QExtConstLimitReference<Obj> mObj;
};

/**
 * @brief QExtBoundConstMemberFunctor2 encapsulates a const method with 2 arguments and an object instance.
 * Use the convenience function qextMakeFunctor() to create an instance of QExtBoundConstMemberFunctor2.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Arg2 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1, class Arg2>
class QExtBoundConstMemberFunctor2 : public QExtConstMemberFunctor2<Return, Obj, Arg1, Arg2>
{
    typedef QExtConstMemberFunctor2<Return, Obj, Arg1, Arg2> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /**
     * @brief Constructs a QExtBoundConstMemberFunctor2 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundConstMemberFunctor2(const Obj *obj, FunctionType func) : BaseType(func), mObj(*obj) {}

    /**
     * @brief Constructs a QExtBoundConstMemberFunctor2 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundConstMemberFunctor2(const Obj &obj, FunctionType func) : BaseType(func), mObj(obj) {}

    QExtBoundConstMemberFunctor2(const QExtBoundConstMemberFunctor2 &other)
        : BaseType(other.mFuncPtr), mObj(other.mObj) {}

    /**
     * @brief Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2) const
    {
        return (mObj.invoke().*(this->mFuncPtr))(arg1, arg2);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QExtConstLimitReference<Obj> mObj;
};

/**
 * @brief QExtBoundConstMemberFunctor1 encapsulates a const method with 1 arguments and an object instance.
 * Use the convenience function qextMakeFunctor() to create an instance of QExtBoundConstMemberFunctor1.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1>
class QExtBoundConstMemberFunctor1 : public QExtConstMemberFunctor1<Return, Obj, Arg1>
{
    typedef QExtConstMemberFunctor1<Return, Obj, Arg1> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /**
     * @brief Constructs a QExtBoundConstMemberFunctor1 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundConstMemberFunctor1(const Obj *obj, FunctionType func) : BaseType(func), mObj(*obj) {}

    /**
     * @brief Constructs a QExtBoundConstMemberFunctor1 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundConstMemberFunctor1(const Obj &obj, FunctionType func) : BaseType(func), mObj(obj) {}

    /**
     * @brief Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1) const
    {
        return (mObj.invoke().*(this->mFuncPtr))(arg1);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QExtConstLimitReference<Obj> mObj;
};

/**
 * @brief QExtBoundConstMemberFunctor0 encapsulates a const method with 0 arguments and an object instance.
 * Use the convenience function qextMakeFunctor() to create an instance of QExtBoundConstMemberFunctor0.
 *
 * The following template arguments are used:
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj>
class QExtBoundConstMemberFunctor0 : public QExtConstMemberFunctor0<Return, Obj>
{
    typedef QExtConstMemberFunctor0<Return, Obj> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /**
     * @brief Constructs a QExtBoundConstMemberFunctor0 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundConstMemberFunctor0(const Obj *obj, FunctionType func) : BaseType(func), mObj(*obj) {}

    /**
     * @brief Constructs a QExtBoundConstMemberFunctor0 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundConstMemberFunctor0(const Obj &obj, FunctionType func) : BaseType(func), mObj(obj) {}

    QExtBoundConstMemberFunctor0(const QExtBoundConstMemberFunctor0 &other)
        : BaseType(other.mFuncPtr), mObj(other.mObj) {}

    /**
     * @brief Execute the wrapped method operating on the stored instance.
     * @return The return value of the method invocation.
     */
    Return operator()() const
    {
        return (mObj.invoke().*(this->mFuncPtr))();
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QExtConstLimitReference<Obj> mObj;
};

/**
 * @brief QExtBoundVolatileMemberFunctor7 encapsulates a volatile method with 7 arguments and an object instance.
 * Use the convenience function qextMakeFunctor() to create an instance of QExtBoundVolatileMemberFunctor7.
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
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
class QExtBoundVolatileMemberFunctor7
        : public QExtVolatileMemberFunctor7<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>
{
    typedef QExtVolatileMemberFunctor7<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /**
     * @brief Constructs a QExtBoundVolatileMemberFunctor7 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundVolatileMemberFunctor7(Obj *obj, FunctionType func) : BaseType(func), mObj(*obj) {}

    /**
     * @brief Constructs a QExtBoundVolatileMemberFunctor7 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundVolatileMemberFunctor7(Obj &obj, FunctionType func) : BaseType(func), mObj(obj) {}

    QExtBoundVolatileMemberFunctor7(const QExtBoundVolatileMemberFunctor7 &other)
        : BaseType(other.mFuncPtr), mObj(other.mObj) {}

    /**
     * @brief Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @param arg6 Argument to be passed on to the method.
     * @param arg7 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5,
                      typename QExtTypeTrait<Arg6>::Take arg6,
                      typename QExtTypeTrait<Arg7>::Take arg7) const
    {
        return (mObj.invoke().*(this->mFuncPtr))(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QExtVolatileLimitReference<Obj> mObj;
};

/**
 * @brief QExtBoundVolatileMemberFunctor6 encapsulates a volatile method with 6 arguments and an object instance.
 * Use the convenience function qextMakeFunctor() to create an instance of QExtBoundVolatileMemberFunctor6.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Arg2 Argument type used in the definition of operator()().
 * - @e Arg3 Argument type used in the definition of operator()().
 * - @e Arg4 Argument type used in the definition of operator()().
 * - @e Arg5 Argument type used in the definition of operator()().
 * - @e Arg6 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
class QExtBoundVolatileMemberFunctor6
        : public QExtVolatileMemberFunctor6<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>
{
    typedef QExtVolatileMemberFunctor6<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /**
     * @brief Constructs a QExtBoundVolatileMemberFunctor6 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundVolatileMemberFunctor6(Obj *obj, FunctionType func) : BaseType(func), mObj(*obj) {}

    /**
     * @brief Constructs a QExtBoundVolatileMemberFunctor6 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundVolatileMemberFunctor6(Obj &obj, FunctionType func) : BaseType(func), mObj(obj) {}

    QExtBoundVolatileMemberFunctor6(const QExtBoundVolatileMemberFunctor6 &other)
        : BaseType(other.mFuncPtr), mObj(other.mObj) {}

    /**
     * @brief Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @param arg6 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5,
                      typename QExtTypeTrait<Arg6>::Take arg6) const
    {
        return (mObj.invoke().*(this->mFuncPtr))(arg1, arg2, arg3, arg4, arg5, arg6);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QExtVolatileLimitReference<Obj> mObj;
};

/**
 * @brief QExtBoundVolatileMemberFunctor5 encapsulates a volatile method with 5 arguments and an object instance.
 * Use the convenience function qextMakeFunctor() to create an instance of QExtBoundVolatileMemberFunctor5.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Arg2 Argument type used in the definition of operator()().
 * - @e Arg3 Argument type used in the definition of operator()().
 * - @e Arg4 Argument type used in the definition of operator()().
 * - @e Arg5 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
class QExtBoundVolatileMemberFunctor5
        : public QExtVolatileMemberFunctor5<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5>
{
    typedef QExtVolatileMemberFunctor5<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /**
     * @brief Constructs a QExtBoundVolatileMemberFunctor5 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundVolatileMemberFunctor5(Obj *obj, FunctionType func) : BaseType(func), mObj(*obj) {}

    /**
     * @brief Constructs a QExtBoundVolatileMemberFunctor5 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundVolatileMemberFunctor5(Obj &obj, FunctionType func) : BaseType(func), mObj(obj) {}

    QExtBoundVolatileMemberFunctor5(const QExtBoundVolatileMemberFunctor5 &other)
        : BaseType(other.mFuncPtr), mObj(other.mObj) {}

    /**
     * @brief Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5) const
    {
        return (mObj.invoke().*(this->mFuncPtr))(arg1, arg2, arg3, arg4, arg5);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QExtVolatileLimitReference<Obj> mObj;
};

/**
 * @brief QExtBoundVolatileMemberFunctor4 encapsulates a volatile method with 4 arguments and an object instance.
 * Use the convenience function qextMakeFunctor() to create an instance of QExtBoundVolatileMemberFunctor4.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Arg2 Argument type used in the definition of operator()().
 * - @e Arg3 Argument type used in the definition of operator()().
 * - @e Arg4 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4>
class QExtBoundVolatileMemberFunctor4
        : public QExtVolatileMemberFunctor4<Return, Obj, Arg1, Arg2, Arg3, Arg4>
{
    typedef QExtVolatileMemberFunctor4<Return, Obj, Arg1, Arg2, Arg3, Arg4> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /**
     * @brief Constructs a QExtBoundVolatileMemberFunctor4 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundVolatileMemberFunctor4(Obj *obj, FunctionType func) : BaseType(func), mObj(*obj) {}

    /**
     * @brief Constructs a QExtBoundVolatileMemberFunctor4 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundVolatileMemberFunctor4(Obj &obj, FunctionType func) : BaseType(func), mObj(obj) {}

    QExtBoundVolatileMemberFunctor4(const QExtBoundVolatileMemberFunctor4 &other)
        : BaseType(other.mFuncPtr), mObj(other.mObj) {}

    /**
     * @brief Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4) const
    {
        return (mObj.invoke().*(this->mFuncPtr))(arg1, arg2, arg3, arg4);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QExtVolatileLimitReference<Obj> mObj;
};

/**
 * @brief QExtBoundVolatileMemberFunctor3 encapsulates a volatile method with 3 arguments and an object instance.
 * Use the convenience function qextMakeFunctor() to create an instance of QExtBoundVolatileMemberFunctor3.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Arg2 Argument type used in the definition of operator()().
 * - @e Arg3 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3>
class QExtBoundVolatileMemberFunctor3 : public QExtVolatileMemberFunctor3<Return, Obj, Arg1, Arg2, Arg3>
{
    typedef QExtVolatileMemberFunctor3<Return, Obj, Arg1, Arg2, Arg3> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /**
     * @brief Constructs a QExtBoundVolatileMemberFunctor3 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundVolatileMemberFunctor3(Obj *obj, FunctionType func) : BaseType(func), mObj(*obj) {}

    /**
     * @brief Constructs a QExtBoundVolatileMemberFunctor3 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundVolatileMemberFunctor3(Obj &obj, FunctionType func) : BaseType(func), mObj(obj) {}

    QExtBoundVolatileMemberFunctor3(const QExtBoundVolatileMemberFunctor3 &other)
        : BaseType(other.mFuncPtr), mObj(other.mObj) {}

    /**
     * @brief Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3) const
    {
        return (mObj.invoke().*(this->mFuncPtr))(arg1, arg2, arg3);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QExtVolatileLimitReference<Obj> mObj;
};

/**
 * @brief QExtBoundVolatileMemberFunctor2 encapsulates a volatile method with 2 arguments and an object instance.
 * Use the convenience function qextMakeFunctor() to create an instance of QExtBoundVolatileMemberFunctor2.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Arg2 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1, class Arg2>
class QExtBoundVolatileMemberFunctor2 : public QExtVolatileMemberFunctor2<Return, Obj, Arg1, Arg2>
{
    typedef QExtVolatileMemberFunctor2<Return, Obj, Arg1, Arg2> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /**
     * @brief Constructs a QExtBoundVolatileMemberFunctor2 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundVolatileMemberFunctor2(Obj *obj, FunctionType func) : BaseType(func), mObj(*obj) {}

    /**
     * @brief Constructs a QExtBoundVolatileMemberFunctor2 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundVolatileMemberFunctor2(Obj &obj, FunctionType func) : BaseType(func), mObj(obj) {}

    QExtBoundVolatileMemberFunctor2(const QExtBoundVolatileMemberFunctor2 &other)
        : BaseType(other.mFuncPtr), mObj(other.mObj) {}

    /**
     * @brief Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2) const
    {
        return (mObj.invoke().*(this->mFuncPtr))(arg1, arg2);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QExtVolatileLimitReference<Obj> mObj;
};

/**
 * @brief QExtBoundVolatileMemberFunctor1 encapsulates a volatile method with 1 arguments and an object instance.
 * Use the convenience function qextMakeFunctor() to create an instance of QExtBoundVolatileMemberFunctor1.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1>
class QExtBoundVolatileMemberFunctor1 : public QExtVolatileMemberFunctor1<Return, Obj, Arg1>
{
    typedef QExtVolatileMemberFunctor1<Return, Obj, Arg1> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /**
     * @brief Constructs a QExtBoundVolatileMemberFunctor1 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundVolatileMemberFunctor1(Obj *obj, FunctionType func) : BaseType(func), mObj(*obj) {}

    /**
     * @brief Constructs a QExtBoundVolatileMemberFunctor1 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundVolatileMemberFunctor1(Obj &obj, FunctionType func) : BaseType(func), mObj(obj) {}

    QExtBoundVolatileMemberFunctor1(const QExtBoundVolatileMemberFunctor1 &other)
        : BaseType(other.mFuncPtr), mObj(other.mObj) {}

    /**
     * @brief Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1) const
    {
        return (mObj.invoke().*(this->mFuncPtr))(arg1);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QExtVolatileLimitReference<Obj> mObj;
};

/**
 * @brief QExtBoundVolatileMemberFunctor0 encapsulates a volatile method with 0 arguments and an object instance.
 * Use the convenience function qextMakeFunctor() to create an instance of QExtBoundVolatileMemberFunctor0.
 *
 * The following template arguments are used:
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj>
class QExtBoundVolatileMemberFunctor0 : public QExtVolatileMemberFunctor0<Return, Obj>
{
    typedef QExtVolatileMemberFunctor0<Return, Obj> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /**
     * @brief Constructs a QExtBoundVolatileMemberFunctor0 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundVolatileMemberFunctor0(Obj *obj, FunctionType func) : BaseType(func), mObj(*obj) {}

    /**
     * @brief Constructs a QExtBoundVolatileMemberFunctor0 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundVolatileMemberFunctor0(Obj &obj, FunctionType func) : BaseType(func), mObj(obj) {}

    QExtBoundVolatileMemberFunctor0(const QExtBoundVolatileMemberFunctor0 &other)
        : BaseType(other.mFuncPtr), mObj(other.mObj) {}

    /**
     * @brief Execute the wrapped method operating on the stored instance.
     * @return The return value of the method invocation.
     */
    Return operator()() const
    {
        return (mObj.invoke().*(this->mFuncPtr))();
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QExtVolatileLimitReference<Obj> mObj;
};

/**
 * @brief QExtBoundConstVolatileMemberFunctor7 encapsulates a const volatile method with 7 arguments and an object instance.
 * Use the convenience function qextMakeFunctor() to create an instance of QExtBoundConstVolatileMemberFunctor7.
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
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
class QExtBoundConstVolatileMemberFunctor7
        : public QExtConstVolatileMemberFunctor7<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>
{
    typedef QExtConstVolatileMemberFunctor7<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /**
     * @brief Constructs a QExtBoundConstVolatileMemberFunctor7 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundConstVolatileMemberFunctor7(const Obj *obj, FunctionType func) : BaseType(func), mObj(*obj) {}

    /**
     * @brief Constructs a QExtBoundConstVolatileMemberFunctor7 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundConstVolatileMemberFunctor7(const Obj &obj, FunctionType func) : BaseType(func), mObj(obj) {}

    QExtBoundConstVolatileMemberFunctor7(const QExtBoundConstVolatileMemberFunctor7 &other)
        : BaseType(other.mFuncPtr), mObj(other.mObj) {}

    /**
     * @brief Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @param arg6 Argument to be passed on to the method.
     * @param arg7 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5,
                      typename QExtTypeTrait<Arg6>::Take arg6,
                      typename QExtTypeTrait<Arg7>::Take arg7) const
    {
        return (mObj.invoke().*(this->mFuncPtr))(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QExtConstVolatileLimitReference<Obj> mObj;
};

/**
 * @brief QExtBoundConstVolatileMemberFunctor6 encapsulates a const volatile method with 6 arguments and an object instance.
 * Use the convenience function qextMakeFunctor() to create an instance of QExtBoundConstVolatileMemberFunctor6.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Arg2 Argument type used in the definition of operator()().
 * - @e Arg3 Argument type used in the definition of operator()().
 * - @e Arg4 Argument type used in the definition of operator()().
 * - @e Arg5 Argument type used in the definition of operator()().
 * - @e Arg6 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
class QExtBoundConstVolatileMemberFunctor6
        : public QExtConstVolatileMemberFunctor6<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>
{
    typedef QExtConstVolatileMemberFunctor6<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /**
     * @brief Constructs a QExtBoundConstVolatileMemberFunctor6 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundConstVolatileMemberFunctor6(const Obj *obj, FunctionType func) : BaseType(func), mObj(*obj) {}

    /**
     * @brief Constructs a QExtBoundConstVolatileMemberFunctor6 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundConstVolatileMemberFunctor6(const Obj &obj, FunctionType func) : BaseType(func), mObj(obj) {}

    QExtBoundConstVolatileMemberFunctor6(const QExtBoundConstVolatileMemberFunctor6 &other)
        : BaseType(other.mFuncPtr), mObj(other.mObj) {}

    /**
     * @brief Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @param arg6 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5,
                      typename QExtTypeTrait<Arg6>::Take arg6) const
    {
        return (mObj.invoke().*(this->mFuncPtr))(arg1, arg2, arg3, arg4, arg5, arg6);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QExtConstVolatileLimitReference<Obj> mObj;
};

/**
 * @brief QExtBoundConstVolatileMemberFunctor5 encapsulates a const volatile method with 5 arguments and an object instance.
 * Use the convenience function qextMakeFunctor() to create an instance of QExtBoundConstVolatileMemberFunctor5.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Arg2 Argument type used in the definition of operator()().
 * - @e Arg3 Argument type used in the definition of operator()().
 * - @e Arg4 Argument type used in the definition of operator()().
 * - @e Arg5 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
class QExtBoundConstVolatileMemberFunctor5
        : public QExtConstVolatileMemberFunctor5<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5>
{
    typedef QExtConstVolatileMemberFunctor5<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /**
     * @brief Constructs a QExtBoundConstVolatileMemberFunctor5 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundConstVolatileMemberFunctor5(const Obj *obj, FunctionType func) : BaseType(func), mObj(*obj) {}

    /**
     * @brief Constructs a QExtBoundConstVolatileMemberFunctor5 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundConstVolatileMemberFunctor5(const Obj &obj, FunctionType func) : BaseType(func), mObj(obj) {}

    QExtBoundConstVolatileMemberFunctor5(const QExtBoundConstVolatileMemberFunctor5 &other)
        : BaseType(other.mFuncPtr), mObj(other.mObj) {}

    /**
     * @brief Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5) const
    {
        return (mObj.invoke().*(this->mFuncPtr))(arg1, arg2, arg3, arg4, arg5);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QExtConstVolatileLimitReference<Obj> mObj;
};

/**
 * @brief QExtBoundConstVolatileMemberFunctor4 encapsulates a const volatile method with 4 arguments and an object instance.
 * Use the convenience function qextMakeFunctor() to create an instance of QExtBoundConstVolatileMemberFunctor4.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Arg2 Argument type used in the definition of operator()().
 * - @e Arg3 Argument type used in the definition of operator()().
 * - @e Arg4 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4>
class QExtBoundConstVolatileMemberFunctor4
        : public QExtConstVolatileMemberFunctor4<Return, Obj, Arg1, Arg2, Arg3, Arg4>
{
    typedef QExtConstVolatileMemberFunctor4<Return, Obj, Arg1, Arg2, Arg3, Arg4> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /**
     * @brief Constructs a QExtBoundConstVolatileMemberFunctor4 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundConstVolatileMemberFunctor4(const Obj *obj, FunctionType func) : BaseType(func), mObj(*obj) {}

    /**
     * @brief Constructs a QExtBoundConstVolatileMemberFunctor4 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundConstVolatileMemberFunctor4(const Obj &obj, FunctionType func) : BaseType(func), mObj(obj) {}

    QExtBoundConstVolatileMemberFunctor4(const QExtBoundConstVolatileMemberFunctor4 &other)
        : BaseType(other.mFuncPtr), mObj(other.mObj) {}

    /**
     * @brief Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4) const
    {
        return (mObj.invoke().*(this->mFuncPtr))(arg1, arg2, arg3, arg4);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QExtConstVolatileLimitReference<Obj> mObj;
};

/**
 * @brief QExtBoundConstVolatileMemberFunctor3 encapsulates a const volatile method with 3 arguments and an object instance.
 * Use the convenience function qextMakeFunctor() to create an instance of QExtBoundConstVolatileMemberFunctor3.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Arg2 Argument type used in the definition of operator()().
 * - @e Arg3 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3>
class QExtBoundConstVolatileMemberFunctor3
        : public QExtConstVolatileMemberFunctor3<Return, Obj, Arg1, Arg2, Arg3>
{
    typedef QExtConstVolatileMemberFunctor3<Return, Obj, Arg1, Arg2, Arg3> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /**
     * @brief Constructs a QExtBoundConstVolatileMemberFunctor3 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundConstVolatileMemberFunctor3(const Obj *obj, FunctionType func) : BaseType(func), mObj(*obj) {}

    /**
     * @brief Constructs a QExtBoundConstVolatileMemberFunctor3 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundConstVolatileMemberFunctor3(const Obj &obj, FunctionType func) : BaseType(func), mObj(obj) {}

    QExtBoundConstVolatileMemberFunctor3(const QExtBoundConstVolatileMemberFunctor3 &other)
        : BaseType(other.mFuncPtr), mObj(other.mObj) {}

    /**
     * @brief Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3) const
    {
        return (mObj.invoke().*(this->mFuncPtr))(arg1, arg2, arg3);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QExtConstVolatileLimitReference<Obj> mObj;
};

/**
 * @brief QExtBoundConstVolatileMemberFunctor2 encapsulates a const volatile method with 2 arguments and an object instance.
 * Use the convenience function qextMakeFunctor() to create an instance of QExtBoundConstVolatileMemberFunctor2.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Arg2 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1, class Arg2>
class QExtBoundConstVolatileMemberFunctor2 : public QExtConstVolatileMemberFunctor2<Return, Obj, Arg1, Arg2>
{
    typedef QExtConstVolatileMemberFunctor2<Return, Obj, Arg1, Arg2> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /**
     * @brief Constructs a QExtBoundConstVolatileMemberFunctor2 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundConstVolatileMemberFunctor2(const Obj *obj, FunctionType func) : BaseType(func), mObj(*obj) {}

    /**
     * @brief Constructs a QExtBoundConstVolatileMemberFunctor2 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundConstVolatileMemberFunctor2(const Obj &obj, FunctionType func) : BaseType(func), mObj(obj) {}

    QExtBoundConstVolatileMemberFunctor2(const QExtBoundConstVolatileMemberFunctor2 &other)
        : BaseType(other.mFuncPtr), mObj(other.mObj) {}

    /**
     * @brief Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2) const
    {
        return (mObj.invoke().*(this->mFuncPtr))(arg1, arg2);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QExtConstVolatileLimitReference<Obj> mObj;
};

/**
 * @brief QExtBoundConstVolatileMemberFunctor1 encapsulates a const volatile method with 1 arguments and an object instance.
 * Use the convenience function qextMakeFunctor() to create an instance of QExtBoundConstVolatileMemberFunctor1.
 *
 * The following template arguments are used:
 * - @e Arg1 Argument type used in the definition of operator()().
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj, class Arg1>
class QExtBoundConstVolatileMemberFunctor1 : public QExtConstVolatileMemberFunctor1<Return, Obj, Arg1>
{
    typedef QExtConstVolatileMemberFunctor1<Return, Obj, Arg1> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /**
     * @brief Constructs a QExtBoundConstVolatileMemberFunctor1 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundConstVolatileMemberFunctor1(const Obj *obj, FunctionType func) : BaseType(func), mObj(*obj) {}

    /**
     * @brief Constructs a QExtBoundConstVolatileMemberFunctor1 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundConstVolatileMemberFunctor1(const Obj &obj, FunctionType func) : BaseType(func), mObj(obj) {}

    QExtBoundConstVolatileMemberFunctor1(const QExtBoundConstVolatileMemberFunctor1 &other)
        : BaseType(other.mFuncPtr), mObj(other.mObj) {}

    /**
     * @brief Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1) const
    {
        return (mObj.invoke().*(this->mFuncPtr))(arg1);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QExtConstVolatileLimitReference<Obj> mObj;
};

/**
 * @brief QExtBoundConstVolatileMemberFunctor0 encapsulates a const volatile method with 0 arguments and an object instance.
 * Use the convenience function qextMakeFunctor() to create an instance of QExtBoundConstVolatileMemberFunctor0.
 *
 * The following template arguments are used:
 * - @e Return The return type of operator()().
 * - @e Obj The object type.
 */
template<class Return, class Obj>
class QExtBoundConstVolatileMemberFunctor0 : public QExtConstVolatileMemberFunctor0<Return, Obj>
{
    typedef QExtConstVolatileMemberFunctor0<Return, Obj> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /**
     * @brief Constructs a QExtBoundConstVolatileMemberFunctor0 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundConstVolatileMemberFunctor0(const Obj *obj, FunctionType func) : BaseType(func), mObj(*obj) {}

    /**
     * @brief Constructs a QExtBoundConstVolatileMemberFunctor0 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QExtBoundConstVolatileMemberFunctor0(const Obj &obj, FunctionType func) : BaseType(func), mObj(obj) {}

    QExtBoundConstVolatileMemberFunctor0(const QExtBoundConstVolatileMemberFunctor0 &other)
        : BaseType(other.mFuncPtr), mObj(other.mObj) {}

    /**
     * @brief Execute the wrapped method operating on the stored instance.
     * @return The return value of the method invocation.
     */
    Return operator()() const
    {
        return (mObj.invoke().*(this->mFuncPtr))();
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QExtConstVolatileLimitReference<Obj> mObj;
};

} // namespace QExtPrivate



template<class Return,
         class Obj,
         class Arg1 = QExtNil,
         class Arg2 = QExtNil,
         class Arg3 = QExtNil,
         class Arg4 = QExtNil,
         class Arg5 = QExtNil,
         class Arg6 = QExtNil,
         class Arg7 = QExtNil>
class QExtMemberFunctor
        : public detail::QExtMemberFunctor7<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>
{
    typedef detail::QExtMemberFunctor7<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtMemberFunctor() {}

    QExtMemberFunctor(FunctionType func) : BaseType(func) {}

    QExtMemberFunctor(const QExtMemberFunctor &other) : BaseType(other.mFuncPtr) {}

    Return operator()(Obj *obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5,
                      typename QExtTypeTrait<Arg6>::Take arg6,
                      typename QExtTypeTrait<Arg7>::Take arg7) const
    {
        return BaseType::operator()(obj, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    Return operator()(Obj &obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5,
                      typename QExtTypeTrait<Arg6>::Take arg6,
                      typename QExtTypeTrait<Arg7>::Take arg7) const
    {
        return BaseType::operator()(obj, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
class QExtMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, QExtNil>
        : public detail::QExtMemberFunctor6<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>
{
    typedef detail::QExtMemberFunctor6<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtMemberFunctor() {}

    QExtMemberFunctor(FunctionType func) : BaseType(func) {}

    QExtMemberFunctor(const QExtMemberFunctor &other) : BaseType(other.mFuncPtr) {}

    Return operator()(Obj *obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5,
                      typename QExtTypeTrait<Arg6>::Take arg6) const
    {
        return BaseType::operator()(obj, arg1, arg2, arg3, arg4, arg5, arg6);
    }

    Return operator()(Obj &obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5,
                      typename QExtTypeTrait<Arg6>::Take arg6) const
    {
        return BaseType::operator()(obj, arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
class QExtMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, QExtNil, QExtNil>
        : public detail::QExtMemberFunctor5<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5>
{
    typedef detail::QExtMemberFunctor5<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtMemberFunctor() {}

    QExtMemberFunctor(FunctionType func) : BaseType(func) {}

    QExtMemberFunctor(const QExtMemberFunctor &other) : BaseType(other.mFuncPtr) {}

    Return operator()(Obj *obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5) const
    {
        return BaseType::operator()(obj, arg1, arg2, arg3, arg4, arg5);
    }

    Return operator()(Obj &obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5) const
    {
        return BaseType::operator()(obj, arg1, arg2, arg3, arg4, arg5);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4>
class QExtMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, QExtNil, QExtNil, QExtNil>
        : public detail::QExtMemberFunctor4<Return, Obj, Arg1, Arg2, Arg3, Arg4>
{
    typedef detail::QExtMemberFunctor4<Return, Obj, Arg1, Arg2, Arg3, Arg4> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtMemberFunctor() {}

    QExtMemberFunctor(FunctionType func) : BaseType(func) {}

    QExtMemberFunctor(const QExtMemberFunctor &other) : BaseType(other.mFuncPtr) {}

    Return operator()(Obj *obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4) const
    {
        return BaseType::operator()(obj, arg1, arg2, arg3, arg4);
    }

    Return operator()(Obj &obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4) const
    {
        return BaseType::operator()(obj, arg1, arg2, arg3, arg4);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3>
class QExtMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, QExtNil, QExtNil, QExtNil, QExtNil>
        : public detail::QExtMemberFunctor3<Return, Obj, Arg1, Arg2, Arg3>
{
    typedef detail::QExtMemberFunctor3<Return, Obj, Arg1, Arg2, Arg3> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtMemberFunctor() {}

    QExtMemberFunctor(FunctionType func) : BaseType(func) {}

    QExtMemberFunctor(const QExtMemberFunctor &other) : BaseType(other.mFuncPtr) {}

    Return operator()(Obj *obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3) const
    {
        return BaseType::operator()(obj, arg1, arg2, arg3);
    }

    Return operator()(Obj &obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3) const
    {
        return BaseType::operator()(obj, arg1, arg2, arg3);
    }
};

template<class Return, class Obj, class Arg1, class Arg2>
class QExtMemberFunctor<Return, Obj, Arg1, Arg2, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
        : public detail::QExtMemberFunctor2<Return, Obj, Arg1, Arg2>
{
    typedef detail::QExtMemberFunctor2<Return, Obj, Arg1, Arg2> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtMemberFunctor() {}

    QExtMemberFunctor(FunctionType func) : BaseType(func) {}

    QExtMemberFunctor(const QExtMemberFunctor &other) : BaseType(other.mFuncPtr) {}

    Return operator()(Obj *obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2) const
    {
        return BaseType::operator()(obj, arg1, arg2);
    }

    Return operator()(Obj &obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2) const
    {
        return BaseType::operator()(obj, arg1, arg2);
    }
};

template<class Return, class Obj, class Arg1>
class QExtMemberFunctor<Return, Obj, Arg1, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
        : public detail::QExtMemberFunctor1<Return, Obj, Arg1>
{
    typedef detail::QExtMemberFunctor1<Return, Obj, Arg1> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtMemberFunctor() {}

    QExtMemberFunctor(FunctionType func) : BaseType(func) {}

    QExtMemberFunctor(const QExtMemberFunctor &other) : BaseType(other.mFuncPtr) {}

    Return operator()(Obj *obj, typename QExtTypeTrait<Arg1>::Take arg1) const
    {
        return BaseType::operator()(obj, arg1);
    }

    Return operator()(Obj &obj, typename QExtTypeTrait<Arg1>::Take arg1) const
    {
        return BaseType::operator()(obj, arg1);
    }
};

template<class Return, class Obj>
class QExtMemberFunctor<Return, Obj, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
        : public detail::QExtMemberFunctor0<Return, Obj>
{
public:
    typedef detail::QExtMemberFunctor0<Return, Obj> BaseType;
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtMemberFunctor() {}

    QExtMemberFunctor(FunctionType func) : BaseType(func) {}

    QExtMemberFunctor(const QExtMemberFunctor &other) : BaseType(other.mFuncPtr) {}

    Return operator()(Obj *obj) const
    {
        return BaseType::operator()(obj);
    }

    Return operator()(Obj &obj) const
    {
        return BaseType::operator()(obj);
    }
};

template<class Return,
         class Obj,
         class Arg1 = QExtNil,
         class Arg2 = QExtNil,
         class Arg3 = QExtNil,
         class Arg4 = QExtNil,
         class Arg5 = QExtNil,
         class Arg6 = QExtNil,
         class Arg7 = QExtNil>
class QExtConstMemberFunctor
        : public detail::QExtConstMemberFunctor7<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>
{
    typedef detail::QExtConstMemberFunctor7<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtConstMemberFunctor() {}

    QExtConstMemberFunctor(FunctionType func) : BaseType(func) {}

    QExtConstMemberFunctor(const QExtConstMemberFunctor &other) : BaseType(other.mFuncPtr) {}

    Return operator()(const Obj *obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5,
                      typename QExtTypeTrait<Arg6>::Take arg6,
                      typename QExtTypeTrait<Arg7>::Take arg7) const
    {
        return BaseType::operator()(obj, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    Return operator()(const Obj &obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5,
                      typename QExtTypeTrait<Arg6>::Take arg6,
                      typename QExtTypeTrait<Arg7>::Take arg7) const
    {
        return BaseType::operator()(obj, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
class QExtConstMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, QExtNil>
        : public detail::QExtConstMemberFunctor6<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>
{
    typedef detail::QExtConstMemberFunctor6<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtConstMemberFunctor() {}

    QExtConstMemberFunctor(FunctionType func) : BaseType(func) {}

    QExtConstMemberFunctor(const QExtConstMemberFunctor &other) : BaseType(other.mFuncPtr) {}

    Return operator()(const Obj *obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5,
                      typename QExtTypeTrait<Arg6>::Take arg6) const
    {
        return BaseType::operator()(obj, arg1, arg2, arg3, arg4, arg5, arg6);
    }

    Return operator()(const Obj &obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5,
                      typename QExtTypeTrait<Arg6>::Take arg6) const
    {
        return BaseType::operator()(obj, arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
class QExtConstMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, QExtNil, QExtNil>
        : public detail::QExtConstMemberFunctor5<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5>
{
    typedef detail::QExtConstMemberFunctor5<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtConstMemberFunctor() {}

    QExtConstMemberFunctor(FunctionType func) : BaseType(func) {}

    QExtConstMemberFunctor(const QExtConstMemberFunctor &other) : BaseType(other.mFuncPtr) {}

    Return operator()(const Obj *obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5) const
    {
        return BaseType::operator()(obj, arg1, arg2, arg3, arg4, arg5);
    }

    Return operator()(const Obj &obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5) const
    {
        return BaseType::operator()(obj, arg1, arg2, arg3, arg4, arg5);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4>
class QExtConstMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, QExtNil, QExtNil, QExtNil>
        : public detail::QExtConstMemberFunctor4<Return, Obj, Arg1, Arg2, Arg3, Arg4>
{
    typedef detail::QExtConstMemberFunctor4<Return, Obj, Arg1, Arg2, Arg3, Arg4> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtConstMemberFunctor() {}

    QExtConstMemberFunctor(FunctionType func) : BaseType(func) {}

    QExtConstMemberFunctor(const QExtConstMemberFunctor &other) : BaseType(other.mFuncPtr) {}

    Return operator()(const Obj *obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4) const
    {
        return BaseType::operator()(obj, arg1, arg2, arg3, arg4);
    }

    Return operator()(const Obj &obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4) const
    {
        return BaseType::operator()(obj, arg1, arg2, arg3, arg4);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3>
class QExtConstMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, QExtNil, QExtNil, QExtNil, QExtNil>
        : public detail::QExtConstMemberFunctor3<Return, Obj, Arg1, Arg2, Arg3>
{
    typedef detail::QExtConstMemberFunctor3<Return, Obj, Arg1, Arg2, Arg3> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtConstMemberFunctor() {}

    QExtConstMemberFunctor(FunctionType func) : BaseType(func) {}

    QExtConstMemberFunctor(const QExtConstMemberFunctor &other) : BaseType(other.mFuncPtr) {}

    Return operator()(const Obj *obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3) const
    {
        return BaseType::operator()(obj, arg1, arg2, arg3);
    }

    Return operator()(const Obj &obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3) const
    {
        return BaseType::operator()(obj, arg1, arg2, arg3);
    }
};

template<class Return, class Obj, class Arg1, class Arg2>
class QExtConstMemberFunctor<Return, Obj, Arg1, Arg2, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
        : public detail::QExtConstMemberFunctor2<Return, Obj, Arg1, Arg2>
{
    typedef detail::QExtConstMemberFunctor2<Return, Obj, Arg1, Arg2> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtConstMemberFunctor() {}

    QExtConstMemberFunctor(FunctionType func) : BaseType(func) {}

    QExtConstMemberFunctor(const QExtConstMemberFunctor &other) : BaseType(other.mFuncPtr) {}

    Return operator()(const Obj *obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2) const
    {
        return BaseType::operator()(obj, arg1, arg2);
    }

    Return operator()(const Obj &obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2) const
    {
        return BaseType::operator()(obj, arg1, arg2);
    }
};

template<class Return, class Obj, class Arg1>
class QExtConstMemberFunctor<Return, Obj, Arg1, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
        : public detail::QExtConstMemberFunctor1<Return, Obj, Arg1>
{
    typedef detail::QExtConstMemberFunctor1<Return, Obj, Arg1> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtConstMemberFunctor() {}

    QExtConstMemberFunctor(FunctionType func) : BaseType(func) {}

    QExtConstMemberFunctor(const QExtConstMemberFunctor &other) : BaseType(other.mFuncPtr) {}

    Return operator()(const Obj *obj, typename QExtTypeTrait<Arg1>::Take arg1) const
    {
        return BaseType::operator()(obj, arg1);
    }

    Return operator()(const Obj &obj, typename QExtTypeTrait<Arg1>::Take arg1) const
    {
        return BaseType::operator()(obj, arg1);
    }
};

template<class Return, class Obj>
class QExtConstMemberFunctor<Return, Obj, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
        : public detail::QExtConstMemberFunctor0<Return, Obj>
{
    typedef detail::QExtConstMemberFunctor0<Return, Obj> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtConstMemberFunctor() {}

    QExtConstMemberFunctor(FunctionType func) : BaseType(func) {}

    QExtConstMemberFunctor(const QExtConstMemberFunctor &other) : BaseType(other.mFuncPtr) {}

    Return operator()(const Obj *obj) const
    {
        return BaseType::operator()(obj);
    }

    Return operator()(const Obj &obj) const
    {
        return BaseType::operator()(obj);
    }
};

template<class Return,
         class Obj,
         class Arg1 = QExtNil,
         class Arg2 = QExtNil,
         class Arg3 = QExtNil,
         class Arg4 = QExtNil,
         class Arg5 = QExtNil,
         class Arg6 = QExtNil,
         class Arg7 = QExtNil>
class QExtVolatileMemberFunctor
        : public detail::QExtVolatileMemberFunctor7<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>
{
    typedef detail::QExtVolatileMemberFunctor7<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtVolatileMemberFunctor() {}

    QExtVolatileMemberFunctor(FunctionType func) : BaseType(func) {}

    QExtVolatileMemberFunctor(const QExtVolatileMemberFunctor &other) : BaseType(other.mFuncPtr) {}

    Return operator()(Obj *obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5,
                      typename QExtTypeTrait<Arg6>::Take arg6,
                      typename QExtTypeTrait<Arg7>::Take arg7) const
    {
        return BaseType::operator()(obj, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    Return operator()(Obj &obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5,
                      typename QExtTypeTrait<Arg6>::Take arg6,
                      typename QExtTypeTrait<Arg7>::Take arg7) const
    {
        return BaseType::operator()(obj, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
class QExtVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, QExtNil>
        : public detail::QExtVolatileMemberFunctor6<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>
{
    typedef detail::QExtVolatileMemberFunctor6<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtVolatileMemberFunctor() {}

    QExtVolatileMemberFunctor(FunctionType func) : BaseType(func) {}

    QExtVolatileMemberFunctor(const QExtVolatileMemberFunctor &other) : BaseType(other.mFuncPtr) {}

    Return operator()(Obj *obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5,
                      typename QExtTypeTrait<Arg6>::Take arg6) const
    {
        return BaseType::operator()(obj, arg1, arg2, arg3, arg4, arg5, arg6);
    }

    Return operator()(Obj &obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5,
                      typename QExtTypeTrait<Arg6>::Take arg6) const
    {
        return BaseType::operator()(obj, arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
class QExtVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, QExtNil, QExtNil>
        : public detail::QExtVolatileMemberFunctor5<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5>
{
    typedef detail::QExtVolatileMemberFunctor5<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtVolatileMemberFunctor() {}

    QExtVolatileMemberFunctor(FunctionType func) : BaseType(func) {}

    QExtVolatileMemberFunctor(const QExtVolatileMemberFunctor &other) : BaseType(other.mFuncPtr) {}

    Return operator()(Obj *obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5) const
    {
        return BaseType::operator()(obj, arg1, arg2, arg3, arg4, arg5);
    }

    Return operator()(Obj &obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5) const
    {
        return BaseType::operator()(obj, arg1, arg2, arg3, arg4, arg5);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4>
class QExtVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, QExtNil, QExtNil, QExtNil>
        : public detail::QExtVolatileMemberFunctor4<Return, Obj, Arg1, Arg2, Arg3, Arg4>
{
    typedef detail::QExtVolatileMemberFunctor4<Return, Obj, Arg1, Arg2, Arg3, Arg4> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtVolatileMemberFunctor() {}

    QExtVolatileMemberFunctor(FunctionType func) : BaseType(func) {}

    QExtVolatileMemberFunctor(const QExtVolatileMemberFunctor &other) : BaseType(other.mFuncPtr) {}

    Return operator()(Obj *obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4) const
    {
        return BaseType::operator()(obj, arg1, arg2, arg3, arg4);
    }

    Return operator()(Obj &obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4) const
    {
        return BaseType::operator()(obj, arg1, arg2, arg3, arg4);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3>
class QExtVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, QExtNil, QExtNil, QExtNil, QExtNil>
        : public detail::QExtVolatileMemberFunctor3<Return, Obj, Arg1, Arg2, Arg3>
{
    typedef detail::QExtVolatileMemberFunctor3<Return, Obj, Arg1, Arg2, Arg3> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtVolatileMemberFunctor() {}

    QExtVolatileMemberFunctor(FunctionType func) : BaseType(func) {}

    QExtVolatileMemberFunctor(const QExtVolatileMemberFunctor &other) : BaseType(other.mFuncPtr) {}

    Return operator()(Obj *obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3) const
    {
        return BaseType::operator()(obj, arg1, arg2, arg3);
    }

    Return operator()(Obj &obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3) const
    {
        return BaseType::operator()(obj, arg1, arg2, arg3);
    }
};

template<class Return, class Obj, class Arg1, class Arg2>
class QExtVolatileMemberFunctor<Return, Obj, Arg1, Arg2, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
        : public detail::QExtVolatileMemberFunctor2<Return, Obj, Arg1, Arg2>
{
    typedef detail::QExtVolatileMemberFunctor2<Return, Obj, Arg1, Arg2> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtVolatileMemberFunctor() {}

    QExtVolatileMemberFunctor(FunctionType func) : BaseType(func) {}

    QExtVolatileMemberFunctor(const QExtVolatileMemberFunctor &other) : BaseType(other.mFuncPtr) {}

    Return operator()(Obj *obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2) const
    {
        return BaseType::operator()(obj, arg1, arg2);
    }

    Return operator()(Obj &obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2) const
    {
        return BaseType::operator()(obj, arg1, arg2);
    }
};

template<class Return, class Obj, class Arg1>
class QExtVolatileMemberFunctor<Return, Obj, Arg1, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
        : public detail::QExtVolatileMemberFunctor1<Return, Obj, Arg1>
{
    typedef detail::QExtVolatileMemberFunctor1<Return, Obj, Arg1> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtVolatileMemberFunctor() {}

    QExtVolatileMemberFunctor(FunctionType func) : BaseType(func) {}

    QExtVolatileMemberFunctor(const QExtVolatileMemberFunctor &other) : BaseType(other.mFuncPtr) {}

    Return operator()(Obj *obj, typename QExtTypeTrait<Arg1>::Take arg1) const
    {
        return BaseType::operator()(obj, arg1);
    }

    Return operator()(Obj &obj, typename QExtTypeTrait<Arg1>::Take arg1) const
    {
        return BaseType::operator()(obj, arg1);
    }
};

template<class Return, class Obj>
class QExtVolatileMemberFunctor<Return, Obj, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
        : public detail::QExtVolatileMemberFunctor0<Return, Obj>
{
    typedef detail::QExtVolatileMemberFunctor0<Return, Obj> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtVolatileMemberFunctor() {}

    QExtVolatileMemberFunctor(FunctionType func) : BaseType(func) {}

    QExtVolatileMemberFunctor(const QExtVolatileMemberFunctor &other) : BaseType(other.mFuncPtr) {}

    Return operator()(Obj *obj) const
    {
        return BaseType::operator()(obj);
    }

    Return operator()(Obj &obj) const
    {
        return BaseType::operator()(obj);
    }
};

template<class Return,
         class Obj,
         class Arg1 = QExtNil,
         class Arg2 = QExtNil,
         class Arg3 = QExtNil,
         class Arg4 = QExtNil,
         class Arg5 = QExtNil,
         class Arg6 = QExtNil,
         class Arg7 = QExtNil>
class QExtConstVolatileMemberFunctor
        : public detail::QExtConstVolatileMemberFunctor7<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>
{
    typedef detail::QExtConstVolatileMemberFunctor7<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtConstVolatileMemberFunctor() {}

    QExtConstVolatileMemberFunctor(FunctionType func) : BaseType(func) {}

    QExtConstVolatileMemberFunctor(const QExtConstVolatileMemberFunctor &other) : BaseType(other.mFuncPtr) {}

    Return operator()(const Obj *obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5,
                      typename QExtTypeTrait<Arg6>::Take arg6,
                      typename QExtTypeTrait<Arg7>::Take arg7) const
    {
        return BaseType::operator()(obj, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    Return operator()(const Obj &obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5,
                      typename QExtTypeTrait<Arg6>::Take arg6,
                      typename QExtTypeTrait<Arg7>::Take arg7) const
    {
        return BaseType::operator()(obj, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
class QExtConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, QExtNil>
        : public detail::QExtConstVolatileMemberFunctor6<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>
{
    typedef detail::QExtConstVolatileMemberFunctor6<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtConstVolatileMemberFunctor() {}

    QExtConstVolatileMemberFunctor(FunctionType func) : BaseType(func) {}

    QExtConstVolatileMemberFunctor(const QExtConstVolatileMemberFunctor &other) : BaseType(other.mFuncPtr) {}

    Return operator()(const Obj *obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5,
                      typename QExtTypeTrait<Arg6>::Take arg6) const
    {
        return BaseType::operator()(obj, arg1, arg2, arg3, arg4, arg5, arg6);
    }

    Return operator()(const Obj &obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5,
                      typename QExtTypeTrait<Arg6>::Take arg6) const
    {
        return BaseType::operator()(obj, arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
class QExtConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, QExtNil, QExtNil>
        : public detail::QExtConstVolatileMemberFunctor5<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5>
{
    typedef detail::QExtConstVolatileMemberFunctor5<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtConstVolatileMemberFunctor() {}

    QExtConstVolatileMemberFunctor(FunctionType func) : BaseType(func) {}

    QExtConstVolatileMemberFunctor(const QExtConstVolatileMemberFunctor &other) : BaseType(other.mFuncPtr) {}

    Return operator()(const Obj *obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5) const
    {
        return BaseType::operator()(obj, arg1, arg2, arg3, arg4, arg5);
    }

    Return operator()(const Obj &obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5) const
    {
        return BaseType::operator()(obj, arg1, arg2, arg3, arg4, arg5);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4>
class QExtConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, QExtNil, QExtNil, QExtNil>
        : public detail::QExtConstVolatileMemberFunctor4<Return, Obj, Arg1, Arg2, Arg3, Arg4>
{
    typedef detail::QExtConstVolatileMemberFunctor4<Return, Obj, Arg1, Arg2, Arg3, Arg4> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtConstVolatileMemberFunctor() {}

    QExtConstVolatileMemberFunctor(FunctionType func) : BaseType(func) {}

    QExtConstVolatileMemberFunctor(const QExtConstVolatileMemberFunctor &other) : BaseType(other.mFuncPtr) {}

    Return operator()(const Obj *obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4) const
    {
        return BaseType::operator()(obj, arg1, arg2, arg3, arg4);
    }

    Return operator()(const Obj &obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4) const
    {
        return BaseType::operator()(obj, arg1, arg2, arg3, arg4);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3>
class QExtConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, QExtNil, QExtNil, QExtNil, QExtNil>
        : public detail::QExtConstVolatileMemberFunctor3<Return, Obj, Arg1, Arg2, Arg3>
{
    typedef detail::QExtConstVolatileMemberFunctor3<Return, Obj, Arg1, Arg2, Arg3> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtConstVolatileMemberFunctor() {}

    QExtConstVolatileMemberFunctor(FunctionType func) : BaseType(func) {}

    QExtConstVolatileMemberFunctor(const QExtConstVolatileMemberFunctor &other) : BaseType(other.mFuncPtr) {}

    Return operator()(const Obj *obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3) const
    {
        return BaseType::operator()(obj, arg1, arg2, arg3);
    }

    Return operator()(const Obj &obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3) const
    {
        return BaseType::operator()(obj, arg1, arg2, arg3);
    }
};

template<class Return, class Obj, class Arg1, class Arg2>
class QExtConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
        : public detail::QExtConstVolatileMemberFunctor2<Return, Obj, Arg1, Arg2>
{
    typedef detail::QExtConstVolatileMemberFunctor2<Return, Obj, Arg1, Arg2> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtConstVolatileMemberFunctor() {}

    QExtConstVolatileMemberFunctor(FunctionType func) : BaseType(func) {}

    QExtConstVolatileMemberFunctor(const QExtConstVolatileMemberFunctor &other) : BaseType(other.mFuncPtr) {}

    Return operator()(const Obj *obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2) const
    {
        return BaseType::operator()(obj, arg1, arg2);
    }

    Return operator()(const Obj &obj,
                      typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2) const
    {
        return BaseType::operator()(obj, arg1, arg2);
    }
};

template<class Return, class Obj, class Arg1>
class QExtConstVolatileMemberFunctor<Return, Obj, Arg1, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
        : public detail::QExtConstVolatileMemberFunctor1<Return, Obj, Arg1>
{
    typedef detail::QExtConstVolatileMemberFunctor1<Return, Obj, Arg1> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtConstVolatileMemberFunctor() {}

    QExtConstVolatileMemberFunctor(FunctionType func) : BaseType(func) {}

    QExtConstVolatileMemberFunctor(const QExtConstVolatileMemberFunctor &other) : BaseType(other.mFuncPtr) {}

    Return operator()(const Obj *obj, typename QExtTypeTrait<Arg1>::Take arg1) const
    {
        return BaseType::operator()(obj, arg1);
    }

    Return operator()(const Obj &obj, typename QExtTypeTrait<Arg1>::Take arg1) const
    {
        return BaseType::operator()(obj, arg1);
    }
};

template<class Return, class Obj>
class QExtConstVolatileMemberFunctor<Return, Obj, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
        : public detail::QExtConstVolatileMemberFunctor0<Return, Obj>
{
    typedef detail::QExtConstVolatileMemberFunctor0<Return, Obj> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtConstVolatileMemberFunctor() {}

    QExtConstVolatileMemberFunctor(FunctionType func) : BaseType(func) {}

    QExtConstVolatileMemberFunctor(const QExtConstVolatileMemberFunctor &other) : BaseType(other.mFuncPtr) {}

    Return operator()(const Obj *obj) const
    {
        return BaseType::operator()(obj);
    }

    Return operator()(const Obj &obj) const
    {
        return BaseType::operator()(obj);
    }
};

template<class Return,
         class Obj,
         class Arg1 = QExtNil,
         class Arg2 = QExtNil,
         class Arg3 = QExtNil,
         class Arg4 = QExtNil,
         class Arg5 = QExtNil,
         class Arg6 = QExtNil,
         class Arg7 = QExtNil>
class QExtBoundMemberFunctor
        : public detail::QExtBoundMemberFunctor7<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>
{
    typedef detail::QExtBoundMemberFunctor7<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtBoundMemberFunctor(Obj *obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundMemberFunctor(Obj &obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundMemberFunctor(const QExtBoundMemberFunctor &other) : BaseType(other) {}

    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5,
                      typename QExtTypeTrait<Arg6>::Take arg6,
                      typename QExtTypeTrait<Arg7>::Take arg7) const
    {
        return BaseType::operator()(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
struct QExtVisitor<QExtBoundMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7> >
{
    typedef QExtBoundMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7> TargetType;
    template<typename Action>
    static void doVisitEach(const Action &action, const TargetType &target)
    {
        qextVisitEach(action, target.mObj);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
class QExtBoundMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, QExtNil>
        : public detail::QExtBoundMemberFunctor6<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>
{
    typedef detail::QExtBoundMemberFunctor6<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtBoundMemberFunctor(Obj *obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundMemberFunctor(Obj &obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundMemberFunctor(const QExtBoundMemberFunctor &other) : BaseType(other) {}

    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5,
                      typename QExtTypeTrait<Arg6>::Take arg6) const
    {
        return BaseType::operator()(arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
struct QExtVisitor<QExtBoundMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6> >
{
    typedef QExtBoundMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6> TargetType;
    template<typename Action>
    static void doVisitEach(const Action &action, const TargetType &target)
    {
        qextVisitEach(action, target.mObj);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
class QExtBoundMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, QExtNil, QExtNil>
        : public detail::QExtBoundMemberFunctor5<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5>
{
    typedef detail::QExtBoundMemberFunctor5<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtBoundMemberFunctor(Obj *obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundMemberFunctor(Obj &obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundMemberFunctor(const QExtBoundMemberFunctor &other) : BaseType(other) {}

    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5) const
    {
        return BaseType::operator()(arg1, arg2, arg3, arg4, arg5);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
struct QExtVisitor<QExtBoundMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5> >
{
    typedef QExtBoundMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5> TargetType;
    template<typename Action>
    static void doVisitEach(const Action &action, const TargetType &target)
    {
        qextVisitEach(action, target.mObj);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4>
class QExtBoundMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, QExtNil, QExtNil, QExtNil>
        : public detail::QExtBoundMemberFunctor4<Return, Obj, Arg1, Arg2, Arg3, Arg4>
{
    typedef detail::QExtBoundMemberFunctor4<Return, Obj, Arg1, Arg2, Arg3, Arg4> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtBoundMemberFunctor(Obj *obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundMemberFunctor(Obj &obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundMemberFunctor(const QExtBoundMemberFunctor &other) : BaseType(other) {}

    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4) const
    {
        return BaseType::operator()(arg1, arg2, arg3, arg4);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4>
struct QExtVisitor<QExtBoundMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4> >
{
    typedef QExtBoundMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4> TargetType;
    template<typename Action>
    static void doVisitEach(const Action &action, const TargetType &target)
    {
        qextVisitEach(action, target.mObj);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3>
class QExtBoundMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, QExtNil, QExtNil, QExtNil, QExtNil>
        : public detail::QExtBoundMemberFunctor3<Return, Obj, Arg1, Arg2, Arg3>
{
    typedef detail::QExtBoundMemberFunctor3<Return, Obj, Arg1, Arg2, Arg3> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtBoundMemberFunctor(Obj *obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundMemberFunctor(Obj &obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundMemberFunctor(const QExtBoundMemberFunctor &other) : BaseType(other) {}

    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3) const
    {
        return BaseType::operator()(arg1, arg2, arg3);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3>
struct QExtVisitor<QExtBoundMemberFunctor<Return, Obj, Arg1, Arg2, Arg3> >
{
    typedef QExtBoundMemberFunctor<Return, Obj, Arg1, Arg2, Arg3> TargetType;
    template<typename Action>
    static void doVisitEach(const Action &action, const TargetType &target)
    {
        qextVisitEach(action, target.mObj);
    }
};

template<class Return, class Obj, class Arg1, class Arg2>
class QExtBoundMemberFunctor<Return, Obj, Arg1, Arg2, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
        : public detail::QExtBoundMemberFunctor2<Return, Obj, Arg1, Arg2>
{
    typedef detail::QExtBoundMemberFunctor2<Return, Obj, Arg1, Arg2> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtBoundMemberFunctor(Obj *obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundMemberFunctor(Obj &obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundMemberFunctor(const QExtBoundMemberFunctor &other) : BaseType(other) {}

    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1, typename QExtTypeTrait<Arg2>::Take arg2) const
    {
        return BaseType::operator()(arg1, arg2);
    }
};

template<class Return, class Obj, class Arg1, class Arg2>
struct QExtVisitor<QExtBoundMemberFunctor<Return, Obj, Arg1, Arg2> >
{
    typedef QExtBoundMemberFunctor<Return, Obj, Arg1, Arg2> TargetType;
    template<typename Action>
    static void doVisitEach(const Action &action, const TargetType &target)
    {
        qextVisitEach(action, target.mObj);
    }
};

template<class Return, class Obj, class Arg1>
class QExtBoundMemberFunctor<Return, Obj, Arg1, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
        : public detail::QExtBoundMemberFunctor1<Return, Obj, Arg1>
{
    typedef detail::QExtBoundMemberFunctor1<Return, Obj, Arg1> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtBoundMemberFunctor(Obj *obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundMemberFunctor(Obj &obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundMemberFunctor(const QExtBoundMemberFunctor &other) : BaseType(other) {}

    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1) const
    {
        return BaseType::operator()(arg1);
    }
};

template<class Return, class Obj, class Arg1>
struct QExtVisitor<QExtBoundMemberFunctor<Return, Obj, Arg1> >
{
    typedef QExtBoundMemberFunctor<Return, Obj, Arg1> TargetType;
    template<typename Action>
    static void doVisitEach(const Action &action, const TargetType &target)
    {
        qextVisitEach(action, target.mObj);
    }
};

template<class Return, class Obj>
class QExtBoundMemberFunctor<Return, Obj, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
        : public detail::QExtBoundMemberFunctor0<Return, Obj>
{
    typedef detail::QExtBoundMemberFunctor0<Return, Obj> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtBoundMemberFunctor(Obj *obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundMemberFunctor(Obj &obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundMemberFunctor(const QExtBoundMemberFunctor &other) : BaseType(other) {}

    Return operator()() const
    {
        return BaseType::operator()();
    }
};

template<class Return, class Obj>
struct QExtVisitor<QExtBoundMemberFunctor<Return, Obj> >
{
    typedef QExtBoundMemberFunctor<Return, Obj> TargetType;
    template<typename Action>
    static void doVisitEach(const Action &action, const TargetType &target)
    {
        qextVisitEach(action, target.mObj);
    }
};

template<class Return,
         class Obj,
         class Arg1 = QExtNil,
         class Arg2 = QExtNil,
         class Arg3 = QExtNil,
         class Arg4 = QExtNil,
         class Arg5 = QExtNil,
         class Arg6 = QExtNil,
         class Arg7 = QExtNil>
class QExtBoundConstMemberFunctor
        : public detail::QExtBoundConstMemberFunctor7<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>
{
    typedef detail::QExtBoundConstMemberFunctor7<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtBoundConstMemberFunctor(const Obj *obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundConstMemberFunctor(const Obj &obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundConstMemberFunctor(const QExtBoundConstMemberFunctor &other) : BaseType(other) {}

    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5,
                      typename QExtTypeTrait<Arg6>::Take arg6,
                      typename QExtTypeTrait<Arg7>::Take arg7) const
    {
        return BaseType::operator()(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
struct QExtVisitor<QExtBoundConstMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7> >
{
    typedef QExtBoundConstMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7> TargetType;
    template<typename Action>
    static void doVisitEach(const Action &action, const TargetType &target)
    {
        qextVisitEach(action, target.mObj);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
class QExtBoundConstMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, QExtNil>
        : public detail::QExtBoundConstMemberFunctor6<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>
{
    typedef detail::QExtBoundConstMemberFunctor6<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtBoundConstMemberFunctor(const Obj *obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundConstMemberFunctor(const Obj &obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundConstMemberFunctor(const QExtBoundConstMemberFunctor &other) : BaseType(other) {}

    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5,
                      typename QExtTypeTrait<Arg6>::Take arg6) const
    {
        return BaseType::operator()(arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
struct QExtVisitor<QExtBoundConstMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6> >
{
    typedef QExtBoundConstMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6> TargetType;
    template<typename Action>
    static void doVisitEach(const Action &action, const TargetType &target)
    {
        qextVisitEach(action, target.mObj);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
class QExtBoundConstMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, QExtNil, QExtNil>
        : public detail::QExtBoundConstMemberFunctor5<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5>
{
    typedef detail::QExtBoundConstMemberFunctor5<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtBoundConstMemberFunctor(const Obj *obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundConstMemberFunctor(const Obj &obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundConstMemberFunctor(const QExtBoundConstMemberFunctor &other) : BaseType(other) {}

    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5) const
    {
        return BaseType::operator()(arg1, arg2, arg3, arg4, arg5);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
struct QExtVisitor<QExtBoundConstMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5> >
{
    typedef QExtBoundConstMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5> TargetType;
    template<typename Action>
    static void doVisitEach(const Action &action, const TargetType &target)
    {
        qextVisitEach(action, target.mObj);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4>
class QExtBoundConstMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, QExtNil, QExtNil, QExtNil>
        : public detail::QExtBoundConstMemberFunctor4<Return, Obj, Arg1, Arg2, Arg3, Arg4>
{
    typedef detail::QExtBoundConstMemberFunctor4<Return, Obj, Arg1, Arg2, Arg3, Arg4> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtBoundConstMemberFunctor(const Obj *obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundConstMemberFunctor(const Obj &obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundConstMemberFunctor(const QExtBoundConstMemberFunctor &other) : BaseType(other) {}

    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4) const
    {
        return BaseType::operator()(arg1, arg2, arg3, arg4);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4>
struct QExtVisitor<QExtBoundConstMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4> >
{
    typedef QExtBoundConstMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4> TargetType;
    template<typename Action>
    static void doVisitEach(const Action &action, const TargetType &target)
    {
        qextVisitEach(action, target.mObj);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3>
class QExtBoundConstMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, QExtNil, QExtNil, QExtNil, QExtNil>
        : public detail::QExtBoundConstMemberFunctor3<Return, Obj, Arg1, Arg2, Arg3>
{
    typedef detail::QExtBoundConstMemberFunctor3<Return, Obj, Arg1, Arg2, Arg3> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtBoundConstMemberFunctor(const Obj *obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundConstMemberFunctor(const Obj &obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundConstMemberFunctor(const QExtBoundConstMemberFunctor &other) : BaseType(other) {}

    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3) const
    {
        return BaseType::operator()(arg1, arg2, arg3);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3>
struct QExtVisitor<QExtBoundConstMemberFunctor<Return, Obj, Arg1, Arg2, Arg3> >
{
    typedef QExtBoundConstMemberFunctor<Return, Obj, Arg1, Arg2, Arg3> TargetType;
    template<typename Action>
    static void doVisitEach(const Action &action, const TargetType &target)
    {
        qextVisitEach(action, target.mObj);
    }
};

template<class Return, class Obj, class Arg1, class Arg2>
class QExtBoundConstMemberFunctor<Return, Obj, Arg1, Arg2, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
        : public detail::QExtBoundConstMemberFunctor2<Return, Obj, Arg1, Arg2>
{
    typedef detail::QExtBoundConstMemberFunctor2<Return, Obj, Arg1, Arg2> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtBoundConstMemberFunctor(const Obj *obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundConstMemberFunctor(const Obj &obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundConstMemberFunctor(const QExtBoundConstMemberFunctor &other) : BaseType(other) {}

    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1, typename QExtTypeTrait<Arg2>::Take arg2) const
    {
        return BaseType::operator()(arg1, arg2);
    }
};

template<class Return, class Obj, class Arg1, class Arg2>
struct QExtVisitor<QExtBoundConstMemberFunctor<Return, Obj, Arg1, Arg2> >
{
    typedef QExtBoundConstMemberFunctor<Return, Obj, Arg1, Arg2> TargetType;
    template<typename Action>
    static void doVisitEach(const Action &action, const TargetType &target)
    {
        qextVisitEach(action, target.mObj);
    }
};

template<class Return, class Obj, class Arg1>
class QExtBoundConstMemberFunctor<Return, Obj, Arg1, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
        : public detail::QExtBoundConstMemberFunctor1<Return, Obj, Arg1>
{
    typedef detail::QExtBoundConstMemberFunctor1<Return, Obj, Arg1> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtBoundConstMemberFunctor(const Obj *obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundConstMemberFunctor(const Obj &obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundConstMemberFunctor(const QExtBoundConstMemberFunctor &other) : BaseType(other) {}

    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1) const
    {
        return BaseType::operator()(arg1);
    }
};

template<class Return, class Obj, class Arg1>
struct QExtVisitor<QExtBoundConstMemberFunctor<Return, Obj, Arg1> >
{
    typedef QExtBoundConstMemberFunctor<Return, Obj, Arg1> TargetType;
    template<typename Action>
    static void doVisitEach(const Action &action, const TargetType &target)
    {
        qextVisitEach(action, target.mObj);
    }
};

template<class Return, class Obj>
class QExtBoundConstMemberFunctor<Return, Obj, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
        : public detail::QExtBoundConstMemberFunctor0<Return, Obj>
{
    typedef detail::QExtBoundConstMemberFunctor0<Return, Obj> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtBoundConstMemberFunctor(const Obj *obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundConstMemberFunctor(const Obj &obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundConstMemberFunctor(const QExtBoundConstMemberFunctor &other) : BaseType(other) {}

    Return operator()() const
    {
        return BaseType::operator()();
    }
};

template<class Return, class Obj>
struct QExtVisitor<QExtBoundConstMemberFunctor<Return, Obj> >
{
    template<typename Action>
    static void doVisitEach(const Action &action, const QExtBoundConstMemberFunctor<Return, Obj> &target)
    {
        qextVisitEach(action, target.mObj);
    }
};

template<class Return,
         class Obj,
         class Arg1 = QExtNil,
         class Arg2 = QExtNil,
         class Arg3 = QExtNil,
         class Arg4 = QExtNil,
         class Arg5 = QExtNil,
         class Arg6 = QExtNil,
         class Arg7 = QExtNil>
class QExtBoundVolatileMemberFunctor
        : public detail::QExtBoundVolatileMemberFunctor7<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>
{
    typedef detail::QExtBoundVolatileMemberFunctor7<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtBoundVolatileMemberFunctor(Obj *obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundVolatileMemberFunctor(Obj &obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundVolatileMemberFunctor(const QExtBoundVolatileMemberFunctor &other) : BaseType(other) {}

    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5,
                      typename QExtTypeTrait<Arg6>::Take arg6,
                      typename QExtTypeTrait<Arg7>::Take arg7) const
    {
        return BaseType::operator()(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
struct QExtVisitor<QExtBoundVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7> >
{
    typedef QExtBoundVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7> TargetType;
    template<typename Action>
    static void doVisitEach(const Action &action, const TargetType &target)
    {
        qextVisitEach(action, target.mObj);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
class QExtBoundVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, QExtNil>
        : public detail::QExtBoundVolatileMemberFunctor6<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>
{
    typedef detail::QExtBoundVolatileMemberFunctor6<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtBoundVolatileMemberFunctor(Obj *obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundVolatileMemberFunctor(Obj &obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundVolatileMemberFunctor(const QExtBoundVolatileMemberFunctor &other) : BaseType(other) {}

    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5,
                      typename QExtTypeTrait<Arg6>::Take arg6) const
    {
        return BaseType::operator()(arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
struct QExtVisitor<QExtBoundVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6> >
{
    typedef QExtBoundVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6> TargetType;
    template<typename Action>
    static void doVisitEach(const Action &action, const TargetType &target)
    {
        qextVisitEach(action, target.mObj);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
class QExtBoundVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, QExtNil, QExtNil>
        : public detail::QExtBoundVolatileMemberFunctor5<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5>
{
    typedef detail::QExtBoundVolatileMemberFunctor5<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtBoundVolatileMemberFunctor(Obj *obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundVolatileMemberFunctor(Obj &obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundVolatileMemberFunctor(const QExtBoundVolatileMemberFunctor &other) : BaseType(other) {}

    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5) const
    {
        return BaseType::operator()(arg1, arg2, arg3, arg4, arg5);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
struct QExtVisitor<QExtBoundVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5> >
{
    typedef QExtBoundVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5> TargetType;
    template<typename Action>
    static void doVisitEach(const Action &action, const TargetType &target)
    {
        qextVisitEach(action, target.mObj);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4>
class QExtBoundVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, QExtNil, QExtNil, QExtNil>
        : public detail::QExtBoundVolatileMemberFunctor4<Return, Obj, Arg1, Arg2, Arg3, Arg4>
{
    typedef detail::QExtBoundVolatileMemberFunctor4<Return, Obj, Arg1, Arg2, Arg3, Arg4> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtBoundVolatileMemberFunctor(Obj *obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundVolatileMemberFunctor(Obj &obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundVolatileMemberFunctor(const QExtBoundVolatileMemberFunctor &other) : BaseType(other) {}

    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4) const
    {
        return BaseType::operator()(arg1, arg2, arg3, arg4);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4>
struct QExtVisitor<QExtBoundVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4> >
{
    typedef QExtBoundVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4> TargetType;
    template<typename Action>
    static void doVisitEach(const Action &action, const TargetType &target)
    {
        qextVisitEach(action, target.mObj);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3>
class QExtBoundVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, QExtNil, QExtNil, QExtNil, QExtNil>
        : public detail::QExtBoundVolatileMemberFunctor3<Return, Obj, Arg1, Arg2, Arg3>
{
    typedef detail::QExtBoundVolatileMemberFunctor3<Return, Obj, Arg1, Arg2, Arg3> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtBoundVolatileMemberFunctor(Obj *obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundVolatileMemberFunctor(Obj &obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundVolatileMemberFunctor(const QExtBoundVolatileMemberFunctor &other) : BaseType(other) {}

    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3) const
    {
        return BaseType::operator()(arg1, arg2, arg3);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3>
struct QExtVisitor<QExtBoundVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3> >
{
    typedef QExtBoundVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3> TargetType;
    template<typename Action>
    static void doVisitEach(const Action &action, const TargetType &target)
    {
        qextVisitEach(action, target.mObj);
    }
};

template<class Return, class Obj, class Arg1, class Arg2>
class QExtBoundVolatileMemberFunctor<Return, Obj, Arg1, Arg2, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
        : public detail::QExtBoundVolatileMemberFunctor2<Return, Obj, Arg1, Arg2>
{
    typedef detail::QExtBoundVolatileMemberFunctor2<Return, Obj, Arg1, Arg2> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtBoundVolatileMemberFunctor(Obj *obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundVolatileMemberFunctor(Obj &obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundVolatileMemberFunctor(const QExtBoundVolatileMemberFunctor &other) : BaseType(other) {}

    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1, typename QExtTypeTrait<Arg2>::Take arg2) const
    {
        return BaseType::operator()(arg1, arg2);
    }
};

template<class Return, class Obj, class Arg1, class Arg2>
struct QExtVisitor<QExtBoundVolatileMemberFunctor<Return, Obj, Arg1, Arg2> >
{
    typedef QExtBoundVolatileMemberFunctor<Return, Obj, Arg1, Arg2> TargetType;
    template<typename Action>
    static void doVisitEach(const Action &action, const TargetType &target)
    {
        qextVisitEach(action, target.mObj);
    }
};

template<class Return, class Obj, class Arg1>
class QExtBoundVolatileMemberFunctor<Return, Obj, Arg1, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
        : public detail::QExtBoundVolatileMemberFunctor1<Return, Obj, Arg1>
{
    typedef detail::QExtBoundVolatileMemberFunctor1<Return, Obj, Arg1> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtBoundVolatileMemberFunctor(Obj *obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundVolatileMemberFunctor(Obj &obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundVolatileMemberFunctor(const QExtBoundVolatileMemberFunctor &other) : BaseType(other) {}

    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1) const
    {
        return BaseType::operator()(arg1);
    }
};

template<class Return, class Obj, class Arg1>
struct QExtVisitor<QExtBoundVolatileMemberFunctor<Return, Obj, Arg1> >
{
    typedef QExtBoundVolatileMemberFunctor<Return, Obj, Arg1> TargetType;
    template<typename Action>
    static void doVisitEach(const Action &action, const TargetType &target)
    {
        qextVisitEach(action, target.mObj);
    }
};

template<class Return, class Obj>
class QExtBoundVolatileMemberFunctor<Return, Obj, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
        : public detail::QExtBoundVolatileMemberFunctor0<Return, Obj>
{
    typedef detail::QExtBoundVolatileMemberFunctor0<Return, Obj> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtBoundVolatileMemberFunctor(Obj *obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundVolatileMemberFunctor(Obj &obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundVolatileMemberFunctor(const QExtBoundVolatileMemberFunctor &other) : BaseType(other) {}

    Return operator()() const
    {
        return BaseType::operator()();
    }
};

template<class Return, class Obj>
struct QExtVisitor<QExtBoundVolatileMemberFunctor<Return, Obj> >
{
    typedef QExtBoundVolatileMemberFunctor<Return, Obj> TargetType;
    template<typename Action>
    static void doVisitEach(const Action &action, const TargetType &target)
    {
        qextVisitEach(action, target.mObj);
    }
};

template<class Return,
         class Obj,
         class Arg1 = QExtNil,
         class Arg2 = QExtNil,
         class Arg3 = QExtNil,
         class Arg4 = QExtNil,
         class Arg5 = QExtNil,
         class Arg6 = QExtNil,
         class Arg7 = QExtNil>
class QExtBoundConstVolatileMemberFunctor
        : public detail::QExtBoundConstVolatileMemberFunctor7<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>
{
    typedef detail::QExtBoundConstVolatileMemberFunctor7<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtBoundConstVolatileMemberFunctor(const Obj *obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundConstVolatileMemberFunctor(const Obj &obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundConstVolatileMemberFunctor(const QExtBoundConstVolatileMemberFunctor &other) : BaseType(other) {}

    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5,
                      typename QExtTypeTrait<Arg6>::Take arg6,
                      typename QExtTypeTrait<Arg7>::Take arg7) const
    {
        return BaseType::operator()(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
struct QExtVisitor<QExtBoundConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7> >
{
    typedef QExtBoundConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7> TargetType;
    template<typename Action>
    static void doVisitEach(const Action &action, const TargetType &target)
    {
        qextVisitEach(action, target.mObj);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
class QExtBoundConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, QExtNil>
        : public detail::QExtBoundConstVolatileMemberFunctor6<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>
{
    typedef detail::QExtBoundConstVolatileMemberFunctor6<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtBoundConstVolatileMemberFunctor(const Obj *obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundConstVolatileMemberFunctor(const Obj &obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundConstVolatileMemberFunctor(const QExtBoundConstVolatileMemberFunctor &other) : BaseType(other) {}

    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5,
                      typename QExtTypeTrait<Arg6>::Take arg6) const
    {
        return BaseType::operator()(arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
struct QExtVisitor<QExtBoundConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6> >
{
    typedef QExtBoundConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6> TargetType;
    template<typename Action>
    static void doVisitEach(const Action &action, const TargetType &target)
    {
        qextVisitEach(action, target.mObj);
    }
};

template<class Return,
         class Obj,
         class Arg1,
         class Arg2,
         class Arg3,
         class Arg4,
         class Arg5>
class QExtBoundConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, QExtNil, QExtNil>
        : public detail::QExtBoundConstVolatileMemberFunctor5<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5>
{
    typedef detail::QExtBoundConstVolatileMemberFunctor5<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtBoundConstVolatileMemberFunctor(const Obj *obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundConstVolatileMemberFunctor(const Obj &obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundConstVolatileMemberFunctor(const QExtBoundConstVolatileMemberFunctor &other) : BaseType(other) {}

    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4,
                      typename QExtTypeTrait<Arg5>::Take arg5) const
    {
        return BaseType::operator()(arg1, arg2, arg3, arg4, arg5);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
struct QExtVisitor<QExtBoundConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5> >
{
    typedef QExtBoundConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5> TargetType;
    template<typename Action>
    static void doVisitEach(const Action &action, const TargetType &target)
    {
        qextVisitEach(action, target.mObj);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4>
class QExtBoundConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, QExtNil, QExtNil, QExtNil>
        : public detail::QExtBoundConstVolatileMemberFunctor4<Return, Obj, Arg1, Arg2, Arg3, Arg4>
{
    typedef detail::QExtBoundConstVolatileMemberFunctor4<Return, Obj, Arg1, Arg2, Arg3, Arg4> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtBoundConstVolatileMemberFunctor(const Obj *obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundConstVolatileMemberFunctor(const Obj &obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundConstVolatileMemberFunctor(const QExtBoundConstVolatileMemberFunctor &other) : BaseType(other) {}

    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3,
                      typename QExtTypeTrait<Arg4>::Take arg4) const
    {
        return BaseType::operator()(arg1, arg2, arg3, arg4);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4>
struct QExtVisitor<QExtBoundConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4> >
{
    typedef QExtBoundConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4> TargetType;
    template<typename Action>
    static void doVisitEach(const Action &action, const TargetType &target)
    {
        qextVisitEach(action, target.mObj);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3>
class QExtBoundConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, QExtNil, QExtNil, QExtNil, QExtNil>
        : public detail::QExtBoundConstVolatileMemberFunctor3<Return, Obj, Arg1, Arg2, Arg3>
{
    typedef detail::QExtBoundConstVolatileMemberFunctor3<Return, Obj, Arg1, Arg2, Arg3> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtBoundConstVolatileMemberFunctor(const Obj *obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundConstVolatileMemberFunctor(const Obj &obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundConstVolatileMemberFunctor(const QExtBoundConstVolatileMemberFunctor &other) : BaseType(other) {}

    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2,
                      typename QExtTypeTrait<Arg3>::Take arg3) const
    {
        return BaseType::operator()(arg1, arg2, arg3);
    }
};

template<class Return, class Obj, class Arg1, class Arg2, class Arg3>
struct QExtVisitor<QExtBoundConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3> >
{
    typedef QExtBoundConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3> TargetType;
    template<typename Action>
    static void doVisitEach(const Action &action, const TargetType &target)
    {
        qextVisitEach(action, target.mObj);
    }
};

template<class Return, class Obj, class Arg1, class Arg2>
class QExtBoundConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
        : public detail::QExtBoundConstVolatileMemberFunctor2<Return, Obj, Arg1, Arg2>
{
    typedef detail::QExtBoundConstVolatileMemberFunctor2<Return, Obj, Arg1, Arg2> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtBoundConstVolatileMemberFunctor(const Obj *obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundConstVolatileMemberFunctor(const Obj &obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundConstVolatileMemberFunctor(const QExtBoundConstVolatileMemberFunctor &other) : BaseType(other) {}

    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1,
                      typename QExtTypeTrait<Arg2>::Take arg2) const
    {
        return BaseType::operator()(arg1, arg2);
    }
};

template<class Return, class Obj, class Arg1, class Arg2>
struct QExtVisitor<QExtBoundConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2> >
{
    typedef QExtBoundConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2> TargetType;
    template<typename Action>
    static void doVisitEach(const Action &action, const TargetType &target)
    {
        qextVisitEach(action, target.mObj);
    }
};

template<class Return, class Obj, class Arg1>
class QExtBoundConstVolatileMemberFunctor<Return, Obj, Arg1, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
        : public detail::QExtBoundConstVolatileMemberFunctor1<Return, Obj, Arg1>
{
    typedef detail::QExtBoundConstVolatileMemberFunctor1<Return, Obj, Arg1> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtBoundConstVolatileMemberFunctor(const Obj *obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundConstVolatileMemberFunctor(const Obj &obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundConstVolatileMemberFunctor(const QExtBoundConstVolatileMemberFunctor &other) : BaseType(other) {}

    Return operator()(typename QExtTypeTrait<Arg1>::Take arg1) const
    {
        return BaseType::operator()(arg1);
    }
};

template<class Return, class Obj, class Arg1>
struct QExtVisitor<QExtBoundConstVolatileMemberFunctor<Return, Obj, Arg1> >
{
    typedef QExtBoundConstVolatileMemberFunctor<Return, Obj, Arg1> TargetType;
    template<typename Action>
    static void doVisitEach(const Action &action, const TargetType &target)
    {
        qextVisitEach(action, target.mObj);
    }
};

template<class Return, class Obj>
class QExtBoundConstVolatileMemberFunctor<Return, Obj, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
        : public detail::QExtBoundConstVolatileMemberFunctor0<Return, Obj>
{
    typedef detail::QExtBoundConstVolatileMemberFunctor0<Return, Obj> BaseType;

public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QExtBoundConstVolatileMemberFunctor(const Obj *obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundConstVolatileMemberFunctor(const Obj &obj, FunctionType func) : BaseType(obj, func) {}

    QExtBoundConstVolatileMemberFunctor(const QExtBoundConstVolatileMemberFunctor &other) : BaseType(other) {}

    Return operator()() const
    {
        return BaseType::operator()();
    }
};

template<class Return, class Obj>
struct QExtVisitor<QExtBoundConstVolatileMemberFunctor<Return, Obj> >
{
    typedef QExtBoundConstVolatileMemberFunctor<Return, Obj> TargetType;
    template<typename Action>
    static void doVisitEach(const Action &action, const TargetType &target)
    {
        qextVisitEach(action, target.mObj);
    }
};

/**
 * @brief Creates a functor of type QExtMemberFunctor which wraps a method with 7 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
inline QExtMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>
qextMakeFunctor(Return (Obj::*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7))
{
    return QExtMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>(func);
}

/**
 * @brief Creates a functor of type QExtMemberFunctor which wraps a method with 6 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
inline QExtMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>
qextMakeFunctor(Return (Obj::*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6))
{
    return QExtMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>(func);
}

/**
 * @brief Creates a functor of type QExtMemberFunctor which wraps a method with 5 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
inline QExtMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5>
qextMakeFunctor(Return (Obj::*func)(Arg1, Arg2, Arg3, Arg4, Arg5))
{
    return QExtMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5>(func);
}

/**
 * @brief Creates a functor of type QExtMemberFunctor which wraps a method with 4 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4>
inline QExtMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4>
qextMakeFunctor(Return (Obj::*func)(Arg1, Arg2, Arg3, Arg4))
{
    return QExtMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4>(func);
}

/**
 * @brief Creates a functor of type QExtMemberFunctor which wraps a method with 3 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3>
inline QExtMemberFunctor<Return, Obj, Arg1, Arg2, Arg3>
qextMakeFunctor(Return (Obj::*func)(Arg1, Arg2, Arg3))
{
    return QExtMemberFunctor<Return, Obj, Arg1, Arg2, Arg3>(func);
}

/**
 * @brief Creates a functor of type QExtMemberFunctor which wraps a method with 2 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2>
inline QExtMemberFunctor<Return, Obj, Arg1, Arg2>
qextMakeFunctor(Return (Obj::*func)(Arg1, Arg2))
{
    return QExtMemberFunctor<Return, Obj, Arg1, Arg2>(func);
}

/**
 * @brief Creates a functor of type QExtMemberFunctor which wraps a method with 1 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 */
template<class Return, class Obj, class Arg1>
inline QExtMemberFunctor<Return, Obj, Arg1>
qextMakeFunctor(Return (Obj::*func)(Arg1))
{
    return QExtMemberFunctor<Return, Obj, Arg1>(func);
}

/**
 * @brief Creates a functor of type QExtMemberFunctor which wraps a method with no args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 */
template<class Return, class Obj>
inline QExtMemberFunctor<Return, Obj>
qextMakeFunctor(Return (Obj::*func)())
{
    return QExtMemberFunctor<Return, Obj>(func);
}

/**
 * @brief Creates a functor of type QExtConstMemberFunctor which wraps a const method with 7 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
inline QExtConstMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>
qextMakeFunctor(Return (Obj::*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7) const)
{
    return QExtConstMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>(func);
}

/**
 * @brief Creates a functor of type QExtConstMemberFunctor which wraps a const method with 6 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
inline QExtConstMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>
qextMakeFunctor(Return (Obj::*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6) const)
{
    return QExtConstMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>(func);
}

/**
 * @brief Creates a functor of type QExtConstMemberFunctor which wraps a const method with 5 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
inline QExtConstMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5>
qextMakeFunctor(Return (Obj::*func)(Arg1, Arg2, Arg3, Arg4, Arg5) const)
{
    return QExtConstMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5>(func);
}

/**
 * @brief Creates a functor of type QExtConstMemberFunctor which wraps a const method with 4 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4>
inline QExtConstMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4>
qextMakeFunctor(Return (Obj::*func)(Arg1, Arg2, Arg3, Arg4) const)
{
    return QExtConstMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4>(func);
}

/**
 * @brief Creates a functor of type QExtConstMemberFunctor which wraps a const method with 3 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3>
inline QExtConstMemberFunctor<Return, Obj, Arg1, Arg2, Arg3>
qextMakeFunctor(Return (Obj::*func)(Arg1, Arg2, Arg3) const)
{
    return QExtConstMemberFunctor<Return, Obj, Arg1, Arg2, Arg3>(func);
}

/**
 * @brief Creates a functor of type QExtConstMemberFunctor which wraps a const method with 2 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2>
inline QExtConstMemberFunctor<Return, Obj, Arg1, Arg2>
qextMakeFunctor(Return (Obj::*func)(Arg1, Arg2) const)
{
    return QExtConstMemberFunctor<Return, Obj, Arg1, Arg2>(func);
}

/**
 * @brief Creates a functor of type QExtConstMemberFunctor which wraps a const method with 1 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 */
template<class Return, class Obj, class Arg1>
inline QExtConstMemberFunctor<Return, Obj, Arg1>
qextMakeFunctor(Return (Obj::*func)(Arg1) const)
{
    return QExtConstMemberFunctor<Return, Obj, Arg1>(func);
}

/**
 * @brief Creates a functor of type QExtConstMemberFunctor which wraps a const method with no args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 */
template<class Return, class Obj>
inline QExtConstMemberFunctor<Return, Obj>
qextMakeFunctor(Return (Obj::*func)() const)
{
    return QExtConstMemberFunctor<Return, Obj>(func);
}

/**
 * @brief Creates a functor of type QExtVolatileMemberFunctor which wraps a volatile method with 7 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
inline QExtVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>
qextMakeFunctor(Return (Obj::*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7) volatile)
{
    return QExtVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>(func);
}

/**
 * @brief Creates a functor of type QExtVolatileMemberFunctor which wraps a volatile method with 6 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
inline QExtVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>
qextMakeFunctor(Return (Obj::*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6) volatile)
{
    return QExtVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>(func);
}

/**
 * @brief Creates a functor of type QExtVolatileMemberFunctor which wraps a volatile method with 5 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
inline QExtVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5>
qextMakeFunctor(Return (Obj::*func)(Arg1, Arg2, Arg3, Arg4, Arg5) volatile)
{
    return QExtVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5>(func);
}

/**
 * @brief Creates a functor of type QExtVolatileMemberFunctor which wraps a volatile method with 4 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4>
inline QExtVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4>
qextMakeFunctor(Return (Obj::*func)(Arg1, Arg2, Arg3, Arg4) volatile)
{
    return QExtVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4>(func);
}

/**
 * @brief Creates a functor of type QExtVolatileMemberFunctor which wraps a volatile method with 3 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3>
inline QExtVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3>
qextMakeFunctor(Return (Obj::*func)(Arg1, Arg2, Arg3) volatile)
{
    return QExtVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3>(func);
}

/**
 * @brief Creates a functor of type QExtVolatileMemberFunctor which wraps a volatile method with 2 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2>
inline QExtVolatileMemberFunctor<Return, Obj, Arg1, Arg2>
qextMakeFunctor(Return (Obj::*func)(Arg1, Arg2) volatile)
{
    return QExtVolatileMemberFunctor<Return, Obj, Arg1, Arg2>(func);
}

/**
 * @brief Creates a functor of type QExtVolatileMemberFunctor which wraps a volatile method with 1 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 */
template<class Return, class Obj, class Arg1>
inline QExtVolatileMemberFunctor<Return, Obj, Arg1>
qextMakeFunctor(Return (Obj::*func)(Arg1) volatile)
{
    return QExtVolatileMemberFunctor<Return, Obj, Arg1>(func);
}

/**
 * @brief Creates a functor of type QExtVolatileMemberFunctor which wraps a volatile method with no args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 */
template<class Return, class Obj>
inline QExtVolatileMemberFunctor<Return, Obj>
qextMakeFunctor(Return (Obj::*func)() volatile)
{
    return QExtVolatileMemberFunctor<Return, Obj>(func);
}

/**
 * @brief Creates a functor of type QExtConstVolatileMemberFunctor which wraps a const volatile method with 7 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
inline QExtConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>
qextMakeFunctor(Return (Obj::*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7) const volatile)
{
    return QExtConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>(func);
}

/**
 * @brief Creates a functor of type QExtConstVolatileMemberFunctor which wraps a const volatile method with 6 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
inline QExtConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>
qextMakeFunctor(Return (Obj::*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6) const volatile)
{
    return QExtConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>(func);
}

/**
 * @brief Creates a functor of type QExtConstVolatileMemberFunctor which wraps a const volatile method with 5 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
inline QExtConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5>
qextMakeFunctor(Return (Obj::*func)(Arg1, Arg2, Arg3, Arg4, Arg5) const volatile)
{
    return QExtConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5>(func);
}

/**
 * @brief Creates a functor of type QExtConstVolatileMemberFunctor which wraps a const volatile method with 4 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4>
inline QExtConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4>
qextMakeFunctor(Return (Obj::*func)(Arg1, Arg2, Arg3, Arg4) const volatile)
{
    return QExtConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4>(func);
}

/**
 * @brief Creates a functor of type QExtConstVolatileMemberFunctor which wraps a const volatile method with 3 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3>
inline QExtConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3>
qextMakeFunctor(Return (Obj::*func)(Arg1, Arg2, Arg3) const volatile)
{
    return QExtConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3>(func);
}

/**
 * @brief Creates a functor of type QExtConstVolatileMemberFunctor which wraps a const volatile method with 2 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2>
inline QExtConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2>
qextMakeFunctor(Return (Obj::*func)(Arg1, Arg2) const volatile)
{
    return QExtConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2>(func);
}

/**
 * @brief Creates a functor of type QExtConstVolatileMemberFunctor which wraps a const volatile method with 1 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 */
template<class Return, class Obj, class Arg1>
inline QExtConstVolatileMemberFunctor<Return, Obj, Arg1>
qextMakeFunctor(Return (Obj::*func)(Arg1) const volatile)
{
    return QExtConstVolatileMemberFunctor<Return, Obj, Arg1>(func);
}

/**
 * @brief Creates a functor of type QExtConstVolatileMemberFunctor which wraps a const volatile method with no args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 */
template<class Return, class Obj>
inline QExtConstVolatileMemberFunctor<Return, Obj>
qextMakeFunctor(Return (Obj::*func)() const volatile)
{
    return QExtConstVolatileMemberFunctor<Return, Obj>(func);
}

/**
 * @brief Creates a functor of type QExtBoundMemberFunctor0 which encapsulates a method and
 * an object instance with 7 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
inline QExtBoundMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>
qextMakeFunctor(Obj *obj, Return (Obj::*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7))
{
    return QExtBoundMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundMemberFunctor which encapsulates a method and
 * an object instance with 7 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
inline QExtBoundMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>
qextMakeFunctor(Obj &obj, Return (Obj::*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7))
{
    return QExtBoundMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundMemberFunctor0 which encapsulates a method and
 * an object instance with 6 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
inline QExtBoundMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>
qextMakeFunctor(Obj *obj, Return (Obj::*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6))
{
    return QExtBoundMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundMemberFunctor which encapsulates a method and
 * an object instance with 6 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
inline QExtBoundMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>
qextMakeFunctor(Obj &obj, Return (Obj::*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6))
{
    return QExtBoundMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundMemberFunctor0 which encapsulates a method and
 * an object instance with 5 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
inline QExtBoundMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5>
qextMakeFunctor(Obj *obj, Return (Obj::*func)(Arg1, Arg2, Arg3, Arg4, Arg5))
{
    return QExtBoundMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundMemberFunctor which encapsulates a method and
 * an object instance with 5 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
inline QExtBoundMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5>
qextMakeFunctor(Obj &obj, Return (Obj::*func)(Arg1, Arg2, Arg3, Arg4, Arg5))
{
    return QExtBoundMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundMemberFunctor0 which encapsulates a method and
 * an object instance with 4 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4>
inline QExtBoundMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4>
qextMakeFunctor(Obj *obj, Return (Obj::*func)(Arg1, Arg2, Arg3, Arg4))
{
    return QExtBoundMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundMemberFunctor which encapsulates a method and
 * an object instance with 4 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4>
inline QExtBoundMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4>
qextMakeFunctor(Obj &obj, Return (Obj::*func)(Arg1, Arg2, Arg3, Arg4))
{
    return QExtBoundMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundMemberFunctor0 which encapsulates a method and
 * an object instance with 3 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3>
inline QExtBoundMemberFunctor<Return, Obj, Arg1, Arg2, Arg3>
qextMakeFunctor(Obj *obj, Return (Obj::*func)(Arg1, Arg2, Arg3))
{
    return QExtBoundMemberFunctor<Return, Obj, Arg1, Arg2, Arg3>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundMemberFunctor which encapsulates a method and
 * an object instance with 3 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3>
inline QExtBoundMemberFunctor<Return, Obj, Arg1, Arg2, Arg3>
qextMakeFunctor(Obj &obj, Return (Obj::*func)(Arg1, Arg2, Arg3))
{
    return QExtBoundMemberFunctor<Return, Obj, Arg1, Arg2, Arg3>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundMemberFunctor0 which encapsulates a method and
 * an object instance with 2 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2>
inline QExtBoundMemberFunctor<Return, Obj, Arg1, Arg2>
qextMakeFunctor(Obj *obj, Return (Obj::*func)(Arg1, Arg2))
{
    return QExtBoundMemberFunctor<Return, Obj, Arg1, Arg2>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundMemberFunctor which encapsulates a method and
 * an object instance with 2 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2>
inline QExtBoundMemberFunctor<Return, Obj, Arg1, Arg2>
qextMakeFunctor(Obj &obj, Return (Obj::*func)(Arg1, Arg2))
{
    return QExtBoundMemberFunctor<Return, Obj, Arg1, Arg2>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundMemberFunctor0 which encapsulates a method and
 * an object instance with 1 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1>
inline QExtBoundMemberFunctor<Return, Obj, Arg1>
qextMakeFunctor(Obj *obj, Return (Obj::*func)(Arg1))
{
    return QExtBoundMemberFunctor<Return, Obj, Arg1>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundMemberFunctor which encapsulates a method and
 * an object instance with 1 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1>
inline QExtBoundMemberFunctor<Return, Obj, Arg1>
qextMakeFunctor(Obj &obj, Return (Obj::*func)(Arg1))
{
    return QExtBoundMemberFunctor<Return, Obj, Arg1>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundMemberFunctor0 which encapsulates a method and
 * an object instance with no args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj>
inline QExtBoundMemberFunctor<Return, Obj>
qextMakeFunctor(Obj *obj, Return (Obj::*func)())
{
    return QExtBoundMemberFunctor<Return, Obj>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundMemberFunctor which encapsulates a method and
 * an object instance with no args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj>
inline QExtBoundMemberFunctor<Return, Obj>
qextMakeFunctor(Obj &obj, Return (Obj::*func)())
{
    return QExtBoundMemberFunctor<Return, Obj>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundConstMemberFunctor which encapsulates a method and
 * an object instance with 7 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
inline QExtBoundConstMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>
qextMakeFunctor(Obj *obj, Return (Obj::*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7) const)
{
    return QExtBoundConstMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundConstMemberFunctor which encapsulates a method and
 * an object instance with 7 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
inline QExtBoundConstMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>
qextMakeFunctor(Obj &obj, Return (Obj::*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7) const)
{
    return QExtBoundConstMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundConstMemberFunctor which encapsulates a method and
 * an object instance with 6 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
inline QExtBoundConstMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>
qextMakeFunctor(Obj *obj, Return (Obj::*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6) const)
{
    return QExtBoundConstMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundConstMemberFunctor which encapsulates a method and
 * an object instance with 6 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
inline QExtBoundConstMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>
qextMakeFunctor(Obj &obj, Return (Obj::*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6) const)
{
    return QExtBoundConstMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundConstMemberFunctor which encapsulates a method and
 * an object instance with 5 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
inline QExtBoundConstMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5>
qextMakeFunctor(Obj *obj, Return (Obj::*func)(Arg1, Arg2, Arg3, Arg4, Arg5) const)
{
    return QExtBoundConstMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundConstMemberFunctor which encapsulates a method and
 * an object instance with 5 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
inline QExtBoundConstMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5>
qextMakeFunctor(Obj &obj, Return (Obj::*func)(Arg1, Arg2, Arg3, Arg4, Arg5) const)
{
    return QExtBoundConstMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundConstMemberFunctor which encapsulates a method and
 * an object instance with 4 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4>
inline QExtBoundConstMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4>
qextMakeFunctor(Obj *obj, Return (Obj::*func)(Arg1, Arg2, Arg3, Arg4) const)
{
    return QExtBoundConstMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundConstMemberFunctor which encapsulates a method and
 * an object instance with 4 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4>
inline QExtBoundConstMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4>
qextMakeFunctor(Obj &obj, Return (Obj::*func)(Arg1, Arg2, Arg3, Arg4) const)
{
    return QExtBoundConstMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundConstMemberFunctor which encapsulates a method and
 * an object instance with 3 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3>
inline QExtBoundConstMemberFunctor<Return, Obj, Arg1, Arg2, Arg3>
qextMakeFunctor(Obj *obj, Return (Obj::*func)(Arg1, Arg2, Arg3) const)
{
    return QExtBoundConstMemberFunctor<Return, Obj, Arg1, Arg2, Arg3>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundConstMemberFunctor which encapsulates a method and
 * an object instance with 3 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3>
inline QExtBoundConstMemberFunctor<Return, Obj, Arg1, Arg2, Arg3>
qextMakeFunctor(Obj &obj, Return (Obj::*func)(Arg1, Arg2, Arg3) const)
{
    return QExtBoundConstMemberFunctor<Return, Obj, Arg1, Arg2, Arg3>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundConstMemberFunctor which encapsulates a method and
 * an object instance with 2 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2>
inline QExtBoundConstMemberFunctor<Return, Obj, Arg1, Arg2>
qextMakeFunctor(Obj *obj, Return (Obj::*func)(Arg1, Arg2) const)
{
    return QExtBoundConstMemberFunctor<Return, Obj, Arg1, Arg2>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundConstMemberFunctor which encapsulates a method and
 * an object instance with 2 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2>
inline QExtBoundConstMemberFunctor<Return, Obj, Arg1, Arg2>
qextMakeFunctor(Obj &obj, Return (Obj::*func)(Arg1, Arg2) const)
{
    return QExtBoundConstMemberFunctor<Return, Obj, Arg1, Arg2>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundConstMemberFunctor which encapsulates a method and
 * an object instance with 1 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1>
inline QExtBoundConstMemberFunctor<Return, Obj, Arg1>
qextMakeFunctor(Obj *obj, Return (Obj::*func)(Arg1) const)
{
    return QExtBoundConstMemberFunctor<Return, Obj, Arg1>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundConstMemberFunctor which encapsulates a method and
 * an object instance with 1 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1>
inline QExtBoundConstMemberFunctor<Return, Obj, Arg1>
qextMakeFunctor(Obj &obj, Return (Obj::*func)(Arg1) const)
{
    return QExtBoundConstMemberFunctor<Return, Obj, Arg1>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundConstMemberFunctor which encapsulates a method and
 * an object instance with no args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj>
inline QExtBoundConstMemberFunctor<Return, Obj>
qextMakeFunctor(Obj *obj, Return (Obj::*func)() const)
{
    return QExtBoundConstMemberFunctor<Return, Obj>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundConstMemberFunctor which encapsulates a method and
 * an object instance with no args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj>
inline QExtBoundConstMemberFunctor<Return, Obj>
qextMakeFunctor(Obj &obj, Return (Obj::*func)() const)
{
    return QExtBoundConstMemberFunctor<Return, Obj>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundVolatileMemberFunctor which encapsulates a method and
 * an object instance with 7 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
inline QExtBoundVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>
qextMakeFunctor(Obj *obj, Return (Obj::*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7) volatile)
{
    return QExtBoundVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundVolatileMemberFunctor which encapsulates a method and
 * an object instance with 7 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
inline QExtBoundVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>
qextMakeFunctor(Obj &obj, Return (Obj::*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7) volatile)
{
    return QExtBoundVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundVolatileMemberFunctor which encapsulates a method and
 * an object instance with 6 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
inline QExtBoundVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>
qextMakeFunctor(Obj *obj, Return (Obj::*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6) volatile)
{
    return QExtBoundVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundVolatileMemberFunctor which encapsulates a method and
 * an object instance with 6 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
inline QExtBoundVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>
qextMakeFunctor(Obj &obj, Return (Obj::*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6) volatile)
{
    return QExtBoundVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundVolatileMemberFunctor which encapsulates a method and
 * an object instance with 5 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
inline QExtBoundVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5>
qextMakeFunctor(Obj *obj, Return (Obj::*func)(Arg1, Arg2, Arg3, Arg4, Arg5) volatile)
{
    return QExtBoundVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundVolatileMemberFunctor which encapsulates a method and
 * an object instance with 5 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
inline QExtBoundVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5>
qextMakeFunctor(Obj &obj, Return (Obj::*func)(Arg1, Arg2, Arg3, Arg4, Arg5) volatile)
{
    return QExtBoundVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundVolatileMemberFunctor which encapsulates a method and
 * an object instance with 4 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4>
inline QExtBoundVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4>
qextMakeFunctor(Obj *obj, Return (Obj::*func)(Arg1, Arg2, Arg3, Arg4) volatile)
{
    return QExtBoundVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundVolatileMemberFunctor which encapsulates a method and
 * an object instance with 4 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4>
inline QExtBoundVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4>
qextMakeFunctor(Obj &obj, Return (Obj::*func)(Arg1, Arg2, Arg3, Arg4) volatile)
{
    return QExtBoundVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundVolatileMemberFunctor which encapsulates a method and
 * an object  instance with 3 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3>
inline QExtBoundVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3>
qextMakeFunctor(Obj *obj, Return (Obj::*func)(Arg1, Arg2, Arg3) volatile)
{
    return QExtBoundVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundVolatileMemberFunctor which encapsulates a method and
 * an object  instance with 3 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3>
inline QExtBoundVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3>
qextMakeFunctor(Obj &obj, Return (Obj::*func)(Arg1, Arg2, Arg3) volatile)
{
    return QExtBoundVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundVolatileMemberFunctor which encapsulates a method and
 * an object instance with 2 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2>
inline QExtBoundVolatileMemberFunctor<Return, Obj, Arg1, Arg2>
qextMakeFunctor(Obj *obj, Return (Obj::*func)(Arg1, Arg2) volatile)
{
    return QExtBoundVolatileMemberFunctor<Return, Obj, Arg1, Arg2>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundVolatileMemberFunctor which encapsulates a method and
 * an object  instance with 2 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2>
inline QExtBoundVolatileMemberFunctor<Return, Obj, Arg1, Arg2>
qextMakeFunctor(Obj &obj, Return (Obj::*func)(Arg1, Arg2) volatile)
{
    return QExtBoundVolatileMemberFunctor<Return, Obj, Arg1, Arg2>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundVolatileMemberFunctor which encapsulates a method and
 * an object instance with 1 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1>
inline QExtBoundVolatileMemberFunctor<Return, Obj, Arg1>
qextMakeFunctor(Obj *obj, Return (Obj::*func)(Arg1) volatile)
{
    return QExtBoundVolatileMemberFunctor<Return, Obj, Arg1>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundVolatileMemberFunctor which encapsulates a method and
 * an object instance with 1 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1>
inline QExtBoundVolatileMemberFunctor<Return, Obj, Arg1>
qextMakeFunctor(Obj &obj, Return (Obj::*func)(Arg1) volatile)
{
    return QExtBoundVolatileMemberFunctor<Return, Obj, Arg1>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundVolatileMemberFunctor which encapsulates a method and
 * an object instance with no args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj>
inline QExtBoundVolatileMemberFunctor<Return, Obj>
qextMakeFunctor(Obj *obj, Return (Obj::*func)() volatile)
{
    return QExtBoundVolatileMemberFunctor<Return, Obj>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundVolatileMemberFunctor which encapsulates a method and
 * an object instance with no args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj>
inline QExtBoundVolatileMemberFunctor<Return, Obj>
qextMakeFunctor(Obj &obj, Return (Obj::*func)() volatile)
{
    return QExtBoundVolatileMemberFunctor<Return, Obj>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundConstVolatileMemberFunctor which encapsulates a method and
 * an object instance with 7 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
inline QExtBoundConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>
qextMakeFunctor(Obj *obj, Return (Obj::*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7) const volatile)
{
    return QExtBoundConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundConstVolatileMemberFunctor which encapsulates a method and
 * an object instance with 7 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
inline QExtBoundConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>
qextMakeFunctor(Obj &obj, Return (Obj::*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7) const volatile)
{
    return QExtBoundConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundConstVolatileMemberFunctor which encapsulates a method and
 * an object instance with 6 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
inline QExtBoundConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>
qextMakeFunctor(Obj *obj, Return (Obj::*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6) const volatile)
{
    return QExtBoundConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundConstVolatileMemberFunctor which encapsulates a method and
 * an object instance with 6 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
inline QExtBoundConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>
qextMakeFunctor(Obj &obj, Return (Obj::*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6) const volatile)
{
    return QExtBoundConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundConstVolatileMemberFunctor which encapsulates a method and
 * an object instance with 5 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
inline QExtBoundConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5>
qextMakeFunctor(Obj *obj, Return (Obj::*func)(Arg1, Arg2, Arg3, Arg4, Arg5) const volatile)
{
    return QExtBoundConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundConstVolatileMemberFunctor which encapsulates a method and
 * an object instance with 5 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
inline QExtBoundConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5>
qextMakeFunctor(Obj &obj, Return (Obj::*func)(Arg1, Arg2, Arg3, Arg4, Arg5) const volatile)
{
    return QExtBoundConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundConstVolatileMemberFunctor which encapsulates a method and
 * an object instance with 4 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4>
inline QExtBoundConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4>
qextMakeFunctor(Obj *obj, Return (Obj::*func)(Arg1, Arg2, Arg3, Arg4) const volatile)
{
    return QExtBoundConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundConstVolatileMemberFunctor which encapsulates a method and
 * an object instance with 4 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4>
inline QExtBoundConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4>
qextMakeFunctor(Obj &obj, Return (Obj::*func)(Arg1, Arg2, Arg3, Arg4) const volatile)
{
    return QExtBoundConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3, Arg4>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundConstVolatileMemberFunctor which encapsulates a method and
 * an object instance with 3 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3>
inline QExtBoundConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3>
qextMakeFunctor(Obj *obj, Return (Obj::*func)(Arg1, Arg2, Arg3) const volatile)
{
    return QExtBoundConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundConstVolatileMemberFunctor which encapsulates a method and
 * an object instance with 3 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2, class Arg3>
inline QExtBoundConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3>
qextMakeFunctor(Obj &obj, Return (Obj::*func)(Arg1, Arg2, Arg3) const volatile)
{
    return QExtBoundConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2, Arg3>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundConstVolatileMemberFunctor which encapsulates a method and
 * an object instance with 2 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2>
inline QExtBoundConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2>
qextMakeFunctor(Obj *obj, Return (Obj::*func)(Arg1, Arg2) const volatile)
{
    return QExtBoundConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundConstVolatileMemberFunctor which encapsulates a method and
 * an object instance with 2 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1, class Arg2>
inline QExtBoundConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2>
qextMakeFunctor(Obj &obj, Return (Obj::*func)(Arg1, Arg2) const volatile)
{
    return QExtBoundConstVolatileMemberFunctor<Return, Obj, Arg1, Arg2>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundConstVolatileMemberFunctor which encapsulates a method and
 * an object instance with 1 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1>
inline QExtBoundConstVolatileMemberFunctor<Return, Obj, Arg1>
qextMakeFunctor(Obj *obj, Return (Obj::*func)(Arg1) const volatile)
{
    return QExtBoundConstVolatileMemberFunctor<Return, Obj, Arg1>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundConstVolatileMemberFunctor which encapsulates a method and
 * an object instance with 1 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj, class Arg1>
inline QExtBoundConstVolatileMemberFunctor<Return, Obj, Arg1>
qextMakeFunctor(Obj &obj, Return (Obj::*func)(Arg1) const volatile)
{
    return QExtBoundConstVolatileMemberFunctor<Return, Obj, Arg1>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundConstVolatileMemberFunctor which encapsulates a method and
 * an object instance with no args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj>
inline QExtBoundConstVolatileMemberFunctor<Return, Obj>
qextMakeFunctor(Obj *obj, Return (Obj::*func)() const volatile)
{
    return QExtBoundConstVolatileMemberFunctor<Return, Obj>(obj, func);
}

/**
 * @brief Creates a functor of type QExtBoundConstVolatileMemberFunctor which encapsulates a method and
 * an object instance with no args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 */
template<class Return, class Obj>
inline QExtBoundConstVolatileMemberFunctor<Return, Obj>
qextMakeFunctor(Obj &obj, Return (Obj::*func)() const volatile)
{
    return QExtBoundConstVolatileMemberFunctor<Return, Obj>(obj, func);
}

#endif // _QEXTMEMBERFUNCTOR_H
