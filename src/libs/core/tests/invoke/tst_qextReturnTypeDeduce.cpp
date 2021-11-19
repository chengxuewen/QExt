#include <qextReturnTypeDeduce.h>

#include <QtTest>

#include <iostream>
#include <string>
#include <sstream>

class QEXTReturnTypeDeduceTest : public QObject
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

struct Foo : public QEXTFunctorBase
{
    typedef double Return;

    int operator()(int i = 1);
    double operator()(const int &, int);
};

struct Foo2 : public Foo {};

struct Foo3 : public QEXTFunctorBase
{
    typedef int Return;

    int operator()(int i = 1);
    double operator()(const int &, int);
};

void QEXTReturnTypeDeduceTest::testSimple()
{
    sg_string = "";
    Bar(QEXTReturnTypeDeduce<Foo2, long>::Type());
    QVERIFY("double" == sg_string);

    sg_string = "";
    Bar(QEXTReturnTypeDeduce<Foo2, int, int>::Type());
    QVERIFY("double" == sg_string);

    sg_string = "";
    Bar(QEXTReturnTypeDeduce<Foo3, int, int>::Type());
    QVERIFY("int" == sg_string);

    sg_string = "";
    Bar(QEXTReturnTypeDeduce<Foo2, int, int, int>::Type());
    QVERIFY("double" == sg_string);
}



QTEST_APPLESS_MAIN(QEXTReturnTypeDeduceTest)

#include <tst_qextReturnTypeDeduce.moc>
