#ifndef QEXTFUNCTIONTEST_H
#define QEXTFUNCTIONTEST_H

#include <qextBindFunctor.h>
#include <qextFunction.h>
#include <qextGlobal.h>
#include <qextMemberFunctor.h>
#include <qextPointerFunctor.h>
#include <qextSlot.h>

#include "qextFunctions.h"
#include "qextMember.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

#if QEXT_CC_STD_11
#include <functional>
#endif

#include <CppUTest/TestHarness.h>

QEXT_USE_NAMESPACE

namespace qextFunctionTest
{

    static std::string *sg_string = QEXT_DECL_NULLPTR;

    TEST_GROUP(qextFunctionTest){};

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
            QEXT_UNUSED(a1)
            *sg_string = "MFunctor::voidFunction1";
        }
        void operator()(int a1, int a2)
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            *sg_string = "MFunctor::voidFunction2";
        }
        void operator()(int a1, int a2, int a3)
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            *sg_string = "MFunctor::voidFunction3";
        }
        void operator()(int a1, int a2, int a3, int a4)
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            *sg_string = "MFunctor::voidFunction4";
        }
        void operator()(int a1, int a2, int a3, int a4, int a5)
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            *sg_string = "MFunctor::voidFunction5";
        }
        void operator()(int a1, int a2, int a3, int a4, int a5, int a6)
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            QEXT_UNUSED(a6)
            *sg_string = "MFunctor::voidFunction6";
        }
        void operator()(int a1, int a2, int a3, int a4, int a5, int a6, int a7)
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            QEXT_UNUSED(a6)
            QEXT_UNUSED(a7)
            *sg_string = "MFunctor::voidFunction7";
        }
        void operator()(bool a1)
        {
            QEXT_UNUSED(a1)
            *sg_string = "MFunctor::voidFunctionB1";
        }
        void operator()(bool a1, int a2)
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            *sg_string = "MFunctor::voidFunctionB2";
        }
        void operator()(bool a1, int a2, int a3)
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            *sg_string = "MFunctor::voidFunctionB3";
        }
        void operator()(bool a1, int a2, int a3, int a4)
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            *sg_string = "MFunctor::voidFunctionB4";
        }
        void operator()(bool a1, int a2, int a3, int a4, int a5)
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            *sg_string = "MFunctor::voidFunctionB5";
        }
        void operator()(bool a1, int a2, int a3, int a4, int a5, int a6)
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            QEXT_UNUSED(a6)
            *sg_string = "MFunctor::voidFunctionB6";
        }
        void operator()(bool a1, int a2, int a3, int a4, int a5, int a6, int a7)
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            QEXT_UNUSED(a6)
            QEXT_UNUSED(a7)
            *sg_string = "MFunctor::voidFunctionB7";
        }
    };

    TEST(qextFunctionTest, functor)
    {
        std::string string;
        sg_string = &string;
        MFunctor mFunctor;

        QEXTFunction< void > voidFunctorArg0(mFunctor);
        voidFunctorArg0();
        CHECK("MFunctor::voidFunction0" == string);
        QEXTFunction< void, int > voidFunctorArg1(mFunctor);
        voidFunctorArg1(1);
        CHECK("MFunctor::voidFunction1" == string);
        QEXTFunction< void, int, int > voidFunctorArg2(mFunctor);
        voidFunctorArg2(1, 2);
        CHECK("MFunctor::voidFunction2" == string);
        QEXTFunction< void, int, int, int > voidFunctorArg3(mFunctor);
        voidFunctorArg3(1, 2, 3);
        CHECK("MFunctor::voidFunction3" == string);
        QEXTFunction< void, int, int, int, int > voidFunctorArg4(mFunctor);
        voidFunctorArg4(1, 2, 3, 4);
        CHECK("MFunctor::voidFunction4" == string);
        QEXTFunction< void, int, int, int, int, int > voidFunctorArg5(mFunctor);
        voidFunctorArg5(1, 2, 3, 4, 5);
        CHECK("MFunctor::voidFunction5" == string);
        QEXTFunction< void, int, int, int, int, int, int > voidFunctorArg6(mFunctor);
        voidFunctorArg6(1, 2, 3, 4, 5, 6);
        CHECK("MFunctor::voidFunction6" == string);
        QEXTFunction< void, int, int, int, int, int, int, int > voidFunctorArg7(mFunctor);
        voidFunctorArg7(1, 2, 3, 4, 5, 6, 7);
        CHECK("MFunctor::voidFunction7" == string);

        QEXTFunction< void, bool > voidFunctorBArg1(mFunctor);
        voidFunctorBArg1(true);
        CHECK("MFunctor::voidFunctionB1" == string);
        QEXTFunction< void, bool, int > voidFunctorBArg2(mFunctor);
        voidFunctorBArg2(true, 2);
        CHECK("MFunctor::voidFunctionB2" == string);
        QEXTFunction< void, bool, int, int > voidFunctorBArg3(mFunctor);
        voidFunctorBArg3(true, 2, 3);
        CHECK("MFunctor::voidFunctionB3" == string);
        QEXTFunction< void, bool, int, int, int > voidFunctorBArg4(mFunctor);
        voidFunctorBArg4(true, 2, 3, 4);
        CHECK("MFunctor::voidFunctionB4" == string);
        QEXTFunction< void, bool, int, int, int, int > voidFunctorBArg5(mFunctor);
        voidFunctorBArg5(true, 2, 3, 4, 5);
        CHECK("MFunctor::voidFunctionB5" == string);
        QEXTFunction< void, bool, int, int, int, int, int > voidFunctorBArg6(mFunctor);
        voidFunctorBArg6(true, 2, 3, 4, 5, 6);
        CHECK("MFunctor::voidFunctionB6" == string);
        QEXTFunction< void, bool, int, int, int, int, int, int > voidFunctorBArg7(mFunctor);
        voidFunctorBArg7(true, 2, 3, 4, 5, 6, 7);
        CHECK("MFunctor::voidFunctionB7" == string);
    }

#if QEXT_CC_STD_11
    TEST(qextFunctionTest, stdFunction)
    {
        std::string string;
        sg_string = &string;

        /*lambda*/
        QEXTFunction< void > voidFunctorArg0([=](){ *sg_string = "lambda::voidFunction0"; });
        voidFunctorArg0();
        CHECK("lambda::voidFunction0" == string);
        QEXTFunction< void, int > voidFunctorArg1([=](int){ *sg_string = "lambda::voidFunction1"; });
        voidFunctorArg1(1);
        CHECK("lambda::voidFunction1" == string);
        QEXTFunction< void, int, int > voidFunctorArg2([=](int, int){ *sg_string = "lambda::voidFunction2"; });
        voidFunctorArg2(1, 2);
        CHECK("lambda::voidFunction2" == string);
        QEXTFunction< void, int, int, int > voidFunctorArg3([=](int, int, int){ *sg_string = "lambda::voidFunction3"; });
        voidFunctorArg3(1, 2, 3);
        CHECK("lambda::voidFunction3" == string);
        QEXTFunction< void, int, int, int, int > voidFunctorArg4([=](int, int, int, int){ *sg_string = "lambda::voidFunction4"; });
        voidFunctorArg4(1, 2, 3, 4);
        CHECK("lambda::voidFunction4" == string);
        QEXTFunction< void, int, int, int, int, int > voidFunctorArg5([=](int, int, int, int, int){ *sg_string = "lambda::voidFunction5"; });
        voidFunctorArg5(1, 2, 3, 4, 5);
        CHECK("lambda::voidFunction5" == string);
        QEXTFunction< void, int, int, int, int, int, int > voidFunctorArg6([=](int, int, int, int, int, int){ *sg_string = "lambda::voidFunction6"; });
        voidFunctorArg6(1, 2, 3, 4, 5, 6);
        CHECK("lambda::voidFunction6" == string);
        QEXTFunction< void, int, int, int, int, int, int, int > voidFunctorArg7([=](int, int, int, int, int, int, int){ *sg_string = "lambda::voidFunction7"; });
        voidFunctorArg7(1, 2, 3, 4, 5, 6, 7);
        CHECK("lambda::voidFunction7" == string);

        MFunctor mFunctor;

        QEXTFunction< void, bool > voidFunctorBArg1 = std::function<void(bool)>(mFunctor);
        voidFunctorBArg1(true);
        CHECK("MFunctor::voidFunctionB1" == string);
        QEXTFunction< void, bool, int > voidFunctorBArg2 = std::function<void(bool, int)>(mFunctor);
        voidFunctorBArg2(true, 2);
        CHECK("MFunctor::voidFunctionB2" == string);
        QEXTFunction< void, bool, int, int > voidFunctorBArg3 = std::function<void(bool, int, int)>(mFunctor);
        voidFunctorBArg3(true, 2, 3);
        CHECK("MFunctor::voidFunctionB3" == string);
        QEXTFunction< void, bool, int, int, int > voidFunctorBArg4 = std::function<void(bool, int, int, int)>(mFunctor);
        voidFunctorBArg4(true, 2, 3, 4);
        CHECK("MFunctor::voidFunctionB4" == string);
        QEXTFunction< void, bool, int, int, int, int > voidFunctorBArg5 = std::function<void(bool, int, int, int, int)>(mFunctor);
        voidFunctorBArg5(true, 2, 3, 4, 5);
        CHECK("MFunctor::voidFunctionB5" == string);
        QEXTFunction< void, bool, int, int, int, int, int > voidFunctorBArg6 = std::function<void(bool, int, int, int, int, int)>(mFunctor);
        voidFunctorBArg6(true, 2, 3, 4, 5, 6);
        CHECK("MFunctor::voidFunctionB6" == string);
        QEXTFunction< void, bool, int, int, int, int, int, int > voidFunctorBArg7 = std::function<void(bool, int, int, int, int, int, int)>(mFunctor);
        voidFunctorBArg7(true, 2, 3, 4, 5, 6, 7);
        CHECK("MFunctor::voidFunctionB7" == string);
    }
#endif

    class MRetIntFunctor : public QEXTFunctorBase
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
    TEST(qextFunctionTest, retIntFunctor)
    {
        std::string string;
        sg_string = &string;
        MRetIntFunctor mFunctor;

        QEXTFunction< int > intFunctorArg0(mFunctor);
        intFunctorArg0();
        CHECK("MRetIntFunctor::intFunction0" == string);
        QEXTFunction< int, int > intFunctorArg1(mFunctor);
        CHECK(1 == intFunctorArg1(1));
        QEXTFunction< int, int, int > intFunctorArg2(mFunctor);
        CHECK(3 == intFunctorArg2(1, 2));
        QEXTFunction< int, int, int, int > intFunctorArg3(mFunctor);
        CHECK(6 == intFunctorArg3(1, 2, 3));
        QEXTFunction< int, int, int, int, int > intFunctorArg4(mFunctor);
        CHECK(10 == intFunctorArg4(1, 2, 3, 4));
        QEXTFunction< int, int, int, int, int, int > intFunctorArg5(mFunctor);
        CHECK(15 == intFunctorArg5(1, 2, 3, 4, 5));
        QEXTFunction< int, int, int, int, int, int, int > intFunctorArg6(mFunctor);
        CHECK(21 == intFunctorArg6(1, 2, 3, 4, 5, 6));
        QEXTFunction< int, int, int, int, int, int, int, int > intFunctorArg7(mFunctor);
        CHECK(28 == intFunctorArg7(1, 2, 3, 4, 5, 6, 7));

        QEXTFunction< int, bool > intFunctorBArg1(mFunctor);
        CHECK(1 == intFunctorBArg1(true));
        CHECK(0 == intFunctorBArg1(false));
        QEXTFunction< int, bool, int > intFunctorBArg2(mFunctor);
        CHECK(2 == intFunctorBArg2(true, 2));
        CHECK(0 == intFunctorBArg2(false, 2));
        QEXTFunction< int, bool, int, int > intFunctorBArg3(mFunctor);
        CHECK(5 == intFunctorBArg3(true, 2, 3));
        CHECK(6 == intFunctorBArg3(false, 2, 3));
        QEXTFunction< int, bool, int, int, int > intFunctorBArg4(mFunctor);
        CHECK(9 == intFunctorBArg4(true, 2, 3, 4));
        CHECK(24 == intFunctorBArg4(false, 2, 3, 4));
        QEXTFunction< int, bool, int, int, int, int > intFunctorBArg5(mFunctor);
        CHECK(14 == intFunctorBArg5(true, 2, 3, 4, 5));
        CHECK(120 == intFunctorBArg5(false, 2, 3, 4, 5));
        QEXTFunction< int, bool, int, int, int, int, int > intFunctorBArg6(mFunctor);
        CHECK(20 == intFunctorBArg6(true, 2, 3, 4, 5, 6));
        CHECK(720 == intFunctorBArg6(false, 2, 3, 4, 5, 6));
        QEXTFunction< int, bool, int, int, int, int, int, int > intFunctorBArg7(mFunctor);
        CHECK(27 == intFunctorBArg7(true, 2, 3, 4, 5, 6, 7));
        CHECK(5040 == intFunctorBArg7(false, 2, 3, 4, 5, 6, 7));
    }

#if QEXT_CC_STD_11
    TEST(qextFunctionTest, stdRetIntFunction)
    {
        std::string string;
        sg_string = &string;

        QEXTFunction< int > intFunctorArg0 = []() -> int { *sg_string = "lambda::intFunction0"; return 0; };
        intFunctorArg0();
        CHECK("lambda::intFunction0" == string);
        QEXTFunction< int, int > intFunctorArg1 = [](int a1) -> int { return a1; };
        CHECK(1 == intFunctorArg1(1));
        QEXTFunction< int, int, int > intFunctorArg2 = [](int a1, int a2) -> int { return a1 + a2; };
        CHECK(3 == intFunctorArg2(1, 2));
        QEXTFunction< int, int, int, int > intFunctorArg3 = [](int a1, int a2, int a3) -> int { return a1 + a2 + a3; };
        CHECK(6 == intFunctorArg3(1, 2, 3));
        QEXTFunction< int, int, int, int, int > intFunctorArg4 = [](int a1, int a2, int a3, int a4) -> int { return a1 + a2 + a3 + a4; };
        CHECK(10 == intFunctorArg4(1, 2, 3, 4));
        QEXTFunction< int, int, int, int, int, int > intFunctorArg5 = [](int a1, int a2, int a3, int a4, int a5) -> int { return a1 + a2 + a3 + a4 + a5; };
        CHECK(15 == intFunctorArg5(1, 2, 3, 4, 5));
        QEXTFunction< int, int, int, int, int, int, int > intFunctorArg6 = [](int a1, int a2, int a3, int a4, int a5, int a6) -> int { return a1 + a2 + a3 + a4 + a5 + a6; };
        CHECK(21 == intFunctorArg6(1, 2, 3, 4, 5, 6));
        QEXTFunction< int, int, int, int, int, int, int, int > intFunctorArg7 = [](int a1, int a2, int a3, int a4, int a5, int a6, int a7) -> int { return a1 + a2 + a3 + a4 + a5 + a6 + a7; };
        CHECK(28 == intFunctorArg7(1, 2, 3, 4, 5, 6, 7));

        MRetIntFunctor mFunctor;

        QEXTFunction< int, bool > intFunctorBArg1 = std::function<int(bool)>(mFunctor);
        CHECK(1 == intFunctorBArg1(true));
        CHECK(0 == intFunctorBArg1(false));
        QEXTFunction< int, bool, int > intFunctorBArg2 = std::function<int(bool, int)>(mFunctor);
        CHECK(2 == intFunctorBArg2(true, 2));
        CHECK(0 == intFunctorBArg2(false, 2));
        QEXTFunction< int, bool, int, int > intFunctorBArg3 = std::function<int(bool, int, int)>(mFunctor);
        CHECK(5 == intFunctorBArg3(true, 2, 3));
        CHECK(6 == intFunctorBArg3(false, 2, 3));
        QEXTFunction< int, bool, int, int, int > intFunctorBArg4 = std::function<int(bool, int, int, int)>(mFunctor);
        CHECK(9 == intFunctorBArg4(true, 2, 3, 4));
        CHECK(24 == intFunctorBArg4(false, 2, 3, 4));
        QEXTFunction< int, bool, int, int, int, int > intFunctorBArg5 = std::function<int(bool, int, int, int, int)>(mFunctor);
        CHECK(14 == intFunctorBArg5(true, 2, 3, 4, 5));
        CHECK(120 == intFunctorBArg5(false, 2, 3, 4, 5));
        QEXTFunction< int, bool, int, int, int, int, int > intFunctorBArg6 = std::function<int(bool, int, int, int, int, int)>(mFunctor);
        CHECK(20 == intFunctorBArg6(true, 2, 3, 4, 5, 6));
        CHECK(720 == intFunctorBArg6(false, 2, 3, 4, 5, 6));
        QEXTFunction< int, bool, int, int, int, int, int, int > intFunctorBArg7 = std::function<int(bool, int, int, int, int, int, int)>(mFunctor);
        CHECK(27 == intFunctorBArg7(true, 2, 3, 4, 5, 6, 7));
        CHECK(5040 == intFunctorBArg7(false, 2, 3, 4, 5, 6, 7));
    }
#endif

    class MRetDoubleFunctor : public QEXTFunctorBase
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
    TEST(qextFunctionTest, retDoubleFunctor)
    {
        std::string string;
        sg_string = &string;
        MRetDoubleFunctor mFunctor;

        QEXTFunction< double > doubleFunctorArg0(mFunctor);
        doubleFunctorArg0();
        CHECK("MRetDoubleFunctor::doubleFunction0" == string);
        QEXTFunction< double, double > doubleFunctorArg1(mFunctor);
        CHECK(1 == doubleFunctorArg1(1));
        QEXTFunction< double, double, double > doubleFunctorArg2(mFunctor);
        CHECK(3 == doubleFunctorArg2(1, 2));
        QEXTFunction< double, double, double, double > doubleFunctorArg3(mFunctor);
        CHECK(6 == doubleFunctorArg3(1, 2, 3));
        QEXTFunction< double, double, double, double, double > doubleFunctorArg4(mFunctor);
        CHECK(10 == doubleFunctorArg4(1, 2, 3, 4));
        QEXTFunction< double, double, double, double, double, double > doubleFunctorArg5(mFunctor);
        CHECK(15 == doubleFunctorArg5(1, 2, 3, 4, 5));
        QEXTFunction< double, double, double, double, double, double, double > doubleFunctorArg6(mFunctor);
        CHECK(21 == doubleFunctorArg6(1, 2, 3, 4, 5, 6));
        QEXTFunction< double, double, double, double, double, double, double, double > doubleFunctorArg7(mFunctor);
        CHECK(28 == doubleFunctorArg7(1, 2, 3, 4, 5, 6, 7));

        QEXTFunction< double, bool > voidFunctorBArg1(mFunctor);
        CHECK(1 == voidFunctorBArg1(true));
        CHECK(0 == voidFunctorBArg1(false));
        QEXTFunction< double, bool, double > voidFunctorBArg2(mFunctor);
        CHECK(2 == voidFunctorBArg2(true, 2));
        CHECK(0 == voidFunctorBArg2(false, 2));
        QEXTFunction< double, bool, double, double > voidFunctorBArg3(mFunctor);
        CHECK(5 == voidFunctorBArg3(true, 2, 3));
        CHECK(6 == voidFunctorBArg3(false, 2, 3));
        QEXTFunction< double, bool, double, double, double > voidFunctorBArg4(mFunctor);
        CHECK(9 == voidFunctorBArg4(true, 2, 3, 4));
        CHECK(24 == voidFunctorBArg4(false, 2, 3, 4));
        QEXTFunction< double, bool, double, double, double, double > voidFunctorBArg5(mFunctor);
        CHECK(14 == voidFunctorBArg5(true, 2, 3, 4, 5));
        CHECK(120 == voidFunctorBArg5(false, 2, 3, 4, 5));
        QEXTFunction< double, bool, double, double, double, double, double > voidFunctorBArg6(mFunctor);
        CHECK(20 == voidFunctorBArg6(true, 2, 3, 4, 5, 6));
        CHECK(720 == voidFunctorBArg6(false, 2, 3, 4, 5, 6));
        QEXTFunction< double, bool, double, double, double, double, double, double > voidFunctorBArg7(mFunctor);
        CHECK(27 == voidFunctorBArg7(true, 2, 3, 4, 5, 6, 7));
        CHECK(5040 == voidFunctorBArg7(false, 2, 3, 4, 5, 6, 7));
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
            QEXT_UNUSED(a1)
            *sg_string = "MConstFunctor::voidConstFunction1";
        }
        void operator()(int a1, int a2) const
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            *sg_string = "MConstFunctor::voidConstFunction2";
        }
        void operator()(int a1, int a2, int a3) const
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            *sg_string = "MConstFunctor::voidConstFunction3";
        }
        void operator()(int a1, int a2, int a3, int a4) const
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            *sg_string = "MConstFunctor::voidConstFunction4";
        }
        void operator()(int a1, int a2, int a3, int a4, int a5) const
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            *sg_string = "MConstFunctor::voidConstFunction5";
        }
        void operator()(int a1, int a2, int a3, int a4, int a5, int a6) const
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            QEXT_UNUSED(a6)
            *sg_string = "MConstFunctor::voidConstFunction6";
        }
        void operator()(int a1, int a2, int a3, int a4, int a5, int a6, int a7) const
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            QEXT_UNUSED(a6)
            QEXT_UNUSED(a7)
            *sg_string = "MConstFunctor::voidConstFunction7";
        }
        void operator()(bool a1) const
        {
            QEXT_UNUSED(a1)
            *sg_string = "MConstFunctor::voidConstFunctionB1";
        }
        void operator()(bool a1, int a2) const
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            *sg_string = "MConstFunctor::voidConstFunctionB2";
        }
        void operator()(bool a1, int a2, int a3) const
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            *sg_string = "MConstFunctor::voidConstFunctionB3";
        }
        void operator()(bool a1, int a2, int a3, int a4) const
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            *sg_string = "MConstFunctor::voidConstFunctionB4";
        }
        void operator()(bool a1, int a2, int a3, int a4, int a5) const
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            *sg_string = "MConstFunctor::voidConstFunctionB5";
        }
        void operator()(bool a1, int a2, int a3, int a4, int a5, int a6) const
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            QEXT_UNUSED(a6)
            *sg_string = "MConstFunctor::voidConstFunctionB6";
        }
        void operator()(bool a1, int a2, int a3, int a4, int a5, int a6, int a7) const
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            QEXT_UNUSED(a6)
            QEXT_UNUSED(a7)
            *sg_string = "MConstFunctor::voidConstFunctionB7";
        }
    };
    TEST(qextFunctionTest, constFunctor)
    {
        std::string string;
        sg_string = &string;
        MConstFunctor mFunctor;

        QEXTFunction< void > voidFunctorArg0(mFunctor);
        voidFunctorArg0();
        CHECK("MConstFunctor::voidConstFunction0" == string);
        QEXTFunction< void, int > voidFunctorArg1(mFunctor);
        voidFunctorArg1(1);
        CHECK("MConstFunctor::voidConstFunction1" == string);
        QEXTFunction< void, int, int > voidFunctorArg2(mFunctor);
        voidFunctorArg2(1, 2);
        CHECK("MConstFunctor::voidConstFunction2" == string);
        QEXTFunction< void, int, int, int > voidFunctorArg3(mFunctor);
        voidFunctorArg3(1, 2, 3);
        CHECK("MConstFunctor::voidConstFunction3" == string);
        QEXTFunction< void, int, int, int, int > voidFunctorArg4(mFunctor);
        voidFunctorArg4(1, 2, 3, 4);
        CHECK("MConstFunctor::voidConstFunction4" == string);
        QEXTFunction< void, int, int, int, int, int > voidFunctorArg5(mFunctor);
        voidFunctorArg5(1, 2, 3, 4, 5);
        CHECK("MConstFunctor::voidConstFunction5" == string);
        QEXTFunction< void, int, int, int, int, int, int > voidFunctorArg6(mFunctor);
        voidFunctorArg6(1, 2, 3, 4, 5, 6);
        CHECK("MConstFunctor::voidConstFunction6" == string);
        QEXTFunction< void, int, int, int, int, int, int, int > voidFunctorArg7(mFunctor);
        voidFunctorArg7(1, 2, 3, 4, 5, 6, 7);
        CHECK("MConstFunctor::voidConstFunction7" == string);

        QEXTFunction< void, bool > voidFunctorBArg1(mFunctor);
        voidFunctorBArg1(true);
        CHECK("MConstFunctor::voidConstFunctionB1" == string);
        QEXTFunction< void, bool, int > voidFunctorBArg2(mFunctor);
        voidFunctorBArg2(true, 2);
        CHECK("MConstFunctor::voidConstFunctionB2" == string);
        QEXTFunction< void, bool, int, int > voidFunctorBArg3(mFunctor);
        voidFunctorBArg3(true, 2, 3);
        CHECK("MConstFunctor::voidConstFunctionB3" == string);
        QEXTFunction< void, bool, int, int, int > voidFunctorBArg4(mFunctor);
        voidFunctorBArg4(true, 2, 3, 4);
        CHECK("MConstFunctor::voidConstFunctionB4" == string);
        QEXTFunction< void, bool, int, int, int, int > voidFunctorBArg5(mFunctor);
        voidFunctorBArg5(true, 2, 3, 4, 5);
        CHECK("MConstFunctor::voidConstFunctionB5" == string);
        QEXTFunction< void, bool, int, int, int, int, int > voidFunctorBArg6(mFunctor);
        voidFunctorBArg6(true, 2, 3, 4, 5, 6);
        CHECK("MConstFunctor::voidConstFunctionB6" == string);
        QEXTFunction< void, bool, int, int, int, int, int, int > voidFunctorBArg7(mFunctor);
        voidFunctorBArg7(true, 2, 3, 4, 5, 6, 7);
        CHECK("MConstFunctor::voidConstFunctionB7" == string);
    }

    class MRetIntConstFunctor : public QEXTFunctorBase
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
    TEST(qextFunctionTest, retIntConstFunctor)
    {
        std::string string;
        sg_string = &string;
        MRetIntConstFunctor mFunctor;

        QEXTFunction< int > intFunctorArg0(mFunctor);
        intFunctorArg0();
        CHECK("MRetIntConstFunctor::intConstFunction0" == string);
        QEXTFunction< int, int > intFunctorArg1(mFunctor);
        CHECK(1 == intFunctorArg1(1));
        QEXTFunction< int, int, int > intFunctorArg2(mFunctor);
        CHECK(3 == intFunctorArg2(1, 2));
        QEXTFunction< int, int, int, int > intFunctorArg3(mFunctor);
        CHECK(6 == intFunctorArg3(1, 2, 3));
        QEXTFunction< int, int, int, int, int > intFunctorArg4(mFunctor);
        CHECK(10 == intFunctorArg4(1, 2, 3, 4));
        QEXTFunction< int, int, int, int, int, int > intFunctorArg5(mFunctor);
        CHECK(15 == intFunctorArg5(1, 2, 3, 4, 5));
        QEXTFunction< int, int, int, int, int, int, int > intFunctorArg6(mFunctor);
        CHECK(21 == intFunctorArg6(1, 2, 3, 4, 5, 6));
        QEXTFunction< int, int, int, int, int, int, int, int > intFunctorArg7(mFunctor);
        CHECK(28 == intFunctorArg7(1, 2, 3, 4, 5, 6, 7));

        QEXTFunction< int, bool > intFunctorBArg1(mFunctor);
        CHECK(1 == intFunctorBArg1(true));
        CHECK(0 == intFunctorBArg1(false));
        QEXTFunction< int, bool, int > intFunctorBArg2(mFunctor);
        CHECK(2 == intFunctorBArg2(true, 2));
        CHECK(0 == intFunctorBArg2(false, 2));
        QEXTFunction< int, bool, int, int > intFunctorBArg3(mFunctor);
        CHECK(5 == intFunctorBArg3(true, 2, 3));
        CHECK(6 == intFunctorBArg3(false, 2, 3));
        QEXTFunction< int, bool, int, int, int > intFunctorBArg4(mFunctor);
        CHECK(9 == intFunctorBArg4(true, 2, 3, 4));
        CHECK(24 == intFunctorBArg4(false, 2, 3, 4));
        QEXTFunction< int, bool, int, int, int, int > intFunctorBArg5(mFunctor);
        CHECK(14 == intFunctorBArg5(true, 2, 3, 4, 5));
        CHECK(120 == intFunctorBArg5(false, 2, 3, 4, 5));
        QEXTFunction< int, bool, int, int, int, int, int > intFunctorBArg6(mFunctor);
        CHECK(20 == intFunctorBArg6(true, 2, 3, 4, 5, 6));
        CHECK(720 == intFunctorBArg6(false, 2, 3, 4, 5, 6));
        QEXTFunction< int, bool, int, int, int, int, int, int > intFunctorBArg7(mFunctor);
        CHECK(27 == intFunctorBArg7(true, 2, 3, 4, 5, 6, 7));
        CHECK(5040 == intFunctorBArg7(false, 2, 3, 4, 5, 6, 7));
    }

    class MRetDoubleConstFunctor : public QEXTFunctorBase
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
    TEST(qextFunctionTest, retDoubleConstFunctor)
    {
        std::string string;
        sg_string = &string;
        MRetDoubleConstFunctor mFunctor;

        QEXTFunction< double > doubleFunctorArg0(mFunctor);
        doubleFunctorArg0();
        CHECK("MRetDoubleConstFunctor::doubleConstFunction0" == string);
        QEXTFunction< double, double > doubleFunctorArg1(mFunctor);
        CHECK(1 == doubleFunctorArg1(1));
        QEXTFunction< double, double, double > doubleFunctorArg2(mFunctor);
        CHECK(3 == doubleFunctorArg2(1, 2));
        QEXTFunction< double, double, double, double > doubleFunctorArg3(mFunctor);
        CHECK(6 == doubleFunctorArg3(1, 2, 3));
        QEXTFunction< double, double, double, double, double > doubleFunctorArg4(mFunctor);
        CHECK(10 == doubleFunctorArg4(1, 2, 3, 4));
        QEXTFunction< double, double, double, double, double, double > doubleFunctorArg5(mFunctor);
        CHECK(15 == doubleFunctorArg5(1, 2, 3, 4, 5));
        QEXTFunction< double, double, double, double, double, double, double > doubleFunctorArg6(mFunctor);
        CHECK(21 == doubleFunctorArg6(1, 2, 3, 4, 5, 6));
        QEXTFunction< double, double, double, double, double, double, double, double > doubleFunctorArg7(mFunctor);
        CHECK(28 == doubleFunctorArg7(1, 2, 3, 4, 5, 6, 7));

        QEXTFunction< double, bool > voidFunctorBArg1(mFunctor);
        CHECK(1 == voidFunctorBArg1(true));
        CHECK(0 == voidFunctorBArg1(false));
        QEXTFunction< double, bool, double > voidFunctorBArg2(mFunctor);
        CHECK(2 == voidFunctorBArg2(true, 2));
        CHECK(0 == voidFunctorBArg2(false, 2));
        QEXTFunction< double, bool, double, double > voidFunctorBArg3(mFunctor);
        CHECK(5 == voidFunctorBArg3(true, 2, 3));
        CHECK(6 == voidFunctorBArg3(false, 2, 3));
        QEXTFunction< double, bool, double, double, double > voidFunctorBArg4(mFunctor);
        CHECK(9 == voidFunctorBArg4(true, 2, 3, 4));
        CHECK(24 == voidFunctorBArg4(false, 2, 3, 4));
        QEXTFunction< double, bool, double, double, double, double > voidFunctorBArg5(mFunctor);
        CHECK(14 == voidFunctorBArg5(true, 2, 3, 4, 5));
        CHECK(120 == voidFunctorBArg5(false, 2, 3, 4, 5));
        QEXTFunction< double, bool, double, double, double, double, double > voidFunctorBArg6(mFunctor);
        CHECK(20 == voidFunctorBArg6(true, 2, 3, 4, 5, 6));
        CHECK(720 == voidFunctorBArg6(false, 2, 3, 4, 5, 6));
        QEXTFunction< double, bool, double, double, double, double, double, double > voidFunctorBArg7(mFunctor);
        CHECK(27 == voidFunctorBArg7(true, 2, 3, 4, 5, 6, 7));
        CHECK(5040 == voidFunctorBArg7(false, 2, 3, 4, 5, 6, 7));
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
            QEXT_UNUSED(a1)
            *sg_string = "MRetVolatileFunctor::voidVolatileFunction1";
        }
        void operator()(int a1, int a2) volatile
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            *sg_string = "MRetVolatileFunctor::voidVolatileFunction2";
        }
        void operator()(int a1, int a2, int a3) volatile
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            *sg_string = "MRetVolatileFunctor::voidVolatileFunction3";
        }
        void operator()(int a1, int a2, int a3, int a4) volatile
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            *sg_string = "MRetVolatileFunctor::voidVolatileFunction4";
        }
        void operator()(int a1, int a2, int a3, int a4, int a5) volatile
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            *sg_string = "MRetVolatileFunctor::voidVolatileFunction5";
        }
        void operator()(int a1, int a2, int a3, int a4, int a5, int a6) volatile
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            QEXT_UNUSED(a6)
            *sg_string = "MRetVolatileFunctor::voidVolatileFunction6";
        }
        void operator()(int a1, int a2, int a3, int a4, int a5, int a6, int a7) volatile
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            QEXT_UNUSED(a6)
            QEXT_UNUSED(a7)
            *sg_string = "MRetVolatileFunctor::voidVolatileFunction7";
        }
        void operator()(bool a1) volatile
        {
            QEXT_UNUSED(a1)
            *sg_string = "MRetVolatileFunctor::voidVolatileFunctionB1";
        }
        void operator()(bool a1, int a2) volatile
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            *sg_string = "MRetVolatileFunctor::voidVolatileFunctionB2";
        }
        void operator()(bool a1, int a2, int a3) volatile
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            *sg_string = "MRetVolatileFunctor::voidVolatileFunctionB3";
        }
        void operator()(bool a1, int a2, int a3, int a4) volatile
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            *sg_string = "MRetVolatileFunctor::voidVolatileFunctionB4";
        }
        void operator()(bool a1, int a2, int a3, int a4, int a5) volatile
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            *sg_string = "MRetVolatileFunctor::voidVolatileFunctionB5";
        }
        void operator()(bool a1, int a2, int a3, int a4, int a5, int a6) volatile
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            QEXT_UNUSED(a6)
            *sg_string = "MRetVolatileFunctor::voidVolatileFunctionB6";
        }
        void operator()(bool a1, int a2, int a3, int a4, int a5, int a6, int a7) volatile
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            QEXT_UNUSED(a6)
            QEXT_UNUSED(a7)
            *sg_string = "MRetVolatileFunctor::voidVolatileFunctionB7";
        }
    };
    TEST(qextFunctionTest, retVolatileFunctor)
    {
        std::string string;
        sg_string = &string;
        MRetVolatileFunctor mFunctor;

        QEXTFunction< void > voidFunctorArg0(mFunctor);
        voidFunctorArg0();
        CHECK("MRetVolatileFunctor::voidVolatileFunction0" == string);
        QEXTFunction< void, int > voidFunctorArg1(mFunctor);
        voidFunctorArg1(1);
        CHECK("MRetVolatileFunctor::voidVolatileFunction1" == string);
        QEXTFunction< void, int, int > voidFunctorArg2(mFunctor);
        voidFunctorArg2(1, 2);
        CHECK("MRetVolatileFunctor::voidVolatileFunction2" == string);
        QEXTFunction< void, int, int, int > voidFunctorArg3(mFunctor);
        voidFunctorArg3(1, 2, 3);
        CHECK("MRetVolatileFunctor::voidVolatileFunction3" == string);
        QEXTFunction< void, int, int, int, int > voidFunctorArg4(mFunctor);
        voidFunctorArg4(1, 2, 3, 4);
        CHECK("MRetVolatileFunctor::voidVolatileFunction4" == string);
        QEXTFunction< void, int, int, int, int, int > voidFunctorArg5(mFunctor);
        voidFunctorArg5(1, 2, 3, 4, 5);
        CHECK("MRetVolatileFunctor::voidVolatileFunction5" == string);
        QEXTFunction< void, int, int, int, int, int, int > voidFunctorArg6(mFunctor);
        voidFunctorArg6(1, 2, 3, 4, 5, 6);
        CHECK("MRetVolatileFunctor::voidVolatileFunction6" == string);
        QEXTFunction< void, int, int, int, int, int, int, int > voidFunctorArg7(mFunctor);
        voidFunctorArg7(1, 2, 3, 4, 5, 6, 7);
        CHECK("MRetVolatileFunctor::voidVolatileFunction7" == string);

        QEXTFunction< void, bool > voidFunctorBArg1(mFunctor);
        voidFunctorBArg1(true);
        CHECK("MRetVolatileFunctor::voidVolatileFunctionB1" == string);
        QEXTFunction< void, bool, int > voidFunctorBArg2(mFunctor);
        voidFunctorBArg2(true, 2);
        CHECK("MRetVolatileFunctor::voidVolatileFunctionB2" == string);
        QEXTFunction< void, bool, int, int > voidFunctorBArg3(mFunctor);
        voidFunctorBArg3(true, 2, 3);
        CHECK("MRetVolatileFunctor::voidVolatileFunctionB3" == string);
        QEXTFunction< void, bool, int, int, int > voidFunctorBArg4(mFunctor);
        voidFunctorBArg4(true, 2, 3, 4);
        CHECK("MRetVolatileFunctor::voidVolatileFunctionB4" == string);
        QEXTFunction< void, bool, int, int, int, int > voidFunctorBArg5(mFunctor);
        voidFunctorBArg5(true, 2, 3, 4, 5);
        CHECK("MRetVolatileFunctor::voidVolatileFunctionB5" == string);
        QEXTFunction< void, bool, int, int, int, int, int > voidFunctorBArg6(mFunctor);
        voidFunctorBArg6(true, 2, 3, 4, 5, 6);
        CHECK("MRetVolatileFunctor::voidVolatileFunctionB6" == string);
        QEXTFunction< void, bool, int, int, int, int, int, int > voidFunctorBArg7(mFunctor);
        voidFunctorBArg7(true, 2, 3, 4, 5, 6, 7);
        CHECK("MRetVolatileFunctor::voidVolatileFunctionB7" == string);
    }

    class MRetIntVolatileFunctor : public QEXTFunctorBase
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
    TEST(qextFunctionTest, retIntVolatileFunctor)
    {
        std::string string;
        sg_string = &string;
        MRetIntVolatileFunctor mFunctor;

        QEXTFunction< int > intFunctorArg0(mFunctor);
        intFunctorArg0();
        CHECK("MRetIntVolatileFunctor::intVolatileFunction0" == string);
        QEXTFunction< int, int > intFunctorArg1(mFunctor);
        CHECK(1 == intFunctorArg1(1));
        QEXTFunction< int, int, int > intFunctorArg2(mFunctor);
        CHECK(3 == intFunctorArg2(1, 2));
        QEXTFunction< int, int, int, int > intFunctorArg3(mFunctor);
        CHECK(6 == intFunctorArg3(1, 2, 3));
        QEXTFunction< int, int, int, int, int > intFunctorArg4(mFunctor);
        CHECK(10 == intFunctorArg4(1, 2, 3, 4));
        QEXTFunction< int, int, int, int, int, int > intFunctorArg5(mFunctor);
        CHECK(15 == intFunctorArg5(1, 2, 3, 4, 5));
        QEXTFunction< int, int, int, int, int, int, int > intFunctorArg6(mFunctor);
        CHECK(21 == intFunctorArg6(1, 2, 3, 4, 5, 6));
        QEXTFunction< int, int, int, int, int, int, int, int > intFunctorArg7(mFunctor);
        CHECK(28 == intFunctorArg7(1, 2, 3, 4, 5, 6, 7));

        QEXTFunction< int, bool > intFunctorBArg1(mFunctor);
        CHECK(1 == intFunctorBArg1(true));
        CHECK(0 == intFunctorBArg1(false));
        QEXTFunction< int, bool, int > intFunctorBArg2(mFunctor);
        CHECK(2 == intFunctorBArg2(true, 2));
        CHECK(0 == intFunctorBArg2(false, 2));
        QEXTFunction< int, bool, int, int > intFunctorBArg3(mFunctor);
        CHECK(5 == intFunctorBArg3(true, 2, 3));
        CHECK(6 == intFunctorBArg3(false, 2, 3));
        QEXTFunction< int, bool, int, int, int > intFunctorBArg4(mFunctor);
        CHECK(9 == intFunctorBArg4(true, 2, 3, 4));
        CHECK(24 == intFunctorBArg4(false, 2, 3, 4));
        QEXTFunction< int, bool, int, int, int, int > intFunctorBArg5(mFunctor);
        CHECK(14 == intFunctorBArg5(true, 2, 3, 4, 5));
        CHECK(120 == intFunctorBArg5(false, 2, 3, 4, 5));
        QEXTFunction< int, bool, int, int, int, int, int > intFunctorBArg6(mFunctor);
        CHECK(20 == intFunctorBArg6(true, 2, 3, 4, 5, 6));
        CHECK(720 == intFunctorBArg6(false, 2, 3, 4, 5, 6));
        QEXTFunction< int, bool, int, int, int, int, int, int > intFunctorBArg7(mFunctor);
        CHECK(27 == intFunctorBArg7(true, 2, 3, 4, 5, 6, 7));
        CHECK(5040 == intFunctorBArg7(false, 2, 3, 4, 5, 6, 7));
    }

    class MRetDoubleVolatileFunctor : public QEXTFunctorBase
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
    TEST(qextFunctionTest, retDoubleVolatileFunctor)
    {
        std::string string;
        sg_string = &string;
        MRetDoubleVolatileFunctor mFunctor;

        QEXTFunction< double > doubleFunctorArg0(mFunctor);
        doubleFunctorArg0();
        CHECK("MRetDoubleVolatileFunctor::doubleVolatileFunction0" == string);
        QEXTFunction< double, double > doubleFunctorArg1(mFunctor);
        CHECK(1 == doubleFunctorArg1(1));
        QEXTFunction< double, double, double > doubleFunctorArg2(mFunctor);
        CHECK(3 == doubleFunctorArg2(1, 2));
        QEXTFunction< double, double, double, double > doubleFunctorArg3(mFunctor);
        CHECK(6 == doubleFunctorArg3(1, 2, 3));
        QEXTFunction< double, double, double, double, double > doubleFunctorArg4(mFunctor);
        CHECK(10 == doubleFunctorArg4(1, 2, 3, 4));
        QEXTFunction< double, double, double, double, double, double > doubleFunctorArg5(mFunctor);
        CHECK(15 == doubleFunctorArg5(1, 2, 3, 4, 5));
        QEXTFunction< double, double, double, double, double, double, double > doubleFunctorArg6(mFunctor);
        CHECK(21 == doubleFunctorArg6(1, 2, 3, 4, 5, 6));
        QEXTFunction< double, double, double, double, double, double, double, double > doubleFunctorArg7(mFunctor);
        CHECK(28 == doubleFunctorArg7(1, 2, 3, 4, 5, 6, 7));

        QEXTFunction< double, bool > voidFunctorBArg1(mFunctor);
        CHECK(1 == voidFunctorBArg1(true));
        CHECK(0 == voidFunctorBArg1(false));
        QEXTFunction< double, bool, double > voidFunctorBArg2(mFunctor);
        CHECK(2 == voidFunctorBArg2(true, 2));
        CHECK(0 == voidFunctorBArg2(false, 2));
        QEXTFunction< double, bool, double, double > voidFunctorBArg3(mFunctor);
        CHECK(5 == voidFunctorBArg3(true, 2, 3));
        CHECK(6 == voidFunctorBArg3(false, 2, 3));
        QEXTFunction< double, bool, double, double, double > voidFunctorBArg4(mFunctor);
        CHECK(9 == voidFunctorBArg4(true, 2, 3, 4));
        CHECK(24 == voidFunctorBArg4(false, 2, 3, 4));
        QEXTFunction< double, bool, double, double, double, double > voidFunctorBArg5(mFunctor);
        CHECK(14 == voidFunctorBArg5(true, 2, 3, 4, 5));
        CHECK(120 == voidFunctorBArg5(false, 2, 3, 4, 5));
        QEXTFunction< double, bool, double, double, double, double, double > voidFunctorBArg6(mFunctor);
        CHECK(20 == voidFunctorBArg6(true, 2, 3, 4, 5, 6));
        CHECK(720 == voidFunctorBArg6(false, 2, 3, 4, 5, 6));
        QEXTFunction< double, bool, double, double, double, double, double, double > voidFunctorBArg7(mFunctor);
        CHECK(27 == voidFunctorBArg7(true, 2, 3, 4, 5, 6, 7));
        CHECK(5040 == voidFunctorBArg7(false, 2, 3, 4, 5, 6, 7));
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
            QEXT_UNUSED(a1)
            *sg_string = "MRetConstVolatileFunctor::voidConstVolatileFunction1";
        }
        void operator()(int a1, int a2) const volatile
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            *sg_string = "MRetConstVolatileFunctor::voidConstVolatileFunction2";
        }
        void operator()(int a1, int a2, int a3) const volatile
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            *sg_string = "MRetConstVolatileFunctor::voidConstVolatileFunction3";
        }
        void operator()(int a1, int a2, int a3, int a4) const volatile
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            *sg_string = "MRetConstVolatileFunctor::voidConstVolatileFunction4";
        }
        void operator()(int a1, int a2, int a3, int a4, int a5) const volatile
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            *sg_string = "MRetConstVolatileFunctor::voidConstVolatileFunction5";
        }
        void operator()(int a1, int a2, int a3, int a4, int a5, int a6) const volatile
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            QEXT_UNUSED(a6)
            *sg_string = "MRetConstVolatileFunctor::voidConstVolatileFunction6";
        }
        void operator()(int a1, int a2, int a3, int a4, int a5, int a6, int a7) const volatile
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            QEXT_UNUSED(a6)
            QEXT_UNUSED(a7)
            *sg_string = "MRetConstVolatileFunctor::voidConstVolatileFunction7";
        }
        void operator()(bool a1) const volatile
        {
            QEXT_UNUSED(a1)
            *sg_string = "MRetConstVolatileFunctor::voidConstVolatileFunctionB1";
        }
        void operator()(bool a1, int a2) const volatile
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            *sg_string = "MRetConstVolatileFunctor::voidConstVolatileFunctionB2";
        }
        void operator()(bool a1, int a2, int a3) const volatile
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            *sg_string = "MRetConstVolatileFunctor::voidConstVolatileFunctionB3";
        }
        void operator()(bool a1, int a2, int a3, int a4) const volatile
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            *sg_string = "MRetConstVolatileFunctor::voidConstVolatileFunctionB4";
        }
        void operator()(bool a1, int a2, int a3, int a4, int a5) const volatile
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            *sg_string = "MRetConstVolatileFunctor::voidConstVolatileFunctionB5";
        }
        void operator()(bool a1, int a2, int a3, int a4, int a5, int a6) const volatile
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            QEXT_UNUSED(a6)
            *sg_string = "MRetConstVolatileFunctor::voidConstVolatileFunctionB6";
        }
        void operator()(bool a1, int a2, int a3, int a4, int a5, int a6, int a7) const volatile
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            QEXT_UNUSED(a6)
            QEXT_UNUSED(a7)
            *sg_string = "MRetConstVolatileFunctor::voidConstVolatileFunctionB7";
        }
    };
    TEST(qextFunctionTest, retConstVolatileFunctor)
    {
        std::string string;
        sg_string = &string;
        MRetConstVolatileFunctor mFunctor;

        QEXTFunction< void > voidFunctorArg0(mFunctor);
        voidFunctorArg0();
        CHECK("MRetConstVolatileFunctor::voidConstVolatileFunction0" == string);
        QEXTFunction< void, int > voidFunctorArg1(mFunctor);
        voidFunctorArg1(1);
        CHECK("MRetConstVolatileFunctor::voidConstVolatileFunction1" == string);
        QEXTFunction< void, int, int > voidFunctorArg2(mFunctor);
        voidFunctorArg2(1, 2);
        CHECK("MRetConstVolatileFunctor::voidConstVolatileFunction2" == string);
        QEXTFunction< void, int, int, int > voidFunctorArg3(mFunctor);
        voidFunctorArg3(1, 2, 3);
        CHECK("MRetConstVolatileFunctor::voidConstVolatileFunction3" == string);
        QEXTFunction< void, int, int, int, int > voidFunctorArg4(mFunctor);
        voidFunctorArg4(1, 2, 3, 4);
        CHECK("MRetConstVolatileFunctor::voidConstVolatileFunction4" == string);
        QEXTFunction< void, int, int, int, int, int > voidFunctorArg5(mFunctor);
        voidFunctorArg5(1, 2, 3, 4, 5);
        CHECK("MRetConstVolatileFunctor::voidConstVolatileFunction5" == string);
        QEXTFunction< void, int, int, int, int, int, int > voidFunctorArg6(mFunctor);
        voidFunctorArg6(1, 2, 3, 4, 5, 6);
        CHECK("MRetConstVolatileFunctor::voidConstVolatileFunction6" == string);
        QEXTFunction< void, int, int, int, int, int, int, int > voidFunctorArg7(mFunctor);
        voidFunctorArg7(1, 2, 3, 4, 5, 6, 7);
        CHECK("MRetConstVolatileFunctor::voidConstVolatileFunction7" == string);

        QEXTFunction< void, bool > voidFunctorBArg1(mFunctor);
        voidFunctorBArg1(true);
        CHECK("MRetConstVolatileFunctor::voidConstVolatileFunctionB1" == string);
        QEXTFunction< void, bool, int > voidFunctorBArg2(mFunctor);
        voidFunctorBArg2(true, 2);
        CHECK("MRetConstVolatileFunctor::voidConstVolatileFunctionB2" == string);
        QEXTFunction< void, bool, int, int > voidFunctorBArg3(mFunctor);
        voidFunctorBArg3(true, 2, 3);
        CHECK("MRetConstVolatileFunctor::voidConstVolatileFunctionB3" == string);
        QEXTFunction< void, bool, int, int, int > voidFunctorBArg4(mFunctor);
        voidFunctorBArg4(true, 2, 3, 4);
        CHECK("MRetConstVolatileFunctor::voidConstVolatileFunctionB4" == string);
        QEXTFunction< void, bool, int, int, int, int > voidFunctorBArg5(mFunctor);
        voidFunctorBArg5(true, 2, 3, 4, 5);
        CHECK("MRetConstVolatileFunctor::voidConstVolatileFunctionB5" == string);
        QEXTFunction< void, bool, int, int, int, int, int > voidFunctorBArg6(mFunctor);
        voidFunctorBArg6(true, 2, 3, 4, 5, 6);
        CHECK("MRetConstVolatileFunctor::voidConstVolatileFunctionB6" == string);
        QEXTFunction< void, bool, int, int, int, int, int, int > voidFunctorBArg7(mFunctor);
        voidFunctorBArg7(true, 2, 3, 4, 5, 6, 7);
        CHECK("MRetConstVolatileFunctor::voidConstVolatileFunctionB7" == string);
    }

    class MRetIntConstVolatileFunctor : public QEXTFunctorBase
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
    TEST(qextFunctionTest, retIntConstVolatileFunctor)
    {
        std::string string;
        sg_string = &string;
        MRetIntConstVolatileFunctor mFunctor;

        QEXTFunction< int > intFunctorArg0(mFunctor);
        intFunctorArg0();
        CHECK("MRetIntConstVolatileFunctor::intConstVolatileFunction0" == string);
        QEXTFunction< int, int > intFunctorArg1(mFunctor);
        CHECK(1 == intFunctorArg1(1));
        QEXTFunction< int, int, int > intFunctorArg2(mFunctor);
        CHECK(3 == intFunctorArg2(1, 2));
        QEXTFunction< int, int, int, int > intFunctorArg3(mFunctor);
        CHECK(6 == intFunctorArg3(1, 2, 3));
        QEXTFunction< int, int, int, int, int > intFunctorArg4(mFunctor);
        CHECK(10 == intFunctorArg4(1, 2, 3, 4));
        QEXTFunction< int, int, int, int, int, int > intFunctorArg5(mFunctor);
        CHECK(15 == intFunctorArg5(1, 2, 3, 4, 5));
        QEXTFunction< int, int, int, int, int, int, int > intFunctorArg6(mFunctor);
        CHECK(21 == intFunctorArg6(1, 2, 3, 4, 5, 6));
        QEXTFunction< int, int, int, int, int, int, int, int > intFunctorArg7(mFunctor);
        CHECK(28 == intFunctorArg7(1, 2, 3, 4, 5, 6, 7));

        QEXTFunction< int, bool > intFunctorBArg1(mFunctor);
        CHECK(1 == intFunctorBArg1(true));
        CHECK(0 == intFunctorBArg1(false));
        QEXTFunction< int, bool, int > intFunctorBArg2(mFunctor);
        CHECK(2 == intFunctorBArg2(true, 2));
        CHECK(0 == intFunctorBArg2(false, 2));
        QEXTFunction< int, bool, int, int > intFunctorBArg3(mFunctor);
        CHECK(5 == intFunctorBArg3(true, 2, 3));
        CHECK(6 == intFunctorBArg3(false, 2, 3));
        QEXTFunction< int, bool, int, int, int > intFunctorBArg4(mFunctor);
        CHECK(9 == intFunctorBArg4(true, 2, 3, 4));
        CHECK(24 == intFunctorBArg4(false, 2, 3, 4));
        QEXTFunction< int, bool, int, int, int, int > intFunctorBArg5(mFunctor);
        CHECK(14 == intFunctorBArg5(true, 2, 3, 4, 5));
        CHECK(120 == intFunctorBArg5(false, 2, 3, 4, 5));
        QEXTFunction< int, bool, int, int, int, int, int > intFunctorBArg6(mFunctor);
        CHECK(20 == intFunctorBArg6(true, 2, 3, 4, 5, 6));
        CHECK(720 == intFunctorBArg6(false, 2, 3, 4, 5, 6));
        QEXTFunction< int, bool, int, int, int, int, int, int > intFunctorBArg7(mFunctor);
        CHECK(27 == intFunctorBArg7(true, 2, 3, 4, 5, 6, 7));
        CHECK(5040 == intFunctorBArg7(false, 2, 3, 4, 5, 6, 7));
    }

    class MRetDoubleConstVolatileFunctor : public QEXTFunctorBase
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
    TEST(qextFunctionTest, retDoubleConstVolatileFunctor)
    {
        std::string string;
        sg_string = &string;
        MRetDoubleConstVolatileFunctor mFunctor;

        QEXTFunction< double > doubleFunctorArg0(mFunctor);
        doubleFunctorArg0();
        CHECK("MRetDoubleConstVolatileFunctor::doubleConstVolatileFunction0" == string);
        QEXTFunction< double, double > doubleFunctorArg1(mFunctor);
        CHECK(1 == doubleFunctorArg1(1));
        QEXTFunction< double, double, double > doubleFunctorArg2(mFunctor);
        CHECK(3 == doubleFunctorArg2(1, 2));
        QEXTFunction< double, double, double, double > doubleFunctorArg3(mFunctor);
        CHECK(6 == doubleFunctorArg3(1, 2, 3));
        QEXTFunction< double, double, double, double, double > doubleFunctorArg4(mFunctor);
        CHECK(10 == doubleFunctorArg4(1, 2, 3, 4));
        QEXTFunction< double, double, double, double, double, double > doubleFunctorArg5(mFunctor);
        CHECK(15 == doubleFunctorArg5(1, 2, 3, 4, 5));
        QEXTFunction< double, double, double, double, double, double, double > doubleFunctorArg6(mFunctor);
        CHECK(21 == doubleFunctorArg6(1, 2, 3, 4, 5, 6));
        QEXTFunction< double, double, double, double, double, double, double, double > doubleFunctorArg7(mFunctor);
        CHECK(28 == doubleFunctorArg7(1, 2, 3, 4, 5, 6, 7));

        QEXTFunction< double, bool > voidFunctorBArg1(mFunctor);
        CHECK(1 == voidFunctorBArg1(true));
        CHECK(0 == voidFunctorBArg1(false));
        QEXTFunction< double, bool, double > voidFunctorBArg2(mFunctor);
        CHECK(2 == voidFunctorBArg2(true, 2));
        CHECK(0 == voidFunctorBArg2(false, 2));
        QEXTFunction< double, bool, double, double > voidFunctorBArg3(mFunctor);
        CHECK(5 == voidFunctorBArg3(true, 2, 3));
        CHECK(6 == voidFunctorBArg3(false, 2, 3));
        QEXTFunction< double, bool, double, double, double > voidFunctorBArg4(mFunctor);
        CHECK(9 == voidFunctorBArg4(true, 2, 3, 4));
        CHECK(24 == voidFunctorBArg4(false, 2, 3, 4));
        QEXTFunction< double, bool, double, double, double, double > voidFunctorBArg5(mFunctor);
        CHECK(14 == voidFunctorBArg5(true, 2, 3, 4, 5));
        CHECK(120 == voidFunctorBArg5(false, 2, 3, 4, 5));
        QEXTFunction< double, bool, double, double, double, double, double > voidFunctorBArg6(mFunctor);
        CHECK(20 == voidFunctorBArg6(true, 2, 3, 4, 5, 6));
        CHECK(720 == voidFunctorBArg6(false, 2, 3, 4, 5, 6));
        QEXTFunction< double, bool, double, double, double, double, double, double > voidFunctorBArg7(mFunctor);
        CHECK(27 == voidFunctorBArg7(true, 2, 3, 4, 5, 6, 7));
        CHECK(5040 == voidFunctorBArg7(false, 2, 3, 4, 5, 6, 7));
    }

    TEST(qextFunctionTest, pointerFunctorWith0Arg)
    {
        QEXTFunction< void > voidFunctor(&voidFunction0);
        voidFunctor();
        CHECK("voidFunction0" == sg_functionString);
        QEXTFunction< int > intFunctor(&intFunction0);
        CHECK(0 == intFunctor());
        QEXTFunction< double > doubleFunctor(&doubleFunction0);
        CHECK(0 == doubleFunctor());
    }

    TEST(qextFunctionTest, pointerFunctorWith1Arg)
    {

        QEXTFunction< void, int > voidFunctor(&voidFunction1);
        voidFunctor(1);
        CHECK("voidFunction1" == sg_functionString);
        QEXTFunction< int, int > intFunctor(&intFunction1);
        CHECK(1 == intFunctor(1));
        QEXTFunction< double, double > doubleFunctor(&doubleFunction1);
        CHECK(1.1 == doubleFunctor(1.1));

        QEXTFunction< void, bool > voidFunctorB(&voidFunctionB1);
        voidFunctorB(1);
        CHECK("voidFunctionB1" == sg_functionString);
        QEXTFunction< int, bool > intFunctorB(&intFunctionB1);
        CHECK(1 == intFunctorB(true));
        CHECK(0 == intFunctorB(false));
        QEXTFunction< double, bool > doubleFunctorB(&doubleFunctionB1);
        CHECK(1 == doubleFunctorB(true));
        CHECK(0 == doubleFunctorB(false));

        QEXTFunction< void, int & > voidFunctorR(&voidFunctionR1);
        int a1 = 1;
        voidFunctorR(a1);
        CHECK(2 == a1);
    }

    TEST(qextFunctionTest, testFunctorWith2Arg)
    {
        QEXTFunction< void, int, int > voidFunctor(&voidFunction2);
        voidFunctor(1, 2);
        CHECK("voidFunction2" == sg_functionString);
        QEXTFunction< int, int, int > intFunctor(&intFunction2);
        CHECK(1 + 2 == intFunctor(1, 2));
        QEXTFunction< double, double, double > doubleFunctor(&doubleFunction2);
        CHECK(1.1 + 2.2 == doubleFunctor(1.1, 2.2));

        QEXTFunction< void, bool, int > voidFunctorB(&voidFunctionB2);
        voidFunctorB(true, 2);
        CHECK("voidFunctionB2" == sg_functionString);
        QEXTFunction< int, bool, int > intFunctorB(&intFunctionB2);
        CHECK(2 == intFunctorB(true, 2));
        CHECK(0 == intFunctorB(false, 2));
        QEXTFunction< double, bool, double > doubleFunctorB(&doubleFunctionB2);
        CHECK(2.2 == doubleFunctorB(true, 2.2));
        CHECK(0 == doubleFunctorB(false, 2.2));

        QEXTFunction< void, int &, int & > voidFunctorR(&voidFunctionR2);
        int a1 = 1;
        int a2 = 2;
        voidFunctorR(a1, a2);
        CHECK(2 == a1);
        CHECK(3 == a2);
    }

    TEST(qextFunctionTest, testFunctorWith3Arg)
    {
        QEXTFunction< void, int, int, int > voidFunctor(&voidFunction3);
        voidFunctor(1, 2, 3);
        CHECK("voidFunction3" == sg_functionString);
        QEXTFunction< int, int, int, int > intFunctor(&intFunction3);
        CHECK(1 + 2 + 3 == intFunctor(1, 2, 3));
        QEXTFunction< double, double, double, double > doubleFunctor(&doubleFunction3);
        CHECK(1.1 + 2.2 + 3.3 == doubleFunctor(1.1, 2.2, 3.3));

        QEXTFunction< void, bool, int, int > voidFunctorB3(&voidFunctionB3);
        voidFunctorB3(true, 2, 3);
        CHECK("voidFunctionB3" == sg_functionString);
        QEXTFunction< int, bool, int, int > intFunctorB(&intFunctionB3);
        CHECK(2 + 3 == intFunctorB(true, 2, 3));
        CHECK(2 * 3 == intFunctorB(false, 2, 3));
        QEXTFunction< double, bool, double, double > doubleFunctorB(&doubleFunctionB3);
        CHECK(2.2 + 3.3 == doubleFunctorB(true, 2.2, 3.3));
        CHECK(2.2 * 3.3 == doubleFunctorB(false, 2.2, 3.3));

        QEXTFunction< void, int &, int &, int & > voidFunctorR(&voidFunctionR3);
        int a1 = 1;
        int a2 = 2;
        int a3 = 3;
        voidFunctorR(a1, a2, a3);
        CHECK(2 == a1);
        CHECK(3 == a2);
        CHECK(4 == a3);
    }

    TEST(qextFunctionTest, testFunctorWith4Arg)
    {
        QEXTFunction< void, bool, int, int, int > voidFunctorB(&voidFunctionB4);
        voidFunctorB(1, 2, 3, 4);
        CHECK("voidFunctionB4" == sg_functionString);
        QEXTFunction< int, bool, int, int, int > intFunctorB(&intFunctionB4);
        CHECK(2 + 3 + 4 == intFunctorB(true, 2, 3, 4));
        CHECK(2 * 3 * 4 == intFunctorB(false, 2, 3, 4));
        QEXTFunction< double, bool, double, double, double > doubleFunctorB(&doubleFunctionB4);
        CHECK(2.2 + 3.3 + 4.4 == doubleFunctorB(true, 2.2, 3.3, 4.4));
        CHECK(2.2 * 3.3 * 4.4 == doubleFunctorB(false, 2.2, 3.3, 4.4));

        QEXTFunction< void, int, int, int, int > voidFunctor(&voidFunction4);
        voidFunctor(1, 2, 3, 4);
        CHECK("voidFunction4" == sg_functionString);
        QEXTFunction< int, int, int, int, int > intFunctor(&intFunction4);
        CHECK(1 + 2 + 3 + 4 == intFunctor(1, 2, 3, 4));
        QEXTFunction< double, double, double, double, double > doubleFunctor(&doubleFunction4);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 == doubleFunctor(1.1, 2.2, 3.3, 4.4));

        QEXTFunction< void, int &, int &, int &, int & > voidFunctorR(&voidFunctionR4);
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

    TEST(qextFunctionTest, testFunctorWith5Arg)
    {
        QEXTFunction< void, int, int, int, int, int > voidFunctor(&voidFunction5);
        voidFunctor(1, 2, 3, 4, 5);
        CHECK("voidFunction5" == sg_functionString);
        QEXTFunction< int, int, int, int, int, int > intFunctor(&intFunction5);
        CHECK(1 + 2 + 3 + 4 + 5 == intFunctor(1, 2, 3, 4, 5));
        QEXTFunction< double, double, double, double, double, double > doubleFunctor(&doubleFunction5);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleFunctor(1.1, 2.2, 3.3, 4.4, 5.5));

        QEXTFunction< void, bool, int, int, int, int > voidFunctorB(&voidFunctionB5);
        voidFunctorB(true, 2, 3, 4, 5);
        CHECK("voidFunctionB5" == sg_functionString);
        QEXTFunction< int, bool, int, int, int, int > intFunctorB(&intFunctionB5);
        CHECK(2 + 3 + 4 + 5 == intFunctorB(true, 2, 3, 4, 5));
        CHECK(2 * 3 * 4 * 5 == intFunctorB(false, 2, 3, 4, 5));
        QEXTFunction< double, bool, double, double, double, double > doubleFunctorB(&doubleFunctionB5);
        CHECK(2.2 + 3.3 + 4.4 + 5.5 == doubleFunctorB(true, 2.2, 3.3, 4.4, 5.5));
        CHECK(2.2 * 3.3 * 4.4 * 5.5 == doubleFunctorB(false, 2.2, 3.3, 4.4, 5.5));

        QEXTFunction< void, int &, int &, int &, int &, int & > voidFunctorR(&voidFunctionR5);
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

    TEST(qextFunctionTest, testFunctorWith6Arg)
    {
        QEXTFunction< void, int, int, int, int, int, int > voidFunctor(&voidFunction6);
        voidFunctor(1, 2, 3, 4, 5, 6);
        CHECK("voidFunction6" == sg_functionString);
        QEXTFunction< int, int, int, int, int, int, int > intFunctor(&intFunction6);
        CHECK(1 + 2 + 3 + 4 + 5 + 6 == intFunctor(1, 2, 3, 4, 5, 6));
        QEXTFunction< double, double, double, double, double, double, double > doubleFunctor(&doubleFunction6);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

        QEXTFunction< void, bool, int, int, int, int, int > voidFunctorB(&voidFunctionB6);
        voidFunctorB(true, 2, 3, 4, 5, 6);
        CHECK("voidFunctionB6" == sg_functionString);
        QEXTFunction< int, bool, int, int, int, int, int > intFunctorB(&intFunctionB6);
        CHECK(2 + 3 + 4 + 5 + 6 == intFunctorB(true, 2, 3, 4, 5, 6));
        CHECK(2 * 3 * 4 * 5 * 6 == intFunctorB(false, 2, 3, 4, 5, 6));
        QEXTFunction< double, bool, double, double, double, double, double > doubleFunctorB(&doubleFunctionB6);
        CHECK(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6));
        CHECK(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6));

        QEXTFunction< void, int &, int &, int &, int &, int &, int & > voidFunctorR(&voidFunctionR6);
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

    TEST(qextFunctionTest, pointerFunctorWith7Arg)
    {
        QEXTFunction< void, int, int, int, int, int, int, int > voidFunctor(&voidFunction7);
        voidFunctor(1, 2, 3, 4, 5, 6, 7);
        CHECK("voidFunction7" == sg_functionString);
        QEXTFunction< int, int, int, int, int, int, int, int > intFunctor(&intFunction7);
        CHECK(1 + 2 + 3 + 4 + 5 + 6 + 7 == intFunctor(1, 2, 3, 4, 5, 6, 7));
        QEXTFunction< double, double, double, double, double, double, double, double > doubleFunctor(&doubleFunction7);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

        QEXTFunction< void, bool, int, int, int, int, int, int > voidFunctorB(&voidFunctionB7);
        voidFunctorB(1, 2, 3, 4, 5, 6, 7);
        CHECK("voidFunctionB7" == sg_functionString);
        QEXTFunction< int, bool, int, int, int, int, int, int > intFunctorB(&intFunctionB7);
        CHECK(2 + 3 + 4 + 5 + 6 + 7 == intFunctorB(true, 2, 3, 4, 5, 6, 7));
        CHECK(2 * 3 * 4 * 5 * 6 * 7 == intFunctorB(false, 2, 3, 4, 5, 6, 7));
        QEXTFunction< double, bool, double, double, double, double, double, double > doubleFunctorB(&doubleFunctionB7);
        CHECK(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
        CHECK(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

        QEXTFunction< void, int &, int &, int &, int &, int &, int &, int & > voidFunctorR(&voidFunctionR7);
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

    TEST(qextFunctionTest, testBoundFunctorWith0Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        *sg_memberString = "";
        QEXTFunction< void > voidBoundMemberBaseFunctorR(memberBase, &MemberBase::voidFunction0);
        voidBoundMemberBaseFunctorR();
        CHECK("MemberBase::voidFunction0" == *sg_memberString);
        *sg_memberString = "";
        QEXTFunction< void > voidBoundMemberBaseFunctorP(&memberBase, &MemberBase::voidFunction0);
        voidBoundMemberBaseFunctorP();
        CHECK("MemberBase::voidFunction0" == *sg_memberString);

        *sg_memberString = "";
        QEXTFunction< int > intBoundMemberBaseFunctorR(memberBase, &MemberBase::intFunction0);
        intBoundMemberBaseFunctorR();
        CHECK("MemberBase::intFunction0" == *sg_memberString);
        *sg_memberString = "";
        QEXTFunction< int > intBoundMemberBaseFunctorP(&memberBase, &MemberBase::intFunction0);
        intBoundMemberBaseFunctorP();
        CHECK("MemberBase::intFunction0" == *sg_memberString);

        *sg_memberString = "";
        QEXTFunction< double > doubleBoundMemberBaseFunctorR(memberBase, &MemberBase::doubleFunction0);
        doubleBoundMemberBaseFunctorR();
        CHECK("MemberBase::doubleFunction0" == *sg_memberString);
        *sg_memberString = "";
        QEXTFunction< double > doubleBoundMemberBaseFunctorP(&memberBase, &MemberBase::doubleFunction0);
        doubleBoundMemberBaseFunctorP();
        CHECK("MemberBase::doubleFunction0" == *sg_memberString);
    }

    TEST(qextFunctionTest, testPolymorphismBoundFunctorWith0Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        *sg_memberString = "";
        QEXTFunction< void > voidBoundMemberBaseFunctorR(dynamic_cast< MemberBase & >(member), &MemberBase::voidFunction0);
        voidBoundMemberBaseFunctorR();
        CHECK("Member::voidFunction0" == *sg_memberString);
        *sg_memberString = "";
        QEXTFunction< void > voidBoundMemberBaseFunctorP(dynamic_cast< MemberBase * >(&member), &MemberBase::voidFunction0);
        voidBoundMemberBaseFunctorP();
        CHECK("Member::voidFunction0" == *sg_memberString);

        *sg_memberString = "";
        QEXTFunction< int > intBoundMemberBaseFunctorR(dynamic_cast< MemberBase & >(member), &MemberBase::intFunction0);
        intBoundMemberBaseFunctorR();
        CHECK("Member::intFunction0" == *sg_memberString);
        *sg_memberString = "";
        QEXTFunction< int > intBoundMemberBaseFunctorP(dynamic_cast< MemberBase * >(&member), &MemberBase::intFunction0);
        intBoundMemberBaseFunctorP();
        CHECK("Member::intFunction0" == *sg_memberString);

        *sg_memberString = "";
        QEXTFunction< double > doubleBoundMemberBaseFunctorR(dynamic_cast< MemberBase & >(member), &MemberBase::doubleFunction0);
        doubleBoundMemberBaseFunctorR();
        CHECK("Member::doubleFunction0" == *sg_memberString);
        *sg_memberString = "";
        QEXTFunction< double > doubleBoundMemberBaseFunctorP(dynamic_cast< MemberBase * >(&member), &MemberBase::doubleFunction0);
        doubleBoundMemberBaseFunctorP();
        CHECK("Member::doubleFunction0" == *sg_memberString);
    }

    //TODO ref test
    TEST(qextFunctionTest, testBoundConstFunctorWith0Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTFunction< void > voidBoundConstMemberBaseFunctor(&memberBase, &MemberBase::voidConstFunction0);
        voidBoundConstMemberBaseFunctor();
        CHECK("MemberBase::voidConstFunction0" == *sg_memberString);
        QEXTFunction< int > intBoundConstMemberBaseFunctor(&memberBase, &MemberBase::intConstFunction0);
        intBoundConstMemberBaseFunctor();
        CHECK("MemberBase::intConstFunction0" == *sg_memberString);
        QEXTFunction< double > doubleBoundConstMemberBaseFunctor(&memberBase, &MemberBase::doubleConstFunction0);
        doubleBoundConstMemberBaseFunctor();
        CHECK("MemberBase::doubleConstFunction0" == *sg_memberString);
    }

    TEST(qextFunctionTest, testPolymorphismBoundConstFunctorWith0Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTFunction< void > voidBoundConstMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstFunction0);
        voidBoundConstMemberBaseFunctor();
        CHECK("Member::voidConstFunction0" == *sg_memberString);
        QEXTFunction< int > intBoundConstMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::intConstFunction0);
        intBoundConstMemberBaseFunctor();
        CHECK("Member::intConstFunction0" == *sg_memberString);
        QEXTFunction< double > doubleBoundConstMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstFunction0);
        doubleBoundConstMemberBaseFunctor();
        CHECK("Member::doubleConstFunction0" == *sg_memberString);
    }

    TEST(qextFunctionTest, testBoundVolatileFunctorWith0Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTFunction< void > voidBoundVolatileMemberBaseFunctor(&memberBase, &MemberBase::voidVolatileFunction0);
        voidBoundVolatileMemberBaseFunctor();
        CHECK("MemberBase::voidVolatileFunction0" == *sg_memberString);
        QEXTFunction< int > intBoundVolatileMemberBaseFunctor(&memberBase, &MemberBase::intVolatileFunction0);
        intBoundVolatileMemberBaseFunctor();
        CHECK("MemberBase::intVolatileFunction0" == *sg_memberString);
        QEXTFunction< double > doubleBoundVolatileMemberBaseFunctor(&memberBase, &MemberBase::doubleVolatileFunction0);
        doubleBoundVolatileMemberBaseFunctor();
        CHECK("MemberBase::doubleVolatileFunction0" == *sg_memberString);
    }

    TEST(qextFunctionTest, testPolymorphismBoundVolatileFunctorWith0Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTFunction< void > voidBoundVolatileMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::voidVolatileFunction0);
        voidBoundVolatileMemberBaseFunctor();
        CHECK("Member::voidVolatileFunction0" == *sg_memberString);
        QEXTFunction< int > intBoundVolatileMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::intVolatileFunction0);
        intBoundVolatileMemberBaseFunctor();
        CHECK("Member::intVolatileFunction0" == *sg_memberString);
        QEXTFunction< double > doubleBoundVolatileMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::doubleVolatileFunction0);
        doubleBoundVolatileMemberBaseFunctor();
        CHECK("Member::doubleVolatileFunction0" == *sg_memberString);
    }

    TEST(qextFunctionTest, testBoundConstVolatileFunctorWith0Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTFunction< void > voidBoundConstVolatileMemberBaseFunctor(&memberBase, &MemberBase::voidConstVolatileFunction0);
        voidBoundConstVolatileMemberBaseFunctor();
        CHECK("MemberBase::voidConstVolatileFunction0" == *sg_memberString);
        QEXTFunction< int > intBoundConstVolatileMemberBaseFunctor(&memberBase, &MemberBase::intConstVolatileFunction0);
        intBoundConstVolatileMemberBaseFunctor();
        CHECK("MemberBase::intConstVolatileFunction0" == *sg_memberString);
        QEXTFunction< double > doubleBoundConstVolatileMemberBaseFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction0);
        doubleBoundConstVolatileMemberBaseFunctor();
        CHECK("MemberBase::doubleConstVolatileFunction0" == *sg_memberString);
    }

    TEST(qextFunctionTest, testPolymorphismBoundConstVolatileFunctorWith0Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTFunction< void > voidBoundConstVolatileMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstVolatileFunction0);
        voidBoundConstVolatileMemberBaseFunctor();
        CHECK("Member::voidConstVolatileFunction0" == *sg_memberString);
        QEXTFunction< int > intBoundConstVolatileMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::intConstVolatileFunction0);
        intBoundConstVolatileMemberBaseFunctor();
        CHECK("Member::intConstVolatileFunction0" == *sg_memberString);
        QEXTFunction< double > doubleBoundConstVolatileMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstVolatileFunction0);
        doubleBoundConstVolatileMemberBaseFunctor();
        CHECK("Member::doubleConstVolatileFunction0" == *sg_memberString);
    }

    TEST(qextFunctionTest, testBoundFunctorWith1Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTFunction< void, int > voidBoundMemberBaseFunctor(&memberBase, &MemberBase::voidFunction1);
        voidBoundMemberBaseFunctor(1);
        CHECK("MemberBase::voidFunction1" == *sg_memberString);
        QEXTFunction< int, int > intBoundMemberBaseFunctor(&memberBase, &MemberBase::intFunction1);
        CHECK(1 == intBoundMemberBaseFunctor(1));
        QEXTFunction< double, double > doubleBoundMemberBaseFunctor(&memberBase, &MemberBase::doubleFunction1);
        CHECK(1.1 == doubleBoundMemberBaseFunctor(1.1));

        QEXTFunction< void, bool > voidBoundMemberBaseFunctorB(&memberBase, &MemberBase::voidFunctionB1);
        voidBoundMemberBaseFunctorB(1);
        CHECK("MemberBase::voidFunctionB1" == *sg_memberString);
        QEXTFunction< int, bool > intBoundMemberBaseFunctorB(&memberBase, &MemberBase::intFunctionB1);
        CHECK(1 == intBoundMemberBaseFunctorB(true));
        CHECK(0 == intBoundMemberBaseFunctorB(false));
        QEXTFunction< double, bool > doubleBoundMemberBaseFunctorB(&memberBase, &MemberBase::doubleFunctionB1);
        CHECK(1 == doubleBoundMemberBaseFunctorB(true));
        CHECK(0 == doubleBoundMemberBaseFunctorB(false));
    }

    TEST(qextFunctionTest, testPolymorphismBoundFunctorWith1Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTFunction< void, int > voidBoundMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::voidFunction1);
        voidBoundMemberBaseFunctor(1);
        CHECK("Member::voidFunction1" == *sg_memberString);
        QEXTFunction< int, int > intBoundMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::intFunction1);
        CHECK(0 == intBoundMemberBaseFunctor(1));
        QEXTFunction< double, double > doubleBoundMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::doubleFunction1);
        CHECK(0 == doubleBoundMemberBaseFunctor(1.1));

        QEXTFunction< void, bool > voidBoundMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::voidFunctionB1);
        voidBoundMemberBaseFunctorB(1);
        CHECK("Member::voidFunctionB1" == *sg_memberString);
        QEXTFunction< int, bool > intBoundMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::intFunctionB1);
        CHECK(1 == intBoundMemberBaseFunctorB(true));
        CHECK(0 == intBoundMemberBaseFunctorB(false));
        QEXTFunction< double, bool > doubleBoundMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::doubleFunctionB1);
        CHECK(1 == doubleBoundMemberBaseFunctorB(true));
        CHECK(0 == doubleBoundMemberBaseFunctorB(false));
    }

    TEST(qextFunctionTest, testBoundConstFunctorWith1Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTFunction< void, int > voidBoundConstMemberBaseFunctor(&memberBase, &MemberBase::voidConstFunction1);
        voidBoundConstMemberBaseFunctor(1);
        CHECK("MemberBase::voidConstFunction1" == *sg_memberString);
        QEXTFunction< int, int > intBoundConstMemberBaseFunctor(&memberBase, &MemberBase::intConstFunction1);
        CHECK(1 == intBoundConstMemberBaseFunctor(1));
        QEXTFunction< double, double > doubleBoundConstMemberBaseFunctor(&memberBase, &MemberBase::doubleConstFunction1);
        CHECK(1.1 == doubleBoundConstMemberBaseFunctor(1.1));

        QEXTFunction< void, bool > voidBoundConstMemberBaseFunctorB(&memberBase, &MemberBase::voidConstFunctionB1);
        voidBoundConstMemberBaseFunctorB(1);
        CHECK("MemberBase::voidConstFunctionB1" == *sg_memberString);
        QEXTFunction< int, bool > intBoundConstMemberBaseFunctorB(&memberBase, &MemberBase::intConstFunctionB1);
        CHECK(1 == intBoundConstMemberBaseFunctorB(true));
        CHECK(0 == intBoundConstMemberBaseFunctorB(false));
        QEXTFunction< double, bool > doubleBoundConstMemberBaseFunctorB(&memberBase, &MemberBase::doubleConstFunctionB1);
        CHECK(1 == doubleBoundConstMemberBaseFunctorB(true));
        CHECK(0 == doubleBoundConstMemberBaseFunctorB(false));
    }

    TEST(qextFunctionTest, testPolymorphismBoundConstFunctorWith1Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTFunction< void, int > voidBoundConstMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstFunction1);
        voidBoundConstMemberBaseFunctor(1);
        CHECK("Member::voidConstFunction1" == *sg_memberString);
        QEXTFunction< int, int > intBoundConstMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::intConstFunction1);
        CHECK(0 == intBoundConstMemberBaseFunctor(1));
        QEXTFunction< double, double > doubleBoundConstMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstFunction1);
        CHECK(0 == doubleBoundConstMemberBaseFunctor(1.1));

        QEXTFunction< void, bool > voidBoundConstMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstFunctionB1);
        voidBoundConstMemberBaseFunctorB(1);
        CHECK("Member::voidConstFunctionB1" == *sg_memberString);
        QEXTFunction< int, bool > intBoundConstMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::intConstFunctionB1);
        CHECK(1 == intBoundConstMemberBaseFunctorB(true));
        CHECK(0 == intBoundConstMemberBaseFunctorB(false));
        QEXTFunction< double, bool > doubleBoundConstMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstFunctionB1);
        CHECK(1 == doubleBoundConstMemberBaseFunctorB(true));
        CHECK(0 == doubleBoundConstMemberBaseFunctorB(false));
    }

    TEST(qextFunctionTest, testBoundVolatileFunctorWith1Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTFunction< void, int > voidBoundVolatileMemberBaseFunctor(&memberBase, &MemberBase::voidVolatileFunction1);
        voidBoundVolatileMemberBaseFunctor(1);
        CHECK("MemberBase::voidVolatileFunction1" == *sg_memberString);
        QEXTFunction< int, int > intBoundVolatileMemberBaseFunctor(&memberBase, &MemberBase::intVolatileFunction1);
        CHECK(1 == intBoundVolatileMemberBaseFunctor(1));
        QEXTFunction< double, double > doubleBoundVolatileMemberBaseFunctor(&memberBase, &MemberBase::doubleVolatileFunction1);
        CHECK(1.1 == doubleBoundVolatileMemberBaseFunctor(1.1));

        QEXTFunction< void, bool > voidBoundVolatileMemberBaseFunctorB(&memberBase, &MemberBase::voidVolatileFunctionB1);
        voidBoundVolatileMemberBaseFunctorB(1);
        CHECK("MemberBase::voidVolatileFunctionB1" == *sg_memberString);
        QEXTFunction< int, bool > intBoundVolatileMemberBaseFunctorB(&memberBase, &MemberBase::intVolatileFunctionB1);
        CHECK(1 == intBoundVolatileMemberBaseFunctorB(true));
        CHECK(0 == intBoundVolatileMemberBaseFunctorB(false));
        QEXTFunction< double, bool > doubleBoundVolatileMemberBaseFunctorB(&memberBase, &MemberBase::doubleVolatileFunctionB1);
        CHECK(1 == doubleBoundVolatileMemberBaseFunctorB(true));
        CHECK(0 == doubleBoundVolatileMemberBaseFunctorB(false));
    }

    TEST(qextFunctionTest, testPolymorphismBoundVolatileFunctorWith1Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTFunction< void, int > voidBoundVolatileMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::voidVolatileFunction1);
        voidBoundVolatileMemberBaseFunctor(1);
        CHECK("Member::voidVolatileFunction1" == *sg_memberString);
        QEXTFunction< int, int > intBoundVolatileMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::intVolatileFunction1);
        CHECK(0 == intBoundVolatileMemberBaseFunctor(1));
        QEXTFunction< double, double > doubleBoundVolatileMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::doubleVolatileFunction1);
        CHECK(0 == doubleBoundVolatileMemberBaseFunctor(1.1));

        QEXTFunction< void, bool > voidBoundVolatileMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::voidVolatileFunctionB1);
        voidBoundVolatileMemberBaseFunctorB(1);
        CHECK("Member::voidVolatileFunctionB1" == *sg_memberString);
        QEXTFunction< int, bool > intBoundVolatileMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::intVolatileFunctionB1);
        CHECK(1 == intBoundVolatileMemberBaseFunctorB(true));
        CHECK(0 == intBoundVolatileMemberBaseFunctorB(false));
        QEXTFunction< double, bool > doubleBoundVolatileMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::doubleVolatileFunctionB1);
        CHECK(1 == doubleBoundVolatileMemberBaseFunctorB(true));
        CHECK(0 == doubleBoundVolatileMemberBaseFunctorB(false));
    }

    TEST(qextFunctionTest, testBoundConstVolatileFunctorWith1Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTFunction< void, int > voidBoundConstVolatileMemberBaseFunctor(&memberBase, &MemberBase::voidConstVolatileFunction1);
        voidBoundConstVolatileMemberBaseFunctor(1);
        CHECK("MemberBase::voidConstVolatileFunction1" == *sg_memberString);
        QEXTFunction< int, int > intBoundConstVolatileMemberBaseFunctor(&memberBase, &MemberBase::intConstVolatileFunction1);
        CHECK(1 == intBoundConstVolatileMemberBaseFunctor(1));
        QEXTFunction< double, double > doubleBoundConstVolatileMemberBaseFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction1);
        CHECK(1.1 == doubleBoundConstVolatileMemberBaseFunctor(1.1));

        QEXTFunction< void, bool > voidBoundConstVolatileMemberBaseFunctorB(&memberBase, &MemberBase::voidConstVolatileFunctionB1);
        voidBoundConstVolatileMemberBaseFunctorB(1);
        CHECK("MemberBase::voidConstVolatileFunctionB1" == *sg_memberString);
        QEXTFunction< int, bool > intBoundConstVolatileMemberBaseFunctorB(&memberBase, &MemberBase::intConstVolatileFunctionB1);
        CHECK(1 == intBoundConstVolatileMemberBaseFunctorB(true));
        CHECK(0 == intBoundConstVolatileMemberBaseFunctorB(false));
        QEXTFunction< double, bool > doubleBoundConstVolatileMemberBaseFunctorB(&memberBase, &MemberBase::doubleConstVolatileFunctionB1);
        CHECK(1 == doubleBoundConstVolatileMemberBaseFunctorB(true));
        CHECK(0 == doubleBoundConstVolatileMemberBaseFunctorB(false));
    }

    TEST(qextFunctionTest, testPolymorphismBoundConstVolatileFunctorWith1Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTFunction< void, int > voidBoundConstVolatileMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstVolatileFunction1);
        voidBoundConstVolatileMemberBaseFunctor(1);
        CHECK("Member::voidConstVolatileFunction1" == *sg_memberString);
        QEXTFunction< int, int > intBoundConstVolatileMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::intConstVolatileFunction1);
        CHECK(0 == intBoundConstVolatileMemberBaseFunctor(1));
        QEXTFunction< double, double > doubleBoundConstVolatileMemberBaseFunctor(
            dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstVolatileFunction1);
        CHECK(0 == doubleBoundConstVolatileMemberBaseFunctor(1.1));

        QEXTFunction< void, bool > voidBoundConstVolatileMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstVolatileFunctionB1);
        voidBoundConstVolatileMemberBaseFunctorB(1);
        CHECK("Member::voidConstVolatileFunctionB1" == *sg_memberString);
        QEXTFunction< int, bool > intBoundConstVolatileMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::intConstVolatileFunctionB1);
        CHECK(1 == intBoundConstVolatileMemberBaseFunctorB(true));
        CHECK(0 == intBoundConstVolatileMemberBaseFunctorB(false));
        QEXTFunction< double, bool > doubleBoundConstVolatileMemberBaseFunctorB(
            dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstVolatileFunctionB1);
        CHECK(1 == doubleBoundConstVolatileMemberBaseFunctorB(true));
        CHECK(0 == doubleBoundConstVolatileMemberBaseFunctorB(false));
    }

    TEST(qextFunctionTest, testBoundFunctorWith2Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTFunction< void, int, int > voidBoundMemberBaseFunctor(&memberBase, &MemberBase::voidFunction2);
        voidBoundMemberBaseFunctor(1, 2);
        CHECK("MemberBase::voidFunction2" == *sg_memberString);
        QEXTFunction< int, int, int > intBoundMemberBaseFunctor(&memberBase, &MemberBase::intFunction2);
        CHECK(1 + 2 == intBoundMemberBaseFunctor(1, 2));
        QEXTFunction< double, double, double > doubleBoundMemberBaseFunctor(&memberBase, &MemberBase::doubleFunction2);
        CHECK(1.1 + 2.2 == doubleBoundMemberBaseFunctor(1.1, 2.2));

        QEXTFunction< void, bool, int > voidBoundMemberBaseFunctorB(&memberBase, &MemberBase::voidFunctionB2);
        voidBoundMemberBaseFunctorB(true, 2);
        CHECK("MemberBase::voidFunctionB2" == *sg_memberString);
        QEXTFunction< int, bool, int > intBoundMemberBaseFunctorB(&memberBase, &MemberBase::intFunctionB2);
        CHECK(2 == intBoundMemberBaseFunctorB(true, 2));
        CHECK(0 == intBoundMemberBaseFunctorB(false, 2));
        QEXTFunction< double, bool, double > doubleBoundMemberBaseFunctorB(&memberBase, &MemberBase::doubleFunctionB2);
        CHECK(2.2 == doubleBoundMemberBaseFunctorB(true, 2.2));
        CHECK(0 == doubleBoundMemberBaseFunctorB(false, 2.2));
    }

    TEST(qextFunctionTest, testPolymorphismBoundFunctorWith2Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTFunction< void, int, int > voidBoundMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::voidFunction2);
        voidBoundMemberBaseFunctor(1, 2);
        CHECK("Member::voidFunction2" == *sg_memberString);
        QEXTFunction< int, int, int > intBoundMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::intFunction2);
        CHECK(0 == intBoundMemberBaseFunctor(1, 2));
        QEXTFunction< double, double, double > doubleBoundMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::doubleFunction2);
        CHECK(0 == doubleBoundMemberBaseFunctor(1.1, 2.2));

        QEXTFunction< void, bool, int > voidBoundMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::voidFunctionB2);
        voidBoundMemberBaseFunctorB(true, 2);
        CHECK("Member::voidFunctionB2" == *sg_memberString);
        QEXTFunction< int, bool, int > intBoundMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::intFunctionB2);
        CHECK(1 == intBoundMemberBaseFunctorB(true, 2));
        CHECK(0 == intBoundMemberBaseFunctorB(false, 2));
        QEXTFunction< double, bool, double > doubleBoundMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::doubleFunctionB2);
        CHECK(1 == doubleBoundMemberBaseFunctorB(true, 2.2));
        CHECK(0 == doubleBoundMemberBaseFunctorB(false, 2.2));
    }

    TEST(qextFunctionTest, testBoundConstFunctorWith2Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTFunction< void, int, int > voidBoundConstMemberBaseFunctor(&memberBase, &MemberBase::voidConstFunction2);
        voidBoundConstMemberBaseFunctor(1, 2);
        CHECK("MemberBase::voidConstFunction2" == *sg_memberString);
        QEXTFunction< int, int, int > intBoundConstMemberBaseFunctor(&memberBase, &MemberBase::intConstFunction2);
        CHECK(1 + 2 == intBoundConstMemberBaseFunctor(1, 2));
        QEXTFunction< double, double, double > doubleBoundConstMemberBaseFunctor(&memberBase, &MemberBase::doubleConstFunction2);
        CHECK(1.1 + 2.2 == doubleBoundConstMemberBaseFunctor(1.1, 2.2));

        QEXTFunction< void, bool, int > voidBoundConstMemberBaseFunctorB(&memberBase, &MemberBase::voidConstFunctionB2);
        voidBoundConstMemberBaseFunctorB(true, 2);
        CHECK("MemberBase::voidConstFunctionB2" == *sg_memberString);
        QEXTFunction< int, bool, int > intBoundConstMemberBaseFunctorB(&memberBase, &MemberBase::intConstFunctionB2);
        CHECK(2 == intBoundConstMemberBaseFunctorB(true, 2));
        CHECK(0 == intBoundConstMemberBaseFunctorB(false, 2));
        QEXTFunction< double, bool, double > doubleBoundConstMemberBaseFunctorB(&memberBase, &MemberBase::doubleConstFunctionB2);
        CHECK(2.2 == doubleBoundConstMemberBaseFunctorB(true, 2.2));
        CHECK(0 == doubleBoundConstMemberBaseFunctorB(false, 2.2));
    }

    TEST(qextFunctionTest, testPolymorphismBoundConstFunctorWith2Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTFunction< void, int, int > voidBoundConstMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstFunction2);
        voidBoundConstMemberBaseFunctor(1, 2);
        CHECK("Member::voidConstFunction2" == *sg_memberString);
        QEXTFunction< int, int, int > intBoundConstMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::intConstFunction2);
        CHECK(0 == intBoundConstMemberBaseFunctor(1, 2));
        QEXTFunction< double, double, double > doubleBoundConstMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstFunction2);
        CHECK(0 == doubleBoundConstMemberBaseFunctor(1.1, 2.2));

        QEXTFunction< void, bool, int > voidBoundConstMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstFunctionB2);
        voidBoundConstMemberBaseFunctorB(true, 2);
        CHECK("Member::voidConstFunctionB2" == *sg_memberString);
        QEXTFunction< int, bool, int > intBoundConstMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::intConstFunctionB2);
        CHECK(1 == intBoundConstMemberBaseFunctorB(true, 2));
        CHECK(0 == intBoundConstMemberBaseFunctorB(false, 2));
        QEXTFunction< double, bool, double > doubleBoundConstMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstFunctionB2);
        CHECK(1 == doubleBoundConstMemberBaseFunctorB(true, 2.2));
        CHECK(0 == doubleBoundConstMemberBaseFunctorB(false, 2.2));
    }

    TEST(qextFunctionTest, testBoundVolatileFunctorWith2Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTFunction< void, int, int > voidBoundVolatileMemberBaseFunctor(&memberBase, &MemberBase::voidVolatileFunction2);
        voidBoundVolatileMemberBaseFunctor(1, 2);
        CHECK("MemberBase::voidVolatileFunction2" == *sg_memberString);
        QEXTFunction< int, int, int > intBoundVolatileMemberBaseFunctor(&memberBase, &MemberBase::intVolatileFunction2);
        CHECK(1 + 2 == intBoundVolatileMemberBaseFunctor(1, 2));
        QEXTFunction< double, double, double > doubleBoundVolatileMemberBaseFunctor(&memberBase, &MemberBase::doubleVolatileFunction2);
        CHECK(1.1 + 2.2 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2));

        QEXTFunction< void, bool, int > voidBoundVolatileMemberBaseFunctorB(&memberBase, &MemberBase::voidVolatileFunctionB2);
        voidBoundVolatileMemberBaseFunctorB(true, 2);
        CHECK("MemberBase::voidVolatileFunctionB2" == *sg_memberString);
        QEXTFunction< int, bool, int > intBoundVolatileMemberBaseFunctorB(&memberBase, &MemberBase::intVolatileFunctionB2);
        CHECK(2 == intBoundVolatileMemberBaseFunctorB(true, 2));
        CHECK(0 == intBoundVolatileMemberBaseFunctorB(false, 2));
        QEXTFunction< double, bool, double > doubleBoundVolatileMemberBaseFunctorB(&memberBase, &MemberBase::doubleVolatileFunctionB2);
        CHECK(2.2 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2));
        CHECK(0 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2));
    }

    TEST(qextFunctionTest, testPolymorphismBoundVolatileFunctorWith2Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTFunction< void, int, int > voidBoundVolatileMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::voidVolatileFunction2);
        voidBoundVolatileMemberBaseFunctor(1, 2);
        CHECK("Member::voidVolatileFunction2" == *sg_memberString);
        QEXTFunction< int, int, int > intBoundVolatileMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::intVolatileFunction2);
        CHECK(0 == intBoundVolatileMemberBaseFunctor(1, 2));
        QEXTFunction< double, double, double > doubleBoundVolatileMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::doubleVolatileFunction2);
        CHECK(0 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2));

        QEXTFunction< void, bool, int > voidBoundVolatileMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::voidVolatileFunctionB2);
        voidBoundVolatileMemberBaseFunctorB(true, 2);
        CHECK("Member::voidVolatileFunctionB2" == *sg_memberString);
        QEXTFunction< int, bool, int > intBoundVolatileMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::intVolatileFunctionB2);
        CHECK(1 == intBoundVolatileMemberBaseFunctorB(true, 2));
        CHECK(0 == intBoundVolatileMemberBaseFunctorB(false, 2));
        QEXTFunction< double, bool, double > doubleBoundVolatileMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::doubleVolatileFunctionB2);
        CHECK(1 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2));
        CHECK(0 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2));
    }

    TEST(qextFunctionTest, testBoundConstVolatileFunctorWith2Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTFunction< void, int, int > voidBoundConstVolatileMemberBaseFunctor(&memberBase, &MemberBase::voidConstVolatileFunction2);
        voidBoundConstVolatileMemberBaseFunctor(1, 2);
        CHECK("MemberBase::voidConstVolatileFunction2" == *sg_memberString);
        QEXTFunction< int, int, int > intBoundConstVolatileMemberBaseFunctor(&memberBase, &MemberBase::intConstVolatileFunction2);
        CHECK(1 + 2 == intBoundConstVolatileMemberBaseFunctor(1, 2));
        QEXTFunction< double, double, double > doubleBoundConstVolatileMemberBaseFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction2);
        CHECK(1.1 + 2.2 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2));

        QEXTFunction< void, bool, int > voidBoundConstVolatileMemberBaseFunctorB(&memberBase, &MemberBase::voidConstVolatileFunctionB2);
        voidBoundConstVolatileMemberBaseFunctorB(true, 2);
        CHECK("MemberBase::voidConstVolatileFunctionB2" == *sg_memberString);
        QEXTFunction< int, bool, int > intBoundConstVolatileMemberBaseFunctorB(&memberBase, &MemberBase::intConstVolatileFunctionB2);
        CHECK(2 == intBoundConstVolatileMemberBaseFunctorB(true, 2));
        CHECK(0 == intBoundConstVolatileMemberBaseFunctorB(false, 2));
        QEXTFunction< double, bool, double > doubleBoundConstVolatileMemberBaseFunctorB(&memberBase, &MemberBase::doubleConstVolatileFunctionB2);
        CHECK(2.2 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2));
        CHECK(0 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2));
    }

    TEST(qextFunctionTest, testPolymorphismBoundConstVolatileFunctorWith2Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTFunction< void, int, int > voidBoundConstVolatileMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstVolatileFunction2);
        voidBoundConstVolatileMemberBaseFunctor(1, 2);
        CHECK("Member::voidConstVolatileFunction2" == *sg_memberString);
        QEXTFunction< int, int, int > intBoundConstVolatileMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::intConstVolatileFunction2);
        CHECK(0 == intBoundConstVolatileMemberBaseFunctor(1, 2));
        QEXTFunction< double, double, double > doubleBoundConstVolatileMemberBaseFunctor(
            dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstVolatileFunction2);
        CHECK(0 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2));

        QEXTFunction< void, bool, int > voidBoundConstVolatileMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstVolatileFunctionB2);
        voidBoundConstVolatileMemberBaseFunctorB(true, 2);
        CHECK("Member::voidConstVolatileFunctionB2" == *sg_memberString);
        QEXTFunction< int, bool, int > intBoundConstVolatileMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::intConstVolatileFunctionB2);
        CHECK(1 == intBoundConstVolatileMemberBaseFunctorB(true, 2));
        CHECK(0 == intBoundConstVolatileMemberBaseFunctorB(false, 2));
        QEXTFunction< double, bool, double > doubleBoundConstVolatileMemberBaseFunctorB(
            dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstVolatileFunctionB2);
        CHECK(1 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2));
        CHECK(0 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2));
    }

    TEST(qextFunctionTest, testBoundFunctorWith3Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTFunction< void, int, int, int > voidBoundMemberBaseFunctor(&memberBase, &MemberBase::voidFunction3);
        voidBoundMemberBaseFunctor(1, 2, 3);
        CHECK("MemberBase::voidFunction3" == *sg_memberString);
        QEXTFunction< int, int, int, int > intBoundMemberBaseFunctor(&memberBase, &MemberBase::intFunction3);
        CHECK(1 + 2 + 3 == intBoundMemberBaseFunctor(1, 2, 3));
        QEXTFunction< double, double, double, double > doubleBoundMemberBaseFunctor(&memberBase, &MemberBase::doubleFunction3);
        CHECK(1.1 + 2.2 + 3.3 == doubleBoundMemberBaseFunctor(1.1, 2.2, 3.3));

        QEXTFunction< void, bool, int, int > voidBoundMemberBaseFunctorB(&memberBase, &MemberBase::voidFunctionB3);
        voidBoundMemberBaseFunctorB(true, 2, 3);
        CHECK("MemberBase::voidFunctionB3" == *sg_memberString);
        QEXTFunction< int, bool, int, int > intBoundMemberBaseFunctorB(&memberBase, &MemberBase::intFunctionB3);
        CHECK(2 + 3 == intBoundMemberBaseFunctorB(true, 2, 3));
        CHECK(2 * 3 == intBoundMemberBaseFunctorB(false, 2, 3));
        QEXTFunction< double, bool, double, double > doubleBoundMemberBaseFunctorB(&memberBase, &MemberBase::doubleFunctionB3);
        CHECK(2.2 + 3.3 == doubleBoundMemberBaseFunctorB(true, 2.2, 3.3));
        CHECK(2.2 * 3.3 == doubleBoundMemberBaseFunctorB(false, 2.2, 3.3));
    }

    TEST(qextFunctionTest, testPolymorphismBoundFunctorWith3Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTFunction< void, int, int, int > voidBoundMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::voidFunction3);
        voidBoundMemberBaseFunctor(1, 2, 3);
        CHECK("Member::voidFunction3" == *sg_memberString);
        QEXTFunction< int, int, int, int > intBoundMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::intFunction3);
        CHECK(0 == intBoundMemberBaseFunctor(1, 2, 3));
        QEXTFunction< double, double, double, double > doubleBoundMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::doubleFunction3);
        CHECK(0 == doubleBoundMemberBaseFunctor(1.1, 2.2, 3.3));

        QEXTFunction< void, bool, int, int > voidBoundMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::voidFunctionB3);
        voidBoundMemberBaseFunctorB(true, 2, 3);
        CHECK("Member::voidFunctionB3" == *sg_memberString);
        QEXTFunction< int, bool, int, int > intBoundMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::intFunctionB3);
        CHECK(1 == intBoundMemberBaseFunctorB(true, 2, 3));
        CHECK(0 == intBoundMemberBaseFunctorB(false, 2, 3));
        QEXTFunction< double, bool, double, double > doubleBoundMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::doubleFunctionB3);
        CHECK(1 == doubleBoundMemberBaseFunctorB(true, 2.2, 3.3));
        CHECK(0 == doubleBoundMemberBaseFunctorB(false, 2.2, 3.3));
    }

    TEST(qextFunctionTest, testBoundConstFunctorWith3Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTFunction< void, int, int, int > voidBoundConstMemberBaseFunctor(&memberBase, &MemberBase::voidConstFunction3);
        voidBoundConstMemberBaseFunctor(1, 2, 3);
        CHECK("MemberBase::voidConstFunction3" == *sg_memberString);
        QEXTFunction< int, int, int, int > intBoundConstMemberBaseFunctor(&memberBase, &MemberBase::intConstFunction3);
        CHECK(1 + 2 + 3 == intBoundConstMemberBaseFunctor(1, 2, 3));
        QEXTFunction< double, double, double, double > doubleBoundConstMemberBaseFunctor(&memberBase, &MemberBase::doubleConstFunction3);
        CHECK(1.1 + 2.2 + 3.3 == doubleBoundConstMemberBaseFunctor(1.1, 2.2, 3.3));

        QEXTFunction< void, bool, int, int > voidBoundConstMemberBaseFunctorB(&memberBase, &MemberBase::voidConstFunctionB3);
        voidBoundConstMemberBaseFunctorB(true, 2, 3);
        CHECK("MemberBase::voidConstFunctionB3" == *sg_memberString);
        QEXTFunction< int, bool, int, int > intBoundConstMemberBaseFunctorB(&memberBase, &MemberBase::intConstFunctionB3);
        CHECK(2 + 3 == intBoundConstMemberBaseFunctorB(true, 2, 3));
        CHECK(2 * 3 == intBoundConstMemberBaseFunctorB(false, 2, 3));
        QEXTFunction< double, bool, double, double > doubleBoundConstMemberBaseFunctorB(&memberBase, &MemberBase::doubleConstFunctionB3);
        CHECK(2.2 + 3.3 == doubleBoundConstMemberBaseFunctorB(true, 2.2, 3.3));
        CHECK(2.2 * 3.3 == doubleBoundConstMemberBaseFunctorB(false, 2.2, 3.3));
    }

    TEST(qextFunctionTest, testPolymorphismBoundConstFunctorWith3Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTFunction< void, int, int, int > voidBoundConstMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstFunction3);
        voidBoundConstMemberBaseFunctor(1, 2, 3);
        CHECK("Member::voidConstFunction3" == *sg_memberString);
        QEXTFunction< int, int, int, int > intBoundConstMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::intConstFunction3);
        CHECK(0 == intBoundConstMemberBaseFunctor(1, 2, 3));
        QEXTFunction< double, double, double, double > doubleBoundConstMemberBaseFunctor(
            dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstFunction3);
        CHECK(0 == doubleBoundConstMemberBaseFunctor(1.1, 2.2, 3.3));

        QEXTFunction< void, bool, int, int > voidBoundConstMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstFunctionB3);
        voidBoundConstMemberBaseFunctorB(true, 2, 3);
        CHECK("Member::voidConstFunctionB3" == *sg_memberString);
        QEXTFunction< int, bool, int, int > intBoundConstMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::intConstFunctionB3);
        CHECK(1 == intBoundConstMemberBaseFunctorB(true, 2, 3));
        CHECK(0 == intBoundConstMemberBaseFunctorB(false, 2, 3));
        QEXTFunction< double, bool, double, double > doubleBoundConstMemberBaseFunctorB(
            dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstFunctionB3);
        CHECK(1 == doubleBoundConstMemberBaseFunctorB(true, 2.2, 3.3));
        CHECK(0 == doubleBoundConstMemberBaseFunctorB(false, 2.2, 3.3));
    }

    TEST(qextFunctionTest, testBoundVolatileFunctorWith3Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTFunction< void, int, int, int > voidBoundVolatileMemberBaseFunctor(&memberBase, &MemberBase::voidVolatileFunction3);
        voidBoundVolatileMemberBaseFunctor(1, 2, 3);
        CHECK("MemberBase::voidVolatileFunction3" == *sg_memberString);
        QEXTFunction< int, int, int, int > intBoundVolatileMemberBaseFunctor(&memberBase, &MemberBase::intVolatileFunction3);
        CHECK(1 + 2 + 3 == intBoundVolatileMemberBaseFunctor(1, 2, 3));
        QEXTFunction< double, double, double, double > doubleBoundVolatileMemberBaseFunctor(&memberBase, &MemberBase::doubleVolatileFunction3);
        CHECK(1.1 + 2.2 + 3.3 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2, 3.3));

        QEXTFunction< void, bool, int, int > voidBoundVolatileMemberBaseFunctorB(&memberBase, &MemberBase::voidVolatileFunctionB3);
        voidBoundVolatileMemberBaseFunctorB(true, 2, 3);
        CHECK("MemberBase::voidVolatileFunctionB3" == *sg_memberString);
        QEXTFunction< int, bool, int, int > intBoundVolatileMemberBaseFunctorB(&memberBase, &MemberBase::intVolatileFunctionB3);
        CHECK(2 + 3 == intBoundVolatileMemberBaseFunctorB(true, 2, 3));
        CHECK(2 * 3 == intBoundVolatileMemberBaseFunctorB(false, 2, 3));
        QEXTFunction< double, bool, double, double > doubleBoundVolatileMemberBaseFunctorB(&memberBase, &MemberBase::doubleVolatileFunctionB3);
        CHECK(2.2 + 3.3 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2, 3.3));
        CHECK(2.2 * 3.3 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2, 3.3));
    }

    TEST(qextFunctionTest, testPolymorphismBoundVolatileFunctorWith3Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTFunction< void, int, int, int > voidBoundVolatileMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::voidVolatileFunction3);
        voidBoundVolatileMemberBaseFunctor(1, 2, 3);
        CHECK("Member::voidVolatileFunction3" == *sg_memberString);
        QEXTFunction< int, int, int, int > intBoundVolatileMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::intVolatileFunction3);
        CHECK(0 == intBoundVolatileMemberBaseFunctor(1, 2, 3));
        QEXTFunction< double, double, double, double > doubleBoundVolatileMemberBaseFunctor(
            dynamic_cast< MemberBase * >(&member), &MemberBase::doubleVolatileFunction3);
        CHECK(0 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2, 3.3));

        QEXTFunction< void, bool, int, int > voidBoundVolatileMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::voidVolatileFunctionB3);
        voidBoundVolatileMemberBaseFunctorB(true, 2, 3);
        CHECK("Member::voidVolatileFunctionB3" == *sg_memberString);
        QEXTFunction< int, bool, int, int > intBoundVolatileMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::intVolatileFunctionB3);
        CHECK(1 == intBoundVolatileMemberBaseFunctorB(true, 2, 3));
        CHECK(0 == intBoundVolatileMemberBaseFunctorB(false, 2, 3));
        QEXTFunction< double, bool, double, double > doubleBoundVolatileMemberBaseFunctorB(
            dynamic_cast< MemberBase * >(&member), &MemberBase::doubleVolatileFunctionB3);
        CHECK(1 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2, 3.3));
        CHECK(0 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2, 3.3));
    }

    TEST(qextFunctionTest, testBoundConstVolatileFunctorWith3Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTFunction< void, int, int, int > voidBoundConstVolatileMemberBaseFunctor(&memberBase, &MemberBase::voidConstVolatileFunction3);
        voidBoundConstVolatileMemberBaseFunctor(1, 2, 3);
        CHECK("MemberBase::voidConstVolatileFunction3" == *sg_memberString);
        QEXTFunction< int, int, int, int > intBoundConstVolatileMemberBaseFunctor(&memberBase, &MemberBase::intConstVolatileFunction3);
        CHECK(1 + 2 + 3 == intBoundConstVolatileMemberBaseFunctor(1, 2, 3));
        QEXTFunction< double, double, double, double > doubleBoundConstVolatileMemberBaseFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction3);
        CHECK(1.1 + 2.2 + 3.3 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2, 3.3));

        QEXTFunction< void, bool, int, int > voidBoundConstVolatileMemberBaseFunctorB(&memberBase, &MemberBase::voidConstVolatileFunctionB3);
        voidBoundConstVolatileMemberBaseFunctorB(true, 2, 3);
        CHECK("MemberBase::voidConstVolatileFunctionB3" == *sg_memberString);
        QEXTFunction< int, bool, int, int > intBoundConstVolatileMemberBaseFunctorB(&memberBase, &MemberBase::intConstVolatileFunctionB3);
        CHECK(2 + 3 == intBoundConstVolatileMemberBaseFunctorB(true, 2, 3));
        CHECK(2 * 3 == intBoundConstVolatileMemberBaseFunctorB(false, 2, 3));
        QEXTFunction< double, bool, double, double > doubleBoundConstVolatileMemberBaseFunctorB(&memberBase, &MemberBase::doubleConstVolatileFunctionB3);
        CHECK(2.2 + 3.3 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2, 3.3));
        CHECK(2.2 * 3.3 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2, 3.3));
    }

    TEST(qextFunctionTest, testPolymorphismBoundConstVolatileFunctorWith3Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTFunction< void, int, int, int > voidBoundConstVolatileMemberBaseFunctor(
            dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstVolatileFunction3);
        voidBoundConstVolatileMemberBaseFunctor(1, 2, 3);
        CHECK("Member::voidConstVolatileFunction3" == *sg_memberString);
        QEXTFunction< int, int, int, int > intBoundConstVolatileMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::intConstVolatileFunction3);
        CHECK(0 == intBoundConstVolatileMemberBaseFunctor(1, 2, 3));
        QEXTFunction< double, double, double, double > doubleBoundConstVolatileMemberBaseFunctor(
            dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstVolatileFunction3);
        CHECK(0 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2, 3.3));

        QEXTFunction< void, bool, int, int > voidBoundConstVolatileMemberBaseFunctorB(
            dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstVolatileFunctionB3);
        voidBoundConstVolatileMemberBaseFunctorB(true, 2, 3);
        CHECK("Member::voidConstVolatileFunctionB3" == *sg_memberString);
        QEXTFunction< int, bool, int, int > intBoundConstVolatileMemberBaseFunctorB(
            dynamic_cast< MemberBase * >(&member), &MemberBase::intConstVolatileFunctionB3);
        CHECK(1 == intBoundConstVolatileMemberBaseFunctorB(true, 2, 3));
        CHECK(0 == intBoundConstVolatileMemberBaseFunctorB(false, 2, 3));
        QEXTFunction< double, bool, double, double > doubleBoundConstVolatileMemberBaseFunctorB(
            dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstVolatileFunctionB3);
        CHECK(1 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2, 3.3));
        CHECK(0 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2, 3.3));
    }

    TEST(qextFunctionTest, testBoundFunctorWith4Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTFunction< void, int, int, int, int > voidBoundMemberBaseFunctor(&memberBase, &MemberBase::voidFunction4);
        voidBoundMemberBaseFunctor(1, 2, 3, 4);
        CHECK("MemberBase::voidFunction4" == *sg_memberString);
        QEXTFunction< int, int, int, int, int > intBoundMemberBaseFunctor(&memberBase, &MemberBase::intFunction4);
        CHECK(1 + 2 + 3 + 4 == intBoundMemberBaseFunctor(1, 2, 3, 4));
        QEXTFunction< double, double, double, double, double > doubleBoundMemberBaseFunctor(&memberBase, &MemberBase::doubleFunction4);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 == doubleBoundMemberBaseFunctor(1.1, 2.2, 3.3, 4.4));

        QEXTFunction< void, bool, int, int, int > voidBoundMemberBaseFunctorB(&memberBase, &MemberBase::voidFunctionB4);
        voidBoundMemberBaseFunctorB(true, 2, 3, 4);
        CHECK("MemberBase::voidFunctionB4" == *sg_memberString);
        QEXTFunction< int, bool, int, int, int > intBoundMemberBaseFunctorB(&memberBase, &MemberBase::intFunctionB4);
        CHECK(2 + 3 + 4 == intBoundMemberBaseFunctorB(true, 2, 3, 4));
        CHECK(2 * 3 * 4 == intBoundMemberBaseFunctorB(false, 2, 3, 4));
        QEXTFunction< double, bool, double, double, double > doubleBoundMemberBaseFunctorB(&memberBase, &MemberBase::doubleFunctionB4);
        CHECK(2.2 + 3.3 + 4.4 == doubleBoundMemberBaseFunctorB(true, 2.2, 3.3, 4.4));
        CHECK(2.2 * 3.3 * 4.4 == doubleBoundMemberBaseFunctorB(false, 2.2, 3.3, 4.4));
    }

    TEST(qextFunctionTest, testPolymorphismBoundFunctorWith4Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTFunction< void, int, int, int, int > voidBoundMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::voidFunction4);
        voidBoundMemberBaseFunctor(1, 2, 3, 4);
        CHECK("Member::voidFunction4" == *sg_memberString);
        QEXTFunction< int, int, int, int, int > intBoundMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::intFunction4);
        CHECK(0 == intBoundMemberBaseFunctor(1, 2, 3, 4));
        QEXTFunction< double, double, double, double, double > doubleBoundMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::doubleFunction4);
        CHECK(0 == doubleBoundMemberBaseFunctor(1.1, 2.2, 3.3, 4.4));

        QEXTFunction< void, bool, int, int, int > voidBoundMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::voidFunctionB4);
        voidBoundMemberBaseFunctorB(true, 2, 3, 4);
        CHECK("Member::voidFunctionB4" == *sg_memberString);
        QEXTFunction< int, bool, int, int, int > intBoundMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::intFunctionB4);
        CHECK(1 == intBoundMemberBaseFunctorB(true, 2, 3, 4));
        CHECK(0 == intBoundMemberBaseFunctorB(false, 2, 3, 4));
        QEXTFunction< double, bool, double, double, double > doubleBoundMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::doubleFunctionB4);
        CHECK(1 == doubleBoundMemberBaseFunctorB(true, 2.2, 3.3, 4.4));
        CHECK(0 == doubleBoundMemberBaseFunctorB(false, 2.2, 3.3, 4.4));
    }

    TEST(qextFunctionTest, testBoundConstFunctorWith4Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTFunction< void, int, int, int, int > voidBoundConstMemberBaseFunctor(&memberBase, &MemberBase::voidConstFunction4);
        voidBoundConstMemberBaseFunctor(1, 2, 3, 4);
        CHECK("MemberBase::voidConstFunction4" == *sg_memberString);
        QEXTFunction< int, int, int, int, int > intBoundConstMemberBaseFunctor(&memberBase, &MemberBase::intConstFunction4);
        CHECK(1 + 2 + 3 + 4 == intBoundConstMemberBaseFunctor(1, 2, 3, 4));
        QEXTFunction< double, double, double, double, double > doubleBoundConstMemberBaseFunctor(&memberBase, &MemberBase::doubleConstFunction4);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 == doubleBoundConstMemberBaseFunctor(1.1, 2.2, 3.3, 4.4));

        QEXTFunction< void, bool, int, int, int > voidBoundConstMemberBaseFunctorB(&memberBase, &MemberBase::voidConstFunctionB4);
        voidBoundConstMemberBaseFunctorB(true, 2, 3, 4);
        CHECK("MemberBase::voidConstFunctionB4" == *sg_memberString);
        QEXTFunction< int, bool, int, int, int > intBoundConstMemberBaseFunctorB(&memberBase, &MemberBase::intConstFunctionB4);
        CHECK(2 + 3 + 4 == intBoundConstMemberBaseFunctorB(true, 2, 3, 4));
        CHECK(2 * 3 * 4 == intBoundConstMemberBaseFunctorB(false, 2, 3, 4));
        QEXTFunction< double, bool, double, double, double > doubleBoundConstMemberBaseFunctorB(&memberBase, &MemberBase::doubleConstFunctionB4);
        CHECK(2.2 + 3.3 + 4.4 == doubleBoundConstMemberBaseFunctorB(true, 2.2, 3.3, 4.4));
        CHECK(2.2 * 3.3 * 4.4 == doubleBoundConstMemberBaseFunctorB(false, 2.2, 3.3, 4.4));
    }

    TEST(qextFunctionTest, testPolymorphismBoundConstFunctorWith4Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTFunction< void, int, int, int, int > voidBoundConstMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstFunction4);
        voidBoundConstMemberBaseFunctor(1, 2, 3, 4);
        CHECK("Member::voidConstFunction4" == *sg_memberString);
        QEXTFunction< int, int, int, int, int > intBoundConstMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::intConstFunction4);
        CHECK(0 == intBoundConstMemberBaseFunctor(1, 2, 3, 4));
        QEXTFunction< double, double, double, double, double > doubleBoundConstMemberBaseFunctor(
            dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstFunction4);
        CHECK(0 == doubleBoundConstMemberBaseFunctor(1.1, 2.2, 3.3, 4.4));

        QEXTFunction< void, bool, int, int, int > voidBoundConstMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstFunctionB4);
        voidBoundConstMemberBaseFunctorB(true, 2, 3, 4);
        CHECK("Member::voidConstFunctionB4" == *sg_memberString);
        QEXTFunction< int, bool, int, int, int > intBoundConstMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::intConstFunctionB4);
        CHECK(1 == intBoundConstMemberBaseFunctorB(true, 2, 3, 4));
        CHECK(0 == intBoundConstMemberBaseFunctorB(false, 2, 3, 4));
        QEXTFunction< double, bool, double, double, double > doubleBoundConstMemberBaseFunctorB(
            dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstFunctionB4);
        CHECK(1 == doubleBoundConstMemberBaseFunctorB(true, 2.2, 3.3, 4.4));
        CHECK(0 == doubleBoundConstMemberBaseFunctorB(false, 2.2, 3.3, 4.4));
    }

    TEST(qextFunctionTest, testBoundVolatileFunctorWith4Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTFunction< void, int, int, int, int > voidBoundVolatileMemberBaseFunctor(&memberBase, &MemberBase::voidVolatileFunction4);
        voidBoundVolatileMemberBaseFunctor(1, 2, 3, 4);
        CHECK("MemberBase::voidVolatileFunction4" == *sg_memberString);
        QEXTFunction< int, int, int, int, int > intBoundVolatileMemberBaseFunctor(&memberBase, &MemberBase::intVolatileFunction4);
        CHECK(1 + 2 + 3 + 4 == intBoundVolatileMemberBaseFunctor(1, 2, 3, 4));
        QEXTFunction< double, double, double, double, double > doubleBoundVolatileMemberBaseFunctor(&memberBase, &MemberBase::doubleVolatileFunction4);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4));

        QEXTFunction< void, bool, int, int, int > voidBoundVolatileMemberBaseFunctorB(&memberBase, &MemberBase::voidVolatileFunctionB4);
        voidBoundVolatileMemberBaseFunctorB(true, 2, 3, 4);
        CHECK("MemberBase::voidVolatileFunctionB4" == *sg_memberString);
        QEXTFunction< int, bool, int, int, int > intBoundVolatileMemberBaseFunctorB(&memberBase, &MemberBase::intVolatileFunctionB4);
        CHECK(2 + 3 + 4 == intBoundVolatileMemberBaseFunctorB(true, 2, 3, 4));
        CHECK(2 * 3 * 4 == intBoundVolatileMemberBaseFunctorB(false, 2, 3, 4));
        QEXTFunction< double, bool, double, double, double > doubleBoundVolatileMemberBaseFunctorB(&memberBase, &MemberBase::doubleVolatileFunctionB4);
        CHECK(2.2 + 3.3 + 4.4 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4));
        CHECK(2.2 * 3.3 * 4.4 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4));
    }

    TEST(qextFunctionTest, testPolymorphismBoundVolatileFunctorWith4Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTFunction< void, int, int, int, int > voidBoundVolatileMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::voidVolatileFunction4);
        voidBoundVolatileMemberBaseFunctor(1, 2, 3, 4);
        CHECK("Member::voidVolatileFunction4" == *sg_memberString);
        QEXTFunction< int, int, int, int, int > intBoundVolatileMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::intVolatileFunction4);
        CHECK(0 == intBoundVolatileMemberBaseFunctor(1, 2, 3, 4));
        QEXTFunction< double, double, double, double, double > doubleBoundVolatileMemberBaseFunctor(
            dynamic_cast< MemberBase * >(&member), &MemberBase::doubleVolatileFunction4);
        CHECK(0 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4));

        QEXTFunction< void, bool, int, int, int > voidBoundVolatileMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::voidVolatileFunctionB4);
        voidBoundVolatileMemberBaseFunctorB(true, 2, 3, 4);
        CHECK("Member::voidVolatileFunctionB4" == *sg_memberString);
        QEXTFunction< int, bool, int, int, int > intBoundVolatileMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::intVolatileFunctionB4);
        CHECK(1 == intBoundVolatileMemberBaseFunctorB(true, 2, 3, 4));
        CHECK(0 == intBoundVolatileMemberBaseFunctorB(false, 2, 3, 4));
        QEXTFunction< double, bool, double, double, double > doubleBoundVolatileMemberBaseFunctorB(
            dynamic_cast< MemberBase * >(&member), &MemberBase::doubleVolatileFunctionB4);
        CHECK(1 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4));
        CHECK(0 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4));
    }

    TEST(qextFunctionTest, testBoundConstVolatileFunctorWith4Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTFunction< void, int, int, int, int > voidBoundConstVolatileMemberBaseFunctor(&memberBase, &MemberBase::voidConstVolatileFunction4);
        voidBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4);
        CHECK("MemberBase::voidConstVolatileFunction4" == *sg_memberString);
        QEXTFunction< int, int, int, int, int > intBoundConstVolatileMemberBaseFunctor(&memberBase, &MemberBase::intConstVolatileFunction4);
        CHECK(1 + 2 + 3 + 4 == intBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4));
        QEXTFunction< double, double, double, double, double > doubleBoundConstVolatileMemberBaseFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction4);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4));

        QEXTFunction< void, bool, int, int, int > voidBoundConstVolatileMemberBaseFunctorB(&memberBase, &MemberBase::voidConstVolatileFunctionB4);
        voidBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4);
        CHECK("MemberBase::voidConstVolatileFunctionB4" == *sg_memberString);
        QEXTFunction< int, bool, int, int, int > intBoundConstVolatileMemberBaseFunctorB(&memberBase, &MemberBase::intConstVolatileFunctionB4);
        CHECK(2 + 3 + 4 == intBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4));
        CHECK(2 * 3 * 4 == intBoundConstVolatileMemberBaseFunctorB(false, 2, 3, 4));
        QEXTFunction< double, bool, double, double, double > doubleBoundConstVolatileMemberBaseFunctorB(&memberBase, &MemberBase::doubleConstVolatileFunctionB4);
        CHECK(2.2 + 3.3 + 4.4 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4));
        CHECK(2.2 * 3.3 * 4.4 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4));
    }

    TEST(qextFunctionTest, testPolymorphismBoundConstVolatileFunctorWith4Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTFunction< void, int, int, int, int > voidBoundConstVolatileMemberBaseFunctor(
            dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstVolatileFunction4);
        voidBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4);
        CHECK("Member::voidConstVolatileFunction4" == *sg_memberString);
        QEXTFunction< int, int, int, int, int > intBoundConstVolatileMemberBaseFunctor(
            dynamic_cast< MemberBase * >(&member), &MemberBase::intConstVolatileFunction4);
        CHECK(0 == intBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4));
        QEXTFunction< double, double, double, double, double > doubleBoundConstVolatileMemberBaseFunctor(
            dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstVolatileFunction4);
        CHECK(0 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4));

        QEXTFunction< void, bool, int, int, int > voidBoundConstVolatileMemberBaseFunctorB(
            dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstVolatileFunctionB4);
        voidBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4);
        CHECK("Member::voidConstVolatileFunctionB4" == *sg_memberString);
        QEXTFunction< int, bool, int, int, int > intBoundConstVolatileMemberBaseFunctorB(
            dynamic_cast< MemberBase * >(&member), &MemberBase::intConstVolatileFunctionB4);
        CHECK(1 == intBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4));
        CHECK(0 == intBoundConstVolatileMemberBaseFunctorB(false, 2, 3, 4));
        QEXTFunction< double, bool, double, double, double > doubleBoundConstVolatileMemberBaseFunctorB(
            dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstVolatileFunctionB4);
        CHECK(1 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4));
        CHECK(0 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4));
    }

    TEST(qextFunctionTest, testBoundFunctorWith5Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTFunction< void, int, int, int, int, int > voidBoundMemberBaseFunctor(&memberBase, &MemberBase::voidFunction5);
        voidBoundMemberBaseFunctor(1, 2, 3, 4, 5);
        CHECK("MemberBase::voidFunction5" == *sg_memberString);
        QEXTFunction< int, int, int, int, int, int > intBoundMemberBaseFunctor(&memberBase, &MemberBase::intFunction5);
        CHECK(1 + 2 + 3 + 4 + 5 == intBoundMemberBaseFunctor(1, 2, 3, 4, 5));
        QEXTFunction< double, double, double, double, double, double > doubleBoundMemberBaseFunctor(&memberBase, &MemberBase::doubleFunction5);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleBoundMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5));

        QEXTFunction< void, bool, int, int, int, int > voidBoundMemberBaseFunctorB(&memberBase, &MemberBase::voidFunctionB5);
        voidBoundMemberBaseFunctorB(true, 2, 3, 4, 5);
        CHECK("MemberBase::voidFunctionB5" == *sg_memberString);
        QEXTFunction< int, bool, int, int, int, int > intBoundMemberBaseFunctorB(&memberBase, &MemberBase::intFunctionB5);
        CHECK(2 + 3 + 4 + 5 == intBoundMemberBaseFunctorB(true, 2, 3, 4, 5));
        CHECK(2 * 3 * 4 * 5 == intBoundMemberBaseFunctorB(false, 2, 3, 4, 5));
        QEXTFunction< double, bool, double, double, double, double > doubleBoundMemberBaseFunctorB(&memberBase, &MemberBase::doubleFunctionB5);
        CHECK(2.2 + 3.3 + 4.4 + 5.5 == doubleBoundMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5));
        CHECK(2.2 * 3.3 * 4.4 * 5.5 == doubleBoundMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5));
    }

    TEST(qextFunctionTest, testPolymorphismBoundFunctorWith5Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTFunction< void, int, int, int, int, int > voidBoundMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::voidFunction5);
        voidBoundMemberBaseFunctor(1, 2, 3, 4, 5);
        CHECK("Member::voidFunction5" == *sg_memberString);
        QEXTFunction< int, int, int, int, int, int > intBoundMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::intFunction5);
        CHECK(0 == intBoundMemberBaseFunctor(1, 2, 3, 4, 5));
        QEXTFunction< double, double, double, double, double, double > doubleBoundMemberBaseFunctor(
            dynamic_cast< MemberBase * >(&member), &MemberBase::doubleFunction5);
        CHECK(0 == doubleBoundMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5));

        QEXTFunction< void, bool, int, int, int, int > voidBoundMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::voidFunctionB5);
        voidBoundMemberBaseFunctorB(true, 2, 3, 4, 5);
        CHECK("Member::voidFunctionB5" == *sg_memberString);
        QEXTFunction< int, bool, int, int, int, int > intBoundMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::intFunctionB5);
        CHECK(1 == intBoundMemberBaseFunctorB(true, 2, 3, 4, 5));
        CHECK(0 == intBoundMemberBaseFunctorB(false, 2, 3, 4, 5));
        QEXTFunction< double, bool, double, double, double, double > doubleBoundMemberBaseFunctorB(
            dynamic_cast< MemberBase * >(&member), &MemberBase::doubleFunctionB5);
        CHECK(1 == doubleBoundMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5));
        CHECK(0 == doubleBoundMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5));
    }

    TEST(qextFunctionTest, testBoundConstFunctorWith5Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTFunction< void, int, int, int, int, int > voidBoundConstMemberBaseFunctor(&memberBase, &MemberBase::voidConstFunction5);
        voidBoundConstMemberBaseFunctor(1, 2, 3, 4, 5);
        CHECK("MemberBase::voidConstFunction5" == *sg_memberString);
        QEXTFunction< int, int, int, int, int, int > intBoundConstMemberBaseFunctor(&memberBase, &MemberBase::intConstFunction5);
        CHECK(1 + 2 + 3 + 4 + 5 == intBoundConstMemberBaseFunctor(1, 2, 3, 4, 5));
        QEXTFunction< double, double, double, double, double, double > doubleBoundConstMemberBaseFunctor(&memberBase, &MemberBase::doubleConstFunction5);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleBoundConstMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5));

        QEXTFunction< void, bool, int, int, int, int > voidBoundConstMemberBaseFunctorB(&memberBase, &MemberBase::voidConstFunctionB5);
        voidBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5);
        CHECK("MemberBase::voidConstFunctionB5" == *sg_memberString);
        QEXTFunction< int, bool, int, int, int, int > intBoundConstMemberBaseFunctorB(&memberBase, &MemberBase::intConstFunctionB5);
        CHECK(2 + 3 + 4 + 5 == intBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5));
        CHECK(2 * 3 * 4 * 5 == intBoundConstMemberBaseFunctorB(false, 2, 3, 4, 5));
        QEXTFunction< double, bool, double, double, double, double > doubleBoundConstMemberBaseFunctorB(&memberBase, &MemberBase::doubleConstFunctionB5);
        CHECK(2.2 + 3.3 + 4.4 + 5.5 == doubleBoundConstMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5));
        CHECK(2.2 * 3.3 * 4.4 * 5.5 == doubleBoundConstMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5));
    }

    TEST(qextFunctionTest, testPolymorphismBoundConstFunctorWith5Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTFunction< void, int, int, int, int, int > voidBoundConstMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstFunction5);
        voidBoundConstMemberBaseFunctor(1, 2, 3, 4, 5);
        CHECK("Member::voidConstFunction5" == *sg_memberString);
        QEXTFunction< int, int, int, int, int, int > intBoundConstMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::intConstFunction5);
        CHECK(0 == intBoundConstMemberBaseFunctor(1, 2, 3, 4, 5));
        QEXTFunction< double, double, double, double, double, double > doubleBoundConstMemberBaseFunctor(
            dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstFunction5);
        CHECK(0 == doubleBoundConstMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5));

        QEXTFunction< void, bool, int, int, int, int > voidBoundConstMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstFunctionB5);
        voidBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5);
        CHECK("Member::voidConstFunctionB5" == *sg_memberString);
        QEXTFunction< int, bool, int, int, int, int > intBoundConstMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::intConstFunctionB5);
        CHECK(1 == intBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5));
        CHECK(0 == intBoundConstMemberBaseFunctorB(false, 2, 3, 4, 5));
        QEXTFunction< double, bool, double, double, double, double > doubleBoundConstMemberBaseFunctorB(
            dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstFunctionB5);
        CHECK(1 == doubleBoundConstMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5));
        CHECK(0 == doubleBoundConstMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5));
    }

    TEST(qextFunctionTest, testBoundVolatileFunctorWith5Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTFunction< void, int, int, int, int, int > voidBoundVolatileMemberBaseFunctor(&memberBase, &MemberBase::voidVolatileFunction5);
        voidBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5);
        CHECK("MemberBase::voidVolatileFunction5" == *sg_memberString);
        QEXTFunction< int, int, int, int, int, int > intBoundVolatileMemberBaseFunctor(&memberBase, &MemberBase::intVolatileFunction5);
        CHECK(1 + 2 + 3 + 4 + 5 == intBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5));
        QEXTFunction< double, double, double, double, double, double > doubleBoundVolatileMemberBaseFunctor(&memberBase, &MemberBase::doubleVolatileFunction5);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5));

        QEXTFunction< void, bool, int, int, int, int > voidBoundVolatileMemberBaseFunctorB(&memberBase, &MemberBase::voidVolatileFunctionB5);
        voidBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5);
        CHECK("MemberBase::voidVolatileFunctionB5" == *sg_memberString);
        QEXTFunction< int, bool, int, int, int, int > intBoundVolatileMemberBaseFunctorB(&memberBase, &MemberBase::intVolatileFunctionB5);
        CHECK(2 + 3 + 4 + 5 == intBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5));
        CHECK(2 * 3 * 4 * 5 == intBoundVolatileMemberBaseFunctorB(false, 2, 3, 4, 5));
        QEXTFunction< double, bool, double, double, double, double > doubleBoundVolatileMemberBaseFunctorB(&memberBase, &MemberBase::doubleVolatileFunctionB5);
        CHECK(2.2 + 3.3 + 4.4 + 5.5 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5));
        CHECK(2.2 * 3.3 * 4.4 * 5.5 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5));
    }

    TEST(qextFunctionTest, testPolymorphismBoundVolatileFunctorWith5Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTFunction< void, int, int, int, int, int > voidBoundVolatileMemberBaseFunctor(
            dynamic_cast< MemberBase * >(&member), &MemberBase::voidVolatileFunction5);
        voidBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5);
        CHECK("Member::voidVolatileFunction5" == *sg_memberString);
        QEXTFunction< int, int, int, int, int, int > intBoundVolatileMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::intVolatileFunction5);
        CHECK(0 == intBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5));
        QEXTFunction< double, double, double, double, double, double > doubleBoundVolatileMemberBaseFunctor(
            dynamic_cast< MemberBase * >(&member), &MemberBase::doubleVolatileFunction5);
        CHECK(0 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5));

        QEXTFunction< void, bool, int, int, int, int > voidBoundVolatileMemberBaseFunctorB(
            dynamic_cast< MemberBase * >(&member), &MemberBase::voidVolatileFunctionB5);
        voidBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5);
        CHECK("Member::voidVolatileFunctionB5" == *sg_memberString);
        QEXTFunction< int, bool, int, int, int, int > intBoundVolatileMemberBaseFunctorB(
            dynamic_cast< MemberBase * >(&member), &MemberBase::intVolatileFunctionB5);
        CHECK(1 == intBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5));
        CHECK(0 == intBoundVolatileMemberBaseFunctorB(false, 2, 3, 4, 5));
        QEXTFunction< double, bool, double, double, double, double > doubleBoundVolatileMemberBaseFunctorB(
            dynamic_cast< MemberBase * >(&member), &MemberBase::doubleVolatileFunctionB5);
        CHECK(1 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5));
        CHECK(0 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5));
    }

    TEST(qextFunctionTest, testBoundConstVolatileFunctorWith5Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTFunction< void, int, int, int, int, int > voidBoundConstVolatileMemberBaseFunctor(&memberBase, &MemberBase::voidConstVolatileFunction5);
        voidBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5);
        CHECK("MemberBase::voidConstVolatileFunction5" == *sg_memberString);
        QEXTFunction< int, int, int, int, int, int > intBoundConstVolatileMemberBaseFunctor(&memberBase, &MemberBase::intConstVolatileFunction5);
        CHECK(1 + 2 + 3 + 4 + 5 == intBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5));
        QEXTFunction< double, double, double, double, double, double > doubleBoundConstVolatileMemberBaseFunctor(
            &memberBase, &MemberBase::doubleConstVolatileFunction5);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5));

        QEXTFunction< void, bool, int, int, int, int > voidBoundConstVolatileMemberBaseFunctorB(&memberBase, &MemberBase::voidConstVolatileFunctionB5);
        voidBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5);
        CHECK("MemberBase::voidConstVolatileFunctionB5" == *sg_memberString);
        QEXTFunction< int, bool, int, int, int, int > intBoundConstVolatileMemberBaseFunctorB(&memberBase, &MemberBase::intConstVolatileFunctionB5);
        CHECK(2 + 3 + 4 + 5 == intBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5));
        CHECK(2 * 3 * 4 * 5 == intBoundConstVolatileMemberBaseFunctorB(false, 2, 3, 4, 5));
        QEXTFunction< double, bool, double, double, double, double > doubleBoundConstVolatileMemberBaseFunctorB(
            &memberBase, &MemberBase::doubleConstVolatileFunctionB5);
        CHECK(2.2 + 3.3 + 4.4 + 5.5 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5));
        CHECK(2.2 * 3.3 * 4.4 * 5.5 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5));
    }

    TEST(qextFunctionTest, testPolymorphismBoundConstVolatileFunctorWith5Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTFunction< void, int, int, int, int, int > voidBoundConstVolatileMemberBaseFunctor(
            dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstVolatileFunction5);
        voidBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5);
        CHECK("Member::voidConstVolatileFunction5" == *sg_memberString);
        QEXTFunction< int, int, int, int, int, int > intBoundConstVolatileMemberBaseFunctor(
            dynamic_cast< MemberBase * >(&member), &MemberBase::intConstVolatileFunction5);
        CHECK(0 == intBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5));
        QEXTFunction< double, double, double, double, double, double > doubleBoundConstVolatileMemberBaseFunctor(
            dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstVolatileFunction5);
        CHECK(0 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5));

        QEXTFunction< void, bool, int, int, int, int > voidBoundConstVolatileMemberBaseFunctorB(
            dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstVolatileFunctionB5);
        voidBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5);
        CHECK("Member::voidConstVolatileFunctionB5" == *sg_memberString);
        QEXTFunction< int, bool, int, int, int, int > intBoundConstVolatileMemberBaseFunctorB(
            dynamic_cast< MemberBase * >(&member), &MemberBase::intConstVolatileFunctionB5);
        CHECK(1 == intBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5));
        CHECK(0 == intBoundConstVolatileMemberBaseFunctorB(false, 2, 3, 4, 5));
        QEXTFunction< double, bool, double, double, double, double > doubleBoundConstVolatileMemberBaseFunctorB(
            dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstVolatileFunctionB5);
        CHECK(1 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5));
        CHECK(0 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5));
    }

    TEST(qextFunctionTest, testBoundFunctorWith6Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTFunction< void, int, int, int, int, int, int > voidBoundMemberBaseFunctor(&memberBase, &MemberBase::voidFunction6);
        voidBoundMemberBaseFunctor(1, 2, 3, 4, 5, 6);
        CHECK("MemberBase::voidFunction6" == *sg_memberString);
        QEXTFunction< int, int, int, int, int, int, int > intBoundMemberBaseFunctor(&memberBase, &MemberBase::intFunction6);
        CHECK(1 + 2 + 3 + 4 + 5 + 6 == intBoundMemberBaseFunctor(1, 2, 3, 4, 5, 6));
        QEXTFunction< double, double, double, double, double, double, double > doubleBoundMemberBaseFunctor(&memberBase, &MemberBase::doubleFunction6);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

        QEXTFunction< void, bool, int, int, int, int, int > voidBoundMemberBaseFunctorB(&memberBase, &MemberBase::voidFunctionB6);
        voidBoundMemberBaseFunctorB(true, 2, 3, 4, 5, 6);
        CHECK("MemberBase::voidFunctionB6" == *sg_memberString);
        QEXTFunction< int, bool, int, int, int, int, int > intBoundMemberBaseFunctorB(&memberBase, &MemberBase::intFunctionB6);
        CHECK(2 + 3 + 4 + 5 + 6 == intBoundMemberBaseFunctorB(true, 2, 3, 4, 5, 6));
        CHECK(2 * 3 * 4 * 5 * 6 == intBoundMemberBaseFunctorB(false, 2, 3, 4, 5, 6));
        QEXTFunction< double, bool, double, double, double, double, double > doubleBoundMemberBaseFunctorB(&memberBase, &MemberBase::doubleFunctionB6);
        CHECK(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6));
        CHECK(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleBoundMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6));
    }

    TEST(qextFunctionTest, testPolymorphismBoundFunctorWith6Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTFunction< void, int, int, int, int, int, int > voidBoundMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::voidFunction6);
        voidBoundMemberBaseFunctor(1, 2, 3, 4, 5, 6);
        CHECK("Member::voidFunction6" == *sg_memberString);
        QEXTFunction< int, int, int, int, int, int, int > intBoundMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::intFunction6);
        CHECK(0 == intBoundMemberBaseFunctor(1, 2, 3, 4, 5, 6));
        QEXTFunction< double, double, double, double, double, double, double > doubleBoundMemberBaseFunctor(
            dynamic_cast< MemberBase * >(&member), &MemberBase::doubleFunction6);
        CHECK(0 == doubleBoundMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

        QEXTFunction< void, bool, int, int, int, int, int > voidBoundMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::voidFunctionB6);
        voidBoundMemberBaseFunctorB(true, 2, 3, 4, 5, 6);
        CHECK("Member::voidFunctionB6" == *sg_memberString);
        QEXTFunction< int, bool, int, int, int, int, int > intBoundMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::intFunctionB6);
        CHECK(1 == intBoundMemberBaseFunctorB(true, 2, 3, 4, 5, 6));
        CHECK(0 == intBoundMemberBaseFunctorB(false, 2, 3, 4, 5, 6));
        QEXTFunction< double, bool, double, double, double, double, double > doubleBoundMemberBaseFunctorB(
            dynamic_cast< MemberBase * >(&member), &MemberBase::doubleFunctionB6);
        CHECK(1 == doubleBoundMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6));
        CHECK(0 == doubleBoundMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6));
    }

    TEST(qextFunctionTest, testBoundConstFunctorWith6Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTFunction< void, int, int, int, int, int, int > voidBoundConstMemberBaseFunctor(&memberBase, &MemberBase::voidConstFunction6);
        voidBoundConstMemberBaseFunctor(1, 2, 3, 4, 5, 6);
        CHECK("MemberBase::voidConstFunction6" == *sg_memberString);
        QEXTFunction< int, int, int, int, int, int, int > intBoundConstMemberBaseFunctor(&memberBase, &MemberBase::intConstFunction6);
        CHECK(1 + 2 + 3 + 4 + 5 + 6 == intBoundConstMemberBaseFunctor(1, 2, 3, 4, 5, 6));
        QEXTFunction< double, double, double, double, double, double, double > doubleBoundConstMemberBaseFunctor(&memberBase, &MemberBase::doubleConstFunction6);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundConstMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

        QEXTFunction< void, bool, int, int, int, int, int > voidBoundConstMemberBaseFunctorB(&memberBase, &MemberBase::voidConstFunctionB6);
        voidBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5, 6);
        CHECK("MemberBase::voidConstFunctionB6" == *sg_memberString);
        QEXTFunction< int, bool, int, int, int, int, int > intBoundConstMemberBaseFunctorB(&memberBase, &MemberBase::intConstFunctionB6);
        CHECK(2 + 3 + 4 + 5 + 6 == intBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5, 6));
        CHECK(2 * 3 * 4 * 5 * 6 == intBoundConstMemberBaseFunctorB(false, 2, 3, 4, 5, 6));
        QEXTFunction< double, bool, double, double, double, double, double > doubleBoundConstMemberBaseFunctorB(&memberBase, &MemberBase::doubleConstFunctionB6);
        CHECK(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundConstMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6));
        CHECK(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleBoundConstMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6));
    }

    TEST(qextFunctionTest, testPolymorphismBoundConstFunctorWith6Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTFunction< void, int, int, int, int, int, int > voidBoundConstMemberBaseFunctor(
            dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstFunction6);
        voidBoundConstMemberBaseFunctor(1, 2, 3, 4, 5, 6);
        CHECK("Member::voidConstFunction6" == *sg_memberString);
        QEXTFunction< int, int, int, int, int, int, int > intBoundConstMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::intConstFunction6);
        CHECK(0 == intBoundConstMemberBaseFunctor(1, 2, 3, 4, 5, 6));
        QEXTFunction< double, double, double, double, double, double, double > doubleBoundConstMemberBaseFunctor(
            dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstFunction6);
        CHECK(0 == doubleBoundConstMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

        QEXTFunction< void, bool, int, int, int, int, int > voidBoundConstMemberBaseFunctorB(
            dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstFunctionB6);
        voidBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5, 6);
        CHECK("Member::voidConstFunctionB6" == *sg_memberString);
        QEXTFunction< int, bool, int, int, int, int, int > intBoundConstMemberBaseFunctorB(
            dynamic_cast< MemberBase * >(&member), &MemberBase::intConstFunctionB6);
        CHECK(1 == intBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5, 6));
        CHECK(0 == intBoundConstMemberBaseFunctorB(false, 2, 3, 4, 5, 6));
        QEXTFunction< double, bool, double, double, double, double, double > doubleBoundConstMemberBaseFunctorB(
            dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstFunctionB6);
        CHECK(1 == doubleBoundConstMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6));
        CHECK(0 == doubleBoundConstMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6));
    }

    TEST(qextFunctionTest, testBoundVolatileFunctorWith6Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTFunction< void, int, int, int, int, int, int > voidBoundVolatileMemberBaseFunctor(&memberBase, &MemberBase::voidVolatileFunction6);
        voidBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6);
        CHECK("MemberBase::voidVolatileFunction6" == *sg_memberString);
        QEXTFunction< int, int, int, int, int, int, int > intBoundVolatileMemberBaseFunctor(&memberBase, &MemberBase::intVolatileFunction6);
        CHECK(1 + 2 + 3 + 4 + 5 + 6 == intBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6));
        QEXTFunction< double, double, double, double, double, double, double > doubleBoundVolatileMemberBaseFunctor(
            &memberBase, &MemberBase::doubleVolatileFunction6);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

        QEXTFunction< void, bool, int, int, int, int, int > voidBoundVolatileMemberBaseFunctorB(&memberBase, &MemberBase::voidVolatileFunctionB6);
        voidBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6);
        CHECK("MemberBase::voidVolatileFunctionB6" == *sg_memberString);
        QEXTFunction< int, bool, int, int, int, int, int > intBoundVolatileMemberBaseFunctorB(&memberBase, &MemberBase::intVolatileFunctionB6);
        CHECK(2 + 3 + 4 + 5 + 6 == intBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6));
        CHECK(2 * 3 * 4 * 5 * 6 == intBoundVolatileMemberBaseFunctorB(false, 2, 3, 4, 5, 6));
        QEXTFunction< double, bool, double, double, double, double, double > doubleBoundVolatileMemberBaseFunctorB(
            &memberBase, &MemberBase::doubleVolatileFunctionB6);
        CHECK(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6));
        CHECK(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6));
    }

    TEST(qextFunctionTest, testPolymorphismBoundVolatileFunctorWith6Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTFunction< void, int, int, int, int, int, int > voidBoundVolatileMemberBaseFunctor(
            dynamic_cast< MemberBase * >(&member), &MemberBase::voidVolatileFunction6);
        voidBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6);
        CHECK("Member::voidVolatileFunction6" == *sg_memberString);
        QEXTFunction< int, int, int, int, int, int, int > intBoundVolatileMemberBaseFunctor(
            dynamic_cast< MemberBase * >(&member), &MemberBase::intVolatileFunction6);
        CHECK(0 == intBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6));
        QEXTFunction< double, double, double, double, double, double, double > doubleBoundVolatileMemberBaseFunctor(
            dynamic_cast< MemberBase * >(&member), &MemberBase::doubleVolatileFunction6);
        CHECK(0 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

        QEXTFunction< void, bool, int, int, int, int, int > voidBoundVolatileMemberBaseFunctorB(
            dynamic_cast< MemberBase * >(&member), &MemberBase::voidVolatileFunctionB6);
        voidBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6);
        CHECK("Member::voidVolatileFunctionB6" == *sg_memberString);
        QEXTFunction< int, bool, int, int, int, int, int > intBoundVolatileMemberBaseFunctorB(
            dynamic_cast< MemberBase * >(&member), &MemberBase::intVolatileFunctionB6);
        CHECK(1 == intBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6));
        CHECK(0 == intBoundVolatileMemberBaseFunctorB(false, 2, 3, 4, 5, 6));
        QEXTFunction< double, bool, double, double, double, double, double > doubleBoundVolatileMemberBaseFunctorB(
            dynamic_cast< MemberBase * >(&member), &MemberBase::doubleVolatileFunctionB6);
        CHECK(1 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6));
        CHECK(0 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6));
    }

    TEST(qextFunctionTest, testBoundConstVolatileFunctorWith6Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTFunction< void, int, int, int, int, int, int > voidBoundConstVolatileMemberBaseFunctor(&memberBase, &MemberBase::voidConstVolatileFunction6);
        voidBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6);
        CHECK("MemberBase::voidConstVolatileFunction6" == *sg_memberString);
        QEXTFunction< int, int, int, int, int, int, int > intBoundConstVolatileMemberBaseFunctor(&memberBase, &MemberBase::intConstVolatileFunction6);
        CHECK(1 + 2 + 3 + 4 + 5 + 6 == intBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6));
        QEXTFunction< double, double, double, double, double, double, double > doubleBoundConstVolatileMemberBaseFunctor(
            &memberBase, &MemberBase::doubleConstVolatileFunction6);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

        QEXTFunction< void, bool, int, int, int, int, int > voidBoundConstVolatileMemberBaseFunctorB(&memberBase, &MemberBase::voidConstVolatileFunctionB6);
        voidBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6);
        CHECK("MemberBase::voidConstVolatileFunctionB6" == *sg_memberString);
        QEXTFunction< int, bool, int, int, int, int, int > intBoundConstVolatileMemberBaseFunctorB(&memberBase, &MemberBase::intConstVolatileFunctionB6);
        CHECK(2 + 3 + 4 + 5 + 6 == intBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6));
        CHECK(2 * 3 * 4 * 5 * 6 == intBoundConstVolatileMemberBaseFunctorB(false, 2, 3, 4, 5, 6));
        QEXTFunction< double, bool, double, double, double, double, double > doubleBoundConstVolatileMemberBaseFunctorB(
            &memberBase, &MemberBase::doubleConstVolatileFunctionB6);
        CHECK(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6));
        CHECK(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6));
    }

    TEST(qextFunctionTest, testPolymorphismBoundConstVolatileFunctorWith6Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTFunction< void, int, int, int, int, int, int > voidBoundConstVolatileMemberBaseFunctor(
            dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstVolatileFunction6);
        voidBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6);
        CHECK("Member::voidConstVolatileFunction6" == *sg_memberString);
        QEXTFunction< int, int, int, int, int, int, int > intBoundConstVolatileMemberBaseFunctor(
            dynamic_cast< MemberBase * >(&member), &MemberBase::intConstVolatileFunction6);
        CHECK(0 == intBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6));
        QEXTFunction< double, double, double, double, double, double, double > doubleBoundConstVolatileMemberBaseFunctor(
            dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstVolatileFunction6);
        CHECK(0 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

        QEXTFunction< void, bool, int, int, int, int, int > voidBoundConstVolatileMemberBaseFunctorB(
            dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstVolatileFunctionB6);
        voidBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6);
        CHECK("Member::voidConstVolatileFunctionB6" == *sg_memberString);
        QEXTFunction< int, bool, int, int, int, int, int > intBoundConstVolatileMemberBaseFunctorB(
            dynamic_cast< MemberBase * >(&member), &MemberBase::intConstVolatileFunctionB6);
        CHECK(1 == intBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6));
        CHECK(0 == intBoundConstVolatileMemberBaseFunctorB(false, 2, 3, 4, 5, 6));
        QEXTFunction< double, bool, double, double, double, double, double > doubleBoundConstVolatileMemberBaseFunctorB(
            dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstVolatileFunctionB6);
        CHECK(1 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6));
        CHECK(0 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6));
    }

    TEST(qextFunctionTest, testBoundFunctorWith7Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTFunction< void, int, int, int, int, int, int, int > voidBoundMemberBaseFunctor(&memberBase, &MemberBase::voidFunction7);
        voidBoundMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7);
        CHECK("MemberBase::voidFunction7" == *sg_memberString);
        QEXTFunction< int, int, int, int, int, int, int, int > intBoundMemberBaseFunctor(&memberBase, &MemberBase::intFunction7);
        CHECK(1 + 2 + 3 + 4 + 5 + 6 + 7 == intBoundMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7));
        QEXTFunction< double, double, double, double, double, double, double, double > doubleBoundMemberBaseFunctor(&memberBase, &MemberBase::doubleFunction7);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

        QEXTFunction< void, bool, int, int, int, int, int, int > voidBoundMemberBaseFunctorB(&memberBase, &MemberBase::voidFunctionB7);
        voidBoundMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7);
        CHECK("MemberBase::voidFunctionB7" == *sg_memberString);
        QEXTFunction< int, bool, int, int, int, int, int, int > intBoundMemberBaseFunctorB(&memberBase, &MemberBase::intFunctionB7);
        CHECK(2 + 3 + 4 + 5 + 6 + 7 == intBoundMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7));
        CHECK(2 * 3 * 4 * 5 * 6 * 7 == intBoundMemberBaseFunctorB(false, 2, 3, 4, 5, 6, 7));
        QEXTFunction< double, bool, double, double, double, double, double, double > doubleBoundMemberBaseFunctorB(&memberBase, &MemberBase::doubleFunctionB7);
        CHECK(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
        CHECK(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleBoundMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    }

    TEST(qextFunctionTest, testPolymorphismBoundFunctorWith7Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTFunction< void, int, int, int, int, int, int, int > voidBoundMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::voidFunction7);
        voidBoundMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7);
        CHECK("Member::voidFunction7" == *sg_memberString);
        QEXTFunction< int, int, int, int, int, int, int, int > intBoundMemberBaseFunctor(dynamic_cast< MemberBase * >(&member), &MemberBase::intFunction7);
        CHECK(0 == intBoundMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7));
        QEXTFunction< double, double, double, double, double, double, double, double > doubleBoundMemberBaseFunctor(
            dynamic_cast< MemberBase * >(&member), &MemberBase::doubleFunction7);
        CHECK(0 == doubleBoundMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

        QEXTFunction< void, bool, int, int, int, int, int, int > voidBoundMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::voidFunctionB7);
        voidBoundMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7);
        CHECK("Member::voidFunctionB7" == *sg_memberString);
        QEXTFunction< int, bool, int, int, int, int, int, int > intBoundMemberBaseFunctorB(dynamic_cast< MemberBase * >(&member), &MemberBase::intFunctionB7);
        CHECK(1 == intBoundMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7));
        CHECK(0 == intBoundMemberBaseFunctorB(false, 2, 3, 4, 5, 6, 7));
        QEXTFunction< double, bool, double, double, double, double, double, double > doubleBoundMemberBaseFunctorB(
            dynamic_cast< MemberBase * >(&member), &MemberBase::doubleFunctionB7);
        CHECK(1 == doubleBoundMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
        CHECK(0 == doubleBoundMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    }

    TEST(qextFunctionTest, testBoundConstFunctorWith7Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTFunction< void, int, int, int, int, int, int, int > voidBoundConstMemberBaseFunctor(&memberBase, &MemberBase::voidConstFunction7);
        voidBoundConstMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7);
        CHECK("MemberBase::voidConstFunction7" == *sg_memberString);
        QEXTFunction< int, int, int, int, int, int, int, int > intBoundConstMemberBaseFunctor(&memberBase, &MemberBase::intConstFunction7);
        CHECK(1 + 2 + 3 + 4 + 5 + 6 + 7 == intBoundConstMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7));
        QEXTFunction< double, double, double, double, double, double, double, double > doubleBoundConstMemberBaseFunctor(
            &memberBase, &MemberBase::doubleConstFunction7);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundConstMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

        QEXTFunction< void, bool, int, int, int, int, int, int > voidBoundConstMemberBaseFunctorB(&memberBase, &MemberBase::voidConstFunctionB7);
        voidBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7);
        CHECK("MemberBase::voidConstFunctionB7" == *sg_memberString);
        QEXTFunction< int, bool, int, int, int, int, int, int > intBoundConstMemberBaseFunctorB(&memberBase, &MemberBase::intConstFunctionB7);
        CHECK(2 + 3 + 4 + 5 + 6 + 7 == intBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7));
        CHECK(2 * 3 * 4 * 5 * 6 * 7 == intBoundConstMemberBaseFunctorB(false, 2, 3, 4, 5, 6, 7));
        QEXTFunction< double, bool, double, double, double, double, double, double > doubleBoundConstMemberBaseFunctorB(
            &memberBase, &MemberBase::doubleConstFunctionB7);
        CHECK(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundConstMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
        CHECK(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleBoundConstMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    }

    TEST(qextFunctionTest, testPolymorphismBoundConstFunctorWith7Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTFunction< void, int, int, int, int, int, int, int > voidBoundConstMemberBaseFunctor(
            dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstFunction7);
        voidBoundConstMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7);
        CHECK("Member::voidConstFunction7" == *sg_memberString);
        QEXTFunction< int, int, int, int, int, int, int, int > intBoundConstMemberBaseFunctor(
            dynamic_cast< MemberBase * >(&member), &MemberBase::intConstFunction7);
        CHECK(0 == intBoundConstMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7));
        QEXTFunction< double, double, double, double, double, double, double, double > doubleBoundConstMemberBaseFunctor(
            dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstFunction7);
        CHECK(0 == doubleBoundConstMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

        QEXTFunction< void, bool, int, int, int, int, int, int > voidBoundConstMemberBaseFunctorB(
            dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstFunctionB7);
        voidBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7);
        CHECK("Member::voidConstFunctionB7" == *sg_memberString);
        QEXTFunction< int, bool, int, int, int, int, int, int > intBoundConstMemberBaseFunctorB(
            dynamic_cast< MemberBase * >(&member), &MemberBase::intConstFunctionB7);
        CHECK(1 == intBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7));
        CHECK(0 == intBoundConstMemberBaseFunctorB(false, 2, 3, 4, 5, 6, 7));
        QEXTFunction< double, bool, double, double, double, double, double, double > doubleBoundConstMemberBaseFunctorB(
            dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstFunctionB7);
        CHECK(1 == doubleBoundConstMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
        CHECK(0 == doubleBoundConstMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    }

    TEST(qextFunctionTest, testBoundVolatileFunctorWith7Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTFunction< void, int, int, int, int, int, int, int > voidBoundVolatileMemberBaseFunctor(&memberBase, &MemberBase::voidVolatileFunction7);
        voidBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7);
        CHECK("MemberBase::voidVolatileFunction7" == *sg_memberString);
        QEXTFunction< int, int, int, int, int, int, int, int > intBoundVolatileMemberBaseFunctor(&memberBase, &MemberBase::intVolatileFunction7);
        CHECK(1 + 2 + 3 + 4 + 5 + 6 + 7 == intBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7));
        QEXTFunction< double, double, double, double, double, double, double, double > doubleBoundVolatileMemberBaseFunctor(
            &memberBase, &MemberBase::doubleVolatileFunction7);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

        QEXTFunction< void, bool, int, int, int, int, int, int > voidBoundVolatileMemberBaseFunctorB(&memberBase, &MemberBase::voidVolatileFunctionB7);
        voidBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7);
        CHECK("MemberBase::voidVolatileFunctionB7" == *sg_memberString);
        QEXTFunction< int, bool, int, int, int, int, int, int > intBoundVolatileMemberBaseFunctorB(&memberBase, &MemberBase::intVolatileFunctionB7);
        CHECK(2 + 3 + 4 + 5 + 6 + 7 == intBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7));
        CHECK(2 * 3 * 4 * 5 * 6 * 7 == intBoundVolatileMemberBaseFunctorB(false, 2, 3, 4, 5, 6, 7));
        QEXTFunction< double, bool, double, double, double, double, double, double > doubleBoundVolatileMemberBaseFunctorB(
            &memberBase, &MemberBase::doubleVolatileFunctionB7);
        CHECK(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
        CHECK(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    }

    TEST(qextFunctionTest, testPolymorphismBoundVolatileFunctorWith7Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTFunction< void, int, int, int, int, int, int, int > voidBoundVolatileMemberBaseFunctor(
            dynamic_cast< MemberBase * >(&member), &MemberBase::voidVolatileFunction7);
        voidBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7);
        CHECK("Member::voidVolatileFunction7" == *sg_memberString);
        QEXTFunction< int, int, int, int, int, int, int, int > intBoundVolatileMemberBaseFunctor(
            dynamic_cast< MemberBase * >(&member), &MemberBase::intVolatileFunction7);
        CHECK(0 == intBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7));
        QEXTFunction< double, double, double, double, double, double, double, double > doubleBoundVolatileMemberBaseFunctor(
            dynamic_cast< MemberBase * >(&member), &MemberBase::doubleVolatileFunction7);
        CHECK(0 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

        QEXTFunction< void, bool, int, int, int, int, int, int > voidBoundVolatileMemberBaseFunctorB(
            dynamic_cast< MemberBase * >(&member), &MemberBase::voidVolatileFunctionB7);
        voidBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7);
        CHECK("Member::voidVolatileFunctionB7" == *sg_memberString);
        QEXTFunction< int, bool, int, int, int, int, int, int > intBoundVolatileMemberBaseFunctorB(
            dynamic_cast< MemberBase * >(&member), &MemberBase::intVolatileFunctionB7);
        CHECK(1 == intBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7));
        CHECK(0 == intBoundVolatileMemberBaseFunctorB(false, 2, 3, 4, 5, 6, 7));
        QEXTFunction< double, bool, double, double, double, double, double, double > doubleBoundVolatileMemberBaseFunctorB(
            dynamic_cast< MemberBase * >(&member), &MemberBase::doubleVolatileFunctionB7);
        CHECK(1 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
        CHECK(0 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    }

    TEST(qextFunctionTest, testBoundConstVolatileFunctorWith7Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTFunction< void, int, int, int, int, int, int, int > voidBoundConstVolatileMemberBaseFunctor(&memberBase, &MemberBase::voidConstVolatileFunction7);
        voidBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7);
        CHECK("MemberBase::voidConstVolatileFunction7" == *sg_memberString);
        QEXTFunction< int, int, int, int, int, int, int, int > intBoundConstVolatileMemberBaseFunctor(&memberBase, &MemberBase::intConstVolatileFunction7);
        CHECK(1 + 2 + 3 + 4 + 5 + 6 + 7 == intBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7));
        QEXTFunction< double, double, double, double, double, double, double, double > doubleBoundConstVolatileMemberBaseFunctor(
            &memberBase, &MemberBase::doubleConstVolatileFunction7);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

        QEXTFunction< void, bool, int, int, int, int, int, int > voidBoundConstVolatileMemberBaseFunctorB(&memberBase, &MemberBase::voidConstVolatileFunctionB7);
        voidBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7);
        CHECK("MemberBase::voidConstVolatileFunctionB7" == *sg_memberString);
        QEXTFunction< int, bool, int, int, int, int, int, int > intBoundConstVolatileMemberBaseFunctorB(&memberBase, &MemberBase::intConstVolatileFunctionB7);
        CHECK(2 + 3 + 4 + 5 + 6 + 7 == intBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7));
        CHECK(2 * 3 * 4 * 5 * 6 * 7 == intBoundConstVolatileMemberBaseFunctorB(false, 2, 3, 4, 5, 6, 7));
        QEXTFunction< double, bool, double, double, double, double, double, double > doubleBoundConstVolatileMemberBaseFunctorB(
            &memberBase, &MemberBase::doubleConstVolatileFunctionB7);
        CHECK(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
        CHECK(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    }

    TEST(qextFunctionTest, testPolymorphismBoundConstVolatileFunctorWith7Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTFunction< void, int, int, int, int, int, int, int > voidBoundConstVolatileMemberBaseFunctor(
            dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstVolatileFunction7);
        voidBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7);
        CHECK("Member::voidConstVolatileFunction7" == *sg_memberString);
        QEXTFunction< int, int, int, int, int, int, int, int > intBoundConstVolatileMemberBaseFunctor(
            dynamic_cast< MemberBase * >(&member), &MemberBase::intConstVolatileFunction7);
        CHECK(0 == intBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7));
        QEXTFunction< double, double, double, double, double, double, double, double > doubleBoundConstVolatileMemberBaseFunctor(
            dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstVolatileFunction7);
        CHECK(0 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

        QEXTFunction< void, bool, int, int, int, int, int, int > voidBoundConstVolatileMemberBaseFunctorB(
            dynamic_cast< MemberBase * >(&member), &MemberBase::voidConstVolatileFunctionB7);
        voidBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7);
        CHECK("Member::voidConstVolatileFunctionB7" == *sg_memberString);
        QEXTFunction< int, bool, int, int, int, int, int, int > intBoundConstVolatileMemberBaseFunctorB(
            dynamic_cast< MemberBase * >(&member), &MemberBase::intConstVolatileFunctionB7);
        CHECK(1 == intBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7));
        CHECK(0 == intBoundConstVolatileMemberBaseFunctorB(false, 2, 3, 4, 5, 6, 7));
        QEXTFunction< double, bool, double, double, double, double, double, double > doubleBoundConstVolatileMemberBaseFunctorB(
            dynamic_cast< MemberBase * >(&member), &MemberBase::doubleConstVolatileFunctionB7);
        CHECK(1 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
        CHECK(0 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    }

} // namespace qextFunctionTest

#endif // QEXTFUNCTIONTEST_H
