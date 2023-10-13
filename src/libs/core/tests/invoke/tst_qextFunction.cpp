#include <qextBindFunctor.h>
#include <qextFunction.h>
#include <qextGlobal.h>
#include <qextMemberFunctor.h>
#include <qextPointerFunctor.h>
#include <qextFunction.h>

#include "qextFunctions.h"
#include "qextMember.h"

#include <QtTest>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

#if QEXT_CC_STD_11
#include <functional>
#endif

static QString *sg_string = QEXT_DECL_NULLPTR;

class MFunctor
{
public:
    MFunctor() {}

    void operator()()
    {
        *sg_string = "MFunctor::voidFunction0";
    }
    void operator()(int a1)
    {
        Q_UNUSED(a1)
        *sg_string = "MFunctor::voidFunction1";
    }
    void operator()(int a1, int a2)
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        *sg_string = "MFunctor::voidFunction2";
    }
    void operator()(int a1, int a2, int a3)
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        *sg_string = "MFunctor::voidFunction3";
    }
    void operator()(int a1, int a2, int a3, int a4)
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        *sg_string = "MFunctor::voidFunction4";
    }
    void operator()(int a1, int a2, int a3, int a4, int a5)
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        *sg_string = "MFunctor::voidFunction5";
    }
    void operator()(int a1, int a2, int a3, int a4, int a5, int a6)
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        *sg_string = "MFunctor::voidFunction6";
    }
    void operator()(int a1, int a2, int a3, int a4, int a5, int a6, int a7)
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        Q_UNUSED(a7)
        *sg_string = "MFunctor::voidFunction7";
    }
    void operator()(bool a1)
    {
        Q_UNUSED(a1)
        *sg_string = "MFunctor::voidFunctionB1";
    }
    void operator()(bool a1, int a2)
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        *sg_string = "MFunctor::voidFunctionB2";
    }
    void operator()(bool a1, int a2, int a3)
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        *sg_string = "MFunctor::voidFunctionB3";
    }
    void operator()(bool a1, int a2, int a3, int a4)
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        *sg_string = "MFunctor::voidFunctionB4";
    }
    void operator()(bool a1, int a2, int a3, int a4, int a5)
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        *sg_string = "MFunctor::voidFunctionB5";
    }
    void operator()(bool a1, int a2, int a3, int a4, int a5, int a6)
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        *sg_string = "MFunctor::voidFunctionB6";
    }
    void operator()(bool a1, int a2, int a3, int a4, int a5, int a6, int a7)
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        Q_UNUSED(a7)
        *sg_string = "MFunctor::voidFunctionB7";
    }
};


class QExtFunctionTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void functor();
    void stdFunction();
    void retIntFunctor();
    void stdRetIntFunction();
    void retDoubleFunctor();
    void constFunctor();
    void retIntConstFunctor();
    void retDoubleConstFunctor();
    void retVolatileFunctor();
    void retIntVolatileFunctor();
    void retDoubleVolatileFunctor();
    void retConstVolatileFunctor();
    void retIntConstVolatileFunctor();
    void retDoubleConstVolatileFunctor();
    void pointerFunctorWith0Arg();
    void pointerFunctorWith1Arg();
    void testFunctorWith2Arg();
    void testFunctorWith3Arg();
    void testFunctorWith4Arg();
    void testFunctorWith5Arg();
    void testFunctorWith6Arg();
    void pointerFunctorWith7Arg();
    void testBoundFunctorWith0Arg();
    void testPolymorphismBoundFunctorWith0Arg();
    void testBoundConstFunctorWith0Arg();
    void testPolymorphismBoundConstFunctorWith0Arg();
    void testBoundVolatileFunctorWith0Arg();
    void testPolymorphismBoundVolatileFunctorWith0Arg();
    void testBoundConstVolatileFunctorWith0Arg();
    void testPolymorphismBoundConstVolatileFunctorWith0Arg();
    void testBoundFunctorWith1Arg();
    void testPolymorphismBoundFunctorWith1Arg();
    void testBoundConstFunctorWith1Arg();
    void testPolymorphismBoundConstFunctorWith1Arg();
    void testBoundVolatileFunctorWith1Arg();
    void testPolymorphismBoundVolatileFunctorWith1Arg();
    void testBoundConstVolatileFunctorWith1Arg();
    void testPolymorphismBoundConstVolatileFunctorWith1Arg();
    void testBoundFunctorWith2Arg();
    void testPolymorphismBoundFunctorWith2Arg();
    void testBoundConstFunctorWith2Arg();
    void testPolymorphismBoundConstFunctorWith2Arg();
    void testBoundVolatileFunctorWith2Arg();
    void testPolymorphismBoundVolatileFunctorWith2Arg();
    void testBoundConstVolatileFunctorWith2Arg();
    void testPolymorphismBoundConstVolatileFunctorWith2Arg();
    void testBoundFunctorWith3Arg();
    void testPolymorphismBoundFunctorWith3Arg();
    void testBoundConstFunctorWith3Arg();
    void testPolymorphismBoundConstFunctorWith3Arg();
    void testBoundVolatileFunctorWith3Arg();
    void testPolymorphismBoundVolatileFunctorWith3Arg();
    void testBoundConstVolatileFunctorWith3Arg();
    void testPolymorphismBoundConstVolatileFunctorWith3Arg();
    void testBoundFunctorWith4Arg();
    void testPolymorphismBoundFunctorWith4Arg();
    void testBoundConstFunctorWith4Arg();
    void testPolymorphismBoundConstFunctorWith4Arg();
    void testBoundVolatileFunctorWith4Arg();
    void testPolymorphismBoundVolatileFunctorWith4Arg();
    void testBoundConstVolatileFunctorWith4Arg();
    void testPolymorphismBoundConstVolatileFunctorWith4Arg();
    void testBoundFunctorWith5Arg();
    void testPolymorphismBoundFunctorWith5Arg();
    void testBoundConstFunctorWith5Arg();
    void testPolymorphismBoundConstFunctorWith5Arg();
    void testBoundVolatileFunctorWith5Arg();
    void testPolymorphismBoundVolatileFunctorWith5Arg();
    void testBoundConstVolatileFunctorWith5Arg();
    void testPolymorphismBoundConstVolatileFunctorWith5Arg();
    void testBoundFunctorWith6Arg();
    void testPolymorphismBoundFunctorWith6Arg();
    void testBoundConstFunctorWith6Arg();
    void testPolymorphismBoundConstFunctorWith6Arg();
    void testBoundVolatileFunctorWith6Arg();
    void testPolymorphismBoundVolatileFunctorWith6Arg();
    void testBoundConstVolatileFunctorWith6Arg();
    void testPolymorphismBoundConstVolatileFunctorWith6Arg();
    void testBoundFunctorWith7Arg();
    void testPolymorphismBoundFunctorWith7Arg();
    void testBoundConstFunctorWith7Arg();
    void testPolymorphismBoundConstFunctorWith7Arg();
    void testBoundVolatileFunctorWith7Arg();
    void testPolymorphismBoundVolatileFunctorWith7Arg();
    void testBoundConstVolatileFunctorWith7Arg();
    void testPolymorphismBoundConstVolatileFunctorWith7Arg();

};



void QExtFunctionTest::functor()
{
    QString string;
    sg_string = &string;
    MFunctor mFunctor;

    QExtFunction< void > voidFunctorArg0(mFunctor);
    voidFunctorArg0();
    QVERIFY("MFunctor::voidFunction0" == string);
    QExtFunction< void, int > voidFunctorArg1(mFunctor);
    voidFunctorArg1(1);
    QVERIFY("MFunctor::voidFunction1" == string);
    QExtFunction< void, int, int > voidFunctorArg2(mFunctor);
    voidFunctorArg2(1, 2);
    QVERIFY("MFunctor::voidFunction2" == string);
    QExtFunction< void, int, int, int > voidFunctorArg3(mFunctor);
    voidFunctorArg3(1, 2, 3);
    QVERIFY("MFunctor::voidFunction3" == string);
    QExtFunction< void, int, int, int, int > voidFunctorArg4(mFunctor);
    voidFunctorArg4(1, 2, 3, 4);
    QVERIFY("MFunctor::voidFunction4" == string);
    QExtFunction< void, int, int, int, int, int > voidFunctorArg5(mFunctor);
    voidFunctorArg5(1, 2, 3, 4, 5);
    QVERIFY("MFunctor::voidFunction5" == string);
    QExtFunction< void, int, int, int, int, int, int > voidFunctorArg6(mFunctor);
    voidFunctorArg6(1, 2, 3, 4, 5, 6);
    QVERIFY("MFunctor::voidFunction6" == string);
    QExtFunction< void, int, int, int, int, int, int, int > voidFunctorArg7(mFunctor);
    voidFunctorArg7(1, 2, 3, 4, 5, 6, 7);
    QVERIFY("MFunctor::voidFunction7" == string);

    QExtFunction< void, bool > voidFunctorBArg1(mFunctor);
    voidFunctorBArg1(true);
    QVERIFY("MFunctor::voidFunctionB1" == string);
    QExtFunction< void, bool, int > voidFunctorBArg2(mFunctor);
    voidFunctorBArg2(true, 2);
    QVERIFY("MFunctor::voidFunctionB2" == string);
    QExtFunction< void, bool, int, int > voidFunctorBArg3(mFunctor);
    voidFunctorBArg3(true, 2, 3);
    QVERIFY("MFunctor::voidFunctionB3" == string);
    QExtFunction< void, bool, int, int, int > voidFunctorBArg4(mFunctor);
    voidFunctorBArg4(true, 2, 3, 4);
    QVERIFY("MFunctor::voidFunctionB4" == string);
    QExtFunction< void, bool, int, int, int, int > voidFunctorBArg5(mFunctor);
    voidFunctorBArg5(true, 2, 3, 4, 5);
    QVERIFY("MFunctor::voidFunctionB5" == string);
    QExtFunction< void, bool, int, int, int, int, int > voidFunctorBArg6(mFunctor);
    voidFunctorBArg6(true, 2, 3, 4, 5, 6);
    QVERIFY("MFunctor::voidFunctionB6" == string);
    QExtFunction< void, bool, int, int, int, int, int, int > voidFunctorBArg7(mFunctor);
    voidFunctorBArg7(true, 2, 3, 4, 5, 6, 7);
    QVERIFY("MFunctor::voidFunctionB7" == string);
}

void QExtFunctionTest::stdFunction()
{
#if QEXT_CC_STD_11
    QString string;
    sg_string = &string;

    /*lambda*/
    QExtFunction< void > voidFunctorArg0([=](){ *sg_string = "lambda::voidFunction0"; });
    voidFunctorArg0();
    QVERIFY("lambda::voidFunction0" == string);
    QExtFunction< void, int > voidFunctorArg1([=](int){ *sg_string = "lambda::voidFunction1"; });
    voidFunctorArg1(1);
    QVERIFY("lambda::voidFunction1" == string);
    QExtFunction< void, int, int > voidFunctorArg2([=](int, int){ *sg_string = "lambda::voidFunction2"; });
    voidFunctorArg2(1, 2);
    QVERIFY("lambda::voidFunction2" == string);
    QExtFunction< void, int, int, int > voidFunctorArg3([=](int, int, int){ *sg_string = "lambda::voidFunction3"; });
    voidFunctorArg3(1, 2, 3);
    QVERIFY("lambda::voidFunction3" == string);
    QExtFunction< void, int, int, int, int > voidFunctorArg4([=](int, int, int, int){ *sg_string = "lambda::voidFunction4"; });
    voidFunctorArg4(1, 2, 3, 4);
    QVERIFY("lambda::voidFunction4" == string);
    QExtFunction< void, int, int, int, int, int > voidFunctorArg5([=](int, int, int, int, int){ *sg_string = "lambda::voidFunction5"; });
    voidFunctorArg5(1, 2, 3, 4, 5);
    QVERIFY("lambda::voidFunction5" == string);
    QExtFunction< void, int, int, int, int, int, int > voidFunctorArg6([=](int, int, int, int, int, int){ *sg_string = "lambda::voidFunction6"; });
    voidFunctorArg6(1, 2, 3, 4, 5, 6);
    QVERIFY("lambda::voidFunction6" == string);
    QExtFunction< void, int, int, int, int, int, int, int > voidFunctorArg7([=](int, int, int, int, int, int, int){ *sg_string = "lambda::voidFunction7"; });
    voidFunctorArg7(1, 2, 3, 4, 5, 6, 7);
    QVERIFY("lambda::voidFunction7" == string);

    MFunctor mFunctor;

    QExtFunction< void, bool > voidFunctorBArg1 = std::function<void(bool)>(mFunctor);
    voidFunctorBArg1(true);
    QVERIFY("MFunctor::voidFunctionB1" == string);
    QExtFunction< void, bool, int > voidFunctorBArg2 = std::function<void(bool, int)>(mFunctor);
    voidFunctorBArg2(true, 2);
    QVERIFY("MFunctor::voidFunctionB2" == string);
    QExtFunction< void, bool, int, int > voidFunctorBArg3 = std::function<void(bool, int, int)>(mFunctor);
    voidFunctorBArg3(true, 2, 3);
    QVERIFY("MFunctor::voidFunctionB3" == string);
    QExtFunction< void, bool, int, int, int > voidFunctorBArg4 = std::function<void(bool, int, int, int)>(mFunctor);
    voidFunctorBArg4(true, 2, 3, 4);
    QVERIFY("MFunctor::voidFunctionB4" == string);
    QExtFunction< void, bool, int, int, int, int > voidFunctorBArg5 = std::function<void(bool, int, int, int, int)>(mFunctor);
    voidFunctorBArg5(true, 2, 3, 4, 5);
    QVERIFY("MFunctor::voidFunctionB5" == string);
    QExtFunction< void, bool, int, int, int, int, int > voidFunctorBArg6 = std::function<void(bool, int, int, int, int, int)>(mFunctor);
    voidFunctorBArg6(true, 2, 3, 4, 5, 6);
    QVERIFY("MFunctor::voidFunctionB6" == string);
    QExtFunction< void, bool, int, int, int, int, int, int > voidFunctorBArg7 = std::function<void(bool, int, int, int, int, int, int)>(mFunctor);
    voidFunctorBArg7(true, 2, 3, 4, 5, 6, 7);
    QVERIFY("MFunctor::voidFunctionB7" == string);
#endif
}

class MRetIntFunctor : public QExtFunctorBase
{
public:
    typedef int Return;
    typedef MRetIntFunctor Object;

    MRetIntFunctor() {}

    int operator()()
    {
        *sg_string = "MRetIntFunctor::intFunction0";
        return 0;
    }
    int operator()(int a1)
    {
        return a1;
    }
    int operator()(int a1, int a2)
    {
        return a1 + a2;
    }
    int operator()(int a1, int a2, int a3)
    {
        return a1 + a2 + a3;
    }
    int operator()(int a1, int a2, int a3, int a4)
    {
        return a1 + a2 + a3 + a4;
    }
    int operator()(int a1, int a2, int a3, int a4, int a5)
    {
        return a1 + a2 + a3 + a4 + a5;
    }
    int operator()(int a1, int a2, int a3, int a4, int a5, int a6)
    {
        return a1 + a2 + a3 + a4 + a5 + a6;
    }
    int operator()(int a1, int a2, int a3, int a4, int a5, int a6, int a7)
    {
        return a1 + a2 + a3 + a4 + a5 + a6 + a7;
    }
    int operator()(bool a1)
    {
        return a1;
    }
    int operator()(bool a1, int a2)
    {
        return a1 ? a2 : 0;
    }
    int operator()(bool a1, int a2, int a3)
    {
        return a1 ? (a2 + a3) : (a2 * a3);
    }
    int operator()(bool a1, int a2, int a3, int a4)
    {
        return a1 ? (a2 + a3 + a4) : (a2 * a3 * a4);
    }
    int operator()(bool a1, int a2, int a3, int a4, int a5)
    {
        return a1 ? (a2 + a3 + a4 + a5) : (a2 * a3 * a4 * a5);
    }
    int operator()(bool a1, int a2, int a3, int a4, int a5, int a6)
    {
        return a1 ? (a2 + a3 + a4 + a5 + a6) : (a2 * a3 * a4 * a5 * a6);
    }
    int operator()(bool a1, int a2, int a3, int a4, int a5, int a6, int a7)
    {
        return a1 ? (a2 + a3 + a4 + a5 + a6 + a7) : (a2 * a3 * a4 * a5 * a6 * a7);
    }
};


void QExtFunctionTest::retIntFunctor()
{
    QString string;
    sg_string = &string;
    MRetIntFunctor mFunctor;

    QExtFunction< int > intFunctorArg0(mFunctor);
    intFunctorArg0();
    QVERIFY("MRetIntFunctor::intFunction0" == string);
    QExtFunction< int, int > intFunctorArg1(mFunctor);
    QVERIFY(1 == intFunctorArg1(1));
    QExtFunction< int, int, int > intFunctorArg2(mFunctor);
    QVERIFY(3 == intFunctorArg2(1, 2));
    QExtFunction< int, int, int, int > intFunctorArg3(mFunctor);
    QVERIFY(6 == intFunctorArg3(1, 2, 3));
    QExtFunction< int, int, int, int, int > intFunctorArg4(mFunctor);
    QVERIFY(10 == intFunctorArg4(1, 2, 3, 4));
    QExtFunction< int, int, int, int, int, int > intFunctorArg5(mFunctor);
    QVERIFY(15 == intFunctorArg5(1, 2, 3, 4, 5));
    QExtFunction< int, int, int, int, int, int, int > intFunctorArg6(mFunctor);
    QVERIFY(21 == intFunctorArg6(1, 2, 3, 4, 5, 6));
    QExtFunction< int, int, int, int, int, int, int, int > intFunctorArg7(mFunctor);
    QVERIFY(28 == intFunctorArg7(1, 2, 3, 4, 5, 6, 7));

    QExtFunction< int, bool > intFunctorBArg1(mFunctor);
    QVERIFY(1 == intFunctorBArg1(true));
    QVERIFY(0 == intFunctorBArg1(false));
    QExtFunction< int, bool, int > intFunctorBArg2(mFunctor);
    QVERIFY(2 == intFunctorBArg2(true, 2));
    QVERIFY(0 == intFunctorBArg2(false, 2));
    QExtFunction< int, bool, int, int > intFunctorBArg3(mFunctor);
    QVERIFY(5 == intFunctorBArg3(true, 2, 3));
    QVERIFY(6 == intFunctorBArg3(false, 2, 3));
    QExtFunction< int, bool, int, int, int > intFunctorBArg4(mFunctor);
    QVERIFY(9 == intFunctorBArg4(true, 2, 3, 4));
    QVERIFY(24 == intFunctorBArg4(false, 2, 3, 4));
    QExtFunction< int, bool, int, int, int, int > intFunctorBArg5(mFunctor);
    QVERIFY(14 == intFunctorBArg5(true, 2, 3, 4, 5));
    QVERIFY(120 == intFunctorBArg5(false, 2, 3, 4, 5));
    QExtFunction< int, bool, int, int, int, int, int > intFunctorBArg6(mFunctor);
    QVERIFY(20 == intFunctorBArg6(true, 2, 3, 4, 5, 6));
    QVERIFY(720 == intFunctorBArg6(false, 2, 3, 4, 5, 6));
    QExtFunction< int, bool, int, int, int, int, int, int > intFunctorBArg7(mFunctor);
    QVERIFY(27 == intFunctorBArg7(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(5040 == intFunctorBArg7(false, 2, 3, 4, 5, 6, 7));
}

void QExtFunctionTest::stdRetIntFunction()
{
#if QEXT_CC_STD_11
    QString string;
    sg_string = &string;

    QExtFunction< int > intFunctorArg0 = []() -> int { *sg_string = "lambda::intFunction0"; return 0; };
    intFunctorArg0();
    QVERIFY("lambda::intFunction0" == string);
    QExtFunction< int, int > intFunctorArg1 = [](int a1) -> int { return a1; };
    QVERIFY(1 == intFunctorArg1(1));
    QExtFunction< int, int, int > intFunctorArg2 = [](int a1, int a2) -> int { return a1 + a2; };
    QVERIFY(3 == intFunctorArg2(1, 2));
    QExtFunction< int, int, int, int > intFunctorArg3 = [](int a1, int a2, int a3) -> int { return a1 + a2 + a3; };
    QVERIFY(6 == intFunctorArg3(1, 2, 3));
    QExtFunction< int, int, int, int, int > intFunctorArg4 = [](int a1, int a2, int a3, int a4) -> int { return a1 + a2 + a3 + a4; };
    QVERIFY(10 == intFunctorArg4(1, 2, 3, 4));
    QExtFunction< int, int, int, int, int, int > intFunctorArg5 = [](int a1, int a2, int a3, int a4, int a5) -> int { return a1 + a2 + a3 + a4 + a5; };
    QVERIFY(15 == intFunctorArg5(1, 2, 3, 4, 5));
    QExtFunction< int, int, int, int, int, int, int > intFunctorArg6 = [](int a1, int a2, int a3, int a4, int a5, int a6) -> int { return a1 + a2 + a3 + a4 + a5 + a6; };
    QVERIFY(21 == intFunctorArg6(1, 2, 3, 4, 5, 6));
    QExtFunction< int, int, int, int, int, int, int, int > intFunctorArg7 = [](int a1, int a2, int a3, int a4, int a5, int a6, int a7) -> int { return a1 + a2 + a3 + a4 + a5 + a6 + a7; };
    QVERIFY(28 == intFunctorArg7(1, 2, 3, 4, 5, 6, 7));

    MRetIntFunctor mFunctor;

    QExtFunction< int, bool > intFunctorBArg1 = std::function<int(bool)>(mFunctor);
    QVERIFY(1 == intFunctorBArg1(true));
    QVERIFY(0 == intFunctorBArg1(false));
    QExtFunction< int, bool, int > intFunctorBArg2 = std::function<int(bool, int)>(mFunctor);
    QVERIFY(2 == intFunctorBArg2(true, 2));
    QVERIFY(0 == intFunctorBArg2(false, 2));
    QExtFunction< int, bool, int, int > intFunctorBArg3 = std::function<int(bool, int, int)>(mFunctor);
    QVERIFY(5 == intFunctorBArg3(true, 2, 3));
    QVERIFY(6 == intFunctorBArg3(false, 2, 3));
    QExtFunction< int, bool, int, int, int > intFunctorBArg4 = std::function<int(bool, int, int, int)>(mFunctor);
    QVERIFY(9 == intFunctorBArg4(true, 2, 3, 4));
    QVERIFY(24 == intFunctorBArg4(false, 2, 3, 4));
    QExtFunction< int, bool, int, int, int, int > intFunctorBArg5 = std::function<int(bool, int, int, int, int)>(mFunctor);
    QVERIFY(14 == intFunctorBArg5(true, 2, 3, 4, 5));
    QVERIFY(120 == intFunctorBArg5(false, 2, 3, 4, 5));
    QExtFunction< int, bool, int, int, int, int, int > intFunctorBArg6 = std::function<int(bool, int, int, int, int, int)>(mFunctor);
    QVERIFY(20 == intFunctorBArg6(true, 2, 3, 4, 5, 6));
    QVERIFY(720 == intFunctorBArg6(false, 2, 3, 4, 5, 6));
    QExtFunction< int, bool, int, int, int, int, int, int > intFunctorBArg7 = std::function<int(bool, int, int, int, int, int, int)>(mFunctor);
    QVERIFY(27 == intFunctorBArg7(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(5040 == intFunctorBArg7(false, 2, 3, 4, 5, 6, 7));
#endif
}

class MRetDoubleFunctor : public QExtFunctorBase
{
public:
    typedef double Return;
    typedef MRetDoubleFunctor Object;
    MRetDoubleFunctor() {}

    double operator()()
    {
        *sg_string = "MRetDoubleFunctor::doubleFunction0";
        return 0;
    }
    double operator()(double a1)
    {
        return a1;
    }
    double operator()(double a1, double a2)
    {
        return a1 + a2;
    }
    double operator()(double a1, double a2, double a3)
    {
        return a1 + a2 + a3;
    }
    double operator()(double a1, double a2, double a3, double a4)
    {
        return a1 + a2 + a3 + a4;
    }
    double operator()(double a1, double a2, double a3, double a4, double a5)
    {
        return a1 + a2 + a3 + a4 + a5;
    }
    double operator()(double a1, double a2, double a3, double a4, double a5, double a6)
    {
        return a1 + a2 + a3 + a4 + a5 + a6;
    }
    double operator()(double a1, double a2, double a3, double a4, double a5, double a6, double a7)
    {
        return a1 + a2 + a3 + a4 + a5 + a6 + a7;
    }
    double operator()(bool a1)
    {
        return a1;
    }
    double operator()(bool a1, double a2)
    {
        return a1 ? a2 : 0;
    }
    double operator()(bool a1, double a2, double a3)
    {
        return a1 ? (a2 + a3) : (a2 * a3);
    }
    double operator()(bool a1, double a2, double a3, double a4)
    {
        return a1 ? (a2 + a3 + a4) : (a2 * a3 * a4);
    }
    double operator()(bool a1, double a2, double a3, double a4, double a5)
    {
        return a1 ? (a2 + a3 + a4 + a5) : (a2 * a3 * a4 * a5);
    }
    double operator()(bool a1, double a2, double a3, double a4, double a5, double a6)
    {
        return a1 ? (a2 + a3 + a4 + a5 + a6) : (a2 * a3 * a4 * a5 * a6);
    }
    double operator()(bool a1, double a2, double a3, double a4, double a5, double a6, double a7)
    {
        return a1 ? (a2 + a3 + a4 + a5 + a6 + a7) : (a2 * a3 * a4 * a5 * a6 * a7);
    }
};

void QExtFunctionTest::retDoubleFunctor()
{
    QString string;
    sg_string = &string;
    MRetDoubleFunctor mFunctor;

    QExtFunction< double > doubleFunctorArg0(mFunctor);
    doubleFunctorArg0();
    QVERIFY("MRetDoubleFunctor::doubleFunction0" == string);
    QExtFunction< double, double > doubleFunctorArg1(mFunctor);
    QVERIFY(1 == doubleFunctorArg1(1));
    QExtFunction< double, double, double > doubleFunctorArg2(mFunctor);
    QVERIFY(3 == doubleFunctorArg2(1, 2));
    QExtFunction< double, double, double, double > doubleFunctorArg3(mFunctor);
    QVERIFY(6 == doubleFunctorArg3(1, 2, 3));
    QExtFunction< double, double, double, double, double > doubleFunctorArg4(mFunctor);
    QVERIFY(10 == doubleFunctorArg4(1, 2, 3, 4));
    QExtFunction< double, double, double, double, double, double > doubleFunctorArg5(mFunctor);
    QVERIFY(15 == doubleFunctorArg5(1, 2, 3, 4, 5));
    QExtFunction< double, double, double, double, double, double, double > doubleFunctorArg6(mFunctor);
    QVERIFY(21 == doubleFunctorArg6(1, 2, 3, 4, 5, 6));
    QExtFunction< double, double, double, double, double, double, double, double > doubleFunctorArg7(mFunctor);
    QVERIFY(28 == doubleFunctorArg7(1, 2, 3, 4, 5, 6, 7));

    QExtFunction< double, bool > voidFunctorBArg1(mFunctor);
    QVERIFY(1 == voidFunctorBArg1(true));
    QVERIFY(0 == voidFunctorBArg1(false));
    QExtFunction< double, bool, double > voidFunctorBArg2(mFunctor);
    QVERIFY(2 == voidFunctorBArg2(true, 2));
    QVERIFY(0 == voidFunctorBArg2(false, 2));
    QExtFunction< double, bool, double, double > voidFunctorBArg3(mFunctor);
    QVERIFY(5 == voidFunctorBArg3(true, 2, 3));
    QVERIFY(6 == voidFunctorBArg3(false, 2, 3));
    QExtFunction< double, bool, double, double, double > voidFunctorBArg4(mFunctor);
    QVERIFY(9 == voidFunctorBArg4(true, 2, 3, 4));
    QVERIFY(24 == voidFunctorBArg4(false, 2, 3, 4));
    QExtFunction< double, bool, double, double, double, double > voidFunctorBArg5(mFunctor);
    QVERIFY(14 == voidFunctorBArg5(true, 2, 3, 4, 5));
    QVERIFY(120 == voidFunctorBArg5(false, 2, 3, 4, 5));
    QExtFunction< double, bool, double, double, double, double, double > voidFunctorBArg6(mFunctor);
    QVERIFY(20 == voidFunctorBArg6(true, 2, 3, 4, 5, 6));
    QVERIFY(720 == voidFunctorBArg6(false, 2, 3, 4, 5, 6));
    QExtFunction< double, bool, double, double, double, double, double, double > voidFunctorBArg7(mFunctor);
    QVERIFY(27 == voidFunctorBArg7(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(5040 == voidFunctorBArg7(false, 2, 3, 4, 5, 6, 7));
}

class MConstFunctor
{
public:
    MConstFunctor() {}

    // const function
    void operator()() const
    {
        *sg_string = "MConstFunctor::voidConstFunction0";
    }
    void operator()(int a1) const
    {
        Q_UNUSED(a1)
        *sg_string = "MConstFunctor::voidConstFunction1";
    }
    void operator()(int a1, int a2) const
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        *sg_string = "MConstFunctor::voidConstFunction2";
    }
    void operator()(int a1, int a2, int a3) const
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        *sg_string = "MConstFunctor::voidConstFunction3";
    }
    void operator()(int a1, int a2, int a3, int a4) const
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        *sg_string = "MConstFunctor::voidConstFunction4";
    }
    void operator()(int a1, int a2, int a3, int a4, int a5) const
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        *sg_string = "MConstFunctor::voidConstFunction5";
    }
    void operator()(int a1, int a2, int a3, int a4, int a5, int a6) const
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        *sg_string = "MConstFunctor::voidConstFunction6";
    }
    void operator()(int a1, int a2, int a3, int a4, int a5, int a6, int a7) const
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        Q_UNUSED(a7)
        *sg_string = "MConstFunctor::voidConstFunction7";
    }
    void operator()(bool a1) const
    {
        Q_UNUSED(a1)
        *sg_string = "MConstFunctor::voidConstFunctionB1";
    }
    void operator()(bool a1, int a2) const
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        *sg_string = "MConstFunctor::voidConstFunctionB2";
    }
    void operator()(bool a1, int a2, int a3) const
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        *sg_string = "MConstFunctor::voidConstFunctionB3";
    }
    void operator()(bool a1, int a2, int a3, int a4) const
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        *sg_string = "MConstFunctor::voidConstFunctionB4";
    }
    void operator()(bool a1, int a2, int a3, int a4, int a5) const
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        *sg_string = "MConstFunctor::voidConstFunctionB5";
    }
    void operator()(bool a1, int a2, int a3, int a4, int a5, int a6) const
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        *sg_string = "MConstFunctor::voidConstFunctionB6";
    }
    void operator()(bool a1, int a2, int a3, int a4, int a5, int a6, int a7) const
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        Q_UNUSED(a7)
        *sg_string = "MConstFunctor::voidConstFunctionB7";
    }
};

void QExtFunctionTest::constFunctor()
{
    QString string;
    sg_string = &string;
    MConstFunctor mFunctor;

    QExtFunction< void > voidFunctorArg0(mFunctor);
    voidFunctorArg0();
    QVERIFY("MConstFunctor::voidConstFunction0" == string);
    QExtFunction< void, int > voidFunctorArg1(mFunctor);
    voidFunctorArg1(1);
    QVERIFY("MConstFunctor::voidConstFunction1" == string);
    QExtFunction< void, int, int > voidFunctorArg2(mFunctor);
    voidFunctorArg2(1, 2);
    QVERIFY("MConstFunctor::voidConstFunction2" == string);
    QExtFunction< void, int, int, int > voidFunctorArg3(mFunctor);
    voidFunctorArg3(1, 2, 3);
    QVERIFY("MConstFunctor::voidConstFunction3" == string);
    QExtFunction< void, int, int, int, int > voidFunctorArg4(mFunctor);
    voidFunctorArg4(1, 2, 3, 4);
    QVERIFY("MConstFunctor::voidConstFunction4" == string);
    QExtFunction< void, int, int, int, int, int > voidFunctorArg5(mFunctor);
    voidFunctorArg5(1, 2, 3, 4, 5);
    QVERIFY("MConstFunctor::voidConstFunction5" == string);
    QExtFunction< void, int, int, int, int, int, int > voidFunctorArg6(mFunctor);
    voidFunctorArg6(1, 2, 3, 4, 5, 6);
    QVERIFY("MConstFunctor::voidConstFunction6" == string);
    QExtFunction< void, int, int, int, int, int, int, int > voidFunctorArg7(mFunctor);
    voidFunctorArg7(1, 2, 3, 4, 5, 6, 7);
    QVERIFY("MConstFunctor::voidConstFunction7" == string);

    QExtFunction< void, bool > voidFunctorBArg1(mFunctor);
    voidFunctorBArg1(true);
    QVERIFY("MConstFunctor::voidConstFunctionB1" == string);
    QExtFunction< void, bool, int > voidFunctorBArg2(mFunctor);
    voidFunctorBArg2(true, 2);
    QVERIFY("MConstFunctor::voidConstFunctionB2" == string);
    QExtFunction< void, bool, int, int > voidFunctorBArg3(mFunctor);
    voidFunctorBArg3(true, 2, 3);
    QVERIFY("MConstFunctor::voidConstFunctionB3" == string);
    QExtFunction< void, bool, int, int, int > voidFunctorBArg4(mFunctor);
    voidFunctorBArg4(true, 2, 3, 4);
    QVERIFY("MConstFunctor::voidConstFunctionB4" == string);
    QExtFunction< void, bool, int, int, int, int > voidFunctorBArg5(mFunctor);
    voidFunctorBArg5(true, 2, 3, 4, 5);
    QVERIFY("MConstFunctor::voidConstFunctionB5" == string);
    QExtFunction< void, bool, int, int, int, int, int > voidFunctorBArg6(mFunctor);
    voidFunctorBArg6(true, 2, 3, 4, 5, 6);
    QVERIFY("MConstFunctor::voidConstFunctionB6" == string);
    QExtFunction< void, bool, int, int, int, int, int, int > voidFunctorBArg7(mFunctor);
    voidFunctorBArg7(true, 2, 3, 4, 5, 6, 7);
    QVERIFY("MConstFunctor::voidConstFunctionB7" == string);
}

class MRetIntConstFunctor : public QExtFunctorBase
{
public:
    typedef double Return;
    typedef MRetIntConstFunctor Object;
    MRetIntConstFunctor() {}

    int operator()() const
    {
        *sg_string = "MRetIntConstFunctor::intConstFunction0";
        return 0;
    }
    int operator()(int a1) const
    {
        return a1;
    }
    int operator()(int a1, int a2) const
    {
        return a1 + a2;
    }
    int operator()(int a1, int a2, int a3) const
    {
        return a1 + a2 + a3;
    }
    int operator()(int a1, int a2, int a3, int a4) const
    {
        return a1 + a2 + a3 + a4;
    }
    int operator()(int a1, int a2, int a3, int a4, int a5) const
    {
        return a1 + a2 + a3 + a4 + a5;
    }
    int operator()(int a1, int a2, int a3, int a4, int a5, int a6) const
    {
        return a1 + a2 + a3 + a4 + a5 + a6;
    }
    int operator()(int a1, int a2, int a3, int a4, int a5, int a6, int a7) const
    {
        return a1 + a2 + a3 + a4 + a5 + a6 + a7;
    }
    int operator()(bool a1) const
    {
        return a1;
    }
    int operator()(bool a1, int a2) const
    {
        return a1 ? a2 : 0;
    }
    int operator()(bool a1, int a2, int a3) const
    {
        return a1 ? (a2 + a3) : (a2 * a3);
    }
    int operator()(bool a1, int a2, int a3, int a4) const
    {
        return a1 ? (a2 + a3 + a4) : (a2 * a3 * a4);
    }
    int operator()(bool a1, int a2, int a3, int a4, int a5) const
    {
        return a1 ? (a2 + a3 + a4 + a5) : (a2 * a3 * a4 * a5);
    }
    int operator()(bool a1, int a2, int a3, int a4, int a5, int a6) const
    {
        return a1 ? (a2 + a3 + a4 + a5 + a6) : (a2 * a3 * a4 * a5 * a6);
    }
    int operator()(bool a1, int a2, int a3, int a4, int a5, int a6, int a7) const
    {
        return a1 ? (a2 + a3 + a4 + a5 + a6 + a7) : (a2 * a3 * a4 * a5 * a6 * a7);
    }
};


void QExtFunctionTest::retIntConstFunctor()
{
    QString string;
    sg_string = &string;
    MRetIntConstFunctor mFunctor;

    QExtFunction< int > intFunctorArg0(mFunctor);
    intFunctorArg0();
    QVERIFY("MRetIntConstFunctor::intConstFunction0" == string);
    QExtFunction< int, int > intFunctorArg1(mFunctor);
    QVERIFY(1 == intFunctorArg1(1));
    QExtFunction< int, int, int > intFunctorArg2(mFunctor);
    QVERIFY(3 == intFunctorArg2(1, 2));
    QExtFunction< int, int, int, int > intFunctorArg3(mFunctor);
    QVERIFY(6 == intFunctorArg3(1, 2, 3));
    QExtFunction< int, int, int, int, int > intFunctorArg4(mFunctor);
    QVERIFY(10 == intFunctorArg4(1, 2, 3, 4));
    QExtFunction< int, int, int, int, int, int > intFunctorArg5(mFunctor);
    QVERIFY(15 == intFunctorArg5(1, 2, 3, 4, 5));
    QExtFunction< int, int, int, int, int, int, int > intFunctorArg6(mFunctor);
    QVERIFY(21 == intFunctorArg6(1, 2, 3, 4, 5, 6));
    QExtFunction< int, int, int, int, int, int, int, int > intFunctorArg7(mFunctor);
    QVERIFY(28 == intFunctorArg7(1, 2, 3, 4, 5, 6, 7));

    QExtFunction< int, bool > intFunctorBArg1(mFunctor);
    QVERIFY(1 == intFunctorBArg1(true));
    QVERIFY(0 == intFunctorBArg1(false));
    QExtFunction< int, bool, int > intFunctorBArg2(mFunctor);
    QVERIFY(2 == intFunctorBArg2(true, 2));
    QVERIFY(0 == intFunctorBArg2(false, 2));
    QExtFunction< int, bool, int, int > intFunctorBArg3(mFunctor);
    QVERIFY(5 == intFunctorBArg3(true, 2, 3));
    QVERIFY(6 == intFunctorBArg3(false, 2, 3));
    QExtFunction< int, bool, int, int, int > intFunctorBArg4(mFunctor);
    QVERIFY(9 == intFunctorBArg4(true, 2, 3, 4));
    QVERIFY(24 == intFunctorBArg4(false, 2, 3, 4));
    QExtFunction< int, bool, int, int, int, int > intFunctorBArg5(mFunctor);
    QVERIFY(14 == intFunctorBArg5(true, 2, 3, 4, 5));
    QVERIFY(120 == intFunctorBArg5(false, 2, 3, 4, 5));
    QExtFunction< int, bool, int, int, int, int, int > intFunctorBArg6(mFunctor);
    QVERIFY(20 == intFunctorBArg6(true, 2, 3, 4, 5, 6));
    QVERIFY(720 == intFunctorBArg6(false, 2, 3, 4, 5, 6));
    QExtFunction< int, bool, int, int, int, int, int, int > intFunctorBArg7(mFunctor);
    QVERIFY(27 == intFunctorBArg7(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(5040 == intFunctorBArg7(false, 2, 3, 4, 5, 6, 7));
}

class MRetDoubleConstFunctor : public QExtFunctorBase
{
public:
    typedef double Return;
    typedef MRetDoubleConstFunctor Object;
    MRetDoubleConstFunctor() {}

    double operator()() const
    {
        *sg_string = "MRetDoubleConstFunctor::doubleConstFunction0";
        return 0;
    }
    double operator()(double a1) const
    {
        return a1;
    }
    double operator()(double a1, double a2) const
    {
        return a1 + a2;
    }
    double operator()(double a1, double a2, double a3) const
    {
        return a1 + a2 + a3;
    }
    double operator()(double a1, double a2, double a3, double a4) const
    {
        return a1 + a2 + a3 + a4;
    }
    double operator()(double a1, double a2, double a3, double a4, double a5) const
    {
        return a1 + a2 + a3 + a4 + a5;
    }
    double operator()(double a1, double a2, double a3, double a4, double a5, double a6) const
    {
        return a1 + a2 + a3 + a4 + a5 + a6;
    }
    double operator()(double a1, double a2, double a3, double a4, double a5, double a6, double a7) const
    {
        return a1 + a2 + a3 + a4 + a5 + a6 + a7;
    }
    double operator()(bool a1) const
    {
        return a1 ? 1 : 0;
    }
    double operator()(bool a1, double a2) const
    {
        return a1 ? a2 : 0;
    }
    double operator()(bool a1, double a2, double a3) const
    {
        return a1 ? (a2 + a3) : (a2 * a3);
    }
    double operator()(bool a1, double a2, double a3, double a4) const
    {
        return a1 ? (a2 + a3 + a4) : (a2 * a3 * a4);
    }
    double operator()(bool a1, double a2, double a3, double a4, double a5) const
    {
        return a1 ? (a2 + a3 + a4 + a5) : (a2 * a3 * a4 * a5);
    }
    double operator()(bool a1, double a2, double a3, double a4, double a5, double a6) const
    {
        return a1 ? (a2 + a3 + a4 + a5 + a6) : (a2 * a3 * a4 * a5 * a6);
    }
    double operator()(bool a1, double a2, double a3, double a4, double a5, double a6, double a7) const
    {
        return a1 ? (a2 + a3 + a4 + a5 + a6 + a7) : (a2 * a3 * a4 * a5 * a6 * a7);
    }
};


void QExtFunctionTest::retDoubleConstFunctor()
{
    QString string;
    sg_string = &string;
    MRetDoubleConstFunctor mFunctor;

    QExtFunction< double > doubleFunctorArg0(mFunctor);
    doubleFunctorArg0();
    QVERIFY("MRetDoubleConstFunctor::doubleConstFunction0" == string);
    QExtFunction< double, double > doubleFunctorArg1(mFunctor);
    QVERIFY(1 == doubleFunctorArg1(1));
    QExtFunction< double, double, double > doubleFunctorArg2(mFunctor);
    QVERIFY(3 == doubleFunctorArg2(1, 2));
    QExtFunction< double, double, double, double > doubleFunctorArg3(mFunctor);
    QVERIFY(6 == doubleFunctorArg3(1, 2, 3));
    QExtFunction< double, double, double, double, double > doubleFunctorArg4(mFunctor);
    QVERIFY(10 == doubleFunctorArg4(1, 2, 3, 4));
    QExtFunction< double, double, double, double, double, double > doubleFunctorArg5(mFunctor);
    QVERIFY(15 == doubleFunctorArg5(1, 2, 3, 4, 5));
    QExtFunction< double, double, double, double, double, double, double > doubleFunctorArg6(mFunctor);
    QVERIFY(21 == doubleFunctorArg6(1, 2, 3, 4, 5, 6));
    QExtFunction< double, double, double, double, double, double, double, double > doubleFunctorArg7(mFunctor);
    QVERIFY(28 == doubleFunctorArg7(1, 2, 3, 4, 5, 6, 7));

    QExtFunction< double, bool > voidFunctorBArg1(mFunctor);
    QVERIFY(1 == voidFunctorBArg1(true));
    QVERIFY(0 == voidFunctorBArg1(false));
    QExtFunction< double, bool, double > voidFunctorBArg2(mFunctor);
    QVERIFY(2 == voidFunctorBArg2(true, 2));
    QVERIFY(0 == voidFunctorBArg2(false, 2));
    QExtFunction< double, bool, double, double > voidFunctorBArg3(mFunctor);
    QVERIFY(5 == voidFunctorBArg3(true, 2, 3));
    QVERIFY(6 == voidFunctorBArg3(false, 2, 3));
    QExtFunction< double, bool, double, double, double > voidFunctorBArg4(mFunctor);
    QVERIFY(9 == voidFunctorBArg4(true, 2, 3, 4));
    QVERIFY(24 == voidFunctorBArg4(false, 2, 3, 4));
    QExtFunction< double, bool, double, double, double, double > voidFunctorBArg5(mFunctor);
    QVERIFY(14 == voidFunctorBArg5(true, 2, 3, 4, 5));
    QVERIFY(120 == voidFunctorBArg5(false, 2, 3, 4, 5));
    QExtFunction< double, bool, double, double, double, double, double > voidFunctorBArg6(mFunctor);
    QVERIFY(20 == voidFunctorBArg6(true, 2, 3, 4, 5, 6));
    QVERIFY(720 == voidFunctorBArg6(false, 2, 3, 4, 5, 6));
    QExtFunction< double, bool, double, double, double, double, double, double > voidFunctorBArg7(mFunctor);
    QVERIFY(27 == voidFunctorBArg7(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(5040 == voidFunctorBArg7(false, 2, 3, 4, 5, 6, 7));
}

class MRetVolatileFunctor
{
public:
    MRetVolatileFunctor() {}

    // volatile function
    void operator()() volatile
    {
        *sg_string = "MRetVolatileFunctor::voidVolatileFunction0";
    }
    void operator()(int a1) volatile
    {
        Q_UNUSED(a1)
        *sg_string = "MRetVolatileFunctor::voidVolatileFunction1";
    }
    void operator()(int a1, int a2) volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        *sg_string = "MRetVolatileFunctor::voidVolatileFunction2";
    }
    void operator()(int a1, int a2, int a3) volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        *sg_string = "MRetVolatileFunctor::voidVolatileFunction3";
    }
    void operator()(int a1, int a2, int a3, int a4) volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        *sg_string = "MRetVolatileFunctor::voidVolatileFunction4";
    }
    void operator()(int a1, int a2, int a3, int a4, int a5) volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        *sg_string = "MRetVolatileFunctor::voidVolatileFunction5";
    }
    void operator()(int a1, int a2, int a3, int a4, int a5, int a6) volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        *sg_string = "MRetVolatileFunctor::voidVolatileFunction6";
    }
    void operator()(int a1, int a2, int a3, int a4, int a5, int a6, int a7) volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        Q_UNUSED(a7)
        *sg_string = "MRetVolatileFunctor::voidVolatileFunction7";
    }
    void operator()(bool a1) volatile
    {
        Q_UNUSED(a1)
        *sg_string = "MRetVolatileFunctor::voidVolatileFunctionB1";
    }
    void operator()(bool a1, int a2) volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        *sg_string = "MRetVolatileFunctor::voidVolatileFunctionB2";
    }
    void operator()(bool a1, int a2, int a3) volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        *sg_string = "MRetVolatileFunctor::voidVolatileFunctionB3";
    }
    void operator()(bool a1, int a2, int a3, int a4) volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        *sg_string = "MRetVolatileFunctor::voidVolatileFunctionB4";
    }
    void operator()(bool a1, int a2, int a3, int a4, int a5) volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        *sg_string = "MRetVolatileFunctor::voidVolatileFunctionB5";
    }
    void operator()(bool a1, int a2, int a3, int a4, int a5, int a6) volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        *sg_string = "MRetVolatileFunctor::voidVolatileFunctionB6";
    }
    void operator()(bool a1, int a2, int a3, int a4, int a5, int a6, int a7) volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        Q_UNUSED(a7)
        *sg_string = "MRetVolatileFunctor::voidVolatileFunctionB7";
    }
};


void QExtFunctionTest::retVolatileFunctor()
{
    QString string;
    sg_string = &string;
    MRetVolatileFunctor mFunctor;

    QExtFunction< void > voidFunctorArg0(mFunctor);
    voidFunctorArg0();
    QVERIFY("MRetVolatileFunctor::voidVolatileFunction0" == string);
    QExtFunction< void, int > voidFunctorArg1(mFunctor);
    voidFunctorArg1(1);
    QVERIFY("MRetVolatileFunctor::voidVolatileFunction1" == string);
    QExtFunction< void, int, int > voidFunctorArg2(mFunctor);
    voidFunctorArg2(1, 2);
    QVERIFY("MRetVolatileFunctor::voidVolatileFunction2" == string);
    QExtFunction< void, int, int, int > voidFunctorArg3(mFunctor);
    voidFunctorArg3(1, 2, 3);
    QVERIFY("MRetVolatileFunctor::voidVolatileFunction3" == string);
    QExtFunction< void, int, int, int, int > voidFunctorArg4(mFunctor);
    voidFunctorArg4(1, 2, 3, 4);
    QVERIFY("MRetVolatileFunctor::voidVolatileFunction4" == string);
    QExtFunction< void, int, int, int, int, int > voidFunctorArg5(mFunctor);
    voidFunctorArg5(1, 2, 3, 4, 5);
    QVERIFY("MRetVolatileFunctor::voidVolatileFunction5" == string);
    QExtFunction< void, int, int, int, int, int, int > voidFunctorArg6(mFunctor);
    voidFunctorArg6(1, 2, 3, 4, 5, 6);
    QVERIFY("MRetVolatileFunctor::voidVolatileFunction6" == string);
    QExtFunction< void, int, int, int, int, int, int, int > voidFunctorArg7(mFunctor);
    voidFunctorArg7(1, 2, 3, 4, 5, 6, 7);
    QVERIFY("MRetVolatileFunctor::voidVolatileFunction7" == string);

    QExtFunction< void, bool > voidFunctorBArg1(mFunctor);
    voidFunctorBArg1(true);
    QVERIFY("MRetVolatileFunctor::voidVolatileFunctionB1" == string);
    QExtFunction< void, bool, int > voidFunctorBArg2(mFunctor);
    voidFunctorBArg2(true, 2);
    QVERIFY("MRetVolatileFunctor::voidVolatileFunctionB2" == string);
    QExtFunction< void, bool, int, int > voidFunctorBArg3(mFunctor);
    voidFunctorBArg3(true, 2, 3);
    QVERIFY("MRetVolatileFunctor::voidVolatileFunctionB3" == string);
    QExtFunction< void, bool, int, int, int > voidFunctorBArg4(mFunctor);
    voidFunctorBArg4(true, 2, 3, 4);
    QVERIFY("MRetVolatileFunctor::voidVolatileFunctionB4" == string);
    QExtFunction< void, bool, int, int, int, int > voidFunctorBArg5(mFunctor);
    voidFunctorBArg5(true, 2, 3, 4, 5);
    QVERIFY("MRetVolatileFunctor::voidVolatileFunctionB5" == string);
    QExtFunction< void, bool, int, int, int, int, int > voidFunctorBArg6(mFunctor);
    voidFunctorBArg6(true, 2, 3, 4, 5, 6);
    QVERIFY("MRetVolatileFunctor::voidVolatileFunctionB6" == string);
    QExtFunction< void, bool, int, int, int, int, int, int > voidFunctorBArg7(mFunctor);
    voidFunctorBArg7(true, 2, 3, 4, 5, 6, 7);
    QVERIFY("MRetVolatileFunctor::voidVolatileFunctionB7" == string);
}

class MRetIntVolatileFunctor : public QExtFunctorBase
{
public:
    typedef int Return;
    typedef MRetIntVolatileFunctor Object;
    MRetIntVolatileFunctor() {}

    int operator()() volatile
    {
        *sg_string = "MRetIntVolatileFunctor::intVolatileFunction0";
        return 0;
    }
    int operator()(int a1) volatile
    {
        return a1;
    }
    int operator()(int a1, int a2) volatile
    {
        return a1 + a2;
    }
    int operator()(int a1, int a2, int a3) volatile
    {
        return a1 + a2 + a3;
    }
    int operator()(int a1, int a2, int a3, int a4) volatile
    {
        return a1 + a2 + a3 + a4;
    }
    int operator()(int a1, int a2, int a3, int a4, int a5) volatile
    {
        return a1 + a2 + a3 + a4 + a5;
    }
    int operator()(int a1, int a2, int a3, int a4, int a5, int a6) volatile
    {
        return a1 + a2 + a3 + a4 + a5 + a6;
    }
    int operator()(int a1, int a2, int a3, int a4, int a5, int a6, int a7) volatile
    {
        return a1 + a2 + a3 + a4 + a5 + a6 + a7;
    }
    int operator()(bool a1) volatile
    {
        return a1;
    }
    int operator()(bool a1, int a2) volatile
    {
        return a1 ? a2 : 0;
    }
    int operator()(bool a1, int a2, int a3) volatile
    {
        return a1 ? (a2 + a3) : (a2 * a3);
    }
    int operator()(bool a1, int a2, int a3, int a4) volatile
    {
        return a1 ? (a2 + a3 + a4) : (a2 * a3 * a4);
    }
    int operator()(bool a1, int a2, int a3, int a4, int a5) volatile
    {
        return a1 ? (a2 + a3 + a4 + a5) : (a2 * a3 * a4 * a5);
    }
    int operator()(bool a1, int a2, int a3, int a4, int a5, int a6) volatile
    {
        return a1 ? (a2 + a3 + a4 + a5 + a6) : (a2 * a3 * a4 * a5 * a6);
    }
    int operator()(bool a1, int a2, int a3, int a4, int a5, int a6, int a7) volatile
    {
        return a1 ? (a2 + a3 + a4 + a5 + a6 + a7) : (a2 * a3 * a4 * a5 * a6 * a7);
    }
};


void QExtFunctionTest::retIntVolatileFunctor()
{
    QString string;
    sg_string = &string;
    MRetIntVolatileFunctor mFunctor;

    QExtFunction< int > intFunctorArg0(mFunctor);
    intFunctorArg0();
    QVERIFY("MRetIntVolatileFunctor::intVolatileFunction0" == string);
    QExtFunction< int, int > intFunctorArg1(mFunctor);
    QVERIFY(1 == intFunctorArg1(1));
    QExtFunction< int, int, int > intFunctorArg2(mFunctor);
    QVERIFY(3 == intFunctorArg2(1, 2));
    QExtFunction< int, int, int, int > intFunctorArg3(mFunctor);
    QVERIFY(6 == intFunctorArg3(1, 2, 3));
    QExtFunction< int, int, int, int, int > intFunctorArg4(mFunctor);
    QVERIFY(10 == intFunctorArg4(1, 2, 3, 4));
    QExtFunction< int, int, int, int, int, int > intFunctorArg5(mFunctor);
    QVERIFY(15 == intFunctorArg5(1, 2, 3, 4, 5));
    QExtFunction< int, int, int, int, int, int, int > intFunctorArg6(mFunctor);
    QVERIFY(21 == intFunctorArg6(1, 2, 3, 4, 5, 6));
    QExtFunction< int, int, int, int, int, int, int, int > intFunctorArg7(mFunctor);
    QVERIFY(28 == intFunctorArg7(1, 2, 3, 4, 5, 6, 7));

    QExtFunction< int, bool > intFunctorBArg1(mFunctor);
    QVERIFY(1 == intFunctorBArg1(true));
    QVERIFY(0 == intFunctorBArg1(false));
    QExtFunction< int, bool, int > intFunctorBArg2(mFunctor);
    QVERIFY(2 == intFunctorBArg2(true, 2));
    QVERIFY(0 == intFunctorBArg2(false, 2));
    QExtFunction< int, bool, int, int > intFunctorBArg3(mFunctor);
    QVERIFY(5 == intFunctorBArg3(true, 2, 3));
    QVERIFY(6 == intFunctorBArg3(false, 2, 3));
    QExtFunction< int, bool, int, int, int > intFunctorBArg4(mFunctor);
    QVERIFY(9 == intFunctorBArg4(true, 2, 3, 4));
    QVERIFY(24 == intFunctorBArg4(false, 2, 3, 4));
    QExtFunction< int, bool, int, int, int, int > intFunctorBArg5(mFunctor);
    QVERIFY(14 == intFunctorBArg5(true, 2, 3, 4, 5));
    QVERIFY(120 == intFunctorBArg5(false, 2, 3, 4, 5));
    QExtFunction< int, bool, int, int, int, int, int > intFunctorBArg6(mFunctor);
    QVERIFY(20 == intFunctorBArg6(true, 2, 3, 4, 5, 6));
    QVERIFY(720 == intFunctorBArg6(false, 2, 3, 4, 5, 6));
    QExtFunction< int, bool, int, int, int, int, int, int > intFunctorBArg7(mFunctor);
    QVERIFY(27 == intFunctorBArg7(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(5040 == intFunctorBArg7(false, 2, 3, 4, 5, 6, 7));
}

class MRetDoubleVolatileFunctor : public QExtFunctorBase
{
public:
    typedef double Return;
    typedef MRetDoubleVolatileFunctor Object;
    MRetDoubleVolatileFunctor() {}

    double operator()() volatile
    {
        *sg_string = "MRetDoubleVolatileFunctor::doubleVolatileFunction0";
        return 0;
    }
    double operator()(double a1) volatile
    {
        return a1;
    }
    double operator()(double a1, double a2) volatile
    {
        return a1 + a2;
    }
    double operator()(double a1, double a2, double a3) volatile
    {
        return a1 + a2 + a3;
    }
    double operator()(double a1, double a2, double a3, double a4) volatile
    {
        return a1 + a2 + a3 + a4;
    }
    double operator()(double a1, double a2, double a3, double a4, double a5) volatile
    {
        return a1 + a2 + a3 + a4 + a5;
    }
    double operator()(double a1, double a2, double a3, double a4, double a5, double a6) volatile
    {
        return a1 + a2 + a3 + a4 + a5 + a6;
    }
    double operator()(double a1, double a2, double a3, double a4, double a5, double a6, double a7) volatile
    {
        return a1 + a2 + a3 + a4 + a5 + a6 + a7;
    }
    double operator()(bool a1) volatile
    {
        return a1 ? 1 : 0;
    }
    double operator()(bool a1, double a2) volatile
    {
        return a1 ? a2 : 0;
    }
    double operator()(bool a1, double a2, double a3) volatile
    {
        return a1 ? (a2 + a3) : (a2 * a3);
    }
    double operator()(bool a1, double a2, double a3, double a4) volatile
    {
        return a1 ? (a2 + a3 + a4) : (a2 * a3 * a4);
    }
    double operator()(bool a1, double a2, double a3, double a4, double a5) volatile
    {
        return a1 ? (a2 + a3 + a4 + a5) : (a2 * a3 * a4 * a5);
    }
    double operator()(bool a1, double a2, double a3, double a4, double a5, double a6) volatile
    {
        return a1 ? (a2 + a3 + a4 + a5 + a6) : (a2 * a3 * a4 * a5 * a6);
    }
    double operator()(bool a1, double a2, double a3, double a4, double a5, double a6, double a7) volatile
    {
        return a1 ? (a2 + a3 + a4 + a5 + a6 + a7) : (a2 * a3 * a4 * a5 * a6 * a7);
    }
};


void QExtFunctionTest::retDoubleVolatileFunctor()
{
    QString string;
    sg_string = &string;
    MRetDoubleVolatileFunctor mFunctor;

    QExtFunction< double > doubleFunctorArg0(mFunctor);
    doubleFunctorArg0();
    QVERIFY("MRetDoubleVolatileFunctor::doubleVolatileFunction0" == string);
    QExtFunction< double, double > doubleFunctorArg1(mFunctor);
    QVERIFY(1 == doubleFunctorArg1(1));
    QExtFunction< double, double, double > doubleFunctorArg2(mFunctor);
    QVERIFY(3 == doubleFunctorArg2(1, 2));
    QExtFunction< double, double, double, double > doubleFunctorArg3(mFunctor);
    QVERIFY(6 == doubleFunctorArg3(1, 2, 3));
    QExtFunction< double, double, double, double, double > doubleFunctorArg4(mFunctor);
    QVERIFY(10 == doubleFunctorArg4(1, 2, 3, 4));
    QExtFunction< double, double, double, double, double, double > doubleFunctorArg5(mFunctor);
    QVERIFY(15 == doubleFunctorArg5(1, 2, 3, 4, 5));
    QExtFunction< double, double, double, double, double, double, double > doubleFunctorArg6(mFunctor);
    QVERIFY(21 == doubleFunctorArg6(1, 2, 3, 4, 5, 6));
    QExtFunction< double, double, double, double, double, double, double, double > doubleFunctorArg7(mFunctor);
    QVERIFY(28 == doubleFunctorArg7(1, 2, 3, 4, 5, 6, 7));

    QExtFunction< double, bool > voidFunctorBArg1(mFunctor);
    QVERIFY(1 == voidFunctorBArg1(true));
    QVERIFY(0 == voidFunctorBArg1(false));
    QExtFunction< double, bool, double > voidFunctorBArg2(mFunctor);
    QVERIFY(2 == voidFunctorBArg2(true, 2));
    QVERIFY(0 == voidFunctorBArg2(false, 2));
    QExtFunction< double, bool, double, double > voidFunctorBArg3(mFunctor);
    QVERIFY(5 == voidFunctorBArg3(true, 2, 3));
    QVERIFY(6 == voidFunctorBArg3(false, 2, 3));
    QExtFunction< double, bool, double, double, double > voidFunctorBArg4(mFunctor);
    QVERIFY(9 == voidFunctorBArg4(true, 2, 3, 4));
    QVERIFY(24 == voidFunctorBArg4(false, 2, 3, 4));
    QExtFunction< double, bool, double, double, double, double > voidFunctorBArg5(mFunctor);
    QVERIFY(14 == voidFunctorBArg5(true, 2, 3, 4, 5));
    QVERIFY(120 == voidFunctorBArg5(false, 2, 3, 4, 5));
    QExtFunction< double, bool, double, double, double, double, double > voidFunctorBArg6(mFunctor);
    QVERIFY(20 == voidFunctorBArg6(true, 2, 3, 4, 5, 6));
    QVERIFY(720 == voidFunctorBArg6(false, 2, 3, 4, 5, 6));
    QExtFunction< double, bool, double, double, double, double, double, double > voidFunctorBArg7(mFunctor);
    QVERIFY(27 == voidFunctorBArg7(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(5040 == voidFunctorBArg7(false, 2, 3, 4, 5, 6, 7));
}

class MRetConstVolatileFunctor
{
public:
    MRetConstVolatileFunctor() {}

    // const volatile
    void operator()() const volatile
    {
        *sg_string = "MRetConstVolatileFunctor::voidConstVolatileFunction0";
    }
    void operator()(int a1) const volatile
    {
        Q_UNUSED(a1)
        *sg_string = "MRetConstVolatileFunctor::voidConstVolatileFunction1";
    }
    void operator()(int a1, int a2) const volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        *sg_string = "MRetConstVolatileFunctor::voidConstVolatileFunction2";
    }
    void operator()(int a1, int a2, int a3) const volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        *sg_string = "MRetConstVolatileFunctor::voidConstVolatileFunction3";
    }
    void operator()(int a1, int a2, int a3, int a4) const volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        *sg_string = "MRetConstVolatileFunctor::voidConstVolatileFunction4";
    }
    void operator()(int a1, int a2, int a3, int a4, int a5) const volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        *sg_string = "MRetConstVolatileFunctor::voidConstVolatileFunction5";
    }
    void operator()(int a1, int a2, int a3, int a4, int a5, int a6) const volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        *sg_string = "MRetConstVolatileFunctor::voidConstVolatileFunction6";
    }
    void operator()(int a1, int a2, int a3, int a4, int a5, int a6, int a7) const volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        Q_UNUSED(a7)
        *sg_string = "MRetConstVolatileFunctor::voidConstVolatileFunction7";
    }
    void operator()(bool a1) const volatile
    {
        Q_UNUSED(a1)
        *sg_string = "MRetConstVolatileFunctor::voidConstVolatileFunctionB1";
    }
    void operator()(bool a1, int a2) const volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        *sg_string = "MRetConstVolatileFunctor::voidConstVolatileFunctionB2";
    }
    void operator()(bool a1, int a2, int a3) const volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        *sg_string = "MRetConstVolatileFunctor::voidConstVolatileFunctionB3";
    }
    void operator()(bool a1, int a2, int a3, int a4) const volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        *sg_string = "MRetConstVolatileFunctor::voidConstVolatileFunctionB4";
    }
    void operator()(bool a1, int a2, int a3, int a4, int a5) const volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        *sg_string = "MRetConstVolatileFunctor::voidConstVolatileFunctionB5";
    }
    void operator()(bool a1, int a2, int a3, int a4, int a5, int a6) const volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        *sg_string = "MRetConstVolatileFunctor::voidConstVolatileFunctionB6";
    }
    void operator()(bool a1, int a2, int a3, int a4, int a5, int a6, int a7) const volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        Q_UNUSED(a7)
        *sg_string = "MRetConstVolatileFunctor::voidConstVolatileFunctionB7";
    }
};


void QExtFunctionTest::retConstVolatileFunctor()
{
    QString string;
    sg_string = &string;
    MRetConstVolatileFunctor mFunctor;

    QExtFunction< void > voidFunctorArg0(mFunctor);
    voidFunctorArg0();
    QVERIFY("MRetConstVolatileFunctor::voidConstVolatileFunction0" == string);
    QExtFunction< void, int > voidFunctorArg1(mFunctor);
    voidFunctorArg1(1);
    QVERIFY("MRetConstVolatileFunctor::voidConstVolatileFunction1" == string);
    QExtFunction< void, int, int > voidFunctorArg2(mFunctor);
    voidFunctorArg2(1, 2);
    QVERIFY("MRetConstVolatileFunctor::voidConstVolatileFunction2" == string);
    QExtFunction< void, int, int, int > voidFunctorArg3(mFunctor);
    voidFunctorArg3(1, 2, 3);
    QVERIFY("MRetConstVolatileFunctor::voidConstVolatileFunction3" == string);
    QExtFunction< void, int, int, int, int > voidFunctorArg4(mFunctor);
    voidFunctorArg4(1, 2, 3, 4);
    QVERIFY("MRetConstVolatileFunctor::voidConstVolatileFunction4" == string);
    QExtFunction< void, int, int, int, int, int > voidFunctorArg5(mFunctor);
    voidFunctorArg5(1, 2, 3, 4, 5);
    QVERIFY("MRetConstVolatileFunctor::voidConstVolatileFunction5" == string);
    QExtFunction< void, int, int, int, int, int, int > voidFunctorArg6(mFunctor);
    voidFunctorArg6(1, 2, 3, 4, 5, 6);
    QVERIFY("MRetConstVolatileFunctor::voidConstVolatileFunction6" == string);
    QExtFunction< void, int, int, int, int, int, int, int > voidFunctorArg7(mFunctor);
    voidFunctorArg7(1, 2, 3, 4, 5, 6, 7);
    QVERIFY("MRetConstVolatileFunctor::voidConstVolatileFunction7" == string);

    QExtFunction< void, bool > voidFunctorBArg1(mFunctor);
    voidFunctorBArg1(true);
    QVERIFY("MRetConstVolatileFunctor::voidConstVolatileFunctionB1" == string);
    QExtFunction< void, bool, int > voidFunctorBArg2(mFunctor);
    voidFunctorBArg2(true, 2);
    QVERIFY("MRetConstVolatileFunctor::voidConstVolatileFunctionB2" == string);
    QExtFunction< void, bool, int, int > voidFunctorBArg3(mFunctor);
    voidFunctorBArg3(true, 2, 3);
    QVERIFY("MRetConstVolatileFunctor::voidConstVolatileFunctionB3" == string);
    QExtFunction< void, bool, int, int, int > voidFunctorBArg4(mFunctor);
    voidFunctorBArg4(true, 2, 3, 4);
    QVERIFY("MRetConstVolatileFunctor::voidConstVolatileFunctionB4" == string);
    QExtFunction< void, bool, int, int, int, int > voidFunctorBArg5(mFunctor);
    voidFunctorBArg5(true, 2, 3, 4, 5);
    QVERIFY("MRetConstVolatileFunctor::voidConstVolatileFunctionB5" == string);
    QExtFunction< void, bool, int, int, int, int, int > voidFunctorBArg6(mFunctor);
    voidFunctorBArg6(true, 2, 3, 4, 5, 6);
    QVERIFY("MRetConstVolatileFunctor::voidConstVolatileFunctionB6" == string);
    QExtFunction< void, bool, int, int, int, int, int, int > voidFunctorBArg7(mFunctor);
    voidFunctorBArg7(true, 2, 3, 4, 5, 6, 7);
    QVERIFY("MRetConstVolatileFunctor::voidConstVolatileFunctionB7" == string);
}

class MRetIntConstVolatileFunctor : public QExtFunctorBase
{
public:
    typedef int Return;
    typedef MRetIntConstVolatileFunctor Object;
    MRetIntConstVolatileFunctor() {}

    int operator()() const volatile
    {
        *sg_string = "MRetIntConstVolatileFunctor::intConstVolatileFunction0";
        return 0;
    }
    int operator()(int a1) const volatile
    {
        return a1;
    }
    int operator()(int a1, int a2) const volatile
    {
        return a1 + a2;
    }
    int operator()(int a1, int a2, int a3) const volatile
    {
        return a1 + a2 + a3;
    }
    int operator()(int a1, int a2, int a3, int a4) const volatile
    {
        return a1 + a2 + a3 + a4;
    }
    int operator()(int a1, int a2, int a3, int a4, int a5) const volatile
    {
        return a1 + a2 + a3 + a4 + a5;
    }
    int operator()(int a1, int a2, int a3, int a4, int a5, int a6) const volatile
    {
        return a1 + a2 + a3 + a4 + a5 + a6;
    }
    int operator()(int a1, int a2, int a3, int a4, int a5, int a6, int a7) const volatile
    {
        return a1 + a2 + a3 + a4 + a5 + a6 + a7;
    }
    int operator()(bool a1) const volatile
    {
        return a1;
    }
    int operator()(bool a1, int a2) const volatile
    {
        return a1 ? a2 : 0;
    }
    int operator()(bool a1, int a2, int a3) const volatile
    {
        return a1 ? (a2 + a3) : (a2 * a3);
    }
    int operator()(bool a1, int a2, int a3, int a4) const volatile
    {
        return a1 ? (a2 + a3 + a4) : (a2 * a3 * a4);
    }
    int operator()(bool a1, int a2, int a3, int a4, int a5) const volatile
    {
        return a1 ? (a2 + a3 + a4 + a5) : (a2 * a3 * a4 * a5);
    }
    int operator()(bool a1, int a2, int a3, int a4, int a5, int a6) const volatile
    {
        return a1 ? (a2 + a3 + a4 + a5 + a6) : (a2 * a3 * a4 * a5 * a6);
    }
    int operator()(bool a1, int a2, int a3, int a4, int a5, int a6, int a7) const volatile
    {
        return a1 ? (a2 + a3 + a4 + a5 + a6 + a7) : (a2 * a3 * a4 * a5 * a6 * a7);
    }
};


void QExtFunctionTest::retIntConstVolatileFunctor()
{
    QString string;
    sg_string = &string;
    MRetIntConstVolatileFunctor mFunctor;

    QExtFunction< int > intFunctorArg0(mFunctor);
    intFunctorArg0();
    QVERIFY("MRetIntConstVolatileFunctor::intConstVolatileFunction0" == string);
    QExtFunction< int, int > intFunctorArg1(mFunctor);
    QVERIFY(1 == intFunctorArg1(1));
    QExtFunction< int, int, int > intFunctorArg2(mFunctor);
    QVERIFY(3 == intFunctorArg2(1, 2));
    QExtFunction< int, int, int, int > intFunctorArg3(mFunctor);
    QVERIFY(6 == intFunctorArg3(1, 2, 3));
    QExtFunction< int, int, int, int, int > intFunctorArg4(mFunctor);
    QVERIFY(10 == intFunctorArg4(1, 2, 3, 4));
    QExtFunction< int, int, int, int, int, int > intFunctorArg5(mFunctor);
    QVERIFY(15 == intFunctorArg5(1, 2, 3, 4, 5));
    QExtFunction< int, int, int, int, int, int, int > intFunctorArg6(mFunctor);
    QVERIFY(21 == intFunctorArg6(1, 2, 3, 4, 5, 6));
    QExtFunction< int, int, int, int, int, int, int, int > intFunctorArg7(mFunctor);
    QVERIFY(28 == intFunctorArg7(1, 2, 3, 4, 5, 6, 7));

    QExtFunction< int, bool > intFunctorBArg1(mFunctor);
    QVERIFY(1 == intFunctorBArg1(true));
    QVERIFY(0 == intFunctorBArg1(false));
    QExtFunction< int, bool, int > intFunctorBArg2(mFunctor);
    QVERIFY(2 == intFunctorBArg2(true, 2));
    QVERIFY(0 == intFunctorBArg2(false, 2));
    QExtFunction< int, bool, int, int > intFunctorBArg3(mFunctor);
    QVERIFY(5 == intFunctorBArg3(true, 2, 3));
    QVERIFY(6 == intFunctorBArg3(false, 2, 3));
    QExtFunction< int, bool, int, int, int > intFunctorBArg4(mFunctor);
    QVERIFY(9 == intFunctorBArg4(true, 2, 3, 4));
    QVERIFY(24 == intFunctorBArg4(false, 2, 3, 4));
    QExtFunction< int, bool, int, int, int, int > intFunctorBArg5(mFunctor);
    QVERIFY(14 == intFunctorBArg5(true, 2, 3, 4, 5));
    QVERIFY(120 == intFunctorBArg5(false, 2, 3, 4, 5));
    QExtFunction< int, bool, int, int, int, int, int > intFunctorBArg6(mFunctor);
    QVERIFY(20 == intFunctorBArg6(true, 2, 3, 4, 5, 6));
    QVERIFY(720 == intFunctorBArg6(false, 2, 3, 4, 5, 6));
    QExtFunction< int, bool, int, int, int, int, int, int > intFunctorBArg7(mFunctor);
    QVERIFY(27 == intFunctorBArg7(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(5040 == intFunctorBArg7(false, 2, 3, 4, 5, 6, 7));
}

class MRetDoubleConstVolatileFunctor : public QExtFunctorBase
{
public:
    typedef double Return;
    typedef MRetDoubleConstVolatileFunctor Object;
    MRetDoubleConstVolatileFunctor() {}

    double operator()() const volatile
    {
        *sg_string = "MRetDoubleConstVolatileFunctor::doubleConstVolatileFunction0";
        return 0;
    }
    double operator()(double a1) const volatile
    {
        return a1;
    }
    double operator()(double a1, double a2) const volatile
    {
        return a1 + a2;
    }
    double operator()(double a1, double a2, double a3) const volatile
    {
        return a1 + a2 + a3;
    }
    double operator()(double a1, double a2, double a3, double a4) const volatile
    {
        return a1 + a2 + a3 + a4;
    }
    double operator()(double a1, double a2, double a3, double a4, double a5) const volatile
    {
        return a1 + a2 + a3 + a4 + a5;
    }
    double operator()(double a1, double a2, double a3, double a4, double a5, double a6) const volatile
    {
        return a1 + a2 + a3 + a4 + a5 + a6;
    }
    double operator()(double a1, double a2, double a3, double a4, double a5, double a6, double a7) const volatile
    {
        return a1 + a2 + a3 + a4 + a5 + a6 + a7;
    }
    double operator()(bool a1) const volatile
    {
        return a1 ? 1 : 0;
    }
    double operator()(bool a1, double a2) const volatile
    {
        return a1 ? a2 : 0;
    }
    double operator()(bool a1, double a2, double a3) const volatile
    {
        return a1 ? (a2 + a3) : (a2 * a3);
    }
    double operator()(bool a1, double a2, double a3, double a4) const volatile
    {
        return a1 ? (a2 + a3 + a4) : (a2 * a3 * a4);
    }
    double operator()(bool a1, double a2, double a3, double a4, double a5) const volatile
    {
        return a1 ? (a2 + a3 + a4 + a5) : (a2 * a3 * a4 * a5);
    }
    double operator()(bool a1, double a2, double a3, double a4, double a5, double a6) const volatile
    {
        return a1 ? (a2 + a3 + a4 + a5 + a6) : (a2 * a3 * a4 * a5 * a6);
    }
    double operator()(bool a1, double a2, double a3, double a4, double a5, double a6, double a7) const volatile
    {
        return a1 ? (a2 + a3 + a4 + a5 + a6 + a7) : (a2 * a3 * a4 * a5 * a6 * a7);
    }
};

void QExtFunctionTest::retDoubleConstVolatileFunctor()
{
    QString string;
    sg_string = &string;
    MRetDoubleConstVolatileFunctor mFunctor;

    QExtFunction< double > doubleFunctorArg0(mFunctor);
    doubleFunctorArg0();
    QVERIFY("MRetDoubleConstVolatileFunctor::doubleConstVolatileFunction0" == string);
    QExtFunction< double, double > doubleFunctorArg1(mFunctor);
    QVERIFY(1 == doubleFunctorArg1(1));
    QExtFunction< double, double, double > doubleFunctorArg2(mFunctor);
    QVERIFY(3 == doubleFunctorArg2(1, 2));
    QExtFunction< double, double, double, double > doubleFunctorArg3(mFunctor);
    QVERIFY(6 == doubleFunctorArg3(1, 2, 3));
    QExtFunction< double, double, double, double, double > doubleFunctorArg4(mFunctor);
    QVERIFY(10 == doubleFunctorArg4(1, 2, 3, 4));
    QExtFunction< double, double, double, double, double, double > doubleFunctorArg5(mFunctor);
    QVERIFY(15 == doubleFunctorArg5(1, 2, 3, 4, 5));
    QExtFunction< double, double, double, double, double, double, double > doubleFunctorArg6(mFunctor);
    QVERIFY(21 == doubleFunctorArg6(1, 2, 3, 4, 5, 6));
    QExtFunction< double, double, double, double, double, double, double, double > doubleFunctorArg7(mFunctor);
    QVERIFY(28 == doubleFunctorArg7(1, 2, 3, 4, 5, 6, 7));

    QExtFunction< double, bool > voidFunctorBArg1(mFunctor);
    QVERIFY(1 == voidFunctorBArg1(true));
    QVERIFY(0 == voidFunctorBArg1(false));
    QExtFunction< double, bool, double > voidFunctorBArg2(mFunctor);
    QVERIFY(2 == voidFunctorBArg2(true, 2));
    QVERIFY(0 == voidFunctorBArg2(false, 2));
    QExtFunction< double, bool, double, double > voidFunctorBArg3(mFunctor);
    QVERIFY(5 == voidFunctorBArg3(true, 2, 3));
    QVERIFY(6 == voidFunctorBArg3(false, 2, 3));
    QExtFunction< double, bool, double, double, double > voidFunctorBArg4(mFunctor);
    QVERIFY(9 == voidFunctorBArg4(true, 2, 3, 4));
    QVERIFY(24 == voidFunctorBArg4(false, 2, 3, 4));
    QExtFunction< double, bool, double, double, double, double > voidFunctorBArg5(mFunctor);
    QVERIFY(14 == voidFunctorBArg5(true, 2, 3, 4, 5));
    QVERIFY(120 == voidFunctorBArg5(false, 2, 3, 4, 5));
    QExtFunction< double, bool, double, double, double, double, double > voidFunctorBArg6(mFunctor);
    QVERIFY(20 == voidFunctorBArg6(true, 2, 3, 4, 5, 6));
    QVERIFY(720 == voidFunctorBArg6(false, 2, 3, 4, 5, 6));
    QExtFunction< double, bool, double, double, double, double, double, double > voidFunctorBArg7(mFunctor);
    QVERIFY(27 == voidFunctorBArg7(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(5040 == voidFunctorBArg7(false, 2, 3, 4, 5, 6, 7));
}

void QExtFunctionTest::pointerFunctorWith0Arg()
{
    QExtFunction< void > voidFunctor(&voidFunction0);
    voidFunctor();
    QVERIFY("voidFunction0" == sg_functionString);
    QExtFunction< int > intFunctor(&intFunction0);
    QVERIFY(0 == intFunctor());
    QExtFunction< double > doubleFunctor(&doubleFunction0);
    QVERIFY(0 == doubleFunctor());
}

void QExtFunctionTest::pointerFunctorWith1Arg()
{
    QExtFunction< void, int > voidFunctor(&voidFunction1);
    voidFunctor(1);
    QVERIFY("voidFunction1" == sg_functionString);
    QExtFunction< int, int > intFunctor(&intFunction1);
    QVERIFY(1 == intFunctor(1));
    QExtFunction< double, double > doubleFunctor(&doubleFunction1);
    QVERIFY(1.1 == doubleFunctor(1.1));

    QExtFunction< void, bool > voidFunctorB(&voidFunctionB1);
    voidFunctorB(1);
    QVERIFY("voidFunctionB1" == sg_functionString);
    QExtFunction< int, bool > intFunctorB(&intFunctionB1);
    QVERIFY(1 == intFunctorB(true));
    QVERIFY(0 == intFunctorB(false));
    QExtFunction< double, bool > doubleFunctorB(&doubleFunctionB1);
    QVERIFY(1 == doubleFunctorB(true));
    QVERIFY(0 == doubleFunctorB(false));

    QExtFunction< void, int & > voidFunctorR(&voidFunctionR1);
    int a1 = 1;
    voidFunctorR(a1);
    QVERIFY(2 == a1);
}

void QExtFunctionTest::testFunctorWith2Arg()
{
    QExtFunction< void, int, int > voidFunctor(&voidFunction2);
    voidFunctor(1, 2);
    QVERIFY("voidFunction2" == sg_functionString);
    QExtFunction< int, int, int > intFunctor(&intFunction2);
    QVERIFY(1 + 2 == intFunctor(1, 2));
    QExtFunction< double, double, double > doubleFunctor(&doubleFunction2);
    QVERIFY(1.1 + 2.2 == doubleFunctor(1.1, 2.2));

    QExtFunction< void, bool, int > voidFunctorB(&voidFunctionB2);
    voidFunctorB(true, 2);
    QVERIFY("voidFunctionB2" == sg_functionString);
    QExtFunction< int, bool, int > intFunctorB(&intFunctionB2);
    QVERIFY(2 == intFunctorB(true, 2));
    QVERIFY(0 == intFunctorB(false, 2));
    QExtFunction< double, bool, double > doubleFunctorB(&doubleFunctionB2);
    QVERIFY(2.2 == doubleFunctorB(true, 2.2));
    QVERIFY(0 == doubleFunctorB(false, 2.2));

    QExtFunction< void, int &, int & > voidFunctorR(&voidFunctionR2);
    int a1 = 1;
    int a2 = 2;
    voidFunctorR(a1, a2);
    QVERIFY(2 == a1);
    QVERIFY(3 == a2);
}

void QExtFunctionTest::testFunctorWith3Arg()
{
    QExtFunction< void, int, int, int > voidFunctor(&voidFunction3);
    voidFunctor(1, 2, 3);
    QVERIFY("voidFunction3" == sg_functionString);
    QExtFunction< int, int, int, int > intFunctor(&intFunction3);
    QVERIFY(1 + 2 + 3 == intFunctor(1, 2, 3));
    QExtFunction< double, double, double, double > doubleFunctor(&doubleFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleFunctor(1.1, 2.2, 3.3));

    QExtFunction< void, bool, int, int > voidFunctorB3(&voidFunctionB3);
    voidFunctorB3(true, 2, 3);
    QVERIFY("voidFunctionB3" == sg_functionString);
    QExtFunction< int, bool, int, int > intFunctorB(&intFunctionB3);
    QVERIFY(2 + 3 == intFunctorB(true, 2, 3));
    QVERIFY(2 * 3 == intFunctorB(false, 2, 3));
    QExtFunction< double, bool, double, double > doubleFunctorB(&doubleFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleFunctorB(true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleFunctorB(false, 2.2, 3.3));

    QExtFunction< void, int &, int &, int & > voidFunctorR(&voidFunctionR3);
    int a1 = 1;
    int a2 = 2;
    int a3 = 3;
    voidFunctorR(a1, a2, a3);
    QVERIFY(2 == a1);
    QVERIFY(3 == a2);
    QVERIFY(4 == a3);
}

void QExtFunctionTest::testFunctorWith4Arg()
{
    QExtFunction< void, bool, int, int, int > voidFunctorB(&voidFunctionB4);
    voidFunctorB(1, 2, 3, 4);
    QVERIFY("voidFunctionB4" == sg_functionString);
    QExtFunction< int, bool, int, int, int > intFunctorB(&intFunctionB4);
    QVERIFY(2 + 3 + 4 == intFunctorB(true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intFunctorB(false, 2, 3, 4));
    QExtFunction< double, bool, double, double, double > doubleFunctorB(&doubleFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleFunctorB(true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleFunctorB(false, 2.2, 3.3, 4.4));

    QExtFunction< void, int, int, int, int > voidFunctor(&voidFunction4);
    voidFunctor(1, 2, 3, 4);
    QVERIFY("voidFunction4" == sg_functionString);
    QExtFunction< int, int, int, int, int > intFunctor(&intFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intFunctor(1, 2, 3, 4));
    QExtFunction< double, double, double, double, double > doubleFunctor(&doubleFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleFunctor(1.1, 2.2, 3.3, 4.4));

    QExtFunction< void, int &, int &, int &, int & > voidFunctorR(&voidFunctionR4);
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

void QExtFunctionTest::testFunctorWith5Arg()
{
    QExtFunction< void, int, int, int, int, int > voidFunctor(&voidFunction5);
    voidFunctor(1, 2, 3, 4, 5);
    QVERIFY("voidFunction5" == sg_functionString);
    QExtFunction< int, int, int, int, int, int > intFunctor(&intFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intFunctor(1, 2, 3, 4, 5));
    QExtFunction< double, double, double, double, double, double > doubleFunctor(&doubleFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleFunctor(1.1, 2.2, 3.3, 4.4, 5.5));

    QExtFunction< void, bool, int, int, int, int > voidFunctorB(&voidFunctionB5);
    voidFunctorB(true, 2, 3, 4, 5);
    QVERIFY("voidFunctionB5" == sg_functionString);
    QExtFunction< int, bool, int, int, int, int > intFunctorB(&intFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intFunctorB(true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intFunctorB(false, 2, 3, 4, 5));
    QExtFunction< double, bool, double, double, double, double > doubleFunctorB(&doubleFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleFunctorB(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleFunctorB(false, 2.2, 3.3, 4.4, 5.5));

    QExtFunction< void, int &, int &, int &, int &, int & > voidFunctorR(&voidFunctionR5);
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

void QExtFunctionTest::testFunctorWith6Arg()
{
    QExtFunction< void, int, int, int, int, int, int > voidFunctor(&voidFunction6);
    voidFunctor(1, 2, 3, 4, 5, 6);
    QVERIFY("voidFunction6" == sg_functionString);
    QExtFunction< int, int, int, int, int, int, int > intFunctor(&intFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intFunctor(1, 2, 3, 4, 5, 6));
    QExtFunction< double, double, double, double, double, double, double > doubleFunctor(&doubleFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QExtFunction< void, bool, int, int, int, int, int > voidFunctorB(&voidFunctionB6);
    voidFunctorB(true, 2, 3, 4, 5, 6);
    QVERIFY("voidFunctionB6" == sg_functionString);
    QExtFunction< int, bool, int, int, int, int, int > intFunctorB(&intFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intFunctorB(true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intFunctorB(false, 2, 3, 4, 5, 6));
    QExtFunction< double, bool, double, double, double, double, double > doubleFunctorB(&doubleFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QExtFunction< void, int &, int &, int &, int &, int &, int & > voidFunctorR(&voidFunctionR6);
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

void QExtFunctionTest::pointerFunctorWith7Arg()
{
    QExtFunction< void, int, int, int, int, int, int, int > voidFunctor(&voidFunction7);
    voidFunctor(1, 2, 3, 4, 5, 6, 7);
    QVERIFY("voidFunction7" == sg_functionString);
    QExtFunction< int, int, int, int, int, int, int, int > intFunctor(&intFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intFunctor(1, 2, 3, 4, 5, 6, 7));
    QExtFunction< double, double, double, double, double, double, double, double > doubleFunctor(&doubleFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QExtFunction< void, bool, int, int, int, int, int, int > voidFunctorB(&voidFunctionB7);
    voidFunctorB(1, 2, 3, 4, 5, 6, 7);
    QVERIFY("voidFunctionB7" == sg_functionString);
    QExtFunction< int, bool, int, int, int, int, int, int > intFunctorB(&intFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intFunctorB(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intFunctorB(false, 2, 3, 4, 5, 6, 7));
    QExtFunction< double, bool, double, double, double, double, double, double > doubleFunctorB(&doubleFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QExtFunction< void, int &, int &, int &, int &, int &, int &, int & > voidFunctorR(&voidFunctionR7);
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

void QExtFunctionTest::testBoundFunctorWith0Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    *sg_memberString = "";
    QExtFunction< void > voidBoundMemberBaseFunctorR(memberBase, &MemberBase::voidFunction0);
    voidBoundMemberBaseFunctorR();
    QVERIFY("MemberBase::voidFunction0" == *sg_memberString);
    *sg_memberString = "";
    QExtFunction< void > voidBoundMemberBaseFunctorP(&memberBase, &MemberBase::voidFunction0);
    voidBoundMemberBaseFunctorP();
    QVERIFY("MemberBase::voidFunction0" == *sg_memberString);

    *sg_memberString = "";
    QExtFunction< int > intBoundMemberBaseFunctorR(memberBase, &MemberBase::intFunction0);
    intBoundMemberBaseFunctorR();
    QVERIFY("MemberBase::intFunction0" == *sg_memberString);
    *sg_memberString = "";
    QExtFunction< int > intBoundMemberBaseFunctorP(&memberBase, &MemberBase::intFunction0);
    intBoundMemberBaseFunctorP();
    QVERIFY("MemberBase::intFunction0" == *sg_memberString);

    *sg_memberString = "";
    QExtFunction< double > doubleBoundMemberBaseFunctorR(memberBase, &MemberBase::doubleFunction0);
    doubleBoundMemberBaseFunctorR();
    QVERIFY("MemberBase::doubleFunction0" == *sg_memberString);
    *sg_memberString = "";
    QExtFunction< double > doubleBoundMemberBaseFunctorP(&memberBase, &MemberBase::doubleFunction0);
    doubleBoundMemberBaseFunctorP();
    QVERIFY("MemberBase::doubleFunction0" == *sg_memberString);
}

void QExtFunctionTest::testPolymorphismBoundFunctorWith0Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    *sg_memberString = "";
    QExtFunction< void > voidBoundMemberBaseFunctorR(dynamic_cast< MemberBase & >(member), &MemberBase::voidFunction0);
    voidBoundMemberBaseFunctorR();
    QVERIFY("Member::voidFunction0" == *sg_memberString);
    *sg_memberString = "";
    QExtFunction< void > voidBoundMemberBaseFunctorP(dynamic_cast< MemberBase * >(&member), &MemberBase::voidFunction0);
    voidBoundMemberBaseFunctorP();
    QVERIFY("Member::voidFunction0" == *sg_memberString);

    *sg_memberString = "";
    QExtFunction< int > intBoundMemberBaseFunctorR(dynamic_cast< MemberBase & >(member), &MemberBase::intFunction0);
    intBoundMemberBaseFunctorR();
    QVERIFY("Member::intFunction0" == *sg_memberString);
    *sg_memberString = "";
    QExtFunction< int > intBoundMemberBaseFunctorP(dynamic_cast< MemberBase * >(&member), &MemberBase::intFunction0);
    intBoundMemberBaseFunctorP();
    QVERIFY("Member::intFunction0" == *sg_memberString);

    *sg_memberString = "";
    QExtFunction< double > doubleBoundMemberBaseFunctorR(dynamic_cast< MemberBase & >(member), &MemberBase::doubleFunction0);
    doubleBoundMemberBaseFunctorR();
    QVERIFY("Member::doubleFunction0" == *sg_memberString);
    *sg_memberString = "";
    QExtFunction< double > doubleBoundMemberBaseFunctorP(dynamic_cast< MemberBase * >(&member), &MemberBase::doubleFunction0);
    doubleBoundMemberBaseFunctorP();
    QVERIFY("Member::doubleFunction0" == *sg_memberString);
}

//TODO ref test
void QExtFunctionTest::testBoundConstFunctorWith0Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QExtFunction< void > voidBoundConstMemberBaseFunctor(&memberBase, &MemberBase::voidConstFunction0);
    voidBoundConstMemberBaseFunctor();
    QVERIFY("MemberBase::voidConstFunction0" == *sg_memberString);
    QExtFunction< int > intBoundConstMemberBaseFunctor(&memberBase, &MemberBase::intConstFunction0);
    intBoundConstMemberBaseFunctor();
    QVERIFY("MemberBase::intConstFunction0" == *sg_memberString);
    QExtFunction< double > doubleBoundConstMemberBaseFunctor(&memberBase, &MemberBase::doubleConstFunction0);
    doubleBoundConstMemberBaseFunctor();
    QVERIFY("MemberBase::doubleConstFunction0" == *sg_memberString);
}

void QExtFunctionTest::testPolymorphismBoundConstFunctorWith0Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QExtFunction< void > voidBoundConstMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstFunction0);
    voidBoundConstMemberBaseFunctor();
    QVERIFY("Member::voidConstFunction0" == *sg_memberString);
    QExtFunction< int > intBoundConstMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::intConstFunction0);
    intBoundConstMemberBaseFunctor();
    QVERIFY("Member::intConstFunction0" == *sg_memberString);
    QExtFunction< double > doubleBoundConstMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstFunction0);
    doubleBoundConstMemberBaseFunctor();
    QVERIFY("Member::doubleConstFunction0" == *sg_memberString);
}

void QExtFunctionTest::testBoundVolatileFunctorWith0Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QExtFunction< void > voidBoundVolatileMemberBaseFunctor(&memberBase, &MemberBase::voidVolatileFunction0);
    voidBoundVolatileMemberBaseFunctor();
    QVERIFY("MemberBase::voidVolatileFunction0" == *sg_memberString);
    QExtFunction< int > intBoundVolatileMemberBaseFunctor(&memberBase, &MemberBase::intVolatileFunction0);
    intBoundVolatileMemberBaseFunctor();
    QVERIFY("MemberBase::intVolatileFunction0" == *sg_memberString);
    QExtFunction< double > doubleBoundVolatileMemberBaseFunctor(&memberBase, &MemberBase::doubleVolatileFunction0);
    doubleBoundVolatileMemberBaseFunctor();
    QVERIFY("MemberBase::doubleVolatileFunction0" == *sg_memberString);
}

void QExtFunctionTest::testPolymorphismBoundVolatileFunctorWith0Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QExtFunction< void > voidBoundVolatileMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::voidVolatileFunction0);
    voidBoundVolatileMemberBaseFunctor();
    QVERIFY("Member::voidVolatileFunction0" == *sg_memberString);
    QExtFunction< int > intBoundVolatileMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::intVolatileFunction0);
    intBoundVolatileMemberBaseFunctor();
    QVERIFY("Member::intVolatileFunction0" == *sg_memberString);
    QExtFunction< double > doubleBoundVolatileMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::doubleVolatileFunction0);
    doubleBoundVolatileMemberBaseFunctor();
    QVERIFY("Member::doubleVolatileFunction0" == *sg_memberString);
}

void QExtFunctionTest::testBoundConstVolatileFunctorWith0Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QExtFunction< void > voidBoundConstVolatileMemberBaseFunctor(&memberBase, &MemberBase::voidConstVolatileFunction0);
    voidBoundConstVolatileMemberBaseFunctor();
    QVERIFY("MemberBase::voidConstVolatileFunction0" == *sg_memberString);
    QExtFunction< int > intBoundConstVolatileMemberBaseFunctor(&memberBase, &MemberBase::intConstVolatileFunction0);
    intBoundConstVolatileMemberBaseFunctor();
    QVERIFY("MemberBase::intConstVolatileFunction0" == *sg_memberString);
    QExtFunction< double > doubleBoundConstVolatileMemberBaseFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction0);
    doubleBoundConstVolatileMemberBaseFunctor();
    QVERIFY("MemberBase::doubleConstVolatileFunction0" == *sg_memberString);
}

void QExtFunctionTest::testPolymorphismBoundConstVolatileFunctorWith0Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QExtFunction< void > voidBoundConstVolatileMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstVolatileFunction0);
    voidBoundConstVolatileMemberBaseFunctor();
    QVERIFY("Member::voidConstVolatileFunction0" == *sg_memberString);
    QExtFunction< int > intBoundConstVolatileMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::intConstVolatileFunction0);
    intBoundConstVolatileMemberBaseFunctor();
    QVERIFY("Member::intConstVolatileFunction0" == *sg_memberString);
    QExtFunction< double > doubleBoundConstVolatileMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstVolatileFunction0);
    doubleBoundConstVolatileMemberBaseFunctor();
    QVERIFY("Member::doubleConstVolatileFunction0" == *sg_memberString);
}

void QExtFunctionTest::testBoundFunctorWith1Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QExtFunction< void, int > voidBoundMemberBaseFunctor(&memberBase, &MemberBase::voidFunction1);
    voidBoundMemberBaseFunctor(1);
    QVERIFY("MemberBase::voidFunction1" == *sg_memberString);
    QExtFunction< int, int > intBoundMemberBaseFunctor(&memberBase, &MemberBase::intFunction1);
    QVERIFY(1 == intBoundMemberBaseFunctor(1));
    QExtFunction< double, double > doubleBoundMemberBaseFunctor(&memberBase, &MemberBase::doubleFunction1);
    QVERIFY(1.1 == doubleBoundMemberBaseFunctor(1.1));

    QExtFunction< void, bool > voidBoundMemberBaseFunctorB(&memberBase, &MemberBase::voidFunctionB1);
    voidBoundMemberBaseFunctorB(1);
    QVERIFY("MemberBase::voidFunctionB1" == *sg_memberString);
    QExtFunction< int, bool > intBoundMemberBaseFunctorB(&memberBase, &MemberBase::intFunctionB1);
    QVERIFY(1 == intBoundMemberBaseFunctorB(true));
    QVERIFY(0 == intBoundMemberBaseFunctorB(false));
    QExtFunction< double, bool > doubleBoundMemberBaseFunctorB(&memberBase, &MemberBase::doubleFunctionB1);
    QVERIFY(1 == doubleBoundMemberBaseFunctorB(true));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB(false));
}

void QExtFunctionTest::testPolymorphismBoundFunctorWith1Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QExtFunction< void, int > voidBoundMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::voidFunction1);
    voidBoundMemberBaseFunctor(1);
    QVERIFY("Member::voidFunction1" == *sg_memberString);
    QExtFunction< int, int > intBoundMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::intFunction1);
    QVERIFY(0 == intBoundMemberBaseFunctor(1));
    QExtFunction< double, double > doubleBoundMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::doubleFunction1);
    QVERIFY(0 == doubleBoundMemberBaseFunctor(1.1));

    QExtFunction< void, bool > voidBoundMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::voidFunctionB1);
    voidBoundMemberBaseFunctorB(1);
    QVERIFY("Member::voidFunctionB1" == *sg_memberString);
    QExtFunction< int, bool > intBoundMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::intFunctionB1);
    QVERIFY(1 == intBoundMemberBaseFunctorB(true));
    QVERIFY(0 == intBoundMemberBaseFunctorB(false));
    QExtFunction< double, bool > doubleBoundMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::doubleFunctionB1);
    QVERIFY(1 == doubleBoundMemberBaseFunctorB(true));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB(false));
}

void QExtFunctionTest::testBoundConstFunctorWith1Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QExtFunction< void, int > voidBoundConstMemberBaseFunctor(&memberBase, &MemberBase::voidConstFunction1);
    voidBoundConstMemberBaseFunctor(1);
    QVERIFY("MemberBase::voidConstFunction1" == *sg_memberString);
    QExtFunction< int, int > intBoundConstMemberBaseFunctor(&memberBase, &MemberBase::intConstFunction1);
    QVERIFY(1 == intBoundConstMemberBaseFunctor(1));
    QExtFunction< double, double > doubleBoundConstMemberBaseFunctor(&memberBase, &MemberBase::doubleConstFunction1);
    QVERIFY(1.1 == doubleBoundConstMemberBaseFunctor(1.1));

    QExtFunction< void, bool > voidBoundConstMemberBaseFunctorB(&memberBase, &MemberBase::voidConstFunctionB1);
    voidBoundConstMemberBaseFunctorB(1);
    QVERIFY("MemberBase::voidConstFunctionB1" == *sg_memberString);
    QExtFunction< int, bool > intBoundConstMemberBaseFunctorB(&memberBase, &MemberBase::intConstFunctionB1);
    QVERIFY(1 == intBoundConstMemberBaseFunctorB(true));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB(false));
    QExtFunction< double, bool > doubleBoundConstMemberBaseFunctorB(&memberBase, &MemberBase::doubleConstFunctionB1);
    QVERIFY(1 == doubleBoundConstMemberBaseFunctorB(true));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB(false));
}

void QExtFunctionTest::testPolymorphismBoundConstFunctorWith1Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QExtFunction< void, int > voidBoundConstMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstFunction1);
    voidBoundConstMemberBaseFunctor(1);
    QVERIFY("Member::voidConstFunction1" == *sg_memberString);
    QExtFunction< int, int > intBoundConstMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::intConstFunction1);
    QVERIFY(0 == intBoundConstMemberBaseFunctor(1));
    QExtFunction< double, double > doubleBoundConstMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstFunction1);
    QVERIFY(0 == doubleBoundConstMemberBaseFunctor(1.1));

    QExtFunction< void, bool > voidBoundConstMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstFunctionB1);
    voidBoundConstMemberBaseFunctorB(1);
    QVERIFY("Member::voidConstFunctionB1" == *sg_memberString);
    QExtFunction< int, bool > intBoundConstMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::intConstFunctionB1);
    QVERIFY(1 == intBoundConstMemberBaseFunctorB(true));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB(false));
    QExtFunction< double, bool > doubleBoundConstMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstFunctionB1);
    QVERIFY(1 == doubleBoundConstMemberBaseFunctorB(true));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB(false));
}

void QExtFunctionTest::testBoundVolatileFunctorWith1Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QExtFunction< void, int > voidBoundVolatileMemberBaseFunctor(&memberBase, &MemberBase::voidVolatileFunction1);
    voidBoundVolatileMemberBaseFunctor(1);
    QVERIFY("MemberBase::voidVolatileFunction1" == *sg_memberString);
    QExtFunction< int, int > intBoundVolatileMemberBaseFunctor(&memberBase, &MemberBase::intVolatileFunction1);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctor(1));
    QExtFunction< double, double > doubleBoundVolatileMemberBaseFunctor(&memberBase, &MemberBase::doubleVolatileFunction1);
    QVERIFY(1.1 == doubleBoundVolatileMemberBaseFunctor(1.1));

    QExtFunction< void, bool > voidBoundVolatileMemberBaseFunctorB(&memberBase, &MemberBase::voidVolatileFunctionB1);
    voidBoundVolatileMemberBaseFunctorB(1);
    QVERIFY("MemberBase::voidVolatileFunctionB1" == *sg_memberString);
    QExtFunction< int, bool > intBoundVolatileMemberBaseFunctorB(&memberBase, &MemberBase::intVolatileFunctionB1);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctorB(true));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB(false));
    QExtFunction< double, bool > doubleBoundVolatileMemberBaseFunctorB(&memberBase, &MemberBase::doubleVolatileFunctionB1);
    QVERIFY(1 == doubleBoundVolatileMemberBaseFunctorB(true));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB(false));
}

void QExtFunctionTest::testPolymorphismBoundVolatileFunctorWith1Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QExtFunction< void, int > voidBoundVolatileMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::voidVolatileFunction1);
    voidBoundVolatileMemberBaseFunctor(1);
    QVERIFY("Member::voidVolatileFunction1" == *sg_memberString);
    QExtFunction< int, int > intBoundVolatileMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::intVolatileFunction1);
    QVERIFY(0 == intBoundVolatileMemberBaseFunctor(1));
    QExtFunction< double, double > doubleBoundVolatileMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::doubleVolatileFunction1);
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctor(1.1));

    QExtFunction< void, bool > voidBoundVolatileMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::voidVolatileFunctionB1);
    voidBoundVolatileMemberBaseFunctorB(1);
    QVERIFY("Member::voidVolatileFunctionB1" == *sg_memberString);
    QExtFunction< int, bool > intBoundVolatileMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::intVolatileFunctionB1);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctorB(true));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB(false));
    QExtFunction< double, bool > doubleBoundVolatileMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::doubleVolatileFunctionB1);
    QVERIFY(1 == doubleBoundVolatileMemberBaseFunctorB(true));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB(false));
}

void QExtFunctionTest::testBoundConstVolatileFunctorWith1Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QExtFunction< void, int > voidBoundConstVolatileMemberBaseFunctor(&memberBase, &MemberBase::voidConstVolatileFunction1);
    voidBoundConstVolatileMemberBaseFunctor(1);
    QVERIFY("MemberBase::voidConstVolatileFunction1" == *sg_memberString);
    QExtFunction< int, int > intBoundConstVolatileMemberBaseFunctor(&memberBase, &MemberBase::intConstVolatileFunction1);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctor(1));
    QExtFunction< double, double > doubleBoundConstVolatileMemberBaseFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction1);
    QVERIFY(1.1 == doubleBoundConstVolatileMemberBaseFunctor(1.1));

    QExtFunction< void, bool > voidBoundConstVolatileMemberBaseFunctorB(&memberBase, &MemberBase::voidConstVolatileFunctionB1);
    voidBoundConstVolatileMemberBaseFunctorB(1);
    QVERIFY("MemberBase::voidConstVolatileFunctionB1" == *sg_memberString);
    QExtFunction< int, bool > intBoundConstVolatileMemberBaseFunctorB(&memberBase, &MemberBase::intConstVolatileFunctionB1);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctorB(true));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB(false));
    QExtFunction< double, bool > doubleBoundConstVolatileMemberBaseFunctorB(&memberBase, &MemberBase::doubleConstVolatileFunctionB1);
    QVERIFY(1 == doubleBoundConstVolatileMemberBaseFunctorB(true));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB(false));
}

void QExtFunctionTest::testPolymorphismBoundConstVolatileFunctorWith1Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QExtFunction< void, int > voidBoundConstVolatileMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstVolatileFunction1);
    voidBoundConstVolatileMemberBaseFunctor(1);
    QVERIFY("Member::voidConstVolatileFunction1" == *sg_memberString);
    QExtFunction< int, int > intBoundConstVolatileMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::intConstVolatileFunction1);
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctor(1));
    QExtFunction< double, double > doubleBoundConstVolatileMemberBaseFunctor(
                dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstVolatileFunction1);
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctor(1.1));

    QExtFunction< void, bool > voidBoundConstVolatileMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstVolatileFunctionB1);
    voidBoundConstVolatileMemberBaseFunctorB(1);
    QVERIFY("Member::voidConstVolatileFunctionB1" == *sg_memberString);
    QExtFunction< int, bool > intBoundConstVolatileMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::intConstVolatileFunctionB1);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctorB(true));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB(false));
    QExtFunction< double, bool > doubleBoundConstVolatileMemberBaseFunctorB(
                dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstVolatileFunctionB1);
    QVERIFY(1 == doubleBoundConstVolatileMemberBaseFunctorB(true));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB(false));
}

void QExtFunctionTest::testBoundFunctorWith2Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QExtFunction< void, int, int > voidBoundMemberBaseFunctor(&memberBase, &MemberBase::voidFunction2);
    voidBoundMemberBaseFunctor(1, 2);
    QVERIFY("MemberBase::voidFunction2" == *sg_memberString);
    QExtFunction< int, int, int > intBoundMemberBaseFunctor(&memberBase, &MemberBase::intFunction2);
    QVERIFY(1 + 2 == intBoundMemberBaseFunctor(1, 2));
    QExtFunction< double, double, double > doubleBoundMemberBaseFunctor(&memberBase, &MemberBase::doubleFunction2);
    QVERIFY(1.1 + 2.2 == doubleBoundMemberBaseFunctor(1.1, 2.2));

    QExtFunction< void, bool, int > voidBoundMemberBaseFunctorB(&memberBase, &MemberBase::voidFunctionB2);
    voidBoundMemberBaseFunctorB(true, 2);
    QVERIFY("MemberBase::voidFunctionB2" == *sg_memberString);
    QExtFunction< int, bool, int > intBoundMemberBaseFunctorB(&memberBase, &MemberBase::intFunctionB2);
    QVERIFY(2 == intBoundMemberBaseFunctorB(true, 2));
    QVERIFY(0 == intBoundMemberBaseFunctorB(false, 2));
    QExtFunction< double, bool, double > doubleBoundMemberBaseFunctorB(&memberBase, &MemberBase::doubleFunctionB2);
    QVERIFY(2.2 == doubleBoundMemberBaseFunctorB(true, 2.2));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB(false, 2.2));
}

void QExtFunctionTest::testPolymorphismBoundFunctorWith2Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QExtFunction< void, int, int > voidBoundMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::voidFunction2);
    voidBoundMemberBaseFunctor(1, 2);
    QVERIFY("Member::voidFunction2" == *sg_memberString);
    QExtFunction< int, int, int > intBoundMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::intFunction2);
    QVERIFY(0 == intBoundMemberBaseFunctor(1, 2));
    QExtFunction< double, double, double > doubleBoundMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::doubleFunction2);
    QVERIFY(0 == doubleBoundMemberBaseFunctor(1.1, 2.2));

    QExtFunction< void, bool, int > voidBoundMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::voidFunctionB2);
    voidBoundMemberBaseFunctorB(true, 2);
    QVERIFY("Member::voidFunctionB2" == *sg_memberString);
    QExtFunction< int, bool, int > intBoundMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::intFunctionB2);
    QVERIFY(1 == intBoundMemberBaseFunctorB(true, 2));
    QVERIFY(0 == intBoundMemberBaseFunctorB(false, 2));
    QExtFunction< double, bool, double > doubleBoundMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::doubleFunctionB2);
    QVERIFY(1 == doubleBoundMemberBaseFunctorB(true, 2.2));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB(false, 2.2));
}

void QExtFunctionTest::testBoundConstFunctorWith2Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QExtFunction< void, int, int > voidBoundConstMemberBaseFunctor(&memberBase, &MemberBase::voidConstFunction2);
    voidBoundConstMemberBaseFunctor(1, 2);
    QVERIFY("MemberBase::voidConstFunction2" == *sg_memberString);
    QExtFunction< int, int, int > intBoundConstMemberBaseFunctor(&memberBase, &MemberBase::intConstFunction2);
    QVERIFY(1 + 2 == intBoundConstMemberBaseFunctor(1, 2));
    QExtFunction< double, double, double > doubleBoundConstMemberBaseFunctor(&memberBase, &MemberBase::doubleConstFunction2);
    QVERIFY(1.1 + 2.2 == doubleBoundConstMemberBaseFunctor(1.1, 2.2));

    QExtFunction< void, bool, int > voidBoundConstMemberBaseFunctorB(&memberBase, &MemberBase::voidConstFunctionB2);
    voidBoundConstMemberBaseFunctorB(true, 2);
    QVERIFY("MemberBase::voidConstFunctionB2" == *sg_memberString);
    QExtFunction< int, bool, int > intBoundConstMemberBaseFunctorB(&memberBase, &MemberBase::intConstFunctionB2);
    QVERIFY(2 == intBoundConstMemberBaseFunctorB(true, 2));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB(false, 2));
    QExtFunction< double, bool, double > doubleBoundConstMemberBaseFunctorB(&memberBase, &MemberBase::doubleConstFunctionB2);
    QVERIFY(2.2 == doubleBoundConstMemberBaseFunctorB(true, 2.2));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB(false, 2.2));
}

void QExtFunctionTest::testPolymorphismBoundConstFunctorWith2Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QExtFunction< void, int, int > voidBoundConstMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstFunction2);
    voidBoundConstMemberBaseFunctor(1, 2);
    QVERIFY("Member::voidConstFunction2" == *sg_memberString);
    QExtFunction< int, int, int > intBoundConstMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::intConstFunction2);
    QVERIFY(0 == intBoundConstMemberBaseFunctor(1, 2));
    QExtFunction< double, double, double > doubleBoundConstMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstFunction2);
    QVERIFY(0 == doubleBoundConstMemberBaseFunctor(1.1, 2.2));

    QExtFunction< void, bool, int > voidBoundConstMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstFunctionB2);
    voidBoundConstMemberBaseFunctorB(true, 2);
    QVERIFY("Member::voidConstFunctionB2" == *sg_memberString);
    QExtFunction< int, bool, int > intBoundConstMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::intConstFunctionB2);
    QVERIFY(1 == intBoundConstMemberBaseFunctorB(true, 2));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB(false, 2));
    QExtFunction< double, bool, double > doubleBoundConstMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstFunctionB2);
    QVERIFY(1 == doubleBoundConstMemberBaseFunctorB(true, 2.2));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB(false, 2.2));
}

void QExtFunctionTest::testBoundVolatileFunctorWith2Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QExtFunction< void, int, int > voidBoundVolatileMemberBaseFunctor(&memberBase, &MemberBase::voidVolatileFunction2);
    voidBoundVolatileMemberBaseFunctor(1, 2);
    QVERIFY("MemberBase::voidVolatileFunction2" == *sg_memberString);
    QExtFunction< int, int, int > intBoundVolatileMemberBaseFunctor(&memberBase, &MemberBase::intVolatileFunction2);
    QVERIFY(1 + 2 == intBoundVolatileMemberBaseFunctor(1, 2));
    QExtFunction< double, double, double > doubleBoundVolatileMemberBaseFunctor(&memberBase, &MemberBase::doubleVolatileFunction2);
    QVERIFY(1.1 + 2.2 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2));

    QExtFunction< void, bool, int > voidBoundVolatileMemberBaseFunctorB(&memberBase, &MemberBase::voidVolatileFunctionB2);
    voidBoundVolatileMemberBaseFunctorB(true, 2);
    QVERIFY("MemberBase::voidVolatileFunctionB2" == *sg_memberString);
    QExtFunction< int, bool, int > intBoundVolatileMemberBaseFunctorB(&memberBase, &MemberBase::intVolatileFunctionB2);
    QVERIFY(2 == intBoundVolatileMemberBaseFunctorB(true, 2));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB(false, 2));
    QExtFunction< double, bool, double > doubleBoundVolatileMemberBaseFunctorB(&memberBase, &MemberBase::doubleVolatileFunctionB2);
    QVERIFY(2.2 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2));
}

void QExtFunctionTest::testPolymorphismBoundVolatileFunctorWith2Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QExtFunction< void, int, int > voidBoundVolatileMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::voidVolatileFunction2);
    voidBoundVolatileMemberBaseFunctor(1, 2);
    QVERIFY("Member::voidVolatileFunction2" == *sg_memberString);
    QExtFunction< int, int, int > intBoundVolatileMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::intVolatileFunction2);
    QVERIFY(0 == intBoundVolatileMemberBaseFunctor(1, 2));
    QExtFunction< double, double, double > doubleBoundVolatileMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::doubleVolatileFunction2);
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2));

    QExtFunction< void, bool, int > voidBoundVolatileMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::voidVolatileFunctionB2);
    voidBoundVolatileMemberBaseFunctorB(true, 2);
    QVERIFY("Member::voidVolatileFunctionB2" == *sg_memberString);
    QExtFunction< int, bool, int > intBoundVolatileMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::intVolatileFunctionB2);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctorB(true, 2));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB(false, 2));
    QExtFunction< double, bool, double > doubleBoundVolatileMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::doubleVolatileFunctionB2);
    QVERIFY(1 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2));
}

void QExtFunctionTest::testBoundConstVolatileFunctorWith2Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QExtFunction< void, int, int > voidBoundConstVolatileMemberBaseFunctor(&memberBase, &MemberBase::voidConstVolatileFunction2);
    voidBoundConstVolatileMemberBaseFunctor(1, 2);
    QVERIFY("MemberBase::voidConstVolatileFunction2" == *sg_memberString);
    QExtFunction< int, int, int > intBoundConstVolatileMemberBaseFunctor(&memberBase, &MemberBase::intConstVolatileFunction2);
    QVERIFY(1 + 2 == intBoundConstVolatileMemberBaseFunctor(1, 2));
    QExtFunction< double, double, double > doubleBoundConstVolatileMemberBaseFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction2);
    QVERIFY(1.1 + 2.2 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2));

    QExtFunction< void, bool, int > voidBoundConstVolatileMemberBaseFunctorB(&memberBase, &MemberBase::voidConstVolatileFunctionB2);
    voidBoundConstVolatileMemberBaseFunctorB(true, 2);
    QVERIFY("MemberBase::voidConstVolatileFunctionB2" == *sg_memberString);
    QExtFunction< int, bool, int > intBoundConstVolatileMemberBaseFunctorB(&memberBase, &MemberBase::intConstVolatileFunctionB2);
    QVERIFY(2 == intBoundConstVolatileMemberBaseFunctorB(true, 2));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB(false, 2));
    QExtFunction< double, bool, double > doubleBoundConstVolatileMemberBaseFunctorB(&memberBase, &MemberBase::doubleConstVolatileFunctionB2);
    QVERIFY(2.2 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2));
}

void QExtFunctionTest::testPolymorphismBoundConstVolatileFunctorWith2Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QExtFunction< void, int, int > voidBoundConstVolatileMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstVolatileFunction2);
    voidBoundConstVolatileMemberBaseFunctor(1, 2);
    QVERIFY("Member::voidConstVolatileFunction2" == *sg_memberString);
    QExtFunction< int, int, int > intBoundConstVolatileMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::intConstVolatileFunction2);
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctor(1, 2));
    QExtFunction< double, double, double > doubleBoundConstVolatileMemberBaseFunctor(
                dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstVolatileFunction2);
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2));

    QExtFunction< void, bool, int > voidBoundConstVolatileMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstVolatileFunctionB2);
    voidBoundConstVolatileMemberBaseFunctorB(true, 2);
    QVERIFY("Member::voidConstVolatileFunctionB2" == *sg_memberString);
    QExtFunction< int, bool, int > intBoundConstVolatileMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::intConstVolatileFunctionB2);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctorB(true, 2));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB(false, 2));
    QExtFunction< double, bool, double > doubleBoundConstVolatileMemberBaseFunctorB(
                dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstVolatileFunctionB2);
    QVERIFY(1 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2));
}

void QExtFunctionTest::testBoundFunctorWith3Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QExtFunction< void, int, int, int > voidBoundMemberBaseFunctor(&memberBase, &MemberBase::voidFunction3);
    voidBoundMemberBaseFunctor(1, 2, 3);
    QVERIFY("MemberBase::voidFunction3" == *sg_memberString);
    QExtFunction< int, int, int, int > intBoundMemberBaseFunctor(&memberBase, &MemberBase::intFunction3);
    QVERIFY(1 + 2 + 3 == intBoundMemberBaseFunctor(1, 2, 3));
    QExtFunction< double, double, double, double > doubleBoundMemberBaseFunctor(&memberBase, &MemberBase::doubleFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleBoundMemberBaseFunctor(1.1, 2.2, 3.3));

    QExtFunction< void, bool, int, int > voidBoundMemberBaseFunctorB(&memberBase, &MemberBase::voidFunctionB3);
    voidBoundMemberBaseFunctorB(true, 2, 3);
    QVERIFY("MemberBase::voidFunctionB3" == *sg_memberString);
    QExtFunction< int, bool, int, int > intBoundMemberBaseFunctorB(&memberBase, &MemberBase::intFunctionB3);
    QVERIFY(2 + 3 == intBoundMemberBaseFunctorB(true, 2, 3));
    QVERIFY(2 * 3 == intBoundMemberBaseFunctorB(false, 2, 3));
    QExtFunction< double, bool, double, double > doubleBoundMemberBaseFunctorB(&memberBase, &MemberBase::doubleFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleBoundMemberBaseFunctorB(true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleBoundMemberBaseFunctorB(false, 2.2, 3.3));
}

void QExtFunctionTest::testPolymorphismBoundFunctorWith3Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QExtFunction< void, int, int, int > voidBoundMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::voidFunction3);
    voidBoundMemberBaseFunctor(1, 2, 3);
    QVERIFY("Member::voidFunction3" == *sg_memberString);
    QExtFunction< int, int, int, int > intBoundMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::intFunction3);
    QVERIFY(0 == intBoundMemberBaseFunctor(1, 2, 3));
    QExtFunction< double, double, double, double > doubleBoundMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::doubleFunction3);
    QVERIFY(0 == doubleBoundMemberBaseFunctor(1.1, 2.2, 3.3));

    QExtFunction< void, bool, int, int > voidBoundMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::voidFunctionB3);
    voidBoundMemberBaseFunctorB(true, 2, 3);
    QVERIFY("Member::voidFunctionB3" == *sg_memberString);
    QExtFunction< int, bool, int, int > intBoundMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::intFunctionB3);
    QVERIFY(1 == intBoundMemberBaseFunctorB(true, 2, 3));
    QVERIFY(0 == intBoundMemberBaseFunctorB(false, 2, 3));
    QExtFunction< double, bool, double, double > doubleBoundMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::doubleFunctionB3);
    QVERIFY(1 == doubleBoundMemberBaseFunctorB(true, 2.2, 3.3));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB(false, 2.2, 3.3));
}

void QExtFunctionTest::testBoundConstFunctorWith3Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QExtFunction< void, int, int, int > voidBoundConstMemberBaseFunctor(&memberBase, &MemberBase::voidConstFunction3);
    voidBoundConstMemberBaseFunctor(1, 2, 3);
    QVERIFY("MemberBase::voidConstFunction3" == *sg_memberString);
    QExtFunction< int, int, int, int > intBoundConstMemberBaseFunctor(&memberBase, &MemberBase::intConstFunction3);
    QVERIFY(1 + 2 + 3 == intBoundConstMemberBaseFunctor(1, 2, 3));
    QExtFunction< double, double, double, double > doubleBoundConstMemberBaseFunctor(&memberBase, &MemberBase::doubleConstFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleBoundConstMemberBaseFunctor(1.1, 2.2, 3.3));

    QExtFunction< void, bool, int, int > voidBoundConstMemberBaseFunctorB(&memberBase, &MemberBase::voidConstFunctionB3);
    voidBoundConstMemberBaseFunctorB(true, 2, 3);
    QVERIFY("MemberBase::voidConstFunctionB3" == *sg_memberString);
    QExtFunction< int, bool, int, int > intBoundConstMemberBaseFunctorB(&memberBase, &MemberBase::intConstFunctionB3);
    QVERIFY(2 + 3 == intBoundConstMemberBaseFunctorB(true, 2, 3));
    QVERIFY(2 * 3 == intBoundConstMemberBaseFunctorB(false, 2, 3));
    QExtFunction< double, bool, double, double > doubleBoundConstMemberBaseFunctorB(&memberBase, &MemberBase::doubleConstFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleBoundConstMemberBaseFunctorB(true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleBoundConstMemberBaseFunctorB(false, 2.2, 3.3));
}

void QExtFunctionTest::testPolymorphismBoundConstFunctorWith3Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QExtFunction< void, int, int, int > voidBoundConstMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstFunction3);
    voidBoundConstMemberBaseFunctor(1, 2, 3);
    QVERIFY("Member::voidConstFunction3" == *sg_memberString);
    QExtFunction< int, int, int, int > intBoundConstMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::intConstFunction3);
    QVERIFY(0 == intBoundConstMemberBaseFunctor(1, 2, 3));
    QExtFunction< double, double, double, double > doubleBoundConstMemberBaseFunctor(
                dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstFunction3);
    QVERIFY(0 == doubleBoundConstMemberBaseFunctor(1.1, 2.2, 3.3));

    QExtFunction< void, bool, int, int > voidBoundConstMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstFunctionB3);
    voidBoundConstMemberBaseFunctorB(true, 2, 3);
    QVERIFY("Member::voidConstFunctionB3" == *sg_memberString);
    QExtFunction< int, bool, int, int > intBoundConstMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::intConstFunctionB3);
    QVERIFY(1 == intBoundConstMemberBaseFunctorB(true, 2, 3));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB(false, 2, 3));
    QExtFunction< double, bool, double, double > doubleBoundConstMemberBaseFunctorB(
                dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstFunctionB3);
    QVERIFY(1 == doubleBoundConstMemberBaseFunctorB(true, 2.2, 3.3));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB(false, 2.2, 3.3));
}

void QExtFunctionTest::testBoundVolatileFunctorWith3Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QExtFunction< void, int, int, int > voidBoundVolatileMemberBaseFunctor(&memberBase, &MemberBase::voidVolatileFunction3);
    voidBoundVolatileMemberBaseFunctor(1, 2, 3);
    QVERIFY("MemberBase::voidVolatileFunction3" == *sg_memberString);
    QExtFunction< int, int, int, int > intBoundVolatileMemberBaseFunctor(&memberBase, &MemberBase::intVolatileFunction3);
    QVERIFY(1 + 2 + 3 == intBoundVolatileMemberBaseFunctor(1, 2, 3));
    QExtFunction< double, double, double, double > doubleBoundVolatileMemberBaseFunctor(&memberBase, &MemberBase::doubleVolatileFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2, 3.3));

    QExtFunction< void, bool, int, int > voidBoundVolatileMemberBaseFunctorB(&memberBase, &MemberBase::voidVolatileFunctionB3);
    voidBoundVolatileMemberBaseFunctorB(true, 2, 3);
    QVERIFY("MemberBase::voidVolatileFunctionB3" == *sg_memberString);
    QExtFunction< int, bool, int, int > intBoundVolatileMemberBaseFunctorB(&memberBase, &MemberBase::intVolatileFunctionB3);
    QVERIFY(2 + 3 == intBoundVolatileMemberBaseFunctorB(true, 2, 3));
    QVERIFY(2 * 3 == intBoundVolatileMemberBaseFunctorB(false, 2, 3));
    QExtFunction< double, bool, double, double > doubleBoundVolatileMemberBaseFunctorB(&memberBase, &MemberBase::doubleVolatileFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2, 3.3));
}

void QExtFunctionTest::testPolymorphismBoundVolatileFunctorWith3Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QExtFunction< void, int, int, int > voidBoundVolatileMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::voidVolatileFunction3);
    voidBoundVolatileMemberBaseFunctor(1, 2, 3);
    QVERIFY("Member::voidVolatileFunction3" == *sg_memberString);
    QExtFunction< int, int, int, int > intBoundVolatileMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::intVolatileFunction3);
    QVERIFY(0 == intBoundVolatileMemberBaseFunctor(1, 2, 3));
    QExtFunction< double, double, double, double > doubleBoundVolatileMemberBaseFunctor(
                dynamic_cast< MemberBase * >(&member), &MemberBase::doubleVolatileFunction3);
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2, 3.3));

    QExtFunction< void, bool, int, int > voidBoundVolatileMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::voidVolatileFunctionB3);
    voidBoundVolatileMemberBaseFunctorB(true, 2, 3);
    QVERIFY("Member::voidVolatileFunctionB3" == *sg_memberString);
    QExtFunction< int, bool, int, int > intBoundVolatileMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::intVolatileFunctionB3);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctorB(true, 2, 3));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB(false, 2, 3));
    QExtFunction< double, bool, double, double > doubleBoundVolatileMemberBaseFunctorB(
                dynamic_cast< MemberBase * >(&member), &MemberBase::doubleVolatileFunctionB3);
    QVERIFY(1 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2, 3.3));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2, 3.3));
}

void QExtFunctionTest::testBoundConstVolatileFunctorWith3Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QExtFunction< void, int, int, int > voidBoundConstVolatileMemberBaseFunctor(&memberBase, &MemberBase::voidConstVolatileFunction3);
    voidBoundConstVolatileMemberBaseFunctor(1, 2, 3);
    QVERIFY("MemberBase::voidConstVolatileFunction3" == *sg_memberString);
    QExtFunction< int, int, int, int > intBoundConstVolatileMemberBaseFunctor(&memberBase, &MemberBase::intConstVolatileFunction3);
    QVERIFY(1 + 2 + 3 == intBoundConstVolatileMemberBaseFunctor(1, 2, 3));
    QExtFunction< double, double, double, double > doubleBoundConstVolatileMemberBaseFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2, 3.3));

    QExtFunction< void, bool, int, int > voidBoundConstVolatileMemberBaseFunctorB(&memberBase, &MemberBase::voidConstVolatileFunctionB3);
    voidBoundConstVolatileMemberBaseFunctorB(true, 2, 3);
    QVERIFY("MemberBase::voidConstVolatileFunctionB3" == *sg_memberString);
    QExtFunction< int, bool, int, int > intBoundConstVolatileMemberBaseFunctorB(&memberBase, &MemberBase::intConstVolatileFunctionB3);
    QVERIFY(2 + 3 == intBoundConstVolatileMemberBaseFunctorB(true, 2, 3));
    QVERIFY(2 * 3 == intBoundConstVolatileMemberBaseFunctorB(false, 2, 3));
    QExtFunction< double, bool, double, double > doubleBoundConstVolatileMemberBaseFunctorB(&memberBase, &MemberBase::doubleConstVolatileFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2, 3.3));
}

void QExtFunctionTest::testPolymorphismBoundConstVolatileFunctorWith3Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QExtFunction< void, int, int, int > voidBoundConstVolatileMemberBaseFunctor(
                dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstVolatileFunction3);
    voidBoundConstVolatileMemberBaseFunctor(1, 2, 3);
    QVERIFY("Member::voidConstVolatileFunction3" == *sg_memberString);
    QExtFunction< int, int, int, int > intBoundConstVolatileMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::intConstVolatileFunction3);
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctor(1, 2, 3));
    QExtFunction< double, double, double, double > doubleBoundConstVolatileMemberBaseFunctor(
                dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstVolatileFunction3);
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2, 3.3));

    QExtFunction< void, bool, int, int > voidBoundConstVolatileMemberBaseFunctorB(
                dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstVolatileFunctionB3);
    voidBoundConstVolatileMemberBaseFunctorB(true, 2, 3);
    QVERIFY("Member::voidConstVolatileFunctionB3" == *sg_memberString);
    QExtFunction< int, bool, int, int > intBoundConstVolatileMemberBaseFunctorB(
                dynamic_cast< MemberBase * >(&member), &MemberBase::intConstVolatileFunctionB3);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctorB(true, 2, 3));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB(false, 2, 3));
    QExtFunction< double, bool, double, double > doubleBoundConstVolatileMemberBaseFunctorB(
                dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstVolatileFunctionB3);
    QVERIFY(1 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2, 3.3));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2, 3.3));
}

void QExtFunctionTest::testBoundFunctorWith4Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QExtFunction< void, int, int, int, int > voidBoundMemberBaseFunctor(&memberBase, &MemberBase::voidFunction4);
    voidBoundMemberBaseFunctor(1, 2, 3, 4);
    QVERIFY("MemberBase::voidFunction4" == *sg_memberString);
    QExtFunction< int, int, int, int, int > intBoundMemberBaseFunctor(&memberBase, &MemberBase::intFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intBoundMemberBaseFunctor(1, 2, 3, 4));
    QExtFunction< double, double, double, double, double > doubleBoundMemberBaseFunctor(&memberBase, &MemberBase::doubleFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleBoundMemberBaseFunctor(1.1, 2.2, 3.3, 4.4));

    QExtFunction< void, bool, int, int, int > voidBoundMemberBaseFunctorB(&memberBase, &MemberBase::voidFunctionB4);
    voidBoundMemberBaseFunctorB(true, 2, 3, 4);
    QVERIFY("MemberBase::voidFunctionB4" == *sg_memberString);
    QExtFunction< int, bool, int, int, int > intBoundMemberBaseFunctorB(&memberBase, &MemberBase::intFunctionB4);
    QVERIFY(2 + 3 + 4 == intBoundMemberBaseFunctorB(true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intBoundMemberBaseFunctorB(false, 2, 3, 4));
    QExtFunction< double, bool, double, double, double > doubleBoundMemberBaseFunctorB(&memberBase, &MemberBase::doubleFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleBoundMemberBaseFunctorB(true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleBoundMemberBaseFunctorB(false, 2.2, 3.3, 4.4));
}

void QExtFunctionTest::testPolymorphismBoundFunctorWith4Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QExtFunction< void, int, int, int, int > voidBoundMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::voidFunction4);
    voidBoundMemberBaseFunctor(1, 2, 3, 4);
    QVERIFY("Member::voidFunction4" == *sg_memberString);
    QExtFunction< int, int, int, int, int > intBoundMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::intFunction4);
    QVERIFY(0 == intBoundMemberBaseFunctor(1, 2, 3, 4));
    QExtFunction< double, double, double, double, double > doubleBoundMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::doubleFunction4);
    QVERIFY(0 == doubleBoundMemberBaseFunctor(1.1, 2.2, 3.3, 4.4));

    QExtFunction< void, bool, int, int, int > voidBoundMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::voidFunctionB4);
    voidBoundMemberBaseFunctorB(true, 2, 3, 4);
    QVERIFY("Member::voidFunctionB4" == *sg_memberString);
    QExtFunction< int, bool, int, int, int > intBoundMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::intFunctionB4);
    QVERIFY(1 == intBoundMemberBaseFunctorB(true, 2, 3, 4));
    QVERIFY(0 == intBoundMemberBaseFunctorB(false, 2, 3, 4));
    QExtFunction< double, bool, double, double, double > doubleBoundMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::doubleFunctionB4);
    QVERIFY(1 == doubleBoundMemberBaseFunctorB(true, 2.2, 3.3, 4.4));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB(false, 2.2, 3.3, 4.4));
}

void QExtFunctionTest::testBoundConstFunctorWith4Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QExtFunction< void, int, int, int, int > voidBoundConstMemberBaseFunctor(&memberBase, &MemberBase::voidConstFunction4);
    voidBoundConstMemberBaseFunctor(1, 2, 3, 4);
    QVERIFY("MemberBase::voidConstFunction4" == *sg_memberString);
    QExtFunction< int, int, int, int, int > intBoundConstMemberBaseFunctor(&memberBase, &MemberBase::intConstFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intBoundConstMemberBaseFunctor(1, 2, 3, 4));
    QExtFunction< double, double, double, double, double > doubleBoundConstMemberBaseFunctor(&memberBase, &MemberBase::doubleConstFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleBoundConstMemberBaseFunctor(1.1, 2.2, 3.3, 4.4));

    QExtFunction< void, bool, int, int, int > voidBoundConstMemberBaseFunctorB(&memberBase, &MemberBase::voidConstFunctionB4);
    voidBoundConstMemberBaseFunctorB(true, 2, 3, 4);
    QVERIFY("MemberBase::voidConstFunctionB4" == *sg_memberString);
    QExtFunction< int, bool, int, int, int > intBoundConstMemberBaseFunctorB(&memberBase, &MemberBase::intConstFunctionB4);
    QVERIFY(2 + 3 + 4 == intBoundConstMemberBaseFunctorB(true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intBoundConstMemberBaseFunctorB(false, 2, 3, 4));
    QExtFunction< double, bool, double, double, double > doubleBoundConstMemberBaseFunctorB(&memberBase, &MemberBase::doubleConstFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleBoundConstMemberBaseFunctorB(true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleBoundConstMemberBaseFunctorB(false, 2.2, 3.3, 4.4));
}

void QExtFunctionTest::testPolymorphismBoundConstFunctorWith4Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QExtFunction< void, int, int, int, int > voidBoundConstMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstFunction4);
    voidBoundConstMemberBaseFunctor(1, 2, 3, 4);
    QVERIFY("Member::voidConstFunction4" == *sg_memberString);
    QExtFunction< int, int, int, int, int > intBoundConstMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::intConstFunction4);
    QVERIFY(0 == intBoundConstMemberBaseFunctor(1, 2, 3, 4));
    QExtFunction< double, double, double, double, double > doubleBoundConstMemberBaseFunctor(
                dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstFunction4);
    QVERIFY(0 == doubleBoundConstMemberBaseFunctor(1.1, 2.2, 3.3, 4.4));

    QExtFunction< void, bool, int, int, int > voidBoundConstMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstFunctionB4);
    voidBoundConstMemberBaseFunctorB(true, 2, 3, 4);
    QVERIFY("Member::voidConstFunctionB4" == *sg_memberString);
    QExtFunction< int, bool, int, int, int > intBoundConstMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::intConstFunctionB4);
    QVERIFY(1 == intBoundConstMemberBaseFunctorB(true, 2, 3, 4));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB(false, 2, 3, 4));
    QExtFunction< double, bool, double, double, double > doubleBoundConstMemberBaseFunctorB(
                dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstFunctionB4);
    QVERIFY(1 == doubleBoundConstMemberBaseFunctorB(true, 2.2, 3.3, 4.4));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB(false, 2.2, 3.3, 4.4));
}

void QExtFunctionTest::testBoundVolatileFunctorWith4Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QExtFunction< void, int, int, int, int > voidBoundVolatileMemberBaseFunctor(&memberBase, &MemberBase::voidVolatileFunction4);
    voidBoundVolatileMemberBaseFunctor(1, 2, 3, 4);
    QVERIFY("MemberBase::voidVolatileFunction4" == *sg_memberString);
    QExtFunction< int, int, int, int, int > intBoundVolatileMemberBaseFunctor(&memberBase, &MemberBase::intVolatileFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intBoundVolatileMemberBaseFunctor(1, 2, 3, 4));
    QExtFunction< double, double, double, double, double > doubleBoundVolatileMemberBaseFunctor(&memberBase, &MemberBase::doubleVolatileFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4));

    QExtFunction< void, bool, int, int, int > voidBoundVolatileMemberBaseFunctorB(&memberBase, &MemberBase::voidVolatileFunctionB4);
    voidBoundVolatileMemberBaseFunctorB(true, 2, 3, 4);
    QVERIFY("MemberBase::voidVolatileFunctionB4" == *sg_memberString);
    QExtFunction< int, bool, int, int, int > intBoundVolatileMemberBaseFunctorB(&memberBase, &MemberBase::intVolatileFunctionB4);
    QVERIFY(2 + 3 + 4 == intBoundVolatileMemberBaseFunctorB(true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intBoundVolatileMemberBaseFunctorB(false, 2, 3, 4));
    QExtFunction< double, bool, double, double, double > doubleBoundVolatileMemberBaseFunctorB(&memberBase, &MemberBase::doubleVolatileFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4));
}

void QExtFunctionTest::testPolymorphismBoundVolatileFunctorWith4Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QExtFunction< void, int, int, int, int > voidBoundVolatileMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::voidVolatileFunction4);
    voidBoundVolatileMemberBaseFunctor(1, 2, 3, 4);
    QVERIFY("Member::voidVolatileFunction4" == *sg_memberString);
    QExtFunction< int, int, int, int, int > intBoundVolatileMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::intVolatileFunction4);
    QVERIFY(0 == intBoundVolatileMemberBaseFunctor(1, 2, 3, 4));
    QExtFunction< double, double, double, double, double > doubleBoundVolatileMemberBaseFunctor(
                dynamic_cast< MemberBase * >(&member), &MemberBase::doubleVolatileFunction4);
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4));

    QExtFunction< void, bool, int, int, int > voidBoundVolatileMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::voidVolatileFunctionB4);
    voidBoundVolatileMemberBaseFunctorB(true, 2, 3, 4);
    QVERIFY("Member::voidVolatileFunctionB4" == *sg_memberString);
    QExtFunction< int, bool, int, int, int > intBoundVolatileMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::intVolatileFunctionB4);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctorB(true, 2, 3, 4));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB(false, 2, 3, 4));
    QExtFunction< double, bool, double, double, double > doubleBoundVolatileMemberBaseFunctorB(
                dynamic_cast< MemberBase * >(&member), &MemberBase::doubleVolatileFunctionB4);
    QVERIFY(1 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4));
}

void QExtFunctionTest::testBoundConstVolatileFunctorWith4Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QExtFunction< void, int, int, int, int > voidBoundConstVolatileMemberBaseFunctor(&memberBase, &MemberBase::voidConstVolatileFunction4);
    voidBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4);
    QVERIFY("MemberBase::voidConstVolatileFunction4" == *sg_memberString);
    QExtFunction< int, int, int, int, int > intBoundConstVolatileMemberBaseFunctor(&memberBase, &MemberBase::intConstVolatileFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4));
    QExtFunction< double, double, double, double, double > doubleBoundConstVolatileMemberBaseFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4));

    QExtFunction< void, bool, int, int, int > voidBoundConstVolatileMemberBaseFunctorB(&memberBase, &MemberBase::voidConstVolatileFunctionB4);
    voidBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4);
    QVERIFY("MemberBase::voidConstVolatileFunctionB4" == *sg_memberString);
    QExtFunction< int, bool, int, int, int > intBoundConstVolatileMemberBaseFunctorB(&memberBase, &MemberBase::intConstVolatileFunctionB4);
    QVERIFY(2 + 3 + 4 == intBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intBoundConstVolatileMemberBaseFunctorB(false, 2, 3, 4));
    QExtFunction< double, bool, double, double, double > doubleBoundConstVolatileMemberBaseFunctorB(&memberBase, &MemberBase::doubleConstVolatileFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4));
}

void QExtFunctionTest::testPolymorphismBoundConstVolatileFunctorWith4Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QExtFunction< void, int, int, int, int > voidBoundConstVolatileMemberBaseFunctor(
                dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstVolatileFunction4);
    voidBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4);
    QVERIFY("Member::voidConstVolatileFunction4" == *sg_memberString);
    QExtFunction< int, int, int, int, int > intBoundConstVolatileMemberBaseFunctor(
                dynamic_cast< MemberBase * >(&member), &MemberBase::intConstVolatileFunction4);
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4));
    QExtFunction< double, double, double, double, double > doubleBoundConstVolatileMemberBaseFunctor(
                dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstVolatileFunction4);
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4));

    QExtFunction< void, bool, int, int, int > voidBoundConstVolatileMemberBaseFunctorB(
                dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstVolatileFunctionB4);
    voidBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4);
    QVERIFY("Member::voidConstVolatileFunctionB4" == *sg_memberString);
    QExtFunction< int, bool, int, int, int > intBoundConstVolatileMemberBaseFunctorB(
                dynamic_cast< MemberBase * >(&member), &MemberBase::intConstVolatileFunctionB4);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB(false, 2, 3, 4));
    QExtFunction< double, bool, double, double, double > doubleBoundConstVolatileMemberBaseFunctorB(
                dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstVolatileFunctionB4);
    QVERIFY(1 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4));
}

void QExtFunctionTest::testBoundFunctorWith5Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QExtFunction< void, int, int, int, int, int > voidBoundMemberBaseFunctor(&memberBase, &MemberBase::voidFunction5);
    voidBoundMemberBaseFunctor(1, 2, 3, 4, 5);
    QVERIFY("MemberBase::voidFunction5" == *sg_memberString);
    QExtFunction< int, int, int, int, int, int > intBoundMemberBaseFunctor(&memberBase, &MemberBase::intFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intBoundMemberBaseFunctor(1, 2, 3, 4, 5));
    QExtFunction< double, double, double, double, double, double > doubleBoundMemberBaseFunctor(&memberBase, &MemberBase::doubleFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleBoundMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5));

    QExtFunction< void, bool, int, int, int, int > voidBoundMemberBaseFunctorB(&memberBase, &MemberBase::voidFunctionB5);
    voidBoundMemberBaseFunctorB(true, 2, 3, 4, 5);
    QVERIFY("MemberBase::voidFunctionB5" == *sg_memberString);
    QExtFunction< int, bool, int, int, int, int > intBoundMemberBaseFunctorB(&memberBase, &MemberBase::intFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intBoundMemberBaseFunctorB(true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intBoundMemberBaseFunctorB(false, 2, 3, 4, 5));
    QExtFunction< double, bool, double, double, double, double > doubleBoundMemberBaseFunctorB(&memberBase, &MemberBase::doubleFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleBoundMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleBoundMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5));
}

void QExtFunctionTest::testPolymorphismBoundFunctorWith5Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QExtFunction< void, int, int, int, int, int > voidBoundMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::voidFunction5);
    voidBoundMemberBaseFunctor(1, 2, 3, 4, 5);
    QVERIFY("Member::voidFunction5" == *sg_memberString);
    QExtFunction< int, int, int, int, int, int > intBoundMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::intFunction5);
    QVERIFY(0 == intBoundMemberBaseFunctor(1, 2, 3, 4, 5));
    QExtFunction< double, double, double, double, double, double > doubleBoundMemberBaseFunctor(
                dynamic_cast< MemberBase * >(&member), &MemberBase::doubleFunction5);
    QVERIFY(0 == doubleBoundMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5));

    QExtFunction< void, bool, int, int, int, int > voidBoundMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::voidFunctionB5);
    voidBoundMemberBaseFunctorB(true, 2, 3, 4, 5);
    QVERIFY("Member::voidFunctionB5" == *sg_memberString);
    QExtFunction< int, bool, int, int, int, int > intBoundMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::intFunctionB5);
    QVERIFY(1 == intBoundMemberBaseFunctorB(true, 2, 3, 4, 5));
    QVERIFY(0 == intBoundMemberBaseFunctorB(false, 2, 3, 4, 5));
    QExtFunction< double, bool, double, double, double, double > doubleBoundMemberBaseFunctorB(
                dynamic_cast< MemberBase * >(&member), &MemberBase::doubleFunctionB5);
    QVERIFY(1 == doubleBoundMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5));
}

void QExtFunctionTest::testBoundConstFunctorWith5Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QExtFunction< void, int, int, int, int, int > voidBoundConstMemberBaseFunctor(&memberBase, &MemberBase::voidConstFunction5);
    voidBoundConstMemberBaseFunctor(1, 2, 3, 4, 5);
    QVERIFY("MemberBase::voidConstFunction5" == *sg_memberString);
    QExtFunction< int, int, int, int, int, int > intBoundConstMemberBaseFunctor(&memberBase, &MemberBase::intConstFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intBoundConstMemberBaseFunctor(1, 2, 3, 4, 5));
    QExtFunction< double, double, double, double, double, double > doubleBoundConstMemberBaseFunctor(&memberBase, &MemberBase::doubleConstFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleBoundConstMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5));

    QExtFunction< void, bool, int, int, int, int > voidBoundConstMemberBaseFunctorB(&memberBase, &MemberBase::voidConstFunctionB5);
    voidBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5);
    QVERIFY("MemberBase::voidConstFunctionB5" == *sg_memberString);
    QExtFunction< int, bool, int, int, int, int > intBoundConstMemberBaseFunctorB(&memberBase, &MemberBase::intConstFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intBoundConstMemberBaseFunctorB(false, 2, 3, 4, 5));
    QExtFunction< double, bool, double, double, double, double > doubleBoundConstMemberBaseFunctorB(&memberBase, &MemberBase::doubleConstFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleBoundConstMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleBoundConstMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5));
}

void QExtFunctionTest::testPolymorphismBoundConstFunctorWith5Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QExtFunction< void, int, int, int, int, int > voidBoundConstMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstFunction5);
    voidBoundConstMemberBaseFunctor(1, 2, 3, 4, 5);
    QVERIFY("Member::voidConstFunction5" == *sg_memberString);
    QExtFunction< int, int, int, int, int, int > intBoundConstMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::intConstFunction5);
    QVERIFY(0 == intBoundConstMemberBaseFunctor(1, 2, 3, 4, 5));
    QExtFunction< double, double, double, double, double, double > doubleBoundConstMemberBaseFunctor(
                dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstFunction5);
    QVERIFY(0 == doubleBoundConstMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5));

    QExtFunction< void, bool, int, int, int, int > voidBoundConstMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstFunctionB5);
    voidBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5);
    QVERIFY("Member::voidConstFunctionB5" == *sg_memberString);
    QExtFunction< int, bool, int, int, int, int > intBoundConstMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::intConstFunctionB5);
    QVERIFY(1 == intBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB(false, 2, 3, 4, 5));
    QExtFunction< double, bool, double, double, double, double > doubleBoundConstMemberBaseFunctorB(
                dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstFunctionB5);
    QVERIFY(1 == doubleBoundConstMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5));
}

void QExtFunctionTest::testBoundVolatileFunctorWith5Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QExtFunction< void, int, int, int, int, int > voidBoundVolatileMemberBaseFunctor(&memberBase, &MemberBase::voidVolatileFunction5);
    voidBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5);
    QVERIFY("MemberBase::voidVolatileFunction5" == *sg_memberString);
    QExtFunction< int, int, int, int, int, int > intBoundVolatileMemberBaseFunctor(&memberBase, &MemberBase::intVolatileFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5));
    QExtFunction< double, double, double, double, double, double > doubleBoundVolatileMemberBaseFunctor(&memberBase, &MemberBase::doubleVolatileFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5));

    QExtFunction< void, bool, int, int, int, int > voidBoundVolatileMemberBaseFunctorB(&memberBase, &MemberBase::voidVolatileFunctionB5);
    voidBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5);
    QVERIFY("MemberBase::voidVolatileFunctionB5" == *sg_memberString);
    QExtFunction< int, bool, int, int, int, int > intBoundVolatileMemberBaseFunctorB(&memberBase, &MemberBase::intVolatileFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intBoundVolatileMemberBaseFunctorB(false, 2, 3, 4, 5));
    QExtFunction< double, bool, double, double, double, double > doubleBoundVolatileMemberBaseFunctorB(&memberBase, &MemberBase::doubleVolatileFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5));
}

void QExtFunctionTest::testPolymorphismBoundVolatileFunctorWith5Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QExtFunction< void, int, int, int, int, int > voidBoundVolatileMemberBaseFunctor(
                dynamic_cast< MemberBase * >(&member), &MemberBase::voidVolatileFunction5);
    voidBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5);
    QVERIFY("Member::voidVolatileFunction5" == *sg_memberString);
    QExtFunction< int, int, int, int, int, int > intBoundVolatileMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::intVolatileFunction5);
    QVERIFY(0 == intBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5));
    QExtFunction< double, double, double, double, double, double > doubleBoundVolatileMemberBaseFunctor(
                dynamic_cast< MemberBase * >(&member), &MemberBase::doubleVolatileFunction5);
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5));

    QExtFunction< void, bool, int, int, int, int > voidBoundVolatileMemberBaseFunctorB(
                dynamic_cast< MemberBase * >(&member), &MemberBase::voidVolatileFunctionB5);
    voidBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5);
    QVERIFY("Member::voidVolatileFunctionB5" == *sg_memberString);
    QExtFunction< int, bool, int, int, int, int > intBoundVolatileMemberBaseFunctorB(
                dynamic_cast< MemberBase * >(&member), &MemberBase::intVolatileFunctionB5);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB(false, 2, 3, 4, 5));
    QExtFunction< double, bool, double, double, double, double > doubleBoundVolatileMemberBaseFunctorB(
                dynamic_cast< MemberBase * >(&member), &MemberBase::doubleVolatileFunctionB5);
    QVERIFY(1 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5));
}

void QExtFunctionTest::testBoundConstVolatileFunctorWith5Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QExtFunction< void, int, int, int, int, int > voidBoundConstVolatileMemberBaseFunctor(&memberBase, &MemberBase::voidConstVolatileFunction5);
    voidBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5);
    QVERIFY("MemberBase::voidConstVolatileFunction5" == *sg_memberString);
    QExtFunction< int, int, int, int, int, int > intBoundConstVolatileMemberBaseFunctor(&memberBase, &MemberBase::intConstVolatileFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5));
    QExtFunction< double, double, double, double, double, double > doubleBoundConstVolatileMemberBaseFunctor(
                &memberBase, &MemberBase::doubleConstVolatileFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5));

    QExtFunction< void, bool, int, int, int, int > voidBoundConstVolatileMemberBaseFunctorB(&memberBase, &MemberBase::voidConstVolatileFunctionB5);
    voidBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5);
    QVERIFY("MemberBase::voidConstVolatileFunctionB5" == *sg_memberString);
    QExtFunction< int, bool, int, int, int, int > intBoundConstVolatileMemberBaseFunctorB(&memberBase, &MemberBase::intConstVolatileFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intBoundConstVolatileMemberBaseFunctorB(false, 2, 3, 4, 5));
    QExtFunction< double, bool, double, double, double, double > doubleBoundConstVolatileMemberBaseFunctorB(
                &memberBase, &MemberBase::doubleConstVolatileFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5));
}

void QExtFunctionTest::testPolymorphismBoundConstVolatileFunctorWith5Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QExtFunction< void, int, int, int, int, int > voidBoundConstVolatileMemberBaseFunctor(
                dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstVolatileFunction5);
    voidBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5);
    QVERIFY("Member::voidConstVolatileFunction5" == *sg_memberString);
    QExtFunction< int, int, int, int, int, int > intBoundConstVolatileMemberBaseFunctor(
                dynamic_cast< MemberBase * >(&member), &MemberBase::intConstVolatileFunction5);
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5));
    QExtFunction< double, double, double, double, double, double > doubleBoundConstVolatileMemberBaseFunctor(
                dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstVolatileFunction5);
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5));

    QExtFunction< void, bool, int, int, int, int > voidBoundConstVolatileMemberBaseFunctorB(
                dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstVolatileFunctionB5);
    voidBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5);
    QVERIFY("Member::voidConstVolatileFunctionB5" == *sg_memberString);
    QExtFunction< int, bool, int, int, int, int > intBoundConstVolatileMemberBaseFunctorB(
                dynamic_cast< MemberBase * >(&member), &MemberBase::intConstVolatileFunctionB5);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB(false, 2, 3, 4, 5));
    QExtFunction< double, bool, double, double, double, double > doubleBoundConstVolatileMemberBaseFunctorB(
                dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstVolatileFunctionB5);
    QVERIFY(1 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5));
}

void QExtFunctionTest::testBoundFunctorWith6Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QExtFunction< void, int, int, int, int, int, int > voidBoundMemberBaseFunctor(&memberBase, &MemberBase::voidFunction6);
    voidBoundMemberBaseFunctor(1, 2, 3, 4, 5, 6);
    QVERIFY("MemberBase::voidFunction6" == *sg_memberString);
    QExtFunction< int, int, int, int, int, int, int > intBoundMemberBaseFunctor(&memberBase, &MemberBase::intFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intBoundMemberBaseFunctor(1, 2, 3, 4, 5, 6));
    QExtFunction< double, double, double, double, double, double, double > doubleBoundMemberBaseFunctor(&memberBase, &MemberBase::doubleFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QExtFunction< void, bool, int, int, int, int, int > voidBoundMemberBaseFunctorB(&memberBase, &MemberBase::voidFunctionB6);
    voidBoundMemberBaseFunctorB(true, 2, 3, 4, 5, 6);
    QVERIFY("MemberBase::voidFunctionB6" == *sg_memberString);
    QExtFunction< int, bool, int, int, int, int, int > intBoundMemberBaseFunctorB(&memberBase, &MemberBase::intFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intBoundMemberBaseFunctorB(true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intBoundMemberBaseFunctorB(false, 2, 3, 4, 5, 6));
    QExtFunction< double, bool, double, double, double, double, double > doubleBoundMemberBaseFunctorB(&memberBase, &MemberBase::doubleFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleBoundMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6));
}

void QExtFunctionTest::testPolymorphismBoundFunctorWith6Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QExtFunction< void, int, int, int, int, int, int > voidBoundMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::voidFunction6);
    voidBoundMemberBaseFunctor(1, 2, 3, 4, 5, 6);
    QVERIFY("Member::voidFunction6" == *sg_memberString);
    QExtFunction< int, int, int, int, int, int, int > intBoundMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::intFunction6);
    QVERIFY(0 == intBoundMemberBaseFunctor(1, 2, 3, 4, 5, 6));
    QExtFunction< double, double, double, double, double, double, double > doubleBoundMemberBaseFunctor(
                dynamic_cast< MemberBase * >(&member), &MemberBase::doubleFunction6);
    QVERIFY(0 == doubleBoundMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QExtFunction< void, bool, int, int, int, int, int > voidBoundMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::voidFunctionB6);
    voidBoundMemberBaseFunctorB(true, 2, 3, 4, 5, 6);
    QVERIFY("Member::voidFunctionB6" == *sg_memberString);
    QExtFunction< int, bool, int, int, int, int, int > intBoundMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::intFunctionB6);
    QVERIFY(1 == intBoundMemberBaseFunctorB(true, 2, 3, 4, 5, 6));
    QVERIFY(0 == intBoundMemberBaseFunctorB(false, 2, 3, 4, 5, 6));
    QExtFunction< double, bool, double, double, double, double, double > doubleBoundMemberBaseFunctorB(
                dynamic_cast< MemberBase * >(&member), &MemberBase::doubleFunctionB6);
    QVERIFY(1 == doubleBoundMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6));
}

void QExtFunctionTest::testBoundConstFunctorWith6Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QExtFunction< void, int, int, int, int, int, int > voidBoundConstMemberBaseFunctor(&memberBase, &MemberBase::voidConstFunction6);
    voidBoundConstMemberBaseFunctor(1, 2, 3, 4, 5, 6);
    QVERIFY("MemberBase::voidConstFunction6" == *sg_memberString);
    QExtFunction< int, int, int, int, int, int, int > intBoundConstMemberBaseFunctor(&memberBase, &MemberBase::intConstFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intBoundConstMemberBaseFunctor(1, 2, 3, 4, 5, 6));
    QExtFunction< double, double, double, double, double, double, double > doubleBoundConstMemberBaseFunctor(&memberBase, &MemberBase::doubleConstFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundConstMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QExtFunction< void, bool, int, int, int, int, int > voidBoundConstMemberBaseFunctorB(&memberBase, &MemberBase::voidConstFunctionB6);
    voidBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5, 6);
    QVERIFY("MemberBase::voidConstFunctionB6" == *sg_memberString);
    QExtFunction< int, bool, int, int, int, int, int > intBoundConstMemberBaseFunctorB(&memberBase, &MemberBase::intConstFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intBoundConstMemberBaseFunctorB(false, 2, 3, 4, 5, 6));
    QExtFunction< double, bool, double, double, double, double, double > doubleBoundConstMemberBaseFunctorB(&memberBase, &MemberBase::doubleConstFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundConstMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleBoundConstMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6));
}

void QExtFunctionTest::testPolymorphismBoundConstFunctorWith6Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QExtFunction< void, int, int, int, int, int, int > voidBoundConstMemberBaseFunctor(
                dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstFunction6);
    voidBoundConstMemberBaseFunctor(1, 2, 3, 4, 5, 6);
    QVERIFY("Member::voidConstFunction6" == *sg_memberString);
    QExtFunction< int, int, int, int, int, int, int > intBoundConstMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::intConstFunction6);
    QVERIFY(0 == intBoundConstMemberBaseFunctor(1, 2, 3, 4, 5, 6));
    QExtFunction< double, double, double, double, double, double, double > doubleBoundConstMemberBaseFunctor(
                dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstFunction6);
    QVERIFY(0 == doubleBoundConstMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QExtFunction< void, bool, int, int, int, int, int > voidBoundConstMemberBaseFunctorB(
                dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstFunctionB6);
    voidBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5, 6);
    QVERIFY("Member::voidConstFunctionB6" == *sg_memberString);
    QExtFunction< int, bool, int, int, int, int, int > intBoundConstMemberBaseFunctorB(
                dynamic_cast< MemberBase * >(&member), &MemberBase::intConstFunctionB6);
    QVERIFY(1 == intBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5, 6));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB(false, 2, 3, 4, 5, 6));
    QExtFunction< double, bool, double, double, double, double, double > doubleBoundConstMemberBaseFunctorB(
                dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstFunctionB6);
    QVERIFY(1 == doubleBoundConstMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6));
}

void QExtFunctionTest::testBoundVolatileFunctorWith6Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QExtFunction< void, int, int, int, int, int, int > voidBoundVolatileMemberBaseFunctor(&memberBase, &MemberBase::voidVolatileFunction6);
    voidBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6);
    QVERIFY("MemberBase::voidVolatileFunction6" == *sg_memberString);
    QExtFunction< int, int, int, int, int, int, int > intBoundVolatileMemberBaseFunctor(&memberBase, &MemberBase::intVolatileFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6));
    QExtFunction< double, double, double, double, double, double, double > doubleBoundVolatileMemberBaseFunctor(
                &memberBase, &MemberBase::doubleVolatileFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QExtFunction< void, bool, int, int, int, int, int > voidBoundVolatileMemberBaseFunctorB(&memberBase, &MemberBase::voidVolatileFunctionB6);
    voidBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6);
    QVERIFY("MemberBase::voidVolatileFunctionB6" == *sg_memberString);
    QExtFunction< int, bool, int, int, int, int, int > intBoundVolatileMemberBaseFunctorB(&memberBase, &MemberBase::intVolatileFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intBoundVolatileMemberBaseFunctorB(false, 2, 3, 4, 5, 6));
    QExtFunction< double, bool, double, double, double, double, double > doubleBoundVolatileMemberBaseFunctorB(
                &memberBase, &MemberBase::doubleVolatileFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6));
}

void QExtFunctionTest::testPolymorphismBoundVolatileFunctorWith6Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QExtFunction< void, int, int, int, int, int, int > voidBoundVolatileMemberBaseFunctor(
                dynamic_cast< MemberBase * >(&member), &MemberBase::voidVolatileFunction6);
    voidBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6);
    QVERIFY("Member::voidVolatileFunction6" == *sg_memberString);
    QExtFunction< int, int, int, int, int, int, int > intBoundVolatileMemberBaseFunctor(
                dynamic_cast< MemberBase * >(&member), &MemberBase::intVolatileFunction6);
    QVERIFY(0 == intBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6));
    QExtFunction< double, double, double, double, double, double, double > doubleBoundVolatileMemberBaseFunctor(
                dynamic_cast< MemberBase * >(&member), &MemberBase::doubleVolatileFunction6);
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QExtFunction< void, bool, int, int, int, int, int > voidBoundVolatileMemberBaseFunctorB(
                dynamic_cast< MemberBase * >(&member), &MemberBase::voidVolatileFunctionB6);
    voidBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6);
    QVERIFY("Member::voidVolatileFunctionB6" == *sg_memberString);
    QExtFunction< int, bool, int, int, int, int, int > intBoundVolatileMemberBaseFunctorB(
                dynamic_cast< MemberBase * >(&member), &MemberBase::intVolatileFunctionB6);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB(false, 2, 3, 4, 5, 6));
    QExtFunction< double, bool, double, double, double, double, double > doubleBoundVolatileMemberBaseFunctorB(
                dynamic_cast< MemberBase * >(&member), &MemberBase::doubleVolatileFunctionB6);
    QVERIFY(1 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6));
}

void QExtFunctionTest::testBoundConstVolatileFunctorWith6Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QExtFunction< void, int, int, int, int, int, int > voidBoundConstVolatileMemberBaseFunctor(&memberBase, &MemberBase::voidConstVolatileFunction6);
    voidBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6);
    QVERIFY("MemberBase::voidConstVolatileFunction6" == *sg_memberString);
    QExtFunction< int, int, int, int, int, int, int > intBoundConstVolatileMemberBaseFunctor(&memberBase, &MemberBase::intConstVolatileFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6));
    QExtFunction< double, double, double, double, double, double, double > doubleBoundConstVolatileMemberBaseFunctor(
                &memberBase, &MemberBase::doubleConstVolatileFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QExtFunction< void, bool, int, int, int, int, int > voidBoundConstVolatileMemberBaseFunctorB(&memberBase, &MemberBase::voidConstVolatileFunctionB6);
    voidBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6);
    QVERIFY("MemberBase::voidConstVolatileFunctionB6" == *sg_memberString);
    QExtFunction< int, bool, int, int, int, int, int > intBoundConstVolatileMemberBaseFunctorB(&memberBase, &MemberBase::intConstVolatileFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intBoundConstVolatileMemberBaseFunctorB(false, 2, 3, 4, 5, 6));
    QExtFunction< double, bool, double, double, double, double, double > doubleBoundConstVolatileMemberBaseFunctorB(
                &memberBase, &MemberBase::doubleConstVolatileFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6));
}

void QExtFunctionTest::testPolymorphismBoundConstVolatileFunctorWith6Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QExtFunction< void, int, int, int, int, int, int > voidBoundConstVolatileMemberBaseFunctor(
                dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstVolatileFunction6);
    voidBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6);
    QVERIFY("Member::voidConstVolatileFunction6" == *sg_memberString);
    QExtFunction< int, int, int, int, int, int, int > intBoundConstVolatileMemberBaseFunctor(
                dynamic_cast< MemberBase * >(&member), &MemberBase::intConstVolatileFunction6);
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6));
    QExtFunction< double, double, double, double, double, double, double > doubleBoundConstVolatileMemberBaseFunctor(
                dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstVolatileFunction6);
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QExtFunction< void, bool, int, int, int, int, int > voidBoundConstVolatileMemberBaseFunctorB(
                dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstVolatileFunctionB6);
    voidBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6);
    QVERIFY("Member::voidConstVolatileFunctionB6" == *sg_memberString);
    QExtFunction< int, bool, int, int, int, int, int > intBoundConstVolatileMemberBaseFunctorB(
                dynamic_cast< MemberBase * >(&member), &MemberBase::intConstVolatileFunctionB6);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB(false, 2, 3, 4, 5, 6));
    QExtFunction< double, bool, double, double, double, double, double > doubleBoundConstVolatileMemberBaseFunctorB(
                dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstVolatileFunctionB6);
    QVERIFY(1 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6));
}

void QExtFunctionTest::testBoundFunctorWith7Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QExtFunction< void, int, int, int, int, int, int, int > voidBoundMemberBaseFunctor(&memberBase, &MemberBase::voidFunction7);
    voidBoundMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7);
    QVERIFY("MemberBase::voidFunction7" == *sg_memberString);
    QExtFunction< int, int, int, int, int, int, int, int > intBoundMemberBaseFunctor(&memberBase, &MemberBase::intFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intBoundMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7));
    QExtFunction< double, double, double, double, double, double, double, double > doubleBoundMemberBaseFunctor(&memberBase, &MemberBase::doubleFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QExtFunction< void, bool, int, int, int, int, int, int > voidBoundMemberBaseFunctorB(&memberBase, &MemberBase::voidFunctionB7);
    voidBoundMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7);
    QVERIFY("MemberBase::voidFunctionB7" == *sg_memberString);
    QExtFunction< int, bool, int, int, int, int, int, int > intBoundMemberBaseFunctorB(&memberBase, &MemberBase::intFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intBoundMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intBoundMemberBaseFunctorB(false, 2, 3, 4, 5, 6, 7));
    QExtFunction< double, bool, double, double, double, double, double, double > doubleBoundMemberBaseFunctorB(&memberBase, &MemberBase::doubleFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleBoundMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
}

void QExtFunctionTest::testPolymorphismBoundFunctorWith7Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QExtFunction< void, int, int, int, int, int, int, int > voidBoundMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::voidFunction7);
    voidBoundMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7);
    QVERIFY("Member::voidFunction7" == *sg_memberString);
    QExtFunction< int, int, int, int, int, int, int, int > intBoundMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::intFunction7);
    QVERIFY(0 == intBoundMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7));
    QExtFunction< double, double, double, double, double, double, double, double > doubleBoundMemberBaseFunctor(
                dynamic_cast< MemberBase * >(&member), &MemberBase::doubleFunction7);
    QVERIFY(0 == doubleBoundMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QExtFunction< void, bool, int, int, int, int, int, int > voidBoundMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::voidFunctionB7);
    voidBoundMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7);
    QVERIFY("Member::voidFunctionB7" == *sg_memberString);
    QExtFunction< int, bool, int, int, int, int, int, int > intBoundMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::intFunctionB7);
    QVERIFY(1 == intBoundMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(0 == intBoundMemberBaseFunctorB(false, 2, 3, 4, 5, 6, 7));
    QExtFunction< double, bool, double, double, double, double, double, double > doubleBoundMemberBaseFunctorB(
                dynamic_cast< MemberBase * >(&member), &MemberBase::doubleFunctionB7);
    QVERIFY(1 == doubleBoundMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
}

void QExtFunctionTest::testBoundConstFunctorWith7Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QExtFunction< void, int, int, int, int, int, int, int > voidBoundConstMemberBaseFunctor(&memberBase, &MemberBase::voidConstFunction7);
    voidBoundConstMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7);
    QVERIFY("MemberBase::voidConstFunction7" == *sg_memberString);
    QExtFunction< int, int, int, int, int, int, int, int > intBoundConstMemberBaseFunctor(&memberBase, &MemberBase::intConstFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intBoundConstMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7));
    QExtFunction< double, double, double, double, double, double, double, double > doubleBoundConstMemberBaseFunctor(
                &memberBase, &MemberBase::doubleConstFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundConstMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QExtFunction< void, bool, int, int, int, int, int, int > voidBoundConstMemberBaseFunctorB(&memberBase, &MemberBase::voidConstFunctionB7);
    voidBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7);
    QVERIFY("MemberBase::voidConstFunctionB7" == *sg_memberString);
    QExtFunction< int, bool, int, int, int, int, int, int > intBoundConstMemberBaseFunctorB(&memberBase, &MemberBase::intConstFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intBoundConstMemberBaseFunctorB(false, 2, 3, 4, 5, 6, 7));
    QExtFunction< double, bool, double, double, double, double, double, double > doubleBoundConstMemberBaseFunctorB(
                &memberBase, &MemberBase::doubleConstFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundConstMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleBoundConstMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
}

void QExtFunctionTest::testPolymorphismBoundConstFunctorWith7Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QExtFunction< void, int, int, int, int, int, int, int > voidBoundConstMemberBaseFunctor(
                dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstFunction7);
    voidBoundConstMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7);
    QVERIFY("Member::voidConstFunction7" == *sg_memberString);
    QExtFunction< int, int, int, int, int, int, int, int > intBoundConstMemberBaseFunctor(
                dynamic_cast< MemberBase * >(&member), &MemberBase::intConstFunction7);
    QVERIFY(0 == intBoundConstMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7));
    QExtFunction< double, double, double, double, double, double, double, double > doubleBoundConstMemberBaseFunctor(
                dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstFunction7);
    QVERIFY(0 == doubleBoundConstMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QExtFunction< void, bool, int, int, int, int, int, int > voidBoundConstMemberBaseFunctorB(
                dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstFunctionB7);
    voidBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7);
    QVERIFY("Member::voidConstFunctionB7" == *sg_memberString);
    QExtFunction< int, bool, int, int, int, int, int, int > intBoundConstMemberBaseFunctorB(
                dynamic_cast< MemberBase * >(&member), &MemberBase::intConstFunctionB7);
    QVERIFY(1 == intBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB(false, 2, 3, 4, 5, 6, 7));
    QExtFunction< double, bool, double, double, double, double, double, double > doubleBoundConstMemberBaseFunctorB(
                dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstFunctionB7);
    QVERIFY(1 == doubleBoundConstMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
}

void QExtFunctionTest::testBoundVolatileFunctorWith7Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QExtFunction< void, int, int, int, int, int, int, int > voidBoundVolatileMemberBaseFunctor(&memberBase, &MemberBase::voidVolatileFunction7);
    voidBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7);
    QVERIFY("MemberBase::voidVolatileFunction7" == *sg_memberString);
    QExtFunction< int, int, int, int, int, int, int, int > intBoundVolatileMemberBaseFunctor(&memberBase, &MemberBase::intVolatileFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7));
    QExtFunction< double, double, double, double, double, double, double, double > doubleBoundVolatileMemberBaseFunctor(
                &memberBase, &MemberBase::doubleVolatileFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QExtFunction< void, bool, int, int, int, int, int, int > voidBoundVolatileMemberBaseFunctorB(&memberBase, &MemberBase::voidVolatileFunctionB7);
    voidBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7);
    QVERIFY("MemberBase::voidVolatileFunctionB7" == *sg_memberString);
    QExtFunction< int, bool, int, int, int, int, int, int > intBoundVolatileMemberBaseFunctorB(&memberBase, &MemberBase::intVolatileFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intBoundVolatileMemberBaseFunctorB(false, 2, 3, 4, 5, 6, 7));
    QExtFunction< double, bool, double, double, double, double, double, double > doubleBoundVolatileMemberBaseFunctorB(
                &memberBase, &MemberBase::doubleVolatileFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
}

void QExtFunctionTest::testPolymorphismBoundVolatileFunctorWith7Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QExtFunction< void, int, int, int, int, int, int, int > voidBoundVolatileMemberBaseFunctor(
                dynamic_cast< MemberBase * >(&member), &MemberBase::voidVolatileFunction7);
    voidBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7);
    QVERIFY("Member::voidVolatileFunction7" == *sg_memberString);
    QExtFunction< int, int, int, int, int, int, int, int > intBoundVolatileMemberBaseFunctor(
                dynamic_cast< MemberBase * >(&member), &MemberBase::intVolatileFunction7);
    QVERIFY(0 == intBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7));
    QExtFunction< double, double, double, double, double, double, double, double > doubleBoundVolatileMemberBaseFunctor(
                dynamic_cast< MemberBase * >(&member), &MemberBase::doubleVolatileFunction7);
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QExtFunction< void, bool, int, int, int, int, int, int > voidBoundVolatileMemberBaseFunctorB(
                dynamic_cast< MemberBase * >(&member), &MemberBase::voidVolatileFunctionB7);
    voidBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7);
    QVERIFY("Member::voidVolatileFunctionB7" == *sg_memberString);
    QExtFunction< int, bool, int, int, int, int, int, int > intBoundVolatileMemberBaseFunctorB(
                dynamic_cast< MemberBase * >(&member), &MemberBase::intVolatileFunctionB7);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB(false, 2, 3, 4, 5, 6, 7));
    QExtFunction< double, bool, double, double, double, double, double, double > doubleBoundVolatileMemberBaseFunctorB(
                dynamic_cast< MemberBase * >(&member), &MemberBase::doubleVolatileFunctionB7);
    QVERIFY(1 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
}

void QExtFunctionTest::testBoundConstVolatileFunctorWith7Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QExtFunction< void, int, int, int, int, int, int, int > voidBoundConstVolatileMemberBaseFunctor(&memberBase, &MemberBase::voidConstVolatileFunction7);
    voidBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7);
    QVERIFY("MemberBase::voidConstVolatileFunction7" == *sg_memberString);
    QExtFunction< int, int, int, int, int, int, int, int > intBoundConstVolatileMemberBaseFunctor(&memberBase, &MemberBase::intConstVolatileFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7));
    QExtFunction< double, double, double, double, double, double, double, double > doubleBoundConstVolatileMemberBaseFunctor(
                &memberBase, &MemberBase::doubleConstVolatileFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QExtFunction< void, bool, int, int, int, int, int, int > voidBoundConstVolatileMemberBaseFunctorB(&memberBase, &MemberBase::voidConstVolatileFunctionB7);
    voidBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7);
    QVERIFY("MemberBase::voidConstVolatileFunctionB7" == *sg_memberString);
    QExtFunction< int, bool, int, int, int, int, int, int > intBoundConstVolatileMemberBaseFunctorB(&memberBase, &MemberBase::intConstVolatileFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intBoundConstVolatileMemberBaseFunctorB(false, 2, 3, 4, 5, 6, 7));
    QExtFunction< double, bool, double, double, double, double, double, double > doubleBoundConstVolatileMemberBaseFunctorB(
                &memberBase, &MemberBase::doubleConstVolatileFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
}

void QExtFunctionTest::testPolymorphismBoundConstVolatileFunctorWith7Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QExtFunction< void, int, int, int, int, int, int, int > voidBoundConstVolatileMemberBaseFunctor(
                dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstVolatileFunction7);
    voidBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7);
    QVERIFY("Member::voidConstVolatileFunction7" == *sg_memberString);
    QExtFunction< int, int, int, int, int, int, int, int > intBoundConstVolatileMemberBaseFunctor(
                dynamic_cast< MemberBase * >(&member), &MemberBase::intConstVolatileFunction7);
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7));
    QExtFunction< double, double, double, double, double, double, double, double > doubleBoundConstVolatileMemberBaseFunctor(
                dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstVolatileFunction7);
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QExtFunction< void, bool, int, int, int, int, int, int > voidBoundConstVolatileMemberBaseFunctorB(
                dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstVolatileFunctionB7);
    voidBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7);
    QVERIFY("Member::voidConstVolatileFunctionB7" == *sg_memberString);
    QExtFunction< int, bool, int, int, int, int, int, int > intBoundConstVolatileMemberBaseFunctorB(
                dynamic_cast< MemberBase * >(&member), &MemberBase::intConstVolatileFunctionB7);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB(false, 2, 3, 4, 5, 6, 7));
    QExtFunction< double, bool, double, double, double, double, double, double > doubleBoundConstVolatileMemberBaseFunctorB(
                dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstVolatileFunctionB7);
    QVERIFY(1 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
}





QTEST_APPLESS_MAIN(QExtFunctionTest)

#include <tst_qextFunction.moc>
