/****************************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2021 ChengXueWen. Contact: 1398831004@qq.com
** Copyright (c) 2006, Google Inc.
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
** FITNESS FOR T_A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
** SOFTWARE.
**
****************************************************************************************************************************/

#ifndef _QEXTTYPETRAIT_H
#define _QEXTTYPETRAIT_H

#include <qextGlobal.h>

#if QEXT_CC_STD_11
#   include <type_traits>
#endif

#include <QPair>

namespace internal
{

// Types small_ and big_ are guaranteed such that sizeof(Small) <
// sizeof(Big)
typedef char Small;

struct Big
{
    char dummy[2];
};

// Identity metafunction.
template <typename T>
struct Identity
{
    typedef T Type;
};

}

/***********************************************************************************************************************
    QExt integral constant type trait
***********************************************************************************************************************/
// QExtIntegralConstant, defined in tr1, is a wrapper for an integer value. We don't really need this generality;
// we could get away with hardcoding the integer type to bool. We use the fully general QExtIntegralConstant
// for compatibility with tr1.
template<typename T, T v>
struct QExtIntegralConstant
{
    static const T value = v;
    typedef T Value;
    typedef QExtIntegralConstant<T, v> Type;
};

template<typename T, T v> const T QExtIntegralConstant<T, v>::value;

// Abbreviations: QExtTrueType and QExtFalseType are structs that represent boolean true and false values.
// Also define the boost::mpl versions of those names, true_ and false_.
typedef QExtIntegralConstant<bool, true>  QExtTrueType;
typedef QExtIntegralConstant<bool, false> QExtFalseType;


/***********************************************************************************************************************
    QExt is integral type trait
***********************************************************************************************************************/
template <typename T> struct QExtIsIntegral : public QExtFalseType {};
template <typename T> struct QExtIsIntegral<const T> : public QExtIsIntegral<T> {};
template <typename T> struct QExtIsIntegral<volatile const T> : public QExtIsIntegral<T>{};
template <typename T> struct QExtIsIntegral<volatile T> : public QExtIsIntegral<T>{};

//* is a type T an [cv-qualified-] integral type described in the standard (3.9.1p3)
// as an extension we include long long, as this is likely to be added to the
// standard at a later date
template<> struct QExtIsIntegral<unsigned char> : public QExtTrueType {};
template<> struct QExtIsIntegral<unsigned short> : public QExtTrueType{};
template<> struct QExtIsIntegral<unsigned int> : public QExtTrueType{};
template<> struct QExtIsIntegral<unsigned long> : public QExtTrueType{};

template<> struct QExtIsIntegral<signed char> : public QExtTrueType{};
template<> struct QExtIsIntegral<short> : public QExtTrueType{};
template<> struct QExtIsIntegral<int> : public QExtTrueType{};
template<> struct QExtIsIntegral<long> : public QExtTrueType{};

template<> struct QExtIsIntegral<char> : public QExtTrueType{};
template<> struct QExtIsIntegral<bool> : public QExtTrueType{};

#if defined(_MSC_VER)
// wchar_t is not by default a distinct type from unsigned short in Microsoft C.
// See http://msdn2.microsoft.com/en-us/library/dh8che7s(VS.80).aspx
template<> struct QExtIsIntegral<__wchar_t> : QExtTrueType { };
#else
template<> struct QExtIsIntegral<wchar_t> : QExtTrueType { };
#endif

#if defined(Q_OS_WIN) && !defined(Q_CC_GNU)
template<> struct QExtIsIntegral<__int64> : QExtTrueType { };
template<> struct QExtIsIntegral<unsigned __int64> : QExtTrueType { };
#else
template<> struct QExtIsIntegral<long long> : QExtTrueType { };
template<> struct QExtIsIntegral<unsigned long long> : QExtTrueType { };
#endif

#if QEXT_CC_FEATURE_UNICODE_STRINGS
template<> struct QExtIsIntegral<char16_t> : QExtTrueType { };
template<> struct QExtIsIntegral<char32_t> : QExtTrueType { };
#endif

typedef char QExtYesType;
struct QExtNoType { char padding[8]; };


/***********************************************************************************************************************
    QExt is floating point type trait
***********************************************************************************************************************/
template <bool, typename T = void> struct QExtTypeEnableIf { };
template <typename T> struct QExtTypeEnableIf<true, T>
{
    typedef T Type;
};

// QExtTypeIf is a templatized conditional statement.
// QExtTypeIf<cond, T_A, T_B> is a compile time evaluation of cond.
// QExtTypeIf<>::Type contains T_A if cond is true, T_B otherwise.
template<bool cond, typename T_A, typename T_B>
struct QExtTypeIf
{
    typedef T_A Type;
};

template<typename T_A, typename T_B>
struct QExtTypeIf<false, T_A, T_B>
{
    typedef T_B Type;
};

// QExtTypeAnd is a template && operator.
// QExtTypeAnd<T_A, T_B>::value evaluates "T_A::value && T_B::value".
template<typename T_A, typename T_B>
struct QExtTypeAnd : public QExtIntegralConstant<bool, (T_A::value && T_B::value)> { };

// QExtTypeOr is a template || operator.
// QExtTypeOr<T_A, T_B>::value evaluates "T_A::value || T_B::value".
template<typename T_A, typename T_B>
struct QExtTypeOr : public QExtIntegralConstant<bool, (T_A::value || T_B::value)> { };

// a metafunction to invert an QExtIntegralConstant:
template <typename T>
struct QExtTypeNot : QExtIntegralConstant<bool, !T::value> {};


/***********************************************************************************************************************
    QExt is floating point type trait
***********************************************************************************************************************/
// Checks whether a type is unsigned (T must be convertible to unsigned int):
template <typename T> struct QExtIsUnsigned : QExtIntegralConstant<bool, (T(0)<T(-1))> {};

// Checks whether a type is signed (T must be convertible to int):
template <typename T> struct QExtIsSigned : QExtTypeNot<QExtIsUnsigned<T> > {};

QEXT_STATIC_ASSERT(( QExtIsUnsigned<quint8>::value));
QEXT_STATIC_ASSERT((!QExtIsUnsigned<qint8>::value));

QEXT_STATIC_ASSERT((!QExtIsSigned<quint8>::value));
QEXT_STATIC_ASSERT(( QExtIsSigned<qint8>::value));

QEXT_STATIC_ASSERT(( QExtIsUnsigned<quint16>::value));
QEXT_STATIC_ASSERT((!QExtIsUnsigned<qint16>::value));

QEXT_STATIC_ASSERT((!QExtIsSigned<quint16>::value));
QEXT_STATIC_ASSERT(( QExtIsSigned<qint16>::value));

QEXT_STATIC_ASSERT(( QExtIsUnsigned<quint32>::value));
QEXT_STATIC_ASSERT((!QExtIsUnsigned<qint32>::value));

QEXT_STATIC_ASSERT((!QExtIsSigned<quint32>::value));
QEXT_STATIC_ASSERT(( QExtIsSigned<qint32>::value));

QEXT_STATIC_ASSERT(( QExtIsUnsigned<quint64>::value));
QEXT_STATIC_ASSERT((!QExtIsUnsigned<qint64>::value));

QEXT_STATIC_ASSERT((!QExtIsSigned<quint64>::value));
QEXT_STATIC_ASSERT(( QExtIsSigned<qint64>::value));


/***********************************************************************************************************************
    QExt is floating point type trait
***********************************************************************************************************************/
//* is a type T a floating-point type described in the standard (3.9.1p8)
template <typename T> struct QExtIsFloatingPoint : public QExtFalseType{};
template <typename T> struct QExtIsFloatingPoint<const T> : public QExtIsFloatingPoint<T>{};
template <typename T> struct QExtIsFloatingPoint<volatile const T> : public QExtIsFloatingPoint<T>{};
template <typename T> struct QExtIsFloatingPoint<volatile T> : public QExtIsFloatingPoint<T>{};
template<> struct QExtIsFloatingPoint<float> : public QExtTrueType{};
template<> struct QExtIsFloatingPoint<double> : public QExtTrueType{};
template<> struct QExtIsFloatingPoint<long double> : public QExtTrueType{};


/***********************************************************************************************************************
    QExt is float type trait
***********************************************************************************************************************/
template <typename T> struct QExtIsFloat : public QExtIsFloatingPoint<T> {};


/***********************************************************************************************************************
    QExt is arithmetic type trait
***********************************************************************************************************************/
template <typename T>
struct QExtIsArithmetic : public QExtIntegralConstant<bool, QExtIsIntegral<T>::value || QExtIsFloatingPoint<T>::value> {};


/***********************************************************************************************************************
    QExt is member pointer type trait
***********************************************************************************************************************/
#if QEXT_CC_STD_11
template <typename T>
struct QExtIsMemberPointer : public QExtIntegralConstant<bool, std::is_member_function_pointer<T>::value>{};
#endif
template <typename T, typename U> struct QExtIsMemberPointer<U T::* > : public QExtTrueType{};


/***********************************************************************************************************************
    QExt is same type trait
***********************************************************************************************************************/
template <typename T, typename U> struct QExtIsSame : public QExtFalseType {};
template <typename T> struct QExtIsSame<T,T> : public QExtTrueType {};


/***********************************************************************************************************************
    QExt is void type trait
***********************************************************************************************************************/
template <typename T> struct QExtIsVoid : public QExtFalseType {};
template<> struct QExtIsVoid<void> : public QExtTrueType {};
template<> struct QExtIsVoid<const void> : public QExtTrueType{};
template<> struct QExtIsVoid<const volatile void> : public QExtTrueType{};
template<> struct QExtIsVoid<volatile void> : public QExtTrueType{};


/***********************************************************************************************************************
    QExt is const type trait
***********************************************************************************************************************/
template <typename T> struct QExtIsConst : public QExtFalseType {};
template <typename T> struct QExtIsConst<T const> : public QExtTrueType{};
template <typename T> struct QExtIsConst<T const[]> : public QExtTrueType{};
template <typename T, std::size_t N> struct QExtIsConst<T const[N]> : public QExtTrueType{};


/***********************************************************************************************************************
    QExt remove const type trait
***********************************************************************************************************************/
template<typename T> struct QExtRemoveConst { typedef T Type; };
template<typename T> struct QExtRemoveConst<T const> { typedef T Type; };


/***********************************************************************************************************************
    QExt add const type trait
***********************************************************************************************************************/
template<typename T> struct QExtAddConst { typedef T const Type; };


/***********************************************************************************************************************
    QExt is volatile type trait
***********************************************************************************************************************/
template <typename T> struct QExtIsVolatile : public QExtFalseType {};
template <typename T> struct QExtIsVolatile<T volatile> : public QExtTrueType{};
template <typename T> struct QExtIsVolatile<T volatile[]> : public QExtTrueType{};
template <typename T, std::size_t N> struct QExtIsVolatile<T volatile[N]> : public QExtTrueType{};


/***********************************************************************************************************************
    QExt remove volatile type trait
***********************************************************************************************************************/
template<typename T> struct QExtRemoveVolatile { typedef T Type; };
template<typename T> struct QExtRemoveVolatile<T volatile> { typedef T Type; };


/***********************************************************************************************************************
    QExt add volatile type trait
***********************************************************************************************************************/
template<typename t> struct QExtAddVolatile { typedef t volatile Type; };


/***********************************************************************************************************************
    QExt remove const volatile type trait
***********************************************************************************************************************/
template<typename T>
struct QExtRemoveConstVolatile
{
    typedef typename QExtRemoveConst<typename QExtRemoveVolatile<T>::Type>::Type Type;
};


/***********************************************************************************************************************
    QExt add const volatile type trait
***********************************************************************************************************************/
template<typename T>
struct QExtAddConstVolatile
{
    typedef typename QExtAddConst<typename QExtAddVolatile<T>::Type>::Type Type;
};


/***********************************************************************************************************************
    QExt is reference type trait
***********************************************************************************************************************/
template<typename T> struct QExtIsLValueReference : QExtFalseType {};
template<typename T> struct QExtIsLValueReference<T &> : QExtTrueType {};

template <typename T> struct QExtIsRValueReference : public QExtFalseType {};
#if QEXT_CC_FEATURE_RVALUE_REFS
template <typename T> struct QExtIsRValueReference<T&&> : public QExtTrueType {};
#endif

template <typename T> struct QExtIsReference
    : public QExtIntegralConstant<bool, QExtIsLValueReference<T>::value || QExtIsRValueReference<T>::value> {};


/***********************************************************************************************************************
    QExt remove reference type trait
***********************************************************************************************************************/
// We can't filter out rvalue_references at the same level as references or we get ambiguities from msvc:
template <typename T>
struct QExtRemoveRValueReference
{
    typedef T Type;
};
#if QEXT_CC_FEATURE_RVALUE_REFS
template <typename T>
struct QExtRemoveRValueReference<T&&>
{
    typedef T Type;
};
#endif

template <typename T> struct QExtRemoveReference{ typedef typename QExtRemoveRValueReference<T>::Type Type; };
template <typename T> struct QExtRemoveReference<T&>{ typedef T Type; };


/***********************************************************************************************************************
    QExt add reference type trait
***********************************************************************************************************************/
namespace detail
{
// We can't filter out rvalue_references at the same level as references or we get ambiguities from msvc:
template <typename T>
struct QExtAddReferenceImpl
{
    typedef T& Type;
};
#if QEXT_CC_FEATURE_RVALUE_REFS
template <typename T>
struct QExtAddReferenceImpl<T&&>
{
    typedef T&& Type;
};
#endif
} // namespace detail

template <typename T>
struct QExtAddReference
{
    typedef typename detail::QExtAddReferenceImpl<T>::Type Type;
};
template <typename T>
struct QExtAddReference<T&>
{
    typedef T& Type;
};
template <> struct QExtAddReference<void> { typedef void Type; };


/***********************************************************************************************************************
    QExt is pointer type trait
***********************************************************************************************************************/
template <typename T> struct QExtIsPointer : public QExtFalseType{};
template <typename T> struct QExtIsPointer<T*> : public QExtTrueType{};
template <typename T> struct QExtIsPointer<T*const> : public QExtTrueType{};
template <typename T> struct QExtIsPointer<T*const volatile> : public QExtTrueType{};
template <typename T> struct QExtIsPointer<T*volatile> : public QExtTrueType{};

#ifdef _MSC_VER
template <typename T> struct QExtIsPointer<T const> : public QExtIsPointer<T>{};
template <typename T> struct QExtIsPointer<T const volatile> : public QExtIsPointer<T>{};
template <typename T> struct QExtIsPointer<T volatile> : public QExtIsPointer<T>{};
#endif


/***********************************************************************************************************************
    QExt remove pointer type trait
***********************************************************************************************************************/
template<typename T> struct QExtRemovePointer { typedef T Type; };
template<typename T> struct QExtRemovePointer<T *> { typedef T Type; };
template<typename T> struct QExtRemovePointer<T *const> { typedef T Type; };
template<typename T> struct QExtRemovePointer<T *volatile> { typedef T Type; };
template<typename T> struct QExtRemovePointer<T *const volatile> { typedef T Type; };


/***********************************************************************************************************************
    QExt add pointer type trait
***********************************************************************************************************************/
template<typename T> struct QExtAddPointer { typedef typename QExtRemoveReference<T>::Type *Type; };


/***********************************************************************************************************************
    QExt is union type trait
***********************************************************************************************************************/
#if ((defined(QEXT_CC_MSVC) && defined(QEXT_MSVC_FULL_VER) && (QEXT_MSVC_FULL_VER >=140050215)) || \
    (defined(QEXT_CC_INTEL) && defined(_MSC_VER) && (_MSC_VER >= 1500)))
#   define QEXT_IS_UNION(T) __is_union(T)
#elif (defined(QEXT_CC_CLANG) && defined(__has_feature) && !defined(__CUDACC__)) && __has_feature(is_union)
#   define QEXT_IS_UNION(T) __is_union(T)
#elif (defined(__GNUC__) && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 3) && !defined(__GCCXML__))) && \
    !defined(QEXT_CC_CLANG))
#   define QEXT_IS_UNION(T) __is_union(T)
#elif defined(__SUNPRO_CC) && (__SUNPRO_CC >= 0x5130)
#   define QEXT_IS_UNION(T) __oracle_is_union(T)
#endif

#ifdef QEXT_IS_UNION
template <typename T> struct QExtIsUnion : public QExtIntegralConstant<bool, QEXT_IS_UNION(T)> {};
#else
template <typename T> struct QExtIsUnion : public QExtIntegralConstant<bool, false> {};
#endif

template <typename T> struct QExtIsUnion<T const> : public QExtIsUnion<T>{};
template <typename T> struct QExtIsUnion<T volatile const> : public QExtIsUnion<T>{};
template <typename T> struct QExtIsUnion<T volatile> : public QExtIsUnion<T>{};


/***********************************************************************************************************************
    QExt is array type trait
***********************************************************************************************************************/
template <typename T> struct QExtIsArray : public QExtFalseType {};
template <typename T, std::size_t N> struct QExtIsArray<T[N]> : public QExtTrueType {};
template <typename T, std::size_t N> struct QExtIsArray<T const[N]> : public QExtTrueType{};
template <typename T, std::size_t N> struct QExtIsArray<T volatile[N]> : public QExtTrueType{};
template <typename T, std::size_t N> struct QExtIsArray<T const volatile[N]> : public QExtTrueType{};
template <typename T> struct QExtIsArray<T[]> : public QExtTrueType{};
template <typename T> struct QExtIsArray<T const[]> : public QExtTrueType{};
template <typename T> struct QExtIsArray<T const volatile[]> : public QExtTrueType{};
template <typename T> struct QExtIsArray<T volatile[]> : public QExtTrueType{};


/***********************************************************************************************************************
    QExt is convertible type trait
***********************************************************************************************************************/
// Specified by TR1 [4.6] Relationships between types
#if !defined(_MSC_VER) && !(defined(__GNUC__) && __GNUC__ <= 3)
namespace internal
{
// This class is an implementation detail for QExtIsConvertible, and you don't need to know how it works to use
// QExtIsConvertible. For those who care: we declare two different functions, one whose argument is of type To and
// one with a variadic argument list. We give them return types of different size, so we can use sizeof to trick the
// compiler into telling us which function it would have chosen if we had called it with an argument of type From.
// See Alexandrescu's _Modern C++ Design_ for more details on this sort of trick.
template <typename From, typename To>
struct ConvertHelper
{
    static Small Test(To);
    static Big Test(...);
    static From Create();
};

}

// Inherits from QExtTrueType if From is convertible to To, QExtFalseType otherwise.
template <typename From, typename To>
struct QExtIsConvertible
    : QExtIntegralConstant<bool, sizeof(internal::ConvertHelper<From, To>::Test(internal::ConvertHelper<From, To>::Create())) == sizeof(internal::Small)>
{
};

#endif


/***********************************************************************************************************************
    QExt is enum type trait
***********************************************************************************************************************/
#if (defined(QEXT_CC_MSVC) && defined(QEXT_CC_MSVC_FULL_VER) && (QEXT_CC_MSVC_FULL_VER >=140050215)) \
    || (defined(QEXT_CC_INTEL) && defined(_MSC_VER) && (_MSC_VER >= 1500))
#   define QEXT_IS_ENUM(T) __is_enum(T)
#elif defined(QEXT_CC_CLANG) && defined(__has_feature) && !defined(__CUDACC__) && __has_feature(is_enum)
// #   define QEXT_IS_ENUM(T) __is_enum(T)
#elif defined(__GNUC__) && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 3) && !defined(__GCCXML__))) && \
    !defined(QEXT_CC_CLANG)
#   define QEXT_IS_ENUM(T) __is_enum(T)
#elif defined(__SUNPRO_CC) && (__SUNPRO_CC >= 0x5130)
#   define QEXT_IS_ENUM(T) __oracle_is_enum(T)
#endif

#ifndef QEXT_IS_ENUM
#   if !defined(_MSC_VER) && !(defined(__GNUC__) && __GNUC__ <= 3)
template <typename T> struct QExtTypeIsClassOrUnion
{
    template <typename U> static internal::Small tester(void (U::*)());
    template <typename U> static internal::Big tester(...);
    static const bool value = sizeof(tester<T>(0)) == sizeof(internal::Small);
};

// QExtIsConvertible chokes if the first argument is an array. That's why we use QExtAddReference here.
template <bool NotUnum, typename T>
struct QExtTypeIsEnumImpl : QExtIsConvertible<typename QExtAddReference<T>::Type, int> { };
template <typename T> struct QExtTypeIsEnumImpl<true, T> : QExtFalseType { };


// Specified by TR1 [4.5.1] primary type categories.
// Implementation note:
// Each type is either void, integral, floating point, array, pointer, reference, member object pointer, member function
// pointer, enum, union or class. Out of these, only integral, floating point, reference, class and enum types are
// potentially convertible to int. Therefore, if a type is not a reference, integral, floating point or class and
// is convertible to int, it's a enum. Adding cv-qualification to a type does not change whether it's an enum.
//
// Is-convertible-to-int check is done only if all other checks pass, because it can't be used with some types
// (e.g. void or classes with inaccessible conversion operators).
template <typename T> struct QExtIsEnum : QExtTypeIsEnumImpl<QExtIsSame<T, void>::value ||
                                                                 QExtIsIntegral<T>::value ||
                                                                 QExtIsFloatingPoint<T>::value ||
                                                                 QExtIsReference<T>::value ||
                                                                 QExtTypeIsClassOrUnion<T>::value, T>
{
};

template <typename T> struct QExtIsEnum<const T> : QExtIsEnum<T> { };
template <typename T> struct QExtIsEnum<volatile T> : QExtIsEnum<T> { };
template <typename T> struct QExtIsEnum<const volatile T> : QExtIsEnum<T> { };
#   else
template <typename T> struct QExtIsEnum : public QExtIntegralConstant<bool, false> {};
#   endif
#else // QEXT_IS_ENUM
template <class T> struct QExtIsEnum : public QExtIntegralConstant<bool, QEXT_IS_ENUM(T)> {};
#endif











template <typename T> struct QExtTypeIsPod;
template <typename T> struct QExtTypeHasTrivialConstructor;
template <typename T> struct QExtTypeHasTrivialCopy;
template <typename T> struct QExtTypeHasTrivialAssign;
template <typename T> struct QExtTypeHasTrivialDestructor;

template <typename T>
struct QExtTypeTrait
{
    typedef T          Type;
    typedef T         &Pass;
    typedef const T   &Take;
    typedef T         *Pointer;
};

template <typename T, int N>
struct QExtTypeTrait<T[N]>
{
    typedef T         *Type;
    typedef T        *&Pass;
    typedef const T  *&Take;
    typedef T        **Pointer;
};

template <typename T>
struct QExtTypeTrait<T &>
{
    typedef T          Type;
    typedef T         &Pass;
    typedef T         &Take;
    typedef T         *Pointer;
};

template <typename T>
struct QExtTypeTrait<const T &>
{
    typedef const T    Type;
    typedef const T   &Pass;
    typedef const T   &Take;
    typedef const T   *Pointer;
};

template<>
struct QExtTypeTrait<void>
{
    typedef void            Type;
    typedef void            Pass;
    typedef void            Take;
    typedef void           *Pointer;
};



// We can't get QExtTypeIsPod right without compiler help, so fail conservatively.
// We will assume it's false except for arithmetic types, enumerations,
// pointers and cv-qualified versions thereof. Note that QPair<T,U>
// is not a POD even if T and U are PODs.
template <typename T> struct QExtTypeIsPod
    : QExtIntegralConstant < bool, (QExtIsIntegral<T>::value || QExtIsFloatingPoint<T>::value ||
#if !defined(_MSC_VER) && !(defined(__GNUC__) && __GNUC__ <= 3)
                                  // QExtIsEnum is not available on MSVC.
                                  QExtIsEnum<T>::value ||
#endif
                                  QExtIsPointer<T>::value) >
{
};
template <typename T> struct QExtTypeIsPod<const T> : QExtTypeIsPod<T> { };
template <typename T> struct QExtTypeIsPod<volatile T> : QExtTypeIsPod<T> { };
template <typename T> struct QExtTypeIsPod<const volatile T> : QExtTypeIsPod<T> { };



// We can't get QExtTypeHasTrivialConstructor right without compiler help, so
// fail conservatively. We will assume it's false except for: (1) types
// for which QExtTypeIsPod is true. (2) QPair of types with trivial
// constructors. (3) array of a type with a trivial constructor.
// (4) const versions thereof.
template <typename T> struct QExtTypeHasTrivialConstructor
    : QExtTypeIsPod<T> { };
template <typename T, typename U> struct QExtTypeHasTrivialConstructor<QPair<T, U> >
    : QExtIntegralConstant<bool, (QExtTypeHasTrivialConstructor<T>::value && QExtTypeHasTrivialConstructor<U>::value) > { };
template <typename T_A, int N> struct QExtTypeHasTrivialConstructor<T_A[N]>
    : QExtTypeHasTrivialConstructor<T_A> { };
template <typename T> struct QExtTypeHasTrivialConstructor<const T>
    : QExtTypeHasTrivialConstructor<T> { };


// We can't get QExtTypeHasTrivialCopy right without compiler help, so fail
// conservatively. We will assume it's false except for: (1) types
// for which QExtTypeIsPod is true. (2) QPair of types with trivial copy
// constructors. (3) array of a type with a trivial copy constructor.
// (4) const versions thereof.
template <typename T> struct QExtTypeHasTrivialCopy
    : QExtTypeIsPod<T> { };
template <typename T, typename U> struct QExtTypeHasTrivialCopy<QPair<T, U> >
    : QExtIntegralConstant<bool, (QExtTypeHasTrivialCopy<T>::value && QExtTypeHasTrivialCopy<U>::value) > { };
template <typename T_A, int N> struct QExtTypeHasTrivialCopy<T_A[N]>
    : QExtTypeHasTrivialCopy<T_A> { };
template <typename T> struct QExtTypeHasTrivialCopy<const T> : QExtTypeHasTrivialCopy<T> { };


// We can't get QExtTypeHasTrivialAssign right without compiler help, so fail
// conservatively. We will assume it's false except for: (1) types
// for which QExtTypeIsPod is true. (2) QPair of types with trivial copy
// constructors. (3) array of a type with a trivial assign constructor.
template <typename T> struct QExtTypeHasTrivialAssign
    : QExtTypeIsPod<T> { };
template <typename T, typename U> struct QExtTypeHasTrivialAssign<QPair<T, U> >
    : QExtIntegralConstant<bool, (QExtTypeHasTrivialAssign<T>::value && QExtTypeHasTrivialAssign<U>::value) > { };
template <typename T_A, int N> struct QExtTypeHasTrivialAssign<T_A[N]>
    : QExtTypeHasTrivialAssign<T_A> { };

// We can't get QExtTypeHasTrivialDestructor right without compiler help, so
// fail conservatively. We will assume it's false except for: (1) types
// for which QExtTypeIsPod is true. (2) QPair of types with trivial
// destructors. (3) array of a type with a trivial destructor.
// (4) const versions thereof.
template <typename T> struct QExtTypeHasTrivialDestructor
    : QExtTypeIsPod<T> { };
template <typename T, typename U> struct QExtTypeHasTrivialDestructor<QPair<T, U> >
    : QExtIntegralConstant<bool, (QExtTypeHasTrivialDestructor<T>::value && QExtTypeHasTrivialDestructor<U>::value) > { };
template <typename T_A, int N> struct QExtTypeHasTrivialDestructor<T_A[N]>
    : QExtTypeHasTrivialDestructor<T_A> { };
template <typename T> struct QExtTypeHasTrivialDestructor<const T>
    : QExtTypeHasTrivialDestructor<T> { };


template<typename T = void> struct QExtTypeIsDefaultConstructible;

template<>
struct QExtTypeIsDefaultConstructible<void>
{
protected:
    template<bool> struct Test
    {
        typedef char Type;
    };
public:
    static bool const value = false;
};

template<>
struct QExtTypeIsDefaultConstructible<>::Test<true>
{
    typedef double Type;
};

template<typename T>
struct QExtTypeIsDefaultConstructible : QExtTypeIsDefaultConstructible<>
{
private:
    template<typename U> static typename Test < !!sizeof(::new U()) >::Type sfinae(U *);
    template<typename U> static char sfinae(...);
public:
    static bool const value = sizeof(sfinae<T>(0)) > 1;
};


#if QEXT_CC_STD_11
//std::is_base_of

template <typename T_base, typename T_derived>
struct QEXTIsBaseOf : public std::is_base_of<T_base, T_derived> { };

#else

/**
 * Compile-time determination of base-class relationship in C++.
 *
 * Use this to provide a template specialization for a set of types.
 * For instance,
 *
 * @code
 * template < class T_thing, bool Tval_derives_from_something = QEXTIsBaseOf<Something, T_thing>::value >
 * class TheTemplate
 * {
 *   //Standard implementation.
 * }
 *
 * //Specialization for T_things that derive from Something (Tval_derives_from_something is true)
 * template <typename T_thing>
 * class TheTemplate<T_thing, true>
 * {
 *   T_thing thing;
 *   thing.method_that_is_in_something();
 * }
 * @endcode
 *
 * If you need such a template class elsewhere, and you have a C++11 compiler, std::is_base_of<>
 * is recommended.
 */
template <typename T_base, typename T_derived>
struct QEXTIsBaseOf
{
private:
    struct Big
    {
        char memory[64];
    };

//#ifndef _QEXT_SELF_REFERENCE_IN_MEMBER_INITIALIZATION
#if 0

    //Allow the internal inner class to access the other (Big) inner class.
    //The Tru64 compiler needs this.
    friend struct InternalClass;

    //Certain compilers, notably GCC 3.2, require these functions to be inside an inner class.
    struct InternalClass
    {
        static Big  isBaseClass(...);
        static char isBaseClass(typename QExtTypeTrait<T_base>::Pointer);
    };

public:
    static const bool value =
        sizeof(InternalClass::isBaseClass(reinterpret_cast<typename QExtTypeTrait<T_derived>::Pointer>(0))) ==
        sizeof(char);

#else //SELF_REFERENCE_IN_MEMBER_INITIALIZATION

    //The AIX xlC compiler does not like these 2 functions being in the inner class.
    //It says "The incomplete type "test" must not be used as a qualifier.
    //It does not seem necessary anyway.
    static Big  isBaseClass(...);
    static char isBaseClass(typename QExtTypeTrait<T_base>::Pointer);

public:
    static const bool value =
        sizeof(isBaseClass(reinterpret_cast<typename QExtTypeTrait<T_derived>::Pointer>(0))) ==
        sizeof(char);

#endif //SELF_REFERENCE_IN_MEMBER_INITIALIZATION
};

template <typename T_base>
struct QEXTIsBaseOf<T_base, T_base>
{
    static const bool value = true;
};

#endif

#endif // _QEXTTYPETRAIT_H
