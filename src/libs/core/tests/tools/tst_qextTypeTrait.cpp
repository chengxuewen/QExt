#include <qextTypeTrait.h>

#include <QtTest>
#include <QObject>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

class QEXTTypeTraitTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void testBaseAndDerived();
    void testIsInteger();
    void testIsFloating();
    void testIsPointer();
    void testIsEnum();
    void testIsReference();
    void testAddReference();
    void testIsPod();
    void testHasTrivialConstructor();
    void testHasTrivialCopy();
    void testHasTrivialAssign();
    void testHasTrivialDestructor();
    void testRemovePointer();
    void testRemoveConst();
    void testRemoveVolatile();
    void testRemoveCV();
    void testRemoveReference();
    void testIsSame();
    void testConvertible();
};


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


void QEXTTypeTraitTest::testBaseAndDerived()
{
    bool drived = true;
    drived = QEXTIsBaseOf<MClassBase, MClass>::value;
    QVERIFY(drived);
    drived = QEXTIsBaseOf<MClassBase, MClassBase>::value;
    QVERIFY(drived);

    QVERIFY(MClassTrait<MClassBase>().data());
    QVERIFY(MClassTrait<MClass>().data());
    QVERIFY(!MClassTrait<A>().data());
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

void QEXTTypeTraitTest::testIsInteger()
{
    // Verify that QEXTTypeIsIntegral is true for all integer types.
    QVERIFY(QEXTTypeIsIntegral<bool>::value);
    QVERIFY(QEXTTypeIsIntegral<char>::value);
    QVERIFY(QEXTTypeIsIntegral<unsigned char>::value);
    QVERIFY(QEXTTypeIsIntegral<signed char>::value);
    QVERIFY(QEXTTypeIsIntegral<wchar_t>::value);
    QVERIFY(QEXTTypeIsIntegral<int>::value);
    QVERIFY(QEXTTypeIsIntegral<unsigned int>::value);
    QVERIFY(QEXTTypeIsIntegral<short>::value);
    QVERIFY(QEXTTypeIsIntegral<unsigned short>::value);
    QVERIFY(QEXTTypeIsIntegral<long>::value);
    QVERIFY(QEXTTypeIsIntegral<unsigned long>::value);

    // Verify that QEXTTypeIsIntegral is false for a few non-integer types.
    QVERIFY(!QEXTTypeIsIntegral<void>::value);
    QVERIFY(!QEXTTypeIsIntegral<float>::value);
    QVERIFY(!QEXTTypeIsIntegral<std::string>::value);
    QVERIFY(!QEXTTypeIsIntegral<int *>::value);
    QVERIFY(!QEXTTypeIsIntegral<A>::value);
    QVERIFY(!(QEXTTypeIsIntegral<std::pair<int, int> >::value));

    // Verify that cv-qualified integral types are still integral, and
    // cv-qualified non-integral types are still non-integral.
    QVERIFY(QEXTTypeIsIntegral<const char>::value);
    QVERIFY(QEXTTypeIsIntegral<volatile bool>::value);
    QVERIFY(QEXTTypeIsIntegral<const volatile unsigned int>::value);
    QVERIFY(!QEXTTypeIsIntegral<const float>::value);
    QVERIFY(!QEXTTypeIsIntegral<int *volatile>::value);
    QVERIFY(!QEXTTypeIsIntegral<const volatile std::string>::value);
}

void QEXTTypeTraitTest::testIsFloating()
{
    // Verify that QEXTTypeIsFloatingPoint is true for all floating-point types.
    QVERIFY(QEXTTypeIsFloatingPoint<float>::value);
    QVERIFY(QEXTTypeIsFloatingPoint<double>::value);
    QVERIFY(QEXTTypeIsFloatingPoint<long double>::value);

    // Verify that QEXTTypeIsFloatingPoint is false for a few non-float types.
    QVERIFY(!QEXTTypeIsFloatingPoint<void>::value);
    QVERIFY(!QEXTTypeIsFloatingPoint<long>::value);
    QVERIFY(!QEXTTypeIsFloatingPoint<std::string>::value);
    QVERIFY(!QEXTTypeIsFloatingPoint<float *>::value);
    QVERIFY(!QEXTTypeIsFloatingPoint<A>::value);
    QVERIFY(!(QEXTTypeIsFloatingPoint<std::pair<int, int> >::value));

    // Verify that cv-qualified floating point types are still floating, and
    // cv-qualified non-floating types are still non-floating.
    QVERIFY(QEXTTypeIsFloatingPoint<const float>::value);
    QVERIFY(QEXTTypeIsFloatingPoint<volatile double>::value);
    QVERIFY(QEXTTypeIsFloatingPoint<const volatile long double>::value);
    QVERIFY(!QEXTTypeIsFloatingPoint<const int>::value);
    QVERIFY(!QEXTTypeIsFloatingPoint<volatile std::string>::value);
    QVERIFY(!QEXTTypeIsFloatingPoint<const volatile char>::value);
}

void QEXTTypeTraitTest::testIsPointer()
{
    // Verify that QEXTTypeIsPointer is true for some pointer types.
    QVERIFY(QEXTTypeIsPointer<int *>::value);
    QVERIFY(QEXTTypeIsPointer<void *>::value);
    QVERIFY(QEXTTypeIsPointer<std::string *>::value);
    QVERIFY(QEXTTypeIsPointer<const void *>::value);
    QVERIFY(QEXTTypeIsPointer<volatile float *const *>::value);

    // Verify that QEXTTypeIsPointer is false for some non-pointer types.
    QVERIFY(!QEXTTypeIsPointer<void>::value);
    QVERIFY(!QEXTTypeIsPointer<float &>::value);
    QVERIFY(!QEXTTypeIsPointer<long>::value);
    QVERIFY(!QEXTTypeIsPointer<std::vector<int *> >::value);
    QVERIFY(!QEXTTypeIsPointer<int[5]>::value);

    // A function pointer is a pointer, but a function type, or a function
    // reference type, is not.
    QVERIFY(QEXTTypeIsPointer<int (*)(int x)>::value);
    QVERIFY(!QEXTTypeIsPointer<void(char x)>::value);
    QVERIFY(!QEXTTypeIsPointer<double (&)(std::string x)>::value);

    // Verify that QEXTTypeIsPointer<T> is true for some cv-qualified pointer types,
    // and false for some cv-qualified non-pointer types.
    QVERIFY(QEXTTypeIsPointer<int *const>::value);
    QVERIFY(QEXTTypeIsPointer<const void *volatile>::value);
    QVERIFY(QEXTTypeIsPointer<char **const volatile>::value);
    QVERIFY(!QEXTTypeIsPointer<const int>::value);
    QVERIFY(!QEXTTypeIsPointer<volatile std::vector<int *> >::value);
    QVERIFY(!QEXTTypeIsPointer<const volatile double>::value);
}

void QEXTTypeTraitTest::testIsEnum()
{
    // QEXTTypeIsEnum isn't supported on MSVC or gcc 3.x
#if !defined(_MSC_VER) && !(defined(__GNUC__) && __GNUC__ <= 3)
    // Verify that QEXTTypeIsEnum is true for enum types.
    QVERIFY(QEXTTypeIsEnum<G>::value);
    QVERIFY(QEXTTypeIsEnum<const G>::value);
    QVERIFY(QEXTTypeIsEnum<volatile G>::value);
    QVERIFY(QEXTTypeIsEnum<const volatile G>::value);

    // Verify that QEXTTypeIsEnum is false for a few non-enum types.
    QVERIFY(!QEXTTypeIsEnum<void>::value);
    QVERIFY(!QEXTTypeIsEnum<G &>::value);
    QVERIFY(!QEXTTypeIsEnum<G[1]>::value);
    QVERIFY(!QEXTTypeIsEnum<const G[1]>::value);
    QVERIFY(!QEXTTypeIsEnum<G[]>::value);
    QVERIFY(!QEXTTypeIsEnum<int>::value);
    QVERIFY(!QEXTTypeIsEnum<float>::value);
    QVERIFY(!QEXTTypeIsEnum<A>::value);
    QVERIFY(!QEXTTypeIsEnum<A *>::value);
    QVERIFY(!QEXTTypeIsEnum<const A>::value);
    QVERIFY(!QEXTTypeIsEnum<H>::value);
    QVERIFY(!QEXTTypeIsEnum<I>::value);
    QVERIFY(!QEXTTypeIsEnum<J>::value);
    QVERIFY(!QEXTTypeIsEnum<void()>::value);
    QVERIFY(!QEXTTypeIsEnum<void(*)()>::value);
    QVERIFY(!QEXTTypeIsEnum<int A::*>::value);
    QVERIFY(!QEXTTypeIsEnum<void (A::*)()>::value);
#endif
}

void QEXTTypeTraitTest::testIsReference()
{
    // Verifies that QEXTTypeIsReference is true for all reference types.
    typedef float &RefFloat;
    QVERIFY(QEXTTypeIsReference<float &>::value);
    QVERIFY(QEXTTypeIsReference<const int &>::value);
    QVERIFY(QEXTTypeIsReference<const int *&>::value);
    QVERIFY(QEXTTypeIsReference<int (&)(bool)>::value);
    QVERIFY(QEXTTypeIsReference<RefFloat>::value);
    QVERIFY(QEXTTypeIsReference<const RefFloat>::value);
    QVERIFY(QEXTTypeIsReference<volatile RefFloat>::value);
    QVERIFY(QEXTTypeIsReference<const volatile RefFloat>::value);


    // Verifies that QEXTTypeIsReference is false for all non-reference types.
    QVERIFY(!QEXTTypeIsReference<float>::value);
    QVERIFY(!QEXTTypeIsReference<const float>::value);
    QVERIFY(!QEXTTypeIsReference<volatile float>::value);
    QVERIFY(!QEXTTypeIsReference<const volatile float>::value);
    QVERIFY(!QEXTTypeIsReference<const int *>::value);
    QVERIFY(!QEXTTypeIsReference<int()>::value);
    QVERIFY(!QEXTTypeIsReference<void(*)(const char &)>::value);
}

void QEXTTypeTraitTest::testAddReference()
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

void QEXTTypeTraitTest::testIsPod()
{
    // Verify that arithmetic types and pointers are marked as PODs.
    QVERIFY(QEXTTypeIsPod<bool>::value);
    QVERIFY(QEXTTypeIsPod<char>::value);
    QVERIFY(QEXTTypeIsPod<unsigned char>::value);
    QVERIFY(QEXTTypeIsPod<signed char>::value);
    QVERIFY(QEXTTypeIsPod<wchar_t>::value);
    QVERIFY(QEXTTypeIsPod<int>::value);
    QVERIFY(QEXTTypeIsPod<unsigned int>::value);
    QVERIFY(QEXTTypeIsPod<short>::value);
    QVERIFY(QEXTTypeIsPod<unsigned short>::value);
    QVERIFY(QEXTTypeIsPod<long>::value);
    QVERIFY(QEXTTypeIsPod<unsigned long>::value);
    QVERIFY(QEXTTypeIsPod<float>::value);
    QVERIFY(QEXTTypeIsPod<double>::value);
    QVERIFY(QEXTTypeIsPod<long double>::value);
    QVERIFY(QEXTTypeIsPod<std::string *>::value);
    QVERIFY(QEXTTypeIsPod<A *>::value);
    QVERIFY(QEXTTypeIsPod<const B *>::value);
    QVERIFY(QEXTTypeIsPod<C **>::value);
    QVERIFY(QEXTTypeIsPod<const int>::value);
    QVERIFY(QEXTTypeIsPod<char *volatile>::value);
    QVERIFY(QEXTTypeIsPod<const volatile double>::value);
#if !defined(_MSC_VER) && !(defined(__GNUC__) && __GNUC__ <= 3)
    QVERIFY(QEXTTypeIsPod<G>::value);
    QVERIFY(QEXTTypeIsPod<const G>::value);
    QVERIFY(QEXTTypeIsPod<volatile G>::value);
    QVERIFY(QEXTTypeIsPod<const volatile G>::value);
#endif

    // Verify that some non-POD types are not marked as PODs.
    QVERIFY(!QEXTTypeIsPod<void>::value);
    QVERIFY(!QEXTTypeIsPod<std::string>::value);
    QVERIFY(!(QEXTTypeIsPod<std::pair<int, int> >::value));
    QVERIFY(!QEXTTypeIsPod<A>::value);
    QVERIFY(!QEXTTypeIsPod<B>::value);
    QVERIFY(!QEXTTypeIsPod<C>::value);
    QVERIFY(!QEXTTypeIsPod<const std::string>::value);
    QVERIFY(!QEXTTypeIsPod<volatile A>::value);
    QVERIFY(!QEXTTypeIsPod<const volatile B>::value);
}

void QEXTTypeTraitTest::testHasTrivialConstructor()
{
    // Verify that arithmetic types and pointers have trivial constructors.
    QVERIFY(QEXTTypeHasTrivialConstructor<bool>::value);
    QVERIFY(QEXTTypeHasTrivialConstructor<char>::value);
    QVERIFY(QEXTTypeHasTrivialConstructor<unsigned char>::value);
    QVERIFY(QEXTTypeHasTrivialConstructor<signed char>::value);
    QVERIFY(QEXTTypeHasTrivialConstructor<wchar_t>::value);
    QVERIFY(QEXTTypeHasTrivialConstructor<int>::value);
    QVERIFY(QEXTTypeHasTrivialConstructor<unsigned int>::value);
    QVERIFY(QEXTTypeHasTrivialConstructor<short>::value);
    QVERIFY(QEXTTypeHasTrivialConstructor<unsigned short>::value);
    QVERIFY(QEXTTypeHasTrivialConstructor<long>::value);
    QVERIFY(QEXTTypeHasTrivialConstructor<unsigned long>::value);
    QVERIFY(QEXTTypeHasTrivialConstructor<float>::value);
    QVERIFY(QEXTTypeHasTrivialConstructor<double>::value);
    QVERIFY(QEXTTypeHasTrivialConstructor<long double>::value);
    QVERIFY(QEXTTypeHasTrivialConstructor<std::string *>::value);
    QVERIFY(QEXTTypeHasTrivialConstructor<A *>::value);
    QVERIFY(QEXTTypeHasTrivialConstructor<const B *>::value);
    QVERIFY(QEXTTypeHasTrivialConstructor<C **>::value);

    // Verify that pairs and arrays of such types have trivial
    // constructors.
    typedef int int10[10];
    QVERIFY((QEXTTypeHasTrivialConstructor<std::pair<int, char *> >::value));
    QVERIFY(QEXTTypeHasTrivialConstructor<int10>::value);

    // Verify that pairs of types without trivial constructors
    // are not marked as trivial.
    QVERIFY(!(QEXTTypeHasTrivialConstructor<std::pair<int, std::string> >::value));
    QVERIFY(!(QEXTTypeHasTrivialConstructor<std::pair<std::string, int> >::value));

    // Verify that types without trivial constructors are
    // correctly marked as such.
    QVERIFY(!QEXTTypeHasTrivialConstructor<std::string>::value);
    QVERIFY(!QEXTTypeHasTrivialConstructor<std::vector<int> >::value);

    // Verify that E, which we have declared to have a trivial
    // constructor, is correctly marked as such.
    QVERIFY(QEXTTypeHasTrivialConstructor<E>::value);
}

void QEXTTypeTraitTest::testHasTrivialCopy()
{
    // Verify that arithmetic types and pointers have trivial copy
    // constructors.
    QVERIFY(QEXTTypeHasTrivialCopy<bool>::value);
    QVERIFY(QEXTTypeHasTrivialCopy<char>::value);
    QVERIFY(QEXTTypeHasTrivialCopy<unsigned char>::value);
    QVERIFY(QEXTTypeHasTrivialCopy<signed char>::value);
    QVERIFY(QEXTTypeHasTrivialCopy<wchar_t>::value);
    QVERIFY(QEXTTypeHasTrivialCopy<int>::value);
    QVERIFY(QEXTTypeHasTrivialCopy<unsigned int>::value);
    QVERIFY(QEXTTypeHasTrivialCopy<short>::value);
    QVERIFY(QEXTTypeHasTrivialCopy<unsigned short>::value);
    QVERIFY(QEXTTypeHasTrivialCopy<long>::value);
    QVERIFY(QEXTTypeHasTrivialCopy<unsigned long>::value);
    QVERIFY(QEXTTypeHasTrivialCopy<float>::value);
    QVERIFY(QEXTTypeHasTrivialCopy<double>::value);
    QVERIFY(QEXTTypeHasTrivialCopy<long double>::value);
    QVERIFY(QEXTTypeHasTrivialCopy<std::string *>::value);
    QVERIFY(QEXTTypeHasTrivialCopy<A *>::value);
    QVERIFY(QEXTTypeHasTrivialCopy<const B *>::value);
    QVERIFY(QEXTTypeHasTrivialCopy<C **>::value);

    // Verify that pairs and arrays of such types have trivial
    // copy constructors.
    typedef int int10[10];
    QVERIFY((QEXTTypeHasTrivialCopy<std::pair<int, char *> >::value));
    QVERIFY(QEXTTypeHasTrivialCopy<int10>::value);

    // Verify that pairs of types without trivial copy constructors
    // are not marked as trivial.
    QVERIFY(!(QEXTTypeHasTrivialCopy<std::pair<int, std::string> >::value));
    QVERIFY(!(QEXTTypeHasTrivialCopy<std::pair<std::string, int> >::value));

    // Verify that types without trivial copy constructors are
    // correctly marked as such.
    QVERIFY(!QEXTTypeHasTrivialCopy<std::string>::value);
    QVERIFY(!QEXTTypeHasTrivialCopy<std::vector<int> >::value);

    // Verify that C, which we have declared to have a trivial
    // copy constructor, is correctly marked as such.
    QVERIFY(QEXTTypeHasTrivialCopy<C>::value);
}

void QEXTTypeTraitTest::testHasTrivialAssign()
{
    // Verify that arithmetic types and pointers have trivial assignment
    // operators.
    QVERIFY(QEXTTypeHasTrivialAssign<bool>::value);
    QVERIFY(QEXTTypeHasTrivialAssign<char>::value);
    QVERIFY(QEXTTypeHasTrivialAssign<unsigned char>::value);
    QVERIFY(QEXTTypeHasTrivialAssign<signed char>::value);
    QVERIFY(QEXTTypeHasTrivialAssign<wchar_t>::value);
    QVERIFY(QEXTTypeHasTrivialAssign<int>::value);
    QVERIFY(QEXTTypeHasTrivialAssign<unsigned int>::value);
    QVERIFY(QEXTTypeHasTrivialAssign<short>::value);
    QVERIFY(QEXTTypeHasTrivialAssign<unsigned short>::value);
    QVERIFY(QEXTTypeHasTrivialAssign<long>::value);
    QVERIFY(QEXTTypeHasTrivialAssign<unsigned long>::value);
    QVERIFY(QEXTTypeHasTrivialAssign<float>::value);
    QVERIFY(QEXTTypeHasTrivialAssign<double>::value);
    QVERIFY(QEXTTypeHasTrivialAssign<long double>::value);
    QVERIFY(QEXTTypeHasTrivialAssign<std::string *>::value);
    QVERIFY(QEXTTypeHasTrivialAssign<A *>::value);
    QVERIFY(QEXTTypeHasTrivialAssign<const B *>::value);
    QVERIFY(QEXTTypeHasTrivialAssign<C **>::value);

    // Verify that pairs and arrays of such types have trivial
    // assignment operators.
    typedef int int10[10];
    QVERIFY((QEXTTypeHasTrivialAssign<std::pair<int, char *> >::value));
    QVERIFY(QEXTTypeHasTrivialAssign<int10>::value);

    // Verify that pairs of types without trivial assignment operators
    // are not marked as trivial.
    QVERIFY(!(QEXTTypeHasTrivialAssign<std::pair<int, std::string> >::value));
    QVERIFY(!(QEXTTypeHasTrivialAssign<std::pair<std::string, int> >::value));

    // Verify that types without trivial assignment operators are
    // correctly marked as such.
    QVERIFY(!QEXTTypeHasTrivialAssign<std::string>::value);
    QVERIFY(!QEXTTypeHasTrivialAssign<std::vector<int> >::value);

    // Verify that D, which we have declared to have a trivial
    // assignment operator, is correctly marked as such.
    QVERIFY(QEXTTypeHasTrivialAssign<D>::value);
}

void QEXTTypeTraitTest::testHasTrivialDestructor()
{
    // Verify that arithmetic types and pointers have trivial destructors.
    QVERIFY(QEXTTypeHasTrivialDestructor<bool>::value);
    QVERIFY(QEXTTypeHasTrivialDestructor<char>::value);
    QVERIFY(QEXTTypeHasTrivialDestructor<unsigned char>::value);
    QVERIFY(QEXTTypeHasTrivialDestructor<signed char>::value);
    QVERIFY(QEXTTypeHasTrivialDestructor<wchar_t>::value);
    QVERIFY(QEXTTypeHasTrivialDestructor<int>::value);
    QVERIFY(QEXTTypeHasTrivialDestructor<unsigned int>::value);
    QVERIFY(QEXTTypeHasTrivialDestructor<short>::value);
    QVERIFY(QEXTTypeHasTrivialDestructor<unsigned short>::value);
    QVERIFY(QEXTTypeHasTrivialDestructor<long>::value);
    QVERIFY(QEXTTypeHasTrivialDestructor<unsigned long>::value);
    QVERIFY(QEXTTypeHasTrivialDestructor<float>::value);
    QVERIFY(QEXTTypeHasTrivialDestructor<double>::value);
    QVERIFY(QEXTTypeHasTrivialDestructor<long double>::value);
    QVERIFY(QEXTTypeHasTrivialDestructor<std::string *>::value);
    QVERIFY(QEXTTypeHasTrivialDestructor<A *>::value);
    QVERIFY(QEXTTypeHasTrivialDestructor<const B *>::value);
    QVERIFY(QEXTTypeHasTrivialDestructor<C **>::value);

    // Verify that pairs and arrays of such types have trivial
    // destructors.
    typedef int int10[10];
    QVERIFY((QEXTTypeHasTrivialDestructor<std::pair<int, char *> >::value));
    QVERIFY(QEXTTypeHasTrivialDestructor<int10>::value);

    // Verify that pairs of types without trivial destructors
    // are not marked as trivial.
    QVERIFY(!(QEXTTypeHasTrivialDestructor<std::pair<int, std::string> >::value));
    QVERIFY(!(QEXTTypeHasTrivialDestructor<std::pair<std::string, int> >::value));

    // Verify that types without trivial destructors are
    // correctly marked as such.
    QVERIFY(!QEXTTypeHasTrivialDestructor<std::string>::value);
    QVERIFY(!QEXTTypeHasTrivialDestructor<std::vector<int> >::value);

    // Verify that F, which we have declared to have a trivial
    // destructor, is correctly marked as such.
    QVERIFY(QEXTTypeHasTrivialDestructor<F>::value);
}

void QEXTTypeTraitTest::testRemovePointer()
{
    COMPILE_ASSERT_TYPES_EQ(int, QEXTTypeRemovePointer<int>::Type);
    COMPILE_ASSERT_TYPES_EQ(int, QEXTTypeRemovePointer<int *>::Type);
    COMPILE_ASSERT_TYPES_EQ(const int, QEXTTypeRemovePointer<const int *>::Type);
    COMPILE_ASSERT_TYPES_EQ(int, QEXTTypeRemovePointer<int *const>::Type);
    COMPILE_ASSERT_TYPES_EQ(int, QEXTTypeRemovePointer<int *volatile>::Type);
}

void QEXTTypeTraitTest::testRemoveConst()
{
    COMPILE_ASSERT_TYPES_EQ(int, QEXTTypeRemoveConst<int>::Type);
    COMPILE_ASSERT_TYPES_EQ(int, QEXTTypeRemoveConst<const int>::Type);
    COMPILE_ASSERT_TYPES_EQ(int *, QEXTTypeRemoveConst<int *const>::Type);
    // TR1 examples.
    COMPILE_ASSERT_TYPES_EQ(const int *, QEXTTypeRemoveConst<const int *>::Type);
    COMPILE_ASSERT_TYPES_EQ(volatile int, QEXTTypeRemoveConst<const volatile int>::Type);
}

void QEXTTypeTraitTest::testRemoveVolatile()
{
    COMPILE_ASSERT_TYPES_EQ(int, QEXTTypeRemoveVolatile<int>::Type);
    COMPILE_ASSERT_TYPES_EQ(int, QEXTTypeRemoveVolatile<volatile int>::Type);
    COMPILE_ASSERT_TYPES_EQ(int *, QEXTTypeRemoveVolatile<int *volatile>::Type);
    // TR1 examples.
    COMPILE_ASSERT_TYPES_EQ(volatile int *, QEXTTypeRemoveVolatile<volatile int *>::Type);
    COMPILE_ASSERT_TYPES_EQ(const int, QEXTTypeRemoveVolatile<const volatile int>::Type);
}

void QEXTTypeTraitTest::testRemoveCV()
{
    COMPILE_ASSERT_TYPES_EQ(int, QEXTTypeRemoveConstVolatile<int>::Type);
    COMPILE_ASSERT_TYPES_EQ(int, QEXTTypeRemoveConstVolatile<volatile int>::Type);
    COMPILE_ASSERT_TYPES_EQ(int, QEXTTypeRemoveConstVolatile<const int>::Type);
    COMPILE_ASSERT_TYPES_EQ(int *, QEXTTypeRemoveConstVolatile<int *const volatile>::Type);
    // TR1 examples.
    COMPILE_ASSERT_TYPES_EQ(const volatile int *, QEXTTypeRemoveConstVolatile<const volatile int *>::Type);
    COMPILE_ASSERT_TYPES_EQ(int, QEXTTypeRemoveConstVolatile<const volatile int>::Type);
}

void QEXTTypeTraitTest::testRemoveReference()
{
    COMPILE_ASSERT_TYPES_EQ(int, QEXTTypeRemoveReference<int>::Type);
    COMPILE_ASSERT_TYPES_EQ(int, QEXTTypeRemoveReference<int &>::Type);
    COMPILE_ASSERT_TYPES_EQ(const int, QEXTTypeRemoveReference<const int &>::Type);
    COMPILE_ASSERT_TYPES_EQ(int *, QEXTTypeRemoveReference<int *&>::Type);
}

void QEXTTypeTraitTest::testIsSame()
{
    QVERIFY((QEXTTypeIsSame<int32, int32>::value));
    QVERIFY(!(QEXTTypeIsSame<int32, int64>::value));
    QVERIFY(!(QEXTTypeIsSame<int64, int32>::value));
    QVERIFY(!(QEXTTypeIsSame<int, const int>::value));

    QVERIFY((QEXTTypeIsSame<void, void>::value));
    QVERIFY(!(QEXTTypeIsSame<void, int>::value));
    QVERIFY(!(QEXTTypeIsSame<int, void>::value));

    QVERIFY((QEXTTypeIsSame<int *, int *>::value));
    QVERIFY((QEXTTypeIsSame<void *, void *>::value));
    QVERIFY(!(QEXTTypeIsSame<int *, void *>::value));
    QVERIFY(!(QEXTTypeIsSame<void *, int *>::value));
    QVERIFY(!(QEXTTypeIsSame<void *, const void *>::value));
    QVERIFY(!(QEXTTypeIsSame<void *, void *const>::value));

    QVERIFY((QEXTTypeIsSame<Base *, Base *>::value));
    QVERIFY((QEXTTypeIsSame<Derived *, Derived *>::value));
    QVERIFY(!(QEXTTypeIsSame<Base *, Derived *>::value));
    QVERIFY(!(QEXTTypeIsSame<Derived *, Base *>::value));
}

void QEXTTypeTraitTest::testConvertible()
{
#if !defined(_MSC_VER) && !(defined(__GNUC__) && __GNUC__ <= 3)
    QVERIFY((QEXTTypeIsConvertible<int, int>::value));
    QVERIFY((QEXTTypeIsConvertible<int, long>::value));
    QVERIFY((QEXTTypeIsConvertible<long, int>::value));

    QVERIFY((QEXTTypeIsConvertible<int *, void *>::value));
    QVERIFY(!(QEXTTypeIsConvertible<void *, int *>::value));

    QVERIFY((QEXTTypeIsConvertible<Derived *, Base *>::value));
    QVERIFY(!(QEXTTypeIsConvertible<Base *, Derived *>::value));
    QVERIFY((QEXTTypeIsConvertible<Derived *, const Base *>::value));
    QVERIFY(!(QEXTTypeIsConvertible<const Derived *, Base *>::value));
#endif
}

QTEST_APPLESS_MAIN(QEXTTypeTraitTest)

#include <tst_qextTypeTrait.moc>

