#ifndef QEXTPOINTERFUNCTORTEST_H
#define QEXTPOINTERFUNCTORTEST_H

#include <qextPointerFunctor.h>

#include "qextFunctions.h"

#include <iostream>
#include <string>
#include <sstream>

#include <CppUTest/TestHarness.h>

QEXT_USE_NAMESPACE

namespace qextPointerFunctorTest
{

    TEST_GROUP(qextPointerFunctorTest)
    {
    };


    TEST(qextPointerFunctorTest, testFunctorWith0Arg)
    {
        QEXTPointerFunctor<void> voidFunctor = qextPointerFunctor(&voidFunction0);
        voidFunctor();
        CHECK("voidFunction0" == sg_functionString);
        QEXTPointerFunctor<int> intFunctor = qextPointerFunctor(&intFunction0);
        CHECK(0 == intFunctor());
        QEXTPointerFunctor<double> doubleFunctor = qextPointerFunctor(&doubleFunction0);
        CHECK(0 == doubleFunctor());
    }

    TEST(qextPointerFunctorTest, testFunctorWith1Arg)
    {
        QEXTPointerFunctor<void, int> voidFunctor = qextPointerFunctor(&voidFunction1);
        voidFunctor(1);
        CHECK("voidFunction1" == sg_functionString);
        QEXTPointerFunctor<int, int> intFunctor = qextPointerFunctor(&intFunction1);
        CHECK(1 == intFunctor(1));
        QEXTPointerFunctor<double, double> doubleFunctor = qextPointerFunctor(&doubleFunction1);
        CHECK(1.1 == doubleFunctor(1.1));

        QEXTPointerFunctor<void, bool> voidFunctorB = qextPointerFunctor(&voidFunctionB1);
        voidFunctorB(1);
        CHECK("voidFunctionB1" == sg_functionString);
        QEXTPointerFunctor<int, bool> intFunctorB = qextPointerFunctor(&intFunctionB1);
        CHECK(1 == intFunctorB(true));
        CHECK(0 == intFunctorB(false));
        QEXTPointerFunctor<double, bool> doubleFunctorB = qextPointerFunctor(&doubleFunctionB1);
        CHECK(1 == doubleFunctorB(true));
        CHECK(0 == doubleFunctorB(false));

        QEXTPointerFunctor<void, int &> voidFunctorR = qextPointerFunctor(&voidFunctionR1);
        int a1 = 1;
        voidFunctorR(a1);
        CHECK(2 == a1);
    }

    TEST(qextPointerFunctorTest, testFunctorWith2Arg)
    {
        QEXTPointerFunctor<void, int, int> voidFunctor = qextPointerFunctor(&voidFunction2);
        voidFunctor(1, 2);
        CHECK("voidFunction2" == sg_functionString);
        QEXTPointerFunctor<int, int, int> intFunctor = qextPointerFunctor(&intFunction2);
        CHECK(1 + 2 == intFunctor(1, 2));
        QEXTPointerFunctor<double, double, double> doubleFunctor = qextPointerFunctor(&doubleFunction2);
        CHECK(1.1 + 2.2 == doubleFunctor(1.1, 2.2));

        QEXTPointerFunctor<void, bool, int> voidFunctorB = qextPointerFunctor(&voidFunctionB2);
        voidFunctorB(true, 2);
        CHECK("voidFunctionB2" == sg_functionString);
        QEXTPointerFunctor<int, bool, int> intFunctorB = qextPointerFunctor(&intFunctionB2);
        CHECK(2 == intFunctorB(true, 2));
        CHECK(0 == intFunctorB(false, 2));
        QEXTPointerFunctor<double, bool, double> doubleFunctorB = qextPointerFunctor(&doubleFunctionB2);
        CHECK(2.2 == doubleFunctorB(true, 2.2));
        CHECK(0 == doubleFunctorB(false, 2.2));

        QEXTPointerFunctor<void, int &, int &> voidFunctorR = qextPointerFunctor(&voidFunctionR2);
        int a1 = 1;
        int a2 = 2;
        voidFunctorR(a1, a2);
        CHECK(2 == a1);
        CHECK(3 == a2);
    }

    TEST(qextPointerFunctorTest, testFunctorWith3Arg)
    {
        QEXTPointerFunctor<void, int, int, int> voidFunctor = qextPointerFunctor(&voidFunction3);
        voidFunctor(1, 2, 3);
        CHECK("voidFunction3" == sg_functionString);
        QEXTPointerFunctor<int, int, int, int> intFunctor = qextPointerFunctor(&intFunction3);
        CHECK(1 + 2 + 3 == intFunctor(1, 2, 3));
        QEXTPointerFunctor<double, double, double, double> doubleFunctor = qextPointerFunctor(&doubleFunction3);
        CHECK(1.1 + 2.2 + 3.3 == doubleFunctor(1.1, 2.2, 3.3));

        QEXTPointerFunctor<void, bool, int, int> voidFunctorB = qextPointerFunctor(&voidFunctionB3);
        voidFunctorB(true, 2, 3);
        CHECK("voidFunctionB3" == sg_functionString);
        QEXTPointerFunctor<int, bool, int, int> intFunctorB = qextPointerFunctor(&intFunctionB3);
        CHECK(2 + 3 == intFunctorB(true, 2, 3));
        CHECK(2 * 3 == intFunctorB(false, 2, 3));
        QEXTPointerFunctor<double, bool, double, double> doubleFunctorB = qextPointerFunctor(&doubleFunctionB3);
        CHECK(2.2 + 3.3 == doubleFunctorB(true, 2.2, 3.3));
        CHECK(2.2 * 3.3 == doubleFunctorB(false, 2.2, 3.3));

        QEXTPointerFunctor<void, int &, int &, int &> voidFunctorR = qextPointerFunctor(&voidFunctionR3);
        int a1 = 1;
        int a2 = 2;
        int a3 = 3;
        voidFunctorR(a1, a2, a3);
        CHECK(2 == a1);
        CHECK(3 == a2);
        CHECK(4 == a3);
    }

    TEST(qextPointerFunctorTest, testFunctorWith4Arg)
    {
        QEXTPointerFunctor<void, bool, int, int, int> voidFunctorB = qextPointerFunctor(&voidFunctionB4);
        voidFunctorB(1, 2, 3, 4);
        CHECK("voidFunctionB4" == sg_functionString);
        QEXTPointerFunctor<int, bool, int, int, int> intFunctorB = qextPointerFunctor(&intFunctionB4);
        CHECK(2 + 3 + 4 == intFunctorB(true, 2, 3, 4));
        CHECK(2 * 3 * 4 == intFunctorB(false, 2, 3, 4));
        QEXTPointerFunctor<double, bool, double, double, double> doubleFunctorB = qextPointerFunctor(&doubleFunctionB4);
        CHECK(2.2 + 3.3 + 4.4 == doubleFunctorB(true, 2.2, 3.3, 4.4));
        CHECK(2.2 * 3.3 * 4.4 == doubleFunctorB(false, 2.2, 3.3, 4.4));


        QEXTPointerFunctor<void, int, int, int, int> voidFunctor = qextPointerFunctor(&voidFunction4);
        voidFunctor(1, 2, 3, 4);
        CHECK("voidFunction4" == sg_functionString);
        QEXTPointerFunctor<int, int, int, int, int> intFunctor = qextPointerFunctor(&intFunction4);
        CHECK(1 + 2 + 3 + 4 == intFunctor(1, 2, 3, 4));
        QEXTPointerFunctor<double, double, double, double, double> doubleFunctor = qextPointerFunctor(&doubleFunction4);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 == doubleFunctor(1.1, 2.2, 3.3, 4.4));

        QEXTPointerFunctor<void, int &, int &, int &, int &> voidFunctorR = qextPointerFunctor(&voidFunctionR4);
        int a1 = 1;
        int a2 = 2;
        int a3 = 3;
        int a4 = 4;
        voidFunctorR(a1, a2, a3, a4);
        CHECK(2 == a1);
        CHECK(3 == a2);
        CHECK(4 == a3);
        CHECK(5 == a4);
    }

    TEST(qextPointerFunctorTest, testFunctorWith5Arg)
    {
        QEXTPointerFunctor<void, int, int, int, int, int> voidFunctor = qextPointerFunctor(&voidFunction5);
        voidFunctor(1, 2, 3, 4, 5);
        CHECK("voidFunction5" == sg_functionString);
        QEXTPointerFunctor<int, int, int, int, int, int> intFunctor = qextPointerFunctor(&intFunction5);
        CHECK(1 + 2 + 3 + 4 + 5 == intFunctor(1, 2, 3, 4, 5));
        QEXTPointerFunctor<double, double, double, double, double, double> doubleFunctor = qextPointerFunctor(&doubleFunction5);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleFunctor(1.1, 2.2, 3.3, 4.4, 5.5));

        QEXTPointerFunctor<void, bool, int, int, int, int> voidFunctorB = qextPointerFunctor(&voidFunctionB5);
        voidFunctorB(true, 2, 3, 4, 5);
        CHECK("voidFunctionB5" == sg_functionString);
        QEXTPointerFunctor<int, bool, int, int, int, int> intFunctorB = qextPointerFunctor(&intFunctionB5);
        CHECK(2 + 3 + 4 + 5 == intFunctorB(true, 2, 3, 4, 5));
        CHECK(2 * 3 * 4 * 5 == intFunctorB(false, 2, 3, 4, 5));
        QEXTPointerFunctor<double, bool, double, double, double, double> doubleFunctorB = qextPointerFunctor(&doubleFunctionB5);
        CHECK(2.2 + 3.3 + 4.4 + 5.5 == doubleFunctorB(true, 2.2, 3.3, 4.4, 5.5));
        CHECK(2.2 * 3.3 * 4.4 * 5.5 == doubleFunctorB(false, 2.2, 3.3, 4.4, 5.5));

        QEXTPointerFunctor<void, int &, int &, int &, int &, int &> voidFunctorR = qextPointerFunctor(&voidFunctionR5);
        int a1 = 1;
        int a2 = 2;
        int a3 = 3;
        int a4 = 4;
        int a5 = 5;
        voidFunctorR(a1, a2, a3, a4, a5);
        CHECK(2 == a1);
        CHECK(3 == a2);
        CHECK(4 == a3);
        CHECK(5 == a4);
        CHECK(6 == a5);
    }

    TEST(qextPointerFunctorTest, testFunctorWith6Arg)
    {
        QEXTPointerFunctor<void, int, int, int, int, int, int> voidFunctor = qextPointerFunctor(&voidFunction6);
        voidFunctor(1, 2, 3, 4, 5, 6);
        CHECK("voidFunction6" == sg_functionString);
        QEXTPointerFunctor<int, int, int, int, int, int, int> intFunctor = qextPointerFunctor(&intFunction6);
        CHECK(1 + 2 + 3 + 4 + 5 + 6 == intFunctor(1, 2, 3, 4, 5, 6));
        QEXTPointerFunctor<double, double, double, double, double, double, double> doubleFunctor = qextPointerFunctor(&doubleFunction6);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

        QEXTPointerFunctor<void, bool, int, int, int, int, int> voidFunctorB = qextPointerFunctor(&voidFunctionB6);
        voidFunctorB(true, 2, 3, 4, 5, 6);
        CHECK("voidFunctionB6" == sg_functionString);
        QEXTPointerFunctor<int, bool, int, int, int, int, int> intFunctorB = qextPointerFunctor(&intFunctionB6);
        CHECK(2 + 3 + 4 + 5 + 6 == intFunctorB(true, 2, 3, 4, 5, 6));
        CHECK(2 * 3 * 4 * 5 * 6 == intFunctorB(false, 2, 3, 4, 5, 6));
        QEXTPointerFunctor<double, bool, double, double, double, double, double> doubleFunctorB = qextPointerFunctor(&doubleFunctionB6);
        CHECK(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6));
        CHECK(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6));

        QEXTPointerFunctor<void, int &, int &, int &, int &, int &, int &> voidFunctorR = qextPointerFunctor(&voidFunctionR6);
        int a1 = 1;
        int a2 = 2;
        int a3 = 3;
        int a4 = 4;
        int a5 = 5;
        int a6 = 6;
        voidFunctorR(a1, a2, a3, a4, a5, a6);
        CHECK(2 == a1);
        CHECK(3 == a2);
        CHECK(4 == a3);
        CHECK(5 == a4);
        CHECK(6 == a5);
        CHECK(7 == a6);
    }

    TEST(qextPointerFunctorTest, testFunctorWith7Arg)
    {
        QEXTPointerFunctor<void, int, int, int, int, int, int, int> voidFunctor = qextPointerFunctor(&voidFunction7);
        voidFunctor(1, 2, 3, 4, 5, 6, 7);
        CHECK("voidFunction7" == sg_functionString);
        QEXTPointerFunctor<int, int, int, int, int, int, int, int> intFunctor = qextPointerFunctor(&intFunction7);
        CHECK(1 + 2 + 3 + 4 + 5 + 6 + 7 == intFunctor(1, 2, 3, 4, 5, 6, 7));
        QEXTPointerFunctor<double, double, double, double, double, double, double, double> doubleFunctor = qextPointerFunctor(&doubleFunction7);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

        QEXTPointerFunctor<void, bool, int, int, int, int, int, int> voidFunctorB = qextPointerFunctor(&voidFunctionB7);
        voidFunctorB(1, 2, 3, 4, 5, 6, 7);
        CHECK("voidFunctionB7" == sg_functionString);
        QEXTPointerFunctor<int, bool, int, int, int, int, int, int> intFunctorB = qextPointerFunctor(&intFunctionB7);
        CHECK(2 + 3 + 4 + 5 + 6 + 7 == intFunctorB(true, 2, 3, 4, 5, 6, 7));
        CHECK(2 * 3 * 4 * 5 * 6 * 7 == intFunctorB(false, 2, 3, 4, 5, 6, 7));
        QEXTPointerFunctor<double, bool, double, double, double, double, double, double> doubleFunctorB = qextPointerFunctor(&doubleFunctionB7);
        CHECK(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
        CHECK(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));


        QEXTPointerFunctor<void, int &, int &, int &, int &, int &, int &, int &> voidFunctorR = qextPointerFunctor(&voidFunctionR7);
        int a1 = 1;
        int a2 = 2;
        int a3 = 3;
        int a4 = 4;
        int a5 = 5;
        int a6 = 6;
        int a7 = 7;
        voidFunctorR(a1, a2, a3, a4, a5, a6, a7);
        CHECK(2 == a1);
        CHECK(3 == a2);
        CHECK(4 == a3);
        CHECK(5 == a4);
        CHECK(6 == a5);
        CHECK(7 == a6);
        CHECK(8 == a7);
    }

} // namespace qextPointerFunctorTest

#endif // QEXTPOINTERFUNCTORTEST_H
