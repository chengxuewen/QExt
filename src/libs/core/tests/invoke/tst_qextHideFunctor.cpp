#include <qextHideFunctor.h>

#include <QtTest>
#include <iostream>
#include <string>
#include <sstream>

class QExtHideFunctorTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void testSimple();
};

static std::string sg_string = "";

struct Foo : public QExtFunctorBase
{
    // choose a type that can hold all return values
    typedef int ResultType;

    int operator()()
    {
        sg_string = "Foo() ";
        return true;
    }

    int operator()(int j)
    {
        std::stringstream sstream;
        sstream << "Foo(int " << j << ") ";
        sg_string = sstream.str();
        return 1 + j;
    }
};

struct FooVoid : public QExtFunctorBase
{
    typedef void ResultType;

    void operator()()
    {
        sg_string = "FooVoid()";
    }
};


void QExtHideFunctorTest::testSimple()
{
    sg_string = "";
    QVERIFY(3 == qextHideFunctor<0>(Foo())(1, 2));
    QVERIFY("Foo(int 2) " == sg_string);

    sg_string = "";
    QVERIFY(2 == qextHideFunctor<1>(Foo())(1, 2));
    QVERIFY("Foo(int 1) " == sg_string);

    sg_string = "";
    QVERIFY(1 == qextHideFunctor < -1 > (Foo())(1));
    QVERIFY("Foo() " == sg_string);

    sg_string = "";
    QVERIFY(1 == qextHideFunctor(Foo())(1));
    QVERIFY("Foo() " == sg_string);

    sg_string = "";
    qextHideFunctor(FooVoid())(1); // void test
    QVERIFY("FooVoid()" == sg_string);
}

QTEST_APPLESS_MAIN(QExtHideFunctorTest)

#include <tst_qextHideFunctor.moc>
