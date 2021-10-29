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

#ifndef QEXTFUNCTORTRAIT_H
#define QEXTFUNCTORTRAIT_H

#include <qextGlobal.h>
#include <qextTypeTrait.h>

#include <string>



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

/** A hint to the compiler.
 * All functors which define @p result_type should publically inherit from this hint.
 *
 * @ingroup qextFunctors
 */
struct QEXT_CORE_API QEXTFunctorBase
{
    typedef void Return;
    typedef void Object;
    virtual ~QEXTFunctorBase() {}
};

#if QEXT_CC_FEATURE_DECLTYPE

/** Helper macro, to determine if decltype() can deduce the result type of a functor.
 *
 * @ingroup sigqextunctors
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
    static int check(X_functor *obj, decltype(&X_functor::operator()) p = QEXT_DECL_NULLPTR);

public:
    static const bool value = sizeof(check(static_cast< T_functor * >(QEXT_DECL_NULLPTR))) == sizeof(int);
};

// For generic types, directly use the result of the signature of its 'operator()'
template < typename T_functor >
struct QEXTDecltypeFunctionTraits : public QEXTDecltypeFunctionTraits< decltype(&T_functor::operator()) >
{
};

// we specialize for pointers to member function
template < typename T_class, typename T_return, typename... T_args >
struct QEXTDecltypeFunctionTraits< T_return (T_class::*)(T_args...) >
{
    typedef T_return Return;
};

// we specialize for pointers to member const function
template < typename T_class, typename T_return, typename... T_args >
struct QEXTDecltypeFunctionTraits< T_return (T_class::*)(T_args...) const >
{
    typedef T_return Return;
};

// we specialize for pointers to member volatile function
template < typename T_class, typename T_return, typename... T_args >
struct QEXTDecltypeFunctionTraits< T_return (T_class::*)(T_args...) volatile >
{
    typedef T_return Return;
};

// we specialize for pointers to member const volatile function
template < typename T_class, typename T_return, typename... T_args >
struct QEXTDecltypeFunctionTraits< T_return (T_class::*)(T_args...) const volatile >
{
    typedef T_return Return;
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
 * Template specializations for functors derived from QEXTFunctorBase,
 * for other functors whose result type can be deduced with decltype(),
 * for function pointers and for class methods are provided.
 *
 * @tparam T_functor Functor type.
 * @tparam I_derives_functor_base Whether @p T_functor inherits from QEXTFunctorBase.
 * @tparam I_can_use_decltype Whether the result type of @p T_functor can be deduced
 *                            with decltype().
 *
 * @ingroup sigqextunctors
 */
template <
    typename T_functor,
    bool I_derives_functor_base = QEXTIsBaseOf< QEXTFunctorBase, T_functor >::value,
    bool I_can_use_decltype = QEXTCanDeduceResultTypeWithDecltype< T_functor >::value >
struct QEXTFunctorTrait
{
    typedef void Return;
    typedef void Object;
    typedef T_functor Functor;

    std::string typeName() const
    {
        return "UnknownFunctor";
    }
};

template < typename T_functor, bool I_can_use_decltype >
struct QEXTFunctorTrait< T_functor, true, I_can_use_decltype >
{
    typedef typename T_functor::Return Return;
    typedef typename T_functor::Object Object;
    typedef T_functor Functor;

    std::string typeName() const
    {
        return "QEXTFunctorBase";
    }
};

#if QEXT_CC_FEATURE_LAMBDA
template < typename T_functor >
struct QEXTFunctorTrait< T_functor, false, true >
{
    typedef typename QEXTDecltypeFunctionTraits< T_functor >::Return Return;
    typedef T_functor Functor;
    typedef void Object;

    std::string typeName() const
    {
        return "lambda";
    }
};
#endif

/** Helper macro, if you want to mix user-defined and third party functors.
 *
 * If you want to mix functors not derived from QEXTFunctorBase, and
 * these functors define @p Return, use this macro like so:
 * @code
 * QEXT_FUNCTORS_HAVE_RESULT_TYPE
 * @endcode
 *
 * You can't use both QEXT_FUNCTORS_HAVE_RESULT_TYPE and
 * QEXT_FUNCTORS_DEDUCE_RESULT_TYPE_WITH_DECLTYPE in the same compilation unit.
 *
 * @ingroup qextfunctors
 */
#define QEXT_FUNCTORS_HAVE_RESULT_TYPE                                                                                                                           \
    template < typename T_functor >                                                                                                                            \
    struct QEXTFunctorTrait< T_functor, false, false >                                                                                                           \
    {                                                                                                                                                          \
        typedef typename T_functor::Return Return;                                                                                                             \
        typedef T_functor Functor;                                                                                                                             \
    };

/** Helper macro, if you want to mix user-defined and third party functors.
 *
 * If you want to mix functors not derived from QEXTFunctorBase, and
 * these functors don't define @p Return, use this macro inside namespace sigc
 * to expose the return type of the functors like so:
 * @code
 *   QEXT_FUNCTOR_TRAIT(first_functor_type, return_type_of_first_functor_type)
 *   QEXT_FUNCTOR_TRAIT(second_functor_type, return_type_of_second_functor_type)
 *   ...
 * @endcode
 *
 * @ingroup qextfunctors
 */
#define QEXT_FUNCTOR_TRAIT(T_functor, T_return)                                                                                                                  \
    template <>                                                                                                                                                \
    struct QEXTFunctorTrait< T_functor, false, false >                                                                                                           \
    {                                                                                                                                                          \
        typedef T_return Return;                                                                                                                               \
        typedef T_functor Functor;                                                                                                                             \
    };

/** Helper macro, if you want to mix user-defined and third party functors.
 *
 * If you want to mix functors not derived from QEXTFunctorBase,
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
 * @ingroup qextfunctors
 */
#if QEXT_CC_FEATURE_LAMBDA
#define QEXT_FUNCTORS_DEDUCE_RESULT_TYPE_WITH_DECLTYPE
#else
#define QEXT_FUNCTORS_DEDUCE_RESULT_TYPE_WITH_DECLTYPE                                                                                                           \
    template < typename T_functor >                                                                                                                            \
    struct QEXTDecltypeFunctionTraits : public QEXTDecltypeFunctionTraits< decltype(&T_functor::operator()) >                                                      \
    {                                                                                                                                                          \
    };                                                                                                                                                         \
    template < typename T_class, typename T_return, typename... T_args >                                                                                       \
    struct QEXTDecltypeFunctionTraits< T_return (T_class::*)(T_args...) >                                                                                        \
    {                                                                                                                                                          \
        typedef T_return Return;                                                                                                                               \
    };                                                                                                                                                         \
    template < typename T_class, typename T_return, typename... T_args >                                                                                       \
    struct QEXTDecltypeFunctionTraits< T_return (T_class::*)(T_args...) const >                                                                                  \
    {                                                                                                                                                          \
        typedef T_return Return;                                                                                                                               \
    };                                                                                                                                                         \
    template < typename T_class, typename T_return, typename... T_args >                                                                                       \
    struct QEXTDecltypeFunctionTraits< T_return (T_class::*)(T_args...) volatile >                                                                               \
    {                                                                                                                                                          \
        typedef T_return Return;                                                                                                                               \
    };                                                                                                                                                         \
    template < typename T_class, typename T_return, typename... T_args >                                                                                       \
    struct QEXTDecltypeFunctionTraits< T_return (T_class::*)(T_args...) const volatile >                                                                         \
    {                                                                                                                                                          \
        typedef T_return Return;                                                                                                                               \
    };                                                                                                                                                         \
    template < typename T_functor, bool I_can_use_decltype >                                                                                                   \
    struct QEXTFunctorTrait< T_functor, false, I_can_use_decltype >                                                                                              \
    {                                                                                                                                                          \
        typedef typename QEXTDecltypeFunctionTraits< T_functor >::Return Return;                                                                                 \
        typedef T_functor Functor;                                                                                                                             \
        typedef void Object;                                                                                                                               \
        std::string typeName() const                                                                                                                           \
        {                                                                                                                                                      \
            return "lambda";                                                                                                                                   \
        }                                                                                                                                                      \
    };
#endif

template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7 >
class QEXTPointerFunctor;
template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7 >
struct QEXTFunctorTrait< T_return (*)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7), false, false >
{
    typedef T_return Return;
    typedef void Object;
    typedef QEXTPointerFunctor< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 > Functor;

    std::string typeName() const
    {
        return "QEXTPointerFunctor7";
    }
};

template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
struct QEXTFunctorTrait< T_return (*)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6), false, false >
{
    typedef T_return Return;
    typedef void Object;
    typedef QEXTPointerFunctor< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QEXTNil > Functor;

    std::string typeName() const
    {
        return "QEXTPointerFunctor6";
    }
};

template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
struct QEXTFunctorTrait< T_return (*)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5), false, false >
{
    typedef T_return Return;
    typedef void Object;
    typedef QEXTPointerFunctor< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QEXTNil, QEXTNil > Functor;

    std::string typeName() const
    {
        return "QEXTPointerFunctor5";
    }
};

template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
struct QEXTFunctorTrait< T_return (*)(T_arg1, T_arg2, T_arg3, T_arg4), false, false >
{
    typedef T_return Return;
    typedef void Object;
    typedef QEXTPointerFunctor< T_return, T_arg1, T_arg2, T_arg3, T_arg4, QEXTNil, QEXTNil, QEXTNil > Functor;

    std::string typeName() const
    {
        return "QEXTPointerFunctor4";
    }
};

template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3 >
struct QEXTFunctorTrait< T_return (*)(T_arg1, T_arg2, T_arg3), false, false >
{
    typedef T_return Return;
    typedef void Object;
    typedef QEXTPointerFunctor< T_return, T_arg1, T_arg2, T_arg3, QEXTNil, QEXTNil, QEXTNil, QEXTNil > Functor;

    std::string typeName() const
    {
        return "QEXTPointerFunctor3";
    }
};

template < typename T_return, typename T_arg1, typename T_arg2 >
struct QEXTFunctorTrait< T_return (*)(T_arg1, T_arg2), false, false >
{
    typedef T_return Return;
    typedef void Object;
    typedef QEXTPointerFunctor< T_return, T_arg1, T_arg2, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil > Functor;

    std::string typeName() const
    {
        return "QEXTPointerFunctor2";
    }
};

template < typename T_return, typename T_arg1 >
struct QEXTFunctorTrait< T_return (*)(T_arg1), false, false >
{
    typedef T_return Return;
    typedef void Object;
    typedef QEXTPointerFunctor< T_return, T_arg1, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil > Functor;

    std::string typeName() const
    {
        return "QEXTPointerFunctor1";
    }
};

//template <typename T_return> class QEXTPointerFunctor;
template < typename T_return >
struct QEXTFunctorTrait< T_return (*)(), false, false >
{
    typedef T_return Return;
    typedef void Object;
    typedef QEXTPointerFunctor< T_return, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil > Functor;

    std::string typeName() const
    {
        return "QEXTPointerFunctor0";
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
class QEXTMemberFunctor;
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
class QEXTConstMemberFunctor;
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
class QEXTVolatileMemberFunctor;
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
class QEXTConstVolatileMemberFunctor;
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
struct QEXTFunctorTrait< T_return (T_obj::*)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7), false, false >
{
    typedef T_return Return;
    typedef T_obj Object;
    typedef QEXTMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 > Functor;

    std::string typeName() const
    {
        return "QEXTMemberFunctor7";
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
struct QEXTFunctorTrait< T_return (T_obj::*)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const, false, false >
{
    typedef T_return Return;
    typedef T_obj Object;
    typedef QEXTConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 > Functor;

    std::string typeName() const
    {
        return "QEXTConstMemberFunctor7";
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
struct QEXTFunctorTrait< T_return (T_obj::*)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) volatile, false, false >
{
    typedef T_return Return;
    typedef T_obj Object;
    typedef QEXTVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 > Functor;

    std::string typeName() const
    {
        return "QEXTVolatileMemberFunctor7";
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
struct QEXTFunctorTrait< T_return (T_obj::*)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const volatile, false, false >
{
    typedef T_return Return;
    typedef T_obj Object;
    typedef QEXTConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 > Functor;

    std::string typeName() const
    {
        return "QEXTConstVolatileMemberFunctor7";
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
struct QEXTFunctorTrait< T_return (T_obj::*)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6), false, false >
{
    typedef T_return Return;
    typedef T_obj Object;
    typedef QEXTMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QEXTNil > Functor;

    std::string typeName() const
    {
        return "QEXTMemberFunctor6";
    }
};
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
struct QEXTFunctorTrait< T_return (T_obj::*)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const, false, false >
{
    typedef T_return Return;
    typedef T_obj Object;
    typedef QEXTConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QEXTNil > Functor;

    std::string typeName() const
    {
        return "QEXTConstMemberFunctor6";
    }
};
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
struct QEXTFunctorTrait< T_return (T_obj::*)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) volatile, false, false >
{
    typedef T_return Return;
    typedef T_obj Object;
    typedef QEXTVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QEXTNil > Functor;

    std::string typeName() const
    {
        return "QEXTVolatileMemberFunctor6";
    }
};
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
struct QEXTFunctorTrait< T_return (T_obj::*)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const volatile, false, false >
{
    typedef T_return Return;
    typedef T_obj Object;
    typedef QEXTConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QEXTNil > Functor;

    std::string typeName() const
    {
        return "QEXTConstVolatileMemberFunctor6";
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
struct QEXTFunctorTrait< T_return (T_obj::*)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5), false, false >
{
    typedef T_return Return;
    typedef T_obj Object;
    typedef QEXTMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QEXTNil, QEXTNil > Functor;

    std::string typeName() const
    {
        return "QEXTMemberFunctor5";
    }
};
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
struct QEXTFunctorTrait< T_return (T_obj::*)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const, false, false >
{
    typedef T_return Return;
    typedef T_obj Object;
    typedef QEXTConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QEXTNil, QEXTNil > Functor;

    std::string typeName() const
    {
        return "QEXTConstMemberFunctor5";
    }
};
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
struct QEXTFunctorTrait< T_return (T_obj::*)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) volatile, false, false >
{
    typedef T_return Return;
    typedef T_obj Object;
    typedef QEXTVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QEXTNil, QEXTNil > Functor;

    std::string typeName() const
    {
        return "QEXTVolatileMemberFunctor5";
    }
};
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
struct QEXTFunctorTrait< T_return (T_obj::*)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const volatile, false, false >
{
    typedef T_return Return;
    typedef T_obj Object;
    typedef QEXTConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QEXTNil, QEXTNil > Functor;

    std::string typeName() const
    {
        return "QEXTConstVolatileMemberFunctor5";
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
struct QEXTFunctorTrait< T_return (T_obj::*)(T_arg1, T_arg2, T_arg3, T_arg4), false, false >
{
    typedef T_return Return;
    typedef T_obj Object;
    typedef QEXTMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, QEXTNil, QEXTNil, QEXTNil> Functor;

    std::string typeName() const
    {
        return "QEXTMemberFunctor4";
    }
};
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
struct QEXTFunctorTrait< T_return (T_obj::*)(T_arg1, T_arg2, T_arg3, T_arg4) const, false, false >
{
    typedef T_return Return;
    typedef T_obj Object;
    typedef QEXTConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, QEXTNil, QEXTNil, QEXTNil > Functor;

    std::string typeName() const
    {
        return "QEXTConstMemberFunctor4";
    }
};
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
struct QEXTFunctorTrait< T_return (T_obj::*)(T_arg1, T_arg2, T_arg3, T_arg4) volatile, false, false >
{
    typedef T_return Return;
    typedef T_obj Object;
    typedef QEXTVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, QEXTNil, QEXTNil, QEXTNil > Functor;

    std::string typeName() const
    {
        return "QEXTVolatileMemberFunctor4";
    }
};
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
struct QEXTFunctorTrait< T_return (T_obj::*)(T_arg1, T_arg2, T_arg3, T_arg4) const volatile, false, false >
{
    typedef T_return Return;
    typedef T_obj Object;
    typedef QEXTConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, QEXTNil, QEXTNil, QEXTNil > Functor;

    std::string typeName() const
    {
        return "QEXTConstVolatileMemberFunctor4";
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3 >
struct QEXTFunctorTrait< T_return (T_obj::*)(T_arg1, T_arg2, T_arg3), false, false >
{
    typedef T_return Return;
    typedef T_obj Object;
    typedef QEXTMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, QEXTNil, QEXTNil, QEXTNil, QEXTNil > Functor;

    std::string typeName() const
    {
        return "QEXTMemberFunctor3";
    }
};
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3 >
struct QEXTFunctorTrait< T_return (T_obj::*)(T_arg1, T_arg2, T_arg3) const, false, false >
{
    typedef T_return Return;
    typedef T_obj Object;
    typedef QEXTConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, QEXTNil, QEXTNil, QEXTNil, QEXTNil > Functor;

    std::string typeName() const
    {
        return "QEXTConstMemberFunctor3";
    }
};
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3 >
struct QEXTFunctorTrait< T_return (T_obj::*)(T_arg1, T_arg2, T_arg3) volatile, false, false >
{
    typedef T_return Return;
    typedef T_obj Object;
    typedef QEXTVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, QEXTNil, QEXTNil, QEXTNil, QEXTNil > Functor;

    std::string typeName() const
    {
        return "QEXTVolatileMemberFunctor3";
    }
};
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3 >
struct QEXTFunctorTrait< T_return (T_obj::*)(T_arg1, T_arg2, T_arg3) const volatile, false, false >
{
    typedef T_return Return;
    typedef T_obj Object;
    typedef QEXTConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, QEXTNil, QEXTNil, QEXTNil, QEXTNil > Functor;

    std::string typeName() const
    {
        return "QEXTConstVolatileMemberFunctor3";
    }
};

template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2 >
struct QEXTFunctorTrait< T_return (T_obj::*)(T_arg1, T_arg2), false, false >
{
    typedef T_return Return;
    typedef T_obj Object;
    typedef QEXTMemberFunctor< T_return, T_obj, T_arg1, T_arg2, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil > Functor;

    std::string typeName() const
    {
        return "QEXTMemberFunctor2";
    }
};
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2 >
struct QEXTFunctorTrait< T_return (T_obj::*)(T_arg1, T_arg2) const, false, false >
{
    typedef T_return Return;
    typedef T_obj Object;
    typedef QEXTConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil > Functor;

    std::string typeName() const
    {
        return "QEXTConstMemberFunctor2";
    }
};
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2 >
struct QEXTFunctorTrait< T_return (T_obj::*)(T_arg1, T_arg2) volatile, false, false >
{
    typedef T_return Return;
    typedef T_obj Object;
    typedef QEXTVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil > Functor;

    std::string typeName() const
    {
        return "QEXTVolatileMemberFunctor2";
    }
};
template < typename T_return, typename T_obj, typename T_arg1, typename T_arg2 >
struct QEXTFunctorTrait< T_return (T_obj::*)(T_arg1, T_arg2) const volatile, false, false >
{
    typedef T_return Return;
    typedef T_obj Object;
    typedef QEXTConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil > Functor;

    std::string typeName() const
    {
        return "QEXTConstVolatileMemberFunctor2";
    }
};

template < typename T_return, typename T_obj, typename T_arg1 >
struct QEXTFunctorTrait< T_return (T_obj::*)(T_arg1), false, false >
{
    typedef T_return Return;
    typedef T_obj Object;
    typedef QEXTMemberFunctor< T_return, T_obj, T_arg1, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil > Functor;

    std::string typeName() const
    {
        return "QEXTMemberFunctor1";
    }
};
template < typename T_return, typename T_obj, typename T_arg1 >
struct QEXTFunctorTrait< T_return (T_obj::*)(T_arg1) const, false, false >
{
    typedef T_return Return;
    typedef T_obj Object;
    typedef QEXTConstMemberFunctor< T_return, T_obj, T_arg1, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil > Functor;

    std::string typeName() const
    {
        return "QEXTConstMemberFunctor1";
    }
};
template < typename T_return, typename T_obj, typename T_arg1 >
struct QEXTFunctorTrait< T_return (T_obj::*)(T_arg1) volatile, false, false >
{
    typedef T_return Return;
    typedef T_obj Object;
    typedef QEXTVolatileMemberFunctor< T_return, T_obj, T_arg1, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil > Functor;

    std::string typeName() const
    {
        return "QEXTVolatileMemberFunctor1";
    }
};
template < typename T_return, typename T_obj, typename T_arg1 >
struct QEXTFunctorTrait< T_return (T_obj::*)(T_arg1) const volatile, false, false >
{
    typedef T_return Return;
    typedef T_obj Object;
    typedef QEXTConstVolatileMemberFunctor< T_return, T_obj, T_arg1, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil > Functor;

    std::string typeName() const
    {
        return "QEXTConstVolatileMemberFunctor1";
    }
};

template < typename T_return, typename T_obj >
struct QEXTFunctorTrait< T_return (T_obj::*)(), false, false >
{
    typedef T_return Return;
    typedef T_obj Object;
    typedef QEXTMemberFunctor< T_return, T_obj, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil > Functor;

    std::string typeName() const
    {
        return "QEXTMemberFunctor0";
    }
};
template < typename T_return, typename T_obj >
struct QEXTFunctorTrait< T_return (T_obj::*)() const, false, false >
{
    typedef T_return Return;
    typedef T_obj Object;
    typedef QEXTConstMemberFunctor< T_return, T_obj, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil > Functor;

    std::string typeName() const
    {
        return "QEXTConstMemberFunctor0";
    }
};
template < typename T_return, typename T_obj >
struct QEXTFunctorTrait< T_return (T_obj::*)() volatile, false, false >
{
    typedef T_return Return;
    typedef T_obj Object;
    typedef QEXTVolatileMemberFunctor< T_return, T_obj, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil > Functor;

    std::string typeName() const
    {
        return "QEXTVolatileMemberFunctor0";
    }
};
template < typename T_return, typename T_obj >
struct QEXTFunctorTrait< T_return (T_obj::*)() const volatile, false, false >
{
    typedef T_return Return;
    typedef T_obj Object;
    typedef QEXTConstVolatileMemberFunctor< T_return, T_obj, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil > Functor;

    std::string typeName() const
    {
        return "QEXTConstVolatileMemberFunctor0";
    }
};



#endif // QEXTFUNCTORTRAIT_H
