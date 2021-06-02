#ifndef QEXTMEMBERFUNCTOR_H
#define QEXTMEMBERFUNCTOR_H

#include <qextglobal.h>
#include <qextfunctortrait.h>
#include <qextlimitreference.h>


/** @defgroup qextMemberFunctor qextMemberFunctor()
 * qextMemberFunctor() is used to convert a pointer to a method to a functor.
 *
 * Optionally, a reference or pointer to an object can be bound to the functor.
 * Note that only if the object type inherits from QEXTTrackable is
 * the slot automatically cleared when the object goes out of scope!
 *
 * If the member function pointer is to an overloaded type, you must specify
 * the types using template arguments starting with the first argument.
 * It is not necessary to supply the return type.
 *
 * @par Example:
 * @code
 * struct foo : public QEXTTrackable
 * {
 *   void bar(int) {}
 * };
 * foo my_foo;
 * QEXTSlot<void, int> slot = qextMemberFunctor(my_foo, &foo::bar);
 * @endcode
 *
 * For const methods qextMemberFunctor() takes a const reference or pointer to an object.
 *
 * @par Example:
 * @code
 * struct foo : public QEXTTrackable
 * {
 *   void bar(int) const {}
 * };
 * const foo my_foo;
 * QEXTSlot<void, int> slot = qextMemberFunctor(my_foo, &foo::bar);
 * @endcode
 *
 * Use qextMemberFunctor#() if there is an ambiguity as to the number of arguments.
 *
 * @par Example:
 * @code
 * struct foo : public QEXTTrackable
 * {
 *   void bar(int) {}
 *   void bar(float) {}
 *   void bar(int, int) {}
 * };
 * foo my_foo;
 * QEXTSlot<void, int> slot = qextMemberFunctor1<int>(my_foo, &foo::bar);
 * @endcode
 *
 * @ingroup qextfunctors
 */



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
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
class QEXTMemberFunctor7 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7);
    typedef T_return ResultType;

    // Constructs an invalid functor.
    QEXTMemberFunctor7() : m_funcPtr(QEXT_NULLPTR) {}
    /** Constructs a QEXTMemberFunctor7 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTMemberFunctor7(FunctionType func) : m_funcPtr(func) {}
    QEXTMemberFunctor7(const QEXTMemberFunctor7 &src) : m_funcPtr(src.m_funcPtr) {}

    /** Execute the wrapped method operating on the passed instance.
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
    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6,
                        typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return (obj->*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    /** Execute the wrapped method operating on the passed instance.
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
    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6,
                        typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

protected:
    FunctionType m_funcPtr;
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
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
class QEXTMemberFunctor6 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6);
    typedef T_return ResultType;

    // Constructs an invalid functor.
    QEXTMemberFunctor6() : m_funcPtr(QEXT_NULLPTR) {}
    /** Constructs a QEXTMemberFunctor6 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTMemberFunctor6(FunctionType func) : m_funcPtr(func) {}
    QEXTMemberFunctor6(const QEXTMemberFunctor6 &src) : m_funcPtr(src.m_funcPtr) {}

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @param arg6 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return (obj->*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6);
    }

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @param arg6 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4, arg5, arg6);
    }

protected:
    FunctionType m_funcPtr;
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
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class QEXTMemberFunctor5 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5);
    typedef T_return ResultType;

    // Constructs an invalid functor.
    QEXTMemberFunctor5() : m_funcPtr(QEXT_NULLPTR) {}
    /** Constructs a QEXTMemberFunctor5 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTMemberFunctor5(FunctionType func) : m_funcPtr(func) {}
    QEXTMemberFunctor5(const QEXTMemberFunctor5 &src) : m_funcPtr(src.m_funcPtr) {}

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return (obj->*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5);
    }

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4, arg5);
    }

protected:
    FunctionType m_funcPtr;
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
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class QEXTMemberFunctor4 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1, T_arg2, T_arg3, T_arg4);
    typedef T_return ResultType;

    // Constructs an invalid functor.
    QEXTMemberFunctor4() : m_funcPtr(QEXT_NULLPTR) {}
    /** Constructs a QEXTMemberFunctor4 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTMemberFunctor4(FunctionType func) : m_funcPtr(func) {}
    QEXTMemberFunctor4(const QEXTMemberFunctor4 &src) : m_funcPtr(src.m_funcPtr) {}

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return (obj->*(this->m_funcPtr))(arg1, arg2, arg3, arg4);
    }

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4);
    }

protected:
    FunctionType m_funcPtr;
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
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
class QEXTMemberFunctor3 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1, T_arg2, T_arg3);
    typedef T_return ResultType;

    // Constructs an invalid functor.
    QEXTMemberFunctor3() : m_funcPtr(QEXT_NULLPTR) {}
    /** Constructs a QEXTMemberFunctor3 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTMemberFunctor3(FunctionType func) : m_funcPtr(func) {}
    QEXTMemberFunctor3(const QEXTMemberFunctor3 &src) : m_funcPtr(src.m_funcPtr) {}

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return (obj->*(this->m_funcPtr))(arg1, arg2, arg3);
    }

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return (obj.*m_funcPtr)(arg1, arg2, arg3);
    }

protected:
    FunctionType m_funcPtr;
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
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
class QEXTMemberFunctor2 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1, T_arg2);
    typedef T_return ResultType;

    // Constructs an invalid functor.
    QEXTMemberFunctor2() : m_funcPtr(QEXT_NULLPTR) {}
    /** Constructs a QEXTMemberFunctor2 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTMemberFunctor2(FunctionType func) : m_funcPtr(func) {}
    QEXTMemberFunctor2(const QEXTMemberFunctor2 &src) : m_funcPtr(src.m_funcPtr) {}

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(T_obj *obj, typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return (obj->*(this->m_funcPtr))(arg1, arg2);
    }

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(T_obj &obj, typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return (obj.*m_funcPtr)(arg1, arg2);
    }

protected:
    FunctionType m_funcPtr;
};

/** QEXTMemberFunctor1 wraps  methods with 1 argument(s).
 * Use the convenience function qextMemberFunctor() to create an instance of QEXTMemberFunctor1.
 *
 * The following template arguments are used:
 * - @e T_arg1 Argument type used in the definition of operator()().
 * - @e T_return The return type of operator()().
 * - @e T_obj The object type.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1>
class QEXTMemberFunctor1 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1);
    typedef T_return ResultType;

    // Constructs an invalid functor.
    QEXTMemberFunctor1() : m_funcPtr(QEXT_NULLPTR) {}
    /** Constructs a QEXTMemberFunctor1 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTMemberFunctor1(FunctionType func) : m_funcPtr(func) {}
    QEXTMemberFunctor1(const QEXTMemberFunctor1 &src) : m_funcPtr(src.m_funcPtr) {}

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return (obj->*(this->m_funcPtr))(arg1);
    }

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return (obj.*m_funcPtr)(arg1);
    }

protected:
    FunctionType m_funcPtr;
};

/** QEXTMemberFunctor0 wraps  methods with 0 argument(s).
 * Use the convenience function qextMemberFunctor() to create an instance of QEXTMemberFunctor0.
 *
 * The following template arguments are used:
 * - @e T_return The return type of operator()().
 * - @e T_obj The object type.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj>
class QEXTMemberFunctor0 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)();
    typedef T_return ResultType;

    // Constructs an invalid functor.
    QEXTMemberFunctor0() : m_funcPtr(QEXT_NULLPTR) {}
    /** Constructs a QEXTMemberFunctor0 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTMemberFunctor0(FunctionType func) : m_funcPtr(func) {}
    QEXTMemberFunctor0(const QEXTMemberFunctor0 &src) : m_funcPtr(src.m_funcPtr) {}

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @return The return value of the method invocation.
     */
    T_return operator()(T_obj *obj) const {
        return (obj->*(this->m_funcPtr))();
    }

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @return The return value of the method invocation.
     */
    T_return operator()(T_obj &obj) const {
        return (obj.*m_funcPtr)();
    }

protected:
    FunctionType m_funcPtr;
};

template <typename T_return, typename T_obj,
          typename T_arg1 = QEXTNil, typename T_arg2 = QEXTNil, typename T_arg3 = QEXTNil,
          typename T_arg4 = QEXTNil, typename T_arg5 = QEXTNil, typename T_arg6 = QEXTNil, typename T_arg7 = QEXTNil>
class QEXTMemberFunctor
        : public QEXTMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
{
    typedef QEXTMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTMemberFunctor() {}
    QEXTMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTMemberFunctor(const QEXTMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6,
                        typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6,
                        typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
class QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QEXTNil>
        : public QEXTMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
{
    typedef QEXTMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTMemberFunctor() {}
    QEXTMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTMemberFunctor(const QEXTMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4, arg5, arg6);
    }

    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QEXTNil, QEXTNil>
        : public QEXTMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
{
    typedef QEXTMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTMemberFunctor() {}
    QEXTMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTMemberFunctor(const QEXTMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4, arg5);
    }

    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4, arg5);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
{
    typedef QEXTMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTMemberFunctor() {}
    QEXTMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTMemberFunctor(const QEXTMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4);
    }

    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
class QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
{
    typedef QEXTMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTMemberFunctor() {}
    QEXTMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTMemberFunctor(const QEXTMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3);
    }

    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
class QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
{
    typedef QEXTMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTMemberFunctor() {}
    QEXTMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTMemberFunctor(const QEXTMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return BaseType::operator ()(obj, arg1, arg2);
    }

    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return BaseType::operator ()(obj, arg1, arg2);
    }
};

template <typename T_return, typename T_obj, typename T_arg1>
class QEXTMemberFunctor<T_return, T_obj, T_arg1, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTMemberFunctor1<T_return, T_obj, T_arg1>
{
    typedef QEXTMemberFunctor1<T_return, T_obj, T_arg1> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTMemberFunctor() {}
    QEXTMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTMemberFunctor(const QEXTMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return BaseType::operator ()(obj, arg1);
    }

    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return BaseType::operator ()(obj, arg1);
    }
};

template <typename T_return, typename T_obj>
class QEXTMemberFunctor<T_return, T_obj, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTMemberFunctor0<T_return, T_obj>
{
public:
    typedef QEXTMemberFunctor0<T_return, T_obj> BaseType;
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTMemberFunctor() {}
    QEXTMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTMemberFunctor(const QEXTMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(T_obj *obj) const {
        return BaseType::operator ()(obj);
    }

    T_return operator()(T_obj &obj) const {
        return BaseType::operator ()(obj);
    }
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
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
class QEXTConstMemberFunctor7 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const;
    typedef T_return ResultType;

    // Constructs an invalid functor.
    QEXTConstMemberFunctor7() : m_funcPtr(QEXT_NULLPTR) {}
    /** Constructs a QEXTConstMemberFunctor7 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTConstMemberFunctor7(FunctionType func) : m_funcPtr(func) {}
    QEXTConstMemberFunctor7(const QEXTConstMemberFunctor7 &src) : m_funcPtr(src.m_funcPtr) {}

    /** Execute the wrapped method operating on the passed instance.
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
    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6,
                        typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return (obj->*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    /** Execute the wrapped method operating on the passed instance.
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
    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6,
                        typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

protected:
    FunctionType m_funcPtr;
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
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
class QEXTConstMemberFunctor6 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const;
    typedef T_return ResultType;

    // Constructs an invalid functor.
    QEXTConstMemberFunctor6() : m_funcPtr(QEXT_NULLPTR) {}
    /** Constructs a QEXTConstMemberFunctor6 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTConstMemberFunctor6(FunctionType func) : m_funcPtr(func) {}
    QEXTConstMemberFunctor6(const QEXTConstMemberFunctor6 &src) : m_funcPtr(src.m_funcPtr) {}

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @param arg6 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return (obj->*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6);
    }

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @param arg6 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4, arg5, arg6);
    }

protected:
    FunctionType m_funcPtr;
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
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class QEXTConstMemberFunctor5 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const;
    typedef T_return ResultType;

    // Constructs an invalid functor.
    QEXTConstMemberFunctor5() : m_funcPtr(QEXT_NULLPTR) {}
    /** Constructs a QEXTConstMemberFunctor5 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTConstMemberFunctor5(FunctionType func) : m_funcPtr(func) {}
    QEXTConstMemberFunctor5(const QEXTConstMemberFunctor5 &src) : m_funcPtr(src.m_funcPtr) {}

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return (obj->*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5);
    }

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4, arg5);
    }

protected:
    FunctionType m_funcPtr;
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
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class QEXTConstMemberFunctor4 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1, T_arg2, T_arg3, T_arg4) const;
    typedef T_return ResultType;

    // Constructs an invalid functor.
    QEXTConstMemberFunctor4() : m_funcPtr(QEXT_NULLPTR) {}
    /** Constructs a QEXTConstMemberFunctor4 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTConstMemberFunctor4(FunctionType func) : m_funcPtr(func) {}
    QEXTConstMemberFunctor4(const QEXTConstMemberFunctor4 &src) : m_funcPtr(src.m_funcPtr) {}

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return (obj->*(this->m_funcPtr))(arg1, arg2, arg3, arg4);
    }

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4);
    }

protected:
    FunctionType m_funcPtr;
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
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
class QEXTConstMemberFunctor3 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1, T_arg2, T_arg3) const;
    typedef T_return ResultType;

    // Constructs an invalid functor.
    QEXTConstMemberFunctor3() : m_funcPtr(QEXT_NULLPTR) {}
    /** Constructs a QEXTConstMemberFunctor3 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTConstMemberFunctor3(FunctionType func) : m_funcPtr(func) {}
    QEXTConstMemberFunctor3(const QEXTConstMemberFunctor3 &src) : m_funcPtr(src.m_funcPtr) {}

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return (obj->*(this->m_funcPtr))(arg1, arg2, arg3);
    }

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return (obj.*m_funcPtr)(arg1, arg2, arg3);
    }

protected:
    FunctionType m_funcPtr;
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
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
class QEXTConstMemberFunctor2 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1, T_arg2) const;
    typedef T_return ResultType;

    // Constructs an invalid functor.
    QEXTConstMemberFunctor2() : m_funcPtr(QEXT_NULLPTR) {}
    /** Constructs a QEXTConstMemberFunctor2 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTConstMemberFunctor2(FunctionType func) : m_funcPtr(func) {}
    QEXTConstMemberFunctor2(const QEXTConstMemberFunctor2 &src) : m_funcPtr(src.m_funcPtr) {}

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return (obj->*(this->m_funcPtr))(arg1, arg2);
    }

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return (obj.*m_funcPtr)(arg1, arg2);
    }

protected:
    FunctionType m_funcPtr;
};

/** QEXTConstMemberFunctor1 wraps const methods with 1 argument(s).
 * Use the convenience function qextMemberFunctor() to create an instance of QEXTConstMemberFunctor1.
 *
 * The following template arguments are used:
 * - @e T_arg1 Argument type used in the definition of operator()().
 * - @e T_return The return type of operator()().
 * - @e T_obj The object type.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1>
class QEXTConstMemberFunctor1 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1) const;
    typedef T_return ResultType;

    // Constructs an invalid functor.
    QEXTConstMemberFunctor1() : m_funcPtr(QEXT_NULLPTR) {}
    /** Constructs a QEXTConstMemberFunctor1 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTConstMemberFunctor1(FunctionType func) : m_funcPtr(func) {}
    QEXTConstMemberFunctor1(const QEXTConstMemberFunctor1 &src) : m_funcPtr(src.m_funcPtr) {}

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(const T_obj *obj, typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return (obj->*(this->m_funcPtr))(arg1);
    }

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(const T_obj &obj, typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return (obj.*m_funcPtr)(arg1);
    }

protected:
    FunctionType m_funcPtr;
};

/** QEXTConstMemberFunctor0 wraps const methods with 0 argument(s).
 * Use the convenience function qextMemberFunctor() to create an instance of QEXTConstMemberFunctor0.
 *
 * The following template arguments are used:
 * - @e T_return The return type of operator()().
 * - @e T_obj The object type.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj>
class QEXTConstMemberFunctor0 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)() const;
    typedef T_return ResultType;

    // Constructs an invalid functor.
    QEXTConstMemberFunctor0() : m_funcPtr(QEXT_NULLPTR) {}
    /** Constructs a QEXTConstMemberFunctor0 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTConstMemberFunctor0(FunctionType func) : m_funcPtr(func) {}
    QEXTConstMemberFunctor0(const QEXTConstMemberFunctor0 &src) : m_funcPtr(src.m_funcPtr) {}

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @return The return value of the method invocation.
     */
    T_return operator()(const T_obj *obj) const {
        return (obj->*(this->m_funcPtr))();
    }

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @return The return value of the method invocation.
     */
    T_return operator()(const T_obj &obj) const {
        return (obj.*m_funcPtr)();
    }

protected:
    FunctionType m_funcPtr;
};

template <typename T_return, typename T_obj,
          typename T_arg1 = QEXTNil, typename T_arg2 = QEXTNil, typename T_arg3 = QEXTNil,
          typename T_arg4 = QEXTNil, typename T_arg5 = QEXTNil, typename T_arg6 = QEXTNil, typename T_arg7 = QEXTNil>
class QEXTConstMemberFunctor
        : public QEXTConstMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
{
    typedef QEXTConstMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTConstMemberFunctor() {}
    QEXTConstMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTConstMemberFunctor(const QEXTConstMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6,
                        typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6,
                        typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
class QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QEXTNil>
        : public QEXTConstMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
{
    typedef QEXTConstMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTConstMemberFunctor() {}
    QEXTConstMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTConstMemberFunctor(const QEXTConstMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4, arg5, arg6);
    }

    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QEXTNil, QEXTNil>
        : public QEXTConstMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
{
    typedef QEXTConstMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTConstMemberFunctor() {}
    QEXTConstMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTConstMemberFunctor(const QEXTConstMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4, arg5);
    }

    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4, arg5);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTConstMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
{
    typedef QEXTConstMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTConstMemberFunctor() {}
    QEXTConstMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTConstMemberFunctor(const QEXTConstMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4);
    }

    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
class QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTConstMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
{
    typedef QEXTConstMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTConstMemberFunctor() {}
    QEXTConstMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTConstMemberFunctor(const QEXTConstMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3);
    }

    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
class QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTConstMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
{
    typedef QEXTConstMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTConstMemberFunctor() {}
    QEXTConstMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTConstMemberFunctor(const QEXTConstMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return BaseType::operator ()(obj, arg1, arg2);
    }

    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return BaseType::operator ()(obj, arg1, arg2);
    }
};

template <typename T_return, typename T_obj, typename T_arg1>
class QEXTConstMemberFunctor<T_return, T_obj, T_arg1, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTConstMemberFunctor1<T_return, T_obj, T_arg1>
{
    typedef QEXTConstMemberFunctor1<T_return, T_obj, T_arg1> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTConstMemberFunctor() {}
    QEXTConstMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTConstMemberFunctor(const QEXTConstMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return BaseType::operator ()(obj, arg1);
    }

    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return BaseType::operator ()(obj, arg1);
    }
};

template <typename T_return, typename T_obj>
class QEXTConstMemberFunctor<T_return, T_obj, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTConstMemberFunctor0<T_return, T_obj>
{
    typedef QEXTConstMemberFunctor0<T_return, T_obj> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTConstMemberFunctor() {}
    QEXTConstMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTConstMemberFunctor(const QEXTConstMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(const T_obj *obj) const {
        return BaseType::operator ()(obj);
    }

    T_return operator()(const T_obj &obj) const {
        return BaseType::operator ()(obj);
    }
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
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
class QEXTVolatileMemberFunctor7 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) volatile;
    typedef T_return ResultType;

    // Constructs an invalid functor.
    QEXTVolatileMemberFunctor7() : m_funcPtr(QEXT_NULLPTR) {}
    /** Constructs a QEXTVolatileMemberFunctor7 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTVolatileMemberFunctor7(FunctionType func) : m_funcPtr(func) {}
    QEXTVolatileMemberFunctor7(const QEXTVolatileMemberFunctor7 &src) : m_funcPtr(src.m_funcPtr) {}

    /** Execute the wrapped method operating on the passed instance.
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
    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6,
                        typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return (obj->*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    /** Execute the wrapped method operating on the passed instance.
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
    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6,
                        typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

protected:
    FunctionType m_funcPtr;
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
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
class QEXTVolatileMemberFunctor6 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) volatile;
    typedef T_return ResultType;

    // Constructs an invalid functor.
    QEXTVolatileMemberFunctor6() : m_funcPtr(QEXT_NULLPTR) {}
    /** Constructs a QEXTVolatileMemberFunctor6 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTVolatileMemberFunctor6(FunctionType func) : m_funcPtr(func) {}
    QEXTVolatileMemberFunctor6(const QEXTVolatileMemberFunctor6 &src) : m_funcPtr(src.m_funcPtr) {}

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @param arg6 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return (obj->*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6);
    }

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @param arg6 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4, arg5, arg6);
    }

protected:
    FunctionType m_funcPtr;
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
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class QEXTVolatileMemberFunctor5 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) volatile;
    typedef T_return ResultType;

    // Constructs an invalid functor.
    QEXTVolatileMemberFunctor5() : m_funcPtr(QEXT_NULLPTR) {}
    /** Constructs a QEXTVolatileMemberFunctor5 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTVolatileMemberFunctor5(FunctionType func) : m_funcPtr(func) {}
    QEXTVolatileMemberFunctor5(const QEXTVolatileMemberFunctor5 &src) : m_funcPtr(src.m_funcPtr) {}

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return (obj->*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5);
    }

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4, arg5);
    }

protected:
    FunctionType m_funcPtr;
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
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class QEXTVolatileMemberFunctor4 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1, T_arg2, T_arg3, T_arg4) volatile;
    typedef T_return ResultType;

    // Constructs an invalid functor.
    QEXTVolatileMemberFunctor4() : m_funcPtr(QEXT_NULLPTR) {}
    /** Constructs a QEXTVolatileMemberFunctor4 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTVolatileMemberFunctor4(FunctionType func) : m_funcPtr(func) {}
    QEXTVolatileMemberFunctor4(const QEXTVolatileMemberFunctor4 &src) : m_funcPtr(src.m_funcPtr) {}

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return (obj->*(this->m_funcPtr))(arg1, arg2, arg3, arg4);
    }

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4);
    }

protected:
    FunctionType m_funcPtr;
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
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
class QEXTVolatileMemberFunctor3 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1, T_arg2, T_arg3) volatile;
    typedef T_return ResultType;

    // Constructs an invalid functor.
    QEXTVolatileMemberFunctor3() : m_funcPtr(QEXT_NULLPTR) {}
    /** Constructs a QEXTVolatileMemberFunctor3 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTVolatileMemberFunctor3(FunctionType func) : m_funcPtr(func) {}
    QEXTVolatileMemberFunctor3(const QEXTVolatileMemberFunctor3 &src) : m_funcPtr(src.m_funcPtr) {}

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return (obj->*(this->m_funcPtr))(arg1, arg2, arg3);
    }

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return (obj.*m_funcPtr)(arg1, arg2, arg3);
    }

protected:
    FunctionType m_funcPtr;
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
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
class QEXTVolatileMemberFunctor2 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1, T_arg2) volatile;
    typedef T_return ResultType;

    // Constructs an invalid functor.
    QEXTVolatileMemberFunctor2() : m_funcPtr(QEXT_NULLPTR) {}
    /** Constructs a QEXTVolatileMemberFunctor2 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTVolatileMemberFunctor2(FunctionType func) : m_funcPtr(func) {}
    QEXTVolatileMemberFunctor2(const QEXTVolatileMemberFunctor2 &src) : m_funcPtr(src.m_funcPtr) {}

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return (obj->*(this->m_funcPtr))(arg1, arg2);
    }

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return (obj.*m_funcPtr)(arg1, arg2);
    }

protected:
    FunctionType m_funcPtr;
};

/** QEXTVolatileMemberFunctor1 wraps volatile methods with 1 argument(s).
 * Use the convenience function qextMemberFunctor() to create an instance of QEXTVolatileMemberFunctor1.
 *
 * The following template arguments are used:
 * - @e T_arg1 Argument type used in the definition of operator()().
 * - @e T_return The return type of operator()().
 * - @e T_obj The object type.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1>
class QEXTVolatileMemberFunctor1 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1) volatile;
    typedef T_return ResultType;

    // Constructs an invalid functor.
    QEXTVolatileMemberFunctor1() : m_funcPtr(QEXT_NULLPTR) {}
    /** Constructs a QEXTVolatileMemberFunctor1 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTVolatileMemberFunctor1(FunctionType func) : m_funcPtr(func) {}
    QEXTVolatileMemberFunctor1(const QEXTVolatileMemberFunctor1 &src) : m_funcPtr(src.m_funcPtr) {}

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return (obj->*(this->m_funcPtr))(arg1);
    }

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return (obj.*m_funcPtr)(arg1);
    }

protected:
    FunctionType m_funcPtr;
};

/** QEXTVolatileMemberFunctor0 wraps volatile methods with 0 argument(s).
 * Use the convenience function qextMemberFunctor() to create an instance of QEXTVolatileMemberFunctor0.
 *
 * The following template arguments are used:
 * - @e T_return The return type of operator()().
 * - @e T_obj The object type.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj>
class QEXTVolatileMemberFunctor0 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)() volatile;
    typedef T_return ResultType;

    // Constructs an invalid functor.
    QEXTVolatileMemberFunctor0() : m_funcPtr(QEXT_NULLPTR) {}
    /** Constructs a QEXTVolatileMemberFunctor0 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTVolatileMemberFunctor0(FunctionType func) : m_funcPtr(func) {}
    QEXTVolatileMemberFunctor0(const QEXTVolatileMemberFunctor0 &src) : m_funcPtr(src.m_funcPtr) {}

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @return The return value of the method invocation.
     */
    T_return operator()(T_obj *obj) const {
        return (obj->*(this->m_funcPtr))();
    }

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @return The return value of the method invocation.
     */
    T_return operator()(T_obj &obj) const {
        return (obj.*m_funcPtr)();
    }

protected:
    FunctionType m_funcPtr;
};

template <typename T_return, typename T_obj,
          typename T_arg1 = QEXTNil, typename T_arg2 = QEXTNil, typename T_arg3 = QEXTNil,
          typename T_arg4 = QEXTNil, typename T_arg5 = QEXTNil, typename T_arg6 = QEXTNil, typename T_arg7 = QEXTNil>
class QEXTVolatileMemberFunctor
        : public QEXTVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
{
    typedef QEXTVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTVolatileMemberFunctor() {}
    QEXTVolatileMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTVolatileMemberFunctor(const QEXTVolatileMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6,
                        typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6,
                        typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
class QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QEXTNil>
        : public QEXTVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
{
    typedef QEXTVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTVolatileMemberFunctor() {}
    QEXTVolatileMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTVolatileMemberFunctor(const QEXTVolatileMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4, arg5, arg6);
    }

    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QEXTNil, QEXTNil>
        : public QEXTVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
{
    typedef QEXTVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTVolatileMemberFunctor() {}
    QEXTVolatileMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTVolatileMemberFunctor(const QEXTVolatileMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4, arg5);
    }

    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4, arg5);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
{
    typedef QEXTVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTVolatileMemberFunctor() {}
    QEXTVolatileMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTVolatileMemberFunctor(const QEXTVolatileMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4);
    }

    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
class QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
{
    typedef QEXTVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTVolatileMemberFunctor() {}
    QEXTVolatileMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTVolatileMemberFunctor(const QEXTVolatileMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3);
    }

    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
class QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
{
    typedef QEXTVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTVolatileMemberFunctor() {}
    QEXTVolatileMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTVolatileMemberFunctor(const QEXTVolatileMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return BaseType::operator ()(obj, arg1, arg2);
    }

    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return BaseType::operator ()(obj, arg1, arg2);
    }
};

template <typename T_return, typename T_obj, typename T_arg1>
class QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTVolatileMemberFunctor1<T_return, T_obj, T_arg1>
{
    typedef QEXTVolatileMemberFunctor1<T_return, T_obj, T_arg1> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTVolatileMemberFunctor() {}
    QEXTVolatileMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTVolatileMemberFunctor(const QEXTVolatileMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return BaseType::operator ()(obj, arg1);
    }

    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return BaseType::operator ()(obj, arg1);
    }
};

template <typename T_return, typename T_obj>
class QEXTVolatileMemberFunctor<T_return, T_obj, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTVolatileMemberFunctor0<T_return, T_obj>
{
    typedef QEXTVolatileMemberFunctor0<T_return, T_obj> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTVolatileMemberFunctor() {}
    QEXTVolatileMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTVolatileMemberFunctor(const QEXTVolatileMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(T_obj *obj) const {
        return BaseType::operator ()(obj);
    }

    T_return operator()(T_obj &obj) const {
        return BaseType::operator ()(obj);
    }
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
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
class QEXTConstVolatileMemberFunctor7 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const volatile;
    typedef T_return ResultType;

    // Constructs an invalid functor.
    QEXTConstVolatileMemberFunctor7() : m_funcPtr(QEXT_NULLPTR) {}
    /** Constructs a QEXTConstVolatileMemberFunctor7 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTConstVolatileMemberFunctor7(FunctionType func) : m_funcPtr(func) {}
    QEXTConstVolatileMemberFunctor7(const QEXTConstVolatileMemberFunctor7 &src) : m_funcPtr(src.m_funcPtr) {}

    /** Execute the wrapped method operating on the passed instance.
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
    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6,
                        typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return (obj->*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    /** Execute the wrapped method operating on the passed instance.
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
    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6,
                        typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

protected:
    FunctionType m_funcPtr;
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
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
class QEXTConstVolatileMemberFunctor6 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const volatile;
    typedef T_return ResultType;

    // Constructs an invalid functor.
    QEXTConstVolatileMemberFunctor6() : m_funcPtr(QEXT_NULLPTR) {}
    /** Constructs a QEXTConstVolatileMemberFunctor6 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTConstVolatileMemberFunctor6(FunctionType func) : m_funcPtr(func) {}
    QEXTConstVolatileMemberFunctor6(const QEXTConstVolatileMemberFunctor6 &src) : m_funcPtr(src.m_funcPtr) {}

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @param arg6 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return (obj->*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6);
    }

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @param arg6 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4, arg5, arg6);
    }

protected:
    FunctionType m_funcPtr;
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
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class QEXTConstVolatileMemberFunctor5 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const volatile;
    typedef T_return ResultType;

    // Constructs an invalid functor.
    QEXTConstVolatileMemberFunctor5() : m_funcPtr(QEXT_NULLPTR) {}
    /** Constructs a QEXTConstVolatileMemberFunctor5 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTConstVolatileMemberFunctor5(FunctionType func) : m_funcPtr(func) {}
    QEXTConstVolatileMemberFunctor5(const QEXTConstVolatileMemberFunctor5 &src) : m_funcPtr(src.m_funcPtr) {}

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return (obj->*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5);
    }

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4, arg5);
    }

protected:
    FunctionType m_funcPtr;
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
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class QEXTConstVolatileMemberFunctor4 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1, T_arg2, T_arg3, T_arg4) const volatile;
    typedef T_return ResultType;

    // Constructs an invalid functor.
    QEXTConstVolatileMemberFunctor4() : m_funcPtr(QEXT_NULLPTR) {}
    /** Constructs a QEXTConstVolatileMemberFunctor4 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTConstVolatileMemberFunctor4(FunctionType func) : m_funcPtr(func) {}
    QEXTConstVolatileMemberFunctor4(const QEXTConstVolatileMemberFunctor4 &src) : m_funcPtr(src.m_funcPtr) {}

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return (obj->*(this->m_funcPtr))(arg1, arg2, arg3, arg4);
    }

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4);
    }

protected:
    FunctionType m_funcPtr;
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
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
class QEXTConstVolatileMemberFunctor3 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1, T_arg2, T_arg3) const volatile;
    typedef T_return ResultType;

    // Constructs an invalid functor.
    QEXTConstVolatileMemberFunctor3() : m_funcPtr(QEXT_NULLPTR) {}
    /** Constructs a QEXTConstVolatileMemberFunctor3 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTConstVolatileMemberFunctor3(FunctionType func) : m_funcPtr(func) {}
    QEXTConstVolatileMemberFunctor3(const QEXTConstVolatileMemberFunctor3 &src) : m_funcPtr(src.m_funcPtr) {}

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return (obj->*(this->m_funcPtr))(arg1, arg2, arg3);
    }

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return (obj.*m_funcPtr)(arg1, arg2, arg3);
    }

protected:
    FunctionType m_funcPtr;
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
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
class QEXTConstVolatileMemberFunctor2 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1, T_arg2) const volatile;
    typedef T_return ResultType;

    // Constructs an invalid functor.
    QEXTConstVolatileMemberFunctor2() : m_funcPtr(QEXT_NULLPTR) {}
    /** Constructs a QEXTConstVolatileMemberFunctor2 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTConstVolatileMemberFunctor2(FunctionType func) : m_funcPtr(func) {}
    QEXTConstVolatileMemberFunctor2(const QEXTConstVolatileMemberFunctor2 &src) : m_funcPtr(src.m_funcPtr) {}

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return (obj->*(this->m_funcPtr))(arg1, arg2);
    }

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return (obj.*m_funcPtr)(arg1, arg2);
    }

protected:
    FunctionType m_funcPtr;
};

/** QEXTConstVolatileMemberFunctor1 wraps const volatile methods with 1 argument(s).
 * Use the convenience function qextMemberFunctor() to create an instance of QEXTConstVolatileMemberFunctor1.
 *
 * The following template arguments are used:
 * - @e T_arg1 Argument type used in the definition of operator()().
 * - @e T_return The return type of operator()().
 * - @e T_obj The object type.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1>
class QEXTConstVolatileMemberFunctor1 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1) const volatile;
    typedef T_return ResultType;

    // Constructs an invalid functor.
    QEXTConstVolatileMemberFunctor1() : m_funcPtr(QEXT_NULLPTR) {}
    /** Constructs a QEXTConstVolatileMemberFunctor1 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTConstVolatileMemberFunctor1(FunctionType func) : m_funcPtr(func) {}
    QEXTConstVolatileMemberFunctor1(const QEXTConstVolatileMemberFunctor1 &src) : m_funcPtr(src.m_funcPtr) {}

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return (obj->*(this->m_funcPtr))(arg1);
    }

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @param arg1 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return (obj.*m_funcPtr)(arg1);
    }

protected:
    FunctionType m_funcPtr;
};

/** QEXTConstVolatileMemberFunctor0 wraps const volatile methods with 0 argument(s).
 * Use the convenience function qextMemberFunctor() to create an instance of QEXTConstVolatileMemberFunctor0.
 *
 * The following template arguments are used:
 * - @e T_return The return type of operator()().
 * - @e T_obj The object type.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj>
class QEXTConstVolatileMemberFunctor0 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)() const volatile;
    typedef T_return ResultType;

    // Constructs an invalid functor.
    QEXTConstVolatileMemberFunctor0() : m_funcPtr(QEXT_NULLPTR) {}
    /** Constructs a QEXTConstVolatileMemberFunctor0 object that wraps the passed method.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTConstVolatileMemberFunctor0(FunctionType func) : m_funcPtr(func) {}
    QEXTConstVolatileMemberFunctor0(const QEXTConstVolatileMemberFunctor0 &src) : m_funcPtr(src.m_funcPtr) {}

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Pointer to instance the method should operate on.
     * @return The return value of the method invocation.
     */
    T_return operator()(const T_obj *obj) const {
        return (obj->*(this->m_funcPtr))();
    }

    /** Execute the wrapped method operating on the passed instance.
     * @param obj Reference to instance the method should operate on.
     * @return The return value of the method invocation.
     */
    T_return operator()(const T_obj &obj) const {
        return (obj.*m_funcPtr)();
    }

protected:
    FunctionType m_funcPtr;
};

template <typename T_return, typename T_obj,
          typename T_arg1 = QEXTNil, typename T_arg2 = QEXTNil, typename T_arg3 = QEXTNil,
          typename T_arg4 = QEXTNil, typename T_arg5 = QEXTNil, typename T_arg6 = QEXTNil, typename T_arg7 = QEXTNil>
class QEXTConstVolatileMemberFunctor
        : public QEXTConstVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
{
    typedef QEXTConstVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTConstVolatileMemberFunctor() {}
    QEXTConstVolatileMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTConstVolatileMemberFunctor(const QEXTConstVolatileMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6,
                        typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6,
                        typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
class QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QEXTNil>
        : public QEXTConstVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
{
    typedef QEXTConstVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTConstVolatileMemberFunctor() {}
    QEXTConstVolatileMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTConstVolatileMemberFunctor(const QEXTConstVolatileMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4, arg5, arg6);
    }

    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QEXTNil, QEXTNil>
        : public QEXTConstVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
{
    typedef QEXTConstVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTConstVolatileMemberFunctor() {}
    QEXTConstVolatileMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTConstVolatileMemberFunctor(const QEXTConstVolatileMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4, arg5);
    }

    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4, arg5);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTConstVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
{
    typedef QEXTConstVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTConstVolatileMemberFunctor() {}
    QEXTConstVolatileMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTConstVolatileMemberFunctor(const QEXTConstVolatileMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4);
    }

    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
class QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTConstVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
{
    typedef QEXTConstVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTConstVolatileMemberFunctor() {}
    QEXTConstVolatileMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTConstVolatileMemberFunctor(const QEXTConstVolatileMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3);
    }

    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
class QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTConstVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
{
    typedef QEXTConstVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTConstVolatileMemberFunctor() {}
    QEXTConstVolatileMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTConstVolatileMemberFunctor(const QEXTConstVolatileMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return BaseType::operator ()(obj, arg1, arg2);
    }

    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return BaseType::operator ()(obj, arg1, arg2);
    }
};

template <typename T_return, typename T_obj, typename T_arg1>
class QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTConstVolatileMemberFunctor1<T_return, T_obj, T_arg1>
{
    typedef QEXTConstVolatileMemberFunctor1<T_return, T_obj, T_arg1> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTConstVolatileMemberFunctor() {}
    QEXTConstVolatileMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTConstVolatileMemberFunctor(const QEXTConstVolatileMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return BaseType::operator ()(obj, arg1);
    }

    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return BaseType::operator ()(obj, arg1);
    }
};

template <typename T_return, typename T_obj>
class QEXTConstVolatileMemberFunctor<T_return, T_obj, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTConstVolatileMemberFunctor0<T_return, T_obj>
{
    typedef QEXTConstVolatileMemberFunctor0<T_return, T_obj> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTConstVolatileMemberFunctor() {}
    QEXTConstVolatileMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTConstVolatileMemberFunctor(const QEXTConstVolatileMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(const T_obj *obj) const {
        return BaseType::operator ()(obj);
    }

    T_return operator()(const T_obj &obj) const {
        return BaseType::operator ()(obj);
    }
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
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
class QEXTBoundMemberFunctor7
        : public QEXTMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
{
    typedef QEXTMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /** Constructs a QEXTBoundMemberFunctor7 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundMemberFunctor7(T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    /** Constructs a QEXTBoundMemberFunctor7 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundMemberFunctor7(T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundMemberFunctor7(const QEXTBoundMemberFunctor7 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    /** Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @param arg6 Argument to be passed on to the method.
     * @param arg7 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6,
                        typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QEXTLimitReference<T_obj> m_obj;
};

//template specialization of visitor<>::do_visit_each<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for QEXTBoundMemberFunctor performs a functor
 * on the object instance stored in the QEXTBoundMemberFunctor object.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
struct QEXTVisitor<QEXTBoundMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> &target) {
        qextVisitEach(action, target.m_obj);
    }
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
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
class QEXTBoundMemberFunctor6
        : public QEXTMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
{
    typedef QEXTMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /** Constructs a QEXTBoundMemberFunctor6 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundMemberFunctor6(T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    /** Constructs a QEXTBoundMemberFunctor6 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundMemberFunctor6(T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundMemberFunctor6(const QEXTBoundMemberFunctor6 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    /** Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @param arg6 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QEXTLimitReference<T_obj> m_obj;
};

//template specialization of visitor<>::do_visit_each<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for QEXTBoundMemberFunctor performs a functor
 * on the object instance stored in the QEXTBoundMemberFunctor object.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
struct QEXTVisitor<QEXTBoundMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> &target) {
        qextVisitEach(action, target.m_obj);
    }
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
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class QEXTBoundMemberFunctor5
        : public QEXTMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
{
    typedef QEXTMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /** Constructs a QEXTBoundMemberFunctor5 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundMemberFunctor5(T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    /** Constructs a QEXTBoundMemberFunctor5 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundMemberFunctor5(T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundMemberFunctor5(const QEXTBoundMemberFunctor5 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    /** Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QEXTLimitReference<T_obj> m_obj;
};

//template specialization of visitor<>::do_visit_each<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for QEXTBoundMemberFunctor performs a functor
 * on the object instance stored in the QEXTBoundMemberFunctor object.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
struct QEXTVisitor<QEXTBoundMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> &target) {
        qextVisitEach(action, target.m_obj);
    }
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
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class QEXTBoundMemberFunctor4
        : public QEXTMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
{
    typedef QEXTMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /** Constructs a QEXTBoundMemberFunctor4 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundMemberFunctor4(T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    /** Constructs a QEXTBoundMemberFunctor4 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundMemberFunctor4(T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundMemberFunctor4(const QEXTBoundMemberFunctor4 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    /** Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QEXTLimitReference<T_obj> m_obj;
};

//template specialization of visitor<>::do_visit_each<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for QEXTBoundMemberFunctor performs a functor
 * on the object instance stored in the QEXTBoundMemberFunctor object.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
struct QEXTVisitor<QEXTBoundMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> &target) {
        qextVisitEach(action, target.m_obj);
    }
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
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
class QEXTBoundMemberFunctor3
        : public QEXTMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
{
    typedef QEXTMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /** Constructs a QEXTBoundMemberFunctor3 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundMemberFunctor3(T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    /** Constructs a QEXTBoundMemberFunctor3 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundMemberFunctor3(T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundMemberFunctor3(const QEXTBoundMemberFunctor3 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    /** Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QEXTLimitReference<T_obj> m_obj;
};

//template specialization of visitor<>::do_visit_each<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for QEXTBoundMemberFunctor performs a functor
 * on the object instance stored in the QEXTBoundMemberFunctor object.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
struct QEXTVisitor<QEXTBoundMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> &target) {
        qextVisitEach(action, target.m_obj);
    }
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
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
class QEXTBoundMemberFunctor2
        : public QEXTMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
{
    typedef QEXTMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /** Constructs a QEXTBoundMemberFunctor2 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundMemberFunctor2(T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    /** Constructs a QEXTBoundMemberFunctor2 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundMemberFunctor2(T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundMemberFunctor2(const QEXTBoundMemberFunctor2 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    /** Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QEXTLimitReference<T_obj> m_obj;
};

//template specialization of visitor<>::do_visit_each<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for QEXTBoundMemberFunctor performs a functor
 * on the object instance stored in the QEXTBoundMemberFunctor object.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
struct QEXTVisitor<QEXTBoundMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

/** QEXTBoundMemberFunctor1 encapsulates a  method with 1 arguments and an object instance.
 * Use the convenience function qextMemberFunctor() to create an instance of QEXTBoundMemberFunctor1.
 *
 * The following template arguments are used:
 * - @e T_arg1 Argument type used in the definition of operator()().
 * - @e T_return The return type of operator()().
 * - @e T_obj The object type.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1>
class QEXTBoundMemberFunctor1
        : public QEXTMemberFunctor1<T_return, T_obj, T_arg1>
{
    typedef QEXTMemberFunctor1<T_return, T_obj, T_arg1> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /** Constructs a QEXTBoundMemberFunctor1 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundMemberFunctor1(T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    /** Constructs a QEXTBoundMemberFunctor1 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundMemberFunctor1(T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundMemberFunctor1(const QEXTBoundMemberFunctor1 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    /** Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QEXTLimitReference<T_obj> m_obj;
};

//template specialization of visitor<>::do_visit_each<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for QEXTBoundMemberFunctor performs a functor
 * on the object instance stored in the QEXTBoundMemberFunctor object.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1>
struct QEXTVisitor<QEXTBoundMemberFunctor1<T_return, T_obj, T_arg1> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundMemberFunctor1<T_return, T_obj, T_arg1> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

/** QEXTBoundMemberFunctor0 encapsulates a  method with 0 arguments and an object instance.
 * Use the convenience function qextMemberFunctor() to create an instance of QEXTBoundMemberFunctor0.
 *
 * The following template arguments are used:
 * - @e T_return The return type of operator()().
 * - @e T_obj The object type.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj>
class QEXTBoundMemberFunctor0
        : public QEXTMemberFunctor0<T_return, T_obj>
{
    typedef QEXTMemberFunctor0<T_return, T_obj> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /** Constructs a QEXTBoundMemberFunctor0 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundMemberFunctor0(T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    /** Constructs a QEXTBoundMemberFunctor0 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundMemberFunctor0(T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundMemberFunctor0(const QEXTBoundMemberFunctor0 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    /** Execute the wrapped method operating on the stored instance.
     * @return The return value of the method invocation.
     */
    T_return operator()() const {
        return (m_obj.invoke().*(this->m_funcPtr))();
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QEXTLimitReference<T_obj> m_obj;
};

//template specialization of visitor<>::do_visit_each<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for QEXTBoundMemberFunctor performs a functor
 * on the object instance stored in the QEXTBoundMemberFunctor object.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj>
struct QEXTVisitor<QEXTBoundMemberFunctor0<T_return, T_obj> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundMemberFunctor0<T_return, T_obj> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1 = QEXTNil, typename T_arg2 = QEXTNil, typename T_arg3 = QEXTNil,
          typename T_arg4 = QEXTNil, typename T_arg5 = QEXTNil, typename T_arg6 = QEXTNil, typename T_arg7 = QEXTNil>
class QEXTBoundMemberFunctor
        : public QEXTBoundMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
{
    typedef QEXTBoundMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundMemberFunctor(T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundMemberFunctor(T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundMemberFunctor(const QEXTBoundMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6,
                        typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return BaseType::operator ()(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
struct QEXTVisitor<QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
class QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QEXTNil>
        : public QEXTBoundMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
{
    typedef QEXTBoundMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundMemberFunctor(T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundMemberFunctor(T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundMemberFunctor(const QEXTBoundMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return BaseType::operator ()(arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
struct QEXTVisitor<QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QEXTNil, QEXTNil>
        : public QEXTBoundMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
{
    typedef QEXTBoundMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundMemberFunctor(T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundMemberFunctor(T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundMemberFunctor(const QEXTBoundMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return BaseType::operator ()(arg1, arg2, arg3, arg4, arg5);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
struct QEXTVisitor<QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTBoundMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
{
    typedef QEXTBoundMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundMemberFunctor(T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundMemberFunctor(T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundMemberFunctor(const QEXTBoundMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return BaseType::operator ()(arg1, arg2, arg3, arg4);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
struct QEXTVisitor<QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
class QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTBoundMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
{
    typedef QEXTBoundMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundMemberFunctor(T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundMemberFunctor(T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundMemberFunctor(const QEXTBoundMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return BaseType::operator ()(arg1, arg2, arg3);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
struct QEXTVisitor<QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
class QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTBoundMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
{
    typedef QEXTBoundMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundMemberFunctor(T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundMemberFunctor(T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundMemberFunctor(const QEXTBoundMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return BaseType::operator ()(arg1, arg2);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
struct QEXTVisitor<QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj, typename T_arg1>
class QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTBoundMemberFunctor1<T_return, T_obj, T_arg1>
{
    typedef QEXTBoundMemberFunctor1<T_return, T_obj, T_arg1> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundMemberFunctor(T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundMemberFunctor(T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundMemberFunctor(const QEXTBoundMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return BaseType::operator ()(arg1);
    }
};

template <typename T_return, typename T_obj, typename T_arg1>
struct QEXTVisitor<QEXTBoundMemberFunctor<T_return, T_obj, T_arg1> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundMemberFunctor<T_return, T_obj, T_arg1> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj>
class QEXTBoundMemberFunctor<T_return, T_obj, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTBoundMemberFunctor0<T_return, T_obj>
{
    typedef QEXTBoundMemberFunctor0<T_return, T_obj> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundMemberFunctor(T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundMemberFunctor(T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundMemberFunctor(const QEXTBoundMemberFunctor &src) : BaseType(src) {}

    T_return operator()() const {
        return BaseType::operator ()();
    }
};

template <typename T_return, typename T_obj>
struct QEXTVisitor<QEXTBoundMemberFunctor<T_return, T_obj> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundMemberFunctor<T_return, T_obj> &target) {
        qextVisitEach(action, target.m_obj);
    }
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
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
class QEXTBoundConstMemberFunctor7
        : public QEXTConstMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
{
    typedef QEXTConstMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /** Constructs a QEXTBoundConstMemberFunctor7 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundConstMemberFunctor7(const T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    /** Constructs a QEXTBoundConstMemberFunctor7 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundConstMemberFunctor7(const T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundConstMemberFunctor7(const QEXTBoundConstMemberFunctor7 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    /** Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @param arg6 Argument to be passed on to the method.
     * @param arg7 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6,
                        typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QEXTConstLimitReference<T_obj> m_obj;
};

//template specialization of visitor<>::do_visit_each<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for QEXTBoundConstMemberFunctor performs a functor
 * on the object instance stored in the QEXTBoundConstMemberFunctor object.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
struct QEXTVisitor<QEXTBoundConstMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> &target) {
        qextVisitEach(action, target.m_obj);
    }
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
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
class QEXTBoundConstMemberFunctor6
        : public QEXTConstMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
{
    typedef QEXTConstMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /** Constructs a QEXTBoundConstMemberFunctor6 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundConstMemberFunctor6(const T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    /** Constructs a QEXTBoundConstMemberFunctor6 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundConstMemberFunctor6(const T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundConstMemberFunctor6(const QEXTBoundConstMemberFunctor6 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    /** Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @param arg6 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QEXTConstLimitReference<T_obj> m_obj;
};

//template specialization of visitor<>::do_visit_each<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for QEXTBoundConstMemberFunctor performs a functor
 * on the object instance stored in the QEXTBoundConstMemberFunctor object.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
struct QEXTVisitor<QEXTBoundConstMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> &target) {
        qextVisitEach(action, target.m_obj);
    }
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
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class QEXTBoundConstMemberFunctor5
        : public QEXTConstMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
{
    typedef QEXTConstMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /** Constructs a QEXTBoundConstMemberFunctor5 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundConstMemberFunctor5(const T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    /** Constructs a QEXTBoundConstMemberFunctor5 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundConstMemberFunctor5(const T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundConstMemberFunctor5(const QEXTBoundConstMemberFunctor5 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    /** Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QEXTConstLimitReference<T_obj> m_obj;
};

//template specialization of visitor<>::do_visit_each<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for QEXTBoundConstMemberFunctor performs a functor
 * on the object instance stored in the QEXTBoundConstMemberFunctor object.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
struct QEXTVisitor<QEXTBoundConstMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> &target) {
        qextVisitEach(action, target.m_obj);
    }
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
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class QEXTBoundConstMemberFunctor4
        : public QEXTConstMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
{
    typedef QEXTConstMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /** Constructs a QEXTBoundConstMemberFunctor4 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundConstMemberFunctor4(const T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    /** Constructs a QEXTBoundConstMemberFunctor4 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundConstMemberFunctor4(const T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundConstMemberFunctor4(const QEXTBoundConstMemberFunctor4 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    /** Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QEXTConstLimitReference<T_obj> m_obj;
};

//template specialization of visitor<>::do_visit_each<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for QEXTBoundConstMemberFunctor performs a functor
 * on the object instance stored in the QEXTBoundConstMemberFunctor object.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
struct QEXTVisitor<QEXTBoundConstMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> &target) {
        qextVisitEach(action, target.m_obj);
    }
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
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
class QEXTBoundConstMemberFunctor3
        : public QEXTConstMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
{
    typedef QEXTConstMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /** Constructs a QEXTBoundConstMemberFunctor3 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundConstMemberFunctor3(const T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    /** Constructs a QEXTBoundConstMemberFunctor3 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundConstMemberFunctor3(const T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundConstMemberFunctor3(const QEXTBoundConstMemberFunctor3 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    /** Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QEXTConstLimitReference<T_obj> m_obj;
};

//template specialization of visitor<>::do_visit_each<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for QEXTBoundConstMemberFunctor performs a functor
 * on the object instance stored in the QEXTBoundConstMemberFunctor object.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
struct QEXTVisitor<QEXTBoundConstMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> &target) {
        qextVisitEach(action, target.m_obj);
    }
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
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
class QEXTBoundConstMemberFunctor2
        : public QEXTConstMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
{
    typedef QEXTConstMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /** Constructs a QEXTBoundConstMemberFunctor2 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundConstMemberFunctor2(const T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    /** Constructs a QEXTBoundConstMemberFunctor2 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundConstMemberFunctor2(const T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundConstMemberFunctor2(const QEXTBoundConstMemberFunctor2 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    /** Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QEXTConstLimitReference<T_obj> m_obj;
};

//template specialization of visitor<>::do_visit_each<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for QEXTBoundConstMemberFunctor performs a functor
 * on the object instance stored in the QEXTBoundConstMemberFunctor object.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
struct QEXTVisitor<QEXTBoundConstMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

/** QEXTBoundConstMemberFunctor1 encapsulates a const method with 1 arguments and an object instance.
 * Use the convenience function qextMemberFunctor() to create an instance of QEXTBoundConstMemberFunctor1.
 *
 * The following template arguments are used:
 * - @e T_arg1 Argument type used in the definition of operator()().
 * - @e T_return The return type of operator()().
 * - @e T_obj The object type.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1>
class QEXTBoundConstMemberFunctor1
        : public QEXTConstMemberFunctor1<T_return, T_obj, T_arg1>
{
    typedef QEXTConstMemberFunctor1<T_return, T_obj, T_arg1> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /** Constructs a QEXTBoundConstMemberFunctor1 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundConstMemberFunctor1(const T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    /** Constructs a QEXTBoundConstMemberFunctor1 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundConstMemberFunctor1(const T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundConstMemberFunctor1(const QEXTBoundConstMemberFunctor1 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    /** Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QEXTConstLimitReference<T_obj> m_obj;
};

//template specialization of visitor<>::do_visit_each<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for QEXTBoundConstMemberFunctor performs a functor
 * on the object instance stored in the QEXTBoundConstMemberFunctor object.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1>
struct QEXTVisitor<QEXTBoundConstMemberFunctor1<T_return, T_obj, T_arg1> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstMemberFunctor1<T_return, T_obj, T_arg1> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

/** QEXTBoundConstMemberFunctor0 encapsulates a const method with 0 arguments and an object instance.
 * Use the convenience function qextMemberFunctor() to create an instance of QEXTBoundConstMemberFunctor0.
 *
 * The following template arguments are used:
 * - @e T_return The return type of operator()().
 * - @e T_obj The object type.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj>
class QEXTBoundConstMemberFunctor0
        : public QEXTConstMemberFunctor0<T_return, T_obj>
{
    typedef QEXTConstMemberFunctor0<T_return, T_obj> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /** Constructs a QEXTBoundConstMemberFunctor0 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundConstMemberFunctor0(const T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    /** Constructs a QEXTBoundConstMemberFunctor0 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundConstMemberFunctor0(const T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundConstMemberFunctor0(const QEXTBoundConstMemberFunctor0 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    /** Execute the wrapped method operating on the stored instance.
     * @return The return value of the method invocation.
     */
    T_return operator()() const {
        return (m_obj.invoke().*(this->m_funcPtr))();
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QEXTConstLimitReference<T_obj> m_obj;
};

//template specialization of visitor<>::do_visit_each<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for QEXTBoundConstMemberFunctor performs a functor
 * on the object instance stored in the QEXTBoundConstMemberFunctor object.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj>
struct QEXTVisitor<QEXTBoundConstMemberFunctor0<T_return, T_obj> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstMemberFunctor0<T_return, T_obj> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1 = QEXTNil, typename T_arg2 = QEXTNil, typename T_arg3 = QEXTNil,
          typename T_arg4 = QEXTNil, typename T_arg5 = QEXTNil, typename T_arg6 = QEXTNil, typename T_arg7 = QEXTNil>
class QEXTBoundConstMemberFunctor
        : public QEXTBoundConstMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
{
    typedef QEXTBoundConstMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundConstMemberFunctor(const T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstMemberFunctor(const T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstMemberFunctor(const QEXTBoundConstMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6,
                        typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return BaseType::operator ()(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
struct QEXTVisitor<QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
class QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QEXTNil>
        : public QEXTBoundConstMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
{
    typedef QEXTBoundConstMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundConstMemberFunctor(const T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstMemberFunctor(const T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstMemberFunctor(const QEXTBoundConstMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return BaseType::operator ()(arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
struct QEXTVisitor<QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QEXTNil, QEXTNil>
        : public QEXTBoundConstMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
{
    typedef QEXTBoundConstMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundConstMemberFunctor(const T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstMemberFunctor(const T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstMemberFunctor(const QEXTBoundConstMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return BaseType::operator ()(arg1, arg2, arg3, arg4, arg5);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
struct QEXTVisitor<QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTBoundConstMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
{
    typedef QEXTBoundConstMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundConstMemberFunctor(const T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstMemberFunctor(const T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstMemberFunctor(const QEXTBoundConstMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return BaseType::operator ()(arg1, arg2, arg3, arg4);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
struct QEXTVisitor<QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
class QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTBoundConstMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
{
    typedef QEXTBoundConstMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundConstMemberFunctor(const T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstMemberFunctor(const T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstMemberFunctor(const QEXTBoundConstMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return BaseType::operator ()(arg1, arg2, arg3);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
struct QEXTVisitor<QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
class QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTBoundConstMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
{
    typedef QEXTBoundConstMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundConstMemberFunctor(const T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstMemberFunctor(const T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstMemberFunctor(const QEXTBoundConstMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return BaseType::operator ()(arg1, arg2);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
struct QEXTVisitor<QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj, typename T_arg1>
class QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTBoundConstMemberFunctor1<T_return, T_obj, T_arg1>
{
    typedef QEXTBoundConstMemberFunctor1<T_return, T_obj, T_arg1> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundConstMemberFunctor(const T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstMemberFunctor(const T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstMemberFunctor(const QEXTBoundConstMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return BaseType::operator ()(arg1);
    }
};

template <typename T_return, typename T_obj, typename T_arg1>
struct QEXTVisitor<QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj>
class QEXTBoundConstMemberFunctor<T_return, T_obj, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTBoundConstMemberFunctor0<T_return, T_obj>
{
    typedef QEXTBoundConstMemberFunctor0<T_return, T_obj> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundConstMemberFunctor(const T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstMemberFunctor(const T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstMemberFunctor(const QEXTBoundConstMemberFunctor &src) : BaseType(src) {}

    T_return operator()() const {
        return BaseType::operator ()();
    }
};

template <typename T_return, typename T_obj>
struct QEXTVisitor<QEXTBoundConstMemberFunctor<T_return, T_obj> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstMemberFunctor<T_return, T_obj> &target) {
        qextVisitEach(action, target.m_obj);
    }
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
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
class QEXTBoundVolatileMemberFunctor7
        : public QEXTVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
{
    typedef QEXTVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /** Constructs a QEXTBoundVolatileMemberFunctor7 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundVolatileMemberFunctor7(T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    /** Constructs a QEXTBoundVolatileMemberFunctor7 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundVolatileMemberFunctor7(T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundVolatileMemberFunctor7(const QEXTBoundVolatileMemberFunctor7 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    /** Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @param arg6 Argument to be passed on to the method.
     * @param arg7 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6,
                        typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QEXTVolatileLimitReference<T_obj> m_obj;
};

//template specialization of visitor<>::do_visit_each<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for QEXTBoundVolatileMemberFunctor performs a functor
 * on the object instance stored in the QEXTBoundVolatileMemberFunctor object.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
struct QEXTVisitor<QEXTBoundVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> &target) {
        qextVisitEach(action, target.m_obj);
    }
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
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
class QEXTBoundVolatileMemberFunctor6
        : public QEXTVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
{
    typedef QEXTVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /** Constructs a QEXTBoundVolatileMemberFunctor6 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundVolatileMemberFunctor6(T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    /** Constructs a QEXTBoundVolatileMemberFunctor6 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundVolatileMemberFunctor6(T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundVolatileMemberFunctor6(const QEXTBoundVolatileMemberFunctor6 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    /** Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @param arg6 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QEXTVolatileLimitReference<T_obj> m_obj;
};

//template specialization of visitor<>::do_visit_each<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for QEXTBoundVolatileMemberFunctor performs a functor
 * on the object instance stored in the QEXTBoundVolatileMemberFunctor object.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
struct QEXTVisitor<QEXTBoundVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> &target) {
        qextVisitEach(action, target.m_obj);
    }
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
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class QEXTBoundVolatileMemberFunctor5
        : public QEXTVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
{
    typedef QEXTVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /** Constructs a QEXTBoundVolatileMemberFunctor5 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundVolatileMemberFunctor5(T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    /** Constructs a QEXTBoundVolatileMemberFunctor5 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundVolatileMemberFunctor5(T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundVolatileMemberFunctor5(const QEXTBoundVolatileMemberFunctor5 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    /** Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QEXTVolatileLimitReference<T_obj> m_obj;
};

//template specialization of visitor<>::do_visit_each<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for QEXTBoundVolatileMemberFunctor performs a functor
 * on the object instance stored in the QEXTBoundVolatileMemberFunctor object.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
struct QEXTVisitor<QEXTBoundVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> &target) {
        qextVisitEach(action, target.m_obj);
    }
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
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class QEXTBoundVolatileMemberFunctor4
        : public QEXTVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
{
    typedef QEXTVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /** Constructs a QEXTBoundVolatileMemberFunctor4 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundVolatileMemberFunctor4(T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    /** Constructs a QEXTBoundVolatileMemberFunctor4 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundVolatileMemberFunctor4(T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundVolatileMemberFunctor4(const QEXTBoundVolatileMemberFunctor4 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    /** Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QEXTVolatileLimitReference<T_obj> m_obj;
};

//template specialization of visitor<>::do_visit_each<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for QEXTBoundVolatileMemberFunctor performs a functor
 * on the object instance stored in the QEXTBoundVolatileMemberFunctor object.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
struct QEXTVisitor<QEXTBoundVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> &target) {
        qextVisitEach(action, target.m_obj);
    }
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
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
class QEXTBoundVolatileMemberFunctor3
        : public QEXTVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
{
    typedef QEXTVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /** Constructs a QEXTBoundVolatileMemberFunctor3 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundVolatileMemberFunctor3(T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    /** Constructs a QEXTBoundVolatileMemberFunctor3 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundVolatileMemberFunctor3(T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundVolatileMemberFunctor3(const QEXTBoundVolatileMemberFunctor3 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    /** Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QEXTVolatileLimitReference<T_obj> m_obj;
};

//template specialization of visitor<>::do_visit_each<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for QEXTBoundVolatileMemberFunctor performs a functor
 * on the object instance stored in the QEXTBoundVolatileMemberFunctor object.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
struct QEXTVisitor<QEXTBoundVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> &target) {
        qextVisitEach(action, target.m_obj);
    }
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
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
class QEXTBoundVolatileMemberFunctor2
        : public QEXTVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
{
    typedef QEXTVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /** Constructs a QEXTBoundVolatileMemberFunctor2 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundVolatileMemberFunctor2(T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    /** Constructs a QEXTBoundVolatileMemberFunctor2 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundVolatileMemberFunctor2(T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundVolatileMemberFunctor2(const QEXTBoundVolatileMemberFunctor2 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    /** Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QEXTVolatileLimitReference<T_obj> m_obj;
};

//template specialization of visitor<>::do_visit_each<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for QEXTBoundVolatileMemberFunctor performs a functor
 * on the object instance stored in the QEXTBoundVolatileMemberFunctor object.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
struct QEXTVisitor<QEXTBoundVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

/** QEXTBoundVolatileMemberFunctor1 encapsulates a volatile method with 1 arguments and an object instance.
 * Use the convenience function qextMemberFunctor() to create an instance of QEXTBoundVolatileMemberFunctor1.
 *
 * The following template arguments are used:
 * - @e T_arg1 Argument type used in the definition of operator()().
 * - @e T_return The return type of operator()().
 * - @e T_obj The object type.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1>
class QEXTBoundVolatileMemberFunctor1
        : public QEXTVolatileMemberFunctor1<T_return, T_obj, T_arg1>
{
    typedef QEXTVolatileMemberFunctor1<T_return, T_obj, T_arg1> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /** Constructs a QEXTBoundVolatileMemberFunctor1 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundVolatileMemberFunctor1( T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    /** Constructs a QEXTBoundVolatileMemberFunctor1 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundVolatileMemberFunctor1( T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundVolatileMemberFunctor1(const QEXTBoundVolatileMemberFunctor1 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    /** Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QEXTVolatileLimitReference<T_obj> m_obj;
};

//template specialization of visitor<>::do_visit_each<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for QEXTBoundVolatileMemberFunctor performs a functor
 * on the object instance stored in the QEXTBoundVolatileMemberFunctor object.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1>
struct QEXTVisitor<QEXTBoundVolatileMemberFunctor1<T_return, T_obj, T_arg1> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundVolatileMemberFunctor1<T_return, T_obj, T_arg1> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

/** QEXTBoundVolatileMemberFunctor0 encapsulates a volatile method with 0 arguments and an object instance.
 * Use the convenience function qextMemberFunctor() to create an instance of QEXTBoundVolatileMemberFunctor0.
 *
 * The following template arguments are used:
 * - @e T_return The return type of operator()().
 * - @e T_obj The object type.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj>
class QEXTBoundVolatileMemberFunctor0
        : public QEXTVolatileMemberFunctor0<T_return, T_obj>
{
    typedef QEXTVolatileMemberFunctor0<T_return, T_obj> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /** Constructs a QEXTBoundVolatileMemberFunctor0 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundVolatileMemberFunctor0(T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    /** Constructs a QEXTBoundVolatileMemberFunctor0 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundVolatileMemberFunctor0(T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundVolatileMemberFunctor0(const QEXTBoundVolatileMemberFunctor0 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    /** Execute the wrapped method operating on the stored instance.
     * @return The return value of the method invocation.
     */
    T_return operator()() const {
        return (m_obj.invoke().*(this->m_funcPtr))();
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QEXTVolatileLimitReference<T_obj> m_obj;
};

//template specialization of visitor<>::do_visit_each<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for QEXTBoundVolatileMemberFunctor performs a functor
 * on the object instance stored in the QEXTBoundVolatileMemberFunctor object.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj>
struct QEXTVisitor<QEXTBoundVolatileMemberFunctor0<T_return, T_obj> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundVolatileMemberFunctor0<T_return, T_obj> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1 = QEXTNil, typename T_arg2 = QEXTNil, typename T_arg3 = QEXTNil,
          typename T_arg4 = QEXTNil, typename T_arg5 = QEXTNil, typename T_arg6 = QEXTNil, typename T_arg7 = QEXTNil>
class QEXTBoundVolatileMemberFunctor
        : public QEXTBoundVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
{
    typedef QEXTBoundVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundVolatileMemberFunctor(T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundVolatileMemberFunctor(T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundVolatileMemberFunctor(const QEXTBoundVolatileMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6,
                        typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return BaseType::operator ()(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
struct QEXTVisitor<QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
class QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QEXTNil>
        : public QEXTBoundVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
{
    typedef QEXTBoundVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundVolatileMemberFunctor(T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundVolatileMemberFunctor(T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundVolatileMemberFunctor(const QEXTBoundVolatileMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return BaseType::operator ()(arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
struct QEXTVisitor<QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QEXTNil, QEXTNil>
        : public QEXTBoundVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
{
    typedef QEXTBoundVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundVolatileMemberFunctor(T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundVolatileMemberFunctor(T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundVolatileMemberFunctor(const QEXTBoundVolatileMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return BaseType::operator ()(arg1, arg2, arg3, arg4, arg5);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
struct QEXTVisitor<QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTBoundVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
{
    typedef QEXTBoundVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundVolatileMemberFunctor(T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundVolatileMemberFunctor(T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundVolatileMemberFunctor(const QEXTBoundVolatileMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return BaseType::operator ()(arg1, arg2, arg3, arg4);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
struct QEXTVisitor<QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
class QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTBoundVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
{
    typedef QEXTBoundVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundVolatileMemberFunctor(T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundVolatileMemberFunctor(T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundVolatileMemberFunctor(const QEXTBoundVolatileMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return BaseType::operator ()(arg1, arg2, arg3);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
struct QEXTVisitor<QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
class QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTBoundVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
{
    typedef QEXTBoundVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundVolatileMemberFunctor(T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundVolatileMemberFunctor(T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundVolatileMemberFunctor(const QEXTBoundVolatileMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return BaseType::operator ()(arg1, arg2);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
struct QEXTVisitor<QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj, typename T_arg1>
class QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTBoundVolatileMemberFunctor1<T_return, T_obj, T_arg1>
{
    typedef QEXTBoundVolatileMemberFunctor1<T_return, T_obj, T_arg1> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundVolatileMemberFunctor(T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundVolatileMemberFunctor(T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundVolatileMemberFunctor(const QEXTBoundVolatileMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return BaseType::operator ()(arg1);
    }
};

template <typename T_return, typename T_obj, typename T_arg1>
struct QEXTVisitor<QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj>
class QEXTBoundVolatileMemberFunctor<T_return, T_obj, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTBoundVolatileMemberFunctor0<T_return, T_obj>
{
    typedef QEXTBoundVolatileMemberFunctor0<T_return, T_obj> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundVolatileMemberFunctor(T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundVolatileMemberFunctor(T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundVolatileMemberFunctor(const QEXTBoundVolatileMemberFunctor &src) : BaseType(src) {}

    T_return operator()() const {
        return BaseType::operator ()();
    }
};

template <typename T_return, typename T_obj>
struct QEXTVisitor<QEXTBoundVolatileMemberFunctor<T_return, T_obj> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundVolatileMemberFunctor<T_return, T_obj> &target) {
        qextVisitEach(action, target.m_obj);
    }
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
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
class QEXTBoundConstVolatileMemberFunctor7
        : public QEXTConstVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
{
    typedef QEXTConstVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /** Constructs a QEXTBoundConstVolatileMemberFunctor7 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundConstVolatileMemberFunctor7(const T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    /** Constructs a QEXTBoundConstVolatileMemberFunctor7 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundConstVolatileMemberFunctor7(const T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundConstVolatileMemberFunctor7(const QEXTBoundConstVolatileMemberFunctor7 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    /** Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @param arg6 Argument to be passed on to the method.
     * @param arg7 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6,
                        typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QEXTConstVolatileLimitReference<T_obj> m_obj;
};

//template specialization of visitor<>::do_visit_each<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for QEXTBoundConstVolatileMemberFunctor performs a functor
 * on the object instance stored in the QEXTBoundConstVolatileMemberFunctor object.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
struct QEXTVisitor<QEXTBoundConstVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> &target) {
        qextVisitEach(action, target.m_obj);
    }
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
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
class QEXTBoundConstVolatileMemberFunctor6
        : public QEXTConstVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
{
    typedef QEXTConstVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /** Constructs a QEXTBoundConstVolatileMemberFunctor6 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundConstVolatileMemberFunctor6(const T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    /** Constructs a QEXTBoundConstVolatileMemberFunctor6 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundConstVolatileMemberFunctor6(const T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundConstVolatileMemberFunctor6(const QEXTBoundConstVolatileMemberFunctor6 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    /** Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @param arg6 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QEXTConstVolatileLimitReference<T_obj> m_obj;
};

//template specialization of visitor<>::do_visit_each<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for QEXTBoundConstVolatileMemberFunctor performs a functor
 * on the object instance stored in the QEXTBoundConstVolatileMemberFunctor object.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
struct QEXTVisitor<QEXTBoundConstVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> &target) {
        qextVisitEach(action, target.m_obj);
    }
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
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class QEXTBoundConstVolatileMemberFunctor5
        : public QEXTConstVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
{
    typedef QEXTConstVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /** Constructs a QEXTBoundConstVolatileMemberFunctor5 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundConstVolatileMemberFunctor5(const T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    /** Constructs a QEXTBoundConstVolatileMemberFunctor5 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundConstVolatileMemberFunctor5(const T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundConstVolatileMemberFunctor5(const QEXTBoundConstVolatileMemberFunctor5 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    /** Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @param arg5 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QEXTConstVolatileLimitReference<T_obj> m_obj;
};

//template specialization of visitor<>::do_visit_each<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for QEXTBoundConstVolatileMemberFunctor performs a functor
 * on the object instance stored in the QEXTBoundConstVolatileMemberFunctor object.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
struct QEXTVisitor<QEXTBoundConstVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> &target) {
        qextVisitEach(action, target.m_obj);
    }
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
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class QEXTBoundConstVolatileMemberFunctor4
        : public QEXTConstVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
{
    typedef QEXTConstVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /** Constructs a QEXTBoundConstVolatileMemberFunctor4 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundConstVolatileMemberFunctor4(const T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    /** Constructs a QEXTBoundConstVolatileMemberFunctor4 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundConstVolatileMemberFunctor4(const T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundConstVolatileMemberFunctor4(const QEXTBoundConstVolatileMemberFunctor4 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    /** Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @param arg4 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QEXTConstVolatileLimitReference<T_obj> m_obj;
};

//template specialization of visitor<>::do_visit_each<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for QEXTBoundConstVolatileMemberFunctor performs a functor
 * on the object instance stored in the QEXTBoundConstVolatileMemberFunctor object.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
struct QEXTVisitor<QEXTBoundConstVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> &target) {
        qextVisitEach(action, target.m_obj);
    }
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
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
class QEXTBoundConstVolatileMemberFunctor3
        : public QEXTConstVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
{
    typedef QEXTConstVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /** Constructs a QEXTBoundConstVolatileMemberFunctor3 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundConstVolatileMemberFunctor3(const T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    /** Constructs a QEXTBoundConstVolatileMemberFunctor3 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundConstVolatileMemberFunctor3(const T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundConstVolatileMemberFunctor3(const QEXTBoundConstVolatileMemberFunctor3 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    /** Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @param arg3 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QEXTConstVolatileLimitReference<T_obj> m_obj;
};

//template specialization of visitor<>::do_visit_each<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for QEXTBoundConstVolatileMemberFunctor performs a functor
 * on the object instance stored in the QEXTBoundConstVolatileMemberFunctor object.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
struct QEXTVisitor<QEXTBoundConstVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> &target) {
        qextVisitEach(action, target.m_obj);
    }
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
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
class QEXTBoundConstVolatileMemberFunctor2
        : public QEXTConstVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
{
    typedef QEXTConstVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /** Constructs a QEXTBoundConstVolatileMemberFunctor2 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundConstVolatileMemberFunctor2(const T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    /** Constructs a QEXTBoundConstVolatileMemberFunctor2 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundConstVolatileMemberFunctor2(const T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundConstVolatileMemberFunctor2(const QEXTBoundConstVolatileMemberFunctor2 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    /** Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @param arg2 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QEXTConstVolatileLimitReference<T_obj> m_obj;
};

//template specialization of visitor<>::do_visit_each<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for QEXTBoundConstVolatileMemberFunctor performs a functor
 * on the object instance stored in the QEXTBoundConstVolatileMemberFunctor object.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
struct QEXTVisitor<QEXTBoundConstVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

/** QEXTBoundConstVolatileMemberFunctor1 encapsulates a const volatile method with 1 arguments and an object instance.
 * Use the convenience function qextMemberFunctor() to create an instance of QEXTBoundConstVolatileMemberFunctor1.
 *
 * The following template arguments are used:
 * - @e T_arg1 Argument type used in the definition of operator()().
 * - @e T_return The return type of operator()().
 * - @e T_obj The object type.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1>
class QEXTBoundConstVolatileMemberFunctor1
        : public QEXTConstVolatileMemberFunctor1<T_return, T_obj, T_arg1>
{
    typedef QEXTConstVolatileMemberFunctor1<T_return, T_obj, T_arg1> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /** Constructs a QEXTBoundConstVolatileMemberFunctor1 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundConstVolatileMemberFunctor1(const T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    /** Constructs a QEXTBoundConstVolatileMemberFunctor1 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundConstVolatileMemberFunctor1(const T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundConstVolatileMemberFunctor1(const QEXTBoundConstVolatileMemberFunctor1 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    /** Execute the wrapped method operating on the stored instance.
     * @param arg1 Argument to be passed on to the method.
     * @return The return value of the method invocation.
     */
    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1);
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QEXTConstVolatileLimitReference<T_obj> m_obj;
};

//template specialization of visitor<>::do_visit_each<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for QEXTBoundConstVolatileMemberFunctor performs a functor
 * on the object instance stored in the QEXTBoundConstVolatileMemberFunctor object.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1>
struct QEXTVisitor<QEXTBoundConstVolatileMemberFunctor1<T_return, T_obj, T_arg1> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstVolatileMemberFunctor1<T_return, T_obj, T_arg1> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

/** QEXTBoundConstVolatileMemberFunctor0 encapsulates a const volatile method with 0 arguments and an object instance.
 * Use the convenience function qextMemberFunctor() to create an instance of QEXTBoundConstVolatileMemberFunctor0.
 *
 * The following template arguments are used:
 * - @e T_return The return type of operator()().
 * - @e T_obj The object type.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj>
class QEXTBoundConstVolatileMemberFunctor0
        : public QEXTConstVolatileMemberFunctor0<T_return, T_obj>
{
    typedef QEXTConstVolatileMemberFunctor0<T_return, T_obj> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    /** Constructs a QEXTBoundConstVolatileMemberFunctor0 object that wraps the passed method.
     * @param obj Pointer to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundConstVolatileMemberFunctor0(const T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    /** Constructs a QEXTBoundConstVolatileMemberFunctor0 object that wraps the passed method.
     * @param obj Reference to instance the method will operate on.
     * @param func Pointer to method will be invoked from operator()().
     */
    QEXTBoundConstVolatileMemberFunctor0(const T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundConstVolatileMemberFunctor0(const QEXTBoundConstVolatileMemberFunctor0 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    /** Execute the wrapped method operating on the stored instance.
     * @return The return value of the method invocation.
     */
    T_return operator()() const {
        return (m_obj.invoke().*(this->m_funcPtr))();
    }

    // Reference to stored object instance.
    // This is the handler object, such as TheObject in void TheObject::signal_handler().
    QEXTConstVolatileLimitReference<T_obj> m_obj;
};

//template specialization of visitor<>::do_visit_each<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for QEXTBoundConstVolatileMemberFunctor performs a functor
 * on the object instance stored in the QEXTBoundConstVolatileMemberFunctor object.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj>
struct QEXTVisitor<QEXTBoundConstVolatileMemberFunctor0<T_return, T_obj> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstVolatileMemberFunctor0<T_return, T_obj> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1 = QEXTNil, typename T_arg2 = QEXTNil, typename T_arg3 = QEXTNil,
          typename T_arg4 = QEXTNil, typename T_arg5 = QEXTNil, typename T_arg6 = QEXTNil, typename T_arg7 = QEXTNil>
class QEXTBoundConstVolatileMemberFunctor
        : public QEXTBoundConstVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
{
    typedef QEXTBoundConstVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundConstVolatileMemberFunctor(const T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstVolatileMemberFunctor(const T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstVolatileMemberFunctor(const QEXTBoundConstVolatileMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6,
                        typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return BaseType::operator ()(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
struct QEXTVisitor<QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
class QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QEXTNil>
        : public QEXTBoundConstVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
{
    typedef QEXTBoundConstVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundConstVolatileMemberFunctor(const T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstVolatileMemberFunctor(const T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstVolatileMemberFunctor(const QEXTBoundConstVolatileMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return BaseType::operator ()(arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
struct QEXTVisitor<QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QEXTNil, QEXTNil>
        : public QEXTBoundConstVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
{
    typedef QEXTBoundConstVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundConstVolatileMemberFunctor(const T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstVolatileMemberFunctor(const T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstVolatileMemberFunctor(const QEXTBoundConstVolatileMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return BaseType::operator ()(arg1, arg2, arg3, arg4, arg5);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
struct QEXTVisitor<QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTBoundConstVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
{
    typedef QEXTBoundConstVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundConstVolatileMemberFunctor(const T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstVolatileMemberFunctor(const T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstVolatileMemberFunctor(const QEXTBoundConstVolatileMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return BaseType::operator ()(arg1, arg2, arg3, arg4);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
struct QEXTVisitor<QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
class QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTBoundConstVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
{
    typedef QEXTBoundConstVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundConstVolatileMemberFunctor(const T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstVolatileMemberFunctor(const T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstVolatileMemberFunctor(const QEXTBoundConstVolatileMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return BaseType::operator ()(arg1, arg2, arg3);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
struct QEXTVisitor<QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
class QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTBoundConstVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
{
    typedef QEXTBoundConstVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundConstVolatileMemberFunctor(const T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstVolatileMemberFunctor(const T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstVolatileMemberFunctor(const QEXTBoundConstVolatileMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return BaseType::operator ()(arg1, arg2);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
struct QEXTVisitor<QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj, typename T_arg1>
class QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTBoundConstVolatileMemberFunctor1<T_return, T_obj, T_arg1>
{
    typedef QEXTBoundConstVolatileMemberFunctor1<T_return, T_obj, T_arg1> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundConstVolatileMemberFunctor(const T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstVolatileMemberFunctor(const T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstVolatileMemberFunctor(const QEXTBoundConstVolatileMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return BaseType::operator ()(arg1);
    }
};

template <typename T_return, typename T_obj, typename T_arg1>
struct QEXTVisitor<QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj>
class QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTBoundConstVolatileMemberFunctor0<T_return, T_obj>
{
    typedef QEXTBoundConstVolatileMemberFunctor0<T_return, T_obj> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundConstVolatileMemberFunctor(const T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstVolatileMemberFunctor(const T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstVolatileMemberFunctor(const QEXTBoundConstVolatileMemberFunctor &src) : BaseType(src) {}

    T_return operator()() const {
        return BaseType::operator ()();
    }
};

template <typename T_return, typename T_obj>
struct QEXTVisitor<QEXTBoundConstVolatileMemberFunctor<T_return, T_obj> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstVolatileMemberFunctor<T_return, T_obj> &target) {
        qextVisitEach(action, target.m_obj);
    }
};


// numbered
/** Creates a functor of type QEXTMemberFunctor7 which wraps a  method.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor7(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) ) {
    return QEXTMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(func);
}

/** Creates a functor of type QEXTMemberFunctor6 which wraps a  method.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor6(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) ) {
    return QEXTMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(func);
}

/** Creates a functor of type QEXTMemberFunctor5 which wraps a  method.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor5(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) ) {
    return QEXTMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(func);
}

/** Creates a functor of type QEXTMemberFunctor4 which wraps a  method.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor4(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4) ) {
    return QEXTMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(func);
}

/** Creates a functor of type QEXTMemberFunctor3 which wraps a  method.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor3(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3) ) {
    return QEXTMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>(func);
}

/** Creates a functor of type QEXTMemberFunctor2 which wraps a  method.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QEXTMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor2(T_return (T_obj::*func)(T_arg1, T_arg2) ) {
    return QEXTMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>(func);
}

/** Creates a functor of type QEXTMemberFunctor1 which wraps a  method.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1>
inline QEXTMemberFunctor1<T_return, T_obj, T_arg1>
qextMemberFunctor1(T_return (T_obj::*func)(T_arg1) ) {
    return QEXTMemberFunctor1<T_return, T_obj, T_arg1>(func);
}

/** Creates a functor of type QEXTMemberFunctor0 which wraps a  method.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj>
inline QEXTMemberFunctor0<T_return, T_obj>
qextMemberFunctor0(T_return (T_obj::*func)() ) {
    return QEXTMemberFunctor0<T_return, T_obj>(func);
}

/** Creates a functor of type QEXTMemberFunctor which wraps a method with 7 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) ) {
    return QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(func);
}

/** Creates a functor of type QEXTMemberFunctor which wraps a method with 6 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) ) {
    return QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(func);
}

/** Creates a functor of type QEXTMemberFunctor which wraps a method with 5 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) ) {
    return QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(func);
}

/** Creates a functor of type QEXTMemberFunctor which wraps a method with 4 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4) ) {
    return QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(func);
}

/** Creates a functor of type QEXTMemberFunctor which wraps a method with 3 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3) ) {
    return QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>(func);
}

/** Creates a functor of type QEXTMemberFunctor which wraps a method with 2 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2) ) {
    return QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2>(func);
}

/** Creates a functor of type QEXTMemberFunctor which wraps a method with 1 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1>
inline QEXTMemberFunctor<T_return, T_obj, T_arg1>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1) ) {
    return QEXTMemberFunctor<T_return, T_obj, T_arg1>(func);
}

/** Creates a functor of type QEXTMemberFunctor which wraps a method with no args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj>
inline QEXTMemberFunctor<T_return, T_obj>
qextMemberFunctor(T_return (T_obj::*func)() ) {
    return QEXTMemberFunctor<T_return, T_obj>(func);
}



/** Creates a functor of type QEXTConstMemberFunctor7 which wraps a const method.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTConstMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor7(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const) {
    return QEXTConstMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(func);
}

/** Creates a functor of type QEXTConstMemberFunctor6 which wraps a const method.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTConstMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor6(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const) {
    return QEXTConstMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(func);
}

/** Creates a functor of type QEXTConstMemberFunctor5 which wraps a const method.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTConstMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor5(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const) {
    return QEXTConstMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(func);
}

/** Creates a functor of type QEXTConstMemberFunctor4 which wraps a const method.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTConstMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor4(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4) const) {
    return QEXTConstMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(func);
}

/** Creates a functor of type QEXTConstMemberFunctor3 which wraps a const method.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTConstMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor3(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3) const) {
    return QEXTConstMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>(func);
}

/** Creates a functor of type QEXTConstMemberFunctor2 which wraps a const method.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QEXTConstMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor2(T_return (T_obj::*func)(T_arg1, T_arg2) const) {
    return QEXTConstMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>(func);
}

/** Creates a functor of type QEXTConstMemberFunctor1 which wraps a const method.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1>
inline QEXTConstMemberFunctor1<T_return, T_obj, T_arg1>
qextMemberFunctor1(T_return (T_obj::*func)(T_arg1) const) {
    return QEXTConstMemberFunctor1<T_return, T_obj, T_arg1>(func);
}

/** Creates a functor of type QEXTConstMemberFunctor0 which wraps a const method.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj>
inline QEXTConstMemberFunctor0<T_return, T_obj>
qextMemberFunctor0(T_return (T_obj::*func)() const) {
    return QEXTConstMemberFunctor0<T_return, T_obj>(func);
}

/** Creates a functor of type QEXTConstMemberFunctor which wraps a const method with 7 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const) {
    return QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(func);
}

/** Creates a functor of type QEXTConstMemberFunctor which wraps a const method with 6 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const) {
    return QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(func);
}

/** Creates a functor of type QEXTConstMemberFunctor which wraps a const method with 5 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const) {
    return QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(func);
}

/** Creates a functor of type QEXTConstMemberFunctor which wraps a const method with 4 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4) const) {
    return QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(func);
}

/** Creates a functor of type QEXTConstMemberFunctor which wraps a const method with 3 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3) const) {
    return QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>(func);
}

/** Creates a functor of type QEXTConstMemberFunctor which wraps a const method with 2 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2) const) {
    return QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2>(func);
}

/** Creates a functor of type QEXTConstMemberFunctor which wraps a const method with 1 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1>
inline QEXTConstMemberFunctor<T_return, T_obj, T_arg1>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1) const) {
    return QEXTConstMemberFunctor<T_return, T_obj, T_arg1>(func);
}

/** Creates a functor of type QEXTConstMemberFunctor which wraps a const method with no args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj>
inline QEXTConstMemberFunctor<T_return, T_obj>
qextMemberFunctor(T_return (T_obj::*func)() const) {
    return QEXTConstMemberFunctor<T_return, T_obj>(func);
}



/** Creates a functor of type QEXTVolatileMemberFunctor7 which wraps a volatile method.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor7(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) volatile) {
    return QEXTVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(func);
}

/** Creates a functor of type QEXTVolatileMemberFunctor6 which wraps a volatile method.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor6(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) volatile) {
    return QEXTVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(func);
}

/** Creates a functor of type QEXTVolatileMemberFunctor5 which wraps a volatile method.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor5(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) volatile) {
    return QEXTVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(func);
}

/** Creates a functor of type QEXTVolatileMemberFunctor4 which wraps a volatile method.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor4(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4) volatile) {
    return QEXTVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(func);
}

/** Creates a functor of type QEXTVolatileMemberFunctor3 which wraps a volatile method.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor3(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3) volatile) {
    return QEXTVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>(func);
}

/** Creates a functor of type QEXTVolatileMemberFunctor2 which wraps a volatile method.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QEXTVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor2(T_return (T_obj::*func)(T_arg1, T_arg2) volatile) {
    return QEXTVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>(func);
}

/** Creates a functor of type QEXTVolatileMemberFunctor1 which wraps a volatile method.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1>
inline QEXTVolatileMemberFunctor1<T_return, T_obj, T_arg1>
qextMemberFunctor1(T_return (T_obj::*func)(T_arg1) volatile) {
    return QEXTVolatileMemberFunctor1<T_return, T_obj, T_arg1>(func);
}

/** Creates a functor of type QEXTVolatileMemberFunctor0 which wraps a volatile method.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj>
inline QEXTVolatileMemberFunctor0<T_return, T_obj>
qextMemberFunctor0(T_return (T_obj::*func)() volatile) {
    return QEXTVolatileMemberFunctor0<T_return, T_obj>(func);
}

/** Creates a functor of type QEXTVolatileMemberFunctor which wraps a volatile method with 7 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) volatile) {
    return QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(func);
}

/** Creates a functor of type QEXTVolatileMemberFunctor which wraps a volatile method with 6 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) volatile) {
    return QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(func);
}

/** Creates a functor of type QEXTVolatileMemberFunctor which wraps a volatile method with 5 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) volatile) {
    return QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(func);
}

/** Creates a functor of type QEXTVolatileMemberFunctor which wraps a volatile method with 4 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4) volatile) {
    return QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(func);
}

/** Creates a functor of type QEXTVolatileMemberFunctor which wraps a volatile method with 3 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3) volatile) {
    return QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>(func);
}

/** Creates a functor of type QEXTVolatileMemberFunctor which wraps a volatile method with 2 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2) volatile) {
    return QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>(func);
}

/** Creates a functor of type QEXTVolatileMemberFunctor which wraps a volatile method with 1 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1>
inline QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1) volatile) {
    return QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1>(func);
}

/** Creates a functor of type QEXTVolatileMemberFunctor which wraps a volatile method with no args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj>
inline QEXTVolatileMemberFunctor<T_return, T_obj>
qextMemberFunctor(T_return (T_obj::*func)() volatile) {
    return QEXTVolatileMemberFunctor<T_return, T_obj>(func);
}



/** Creates a functor of type QEXTConstVolatileMemberFunctor7 which wraps a const volatile method.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTConstVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor7(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const volatile) {
    return QEXTConstVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(func);
}

/** Creates a functor of type QEXTConstVolatileMemberFunctor6 which wraps a const volatile method.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTConstVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor6(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const volatile) {
    return QEXTConstVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(func);
}

/** Creates a functor of type QEXTConstVolatileMemberFunctor5 which wraps a const volatile method.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTConstVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor5(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const volatile) {
    return QEXTConstVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(func);
}

/** Creates a functor of type QEXTConstVolatileMemberFunctor4 which wraps a const volatile method.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTConstVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor4(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4) const volatile) {
    return QEXTConstVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(func);
}

/** Creates a functor of type QEXTConstVolatileMemberFunctor3 which wraps a const volatile method.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTConstVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor3(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3) const volatile) {
    return QEXTConstVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>(func);
}

/** Creates a functor of type QEXTConstVolatileMemberFunctor2 which wraps a const volatile method.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QEXTConstVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor2(T_return (T_obj::*func)(T_arg1, T_arg2) const volatile) {
    return QEXTConstVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>(func);
}

/** Creates a functor of type QEXTConstVolatileMemberFunctor1 which wraps a const volatile method.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1>
inline QEXTConstVolatileMemberFunctor1<T_return, T_obj, T_arg1>
qextMemberFunctor1(T_return (T_obj::*func)(T_arg1) const volatile) {
    return QEXTConstVolatileMemberFunctor1<T_return, T_obj, T_arg1>(func);
}

/** Creates a functor of type QEXTConstVolatileMemberFunctor0 which wraps a const volatile method.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj>
inline QEXTConstVolatileMemberFunctor0<T_return, T_obj>
qextMemberFunctor0(T_return (T_obj::*func)() const volatile) {
    return QEXTConstVolatileMemberFunctor0<T_return, T_obj>(func);
}

/** Creates a functor of type QEXTConstVolatileMemberFunctor which wraps a const volatile method with 7 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const volatile) {
    return QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(func);
}

/** Creates a functor of type QEXTConstVolatileMemberFunctor which wraps a const volatile method with 6 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const volatile) {
    return QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(func);
}

/** Creates a functor of type QEXTConstVolatileMemberFunctor which wraps a const volatile method with 5 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const volatile) {
    return QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(func);
}

/** Creates a functor of type QEXTConstVolatileMemberFunctor which wraps a const volatile method with 4 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4) const volatile) {
    return QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(func);
}

/** Creates a functor of type QEXTConstVolatileMemberFunctor which wraps a const volatile method with 3 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3) const volatile) {
    return QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>(func);
}

/** Creates a functor of type QEXTConstVolatileMemberFunctor which wraps a const volatile method with 2 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2) const volatile) {
    return QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>(func);
}

/** Creates a functor of type QEXTConstVolatileMemberFunctor which wraps a const volatile method with 1 args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_arg1>
inline QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1) const volatile) {
    return QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1>(func);
}

/** Creates a functor of type QEXTConstVolatileMemberFunctor which wraps a const volatile method with no args.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj>
inline QEXTConstVolatileMemberFunctor<T_return, T_obj>
qextMemberFunctor(T_return (T_obj::*func)() const volatile) {
    return QEXTConstVolatileMemberFunctor<T_return, T_obj>(func);
}



/** Creates a functor of type QEXTBoundMemberFunctor7 which encapsulates a method and an object instance.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTBoundMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor7(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) ) {
    return QEXTBoundMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(obj, func);
}

/** Creates a functor of type QEXTBoundMemberFunctor7 which encapsulates a method and an object instance.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTBoundMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor7(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) ) {
    return QEXTBoundMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(obj, func);
}

/** Creates a functor of type QEXTBoundMemberFunctor6 which encapsulates a method and an object instance.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTBoundMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor6(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) ) {
    return QEXTBoundMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(obj, func);
}

/** Creates a functor of type QEXTBoundMemberFunctor6 which encapsulates a method and an object instance.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTBoundMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor6(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) ) {
    return QEXTBoundMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(obj, func);
}

/** Creates a functor of type QEXTBoundMemberFunctor5 which encapsulates a method and an object instance.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTBoundMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor5(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) ) {
    return QEXTBoundMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(obj, func);
}

/** Creates a functor of type QEXTBoundMemberFunctor5 which encapsulates a method and an object instance.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTBoundMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor5(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) ) {
    return QEXTBoundMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(obj, func);
}

/** Creates a functor of type QEXTBoundMemberFunctor4 which encapsulates a method and an object instance.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTBoundMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor4(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4) ) {
    return QEXTBoundMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(obj, func);
}

/** Creates a functor of type QEXTBoundMemberFunctor4 which encapsulates a method and an object instance.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTBoundMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor4(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4) ) {
    return QEXTBoundMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(obj, func);
}

/** Creates a functor of type QEXTBoundMemberFunctor3 which encapsulates a method and an object instance.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTBoundMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor3(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3) ) {
    return QEXTBoundMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>(obj, func);
}

/** Creates a functor of type QEXTBoundMemberFunctor3 which encapsulates a method and an object instance.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTBoundMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor3(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3) ) {
    return QEXTBoundMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>(obj, func);
}

/** Creates a functor of type QEXTBoundMemberFunctor2 which encapsulates a method and an object instance.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2>
inline QEXTBoundMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor2(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2) ) {
    return QEXTBoundMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>(obj, func);
}

/** Creates a functor of type QEXTBoundMemberFunctor2 which encapsulates a method and an object instance.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2>
inline QEXTBoundMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor2(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2) ) {
    return QEXTBoundMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>(obj, func);
}

/** Creates a functor of type QEXTBoundMemberFunctor1 which encapsulates a method and an object instance.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1>
inline QEXTBoundMemberFunctor1<T_return, T_obj, T_arg1>
qextMemberFunctor1(T_obj *obj, T_return (T_obj2::*func)(T_arg1) ) {
    return QEXTBoundMemberFunctor1<T_return, T_obj, T_arg1>(obj, func);
}

/** Creates a functor of type QEXTBoundMemberFunctor1 which encapsulates a method and an object instance.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1>
inline QEXTBoundMemberFunctor1<T_return, T_obj, T_arg1>
qextMemberFunctor1(T_obj &obj, T_return (T_obj2::*func)(T_arg1) ) {
    return QEXTBoundMemberFunctor1<T_return, T_obj, T_arg1>(obj, func);
}

/** Creates a functor of type QEXTBoundMemberFunctor0 which encapsulates a method and an object instance.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2>
inline QEXTBoundMemberFunctor0<T_return, T_obj>
qextMemberFunctor0(T_obj *obj, T_return (T_obj2::*func)() ) {
    return QEXTBoundMemberFunctor0<T_return, T_obj>(obj, func);
}

/** Creates a functor of type QEXTBoundMemberFunctor0 which encapsulates a method and an object instance.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2>
inline QEXTBoundMemberFunctor0<T_return, T_obj>
qextMemberFunctor0(T_obj &obj, T_return (T_obj2::*func)() ) {
    return QEXTBoundMemberFunctor0<T_return, T_obj>(obj, func);
}

/** Creates a functor of type QEXTBoundMemberFunctor0 which encapsulates a method and an object instance with 7 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) ) {
    return QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(obj, func);
}

/** Creates a functor of type QEXTBoundMemberFunctor which encapsulates a method and an object instance with 7 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) ) {
    return QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(obj, func);
}

/** Creates a functor of type QEXTBoundMemberFunctor0 which encapsulates a method and an object instance with 6 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) ) {
    return QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(obj, func);
}

/** Creates a functor of type QEXTBoundMemberFunctor which encapsulates a method and an object instance with 6 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) ) {
    return QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(obj, func);
}

/** Creates a functor of type QEXTBoundMemberFunctor0 which encapsulates a method and an object instance with 5 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) ) {
    return QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(obj, func);
}

/** Creates a functor of type QEXTBoundMemberFunctor which encapsulates a method and an object instance with 5 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) ) {
    return QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(obj, func);
}

/** Creates a functor of type QEXTBoundMemberFunctor0 which encapsulates a method and an object instance with 4 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4) ) {
    return QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(obj, func);
}

/** Creates a functor of type QEXTBoundMemberFunctor which encapsulates a method and an object instance with 4 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4) ) {
    return QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(obj, func);
}

/** Creates a functor of type QEXTBoundMemberFunctor0 which encapsulates a method and an object instance with 3 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3) ) {
    return QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>(obj, func);
}

/** Creates a functor of type QEXTBoundMemberFunctor which encapsulates a method and an object instance with 3 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3) ) {
    return QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>(obj, func);
}

/** Creates a functor of type QEXTBoundMemberFunctor0 which encapsulates a method and an object instance with 2 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2>
inline QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2) ) {
    return QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2>(obj, func);
}

/** Creates a functor of type QEXTBoundMemberFunctor which encapsulates a method and an object instance with 2 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2>
inline QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2) ) {
    return QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2>(obj, func);
}

/** Creates a functor of type QEXTBoundMemberFunctor0 which encapsulates a method and an object instance with 1 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1>
inline QEXTBoundMemberFunctor<T_return, T_obj, T_arg1>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1) ) {
    return QEXTBoundMemberFunctor<T_return, T_obj, T_arg1>(obj, func);
}

/** Creates a functor of type QEXTBoundMemberFunctor which encapsulates a method and an object instance with 1 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1>
inline QEXTBoundMemberFunctor<T_return, T_obj, T_arg1>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1) ) {
    return QEXTBoundMemberFunctor<T_return, T_obj, T_arg1>(obj, func);
}

/** Creates a functor of type QEXTBoundMemberFunctor0 which encapsulates a method and an object instance with no args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2>
inline QEXTBoundMemberFunctor<T_return, T_obj>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)() ) {
    return QEXTBoundMemberFunctor<T_return, T_obj>(obj, func);
}

/** Creates a functor of type QEXTBoundMemberFunctor which encapsulates a method and an object instance with no args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2>
inline QEXTBoundMemberFunctor<T_return, T_obj>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)() ) {
    return QEXTBoundMemberFunctor<T_return, T_obj>(obj, func);
}



/** Creates a functor of type QEXTBoundConstMemberFunctor7 which encapsulates a method and an object instance.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTBoundConstMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor7(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const) {
    return QEXTBoundConstMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(obj, func);
}

/** Creates a functor of type QEXTBoundConstMemberFunctor7 which encapsulates a method and an object instance.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTBoundConstMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor7(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const) {
    return QEXTBoundConstMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(obj, func);
}

/** Creates a functor of type QEXTBoundConstMemberFunctor6 which encapsulates a method and an object instance.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTBoundConstMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor6(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const) {
    return QEXTBoundConstMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(obj, func);
}

/** Creates a functor of type QEXTBoundConstMemberFunctor6 which encapsulates a method and an object instance.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTBoundConstMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor6(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const) {
    return QEXTBoundConstMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(obj, func);
}

/** Creates a functor of type QEXTBoundConstMemberFunctor5 which encapsulates a method and an object instance.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTBoundConstMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor5(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const) {
    return QEXTBoundConstMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(obj, func);
}

/** Creates a functor of type QEXTBoundConstMemberFunctor5 which encapsulates a method and an object instance.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTBoundConstMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor5(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const) {
    return QEXTBoundConstMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(obj, func);
}

/** Creates a functor of type QEXTBoundConstMemberFunctor4 which encapsulates a method and an object instance.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTBoundConstMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor4(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4) const) {
    return QEXTBoundConstMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(obj, func);
}

/** Creates a functor of type QEXTBoundConstMemberFunctor4 which encapsulates a method and an object instance.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTBoundConstMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor4(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4) const) {
    return QEXTBoundConstMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(obj, func);
}

/** Creates a functor of type QEXTBoundConstMemberFunctor3 which encapsulates a method and an object instance.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTBoundConstMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor3(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3) const) {
    return QEXTBoundConstMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>(obj, func);
}

/** Creates a functor of type QEXTBoundConstMemberFunctor3 which encapsulates a method and an object instance.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTBoundConstMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor3(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3) const) {
    return QEXTBoundConstMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>(obj, func);
}

/** Creates a functor of type QEXTBoundConstMemberFunctor2 which encapsulates a method and an object instance.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2>
inline QEXTBoundConstMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor2(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2) const) {
    return QEXTBoundConstMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>(obj, func);
}

/** Creates a functor of type QEXTBoundConstMemberFunctor2 which encapsulates a method and an object instance.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2>
inline QEXTBoundConstMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor2(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2) const) {
    return QEXTBoundConstMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>(obj, func);
}

/** Creates a functor of type QEXTBoundConstMemberFunctor1 which encapsulates a method and an object instance.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1>
inline QEXTBoundConstMemberFunctor1<T_return, T_obj, T_arg1>
qextMemberFunctor1(T_obj *obj, T_return (T_obj2::*func)(T_arg1) const) {
    return QEXTBoundConstMemberFunctor1<T_return, T_obj, T_arg1>(obj, func);
}

/** Creates a functor of type QEXTBoundConstMemberFunctor1 which encapsulates a method and an object instance.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1>
inline QEXTBoundConstMemberFunctor1<T_return, T_obj, T_arg1>
qextMemberFunctor1(T_obj &obj, T_return (T_obj2::*func)(T_arg1) const) {
    return QEXTBoundConstMemberFunctor1<T_return, T_obj, T_arg1>(obj, func);
}

/** Creates a functor of type QEXTBoundConstMemberFunctor0 which encapsulates a method and an object instance.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2>
inline QEXTBoundConstMemberFunctor0<T_return, T_obj>
qextMemberFunctor0(T_obj *obj, T_return (T_obj2::*func)() const) {
    return QEXTBoundConstMemberFunctor0<T_return, T_obj>(obj, func);
}

/** Creates a functor of type QEXTBoundConstMemberFunctor0 which encapsulates a method and an object instance.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2>
inline QEXTBoundConstMemberFunctor0<T_return, T_obj>
qextMemberFunctor0(T_obj &obj, T_return (T_obj2::*func)() const) {
    return QEXTBoundConstMemberFunctor0<T_return, T_obj>(obj, func);
}

/** Creates a functor of type QEXTBoundConstMemberFunctor which encapsulates a method and an object instance with 7 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const) {
    return QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(obj, func);
}

/** Creates a functor of type QEXTBoundConstMemberFunctor which encapsulates a method and an object instance with 7 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const) {
    return QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(obj, func);
}

/** Creates a functor of type QEXTBoundConstMemberFunctor which encapsulates a method and an object instance with 6 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const) {
    return QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(obj, func);
}

/** Creates a functor of type QEXTBoundConstMemberFunctor which encapsulates a method and an object instance with 6 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const) {
    return QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(obj, func);
}

/** Creates a functor of type QEXTBoundConstMemberFunctor which encapsulates a method and an object instance with 5 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const) {
    return QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(obj, func);
}

/** Creates a functor of type QEXTBoundConstMemberFunctor which encapsulates a method and an object instance with 5 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const) {
    return QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(obj, func);
}

/** Creates a functor of type QEXTBoundConstMemberFunctor which encapsulates a method and an object instance with 4 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4) const) {
    return QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(obj, func);
}

/** Creates a functor of type QEXTBoundConstMemberFunctor which encapsulates a method and an object instance with 4 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4) const) {
    return QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(obj, func);
}

/** Creates a functor of type QEXTBoundConstMemberFunctor which encapsulates a method and an object instance with 3 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3) const) {
    return QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>(obj, func);
}

/** Creates a functor of type QEXTBoundConstMemberFunctor which encapsulates a method and an object instance with 3 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3) const) {
    return QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>(obj, func);
}

/** Creates a functor of type QEXTBoundConstMemberFunctor which encapsulates a method and an object instance with 2 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2>
inline QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2) const) {
    return QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2>(obj, func);
}

/** Creates a functor of type QEXTBoundConstMemberFunctor which encapsulates a method and an object instance with 2 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2>
inline QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2) const) {
    return QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2>(obj, func);
}

/** Creates a functor of type QEXTBoundConstMemberFunctor which encapsulates a method and an object instance with 1 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1>
inline QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1) const) {
    return QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1>(obj, func);
}

/** Creates a functor of type QEXTBoundConstMemberFunctor which encapsulates a method and an object instance with 1 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1>
inline QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1) const) {
    return QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1>(obj, func);
}

/** Creates a functor of type QEXTBoundConstMemberFunctor which encapsulates a method and an object instance with no args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2>
inline QEXTBoundConstMemberFunctor<T_return, T_obj>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)() const) {
    return QEXTBoundConstMemberFunctor<T_return, T_obj>(obj, func);
}

/** Creates a functor of type QEXTBoundConstMemberFunctor which encapsulates a method and an object instance with no args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2>
inline QEXTBoundConstMemberFunctor<T_return, T_obj>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)() const) {
    return QEXTBoundConstMemberFunctor<T_return, T_obj>(obj, func);
}



/** Creates a functor of type QEXTBoundVolatileMemberFunctor7 which encapsulates a method and an object instance.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTBoundVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor7(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) volatile) {
    return QEXTBoundVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(obj, func);
}

/** Creates a functor of type QEXTBoundVolatileMemberFunctor7 which encapsulates a method and an object instance.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTBoundVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor7(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) volatile) {
    return QEXTBoundVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(obj, func);
}

/** Creates a functor of type QEXTBoundVolatileMemberFunctor6 which encapsulates a method and an object instance.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTBoundVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor6(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) volatile) {
    return QEXTBoundVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(obj, func);
}

/** Creates a functor of type QEXTBoundVolatileMemberFunctor6 which encapsulates a method and an object instance.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTBoundVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor6(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) volatile) {
    return QEXTBoundVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(obj, func);
}

/** Creates a functor of type QEXTBoundVolatileMemberFunctor5 which encapsulates a method and an object instance.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTBoundVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor5(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) volatile) {
    return QEXTBoundVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(obj, func);
}

/** Creates a functor of type QEXTBoundVolatileMemberFunctor5 which encapsulates a method and an object instance.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTBoundVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor5(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) volatile) {
    return QEXTBoundVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(obj, func);
}

/** Creates a functor of type QEXTBoundVolatileMemberFunctor4 which encapsulates a method and an object instance.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTBoundVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor4(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4) volatile) {
    return QEXTBoundVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(obj, func);
}

/** Creates a functor of type QEXTBoundVolatileMemberFunctor4 which encapsulates a method and an object instance.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTBoundVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor4(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4) volatile) {
    return QEXTBoundVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(obj, func);
}

/** Creates a functor of type QEXTBoundVolatileMemberFunctor3 which encapsulates a method and an object instance.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTBoundVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor3(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3) volatile) {
    return QEXTBoundVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>(obj, func);
}

/** Creates a functor of type QEXTBoundVolatileMemberFunctor3 which encapsulates a method and an object instance.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTBoundVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor3(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3) volatile)
{ return QEXTBoundVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>(obj, func); }

/** Creates a functor of type QEXTBoundVolatileMemberFunctor2 which encapsulates a method and an object instance.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2>
inline QEXTBoundVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor2(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2) volatile) {
    return QEXTBoundVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>(obj, func);
}

/** Creates a functor of type QEXTBoundVolatileMemberFunctor2 which encapsulates a method and an object instance.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2>
inline QEXTBoundVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor2(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2) volatile)
{ return QEXTBoundVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>(obj, func); }

/** Creates a functor of type QEXTBoundVolatileMemberFunctor1 which encapsulates a method and an object instance.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1>
inline QEXTBoundVolatileMemberFunctor1<T_return, T_obj, T_arg1>
qextMemberFunctor1(T_obj *obj, T_return (T_obj2::*func)(T_arg1) volatile) {
    return QEXTBoundVolatileMemberFunctor1<T_return, T_obj, T_arg1>(obj, func);
}

/** Creates a functor of type QEXTBoundVolatileMemberFunctor1 which encapsulates a method and an object instance.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1>
inline QEXTBoundVolatileMemberFunctor1<T_return, T_obj, T_arg1>
qextMemberFunctor1(T_obj &obj, T_return (T_obj2::*func)(T_arg1) volatile) {
    return QEXTBoundVolatileMemberFunctor1<T_return, T_obj, T_arg1>(obj, func);
}

/** Creates a functor of type QEXTBoundVolatileMemberFunctor0 which encapsulates a method and an object instance.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2>
inline QEXTBoundVolatileMemberFunctor0<T_return, T_obj>
qextMemberFunctor0(T_obj *obj, T_return (T_obj2::*func)() volatile) {
    return QEXTBoundVolatileMemberFunctor0<T_return, T_obj>(obj, func);
}

/** Creates a functor of type QEXTBoundVolatileMemberFunctor0 which encapsulates a method and an object instance.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2>
inline QEXTBoundVolatileMemberFunctor0<T_return, T_obj>
qextMemberFunctor0(T_obj &obj, T_return (T_obj2::*func)() volatile) {
    return QEXTBoundVolatileMemberFunctor0<T_return, T_obj>(obj, func);
}



/** Creates a functor of type QEXTBoundVolatileMemberFunctor which encapsulates a method and an object instance with 7 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) volatile) {
    return QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(obj, func);
}

/** Creates a functor of type QEXTBoundVolatileMemberFunctor which encapsulates a method and an object instance with 7 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) volatile) {
    return QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(obj, func);
}

/** Creates a functor of type QEXTBoundVolatileMemberFunctor which encapsulates a method and an object instance with 6 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) volatile) {
    return QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(obj, func);
}

/** Creates a functor of type QEXTBoundVolatileMemberFunctor which encapsulates a method and an object instance with 6 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) volatile) {
    return QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(obj, func);
}

/** Creates a functor of type QEXTBoundVolatileMemberFunctor which encapsulates a method and an object instance with 5 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) volatile) {
    return QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(obj, func);
}

/** Creates a functor of type QEXTBoundVolatileMemberFunctor which encapsulates a method and an object instance with 5 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) volatile) {
    return QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(obj, func);
}

/** Creates a functor of type QEXTBoundVolatileMemberFunctor which encapsulates a method and an object instance with 4 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4) volatile) {
    return QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(obj, func);
}

/** Creates a functor of type QEXTBoundVolatileMemberFunctor which encapsulates a method and an object instance with 4 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4) volatile) {
    return QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(obj, func);
}

/** Creates a functor of type QEXTBoundVolatileMemberFunctor which encapsulates a method and an object instance with 3 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3) volatile) {
    return QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>(obj, func);
}

/** Creates a functor of type QEXTBoundVolatileMemberFunctor which encapsulates a method and an object instance with 3 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3) volatile) {
    return QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>(obj, func);
}

/** Creates a functor of type QEXTBoundVolatileMemberFunctor which encapsulates a method and an object instance with 2 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2>
inline QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2) volatile) {
    return QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>(obj, func);
}

/** Creates a functor of type QEXTBoundVolatileMemberFunctor which encapsulates a method and an object instance with 2 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2>
inline QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2) volatile) {
    return QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>(obj, func);
}

/** Creates a functor of type QEXTBoundVolatileMemberFunctor which encapsulates a method and an object instance with 1 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1>
inline QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1) volatile) {
    return QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1>(obj, func);
}

/** Creates a functor of type QEXTBoundVolatileMemberFunctor which encapsulates a method and an object instance with 1 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1>
inline QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1) volatile) {
    return QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1>(obj, func);
}

/** Creates a functor of type QEXTBoundVolatileMemberFunctor which encapsulates a method and an object instance with no args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2>
inline QEXTBoundVolatileMemberFunctor<T_return, T_obj>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)() volatile) {
    return QEXTBoundVolatileMemberFunctor<T_return, T_obj>(obj, func);
}

/** Creates a functor of type QEXTBoundVolatileMemberFunctor which encapsulates a method and an object instance with no args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2>
inline QEXTBoundVolatileMemberFunctor<T_return, T_obj>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)() volatile) {
    return QEXTBoundVolatileMemberFunctor<T_return, T_obj>(obj, func);
}



/** Creates a functor of type QEXTBoundConstVolatileMemberFunctor7 which encapsulates a method and an object instance.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTBoundConstVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor7(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(obj, func);
}

/** Creates a functor of type QEXTBoundConstVolatileMemberFunctor7 which encapsulates a method and an object instance.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTBoundConstVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor7(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(obj, func);
}

/** Creates a functor of type QEXTBoundConstVolatileMemberFunctor6 which encapsulates a method and an object instance.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTBoundConstVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor6(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(obj, func);
}

/** Creates a functor of type QEXTBoundConstVolatileMemberFunctor6 which encapsulates a method and an object instance.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTBoundConstVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor6(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(obj, func);
}

/** Creates a functor of type QEXTBoundConstVolatileMemberFunctor5 which encapsulates a method and an object instance.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTBoundConstVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor5(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(obj, func);
}

/** Creates a functor of type QEXTBoundConstVolatileMemberFunctor5 which encapsulates a method and an object instance.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTBoundConstVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor5(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(obj, func);
}

/** Creates a functor of type QEXTBoundConstVolatileMemberFunctor4 which encapsulates a method and an object instance.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTBoundConstVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor4(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(obj, func);
}

/** Creates a functor of type QEXTBoundConstVolatileMemberFunctor4 which encapsulates a method and an object instance.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTBoundConstVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor4(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(obj, func);
}

/** Creates a functor of type QEXTBoundConstVolatileMemberFunctor3 which encapsulates a method and an object instance.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTBoundConstVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor3(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>(obj, func);
}

/** Creates a functor of type QEXTBoundConstVolatileMemberFunctor3 which encapsulates a method and an object instance.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTBoundConstVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor3(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>(obj, func);
}

/** Creates a functor of type QEXTBoundConstVolatileMemberFunctor2 which encapsulates a method and an object instance.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2>
inline QEXTBoundConstVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor2(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>(obj, func);
}

/** Creates a functor of type QEXTBoundConstVolatileMemberFunctor2 which encapsulates a method and an object instance.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2>
inline QEXTBoundConstVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor2(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>(obj, func);
}

/** Creates a functor of type QEXTBoundConstVolatileMemberFunctor1 which encapsulates a method and an object instance.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1>
inline QEXTBoundConstVolatileMemberFunctor1<T_return, T_obj, T_arg1>
qextMemberFunctor1(T_obj *obj, T_return (T_obj2::*func)(T_arg1) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor1<T_return, T_obj, T_arg1>(obj, func);
}

/** Creates a functor of type QEXTBoundConstVolatileMemberFunctor1 which encapsulates a method and an object instance.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1>
inline QEXTBoundConstVolatileMemberFunctor1<T_return, T_obj, T_arg1>
qextMemberFunctor1(T_obj &obj, T_return (T_obj2::*func)(T_arg1) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor1<T_return, T_obj, T_arg1>(obj, func);
}

/** Creates a functor of type QEXTBoundConstVolatileMemberFunctor0 which encapsulates a method and an object instance.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2>
inline QEXTBoundConstVolatileMemberFunctor0<T_return, T_obj>
qextMemberFunctor0(T_obj *obj, T_return (T_obj2::*func)() const volatile) {
    return QEXTBoundConstVolatileMemberFunctor0<T_return, T_obj>(obj, func);
}

/** Creates a functor of type QEXTBoundConstVolatileMemberFunctor0 which encapsulates a method and an object instance.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2>
inline QEXTBoundConstVolatileMemberFunctor0<T_return, T_obj>
qextMemberFunctor0(T_obj &obj, T_return (T_obj2::*func)() const volatile) {
    return QEXTBoundConstVolatileMemberFunctor0<T_return, T_obj>(obj, func);
}



/** Creates a functor of type QEXTBoundConstVolatileMemberFunctor which encapsulates a method and an object instance with 7 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(obj, func);
}

/** Creates a functor of type QEXTBoundConstVolatileMemberFunctor which encapsulates a method and an object instance with 7 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(obj, func);
}

/** Creates a functor of type QEXTBoundConstVolatileMemberFunctor which encapsulates a method and an object instance with 6 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(obj, func);
}

/** Creates a functor of type QEXTBoundConstVolatileMemberFunctor which encapsulates a method and an object instance with 6 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(obj, func);
}

/** Creates a functor of type QEXTBoundConstVolatileMemberFunctor which encapsulates a method and an object instance with 5 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(obj, func);
}

/** Creates a functor of type QEXTBoundConstVolatileMemberFunctor which encapsulates a method and an object instance with 5 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(obj, func);
}

/** Creates a functor of type QEXTBoundConstVolatileMemberFunctor which encapsulates a method and an object instance with 4 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(obj, func);
}

/** Creates a functor of type QEXTBoundConstVolatileMemberFunctor which encapsulates a method and an object instance with 4 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(obj, func);
}

/** Creates a functor of type QEXTBoundConstVolatileMemberFunctor which encapsulates a method and an object instance with 3 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>(obj, func);
}

/** Creates a functor of type QEXTBoundConstVolatileMemberFunctor which encapsulates a method and an object instance with 3 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>(obj, func);
}

/** Creates a functor of type QEXTBoundConstVolatileMemberFunctor which encapsulates a method and an object instance with 2 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2>
inline QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>(obj, func);
}

/** Creates a functor of type QEXTBoundConstVolatileMemberFunctor which encapsulates a method and an object instance with 2 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2>
inline QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>(obj, func);
}

/** Creates a functor of type QEXTBoundConstVolatileMemberFunctor which encapsulates a method and an object instance with 1 args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1>
inline QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1>(obj, func);
}

/** Creates a functor of type QEXTBoundConstVolatileMemberFunctor which encapsulates a method and an object instance with 1 args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1>
inline QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1>(obj, func);
}

/** Creates a functor of type QEXTBoundConstVolatileMemberFunctor which encapsulates a method and an object instance with no args.
 * @param obj Pointer to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2>
inline QEXTBoundConstVolatileMemberFunctor<T_return, T_obj>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)() const volatile) {
    return QEXTBoundConstVolatileMemberFunctor<T_return, T_obj>(obj, func);
}

/** Creates a functor of type QEXTBoundConstVolatileMemberFunctor which encapsulates a method and an object instance with no args.
 * @param obj Reference to object instance the functor should operate on.
 * @param func Pointer to method that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextMemberFunctor
 */
template <typename T_return, typename T_obj, typename T_obj2>
inline QEXTBoundConstVolatileMemberFunctor<T_return, T_obj>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)() const volatile) {
    return QEXTBoundConstVolatileMemberFunctor<T_return, T_obj>(obj, func);
}


#endif // QEXTMEMBERFUNCTOR_H
