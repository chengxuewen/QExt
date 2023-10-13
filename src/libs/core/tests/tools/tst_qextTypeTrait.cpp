#include <qextTypeTrait.h>

#include <QtTest>
#include <QObject>
#include <iostream>
#include <string>
#include <QVector>
#include <utility>

class QExtTypeTraitTest : public QObject
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
// by specializing QExtTypeHasTrivialCopy.
class C
{
public:
    explicit C(int n) : n_(n) { }
private:
    int n_;
};
template<> struct QExtTypeHasTrivialCopy<C> : QExtTypeTrue { };


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
template<> struct QExtTypeHasTrivialAssign<D> : QExtTypeTrue { };


// Another user-defined non-POD type with a trivial constructor.
// We will explicitly declare E to have a trivial constructor
// by specializing has_trivial_constructor.
class E
{
public:
    int n_;
};
template<> struct QExtTypeHasTrivialConstructor<E> : QExtTypeTrue { };


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
template<> struct QExtTypeHasTrivialDestructor<F> : QExtTypeTrue { };


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


void QExtTypeTraitTest::testBaseAndDerived()
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

void QExtTypeTraitTest::testIsInteger()
{
    // Verify that QExtTypeIsIntegral is true for all integer types.
    QVERIFY(QExtTypeIsIntegral<bool>::value);
    QVERIFY(QExtTypeIsIntegral<char>::value);
    QVERIFY(QExtTypeIsIntegral<unsigned char>::value);
    QVERIFY(QExtTypeIsIntegral<signed char>::value);
    QVERIFY(QExtTypeIsIntegral<wchar_t>::value);
    QVERIFY(QExtTypeIsIntegral<int>::value);
    QVERIFY(QExtTypeIsIntegral<unsigned int>::value);
    QVERIFY(QExtTypeIsIntegral<short>::value);
    QVERIFY(QExtTypeIsIntegral<unsigned short>::value);
    QVERIFY(QExtTypeIsIntegral<long>::value);
    QVERIFY(QExtTypeIsIntegral<unsigned long>::value);

    // Verify that QExtTypeIsIntegral is false for a few non-integer types.
    QVERIFY(!QExtTypeIsIntegral<void>::value);
    QVERIFY(!QExtTypeIsIntegral<float>::value);
    QVERIFY(!QExtTypeIsIntegral<QString>::value);
    QVERIFY(!QExtTypeIsIntegral<int *>::value);
    QVERIFY(!QExtTypeIsIntegral<A>::value);
    QVERIFY(!(QExtTypeIsIntegral<QPair<int, int> >::value));

    // Verify that cv-qualified integral types are still integral, and
    // cv-qualified non-integral types are still non-integral.
    QVERIFY(QExtTypeIsIntegral<const char>::value);
    QVERIFY(QExtTypeIsIntegral<volatile bool>::value);
    QVERIFY(QExtTypeIsIntegral<const volatile unsigned int>::value);
    QVERIFY(!QExtTypeIsIntegral<const float>::value);
    QVERIFY(!QExtTypeIsIntegral<int *volatile>::value);
    QVERIFY(!QExtTypeIsIntegral<const volatile QString>::value);
}

void QExtTypeTraitTest::testIsFloating()
{
    // Verify that QExtTypeIsFloatingPoint is true for all floating-point types.
    QVERIFY(QExtTypeIsFloatingPoint<float>::value);
    QVERIFY(QExtTypeIsFloatingPoint<double>::value);
    QVERIFY(QExtTypeIsFloatingPoint<long double>::value);

    // Verify that QExtTypeIsFloatingPoint is false for a few non-float types.
    QVERIFY(!QExtTypeIsFloatingPoint<void>::value);
    QVERIFY(!QExtTypeIsFloatingPoint<long>::value);
    QVERIFY(!QExtTypeIsFloatingPoint<QString>::value);
    QVERIFY(!QExtTypeIsFloatingPoint<float *>::value);
    QVERIFY(!QExtTypeIsFloatingPoint<A>::value);
    QVERIFY(!(QExtTypeIsFloatingPoint<QPair<int, int> >::value));

    // Verify that cv-qualified floating point types are still floating, and
    // cv-qualified non-floating types are still non-floating.
    QVERIFY(QExtTypeIsFloatingPoint<const float>::value);
    QVERIFY(QExtTypeIsFloatingPoint<volatile double>::value);
    QVERIFY(QExtTypeIsFloatingPoint<const volatile long double>::value);
    QVERIFY(!QExtTypeIsFloatingPoint<const int>::value);
    QVERIFY(!QExtTypeIsFloatingPoint<volatile QString>::value);
    QVERIFY(!QExtTypeIsFloatingPoint<const volatile char>::value);
}

void QExtTypeTraitTest::testIsPointer()
{
    // Verify that QExtTypeIsPointer is true for some pointer types.
    QVERIFY(QExtTypeIsPointer<int *>::value);
    QVERIFY(QExtTypeIsPointer<void *>::value);
    QVERIFY(QExtTypeIsPointer<QString *>::value);
    QVERIFY(QExtTypeIsPointer<const void *>::value);
    QVERIFY(QExtTypeIsPointer<volatile float *const *>::value);

    // Verify that QExtTypeIsPointer is false for some non-pointer types.
    QVERIFY(!QExtTypeIsPointer<void>::value);
    QVERIFY(!QExtTypeIsPointer<float &>::value);
    QVERIFY(!QExtTypeIsPointer<long>::value);
    QVERIFY(!QExtTypeIsPointer<QVector<int *> >::value);
    QVERIFY(!QExtTypeIsPointer<int[5]>::value);

    // A function pointer is a pointer, but a function type, or a function
    // reference type, is not.
    QVERIFY(QExtTypeIsPointer<int (*)(int x)>::value);
    QVERIFY(!QExtTypeIsPointer<void(char x)>::value);
    QVERIFY(!QExtTypeIsPointer<double (&)(QString x)>::value);

    // Verify that QExtTypeIsPointer<T> is true for some cv-qualified pointer types,
    // and false for some cv-qualified non-pointer types.
    QVERIFY(QExtTypeIsPointer<int *const>::value);
    QVERIFY(QExtTypeIsPointer<const void *volatile>::value);
    QVERIFY(QExtTypeIsPointer<char **const volatile>::value);
    QVERIFY(!QExtTypeIsPointer<const int>::value);
    QVERIFY(!QExtTypeIsPointer<volatile QVector<int *> >::value);
    QVERIFY(!QExtTypeIsPointer<const volatile double>::value);
}

void QExtTypeTraitTest::testIsEnum()
{
    // QExtTypeIsEnum isn't supported on MSVC or gcc 3.x
#if !defined(_MSC_VER) && !(defined(__GNUC__) && __GNUC__ <= 3)
    // Verify that QExtTypeIsEnum is true for enum types.
    QVERIFY(QExtTypeIsEnum<G>::value);
    QVERIFY(QExtTypeIsEnum<const G>::value);
    QVERIFY(QExtTypeIsEnum<volatile G>::value);
    QVERIFY(QExtTypeIsEnum<const volatile G>::value);

    // Verify that QExtTypeIsEnum is false for a few non-enum types.
    QVERIFY(!QExtTypeIsEnum<void>::value);
    QVERIFY(!QExtTypeIsEnum<G &>::value);
    QVERIFY(!QExtTypeIsEnum<G[1]>::value);
    QVERIFY(!QExtTypeIsEnum<const G[1]>::value);
    QVERIFY(!QExtTypeIsEnum<G[]>::value);
    QVERIFY(!QExtTypeIsEnum<int>::value);
    QVERIFY(!QExtTypeIsEnum<float>::value);
    QVERIFY(!QExtTypeIsEnum<A>::value);
    QVERIFY(!QExtTypeIsEnum<A *>::value);
    QVERIFY(!QExtTypeIsEnum<const A>::value);
    QVERIFY(!QExtTypeIsEnum<H>::value);
    QVERIFY(!QExtTypeIsEnum<I>::value);
    QVERIFY(!QExtTypeIsEnum<J>::value);
    QVERIFY(!QExtTypeIsEnum<void()>::value);
    QVERIFY(!QExtTypeIsEnum<void(*)()>::value);
    QVERIFY(!QExtTypeIsEnum<int A::*>::value);
    QVERIFY(!QExtTypeIsEnum<void (A::*)()>::value);
#endif
}

void QExtTypeTraitTest::testIsReference()
{
    // Verifies that QExtTypeIsReference is true for all reference types.
    typedef float &RefFloat;
    QVERIFY(QExtTypeIsReference<float &>::value);
    QVERIFY(QExtTypeIsReference<const int &>::value);
    QVERIFY(QExtTypeIsReference<const int *&>::value);
    QVERIFY(QExtTypeIsReference<int (&)(bool)>::value);
    QVERIFY(QExtTypeIsReference<RefFloat>::value);
    QVERIFY(QExtTypeIsReference<const RefFloat>::value);
    QVERIFY(QExtTypeIsReference<volatile RefFloat>::value);
    QVERIFY(QExtTypeIsReference<const volatile RefFloat>::value);


    // Verifies that QExtTypeIsReference is false for all non-reference types.
    QVERIFY(!QExtTypeIsReference<float>::value);
    QVERIFY(!QExtTypeIsReference<const float>::value);
    QVERIFY(!QExtTypeIsReference<volatile float>::value);
    QVERIFY(!QExtTypeIsReference<const volatile float>::value);
    QVERIFY(!QExtTypeIsReference<const int *>::value);
    QVERIFY(!QExtTypeIsReference<int()>::value);
    QVERIFY(!QExtTypeIsReference<void(*)(const char &)>::value);
}

void QExtTypeTraitTest::testAddReference()
{
    COMPILE_ASSERT_TYPES_EQ(int &, QExtTypeAddReference<int>::Type);
    COMPILE_ASSERT_TYPES_EQ(const int &, QExtTypeAddReference<const int>::Type);
    COMPILE_ASSERT_TYPES_EQ(volatile int &, QExtTypeAddReference<volatile int>::Type);
    COMPILE_ASSERT_TYPES_EQ(const volatile int &, QExtTypeAddReference<const volatile int>::Type);
    COMPILE_ASSERT_TYPES_EQ(int &, QExtTypeAddReference<int &>::Type);
    COMPILE_ASSERT_TYPES_EQ(const int &, QExtTypeAddReference<const int &>::Type);
    COMPILE_ASSERT_TYPES_EQ(volatile int &, QExtTypeAddReference<volatile int &>::Type);
    COMPILE_ASSERT_TYPES_EQ(const volatile int &, QExtTypeAddReference<const volatile int &>::Type);
}

void QExtTypeTraitTest::testIsPod()
{
    // Verify that arithmetic types and pointers are marked as PODs.
    QVERIFY(QExtTypeIsPod<bool>::value);
    QVERIFY(QExtTypeIsPod<char>::value);
    QVERIFY(QExtTypeIsPod<unsigned char>::value);
    QVERIFY(QExtTypeIsPod<signed char>::value);
    QVERIFY(QExtTypeIsPod<wchar_t>::value);
    QVERIFY(QExtTypeIsPod<int>::value);
    QVERIFY(QExtTypeIsPod<unsigned int>::value);
    QVERIFY(QExtTypeIsPod<short>::value);
    QVERIFY(QExtTypeIsPod<unsigned short>::value);
    QVERIFY(QExtTypeIsPod<long>::value);
    QVERIFY(QExtTypeIsPod<unsigned long>::value);
    QVERIFY(QExtTypeIsPod<float>::value);
    QVERIFY(QExtTypeIsPod<double>::value);
    QVERIFY(QExtTypeIsPod<long double>::value);
    QVERIFY(QExtTypeIsPod<QString *>::value);
    QVERIFY(QExtTypeIsPod<A *>::value);
    QVERIFY(QExtTypeIsPod<const B *>::value);
    QVERIFY(QExtTypeIsPod<C **>::value);
    QVERIFY(QExtTypeIsPod<const int>::value);
    QVERIFY(QExtTypeIsPod<char *volatile>::value);
    QVERIFY(QExtTypeIsPod<const volatile double>::value);
#if !defined(_MSC_VER) && !(defined(__GNUC__) && __GNUC__ <= 3)
    QVERIFY(QExtTypeIsPod<G>::value);
    QVERIFY(QExtTypeIsPod<const G>::value);
    QVERIFY(QExtTypeIsPod<volatile G>::value);
    QVERIFY(QExtTypeIsPod<const volatile G>::value);
#endif

    // Verify that some non-POD types are not marked as PODs.
    QVERIFY(!QExtTypeIsPod<void>::value);
    QVERIFY(!QExtTypeIsPod<QString>::value);
    QVERIFY(!(QExtTypeIsPod<QPair<int, int> >::value));
    QVERIFY(!QExtTypeIsPod<A>::value);
    QVERIFY(!QExtTypeIsPod<B>::value);
    QVERIFY(!QExtTypeIsPod<C>::value);
    QVERIFY(!QExtTypeIsPod<const QString>::value);
    QVERIFY(!QExtTypeIsPod<volatile A>::value);
    QVERIFY(!QExtTypeIsPod<const volatile B>::value);
}

void QExtTypeTraitTest::testHasTrivialConstructor()
{
    // Verify that arithmetic types and pointers have trivial constructors.
    QVERIFY(QExtTypeHasTrivialConstructor<bool>::value);
    QVERIFY(QExtTypeHasTrivialConstructor<char>::value);
    QVERIFY(QExtTypeHasTrivialConstructor<unsigned char>::value);
    QVERIFY(QExtTypeHasTrivialConstructor<signed char>::value);
    QVERIFY(QExtTypeHasTrivialConstructor<wchar_t>::value);
    QVERIFY(QExtTypeHasTrivialConstructor<int>::value);
    QVERIFY(QExtTypeHasTrivialConstructor<unsigned int>::value);
    QVERIFY(QExtTypeHasTrivialConstructor<short>::value);
    QVERIFY(QExtTypeHasTrivialConstructor<unsigned short>::value);
    QVERIFY(QExtTypeHasTrivialConstructor<long>::value);
    QVERIFY(QExtTypeHasTrivialConstructor<unsigned long>::value);
    QVERIFY(QExtTypeHasTrivialConstructor<float>::value);
    QVERIFY(QExtTypeHasTrivialConstructor<double>::value);
    QVERIFY(QExtTypeHasTrivialConstructor<long double>::value);
    QVERIFY(QExtTypeHasTrivialConstructor<QString *>::value);
    QVERIFY(QExtTypeHasTrivialConstructor<A *>::value);
    QVERIFY(QExtTypeHasTrivialConstructor<const B *>::value);
    QVERIFY(QExtTypeHasTrivialConstructor<C **>::value);

    // Verify that pairs and arrays of such types have trivial
    // constructors.
    typedef int int10[10];
    QVERIFY((QExtTypeHasTrivialConstructor<QPair<int, char *> >::value));
    QVERIFY(QExtTypeHasTrivialConstructor<int10>::value);

    // Verify that pairs of types without trivial constructors
    // are not marked as trivial.
    QVERIFY(!(QExtTypeHasTrivialConstructor<QPair<int, QString> >::value));
    QVERIFY(!(QExtTypeHasTrivialConstructor<QPair<QString, int> >::value));

    // Verify that types without trivial constructors are
    // correctly marked as such.
    QVERIFY(!QExtTypeHasTrivialConstructor<QString>::value);
    QVERIFY(!QExtTypeHasTrivialConstructor<QVector<int> >::value);

    // Verify that E, which we have declared to have a trivial
    // constructor, is correctly marked as such.
    QVERIFY(QExtTypeHasTrivialConstructor<E>::value);
}

void QExtTypeTraitTest::testHasTrivialCopy()
{
    // Verify that arithmetic types and pointers have trivial copy
    // constructors.
    QVERIFY(QExtTypeHasTrivialCopy<bool>::value);
    QVERIFY(QExtTypeHasTrivialCopy<char>::value);
    QVERIFY(QExtTypeHasTrivialCopy<unsigned char>::value);
    QVERIFY(QExtTypeHasTrivialCopy<signed char>::value);
    QVERIFY(QExtTypeHasTrivialCopy<wchar_t>::value);
    QVERIFY(QExtTypeHasTrivialCopy<int>::value);
    QVERIFY(QExtTypeHasTrivialCopy<unsigned int>::value);
    QVERIFY(QExtTypeHasTrivialCopy<short>::value);
    QVERIFY(QExtTypeHasTrivialCopy<unsigned short>::value);
    QVERIFY(QExtTypeHasTrivialCopy<long>::value);
    QVERIFY(QExtTypeHasTrivialCopy<unsigned long>::value);
    QVERIFY(QExtTypeHasTrivialCopy<float>::value);
    QVERIFY(QExtTypeHasTrivialCopy<double>::value);
    QVERIFY(QExtTypeHasTrivialCopy<long double>::value);
    QVERIFY(QExtTypeHasTrivialCopy<QString *>::value);
    QVERIFY(QExtTypeHasTrivialCopy<A *>::value);
    QVERIFY(QExtTypeHasTrivialCopy<const B *>::value);
    QVERIFY(QExtTypeHasTrivialCopy<C **>::value);

    // Verify that pairs and arrays of such types have trivial
    // copy constructors.
    typedef int int10[10];
    QVERIFY((QExtTypeHasTrivialCopy<QPair<int, char *> >::value));
    QVERIFY(QExtTypeHasTrivialCopy<int10>::value);

    // Verify that pairs of types without trivial copy constructors
    // are not marked as trivial.
    QVERIFY(!(QExtTypeHasTrivialCopy<QPair<int, QString> >::value));
    QVERIFY(!(QExtTypeHasTrivialCopy<QPair<QString, int> >::value));

    // Verify that types without trivial copy constructors are
    // correctly marked as such.
    QVERIFY(!QExtTypeHasTrivialCopy<QString>::value);
    QVERIFY(!QExtTypeHasTrivialCopy<QVector<int> >::value);

    // Verify that C, which we have declared to have a trivial
    // copy constructor, is correctly marked as such.
    QVERIFY(QExtTypeHasTrivialCopy<C>::value);
}

void QExtTypeTraitTest::testHasTrivialAssign()
{
    // Verify that arithmetic types and pointers have trivial assignment
    // operators.
    QVERIFY(QExtTypeHasTrivialAssign<bool>::value);
    QVERIFY(QExtTypeHasTrivialAssign<char>::value);
    QVERIFY(QExtTypeHasTrivialAssign<unsigned char>::value);
    QVERIFY(QExtTypeHasTrivialAssign<signed char>::value);
    QVERIFY(QExtTypeHasTrivialAssign<wchar_t>::value);
    QVERIFY(QExtTypeHasTrivialAssign<int>::value);
    QVERIFY(QExtTypeHasTrivialAssign<unsigned int>::value);
    QVERIFY(QExtTypeHasTrivialAssign<short>::value);
    QVERIFY(QExtTypeHasTrivialAssign<unsigned short>::value);
    QVERIFY(QExtTypeHasTrivialAssign<long>::value);
    QVERIFY(QExtTypeHasTrivialAssign<unsigned long>::value);
    QVERIFY(QExtTypeHasTrivialAssign<float>::value);
    QVERIFY(QExtTypeHasTrivialAssign<double>::value);
    QVERIFY(QExtTypeHasTrivialAssign<long double>::value);
    QVERIFY(QExtTypeHasTrivialAssign<QString *>::value);
    QVERIFY(QExtTypeHasTrivialAssign<A *>::value);
    QVERIFY(QExtTypeHasTrivialAssign<const B *>::value);
    QVERIFY(QExtTypeHasTrivialAssign<C **>::value);

    // Verify that pairs and arrays of such types have trivial
    // assignment operators.
    typedef int int10[10];
    QVERIFY((QExtTypeHasTrivialAssign<QPair<int, char *> >::value));
    QVERIFY(QExtTypeHasTrivialAssign<int10>::value);

    // Verify that pairs of types without trivial assignment operators
    // are not marked as trivial.
    QVERIFY(!(QExtTypeHasTrivialAssign<QPair<int, QString> >::value));
    QVERIFY(!(QExtTypeHasTrivialAssign<QPair<QString, int> >::value));

    // Verify that types without trivial assignment operators are
    // correctly marked as such.
    QVERIFY(!QExtTypeHasTrivialAssign<QString>::value);
    QVERIFY(!QExtTypeHasTrivialAssign<QVector<int> >::value);

    // Verify that D, which we have declared to have a trivial
    // assignment operator, is correctly marked as such.
    QVERIFY(QExtTypeHasTrivialAssign<D>::value);
}

void QExtTypeTraitTest::testHasTrivialDestructor()
{
    // Verify that arithmetic types and pointers have trivial destructors.
    QVERIFY(QExtTypeHasTrivialDestructor<bool>::value);
    QVERIFY(QExtTypeHasTrivialDestructor<char>::value);
    QVERIFY(QExtTypeHasTrivialDestructor<unsigned char>::value);
    QVERIFY(QExtTypeHasTrivialDestructor<signed char>::value);
    QVERIFY(QExtTypeHasTrivialDestructor<wchar_t>::value);
    QVERIFY(QExtTypeHasTrivialDestructor<int>::value);
    QVERIFY(QExtTypeHasTrivialDestructor<unsigned int>::value);
    QVERIFY(QExtTypeHasTrivialDestructor<short>::value);
    QVERIFY(QExtTypeHasTrivialDestructor<unsigned short>::value);
    QVERIFY(QExtTypeHasTrivialDestructor<long>::value);
    QVERIFY(QExtTypeHasTrivialDestructor<unsigned long>::value);
    QVERIFY(QExtTypeHasTrivialDestructor<float>::value);
    QVERIFY(QExtTypeHasTrivialDestructor<double>::value);
    QVERIFY(QExtTypeHasTrivialDestructor<long double>::value);
    QVERIFY(QExtTypeHasTrivialDestructor<QString *>::value);
    QVERIFY(QExtTypeHasTrivialDestructor<A *>::value);
    QVERIFY(QExtTypeHasTrivialDestructor<const B *>::value);
    QVERIFY(QExtTypeHasTrivialDestructor<C **>::value);

    // Verify that pairs and arrays of such types have trivial
    // destructors.
    typedef int int10[10];
    QVERIFY((QExtTypeHasTrivialDestructor<QPair<int, char *> >::value));
    QVERIFY(QExtTypeHasTrivialDestructor<int10>::value);

    // Verify that pairs of types without trivial destructors
    // are not marked as trivial.
    QVERIFY(!(QExtTypeHasTrivialDestructor<QPair<int, QString> >::value));
    QVERIFY(!(QExtTypeHasTrivialDestructor<QPair<QString, int> >::value));

    // Verify that types without trivial destructors are
    // correctly marked as such.
    QVERIFY(!QExtTypeHasTrivialDestructor<QString>::value);
    QVERIFY(!QExtTypeHasTrivialDestructor<QVector<int> >::value);

    // Verify that F, which we have declared to have a trivial
    // destructor, is correctly marked as such.
    QVERIFY(QExtTypeHasTrivialDestructor<F>::value);
}

void QExtTypeTraitTest::testRemovePointer()
{
    COMPILE_ASSERT_TYPES_EQ(int, QExtTypeRemovePointer<int>::Type);
    COMPILE_ASSERT_TYPES_EQ(int, QExtTypeRemovePointer<int *>::Type);
    COMPILE_ASSERT_TYPES_EQ(const int, QExtTypeRemovePointer<const int *>::Type);
    COMPILE_ASSERT_TYPES_EQ(int, QExtTypeRemovePointer<int *const>::Type);
    COMPILE_ASSERT_TYPES_EQ(int, QExtTypeRemovePointer<int *volatile>::Type);
}

void QExtTypeTraitTest::testRemoveConst()
{
    COMPILE_ASSERT_TYPES_EQ(int, QExtTypeRemoveConst<int>::Type);
    COMPILE_ASSERT_TYPES_EQ(int, QExtTypeRemoveConst<const int>::Type);
    COMPILE_ASSERT_TYPES_EQ(int *, QExtTypeRemoveConst<int *const>::Type);
    // TR1 examples.
    COMPILE_ASSERT_TYPES_EQ(const int *, QExtTypeRemoveConst<const int *>::Type);
    COMPILE_ASSERT_TYPES_EQ(volatile int, QExtTypeRemoveConst<const volatile int>::Type);
}

void QExtTypeTraitTest::testRemoveVolatile()
{
    COMPILE_ASSERT_TYPES_EQ(int, QExtTypeRemoveVolatile<int>::Type);
    COMPILE_ASSERT_TYPES_EQ(int, QExtTypeRemoveVolatile<volatile int>::Type);
    COMPILE_ASSERT_TYPES_EQ(int *, QExtTypeRemoveVolatile<int *volatile>::Type);
    // TR1 examples.
    COMPILE_ASSERT_TYPES_EQ(volatile int *, QExtTypeRemoveVolatile<volatile int *>::Type);
    COMPILE_ASSERT_TYPES_EQ(const int, QExtTypeRemoveVolatile<const volatile int>::Type);
}

void QExtTypeTraitTest::testRemoveCV()
{
    COMPILE_ASSERT_TYPES_EQ(int, QExtTypeRemoveConstVolatile<int>::Type);
    COMPILE_ASSERT_TYPES_EQ(int, QExtTypeRemoveConstVolatile<volatile int>::Type);
    COMPILE_ASSERT_TYPES_EQ(int, QExtTypeRemoveConstVolatile<const int>::Type);
    COMPILE_ASSERT_TYPES_EQ(int *, QExtTypeRemoveConstVolatile<int *const volatile>::Type);
    // TR1 examples.
    COMPILE_ASSERT_TYPES_EQ(const volatile int *, QExtTypeRemoveConstVolatile<const volatile int *>::Type);
    COMPILE_ASSERT_TYPES_EQ(int, QExtTypeRemoveConstVolatile<const volatile int>::Type);
}

void QExtTypeTraitTest::testRemoveReference()
{
    COMPILE_ASSERT_TYPES_EQ(int, QExtTypeRemoveReference<int>::Type);
    COMPILE_ASSERT_TYPES_EQ(int, QExtTypeRemoveReference<int &>::Type);
    COMPILE_ASSERT_TYPES_EQ(const int, QExtTypeRemoveReference<const int &>::Type);
    COMPILE_ASSERT_TYPES_EQ(int *, QExtTypeRemoveReference<int *&>::Type);
}

void QExtTypeTraitTest::testIsSame()
{
    QVERIFY((QExtTypeIsSame<int32, int32>::value));
    QVERIFY(!(QExtTypeIsSame<int32, int64>::value));
    QVERIFY(!(QExtTypeIsSame<int64, int32>::value));
    QVERIFY(!(QExtTypeIsSame<int, const int>::value));

    QVERIFY((QExtTypeIsSame<void, void>::value));
    QVERIFY(!(QExtTypeIsSame<void, int>::value));
    QVERIFY(!(QExtTypeIsSame<int, void>::value));

    QVERIFY((QExtTypeIsSame<int *, int *>::value));
    QVERIFY((QExtTypeIsSame<void *, void *>::value));
    QVERIFY(!(QExtTypeIsSame<int *, void *>::value));
    QVERIFY(!(QExtTypeIsSame<void *, int *>::value));
    QVERIFY(!(QExtTypeIsSame<void *, const void *>::value));
    QVERIFY(!(QExtTypeIsSame<void *, void *const>::value));

    QVERIFY((QExtTypeIsSame<Base *, Base *>::value));
    QVERIFY((QExtTypeIsSame<Derived *, Derived *>::value));
    QVERIFY(!(QExtTypeIsSame<Base *, Derived *>::value));
    QVERIFY(!(QExtTypeIsSame<Derived *, Base *>::value));
}

void QExtTypeTraitTest::testConvertible()
{
#if !defined(_MSC_VER) && !(defined(__GNUC__) && __GNUC__ <= 3)
    QVERIFY((QExtTypeIsConvertible<int, int>::value));
    QVERIFY((QExtTypeIsConvertible<int, long>::value));
    QVERIFY((QExtTypeIsConvertible<long, int>::value));

    QVERIFY((QExtTypeIsConvertible<int *, void *>::value));
    QVERIFY(!(QExtTypeIsConvertible<void *, int *>::value));

    QVERIFY((QExtTypeIsConvertible<Derived *, Base *>::value));
    QVERIFY(!(QExtTypeIsConvertible<Base *, Derived *>::value));
    QVERIFY((QExtTypeIsConvertible<Derived *, const Base *>::value));
    QVERIFY(!(QExtTypeIsConvertible<const Derived *, Base *>::value));
#endif
}

QTEST_APPLESS_MAIN(QExtTypeTraitTest)

#include <tst_qextTypeTrait.moc>

