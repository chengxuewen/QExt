#include <qexttrackable.h>
#include <qexthidefunctor.h>

#include <QtTest>
#include <QDebug>

class QEXTHideFunctorTest : public QObject
{
    Q_OBJECT
private slots:
    void testSimple();



public:
    static int sm_result;
    static QString sm_string;
};


int QEXTHideFunctorTest::sm_result = 0;
QString QEXTHideFunctorTest::sm_string = "";




struct Foo : public QEXTFunctorBase
{
    // choose a type that can hold all return values
    typedef int ResultType;

    int operator()() {
        QEXTHideFunctorTest::sm_string = "Foo() ";
        return true;
    }

    int operator()(int j) {
        QEXTHideFunctorTest::sm_string = QString("Foo(int %1) ").arg(j);
        return 1 + j;
    }
};

struct FooVoid : public QEXTFunctorBase
{
    typedef void ResultType;

    void operator()() {
        QEXTHideFunctorTest::sm_string = "FooVoid()";
    }
};


void QEXTHideFunctorTest::testSimple()
{
    QEXTHideFunctorTest::sm_string = "";
    QVERIFY(3 == qextHideFunctor<0>(Foo())(1, 2));
    QVERIFY("Foo(int 2) " == QEXTHideFunctorTest::sm_string);

    QEXTHideFunctorTest::sm_string = "";
    QVERIFY(2 == qextHideFunctor<1>(Foo())(1, 2));
    QVERIFY("Foo(int 1) " == QEXTHideFunctorTest::sm_string);

    QEXTHideFunctorTest::sm_string = "";
    QVERIFY(1 == qextHideFunctor<-1>(Foo())(1));
    QVERIFY("Foo() " == QEXTHideFunctorTest::sm_string);

    QEXTHideFunctorTest::sm_string = "";
    QVERIFY(1 == qextHideFunctor(Foo())(1));
    QVERIFY("Foo() " == QEXTHideFunctorTest::sm_string);

    QEXTHideFunctorTest::sm_string = "";
    qextHideFunctor(FooVoid())(1); // void test
    QVERIFY("FooVoid()" == QEXTHideFunctorTest::sm_string);
}


QTEST_APPLESS_MAIN(QEXTHideFunctorTest)

#include <tst_qexthidefunctor.moc>
