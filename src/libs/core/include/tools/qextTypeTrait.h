/*************************************************************************************
**
** Library: QEXT
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
*************************************************************************************/

#ifndef _QEXTTYPETRAIT_H
#define _QEXTTYPETRAIT_H

#include <qextGlobal.h>

#if QEXT_CC_STD_11
    #include <type_traits>
#endif

#include <utility>

template <typename T_type, typename U> struct QEXTTypeIsSame;
template <typename T_type> struct QEXTTypeIsIntegral;
template <typename T_type> struct QEXTTypeIsFloating;
template <typename T_type> struct QEXTTypeIsPointer;
template <typename T_type> struct QEXTTypeIsFloatingPoint;
// MSVC can't compile this correctly, and neither can gcc 3.3.5 (at least)
#if !defined(_MSC_VER) && !(defined(__GNUC__) && __GNUC__ <= 3)
// is_enum uses is_convertible, which is not available on MSVC.
template <typename T_type> struct QEXTTypeIsEnum;
#endif
template <typename T_type> struct QEXTTypeIsPod;
template <typename T_type> struct QEXTTypeIsReference;
template <typename T_type> struct QEXTTypeHasTrivialConstructor;
template <typename T_type> struct QEXTTypeHasTrivialCopy;
template <typename T_type> struct QEXTTypeHasTrivialAssign;
template <typename T_type> struct QEXTTypeHasTrivialDestructor;
template <typename T_type> struct QEXTTypeRemoveConst;
template <typename T_type> struct QEXTTypeRemoveVolatile;
template <typename T_type> struct QEXTTypeRemoveConstVolatile;
template <typename T_type> struct QEXTTypeRemoveReference;
template <typename T_type> struct QEXTTypeAddReference;
template <typename T_type> struct QEXTTypeRemovePointer;
#if !defined(_MSC_VER) && !(defined(__GNUC__) && __GNUC__ <= 3)
template <typename From, typename To> struct QEXTTypeIsConvertible;
#endif

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
    template <typename T_type>
    struct Identity
    {
        typedef T_type Type;
    };

}

template <typename T_type>
struct QEXTTypeTrait
{
    typedef T_type          Type;
    typedef T_type         &Pass;
    typedef const T_type   &Take;
    typedef T_type         *Pointer;
};

template <typename T_type, int N>
struct QEXTTypeTrait<T_type[N]>
{
    typedef T_type         *Type;
    typedef T_type        *&Pass;
    typedef const T_type  *&Take;
    typedef T_type        **Pointer;
};

template <typename T_type>
struct QEXTTypeTrait<T_type &>
{
    typedef T_type          Type;
    typedef T_type         &Pass;
    typedef T_type         &Take;
    typedef T_type         *Pointer;
};

template <typename T_type>
struct QEXTTypeTrait<const T_type &>
{
    typedef const T_type    Type;
    typedef const T_type   &Pass;
    typedef const T_type   &Take;
    typedef const T_type   *Pointer;
};

template<>
struct QEXTTypeTrait<void>
{
    typedef void            Type;
    typedef void            Pass;
    typedef void            Take;
    typedef void           *Pointer;
};



// QEXTTypeIntegralConstant, defined in tr1, is a wrapper for an integer
// value. We don't really need this generality; we could get away
// with hardcoding the integer type to bool. We use the fully
// general QEXTIntegralConstant for compatibility with tr1.
template<typename T_type, T_type v>
struct QEXTTypeIntegralConstant
{
    static const T_type value = v;
    typedef T_type Value;
    typedef QEXTTypeIntegralConstant<T_type, v> Type;
};

template<typename T_type, T_type v> const T_type QEXTTypeIntegralConstant<T_type, v>::value;

// Abbreviations: true_type and false_type are structs that represent boolean
// true and false values. Also define the boost::mpl versions of those names,
// true_ and false_.
typedef QEXTTypeIntegralConstant<bool, true>  QEXTTypeTrue;
typedef QEXTTypeIntegralConstant<bool, false> QEXTTypeFalse;



template <bool, typename T_type = void> struct QEXTTypeEnableIf { };
template <typename T_type> struct QEXTTypeEnableIf<true, T_type>
{
    typedef T_type Type;
};


// QEXTTypeIf is a templatized conditional statement.
// QEXTTypeIf<cond, T_A, T_B> is a compile time evaluation of cond.
// QEXTTypeIf<>::Type contains T_A if cond is true, T_B otherwise.
template<bool cond, typename T_A, typename T_B>
struct QEXTTypeIf
{
    typedef T_A Type;
};

template<typename T_A, typename T_B>
struct QEXTTypeIf<false, T_A, T_B>
{
    typedef T_B Type;
};


// QEXTTypeAnd is a template && operator.
// QEXTTypeAnd<T_A, T_B>::value evaluates "T_A::value && T_B::value".
template<typename T_A, typename T_B>
struct QEXTTypeAnd : public QEXTTypeIntegralConstant<bool, (T_A::value && T_B::value)> { };

// QEXTTypeOr is a template || operator.
// QEXTTypeOr<T_A, T_B>::value evaluates "T_A::value || T_B::value".
template<typename T_A, typename T_B>
struct QEXTTypeOr : public QEXTTypeIntegralConstant<bool, (T_A::value || T_B::value)> { };

// a metafunction to invert an QEXTTypeIntegralConstant:
template <typename T_type>
struct QEXTTypeNot : QEXTTypeIntegralConstant<bool, !T_type::value> {};


// QEXTTypeEquals is a template type comparator, similar to Loki IsSameType.
// QEXTTypeEquals<T_A, T_B>::value is true iff "T_A" is the same type as "T_B".
//
// New code should prefer base::is_same, defined in base/type_traits.h.
// It is functionally identical, but is_same is the standard spelling.
template<typename T_type, typename T_unknown> struct QEXTTypeEquals : public QEXTTypeFalse { };
template<typename T_type> struct QEXTTypeEquals<T_type, T_type> : public QEXTTypeTrue { };

// QEXTTypeIsSame
template<typename T_type, typename T_unknown> struct QEXTTypeIsSame : QEXTTypeFalse {};
template<typename T_type>  struct QEXTTypeIsSame<T_type, T_type> : QEXTTypeTrue {};

// QEXTTypeIsVoid
template<typename T_type> struct QEXTTypeIsVoid : QEXTTypeFalse { };
template<> struct QEXTTypeIsVoid<void> : QEXTTypeTrue { };


// QEXTTypeIsIntegral
template<typename T_type> struct QEXTTypeIsIntegral : QEXTTypeFalse { };
template<> struct QEXTTypeIsIntegral<bool> : QEXTTypeTrue { };
template<> struct QEXTTypeIsIntegral<char> : QEXTTypeTrue { };
template<> struct QEXTTypeIsIntegral<unsigned char> : QEXTTypeTrue { };
template<> struct QEXTTypeIsIntegral<signed char> : QEXTTypeTrue { };
#if defined(_MSC_VER)
// wchar_t is not by default a distinct type from unsigned short in
// Microsoft C.
// See http://msdn2.microsoft.com/en-us/library/dh8che7s(VS.80).aspx
template<> struct QEXTTypeIsIntegral<__wchar_t> : QEXTTypeTrue { };
#else
template<> struct QEXTTypeIsIntegral<wchar_t> : QEXTTypeTrue { };
#endif
template<> struct QEXTTypeIsIntegral<short> : QEXTTypeTrue { };
template<> struct QEXTTypeIsIntegral<unsigned short> : QEXTTypeTrue { };
template<> struct QEXTTypeIsIntegral<int> : QEXTTypeTrue { };
template<> struct QEXTTypeIsIntegral<unsigned int> : QEXTTypeTrue { };
template<> struct QEXTTypeIsIntegral<long> : QEXTTypeTrue { };
template<> struct QEXTTypeIsIntegral<unsigned long> : QEXTTypeTrue { };
#if defined(Q_OS_WIN) && !defined(Q_CC_GNU)
template<> struct QEXTTypeIsIntegral<__int64> : QEXTTypeTrue { };
template<> struct QEXTTypeIsIntegral<unsigned __int64> : QEXTTypeTrue { };
#else
template<> struct QEXTTypeIsIntegral<long long> : QEXTTypeTrue { };
template<> struct QEXTTypeIsIntegral<unsigned long long> : QEXTTypeTrue { };
#endif

template<typename T_type> struct QEXTTypeIsIntegral<const T_type> : QEXTTypeIsIntegral<T_type> { };
template<typename T_type> struct QEXTTypeIsIntegral<volatile T_type> : QEXTTypeIsIntegral<T_type> { };
template<typename T_type> struct QEXTTypeIsIntegral<const volatile T_type> : QEXTTypeIsIntegral<T_type> { };
#if QEXT_CC_FEATURE_UNICODE_STRINGS
template<> struct QEXTTypeIsIntegral<char16_t> : QEXTTypeTrue { };
template<> struct QEXTTypeIsIntegral<char32_t> : QEXTTypeTrue { };
#endif

// QEXTTypeIsFloating
template<typename T_type> struct QEXTTypeIsFloating : QEXTTypeFalse { };
template<> struct QEXTTypeIsFloating<float> : QEXTTypeTrue { };
template<> struct QEXTTypeIsFloating<double> : QEXTTypeTrue { };
template<> struct QEXTTypeIsFloating<long double> : QEXTTypeTrue { };

template<typename T_type> struct QEXTTypeIsFloating<const T_type> : QEXTTypeIsFloating<T_type> { };
template<typename T_type> struct QEXTTypeIsFloating<volatile T_type> : QEXTTypeIsFloating<T_type> { };
template<typename T_type> struct QEXTTypeIsFloating<const volatile T_type> : QEXTTypeIsFloating<T_type> { };


// QEXTTypeIsFloatingPoint is false except for the built-in floating-point types.
// T_A cv-qualified type is integral if and only if the underlying type is.
template <typename T_type> struct QEXTTypeIsFloatingPoint : QEXTTypeFalse { };
template<> struct QEXTTypeIsFloatingPoint<float> : QEXTTypeTrue { };
template<> struct QEXTTypeIsFloatingPoint<double> : QEXTTypeTrue { };
template<> struct QEXTTypeIsFloatingPoint<long double> : QEXTTypeTrue { };
template <typename T_type> struct QEXTTypeIsFloatingPoint<const T_type> : QEXTTypeIsFloatingPoint<T_type> { };
template <typename T_type> struct QEXTTypeIsFloatingPoint<volatile T_type> : QEXTTypeIsFloatingPoint<T_type> { };
template <typename T_type> struct QEXTTypeIsFloatingPoint<const volatile T_type> : QEXTTypeIsFloatingPoint<T_type> { };


// QEXTTypeIsPointer is false except for pointer types. T_A cv-qualified type (e.g.
// "int* const", as opposed to "int const*") is cv-qualified if and only if
// the underlying type is.
// QEXTTypeIsPointer
template <typename T_type> struct QEXTTypeIsPointer : QEXTTypeFalse { };
template <typename T_type> struct QEXTTypeIsPointer<T_type *> : QEXTTypeTrue { };
template <typename T_type> struct QEXTTypeIsPointer<const T_type> : QEXTTypeIsPointer<T_type> { };
template <typename T_type> struct QEXTTypeIsPointer<volatile T_type> : QEXTTypeIsPointer<T_type> { };
template <typename T_type> struct QEXTTypeIsPointer<const volatile T_type> : QEXTTypeIsPointer<T_type> { };


// is_reference is false except for reference types.
template<typename T_type> struct QEXTTypeIsReference : QEXTTypeFalse {};
template<typename T_type> struct QEXTTypeIsReference<T_type &> : QEXTTypeTrue {};


// Specified by TR1 [4.5.3] Type Properties
template <typename T_type> struct QEXTTypeIsConst : QEXTTypeFalse {};
template <typename T_type> struct QEXTTypeIsConst<const T_type> : QEXTTypeTrue {};
template <typename T_type> struct QEXTTypeIsVolatile : QEXTTypeFalse {};
template <typename T_type> struct QEXTTypeIsVolatile<volatile T_type> : QEXTTypeTrue {};


#if !defined(_MSC_VER) && !(defined(__GNUC__) && __GNUC__ <= 3)

template <typename T_type> struct QEXTTypeIsClassOrUnion
{
    template <typename U> static internal::Small tester(void (U::*)());
    template <typename U> static internal::Big tester(...);
    static const bool value = sizeof(tester<T_type>(0)) == sizeof(internal::Small);
};

// QEXTTypeIsConvertible chokes if the first argument is an array. That's why
// we use QEXTTypeAddReference here.
template <bool NotUnum, typename T_type>
struct QEXTTypeIsEnumImpl : QEXTTypeIsConvertible<typename QEXTTypeAddReference<T_type>::Type, int>
{
};
template <typename T_type> struct QEXTTypeIsEnumImpl<true, T_type> : QEXTTypeFalse { };


// Specified by TR1 [4.5.1] primary type categories.

// Implementation note:
//
// Each type is either void, integral, floating point, array, pointer,
// reference, member object pointer, member function pointer, enum,
// union or class. Out of these, only integral, floating point, reference,
// class and enum types are potentially convertible to int. Therefore,
// if a type is not a reference, integral, floating point or class and
// is convertible to int, it's a enum. Adding cv-qualification to a type
// does not change whether it's an enum.
//
// Is-convertible-to-int check is done only if all other checks pass,
// because it can't be used with some types (e.g. void or classes with
// inaccessible conversion operators).
template <typename T_type> struct QEXTTypeIsEnum
    : QEXTTypeIsEnumImpl<QEXTTypeIsSame<T_type, void>::value ||
                        QEXTTypeIsIntegral<T_type>::value ||
                        QEXTTypeIsFloatingPoint<T_type>::value ||
                        QEXTTypeIsReference<T_type>::value ||
                        QEXTTypeIsClassOrUnion<T_type>::value,
      T_type>
{
};

template <typename T_type> struct QEXTTypeIsEnum<const T_type> : QEXTTypeIsEnum<T_type> { };
template <typename T_type> struct QEXTTypeIsEnum<volatile T_type> : QEXTTypeIsEnum<T_type> { };
template <typename T_type> struct QEXTTypeIsEnum<const volatile T_type> : QEXTTypeIsEnum<T_type> { };

#endif

#ifndef QEXT_IS_ENUM
    #if defined(QEXT_CC_GNU) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3))
        #define QEXT_IS_ENUM(x) __is_enum(x)
    #elif defined(QEXT_CC_MSVC) && defined(_MSC_FULL_VER) && (_MSC_FULL_VER >=140050215)
        #define QEXT_IS_ENUM(x) __is_enum(x)
    #elif defined(QEXT_CC_CLANG)
        #if __has_extension(is_enum)
            #define QEXT_IS_ENUM(x) __is_enum(x)
        #endif
    #endif
#endif

#ifndef QEXT_IS_ENUM
    #define QEXT_IS_ENUM(x) QEXTTypeIsEnum<x>::value
#endif


// We can't get QEXTTypeIsPod right without compiler help, so fail conservatively.
// We will assume it's false except for arithmetic types, enumerations,
// pointers and cv-qualified versions thereof. Note that std::pair<T_type,U>
// is not a POD even if T_type and U are PODs.
template <typename T_type> struct QEXTTypeIsPod
    : QEXTTypeIntegralConstant < bool, (QEXTTypeIsIntegral<T_type>::value || QEXTTypeIsFloatingPoint<T_type>::value ||
#if !defined(_MSC_VER) && !(defined(__GNUC__) && __GNUC__ <= 3)
    // QEXTTypeIsEnum is not available on MSVC.
    QEXTTypeIsEnum<T_type>::value ||
#endif
    QEXTTypeIsPointer<T_type>::value) >
{
};
template <typename T_type> struct QEXTTypeIsPod<const T_type> : QEXTTypeIsPod<T_type> { };
template <typename T_type> struct QEXTTypeIsPod<volatile T_type> : QEXTTypeIsPod<T_type> { };
template <typename T_type> struct QEXTTypeIsPod<const volatile T_type> : QEXTTypeIsPod<T_type> { };



// We can't get QEXTTypeHasTrivialConstructor right without compiler help, so
// fail conservatively. We will assume it's false except for: (1) types
// for which QEXTTypeIsPod is true. (2) std::pair of types with trivial
// constructors. (3) array of a type with a trivial constructor.
// (4) const versions thereof.
template <typename T_type> struct QEXTTypeHasTrivialConstructor
    : QEXTTypeIsPod<T_type> { };
template <typename T_type, typename U> struct QEXTTypeHasTrivialConstructor<std::pair<T_type, U> >
    : QEXTTypeIntegralConstant<bool, (QEXTTypeHasTrivialConstructor<T_type>::value && QEXTTypeHasTrivialConstructor<U>::value) > { };
template <typename T_A, int N> struct QEXTTypeHasTrivialConstructor<T_A[N]>
    : QEXTTypeHasTrivialConstructor<T_A> { };
template <typename T_type> struct QEXTTypeHasTrivialConstructor<const T_type>
    : QEXTTypeHasTrivialConstructor<T_type> { };


// We can't get QEXTTypeHasTrivialCopy right without compiler help, so fail
// conservatively. We will assume it's false except for: (1) types
// for which QEXTTypeIsPod is true. (2) std::pair of types with trivial copy
// constructors. (3) array of a type with a trivial copy constructor.
// (4) const versions thereof.
template <typename T_type> struct QEXTTypeHasTrivialCopy
    : QEXTTypeIsPod<T_type> { };
template <typename T_type, typename U> struct QEXTTypeHasTrivialCopy<std::pair<T_type, U> >
    : QEXTTypeIntegralConstant<bool, (QEXTTypeHasTrivialCopy<T_type>::value && QEXTTypeHasTrivialCopy<U>::value) > { };
template <typename T_A, int N> struct QEXTTypeHasTrivialCopy<T_A[N]>
    : QEXTTypeHasTrivialCopy<T_A> { };
template <typename T_type> struct QEXTTypeHasTrivialCopy<const T_type> : QEXTTypeHasTrivialCopy<T_type> { };


// We can't get QEXTTypeHasTrivialAssign right without compiler help, so fail
// conservatively. We will assume it's false except for: (1) types
// for which QEXTTypeIsPod is true. (2) std::pair of types with trivial copy
// constructors. (3) array of a type with a trivial assign constructor.
template <typename T_type> struct QEXTTypeHasTrivialAssign
    : QEXTTypeIsPod<T_type> { };
template <typename T_type, typename U> struct QEXTTypeHasTrivialAssign<std::pair<T_type, U> >
    : QEXTTypeIntegralConstant<bool, (QEXTTypeHasTrivialAssign<T_type>::value && QEXTTypeHasTrivialAssign<U>::value) > { };
template <typename T_A, int N> struct QEXTTypeHasTrivialAssign<T_A[N]>
    : QEXTTypeHasTrivialAssign<T_A> { };

// We can't get QEXTTypeHasTrivialDestructor right without compiler help, so
// fail conservatively. We will assume it's false except for: (1) types
// for which QEXTTypeIsPod is true. (2) std::pair of types with trivial
// destructors. (3) array of a type with a trivial destructor.
// (4) const versions thereof.
template <typename T_type> struct QEXTTypeHasTrivialDestructor
    : QEXTTypeIsPod<T_type> { };
template <typename T_type, typename U> struct QEXTTypeHasTrivialDestructor<std::pair<T_type, U> >
    : QEXTTypeIntegralConstant<bool, (QEXTTypeHasTrivialDestructor<T_type>::value && QEXTTypeHasTrivialDestructor<U>::value) > { };
template <typename T_A, int N> struct QEXTTypeHasTrivialDestructor<T_A[N]>
    : QEXTTypeHasTrivialDestructor<T_A> { };
template <typename T_type> struct QEXTTypeHasTrivialDestructor<const T_type>
    : QEXTTypeHasTrivialDestructor<T_type> { };


// Specified by TR1 [4.6] Relationships between types
#if !defined(_MSC_VER) && !(defined(__GNUC__) && __GNUC__ <= 3)
namespace internal
{

    // This class is an implementation detail for QEXTTypeIsConvertible, and you
    // don't need to know how it works to use QEXTTypeIsConvertible. For those
    // who care: we declare two different functions, one whose argument is
    // of type To and one with a variadic argument list. We give them
    // return types of different size, so we can use sizeof to trick the
    // compiler into telling us which function it would have chosen if we
    // had called it with an argument of type From.  See Alexandrescu's
    // _Modern C++ Design_ for more details on this sort of trick.
    template <typename From, typename To>
    struct ConvertHelper
    {
        static Small Test(To);
        static Big Test(...);
        static From Create();
    };

}

// Inherits from true_type if From is convertible to To, false_type otherwise.
template <typename From, typename To>
struct QEXTTypeIsConvertible :
        QEXTTypeIntegralConstant<bool,
        sizeof(internal::ConvertHelper<From, To>::Test(
        internal::ConvertHelper<From, To>::Create())) == sizeof(internal::Small)>
{
};

#endif


// Checks whether a type is unsigned (T_type must be convertible to unsigned int):
template <typename T_type> struct QEXTTypeIsUnsigned : QEXTTypeIntegralConstant<bool, (T_type(0)<T_type(-1))> {};

// Checks whether a type is signed (T_type must be convertible to int):
template <typename T_type> struct QEXTTypeIsSigned : QEXTTypeNot<QEXTTypeIsUnsigned<T_type> > {};

QEXT_STATIC_ASSERT(( QEXTTypeIsUnsigned<quint8>::value));
QEXT_STATIC_ASSERT((!QEXTTypeIsUnsigned<qint8>::value));

QEXT_STATIC_ASSERT((!QEXTTypeIsSigned<quint8>::value));
QEXT_STATIC_ASSERT(( QEXTTypeIsSigned<qint8>::value));

QEXT_STATIC_ASSERT(( QEXTTypeIsUnsigned<quint16>::value));
QEXT_STATIC_ASSERT((!QEXTTypeIsUnsigned<qint16>::value));

QEXT_STATIC_ASSERT((!QEXTTypeIsSigned<quint16>::value));
QEXT_STATIC_ASSERT(( QEXTTypeIsSigned<qint16>::value));

QEXT_STATIC_ASSERT(( QEXTTypeIsUnsigned<quint32>::value));
QEXT_STATIC_ASSERT((!QEXTTypeIsUnsigned<qint32>::value));

QEXT_STATIC_ASSERT((!QEXTTypeIsSigned<quint32>::value));
QEXT_STATIC_ASSERT(( QEXTTypeIsSigned<qint32>::value));

QEXT_STATIC_ASSERT(( QEXTTypeIsUnsigned<quint64>::value));
QEXT_STATIC_ASSERT((!QEXTTypeIsUnsigned<qint64>::value));

QEXT_STATIC_ASSERT((!QEXTTypeIsSigned<quint64>::value));
QEXT_STATIC_ASSERT(( QEXTTypeIsSigned<qint64>::value));


template<typename T_type = void> struct QEXTTypeIsDefaultConstructible;

template<>
struct QEXTTypeIsDefaultConstructible<void>
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
struct QEXTTypeIsDefaultConstructible<>::Test<true>
{
    typedef double Type;
};

template<typename T_type>
struct QEXTTypeIsDefaultConstructible : QEXTTypeIsDefaultConstructible<>
{
private:
    template<typename U> static typename Test < !!sizeof(::new U()) >::Type sfinae(U *);
    template<typename U> static char sfinae(...);
public:
    static bool const value = sizeof(sfinae<T_type>(0)) > 1;
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
        static char isBaseClass(typename QEXTTypeTrait<T_base>::Pointer);
    };

public:
    static const bool value =
        sizeof(InternalClass::isBaseClass(reinterpret_cast<typename QEXTTypeTrait<T_derived>::Pointer>(0))) ==
        sizeof(char);

#else //SELF_REFERENCE_IN_MEMBER_INITIALIZATION

    //The AIX xlC compiler does not like these 2 functions being in the inner class.
    //It says "The incomplete type "test" must not be used as a qualifier.
    //It does not seem necessary anyway.
    static Big  isBaseClass(...);
    static char isBaseClass(typename QEXTTypeTrait<T_base>::Pointer);

public:
    static const bool value =
        sizeof(isBaseClass(reinterpret_cast<typename QEXTTypeTrait<T_derived>::Pointer>(0))) ==
        sizeof(char);

#endif //SELF_REFERENCE_IN_MEMBER_INITIALIZATION
};

template <typename T_base>
struct QEXTIsBaseOf<T_base, T_base>
{
    static const bool value = true;
};

#endif





// Specified by TR1 [4.7.1]
template<typename T_type>
struct QEXTTypeRemoveConst
{
    typedef T_type Type;
};

template<typename T_type>
struct QEXTTypeRemoveConst<T_type const>
{
    typedef T_type Type;
};

template<typename T_type>
struct QEXTTypeRemoveVolatile
{
    typedef T_type Type;
};

template<typename T_type>
struct QEXTTypeRemoveVolatile<T_type volatile>
{
    typedef T_type Type;
};

template<typename T_type>
struct QEXTTypeRemoveConstVolatile
{
    typedef typename QEXTTypeRemoveConst<typename QEXTTypeRemoveVolatile<T_type>::Type>::Type Type;
};


// Specified by TR1 [4.7.2] Reference modifications.
template<typename T_type>
struct QEXTTypeRemoveReference
{
    typedef T_type Type;
};

template<typename T_type>
struct QEXTTypeRemoveReference<T_type &>
{
    typedef T_type Type;
};


template <typename T_type>
struct QEXTTypeAddReference
{
    typedef T_type &Type;
};

template <typename T_type>
struct QEXTTypeAddReference<T_type &>
{
    typedef T_type &Type;
};


// Specified by TR1 [4.7.4] Pointer modifications.
template<typename T_type>
struct QEXTTypeRemovePointer
{
    typedef T_type Type;
};

template<typename T_type>
struct QEXTTypeRemovePointer<T_type *>
{
    typedef T_type Type;
};

template<typename T_type>
struct QEXTTypeRemovePointer<T_type *const>
{
    typedef T_type Type;
};

template<typename T_type>
struct QEXTTypeRemovePointer<T_type *volatile>
{
    typedef T_type Type;
};

template<typename T_type>
struct QEXTTypeRemovePointer<T_type *const volatile>
{
    typedef T_type Type;
};


template<typename T_type>
struct QEXTTypeAddConst
{
    typedef T_type const Type;
};


template<typename T_type>
struct QEXTTypeAddVolatile
{
    typedef T_type volatile Type;
};


template<typename T_type>
struct QEXTTypeAddConstVolatile
{
    typedef typename QEXTTypeAddConst<typename QEXTTypeAddVolatile<T_type>::Type>::Type Type;
};


template<typename T_type>
struct QEXTTypeAddPointer
{
    typedef typename QEXTTypeRemoveReference<T_type>::Type *Type;
};




#endif // _QEXTTYPETRAIT_H
