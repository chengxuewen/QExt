#ifndef QEXTTYPETRAITTEST_H
#define QEXTTYPETRAITTEST_H

#include <qextTypeTrait.h>

#include <iostream>
#include <string>
#include <vector>
#include <utility>

#include <CppUTest/TestHarness.h>




// Another user-defined non-POD type with a trivial copy constructor.
// We will explicitly declare C to have a trivial copy constructor
// by specializing QEXTTypeHasTrivialCopy.
class C
{
public:
    explicit C(int n) : n_(n) { }
private:
    int n_;
};
template<> struct QEXTTypeHasTrivialCopy<C> : QEXTTypeTrue { };


// Another user-defined non-POD type with a trivial assignment operator.
// We will explicitly declare C to have a trivial assignment operator
// by specializing has_trivial_assign.
class D
{
public:
    explicit D(int n) : n_(n) { }
private:
    int n_;
};
template<> struct QEXTTypeHasTrivialAssign<D> : QEXTTypeTrue { };


// Another user-defined non-POD type with a trivial constructor.
// We will explicitly declare E to have a trivial constructor
// by specializing has_trivial_constructor.
class E
{
public:
    int n_;
};
template<> struct QEXTTypeHasTrivialConstructor<E> : QEXTTypeTrue { };


// Another user-defined non-POD type with a trivial destructor.
// We will explicitly declare E to have a trivial destructor
// by specializing has_trivial_destructor.
class F
{
public:
    explicit F(int n) : n_(n) { }
private:
    int n_;
};
template<> struct QEXTTypeHasTrivialDestructor<F> : QEXTTypeTrue { };







QEXT_USE_NAMESPACE

namespace qextTypeTraitTest
{

    typedef int int32;
    typedef long int64;


    // This assertion produces errors like "error: invalid use of
    // incomplete type 'struct <unnamed>::AssertTypesEq<const int, int>'"
    // when it fails.
    template<typename T, typename U> struct AssertTypesEq;
    template<typename T> struct AssertTypesEq<T, T> {};
#define COMPILE_ASSERT_TYPES_EQ(T, U) static_cast<void>(AssertTypesEq<T, U>())

    // A user-defined POD type.
    struct A
    {
        int n_;
    };

    // A user-defined non-POD type with a trivial copy constructor.
    class B
    {
    public:
        explicit B(int n) : n_(n) { }
    private:
        int n_;
    };

    enum G {};

    union H {};

    class I
    {
    public:
        operator int() const;
    };

    class J
    {
    private:
        operator int() const;
    };


    class MClassBase
    {
    public:
        MClassBase() {}
    };

    class MClass : public MClassBase
    {
    public:
        MClass() {}
    };

    template <typename T_obj, bool I_derives_base = QEXTIsBaseOf<MClassBase, T_obj>::value>
    struct MClassTrait
    {
        bool data()
        {
            return true;
        }
    };

    template <typename T_obj>
    struct MClassTrait<T_obj, false>
    {
        bool data()
        {
            return false;
        }
    };


    TEST_GROUP(qextTypeTraitTest)
    {
    };

    TEST(qextTypeTraitTest, testBaseAndDerived)
    {
        bool drived = true;
        drived = QEXTIsBaseOf<MClassBase, MClass>::value;
        CHECK(drived);
        drived = QEXTIsBaseOf<MClassBase, MClassBase>::value;
        CHECK(drived);

        CHECK(MClassTrait<MClassBase>().data());
        CHECK(MClassTrait<MClass>().data());
        CHECK(!MClassTrait<A>().data());
    }



    // A base class and a derived class that inherits from it, used for
    // testing conversion type traits.
    class Base
    {
    public:
        virtual ~Base() { }
    };

    class Derived : public Base
    {
    };

    TEST(qextTypeTraitTest, testIsInteger)
    {
        // Verify that QEXTTypeIsIntegral is true for all integer types.
        CHECK(QEXTTypeIsIntegral<bool>::value);
        CHECK(QEXTTypeIsIntegral<char>::value);
        CHECK(QEXTTypeIsIntegral<unsigned char>::value);
        CHECK(QEXTTypeIsIntegral<signed char>::value);
        CHECK(QEXTTypeIsIntegral<wchar_t>::value);
        CHECK(QEXTTypeIsIntegral<int>::value);
        CHECK(QEXTTypeIsIntegral<unsigned int>::value);
        CHECK(QEXTTypeIsIntegral<short>::value);
        CHECK(QEXTTypeIsIntegral<unsigned short>::value);
        CHECK(QEXTTypeIsIntegral<long>::value);
        CHECK(QEXTTypeIsIntegral<unsigned long>::value);

        // Verify that QEXTTypeIsIntegral is false for a few non-integer types.
        CHECK_FALSE(QEXTTypeIsIntegral<void>::value);
        CHECK_FALSE(QEXTTypeIsIntegral<float>::value);
        CHECK_FALSE(QEXTTypeIsIntegral<std::string>::value);
        CHECK_FALSE(QEXTTypeIsIntegral<int *>::value);
        CHECK_FALSE(QEXTTypeIsIntegral<A>::value);
        CHECK_FALSE((QEXTTypeIsIntegral<std::pair<int, int> >::value));

        // Verify that cv-qualified integral types are still integral, and
        // cv-qualified non-integral types are still non-integral.
        CHECK(QEXTTypeIsIntegral<const char>::value);
        CHECK(QEXTTypeIsIntegral<volatile bool>::value);
        CHECK(QEXTTypeIsIntegral<const volatile unsigned int>::value);
        CHECK_FALSE(QEXTTypeIsIntegral<const float>::value);
        CHECK_FALSE(QEXTTypeIsIntegral<int *volatile>::value);
        CHECK_FALSE(QEXTTypeIsIntegral<const volatile std::string>::value);
    }

    TEST(qextTypeTraitTest, testIsFloating)
    {
        // Verify that QEXTTypeIsFloatingPoint is true for all floating-point types.
        CHECK(QEXTTypeIsFloatingPoint<float>::value);
        CHECK(QEXTTypeIsFloatingPoint<double>::value);
        CHECK(QEXTTypeIsFloatingPoint<long double>::value);

        // Verify that QEXTTypeIsFloatingPoint is false for a few non-float types.
        CHECK_FALSE(QEXTTypeIsFloatingPoint<void>::value);
        CHECK_FALSE(QEXTTypeIsFloatingPoint<long>::value);
        CHECK_FALSE(QEXTTypeIsFloatingPoint<std::string>::value);
        CHECK_FALSE(QEXTTypeIsFloatingPoint<float *>::value);
        CHECK_FALSE(QEXTTypeIsFloatingPoint<A>::value);
        CHECK_FALSE((QEXTTypeIsFloatingPoint<std::pair<int, int> >::value));

        // Verify that cv-qualified floating point types are still floating, and
        // cv-qualified non-floating types are still non-floating.
        CHECK(QEXTTypeIsFloatingPoint<const float>::value);
        CHECK(QEXTTypeIsFloatingPoint<volatile double>::value);
        CHECK(QEXTTypeIsFloatingPoint<const volatile long double>::value);
        CHECK_FALSE(QEXTTypeIsFloatingPoint<const int>::value);
        CHECK_FALSE(QEXTTypeIsFloatingPoint<volatile std::string>::value);
        CHECK_FALSE(QEXTTypeIsFloatingPoint<const volatile char>::value);
    }

    TEST(qextTypeTraitTest, testIsPointer)
    {
        // Verify that QEXTTypeIsPointer is true for some pointer types.
        CHECK(QEXTTypeIsPointer<int *>::value);
        CHECK(QEXTTypeIsPointer<void *>::value);
        CHECK(QEXTTypeIsPointer<std::string *>::value);
        CHECK(QEXTTypeIsPointer<const void *>::value);
        CHECK(QEXTTypeIsPointer<volatile float *const *>::value);

        // Verify that QEXTTypeIsPointer is false for some non-pointer types.
        CHECK_FALSE(QEXTTypeIsPointer<void>::value);
        CHECK_FALSE(QEXTTypeIsPointer<float &>::value);
        CHECK_FALSE(QEXTTypeIsPointer<long>::value);
        CHECK_FALSE(QEXTTypeIsPointer<std::vector<int *> >::value);
        CHECK_FALSE(QEXTTypeIsPointer<int[5]>::value);

        // A function pointer is a pointer, but a function type, or a function
        // reference type, is not.
        CHECK(QEXTTypeIsPointer<int (*)(int x)>::value);
        CHECK_FALSE(QEXTTypeIsPointer<void(char x)>::value);
        CHECK_FALSE(QEXTTypeIsPointer<double (&)(std::string x)>::value);

        // Verify that QEXTTypeIsPointer<T> is true for some cv-qualified pointer types,
        // and false for some cv-qualified non-pointer types.
        CHECK(QEXTTypeIsPointer<int *const>::value);
        CHECK(QEXTTypeIsPointer<const void *volatile>::value);
        CHECK(QEXTTypeIsPointer<char **const volatile>::value);
        CHECK_FALSE(QEXTTypeIsPointer<const int>::value);
        CHECK_FALSE(QEXTTypeIsPointer<volatile std::vector<int *> >::value);
        CHECK_FALSE(QEXTTypeIsPointer<const volatile double>::value);
    }

    TEST(qextTypeTraitTest, testIsEnum)
    {
        // QEXTTypeIsEnum isn't supported on MSVC or gcc 3.x
#if !defined(_MSC_VER) && !(defined(__GNUC__) && __GNUC__ <= 3)
        // Verify that QEXTTypeIsEnum is true for enum types.
        CHECK(QEXTTypeIsEnum<G>::value);
        CHECK(QEXTTypeIsEnum<const G>::value);
        CHECK(QEXTTypeIsEnum<volatile G>::value);
        CHECK(QEXTTypeIsEnum<const volatile G>::value);

        // Verify that QEXTTypeIsEnum is false for a few non-enum types.
        CHECK_FALSE(QEXTTypeIsEnum<void>::value);
        CHECK_FALSE(QEXTTypeIsEnum<G &>::value);
        CHECK_FALSE(QEXTTypeIsEnum<G[1]>::value);
        CHECK_FALSE(QEXTTypeIsEnum<const G[1]>::value);
        CHECK_FALSE(QEXTTypeIsEnum<G[]>::value);
        CHECK_FALSE(QEXTTypeIsEnum<int>::value);
        CHECK_FALSE(QEXTTypeIsEnum<float>::value);
        CHECK_FALSE(QEXTTypeIsEnum<A>::value);
        CHECK_FALSE(QEXTTypeIsEnum<A *>::value);
        CHECK_FALSE(QEXTTypeIsEnum<const A>::value);
        CHECK_FALSE(QEXTTypeIsEnum<H>::value);
        CHECK_FALSE(QEXTTypeIsEnum<I>::value);
        CHECK_FALSE(QEXTTypeIsEnum<J>::value);
        CHECK_FALSE(QEXTTypeIsEnum<void()>::value);
        CHECK_FALSE(QEXTTypeIsEnum<void(*)()>::value);
        CHECK_FALSE(QEXTTypeIsEnum<int A::*>::value);
        CHECK_FALSE(QEXTTypeIsEnum<void (A::*)()>::value);
#endif
    }

    TEST(qextTypeTraitTest, testIsReference)
    {
        // Verifies that QEXTTypeIsReference is true for all reference types.
        typedef float &RefFloat;
        CHECK(QEXTTypeIsReference<float &>::value);
        CHECK(QEXTTypeIsReference<const int &>::value);
        CHECK(QEXTTypeIsReference<const int *&>::value);
        CHECK(QEXTTypeIsReference<int (&)(bool)>::value);
        CHECK(QEXTTypeIsReference<RefFloat>::value);
        CHECK(QEXTTypeIsReference<const RefFloat>::value);
        CHECK(QEXTTypeIsReference<volatile RefFloat>::value);
        CHECK(QEXTTypeIsReference<const volatile RefFloat>::value);


        // Verifies that QEXTTypeIsReference is false for all non-reference types.
        CHECK_FALSE(QEXTTypeIsReference<float>::value);
        CHECK_FALSE(QEXTTypeIsReference<const float>::value);
        CHECK_FALSE(QEXTTypeIsReference<volatile float>::value);
        CHECK_FALSE(QEXTTypeIsReference<const volatile float>::value);
        CHECK_FALSE(QEXTTypeIsReference<const int *>::value);
        CHECK_FALSE(QEXTTypeIsReference<int()>::value);
        CHECK_FALSE(QEXTTypeIsReference<void(*)(const char &)>::value);
    }

    TEST(qextTypeTraitTest, testAddReference)
    {
        COMPILE_ASSERT_TYPES_EQ(int &, QEXTTypeAddReference<int>::Type);
        COMPILE_ASSERT_TYPES_EQ(const int &, QEXTTypeAddReference<const int>::Type);
        COMPILE_ASSERT_TYPES_EQ(volatile int &, QEXTTypeAddReference<volatile int>::Type);
        COMPILE_ASSERT_TYPES_EQ(const volatile int &, QEXTTypeAddReference<const volatile int>::Type);
        COMPILE_ASSERT_TYPES_EQ(int &, QEXTTypeAddReference<int &>::Type);
        COMPILE_ASSERT_TYPES_EQ(const int &, QEXTTypeAddReference<const int &>::Type);
        COMPILE_ASSERT_TYPES_EQ(volatile int &, QEXTTypeAddReference<volatile int &>::Type);
        COMPILE_ASSERT_TYPES_EQ(const volatile int &, QEXTTypeAddReference<const volatile int &>::Type);
    }

    TEST(qextTypeTraitTest, testIsPod)
    {
        // Verify that arithmetic types and pointers are marked as PODs.
        CHECK(QEXTTypeIsPod<bool>::value);
        CHECK(QEXTTypeIsPod<char>::value);
        CHECK(QEXTTypeIsPod<unsigned char>::value);
        CHECK(QEXTTypeIsPod<signed char>::value);
        CHECK(QEXTTypeIsPod<wchar_t>::value);
        CHECK(QEXTTypeIsPod<int>::value);
        CHECK(QEXTTypeIsPod<unsigned int>::value);
        CHECK(QEXTTypeIsPod<short>::value);
        CHECK(QEXTTypeIsPod<unsigned short>::value);
        CHECK(QEXTTypeIsPod<long>::value);
        CHECK(QEXTTypeIsPod<unsigned long>::value);
        CHECK(QEXTTypeIsPod<float>::value);
        CHECK(QEXTTypeIsPod<double>::value);
        CHECK(QEXTTypeIsPod<long double>::value);
        CHECK(QEXTTypeIsPod<std::string *>::value);
        CHECK(QEXTTypeIsPod<A *>::value);
        CHECK(QEXTTypeIsPod<const B *>::value);
        CHECK(QEXTTypeIsPod<C **>::value);
        CHECK(QEXTTypeIsPod<const int>::value);
        CHECK(QEXTTypeIsPod<char *volatile>::value);
        CHECK(QEXTTypeIsPod<const volatile double>::value);
#if !defined(_MSC_VER) && !(defined(__GNUC__) && __GNUC__ <= 3)
        CHECK(QEXTTypeIsPod<G>::value);
        CHECK(QEXTTypeIsPod<const G>::value);
        CHECK(QEXTTypeIsPod<volatile G>::value);
        CHECK(QEXTTypeIsPod<const volatile G>::value);
#endif

        // Verify that some non-POD types are not marked as PODs.
        CHECK_FALSE(QEXTTypeIsPod<void>::value);
        CHECK_FALSE(QEXTTypeIsPod<std::string>::value);
        CHECK_FALSE((QEXTTypeIsPod<std::pair<int, int> >::value));
        CHECK_FALSE(QEXTTypeIsPod<A>::value);
        CHECK_FALSE(QEXTTypeIsPod<B>::value);
        CHECK_FALSE(QEXTTypeIsPod<C>::value);
        CHECK_FALSE(QEXTTypeIsPod<const std::string>::value);
        CHECK_FALSE(QEXTTypeIsPod<volatile A>::value);
        CHECK_FALSE(QEXTTypeIsPod<const volatile B>::value);
    }

    TEST(qextTypeTraitTest, testHasTrivialConstructor)
    {
        // Verify that arithmetic types and pointers have trivial constructors.
        CHECK(QEXTTypeHasTrivialConstructor<bool>::value);
        CHECK(QEXTTypeHasTrivialConstructor<char>::value);
        CHECK(QEXTTypeHasTrivialConstructor<unsigned char>::value);
        CHECK(QEXTTypeHasTrivialConstructor<signed char>::value);
        CHECK(QEXTTypeHasTrivialConstructor<wchar_t>::value);
        CHECK(QEXTTypeHasTrivialConstructor<int>::value);
        CHECK(QEXTTypeHasTrivialConstructor<unsigned int>::value);
        CHECK(QEXTTypeHasTrivialConstructor<short>::value);
        CHECK(QEXTTypeHasTrivialConstructor<unsigned short>::value);
        CHECK(QEXTTypeHasTrivialConstructor<long>::value);
        CHECK(QEXTTypeHasTrivialConstructor<unsigned long>::value);
        CHECK(QEXTTypeHasTrivialConstructor<float>::value);
        CHECK(QEXTTypeHasTrivialConstructor<double>::value);
        CHECK(QEXTTypeHasTrivialConstructor<long double>::value);
        CHECK(QEXTTypeHasTrivialConstructor<std::string *>::value);
        CHECK(QEXTTypeHasTrivialConstructor<A *>::value);
        CHECK(QEXTTypeHasTrivialConstructor<const B *>::value);
        CHECK(QEXTTypeHasTrivialConstructor<C **>::value);

        // Verify that pairs and arrays of such types have trivial
        // constructors.
        typedef int int10[10];
        CHECK((QEXTTypeHasTrivialConstructor<std::pair<int, char *> >::value));
        CHECK(QEXTTypeHasTrivialConstructor<int10>::value);

        // Verify that pairs of types without trivial constructors
        // are not marked as trivial.
        CHECK_FALSE((QEXTTypeHasTrivialConstructor<std::pair<int, std::string> >::value));
        CHECK_FALSE((QEXTTypeHasTrivialConstructor<std::pair<std::string, int> >::value));

        // Verify that types without trivial constructors are
        // correctly marked as such.
        CHECK_FALSE(QEXTTypeHasTrivialConstructor<std::string>::value);
        CHECK_FALSE(QEXTTypeHasTrivialConstructor<std::vector<int> >::value);

        // Verify that E, which we have declared to have a trivial
        // constructor, is correctly marked as such.
        CHECK(QEXTTypeHasTrivialConstructor<E>::value);
    }

    TEST(qextTypeTraitTest, testHasTrivialCopy)
    {
        // Verify that arithmetic types and pointers have trivial copy
        // constructors.
        CHECK(QEXTTypeHasTrivialCopy<bool>::value);
        CHECK(QEXTTypeHasTrivialCopy<char>::value);
        CHECK(QEXTTypeHasTrivialCopy<unsigned char>::value);
        CHECK(QEXTTypeHasTrivialCopy<signed char>::value);
        CHECK(QEXTTypeHasTrivialCopy<wchar_t>::value);
        CHECK(QEXTTypeHasTrivialCopy<int>::value);
        CHECK(QEXTTypeHasTrivialCopy<unsigned int>::value);
        CHECK(QEXTTypeHasTrivialCopy<short>::value);
        CHECK(QEXTTypeHasTrivialCopy<unsigned short>::value);
        CHECK(QEXTTypeHasTrivialCopy<long>::value);
        CHECK(QEXTTypeHasTrivialCopy<unsigned long>::value);
        CHECK(QEXTTypeHasTrivialCopy<float>::value);
        CHECK(QEXTTypeHasTrivialCopy<double>::value);
        CHECK(QEXTTypeHasTrivialCopy<long double>::value);
        CHECK(QEXTTypeHasTrivialCopy<std::string *>::value);
        CHECK(QEXTTypeHasTrivialCopy<A *>::value);
        CHECK(QEXTTypeHasTrivialCopy<const B *>::value);
        CHECK(QEXTTypeHasTrivialCopy<C **>::value);

        // Verify that pairs and arrays of such types have trivial
        // copy constructors.
        typedef int int10[10];
        CHECK((QEXTTypeHasTrivialCopy<std::pair<int, char *> >::value));
        CHECK(QEXTTypeHasTrivialCopy<int10>::value);

        // Verify that pairs of types without trivial copy constructors
        // are not marked as trivial.
        CHECK_FALSE((QEXTTypeHasTrivialCopy<std::pair<int, std::string> >::value));
        CHECK_FALSE((QEXTTypeHasTrivialCopy<std::pair<std::string, int> >::value));

        // Verify that types without trivial copy constructors are
        // correctly marked as such.
        CHECK_FALSE(QEXTTypeHasTrivialCopy<std::string>::value);
        CHECK_FALSE(QEXTTypeHasTrivialCopy<std::vector<int> >::value);

        // Verify that C, which we have declared to have a trivial
        // copy constructor, is correctly marked as such.
        CHECK(QEXTTypeHasTrivialCopy<C>::value);
    }

    TEST(qextTypeTraitTest, testHasTrivialAssign)
    {
        // Verify that arithmetic types and pointers have trivial assignment
        // operators.
        CHECK(QEXTTypeHasTrivialAssign<bool>::value);
        CHECK(QEXTTypeHasTrivialAssign<char>::value);
        CHECK(QEXTTypeHasTrivialAssign<unsigned char>::value);
        CHECK(QEXTTypeHasTrivialAssign<signed char>::value);
        CHECK(QEXTTypeHasTrivialAssign<wchar_t>::value);
        CHECK(QEXTTypeHasTrivialAssign<int>::value);
        CHECK(QEXTTypeHasTrivialAssign<unsigned int>::value);
        CHECK(QEXTTypeHasTrivialAssign<short>::value);
        CHECK(QEXTTypeHasTrivialAssign<unsigned short>::value);
        CHECK(QEXTTypeHasTrivialAssign<long>::value);
        CHECK(QEXTTypeHasTrivialAssign<unsigned long>::value);
        CHECK(QEXTTypeHasTrivialAssign<float>::value);
        CHECK(QEXTTypeHasTrivialAssign<double>::value);
        CHECK(QEXTTypeHasTrivialAssign<long double>::value);
        CHECK(QEXTTypeHasTrivialAssign<std::string *>::value);
        CHECK(QEXTTypeHasTrivialAssign<A *>::value);
        CHECK(QEXTTypeHasTrivialAssign<const B *>::value);
        CHECK(QEXTTypeHasTrivialAssign<C **>::value);

        // Verify that pairs and arrays of such types have trivial
        // assignment operators.
        typedef int int10[10];
        CHECK((QEXTTypeHasTrivialAssign<std::pair<int, char *> >::value));
        CHECK(QEXTTypeHasTrivialAssign<int10>::value);

        // Verify that pairs of types without trivial assignment operators
        // are not marked as trivial.
        CHECK_FALSE((QEXTTypeHasTrivialAssign<std::pair<int, std::string> >::value));
        CHECK_FALSE((QEXTTypeHasTrivialAssign<std::pair<std::string, int> >::value));

        // Verify that types without trivial assignment operators are
        // correctly marked as such.
        CHECK_FALSE(QEXTTypeHasTrivialAssign<std::string>::value);
        CHECK_FALSE(QEXTTypeHasTrivialAssign<std::vector<int> >::value);

        // Verify that D, which we have declared to have a trivial
        // assignment operator, is correctly marked as such.
        CHECK(QEXTTypeHasTrivialAssign<D>::value);
    }

    TEST(qextTypeTraitTest, testHasTrivialDestructor)
    {
        // Verify that arithmetic types and pointers have trivial destructors.
        CHECK(QEXTTypeHasTrivialDestructor<bool>::value);
        CHECK(QEXTTypeHasTrivialDestructor<char>::value);
        CHECK(QEXTTypeHasTrivialDestructor<unsigned char>::value);
        CHECK(QEXTTypeHasTrivialDestructor<signed char>::value);
        CHECK(QEXTTypeHasTrivialDestructor<wchar_t>::value);
        CHECK(QEXTTypeHasTrivialDestructor<int>::value);
        CHECK(QEXTTypeHasTrivialDestructor<unsigned int>::value);
        CHECK(QEXTTypeHasTrivialDestructor<short>::value);
        CHECK(QEXTTypeHasTrivialDestructor<unsigned short>::value);
        CHECK(QEXTTypeHasTrivialDestructor<long>::value);
        CHECK(QEXTTypeHasTrivialDestructor<unsigned long>::value);
        CHECK(QEXTTypeHasTrivialDestructor<float>::value);
        CHECK(QEXTTypeHasTrivialDestructor<double>::value);
        CHECK(QEXTTypeHasTrivialDestructor<long double>::value);
        CHECK(QEXTTypeHasTrivialDestructor<std::string *>::value);
        CHECK(QEXTTypeHasTrivialDestructor<A *>::value);
        CHECK(QEXTTypeHasTrivialDestructor<const B *>::value);
        CHECK(QEXTTypeHasTrivialDestructor<C **>::value);

        // Verify that pairs and arrays of such types have trivial
        // destructors.
        typedef int int10[10];
        CHECK((QEXTTypeHasTrivialDestructor<std::pair<int, char *> >::value));
        CHECK(QEXTTypeHasTrivialDestructor<int10>::value);

        // Verify that pairs of types without trivial destructors
        // are not marked as trivial.
        CHECK_FALSE((QEXTTypeHasTrivialDestructor<std::pair<int, std::string> >::value));
        CHECK_FALSE((QEXTTypeHasTrivialDestructor<std::pair<std::string, int> >::value));

        // Verify that types without trivial destructors are
        // correctly marked as such.
        CHECK_FALSE(QEXTTypeHasTrivialDestructor<std::string>::value);
        CHECK_FALSE(QEXTTypeHasTrivialDestructor<std::vector<int> >::value);

        // Verify that F, which we have declared to have a trivial
        // destructor, is correctly marked as such.
        CHECK(QEXTTypeHasTrivialDestructor<F>::value);
    }

    // Tests QEXTTypeRemovePointer.
    TEST(qextTypeTraitTest, testRemovePointer)
    {
        COMPILE_ASSERT_TYPES_EQ(int, QEXTTypeRemovePointer<int>::Type);
        COMPILE_ASSERT_TYPES_EQ(int, QEXTTypeRemovePointer<int *>::Type);
        COMPILE_ASSERT_TYPES_EQ(const int, QEXTTypeRemovePointer<const int *>::Type);
        COMPILE_ASSERT_TYPES_EQ(int, QEXTTypeRemovePointer<int *const>::Type);
        COMPILE_ASSERT_TYPES_EQ(int, QEXTTypeRemovePointer<int *volatile>::Type);
    }

    TEST(qextTypeTraitTest, testRemoveConst)
    {
        COMPILE_ASSERT_TYPES_EQ(int, QEXTTypeRemoveConst<int>::Type);
        COMPILE_ASSERT_TYPES_EQ(int, QEXTTypeRemoveConst<const int>::Type);
        COMPILE_ASSERT_TYPES_EQ(int *, QEXTTypeRemoveConst<int *const>::Type);
        // TR1 examples.
        COMPILE_ASSERT_TYPES_EQ(const int *, QEXTTypeRemoveConst<const int *>::Type);
        COMPILE_ASSERT_TYPES_EQ(volatile int, QEXTTypeRemoveConst<const volatile int>::Type);
    }

    TEST(qextTypeTraitTest, testRemoveVolatile)
    {
        COMPILE_ASSERT_TYPES_EQ(int, QEXTTypeRemoveVolatile<int>::Type);
        COMPILE_ASSERT_TYPES_EQ(int, QEXTTypeRemoveVolatile<volatile int>::Type);
        COMPILE_ASSERT_TYPES_EQ(int *, QEXTTypeRemoveVolatile<int *volatile>::Type);
        // TR1 examples.
        COMPILE_ASSERT_TYPES_EQ(volatile int *, QEXTTypeRemoveVolatile<volatile int *>::Type);
        COMPILE_ASSERT_TYPES_EQ(const int, QEXTTypeRemoveVolatile<const volatile int>::Type);
    }

    TEST(qextTypeTraitTest, testRemoveCV)
    {
        COMPILE_ASSERT_TYPES_EQ(int, QEXTTypeRemoveConstVolatile<int>::Type);
        COMPILE_ASSERT_TYPES_EQ(int, QEXTTypeRemoveConstVolatile<volatile int>::Type);
        COMPILE_ASSERT_TYPES_EQ(int, QEXTTypeRemoveConstVolatile<const int>::Type);
        COMPILE_ASSERT_TYPES_EQ(int *, QEXTTypeRemoveConstVolatile<int *const volatile>::Type);
        // TR1 examples.
        COMPILE_ASSERT_TYPES_EQ(const volatile int *, QEXTTypeRemoveConstVolatile<const volatile int *>::Type);
        COMPILE_ASSERT_TYPES_EQ(int, QEXTTypeRemoveConstVolatile<const volatile int>::Type);
    }

    TEST(qextTypeTraitTest, testRemoveReference)
    {
        COMPILE_ASSERT_TYPES_EQ(int, QEXTTypeRemoveReference<int>::Type);
        COMPILE_ASSERT_TYPES_EQ(int, QEXTTypeRemoveReference<int &>::Type);
        COMPILE_ASSERT_TYPES_EQ(const int, QEXTTypeRemoveReference<const int &>::Type);
        COMPILE_ASSERT_TYPES_EQ(int *, QEXTTypeRemoveReference<int *&>::Type);
    }

    TEST(qextTypeTraitTest, testIsSame)
    {
        CHECK((QEXTTypeIsSame<int32, int32>::value));
        CHECK_FALSE((QEXTTypeIsSame<int32, int64>::value));
        CHECK_FALSE((QEXTTypeIsSame<int64, int32>::value));
        CHECK_FALSE((QEXTTypeIsSame<int, const int>::value));

        CHECK((QEXTTypeIsSame<void, void>::value));
        CHECK_FALSE((QEXTTypeIsSame<void, int>::value));
        CHECK_FALSE((QEXTTypeIsSame<int, void>::value));

        CHECK((QEXTTypeIsSame<int *, int *>::value));
        CHECK((QEXTTypeIsSame<void *, void *>::value));
        CHECK_FALSE((QEXTTypeIsSame<int *, void *>::value));
        CHECK_FALSE((QEXTTypeIsSame<void *, int *>::value));
        CHECK_FALSE((QEXTTypeIsSame<void *, const void *>::value));
        CHECK_FALSE((QEXTTypeIsSame<void *, void *const>::value));

        CHECK((QEXTTypeIsSame<Base *, Base *>::value));
        CHECK((QEXTTypeIsSame<Derived *, Derived *>::value));
        CHECK_FALSE((QEXTTypeIsSame<Base *, Derived *>::value));
        CHECK_FALSE((QEXTTypeIsSame<Derived *, Base *>::value));
    }

    TEST(qextTypeTraitTest, testConvertible)
    {
#if !defined(_MSC_VER) && !(defined(__GNUC__) && __GNUC__ <= 3)
        CHECK((QEXTTypeIsConvertible<int, int>::value));
        CHECK((QEXTTypeIsConvertible<int, long>::value));
        CHECK((QEXTTypeIsConvertible<long, int>::value));

        CHECK((QEXTTypeIsConvertible<int *, void *>::value));
        CHECK_FALSE((QEXTTypeIsConvertible<void *, int *>::value));

        CHECK((QEXTTypeIsConvertible<Derived *, Base *>::value));
        CHECK_FALSE((QEXTTypeIsConvertible<Base *, Derived *>::value));
        CHECK((QEXTTypeIsConvertible<Derived *, const Base *>::value));
        CHECK_FALSE((QEXTTypeIsConvertible<const Derived *, Base *>::value));
#endif
    }


} // namespace qextTypeTraitTest

#endif // QEXTTYPETRAITTEST_H
