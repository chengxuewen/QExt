#include <qextPointerFunctor.h>

#include "qextFunctions.h"

#include <QtTest>

class QExtPointerFunctorTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void testFunctorWith0Arg();
    void testFunctorWith1Arg();
    void testFunctorWith2Arg();
    void testFunctorWith3Arg();
    void testFunctorWith4Arg();
    void testFunctorWith5Arg();
    void testFunctorWith6Arg();
    void testFunctorWith7Arg();
};

void QExtPointerFunctorTest::testFunctorWith0Arg()
{
    QExtPointerFunctor<void> voidFunctor = qextMakeFunctor(&voidFunction0);
    voidFunctor();
    QVERIFY("voidFunction0" == sg_functionString);
    QExtPointerFunctor<int> intFunctor = qextMakeFunctor(&intFunction0);
    QVERIFY(0 == intFunctor());
    QExtPointerFunctor<double> doubleFunctor = qextMakeFunctor(&doubleFunction0);
    QVERIFY(0 == doubleFunctor());
}

void QExtPointerFunctorTest::testFunctorWith1Arg()
{
    QExtPointerFunctor<void, int> voidFunctor = qextMakeFunctor(&voidFunction1);
    voidFunctor(1);
    QVERIFY("voidFunction1" == sg_functionString);
    QExtPointerFunctor<int, int> intFunctor = qextMakeFunctor(&intFunction1);
    QVERIFY(1 == intFunctor(1));
    QExtPointerFunctor<double, double> doubleFunctor = qextMakeFunctor(&doubleFunction1);
    QVERIFY(1.1 == doubleFunctor(1.1));

    QExtPointerFunctor<void, bool> voidFunctorB = qextMakeFunctor(&voidFunctionB1);
    voidFunctorB(1);
    QVERIFY("voidFunctionB1" == sg_functionString);
    QExtPointerFunctor<int, bool> intFunctorB = qextMakeFunctor(&intFunctionB1);
    QVERIFY(1 == intFunctorB(true));
    QVERIFY(0 == intFunctorB(false));
    QExtPointerFunctor<double, bool> doubleFunctorB = qextMakeFunctor(&doubleFunctionB1);
    QVERIFY(1 == doubleFunctorB(true));
    QVERIFY(0 == doubleFunctorB(false));

    QExtPointerFunctor<void, int &> voidFunctorR = qextMakeFunctor(&voidFunctionR1);
    int a1 = 1;
    voidFunctorR(a1);
    QVERIFY(2 == a1);
}

void QExtPointerFunctorTest::testFunctorWith2Arg()
{
    QExtPointerFunctor<void, int, int> voidFunctor = qextMakeFunctor(&voidFunction2);
    voidFunctor(1, 2);
    QVERIFY("voidFunction2" == sg_functionString);
    QExtPointerFunctor<int, int, int> intFunctor = qextMakeFunctor(&intFunction2);
    QVERIFY(1 + 2 == intFunctor(1, 2));
    QExtPointerFunctor<double, double, double> doubleFunctor = qextMakeFunctor(&doubleFunction2);
    QVERIFY(1.1 + 2.2 == doubleFunctor(1.1, 2.2));

    QExtPointerFunctor<void, bool, int> voidFunctorB = qextMakeFunctor(&voidFunctionB2);
    voidFunctorB(true, 2);
    QVERIFY("voidFunctionB2" == sg_functionString);
    QExtPointerFunctor<int, bool, int> intFunctorB = qextMakeFunctor(&intFunctionB2);
    QVERIFY(2 == intFunctorB(true, 2));
    QVERIFY(0 == intFunctorB(false, 2));
    QExtPointerFunctor<double, bool, double> doubleFunctorB = qextMakeFunctor(&doubleFunctionB2);
    QVERIFY(2.2 == doubleFunctorB(true, 2.2));
    QVERIFY(0 == doubleFunctorB(false, 2.2));

    QExtPointerFunctor<void, int &, int &> voidFunctorR = qextMakeFunctor(&voidFunctionR2);
    int a1 = 1;
    int a2 = 2;
    voidFunctorR(a1, a2);
    QVERIFY(2 == a1);
    QVERIFY(3 == a2);
}

void QExtPointerFunctorTest::testFunctorWith3Arg()
{
    QExtPointerFunctor<void, int, int, int> voidFunctor = qextMakeFunctor(&voidFunction3);
    voidFunctor(1, 2, 3);
    QVERIFY("voidFunction3" == sg_functionString);
    QExtPointerFunctor<int, int, int, int> intFunctor = qextMakeFunctor(&intFunction3);
    QVERIFY(1 + 2 + 3 == intFunctor(1, 2, 3));
    QExtPointerFunctor<double, double, double, double> doubleFunctor = qextMakeFunctor(&doubleFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleFunctor(1.1, 2.2, 3.3));

    QExtPointerFunctor<void, bool, int, int> voidFunctorB = qextMakeFunctor(&voidFunctionB3);
    voidFunctorB(true, 2, 3);
    QVERIFY("voidFunctionB3" == sg_functionString);
    QExtPointerFunctor<int, bool, int, int> intFunctorB = qextMakeFunctor(&intFunctionB3);
    QVERIFY(2 + 3 == intFunctorB(true, 2, 3));
    QVERIFY(2 * 3 == intFunctorB(false, 2, 3));
    QExtPointerFunctor<double, bool, double, double> doubleFunctorB = qextMakeFunctor(&doubleFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleFunctorB(true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleFunctorB(false, 2.2, 3.3));

    QExtPointerFunctor<void, int &, int &, int &> voidFunctorR = qextMakeFunctor(&voidFunctionR3);
    int a1 = 1;
    int a2 = 2;
    int a3 = 3;
    voidFunctorR(a1, a2, a3);
    QVERIFY(2 == a1);
    QVERIFY(3 == a2);
    QVERIFY(4 == a3);
}

void QExtPointerFunctorTest::testFunctorWith4Arg()
{
    QExtPointerFunctor<void, bool, int, int, int> voidFunctorB = qextMakeFunctor(&voidFunctionB4);
    voidFunctorB(1, 2, 3, 4);
    QVERIFY("voidFunctionB4" == sg_functionString);
    QExtPointerFunctor<int, bool, int, int, int> intFunctorB = qextMakeFunctor(&intFunctionB4);
    QVERIFY(2 + 3 + 4 == intFunctorB(true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intFunctorB(false, 2, 3, 4));
    QExtPointerFunctor<double, bool, double, double, double> doubleFunctorB = qextMakeFunctor(&doubleFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleFunctorB(true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleFunctorB(false, 2.2, 3.3, 4.4));


    QExtPointerFunctor<void, int, int, int, int> voidFunctor = qextMakeFunctor(&voidFunction4);
    voidFunctor(1, 2, 3, 4);
    QVERIFY("voidFunction4" == sg_functionString);
    QExtPointerFunctor<int, int, int, int, int> intFunctor = qextMakeFunctor(&intFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intFunctor(1, 2, 3, 4));
    QExtPointerFunctor<double, double, double, double, double> doubleFunctor = qextMakeFunctor(&doubleFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleFunctor(1.1, 2.2, 3.3, 4.4));

    QExtPointerFunctor<void, int &, int &, int &, int &> voidFunctorR = qextMakeFunctor(&voidFunctionR4);
    int a1 = 1;
    int a2 = 2;
    int a3 = 3;
    int a4 = 4;
    voidFunctorR(a1, a2, a3, a4);
    QVERIFY(2 == a1);
    QVERIFY(3 == a2);
    QVERIFY(4 == a3);
    QVERIFY(5 == a4);
}

void QExtPointerFunctorTest::testFunctorWith5Arg()
{
    QExtPointerFunctor<void, int, int, int, int, int> voidFunctor = qextMakeFunctor(&voidFunction5);
    voidFunctor(1, 2, 3, 4, 5);
    QVERIFY("voidFunction5" == sg_functionString);
    QExtPointerFunctor<int, int, int, int, int, int> intFunctor = qextMakeFunctor(&intFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intFunctor(1, 2, 3, 4, 5));
    QExtPointerFunctor<double, double, double, double, double, double> doubleFunctor = qextMakeFunctor(&doubleFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleFunctor(1.1, 2.2, 3.3, 4.4, 5.5));

    QExtPointerFunctor<void, bool, int, int, int, int> voidFunctorB = qextMakeFunctor(&voidFunctionB5);
    voidFunctorB(true, 2, 3, 4, 5);
    QVERIFY("voidFunctionB5" == sg_functionString);
    QExtPointerFunctor<int, bool, int, int, int, int> intFunctorB = qextMakeFunctor(&intFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intFunctorB(true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intFunctorB(false, 2, 3, 4, 5));
    QExtPointerFunctor<double, bool, double, double, double, double> doubleFunctorB = qextMakeFunctor(&doubleFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleFunctorB(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleFunctorB(false, 2.2, 3.3, 4.4, 5.5));

    QExtPointerFunctor<void, int &, int &, int &, int &, int &> voidFunctorR = qextMakeFunctor(&voidFunctionR5);
    int a1 = 1;
    int a2 = 2;
    int a3 = 3;
    int a4 = 4;
    int a5 = 5;
    voidFunctorR(a1, a2, a3, a4, a5);
    QVERIFY(2 == a1);
    QVERIFY(3 == a2);
    QVERIFY(4 == a3);
    QVERIFY(5 == a4);
    QVERIFY(6 == a5);
}

void QExtPointerFunctorTest::testFunctorWith6Arg()
{
    QExtPointerFunctor<void, int, int, int, int, int, int> voidFunctor = qextMakeFunctor(&voidFunction6);
    voidFunctor(1, 2, 3, 4, 5, 6);
    QVERIFY("voidFunction6" == sg_functionString);
    QExtPointerFunctor<int, int, int, int, int, int, int> intFunctor = qextMakeFunctor(&intFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intFunctor(1, 2, 3, 4, 5, 6));
    QExtPointerFunctor<double, double, double, double, double, double, double> doubleFunctor = qextMakeFunctor(&doubleFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QExtPointerFunctor<void, bool, int, int, int, int, int> voidFunctorB = qextMakeFunctor(&voidFunctionB6);
    voidFunctorB(true, 2, 3, 4, 5, 6);
    QVERIFY("voidFunctionB6" == sg_functionString);
    QExtPointerFunctor<int, bool, int, int, int, int, int> intFunctorB = qextMakeFunctor(&intFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intFunctorB(true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intFunctorB(false, 2, 3, 4, 5, 6));
    QExtPointerFunctor<double, bool, double, double, double, double, double> doubleFunctorB = qextMakeFunctor(&doubleFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QExtPointerFunctor<void, int &, int &, int &, int &, int &, int &> voidFunctorR = qextMakeFunctor(&voidFunctionR6);
    int a1 = 1;
    int a2 = 2;
    int a3 = 3;
    int a4 = 4;
    int a5 = 5;
    int a6 = 6;
    voidFunctorR(a1, a2, a3, a4, a5, a6);
    QVERIFY(2 == a1);
    QVERIFY(3 == a2);
    QVERIFY(4 == a3);
    QVERIFY(5 == a4);
    QVERIFY(6 == a5);
    QVERIFY(7 == a6);
}

void QExtPointerFunctorTest::testFunctorWith7Arg()
{
    QExtPointerFunctor<void, int, int, int, int, int, int, int> voidFunctor = qextMakeFunctor(&voidFunction7);
    voidFunctor(1, 2, 3, 4, 5, 6, 7);
    QVERIFY("voidFunction7" == sg_functionString);
    QExtPointerFunctor<int, int, int, int, int, int, int, int> intFunctor = qextMakeFunctor(&intFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intFunctor(1, 2, 3, 4, 5, 6, 7));
    QExtPointerFunctor<double, double, double, double, double, double, double, double> doubleFunctor = qextMakeFunctor(&doubleFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QExtPointerFunctor<void, bool, int, int, int, int, int, int> voidFunctorB = qextMakeFunctor(&voidFunctionB7);
    voidFunctorB(1, 2, 3, 4, 5, 6, 7);
    QVERIFY("voidFunctionB7" == sg_functionString);
    QExtPointerFunctor<int, bool, int, int, int, int, int, int> intFunctorB = qextMakeFunctor(&intFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intFunctorB(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intFunctorB(false, 2, 3, 4, 5, 6, 7));
    QExtPointerFunctor<double, bool, double, double, double, double, double, double> doubleFunctorB = qextMakeFunctor(&doubleFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));


    QExtPointerFunctor<void, int &, int &, int &, int &, int &, int &, int &> voidFunctorR = qextMakeFunctor(&voidFunctionR7);
    int a1 = 1;
    int a2 = 2;
    int a3 = 3;
    int a4 = 4;
    int a5 = 5;
    int a6 = 6;
    int a7 = 7;
    voidFunctorR(a1, a2, a3, a4, a5, a6, a7);
    QVERIFY(2 == a1);
    QVERIFY(3 == a2);
    QVERIFY(4 == a3);
    QVERIFY(5 == a4);
    QVERIFY(6 == a5);
    QVERIFY(7 == a6);
    QVERIFY(8 == a7);
}


QTEST_APPLESS_MAIN(QExtPointerFunctorTest)

#include <tst_qextPointerFunctor.moc>
