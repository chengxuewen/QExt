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

#ifndef _QEXTFUNCTORTRAIT_H
#define _QEXTFUNCTORTRAIT_H

#include <qextGlobal.h>
#include <qextTypeTrait.h>

#include <QString>

/** @defgroup sigqextunctors Functors
 * Functors are copyable types that define operator()().
 *
 * Types that define operator()() overloads with different return types are referred to
 * as multi-type functors. Multi-type functors are only partially supported.
 *
 * Closures are functors that store all information needed to invoke a callback from operator()().
 *
 * Adaptors are functors that alter the signature of a functor's operator()().
 */

/**
 * @brief A hint to the compiler.
 * All functors which define @p result_type should publically inherit from this hint.
 */
struct QEXT_CORE_API QExtFunctorBase
{
    typedef void ResultType;
    typedef void ObjectType;
    virtual ~QExtFunctorBase() {}
};

#if QEXT_CC_FEATURE_DECLTYPE

/** Helper macro, to determine if decltype() can deduce the result type of a functor.
 *
 * \ingroup sigqextunctors
 */
template < typename T_functor >
class QEXTCanDeduceResultTypeWithDecltype
{
private:
    struct BiggerThanInt
    {
        int memory1;
        int memory2;
        int memory3;
        int memory4;
    };

    static BiggerThanInt check(...);

    // If decltype(&X_functor::operator()) can't be evaluated, this check() overload
    // is ignored because of the SFINAE rule (Substitution Failure Is Not An Error).
    template < typename X_functor >
    static int check(X_functor *obj, decltype(&X_functor::operator()) p = QEXT_NULLPTR);

public:
    static const bool value = sizeof(check(static_cast< T_functor * >(QEXT_NULLPTR))) == sizeof(int);
};

// For generic types, directly use the result of the signature of its 'operator()'
template < typename T_functor >
struct QExtDecltypeFunctionTraits : public QExtDecltypeFunctionTraits< decltype(&T_functor::operator()) >
{
};

// we specialize for pointers to member function
template < typename T_class, typename T_return, typename... T_args >
struct QExtDecltypeFunctionTraits< T_return (T_class::*)(T_args...) >
{
    typedef T_return ResultType;
};

// we specialize for pointers to member const function
template < typename T_class, typename T_return, typename... T_args >
struct QExtDecltypeFunctionTraits< T_return (T_class::*)(T_args...) const >
{
    typedef T_return ResultType;
};

// we specialize for pointers to member volatile function
template < typename T_class, typename T_return, typename... T_args >
struct QExtDecltypeFunctionTraits< T_return (T_class::*)(T_args...) volatile >
{
    typedef T_return ResultType;
};

// we specialize for pointers to member const volatile function
template < typename T_class, typename T_return, typename... T_args >
struct QExtDecltypeFunctionTraits< T_return (T_class::*)(T_args...) const volatile >
{
    typedef T_return ResultType;
};

#else

template < typename T_functor >
class QEXTCanDeduceResultTypeWithDecltype
{
public:
    static const bool value = false;
};

#endif // #if QEXT_CC_FEATURE_DECLTYPE

/** Trait that specifies the return type of any type.
 * Template specializations for functors derived from QExtFunctorBase,
 * for other functors whose result type can be deduced with decltype(),
 * for function pointers and for class methods are provided.
 *
 * @tparam T_functor FunctorType type.
 * @tparam I_derives_functor_base Whether @p T_functor inherits from QExtFunctorBase.
 * @tparam I_can_use_decltype Whether the result type of @p T_functor can be deduced
 *                            with decltype().
 *
 * \ingroup sigqextunctors
 */
template <
        typename T_functor,
        bool I_derives_functor_base = QExtIsBaseOf< QExtFunctorBase, T_functor >::value,
        bool I_can_use_decltype = QEXTCanDeduceResultTypeWithDecltype< T_functor >::value >
struct QExtFunctorTrait
{
    typedef void ResultType;
    typedef void ObjectType;
    typedef T_functor FunctorType;

    QString typeName() const
    {
        return "UnknownFunctor";
    }
};

template < typename T_functor, bool I_can_use_decltype >
struct QExtFunctorTrait< T_functor, true, I_can_use_decltype >
{
    typedef typename T_functor::ResultType ResultType;
    typedef typename T_functor::ObjectType ObjectType;
    typedef T_functor FunctorType;

    QString typeName() const
    {
        return "QExtFunctorBase";
    }
};

#if QEXT_CC_FEATURE_LAMBDA
template < typename T_functor >
struct QExtFunctorTrait< T_functor, false, true >
{
    typedef typename QExtDecltypeFunctionTraits< T_functor >::ResultType ResultType;
    typedef T_functor FunctorType;
    typedef void ObjectType;

    QString typeName() const
    {
        return "lambda";
    }
};
#endif

/** Helper macro, if you want to mix user-defined and third party functors.
 *
 * If you want to mix functors not derived from QExtFunctorBase, and
 * these functors define @p ResultType, use this macro like so:
 * @code
 * QEXT_FUNCTORS_HAVE_RESULT_TYPE
 * @endcode
 *
 * You can't use both QEXT_FUNCTORS_HAVE_RESULT_TYPE and
 * QEXT_FUNCTORS_DEDUCE_RESULT_TYPE_WITH_DECLTYPE in the same compilation unit.
 *
 * \ingroup qextfunctors
 */
#define QEXT_FUNCTORS_HAVE_RESULT_TYPE                                                                                                                           \
    template < typename T_functor >                                                                                                                            \
    struct QExtFunctorTrait< T_functor, false, false >                                                                                                           \
{                                                                                                                                                          \
    typedef typename T_functor::ResultType ResultType;                                                                                                             \
    typedef T_functor FunctorType;                                                                                                                             \
    };

/** Helper macro, if you want to mix user-defined and third party functors.
 *
 * If you want to mix functors not derived from QExtFunctorBase, and
 * these functors don't define @p ResultType, use this macro inside namespace sigc
 * to expose the return type of the functors like so:
 * @code
 *   QEXT_FUNCTOR_TRAIT(first_functor_type, return_type_of_first_functor_type)
 *   QEXT_FUNCTOR_TRAIT(second_functor_type, return_type_of_second_functor_type)
 *   ...
 * @endcode
 *
 * \ingroup qextfunctors
 */
#define QEXT_FUNCTOR_TRAIT(T_functor, T_return)                                                                                                                  \
    template <>                                                                                                                                                \
    struct QExtFunctorTrait< T_functor, false, false >                                                                                                           \
{                                                                                                                                                          \
    typedef T_return ResultType;                                                                                                                               \
    typedef T_functor FunctorType;                                                                                                                             \
    };

/** Helper macro, if you want to mix user-defined and third party functors.
 *
 * If you want to mix functors not derived from QExtFunctorBase,
 * and your compiler can deduce the result type of the functor with the C++11
 * keyword <tt>decltype</tt>, use this macro like so:
 * @code
 *   QEXT_FUNCTORS_DEDUCE_RESULT_TYPE_WITH_DECLTYPE
 * @endcode
 *
 * Functors with overloaded operator()() are not supported.
 *
 * @newin{2,2,11}
 *
 * You can't use both QEXT_FUNCTORS_HAVE_RESULT_TYPE and
 * QEXT_FUNCTORS_DEDUCE_RESULT_TYPE_WITH_DECLTYPE in the same compilation unit.
 *
 * \ingroup qextfunctors
 */
#if QEXT_CC_FEATURE_LAMBDA
#define QEXT_FUNCTORS_DEDUCE_RESULT_TYPE_WITH_DECLTYPE
#else
#define QEXT_FUNCTORS_DEDUCE_RESULT_TYPE_WITH_DECLTYPE                                                                                                           \
    template < typename T_functor >                                                                                                                            \
    struct QExtDecltypeFunctionTraits : public QExtDecltypeFunctionTraits< decltype(&T_functor::operator()) >                                                      \
{                                                                                                                                                          \
    };                                                                                                                                                         \
    template < typename T_class, typename T_return, typename... T_args >                                                                                       \
    struct QExtDecltypeFunctionTraits< T_return (T_class::*)(T_args...) >                                                                                        \
{                                                                                                                                                          \
    typedef T_return ResultType;                                                                                                                               \
    };                                                                                                                                                         \
    template < typename T_class, typename T_return, typename... T_args >                                                                                       \
    struct QExtDecltypeFunctionTraits< T_return (T_class::*)(T_args...) const >                                                                                  \
{                                                                                                                                                          \
    typedef T_return ResultType;                                                                                                                               \
    };                                                                                                                                                         \
    template < typename T_class, typename T_return, typename... T_args >                                                                                       \
    struct QExtDecltypeFunctionTraits< T_return (T_class::*)(T_args...) volatile >                                                                               \
{                                                                                                                                                          \
    typedef T_return ResultType;                                                                                                                               \
    };                                                                                                                                                         \
    template < typename T_class, typename T_return, typename... T_args >                                                                                       \
    struct QExtDecltypeFunctionTraits< T_return (T_class::*)(T_args...) const volatile >                                                                         \
{                                                                                                                                                          \
    typedef T_return ResultType;                                                                                                                               \
    };                                                                                                                                                         \
    template < typename T_functor, bool I_can_use_decltype >                                                                                                   \
    struct QExtFunctorTrait< T_functor, false, I_can_use_decltype >                                                                                              \
{                                                                                                                                                          \
    typedef typename QExtDecltypeFunctionTraits< T_functor >::ResultType ResultType;                                                                                 \
    typedef T_functor FunctorType;                                                                                                                             \
    typedef void ObjectType;                                                                                                                               \
    QString typeName() const                                                                                                                           \
{                                                                                                                                                      \
    return "lambda";                                                                                                                                   \
    }                                                                                                                                                      \
    };
#endif

template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7 >
class QExtPointerFunctor;
template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7 >
struct QExtFunctorTrait< T_return (*)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7), false, false >
{
    typedef T_return ResultType;
    typedef void ObjectType;
    typedef QExtPointerFunctor< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 > FunctorType;

    QString typeName() const
    {
        return "QExtPointerFunctor7";
    }
};

template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
struct QExtFunctorTrait< T_return (*)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6), false, false >
{
    typedef T_return ResultType;
    typedef void ObjectType;
    typedef QExtPointerFunctor< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QExtNil > FunctorType;

    QString typeName() const
    {
        return "QExtPointerFunctor6";
    }
};

template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
struct QExtFunctorTrait< T_return (*)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5), false, false >
{
    typedef T_return ResultType;
    typedef void ObjectType;
    typedef QExtPointerFunctor< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QExtNil, QExtNil > FunctorType;

    QString typeName() const
    {
        return "QExtPointerFunctor5";
    }
};

template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
struct QExtFunctorTrait< T_return (*)(T_arg1, T_arg2, T_arg3, T_arg4), false, false >
{
    typedef T_return ResultType;
    typedef void ObjectType;
    typedef QExtPointerFunctor< T_return, T_arg1, T_arg2, T_arg3, T_arg4, QExtNil, QExtNil, QExtNil > FunctorType;

    QString typeName() const
    {
        return "QExtPointerFunctor4";
    }
};

template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3 >
struct QExtFunctorTrait< T_return (*)(T_arg1, T_arg2, T_arg3), false, false >
{
    typedef T_return ResultType;
    typedef void ObjectType;
    typedef QExtPointerFunctor< T_return, T_arg1, T_arg2, T_arg3, QExtNil, QExtNil, QExtNil, QExtNil > FunctorType;

    QString typeName() const
    {
        return "QExtPointerFunctor3";
    }
};

template < typename T_return, typename T_arg1, typename T_arg2 >
struct QExtFunctorTrait< T_return (*)(T_arg1, T_arg2), false, false >
{
    typedef T_return ResultType;
    typedef void ObjectType;
    typedef QExtPointerFunctor< T_return, T_arg1, T_arg2, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil > FunctorType;

    QString typeName() const
    {
        return "QExtPointerFunctor2";
    }
};

template < typename T_return, typename T_arg1 >
struct QExtFunctorTrait< T_return (*)(T_arg1), false, false >
{
    typedef T_return ResultType;
    typedef void ObjectType;
    typedef QExtPointerFunctor< T_return, T_arg1, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil > FunctorType;

    QString typeName() const
    {
        return "QExtPointerFunctor1";
    }
};

//template <typename T_return> class QExtPointerFunctor;
template < typename T_return >
struct QExtFunctorTrait< T_return (*)(), false, false >
{
    typedef T_return ResultType;
    typedef void ObjectType;
    typedef QExtPointerFunctor< T_return, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil > FunctorType;

    QString typeName() const
    {
        return "QExtPointerFunctor0";
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
class QExtMemberFunctor;
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
class QExtConstMemberFunctor;
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
class QExtVolatileMemberFunctor;
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
class QExtConstVolatileMemberFunctor;
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
struct QExtFunctorTrait< T_return (T_obj::*)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7), false, false >
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QExtMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 > FunctorType;

    QString typeName() const
    {
        return "QExtMemberFunctor7";
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
struct QExtFunctorTrait< T_return (T_obj::*)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const, false, false >
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QExtConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 > FunctorType;

    QString typeName() const
    {
        return "QExtConstMemberFunctor7";
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
struct QExtFunctorTrait< T_return (T_obj::*)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) volatile, false, false >
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QExtVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 > FunctorType;

    QString typeName() const
    {
        return "QExtVolatileMemberFunctor7";
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
struct QExtFunctorTrait< T_return (T_obj::*)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const volatile, false, false >
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QExtConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 > FunctorType;

    QString typeName() const
    {
        return "QExtConstVolatileMemberFunctor7";
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
struct QExtFunctorTrait< T_return (T_obj::*)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6), false, false >
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QExtMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QExtNil > FunctorType;

    QString typeName() const
    {
        return "QExtMemberFunctor6";
    }
};
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
struct QExtFunctorTrait< T_return (T_obj::*)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const, false, false >
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QExtConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QExtNil > FunctorType;

    QString typeName() const
    {
        return "QExtConstMemberFunctor6";
    }
};
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
struct QExtFunctorTrait< T_return (T_obj::*)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) volatile, false, false >
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QExtVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QExtNil > FunctorType;

    QString typeName() const
    {
        return "QExtVolatileMemberFunctor6";
    }
};
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
struct QExtFunctorTrait< T_return (T_obj::*)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const volatile, false, false >
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QExtConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QExtNil > FunctorType;

    QString typeName() const
    {
        return "QExtConstVolatileMemberFunctor6";
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
struct QExtFunctorTrait< T_return (T_obj::*)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5), false, false >
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QExtMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QExtNil, QExtNil > FunctorType;

    QString typeName() const
    {
        return "QExtMemberFunctor5";
    }
};
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
struct QExtFunctorTrait< T_return (T_obj::*)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const, false, false >
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QExtConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QExtNil, QExtNil > FunctorType;

    QString typeName() const
    {
        return "QExtConstMemberFunctor5";
    }
};
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
struct QExtFunctorTrait< T_return (T_obj::*)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) volatile, false, false >
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QExtVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QExtNil, QExtNil > FunctorType;

    QString typeName() const
    {
        return "QExtVolatileMemberFunctor5";
    }
};
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
struct QExtFunctorTrait< T_return (T_obj::*)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const volatile, false, false >
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QExtConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QExtNil, QExtNil > FunctorType;

    QString typeName() const
    {
        return "QExtConstVolatileMemberFunctor5";
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
struct QExtFunctorTrait< T_return (T_obj::*)(T_arg1, T_arg2, T_arg3, T_arg4), false, false >
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QExtMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, QExtNil, QExtNil, QExtNil> FunctorType;

    QString typeName() const
    {
        return "QExtMemberFunctor4";
    }
};
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
struct QExtFunctorTrait< T_return (T_obj::*)(T_arg1, T_arg2, T_arg3, T_arg4) const, false, false >
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QExtConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, QExtNil, QExtNil, QExtNil > FunctorType;

    QString typeName() const
    {
        return "QExtConstMemberFunctor4";
    }
};
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
struct QExtFunctorTrait< T_return (T_obj::*)(T_arg1, T_arg2, T_arg3, T_arg4) volatile, false, false >
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QExtVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, QExtNil, QExtNil, QExtNil > FunctorType;

    QString typeName() const
    {
        return "QExtVolatileMemberFunctor4";
    }
};
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
struct QExtFunctorTrait< T_return (T_obj::*)(T_arg1, T_arg2, T_arg3, T_arg4) const volatile, false, false >
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QExtConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, QExtNil, QExtNil, QExtNil > FunctorType;

    QString typeName() const
    {
        return "QExtConstVolatileMemberFunctor4";
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3 >
struct QExtFunctorTrait< T_return (T_obj::*)(T_arg1, T_arg2, T_arg3), false, false >
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QExtMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, QExtNil, QExtNil, QExtNil, QExtNil > FunctorType;

    QString typeName() const
    {
        return "QExtMemberFunctor3";
    }
};
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3 >
struct QExtFunctorTrait< T_return (T_obj::*)(T_arg1, T_arg2, T_arg3) const, false, false >
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QExtConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, QExtNil, QExtNil, QExtNil, QExtNil > FunctorType;

    QString typeName() const
    {
        return "QExtConstMemberFunctor3";
    }
};
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3 >
struct QExtFunctorTrait< T_return (T_obj::*)(T_arg1, T_arg2, T_arg3) volatile, false, false >
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QExtVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, QExtNil, QExtNil, QExtNil, QExtNil > FunctorType;

    QString typeName() const
    {
        return "QExtVolatileMemberFunctor3";
    }
};
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3 >
struct QExtFunctorTrait< T_return (T_obj::*)(T_arg1, T_arg2, T_arg3) const volatile, false, false >
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QExtConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, QExtNil, QExtNil, QExtNil, QExtNil > FunctorType;

    QString typeName() const
    {
        return "QExtConstVolatileMemberFunctor3";
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2 >
struct QExtFunctorTrait< T_return (T_obj::*)(T_arg1, T_arg2), false, false >
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QExtMemberFunctor< T_return, T_obj, T_arg1, T_arg2, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil > FunctorType;

    QString typeName() const
    {
        return "QExtMemberFunctor2";
    }
};
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2 >
struct QExtFunctorTrait< T_return (T_obj::*)(T_arg1, T_arg2) const, false, false >
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QExtConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil > FunctorType;

    QString typeName() const
    {
        return "QExtConstMemberFunctor2";
    }
};
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2 >
struct QExtFunctorTrait< T_return (T_obj::*)(T_arg1, T_arg2) volatile, false, false >
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QExtVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil > FunctorType;

    QString typeName() const
    {
        return "QExtVolatileMemberFunctor2";
    }
};
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2 >
struct QExtFunctorTrait< T_return (T_obj::*)(T_arg1, T_arg2) const volatile, false, false >
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QExtConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil > FunctorType;

    QString typeName() const
    {
        return "QExtConstVolatileMemberFunctor2";
    }
};

template < typename T_return, typename T_obj, typename T_arg1 >
struct QExtFunctorTrait< T_return (T_obj::*)(T_arg1), false, false >
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QExtMemberFunctor< T_return, T_obj, T_arg1, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil > FunctorType;

    QString typeName() const
    {
        return "QExtMemberFunctor1";
    }
};
template < typename T_return, typename T_obj, typename T_arg1 >
struct QExtFunctorTrait< T_return (T_obj::*)(T_arg1) const, false, false >
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QExtConstMemberFunctor< T_return, T_obj, T_arg1, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil > FunctorType;

    QString typeName() const
    {
        return "QExtConstMemberFunctor1";
    }
};
template < typename T_return, typename T_obj, typename T_arg1 >
struct QExtFunctorTrait< T_return (T_obj::*)(T_arg1) volatile, false, false >
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QExtVolatileMemberFunctor< T_return, T_obj, T_arg1, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil > FunctorType;

    QString typeName() const
    {
        return "QExtVolatileMemberFunctor1";
    }
};
template < typename T_return, typename T_obj, typename T_arg1 >
struct QExtFunctorTrait< T_return (T_obj::*)(T_arg1) const volatile, false, false >
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QExtConstVolatileMemberFunctor< T_return, T_obj, T_arg1, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil > FunctorType;

    QString typeName() const
    {
        return "QExtConstVolatileMemberFunctor1";
    }
};

template < typename T_return, typename T_obj >
struct QExtFunctorTrait< T_return (T_obj::*)(), false, false >
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QExtMemberFunctor< T_return, T_obj, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil > FunctorType;

    QString typeName() const
    {
        return "QExtMemberFunctor0";
    }
};
template < typename T_return, typename T_obj >
struct QExtFunctorTrait< T_return (T_obj::*)() const, false, false >
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QExtConstMemberFunctor< T_return, T_obj, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil > FunctorType;

    QString typeName() const
    {
        return "QExtConstMemberFunctor0";
    }
};
template < typename T_return, typename T_obj >
struct QExtFunctorTrait< T_return (T_obj::*)() volatile, false, false >
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QExtVolatileMemberFunctor< T_return, T_obj, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil > FunctorType;

    QString typeName() const
    {
        return "QExtVolatileMemberFunctor0";
    }
};
template < typename T_return, typename T_obj >
struct QExtFunctorTrait< T_return (T_obj::*)() const volatile, false, false >
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QExtConstVolatileMemberFunctor< T_return, T_obj, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil > FunctorType;

    QString typeName() const
    {
        return "QExtConstVolatileMemberFunctor0";
    }
};

#endif // _QEXTFUNCTORTRAIT_H
