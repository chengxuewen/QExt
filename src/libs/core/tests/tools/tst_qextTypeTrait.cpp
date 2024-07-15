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
template<> struct QExtTypeHasTrivialCopy<C> : QExtTrueType { };


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
template<> struct QExtTypeHasTrivialAssign<D> : QExtTrueType { };


// Another user-defined non-POD type with a trivial constructor.
// We will explicitly declare E to have a trivial constructor
// by specializing has_trivial_constructor.
class E
{
public:
    int n_;
};
template<> struct QExtTypeHasTrivialConstructor<E> : QExtTrueType { };


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
template<> struct QExtTypeHasTrivialDestructor<F> : QExtTrueType { };


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

template <typename T_obj, bool I_derives_base = QExtIsBaseOf<MClassBase, T_obj>::value>
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
    drived = QExtIsBaseOf<MClassBase, MClass>::value;
    QVERIFY(drived);
    drived = QExtIsBaseOf<MClassBase, MClassBase>::value;
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
    // Verify that QExtIsIntegral is true for all integer types.
    QVERIFY(QExtIsIntegral<bool>::value);
    QVERIFY(QExtIsIntegral<char>::value);
    QVERIFY(QExtIsIntegral<unsigned char>::value);
    QVERIFY(QExtIsIntegral<signed char>::value);
    QVERIFY(QExtIsIntegral<wchar_t>::value);
    QVERIFY(QExtIsIntegral<int>::value);
    QVERIFY(QExtIsIntegral<unsigned int>::value);
    QVERIFY(QExtIsIntegral<short>::value);
    QVERIFY(QExtIsIntegral<unsigned short>::value);
    QVERIFY(QExtIsIntegral<long>::value);
    QVERIFY(QExtIsIntegral<unsigned long>::value);

    // Verify that QExtIsIntegral is false for a few non-integer types.
    QVERIFY(!QExtIsIntegral<void>::value);
    QVERIFY(!QExtIsIntegral<float>::value);
    QVERIFY(!QExtIsIntegral<QString>::value);
    QVERIFY(!QExtIsIntegral<int *>::value);
    QVERIFY(!QExtIsIntegral<A>::value);
    QVERIFY(!(QExtIsIntegral<QPair<int, int> >::value));

    // Verify that cv-qualified integral types are still integral, and
    // cv-qualified non-integral types are still non-integral.
    QVERIFY(QExtIsIntegral<const char>::value);
    QVERIFY(QExtIsIntegral<volatile bool>::value);
    QVERIFY(QExtIsIntegral<const volatile unsigned int>::value);
    QVERIFY(!QExtIsIntegral<const float>::value);
    QVERIFY(!QExtIsIntegral<int *volatile>::value);
    QVERIFY(!QExtIsIntegral<const volatile QString>::value);
}

void QExtTypeTraitTest::testIsFloating()
{
    // Verify that QExtIsFloatingPoint is true for all floating-point types.
    QVERIFY(QExtIsFloatingPoint<float>::value);
    QVERIFY(QExtIsFloatingPoint<double>::value);
    QVERIFY(QExtIsFloatingPoint<long double>::value);

    // Verify that QExtIsFloatingPoint is false for a few non-float types.
    QVERIFY(!QExtIsFloatingPoint<void>::value);
    QVERIFY(!QExtIsFloatingPoint<long>::value);
    QVERIFY(!QExtIsFloatingPoint<QString>::value);
    QVERIFY(!QExtIsFloatingPoint<float *>::value);
    QVERIFY(!QExtIsFloatingPoint<A>::value);
    QVERIFY(!(QExtIsFloatingPoint<QPair<int, int> >::value));

    // Verify that cv-qualified floating point types are still floating, and
    // cv-qualified non-floating types are still non-floating.
    QVERIFY(QExtIsFloatingPoint<const float>::value);
    QVERIFY(QExtIsFloatingPoint<volatile double>::value);
    QVERIFY(QExtIsFloatingPoint<const volatile long double>::value);
    QVERIFY(!QExtIsFloatingPoint<const int>::value);
    QVERIFY(!QExtIsFloatingPoint<volatile QString>::value);
    QVERIFY(!QExtIsFloatingPoint<const volatile char>::value);
}

void QExtTypeTraitTest::testIsPointer()
{
    // Verify that QExtIsPointer is true for some pointer types.
    QVERIFY(QExtIsPointer<int *>::value);
    QVERIFY(QExtIsPointer<void *>::value);
    QVERIFY(QExtIsPointer<QString *>::value);
    QVERIFY(QExtIsPointer<const void *>::value);
    QVERIFY(QExtIsPointer<volatile float *const *>::value);

    // Verify that QExtIsPointer is false for some non-pointer types.
    QVERIFY(!QExtIsPointer<void>::value);
    QVERIFY(!QExtIsPointer<float &>::value);
    QVERIFY(!QExtIsPointer<long>::value);
    QVERIFY(!QExtIsPointer<QVector<int *> >::value);
    QVERIFY(!QExtIsPointer<int[5]>::value);

    // A function pointer is a pointer, but a function type, or a function
    // reference type, is not.
    QVERIFY(QExtIsPointer<int (*)(int x)>::value);
    QVERIFY(!QExtIsPointer<void(char x)>::value);
    QVERIFY(!QExtIsPointer<double (&)(QString x)>::value);

    // Verify that QExtIsPointer<T> is true for some cv-qualified pointer types,
    // and false for some cv-qualified non-pointer types.
    QVERIFY(QExtIsPointer<int *const>::value);
    QVERIFY(QExtIsPointer<const void *volatile>::value);
    QVERIFY(QExtIsPointer<char **const volatile>::value);
    QVERIFY(!QExtIsPointer<const int>::value);
    QVERIFY(!QExtIsPointer<volatile QVector<int *> >::value);
    QVERIFY(!QExtIsPointer<const volatile double>::value);
}

void QExtTypeTraitTest::testIsEnum()
{
    // QExtIsEnum isn't supported on MSVC or gcc 3.x
#if !defined(_MSC_VER) && !(defined(__GNUC__) && __GNUC__ <= 3)
    // Verify that QExtIsEnum is true for enum types.
    QVERIFY(QExtIsEnum<G>::value);
    QVERIFY(QExtIsEnum<const G>::value);
    QVERIFY(QExtIsEnum<volatile G>::value);
    QVERIFY(QExtIsEnum<const volatile G>::value);

    // Verify that QExtIsEnum is false for a few non-enum types.
    QVERIFY(!QExtIsEnum<void>::value);
    QVERIFY(!QExtIsEnum<G &>::value);
    QVERIFY(!QExtIsEnum<G[1]>::value);
    QVERIFY(!QExtIsEnum<const G[1]>::value);
    QVERIFY(!QExtIsEnum<G[]>::value);
    QVERIFY(!QExtIsEnum<int>::value);
    QVERIFY(!QExtIsEnum<float>::value);
    QVERIFY(!QExtIsEnum<A>::value);
    QVERIFY(!QExtIsEnum<A *>::value);
    QVERIFY(!QExtIsEnum<const A>::value);
    QVERIFY(!QExtIsEnum<H>::value);
    QVERIFY(!QExtIsEnum<I>::value);
    QVERIFY(!QExtIsEnum<J>::value);
    QVERIFY(!QExtIsEnum<void()>::value);
    QVERIFY(!QExtIsEnum<void(*)()>::value);
    QVERIFY(!QExtIsEnum<int A::*>::value);
    QVERIFY(!QExtIsEnum<void (A::*)()>::value);
#endif
}

void QExtTypeTraitTest::testIsReference()
{
    // Verifies that QExtIsReference is true for all reference types.
    typedef float &RefFloat;
    QVERIFY(QExtIsReference<float &>::value);
    QVERIFY(QExtIsReference<const int &>::value);
    QVERIFY(QExtIsReference<const int *&>::value);
    QVERIFY(QExtIsReference<int (&)(bool)>::value);
    QVERIFY(QExtIsReference<RefFloat>::value);
    QVERIFY(QExtIsReference<const RefFloat>::value);
    QVERIFY(QExtIsReference<volatile RefFloat>::value);
    QVERIFY(QExtIsReference<const volatile RefFloat>::value);


    // Verifies that QExtIsReference is false for all non-reference types.
    QVERIFY(!QExtIsReference<float>::value);
    QVERIFY(!QExtIsReference<const float>::value);
    QVERIFY(!QExtIsReference<volatile float>::value);
    QVERIFY(!QExtIsReference<const volatile float>::value);
    QVERIFY(!QExtIsReference<const int *>::value);
    QVERIFY(!QExtIsReference<int()>::value);
    QVERIFY(!QExtIsReference<void(*)(const char &)>::value);
}

void QExtTypeTraitTest::testAddReference()
{
    COMPILE_ASSERT_TYPES_EQ(int &, QExtAddReference<int>::Type);
    COMPILE_ASSERT_TYPES_EQ(const int &, QExtAddReference<const int>::Type);
    COMPILE_ASSERT_TYPES_EQ(volatile int &, QExtAddReference<volatile int>::Type);
    COMPILE_ASSERT_TYPES_EQ(const volatile int &, QExtAddReference<const volatile int>::Type);
    COMPILE_ASSERT_TYPES_EQ(int &, QExtAddReference<int &>::Type);
    COMPILE_ASSERT_TYPES_EQ(const int &, QExtAddReference<const int &>::Type);
    COMPILE_ASSERT_TYPES_EQ(volatile int &, QExtAddReference<volatile int &>::Type);
    COMPILE_ASSERT_TYPES_EQ(const volatile int &, QExtAddReference<const volatile int &>::Type);
}

void QExtTypeTraitTest::testIsPod()
{
    // Verify that arithmetic types and pointers are marked as PODs.
    QVERIFY(QExtIsPod<bool>::value);
    QVERIFY(QExtIsPod<char>::value);
    QVERIFY(QExtIsPod<unsigned char>::value);
    QVERIFY(QExtIsPod<signed char>::value);
    QVERIFY(QExtIsPod<wchar_t>::value);
    QVERIFY(QExtIsPod<int>::value);
    QVERIFY(QExtIsPod<unsigned int>::value);
    QVERIFY(QExtIsPod<short>::value);
    QVERIFY(QExtIsPod<unsigned short>::value);
    QVERIFY(QExtIsPod<long>::value);
    QVERIFY(QExtIsPod<unsigned long>::value);
    QVERIFY(QExtIsPod<float>::value);
    QVERIFY(QExtIsPod<double>::value);
    QVERIFY(QExtIsPod<long double>::value);
    QVERIFY(QExtIsPod<QString *>::value);
    QVERIFY(QExtIsPod<A *>::value);
    QVERIFY(QExtIsPod<const B *>::value);
    QVERIFY(QExtIsPod<C **>::value);
    QVERIFY(QExtIsPod<const int>::value);
    QVERIFY(QExtIsPod<char *volatile>::value);
    QVERIFY(QExtIsPod<const volatile double>::value);
#if !defined(_MSC_VER) && !(defined(__GNUC__) && __GNUC__ <= 3)
    QVERIFY(QExtIsPod<G>::value);
    QVERIFY(QExtIsPod<const G>::value);
    QVERIFY(QExtIsPod<volatile G>::value);
    QVERIFY(QExtIsPod<const volatile G>::value);
#endif

    // Verify that some non-POD types are not marked as PODs.
    QVERIFY(!QExtIsPod<void>::value);
    QVERIFY(!QExtIsPod<QString>::value);
    QVERIFY(!(QExtIsPod<QPair<int, int> >::value));
    QVERIFY(!QExtIsPod<A>::value);
    QVERIFY(!QExtIsPod<B>::value);
    QVERIFY(!QExtIsPod<C>::value);
    QVERIFY(!QExtIsPod<const QString>::value);
    QVERIFY(!QExtIsPod<volatile A>::value);
    QVERIFY(!QExtIsPod<const volatile B>::value);
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
    COMPILE_ASSERT_TYPES_EQ(int, QExtRemovePointer<int>::Type);
    COMPILE_ASSERT_TYPES_EQ(int, QExtRemovePointer<int *>::Type);
    COMPILE_ASSERT_TYPES_EQ(const int, QExtRemovePointer<const int *>::Type);
    COMPILE_ASSERT_TYPES_EQ(int, QExtRemovePointer<int *const>::Type);
    COMPILE_ASSERT_TYPES_EQ(int, QExtRemovePointer<int *volatile>::Type);
}

void QExtTypeTraitTest::testRemoveConst()
{
    COMPILE_ASSERT_TYPES_EQ(int, QExtRemoveConst<int>::Type);
    COMPILE_ASSERT_TYPES_EQ(int, QExtRemoveConst<const int>::Type);
    COMPILE_ASSERT_TYPES_EQ(int *, QExtRemoveConst<int *const>::Type);
    // TR1 examples.
    COMPILE_ASSERT_TYPES_EQ(const int *, QExtRemoveConst<const int *>::Type);
    COMPILE_ASSERT_TYPES_EQ(volatile int, QExtRemoveConst<const volatile int>::Type);
}

void QExtTypeTraitTest::testRemoveVolatile()
{
    COMPILE_ASSERT_TYPES_EQ(int, QExtRemoveVolatile<int>::Type);
    COMPILE_ASSERT_TYPES_EQ(int, QExtRemoveVolatile<volatile int>::Type);
    COMPILE_ASSERT_TYPES_EQ(int *, QExtRemoveVolatile<int *volatile>::Type);
    // TR1 examples.
    COMPILE_ASSERT_TYPES_EQ(volatile int *, QExtRemoveVolatile<volatile int *>::Type);
    COMPILE_ASSERT_TYPES_EQ(const int, QExtRemoveVolatile<const volatile int>::Type);
}

void QExtTypeTraitTest::testRemoveCV()
{
    COMPILE_ASSERT_TYPES_EQ(int, QExtRemoveConstVolatile<int>::Type);
    COMPILE_ASSERT_TYPES_EQ(int, QExtRemoveConstVolatile<volatile int>::Type);
    COMPILE_ASSERT_TYPES_EQ(int, QExtRemoveConstVolatile<const int>::Type);
    COMPILE_ASSERT_TYPES_EQ(int *, QExtRemoveConstVolatile<int *const volatile>::Type);
    // TR1 examples.
    COMPILE_ASSERT_TYPES_EQ(const volatile int *, QExtRemoveConstVolatile<const volatile int *>::Type);
    COMPILE_ASSERT_TYPES_EQ(int, QExtRemoveConstVolatile<const volatile int>::Type);
}

void QExtTypeTraitTest::testRemoveReference()
{
    COMPILE_ASSERT_TYPES_EQ(int, QExtRemoveReference<int>::Type);
    COMPILE_ASSERT_TYPES_EQ(int, QExtRemoveReference<int &>::Type);
    COMPILE_ASSERT_TYPES_EQ(const int, QExtRemoveReference<const int &>::Type);
    COMPILE_ASSERT_TYPES_EQ(int *, QExtRemoveReference<int *&>::Type);
}

void QExtTypeTraitTest::testIsSame()
{
    QVERIFY((QExtIsSame<int32, int32>::value));
    QVERIFY(!(QExtIsSame<int32, int64>::value));
    QVERIFY(!(QExtIsSame<int64, int32>::value));
    QVERIFY(!(QExtIsSame<int, const int>::value));

    QVERIFY((QExtIsSame<void, void>::value));
    QVERIFY(!(QExtIsSame<void, int>::value));
    QVERIFY(!(QExtIsSame<int, void>::value));

    QVERIFY((QExtIsSame<int *, int *>::value));
    QVERIFY((QExtIsSame<void *, void *>::value));
    QVERIFY(!(QExtIsSame<int *, void *>::value));
    QVERIFY(!(QExtIsSame<void *, int *>::value));
    QVERIFY(!(QExtIsSame<void *, const void *>::value));
    QVERIFY(!(QExtIsSame<void *, void *const>::value));

    QVERIFY((QExtIsSame<Base *, Base *>::value));
    QVERIFY((QExtIsSame<Derived *, Derived *>::value));
    QVERIFY(!(QExtIsSame<Base *, Derived *>::value));
    QVERIFY(!(QExtIsSame<Derived *, Base *>::value));
}

void QExtTypeTraitTest::testConvertible()
{
#if !defined(_MSC_VER) && !(defined(__GNUC__) && __GNUC__ <= 3)
    QVERIFY((QExtIsConvertible<int, int>::value));
    QVERIFY((QExtIsConvertible<int, long>::value));
    QVERIFY((QExtIsConvertible<long, int>::value));

    QVERIFY((QExtIsConvertible<int *, void *>::value));
    QVERIFY(!(QExtIsConvertible<void *, int *>::value));

    QVERIFY((QExtIsConvertible<Derived *, Base *>::value));
    QVERIFY(!(QExtIsConvertible<Base *, Derived *>::value));
    QVERIFY((QExtIsConvertible<Derived *, const Base *>::value));
    QVERIFY(!(QExtIsConvertible<const Derived *, Base *>::value));
#endif
}

QTEST_APPLESS_MAIN(QExtTypeTraitTest)

#include <tst_qextTypeTrait.moc>

