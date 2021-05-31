#include <qextcomposefunctor.h>
#include <qextpointerfunctor.h>

#include <QtTest>
#include <QDebug>

class QEXTComposeFunctorTest : public QObject
{
    Q_OBJECT
private slots:
    void testCompose1();
    void testCompose2();
    void testCompose3();

public:
    static int sm_result;
    static QString sm_string;
};

int QEXTComposeFunctorTest::sm_result = 0;
QString QEXTComposeFunctorTest::sm_string = "";

struct Set : public QEXTFunctorBase
{
    typedef double ResultType;

    double operator()(int i) {
        QEXTComposeFunctorTest::sm_string += QString("set(int %1) ").arg(i);
        return i*i;
    }

    double operator()(double i) {
        QEXTComposeFunctorTest::sm_string += QString("set(double %1) ").arg(i);
        return i*5;
    }
};

struct SetVoid : public QEXTFunctorBase
{
    typedef void ResultType;

    void operator()(double i) {
        QEXTComposeFunctorTest::sm_string += QString("set_void(double %1)").arg(i);
    }
};

struct Get : public QEXTFunctorBase
{
    typedef double ResultType;

    double operator()() {
        QEXTComposeFunctorTest::sm_string += QString("get() ");
        return true;
    }

    double operator()(int i) {
        QEXTComposeFunctorTest::sm_string += QString("get(%1) ").arg(i);
        return i*2;
    }

    double operator()(int i, int j) {
        QEXTComposeFunctorTest::sm_string += QString("get(%1, %2) ").arg(i).arg(j);
        return double(i)/double(j);
    }
};


void QEXTComposeFunctorTest::testCompose1()
{
    QEXTComposeFunctorTest::sm_string = "";
    QVERIFY(5 == qextComposeFunctor(Set(), Get())());
    QVERIFY("get() set(double 1) " == QEXTComposeFunctorTest::sm_string);

    QEXTComposeFunctorTest::sm_string = "";
    QVERIFY(10 == qextComposeFunctor(Set(), Get())(1));
    QVERIFY("get(1) set(double 2) " == QEXTComposeFunctorTest::sm_string);

    QEXTComposeFunctorTest::sm_string = "";
    QVERIFY(2.5 == qextComposeFunctor(Set(), Get())(1, 2));
    QVERIFY("get(1, 2) set(double 0.5) " == QEXTComposeFunctorTest::sm_string);

    QEXTComposeFunctorTest::sm_string = "";
    qextComposeFunctor(SetVoid(), Get())(3);
    QVERIFY("get(3) set_void(double 6)" == QEXTComposeFunctorTest::sm_string);
}

void QEXTComposeFunctorTest::testCompose2()
{

}

void QEXTComposeFunctorTest::testCompose3()
{

}

QTEST_APPLESS_MAIN(QEXTComposeFunctorTest)

#include <tst_qextcomposefunctor.moc>
