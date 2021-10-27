#ifndef QEXTMEMBERFUNCTORTEST_H
#define QEXTMEMBERFUNCTORTEST_H

#include <qextMemberFunctor.h>

#include "qextMember.h"

#include <iostream>

#include <CppUTest/TestHarness.h>

QEXT_USE_NAMESPACE

namespace qextMemberFunctorTest
{

    TEST_GROUP(qextMemberFunctorTest)
    {
    };


    TEST(qextMemberFunctorTest, testFunctorWith0Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTMemberFunctor<void, MemberBase> voidMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidFunction0);
        voidMemberBaseFunctor(&memberBase);
        CHECK("MemberBase::voidFunction0" == *sg_memberString);
        QEXTMemberFunctor<int, MemberBase> intMemberBaseFunctor = qextMemberFunctor(&MemberBase::intFunction0);
        intMemberBaseFunctor(&memberBase);
        CHECK("MemberBase::intFunction0" == *sg_memberString);
        QEXTMemberFunctor<double, MemberBase> doubleMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleFunction0);
        doubleMemberBaseFunctor(&memberBase);
        CHECK("MemberBase::doubleFunction0" == *sg_memberString);
    }

    TEST(qextMemberFunctorTest, testPolymorphismFunctorWith0Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTMemberFunctor<void, MemberBase> voidMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidFunction0);
        voidMemberBaseFunctor(&member);
        CHECK("Member::voidFunction0" == *sg_memberString);
        QEXTMemberFunctor<int, MemberBase> intMemberBaseFunctor = qextMemberFunctor(&MemberBase::intFunction0);
        intMemberBaseFunctor(&member);
        CHECK("Member::intFunction0" == *sg_memberString);
        QEXTMemberFunctor<double, MemberBase> doubleMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleFunction0);
        doubleMemberBaseFunctor(&member);
        CHECK("Member::doubleFunction0" == *sg_memberString);
    }

    TEST(qextMemberFunctorTest, testConstFunctorWith0Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTConstMemberFunctor<void, MemberBase> voidConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstFunction0);
        voidConstMemberBaseFunctor(&memberBase);
        CHECK("MemberBase::voidConstFunction0" == *sg_memberString);
        QEXTConstMemberFunctor<int, MemberBase> intConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstFunction0);
        intConstMemberBaseFunctor(&memberBase);
        CHECK("MemberBase::intConstFunction0" == *sg_memberString);
        QEXTConstMemberFunctor<double, MemberBase> doubleConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstFunction0);
        doubleConstMemberBaseFunctor(&memberBase);
        CHECK("MemberBase::doubleConstFunction0" == *sg_memberString);
    }

    TEST(qextMemberFunctorTest, testPolymorphismConstFunctorWith0Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTConstMemberFunctor<void, MemberBase> voidConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstFunction0);
        voidConstMemberBaseFunctor(&member);
        CHECK("Member::voidConstFunction0" == *sg_memberString);
        QEXTConstMemberFunctor<int, MemberBase> intConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstFunction0);
        intConstMemberBaseFunctor(&member);
        CHECK("Member::intConstFunction0" == *sg_memberString);
        QEXTConstMemberFunctor<double, MemberBase> doubleConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstFunction0);
        doubleConstMemberBaseFunctor(&member);
        CHECK("Member::doubleConstFunction0" == *sg_memberString);
    }

    TEST(qextMemberFunctorTest, testVolatileFunctorWith0Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTVolatileMemberFunctor<void, MemberBase> voidVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidVolatileFunction0);
        voidVolatileMemberBaseFunctor(&memberBase);
        CHECK("MemberBase::voidVolatileFunction0" == *sg_memberString);
        QEXTVolatileMemberFunctor<int, MemberBase> intVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intVolatileFunction0);
        intVolatileMemberBaseFunctor(&memberBase);
        CHECK("MemberBase::intVolatileFunction0" == *sg_memberString);
        QEXTVolatileMemberFunctor<double, MemberBase> doubleVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleVolatileFunction0);
        doubleVolatileMemberBaseFunctor(&memberBase);
        CHECK("MemberBase::doubleVolatileFunction0" == *sg_memberString);
    }

    TEST(qextMemberFunctorTest, testPolymorphismVolatileFunctorWith0Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTVolatileMemberFunctor<void, MemberBase> voidVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidVolatileFunction0);
        voidVolatileMemberBaseFunctor(&member);
        CHECK("Member::voidVolatileFunction0" == *sg_memberString);
        QEXTVolatileMemberFunctor<int, MemberBase> intVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intVolatileFunction0);
        intVolatileMemberBaseFunctor(&member);
        CHECK("Member::intVolatileFunction0" == *sg_memberString);
        QEXTVolatileMemberFunctor<double, MemberBase> doubleVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleVolatileFunction0);
        doubleVolatileMemberBaseFunctor(&member);
        CHECK("Member::doubleVolatileFunction0" == *sg_memberString);
    }

    TEST(qextMemberFunctorTest, testConstVolatileFunctorWith0Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTConstVolatileMemberFunctor<void, MemberBase> voidConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstVolatileFunction0);
        voidConstVolatileMemberBaseFunctor(&memberBase);
        CHECK("MemberBase::voidConstVolatileFunction0" == *sg_memberString);
        QEXTConstVolatileMemberFunctor<int, MemberBase> intConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstVolatileFunction0);
        intConstVolatileMemberBaseFunctor(&memberBase);
        CHECK("MemberBase::intConstVolatileFunction0" == *sg_memberString);
        QEXTConstVolatileMemberFunctor<double, MemberBase> doubleConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction0);
        doubleConstVolatileMemberBaseFunctor(&memberBase);
        CHECK("MemberBase::doubleConstVolatileFunction0" == *sg_memberString);
    }

    TEST(qextMemberFunctorTest, testPolymorphismConstVolatileFunctorWith0Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTConstVolatileMemberFunctor<void, MemberBase> voidConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstVolatileFunction0);
        voidConstVolatileMemberBaseFunctor(&member);
        CHECK("Member::voidConstVolatileFunction0" == *sg_memberString);
        QEXTConstVolatileMemberFunctor<int, MemberBase> intConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstVolatileFunction0);
        intConstVolatileMemberBaseFunctor(&member);
        CHECK("Member::intConstVolatileFunction0" == *sg_memberString);
        QEXTConstVolatileMemberFunctor<double, MemberBase> doubleConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction0);
        doubleConstVolatileMemberBaseFunctor(&member);
        CHECK("Member::doubleConstVolatileFunction0" == *sg_memberString);
    }

    TEST(qextMemberFunctorTest, testBoundFunctorWith0Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTBoundMemberFunctor<void, MemberBase> voidBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidFunction0);
        voidBoundMemberBaseFunctor();
        CHECK("MemberBase::voidFunction0" == *sg_memberString);
        QEXTBoundMemberFunctor<int, MemberBase> intBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intFunction0);
        intBoundMemberBaseFunctor();
        CHECK("MemberBase::intFunction0" == *sg_memberString);
        QEXTBoundMemberFunctor<double, MemberBase> doubleBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleFunction0);
        doubleBoundMemberBaseFunctor();
        CHECK("MemberBase::doubleFunction0" == *sg_memberString);
    }

    TEST(qextMemberFunctorTest, testPolymorphismBoundFunctorWith0Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTBoundMemberFunctor<void, MemberBase> voidBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction0);
        voidBoundMemberBaseFunctor();
        CHECK("Member::voidFunction0" == *sg_memberString);
        QEXTBoundMemberFunctor<int, MemberBase> intBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction0);
        intBoundMemberBaseFunctor();
        CHECK("Member::intFunction0" == *sg_memberString);
        QEXTBoundMemberFunctor<double, MemberBase> doubleBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction0);
        doubleBoundMemberBaseFunctor();
        CHECK("Member::doubleFunction0" == *sg_memberString);
    }

    TEST(qextMemberFunctorTest, testBoundConstFunctorWith0Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTBoundConstMemberFunctor<void, MemberBase> voidBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunction0);
        voidBoundConstMemberBaseFunctor();
        CHECK("MemberBase::voidConstFunction0" == *sg_memberString);
        QEXTBoundConstMemberFunctor<int, MemberBase> intBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intConstFunction0);
        intBoundConstMemberBaseFunctor();
        CHECK("MemberBase::intConstFunction0" == *sg_memberString);
        QEXTBoundConstMemberFunctor<double, MemberBase> doubleBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunction0);
        doubleBoundConstMemberBaseFunctor();
        CHECK("MemberBase::doubleConstFunction0" == *sg_memberString);
    }

    TEST(qextMemberFunctorTest, testPolymorphismBoundConstFunctorWith0Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTBoundConstMemberFunctor<void, MemberBase> voidBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction0);
        voidBoundConstMemberBaseFunctor();
        CHECK("Member::voidConstFunction0" == *sg_memberString);
        QEXTBoundConstMemberFunctor<int, MemberBase> intBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction0);
        intBoundConstMemberBaseFunctor();
        CHECK("Member::intConstFunction0" == *sg_memberString);
        QEXTBoundConstMemberFunctor<double, MemberBase> doubleBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction0);
        doubleBoundConstMemberBaseFunctor();
        CHECK("Member::doubleConstFunction0" == *sg_memberString);
    }

    TEST(qextMemberFunctorTest, testBoundVolatileFunctorWith0Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTBoundVolatileMemberFunctor<void, MemberBase> voidBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunction0);
        voidBoundVolatileMemberBaseFunctor();
        CHECK("MemberBase::voidVolatileFunction0" == *sg_memberString);
        QEXTBoundVolatileMemberFunctor<int, MemberBase> intBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunction0);
        intBoundVolatileMemberBaseFunctor();
        CHECK("MemberBase::intVolatileFunction0" == *sg_memberString);
        QEXTBoundVolatileMemberFunctor<double, MemberBase> doubleBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunction0);
        doubleBoundVolatileMemberBaseFunctor();
        CHECK("MemberBase::doubleVolatileFunction0" == *sg_memberString);
    }

    TEST(qextMemberFunctorTest, testPolymorphismBoundVolatileFunctorWith0Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTBoundVolatileMemberFunctor<void, MemberBase> voidBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction0);
        voidBoundVolatileMemberBaseFunctor();
        CHECK("Member::voidVolatileFunction0" == *sg_memberString);
        QEXTBoundVolatileMemberFunctor<int, MemberBase> intBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction0);
        intBoundVolatileMemberBaseFunctor();
        CHECK("Member::intVolatileFunction0" == *sg_memberString);
        QEXTBoundVolatileMemberFunctor<double, MemberBase> doubleBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction0);
        doubleBoundVolatileMemberBaseFunctor();
        CHECK("Member::doubleVolatileFunction0" == *sg_memberString);
    }

    TEST(qextMemberFunctorTest, testBoundConstVolatileFunctorWith0Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTBoundConstVolatileMemberFunctor<void, MemberBase> voidBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunction0);
        voidBoundConstVolatileMemberBaseFunctor();
        CHECK("MemberBase::voidConstVolatileFunction0" == *sg_memberString);
        QEXTBoundConstVolatileMemberFunctor<int, MemberBase> intBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunction0);
        intBoundConstVolatileMemberBaseFunctor();
        CHECK("MemberBase::intConstVolatileFunction0" == *sg_memberString);
        QEXTBoundConstVolatileMemberFunctor<double, MemberBase> doubleBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction0);
        doubleBoundConstVolatileMemberBaseFunctor();
        CHECK("MemberBase::doubleConstVolatileFunction0" == *sg_memberString);
    }

    TEST(qextMemberFunctorTest, testPolymorphismBoundConstVolatileFunctorWith0Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTBoundConstVolatileMemberFunctor<void, MemberBase> voidBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction0);
        voidBoundConstVolatileMemberBaseFunctor();
        CHECK("Member::voidConstVolatileFunction0" == *sg_memberString);
        QEXTBoundConstVolatileMemberFunctor<int, MemberBase> intBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction0);
        intBoundConstVolatileMemberBaseFunctor();
        CHECK("Member::intConstVolatileFunction0" == *sg_memberString);
        QEXTBoundConstVolatileMemberFunctor<double, MemberBase> doubleBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction0);
        doubleBoundConstVolatileMemberBaseFunctor();
        CHECK("Member::doubleConstVolatileFunction0" == *sg_memberString);
    }

    TEST(qextMemberFunctorTest, testFunctorWith1Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTMemberFunctor<void, MemberBase, int> voidMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidFunction1);
        voidMemberBaseFunctor(&memberBase, 1);
        CHECK("MemberBase::voidFunction1" == *sg_memberString);
        QEXTMemberFunctor<int, MemberBase, int> intMemberBaseFunctor = qextMemberFunctor(&MemberBase::intFunction1);
        CHECK(1 == intMemberBaseFunctor(&memberBase, 1));
        QEXTMemberFunctor<double, MemberBase, double> doubleMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleFunction1);
        CHECK(1.1 == doubleMemberBaseFunctor(&memberBase, 1.1));

        QEXTMemberFunctor<void, MemberBase, bool> voidMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidFunctionB1);
        voidMemberBaseFunctorB(&memberBase, 1);
        CHECK("MemberBase::voidFunctionB1" == *sg_memberString);
        QEXTMemberFunctor<int, MemberBase, bool> intMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intFunctionB1);
        CHECK(1 == intMemberBaseFunctorB(&memberBase, true));
        CHECK(0 == intMemberBaseFunctorB(&memberBase, false));
        QEXTMemberFunctor<double, MemberBase, bool> doubleMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleFunctionB1);
        CHECK(1 == doubleMemberBaseFunctorB(&memberBase, true));
        CHECK(0 == doubleMemberBaseFunctorB(&memberBase, false));
    }

    TEST(qextMemberFunctorTest, testPolymorphismFunctorWith1Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTMemberFunctor<void, MemberBase, int> voidMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidFunction1);
        voidMemberBaseFunctor(&member, 1);
        CHECK("Member::voidFunction1" == *sg_memberString);
        QEXTMemberFunctor<int, MemberBase, int> intMemberBaseFunctor = qextMemberFunctor(&MemberBase::intFunction1);
        CHECK(0 == intMemberBaseFunctor(&member, 1));
        QEXTMemberFunctor<double, MemberBase, double> doubleMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleFunction1);
        CHECK(0 == doubleMemberBaseFunctor(&member, 1.1));

        QEXTMemberFunctor<void, MemberBase, bool> voidMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidFunctionB1);
        voidMemberBaseFunctorB(&member, 1);
        CHECK("Member::voidFunctionB1" == *sg_memberString);
        QEXTMemberFunctor<int, MemberBase, bool> intMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intFunctionB1);
        CHECK(1 == intMemberBaseFunctorB(&member, true));
        CHECK(0 == intMemberBaseFunctorB(&member, false));
        QEXTMemberFunctor<double, MemberBase, bool> doubleMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleFunctionB1);
        CHECK(1 == doubleMemberBaseFunctorB(&member, true));
        CHECK(0 == doubleMemberBaseFunctorB(&member, false));
    }

    TEST(qextMemberFunctorTest, testConstFunctorWith1Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTConstMemberFunctor<void, MemberBase, int> voidConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstFunction1);
        voidConstMemberBaseFunctor(&memberBase, 1);
        CHECK("MemberBase::voidConstFunction1" == *sg_memberString);
        QEXTConstMemberFunctor<int, MemberBase, int> intConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstFunction1);
        CHECK(1 == intConstMemberBaseFunctor(&memberBase, 1));
        QEXTConstMemberFunctor<double, MemberBase, double> doubleConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstFunction1);
        CHECK(1.1 == doubleConstMemberBaseFunctor(&memberBase, 1.1));

        QEXTConstMemberFunctor<void, MemberBase, bool> voidConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstFunctionB1);
        voidConstMemberBaseFunctorB(&memberBase, 1);
        CHECK("MemberBase::voidConstFunctionB1" == *sg_memberString);
        QEXTConstMemberFunctor<int, MemberBase, bool> intConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstFunctionB1);
        CHECK(1 == intConstMemberBaseFunctorB(&memberBase, true));
        CHECK(0 == intConstMemberBaseFunctorB(&memberBase, false));
        QEXTConstMemberFunctor<double, MemberBase, bool> doubleConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstFunctionB1);
        CHECK(1 == doubleConstMemberBaseFunctorB(&memberBase, true));
        CHECK(0 == doubleConstMemberBaseFunctorB(&memberBase, false));
    }

    TEST(qextMemberFunctorTest, testPolymorphismConstFunctorWith1Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTConstMemberFunctor<void, MemberBase, int> voidConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstFunction1);
        voidConstMemberBaseFunctor(&member, 1);
        CHECK("Member::voidConstFunction1" == *sg_memberString);
        QEXTConstMemberFunctor<int, MemberBase, int> intConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstFunction1);
        CHECK(0 == intConstMemberBaseFunctor(&member, 1));
        QEXTConstMemberFunctor<double, MemberBase, double> doubleConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstFunction1);
        CHECK(0 == doubleConstMemberBaseFunctor(&member, 1.1));

        QEXTConstMemberFunctor<void, MemberBase, bool> voidConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstFunctionB1);
        voidConstMemberBaseFunctorB(&member, 1);
        CHECK("Member::voidConstFunctionB1" == *sg_memberString);
        QEXTConstMemberFunctor<int, MemberBase, bool> intConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstFunctionB1);
        CHECK(1 == intConstMemberBaseFunctorB(&member, true));
        CHECK(0 == intConstMemberBaseFunctorB(&member, false));
        QEXTConstMemberFunctor<double, MemberBase, bool> doubleConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstFunctionB1);
        CHECK(1 == doubleConstMemberBaseFunctorB(&member, true));
        CHECK(0 == doubleConstMemberBaseFunctorB(&member, false));
    }

    TEST(qextMemberFunctorTest, testVolatileFunctorWith1Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTVolatileMemberFunctor<void, MemberBase, int> voidVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidVolatileFunction1);
        voidVolatileMemberBaseFunctor(&memberBase, 1);
        CHECK("MemberBase::voidVolatileFunction1" == *sg_memberString);
        QEXTVolatileMemberFunctor<int, MemberBase, int> intVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intVolatileFunction1);
        CHECK(1 == intVolatileMemberBaseFunctor(&memberBase, 1));
        QEXTVolatileMemberFunctor<double, MemberBase, double> doubleVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleVolatileFunction1);
        CHECK(1.1 == doubleVolatileMemberBaseFunctor(&memberBase, 1.1));

        QEXTVolatileMemberFunctor<void, MemberBase, bool> voidVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidVolatileFunctionB1);
        voidVolatileMemberBaseFunctorB(&memberBase, 1);
        CHECK("MemberBase::voidVolatileFunctionB1" == *sg_memberString);
        QEXTVolatileMemberFunctor<int, MemberBase, bool> intVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intVolatileFunctionB1);
        CHECK(1 == intVolatileMemberBaseFunctorB(&memberBase, true));
        CHECK(0 == intVolatileMemberBaseFunctorB(&memberBase, false));
        QEXTVolatileMemberFunctor<double, MemberBase, bool> doubleVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB1);
        CHECK(1 == doubleVolatileMemberBaseFunctorB(&memberBase, true));
        CHECK(0 == doubleVolatileMemberBaseFunctorB(&memberBase, false));
    }

    TEST(qextMemberFunctorTest, testPolymorphismVolatileFunctorWith1Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTVolatileMemberFunctor<void, MemberBase, int> voidVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidVolatileFunction1);
        voidVolatileMemberBaseFunctor(&member, 1);
        CHECK("Member::voidVolatileFunction1" == *sg_memberString);
        QEXTVolatileMemberFunctor<int, MemberBase, int> intVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intVolatileFunction1);
        CHECK(0 == intVolatileMemberBaseFunctor(&member, 1));
        QEXTVolatileMemberFunctor<double, MemberBase, double> doubleVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleVolatileFunction1);
        CHECK(0 == doubleVolatileMemberBaseFunctor(&member, 1.1));

        QEXTVolatileMemberFunctor<void, MemberBase, bool> voidVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidVolatileFunctionB1);
        voidVolatileMemberBaseFunctorB(&member, 1);
        CHECK("Member::voidVolatileFunctionB1" == *sg_memberString);
        QEXTVolatileMemberFunctor<int, MemberBase, bool> intVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intVolatileFunctionB1);
        CHECK(1 == intVolatileMemberBaseFunctorB(&member, true));
        CHECK(0 == intVolatileMemberBaseFunctorB(&member, false));
        QEXTVolatileMemberFunctor<double, MemberBase, bool> doubleVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB1);
        CHECK(1 == doubleVolatileMemberBaseFunctorB(&member, true));
        CHECK(0 == doubleVolatileMemberBaseFunctorB(&member, false));
    }

    TEST(qextMemberFunctorTest, testConstVolatileFunctorWith1Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTConstVolatileMemberFunctor<void, MemberBase, int> voidConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstVolatileFunction1);
        voidConstVolatileMemberBaseFunctor(&memberBase, 1);
        CHECK("MemberBase::voidConstVolatileFunction1" == *sg_memberString);
        QEXTConstVolatileMemberFunctor<int, MemberBase, int> intConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstVolatileFunction1);
        CHECK(1 == intConstVolatileMemberBaseFunctor(&memberBase, 1));
        QEXTConstVolatileMemberFunctor<double, MemberBase, double> doubleConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction1);
        CHECK(1.1 == doubleConstVolatileMemberBaseFunctor(&memberBase, 1.1));

        QEXTConstVolatileMemberFunctor<void, MemberBase, bool> voidConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB1);
        voidConstVolatileMemberBaseFunctorB(&memberBase, 1);
        CHECK("MemberBase::voidConstVolatileFunctionB1" == *sg_memberString);
        QEXTConstVolatileMemberFunctor<int, MemberBase, bool> intConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB1);
        CHECK(1 == intConstVolatileMemberBaseFunctorB(&memberBase, true));
        CHECK(0 == intConstVolatileMemberBaseFunctorB(&memberBase, false));
        QEXTConstVolatileMemberFunctor<double, MemberBase, bool> doubleConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB1);
        CHECK(1 == doubleConstVolatileMemberBaseFunctorB(&memberBase, true));
        CHECK(0 == doubleConstVolatileMemberBaseFunctorB(&memberBase, false));
    }

    TEST(qextMemberFunctorTest, testPolymorphismConstVolatileFunctorWith1Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTConstVolatileMemberFunctor<void, MemberBase, int> voidConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstVolatileFunction1);
        voidConstVolatileMemberBaseFunctor(&member, 1);
        CHECK("Member::voidConstVolatileFunction1" == *sg_memberString);
        QEXTConstVolatileMemberFunctor<int, MemberBase, int> intConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstVolatileFunction1);
        CHECK(0 == intConstVolatileMemberBaseFunctor(&member, 1));
        QEXTConstVolatileMemberFunctor<double, MemberBase, double> doubleConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction1);
        CHECK(0 == doubleConstVolatileMemberBaseFunctor(&member, 1.1));

        QEXTConstVolatileMemberFunctor<void, MemberBase, bool> voidConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB1);
        voidConstVolatileMemberBaseFunctorB(&member, 1);
        CHECK("Member::voidConstVolatileFunctionB1" == *sg_memberString);
        QEXTConstVolatileMemberFunctor<int, MemberBase, bool> intConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB1);
        CHECK(1 == intConstVolatileMemberBaseFunctorB(&member, true));
        CHECK(0 == intConstVolatileMemberBaseFunctorB(&member, false));
        QEXTConstVolatileMemberFunctor<double, MemberBase, bool> doubleConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB1);
        CHECK(1 == doubleConstVolatileMemberBaseFunctorB(&member, true));
        CHECK(0 == doubleConstVolatileMemberBaseFunctorB(&member, false));
    }

    TEST(qextMemberFunctorTest, testBoundFunctorWith1Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTBoundMemberFunctor<void, MemberBase, int> voidBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidFunction1);
        voidBoundMemberBaseFunctor(1);
        CHECK("MemberBase::voidFunction1" == *sg_memberString);
        QEXTBoundMemberFunctor<int, MemberBase, int> intBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intFunction1);
        CHECK(1 == intBoundMemberBaseFunctor(1));
        QEXTBoundMemberFunctor<double, MemberBase, double> doubleBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleFunction1);
        CHECK(1.1 == doubleBoundMemberBaseFunctor(1.1));

        QEXTBoundMemberFunctor<void, MemberBase, bool> voidBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidFunctionB1);
        voidBoundMemberBaseFunctorB(1);
        CHECK("MemberBase::voidFunctionB1" == *sg_memberString);
        QEXTBoundMemberFunctor<int, MemberBase, bool> intBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intFunctionB1);
        CHECK(1 == intBoundMemberBaseFunctorB(true));
        CHECK(0 == intBoundMemberBaseFunctorB(false));
        QEXTBoundMemberFunctor<double, MemberBase, bool> doubleBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleFunctionB1);
        CHECK(1 == doubleBoundMemberBaseFunctorB(true));
        CHECK(0 == doubleBoundMemberBaseFunctorB(false));
    }

    TEST(qextMemberFunctorTest, testPolymorphismBoundFunctorWith1Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTBoundMemberFunctor<void, MemberBase, int> voidBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction1);
        voidBoundMemberBaseFunctor(1);
        CHECK("Member::voidFunction1" == *sg_memberString);
        QEXTBoundMemberFunctor<int, MemberBase, int> intBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction1);
        CHECK(0 == intBoundMemberBaseFunctor(1));
        QEXTBoundMemberFunctor<double, MemberBase, double> doubleBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction1);
        CHECK(0 == doubleBoundMemberBaseFunctor(1.1));

        QEXTBoundMemberFunctor<void, MemberBase, bool> voidBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunctionB1);
        voidBoundMemberBaseFunctorB(1);
        CHECK("Member::voidFunctionB1" == *sg_memberString);
        QEXTBoundMemberFunctor<int, MemberBase, bool> intBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunctionB1);
        CHECK(1 == intBoundMemberBaseFunctorB(true));
        CHECK(0 == intBoundMemberBaseFunctorB(false));
        QEXTBoundMemberFunctor<double, MemberBase, bool> doubleBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunctionB1);
        CHECK(1 == doubleBoundMemberBaseFunctorB(true));
        CHECK(0 == doubleBoundMemberBaseFunctorB(false));
    }

    TEST(qextMemberFunctorTest, testBoundConstFunctorWith1Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTBoundConstMemberFunctor<void, MemberBase, int> voidBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunction1);
        voidBoundConstMemberBaseFunctor(1);
        CHECK("MemberBase::voidConstFunction1" == *sg_memberString);
        QEXTBoundConstMemberFunctor<int, MemberBase, int> intBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intConstFunction1);
        CHECK(1 == intBoundConstMemberBaseFunctor(1));
        QEXTBoundConstMemberFunctor<double, MemberBase, double> doubleBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunction1);
        CHECK(1.1 == doubleBoundConstMemberBaseFunctor(1.1));

        QEXTBoundConstMemberFunctor<void, MemberBase, bool> voidBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunctionB1);
        voidBoundConstMemberBaseFunctorB(1);
        CHECK("MemberBase::voidConstFunctionB1" == *sg_memberString);
        QEXTBoundConstMemberFunctor<int, MemberBase, bool> intBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intConstFunctionB1);
        CHECK(1 == intBoundConstMemberBaseFunctorB(true));
        CHECK(0 == intBoundConstMemberBaseFunctorB(false));
        QEXTBoundConstMemberFunctor<double, MemberBase, bool> doubleBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunctionB1);
        CHECK(1 == doubleBoundConstMemberBaseFunctorB(true));
        CHECK(0 == doubleBoundConstMemberBaseFunctorB(false));
    }

    TEST(qextMemberFunctorTest, testPolymorphismBoundConstFunctorWith1Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTBoundConstMemberFunctor<void, MemberBase, int> voidBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction1);
        voidBoundConstMemberBaseFunctor(1);
        CHECK("Member::voidConstFunction1" == *sg_memberString);
        QEXTBoundConstMemberFunctor<int, MemberBase, int> intBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction1);
        CHECK(0 == intBoundConstMemberBaseFunctor(1));
        QEXTBoundConstMemberFunctor<double, MemberBase, double> doubleBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction1);
        CHECK(0 == doubleBoundConstMemberBaseFunctor(1.1));

        QEXTBoundConstMemberFunctor<void, MemberBase, bool> voidBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunctionB1);
        voidBoundConstMemberBaseFunctorB(1);
        CHECK("Member::voidConstFunctionB1" == *sg_memberString);
        QEXTBoundConstMemberFunctor<int, MemberBase, bool> intBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunctionB1);
        CHECK(1 == intBoundConstMemberBaseFunctorB(true));
        CHECK(0 == intBoundConstMemberBaseFunctorB(false));
        QEXTBoundConstMemberFunctor<double, MemberBase, bool> doubleBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunctionB1);
        CHECK(1 == doubleBoundConstMemberBaseFunctorB(true));
        CHECK(0 == doubleBoundConstMemberBaseFunctorB(false));
    }

    TEST(qextMemberFunctorTest, testBoundVolatileFunctorWith1Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTBoundVolatileMemberFunctor<void, MemberBase, int> voidBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunction1);
        voidBoundVolatileMemberBaseFunctor(1);
        CHECK("MemberBase::voidVolatileFunction1" == *sg_memberString);
        QEXTBoundVolatileMemberFunctor<int, MemberBase, int> intBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunction1);
        CHECK(1 == intBoundVolatileMemberBaseFunctor(1));
        QEXTBoundVolatileMemberFunctor<double, MemberBase, double> doubleBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunction1);
        CHECK(1.1 == doubleBoundVolatileMemberBaseFunctor(1.1));

        QEXTBoundVolatileMemberFunctor<void, MemberBase, bool> voidBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunctionB1);
        voidBoundVolatileMemberBaseFunctorB(1);
        CHECK("MemberBase::voidVolatileFunctionB1" == *sg_memberString);
        QEXTBoundVolatileMemberFunctor<int, MemberBase, bool> intBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunctionB1);
        CHECK(1 == intBoundVolatileMemberBaseFunctorB(true));
        CHECK(0 == intBoundVolatileMemberBaseFunctorB(false));
        QEXTBoundVolatileMemberFunctor<double, MemberBase, bool> doubleBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunctionB1);
        CHECK(1 == doubleBoundVolatileMemberBaseFunctorB(true));
        CHECK(0 == doubleBoundVolatileMemberBaseFunctorB(false));
    }

    TEST(qextMemberFunctorTest, testPolymorphismBoundVolatileFunctorWith1Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTBoundVolatileMemberFunctor<void, MemberBase, int> voidBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction1);
        voidBoundVolatileMemberBaseFunctor(1);
        CHECK("Member::voidVolatileFunction1" == *sg_memberString);
        QEXTBoundVolatileMemberFunctor<int, MemberBase, int> intBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction1);
        CHECK(0 == intBoundVolatileMemberBaseFunctor(1));
        QEXTBoundVolatileMemberFunctor<double, MemberBase, double> doubleBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction1);
        CHECK(0 == doubleBoundVolatileMemberBaseFunctor(1.1));

        QEXTBoundVolatileMemberFunctor<void, MemberBase, bool> voidBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunctionB1);
        voidBoundVolatileMemberBaseFunctorB(1);
        CHECK("Member::voidVolatileFunctionB1" == *sg_memberString);
        QEXTBoundVolatileMemberFunctor<int, MemberBase, bool> intBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunctionB1);
        CHECK(1 == intBoundVolatileMemberBaseFunctorB(true));
        CHECK(0 == intBoundVolatileMemberBaseFunctorB(false));
        QEXTBoundVolatileMemberFunctor<double, MemberBase, bool> doubleBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunctionB1);
        CHECK(1 == doubleBoundVolatileMemberBaseFunctorB(true));
        CHECK(0 == doubleBoundVolatileMemberBaseFunctorB(false));
    }

    TEST(qextMemberFunctorTest, testBoundConstVolatileFunctorWith1Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTBoundConstVolatileMemberFunctor<void, MemberBase, int> voidBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunction1);
        voidBoundConstVolatileMemberBaseFunctor(1);
        CHECK("MemberBase::voidConstVolatileFunction1" == *sg_memberString);
        QEXTBoundConstVolatileMemberFunctor<int, MemberBase, int> intBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunction1);
        CHECK(1 == intBoundConstVolatileMemberBaseFunctor(1));
        QEXTBoundConstVolatileMemberFunctor<double, MemberBase, double> doubleBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction1);
        CHECK(1.1 == doubleBoundConstVolatileMemberBaseFunctor(1.1));

        QEXTBoundConstVolatileMemberFunctor<void, MemberBase, bool> voidBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunctionB1);
        voidBoundConstVolatileMemberBaseFunctorB(1);
        CHECK("MemberBase::voidConstVolatileFunctionB1" == *sg_memberString);
        QEXTBoundConstVolatileMemberFunctor<int, MemberBase, bool> intBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunctionB1);
        CHECK(1 == intBoundConstVolatileMemberBaseFunctorB(true));
        CHECK(0 == intBoundConstVolatileMemberBaseFunctorB(false));
        QEXTBoundConstVolatileMemberFunctor<double, MemberBase, bool> doubleBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunctionB1);
        CHECK(1 == doubleBoundConstVolatileMemberBaseFunctorB(true));
        CHECK(0 == doubleBoundConstVolatileMemberBaseFunctorB(false));
    }

    TEST(qextMemberFunctorTest, testPolymorphismBoundConstVolatileFunctorWith1Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTBoundConstVolatileMemberFunctor<void, MemberBase, int> voidBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction1);
        voidBoundConstVolatileMemberBaseFunctor(1);
        CHECK("Member::voidConstVolatileFunction1" == *sg_memberString);
        QEXTBoundConstVolatileMemberFunctor<int, MemberBase, int> intBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction1);
        CHECK(0 == intBoundConstVolatileMemberBaseFunctor(1));
        QEXTBoundConstVolatileMemberFunctor<double, MemberBase, double> doubleBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction1);
        CHECK(0 == doubleBoundConstVolatileMemberBaseFunctor(1.1));

        QEXTBoundConstVolatileMemberFunctor<void, MemberBase, bool> voidBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunctionB1);
        voidBoundConstVolatileMemberBaseFunctorB(1);
        CHECK("Member::voidConstVolatileFunctionB1" == *sg_memberString);
        QEXTBoundConstVolatileMemberFunctor<int, MemberBase, bool> intBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunctionB1);
        CHECK(1 == intBoundConstVolatileMemberBaseFunctorB(true));
        CHECK(0 == intBoundConstVolatileMemberBaseFunctorB(false));
        QEXTBoundConstVolatileMemberFunctor<double, MemberBase, bool> doubleBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunctionB1);
        CHECK(1 == doubleBoundConstVolatileMemberBaseFunctorB(true));
        CHECK(0 == doubleBoundConstVolatileMemberBaseFunctorB(false));
    }

    TEST(qextMemberFunctorTest, testFunctorWith2Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTMemberFunctor<void, MemberBase, int, int> voidMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidFunction2);
        voidMemberBaseFunctor(&memberBase, 1, 2);
        CHECK("MemberBase::voidFunction2" == *sg_memberString);
        QEXTMemberFunctor<int, MemberBase, int, int> intMemberBaseFunctor = qextMemberFunctor(&MemberBase::intFunction2);
        CHECK(1 + 2 == intMemberBaseFunctor(&memberBase, 1, 2));
        QEXTMemberFunctor<double, MemberBase, double, double> doubleMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleFunction2);
        CHECK(1.1 + 2.2 == doubleMemberBaseFunctor(&memberBase, 1.1, 2.2));

        QEXTMemberFunctor<void, MemberBase, bool, int> voidMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidFunctionB2);
        voidMemberBaseFunctorB(&memberBase, true, 2);
        CHECK("MemberBase::voidFunctionB2" == *sg_memberString);
        QEXTMemberFunctor<int, MemberBase, bool, int> intMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intFunctionB2);
        CHECK(2 == intMemberBaseFunctorB(&memberBase, true, 2));
        CHECK(0 == intMemberBaseFunctorB(&memberBase, false, 2));
        QEXTMemberFunctor<double, MemberBase, bool, double> doubleMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleFunctionB2);
        CHECK(2.2 == doubleMemberBaseFunctorB(&memberBase, true, 2.2));
        CHECK(0 == doubleMemberBaseFunctorB(&memberBase, false, 2.2));
    }

    TEST(qextMemberFunctorTest, testPolymorphismFunctorWith2Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTMemberFunctor<void, MemberBase, int, int> voidMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidFunction2);
        voidMemberBaseFunctor(&member, 1, 2);
        CHECK("Member::voidFunction2" == *sg_memberString);
        QEXTMemberFunctor<int, MemberBase, int, int> intMemberBaseFunctor = qextMemberFunctor(&MemberBase::intFunction2);
        CHECK(0 == intMemberBaseFunctor(&member, 1, 2));
        QEXTMemberFunctor<double, MemberBase, double, double> doubleMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleFunction2);
        CHECK(0 == doubleMemberBaseFunctor(&member, 1.1, 2.2));

        QEXTMemberFunctor<void, MemberBase, bool, int> voidMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidFunctionB2);
        voidMemberBaseFunctorB(&member, true, 2);
        CHECK("Member::voidFunctionB2" == *sg_memberString);
        QEXTMemberFunctor<int, MemberBase, bool, int> intMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intFunctionB2);
        CHECK(1 == intMemberBaseFunctorB(&member, true, 2));
        CHECK(0 == intMemberBaseFunctorB(&member, false, 2));
        QEXTMemberFunctor<double, MemberBase, bool, double> doubleMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleFunctionB2);
        CHECK(1 == doubleMemberBaseFunctorB(&member, true, 2.2));
        CHECK(0 == doubleMemberBaseFunctorB(&member, false, 2.2));
    }

    TEST(qextMemberFunctorTest, testConstFunctorWith2Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTConstMemberFunctor<void, MemberBase, int, int> voidConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstFunction2);
        voidConstMemberBaseFunctor(&memberBase, 1, 2);
        CHECK("MemberBase::voidConstFunction2" == *sg_memberString);
        QEXTConstMemberFunctor<int, MemberBase, int, int> intConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstFunction2);
        CHECK(1 + 2 == intConstMemberBaseFunctor(&memberBase, 1, 2));
        QEXTConstMemberFunctor<double, MemberBase, double, double> doubleConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstFunction2);
        CHECK(1.1 + 2.2 == doubleConstMemberBaseFunctor(&memberBase, 1.1, 2.2));

        QEXTConstMemberFunctor<void, MemberBase, bool, int> voidConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstFunctionB2);
        voidConstMemberBaseFunctorB(&memberBase, true, 2);
        CHECK("MemberBase::voidConstFunctionB2" == *sg_memberString);
        QEXTConstMemberFunctor<int, MemberBase, bool, int> intConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstFunctionB2);
        CHECK(2 == intConstMemberBaseFunctorB(&memberBase, true, 2));
        CHECK(0 == intConstMemberBaseFunctorB(&memberBase, false, 2));
        QEXTConstMemberFunctor<double, MemberBase, bool, double> doubleConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstFunctionB2);
        CHECK(2.2 == doubleConstMemberBaseFunctorB(&memberBase, true, 2.2));
        CHECK(0 == doubleConstMemberBaseFunctorB(&memberBase, false, 2.2));
    }

    TEST(qextMemberFunctorTest, testPolymorphismConstFunctorWith2Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTConstMemberFunctor<void, MemberBase, int, int> voidConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstFunction2);
        voidConstMemberBaseFunctor(&member, 1, 2);
        CHECK("Member::voidConstFunction2" == *sg_memberString);
        QEXTConstMemberFunctor<int, MemberBase, int, int> intConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstFunction2);
        CHECK(0 == intConstMemberBaseFunctor(&member, 1, 2));
        QEXTConstMemberFunctor<double, MemberBase, double, double> doubleConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstFunction2);
        CHECK(0 == doubleConstMemberBaseFunctor(&member, 1.1, 2.2));

        QEXTConstMemberFunctor<void, MemberBase, bool, int> voidConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstFunctionB2);
        voidConstMemberBaseFunctorB(&member, true, 2);
        CHECK("Member::voidConstFunctionB2" == *sg_memberString);
        QEXTConstMemberFunctor<int, MemberBase, bool, int> intConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstFunctionB2);
        CHECK(1 == intConstMemberBaseFunctorB(&member, true, 2));
        CHECK(0 == intConstMemberBaseFunctorB(&member, false, 2));
        QEXTConstMemberFunctor<double, MemberBase, bool, double> doubleConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstFunctionB2);
        CHECK(1 == doubleConstMemberBaseFunctorB(&member, true, 2.2));
        CHECK(0 == doubleConstMemberBaseFunctorB(&member, false, 2.2));
    }

    TEST(qextMemberFunctorTest, testVolatileFunctorWith2Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTVolatileMemberFunctor<void, MemberBase, int, int> voidVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidVolatileFunction2);
        voidVolatileMemberBaseFunctor(&memberBase, 1, 2);
        CHECK("MemberBase::voidVolatileFunction2" == *sg_memberString);
        QEXTVolatileMemberFunctor<int, MemberBase, int, int> intVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intVolatileFunction2);
        CHECK(1 + 2 == intVolatileMemberBaseFunctor(&memberBase, 1, 2));
        QEXTVolatileMemberFunctor<double, MemberBase, double, double> doubleVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleVolatileFunction2);
        CHECK(1.1 + 2.2 == doubleVolatileMemberBaseFunctor(&memberBase, 1.1, 2.2));

        QEXTVolatileMemberFunctor<void, MemberBase, bool, int> voidVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidVolatileFunctionB2);
        voidVolatileMemberBaseFunctorB(&memberBase, true, 2);
        CHECK("MemberBase::voidVolatileFunctionB2" == *sg_memberString);
        QEXTVolatileMemberFunctor<int, MemberBase, bool, int> intVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intVolatileFunctionB2);
        CHECK(2 == intVolatileMemberBaseFunctorB(&memberBase, true, 2));
        CHECK(0 == intVolatileMemberBaseFunctorB(&memberBase, false, 2));
        QEXTVolatileMemberFunctor<double, MemberBase, bool, double> doubleVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB2);
        CHECK(2.2 == doubleVolatileMemberBaseFunctorB(&memberBase, true, 2.2));
        CHECK(0 == doubleVolatileMemberBaseFunctorB(&memberBase, false, 2.2));
    }

    TEST(qextMemberFunctorTest, testPolymorphismVolatileFunctorWith2Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTVolatileMemberFunctor<void, MemberBase, int, int> voidVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidVolatileFunction2);
        voidVolatileMemberBaseFunctor(&member, 1, 2);
        CHECK("Member::voidVolatileFunction2" == *sg_memberString);
        QEXTVolatileMemberFunctor<int, MemberBase, int, int> intVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intVolatileFunction2);
        CHECK(0 == intVolatileMemberBaseFunctor(&member, 1, 2));
        QEXTVolatileMemberFunctor<double, MemberBase, double, double> doubleVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleVolatileFunction2);
        CHECK(0 == doubleVolatileMemberBaseFunctor(&member, 1.1, 2.2));

        QEXTVolatileMemberFunctor<void, MemberBase, bool, int> voidVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidVolatileFunctionB2);
        voidVolatileMemberBaseFunctorB(&member, true, 2);
        CHECK("Member::voidVolatileFunctionB2" == *sg_memberString);
        QEXTVolatileMemberFunctor<int, MemberBase, bool, int> intVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intVolatileFunctionB2);
        CHECK(1 == intVolatileMemberBaseFunctorB(&member, true, 2));
        CHECK(0 == intVolatileMemberBaseFunctorB(&member, false, 2));
        QEXTVolatileMemberFunctor<double, MemberBase, bool, double> doubleVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB2);
        CHECK(1 == doubleVolatileMemberBaseFunctorB(&member, true, 2.2));
        CHECK(0 == doubleVolatileMemberBaseFunctorB(&member, false, 2.2));
    }

    TEST(qextMemberFunctorTest, testConstVolatileFunctorWith2Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTConstVolatileMemberFunctor<void, MemberBase, int, int> voidConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstVolatileFunction2);
        voidConstVolatileMemberBaseFunctor(&memberBase, 1, 2);
        CHECK("MemberBase::voidConstVolatileFunction2" == *sg_memberString);
        QEXTConstVolatileMemberFunctor<int, MemberBase, int, int> intConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstVolatileFunction2);
        CHECK(1 + 2 == intConstVolatileMemberBaseFunctor(&memberBase, 1, 2));
        QEXTConstVolatileMemberFunctor<double, MemberBase, double, double> doubleConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction2);
        CHECK(1.1 + 2.2 == doubleConstVolatileMemberBaseFunctor(&memberBase, 1.1, 2.2));

        QEXTConstVolatileMemberFunctor<void, MemberBase, bool, int> voidConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB2);
        voidConstVolatileMemberBaseFunctorB(&memberBase, true, 2);
        CHECK("MemberBase::voidConstVolatileFunctionB2" == *sg_memberString);
        QEXTConstVolatileMemberFunctor<int, MemberBase, bool, int> intConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB2);
        CHECK(2 == intConstVolatileMemberBaseFunctorB(&memberBase, true, 2));
        CHECK(0 == intConstVolatileMemberBaseFunctorB(&memberBase, false, 2));
        QEXTConstVolatileMemberFunctor<double, MemberBase, bool, double> doubleConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB2);
        CHECK(2.2 == doubleConstVolatileMemberBaseFunctorB(&memberBase, true, 2.2));
        CHECK(0 == doubleConstVolatileMemberBaseFunctorB(&memberBase, false, 2.2));
    }

    TEST(qextMemberFunctorTest, testPolymorphismConstVolatileFunctorWith2Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTConstVolatileMemberFunctor<void, MemberBase, int, int> voidConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstVolatileFunction2);
        voidConstVolatileMemberBaseFunctor(&member, 1, 2);
        CHECK("Member::voidConstVolatileFunction2" == *sg_memberString);
        QEXTConstVolatileMemberFunctor<int, MemberBase, int, int> intConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstVolatileFunction2);
        CHECK(0 == intConstVolatileMemberBaseFunctor(&member, 1, 2));
        QEXTConstVolatileMemberFunctor<double, MemberBase, double, double> doubleConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction2);
        CHECK(0 == doubleConstVolatileMemberBaseFunctor(&member, 1.1, 2.2));

        QEXTConstVolatileMemberFunctor<void, MemberBase, bool, int> voidConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB2);
        voidConstVolatileMemberBaseFunctorB(&member, true, 2);
        CHECK("Member::voidConstVolatileFunctionB2" == *sg_memberString);
        QEXTConstVolatileMemberFunctor<int, MemberBase, bool, int> intConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB2);
        CHECK(1 == intConstVolatileMemberBaseFunctorB(&member, true, 2));
        CHECK(0 == intConstVolatileMemberBaseFunctorB(&member, false, 2));
        QEXTConstVolatileMemberFunctor<double, MemberBase, bool, double> doubleConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB2);
        CHECK(1 == doubleConstVolatileMemberBaseFunctorB(&member, true, 2.2));
        CHECK(0 == doubleConstVolatileMemberBaseFunctorB(&member, false, 2.2));
    }

    TEST(qextMemberFunctorTest, testBoundFunctorWith2Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTBoundMemberFunctor<void, MemberBase, int, int> voidBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidFunction2);
        voidBoundMemberBaseFunctor(1, 2);
        CHECK("MemberBase::voidFunction2" == *sg_memberString);
        QEXTBoundMemberFunctor<int, MemberBase, int, int> intBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intFunction2);
        CHECK(1 + 2 == intBoundMemberBaseFunctor(1, 2));
        QEXTBoundMemberFunctor<double, MemberBase, double, double> doubleBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleFunction2);
        CHECK(1.1 + 2.2 == doubleBoundMemberBaseFunctor(1.1, 2.2));

        QEXTBoundMemberFunctor<void, MemberBase, bool, int> voidBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidFunctionB2);
        voidBoundMemberBaseFunctorB(true, 2);
        CHECK("MemberBase::voidFunctionB2" == *sg_memberString);
        QEXTBoundMemberFunctor<int, MemberBase, bool, int> intBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intFunctionB2);
        CHECK(2 == intBoundMemberBaseFunctorB(true, 2));
        CHECK(0 == intBoundMemberBaseFunctorB(false, 2));
        QEXTBoundMemberFunctor<double, MemberBase, bool, double> doubleBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleFunctionB2);
        CHECK(2.2 == doubleBoundMemberBaseFunctorB(true, 2.2));
        CHECK(0 == doubleBoundMemberBaseFunctorB(false, 2.2));
    }

    TEST(qextMemberFunctorTest, testPolymorphismBoundFunctorWith2Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTBoundMemberFunctor<void, MemberBase, int, int> voidBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction2);
        voidBoundMemberBaseFunctor(1, 2);
        CHECK("Member::voidFunction2" == *sg_memberString);
        QEXTBoundMemberFunctor<int, MemberBase, int, int> intBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction2);
        CHECK(0 == intBoundMemberBaseFunctor(1, 2));
        QEXTBoundMemberFunctor<double, MemberBase, double, double> doubleBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction2);
        CHECK(0 == doubleBoundMemberBaseFunctor(1.1, 2.2));

        QEXTBoundMemberFunctor<void, MemberBase, bool, int> voidBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunctionB2);
        voidBoundMemberBaseFunctorB(true, 2);
        CHECK("Member::voidFunctionB2" == *sg_memberString);
        QEXTBoundMemberFunctor<int, MemberBase, bool, int> intBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunctionB2);
        CHECK(1 == intBoundMemberBaseFunctorB(true, 2));
        CHECK(0 == intBoundMemberBaseFunctorB(false, 2));
        QEXTBoundMemberFunctor<double, MemberBase, bool, double> doubleBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunctionB2);
        CHECK(1 == doubleBoundMemberBaseFunctorB(true, 2.2));
        CHECK(0 == doubleBoundMemberBaseFunctorB(false, 2.2));
    }

    TEST(qextMemberFunctorTest, testBoundConstFunctorWith2Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTBoundConstMemberFunctor<void, MemberBase, int, int> voidBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunction2);
        voidBoundConstMemberBaseFunctor(1, 2);
        CHECK("MemberBase::voidConstFunction2" == *sg_memberString);
        QEXTBoundConstMemberFunctor<int, MemberBase, int, int> intBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intConstFunction2);
        CHECK(1 + 2 == intBoundConstMemberBaseFunctor(1, 2));
        QEXTBoundConstMemberFunctor<double, MemberBase, double, double> doubleBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunction2);
        CHECK(1.1 + 2.2 == doubleBoundConstMemberBaseFunctor(1.1, 2.2));

        QEXTBoundConstMemberFunctor<void, MemberBase, bool, int> voidBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunctionB2);
        voidBoundConstMemberBaseFunctorB(true, 2);
        CHECK("MemberBase::voidConstFunctionB2" == *sg_memberString);
        QEXTBoundConstMemberFunctor<int, MemberBase, bool, int> intBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intConstFunctionB2);
        CHECK(2 == intBoundConstMemberBaseFunctorB(true, 2));
        CHECK(0 == intBoundConstMemberBaseFunctorB(false, 2));
        QEXTBoundConstMemberFunctor<double, MemberBase, bool, double> doubleBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunctionB2);
        CHECK(2.2 == doubleBoundConstMemberBaseFunctorB(true, 2.2));
        CHECK(0 == doubleBoundConstMemberBaseFunctorB(false, 2.2));
    }

    TEST(qextMemberFunctorTest, testPolymorphismBoundConstFunctorWith2Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTBoundConstMemberFunctor<void, MemberBase, int, int> voidBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction2);
        voidBoundConstMemberBaseFunctor(1, 2);
        CHECK("Member::voidConstFunction2" == *sg_memberString);
        QEXTBoundConstMemberFunctor<int, MemberBase, int, int> intBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction2);
        CHECK(0 == intBoundConstMemberBaseFunctor(1, 2));
        QEXTBoundConstMemberFunctor<double, MemberBase, double, double> doubleBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction2);
        CHECK(0 == doubleBoundConstMemberBaseFunctor(1.1, 2.2));

        QEXTBoundConstMemberFunctor<void, MemberBase, bool, int> voidBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunctionB2);
        voidBoundConstMemberBaseFunctorB(true, 2);
        CHECK("Member::voidConstFunctionB2" == *sg_memberString);
        QEXTBoundConstMemberFunctor<int, MemberBase, bool, int> intBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunctionB2);
        CHECK(1 == intBoundConstMemberBaseFunctorB(true, 2));
        CHECK(0 == intBoundConstMemberBaseFunctorB(false, 2));
        QEXTBoundConstMemberFunctor<double, MemberBase, bool, double> doubleBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunctionB2);
        CHECK(1 == doubleBoundConstMemberBaseFunctorB(true, 2.2));
        CHECK(0 == doubleBoundConstMemberBaseFunctorB(false, 2.2));
    }

    TEST(qextMemberFunctorTest, testBoundVolatileFunctorWith2Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTBoundVolatileMemberFunctor<void, MemberBase, int, int> voidBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunction2);
        voidBoundVolatileMemberBaseFunctor(1, 2);
        CHECK("MemberBase::voidVolatileFunction2" == *sg_memberString);
        QEXTBoundVolatileMemberFunctor<int, MemberBase, int, int> intBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunction2);
        CHECK(1 + 2 == intBoundVolatileMemberBaseFunctor(1, 2));
        QEXTBoundVolatileMemberFunctor<double, MemberBase, double, double> doubleBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunction2);
        CHECK(1.1 + 2.2 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2));

        QEXTBoundVolatileMemberFunctor<void, MemberBase, bool, int> voidBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunctionB2);
        voidBoundVolatileMemberBaseFunctorB(true, 2);
        CHECK("MemberBase::voidVolatileFunctionB2" == *sg_memberString);
        QEXTBoundVolatileMemberFunctor<int, MemberBase, bool, int> intBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunctionB2);
        CHECK(2 == intBoundVolatileMemberBaseFunctorB(true, 2));
        CHECK(0 == intBoundVolatileMemberBaseFunctorB(false, 2));
        QEXTBoundVolatileMemberFunctor<double, MemberBase, bool, double> doubleBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunctionB2);
        CHECK(2.2 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2));
        CHECK(0 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2));
    }

    TEST(qextMemberFunctorTest, testPolymorphismBoundVolatileFunctorWith2Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTBoundVolatileMemberFunctor<void, MemberBase, int, int> voidBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction2);
        voidBoundVolatileMemberBaseFunctor(1, 2);
        CHECK("Member::voidVolatileFunction2" == *sg_memberString);
        QEXTBoundVolatileMemberFunctor<int, MemberBase, int, int> intBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction2);
        CHECK(0 == intBoundVolatileMemberBaseFunctor(1, 2));
        QEXTBoundVolatileMemberFunctor<double, MemberBase, double, double> doubleBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction2);
        CHECK(0 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2));

        QEXTBoundVolatileMemberFunctor<void, MemberBase, bool, int> voidBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunctionB2);
        voidBoundVolatileMemberBaseFunctorB(true, 2);
        CHECK("Member::voidVolatileFunctionB2" == *sg_memberString);
        QEXTBoundVolatileMemberFunctor<int, MemberBase, bool, int> intBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunctionB2);
        CHECK(1 == intBoundVolatileMemberBaseFunctorB(true, 2));
        CHECK(0 == intBoundVolatileMemberBaseFunctorB(false, 2));
        QEXTBoundVolatileMemberFunctor<double, MemberBase, bool, double> doubleBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunctionB2);
        CHECK(1 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2));
        CHECK(0 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2));
    }

    TEST(qextMemberFunctorTest, testBoundConstVolatileFunctorWith2Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTBoundConstVolatileMemberFunctor<void, MemberBase, int, int> voidBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunction2);
        voidBoundConstVolatileMemberBaseFunctor(1, 2);
        CHECK("MemberBase::voidConstVolatileFunction2" == *sg_memberString);
        QEXTBoundConstVolatileMemberFunctor<int, MemberBase, int, int> intBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunction2);
        CHECK(1 + 2 == intBoundConstVolatileMemberBaseFunctor(1, 2));
        QEXTBoundConstVolatileMemberFunctor<double, MemberBase, double, double> doubleBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction2);
        CHECK(1.1 + 2.2 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2));

        QEXTBoundConstVolatileMemberFunctor<void, MemberBase, bool, int> voidBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunctionB2);
        voidBoundConstVolatileMemberBaseFunctorB(true, 2);
        CHECK("MemberBase::voidConstVolatileFunctionB2" == *sg_memberString);
        QEXTBoundConstVolatileMemberFunctor<int, MemberBase, bool, int> intBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunctionB2);
        CHECK(2 == intBoundConstVolatileMemberBaseFunctorB(true, 2));
        CHECK(0 == intBoundConstVolatileMemberBaseFunctorB(false, 2));
        QEXTBoundConstVolatileMemberFunctor<double, MemberBase, bool, double> doubleBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunctionB2);
        CHECK(2.2 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2));
        CHECK(0 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2));
    }

    TEST(qextMemberFunctorTest, testPolymorphismBoundConstVolatileFunctorWith2Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTBoundConstVolatileMemberFunctor<void, MemberBase, int, int> voidBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction2);
        voidBoundConstVolatileMemberBaseFunctor(1, 2);
        CHECK("Member::voidConstVolatileFunction2" == *sg_memberString);
        QEXTBoundConstVolatileMemberFunctor<int, MemberBase, int, int> intBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction2);
        CHECK(0 == intBoundConstVolatileMemberBaseFunctor(1, 2));
        QEXTBoundConstVolatileMemberFunctor<double, MemberBase, double, double> doubleBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction2);
        CHECK(0 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2));

        QEXTBoundConstVolatileMemberFunctor<void, MemberBase, bool, int> voidBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunctionB2);
        voidBoundConstVolatileMemberBaseFunctorB(true, 2);
        CHECK("Member::voidConstVolatileFunctionB2" == *sg_memberString);
        QEXTBoundConstVolatileMemberFunctor<int, MemberBase, bool, int> intBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunctionB2);
        CHECK(1 == intBoundConstVolatileMemberBaseFunctorB(true, 2));
        CHECK(0 == intBoundConstVolatileMemberBaseFunctorB(false, 2));
        QEXTBoundConstVolatileMemberFunctor<double, MemberBase, bool, double> doubleBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunctionB2);
        CHECK(1 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2));
        CHECK(0 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2));
    }

    TEST(qextMemberFunctorTest, testFunctorWith3Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTMemberFunctor<void, MemberBase, int, int, int> voidMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidFunction3);
        voidMemberBaseFunctor(&memberBase, 1, 2, 3);
        CHECK("MemberBase::voidFunction3" == *sg_memberString);
        QEXTMemberFunctor<int, MemberBase, int, int, int> intMemberBaseFunctor = qextMemberFunctor(&MemberBase::intFunction3);
        CHECK(1 + 2 + 3 == intMemberBaseFunctor(&memberBase, 1, 2, 3));
        QEXTMemberFunctor<double, MemberBase, double, double, double> doubleMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleFunction3);
        CHECK(1.1 + 2.2 + 3.3 == doubleMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3));

        QEXTMemberFunctor<void, MemberBase, bool, int, int> voidMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidFunctionB3);
        voidMemberBaseFunctorB(&memberBase, true, 2, 3);
        CHECK("MemberBase::voidFunctionB3" == *sg_memberString);
        QEXTMemberFunctor<int, MemberBase, bool, int, int> intMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intFunctionB3);
        CHECK(2 + 3 == intMemberBaseFunctorB(&memberBase, true, 2, 3));
        CHECK(2 * 3 == intMemberBaseFunctorB(&memberBase, false, 2, 3));
        QEXTMemberFunctor<double, MemberBase, bool, double, double> doubleMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleFunctionB3);
        CHECK(2.2 + 3.3 == doubleMemberBaseFunctorB(&memberBase, true, 2.2, 3.3));
        CHECK(2.2 * 3.3 == doubleMemberBaseFunctorB(&memberBase, false, 2.2, 3.3));
    }

    TEST(qextMemberFunctorTest, testPolymorphismFunctorWith3Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTMemberFunctor<void, MemberBase, int, int, int> voidMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidFunction3);
        voidMemberBaseFunctor(&member, 1, 2, 3);
        CHECK("Member::voidFunction3" == *sg_memberString);
        QEXTMemberFunctor<int, MemberBase, int, int, int> intMemberBaseFunctor = qextMemberFunctor(&MemberBase::intFunction3);
        CHECK(0 == intMemberBaseFunctor(&member, 1, 2, 3));
        QEXTMemberFunctor<double, MemberBase, double, double, double> doubleMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleFunction3);
        CHECK(0 == doubleMemberBaseFunctor(&member, 1.1, 2.2, 3.3));

        QEXTMemberFunctor<void, MemberBase, bool, int, int> voidMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidFunctionB3);
        voidMemberBaseFunctorB(&member, true, 2, 3);
        CHECK("Member::voidFunctionB3" == *sg_memberString);
        QEXTMemberFunctor<int, MemberBase, bool, int, int> intMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intFunctionB3);
        CHECK(1 == intMemberBaseFunctorB(&member, true, 2, 3));
        CHECK(0 == intMemberBaseFunctorB(&member, false, 2, 3));
        QEXTMemberFunctor<double, MemberBase, bool, double, double> doubleMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleFunctionB3);
        CHECK(1 == doubleMemberBaseFunctorB(&member, true, 2.2, 3.3));
        CHECK(0 == doubleMemberBaseFunctorB(&member, false, 2.2, 3.3));
    }

    TEST(qextMemberFunctorTest, testConstFunctorWith3Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTConstMemberFunctor<void, MemberBase, int, int, int> voidConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstFunction3);
        voidConstMemberBaseFunctor(&memberBase, 1, 2, 3);
        CHECK("MemberBase::voidConstFunction3" == *sg_memberString);
        QEXTConstMemberFunctor<int, MemberBase, int, int, int> intConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstFunction3);
        CHECK(1 + 2 + 3 == intConstMemberBaseFunctor(&memberBase, 1, 2, 3));
        QEXTConstMemberFunctor<double, MemberBase, double, double, double> doubleConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstFunction3);
        CHECK(1.1 + 2.2 + 3.3 == doubleConstMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3));

        QEXTConstMemberFunctor<void, MemberBase, bool, int, int> voidConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstFunctionB3);
        voidConstMemberBaseFunctorB(&memberBase, true, 2, 3);
        CHECK("MemberBase::voidConstFunctionB3" == *sg_memberString);
        QEXTConstMemberFunctor<int, MemberBase, bool, int, int> intConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstFunctionB3);
        CHECK(2 + 3 == intConstMemberBaseFunctorB(&memberBase, true, 2, 3));
        CHECK(2 * 3 == intConstMemberBaseFunctorB(&memberBase, false, 2, 3));
        QEXTConstMemberFunctor<double, MemberBase, bool, double, double> doubleConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstFunctionB3);
        CHECK(2.2 + 3.3 == doubleConstMemberBaseFunctorB(&memberBase, true, 2.2, 3.3));
        CHECK(2.2 * 3.3 == doubleConstMemberBaseFunctorB(&memberBase, false, 2.2, 3.3));
    }

    TEST(qextMemberFunctorTest, testPolymorphismConstFunctorWith3Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTConstMemberFunctor<void, MemberBase, int, int, int> voidConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstFunction3);
        voidConstMemberBaseFunctor(&member, 1, 2, 3);
        CHECK("Member::voidConstFunction3" == *sg_memberString);
        QEXTConstMemberFunctor<int, MemberBase, int, int, int> intConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstFunction3);
        CHECK(0 == intConstMemberBaseFunctor(&member, 1, 2, 3));
        QEXTConstMemberFunctor<double, MemberBase, double, double, double> doubleConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstFunction3);
        CHECK(0 == doubleConstMemberBaseFunctor(&member, 1.1, 2.2, 3.3));

        QEXTConstMemberFunctor<void, MemberBase, bool, int, int> voidConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstFunctionB3);
        voidConstMemberBaseFunctorB(&member, true, 2, 3);
        CHECK("Member::voidConstFunctionB3" == *sg_memberString);
        QEXTConstMemberFunctor<int, MemberBase, bool, int, int> intConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstFunctionB3);
        CHECK(1 == intConstMemberBaseFunctorB(&member, true, 2, 3));
        CHECK(0 == intConstMemberBaseFunctorB(&member, false, 2, 3));
        QEXTConstMemberFunctor<double, MemberBase, bool, double, double> doubleConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstFunctionB3);
        CHECK(1 == doubleConstMemberBaseFunctorB(&member, true, 2.2, 3.3));
        CHECK(0 == doubleConstMemberBaseFunctorB(&member, false, 2.2, 3.3));
    }

    TEST(qextMemberFunctorTest, testVolatileFunctorWith3Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTVolatileMemberFunctor<void, MemberBase, int, int, int> voidVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidVolatileFunction3);
        voidVolatileMemberBaseFunctor(&memberBase, 1, 2, 3);
        CHECK("MemberBase::voidVolatileFunction3" == *sg_memberString);
        QEXTVolatileMemberFunctor<int, MemberBase, int, int, int> intVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intVolatileFunction3);
        CHECK(1 + 2 + 3 == intVolatileMemberBaseFunctor(&memberBase, 1, 2, 3));
        QEXTVolatileMemberFunctor<double, MemberBase, double, double, double> doubleVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleVolatileFunction3);
        CHECK(1.1 + 2.2 + 3.3 == doubleVolatileMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3));

        QEXTVolatileMemberFunctor<void, MemberBase, bool, int, int> voidVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidVolatileFunctionB3);
        voidVolatileMemberBaseFunctorB(&memberBase, true, 2, 3);
        CHECK("MemberBase::voidVolatileFunctionB3" == *sg_memberString);
        QEXTVolatileMemberFunctor<int, MemberBase, bool, int, int> intVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intVolatileFunctionB3);
        CHECK(2 + 3 == intVolatileMemberBaseFunctorB(&memberBase, true, 2, 3));
        CHECK(2 * 3 == intVolatileMemberBaseFunctorB(&memberBase, false, 2, 3));
        QEXTVolatileMemberFunctor<double, MemberBase, bool, double, double> doubleVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB3);
        CHECK(2.2 + 3.3 == doubleVolatileMemberBaseFunctorB(&memberBase, true, 2.2, 3.3));
        CHECK(2.2 * 3.3 == doubleVolatileMemberBaseFunctorB(&memberBase, false, 2.2, 3.3));
    }

    TEST(qextMemberFunctorTest, testPolymorphismVolatileFunctorWith3Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTVolatileMemberFunctor<void, MemberBase, int, int, int> voidVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidVolatileFunction3);
        voidVolatileMemberBaseFunctor(&member, 1, 2, 3);
        CHECK("Member::voidVolatileFunction3" == *sg_memberString);
        QEXTVolatileMemberFunctor<int, MemberBase, int, int, int> intVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intVolatileFunction3);
        CHECK(0 == intVolatileMemberBaseFunctor(&member, 1, 2, 3));
        QEXTVolatileMemberFunctor<double, MemberBase, double, double, double> doubleVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleVolatileFunction3);
        CHECK(0 == doubleVolatileMemberBaseFunctor(&member, 1.1, 2.2, 3.3));

        QEXTVolatileMemberFunctor<void, MemberBase, bool, int, int> voidVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidVolatileFunctionB3);
        voidVolatileMemberBaseFunctorB(&member, true, 2, 3);
        CHECK("Member::voidVolatileFunctionB3" == *sg_memberString);
        QEXTVolatileMemberFunctor<int, MemberBase, bool, int, int> intVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intVolatileFunctionB3);
        CHECK(1 == intVolatileMemberBaseFunctorB(&member, true, 2, 3));
        CHECK(0 == intVolatileMemberBaseFunctorB(&member, false, 2, 3));
        QEXTVolatileMemberFunctor<double, MemberBase, bool, double, double> doubleVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB3);
        CHECK(1 == doubleVolatileMemberBaseFunctorB(&member, true, 2.2, 3.3));
        CHECK(0 == doubleVolatileMemberBaseFunctorB(&member, false, 2.2, 3.3));
    }

    TEST(qextMemberFunctorTest, testConstVolatileFunctorWith3Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTConstVolatileMemberFunctor<void, MemberBase, int, int, int> voidConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstVolatileFunction3);
        voidConstVolatileMemberBaseFunctor(&memberBase, 1, 2, 3);
        CHECK("MemberBase::voidConstVolatileFunction3" == *sg_memberString);
        QEXTConstVolatileMemberFunctor<int, MemberBase, int, int, int> intConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstVolatileFunction3);
        CHECK(1 + 2 + 3 == intConstVolatileMemberBaseFunctor(&memberBase, 1, 2, 3));
        QEXTConstVolatileMemberFunctor<double, MemberBase, double, double, double> doubleConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction3);
        CHECK(1.1 + 2.2 + 3.3 == doubleConstVolatileMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3));

        QEXTConstVolatileMemberFunctor<void, MemberBase, bool, int, int> voidConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB3);
        voidConstVolatileMemberBaseFunctorB(&memberBase, true, 2, 3);
        CHECK("MemberBase::voidConstVolatileFunctionB3" == *sg_memberString);
        QEXTConstVolatileMemberFunctor<int, MemberBase, bool, int, int> intConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB3);
        CHECK(2 + 3 == intConstVolatileMemberBaseFunctorB(&memberBase, true, 2, 3));
        CHECK(2 * 3 == intConstVolatileMemberBaseFunctorB(&memberBase, false, 2, 3));
        QEXTConstVolatileMemberFunctor<double, MemberBase, bool, double, double> doubleConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB3);
        CHECK(2.2 + 3.3 == doubleConstVolatileMemberBaseFunctorB(&memberBase, true, 2.2, 3.3));
        CHECK(2.2 * 3.3 == doubleConstVolatileMemberBaseFunctorB(&memberBase, false, 2.2, 3.3));
    }

    TEST(qextMemberFunctorTest, testPolymorphismConstVolatileFunctorWith3Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTConstVolatileMemberFunctor<void, MemberBase, int, int, int> voidConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstVolatileFunction3);
        voidConstVolatileMemberBaseFunctor(&member, 1, 2, 3);
        CHECK("Member::voidConstVolatileFunction3" == *sg_memberString);
        QEXTConstVolatileMemberFunctor<int, MemberBase, int, int, int> intConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstVolatileFunction3);
        CHECK(0 == intConstVolatileMemberBaseFunctor(&member, 1, 2, 3));
        QEXTConstVolatileMemberFunctor<double, MemberBase, double, double, double> doubleConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction3);
        CHECK(0 == doubleConstVolatileMemberBaseFunctor(&member, 1.1, 2.2, 3.3));

        QEXTConstVolatileMemberFunctor<void, MemberBase, bool, int, int> voidConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB3);
        voidConstVolatileMemberBaseFunctorB(&member, true, 2, 3);
        CHECK("Member::voidConstVolatileFunctionB3" == *sg_memberString);
        QEXTConstVolatileMemberFunctor<int, MemberBase, bool, int, int> intConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB3);
        CHECK(1 == intConstVolatileMemberBaseFunctorB(&member, true, 2, 3));
        CHECK(0 == intConstVolatileMemberBaseFunctorB(&member, false, 2, 3));
        QEXTConstVolatileMemberFunctor<double, MemberBase, bool, double, double> doubleConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB3);
        CHECK(1 == doubleConstVolatileMemberBaseFunctorB(&member, true, 2.2, 3.3));
        CHECK(0 == doubleConstVolatileMemberBaseFunctorB(&member, false, 2.2, 3.3));
    }

    TEST(qextMemberFunctorTest, testBoundFunctorWith3Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTBoundMemberFunctor<void, MemberBase, int, int, int> voidBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidFunction3);
        voidBoundMemberBaseFunctor(1, 2, 3);
        CHECK("MemberBase::voidFunction3" == *sg_memberString);
        QEXTBoundMemberFunctor<int, MemberBase, int, int, int> intBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intFunction3);
        CHECK(1 + 2 + 3 == intBoundMemberBaseFunctor(1, 2, 3));
        QEXTBoundMemberFunctor<double, MemberBase, double, double, double> doubleBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleFunction3);
        CHECK(1.1 + 2.2 + 3.3 == doubleBoundMemberBaseFunctor(1.1, 2.2, 3.3));

        QEXTBoundMemberFunctor<void, MemberBase, bool, int, int> voidBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidFunctionB3);
        voidBoundMemberBaseFunctorB(true, 2, 3);
        CHECK("MemberBase::voidFunctionB3" == *sg_memberString);
        QEXTBoundMemberFunctor<int, MemberBase, bool, int, int> intBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intFunctionB3);
        CHECK(2 + 3 == intBoundMemberBaseFunctorB(true, 2, 3));
        CHECK(2 * 3 == intBoundMemberBaseFunctorB(false, 2, 3));
        QEXTBoundMemberFunctor<double, MemberBase, bool, double, double> doubleBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleFunctionB3);
        CHECK(2.2 + 3.3 == doubleBoundMemberBaseFunctorB(true, 2.2, 3.3));
        CHECK(2.2 * 3.3 == doubleBoundMemberBaseFunctorB(false, 2.2, 3.3));
    }

    TEST(qextMemberFunctorTest, testPolymorphismBoundFunctorWith3Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTBoundMemberFunctor<void, MemberBase, int, int, int> voidBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction3);
        voidBoundMemberBaseFunctor(1, 2, 3);
        CHECK("Member::voidFunction3" == *sg_memberString);
        QEXTBoundMemberFunctor<int, MemberBase, int, int, int> intBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction3);
        CHECK(0 == intBoundMemberBaseFunctor(1, 2, 3));
        QEXTBoundMemberFunctor<double, MemberBase, double, double, double> doubleBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction3);
        CHECK(0 == doubleBoundMemberBaseFunctor(1.1, 2.2, 3.3));

        QEXTBoundMemberFunctor<void, MemberBase, bool, int, int> voidBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunctionB3);
        voidBoundMemberBaseFunctorB(true, 2, 3);
        CHECK("Member::voidFunctionB3" == *sg_memberString);
        QEXTBoundMemberFunctor<int, MemberBase, bool, int, int> intBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunctionB3);
        CHECK(1 == intBoundMemberBaseFunctorB(true, 2, 3));
        CHECK(0 == intBoundMemberBaseFunctorB(false, 2, 3));
        QEXTBoundMemberFunctor<double, MemberBase, bool, double, double> doubleBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunctionB3);
        CHECK(1 == doubleBoundMemberBaseFunctorB(true, 2.2, 3.3));
        CHECK(0 == doubleBoundMemberBaseFunctorB(false, 2.2, 3.3));
    }

    TEST(qextMemberFunctorTest, testBoundConstFunctorWith3Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTBoundConstMemberFunctor<void, MemberBase, int, int, int> voidBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunction3);
        voidBoundConstMemberBaseFunctor(1, 2, 3);
        CHECK("MemberBase::voidConstFunction3" == *sg_memberString);
        QEXTBoundConstMemberFunctor<int, MemberBase, int, int, int> intBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intConstFunction3);
        CHECK(1 + 2 + 3 == intBoundConstMemberBaseFunctor(1, 2, 3));
        QEXTBoundConstMemberFunctor<double, MemberBase, double, double, double> doubleBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunction3);
        CHECK(1.1 + 2.2 + 3.3 == doubleBoundConstMemberBaseFunctor(1.1, 2.2, 3.3));

        QEXTBoundConstMemberFunctor<void, MemberBase, bool, int, int> voidBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunctionB3);
        voidBoundConstMemberBaseFunctorB(true, 2, 3);
        CHECK("MemberBase::voidConstFunctionB3" == *sg_memberString);
        QEXTBoundConstMemberFunctor<int, MemberBase, bool, int, int> intBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intConstFunctionB3);
        CHECK(2 + 3 == intBoundConstMemberBaseFunctorB(true, 2, 3));
        CHECK(2 * 3 == intBoundConstMemberBaseFunctorB(false, 2, 3));
        QEXTBoundConstMemberFunctor<double, MemberBase, bool, double, double> doubleBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunctionB3);
        CHECK(2.2 + 3.3 == doubleBoundConstMemberBaseFunctorB(true, 2.2, 3.3));
        CHECK(2.2 * 3.3 == doubleBoundConstMemberBaseFunctorB(false, 2.2, 3.3));
    }

    TEST(qextMemberFunctorTest, testPolymorphismBoundConstFunctorWith3Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTBoundConstMemberFunctor<void, MemberBase, int, int, int> voidBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction3);
        voidBoundConstMemberBaseFunctor(1, 2, 3);
        CHECK("Member::voidConstFunction3" == *sg_memberString);
        QEXTBoundConstMemberFunctor<int, MemberBase, int, int, int> intBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction3);
        CHECK(0 == intBoundConstMemberBaseFunctor(1, 2, 3));
        QEXTBoundConstMemberFunctor<double, MemberBase, double, double, double> doubleBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction3);
        CHECK(0 == doubleBoundConstMemberBaseFunctor(1.1, 2.2, 3.3));

        QEXTBoundConstMemberFunctor<void, MemberBase, bool, int, int> voidBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunctionB3);
        voidBoundConstMemberBaseFunctorB(true, 2, 3);
        CHECK("Member::voidConstFunctionB3" == *sg_memberString);
        QEXTBoundConstMemberFunctor<int, MemberBase, bool, int, int> intBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunctionB3);
        CHECK(1 == intBoundConstMemberBaseFunctorB(true, 2, 3));
        CHECK(0 == intBoundConstMemberBaseFunctorB(false, 2, 3));
        QEXTBoundConstMemberFunctor<double, MemberBase, bool, double, double> doubleBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunctionB3);
        CHECK(1 == doubleBoundConstMemberBaseFunctorB(true, 2.2, 3.3));
        CHECK(0 == doubleBoundConstMemberBaseFunctorB(false, 2.2, 3.3));
    }

    TEST(qextMemberFunctorTest, testBoundVolatileFunctorWith3Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTBoundVolatileMemberFunctor<void, MemberBase, int, int, int> voidBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunction3);
        voidBoundVolatileMemberBaseFunctor(1, 2, 3);
        CHECK("MemberBase::voidVolatileFunction3" == *sg_memberString);
        QEXTBoundVolatileMemberFunctor<int, MemberBase, int, int, int> intBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunction3);
        CHECK(1 + 2 + 3 == intBoundVolatileMemberBaseFunctor(1, 2, 3));
        QEXTBoundVolatileMemberFunctor<double, MemberBase, double, double, double> doubleBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunction3);
        CHECK(1.1 + 2.2 + 3.3 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2, 3.3));

        QEXTBoundVolatileMemberFunctor<void, MemberBase, bool, int, int> voidBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunctionB3);
        voidBoundVolatileMemberBaseFunctorB(true, 2, 3);
        CHECK("MemberBase::voidVolatileFunctionB3" == *sg_memberString);
        QEXTBoundVolatileMemberFunctor<int, MemberBase, bool, int, int> intBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunctionB3);
        CHECK(2 + 3 == intBoundVolatileMemberBaseFunctorB(true, 2, 3));
        CHECK(2 * 3 == intBoundVolatileMemberBaseFunctorB(false, 2, 3));
        QEXTBoundVolatileMemberFunctor<double, MemberBase, bool, double, double> doubleBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunctionB3);
        CHECK(2.2 + 3.3 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2, 3.3));
        CHECK(2.2 * 3.3 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2, 3.3));
    }

    TEST(qextMemberFunctorTest, testPolymorphismBoundVolatileFunctorWith3Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTBoundVolatileMemberFunctor<void, MemberBase, int, int, int> voidBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction3);
        voidBoundVolatileMemberBaseFunctor(1, 2, 3);
        CHECK("Member::voidVolatileFunction3" == *sg_memberString);
        QEXTBoundVolatileMemberFunctor<int, MemberBase, int, int, int> intBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction3);
        CHECK(0 == intBoundVolatileMemberBaseFunctor(1, 2, 3));
        QEXTBoundVolatileMemberFunctor<double, MemberBase, double, double, double> doubleBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction3);
        CHECK(0 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2, 3.3));

        QEXTBoundVolatileMemberFunctor<void, MemberBase, bool, int, int> voidBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunctionB3);
        voidBoundVolatileMemberBaseFunctorB(true, 2, 3);
        CHECK("Member::voidVolatileFunctionB3" == *sg_memberString);
        QEXTBoundVolatileMemberFunctor<int, MemberBase, bool, int, int> intBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunctionB3);
        CHECK(1 == intBoundVolatileMemberBaseFunctorB(true, 2, 3));
        CHECK(0 == intBoundVolatileMemberBaseFunctorB(false, 2, 3));
        QEXTBoundVolatileMemberFunctor<double, MemberBase, bool, double, double> doubleBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunctionB3);
        CHECK(1 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2, 3.3));
        CHECK(0 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2, 3.3));
    }

    TEST(qextMemberFunctorTest, testBoundConstVolatileFunctorWith3Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTBoundConstVolatileMemberFunctor<void, MemberBase, int, int, int> voidBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunction3);
        voidBoundConstVolatileMemberBaseFunctor(1, 2, 3);
        CHECK("MemberBase::voidConstVolatileFunction3" == *sg_memberString);
        QEXTBoundConstVolatileMemberFunctor<int, MemberBase, int, int, int> intBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunction3);
        CHECK(1 + 2 + 3 == intBoundConstVolatileMemberBaseFunctor(1, 2, 3));
        QEXTBoundConstVolatileMemberFunctor<double, MemberBase, double, double, double> doubleBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction3);
        CHECK(1.1 + 2.2 + 3.3 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2, 3.3));

        QEXTBoundConstVolatileMemberFunctor<void, MemberBase, bool, int, int> voidBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunctionB3);
        voidBoundConstVolatileMemberBaseFunctorB(true, 2, 3);
        CHECK("MemberBase::voidConstVolatileFunctionB3" == *sg_memberString);
        QEXTBoundConstVolatileMemberFunctor<int, MemberBase, bool, int, int> intBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunctionB3);
        CHECK(2 + 3 == intBoundConstVolatileMemberBaseFunctorB(true, 2, 3));
        CHECK(2 * 3 == intBoundConstVolatileMemberBaseFunctorB(false, 2, 3));
        QEXTBoundConstVolatileMemberFunctor<double, MemberBase, bool, double, double> doubleBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunctionB3);
        CHECK(2.2 + 3.3 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2, 3.3));
        CHECK(2.2 * 3.3 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2, 3.3));
    }

    TEST(qextMemberFunctorTest, testPolymorphismBoundConstVolatileFunctorWith3Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTBoundConstVolatileMemberFunctor<void, MemberBase, int, int, int> voidBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction3);
        voidBoundConstVolatileMemberBaseFunctor(1, 2, 3);
        CHECK("Member::voidConstVolatileFunction3" == *sg_memberString);
        QEXTBoundConstVolatileMemberFunctor<int, MemberBase, int, int, int> intBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction3);
        CHECK(0 == intBoundConstVolatileMemberBaseFunctor(1, 2, 3));
        QEXTBoundConstVolatileMemberFunctor<double, MemberBase, double, double, double> doubleBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction3);
        CHECK(0 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2, 3.3));

        QEXTBoundConstVolatileMemberFunctor<void, MemberBase, bool, int, int> voidBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunctionB3);
        voidBoundConstVolatileMemberBaseFunctorB(true, 2, 3);
        CHECK("Member::voidConstVolatileFunctionB3" == *sg_memberString);
        QEXTBoundConstVolatileMemberFunctor<int, MemberBase, bool, int, int> intBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunctionB3);
        CHECK(1 == intBoundConstVolatileMemberBaseFunctorB(true, 2, 3));
        CHECK(0 == intBoundConstVolatileMemberBaseFunctorB(false, 2, 3));
        QEXTBoundConstVolatileMemberFunctor<double, MemberBase, bool, double, double> doubleBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunctionB3);
        CHECK(1 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2, 3.3));
        CHECK(0 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2, 3.3));
    }

    TEST(qextMemberFunctorTest, testFunctorWith4Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTMemberFunctor<void, MemberBase, int, int, int, int> voidMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidFunction4);
        voidMemberBaseFunctor(&memberBase, 1, 2, 3, 4);
        CHECK("MemberBase::voidFunction4" == *sg_memberString);
        QEXTMemberFunctor<int, MemberBase, int, int, int, int> intMemberBaseFunctor = qextMemberFunctor(&MemberBase::intFunction4);
        CHECK(1 + 2 + 3 + 4 == intMemberBaseFunctor(&memberBase, 1, 2, 3, 4));
        QEXTMemberFunctor<double, MemberBase, double, double, double, double> doubleMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleFunction4);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 == doubleMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3, 4.4));

        QEXTMemberFunctor<void, MemberBase, bool, int, int, int> voidMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidFunctionB4);
        voidMemberBaseFunctorB(&memberBase, true, 2, 3, 4);
        CHECK("MemberBase::voidFunctionB4" == *sg_memberString);
        QEXTMemberFunctor<int, MemberBase, bool, int, int, int> intMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intFunctionB4);
        CHECK(2 + 3 + 4 == intMemberBaseFunctorB(&memberBase, true, 2, 3, 4));
        CHECK(2 * 3 * 4 == intMemberBaseFunctorB(&memberBase, false, 2, 3, 4));
        QEXTMemberFunctor<double, MemberBase, bool, double, double, double> doubleMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleFunctionB4);
        CHECK(2.2 + 3.3 + 4.4 == doubleMemberBaseFunctorB(&memberBase, true, 2.2, 3.3, 4.4));
        CHECK(2.2 * 3.3 * 4.4 == doubleMemberBaseFunctorB(&memberBase, false, 2.2, 3.3, 4.4));
    }

    TEST(qextMemberFunctorTest, testPolymorphismFunctorWith4Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTMemberFunctor<void, MemberBase, int, int, int, int> voidMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidFunction4);
        voidMemberBaseFunctor(&member, 1, 2, 3, 4);
        CHECK("Member::voidFunction4" == *sg_memberString);
        QEXTMemberFunctor<int, MemberBase, int, int, int, int> intMemberBaseFunctor = qextMemberFunctor(&MemberBase::intFunction4);
        CHECK(0 == intMemberBaseFunctor(&member, 1, 2, 3, 4));
        QEXTMemberFunctor<double, MemberBase, double, double, double, double> doubleMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleFunction4);
        CHECK(0 == doubleMemberBaseFunctor(&member, 1.1, 2.2, 3.3, 4.4));

        QEXTMemberFunctor<void, MemberBase, bool, int, int, int> voidMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidFunctionB4);
        voidMemberBaseFunctorB(&member, true, 2, 3, 4);
        CHECK("Member::voidFunctionB4" == *sg_memberString);
        QEXTMemberFunctor<int, MemberBase, bool, int, int, int> intMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intFunctionB4);
        CHECK(1 == intMemberBaseFunctorB(&member, true, 2, 3, 4));
        CHECK(0 == intMemberBaseFunctorB(&member, false, 2, 3, 4));
        QEXTMemberFunctor<double, MemberBase, bool, double, double, double> doubleMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleFunctionB4);
        CHECK(1 == doubleMemberBaseFunctorB(&member, true, 2.2, 3.3, 4.4));
        CHECK(0 == doubleMemberBaseFunctorB(&member, false, 2.2, 3.3, 4.4));
    }

    TEST(qextMemberFunctorTest, testConstFunctorWith4Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTConstMemberFunctor<void, MemberBase, int, int, int, int> voidConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstFunction4);
        voidConstMemberBaseFunctor(&memberBase, 1, 2, 3, 4);
        CHECK("MemberBase::voidConstFunction4" == *sg_memberString);
        QEXTConstMemberFunctor<int, MemberBase, int, int, int, int> intConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstFunction4);
        CHECK(1 + 2 + 3 + 4 == intConstMemberBaseFunctor(&memberBase, 1, 2, 3, 4));
        QEXTConstMemberFunctor<double, MemberBase, double, double, double, double> doubleConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstFunction4);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 == doubleConstMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3, 4.4));

        QEXTConstMemberFunctor<void, MemberBase, bool, int, int, int> voidConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstFunctionB4);
        voidConstMemberBaseFunctorB(&memberBase, true, 2, 3, 4);
        CHECK("MemberBase::voidConstFunctionB4" == *sg_memberString);
        QEXTConstMemberFunctor<int, MemberBase, bool, int, int, int> intConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstFunctionB4);
        CHECK(2 + 3 + 4 == intConstMemberBaseFunctorB(&memberBase, true, 2, 3, 4));
        CHECK(2 * 3 * 4 == intConstMemberBaseFunctorB(&memberBase, false, 2, 3, 4));
        QEXTConstMemberFunctor<double, MemberBase, bool, double, double, double> doubleConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstFunctionB4);
        CHECK(2.2 + 3.3 + 4.4 == doubleConstMemberBaseFunctorB(&memberBase, true, 2.2, 3.3, 4.4));
        CHECK(2.2 * 3.3 * 4.4 == doubleConstMemberBaseFunctorB(&memberBase, false, 2.2, 3.3, 4.4));
    }

    TEST(qextMemberFunctorTest, testPolymorphismConstFunctorWith4Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTConstMemberFunctor<void, MemberBase, int, int, int, int> voidConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstFunction4);
        voidConstMemberBaseFunctor(&member, 1, 2, 3, 4);
        CHECK("Member::voidConstFunction4" == *sg_memberString);
        QEXTConstMemberFunctor<int, MemberBase, int, int, int, int> intConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstFunction4);
        CHECK(0 == intConstMemberBaseFunctor(&member, 1, 2, 3, 4));
        QEXTConstMemberFunctor<double, MemberBase, double, double, double, double> doubleConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstFunction4);
        CHECK(0 == doubleConstMemberBaseFunctor(&member, 1.1, 2.2, 3.3, 4.4));

        QEXTConstMemberFunctor<void, MemberBase, bool, int, int, int> voidConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstFunctionB4);
        voidConstMemberBaseFunctorB(&member, true, 2, 3, 4);
        CHECK("Member::voidConstFunctionB4" == *sg_memberString);
        QEXTConstMemberFunctor<int, MemberBase, bool, int, int, int> intConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstFunctionB4);
        CHECK(1 == intConstMemberBaseFunctorB(&member, true, 2, 3, 4));
        CHECK(0 == intConstMemberBaseFunctorB(&member, false, 2, 3, 4));
        QEXTConstMemberFunctor<double, MemberBase, bool, double, double, double> doubleConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstFunctionB4);
        CHECK(1 == doubleConstMemberBaseFunctorB(&member, true, 2.2, 3.3, 4.4));
        CHECK(0 == doubleConstMemberBaseFunctorB(&member, false, 2.2, 3.3, 4.4));
    }

    TEST(qextMemberFunctorTest, testVolatileFunctorWith4Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTVolatileMemberFunctor<void, MemberBase, int, int, int, int> voidVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidVolatileFunction4);
        voidVolatileMemberBaseFunctor(&memberBase, 1, 2, 3, 4);
        CHECK("MemberBase::voidVolatileFunction4" == *sg_memberString);
        QEXTVolatileMemberFunctor<int, MemberBase, int, int, int, int> intVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intVolatileFunction4);
        CHECK(1 + 2 + 3 + 4 == intVolatileMemberBaseFunctor(&memberBase, 1, 2, 3, 4));
        QEXTVolatileMemberFunctor<double, MemberBase, double, double, double, double> doubleVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleVolatileFunction4);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 == doubleVolatileMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3, 4.4));

        QEXTVolatileMemberFunctor<void, MemberBase, bool, int, int, int> voidVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidVolatileFunctionB4);
        voidVolatileMemberBaseFunctorB(&memberBase, true, 2, 3, 4);
        CHECK("MemberBase::voidVolatileFunctionB4" == *sg_memberString);
        QEXTVolatileMemberFunctor<int, MemberBase, bool, int, int, int> intVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intVolatileFunctionB4);
        CHECK(2 + 3 + 4 == intVolatileMemberBaseFunctorB(&memberBase, true, 2, 3, 4));
        CHECK(2 * 3 * 4 == intVolatileMemberBaseFunctorB(&memberBase, false, 2, 3, 4));
        QEXTVolatileMemberFunctor<double, MemberBase, bool, double, double, double> doubleVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB4);
        CHECK(2.2 + 3.3 + 4.4 == doubleVolatileMemberBaseFunctorB(&memberBase, true, 2.2, 3.3, 4.4));
        CHECK(2.2 * 3.3 * 4.4 == doubleVolatileMemberBaseFunctorB(&memberBase, false, 2.2, 3.3, 4.4));
    }

    TEST(qextMemberFunctorTest, testPolymorphismVolatileFunctorWith4Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTVolatileMemberFunctor<void, MemberBase, int, int, int, int> voidVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidVolatileFunction4);
        voidVolatileMemberBaseFunctor(&member, 1, 2, 3, 4);
        CHECK("Member::voidVolatileFunction4" == *sg_memberString);
        QEXTVolatileMemberFunctor<int, MemberBase, int, int, int, int> intVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intVolatileFunction4);
        CHECK(0 == intVolatileMemberBaseFunctor(&member, 1, 2, 3, 4));
        QEXTVolatileMemberFunctor<double, MemberBase, double, double, double, double> doubleVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleVolatileFunction4);
        CHECK(0 == doubleVolatileMemberBaseFunctor(&member, 1.1, 2.2, 3.3, 4.4));

        QEXTVolatileMemberFunctor<void, MemberBase, bool, int, int, int> voidVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidVolatileFunctionB4);
        voidVolatileMemberBaseFunctorB(&member, true, 2, 3, 4);
        CHECK("Member::voidVolatileFunctionB4" == *sg_memberString);
        QEXTVolatileMemberFunctor<int, MemberBase, bool, int, int, int> intVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intVolatileFunctionB4);
        CHECK(1 == intVolatileMemberBaseFunctorB(&member, true, 2, 3, 4));
        CHECK(0 == intVolatileMemberBaseFunctorB(&member, false, 2, 3, 4));
        QEXTVolatileMemberFunctor<double, MemberBase, bool, double, double, double> doubleVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB4);
        CHECK(1 == doubleVolatileMemberBaseFunctorB(&member, true, 2.2, 3.3, 4.4));
        CHECK(0 == doubleVolatileMemberBaseFunctorB(&member, false, 2.2, 3.3, 4.4));
    }

    TEST(qextMemberFunctorTest, testConstVolatileFunctorWith4Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTConstVolatileMemberFunctor<void, MemberBase, int, int, int, int> voidConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstVolatileFunction4);
        voidConstVolatileMemberBaseFunctor(&memberBase, 1, 2, 3, 4);
        CHECK("MemberBase::voidConstVolatileFunction4" == *sg_memberString);
        QEXTConstVolatileMemberFunctor<int, MemberBase, int, int, int, int> intConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstVolatileFunction4);
        CHECK(1 + 2 + 3 + 4 == intConstVolatileMemberBaseFunctor(&memberBase, 1, 2, 3, 4));
        QEXTConstVolatileMemberFunctor<double, MemberBase, double, double, double, double> doubleConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction4);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 == doubleConstVolatileMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3, 4.4));

        QEXTConstVolatileMemberFunctor<void, MemberBase, bool, int, int, int> voidConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB4);
        voidConstVolatileMemberBaseFunctorB(&memberBase, true, 2, 3, 4);
        CHECK("MemberBase::voidConstVolatileFunctionB4" == *sg_memberString);
        QEXTConstVolatileMemberFunctor<int, MemberBase, bool, int, int, int> intConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB4);
        CHECK(2 + 3 + 4 == intConstVolatileMemberBaseFunctorB(&memberBase, true, 2, 3, 4));
        CHECK(2 * 3 * 4 == intConstVolatileMemberBaseFunctorB(&memberBase, false, 2, 3, 4));
        QEXTConstVolatileMemberFunctor<double, MemberBase, bool, double, double, double> doubleConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB4);
        CHECK(2.2 + 3.3 + 4.4 == doubleConstVolatileMemberBaseFunctorB(&memberBase, true, 2.2, 3.3, 4.4));
        CHECK(2.2 * 3.3 * 4.4 == doubleConstVolatileMemberBaseFunctorB(&memberBase, false, 2.2, 3.3, 4.4));
    }

    TEST(qextMemberFunctorTest, testPolymorphismConstVolatileFunctorWith4Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTConstVolatileMemberFunctor<void, MemberBase, int, int, int, int> voidConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstVolatileFunction4);
        voidConstVolatileMemberBaseFunctor(&member, 1, 2, 3, 4);
        CHECK("Member::voidConstVolatileFunction4" == *sg_memberString);
        QEXTConstVolatileMemberFunctor<int, MemberBase, int, int, int, int> intConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstVolatileFunction4);
        CHECK(0 == intConstVolatileMemberBaseFunctor(&member, 1, 2, 3, 4));
        QEXTConstVolatileMemberFunctor<double, MemberBase, double, double, double, double> doubleConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction4);
        CHECK(0 == doubleConstVolatileMemberBaseFunctor(&member, 1.1, 2.2, 3.3, 4.4));

        QEXTConstVolatileMemberFunctor<void, MemberBase, bool, int, int, int> voidConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB4);
        voidConstVolatileMemberBaseFunctorB(&member, true, 2, 3, 4);
        CHECK("Member::voidConstVolatileFunctionB4" == *sg_memberString);
        QEXTConstVolatileMemberFunctor<int, MemberBase, bool, int, int, int> intConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB4);
        CHECK(1 == intConstVolatileMemberBaseFunctorB(&member, true, 2, 3, 4));
        CHECK(0 == intConstVolatileMemberBaseFunctorB(&member, false, 2, 3, 4));
        QEXTConstVolatileMemberFunctor<double, MemberBase, bool, double, double, double> doubleConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB4);
        CHECK(1 == doubleConstVolatileMemberBaseFunctorB(&member, true, 2.2, 3.3, 4.4));
        CHECK(0 == doubleConstVolatileMemberBaseFunctorB(&member, false, 2.2, 3.3, 4.4));
    }

    TEST(qextMemberFunctorTest, testBoundFunctorWith4Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTBoundMemberFunctor<void, MemberBase, int, int, int, int> voidBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidFunction4);
        voidBoundMemberBaseFunctor(1, 2, 3, 4);
        CHECK("MemberBase::voidFunction4" == *sg_memberString);
        QEXTBoundMemberFunctor<int, MemberBase, int, int, int, int> intBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intFunction4);
        CHECK(1 + 2 + 3 + 4 == intBoundMemberBaseFunctor(1, 2, 3, 4));
        QEXTBoundMemberFunctor<double, MemberBase, double, double, double, double> doubleBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleFunction4);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 == doubleBoundMemberBaseFunctor(1.1, 2.2, 3.3, 4.4));

        QEXTBoundMemberFunctor<void, MemberBase, bool, int, int, int> voidBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidFunctionB4);
        voidBoundMemberBaseFunctorB(true, 2, 3, 4);
        CHECK("MemberBase::voidFunctionB4" == *sg_memberString);
        QEXTBoundMemberFunctor<int, MemberBase, bool, int, int, int> intBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intFunctionB4);
        CHECK(2 + 3 + 4 == intBoundMemberBaseFunctorB(true, 2, 3, 4));
        CHECK(2 * 3 * 4 == intBoundMemberBaseFunctorB(false, 2, 3, 4));
        QEXTBoundMemberFunctor<double, MemberBase, bool, double, double, double> doubleBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleFunctionB4);
        CHECK(2.2 + 3.3 + 4.4 == doubleBoundMemberBaseFunctorB(true, 2.2, 3.3, 4.4));
        CHECK(2.2 * 3.3 * 4.4 == doubleBoundMemberBaseFunctorB(false, 2.2, 3.3, 4.4));
    }

    TEST(qextMemberFunctorTest, testPolymorphismBoundFunctorWith4Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTBoundMemberFunctor<void, MemberBase, int, int, int, int> voidBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction4);
        voidBoundMemberBaseFunctor(1, 2, 3, 4);
        CHECK("Member::voidFunction4" == *sg_memberString);
        QEXTBoundMemberFunctor<int, MemberBase, int, int, int, int> intBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction4);
        CHECK(0 == intBoundMemberBaseFunctor(1, 2, 3, 4));
        QEXTBoundMemberFunctor<double, MemberBase, double, double, double, double> doubleBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction4);
        CHECK(0 == doubleBoundMemberBaseFunctor(1.1, 2.2, 3.3, 4.4));

        QEXTBoundMemberFunctor<void, MemberBase, bool, int, int, int> voidBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunctionB4);
        voidBoundMemberBaseFunctorB(true, 2, 3, 4);
        CHECK("Member::voidFunctionB4" == *sg_memberString);
        QEXTBoundMemberFunctor<int, MemberBase, bool, int, int, int> intBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunctionB4);
        CHECK(1 == intBoundMemberBaseFunctorB(true, 2, 3, 4));
        CHECK(0 == intBoundMemberBaseFunctorB(false, 2, 3, 4));
        QEXTBoundMemberFunctor<double, MemberBase, bool, double, double, double> doubleBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunctionB4);
        CHECK(1 == doubleBoundMemberBaseFunctorB(true, 2.2, 3.3, 4.4));
        CHECK(0 == doubleBoundMemberBaseFunctorB(false, 2.2, 3.3, 4.4));
    }

    TEST(qextMemberFunctorTest, testBoundConstFunctorWith4Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTBoundConstMemberFunctor<void, MemberBase, int, int, int, int> voidBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunction4);
        voidBoundConstMemberBaseFunctor(1, 2, 3, 4);
        CHECK("MemberBase::voidConstFunction4" == *sg_memberString);
        QEXTBoundConstMemberFunctor<int, MemberBase, int, int, int, int> intBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intConstFunction4);
        CHECK(1 + 2 + 3 + 4 == intBoundConstMemberBaseFunctor(1, 2, 3, 4));
        QEXTBoundConstMemberFunctor<double, MemberBase, double, double, double, double> doubleBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunction4);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 == doubleBoundConstMemberBaseFunctor(1.1, 2.2, 3.3, 4.4));

        QEXTBoundConstMemberFunctor<void, MemberBase, bool, int, int, int> voidBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunctionB4);
        voidBoundConstMemberBaseFunctorB(true, 2, 3, 4);
        CHECK("MemberBase::voidConstFunctionB4" == *sg_memberString);
        QEXTBoundConstMemberFunctor<int, MemberBase, bool, int, int, int> intBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intConstFunctionB4);
        CHECK(2 + 3 + 4 == intBoundConstMemberBaseFunctorB(true, 2, 3, 4));
        CHECK(2 * 3 * 4 == intBoundConstMemberBaseFunctorB(false, 2, 3, 4));
        QEXTBoundConstMemberFunctor<double, MemberBase, bool, double, double, double> doubleBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunctionB4);
        CHECK(2.2 + 3.3 + 4.4 == doubleBoundConstMemberBaseFunctorB(true, 2.2, 3.3, 4.4));
        CHECK(2.2 * 3.3 * 4.4 == doubleBoundConstMemberBaseFunctorB(false, 2.2, 3.3, 4.4));
    }

    TEST(qextMemberFunctorTest, testPolymorphismBoundConstFunctorWith4Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTBoundConstMemberFunctor<void, MemberBase, int, int, int, int> voidBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction4);
        voidBoundConstMemberBaseFunctor(1, 2, 3, 4);
        CHECK("Member::voidConstFunction4" == *sg_memberString);
        QEXTBoundConstMemberFunctor<int, MemberBase, int, int, int, int> intBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction4);
        CHECK(0 == intBoundConstMemberBaseFunctor(1, 2, 3, 4));
        QEXTBoundConstMemberFunctor<double, MemberBase, double, double, double, double> doubleBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction4);
        CHECK(0 == doubleBoundConstMemberBaseFunctor(1.1, 2.2, 3.3, 4.4));

        QEXTBoundConstMemberFunctor<void, MemberBase, bool, int, int, int> voidBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunctionB4);
        voidBoundConstMemberBaseFunctorB(true, 2, 3, 4);
        CHECK("Member::voidConstFunctionB4" == *sg_memberString);
        QEXTBoundConstMemberFunctor<int, MemberBase, bool, int, int, int> intBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunctionB4);
        CHECK(1 == intBoundConstMemberBaseFunctorB(true, 2, 3, 4));
        CHECK(0 == intBoundConstMemberBaseFunctorB(false, 2, 3, 4));
        QEXTBoundConstMemberFunctor<double, MemberBase, bool, double, double, double> doubleBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunctionB4);
        CHECK(1 == doubleBoundConstMemberBaseFunctorB(true, 2.2, 3.3, 4.4));
        CHECK(0 == doubleBoundConstMemberBaseFunctorB(false, 2.2, 3.3, 4.4));
    }

    TEST(qextMemberFunctorTest, testBoundVolatileFunctorWith4Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTBoundVolatileMemberFunctor<void, MemberBase, int, int, int, int> voidBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunction4);
        voidBoundVolatileMemberBaseFunctor(1, 2, 3, 4);
        CHECK("MemberBase::voidVolatileFunction4" == *sg_memberString);
        QEXTBoundVolatileMemberFunctor<int, MemberBase, int, int, int, int> intBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunction4);
        CHECK(1 + 2 + 3 + 4 == intBoundVolatileMemberBaseFunctor(1, 2, 3, 4));
        QEXTBoundVolatileMemberFunctor<double, MemberBase, double, double, double, double> doubleBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunction4);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4));

        QEXTBoundVolatileMemberFunctor<void, MemberBase, bool, int, int, int> voidBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunctionB4);
        voidBoundVolatileMemberBaseFunctorB(true, 2, 3, 4);
        CHECK("MemberBase::voidVolatileFunctionB4" == *sg_memberString);
        QEXTBoundVolatileMemberFunctor<int, MemberBase, bool, int, int, int> intBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunctionB4);
        CHECK(2 + 3 + 4 == intBoundVolatileMemberBaseFunctorB(true, 2, 3, 4));
        CHECK(2 * 3 * 4 == intBoundVolatileMemberBaseFunctorB(false, 2, 3, 4));
        QEXTBoundVolatileMemberFunctor<double, MemberBase, bool, double, double, double> doubleBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunctionB4);
        CHECK(2.2 + 3.3 + 4.4 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4));
        CHECK(2.2 * 3.3 * 4.4 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4));
    }

    TEST(qextMemberFunctorTest, testPolymorphismBoundVolatileFunctorWith4Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTBoundVolatileMemberFunctor<void, MemberBase, int, int, int, int> voidBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction4);
        voidBoundVolatileMemberBaseFunctor(1, 2, 3, 4);
        CHECK("Member::voidVolatileFunction4" == *sg_memberString);
        QEXTBoundVolatileMemberFunctor<int, MemberBase, int, int, int, int> intBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction4);
        CHECK(0 == intBoundVolatileMemberBaseFunctor(1, 2, 3, 4));
        QEXTBoundVolatileMemberFunctor<double, MemberBase, double, double, double, double> doubleBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction4);
        CHECK(0 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4));

        QEXTBoundVolatileMemberFunctor<void, MemberBase, bool, int, int, int> voidBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunctionB4);
        voidBoundVolatileMemberBaseFunctorB(true, 2, 3, 4);
        CHECK("Member::voidVolatileFunctionB4" == *sg_memberString);
        QEXTBoundVolatileMemberFunctor<int, MemberBase, bool, int, int, int> intBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunctionB4);
        CHECK(1 == intBoundVolatileMemberBaseFunctorB(true, 2, 3, 4));
        CHECK(0 == intBoundVolatileMemberBaseFunctorB(false, 2, 3, 4));
        QEXTBoundVolatileMemberFunctor<double, MemberBase, bool, double, double, double> doubleBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunctionB4);
        CHECK(1 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4));
        CHECK(0 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4));
    }

    TEST(qextMemberFunctorTest, testBoundConstVolatileFunctorWith4Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTBoundConstVolatileMemberFunctor<void, MemberBase, int, int, int, int> voidBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunction4);
        voidBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4);
        CHECK("MemberBase::voidConstVolatileFunction4" == *sg_memberString);
        QEXTBoundConstVolatileMemberFunctor<int, MemberBase, int, int, int, int> intBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunction4);
        CHECK(1 + 2 + 3 + 4 == intBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4));
        QEXTBoundConstVolatileMemberFunctor<double, MemberBase, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction4);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4));

        QEXTBoundConstVolatileMemberFunctor<void, MemberBase, bool, int, int, int> voidBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunctionB4);
        voidBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4);
        CHECK("MemberBase::voidConstVolatileFunctionB4" == *sg_memberString);
        QEXTBoundConstVolatileMemberFunctor<int, MemberBase, bool, int, int, int> intBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunctionB4);
        CHECK(2 + 3 + 4 == intBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4));
        CHECK(2 * 3 * 4 == intBoundConstVolatileMemberBaseFunctorB(false, 2, 3, 4));
        QEXTBoundConstVolatileMemberFunctor<double, MemberBase, bool, double, double, double> doubleBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunctionB4);
        CHECK(2.2 + 3.3 + 4.4 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4));
        CHECK(2.2 * 3.3 * 4.4 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4));
    }

    TEST(qextMemberFunctorTest, testPolymorphismBoundConstVolatileFunctorWith4Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTBoundConstVolatileMemberFunctor<void, MemberBase, int, int, int, int> voidBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction4);
        voidBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4);
        CHECK("Member::voidConstVolatileFunction4" == *sg_memberString);
        QEXTBoundConstVolatileMemberFunctor<int, MemberBase, int, int, int, int> intBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction4);
        CHECK(0 == intBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4));
        QEXTBoundConstVolatileMemberFunctor<double, MemberBase, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction4);
        CHECK(0 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4));

        QEXTBoundConstVolatileMemberFunctor<void, MemberBase, bool, int, int, int> voidBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunctionB4);
        voidBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4);
        CHECK("Member::voidConstVolatileFunctionB4" == *sg_memberString);
        QEXTBoundConstVolatileMemberFunctor<int, MemberBase, bool, int, int, int> intBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunctionB4);
        CHECK(1 == intBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4));
        CHECK(0 == intBoundConstVolatileMemberBaseFunctorB(false, 2, 3, 4));
        QEXTBoundConstVolatileMemberFunctor<double, MemberBase, bool, double, double, double> doubleBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunctionB4);
        CHECK(1 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4));
        CHECK(0 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4));
    }

    TEST(qextMemberFunctorTest, testFunctorWith5Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTMemberFunctor<void, MemberBase, int, int, int, int, int> voidMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidFunction5);
        voidMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5);
        CHECK("MemberBase::voidFunction5" == *sg_memberString);
        QEXTMemberFunctor<int, MemberBase, int, int, int, int, int> intMemberBaseFunctor = qextMemberFunctor(&MemberBase::intFunction5);
        CHECK(1 + 2 + 3 + 4 + 5 == intMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5));
        QEXTMemberFunctor<double, MemberBase, double, double, double, double, double> doubleMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleFunction5);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5));

        QEXTMemberFunctor<void, MemberBase, bool, int, int, int, int> voidMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidFunctionB5);
        voidMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5);
        CHECK("MemberBase::voidFunctionB5" == *sg_memberString);
        QEXTMemberFunctor<int, MemberBase, bool, int, int, int, int> intMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intFunctionB5);
        CHECK(2 + 3 + 4 + 5 == intMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5));
        CHECK(2 * 3 * 4 * 5 == intMemberBaseFunctorB(&memberBase, false, 2, 3, 4, 5));
        QEXTMemberFunctor<double, MemberBase, bool, double, double, double, double> doubleMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleFunctionB5);
        CHECK(2.2 + 3.3 + 4.4 + 5.5 == doubleMemberBaseFunctorB(&memberBase, true, 2.2, 3.3, 4.4, 5.5));
        CHECK(2.2 * 3.3 * 4.4 * 5.5 == doubleMemberBaseFunctorB(&memberBase, false, 2.2, 3.3, 4.4, 5.5));
    }

    TEST(qextMemberFunctorTest, testPolymorphismFunctorWith5Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTMemberFunctor<void, MemberBase, int, int, int, int, int> voidMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidFunction5);
        voidMemberBaseFunctor(&member, 1, 2, 3, 4, 5);
        CHECK("Member::voidFunction5" == *sg_memberString);
        QEXTMemberFunctor<int, MemberBase, int, int, int, int, int> intMemberBaseFunctor = qextMemberFunctor(&MemberBase::intFunction5);
        CHECK(0 == intMemberBaseFunctor(&member, 1, 2, 3, 4, 5));
        QEXTMemberFunctor<double, MemberBase, double, double, double, double, double> doubleMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleFunction5);
        CHECK(0 == doubleMemberBaseFunctor(&member, 1.1, 2.2, 3.3, 4.4, 5.5));

        QEXTMemberFunctor<void, MemberBase, bool, int, int, int, int> voidMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidFunctionB5);
        voidMemberBaseFunctorB(&member, true, 2, 3, 4, 5);
        CHECK("Member::voidFunctionB5" == *sg_memberString);
        QEXTMemberFunctor<int, MemberBase, bool, int, int, int, int> intMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intFunctionB5);
        CHECK(1 == intMemberBaseFunctorB(&member, true, 2, 3, 4, 5));
        CHECK(0 == intMemberBaseFunctorB(&member, false, 2, 3, 4, 5));
        QEXTMemberFunctor<double, MemberBase, bool, double, double, double, double> doubleMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleFunctionB5);
        CHECK(1 == doubleMemberBaseFunctorB(&member, true, 2.2, 3.3, 4.4, 5.5));
        CHECK(0 == doubleMemberBaseFunctorB(&member, false, 2.2, 3.3, 4.4, 5.5));
    }

    TEST(qextMemberFunctorTest, testConstFunctorWith5Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTConstMemberFunctor<void, MemberBase, int, int, int, int, int> voidConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstFunction5);
        voidConstMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5);
        CHECK("MemberBase::voidConstFunction5" == *sg_memberString);
        QEXTConstMemberFunctor<int, MemberBase, int, int, int, int, int> intConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstFunction5);
        CHECK(1 + 2 + 3 + 4 + 5 == intConstMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5));
        QEXTConstMemberFunctor<double, MemberBase, double, double, double, double, double> doubleConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstFunction5);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleConstMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5));

        QEXTConstMemberFunctor<void, MemberBase, bool, int, int, int, int> voidConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstFunctionB5);
        voidConstMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5);
        CHECK("MemberBase::voidConstFunctionB5" == *sg_memberString);
        QEXTConstMemberFunctor<int, MemberBase, bool, int, int, int, int> intConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstFunctionB5);
        CHECK(2 + 3 + 4 + 5 == intConstMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5));
        CHECK(2 * 3 * 4 * 5 == intConstMemberBaseFunctorB(&memberBase, false, 2, 3, 4, 5));
        QEXTConstMemberFunctor<double, MemberBase, bool, double, double, double, double> doubleConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstFunctionB5);
        CHECK(2.2 + 3.3 + 4.4 + 5.5 == doubleConstMemberBaseFunctorB(&memberBase, true, 2.2, 3.3, 4.4, 5.5));
        CHECK(2.2 * 3.3 * 4.4 * 5.5 == doubleConstMemberBaseFunctorB(&memberBase, false, 2.2, 3.3, 4.4, 5.5));
    }

    TEST(qextMemberFunctorTest, testPolymorphismConstFunctorWith5Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTConstMemberFunctor<void, MemberBase, int, int, int, int, int> voidConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstFunction5);
        voidConstMemberBaseFunctor(&member, 1, 2, 3, 4, 5);
        CHECK("Member::voidConstFunction5" == *sg_memberString);
        QEXTConstMemberFunctor<int, MemberBase, int, int, int, int, int> intConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstFunction5);
        CHECK(0 == intConstMemberBaseFunctor(&member, 1, 2, 3, 4, 5));
        QEXTConstMemberFunctor<double, MemberBase, double, double, double, double, double> doubleConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstFunction5);
        CHECK(0 == doubleConstMemberBaseFunctor(&member, 1.1, 2.2, 3.3, 4.4, 5.5));

        QEXTConstMemberFunctor<void, MemberBase, bool, int, int, int, int> voidConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstFunctionB5);
        voidConstMemberBaseFunctorB(&member, true, 2, 3, 4, 5);
        CHECK("Member::voidConstFunctionB5" == *sg_memberString);
        QEXTConstMemberFunctor<int, MemberBase, bool, int, int, int, int> intConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstFunctionB5);
        CHECK(1 == intConstMemberBaseFunctorB(&member, true, 2, 3, 4, 5));
        CHECK(0 == intConstMemberBaseFunctorB(&member, false, 2, 3, 4, 5));
        QEXTConstMemberFunctor<double, MemberBase, bool, double, double, double, double> doubleConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstFunctionB5);
        CHECK(1 == doubleConstMemberBaseFunctorB(&member, true, 2.2, 3.3, 4.4, 5.5));
        CHECK(0 == doubleConstMemberBaseFunctorB(&member, false, 2.2, 3.3, 4.4, 5.5));
    }

    TEST(qextMemberFunctorTest, testVolatileFunctorWith5Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTVolatileMemberFunctor<void, MemberBase, int, int, int, int, int> voidVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidVolatileFunction5);
        voidVolatileMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5);
        CHECK("MemberBase::voidVolatileFunction5" == *sg_memberString);
        QEXTVolatileMemberFunctor<int, MemberBase, int, int, int, int, int> intVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intVolatileFunction5);
        CHECK(1 + 2 + 3 + 4 + 5 == intVolatileMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5));
        QEXTVolatileMemberFunctor<double, MemberBase, double, double, double, double, double> doubleVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleVolatileFunction5);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleVolatileMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5));

        QEXTVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int> voidVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidVolatileFunctionB5);
        voidVolatileMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5);
        CHECK("MemberBase::voidVolatileFunctionB5" == *sg_memberString);
        QEXTVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int> intVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intVolatileFunctionB5);
        CHECK(2 + 3 + 4 + 5 == intVolatileMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5));
        CHECK(2 * 3 * 4 * 5 == intVolatileMemberBaseFunctorB(&memberBase, false, 2, 3, 4, 5));
        QEXTVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double> doubleVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB5);
        CHECK(2.2 + 3.3 + 4.4 + 5.5 == doubleVolatileMemberBaseFunctorB(&memberBase, true, 2.2, 3.3, 4.4, 5.5));
        CHECK(2.2 * 3.3 * 4.4 * 5.5 == doubleVolatileMemberBaseFunctorB(&memberBase, false, 2.2, 3.3, 4.4, 5.5));
    }

    TEST(qextMemberFunctorTest, testPolymorphismVolatileFunctorWith5Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTVolatileMemberFunctor<void, MemberBase, int, int, int, int, int> voidVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidVolatileFunction5);
        voidVolatileMemberBaseFunctor(&member, 1, 2, 3, 4, 5);
        CHECK("Member::voidVolatileFunction5" == *sg_memberString);
        QEXTVolatileMemberFunctor<int, MemberBase, int, int, int, int, int> intVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intVolatileFunction5);
        CHECK(0 == intVolatileMemberBaseFunctor(&member, 1, 2, 3, 4, 5));
        QEXTVolatileMemberFunctor<double, MemberBase, double, double, double, double, double> doubleVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleVolatileFunction5);
        CHECK(0 == doubleVolatileMemberBaseFunctor(&member, 1.1, 2.2, 3.3, 4.4, 5.5));

        QEXTVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int> voidVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidVolatileFunctionB5);
        voidVolatileMemberBaseFunctorB(&member, true, 2, 3, 4, 5);
        CHECK("Member::voidVolatileFunctionB5" == *sg_memberString);
        QEXTVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int> intVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intVolatileFunctionB5);
        CHECK(1 == intVolatileMemberBaseFunctorB(&member, true, 2, 3, 4, 5));
        CHECK(0 == intVolatileMemberBaseFunctorB(&member, false, 2, 3, 4, 5));
        QEXTVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double> doubleVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB5);
        CHECK(1 == doubleVolatileMemberBaseFunctorB(&member, true, 2.2, 3.3, 4.4, 5.5));
        CHECK(0 == doubleVolatileMemberBaseFunctorB(&member, false, 2.2, 3.3, 4.4, 5.5));
    }

    TEST(qextMemberFunctorTest, testConstVolatileFunctorWith5Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTConstVolatileMemberFunctor<void, MemberBase, int, int, int, int, int> voidConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstVolatileFunction5);
        voidConstVolatileMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5);
        CHECK("MemberBase::voidConstVolatileFunction5" == *sg_memberString);
        QEXTConstVolatileMemberFunctor<int, MemberBase, int, int, int, int, int> intConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstVolatileFunction5);
        CHECK(1 + 2 + 3 + 4 + 5 == intConstVolatileMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5));
        QEXTConstVolatileMemberFunctor<double, MemberBase, double, double, double, double, double> doubleConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction5);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleConstVolatileMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5));

        QEXTConstVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int> voidConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB5);
        voidConstVolatileMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5);
        CHECK("MemberBase::voidConstVolatileFunctionB5" == *sg_memberString);
        QEXTConstVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int> intConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB5);
        CHECK(2 + 3 + 4 + 5 == intConstVolatileMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5));
        CHECK(2 * 3 * 4 * 5 == intConstVolatileMemberBaseFunctorB(&memberBase, false, 2, 3, 4, 5));
        QEXTConstVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double> doubleConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB5);
        CHECK(2.2 + 3.3 + 4.4 + 5.5 == doubleConstVolatileMemberBaseFunctorB(&memberBase, true, 2.2, 3.3, 4.4, 5.5));
        CHECK(2.2 * 3.3 * 4.4 * 5.5 == doubleConstVolatileMemberBaseFunctorB(&memberBase, false, 2.2, 3.3, 4.4, 5.5));
    }

    TEST(qextMemberFunctorTest, testPolymorphismConstVolatileFunctorWith5Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTConstVolatileMemberFunctor<void, MemberBase, int, int, int, int, int> voidConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstVolatileFunction5);
        voidConstVolatileMemberBaseFunctor(&member, 1, 2, 3, 4, 5);
        CHECK("Member::voidConstVolatileFunction5" == *sg_memberString);
        QEXTConstVolatileMemberFunctor<int, MemberBase, int, int, int, int, int> intConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstVolatileFunction5);
        CHECK(0 == intConstVolatileMemberBaseFunctor(&member, 1, 2, 3, 4, 5));
        QEXTConstVolatileMemberFunctor<double, MemberBase, double, double, double, double, double> doubleConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction5);
        CHECK(0 == doubleConstVolatileMemberBaseFunctor(&member, 1.1, 2.2, 3.3, 4.4, 5.5));

        QEXTConstVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int> voidConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB5);
        voidConstVolatileMemberBaseFunctorB(&member, true, 2, 3, 4, 5);
        CHECK("Member::voidConstVolatileFunctionB5" == *sg_memberString);
        QEXTConstVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int> intConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB5);
        CHECK(1 == intConstVolatileMemberBaseFunctorB(&member, true, 2, 3, 4, 5));
        CHECK(0 == intConstVolatileMemberBaseFunctorB(&member, false, 2, 3, 4, 5));
        QEXTConstVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double> doubleConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB5);
        CHECK(1 == doubleConstVolatileMemberBaseFunctorB(&member, true, 2.2, 3.3, 4.4, 5.5));
        CHECK(0 == doubleConstVolatileMemberBaseFunctorB(&member, false, 2.2, 3.3, 4.4, 5.5));
    }

    TEST(qextMemberFunctorTest, testBoundFunctorWith5Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTBoundMemberFunctor<void, MemberBase, int, int, int, int, int> voidBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidFunction5);
        voidBoundMemberBaseFunctor(1, 2, 3, 4, 5);
        CHECK("MemberBase::voidFunction5" == *sg_memberString);
        QEXTBoundMemberFunctor<int, MemberBase, int, int, int, int, int> intBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intFunction5);
        CHECK(1 + 2 + 3 + 4 + 5 == intBoundMemberBaseFunctor(1, 2, 3, 4, 5));
        QEXTBoundMemberFunctor<double, MemberBase, double, double, double, double, double> doubleBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleFunction5);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleBoundMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5));

        QEXTBoundMemberFunctor<void, MemberBase, bool, int, int, int, int> voidBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidFunctionB5);
        voidBoundMemberBaseFunctorB(true, 2, 3, 4, 5);
        CHECK("MemberBase::voidFunctionB5" == *sg_memberString);
        QEXTBoundMemberFunctor<int, MemberBase, bool, int, int, int, int> intBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intFunctionB5);
        CHECK(2 + 3 + 4 + 5 == intBoundMemberBaseFunctorB(true, 2, 3, 4, 5));
        CHECK(2 * 3 * 4 * 5 == intBoundMemberBaseFunctorB(false, 2, 3, 4, 5));
        QEXTBoundMemberFunctor<double, MemberBase, bool, double, double, double, double> doubleBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleFunctionB5);
        CHECK(2.2 + 3.3 + 4.4 + 5.5 == doubleBoundMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5));
        CHECK(2.2 * 3.3 * 4.4 * 5.5 == doubleBoundMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5));
    }

    TEST(qextMemberFunctorTest, testPolymorphismBoundFunctorWith5Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTBoundMemberFunctor<void, MemberBase, int, int, int, int, int> voidBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction5);
        voidBoundMemberBaseFunctor(1, 2, 3, 4, 5);
        CHECK("Member::voidFunction5" == *sg_memberString);
        QEXTBoundMemberFunctor<int, MemberBase, int, int, int, int, int> intBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction5);
        CHECK(0 == intBoundMemberBaseFunctor(1, 2, 3, 4, 5));
        QEXTBoundMemberFunctor<double, MemberBase, double, double, double, double, double> doubleBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction5);
        CHECK(0 == doubleBoundMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5));

        QEXTBoundMemberFunctor<void, MemberBase, bool, int, int, int, int> voidBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunctionB5);
        voidBoundMemberBaseFunctorB(true, 2, 3, 4, 5);
        CHECK("Member::voidFunctionB5" == *sg_memberString);
        QEXTBoundMemberFunctor<int, MemberBase, bool, int, int, int, int> intBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunctionB5);
        CHECK(1 == intBoundMemberBaseFunctorB(true, 2, 3, 4, 5));
        CHECK(0 == intBoundMemberBaseFunctorB(false, 2, 3, 4, 5));
        QEXTBoundMemberFunctor<double, MemberBase, bool, double, double, double, double> doubleBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunctionB5);
        CHECK(1 == doubleBoundMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5));
        CHECK(0 == doubleBoundMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5));
    }

    TEST(qextMemberFunctorTest, testBoundConstFunctorWith5Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTBoundConstMemberFunctor<void, MemberBase, int, int, int, int, int> voidBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunction5);
        voidBoundConstMemberBaseFunctor(1, 2, 3, 4, 5);
        CHECK("MemberBase::voidConstFunction5" == *sg_memberString);
        QEXTBoundConstMemberFunctor<int, MemberBase, int, int, int, int, int> intBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intConstFunction5);
        CHECK(1 + 2 + 3 + 4 + 5 == intBoundConstMemberBaseFunctor(1, 2, 3, 4, 5));
        QEXTBoundConstMemberFunctor<double, MemberBase, double, double, double, double, double> doubleBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunction5);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleBoundConstMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5));

        QEXTBoundConstMemberFunctor<void, MemberBase, bool, int, int, int, int> voidBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunctionB5);
        voidBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5);
        CHECK("MemberBase::voidConstFunctionB5" == *sg_memberString);
        QEXTBoundConstMemberFunctor<int, MemberBase, bool, int, int, int, int> intBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intConstFunctionB5);
        CHECK(2 + 3 + 4 + 5 == intBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5));
        CHECK(2 * 3 * 4 * 5 == intBoundConstMemberBaseFunctorB(false, 2, 3, 4, 5));
        QEXTBoundConstMemberFunctor<double, MemberBase, bool, double, double, double, double> doubleBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunctionB5);
        CHECK(2.2 + 3.3 + 4.4 + 5.5 == doubleBoundConstMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5));
        CHECK(2.2 * 3.3 * 4.4 * 5.5 == doubleBoundConstMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5));
    }

    TEST(qextMemberFunctorTest, testPolymorphismBoundConstFunctorWith5Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTBoundConstMemberFunctor<void, MemberBase, int, int, int, int, int> voidBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction5);
        voidBoundConstMemberBaseFunctor(1, 2, 3, 4, 5);
        CHECK("Member::voidConstFunction5" == *sg_memberString);
        QEXTBoundConstMemberFunctor<int, MemberBase, int, int, int, int, int> intBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction5);
        CHECK(0 == intBoundConstMemberBaseFunctor(1, 2, 3, 4, 5));
        QEXTBoundConstMemberFunctor<double, MemberBase, double, double, double, double, double> doubleBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction5);
        CHECK(0 == doubleBoundConstMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5));

        QEXTBoundConstMemberFunctor<void, MemberBase, bool, int, int, int, int> voidBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunctionB5);
        voidBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5);
        CHECK("Member::voidConstFunctionB5" == *sg_memberString);
        QEXTBoundConstMemberFunctor<int, MemberBase, bool, int, int, int, int> intBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunctionB5);
        CHECK(1 == intBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5));
        CHECK(0 == intBoundConstMemberBaseFunctorB(false, 2, 3, 4, 5));
        QEXTBoundConstMemberFunctor<double, MemberBase, bool, double, double, double, double> doubleBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunctionB5);
        CHECK(1 == doubleBoundConstMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5));
        CHECK(0 == doubleBoundConstMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5));
    }

    TEST(qextMemberFunctorTest, testBoundVolatileFunctorWith5Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTBoundVolatileMemberFunctor<void, MemberBase, int, int, int, int, int> voidBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunction5);
        voidBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5);
        CHECK("MemberBase::voidVolatileFunction5" == *sg_memberString);
        QEXTBoundVolatileMemberFunctor<int, MemberBase, int, int, int, int, int> intBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunction5);
        CHECK(1 + 2 + 3 + 4 + 5 == intBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5));
        QEXTBoundVolatileMemberFunctor<double, MemberBase, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunction5);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5));

        QEXTBoundVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int> voidBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunctionB5);
        voidBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5);
        CHECK("MemberBase::voidVolatileFunctionB5" == *sg_memberString);
        QEXTBoundVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int> intBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunctionB5);
        CHECK(2 + 3 + 4 + 5 == intBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5));
        CHECK(2 * 3 * 4 * 5 == intBoundVolatileMemberBaseFunctorB(false, 2, 3, 4, 5));
        QEXTBoundVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double> doubleBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunctionB5);
        CHECK(2.2 + 3.3 + 4.4 + 5.5 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5));
        CHECK(2.2 * 3.3 * 4.4 * 5.5 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5));
    }

    TEST(qextMemberFunctorTest, testPolymorphismBoundVolatileFunctorWith5Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTBoundVolatileMemberFunctor<void, MemberBase, int, int, int, int, int> voidBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction5);
        voidBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5);
        CHECK("Member::voidVolatileFunction5" == *sg_memberString);
        QEXTBoundVolatileMemberFunctor<int, MemberBase, int, int, int, int, int> intBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction5);
        CHECK(0 == intBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5));
        QEXTBoundVolatileMemberFunctor<double, MemberBase, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction5);
        CHECK(0 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5));

        QEXTBoundVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int> voidBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunctionB5);
        voidBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5);
        CHECK("Member::voidVolatileFunctionB5" == *sg_memberString);
        QEXTBoundVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int> intBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunctionB5);
        CHECK(1 == intBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5));
        CHECK(0 == intBoundVolatileMemberBaseFunctorB(false, 2, 3, 4, 5));
        QEXTBoundVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double> doubleBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunctionB5);
        CHECK(1 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5));
        CHECK(0 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5));
    }

    TEST(qextMemberFunctorTest, testBoundConstVolatileFunctorWith5Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTBoundConstVolatileMemberFunctor<void, MemberBase, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunction5);
        voidBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5);
        CHECK("MemberBase::voidConstVolatileFunction5" == *sg_memberString);
        QEXTBoundConstVolatileMemberFunctor<int, MemberBase, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunction5);
        CHECK(1 + 2 + 3 + 4 + 5 == intBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5));
        QEXTBoundConstVolatileMemberFunctor<double, MemberBase, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction5);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5));

        QEXTBoundConstVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int> voidBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunctionB5);
        voidBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5);
        CHECK("MemberBase::voidConstVolatileFunctionB5" == *sg_memberString);
        QEXTBoundConstVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int> intBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunctionB5);
        CHECK(2 + 3 + 4 + 5 == intBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5));
        CHECK(2 * 3 * 4 * 5 == intBoundConstVolatileMemberBaseFunctorB(false, 2, 3, 4, 5));
        QEXTBoundConstVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunctionB5);
        CHECK(2.2 + 3.3 + 4.4 + 5.5 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5));
        CHECK(2.2 * 3.3 * 4.4 * 5.5 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5));
    }

    TEST(qextMemberFunctorTest, testPolymorphismBoundConstVolatileFunctorWith5Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTBoundConstVolatileMemberFunctor<void, MemberBase, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction5);
        voidBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5);
        CHECK("Member::voidConstVolatileFunction5" == *sg_memberString);
        QEXTBoundConstVolatileMemberFunctor<int, MemberBase, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction5);
        CHECK(0 == intBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5));
        QEXTBoundConstVolatileMemberFunctor<double, MemberBase, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction5);
        CHECK(0 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5));

        QEXTBoundConstVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int> voidBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunctionB5);
        voidBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5);
        CHECK("Member::voidConstVolatileFunctionB5" == *sg_memberString);
        QEXTBoundConstVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int> intBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunctionB5);
        CHECK(1 == intBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5));
        CHECK(0 == intBoundConstVolatileMemberBaseFunctorB(false, 2, 3, 4, 5));
        QEXTBoundConstVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunctionB5);
        CHECK(1 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5));
        CHECK(0 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5));
    }

    TEST(qextMemberFunctorTest, testFunctorWith6Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTMemberFunctor<void, MemberBase, int, int, int, int, int, int> voidMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidFunction6);
        voidMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5, 6);
        CHECK("MemberBase::voidFunction6" == *sg_memberString);
        QEXTMemberFunctor<int, MemberBase, int, int, int, int, int, int> intMemberBaseFunctor = qextMemberFunctor(&MemberBase::intFunction6);
        CHECK(1 + 2 + 3 + 4 + 5 + 6 == intMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5, 6));
        QEXTMemberFunctor<double, MemberBase, double, double, double, double, double, double> doubleMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleFunction6);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

        QEXTMemberFunctor<void, MemberBase, bool, int, int, int, int, int> voidMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidFunctionB6);
        voidMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5, 6);
        CHECK("MemberBase::voidFunctionB6" == *sg_memberString);
        QEXTMemberFunctor<int, MemberBase, bool, int, int, int, int, int> intMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intFunctionB6);
        CHECK(2 + 3 + 4 + 5 + 6 == intMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5, 6));
        CHECK(2 * 3 * 4 * 5 * 6 == intMemberBaseFunctorB(&memberBase, false, 2, 3, 4, 5, 6));
        QEXTMemberFunctor<double, MemberBase, bool, double, double, double, double, double> doubleMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleFunctionB6);
        CHECK(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleMemberBaseFunctorB(&memberBase, true, 2.2, 3.3, 4.4, 5.5, 6.6));
        CHECK(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleMemberBaseFunctorB(&memberBase, false, 2.2, 3.3, 4.4, 5.5, 6.6));
    }

    TEST(qextMemberFunctorTest, testPolymorphismFunctorWith6Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTMemberFunctor<void, MemberBase, int, int, int, int, int, int> voidMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidFunction6);
        voidMemberBaseFunctor(&member, 1, 2, 3, 4, 5, 6);
        CHECK("Member::voidFunction6" == *sg_memberString);
        QEXTMemberFunctor<int, MemberBase, int, int, int, int, int, int> intMemberBaseFunctor = qextMemberFunctor(&MemberBase::intFunction6);
        CHECK(0 == intMemberBaseFunctor(&member, 1, 2, 3, 4, 5, 6));
        QEXTMemberFunctor<double, MemberBase, double, double, double, double, double, double> doubleMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleFunction6);
        CHECK(0 == doubleMemberBaseFunctor(&member, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

        QEXTMemberFunctor<void, MemberBase, bool, int, int, int, int, int> voidMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidFunctionB6);
        voidMemberBaseFunctorB(&member, true, 2, 3, 4, 5, 6);
        CHECK("Member::voidFunctionB6" == *sg_memberString);
        QEXTMemberFunctor<int, MemberBase, bool, int, int, int, int, int> intMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intFunctionB6);
        CHECK(1 == intMemberBaseFunctorB(&member, true, 2, 3, 4, 5, 6));
        CHECK(0 == intMemberBaseFunctorB(&member, false, 2, 3, 4, 5, 6));
        QEXTMemberFunctor<double, MemberBase, bool, double, double, double, double, double> doubleMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleFunctionB6);
        CHECK(1 == doubleMemberBaseFunctorB(&member, true, 2.2, 3.3, 4.4, 5.5, 6.6));
        CHECK(0 == doubleMemberBaseFunctorB(&member, false, 2.2, 3.3, 4.4, 5.5, 6.6));
    }

    TEST(qextMemberFunctorTest, testConstFunctorWith6Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTConstMemberFunctor<void, MemberBase, int, int, int, int, int, int> voidConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstFunction6);
        voidConstMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5, 6);
        CHECK("MemberBase::voidConstFunction6" == *sg_memberString);
        QEXTConstMemberFunctor<int, MemberBase, int, int, int, int, int, int> intConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstFunction6);
        CHECK(1 + 2 + 3 + 4 + 5 + 6 == intConstMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5, 6));
        QEXTConstMemberFunctor<double, MemberBase, double, double, double, double, double, double> doubleConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstFunction6);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleConstMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

        QEXTConstMemberFunctor<void, MemberBase, bool, int, int, int, int, int> voidConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstFunctionB6);
        voidConstMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5, 6);
        CHECK("MemberBase::voidConstFunctionB6" == *sg_memberString);
        QEXTConstMemberFunctor<int, MemberBase, bool, int, int, int, int, int> intConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstFunctionB6);
        CHECK(2 + 3 + 4 + 5 + 6 == intConstMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5, 6));
        CHECK(2 * 3 * 4 * 5 * 6 == intConstMemberBaseFunctorB(&memberBase, false, 2, 3, 4, 5, 6));
        QEXTConstMemberFunctor<double, MemberBase, bool, double, double, double, double, double> doubleConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstFunctionB6);
        CHECK(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleConstMemberBaseFunctorB(&memberBase, true, 2.2, 3.3, 4.4, 5.5, 6.6));
        CHECK(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleConstMemberBaseFunctorB(&memberBase, false, 2.2, 3.3, 4.4, 5.5, 6.6));
    }

    TEST(qextMemberFunctorTest, testPolymorphismConstFunctorWith6Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTConstMemberFunctor<void, MemberBase, int, int, int, int, int, int> voidConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstFunction6);
        voidConstMemberBaseFunctor(&member, 1, 2, 3, 4, 5, 6);
        CHECK("Member::voidConstFunction6" == *sg_memberString);
        QEXTConstMemberFunctor<int, MemberBase, int, int, int, int, int, int> intConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstFunction6);
        CHECK(0 == intConstMemberBaseFunctor(&member, 1, 2, 3, 4, 5, 6));
        QEXTConstMemberFunctor<double, MemberBase, double, double, double, double, double, double> doubleConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstFunction6);
        CHECK(0 == doubleConstMemberBaseFunctor(&member, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

        QEXTConstMemberFunctor<void, MemberBase, bool, int, int, int, int, int> voidConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstFunctionB6);
        voidConstMemberBaseFunctorB(&member, true, 2, 3, 4, 5, 6);
        CHECK("Member::voidConstFunctionB6" == *sg_memberString);
        QEXTConstMemberFunctor<int, MemberBase, bool, int, int, int, int, int> intConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstFunctionB6);
        CHECK(1 == intConstMemberBaseFunctorB(&member, true, 2, 3, 4, 5, 6));
        CHECK(0 == intConstMemberBaseFunctorB(&member, false, 2, 3, 4, 5, 6));
        QEXTConstMemberFunctor<double, MemberBase, bool, double, double, double, double, double> doubleConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstFunctionB6);
        CHECK(1 == doubleConstMemberBaseFunctorB(&member, true, 2.2, 3.3, 4.4, 5.5, 6.6));
        CHECK(0 == doubleConstMemberBaseFunctorB(&member, false, 2.2, 3.3, 4.4, 5.5, 6.6));
    }

    TEST(qextMemberFunctorTest, testVolatileFunctorWith6Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTVolatileMemberFunctor<void, MemberBase, int, int, int, int, int, int> voidVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidVolatileFunction6);
        voidVolatileMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5, 6);
        CHECK("MemberBase::voidVolatileFunction6" == *sg_memberString);
        QEXTVolatileMemberFunctor<int, MemberBase, int, int, int, int, int, int> intVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intVolatileFunction6);
        CHECK(1 + 2 + 3 + 4 + 5 + 6 == intVolatileMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5, 6));
        QEXTVolatileMemberFunctor<double, MemberBase, double, double, double, double, double, double> doubleVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleVolatileFunction6);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleVolatileMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

        QEXTVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int, int> voidVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidVolatileFunctionB6);
        voidVolatileMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5, 6);
        CHECK("MemberBase::voidVolatileFunctionB6" == *sg_memberString);
        QEXTVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int, int> intVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intVolatileFunctionB6);
        CHECK(2 + 3 + 4 + 5 + 6 == intVolatileMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5, 6));
        CHECK(2 * 3 * 4 * 5 * 6 == intVolatileMemberBaseFunctorB(&memberBase, false, 2, 3, 4, 5, 6));
        QEXTVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double, double> doubleVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB6);
        CHECK(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleVolatileMemberBaseFunctorB(&memberBase, true, 2.2, 3.3, 4.4, 5.5, 6.6));
        CHECK(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleVolatileMemberBaseFunctorB(&memberBase, false, 2.2, 3.3, 4.4, 5.5, 6.6));
    }

    TEST(qextMemberFunctorTest, testPolymorphismVolatileFunctorWith6Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTVolatileMemberFunctor<void, MemberBase, int, int, int, int, int, int> voidVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidVolatileFunction6);
        voidVolatileMemberBaseFunctor(&member, 1, 2, 3, 4, 5, 6);
        CHECK("Member::voidVolatileFunction6" == *sg_memberString);
        QEXTVolatileMemberFunctor<int, MemberBase, int, int, int, int, int, int> intVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intVolatileFunction6);
        CHECK(0 == intVolatileMemberBaseFunctor(&member, 1, 2, 3, 4, 5, 6));
        QEXTVolatileMemberFunctor<double, MemberBase, double, double, double, double, double, double> doubleVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleVolatileFunction6);
        CHECK(0 == doubleVolatileMemberBaseFunctor(&member, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

        QEXTVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int, int> voidVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidVolatileFunctionB6);
        voidVolatileMemberBaseFunctorB(&member, true, 2, 3, 4, 5, 6);
        CHECK("Member::voidVolatileFunctionB6" == *sg_memberString);
        QEXTVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int, int> intVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intVolatileFunctionB6);
        CHECK(1 == intVolatileMemberBaseFunctorB(&member, true, 2, 3, 4, 5, 6));
        CHECK(0 == intVolatileMemberBaseFunctorB(&member, false, 2, 3, 4, 5, 6));
        QEXTVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double, double> doubleVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB6);
        CHECK(1 == doubleVolatileMemberBaseFunctorB(&member, true, 2.2, 3.3, 4.4, 5.5, 6.6));
        CHECK(0 == doubleVolatileMemberBaseFunctorB(&member, false, 2.2, 3.3, 4.4, 5.5, 6.6));
    }

    TEST(qextMemberFunctorTest, testConstVolatileFunctorWith6Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTConstVolatileMemberFunctor<void, MemberBase, int, int, int, int, int, int> voidConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstVolatileFunction6);
        voidConstVolatileMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5, 6);
        CHECK("MemberBase::voidConstVolatileFunction6" == *sg_memberString);
        QEXTConstVolatileMemberFunctor<int, MemberBase, int, int, int, int, int, int> intConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstVolatileFunction6);
        CHECK(1 + 2 + 3 + 4 + 5 + 6 == intConstVolatileMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5, 6));
        QEXTConstVolatileMemberFunctor<double, MemberBase, double, double, double, double, double, double> doubleConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction6);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleConstVolatileMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

        QEXTConstVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int, int> voidConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB6);
        voidConstVolatileMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5, 6);
        CHECK("MemberBase::voidConstVolatileFunctionB6" == *sg_memberString);
        QEXTConstVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int, int> intConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB6);
        CHECK(2 + 3 + 4 + 5 + 6 == intConstVolatileMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5, 6));
        CHECK(2 * 3 * 4 * 5 * 6 == intConstVolatileMemberBaseFunctorB(&memberBase, false, 2, 3, 4, 5, 6));
        QEXTConstVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double, double> doubleConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB6);
        CHECK(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleConstVolatileMemberBaseFunctorB(&memberBase, true, 2.2, 3.3, 4.4, 5.5, 6.6));
        CHECK(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleConstVolatileMemberBaseFunctorB(&memberBase, false, 2.2, 3.3, 4.4, 5.5, 6.6));
    }

    TEST(qextMemberFunctorTest, testPolymorphismConstVolatileFunctorWith6Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTConstVolatileMemberFunctor<void, MemberBase, int, int, int, int, int, int> voidConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstVolatileFunction6);
        voidConstVolatileMemberBaseFunctor(&member, 1, 2, 3, 4, 5, 6);
        CHECK("Member::voidConstVolatileFunction6" == *sg_memberString);
        QEXTConstVolatileMemberFunctor<int, MemberBase, int, int, int, int, int, int> intConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstVolatileFunction6);
        CHECK(0 == intConstVolatileMemberBaseFunctor(&member, 1, 2, 3, 4, 5, 6));
        QEXTConstVolatileMemberFunctor<double, MemberBase, double, double, double, double, double, double> doubleConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction6);
        CHECK(0 == doubleConstVolatileMemberBaseFunctor(&member, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

        QEXTConstVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int, int> voidConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB6);
        voidConstVolatileMemberBaseFunctorB(&member, true, 2, 3, 4, 5, 6);
        CHECK("Member::voidConstVolatileFunctionB6" == *sg_memberString);
        QEXTConstVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int, int> intConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB6);
        CHECK(1 == intConstVolatileMemberBaseFunctorB(&member, true, 2, 3, 4, 5, 6));
        CHECK(0 == intConstVolatileMemberBaseFunctorB(&member, false, 2, 3, 4, 5, 6));
        QEXTConstVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double, double> doubleConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB6);
        CHECK(1 == doubleConstVolatileMemberBaseFunctorB(&member, true, 2.2, 3.3, 4.4, 5.5, 6.6));
        CHECK(0 == doubleConstVolatileMemberBaseFunctorB(&member, false, 2.2, 3.3, 4.4, 5.5, 6.6));
    }

    TEST(qextMemberFunctorTest, testBoundFunctorWith6Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTBoundMemberFunctor<void, MemberBase, int, int, int, int, int, int> voidBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidFunction6);
        voidBoundMemberBaseFunctor(1, 2, 3, 4, 5, 6);
        CHECK("MemberBase::voidFunction6" == *sg_memberString);
        QEXTBoundMemberFunctor<int, MemberBase, int, int, int, int, int, int> intBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intFunction6);
        CHECK(1 + 2 + 3 + 4 + 5 + 6 == intBoundMemberBaseFunctor(1, 2, 3, 4, 5, 6));
        QEXTBoundMemberFunctor<double, MemberBase, double, double, double, double, double, double> doubleBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleFunction6);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

        QEXTBoundMemberFunctor<void, MemberBase, bool, int, int, int, int, int> voidBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidFunctionB6);
        voidBoundMemberBaseFunctorB(true, 2, 3, 4, 5, 6);
        CHECK("MemberBase::voidFunctionB6" == *sg_memberString);
        QEXTBoundMemberFunctor<int, MemberBase, bool, int, int, int, int, int> intBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intFunctionB6);
        CHECK(2 + 3 + 4 + 5 + 6 == intBoundMemberBaseFunctorB(true, 2, 3, 4, 5, 6));
        CHECK(2 * 3 * 4 * 5 * 6 == intBoundMemberBaseFunctorB(false, 2, 3, 4, 5, 6));
        QEXTBoundMemberFunctor<double, MemberBase, bool, double, double, double, double, double> doubleBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleFunctionB6);
        CHECK(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6));
        CHECK(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleBoundMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6));
    }

    TEST(qextMemberFunctorTest, testPolymorphismBoundFunctorWith6Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTBoundMemberFunctor<void, MemberBase, int, int, int, int, int, int> voidBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction6);
        voidBoundMemberBaseFunctor(1, 2, 3, 4, 5, 6);
        CHECK("Member::voidFunction6" == *sg_memberString);
        QEXTBoundMemberFunctor<int, MemberBase, int, int, int, int, int, int> intBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction6);
        CHECK(0 == intBoundMemberBaseFunctor(1, 2, 3, 4, 5, 6));
        QEXTBoundMemberFunctor<double, MemberBase, double, double, double, double, double, double> doubleBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction6);
        CHECK(0 == doubleBoundMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

        QEXTBoundMemberFunctor<void, MemberBase, bool, int, int, int, int, int> voidBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunctionB6);
        voidBoundMemberBaseFunctorB(true, 2, 3, 4, 5, 6);
        CHECK("Member::voidFunctionB6" == *sg_memberString);
        QEXTBoundMemberFunctor<int, MemberBase, bool, int, int, int, int, int> intBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunctionB6);
        CHECK(1 == intBoundMemberBaseFunctorB(true, 2, 3, 4, 5, 6));
        CHECK(0 == intBoundMemberBaseFunctorB(false, 2, 3, 4, 5, 6));
        QEXTBoundMemberFunctor<double, MemberBase, bool, double, double, double, double, double> doubleBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunctionB6);
        CHECK(1 == doubleBoundMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6));
        CHECK(0 == doubleBoundMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6));
    }

    TEST(qextMemberFunctorTest, testBoundConstFunctorWith6Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTBoundConstMemberFunctor<void, MemberBase, int, int, int, int, int, int> voidBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunction6);
        voidBoundConstMemberBaseFunctor(1, 2, 3, 4, 5, 6);
        CHECK("MemberBase::voidConstFunction6" == *sg_memberString);
        QEXTBoundConstMemberFunctor<int, MemberBase, int, int, int, int, int, int> intBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intConstFunction6);
        CHECK(1 + 2 + 3 + 4 + 5 + 6 == intBoundConstMemberBaseFunctor(1, 2, 3, 4, 5, 6));
        QEXTBoundConstMemberFunctor<double, MemberBase, double, double, double, double, double, double> doubleBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunction6);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundConstMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

        QEXTBoundConstMemberFunctor<void, MemberBase, bool, int, int, int, int, int> voidBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunctionB6);
        voidBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5, 6);
        CHECK("MemberBase::voidConstFunctionB6" == *sg_memberString);
        QEXTBoundConstMemberFunctor<int, MemberBase, bool, int, int, int, int, int> intBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intConstFunctionB6);
        CHECK(2 + 3 + 4 + 5 + 6 == intBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5, 6));
        CHECK(2 * 3 * 4 * 5 * 6 == intBoundConstMemberBaseFunctorB(false, 2, 3, 4, 5, 6));
        QEXTBoundConstMemberFunctor<double, MemberBase, bool, double, double, double, double, double> doubleBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunctionB6);
        CHECK(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundConstMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6));
        CHECK(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleBoundConstMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6));
    }

    TEST(qextMemberFunctorTest, testPolymorphismBoundConstFunctorWith6Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTBoundConstMemberFunctor<void, MemberBase, int, int, int, int, int, int> voidBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction6);
        voidBoundConstMemberBaseFunctor(1, 2, 3, 4, 5, 6);
        CHECK("Member::voidConstFunction6" == *sg_memberString);
        QEXTBoundConstMemberFunctor<int, MemberBase, int, int, int, int, int, int> intBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction6);
        CHECK(0 == intBoundConstMemberBaseFunctor(1, 2, 3, 4, 5, 6));
        QEXTBoundConstMemberFunctor<double, MemberBase, double, double, double, double, double, double> doubleBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction6);
        CHECK(0 == doubleBoundConstMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

        QEXTBoundConstMemberFunctor<void, MemberBase, bool, int, int, int, int, int> voidBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunctionB6);
        voidBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5, 6);
        CHECK("Member::voidConstFunctionB6" == *sg_memberString);
        QEXTBoundConstMemberFunctor<int, MemberBase, bool, int, int, int, int, int> intBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunctionB6);
        CHECK(1 == intBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5, 6));
        CHECK(0 == intBoundConstMemberBaseFunctorB(false, 2, 3, 4, 5, 6));
        QEXTBoundConstMemberFunctor<double, MemberBase, bool, double, double, double, double, double> doubleBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunctionB6);
        CHECK(1 == doubleBoundConstMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6));
        CHECK(0 == doubleBoundConstMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6));
    }

    TEST(qextMemberFunctorTest, testBoundVolatileFunctorWith6Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTBoundVolatileMemberFunctor<void, MemberBase, int, int, int, int, int, int> voidBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunction6);
        voidBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6);
        CHECK("MemberBase::voidVolatileFunction6" == *sg_memberString);
        QEXTBoundVolatileMemberFunctor<int, MemberBase, int, int, int, int, int, int> intBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunction6);
        CHECK(1 + 2 + 3 + 4 + 5 + 6 == intBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6));
        QEXTBoundVolatileMemberFunctor<double, MemberBase, double, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunction6);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

        QEXTBoundVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int, int> voidBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunctionB6);
        voidBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6);
        CHECK("MemberBase::voidVolatileFunctionB6" == *sg_memberString);
        QEXTBoundVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int, int> intBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunctionB6);
        CHECK(2 + 3 + 4 + 5 + 6 == intBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6));
        CHECK(2 * 3 * 4 * 5 * 6 == intBoundVolatileMemberBaseFunctorB(false, 2, 3, 4, 5, 6));
        QEXTBoundVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunctionB6);
        CHECK(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6));
        CHECK(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6));
    }

    TEST(qextMemberFunctorTest, testPolymorphismBoundVolatileFunctorWith6Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTBoundVolatileMemberFunctor<void, MemberBase, int, int, int, int, int, int> voidBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction6);
        voidBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6);
        CHECK("Member::voidVolatileFunction6" == *sg_memberString);
        QEXTBoundVolatileMemberFunctor<int, MemberBase, int, int, int, int, int, int> intBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction6);
        CHECK(0 == intBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6));
        QEXTBoundVolatileMemberFunctor<double, MemberBase, double, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction6);
        CHECK(0 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

        QEXTBoundVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int, int> voidBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunctionB6);
        voidBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6);
        CHECK("Member::voidVolatileFunctionB6" == *sg_memberString);
        QEXTBoundVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int, int> intBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunctionB6);
        CHECK(1 == intBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6));
        CHECK(0 == intBoundVolatileMemberBaseFunctorB(false, 2, 3, 4, 5, 6));
        QEXTBoundVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunctionB6);
        CHECK(1 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6));
        CHECK(0 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6));
    }

    TEST(qextMemberFunctorTest, testBoundConstVolatileFunctorWith6Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTBoundConstVolatileMemberFunctor<void, MemberBase, int, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunction6);
        voidBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6);
        CHECK("MemberBase::voidConstVolatileFunction6" == *sg_memberString);
        QEXTBoundConstVolatileMemberFunctor<int, MemberBase, int, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunction6);
        CHECK(1 + 2 + 3 + 4 + 5 + 6 == intBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6));
        QEXTBoundConstVolatileMemberFunctor<double, MemberBase, double, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction6);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

        QEXTBoundConstVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunctionB6);
        voidBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6);
        CHECK("MemberBase::voidConstVolatileFunctionB6" == *sg_memberString);
        QEXTBoundConstVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunctionB6);
        CHECK(2 + 3 + 4 + 5 + 6 == intBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6));
        CHECK(2 * 3 * 4 * 5 * 6 == intBoundConstVolatileMemberBaseFunctorB(false, 2, 3, 4, 5, 6));
        QEXTBoundConstVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunctionB6);
        CHECK(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6));
        CHECK(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6));
    }

    TEST(qextMemberFunctorTest, testPolymorphismBoundConstVolatileFunctorWith6Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTBoundConstVolatileMemberFunctor<void, MemberBase, int, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction6);
        voidBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6);
        CHECK("Member::voidConstVolatileFunction6" == *sg_memberString);
        QEXTBoundConstVolatileMemberFunctor<int, MemberBase, int, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction6);
        CHECK(0 == intBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6));
        QEXTBoundConstVolatileMemberFunctor<double, MemberBase, double, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction6);
        CHECK(0 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

        QEXTBoundConstVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunctionB6);
        voidBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6);
        CHECK("Member::voidConstVolatileFunctionB6" == *sg_memberString);
        QEXTBoundConstVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunctionB6);
        CHECK(1 == intBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6));
        CHECK(0 == intBoundConstVolatileMemberBaseFunctorB(false, 2, 3, 4, 5, 6));
        QEXTBoundConstVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunctionB6);
        CHECK(1 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6));
        CHECK(0 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6));
    }

    TEST(qextMemberFunctorTest, testFunctorWith7Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTMemberFunctor<void, MemberBase, int, int, int, int, int, int, int> voidMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidFunction7);
        voidMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5, 6, 7);
        CHECK("MemberBase::voidFunction7" == *sg_memberString);
        QEXTMemberFunctor<int, MemberBase, int, int, int, int, int, int, int> intMemberBaseFunctor = qextMemberFunctor(&MemberBase::intFunction7);
        CHECK(1 + 2 + 3 + 4 + 5 + 6 + 7 == intMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5, 6, 7));
        QEXTMemberFunctor<double, MemberBase, double, double, double, double, double, double, double> doubleMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleFunction7);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

        QEXTMemberFunctor<void, MemberBase, bool, int, int, int, int, int, int> voidMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidFunctionB7);
        voidMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5, 6, 7);
        CHECK("MemberBase::voidFunctionB7" == *sg_memberString);
        QEXTMemberFunctor<int, MemberBase, bool, int, int, int, int, int, int> intMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intFunctionB7);
        CHECK(2 + 3 + 4 + 5 + 6 + 7 == intMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5, 6, 7));
        CHECK(2 * 3 * 4 * 5 * 6 * 7 == intMemberBaseFunctorB(&memberBase, false, 2, 3, 4, 5, 6, 7));
        QEXTMemberFunctor<double, MemberBase, bool, double, double, double, double, double, double> doubleMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleFunctionB7);
        CHECK(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleMemberBaseFunctorB(&memberBase, true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
        CHECK(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleMemberBaseFunctorB(&memberBase, false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    }

    TEST(qextMemberFunctorTest, testPolymorphismFunctorWith7Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTMemberFunctor<void, MemberBase, int, int, int, int, int, int, int> voidMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidFunction7);
        voidMemberBaseFunctor(&member, 1, 2, 3, 4, 5, 6, 7);
        CHECK("Member::voidFunction7" == *sg_memberString);
        QEXTMemberFunctor<int, MemberBase, int, int, int, int, int, int, int> intMemberBaseFunctor = qextMemberFunctor(&MemberBase::intFunction7);
        CHECK(0 == intMemberBaseFunctor(&member, 1, 2, 3, 4, 5, 6, 7));
        QEXTMemberFunctor<double, MemberBase, double, double, double, double, double, double, double> doubleMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleFunction7);
        CHECK(0 == doubleMemberBaseFunctor(&member, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

        QEXTMemberFunctor<void, MemberBase, bool, int, int, int, int, int, int> voidMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidFunctionB7);
        voidMemberBaseFunctorB(&member, true, 2, 3, 4, 5, 6, 7);
        CHECK("Member::voidFunctionB7" == *sg_memberString);
        QEXTMemberFunctor<int, MemberBase, bool, int, int, int, int, int, int> intMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intFunctionB7);
        CHECK(1 == intMemberBaseFunctorB(&member, true, 2, 3, 4, 5, 6, 7));
        CHECK(0 == intMemberBaseFunctorB(&member, false, 2, 3, 4, 5, 6, 7));
        QEXTMemberFunctor<double, MemberBase, bool, double, double, double, double, double, double> doubleMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleFunctionB7);
        CHECK(1 == doubleMemberBaseFunctorB(&member, true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
        CHECK(0 == doubleMemberBaseFunctorB(&member, false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    }

    TEST(qextMemberFunctorTest, testConstFunctorWith7Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTConstMemberFunctor<void, MemberBase, int, int, int, int, int, int, int> voidConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstFunction7);
        voidConstMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5, 6, 7);
        CHECK("MemberBase::voidConstFunction7" == *sg_memberString);
        QEXTConstMemberFunctor<int, MemberBase, int, int, int, int, int, int, int> intConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstFunction7);
        CHECK(1 + 2 + 3 + 4 + 5 + 6 + 7 == intConstMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5, 6, 7));
        QEXTConstMemberFunctor<double, MemberBase, double, double, double, double, double, double, double> doubleConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstFunction7);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleConstMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

        QEXTConstMemberFunctor<void, MemberBase, bool, int, int, int, int, int, int> voidConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstFunctionB7);
        voidConstMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5, 6, 7);
        CHECK("MemberBase::voidConstFunctionB7" == *sg_memberString);
        QEXTConstMemberFunctor<int, MemberBase, bool, int, int, int, int, int, int> intConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstFunctionB7);
        CHECK(2 + 3 + 4 + 5 + 6 + 7 == intConstMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5, 6, 7));
        CHECK(2 * 3 * 4 * 5 * 6 * 7 == intConstMemberBaseFunctorB(&memberBase, false, 2, 3, 4, 5, 6, 7));
        QEXTConstMemberFunctor<double, MemberBase, bool, double, double, double, double, double, double> doubleConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstFunctionB7);
        CHECK(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleConstMemberBaseFunctorB(&memberBase, true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
        CHECK(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleConstMemberBaseFunctorB(&memberBase, false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    }

    TEST(qextMemberFunctorTest, testPolymorphismConstFunctorWith7Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTConstMemberFunctor<void, MemberBase, int, int, int, int, int, int, int> voidConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstFunction7);
        voidConstMemberBaseFunctor(&member, 1, 2, 3, 4, 5, 6, 7);
        CHECK("Member::voidConstFunction7" == *sg_memberString);
        QEXTConstMemberFunctor<int, MemberBase, int, int, int, int, int, int, int> intConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstFunction7);
        CHECK(0 == intConstMemberBaseFunctor(&member, 1, 2, 3, 4, 5, 6, 7));
        QEXTConstMemberFunctor<double, MemberBase, double, double, double, double, double, double, double> doubleConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstFunction7);
        CHECK(0 == doubleConstMemberBaseFunctor(&member, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

        QEXTConstMemberFunctor<void, MemberBase, bool, int, int, int, int, int, int> voidConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstFunctionB7);
        voidConstMemberBaseFunctorB(&member, true, 2, 3, 4, 5, 6, 7);
        CHECK("Member::voidConstFunctionB7" == *sg_memberString);
        QEXTConstMemberFunctor<int, MemberBase, bool, int, int, int, int, int, int> intConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstFunctionB7);
        CHECK(1 == intConstMemberBaseFunctorB(&member, true, 2, 3, 4, 5, 6, 7));
        CHECK(0 == intConstMemberBaseFunctorB(&member, false, 2, 3, 4, 5, 6, 7));
        QEXTConstMemberFunctor<double, MemberBase, bool, double, double, double, double, double, double> doubleConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstFunctionB7);
        CHECK(1 == doubleConstMemberBaseFunctorB(&member, true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
        CHECK(0 == doubleConstMemberBaseFunctorB(&member, false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    }

    TEST(qextMemberFunctorTest, testVolatileFunctorWith7Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTVolatileMemberFunctor<void, MemberBase, int, int, int, int, int, int, int> voidVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidVolatileFunction7);
        voidVolatileMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5, 6, 7);
        CHECK("MemberBase::voidVolatileFunction7" == *sg_memberString);
        QEXTVolatileMemberFunctor<int, MemberBase, int, int, int, int, int, int, int> intVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intVolatileFunction7);
        CHECK(1 + 2 + 3 + 4 + 5 + 6 + 7 == intVolatileMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5, 6, 7));
        QEXTVolatileMemberFunctor<double, MemberBase, double, double, double, double, double, double, double> doubleVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleVolatileFunction7);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleVolatileMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

        QEXTVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int, int, int> voidVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidVolatileFunctionB7);
        voidVolatileMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5, 6, 7);
        CHECK("MemberBase::voidVolatileFunctionB7" == *sg_memberString);
        QEXTVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int, int, int> intVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intVolatileFunctionB7);
        CHECK(2 + 3 + 4 + 5 + 6 + 7 == intVolatileMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5, 6, 7));
        CHECK(2 * 3 * 4 * 5 * 6 * 7 == intVolatileMemberBaseFunctorB(&memberBase, false, 2, 3, 4, 5, 6, 7));
        QEXTVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double, double, double> doubleVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB7);
        CHECK(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleVolatileMemberBaseFunctorB(&memberBase, true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
        CHECK(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleVolatileMemberBaseFunctorB(&memberBase, false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    }

    TEST(qextMemberFunctorTest, testPolymorphismVolatileFunctorWith7Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTVolatileMemberFunctor<void, MemberBase, int, int, int, int, int, int, int> voidVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidVolatileFunction7);
        voidVolatileMemberBaseFunctor(&member, 1, 2, 3, 4, 5, 6, 7);
        CHECK("Member::voidVolatileFunction7" == *sg_memberString);
        QEXTVolatileMemberFunctor<int, MemberBase, int, int, int, int, int, int, int> intVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intVolatileFunction7);
        CHECK(0 == intVolatileMemberBaseFunctor(&member, 1, 2, 3, 4, 5, 6, 7));
        QEXTVolatileMemberFunctor<double, MemberBase, double, double, double, double, double, double, double> doubleVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleVolatileFunction7);
        CHECK(0 == doubleVolatileMemberBaseFunctor(&member, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

        QEXTVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int, int, int> voidVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidVolatileFunctionB7);
        voidVolatileMemberBaseFunctorB(&member, true, 2, 3, 4, 5, 6, 7);
        CHECK("Member::voidVolatileFunctionB7" == *sg_memberString);
        QEXTVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int, int, int> intVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intVolatileFunctionB7);
        CHECK(1 == intVolatileMemberBaseFunctorB(&member, true, 2, 3, 4, 5, 6, 7));
        CHECK(0 == intVolatileMemberBaseFunctorB(&member, false, 2, 3, 4, 5, 6, 7));
        QEXTVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double, double, double> doubleVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB7);
        CHECK(1 == doubleVolatileMemberBaseFunctorB(&member, true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
        CHECK(0 == doubleVolatileMemberBaseFunctorB(&member, false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    }

    TEST(qextMemberFunctorTest, testConstVolatileFunctorWith7Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTConstVolatileMemberFunctor<void, MemberBase, int, int, int, int, int, int, int> voidConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstVolatileFunction7);
        voidConstVolatileMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5, 6, 7);
        CHECK("MemberBase::voidConstVolatileFunction7" == *sg_memberString);
        QEXTConstVolatileMemberFunctor<int, MemberBase, int, int, int, int, int, int, int> intConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstVolatileFunction7);
        CHECK(1 + 2 + 3 + 4 + 5 + 6 + 7 == intConstVolatileMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5, 6, 7));
        QEXTConstVolatileMemberFunctor<double, MemberBase, double, double, double, double, double, double, double> doubleConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction7);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleConstVolatileMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

        QEXTConstVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int, int, int> voidConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB7);
        voidConstVolatileMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5, 6, 7);
        CHECK("MemberBase::voidConstVolatileFunctionB7" == *sg_memberString);
        QEXTConstVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int, int, int> intConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB7);
        CHECK(2 + 3 + 4 + 5 + 6 + 7 == intConstVolatileMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5, 6, 7));
        CHECK(2 * 3 * 4 * 5 * 6 * 7 == intConstVolatileMemberBaseFunctorB(&memberBase, false, 2, 3, 4, 5, 6, 7));
        QEXTConstVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double, double, double> doubleConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB7);
        CHECK(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleConstVolatileMemberBaseFunctorB(&memberBase, true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
        CHECK(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleConstVolatileMemberBaseFunctorB(&memberBase, false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    }

    TEST(qextMemberFunctorTest, testPolymorphismConstVolatileFunctorWith7Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTConstVolatileMemberFunctor<void, MemberBase, int, int, int, int, int, int, int> voidConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstVolatileFunction7);
        voidConstVolatileMemberBaseFunctor(&member, 1, 2, 3, 4, 5, 6, 7);
        CHECK("Member::voidConstVolatileFunction7" == *sg_memberString);
        QEXTConstVolatileMemberFunctor<int, MemberBase, int, int, int, int, int, int, int> intConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstVolatileFunction7);
        CHECK(0 == intConstVolatileMemberBaseFunctor(&member, 1, 2, 3, 4, 5, 6, 7));
        QEXTConstVolatileMemberFunctor<double, MemberBase, double, double, double, double, double, double, double> doubleConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction7);
        CHECK(0 == doubleConstVolatileMemberBaseFunctor(&member, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

        QEXTConstVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int, int, int> voidConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB7);
        voidConstVolatileMemberBaseFunctorB(&member, true, 2, 3, 4, 5, 6, 7);
        CHECK("Member::voidConstVolatileFunctionB7" == *sg_memberString);
        QEXTConstVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int, int, int> intConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB7);
        CHECK(1 == intConstVolatileMemberBaseFunctorB(&member, true, 2, 3, 4, 5, 6, 7));
        CHECK(0 == intConstVolatileMemberBaseFunctorB(&member, false, 2, 3, 4, 5, 6, 7));
        QEXTConstVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double, double, double> doubleConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB7);
        CHECK(1 == doubleConstVolatileMemberBaseFunctorB(&member, true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
        CHECK(0 == doubleConstVolatileMemberBaseFunctorB(&member, false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    }

    TEST(qextMemberFunctorTest, testBoundFunctorWith7Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTBoundMemberFunctor<void, MemberBase, int, int, int, int, int, int, int> voidBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidFunction7);
        voidBoundMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7);
        CHECK("MemberBase::voidFunction7" == *sg_memberString);
        QEXTBoundMemberFunctor<int, MemberBase, int, int, int, int, int, int, int> intBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intFunction7);
        CHECK(1 + 2 + 3 + 4 + 5 + 6 + 7 == intBoundMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7));
        QEXTBoundMemberFunctor<double, MemberBase, double, double, double, double, double, double, double> doubleBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleFunction7);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

        QEXTBoundMemberFunctor<void, MemberBase, bool, int, int, int, int, int, int> voidBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidFunctionB7);
        voidBoundMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7);
        CHECK("MemberBase::voidFunctionB7" == *sg_memberString);
        QEXTBoundMemberFunctor<int, MemberBase, bool, int, int, int, int, int, int> intBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intFunctionB7);
        CHECK(2 + 3 + 4 + 5 + 6 + 7 == intBoundMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7));
        CHECK(2 * 3 * 4 * 5 * 6 * 7 == intBoundMemberBaseFunctorB(false, 2, 3, 4, 5, 6, 7));
        QEXTBoundMemberFunctor<double, MemberBase, bool, double, double, double, double, double, double> doubleBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleFunctionB7);
        CHECK(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
        CHECK(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleBoundMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    }

    TEST(qextMemberFunctorTest, testPolymorphismBoundFunctorWith7Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTBoundMemberFunctor<void, MemberBase, int, int, int, int, int, int, int> voidBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction7);
        voidBoundMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7);
        CHECK("Member::voidFunction7" == *sg_memberString);
        QEXTBoundMemberFunctor<int, MemberBase, int, int, int, int, int, int, int> intBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction7);
        CHECK(0 == intBoundMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7));
        QEXTBoundMemberFunctor<double, MemberBase, double, double, double, double, double, double, double> doubleBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction7);
        CHECK(0 == doubleBoundMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

        QEXTBoundMemberFunctor<void, MemberBase, bool, int, int, int, int, int, int> voidBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunctionB7);
        voidBoundMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7);
        CHECK("Member::voidFunctionB7" == *sg_memberString);
        QEXTBoundMemberFunctor<int, MemberBase, bool, int, int, int, int, int, int> intBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunctionB7);
        CHECK(1 == intBoundMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7));
        CHECK(0 == intBoundMemberBaseFunctorB(false, 2, 3, 4, 5, 6, 7));
        QEXTBoundMemberFunctor<double, MemberBase, bool, double, double, double, double, double, double> doubleBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunctionB7);
        CHECK(1 == doubleBoundMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
        CHECK(0 == doubleBoundMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    }

    TEST(qextMemberFunctorTest, testBoundConstFunctorWith7Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTBoundConstMemberFunctor<void, MemberBase, int, int, int, int, int, int, int> voidBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunction7);
        voidBoundConstMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7);
        CHECK("MemberBase::voidConstFunction7" == *sg_memberString);
        QEXTBoundConstMemberFunctor<int, MemberBase, int, int, int, int, int, int, int> intBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intConstFunction7);
        CHECK(1 + 2 + 3 + 4 + 5 + 6 + 7 == intBoundConstMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7));
        QEXTBoundConstMemberFunctor<double, MemberBase, double, double, double, double, double, double, double> doubleBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunction7);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundConstMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

        QEXTBoundConstMemberFunctor<void, MemberBase, bool, int, int, int, int, int, int> voidBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunctionB7);
        voidBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7);
        CHECK("MemberBase::voidConstFunctionB7" == *sg_memberString);
        QEXTBoundConstMemberFunctor<int, MemberBase, bool, int, int, int, int, int, int> intBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intConstFunctionB7);
        CHECK(2 + 3 + 4 + 5 + 6 + 7 == intBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7));
        CHECK(2 * 3 * 4 * 5 * 6 * 7 == intBoundConstMemberBaseFunctorB(false, 2, 3, 4, 5, 6, 7));
        QEXTBoundConstMemberFunctor<double, MemberBase, bool, double, double, double, double, double, double> doubleBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunctionB7);
        CHECK(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundConstMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
        CHECK(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleBoundConstMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    }

    TEST(qextMemberFunctorTest, testPolymorphismBoundConstFunctorWith7Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTBoundConstMemberFunctor<void, MemberBase, int, int, int, int, int, int, int> voidBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction7);
        voidBoundConstMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7);
        CHECK("Member::voidConstFunction7" == *sg_memberString);
        QEXTBoundConstMemberFunctor<int, MemberBase, int, int, int, int, int, int, int> intBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction7);
        CHECK(0 == intBoundConstMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7));
        QEXTBoundConstMemberFunctor<double, MemberBase, double, double, double, double, double, double, double> doubleBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction7);
        CHECK(0 == doubleBoundConstMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

        QEXTBoundConstMemberFunctor<void, MemberBase, bool, int, int, int, int, int, int> voidBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunctionB7);
        voidBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7);
        CHECK("Member::voidConstFunctionB7" == *sg_memberString);
        QEXTBoundConstMemberFunctor<int, MemberBase, bool, int, int, int, int, int, int> intBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunctionB7);
        CHECK(1 == intBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7));
        CHECK(0 == intBoundConstMemberBaseFunctorB(false, 2, 3, 4, 5, 6, 7));
        QEXTBoundConstMemberFunctor<double, MemberBase, bool, double, double, double, double, double, double> doubleBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunctionB7);
        CHECK(1 == doubleBoundConstMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
        CHECK(0 == doubleBoundConstMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    }

    TEST(qextMemberFunctorTest, testBoundVolatileFunctorWith7Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTBoundVolatileMemberFunctor<void, MemberBase, int, int, int, int, int, int, int> voidBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunction7);
        voidBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7);
        CHECK("MemberBase::voidVolatileFunction7" == *sg_memberString);
        QEXTBoundVolatileMemberFunctor<int, MemberBase, int, int, int, int, int, int, int> intBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunction7);
        CHECK(1 + 2 + 3 + 4 + 5 + 6 + 7 == intBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7));
        QEXTBoundVolatileMemberFunctor<double, MemberBase, double, double, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunction7);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

        QEXTBoundVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int, int, int> voidBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunctionB7);
        voidBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7);
        CHECK("MemberBase::voidVolatileFunctionB7" == *sg_memberString);
        QEXTBoundVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int, int, int> intBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunctionB7);
        CHECK(2 + 3 + 4 + 5 + 6 + 7 == intBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7));
        CHECK(2 * 3 * 4 * 5 * 6 * 7 == intBoundVolatileMemberBaseFunctorB(false, 2, 3, 4, 5, 6, 7));
        QEXTBoundVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunctionB7);
        CHECK(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
        CHECK(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    }

    TEST(qextMemberFunctorTest, testPolymorphismBoundVolatileFunctorWith7Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTBoundVolatileMemberFunctor<void, MemberBase, int, int, int, int, int, int, int> voidBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction7);
        voidBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7);
        CHECK("Member::voidVolatileFunction7" == *sg_memberString);
        QEXTBoundVolatileMemberFunctor<int, MemberBase, int, int, int, int, int, int, int> intBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction7);
        CHECK(0 == intBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7));
        QEXTBoundVolatileMemberFunctor<double, MemberBase, double, double, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction7);
        CHECK(0 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

        QEXTBoundVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int, int, int> voidBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunctionB7);
        voidBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7);
        CHECK("Member::voidVolatileFunctionB7" == *sg_memberString);
        QEXTBoundVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int, int, int> intBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunctionB7);
        CHECK(1 == intBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7));
        CHECK(0 == intBoundVolatileMemberBaseFunctorB(false, 2, 3, 4, 5, 6, 7));
        QEXTBoundVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunctionB7);
        CHECK(1 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
        CHECK(0 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    }

    TEST(qextMemberFunctorTest, testBoundConstVolatileFunctorWith7Arg)
    {
        std::string string;
        sg_memberString = &string;

        MemberBase memberBase;

        QEXTBoundConstVolatileMemberFunctor<void, MemberBase, int, int, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunction7);
        voidBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7);
        CHECK("MemberBase::voidConstVolatileFunction7" == *sg_memberString);
        QEXTBoundConstVolatileMemberFunctor<int, MemberBase, int, int, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunction7);
        CHECK(1 + 2 + 3 + 4 + 5 + 6 + 7 == intBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7));
        QEXTBoundConstVolatileMemberFunctor<double, MemberBase, double, double, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction7);
        CHECK(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

        QEXTBoundConstVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunctionB7);
        voidBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7);
        CHECK("MemberBase::voidConstVolatileFunctionB7" == *sg_memberString);
        QEXTBoundConstVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunctionB7);
        CHECK(2 + 3 + 4 + 5 + 6 + 7 == intBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7));
        CHECK(2 * 3 * 4 * 5 * 6 * 7 == intBoundConstVolatileMemberBaseFunctorB(false, 2, 3, 4, 5, 6, 7));
        QEXTBoundConstVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunctionB7);
        CHECK(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
        CHECK(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    }

    TEST(qextMemberFunctorTest, testPolymorphismBoundConstVolatileFunctorWith7Arg)
    {
        std::string string;
        sg_memberString = &string;

        Member member;

        QEXTBoundConstVolatileMemberFunctor<void, MemberBase, int, int, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction7);
        voidBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7);
        CHECK("Member::voidConstVolatileFunction7" == *sg_memberString);
        QEXTBoundConstVolatileMemberFunctor<int, MemberBase, int, int, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction7);
        CHECK(0 == intBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7));
        QEXTBoundConstVolatileMemberFunctor<double, MemberBase, double, double, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction7);
        CHECK(0 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

        QEXTBoundConstVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunctionB7);
        voidBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7);
        CHECK("Member::voidConstVolatileFunctionB7" == *sg_memberString);
        QEXTBoundConstVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunctionB7);
        CHECK(1 == intBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7));
        CHECK(0 == intBoundConstVolatileMemberBaseFunctorB(false, 2, 3, 4, 5, 6, 7));
        QEXTBoundConstVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunctionB7);
        CHECK(1 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
        CHECK(0 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    }

} // namespace qextMemberFunctorTest

#endif // QEXTMEMBERFUNCTORTEST_H
