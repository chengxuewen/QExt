#ifndef QEXTFUNCTORPOINTER_H
#define QEXTFUNCTORPOINTER_H

#include <qextglobal.h>
#include <qextfunctortrait.h>

/** @defgroup qextPointerFunctor qextPointerFunctor()
 * qextPointerFunctor() is used to convert a pointer to a function to a functor.
 * If the function pointer is to an overloaded type, you must specify
 * the types using template arguments starting with the first argument.
 * It is not necessary to supply the return type.
 *
 * @par Example:
 * @code
 * void foo(int) {}
 * QEXTSlot<void, int> slot = qextPointerFunctor(&foo);
 * @endcode
 *
 * Use qextPointerFunctor#() if there is an ambiguity as to the number of arguments.
 *
 * @par Example:
 * @code
 * void foo(int) {}  // choose this one
 * void foo(float) {}
 * void foo(int, int) {}
 * QEXTSlot<void, long> slot = qextPointerFunctor<int>(&foo);
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
 * @ingroup qextfunctors
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
 * @ingroup qextPointerFunctor
 */
template <typename T_return,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
class QEXTPointerFunctor7 : public QEXTFunctorBase
{
public:
    typedef T_return (*FunctionType)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7);
    typedef T_return ResultType;

    // Constructs an invalid functor.
    QEXTPointerFunctor7() : m_funcPtr(QEXT_NULLPTR) {}
    /** Constructs a QEXTPointerFunctor7 object that wraps an existing function.
     * @param func Pointer to function that will be invoked from operator()().
     */
    QEXTPointerFunctor7(FunctionType func): m_funcPtr(func) {}
    QEXTPointerFunctor7(const QEXTPointerFunctor7 &src): m_funcPtr(src.m_funcPtr) {}

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
    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6,
                        typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return m_funcPtr(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

protected:
    FunctionType m_funcPtr;
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
 * @ingroup qextPointerFunctor
 */
template <typename T_return,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
class QEXTPointerFunctor6 : public QEXTFunctorBase
{
public:
    typedef T_return (*FunctionType)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6);
    typedef T_return ResultType;

    // Constructs an invalid functor.
    QEXTPointerFunctor6() : m_funcPtr(QEXT_NULLPTR) {}
    /** Constructs a QEXTPointerFunctor6 object that wraps an existing function.
     * @param func Pointer to function that will be invoked from operator()().
     */
    QEXTPointerFunctor6(FunctionType func): m_funcPtr(func) {}
    QEXTPointerFunctor6(const QEXTPointerFunctor6 &src): m_funcPtr(src.m_funcPtr) {}

    /** Execute the wrapped function.
     * @param arg1 Argument to be passed on to the function.
     * @param arg2 Argument to be passed on to the function.
     * @param arg3 Argument to be passed on to the function.
     * @param arg4 Argument to be passed on to the function.
     * @param arg5 Argument to be passed on to the function.
     * @param arg6 Argument to be passed on to the function.
     * @return The return value of the function invocation.
     */
    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return m_funcPtr(arg1, arg2, arg3, arg4, arg5, arg6);
    }

protected:
    FunctionType m_funcPtr;
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
 * @ingroup qextPointerFunctor
 */
template <typename T_return,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class QEXTPointerFunctor5 : public QEXTFunctorBase
{
public:
    typedef T_return (*FunctionType)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5);
    typedef T_return ResultType;

    // Constructs an invalid functor.
    QEXTPointerFunctor5() : m_funcPtr(QEXT_NULLPTR) {}
    /** Constructs a QEXTPointerFunctor5 object that wraps an existing function.
     * @param func Pointer to function that will be invoked from operator()().
     */
    QEXTPointerFunctor5(FunctionType func): m_funcPtr(func) {}
    QEXTPointerFunctor5(const QEXTPointerFunctor5 &src): m_funcPtr(src.m_funcPtr) {}

    /** Execute the wrapped function.
     * @param arg1 Argument to be passed on to the function.
     * @param arg2 Argument to be passed on to the function.
     * @param arg3 Argument to be passed on to the function.
     * @param arg4 Argument to be passed on to the function.
     * @param arg5 Argument to be passed on to the function.
     * @return The return value of the function invocation.
     */
    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return m_funcPtr(arg1, arg2, arg3, arg4, arg5);
    }

protected:
    FunctionType m_funcPtr;
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
 * @ingroup qextPointerFunctor
 */
template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class QEXTPointerFunctor4 : public QEXTFunctorBase
{
public:
    typedef T_return (*FunctionType)(T_arg1, T_arg2, T_arg3, T_arg4);
    typedef T_return ResultType;

    // Constructs an invalid functor.
    QEXTPointerFunctor4() : m_funcPtr(QEXT_NULLPTR) {}
    /** Constructs a QEXTPointerFunctor4 object that wraps an existing function.
     * @param func Pointer to function that will be invoked from operator()().
     */
    QEXTPointerFunctor4(FunctionType func): m_funcPtr(func) {}
    QEXTPointerFunctor4(const QEXTPointerFunctor4 &src): m_funcPtr(src.m_funcPtr) {}

    /** Execute the wrapped function.
     * @param arg1 Argument to be passed on to the function.
     * @param arg2 Argument to be passed on to the function.
     * @param arg3 Argument to be passed on to the function.
     * @param arg4 Argument to be passed on to the function.
     * @return The return value of the function invocation.
     */
    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return m_funcPtr(arg1, arg2, arg3, arg4);
    }

protected:
    FunctionType m_funcPtr;
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
 * @ingroup qextPointerFunctor
 */
template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3>
class QEXTPointerFunctor3 : public QEXTFunctorBase
{
public:
    typedef T_return (*FunctionType)(T_arg1, T_arg2, T_arg3);
    typedef T_return ResultType;

    // Constructs an invalid functor.
    QEXTPointerFunctor3() : m_funcPtr(QEXT_NULLPTR) {}
    /** Constructs a QEXTPointerFunctor3 object that wraps an existing function.
     * @param func Pointer to function that will be invoked from operator()().
     */
    QEXTPointerFunctor3(FunctionType func): m_funcPtr(func) {}
    QEXTPointerFunctor3(const QEXTPointerFunctor3 &src): m_funcPtr(src.m_funcPtr) {}

    /** Execute the wrapped function.
     * @param arg1 Argument to be passed on to the function.
     * @param arg2 Argument to be passed on to the function.
     * @param arg3 Argument to be passed on to the function.
     * @return The return value of the function invocation.
     */
    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return m_funcPtr(arg1, arg2, arg3);
    }

protected:
    FunctionType m_funcPtr;
};

/** QEXTPointerFunctor2 wraps existing non-member functions with 2 argument(s).
 * Use the convenience function qextPointerFunctor() to create an instance of QEXTPointerFunctor2.
 *
 * The following template arguments are used:
 * - @e T_arg1 Argument type used in the definition of operator()().
 * - @e T_arg2 Argument type used in the definition of operator()().
 * - @e T_return The return type of operator()().
 *
 * @ingroup qextPointerFunctor
 */
template <typename T_return, typename T_arg1, typename T_arg2>
class QEXTPointerFunctor2 : public QEXTFunctorBase
{
public:
    typedef T_return (*FunctionType)(T_arg1, T_arg2);
    typedef T_return ResultType;

    // Constructs an invalid functor.
    QEXTPointerFunctor2() : m_funcPtr(QEXT_NULLPTR) {}
    /** Constructs a QEXTPointerFunctor2 object that wraps an existing function.
     * @param func Pointer to function that will be invoked from operator()().
     */
    QEXTPointerFunctor2(FunctionType func): m_funcPtr(func) {}
    QEXTPointerFunctor2(const QEXTPointerFunctor2 &src): m_funcPtr(src.m_funcPtr) {}

    /** Execute the wrapped function.
     * @param arg1 Argument to be passed on to the function.
     * @param arg2 Argument to be passed on to the function.
     * @return The return value of the function invocation.
     */
    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return m_funcPtr(arg1, arg2);
    }

protected:
    FunctionType m_funcPtr;
};

/** QEXTPointerFunctor1 wraps existing non-member functions with 1 argument(s).
 * Use the convenience function qextPointerFunctor() to create an instance of QEXTPointerFunctor1.
 *
 * The following template arguments are used:
 * - @e T_arg1 Argument type used in the definition of operator()().
 * - @e T_return The return type of operator()().
 *
 * @ingroup qextPointerFunctor
 */
template <typename T_return, typename T_arg1>
class QEXTPointerFunctor1 : public QEXTFunctorBase
{
public:
    typedef T_return (*FunctionType)(T_arg1);
    typedef T_return ResultType;

    // Constructs an invalid functor.
    QEXTPointerFunctor1() : m_funcPtr(QEXT_NULLPTR) {}
    /** Constructs a QEXTPointerFunctor1 object that wraps an existing function.
     * @param func Pointer to function that will be invoked from operator()().
     */
    QEXTPointerFunctor1(FunctionType func): m_funcPtr(func) {}
    QEXTPointerFunctor1(const QEXTPointerFunctor1 &src): m_funcPtr(src.m_funcPtr) {}

    /** Execute the wrapped function.
     * @param arg1 Argument to be passed on to the function.
     * @return The return value of the function invocation.
     */
    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return m_funcPtr(arg1);
    }

protected:
    FunctionType m_funcPtr;
};

/** QEXTPointerFunctor0 wraps existing non-member functions with 0 argument(s).
 * Use the convenience function qextPointerFunctor() to create an instance of QEXTPointerFunctor0.
 *
 * The following template arguments are used:
 * - @e T_return The return type of operator()().
 *
 * @ingroup qextPointerFunctor
 */
template <typename T_return>
class QEXTPointerFunctor0 : public QEXTFunctorBase
{
public:
    typedef T_return (*FunctionType)();
    typedef T_return ResultType;

    QEXTPointerFunctor0() : m_funcPtr(QEXT_NULLPTR) {}
    /** Constructs a QEXTPointerFunctor0 object that wraps an existing function.
     * @param func Pointer to function that will be invoked from operator()().
     */
    QEXTPointerFunctor0(FunctionType func) : m_funcPtr(func) {}
    QEXTPointerFunctor0(const QEXTPointerFunctor0 &src): m_funcPtr(src.m_funcPtr) {}

    /** Execute the wrapped function.
     * @return The return value of the function invocation.
     */
    T_return operator()() const {
        return m_funcPtr();
    }

protected:
    FunctionType m_funcPtr;
};

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
 * @ingroup qextPointerFunctor
 */
template <typename T_return,
          typename T_arg1 = QEXTNil, typename T_arg2 = QEXTNil, typename T_arg3 = QEXTNil,
          typename T_arg4 = QEXTNil, typename T_arg5 = QEXTNil, typename T_arg6 = QEXTNil, typename T_arg7 = QEXTNil>
class QEXTPointerFunctor : public QEXTPointerFunctor7<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
{
public:
    typedef QEXTPointerFunctor7<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> BaseType;
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTPointerFunctor() {}
    QEXTPointerFunctor(FunctionType func) : BaseType(func) {}
    QEXTPointerFunctor(const QEXTPointerFunctor &src) : BaseType(src.m_funcPtr) {}

    /** Invoke the contained functor.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @param arg6 Argument to be passed on to the functor.
     * @param arg7 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
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

/** Convenience wrapper for the numbered QEXTPointerFunctor# templates.
 * See the base class for useful methods.
 * This is the template specialization of the unnumbered QEXTPointerFunctor
 * template for 6 argument(s), specialized for different numbers of arguments
 * This is possible because the template has default (QEXTNil) template types.
 */
template <typename T_return,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
class QEXTPointerFunctor<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QEXTNil>
        : public QEXTPointerFunctor6<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
{
public:
    typedef QEXTPointerFunctor6<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> BaseType;
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTPointerFunctor() {}
    QEXTPointerFunctor(FunctionType func) : BaseType(func) {}
    QEXTPointerFunctor(const QEXTPointerFunctor &src) : BaseType(src.m_funcPtr) {}

    /** Invoke the contained functor unless slot is in blocking state.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @param arg6 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return BaseType::operator ()(arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

/** Convenience wrapper for the numbered QEXTPointerFunctor# templates.
 * See the base class for useful methods.
 * This is the template specialization of the unnumbered QEXTPointerFunctor
 * template for 5 argument(s), specialized for different numbers of arguments
 * This is possible because the template has default (QEXTNil) template types.
 */
template <typename T_return,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class QEXTPointerFunctor<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QEXTNil, QEXTNil>
        : public QEXTPointerFunctor5<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
{
public:
    typedef QEXTPointerFunctor5<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> BaseType;
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTPointerFunctor() {}
    QEXTPointerFunctor(FunctionType func) : BaseType(func) {}
    QEXTPointerFunctor(const QEXTPointerFunctor &src) : BaseType(src.m_funcPtr) {}

    /** Invoke the contained functor unless slot is in blocking state.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return BaseType::operator ()(arg1, arg2, arg3, arg4, arg5);
    }
};

/** Convenience wrapper for the numbered QEXTPointerFunctor# templates.
 * See the base class for useful methods.
 * This is the template specialization of the unnumbered QEXTPointerFunctor
 * template for 4 argument(s), specialized for different numbers of arguments
 * This is possible because the template has default (QEXTNil) template types.
 */
template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class QEXTPointerFunctor<T_return, T_arg1, T_arg2, T_arg3, T_arg4, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTPointerFunctor4<T_return, T_arg1, T_arg2, T_arg3, T_arg4>
{
public:
    typedef QEXTPointerFunctor4<T_return, T_arg1, T_arg2, T_arg3, T_arg4> BaseType;
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTPointerFunctor() {}
    QEXTPointerFunctor(FunctionType func) : BaseType(func) {}
    QEXTPointerFunctor(const QEXTPointerFunctor &src) : BaseType(src.m_funcPtr) {}

    /** Invoke the contained functor unless slot is in blocking state.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return BaseType::operator ()(arg1, arg2, arg3, arg4);
    }
};

/** Convenience wrapper for the numbered QEXTPointerFunctor# templates.
 * See the base class for useful methods.
 * This is the template specialization of the unnumbered QEXTPointerFunctor
 * template for 3 argument(s), specialized for different numbers of arguments
 * This is possible because the template has default (QEXTNil) template types.
 */
template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3>
class QEXTPointerFunctor<T_return, T_arg1, T_arg2, T_arg3, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTPointerFunctor3<T_return, T_arg1, T_arg2, T_arg3>
{
public:
    typedef QEXTPointerFunctor3<T_return, T_arg1, T_arg2, T_arg3> BaseType;
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTPointerFunctor() {}
    QEXTPointerFunctor(FunctionType func) : BaseType(func) {}
    QEXTPointerFunctor(const QEXTPointerFunctor &src) : BaseType(src.m_funcPtr) {}

    /** Invoke the contained functor unless slot is in blocking state.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return BaseType::operator ()(arg1, arg2, arg3);
    }
};

/** Convenience wrapper for the numbered QEXTPointerFunctor# templates.
 * See the base class for useful methods.
 * This is the template specialization of the unnumbered QEXTPointerFunctor
 * template for 2 argument(s), specialized for different numbers of arguments
 * This is possible because the template has default (QEXTNil) template types.
 */
template <typename T_return, typename T_arg1, typename T_arg2>
class QEXTPointerFunctor<T_return, T_arg1, T_arg2, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTPointerFunctor2<T_return, T_arg1, T_arg2>
{
public:
    typedef QEXTPointerFunctor2<T_return, T_arg1, T_arg2> BaseType;
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTPointerFunctor() {}
    QEXTPointerFunctor(FunctionType func) : BaseType(func) {}
    QEXTPointerFunctor(const QEXTPointerFunctor &src) : BaseType(src.m_funcPtr) {}

    /** Invoke the contained functor unless slot is in blocking state.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return BaseType::operator ()(arg1, arg2);
    }
};

/** Convenience wrapper for the numbered QEXTPointerFunctor# templates.
 * See the base class for useful methods.
 * This is the template specialization of the unnumbered QEXTPointerFunctor
 * template for 1 argument(s), specialized for different numbers of arguments
 * This is possible because the template has default (QEXTNil) template types.
 */
template <typename T_return, typename T_arg1>
class QEXTPointerFunctor<T_return, T_arg1, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTPointerFunctor1<T_return, T_arg1>
{
public:
    typedef QEXTPointerFunctor1<T_return, T_arg1> BaseType;
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTPointerFunctor() {}
    QEXTPointerFunctor(FunctionType func) : BaseType(func) {}
    QEXTPointerFunctor(const QEXTPointerFunctor &src) : BaseType(src.m_funcPtr) {}

    /** Invoke the contained functor unless slot is in blocking state.
     * @param arg1 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return BaseType::operator ()(arg1);
    }
};

/** Convenience wrapper for the numbered QEXTPointerFunctor# templates.
 * See the base class for useful methods.
 * This is the template specialization of the unnumbered QEXTPointerFunctor
 * template for 0 argument(s), specialized for different numbers of arguments
 * This is possible because the template has default (QEXTNil) template types.
 */
template <typename T_return>
class QEXTPointerFunctor<T_return, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTPointerFunctor0<T_return>
{
public:
    typedef QEXTPointerFunctor0<T_return> BaseType;
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTPointerFunctor() {}
    QEXTPointerFunctor(FunctionType func) : BaseType(func) {}
    QEXTPointerFunctor(const QEXTPointerFunctor &src) : BaseType(src.m_funcPtr) {}

    /** Invoke the contained functor unless slot is in blocking state.
     * @return The return value of the functor invocation.
     */
    T_return operator()() const {
        return BaseType::operator ()();
    }
};




// numbered qextPointerFunctor
/** Creates a functor of type QEXTPointerFunctor7 which wraps an existing non-member function.
 * @param func Pointer to function that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextPointerFunctor
 */
template <typename T_return,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTPointerFunctor7<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextPointerFunctor7(T_return (*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7)) {
    return QEXTPointerFunctor7<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(func);
}

/** Creates a functor of type QEXTPointerFunctor6 which wraps an existing non-member function.
 * @param func Pointer to function that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextPointerFunctor
 */
template <typename T_return,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTPointerFunctor6<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextPointerFunctor6(T_return (*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6)) {
    return QEXTPointerFunctor6<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(func);
}

/** Creates a functor of type QEXTPointerFunctor5 which wraps an existing non-member function.
 * @param func Pointer to function that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextPointerFunctor
 */
template <typename T_return,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTPointerFunctor5<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextPointerFunctor5(T_return (*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5)) {
    return QEXTPointerFunctor5<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(func);
}

/** Creates a functor of type QEXTPointerFunctor4 which wraps an existing non-member function.
 * @param func Pointer to function that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextPointerFunctor
 */
template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTPointerFunctor4<T_return, T_arg1, T_arg2, T_arg3, T_arg4>
qextPointerFunctor4(T_return (*func)(T_arg1, T_arg2, T_arg3, T_arg4)) {
    return QEXTPointerFunctor4<T_return, T_arg1, T_arg2, T_arg3, T_arg4>(func);
}

/** Creates a functor of type QEXTPointerFunctor3 which wraps an existing non-member function.
 * @param func Pointer to function that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextPointerFunctor
 */
template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTPointerFunctor3<T_return, T_arg1, T_arg2, T_arg3>
qextPointerFunctor3(T_return (*func)(T_arg1, T_arg2, T_arg3)) {
    return QEXTPointerFunctor3<T_return, T_arg1, T_arg2, T_arg3>(func);
}

/** Creates a functor of type QEXTPointerFunctor2 which wraps an existing non-member function.
 * @param func Pointer to function that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextPointerFunctor
 */
template <typename T_return, typename T_arg1, typename T_arg2>
inline QEXTPointerFunctor2<T_return, T_arg1, T_arg2>
qextPointerFunctor2(T_return (*func)(T_arg1, T_arg2)) {
    return QEXTPointerFunctor2<T_return, T_arg1, T_arg2>(func);
}

/** Creates a functor of type QEXTPointerFunctor1 which wraps an existing non-member function.
 * @param func Pointer to function that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextPointerFunctor
 */
template <typename T_return, typename T_arg1>
inline QEXTPointerFunctor1<T_return, T_arg1>
qextPointerFunctor1(T_return (*func)(T_arg1)) {
    return QEXTPointerFunctor1<T_return, T_arg1>(func);
}

/** Creates a functor of type QEXTPointerFunctor0 which wraps an existing non-member function.
 * @param func Pointer to function that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextPointerFunctor
 */
template <typename T_return>
inline QEXTPointerFunctor0<T_return>
qextPointerFunctor0(T_return (*func)()) {
    return QEXTPointerFunctor0<T_return>(func);
}


// unnumbered qextPointerFunctor
/** Creates a functor of type QEXTPointerFunctor7 which wraps an existing non-member function.
 * @param func Pointer to function that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextPointerFunctor
 */
template <typename T_return,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTPointerFunctor<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextPointerFunctor(T_return (*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7)) {
    return QEXTPointerFunctor<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(func);
}

/** Creates a functor of type QEXTPointerFunctor6 which wraps an existing non-member function.
 * @param func Pointer to function that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextPointerFunctor
 */
template <typename T_return,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTPointerFunctor<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextPointerFunctor(T_return (*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6)) {
    return QEXTPointerFunctor<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(func);
}

/** Creates a functor of type QEXTPointerFunctor5 which wraps an existing non-member function.
 * @param func Pointer to function that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextPointerFunctor
 */
template <typename T_return,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTPointerFunctor<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextPointerFunctor(T_return (*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5)) {
    return QEXTPointerFunctor<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(func);
}

/** Creates a functor of type QEXTPointerFunctor4 which wraps an existing non-member function.
 * @param func Pointer to function that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextPointerFunctor
 */
template <typename T_return,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTPointerFunctor<T_return, T_arg1, T_arg2, T_arg3, T_arg4>
qextPointerFunctor(T_return (*func)(T_arg1, T_arg2, T_arg3, T_arg4)) {
    return QEXTPointerFunctor<T_return, T_arg1, T_arg2, T_arg3, T_arg4>(func);
}

/** Creates a functor of type QEXTPointerFunctor3 which wraps an existing non-member function.
 * @param func Pointer to function that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextPointerFunctor
 */
template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTPointerFunctor<T_return, T_arg1, T_arg2, T_arg3>
qextPointerFunctor(T_return (*func)(T_arg1, T_arg2, T_arg3)) {
    return QEXTPointerFunctor<T_return, T_arg1, T_arg2, T_arg3>(func);
}

/** Creates a functor of type QEXTPointerFunctor2 which wraps an existing non-member function.
 * @param func Pointer to function that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextPointerFunctor
 */
template <typename T_return, typename T_arg1, typename T_arg2>
inline QEXTPointerFunctor<T_return, T_arg1, T_arg2>
qextPointerFunctor(T_return (*func)(T_arg1, T_arg2)) {
    return QEXTPointerFunctor<T_return, T_arg1, T_arg2>(func);
}

/** Creates a functor of type QEXTPointerFunctor1 which wraps an existing non-member function.
 * @param func Pointer to function that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextPointerFunctor
 */
template <typename T_return, typename T_arg1>
inline QEXTPointerFunctor<T_return, T_arg1>
qextPointerFunctor(T_return (*func)(T_arg1)) {
    return QEXTPointerFunctor<T_return, T_arg1>(func);
}

/** Creates a functor of type QEXTPointerFunctor0 which wraps an existing non-member function.
 * @param func Pointer to function that should be wrapped.
 * @return Functor that executes @e func on invokation.
 *
 * @ingroup qextPointerFunctor
 */
template <typename T_return>
inline QEXTPointerFunctor<T_return>
qextPointerFunctor(T_return (*func)()) {
    return QEXTPointerFunctor<T_return>(func);
}


#endif // QEXTFUNCTORPOINTER_H
