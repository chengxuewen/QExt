#include <qextReturnTypeDeduce.h>

#include <QtTest>

#include <iostream>
#include <string>
#include <sstream>

class QExtReturnTypeDeduceTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void testSimple();
};

static QString sg_string = "";


template <typename T>
void Bar(T)
{
    sg_string = "unknown";
}

template <>
void Bar<int>(int)
{
    sg_string = "int";
}

template <>
void Bar<long>(long)
{
    sg_string = "long";
}

template <>
void Bar<double>(double)
{
    sg_string = "double";
}

struct Foo : public QExtFunctorBase
{
    typedef double ResultType;

    int operator()(int i = 1);
    double operator()(const int &, int);
};

struct Foo2 : public Foo {};

struct Foo3 : public QExtFunctorBase
{
    typedef int ResultType;

    int operator()(int i = 1);
    double operator()(const int &, int);
};

void QExtReturnTypeDeduceTest::testSimple()
{
    sg_string = "";
    Bar(QExtReturnTypeDeduce<Foo2, long>::Type());
    QVERIFY("double" == sg_string);

    sg_string = "";
    Bar(QExtReturnTypeDeduce<Foo2, int, int>::Type());
    QVERIFY("double" == sg_string);

    sg_string = "";
    Bar(QExtReturnTypeDeduce<Foo3, int, int>::Type());
    QVERIFY("int" == sg_string);

    sg_string = "";
    Bar(QExtReturnTypeDeduce<Foo2, int, int, int>::Type());
    QVERIFY("double" == sg_string);
}



QTEST_APPLESS_MAIN(QExtReturnTypeDeduceTest)

#include <tst_qextReturnTypeDeduce.moc>
