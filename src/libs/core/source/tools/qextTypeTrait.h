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
    #include <type_traits>
#endif

#include <QPair>

template <typename T_type, typename U> struct QExtTypeIsSame;
template <typename T_type> struct QExtTypeIsIntegral;
template <typename T_type> struct QExtTypeIsFloating;
template <typename T_type> struct QExtTypeIsPointer;
template <typename T_type> struct QExtTypeIsFloatingPoint;
// MSVC can't compile this correctly, and neither can gcc 3.3.5 (at least)
#if !defined(_MSC_VER) && !(defined(__GNUC__) && __GNUC__ <= 3)
// is_enum uses is_convertible, which is not available on MSVC.
template <typename T_type> struct QExtTypeIsEnum;
#endif
template <typename T_type> struct QExtTypeIsPod;
template <typename T_type> struct QExtTypeIsReference;
template <typename T_type> struct QExtTypeHasTrivialConstructor;
template <typename T_type> struct QExtTypeHasTrivialCopy;
template <typename T_type> struct QExtTypeHasTrivialAssign;
template <typename T_type> struct QExtTypeHasTrivialDestructor;
template <typename T_type> struct QExtTypeRemoveConst;
template <typename T_type> struct QExtTypeRemoveVolatile;
template <typename T_type> struct QExtTypeRemoveConstVolatile;
template <typename T_type> struct QExtTypeRemoveReference;
template <typename T_type> struct QExtTypeAddReference;
template <typename T_type> struct QExtTypeRemovePointer;
#if !defined(_MSC_VER) && !(defined(__GNUC__) && __GNUC__ <= 3)
template <typename From, typename To> struct QExtTypeIsConvertible;
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
struct QExtTypeTrait
{
    typedef T_type          Type;
    typedef T_type         &Pass;
    typedef const T_type   &Take;
    typedef T_type         *Pointer;
};

template <typename T_type, int N>
struct QExtTypeTrait<T_type[N]>
{
    typedef T_type         *Type;
    typedef T_type        *&Pass;
    typedef const T_type  *&Take;
    typedef T_type        **Pointer;
};

template <typename T_type>
struct QExtTypeTrait<T_type &>
{
    typedef T_type          Type;
    typedef T_type         &Pass;
    typedef T_type         &Take;
    typedef T_type         *Pointer;
};

template <typename T_type>
struct QExtTypeTrait<const T_type &>
{
    typedef const T_type    Type;
    typedef const T_type   &Pass;
    typedef const T_type   &Take;
    typedef const T_type   *Pointer;
};

template<>
struct QExtTypeTrait<void>
{
    typedef void            Type;
    typedef void            Pass;
    typedef void            Take;
    typedef void           *Pointer;
};



// QExtTypeIntegralConstant, defined in tr1, is a wrapper for an integer
// value. We don't really need this generality; we could get away
// with hardcoding the integer type to bool. We use the fully
// general QExtIntegralConstant for compatibility with tr1.
template<typename T_type, T_type v>
struct QExtTypeIntegralConstant
{
    static const T_type value = v;
    typedef T_type Value;
    typedef QExtTypeIntegralConstant<T_type, v> Type;
};

template<typename T_type, T_type v> const T_type QExtTypeIntegralConstant<T_type, v>::value;

// Abbreviations: true_type and false_type are structs that represent boolean
// true and false values. Also define the boost::mpl versions of those names,
// true_ and false_.
typedef QExtTypeIntegralConstant<bool, true>  QExtTypeTrue;
typedef QExtTypeIntegralConstant<bool, false> QExtTypeFalse;



template <bool, typename T_type = void> struct QExtTypeEnableIf { };
template <typename T_type> struct QExtTypeEnableIf<true, T_type>
{
    typedef T_type Type;
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
struct QExtTypeAnd : public QExtTypeIntegralConstant<bool, (T_A::value && T_B::value)> { };

// QExtTypeOr is a template || operator.
// QExtTypeOr<T_A, T_B>::value evaluates "T_A::value || T_B::value".
template<typename T_A, typename T_B>
struct QExtTypeOr : public QExtTypeIntegralConstant<bool, (T_A::value || T_B::value)> { };

// a metafunction to invert an QExtTypeIntegralConstant:
template <typename T_type>
struct QExtTypeNot : QExtTypeIntegralConstant<bool, !T_type::value> {};


// QExtTypeEquals is a template type comparator, similar to Loki IsSameType.
// QExtTypeEquals<T_A, T_B>::value is true iff "T_A" is the same type as "T_B".
//
// New code should prefer base::is_same, defined in base/type_traits.h.
// It is functionally identical, but is_same is the standard spelling.
template<typename T_type, typename T_unknown> struct QExtTypeEquals : public QExtTypeFalse { };
template<typename T_type> struct QExtTypeEquals<T_type, T_type> : public QExtTypeTrue { };

// QExtTypeIsSame
template<typename T_type, typename T_unknown> struct QExtTypeIsSame : QExtTypeFalse {};
template<typename T_type>  struct QExtTypeIsSame<T_type, T_type> : QExtTypeTrue {};

// QExtTypeIsVoid
template<typename T_type> struct QExtTypeIsVoid : QExtTypeFalse { };
template<> struct QExtTypeIsVoid<void> : QExtTypeTrue { };


// QExtTypeIsIntegral
template<typename T_type> struct QExtTypeIsIntegral : QExtTypeFalse { };
template<> struct QExtTypeIsIntegral<bool> : QExtTypeTrue { };
template<> struct QExtTypeIsIntegral<char> : QExtTypeTrue { };
template<> struct QExtTypeIsIntegral<unsigned char> : QExtTypeTrue { };
template<> struct QExtTypeIsIntegral<signed char> : QExtTypeTrue { };
#if defined(_MSC_VER)
// wchar_t is not by default a distinct type from unsigned short in
// Microsoft C.
// See http://msdn2.microsoft.com/en-us/library/dh8che7s(VS.80).aspx
template<> struct QExtTypeIsIntegral<__wchar_t> : QExtTypeTrue { };
#else
template<> struct QExtTypeIsIntegral<wchar_t> : QExtTypeTrue { };
#endif
template<> struct QExtTypeIsIntegral<short> : QExtTypeTrue { };
template<> struct QExtTypeIsIntegral<unsigned short> : QExtTypeTrue { };
template<> struct QExtTypeIsIntegral<int> : QExtTypeTrue { };
template<> struct QExtTypeIsIntegral<unsigned int> : QExtTypeTrue { };
template<> struct QExtTypeIsIntegral<long> : QExtTypeTrue { };
template<> struct QExtTypeIsIntegral<unsigned long> : QExtTypeTrue { };
#if defined(Q_OS_WIN) && !defined(Q_CC_GNU)
template<> struct QExtTypeIsIntegral<__int64> : QExtTypeTrue { };
template<> struct QExtTypeIsIntegral<unsigned __int64> : QExtTypeTrue { };
#else
template<> struct QExtTypeIsIntegral<long long> : QExtTypeTrue { };
template<> struct QExtTypeIsIntegral<unsigned long long> : QExtTypeTrue { };
#endif

template<typename T_type> struct QExtTypeIsIntegral<const T_type> : QExtTypeIsIntegral<T_type> { };
template<typename T_type> struct QExtTypeIsIntegral<volatile T_type> : QExtTypeIsIntegral<T_type> { };
template<typename T_type> struct QExtTypeIsIntegral<const volatile T_type> : QExtTypeIsIntegral<T_type> { };
#if QEXT_CC_FEATURE_UNICODE_STRINGS
template<> struct QExtTypeIsIntegral<char16_t> : QExtTypeTrue { };
template<> struct QExtTypeIsIntegral<char32_t> : QExtTypeTrue { };
#endif

// QExtTypeIsFloating
template<typename T_type> struct QExtTypeIsFloating : QExtTypeFalse { };
template<> struct QExtTypeIsFloating<float> : QExtTypeTrue { };
template<> struct QExtTypeIsFloating<double> : QExtTypeTrue { };
template<> struct QExtTypeIsFloating<long double> : QExtTypeTrue { };

template<typename T_type> struct QExtTypeIsFloating<const T_type> : QExtTypeIsFloating<T_type> { };
template<typename T_type> struct QExtTypeIsFloating<volatile T_type> : QExtTypeIsFloating<T_type> { };
template<typename T_type> struct QExtTypeIsFloating<const volatile T_type> : QExtTypeIsFloating<T_type> { };


// QExtTypeIsFloatingPoint is false except for the built-in floating-point types.
// T_A cv-qualified type is integral if and only if the underlying type is.
template <typename T_type> struct QExtTypeIsFloatingPoint : QExtTypeFalse { };
template<> struct QExtTypeIsFloatingPoint<float> : QExtTypeTrue { };
template<> struct QExtTypeIsFloatingPoint<double> : QExtTypeTrue { };
template<> struct QExtTypeIsFloatingPoint<long double> : QExtTypeTrue { };
template <typename T_type> struct QExtTypeIsFloatingPoint<const T_type> : QExtTypeIsFloatingPoint<T_type> { };
template <typename T_type> struct QExtTypeIsFloatingPoint<volatile T_type> : QExtTypeIsFloatingPoint<T_type> { };
template <typename T_type> struct QExtTypeIsFloatingPoint<const volatile T_type> : QExtTypeIsFloatingPoint<T_type> { };


// QExtTypeIsPointer is false except for pointer types. T_A cv-qualified type (e.g.
// "int* const", as opposed to "int const*") is cv-qualified if and only if
// the underlying type is.
// QExtTypeIsPointer
template <typename T_type> struct QExtTypeIsPointer : QExtTypeFalse { };
template <typename T_type> struct QExtTypeIsPointer<T_type *> : QExtTypeTrue { };
template <typename T_type> struct QExtTypeIsPointer<const T_type> : QExtTypeIsPointer<T_type> { };
template <typename T_type> struct QExtTypeIsPointer<volatile T_type> : QExtTypeIsPointer<T_type> { };
template <typename T_type> struct QExtTypeIsPointer<const volatile T_type> : QExtTypeIsPointer<T_type> { };


// is_reference is false except for reference types.
template<typename T_type> struct QExtTypeIsReference : QExtTypeFalse {};
template<typename T_type> struct QExtTypeIsReference<T_type &> : QExtTypeTrue {};


// Specified by TR1 [4.5.3] Type Properties
template <typename T_type> struct QExtTypeIsConst : QExtTypeFalse {};
template <typename T_type> struct QExtTypeIsConst<const T_type> : QExtTypeTrue {};
template <typename T_type> struct QExtTypeIsVolatile : QExtTypeFalse {};
template <typename T_type> struct QExtTypeIsVolatile<volatile T_type> : QExtTypeTrue {};


#if !defined(_MSC_VER) && !(defined(__GNUC__) && __GNUC__ <= 3)

template <typename T_type> struct QExtTypeIsClassOrUnion
{
    template <typename U> static internal::Small tester(void (U::*)());
    template <typename U> static internal::Big tester(...);
    static const bool value = sizeof(tester<T_type>(0)) == sizeof(internal::Small);
};

// QExtTypeIsConvertible chokes if the first argument is an array. That's why
// we use QExtTypeAddReference here.
template <bool NotUnum, typename T_type>
struct QExtTypeIsEnumImpl : QExtTypeIsConvertible<typename QExtTypeAddReference<T_type>::Type, int>
{
};
template <typename T_type> struct QExtTypeIsEnumImpl<true, T_type> : QExtTypeFalse { };


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
template <typename T_type> struct QExtTypeIsEnum
    : QExtTypeIsEnumImpl<QExtTypeIsSame<T_type, void>::value ||
                        QExtTypeIsIntegral<T_type>::value ||
                        QExtTypeIsFloatingPoint<T_type>::value ||
                        QExtTypeIsReference<T_type>::value ||
                        QExtTypeIsClassOrUnion<T_type>::value,
      T_type>
{
};

template <typename T_type> struct QExtTypeIsEnum<const T_type> : QExtTypeIsEnum<T_type> { };
template <typename T_type> struct QExtTypeIsEnum<volatile T_type> : QExtTypeIsEnum<T_type> { };
template <typename T_type> struct QExtTypeIsEnum<const volatile T_type> : QExtTypeIsEnum<T_type> { };

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
    #define QEXT_IS_ENUM(x) QExtTypeIsEnum<x>::value
#endif


// We can't get QExtTypeIsPod right without compiler help, so fail conservatively.
// We will assume it's false except for arithmetic types, enumerations,
// pointers and cv-qualified versions thereof. Note that QPair<T_type,U>
// is not a POD even if T_type and U are PODs.
template <typename T_type> struct QExtTypeIsPod
    : QExtTypeIntegralConstant < bool, (QExtTypeIsIntegral<T_type>::value || QExtTypeIsFloatingPoint<T_type>::value ||
#if !defined(_MSC_VER) && !(defined(__GNUC__) && __GNUC__ <= 3)
    // QExtTypeIsEnum is not available on MSVC.
    QExtTypeIsEnum<T_type>::value ||
#endif
    QExtTypeIsPointer<T_type>::value) >
{
};
template <typename T_type> struct QExtTypeIsPod<const T_type> : QExtTypeIsPod<T_type> { };
template <typename T_type> struct QExtTypeIsPod<volatile T_type> : QExtTypeIsPod<T_type> { };
template <typename T_type> struct QExtTypeIsPod<const volatile T_type> : QExtTypeIsPod<T_type> { };



// We can't get QExtTypeHasTrivialConstructor right without compiler help, so
// fail conservatively. We will assume it's false except for: (1) types
// for which QExtTypeIsPod is true. (2) QPair of types with trivial
// constructors. (3) array of a type with a trivial constructor.
// (4) const versions thereof.
template <typename T_type> struct QExtTypeHasTrivialConstructor
    : QExtTypeIsPod<T_type> { };
template <typename T_type, typename U> struct QExtTypeHasTrivialConstructor<QPair<T_type, U> >
    : QExtTypeIntegralConstant<bool, (QExtTypeHasTrivialConstructor<T_type>::value && QExtTypeHasTrivialConstructor<U>::value) > { };
template <typename T_A, int N> struct QExtTypeHasTrivialConstructor<T_A[N]>
    : QExtTypeHasTrivialConstructor<T_A> { };
template <typename T_type> struct QExtTypeHasTrivialConstructor<const T_type>
    : QExtTypeHasTrivialConstructor<T_type> { };


// We can't get QExtTypeHasTrivialCopy right without compiler help, so fail
// conservatively. We will assume it's false except for: (1) types
// for which QExtTypeIsPod is true. (2) QPair of types with trivial copy
// constructors. (3) array of a type with a trivial copy constructor.
// (4) const versions thereof.
template <typename T_type> struct QExtTypeHasTrivialCopy
    : QExtTypeIsPod<T_type> { };
template <typename T_type, typename U> struct QExtTypeHasTrivialCopy<QPair<T_type, U> >
    : QExtTypeIntegralConstant<bool, (QExtTypeHasTrivialCopy<T_type>::value && QExtTypeHasTrivialCopy<U>::value) > { };
template <typename T_A, int N> struct QExtTypeHasTrivialCopy<T_A[N]>
    : QExtTypeHasTrivialCopy<T_A> { };
template <typename T_type> struct QExtTypeHasTrivialCopy<const T_type> : QExtTypeHasTrivialCopy<T_type> { };


// We can't get QExtTypeHasTrivialAssign right without compiler help, so fail
// conservatively. We will assume it's false except for: (1) types
// for which QExtTypeIsPod is true. (2) QPair of types with trivial copy
// constructors. (3) array of a type with a trivial assign constructor.
template <typename T_type> struct QExtTypeHasTrivialAssign
    : QExtTypeIsPod<T_type> { };
template <typename T_type, typename U> struct QExtTypeHasTrivialAssign<QPair<T_type, U> >
    : QExtTypeIntegralConstant<bool, (QExtTypeHasTrivialAssign<T_type>::value && QExtTypeHasTrivialAssign<U>::value) > { };
template <typename T_A, int N> struct QExtTypeHasTrivialAssign<T_A[N]>
    : QExtTypeHasTrivialAssign<T_A> { };

// We can't get QExtTypeHasTrivialDestructor right without compiler help, so
// fail conservatively. We will assume it's false except for: (1) types
// for which QExtTypeIsPod is true. (2) QPair of types with trivial
// destructors. (3) array of a type with a trivial destructor.
// (4) const versions thereof.
template <typename T_type> struct QExtTypeHasTrivialDestructor
    : QExtTypeIsPod<T_type> { };
template <typename T_type, typename U> struct QExtTypeHasTrivialDestructor<QPair<T_type, U> >
    : QExtTypeIntegralConstant<bool, (QExtTypeHasTrivialDestructor<T_type>::value && QExtTypeHasTrivialDestructor<U>::value) > { };
template <typename T_A, int N> struct QExtTypeHasTrivialDestructor<T_A[N]>
    : QExtTypeHasTrivialDestructor<T_A> { };
template <typename T_type> struct QExtTypeHasTrivialDestructor<const T_type>
    : QExtTypeHasTrivialDestructor<T_type> { };


// Specified by TR1 [4.6] Relationships between types
#if !defined(_MSC_VER) && !(defined(__GNUC__) && __GNUC__ <= 3)
namespace internal
{

    // This class is an implementation detail for QExtTypeIsConvertible, and you
    // don't need to know how it works to use QExtTypeIsConvertible. For those
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
struct QExtTypeIsConvertible :
        QExtTypeIntegralConstant<bool,
        sizeof(internal::ConvertHelper<From, To>::Test(
        internal::ConvertHelper<From, To>::Create())) == sizeof(internal::Small)>
{
};

#endif


// Checks whether a type is unsigned (T_type must be convertible to unsigned int):
template <typename T_type> struct QExtTypeIsUnsigned : QExtTypeIntegralConstant<bool, (T_type(0)<T_type(-1))> {};

// Checks whether a type is signed (T_type must be convertible to int):
template <typename T_type> struct QExtTypeIsSigned : QExtTypeNot<QExtTypeIsUnsigned<T_type> > {};

QEXT_STATIC_ASSERT(( QExtTypeIsUnsigned<quint8>::value));
QEXT_STATIC_ASSERT((!QExtTypeIsUnsigned<qint8>::value));

QEXT_STATIC_ASSERT((!QExtTypeIsSigned<quint8>::value));
QEXT_STATIC_ASSERT(( QExtTypeIsSigned<qint8>::value));

QEXT_STATIC_ASSERT(( QExtTypeIsUnsigned<quint16>::value));
QEXT_STATIC_ASSERT((!QExtTypeIsUnsigned<qint16>::value));

QEXT_STATIC_ASSERT((!QExtTypeIsSigned<quint16>::value));
QEXT_STATIC_ASSERT(( QExtTypeIsSigned<qint16>::value));

QEXT_STATIC_ASSERT(( QExtTypeIsUnsigned<quint32>::value));
QEXT_STATIC_ASSERT((!QExtTypeIsUnsigned<qint32>::value));

QEXT_STATIC_ASSERT((!QExtTypeIsSigned<quint32>::value));
QEXT_STATIC_ASSERT(( QExtTypeIsSigned<qint32>::value));

QEXT_STATIC_ASSERT(( QExtTypeIsUnsigned<quint64>::value));
QEXT_STATIC_ASSERT((!QExtTypeIsUnsigned<qint64>::value));

QEXT_STATIC_ASSERT((!QExtTypeIsSigned<quint64>::value));
QEXT_STATIC_ASSERT(( QExtTypeIsSigned<qint64>::value));


template<typename T_type = void> struct QExtTypeIsDefaultConstructible;

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

template<typename T_type>
struct QExtTypeIsDefaultConstructible : QExtTypeIsDefaultConstructible<>
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





// Specified by TR1 [4.7.1]
template<typename T_type>
struct QExtTypeRemoveConst
{
    typedef T_type Type;
};

template<typename T_type>
struct QExtTypeRemoveConst<T_type const>
{
    typedef T_type Type;
};

template<typename T_type>
struct QExtTypeRemoveVolatile
{
    typedef T_type Type;
};

template<typename T_type>
struct QExtTypeRemoveVolatile<T_type volatile>
{
    typedef T_type Type;
};

template<typename T_type>
struct QExtTypeRemoveConstVolatile
{
    typedef typename QExtTypeRemoveConst<typename QExtTypeRemoveVolatile<T_type>::Type>::Type Type;
};


// Specified by TR1 [4.7.2] Reference modifications.
template<typename T_type>
struct QExtTypeRemoveReference
{
    typedef T_type Type;
};

template<typename T_type>
struct QExtTypeRemoveReference<T_type &>
{
    typedef T_type Type;
};


template <typename T_type>
struct QExtTypeAddReference
{
    typedef T_type &Type;
};

template <typename T_type>
struct QExtTypeAddReference<T_type &>
{
    typedef T_type &Type;
};


// Specified by TR1 [4.7.4] Pointer modifications.
template<typename T_type>
struct QExtTypeRemovePointer
{
    typedef T_type Type;
};

template<typename T_type>
struct QExtTypeRemovePointer<T_type *>
{
    typedef T_type Type;
};

template<typename T_type>
struct QExtTypeRemovePointer<T_type *const>
{
    typedef T_type Type;
};

template<typename T_type>
struct QExtTypeRemovePointer<T_type *volatile>
{
    typedef T_type Type;
};

template<typename T_type>
struct QExtTypeRemovePointer<T_type *const volatile>
{
    typedef T_type Type;
};


template<typename T_type>
struct QExtTypeAddConst
{
    typedef T_type const Type;
};


template<typename T_type>
struct QExtTypeAddVolatile
{
    typedef T_type volatile Type;
};


template<typename T_type>
struct QExtTypeAddConstVolatile
{
    typedef typename QExtTypeAddConst<typename QExtTypeAddVolatile<T_type>::Type>::Type Type;
};


template<typename T_type>
struct QExtTypeAddPointer
{
    typedef typename QExtTypeRemoveReference<T_type>::Type *Type;
};




#endif // _QEXTTYPETRAIT_H
