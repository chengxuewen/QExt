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

/**
 * @brief Helper macro, to determine if decltype() can deduce the result type of a functor.
 */
template < class Functor >
class QExtCanDeduceResultTypeWithDecltype
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

    // If decltype(&XFunctor::operator()) can't be evaluated, this check() overload
    // is ignored because of the SFINAE rule (Substitution Failure Is Not An Error).
    template < class XFunctor >
    static int check(XFunctor *obj, decltype(&XFunctor::operator()) p = QEXT_NULLPTR);

public:
    static const bool value = sizeof(check(static_cast< Functor * >(QEXT_NULLPTR))) == sizeof(int);
};

// For generic types, directly use the result of the signature of its 'operator()'
template < class Functor >
struct QExtDecltypeFunctionTraits : public QExtDecltypeFunctionTraits< decltype(&Functor::operator()) >
{
};

// we specialize for pointers to member function
template < class Class, class Return, class... Args >
struct QExtDecltypeFunctionTraits< Return (Class::*)(Args...) >
{
    typedef Return ResultType;
};

// we specialize for pointers to member const function
template < class Class, class Return, class... Args >
struct QExtDecltypeFunctionTraits< Return (Class::*)(Args...) const >
{
    typedef Return ResultType;
};

// we specialize for pointers to member volatile function
template < class Class, class Return, class... Args >
struct QExtDecltypeFunctionTraits< Return (Class::*)(Args...) volatile >
{
    typedef Return ResultType;
};

// we specialize for pointers to member const volatile function
template < class Class, class Return, class... Args >
struct QExtDecltypeFunctionTraits< Return (Class::*)(Args...) const volatile >
{
    typedef Return ResultType;
};

#else

template < class Functor >
class QExtCanDeduceResultTypeWithDecltype
{
public:
    static const bool value = false;
};

#endif // #if QEXT_CC_FEATURE_DECLTYPE

/**
 * @brief Trait that specifies the return type of any type.
 * Template specializations for functors derived from QExtFunctorBase, for other functors whose result type can
 * be deduced with decltype(), for function pointers and for class methods are provided.
 *
 * @tparam Functor FunctorType type.
 * @tparam I_derives_functor_base Whether @p Functor inherits from QExtFunctorBase.
 * @tparam I_can_use_decltype Whether the result type of @p Functor can be deduced with decltype().
 */
template <class Functor,
         bool I_derives_functor_base = QExtIsBaseOf< QExtFunctorBase, Functor >::value,
         bool I_can_use_decltype = QExtCanDeduceResultTypeWithDecltype< Functor >::value >
struct QExtFunctorTrait
{
    typedef void ResultType;
    typedef void ObjectType;
    typedef Functor FunctorType;

    static inline const char *typeName() { return "UnknownFunctor"; }
};

template <class Functor,
         bool I_can_use_decltype >
struct QExtFunctorTrait< Functor, true, I_can_use_decltype >
{
    typedef typename Functor::ResultType ResultType;
    typedef typename Functor::ObjectType ObjectType;
    typedef Functor FunctorType;

    static inline const char *typeName() { return "QExtFunctorBase"; }
};

#if QEXT_CC_FEATURE_LAMBDA
template < typename Functor >
struct QExtFunctorTrait< Functor, false, true >
{
    typedef typename QExtDecltypeFunctionTraits< Functor >::ResultType ResultType;
    typedef Functor FunctorType;
    typedef void ObjectType;

    static inline const char *typeName() { return "lambda"; }
};
#endif // #if QEXT_CC_FEATURE_LAMBDA

/**
 * @brief Helper macro, if you want to mix user-defined and third party functors.
 *
 * If you want to mix functors not derived from QExtFunctorBase, and these functors define @p ResultType,
 * use this macro like so:
 * @code
 * QEXT_FUNCTORS_HAVE_RESULT_TYPE
 * @endcode
 *
 * You can't use both QEXT_FUNCTORS_HAVE_RESULT_TYPE and QEXT_FUNCTORS_DEDUCE_RESULT_TYPE_WITH_DECLTYPE in the same
 * compilation unit.
 */
#define QEXT_FUNCTORS_HAVE_RESULT_TYPE \
template < class Functor > \
    struct QExtFunctorTrait< Functor, false, false > { \
        typedef typename Functor::ResultType ResultType; \
        typedef Functor FunctorType; \
};

/**
 * @brief Helper macro, if you want to mix user-defined and third party functors.
 *
 * If you want to mix functors not derived from QExtFunctorBase, and these functors don't define @p ResultType,
 * use this macro to expose the return type of the functors like so:
 * @code
 *   QEXT_FUNCTOR_TRAIT(first_functor_type, return_type_of_first_functor_type)
 *   QEXT_FUNCTOR_TRAIT(second_functor_type, return_type_of_second_functor_type)
 *   ...
 * @endcode
 */
#define QEXT_FUNCTOR_TRAIT(Functor, Return) \
template <> \
    struct QExtFunctorTrait< Functor, false, false > { \
        typedef Return ResultType; \
        typedef Functor FunctorType; \
};

/**
 * @brief Helper macro, if you want to mix user-defined and third party functors.
 *
 * If you want to mix functors not derived from QExtFunctorBase, and your compiler can deduce the result type of the
 * functor with the C++11 keyword <tt>decltype</tt>, use this macro like so:
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
 */
#if QEXT_CC_FEATURE_LAMBDA
#   define QEXT_FUNCTORS_DEDUCE_RESULT_TYPE_WITH_DECLTYPE
#else
#   define QEXT_FUNCTORS_DEDUCE_RESULT_TYPE_WITH_DECLTYPE \
    template < typename Functor > \
    struct QExtDecltypeFunctionTraits : public QExtDecltypeFunctionTraits< decltype(&Functor::operator()) > { }; \
    template < typename Class, class Return, typename... Args > \
    struct QExtDecltypeFunctionTraits< Return (Class::*)(Args...) > { typedef Return ResultType; }; \
    template < typename Class, class Return, typename... Args > \
    struct QExtDecltypeFunctionTraits< Return (Class::*)(Args...) const > { typedef Return ResultType; }; \
    template < typename Class, class Return, typename... Args > \
    struct QExtDecltypeFunctionTraits< Return (Class::*)(Args...) volatile > { typedef Return ResultType; }; \
    template < typename Class, class Return, typename... Args > \
    struct QExtDecltypeFunctionTraits< Return (Class::*)(Args...) const volatile > { typedef Return ResultType; }; \
    template < typename Functor, bool I_can_use_decltype > \
    struct QExtFunctorTrait< Functor, false, I_can_use_decltype > { \
        typedef typename QExtDecltypeFunctionTraits< Functor >::ResultType ResultType; \
        typedef Functor FunctorType; \
        typedef void ObjectType; \
        QString typeName() const { return "lambda"; } };
#endif

template < class Return, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7 >
class QExtPointerFunctor;
template < class Return, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7 >
struct QExtFunctorTrait< Return (*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7), false, false >
{
    typedef Return ResultType;
    typedef void ObjectType;
    typedef QExtPointerFunctor< Return, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7 > FunctorType;

    static inline const char *typeName() { return "QExtPointerFunctor7"; }
};

template < class Return, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6 >
struct QExtFunctorTrait< Return (*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6), false, false >
{
    typedef Return ResultType;
    typedef void ObjectType;
    typedef QExtPointerFunctor< Return, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, QExtNil > FunctorType;

    static inline const char *typeName() { return "QExtPointerFunctor6"; }
};

template < class Return, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5 >
struct QExtFunctorTrait< Return (*)(Arg1, Arg2, Arg3, Arg4, Arg5), false, false >
{
    typedef Return ResultType;
    typedef void ObjectType;
    typedef QExtPointerFunctor< Return, Arg1, Arg2, Arg3, Arg4, Arg5, QExtNil, QExtNil > FunctorType;

    static inline const char *typeName() { return "QExtPointerFunctor5"; }
};

template < class Return, class Arg1, class Arg2, class Arg3, class Arg4 >
struct QExtFunctorTrait< Return (*)(Arg1, Arg2, Arg3, Arg4), false, false >
{
    typedef Return ResultType;
    typedef void ObjectType;
    typedef QExtPointerFunctor< Return, Arg1, Arg2, Arg3, Arg4, QExtNil, QExtNil, QExtNil > FunctorType;

    static inline const char *typeName() { return "QExtPointerFunctor4"; }
};

template < class Return, class Arg1, class Arg2, class Arg3 >
struct QExtFunctorTrait< Return (*)(Arg1, Arg2, Arg3), false, false >
{
    typedef Return ResultType;
    typedef void ObjectType;
    typedef QExtPointerFunctor< Return, Arg1, Arg2, Arg3, QExtNil, QExtNil, QExtNil, QExtNil > FunctorType;

    static inline const char *typeName() { return "QExtPointerFunctor3"; }
};

template < class Return, class Arg1, class Arg2 >
struct QExtFunctorTrait< Return (*)(Arg1, Arg2), false, false >
{
    typedef Return ResultType;
    typedef void ObjectType;
    typedef QExtPointerFunctor< Return, Arg1, Arg2, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil > FunctorType;

    static inline const char *typeName() { return "QExtPointerFunctor2"; }
};

template < class Return, class Arg1 >
struct QExtFunctorTrait< Return (*)(Arg1), false, false >
{
    typedef Return ResultType;
    typedef void ObjectType;
    typedef QExtPointerFunctor< Return, Arg1, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil > FunctorType;

    static inline const char *typeName() { return "QExtPointerFunctor1"; }
};

template < class Return >
struct QExtFunctorTrait< Return (*)(), false, false >
{
    typedef Return ResultType;
    typedef void ObjectType;
    typedef QExtPointerFunctor< Return, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil > FunctorType;

    static inline const char *typeName() { return "QExtPointerFunctor0"; }
};

template <class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
class QExtMemberFunctor;
template <class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
class QExtConstMemberFunctor;
template <class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
class QExtVolatileMemberFunctor;
template <class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
class QExtConstVolatileMemberFunctor;
template <class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
struct QExtFunctorTrait< Return (Obj::*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7), false, false >
{
    typedef Return ResultType;
    typedef Obj ObjectType;
    typedef QExtMemberFunctor< Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7 > FunctorType;

    static inline const char *typeName() { return "QExtMemberFunctor7"; }
};
template <class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
struct QExtFunctorTrait< Return (Obj::*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7) const, false, false >
{
    typedef Return ResultType;
    typedef Obj ObjectType;
    typedef QExtConstMemberFunctor< Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7 > FunctorType;

    static inline const char *typeName() { return "QExtConstMemberFunctor7"; }
};
template <class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
struct QExtFunctorTrait< Return (Obj::*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7) volatile, false, false >
{
    typedef Return ResultType;
    typedef Obj ObjectType;
    typedef QExtVolatileMemberFunctor< Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7 > FunctorType;

    static inline const char *typeName() { return "QExtVolatileMemberFunctor7"; }
};
template <class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
struct QExtFunctorTrait< Return (Obj::*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7) const volatile, false, false >
{
    typedef Return ResultType;
    typedef Obj ObjectType;
    typedef QExtConstVolatileMemberFunctor< Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7 > FunctorType;

    static inline const char *typeName() { return "QExtConstVolatileMemberFunctor7"; }
};

template < class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6 >
struct QExtFunctorTrait< Return (Obj::*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6), false, false >
{
    typedef Return ResultType;
    typedef Obj ObjectType;
    typedef QExtMemberFunctor< Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, QExtNil > FunctorType;

    static inline const char *typeName() { return "QExtMemberFunctor6"; }
};
template < class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6 >
struct QExtFunctorTrait< Return (Obj::*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6) const, false, false >
{
    typedef Return ResultType;
    typedef Obj ObjectType;
    typedef QExtConstMemberFunctor< Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, QExtNil > FunctorType;

    static inline const char *typeName() { return "QExtConstMemberFunctor6"; }
};
template < class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6 >
struct QExtFunctorTrait< Return (Obj::*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6) volatile, false, false >
{
    typedef Return ResultType;
    typedef Obj ObjectType;
    typedef QExtVolatileMemberFunctor< Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, QExtNil > FunctorType;

    static inline const char *typeName() { return "QExtVolatileMemberFunctor6"; }
};
template < class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6 >
struct QExtFunctorTrait< Return (Obj::*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6) const volatile, false, false >
{
    typedef Return ResultType;
    typedef Obj ObjectType;
    typedef QExtConstVolatileMemberFunctor< Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, QExtNil > FunctorType;

    static inline const char *typeName() { return "QExtConstVolatileMemberFunctor6"; }
};

template < class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5 >
struct QExtFunctorTrait< Return (Obj::*)(Arg1, Arg2, Arg3, Arg4, Arg5), false, false >
{
    typedef Return ResultType;
    typedef Obj ObjectType;
    typedef QExtMemberFunctor< Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, QExtNil, QExtNil > FunctorType;

    static inline const char *typeName() { return "QExtMemberFunctor5"; }
};
template < class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5 >
struct QExtFunctorTrait< Return (Obj::*)(Arg1, Arg2, Arg3, Arg4, Arg5) const, false, false >
{
    typedef Return ResultType;
    typedef Obj ObjectType;
    typedef QExtConstMemberFunctor< Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, QExtNil, QExtNil > FunctorType;

    static inline const char *typeName() { return "QExtConstMemberFunctor5"; }
};
template < class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5 >
struct QExtFunctorTrait< Return (Obj::*)(Arg1, Arg2, Arg3, Arg4, Arg5) volatile, false, false >
{
    typedef Return ResultType;
    typedef Obj ObjectType;
    typedef QExtVolatileMemberFunctor< Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, QExtNil, QExtNil > FunctorType;

    static inline const char *typeName() { return "QExtVolatileMemberFunctor5"; }
};
template < class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5 >
struct QExtFunctorTrait< Return (Obj::*)(Arg1, Arg2, Arg3, Arg4, Arg5) const volatile, false, false >
{
    typedef Return ResultType;
    typedef Obj ObjectType;
    typedef QExtConstVolatileMemberFunctor< Return, Obj, Arg1, Arg2, Arg3, Arg4, Arg5, QExtNil, QExtNil > FunctorType;

    static inline const char *typeName() { return "QExtConstVolatileMemberFunctor5"; }
};

template < class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4 >
struct QExtFunctorTrait< Return (Obj::*)(Arg1, Arg2, Arg3, Arg4), false, false >
{
    typedef Return ResultType;
    typedef Obj ObjectType;
    typedef QExtMemberFunctor< Return, Obj, Arg1, Arg2, Arg3, Arg4, QExtNil, QExtNil, QExtNil> FunctorType;

    static inline const char *typeName() { return "QExtMemberFunctor4"; }
};
template < class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4 >
struct QExtFunctorTrait< Return (Obj::*)(Arg1, Arg2, Arg3, Arg4) const, false, false >
{
    typedef Return ResultType;
    typedef Obj ObjectType;
    typedef QExtConstMemberFunctor< Return, Obj, Arg1, Arg2, Arg3, Arg4, QExtNil, QExtNil, QExtNil > FunctorType;

    static inline const char *typeName() { return "QExtConstMemberFunctor4"; }
};
template < class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4 >
struct QExtFunctorTrait< Return (Obj::*)(Arg1, Arg2, Arg3, Arg4) volatile, false, false >
{
    typedef Return ResultType;
    typedef Obj ObjectType;
    typedef QExtVolatileMemberFunctor< Return, Obj, Arg1, Arg2, Arg3, Arg4, QExtNil, QExtNil, QExtNil > FunctorType;

    static inline const char *typeName() { return "QExtVolatileMemberFunctor4"; }
};
template < class Return, class Obj, class Arg1, class Arg2, class Arg3, class Arg4 >
struct QExtFunctorTrait< Return (Obj::*)(Arg1, Arg2, Arg3, Arg4) const volatile, false, false >
{
    typedef Return ResultType;
    typedef Obj ObjectType;
    typedef QExtConstVolatileMemberFunctor< Return, Obj, Arg1, Arg2, Arg3, Arg4, QExtNil, QExtNil, QExtNil > FunctorType;

    static inline const char *typeName() { return "QExtConstVolatileMemberFunctor4"; }
};

template < class Return, class Obj, class Arg1, class Arg2, class Arg3 >
struct QExtFunctorTrait< Return (Obj::*)(Arg1, Arg2, Arg3), false, false >
{
    typedef Return ResultType;
    typedef Obj ObjectType;
    typedef QExtMemberFunctor< Return, Obj, Arg1, Arg2, Arg3, QExtNil, QExtNil, QExtNil, QExtNil > FunctorType;

    static inline const char *typeName() { return "QExtMemberFunctor3"; }
};
template < class Return, class Obj, class Arg1, class Arg2, class Arg3 >
struct QExtFunctorTrait< Return (Obj::*)(Arg1, Arg2, Arg3) const, false, false >
{
    typedef Return ResultType;
    typedef Obj ObjectType;
    typedef QExtConstMemberFunctor< Return, Obj, Arg1, Arg2, Arg3, QExtNil, QExtNil, QExtNil, QExtNil > FunctorType;

    static inline const char *typeName() { return "QExtConstMemberFunctor3"; }
};
template < class Return, class Obj, class Arg1, class Arg2, class Arg3 >
struct QExtFunctorTrait< Return (Obj::*)(Arg1, Arg2, Arg3) volatile, false, false >
{
    typedef Return ResultType;
    typedef Obj ObjectType;
    typedef QExtVolatileMemberFunctor< Return, Obj, Arg1, Arg2, Arg3, QExtNil, QExtNil, QExtNil, QExtNil > FunctorType;

    static inline const char *typeName() { return "QExtVolatileMemberFunctor3"; }
};
template < class Return, class Obj, class Arg1, class Arg2, class Arg3 >
struct QExtFunctorTrait< Return (Obj::*)(Arg1, Arg2, Arg3) const volatile, false, false >
{
    typedef Return ResultType;
    typedef Obj ObjectType;
    typedef QExtConstVolatileMemberFunctor< Return, Obj, Arg1, Arg2, Arg3, QExtNil, QExtNil, QExtNil, QExtNil > FunctorType;

    static inline const char *typeName() { return "QExtConstVolatileMemberFunctor3"; }
};

template < class Return, class Obj, class Arg1, class Arg2 >
struct QExtFunctorTrait< Return (Obj::*)(Arg1, Arg2), false, false >
{
    typedef Return ResultType;
    typedef Obj ObjectType;
    typedef QExtMemberFunctor< Return, Obj, Arg1, Arg2, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil > FunctorType;

    static inline const char *typeName() { return "QExtMemberFunctor2"; }
};
template < class Return, class Obj, class Arg1, class Arg2 >
struct QExtFunctorTrait< Return (Obj::*)(Arg1, Arg2) const, false, false >
{
    typedef Return ResultType;
    typedef Obj ObjectType;
    typedef QExtConstMemberFunctor< Return, Obj, Arg1, Arg2, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil > FunctorType;

    static inline const char *typeName() { return "QExtConstMemberFunctor2"; }
};
template < class Return, class Obj, class Arg1, class Arg2 >
struct QExtFunctorTrait< Return (Obj::*)(Arg1, Arg2) volatile, false, false >
{
    typedef Return ResultType;
    typedef Obj ObjectType;
    typedef QExtVolatileMemberFunctor< Return, Obj, Arg1, Arg2, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil > FunctorType;

    static inline const char *typeName() { return "QExtVolatileMemberFunctor2"; }
};
template < class Return, class Obj, class Arg1, class Arg2 >
struct QExtFunctorTrait< Return (Obj::*)(Arg1, Arg2) const volatile, false, false >
{
    typedef Return ResultType;
    typedef Obj ObjectType;
    typedef QExtConstVolatileMemberFunctor< Return, Obj, Arg1, Arg2, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil > FunctorType;

    static inline const char *typeName() { return "QExtConstVolatileMemberFunctor2"; }
};

template < class Return, class Obj, class Arg1 >
struct QExtFunctorTrait< Return (Obj::*)(Arg1), false, false >
{
    typedef Return ResultType;
    typedef Obj ObjectType;
    typedef QExtMemberFunctor< Return, Obj, Arg1, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil > FunctorType;

    static inline const char *typeName() { return "QExtMemberFunctor1"; }
};
template < class Return, class Obj, class Arg1 >
struct QExtFunctorTrait< Return (Obj::*)(Arg1) const, false, false >
{
    typedef Return ResultType;
    typedef Obj ObjectType;
    typedef QExtConstMemberFunctor< Return, Obj, Arg1, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil > FunctorType;

    static inline const char *typeName() { return "QExtConstMemberFunctor1"; }
};
template < class Return, class Obj, class Arg1 >
struct QExtFunctorTrait< Return (Obj::*)(Arg1) volatile, false, false >
{
    typedef Return ResultType;
    typedef Obj ObjectType;
    typedef QExtVolatileMemberFunctor< Return, Obj, Arg1, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil > FunctorType;

    static inline const char *typeName() { return "QExtVolatileMemberFunctor1"; }
};
template < class Return, class Obj, class Arg1 >
struct QExtFunctorTrait< Return (Obj::*)(Arg1) const volatile, false, false >
{
    typedef Return ResultType;
    typedef Obj ObjectType;
    typedef QExtConstVolatileMemberFunctor< Return, Obj, Arg1, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil > FunctorType;

    static inline const char *typeName() { return "QExtConstVolatileMemberFunctor1"; }
};

template < class Return, class Obj >
struct QExtFunctorTrait< Return (Obj::*)(), false, false >
{
    typedef Return ResultType;
    typedef Obj ObjectType;
    typedef QExtMemberFunctor< Return, Obj, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil > FunctorType;

    static inline const char *typeName() { return "QExtMemberFunctor0"; }
};
template < class Return, class Obj >
struct QExtFunctorTrait< Return (Obj::*)() const, false, false >
{
    typedef Return ResultType;
    typedef Obj ObjectType;
    typedef QExtConstMemberFunctor< Return, Obj, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil > FunctorType;

    static inline const char *typeName() { return "QExtConstMemberFunctor0"; }
};
template < class Return, class Obj >
struct QExtFunctorTrait< Return (Obj::*)() volatile, false, false >
{
    typedef Return ResultType;
    typedef Obj ObjectType;
    typedef QExtVolatileMemberFunctor< Return, Obj, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil > FunctorType;

    static inline const char *typeName() { return "QExtVolatileMemberFunctor0"; }
};
template < class Return, class Obj >
struct QExtFunctorTrait< Return (Obj::*)() const volatile, false, false >
{
    typedef Return ResultType;
    typedef Obj ObjectType;
    typedef QExtConstVolatileMemberFunctor<Return, Obj, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil> FunctorType;

    static inline const char *typeName() { return "QExtConstVolatileMemberFunctor0"; }
};

#endif // _QEXTFUNCTORTRAIT_H
