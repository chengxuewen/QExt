#include <qextMemberFunctor.h>

#include "qextMember.h"

#include <QtTest>
#include <iostream>

class QEXTMemberFunctorTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void testFunctorWith0Arg();
    void testPolymorphismFunctorWith0Arg();
    void testConstFunctorWith0Arg();
    void testPolymorphismConstFunctorWith0Arg();
    void testVolatileFunctorWith0Arg();
    void testPolymorphismVolatileFunctorWith0Arg();
    void testConstVolatileFunctorWith0Arg();
    void testPolymorphismConstVolatileFunctorWith0Arg();
    void testBoundFunctorWith0Arg();
    void testPolymorphismBoundFunctorWith0Arg();
    void testBoundConstFunctorWith0Arg();
    void testPolymorphismBoundConstFunctorWith0Arg();
    void testBoundVolatileFunctorWith0Arg();
    void testPolymorphismBoundVolatileFunctorWith0Arg();
    void testBoundConstVolatileFunctorWith0Arg();
    void testPolymorphismBoundConstVolatileFunctorWith0Arg();

    void testFunctorWith1Arg();
    void testPolymorphismFunctorWith1Arg();
    void testConstFunctorWith1Arg();
    void testPolymorphismConstFunctorWith1Arg();
    void testVolatileFunctorWith1Arg();
    void testPolymorphismVolatileFunctorWith1Arg();
    void testConstVolatileFunctorWith1Arg();
    void testPolymorphismConstVolatileFunctorWith1Arg();
    void testBoundFunctorWith1Arg();
    void testPolymorphismBoundFunctorWith1Arg();
    void testBoundConstFunctorWith1Arg();
    void testPolymorphismBoundConstFunctorWith1Arg();
    void testBoundVolatileFunctorWith1Arg();
    void testPolymorphismBoundVolatileFunctorWith1Arg();
    void testBoundConstVolatileFunctorWith1Arg();
    void testPolymorphismBoundConstVolatileFunctorWith1Arg();

    void testFunctorWith2Arg();
    void testPolymorphismFunctorWith2Arg();
    void testConstFunctorWith2Arg();
    void testPolymorphismConstFunctorWith2Arg();
    void testVolatileFunctorWith2Arg();
    void testPolymorphismVolatileFunctorWith2Arg();
    void testConstVolatileFunctorWith2Arg();
    void testPolymorphismConstVolatileFunctorWith2Arg();
    void testBoundFunctorWith2Arg();
    void testPolymorphismBoundFunctorWith2Arg();
    void testBoundConstFunctorWith2Arg();
    void testPolymorphismBoundConstFunctorWith2Arg();
    void testBoundVolatileFunctorWith2Arg();
    void testPolymorphismBoundVolatileFunctorWith2Arg();
    void testBoundConstVolatileFunctorWith2Arg();
    void testPolymorphismBoundConstVolatileFunctorWith2Arg();

    void testFunctorWith3Arg();
    void testPolymorphismFunctorWith3Arg();
    void testConstFunctorWith3Arg();
    void testPolymorphismConstFunctorWith3Arg();
    void testVolatileFunctorWith3Arg();
    void testPolymorphismVolatileFunctorWith3Arg();
    void testConstVolatileFunctorWith3Arg();
    void testPolymorphismConstVolatileFunctorWith3Arg();
    void testBoundFunctorWith3Arg();
    void testPolymorphismBoundFunctorWith3Arg();
    void testBoundConstFunctorWith3Arg();
    void testPolymorphismBoundConstFunctorWith3Arg();
    void testBoundVolatileFunctorWith3Arg();
    void testPolymorphismBoundVolatileFunctorWith3Arg();
    void testBoundConstVolatileFunctorWith3Arg();
    void testPolymorphismBoundConstVolatileFunctorWith3Arg();

    void testFunctorWith4Arg();
    void testPolymorphismFunctorWith4Arg();
    void testConstFunctorWith4Arg();
    void testPolymorphismConstFunctorWith4Arg();
    void testVolatileFunctorWith4Arg();
    void testPolymorphismVolatileFunctorWith4Arg();
    void testConstVolatileFunctorWith4Arg();
    void testPolymorphismConstVolatileFunctorWith4Arg();
    void testBoundFunctorWith4Arg();
    void testPolymorphismBoundFunctorWith4Arg();
    void testBoundConstFunctorWith4Arg();
    void testPolymorphismBoundConstFunctorWith4Arg();
    void testBoundVolatileFunctorWith4Arg();
    void testPolymorphismBoundVolatileFunctorWith4Arg();
    void testBoundConstVolatileFunctorWith4Arg();
    void testPolymorphismBoundConstVolatileFunctorWith4Arg();

    void testFunctorWith5Arg();
    void testPolymorphismFunctorWith5Arg();
    void testConstFunctorWith5Arg();
    void testPolymorphismConstFunctorWith5Arg();
    void testVolatileFunctorWith5Arg();
    void testPolymorphismVolatileFunctorWith5Arg();
    void testConstVolatileFunctorWith5Arg();
    void testPolymorphismConstVolatileFunctorWith5Arg();
    void testBoundFunctorWith5Arg();
    void testPolymorphismBoundFunctorWith5Arg();
    void testBoundConstFunctorWith5Arg();
    void testPolymorphismBoundConstFunctorWith5Arg();
    void testBoundVolatileFunctorWith5Arg();
    void testPolymorphismBoundVolatileFunctorWith5Arg();
    void testBoundConstVolatileFunctorWith5Arg();
    void testPolymorphismBoundConstVolatileFunctorWith5Arg();

    void testFunctorWith6Arg();
    void testPolymorphismFunctorWith6Arg();
    void testConstFunctorWith6Arg();
    void testPolymorphismConstFunctorWith6Arg();
    void testVolatileFunctorWith6Arg();
    void testPolymorphismVolatileFunctorWith6Arg();
    void testConstVolatileFunctorWith6Arg();
    void testPolymorphismConstVolatileFunctorWith6Arg();
    void testBoundFunctorWith6Arg();
    void testPolymorphismBoundFunctorWith6Arg();
    void testBoundConstFunctorWith6Arg();
    void testPolymorphismBoundConstFunctorWith6Arg();
    void testBoundVolatileFunctorWith6Arg();
    void testPolymorphismBoundVolatileFunctorWith6Arg();
    void testBoundConstVolatileFunctorWith6Arg();
    void testPolymorphismBoundConstVolatileFunctorWith6Arg();

    void testFunctorWith7Arg();
    void testPolymorphismFunctorWith7Arg();
    void testConstFunctorWith7Arg();
    void testPolymorphismConstFunctorWith7Arg();
    void testVolatileFunctorWith7Arg();
    void testPolymorphismVolatileFunctorWith7Arg();
    void testConstVolatileFunctorWith7Arg();
    void testPolymorphismConstVolatileFunctorWith7Arg();
    void testBoundFunctorWith7Arg();
    void testPolymorphismBoundFunctorWith7Arg();
    void testBoundConstFunctorWith7Arg();
    void testPolymorphismBoundConstFunctorWith7Arg();
    void testBoundVolatileFunctorWith7Arg();
    void testPolymorphismBoundVolatileFunctorWith7Arg();
    void testBoundConstVolatileFunctorWith7Arg();
    void testPolymorphismBoundConstVolatileFunctorWith7Arg();

};

void QEXTMemberFunctorTest::testFunctorWith0Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTMemberFunctor<void, MemberBase> voidMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidFunction0);
    voidMemberBaseFunctor(&memberBase);
    QVERIFY("MemberBase::voidFunction0" == *sg_memberString);
    QEXTMemberFunctor<int, MemberBase> intMemberBaseFunctor = qextMemberFunctor(&MemberBase::intFunction0);
    intMemberBaseFunctor(&memberBase);
    QVERIFY("MemberBase::intFunction0" == *sg_memberString);
    QEXTMemberFunctor<double, MemberBase> doubleMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleFunction0);
    doubleMemberBaseFunctor(&memberBase);
    QVERIFY("MemberBase::doubleFunction0" == *sg_memberString);
}

void QEXTMemberFunctorTest::testPolymorphismFunctorWith0Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTMemberFunctor<void, MemberBase> voidMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidFunction0);
    voidMemberBaseFunctor(&member);
    QVERIFY("Member::voidFunction0" == *sg_memberString);
    QEXTMemberFunctor<int, MemberBase> intMemberBaseFunctor = qextMemberFunctor(&MemberBase::intFunction0);
    intMemberBaseFunctor(&member);
    QVERIFY("Member::intFunction0" == *sg_memberString);
    QEXTMemberFunctor<double, MemberBase> doubleMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleFunction0);
    doubleMemberBaseFunctor(&member);
    QVERIFY("Member::doubleFunction0" == *sg_memberString);
}

void QEXTMemberFunctorTest::testConstFunctorWith0Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTConstMemberFunctor<void, MemberBase> voidConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstFunction0);
    voidConstMemberBaseFunctor(&memberBase);
    QVERIFY("MemberBase::voidConstFunction0" == *sg_memberString);
    QEXTConstMemberFunctor<int, MemberBase> intConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstFunction0);
    intConstMemberBaseFunctor(&memberBase);
    QVERIFY("MemberBase::intConstFunction0" == *sg_memberString);
    QEXTConstMemberFunctor<double, MemberBase> doubleConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstFunction0);
    doubleConstMemberBaseFunctor(&memberBase);
    QVERIFY("MemberBase::doubleConstFunction0" == *sg_memberString);
}

void QEXTMemberFunctorTest::testPolymorphismConstFunctorWith0Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTConstMemberFunctor<void, MemberBase> voidConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstFunction0);
    voidConstMemberBaseFunctor(&member);
    QVERIFY("Member::voidConstFunction0" == *sg_memberString);
    QEXTConstMemberFunctor<int, MemberBase> intConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstFunction0);
    intConstMemberBaseFunctor(&member);
    QVERIFY("Member::intConstFunction0" == *sg_memberString);
    QEXTConstMemberFunctor<double, MemberBase> doubleConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstFunction0);
    doubleConstMemberBaseFunctor(&member);
    QVERIFY("Member::doubleConstFunction0" == *sg_memberString);
}

void QEXTMemberFunctorTest::testVolatileFunctorWith0Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTVolatileMemberFunctor<void, MemberBase> voidVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidVolatileFunction0);
    voidVolatileMemberBaseFunctor(&memberBase);
    QVERIFY("MemberBase::voidVolatileFunction0" == *sg_memberString);
    QEXTVolatileMemberFunctor<int, MemberBase> intVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intVolatileFunction0);
    intVolatileMemberBaseFunctor(&memberBase);
    QVERIFY("MemberBase::intVolatileFunction0" == *sg_memberString);
    QEXTVolatileMemberFunctor<double, MemberBase> doubleVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleVolatileFunction0);
    doubleVolatileMemberBaseFunctor(&memberBase);
    QVERIFY("MemberBase::doubleVolatileFunction0" == *sg_memberString);
}

void QEXTMemberFunctorTest::testPolymorphismVolatileFunctorWith0Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTVolatileMemberFunctor<void, MemberBase> voidVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidVolatileFunction0);
    voidVolatileMemberBaseFunctor(&member);
    QVERIFY("Member::voidVolatileFunction0" == *sg_memberString);
    QEXTVolatileMemberFunctor<int, MemberBase> intVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intVolatileFunction0);
    intVolatileMemberBaseFunctor(&member);
    QVERIFY("Member::intVolatileFunction0" == *sg_memberString);
    QEXTVolatileMemberFunctor<double, MemberBase> doubleVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleVolatileFunction0);
    doubleVolatileMemberBaseFunctor(&member);
    QVERIFY("Member::doubleVolatileFunction0" == *sg_memberString);
}

void QEXTMemberFunctorTest::testConstVolatileFunctorWith0Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTConstVolatileMemberFunctor<void, MemberBase> voidConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstVolatileFunction0);
    voidConstVolatileMemberBaseFunctor(&memberBase);
    QVERIFY("MemberBase::voidConstVolatileFunction0" == *sg_memberString);
    QEXTConstVolatileMemberFunctor<int, MemberBase> intConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstVolatileFunction0);
    intConstVolatileMemberBaseFunctor(&memberBase);
    QVERIFY("MemberBase::intConstVolatileFunction0" == *sg_memberString);
    QEXTConstVolatileMemberFunctor<double, MemberBase> doubleConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction0);
    doubleConstVolatileMemberBaseFunctor(&memberBase);
    QVERIFY("MemberBase::doubleConstVolatileFunction0" == *sg_memberString);
}

void QEXTMemberFunctorTest::testPolymorphismConstVolatileFunctorWith0Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTConstVolatileMemberFunctor<void, MemberBase> voidConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstVolatileFunction0);
    voidConstVolatileMemberBaseFunctor(&member);
    QVERIFY("Member::voidConstVolatileFunction0" == *sg_memberString);
    QEXTConstVolatileMemberFunctor<int, MemberBase> intConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstVolatileFunction0);
    intConstVolatileMemberBaseFunctor(&member);
    QVERIFY("Member::intConstVolatileFunction0" == *sg_memberString);
    QEXTConstVolatileMemberFunctor<double, MemberBase> doubleConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction0);
    doubleConstVolatileMemberBaseFunctor(&member);
    QVERIFY("Member::doubleConstVolatileFunction0" == *sg_memberString);
}

void QEXTMemberFunctorTest::testBoundFunctorWith0Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTBoundMemberFunctor<void, MemberBase> voidBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidFunction0);
    voidBoundMemberBaseFunctor();
    QVERIFY("MemberBase::voidFunction0" == *sg_memberString);
    QEXTBoundMemberFunctor<int, MemberBase> intBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intFunction0);
    intBoundMemberBaseFunctor();
    QVERIFY("MemberBase::intFunction0" == *sg_memberString);
    QEXTBoundMemberFunctor<double, MemberBase> doubleBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleFunction0);
    doubleBoundMemberBaseFunctor();
    QVERIFY("MemberBase::doubleFunction0" == *sg_memberString);
}

void QEXTMemberFunctorTest::testPolymorphismBoundFunctorWith0Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTBoundMemberFunctor<void, MemberBase> voidBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction0);
    voidBoundMemberBaseFunctor();
    QVERIFY("Member::voidFunction0" == *sg_memberString);
    QEXTBoundMemberFunctor<int, MemberBase> intBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction0);
    intBoundMemberBaseFunctor();
    QVERIFY("Member::intFunction0" == *sg_memberString);
    QEXTBoundMemberFunctor<double, MemberBase> doubleBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction0);
    doubleBoundMemberBaseFunctor();
    QVERIFY("Member::doubleFunction0" == *sg_memberString);
}

void QEXTMemberFunctorTest::testBoundConstFunctorWith0Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTBoundConstMemberFunctor<void, MemberBase> voidBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunction0);
    voidBoundConstMemberBaseFunctor();
    QVERIFY("MemberBase::voidConstFunction0" == *sg_memberString);
    QEXTBoundConstMemberFunctor<int, MemberBase> intBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intConstFunction0);
    intBoundConstMemberBaseFunctor();
    QVERIFY("MemberBase::intConstFunction0" == *sg_memberString);
    QEXTBoundConstMemberFunctor<double, MemberBase> doubleBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunction0);
    doubleBoundConstMemberBaseFunctor();
    QVERIFY("MemberBase::doubleConstFunction0" == *sg_memberString);
}

void QEXTMemberFunctorTest::testPolymorphismBoundConstFunctorWith0Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTBoundConstMemberFunctor<void, MemberBase> voidBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction0);
    voidBoundConstMemberBaseFunctor();
    QVERIFY("Member::voidConstFunction0" == *sg_memberString);
    QEXTBoundConstMemberFunctor<int, MemberBase> intBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction0);
    intBoundConstMemberBaseFunctor();
    QVERIFY("Member::intConstFunction0" == *sg_memberString);
    QEXTBoundConstMemberFunctor<double, MemberBase> doubleBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction0);
    doubleBoundConstMemberBaseFunctor();
    QVERIFY("Member::doubleConstFunction0" == *sg_memberString);
}

void QEXTMemberFunctorTest::testBoundVolatileFunctorWith0Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTBoundVolatileMemberFunctor<void, MemberBase> voidBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunction0);
    voidBoundVolatileMemberBaseFunctor();
    QVERIFY("MemberBase::voidVolatileFunction0" == *sg_memberString);
    QEXTBoundVolatileMemberFunctor<int, MemberBase> intBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunction0);
    intBoundVolatileMemberBaseFunctor();
    QVERIFY("MemberBase::intVolatileFunction0" == *sg_memberString);
    QEXTBoundVolatileMemberFunctor<double, MemberBase> doubleBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunction0);
    doubleBoundVolatileMemberBaseFunctor();
    QVERIFY("MemberBase::doubleVolatileFunction0" == *sg_memberString);
}

void QEXTMemberFunctorTest::testPolymorphismBoundVolatileFunctorWith0Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTBoundVolatileMemberFunctor<void, MemberBase> voidBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction0);
    voidBoundVolatileMemberBaseFunctor();
    QVERIFY("Member::voidVolatileFunction0" == *sg_memberString);
    QEXTBoundVolatileMemberFunctor<int, MemberBase> intBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction0);
    intBoundVolatileMemberBaseFunctor();
    QVERIFY("Member::intVolatileFunction0" == *sg_memberString);
    QEXTBoundVolatileMemberFunctor<double, MemberBase> doubleBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction0);
    doubleBoundVolatileMemberBaseFunctor();
    QVERIFY("Member::doubleVolatileFunction0" == *sg_memberString);
}

void QEXTMemberFunctorTest::testBoundConstVolatileFunctorWith0Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase> voidBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunction0);
    voidBoundConstVolatileMemberBaseFunctor();
    QVERIFY("MemberBase::voidConstVolatileFunction0" == *sg_memberString);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase> intBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunction0);
    intBoundConstVolatileMemberBaseFunctor();
    QVERIFY("MemberBase::intConstVolatileFunction0" == *sg_memberString);
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase> doubleBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction0);
    doubleBoundConstVolatileMemberBaseFunctor();
    QVERIFY("MemberBase::doubleConstVolatileFunction0" == *sg_memberString);
}

void QEXTMemberFunctorTest::testPolymorphismBoundConstVolatileFunctorWith0Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase> voidBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction0);
    voidBoundConstVolatileMemberBaseFunctor();
    QVERIFY("Member::voidConstVolatileFunction0" == *sg_memberString);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase> intBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction0);
    intBoundConstVolatileMemberBaseFunctor();
    QVERIFY("Member::intConstVolatileFunction0" == *sg_memberString);
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase> doubleBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction0);
    doubleBoundConstVolatileMemberBaseFunctor();
    QVERIFY("Member::doubleConstVolatileFunction0" == *sg_memberString);
}

void QEXTMemberFunctorTest::testFunctorWith1Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTMemberFunctor<void, MemberBase, int> voidMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidFunction1);
    voidMemberBaseFunctor(&memberBase, 1);
    QVERIFY("MemberBase::voidFunction1" == *sg_memberString);
    QEXTMemberFunctor<int, MemberBase, int> intMemberBaseFunctor = qextMemberFunctor(&MemberBase::intFunction1);
    QVERIFY(1 == intMemberBaseFunctor(&memberBase, 1));
    QEXTMemberFunctor<double, MemberBase, double> doubleMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleFunction1);
    QVERIFY(1.1 == doubleMemberBaseFunctor(&memberBase, 1.1));

    QEXTMemberFunctor<void, MemberBase, bool> voidMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidFunctionB1);
    voidMemberBaseFunctorB(&memberBase, 1);
    QVERIFY("MemberBase::voidFunctionB1" == *sg_memberString);
    QEXTMemberFunctor<int, MemberBase, bool> intMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intFunctionB1);
    QVERIFY(1 == intMemberBaseFunctorB(&memberBase, true));
    QVERIFY(0 == intMemberBaseFunctorB(&memberBase, false));
    QEXTMemberFunctor<double, MemberBase, bool> doubleMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleFunctionB1);
    QVERIFY(1 == doubleMemberBaseFunctorB(&memberBase, true));
    QVERIFY(0 == doubleMemberBaseFunctorB(&memberBase, false));
}

void QEXTMemberFunctorTest::testPolymorphismFunctorWith1Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTMemberFunctor<void, MemberBase, int> voidMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidFunction1);
    voidMemberBaseFunctor(&member, 1);
    QVERIFY("Member::voidFunction1" == *sg_memberString);
    QEXTMemberFunctor<int, MemberBase, int> intMemberBaseFunctor = qextMemberFunctor(&MemberBase::intFunction1);
    QVERIFY(0 == intMemberBaseFunctor(&member, 1));
    QEXTMemberFunctor<double, MemberBase, double> doubleMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleFunction1);
    QVERIFY(0 == doubleMemberBaseFunctor(&member, 1.1));

    QEXTMemberFunctor<void, MemberBase, bool> voidMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidFunctionB1);
    voidMemberBaseFunctorB(&member, 1);
    QVERIFY("Member::voidFunctionB1" == *sg_memberString);
    QEXTMemberFunctor<int, MemberBase, bool> intMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intFunctionB1);
    QVERIFY(1 == intMemberBaseFunctorB(&member, true));
    QVERIFY(0 == intMemberBaseFunctorB(&member, false));
    QEXTMemberFunctor<double, MemberBase, bool> doubleMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleFunctionB1);
    QVERIFY(1 == doubleMemberBaseFunctorB(&member, true));
    QVERIFY(0 == doubleMemberBaseFunctorB(&member, false));
}

void QEXTMemberFunctorTest::testConstFunctorWith1Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTConstMemberFunctor<void, MemberBase, int> voidConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstFunction1);
    voidConstMemberBaseFunctor(&memberBase, 1);
    QVERIFY("MemberBase::voidConstFunction1" == *sg_memberString);
    QEXTConstMemberFunctor<int, MemberBase, int> intConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstFunction1);
    QVERIFY(1 == intConstMemberBaseFunctor(&memberBase, 1));
    QEXTConstMemberFunctor<double, MemberBase, double> doubleConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstFunction1);
    QVERIFY(1.1 == doubleConstMemberBaseFunctor(&memberBase, 1.1));

    QEXTConstMemberFunctor<void, MemberBase, bool> voidConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstFunctionB1);
    voidConstMemberBaseFunctorB(&memberBase, 1);
    QVERIFY("MemberBase::voidConstFunctionB1" == *sg_memberString);
    QEXTConstMemberFunctor<int, MemberBase, bool> intConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstFunctionB1);
    QVERIFY(1 == intConstMemberBaseFunctorB(&memberBase, true));
    QVERIFY(0 == intConstMemberBaseFunctorB(&memberBase, false));
    QEXTConstMemberFunctor<double, MemberBase, bool> doubleConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstFunctionB1);
    QVERIFY(1 == doubleConstMemberBaseFunctorB(&memberBase, true));
    QVERIFY(0 == doubleConstMemberBaseFunctorB(&memberBase, false));
}

void QEXTMemberFunctorTest::testPolymorphismConstFunctorWith1Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTConstMemberFunctor<void, MemberBase, int> voidConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstFunction1);
    voidConstMemberBaseFunctor(&member, 1);
    QVERIFY("Member::voidConstFunction1" == *sg_memberString);
    QEXTConstMemberFunctor<int, MemberBase, int> intConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstFunction1);
    QVERIFY(0 == intConstMemberBaseFunctor(&member, 1));
    QEXTConstMemberFunctor<double, MemberBase, double> doubleConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstFunction1);
    QVERIFY(0 == doubleConstMemberBaseFunctor(&member, 1.1));

    QEXTConstMemberFunctor<void, MemberBase, bool> voidConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstFunctionB1);
    voidConstMemberBaseFunctorB(&member, 1);
    QVERIFY("Member::voidConstFunctionB1" == *sg_memberString);
    QEXTConstMemberFunctor<int, MemberBase, bool> intConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstFunctionB1);
    QVERIFY(1 == intConstMemberBaseFunctorB(&member, true));
    QVERIFY(0 == intConstMemberBaseFunctorB(&member, false));
    QEXTConstMemberFunctor<double, MemberBase, bool> doubleConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstFunctionB1);
    QVERIFY(1 == doubleConstMemberBaseFunctorB(&member, true));
    QVERIFY(0 == doubleConstMemberBaseFunctorB(&member, false));
}

void QEXTMemberFunctorTest::testVolatileFunctorWith1Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTVolatileMemberFunctor<void, MemberBase, int> voidVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidVolatileFunction1);
    voidVolatileMemberBaseFunctor(&memberBase, 1);
    QVERIFY("MemberBase::voidVolatileFunction1" == *sg_memberString);
    QEXTVolatileMemberFunctor<int, MemberBase, int> intVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intVolatileFunction1);
    QVERIFY(1 == intVolatileMemberBaseFunctor(&memberBase, 1));
    QEXTVolatileMemberFunctor<double, MemberBase, double> doubleVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleVolatileFunction1);
    QVERIFY(1.1 == doubleVolatileMemberBaseFunctor(&memberBase, 1.1));

    QEXTVolatileMemberFunctor<void, MemberBase, bool> voidVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidVolatileFunctionB1);
    voidVolatileMemberBaseFunctorB(&memberBase, 1);
    QVERIFY("MemberBase::voidVolatileFunctionB1" == *sg_memberString);
    QEXTVolatileMemberFunctor<int, MemberBase, bool> intVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intVolatileFunctionB1);
    QVERIFY(1 == intVolatileMemberBaseFunctorB(&memberBase, true));
    QVERIFY(0 == intVolatileMemberBaseFunctorB(&memberBase, false));
    QEXTVolatileMemberFunctor<double, MemberBase, bool> doubleVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB1);
    QVERIFY(1 == doubleVolatileMemberBaseFunctorB(&memberBase, true));
    QVERIFY(0 == doubleVolatileMemberBaseFunctorB(&memberBase, false));
}

void QEXTMemberFunctorTest::testPolymorphismVolatileFunctorWith1Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTVolatileMemberFunctor<void, MemberBase, int> voidVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidVolatileFunction1);
    voidVolatileMemberBaseFunctor(&member, 1);
    QVERIFY("Member::voidVolatileFunction1" == *sg_memberString);
    QEXTVolatileMemberFunctor<int, MemberBase, int> intVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intVolatileFunction1);
    QVERIFY(0 == intVolatileMemberBaseFunctor(&member, 1));
    QEXTVolatileMemberFunctor<double, MemberBase, double> doubleVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleVolatileFunction1);
    QVERIFY(0 == doubleVolatileMemberBaseFunctor(&member, 1.1));

    QEXTVolatileMemberFunctor<void, MemberBase, bool> voidVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidVolatileFunctionB1);
    voidVolatileMemberBaseFunctorB(&member, 1);
    QVERIFY("Member::voidVolatileFunctionB1" == *sg_memberString);
    QEXTVolatileMemberFunctor<int, MemberBase, bool> intVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intVolatileFunctionB1);
    QVERIFY(1 == intVolatileMemberBaseFunctorB(&member, true));
    QVERIFY(0 == intVolatileMemberBaseFunctorB(&member, false));
    QEXTVolatileMemberFunctor<double, MemberBase, bool> doubleVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB1);
    QVERIFY(1 == doubleVolatileMemberBaseFunctorB(&member, true));
    QVERIFY(0 == doubleVolatileMemberBaseFunctorB(&member, false));
}

void QEXTMemberFunctorTest::testConstVolatileFunctorWith1Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTConstVolatileMemberFunctor<void, MemberBase, int> voidConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstVolatileFunction1);
    voidConstVolatileMemberBaseFunctor(&memberBase, 1);
    QVERIFY("MemberBase::voidConstVolatileFunction1" == *sg_memberString);
    QEXTConstVolatileMemberFunctor<int, MemberBase, int> intConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstVolatileFunction1);
    QVERIFY(1 == intConstVolatileMemberBaseFunctor(&memberBase, 1));
    QEXTConstVolatileMemberFunctor<double, MemberBase, double> doubleConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction1);
    QVERIFY(1.1 == doubleConstVolatileMemberBaseFunctor(&memberBase, 1.1));

    QEXTConstVolatileMemberFunctor<void, MemberBase, bool> voidConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB1);
    voidConstVolatileMemberBaseFunctorB(&memberBase, 1);
    QVERIFY("MemberBase::voidConstVolatileFunctionB1" == *sg_memberString);
    QEXTConstVolatileMemberFunctor<int, MemberBase, bool> intConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB1);
    QVERIFY(1 == intConstVolatileMemberBaseFunctorB(&memberBase, true));
    QVERIFY(0 == intConstVolatileMemberBaseFunctorB(&memberBase, false));
    QEXTConstVolatileMemberFunctor<double, MemberBase, bool> doubleConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB1);
    QVERIFY(1 == doubleConstVolatileMemberBaseFunctorB(&memberBase, true));
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctorB(&memberBase, false));
}

void QEXTMemberFunctorTest::testPolymorphismConstVolatileFunctorWith1Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTConstVolatileMemberFunctor<void, MemberBase, int> voidConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstVolatileFunction1);
    voidConstVolatileMemberBaseFunctor(&member, 1);
    QVERIFY("Member::voidConstVolatileFunction1" == *sg_memberString);
    QEXTConstVolatileMemberFunctor<int, MemberBase, int> intConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstVolatileFunction1);
    QVERIFY(0 == intConstVolatileMemberBaseFunctor(&member, 1));
    QEXTConstVolatileMemberFunctor<double, MemberBase, double> doubleConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction1);
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctor(&member, 1.1));

    QEXTConstVolatileMemberFunctor<void, MemberBase, bool> voidConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB1);
    voidConstVolatileMemberBaseFunctorB(&member, 1);
    QVERIFY("Member::voidConstVolatileFunctionB1" == *sg_memberString);
    QEXTConstVolatileMemberFunctor<int, MemberBase, bool> intConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB1);
    QVERIFY(1 == intConstVolatileMemberBaseFunctorB(&member, true));
    QVERIFY(0 == intConstVolatileMemberBaseFunctorB(&member, false));
    QEXTConstVolatileMemberFunctor<double, MemberBase, bool> doubleConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB1);
    QVERIFY(1 == doubleConstVolatileMemberBaseFunctorB(&member, true));
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctorB(&member, false));
}

void QEXTMemberFunctorTest::testBoundFunctorWith1Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTBoundMemberFunctor<void, MemberBase, int> voidBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidFunction1);
    voidBoundMemberBaseFunctor(1);
    QVERIFY("MemberBase::voidFunction1" == *sg_memberString);
    QEXTBoundMemberFunctor<int, MemberBase, int> intBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intFunction1);
    QVERIFY(1 == intBoundMemberBaseFunctor(1));
    QEXTBoundMemberFunctor<double, MemberBase, double> doubleBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleFunction1);
    QVERIFY(1.1 == doubleBoundMemberBaseFunctor(1.1));

    QEXTBoundMemberFunctor<void, MemberBase, bool> voidBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidFunctionB1);
    voidBoundMemberBaseFunctorB(1);
    QVERIFY("MemberBase::voidFunctionB1" == *sg_memberString);
    QEXTBoundMemberFunctor<int, MemberBase, bool> intBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intFunctionB1);
    QVERIFY(1 == intBoundMemberBaseFunctorB(true));
    QVERIFY(0 == intBoundMemberBaseFunctorB(false));
    QEXTBoundMemberFunctor<double, MemberBase, bool> doubleBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleFunctionB1);
    QVERIFY(1 == doubleBoundMemberBaseFunctorB(true));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB(false));
}

void QEXTMemberFunctorTest::testPolymorphismBoundFunctorWith1Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTBoundMemberFunctor<void, MemberBase, int> voidBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction1);
    voidBoundMemberBaseFunctor(1);
    QVERIFY("Member::voidFunction1" == *sg_memberString);
    QEXTBoundMemberFunctor<int, MemberBase, int> intBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction1);
    QVERIFY(0 == intBoundMemberBaseFunctor(1));
    QEXTBoundMemberFunctor<double, MemberBase, double> doubleBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction1);
    QVERIFY(0 == doubleBoundMemberBaseFunctor(1.1));

    QEXTBoundMemberFunctor<void, MemberBase, bool> voidBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunctionB1);
    voidBoundMemberBaseFunctorB(1);
    QVERIFY("Member::voidFunctionB1" == *sg_memberString);
    QEXTBoundMemberFunctor<int, MemberBase, bool> intBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunctionB1);
    QVERIFY(1 == intBoundMemberBaseFunctorB(true));
    QVERIFY(0 == intBoundMemberBaseFunctorB(false));
    QEXTBoundMemberFunctor<double, MemberBase, bool> doubleBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunctionB1);
    QVERIFY(1 == doubleBoundMemberBaseFunctorB(true));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB(false));
}

void QEXTMemberFunctorTest::testBoundConstFunctorWith1Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTBoundConstMemberFunctor<void, MemberBase, int> voidBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunction1);
    voidBoundConstMemberBaseFunctor(1);
    QVERIFY("MemberBase::voidConstFunction1" == *sg_memberString);
    QEXTBoundConstMemberFunctor<int, MemberBase, int> intBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intConstFunction1);
    QVERIFY(1 == intBoundConstMemberBaseFunctor(1));
    QEXTBoundConstMemberFunctor<double, MemberBase, double> doubleBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunction1);
    QVERIFY(1.1 == doubleBoundConstMemberBaseFunctor(1.1));

    QEXTBoundConstMemberFunctor<void, MemberBase, bool> voidBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunctionB1);
    voidBoundConstMemberBaseFunctorB(1);
    QVERIFY("MemberBase::voidConstFunctionB1" == *sg_memberString);
    QEXTBoundConstMemberFunctor<int, MemberBase, bool> intBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intConstFunctionB1);
    QVERIFY(1 == intBoundConstMemberBaseFunctorB(true));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB(false));
    QEXTBoundConstMemberFunctor<double, MemberBase, bool> doubleBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunctionB1);
    QVERIFY(1 == doubleBoundConstMemberBaseFunctorB(true));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB(false));
}

void QEXTMemberFunctorTest::testPolymorphismBoundConstFunctorWith1Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTBoundConstMemberFunctor<void, MemberBase, int> voidBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction1);
    voidBoundConstMemberBaseFunctor(1);
    QVERIFY("Member::voidConstFunction1" == *sg_memberString);
    QEXTBoundConstMemberFunctor<int, MemberBase, int> intBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction1);
    QVERIFY(0 == intBoundConstMemberBaseFunctor(1));
    QEXTBoundConstMemberFunctor<double, MemberBase, double> doubleBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction1);
    QVERIFY(0 == doubleBoundConstMemberBaseFunctor(1.1));

    QEXTBoundConstMemberFunctor<void, MemberBase, bool> voidBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunctionB1);
    voidBoundConstMemberBaseFunctorB(1);
    QVERIFY("Member::voidConstFunctionB1" == *sg_memberString);
    QEXTBoundConstMemberFunctor<int, MemberBase, bool> intBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunctionB1);
    QVERIFY(1 == intBoundConstMemberBaseFunctorB(true));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB(false));
    QEXTBoundConstMemberFunctor<double, MemberBase, bool> doubleBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunctionB1);
    QVERIFY(1 == doubleBoundConstMemberBaseFunctorB(true));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB(false));
}

void QEXTMemberFunctorTest::testBoundVolatileFunctorWith1Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTBoundVolatileMemberFunctor<void, MemberBase, int> voidBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunction1);
    voidBoundVolatileMemberBaseFunctor(1);
    QVERIFY("MemberBase::voidVolatileFunction1" == *sg_memberString);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, int> intBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunction1);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctor(1));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, double> doubleBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunction1);
    QVERIFY(1.1 == doubleBoundVolatileMemberBaseFunctor(1.1));

    QEXTBoundVolatileMemberFunctor<void, MemberBase, bool> voidBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunctionB1);
    voidBoundVolatileMemberBaseFunctorB(1);
    QVERIFY("MemberBase::voidVolatileFunctionB1" == *sg_memberString);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, bool> intBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunctionB1);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctorB(true));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB(false));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, bool> doubleBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunctionB1);
    QVERIFY(1 == doubleBoundVolatileMemberBaseFunctorB(true));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB(false));
}

void QEXTMemberFunctorTest::testPolymorphismBoundVolatileFunctorWith1Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTBoundVolatileMemberFunctor<void, MemberBase, int> voidBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction1);
    voidBoundVolatileMemberBaseFunctor(1);
    QVERIFY("Member::voidVolatileFunction1" == *sg_memberString);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, int> intBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction1);
    QVERIFY(0 == intBoundVolatileMemberBaseFunctor(1));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, double> doubleBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction1);
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctor(1.1));

    QEXTBoundVolatileMemberFunctor<void, MemberBase, bool> voidBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunctionB1);
    voidBoundVolatileMemberBaseFunctorB(1);
    QVERIFY("Member::voidVolatileFunctionB1" == *sg_memberString);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, bool> intBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunctionB1);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctorB(true));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB(false));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, bool> doubleBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunctionB1);
    QVERIFY(1 == doubleBoundVolatileMemberBaseFunctorB(true));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB(false));
}

void QEXTMemberFunctorTest::testBoundConstVolatileFunctorWith1Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, int> voidBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunction1);
    voidBoundConstVolatileMemberBaseFunctor(1);
    QVERIFY("MemberBase::voidConstVolatileFunction1" == *sg_memberString);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, int> intBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunction1);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctor(1));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, double> doubleBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction1);
    QVERIFY(1.1 == doubleBoundConstVolatileMemberBaseFunctor(1.1));

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, bool> voidBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunctionB1);
    voidBoundConstVolatileMemberBaseFunctorB(1);
    QVERIFY("MemberBase::voidConstVolatileFunctionB1" == *sg_memberString);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, bool> intBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunctionB1);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctorB(true));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB(false));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, bool> doubleBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunctionB1);
    QVERIFY(1 == doubleBoundConstVolatileMemberBaseFunctorB(true));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB(false));
}

void QEXTMemberFunctorTest::testPolymorphismBoundConstVolatileFunctorWith1Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, int> voidBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction1);
    voidBoundConstVolatileMemberBaseFunctor(1);
    QVERIFY("Member::voidConstVolatileFunction1" == *sg_memberString);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, int> intBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction1);
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctor(1));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, double> doubleBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction1);
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctor(1.1));

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, bool> voidBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunctionB1);
    voidBoundConstVolatileMemberBaseFunctorB(1);
    QVERIFY("Member::voidConstVolatileFunctionB1" == *sg_memberString);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, bool> intBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunctionB1);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctorB(true));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB(false));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, bool> doubleBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunctionB1);
    QVERIFY(1 == doubleBoundConstVolatileMemberBaseFunctorB(true));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB(false));
}

void QEXTMemberFunctorTest::testFunctorWith2Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTMemberFunctor<void, MemberBase, int, int> voidMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidFunction2);
    voidMemberBaseFunctor(&memberBase, 1, 2);
    QVERIFY("MemberBase::voidFunction2" == *sg_memberString);
    QEXTMemberFunctor<int, MemberBase, int, int> intMemberBaseFunctor = qextMemberFunctor(&MemberBase::intFunction2);
    QVERIFY(1 + 2 == intMemberBaseFunctor(&memberBase, 1, 2));
    QEXTMemberFunctor<double, MemberBase, double, double> doubleMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleFunction2);
    QVERIFY(1.1 + 2.2 == doubleMemberBaseFunctor(&memberBase, 1.1, 2.2));

    QEXTMemberFunctor<void, MemberBase, bool, int> voidMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidFunctionB2);
    voidMemberBaseFunctorB(&memberBase, true, 2);
    QVERIFY("MemberBase::voidFunctionB2" == *sg_memberString);
    QEXTMemberFunctor<int, MemberBase, bool, int> intMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intFunctionB2);
    QVERIFY(2 == intMemberBaseFunctorB(&memberBase, true, 2));
    QVERIFY(0 == intMemberBaseFunctorB(&memberBase, false, 2));
    QEXTMemberFunctor<double, MemberBase, bool, double> doubleMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleFunctionB2);
    QVERIFY(2.2 == doubleMemberBaseFunctorB(&memberBase, true, 2.2));
    QVERIFY(0 == doubleMemberBaseFunctorB(&memberBase, false, 2.2));
}

void QEXTMemberFunctorTest::testPolymorphismFunctorWith2Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTMemberFunctor<void, MemberBase, int, int> voidMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidFunction2);
    voidMemberBaseFunctor(&member, 1, 2);
    QVERIFY("Member::voidFunction2" == *sg_memberString);
    QEXTMemberFunctor<int, MemberBase, int, int> intMemberBaseFunctor = qextMemberFunctor(&MemberBase::intFunction2);
    QVERIFY(0 == intMemberBaseFunctor(&member, 1, 2));
    QEXTMemberFunctor<double, MemberBase, double, double> doubleMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleFunction2);
    QVERIFY(0 == doubleMemberBaseFunctor(&member, 1.1, 2.2));

    QEXTMemberFunctor<void, MemberBase, bool, int> voidMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidFunctionB2);
    voidMemberBaseFunctorB(&member, true, 2);
    QVERIFY("Member::voidFunctionB2" == *sg_memberString);
    QEXTMemberFunctor<int, MemberBase, bool, int> intMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intFunctionB2);
    QVERIFY(1 == intMemberBaseFunctorB(&member, true, 2));
    QVERIFY(0 == intMemberBaseFunctorB(&member, false, 2));
    QEXTMemberFunctor<double, MemberBase, bool, double> doubleMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleFunctionB2);
    QVERIFY(1 == doubleMemberBaseFunctorB(&member, true, 2.2));
    QVERIFY(0 == doubleMemberBaseFunctorB(&member, false, 2.2));
}

void QEXTMemberFunctorTest::testConstFunctorWith2Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTConstMemberFunctor<void, MemberBase, int, int> voidConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstFunction2);
    voidConstMemberBaseFunctor(&memberBase, 1, 2);
    QVERIFY("MemberBase::voidConstFunction2" == *sg_memberString);
    QEXTConstMemberFunctor<int, MemberBase, int, int> intConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstFunction2);
    QVERIFY(1 + 2 == intConstMemberBaseFunctor(&memberBase, 1, 2));
    QEXTConstMemberFunctor<double, MemberBase, double, double> doubleConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstFunction2);
    QVERIFY(1.1 + 2.2 == doubleConstMemberBaseFunctor(&memberBase, 1.1, 2.2));

    QEXTConstMemberFunctor<void, MemberBase, bool, int> voidConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstFunctionB2);
    voidConstMemberBaseFunctorB(&memberBase, true, 2);
    QVERIFY("MemberBase::voidConstFunctionB2" == *sg_memberString);
    QEXTConstMemberFunctor<int, MemberBase, bool, int> intConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstFunctionB2);
    QVERIFY(2 == intConstMemberBaseFunctorB(&memberBase, true, 2));
    QVERIFY(0 == intConstMemberBaseFunctorB(&memberBase, false, 2));
    QEXTConstMemberFunctor<double, MemberBase, bool, double> doubleConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstFunctionB2);
    QVERIFY(2.2 == doubleConstMemberBaseFunctorB(&memberBase, true, 2.2));
    QVERIFY(0 == doubleConstMemberBaseFunctorB(&memberBase, false, 2.2));
}

void QEXTMemberFunctorTest::testPolymorphismConstFunctorWith2Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTConstMemberFunctor<void, MemberBase, int, int> voidConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstFunction2);
    voidConstMemberBaseFunctor(&member, 1, 2);
    QVERIFY("Member::voidConstFunction2" == *sg_memberString);
    QEXTConstMemberFunctor<int, MemberBase, int, int> intConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstFunction2);
    QVERIFY(0 == intConstMemberBaseFunctor(&member, 1, 2));
    QEXTConstMemberFunctor<double, MemberBase, double, double> doubleConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstFunction2);
    QVERIFY(0 == doubleConstMemberBaseFunctor(&member, 1.1, 2.2));

    QEXTConstMemberFunctor<void, MemberBase, bool, int> voidConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstFunctionB2);
    voidConstMemberBaseFunctorB(&member, true, 2);
    QVERIFY("Member::voidConstFunctionB2" == *sg_memberString);
    QEXTConstMemberFunctor<int, MemberBase, bool, int> intConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstFunctionB2);
    QVERIFY(1 == intConstMemberBaseFunctorB(&member, true, 2));
    QVERIFY(0 == intConstMemberBaseFunctorB(&member, false, 2));
    QEXTConstMemberFunctor<double, MemberBase, bool, double> doubleConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstFunctionB2);
    QVERIFY(1 == doubleConstMemberBaseFunctorB(&member, true, 2.2));
    QVERIFY(0 == doubleConstMemberBaseFunctorB(&member, false, 2.2));
}

void QEXTMemberFunctorTest::testVolatileFunctorWith2Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTVolatileMemberFunctor<void, MemberBase, int, int> voidVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidVolatileFunction2);
    voidVolatileMemberBaseFunctor(&memberBase, 1, 2);
    QVERIFY("MemberBase::voidVolatileFunction2" == *sg_memberString);
    QEXTVolatileMemberFunctor<int, MemberBase, int, int> intVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intVolatileFunction2);
    QVERIFY(1 + 2 == intVolatileMemberBaseFunctor(&memberBase, 1, 2));
    QEXTVolatileMemberFunctor<double, MemberBase, double, double> doubleVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleVolatileFunction2);
    QVERIFY(1.1 + 2.2 == doubleVolatileMemberBaseFunctor(&memberBase, 1.1, 2.2));

    QEXTVolatileMemberFunctor<void, MemberBase, bool, int> voidVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidVolatileFunctionB2);
    voidVolatileMemberBaseFunctorB(&memberBase, true, 2);
    QVERIFY("MemberBase::voidVolatileFunctionB2" == *sg_memberString);
    QEXTVolatileMemberFunctor<int, MemberBase, bool, int> intVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intVolatileFunctionB2);
    QVERIFY(2 == intVolatileMemberBaseFunctorB(&memberBase, true, 2));
    QVERIFY(0 == intVolatileMemberBaseFunctorB(&memberBase, false, 2));
    QEXTVolatileMemberFunctor<double, MemberBase, bool, double> doubleVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB2);
    QVERIFY(2.2 == doubleVolatileMemberBaseFunctorB(&memberBase, true, 2.2));
    QVERIFY(0 == doubleVolatileMemberBaseFunctorB(&memberBase, false, 2.2));
}

void QEXTMemberFunctorTest::testPolymorphismVolatileFunctorWith2Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTVolatileMemberFunctor<void, MemberBase, int, int> voidVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidVolatileFunction2);
    voidVolatileMemberBaseFunctor(&member, 1, 2);
    QVERIFY("Member::voidVolatileFunction2" == *sg_memberString);
    QEXTVolatileMemberFunctor<int, MemberBase, int, int> intVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intVolatileFunction2);
    QVERIFY(0 == intVolatileMemberBaseFunctor(&member, 1, 2));
    QEXTVolatileMemberFunctor<double, MemberBase, double, double> doubleVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleVolatileFunction2);
    QVERIFY(0 == doubleVolatileMemberBaseFunctor(&member, 1.1, 2.2));

    QEXTVolatileMemberFunctor<void, MemberBase, bool, int> voidVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidVolatileFunctionB2);
    voidVolatileMemberBaseFunctorB(&member, true, 2);
    QVERIFY("Member::voidVolatileFunctionB2" == *sg_memberString);
    QEXTVolatileMemberFunctor<int, MemberBase, bool, int> intVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intVolatileFunctionB2);
    QVERIFY(1 == intVolatileMemberBaseFunctorB(&member, true, 2));
    QVERIFY(0 == intVolatileMemberBaseFunctorB(&member, false, 2));
    QEXTVolatileMemberFunctor<double, MemberBase, bool, double> doubleVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB2);
    QVERIFY(1 == doubleVolatileMemberBaseFunctorB(&member, true, 2.2));
    QVERIFY(0 == doubleVolatileMemberBaseFunctorB(&member, false, 2.2));
}

void QEXTMemberFunctorTest::testConstVolatileFunctorWith2Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTConstVolatileMemberFunctor<void, MemberBase, int, int> voidConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstVolatileFunction2);
    voidConstVolatileMemberBaseFunctor(&memberBase, 1, 2);
    QVERIFY("MemberBase::voidConstVolatileFunction2" == *sg_memberString);
    QEXTConstVolatileMemberFunctor<int, MemberBase, int, int> intConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstVolatileFunction2);
    QVERIFY(1 + 2 == intConstVolatileMemberBaseFunctor(&memberBase, 1, 2));
    QEXTConstVolatileMemberFunctor<double, MemberBase, double, double> doubleConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction2);
    QVERIFY(1.1 + 2.2 == doubleConstVolatileMemberBaseFunctor(&memberBase, 1.1, 2.2));

    QEXTConstVolatileMemberFunctor<void, MemberBase, bool, int> voidConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB2);
    voidConstVolatileMemberBaseFunctorB(&memberBase, true, 2);
    QVERIFY("MemberBase::voidConstVolatileFunctionB2" == *sg_memberString);
    QEXTConstVolatileMemberFunctor<int, MemberBase, bool, int> intConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB2);
    QVERIFY(2 == intConstVolatileMemberBaseFunctorB(&memberBase, true, 2));
    QVERIFY(0 == intConstVolatileMemberBaseFunctorB(&memberBase, false, 2));
    QEXTConstVolatileMemberFunctor<double, MemberBase, bool, double> doubleConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB2);
    QVERIFY(2.2 == doubleConstVolatileMemberBaseFunctorB(&memberBase, true, 2.2));
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctorB(&memberBase, false, 2.2));
}

void QEXTMemberFunctorTest::testPolymorphismConstVolatileFunctorWith2Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTConstVolatileMemberFunctor<void, MemberBase, int, int> voidConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstVolatileFunction2);
    voidConstVolatileMemberBaseFunctor(&member, 1, 2);
    QVERIFY("Member::voidConstVolatileFunction2" == *sg_memberString);
    QEXTConstVolatileMemberFunctor<int, MemberBase, int, int> intConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstVolatileFunction2);
    QVERIFY(0 == intConstVolatileMemberBaseFunctor(&member, 1, 2));
    QEXTConstVolatileMemberFunctor<double, MemberBase, double, double> doubleConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction2);
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctor(&member, 1.1, 2.2));

    QEXTConstVolatileMemberFunctor<void, MemberBase, bool, int> voidConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB2);
    voidConstVolatileMemberBaseFunctorB(&member, true, 2);
    QVERIFY("Member::voidConstVolatileFunctionB2" == *sg_memberString);
    QEXTConstVolatileMemberFunctor<int, MemberBase, bool, int> intConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB2);
    QVERIFY(1 == intConstVolatileMemberBaseFunctorB(&member, true, 2));
    QVERIFY(0 == intConstVolatileMemberBaseFunctorB(&member, false, 2));
    QEXTConstVolatileMemberFunctor<double, MemberBase, bool, double> doubleConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB2);
    QVERIFY(1 == doubleConstVolatileMemberBaseFunctorB(&member, true, 2.2));
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctorB(&member, false, 2.2));
}

void QEXTMemberFunctorTest::testBoundFunctorWith2Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTBoundMemberFunctor<void, MemberBase, int, int> voidBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidFunction2);
    voidBoundMemberBaseFunctor(1, 2);
    QVERIFY("MemberBase::voidFunction2" == *sg_memberString);
    QEXTBoundMemberFunctor<int, MemberBase, int, int> intBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intFunction2);
    QVERIFY(1 + 2 == intBoundMemberBaseFunctor(1, 2));
    QEXTBoundMemberFunctor<double, MemberBase, double, double> doubleBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleFunction2);
    QVERIFY(1.1 + 2.2 == doubleBoundMemberBaseFunctor(1.1, 2.2));

    QEXTBoundMemberFunctor<void, MemberBase, bool, int> voidBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidFunctionB2);
    voidBoundMemberBaseFunctorB(true, 2);
    QVERIFY("MemberBase::voidFunctionB2" == *sg_memberString);
    QEXTBoundMemberFunctor<int, MemberBase, bool, int> intBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intFunctionB2);
    QVERIFY(2 == intBoundMemberBaseFunctorB(true, 2));
    QVERIFY(0 == intBoundMemberBaseFunctorB(false, 2));
    QEXTBoundMemberFunctor<double, MemberBase, bool, double> doubleBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleFunctionB2);
    QVERIFY(2.2 == doubleBoundMemberBaseFunctorB(true, 2.2));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB(false, 2.2));
}

void QEXTMemberFunctorTest::testPolymorphismBoundFunctorWith2Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTBoundMemberFunctor<void, MemberBase, int, int> voidBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction2);
    voidBoundMemberBaseFunctor(1, 2);
    QVERIFY("Member::voidFunction2" == *sg_memberString);
    QEXTBoundMemberFunctor<int, MemberBase, int, int> intBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction2);
    QVERIFY(0 == intBoundMemberBaseFunctor(1, 2));
    QEXTBoundMemberFunctor<double, MemberBase, double, double> doubleBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction2);
    QVERIFY(0 == doubleBoundMemberBaseFunctor(1.1, 2.2));

    QEXTBoundMemberFunctor<void, MemberBase, bool, int> voidBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunctionB2);
    voidBoundMemberBaseFunctorB(true, 2);
    QVERIFY("Member::voidFunctionB2" == *sg_memberString);
    QEXTBoundMemberFunctor<int, MemberBase, bool, int> intBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunctionB2);
    QVERIFY(1 == intBoundMemberBaseFunctorB(true, 2));
    QVERIFY(0 == intBoundMemberBaseFunctorB(false, 2));
    QEXTBoundMemberFunctor<double, MemberBase, bool, double> doubleBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunctionB2);
    QVERIFY(1 == doubleBoundMemberBaseFunctorB(true, 2.2));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB(false, 2.2));
}

void QEXTMemberFunctorTest::testBoundConstFunctorWith2Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTBoundConstMemberFunctor<void, MemberBase, int, int> voidBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunction2);
    voidBoundConstMemberBaseFunctor(1, 2);
    QVERIFY("MemberBase::voidConstFunction2" == *sg_memberString);
    QEXTBoundConstMemberFunctor<int, MemberBase, int, int> intBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intConstFunction2);
    QVERIFY(1 + 2 == intBoundConstMemberBaseFunctor(1, 2));
    QEXTBoundConstMemberFunctor<double, MemberBase, double, double> doubleBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunction2);
    QVERIFY(1.1 + 2.2 == doubleBoundConstMemberBaseFunctor(1.1, 2.2));

    QEXTBoundConstMemberFunctor<void, MemberBase, bool, int> voidBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunctionB2);
    voidBoundConstMemberBaseFunctorB(true, 2);
    QVERIFY("MemberBase::voidConstFunctionB2" == *sg_memberString);
    QEXTBoundConstMemberFunctor<int, MemberBase, bool, int> intBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intConstFunctionB2);
    QVERIFY(2 == intBoundConstMemberBaseFunctorB(true, 2));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB(false, 2));
    QEXTBoundConstMemberFunctor<double, MemberBase, bool, double> doubleBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunctionB2);
    QVERIFY(2.2 == doubleBoundConstMemberBaseFunctorB(true, 2.2));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB(false, 2.2));
}

void QEXTMemberFunctorTest::testPolymorphismBoundConstFunctorWith2Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTBoundConstMemberFunctor<void, MemberBase, int, int> voidBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction2);
    voidBoundConstMemberBaseFunctor(1, 2);
    QVERIFY("Member::voidConstFunction2" == *sg_memberString);
    QEXTBoundConstMemberFunctor<int, MemberBase, int, int> intBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction2);
    QVERIFY(0 == intBoundConstMemberBaseFunctor(1, 2));
    QEXTBoundConstMemberFunctor<double, MemberBase, double, double> doubleBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction2);
    QVERIFY(0 == doubleBoundConstMemberBaseFunctor(1.1, 2.2));

    QEXTBoundConstMemberFunctor<void, MemberBase, bool, int> voidBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunctionB2);
    voidBoundConstMemberBaseFunctorB(true, 2);
    QVERIFY("Member::voidConstFunctionB2" == *sg_memberString);
    QEXTBoundConstMemberFunctor<int, MemberBase, bool, int> intBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunctionB2);
    QVERIFY(1 == intBoundConstMemberBaseFunctorB(true, 2));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB(false, 2));
    QEXTBoundConstMemberFunctor<double, MemberBase, bool, double> doubleBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunctionB2);
    QVERIFY(1 == doubleBoundConstMemberBaseFunctorB(true, 2.2));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB(false, 2.2));
}

void QEXTMemberFunctorTest::testBoundVolatileFunctorWith2Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTBoundVolatileMemberFunctor<void, MemberBase, int, int> voidBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunction2);
    voidBoundVolatileMemberBaseFunctor(1, 2);
    QVERIFY("MemberBase::voidVolatileFunction2" == *sg_memberString);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, int, int> intBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunction2);
    QVERIFY(1 + 2 == intBoundVolatileMemberBaseFunctor(1, 2));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, double, double> doubleBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunction2);
    QVERIFY(1.1 + 2.2 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2));

    QEXTBoundVolatileMemberFunctor<void, MemberBase, bool, int> voidBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunctionB2);
    voidBoundVolatileMemberBaseFunctorB(true, 2);
    QVERIFY("MemberBase::voidVolatileFunctionB2" == *sg_memberString);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, bool, int> intBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunctionB2);
    QVERIFY(2 == intBoundVolatileMemberBaseFunctorB(true, 2));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB(false, 2));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, bool, double> doubleBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunctionB2);
    QVERIFY(2.2 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2));
}

void QEXTMemberFunctorTest::testPolymorphismBoundVolatileFunctorWith2Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTBoundVolatileMemberFunctor<void, MemberBase, int, int> voidBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction2);
    voidBoundVolatileMemberBaseFunctor(1, 2);
    QVERIFY("Member::voidVolatileFunction2" == *sg_memberString);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, int, int> intBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction2);
    QVERIFY(0 == intBoundVolatileMemberBaseFunctor(1, 2));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, double, double> doubleBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction2);
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2));

    QEXTBoundVolatileMemberFunctor<void, MemberBase, bool, int> voidBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunctionB2);
    voidBoundVolatileMemberBaseFunctorB(true, 2);
    QVERIFY("Member::voidVolatileFunctionB2" == *sg_memberString);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, bool, int> intBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunctionB2);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctorB(true, 2));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB(false, 2));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, bool, double> doubleBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunctionB2);
    QVERIFY(1 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2));
}

void QEXTMemberFunctorTest::testBoundConstVolatileFunctorWith2Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, int, int> voidBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunction2);
    voidBoundConstVolatileMemberBaseFunctor(1, 2);
    QVERIFY("MemberBase::voidConstVolatileFunction2" == *sg_memberString);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, int, int> intBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunction2);
    QVERIFY(1 + 2 == intBoundConstVolatileMemberBaseFunctor(1, 2));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, double, double> doubleBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction2);
    QVERIFY(1.1 + 2.2 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2));

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, bool, int> voidBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunctionB2);
    voidBoundConstVolatileMemberBaseFunctorB(true, 2);
    QVERIFY("MemberBase::voidConstVolatileFunctionB2" == *sg_memberString);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, bool, int> intBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunctionB2);
    QVERIFY(2 == intBoundConstVolatileMemberBaseFunctorB(true, 2));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB(false, 2));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, bool, double> doubleBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunctionB2);
    QVERIFY(2.2 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2));
}

void QEXTMemberFunctorTest::testPolymorphismBoundConstVolatileFunctorWith2Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, int, int> voidBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction2);
    voidBoundConstVolatileMemberBaseFunctor(1, 2);
    QVERIFY("Member::voidConstVolatileFunction2" == *sg_memberString);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, int, int> intBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction2);
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctor(1, 2));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, double, double> doubleBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction2);
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2));

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, bool, int> voidBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunctionB2);
    voidBoundConstVolatileMemberBaseFunctorB(true, 2);
    QVERIFY("Member::voidConstVolatileFunctionB2" == *sg_memberString);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, bool, int> intBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunctionB2);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctorB(true, 2));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB(false, 2));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, bool, double> doubleBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunctionB2);
    QVERIFY(1 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2));
}

void QEXTMemberFunctorTest::testFunctorWith3Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTMemberFunctor<void, MemberBase, int, int, int> voidMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidFunction3);
    voidMemberBaseFunctor(&memberBase, 1, 2, 3);
    QVERIFY("MemberBase::voidFunction3" == *sg_memberString);
    QEXTMemberFunctor<int, MemberBase, int, int, int> intMemberBaseFunctor = qextMemberFunctor(&MemberBase::intFunction3);
    QVERIFY(1 + 2 + 3 == intMemberBaseFunctor(&memberBase, 1, 2, 3));
    QEXTMemberFunctor<double, MemberBase, double, double, double> doubleMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3));

    QEXTMemberFunctor<void, MemberBase, bool, int, int> voidMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidFunctionB3);
    voidMemberBaseFunctorB(&memberBase, true, 2, 3);
    QVERIFY("MemberBase::voidFunctionB3" == *sg_memberString);
    QEXTMemberFunctor<int, MemberBase, bool, int, int> intMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intFunctionB3);
    QVERIFY(2 + 3 == intMemberBaseFunctorB(&memberBase, true, 2, 3));
    QVERIFY(2 * 3 == intMemberBaseFunctorB(&memberBase, false, 2, 3));
    QEXTMemberFunctor<double, MemberBase, bool, double, double> doubleMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleMemberBaseFunctorB(&memberBase, true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleMemberBaseFunctorB(&memberBase, false, 2.2, 3.3));
}

void QEXTMemberFunctorTest::testPolymorphismFunctorWith3Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTMemberFunctor<void, MemberBase, int, int, int> voidMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidFunction3);
    voidMemberBaseFunctor(&member, 1, 2, 3);
    QVERIFY("Member::voidFunction3" == *sg_memberString);
    QEXTMemberFunctor<int, MemberBase, int, int, int> intMemberBaseFunctor = qextMemberFunctor(&MemberBase::intFunction3);
    QVERIFY(0 == intMemberBaseFunctor(&member, 1, 2, 3));
    QEXTMemberFunctor<double, MemberBase, double, double, double> doubleMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleFunction3);
    QVERIFY(0 == doubleMemberBaseFunctor(&member, 1.1, 2.2, 3.3));

    QEXTMemberFunctor<void, MemberBase, bool, int, int> voidMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidFunctionB3);
    voidMemberBaseFunctorB(&member, true, 2, 3);
    QVERIFY("Member::voidFunctionB3" == *sg_memberString);
    QEXTMemberFunctor<int, MemberBase, bool, int, int> intMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intFunctionB3);
    QVERIFY(1 == intMemberBaseFunctorB(&member, true, 2, 3));
    QVERIFY(0 == intMemberBaseFunctorB(&member, false, 2, 3));
    QEXTMemberFunctor<double, MemberBase, bool, double, double> doubleMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleFunctionB3);
    QVERIFY(1 == doubleMemberBaseFunctorB(&member, true, 2.2, 3.3));
    QVERIFY(0 == doubleMemberBaseFunctorB(&member, false, 2.2, 3.3));
}

void QEXTMemberFunctorTest::testConstFunctorWith3Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTConstMemberFunctor<void, MemberBase, int, int, int> voidConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstFunction3);
    voidConstMemberBaseFunctor(&memberBase, 1, 2, 3);
    QVERIFY("MemberBase::voidConstFunction3" == *sg_memberString);
    QEXTConstMemberFunctor<int, MemberBase, int, int, int> intConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstFunction3);
    QVERIFY(1 + 2 + 3 == intConstMemberBaseFunctor(&memberBase, 1, 2, 3));
    QEXTConstMemberFunctor<double, MemberBase, double, double, double> doubleConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleConstMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3));

    QEXTConstMemberFunctor<void, MemberBase, bool, int, int> voidConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstFunctionB3);
    voidConstMemberBaseFunctorB(&memberBase, true, 2, 3);
    QVERIFY("MemberBase::voidConstFunctionB3" == *sg_memberString);
    QEXTConstMemberFunctor<int, MemberBase, bool, int, int> intConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstFunctionB3);
    QVERIFY(2 + 3 == intConstMemberBaseFunctorB(&memberBase, true, 2, 3));
    QVERIFY(2 * 3 == intConstMemberBaseFunctorB(&memberBase, false, 2, 3));
    QEXTConstMemberFunctor<double, MemberBase, bool, double, double> doubleConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleConstMemberBaseFunctorB(&memberBase, true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleConstMemberBaseFunctorB(&memberBase, false, 2.2, 3.3));
}

void QEXTMemberFunctorTest::testPolymorphismConstFunctorWith3Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTConstMemberFunctor<void, MemberBase, int, int, int> voidConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstFunction3);
    voidConstMemberBaseFunctor(&member, 1, 2, 3);
    QVERIFY("Member::voidConstFunction3" == *sg_memberString);
    QEXTConstMemberFunctor<int, MemberBase, int, int, int> intConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstFunction3);
    QVERIFY(0 == intConstMemberBaseFunctor(&member, 1, 2, 3));
    QEXTConstMemberFunctor<double, MemberBase, double, double, double> doubleConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstFunction3);
    QVERIFY(0 == doubleConstMemberBaseFunctor(&member, 1.1, 2.2, 3.3));

    QEXTConstMemberFunctor<void, MemberBase, bool, int, int> voidConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstFunctionB3);
    voidConstMemberBaseFunctorB(&member, true, 2, 3);
    QVERIFY("Member::voidConstFunctionB3" == *sg_memberString);
    QEXTConstMemberFunctor<int, MemberBase, bool, int, int> intConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstFunctionB3);
    QVERIFY(1 == intConstMemberBaseFunctorB(&member, true, 2, 3));
    QVERIFY(0 == intConstMemberBaseFunctorB(&member, false, 2, 3));
    QEXTConstMemberFunctor<double, MemberBase, bool, double, double> doubleConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstFunctionB3);
    QVERIFY(1 == doubleConstMemberBaseFunctorB(&member, true, 2.2, 3.3));
    QVERIFY(0 == doubleConstMemberBaseFunctorB(&member, false, 2.2, 3.3));
}

void QEXTMemberFunctorTest::testVolatileFunctorWith3Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTVolatileMemberFunctor<void, MemberBase, int, int, int> voidVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidVolatileFunction3);
    voidVolatileMemberBaseFunctor(&memberBase, 1, 2, 3);
    QVERIFY("MemberBase::voidVolatileFunction3" == *sg_memberString);
    QEXTVolatileMemberFunctor<int, MemberBase, int, int, int> intVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intVolatileFunction3);
    QVERIFY(1 + 2 + 3 == intVolatileMemberBaseFunctor(&memberBase, 1, 2, 3));
    QEXTVolatileMemberFunctor<double, MemberBase, double, double, double> doubleVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleVolatileFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleVolatileMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3));

    QEXTVolatileMemberFunctor<void, MemberBase, bool, int, int> voidVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidVolatileFunctionB3);
    voidVolatileMemberBaseFunctorB(&memberBase, true, 2, 3);
    QVERIFY("MemberBase::voidVolatileFunctionB3" == *sg_memberString);
    QEXTVolatileMemberFunctor<int, MemberBase, bool, int, int> intVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intVolatileFunctionB3);
    QVERIFY(2 + 3 == intVolatileMemberBaseFunctorB(&memberBase, true, 2, 3));
    QVERIFY(2 * 3 == intVolatileMemberBaseFunctorB(&memberBase, false, 2, 3));
    QEXTVolatileMemberFunctor<double, MemberBase, bool, double, double> doubleVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleVolatileMemberBaseFunctorB(&memberBase, true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleVolatileMemberBaseFunctorB(&memberBase, false, 2.2, 3.3));
}

void QEXTMemberFunctorTest::testPolymorphismVolatileFunctorWith3Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTVolatileMemberFunctor<void, MemberBase, int, int, int> voidVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidVolatileFunction3);
    voidVolatileMemberBaseFunctor(&member, 1, 2, 3);
    QVERIFY("Member::voidVolatileFunction3" == *sg_memberString);
    QEXTVolatileMemberFunctor<int, MemberBase, int, int, int> intVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intVolatileFunction3);
    QVERIFY(0 == intVolatileMemberBaseFunctor(&member, 1, 2, 3));
    QEXTVolatileMemberFunctor<double, MemberBase, double, double, double> doubleVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleVolatileFunction3);
    QVERIFY(0 == doubleVolatileMemberBaseFunctor(&member, 1.1, 2.2, 3.3));

    QEXTVolatileMemberFunctor<void, MemberBase, bool, int, int> voidVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidVolatileFunctionB3);
    voidVolatileMemberBaseFunctorB(&member, true, 2, 3);
    QVERIFY("Member::voidVolatileFunctionB3" == *sg_memberString);
    QEXTVolatileMemberFunctor<int, MemberBase, bool, int, int> intVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intVolatileFunctionB3);
    QVERIFY(1 == intVolatileMemberBaseFunctorB(&member, true, 2, 3));
    QVERIFY(0 == intVolatileMemberBaseFunctorB(&member, false, 2, 3));
    QEXTVolatileMemberFunctor<double, MemberBase, bool, double, double> doubleVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB3);
    QVERIFY(1 == doubleVolatileMemberBaseFunctorB(&member, true, 2.2, 3.3));
    QVERIFY(0 == doubleVolatileMemberBaseFunctorB(&member, false, 2.2, 3.3));
}

void QEXTMemberFunctorTest::testConstVolatileFunctorWith3Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTConstVolatileMemberFunctor<void, MemberBase, int, int, int> voidConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstVolatileFunction3);
    voidConstVolatileMemberBaseFunctor(&memberBase, 1, 2, 3);
    QVERIFY("MemberBase::voidConstVolatileFunction3" == *sg_memberString);
    QEXTConstVolatileMemberFunctor<int, MemberBase, int, int, int> intConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstVolatileFunction3);
    QVERIFY(1 + 2 + 3 == intConstVolatileMemberBaseFunctor(&memberBase, 1, 2, 3));
    QEXTConstVolatileMemberFunctor<double, MemberBase, double, double, double> doubleConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleConstVolatileMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3));

    QEXTConstVolatileMemberFunctor<void, MemberBase, bool, int, int> voidConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB3);
    voidConstVolatileMemberBaseFunctorB(&memberBase, true, 2, 3);
    QVERIFY("MemberBase::voidConstVolatileFunctionB3" == *sg_memberString);
    QEXTConstVolatileMemberFunctor<int, MemberBase, bool, int, int> intConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB3);
    QVERIFY(2 + 3 == intConstVolatileMemberBaseFunctorB(&memberBase, true, 2, 3));
    QVERIFY(2 * 3 == intConstVolatileMemberBaseFunctorB(&memberBase, false, 2, 3));
    QEXTConstVolatileMemberFunctor<double, MemberBase, bool, double, double> doubleConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleConstVolatileMemberBaseFunctorB(&memberBase, true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleConstVolatileMemberBaseFunctorB(&memberBase, false, 2.2, 3.3));
}

void QEXTMemberFunctorTest::testPolymorphismConstVolatileFunctorWith3Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTConstVolatileMemberFunctor<void, MemberBase, int, int, int> voidConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstVolatileFunction3);
    voidConstVolatileMemberBaseFunctor(&member, 1, 2, 3);
    QVERIFY("Member::voidConstVolatileFunction3" == *sg_memberString);
    QEXTConstVolatileMemberFunctor<int, MemberBase, int, int, int> intConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstVolatileFunction3);
    QVERIFY(0 == intConstVolatileMemberBaseFunctor(&member, 1, 2, 3));
    QEXTConstVolatileMemberFunctor<double, MemberBase, double, double, double> doubleConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction3);
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctor(&member, 1.1, 2.2, 3.3));

    QEXTConstVolatileMemberFunctor<void, MemberBase, bool, int, int> voidConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB3);
    voidConstVolatileMemberBaseFunctorB(&member, true, 2, 3);
    QVERIFY("Member::voidConstVolatileFunctionB3" == *sg_memberString);
    QEXTConstVolatileMemberFunctor<int, MemberBase, bool, int, int> intConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB3);
    QVERIFY(1 == intConstVolatileMemberBaseFunctorB(&member, true, 2, 3));
    QVERIFY(0 == intConstVolatileMemberBaseFunctorB(&member, false, 2, 3));
    QEXTConstVolatileMemberFunctor<double, MemberBase, bool, double, double> doubleConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB3);
    QVERIFY(1 == doubleConstVolatileMemberBaseFunctorB(&member, true, 2.2, 3.3));
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctorB(&member, false, 2.2, 3.3));
}

void QEXTMemberFunctorTest::testBoundFunctorWith3Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTBoundMemberFunctor<void, MemberBase, int, int, int> voidBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidFunction3);
    voidBoundMemberBaseFunctor(1, 2, 3);
    QVERIFY("MemberBase::voidFunction3" == *sg_memberString);
    QEXTBoundMemberFunctor<int, MemberBase, int, int, int> intBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intFunction3);
    QVERIFY(1 + 2 + 3 == intBoundMemberBaseFunctor(1, 2, 3));
    QEXTBoundMemberFunctor<double, MemberBase, double, double, double> doubleBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleBoundMemberBaseFunctor(1.1, 2.2, 3.3));

    QEXTBoundMemberFunctor<void, MemberBase, bool, int, int> voidBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidFunctionB3);
    voidBoundMemberBaseFunctorB(true, 2, 3);
    QVERIFY("MemberBase::voidFunctionB3" == *sg_memberString);
    QEXTBoundMemberFunctor<int, MemberBase, bool, int, int> intBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intFunctionB3);
    QVERIFY(2 + 3 == intBoundMemberBaseFunctorB(true, 2, 3));
    QVERIFY(2 * 3 == intBoundMemberBaseFunctorB(false, 2, 3));
    QEXTBoundMemberFunctor<double, MemberBase, bool, double, double> doubleBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleBoundMemberBaseFunctorB(true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleBoundMemberBaseFunctorB(false, 2.2, 3.3));
}

void QEXTMemberFunctorTest::testPolymorphismBoundFunctorWith3Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTBoundMemberFunctor<void, MemberBase, int, int, int> voidBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction3);
    voidBoundMemberBaseFunctor(1, 2, 3);
    QVERIFY("Member::voidFunction3" == *sg_memberString);
    QEXTBoundMemberFunctor<int, MemberBase, int, int, int> intBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction3);
    QVERIFY(0 == intBoundMemberBaseFunctor(1, 2, 3));
    QEXTBoundMemberFunctor<double, MemberBase, double, double, double> doubleBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction3);
    QVERIFY(0 == doubleBoundMemberBaseFunctor(1.1, 2.2, 3.3));

    QEXTBoundMemberFunctor<void, MemberBase, bool, int, int> voidBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunctionB3);
    voidBoundMemberBaseFunctorB(true, 2, 3);
    QVERIFY("Member::voidFunctionB3" == *sg_memberString);
    QEXTBoundMemberFunctor<int, MemberBase, bool, int, int> intBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunctionB3);
    QVERIFY(1 == intBoundMemberBaseFunctorB(true, 2, 3));
    QVERIFY(0 == intBoundMemberBaseFunctorB(false, 2, 3));
    QEXTBoundMemberFunctor<double, MemberBase, bool, double, double> doubleBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunctionB3);
    QVERIFY(1 == doubleBoundMemberBaseFunctorB(true, 2.2, 3.3));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB(false, 2.2, 3.3));
}

void QEXTMemberFunctorTest::testBoundConstFunctorWith3Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTBoundConstMemberFunctor<void, MemberBase, int, int, int> voidBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunction3);
    voidBoundConstMemberBaseFunctor(1, 2, 3);
    QVERIFY("MemberBase::voidConstFunction3" == *sg_memberString);
    QEXTBoundConstMemberFunctor<int, MemberBase, int, int, int> intBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intConstFunction3);
    QVERIFY(1 + 2 + 3 == intBoundConstMemberBaseFunctor(1, 2, 3));
    QEXTBoundConstMemberFunctor<double, MemberBase, double, double, double> doubleBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleBoundConstMemberBaseFunctor(1.1, 2.2, 3.3));

    QEXTBoundConstMemberFunctor<void, MemberBase, bool, int, int> voidBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunctionB3);
    voidBoundConstMemberBaseFunctorB(true, 2, 3);
    QVERIFY("MemberBase::voidConstFunctionB3" == *sg_memberString);
    QEXTBoundConstMemberFunctor<int, MemberBase, bool, int, int> intBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intConstFunctionB3);
    QVERIFY(2 + 3 == intBoundConstMemberBaseFunctorB(true, 2, 3));
    QVERIFY(2 * 3 == intBoundConstMemberBaseFunctorB(false, 2, 3));
    QEXTBoundConstMemberFunctor<double, MemberBase, bool, double, double> doubleBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleBoundConstMemberBaseFunctorB(true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleBoundConstMemberBaseFunctorB(false, 2.2, 3.3));
}

void QEXTMemberFunctorTest::testPolymorphismBoundConstFunctorWith3Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTBoundConstMemberFunctor<void, MemberBase, int, int, int> voidBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction3);
    voidBoundConstMemberBaseFunctor(1, 2, 3);
    QVERIFY("Member::voidConstFunction3" == *sg_memberString);
    QEXTBoundConstMemberFunctor<int, MemberBase, int, int, int> intBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction3);
    QVERIFY(0 == intBoundConstMemberBaseFunctor(1, 2, 3));
    QEXTBoundConstMemberFunctor<double, MemberBase, double, double, double> doubleBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction3);
    QVERIFY(0 == doubleBoundConstMemberBaseFunctor(1.1, 2.2, 3.3));

    QEXTBoundConstMemberFunctor<void, MemberBase, bool, int, int> voidBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunctionB3);
    voidBoundConstMemberBaseFunctorB(true, 2, 3);
    QVERIFY("Member::voidConstFunctionB3" == *sg_memberString);
    QEXTBoundConstMemberFunctor<int, MemberBase, bool, int, int> intBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunctionB3);
    QVERIFY(1 == intBoundConstMemberBaseFunctorB(true, 2, 3));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB(false, 2, 3));
    QEXTBoundConstMemberFunctor<double, MemberBase, bool, double, double> doubleBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunctionB3);
    QVERIFY(1 == doubleBoundConstMemberBaseFunctorB(true, 2.2, 3.3));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB(false, 2.2, 3.3));
}

void QEXTMemberFunctorTest::testBoundVolatileFunctorWith3Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTBoundVolatileMemberFunctor<void, MemberBase, int, int, int> voidBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunction3);
    voidBoundVolatileMemberBaseFunctor(1, 2, 3);
    QVERIFY("MemberBase::voidVolatileFunction3" == *sg_memberString);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, int, int, int> intBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunction3);
    QVERIFY(1 + 2 + 3 == intBoundVolatileMemberBaseFunctor(1, 2, 3));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, double, double, double> doubleBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2, 3.3));

    QEXTBoundVolatileMemberFunctor<void, MemberBase, bool, int, int> voidBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunctionB3);
    voidBoundVolatileMemberBaseFunctorB(true, 2, 3);
    QVERIFY("MemberBase::voidVolatileFunctionB3" == *sg_memberString);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, bool, int, int> intBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunctionB3);
    QVERIFY(2 + 3 == intBoundVolatileMemberBaseFunctorB(true, 2, 3));
    QVERIFY(2 * 3 == intBoundVolatileMemberBaseFunctorB(false, 2, 3));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, bool, double, double> doubleBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2, 3.3));
}

void QEXTMemberFunctorTest::testPolymorphismBoundVolatileFunctorWith3Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTBoundVolatileMemberFunctor<void, MemberBase, int, int, int> voidBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction3);
    voidBoundVolatileMemberBaseFunctor(1, 2, 3);
    QVERIFY("Member::voidVolatileFunction3" == *sg_memberString);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, int, int, int> intBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction3);
    QVERIFY(0 == intBoundVolatileMemberBaseFunctor(1, 2, 3));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, double, double, double> doubleBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction3);
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2, 3.3));

    QEXTBoundVolatileMemberFunctor<void, MemberBase, bool, int, int> voidBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunctionB3);
    voidBoundVolatileMemberBaseFunctorB(true, 2, 3);
    QVERIFY("Member::voidVolatileFunctionB3" == *sg_memberString);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, bool, int, int> intBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunctionB3);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctorB(true, 2, 3));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB(false, 2, 3));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, bool, double, double> doubleBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunctionB3);
    QVERIFY(1 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2, 3.3));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2, 3.3));
}

void QEXTMemberFunctorTest::testBoundConstVolatileFunctorWith3Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, int, int, int> voidBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunction3);
    voidBoundConstVolatileMemberBaseFunctor(1, 2, 3);
    QVERIFY("MemberBase::voidConstVolatileFunction3" == *sg_memberString);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, int, int, int> intBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunction3);
    QVERIFY(1 + 2 + 3 == intBoundConstVolatileMemberBaseFunctor(1, 2, 3));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, double, double, double> doubleBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2, 3.3));

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, bool, int, int> voidBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunctionB3);
    voidBoundConstVolatileMemberBaseFunctorB(true, 2, 3);
    QVERIFY("MemberBase::voidConstVolatileFunctionB3" == *sg_memberString);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, bool, int, int> intBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunctionB3);
    QVERIFY(2 + 3 == intBoundConstVolatileMemberBaseFunctorB(true, 2, 3));
    QVERIFY(2 * 3 == intBoundConstVolatileMemberBaseFunctorB(false, 2, 3));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, bool, double, double> doubleBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2, 3.3));
}

void QEXTMemberFunctorTest::testPolymorphismBoundConstVolatileFunctorWith3Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, int, int, int> voidBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction3);
    voidBoundConstVolatileMemberBaseFunctor(1, 2, 3);
    QVERIFY("Member::voidConstVolatileFunction3" == *sg_memberString);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, int, int, int> intBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction3);
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctor(1, 2, 3));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, double, double, double> doubleBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction3);
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2, 3.3));

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, bool, int, int> voidBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunctionB3);
    voidBoundConstVolatileMemberBaseFunctorB(true, 2, 3);
    QVERIFY("Member::voidConstVolatileFunctionB3" == *sg_memberString);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, bool, int, int> intBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunctionB3);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctorB(true, 2, 3));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB(false, 2, 3));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, bool, double, double> doubleBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunctionB3);
    QVERIFY(1 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2, 3.3));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2, 3.3));
}

void QEXTMemberFunctorTest::testFunctorWith4Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTMemberFunctor<void, MemberBase, int, int, int, int> voidMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidFunction4);
    voidMemberBaseFunctor(&memberBase, 1, 2, 3, 4);
    QVERIFY("MemberBase::voidFunction4" == *sg_memberString);
    QEXTMemberFunctor<int, MemberBase, int, int, int, int> intMemberBaseFunctor = qextMemberFunctor(&MemberBase::intFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intMemberBaseFunctor(&memberBase, 1, 2, 3, 4));
    QEXTMemberFunctor<double, MemberBase, double, double, double, double> doubleMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3, 4.4));

    QEXTMemberFunctor<void, MemberBase, bool, int, int, int> voidMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidFunctionB4);
    voidMemberBaseFunctorB(&memberBase, true, 2, 3, 4);
    QVERIFY("MemberBase::voidFunctionB4" == *sg_memberString);
    QEXTMemberFunctor<int, MemberBase, bool, int, int, int> intMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intFunctionB4);
    QVERIFY(2 + 3 + 4 == intMemberBaseFunctorB(&memberBase, true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intMemberBaseFunctorB(&memberBase, false, 2, 3, 4));
    QEXTMemberFunctor<double, MemberBase, bool, double, double, double> doubleMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleMemberBaseFunctorB(&memberBase, true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleMemberBaseFunctorB(&memberBase, false, 2.2, 3.3, 4.4));
}

void QEXTMemberFunctorTest::testPolymorphismFunctorWith4Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTMemberFunctor<void, MemberBase, int, int, int, int> voidMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidFunction4);
    voidMemberBaseFunctor(&member, 1, 2, 3, 4);
    QVERIFY("Member::voidFunction4" == *sg_memberString);
    QEXTMemberFunctor<int, MemberBase, int, int, int, int> intMemberBaseFunctor = qextMemberFunctor(&MemberBase::intFunction4);
    QVERIFY(0 == intMemberBaseFunctor(&member, 1, 2, 3, 4));
    QEXTMemberFunctor<double, MemberBase, double, double, double, double> doubleMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleFunction4);
    QVERIFY(0 == doubleMemberBaseFunctor(&member, 1.1, 2.2, 3.3, 4.4));

    QEXTMemberFunctor<void, MemberBase, bool, int, int, int> voidMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidFunctionB4);
    voidMemberBaseFunctorB(&member, true, 2, 3, 4);
    QVERIFY("Member::voidFunctionB4" == *sg_memberString);
    QEXTMemberFunctor<int, MemberBase, bool, int, int, int> intMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intFunctionB4);
    QVERIFY(1 == intMemberBaseFunctorB(&member, true, 2, 3, 4));
    QVERIFY(0 == intMemberBaseFunctorB(&member, false, 2, 3, 4));
    QEXTMemberFunctor<double, MemberBase, bool, double, double, double> doubleMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleFunctionB4);
    QVERIFY(1 == doubleMemberBaseFunctorB(&member, true, 2.2, 3.3, 4.4));
    QVERIFY(0 == doubleMemberBaseFunctorB(&member, false, 2.2, 3.3, 4.4));
}

void QEXTMemberFunctorTest::testConstFunctorWith4Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTConstMemberFunctor<void, MemberBase, int, int, int, int> voidConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstFunction4);
    voidConstMemberBaseFunctor(&memberBase, 1, 2, 3, 4);
    QVERIFY("MemberBase::voidConstFunction4" == *sg_memberString);
    QEXTConstMemberFunctor<int, MemberBase, int, int, int, int> intConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intConstMemberBaseFunctor(&memberBase, 1, 2, 3, 4));
    QEXTConstMemberFunctor<double, MemberBase, double, double, double, double> doubleConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleConstMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3, 4.4));

    QEXTConstMemberFunctor<void, MemberBase, bool, int, int, int> voidConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstFunctionB4);
    voidConstMemberBaseFunctorB(&memberBase, true, 2, 3, 4);
    QVERIFY("MemberBase::voidConstFunctionB4" == *sg_memberString);
    QEXTConstMemberFunctor<int, MemberBase, bool, int, int, int> intConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstFunctionB4);
    QVERIFY(2 + 3 + 4 == intConstMemberBaseFunctorB(&memberBase, true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intConstMemberBaseFunctorB(&memberBase, false, 2, 3, 4));
    QEXTConstMemberFunctor<double, MemberBase, bool, double, double, double> doubleConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleConstMemberBaseFunctorB(&memberBase, true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleConstMemberBaseFunctorB(&memberBase, false, 2.2, 3.3, 4.4));
}

void QEXTMemberFunctorTest::testPolymorphismConstFunctorWith4Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTConstMemberFunctor<void, MemberBase, int, int, int, int> voidConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstFunction4);
    voidConstMemberBaseFunctor(&member, 1, 2, 3, 4);
    QVERIFY("Member::voidConstFunction4" == *sg_memberString);
    QEXTConstMemberFunctor<int, MemberBase, int, int, int, int> intConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstFunction4);
    QVERIFY(0 == intConstMemberBaseFunctor(&member, 1, 2, 3, 4));
    QEXTConstMemberFunctor<double, MemberBase, double, double, double, double> doubleConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstFunction4);
    QVERIFY(0 == doubleConstMemberBaseFunctor(&member, 1.1, 2.2, 3.3, 4.4));

    QEXTConstMemberFunctor<void, MemberBase, bool, int, int, int> voidConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstFunctionB4);
    voidConstMemberBaseFunctorB(&member, true, 2, 3, 4);
    QVERIFY("Member::voidConstFunctionB4" == *sg_memberString);
    QEXTConstMemberFunctor<int, MemberBase, bool, int, int, int> intConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstFunctionB4);
    QVERIFY(1 == intConstMemberBaseFunctorB(&member, true, 2, 3, 4));
    QVERIFY(0 == intConstMemberBaseFunctorB(&member, false, 2, 3, 4));
    QEXTConstMemberFunctor<double, MemberBase, bool, double, double, double> doubleConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstFunctionB4);
    QVERIFY(1 == doubleConstMemberBaseFunctorB(&member, true, 2.2, 3.3, 4.4));
    QVERIFY(0 == doubleConstMemberBaseFunctorB(&member, false, 2.2, 3.3, 4.4));
}

void QEXTMemberFunctorTest::testVolatileFunctorWith4Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTVolatileMemberFunctor<void, MemberBase, int, int, int, int> voidVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidVolatileFunction4);
    voidVolatileMemberBaseFunctor(&memberBase, 1, 2, 3, 4);
    QVERIFY("MemberBase::voidVolatileFunction4" == *sg_memberString);
    QEXTVolatileMemberFunctor<int, MemberBase, int, int, int, int> intVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intVolatileFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intVolatileMemberBaseFunctor(&memberBase, 1, 2, 3, 4));
    QEXTVolatileMemberFunctor<double, MemberBase, double, double, double, double> doubleVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleVolatileFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleVolatileMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3, 4.4));

    QEXTVolatileMemberFunctor<void, MemberBase, bool, int, int, int> voidVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidVolatileFunctionB4);
    voidVolatileMemberBaseFunctorB(&memberBase, true, 2, 3, 4);
    QVERIFY("MemberBase::voidVolatileFunctionB4" == *sg_memberString);
    QEXTVolatileMemberFunctor<int, MemberBase, bool, int, int, int> intVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intVolatileFunctionB4);
    QVERIFY(2 + 3 + 4 == intVolatileMemberBaseFunctorB(&memberBase, true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intVolatileMemberBaseFunctorB(&memberBase, false, 2, 3, 4));
    QEXTVolatileMemberFunctor<double, MemberBase, bool, double, double, double> doubleVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleVolatileMemberBaseFunctorB(&memberBase, true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleVolatileMemberBaseFunctorB(&memberBase, false, 2.2, 3.3, 4.4));
}

void QEXTMemberFunctorTest::testPolymorphismVolatileFunctorWith4Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTVolatileMemberFunctor<void, MemberBase, int, int, int, int> voidVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidVolatileFunction4);
    voidVolatileMemberBaseFunctor(&member, 1, 2, 3, 4);
    QVERIFY("Member::voidVolatileFunction4" == *sg_memberString);
    QEXTVolatileMemberFunctor<int, MemberBase, int, int, int, int> intVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intVolatileFunction4);
    QVERIFY(0 == intVolatileMemberBaseFunctor(&member, 1, 2, 3, 4));
    QEXTVolatileMemberFunctor<double, MemberBase, double, double, double, double> doubleVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleVolatileFunction4);
    QVERIFY(0 == doubleVolatileMemberBaseFunctor(&member, 1.1, 2.2, 3.3, 4.4));

    QEXTVolatileMemberFunctor<void, MemberBase, bool, int, int, int> voidVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidVolatileFunctionB4);
    voidVolatileMemberBaseFunctorB(&member, true, 2, 3, 4);
    QVERIFY("Member::voidVolatileFunctionB4" == *sg_memberString);
    QEXTVolatileMemberFunctor<int, MemberBase, bool, int, int, int> intVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intVolatileFunctionB4);
    QVERIFY(1 == intVolatileMemberBaseFunctorB(&member, true, 2, 3, 4));
    QVERIFY(0 == intVolatileMemberBaseFunctorB(&member, false, 2, 3, 4));
    QEXTVolatileMemberFunctor<double, MemberBase, bool, double, double, double> doubleVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB4);
    QVERIFY(1 == doubleVolatileMemberBaseFunctorB(&member, true, 2.2, 3.3, 4.4));
    QVERIFY(0 == doubleVolatileMemberBaseFunctorB(&member, false, 2.2, 3.3, 4.4));
}

void QEXTMemberFunctorTest::testConstVolatileFunctorWith4Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTConstVolatileMemberFunctor<void, MemberBase, int, int, int, int> voidConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstVolatileFunction4);
    voidConstVolatileMemberBaseFunctor(&memberBase, 1, 2, 3, 4);
    QVERIFY("MemberBase::voidConstVolatileFunction4" == *sg_memberString);
    QEXTConstVolatileMemberFunctor<int, MemberBase, int, int, int, int> intConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstVolatileFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intConstVolatileMemberBaseFunctor(&memberBase, 1, 2, 3, 4));
    QEXTConstVolatileMemberFunctor<double, MemberBase, double, double, double, double> doubleConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleConstVolatileMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3, 4.4));

    QEXTConstVolatileMemberFunctor<void, MemberBase, bool, int, int, int> voidConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB4);
    voidConstVolatileMemberBaseFunctorB(&memberBase, true, 2, 3, 4);
    QVERIFY("MemberBase::voidConstVolatileFunctionB4" == *sg_memberString);
    QEXTConstVolatileMemberFunctor<int, MemberBase, bool, int, int, int> intConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB4);
    QVERIFY(2 + 3 + 4 == intConstVolatileMemberBaseFunctorB(&memberBase, true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intConstVolatileMemberBaseFunctorB(&memberBase, false, 2, 3, 4));
    QEXTConstVolatileMemberFunctor<double, MemberBase, bool, double, double, double> doubleConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleConstVolatileMemberBaseFunctorB(&memberBase, true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleConstVolatileMemberBaseFunctorB(&memberBase, false, 2.2, 3.3, 4.4));
}

void QEXTMemberFunctorTest::testPolymorphismConstVolatileFunctorWith4Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTConstVolatileMemberFunctor<void, MemberBase, int, int, int, int> voidConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstVolatileFunction4);
    voidConstVolatileMemberBaseFunctor(&member, 1, 2, 3, 4);
    QVERIFY("Member::voidConstVolatileFunction4" == *sg_memberString);
    QEXTConstVolatileMemberFunctor<int, MemberBase, int, int, int, int> intConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstVolatileFunction4);
    QVERIFY(0 == intConstVolatileMemberBaseFunctor(&member, 1, 2, 3, 4));
    QEXTConstVolatileMemberFunctor<double, MemberBase, double, double, double, double> doubleConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction4);
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctor(&member, 1.1, 2.2, 3.3, 4.4));

    QEXTConstVolatileMemberFunctor<void, MemberBase, bool, int, int, int> voidConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB4);
    voidConstVolatileMemberBaseFunctorB(&member, true, 2, 3, 4);
    QVERIFY("Member::voidConstVolatileFunctionB4" == *sg_memberString);
    QEXTConstVolatileMemberFunctor<int, MemberBase, bool, int, int, int> intConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB4);
    QVERIFY(1 == intConstVolatileMemberBaseFunctorB(&member, true, 2, 3, 4));
    QVERIFY(0 == intConstVolatileMemberBaseFunctorB(&member, false, 2, 3, 4));
    QEXTConstVolatileMemberFunctor<double, MemberBase, bool, double, double, double> doubleConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB4);
    QVERIFY(1 == doubleConstVolatileMemberBaseFunctorB(&member, true, 2.2, 3.3, 4.4));
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctorB(&member, false, 2.2, 3.3, 4.4));
}

void QEXTMemberFunctorTest::testBoundFunctorWith4Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTBoundMemberFunctor<void, MemberBase, int, int, int, int> voidBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidFunction4);
    voidBoundMemberBaseFunctor(1, 2, 3, 4);
    QVERIFY("MemberBase::voidFunction4" == *sg_memberString);
    QEXTBoundMemberFunctor<int, MemberBase, int, int, int, int> intBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intBoundMemberBaseFunctor(1, 2, 3, 4));
    QEXTBoundMemberFunctor<double, MemberBase, double, double, double, double> doubleBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleBoundMemberBaseFunctor(1.1, 2.2, 3.3, 4.4));

    QEXTBoundMemberFunctor<void, MemberBase, bool, int, int, int> voidBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidFunctionB4);
    voidBoundMemberBaseFunctorB(true, 2, 3, 4);
    QVERIFY("MemberBase::voidFunctionB4" == *sg_memberString);
    QEXTBoundMemberFunctor<int, MemberBase, bool, int, int, int> intBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intFunctionB4);
    QVERIFY(2 + 3 + 4 == intBoundMemberBaseFunctorB(true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intBoundMemberBaseFunctorB(false, 2, 3, 4));
    QEXTBoundMemberFunctor<double, MemberBase, bool, double, double, double> doubleBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleBoundMemberBaseFunctorB(true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleBoundMemberBaseFunctorB(false, 2.2, 3.3, 4.4));
}

void QEXTMemberFunctorTest::testPolymorphismBoundFunctorWith4Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTBoundMemberFunctor<void, MemberBase, int, int, int, int> voidBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction4);
    voidBoundMemberBaseFunctor(1, 2, 3, 4);
    QVERIFY("Member::voidFunction4" == *sg_memberString);
    QEXTBoundMemberFunctor<int, MemberBase, int, int, int, int> intBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction4);
    QVERIFY(0 == intBoundMemberBaseFunctor(1, 2, 3, 4));
    QEXTBoundMemberFunctor<double, MemberBase, double, double, double, double> doubleBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction4);
    QVERIFY(0 == doubleBoundMemberBaseFunctor(1.1, 2.2, 3.3, 4.4));

    QEXTBoundMemberFunctor<void, MemberBase, bool, int, int, int> voidBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunctionB4);
    voidBoundMemberBaseFunctorB(true, 2, 3, 4);
    QVERIFY("Member::voidFunctionB4" == *sg_memberString);
    QEXTBoundMemberFunctor<int, MemberBase, bool, int, int, int> intBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunctionB4);
    QVERIFY(1 == intBoundMemberBaseFunctorB(true, 2, 3, 4));
    QVERIFY(0 == intBoundMemberBaseFunctorB(false, 2, 3, 4));
    QEXTBoundMemberFunctor<double, MemberBase, bool, double, double, double> doubleBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunctionB4);
    QVERIFY(1 == doubleBoundMemberBaseFunctorB(true, 2.2, 3.3, 4.4));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB(false, 2.2, 3.3, 4.4));
}

void QEXTMemberFunctorTest::testBoundConstFunctorWith4Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTBoundConstMemberFunctor<void, MemberBase, int, int, int, int> voidBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunction4);
    voidBoundConstMemberBaseFunctor(1, 2, 3, 4);
    QVERIFY("MemberBase::voidConstFunction4" == *sg_memberString);
    QEXTBoundConstMemberFunctor<int, MemberBase, int, int, int, int> intBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intConstFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intBoundConstMemberBaseFunctor(1, 2, 3, 4));
    QEXTBoundConstMemberFunctor<double, MemberBase, double, double, double, double> doubleBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleBoundConstMemberBaseFunctor(1.1, 2.2, 3.3, 4.4));

    QEXTBoundConstMemberFunctor<void, MemberBase, bool, int, int, int> voidBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunctionB4);
    voidBoundConstMemberBaseFunctorB(true, 2, 3, 4);
    QVERIFY("MemberBase::voidConstFunctionB4" == *sg_memberString);
    QEXTBoundConstMemberFunctor<int, MemberBase, bool, int, int, int> intBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intConstFunctionB4);
    QVERIFY(2 + 3 + 4 == intBoundConstMemberBaseFunctorB(true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intBoundConstMemberBaseFunctorB(false, 2, 3, 4));
    QEXTBoundConstMemberFunctor<double, MemberBase, bool, double, double, double> doubleBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleBoundConstMemberBaseFunctorB(true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleBoundConstMemberBaseFunctorB(false, 2.2, 3.3, 4.4));
}

void QEXTMemberFunctorTest::testPolymorphismBoundConstFunctorWith4Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTBoundConstMemberFunctor<void, MemberBase, int, int, int, int> voidBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction4);
    voidBoundConstMemberBaseFunctor(1, 2, 3, 4);
    QVERIFY("Member::voidConstFunction4" == *sg_memberString);
    QEXTBoundConstMemberFunctor<int, MemberBase, int, int, int, int> intBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction4);
    QVERIFY(0 == intBoundConstMemberBaseFunctor(1, 2, 3, 4));
    QEXTBoundConstMemberFunctor<double, MemberBase, double, double, double, double> doubleBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction4);
    QVERIFY(0 == doubleBoundConstMemberBaseFunctor(1.1, 2.2, 3.3, 4.4));

    QEXTBoundConstMemberFunctor<void, MemberBase, bool, int, int, int> voidBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunctionB4);
    voidBoundConstMemberBaseFunctorB(true, 2, 3, 4);
    QVERIFY("Member::voidConstFunctionB4" == *sg_memberString);
    QEXTBoundConstMemberFunctor<int, MemberBase, bool, int, int, int> intBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunctionB4);
    QVERIFY(1 == intBoundConstMemberBaseFunctorB(true, 2, 3, 4));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB(false, 2, 3, 4));
    QEXTBoundConstMemberFunctor<double, MemberBase, bool, double, double, double> doubleBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunctionB4);
    QVERIFY(1 == doubleBoundConstMemberBaseFunctorB(true, 2.2, 3.3, 4.4));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB(false, 2.2, 3.3, 4.4));
}

void QEXTMemberFunctorTest::testBoundVolatileFunctorWith4Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTBoundVolatileMemberFunctor<void, MemberBase, int, int, int, int> voidBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunction4);
    voidBoundVolatileMemberBaseFunctor(1, 2, 3, 4);
    QVERIFY("MemberBase::voidVolatileFunction4" == *sg_memberString);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, int, int, int, int> intBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intBoundVolatileMemberBaseFunctor(1, 2, 3, 4));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, double, double, double, double> doubleBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4));

    QEXTBoundVolatileMemberFunctor<void, MemberBase, bool, int, int, int> voidBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunctionB4);
    voidBoundVolatileMemberBaseFunctorB(true, 2, 3, 4);
    QVERIFY("MemberBase::voidVolatileFunctionB4" == *sg_memberString);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, bool, int, int, int> intBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunctionB4);
    QVERIFY(2 + 3 + 4 == intBoundVolatileMemberBaseFunctorB(true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intBoundVolatileMemberBaseFunctorB(false, 2, 3, 4));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, bool, double, double, double> doubleBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4));
}

void QEXTMemberFunctorTest::testPolymorphismBoundVolatileFunctorWith4Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTBoundVolatileMemberFunctor<void, MemberBase, int, int, int, int> voidBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction4);
    voidBoundVolatileMemberBaseFunctor(1, 2, 3, 4);
    QVERIFY("Member::voidVolatileFunction4" == *sg_memberString);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, int, int, int, int> intBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction4);
    QVERIFY(0 == intBoundVolatileMemberBaseFunctor(1, 2, 3, 4));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, double, double, double, double> doubleBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction4);
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4));

    QEXTBoundVolatileMemberFunctor<void, MemberBase, bool, int, int, int> voidBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunctionB4);
    voidBoundVolatileMemberBaseFunctorB(true, 2, 3, 4);
    QVERIFY("Member::voidVolatileFunctionB4" == *sg_memberString);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, bool, int, int, int> intBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunctionB4);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctorB(true, 2, 3, 4));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB(false, 2, 3, 4));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, bool, double, double, double> doubleBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunctionB4);
    QVERIFY(1 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4));
}

void QEXTMemberFunctorTest::testBoundConstVolatileFunctorWith4Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, int, int, int, int> voidBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunction4);
    voidBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4);
    QVERIFY("MemberBase::voidConstVolatileFunction4" == *sg_memberString);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, int, int, int, int> intBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4));

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, bool, int, int, int> voidBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunctionB4);
    voidBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4);
    QVERIFY("MemberBase::voidConstVolatileFunctionB4" == *sg_memberString);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, bool, int, int, int> intBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunctionB4);
    QVERIFY(2 + 3 + 4 == intBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intBoundConstVolatileMemberBaseFunctorB(false, 2, 3, 4));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, bool, double, double, double> doubleBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4));
}

void QEXTMemberFunctorTest::testPolymorphismBoundConstVolatileFunctorWith4Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, int, int, int, int> voidBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction4);
    voidBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4);
    QVERIFY("Member::voidConstVolatileFunction4" == *sg_memberString);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, int, int, int, int> intBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction4);
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction4);
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4));

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, bool, int, int, int> voidBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunctionB4);
    voidBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4);
    QVERIFY("Member::voidConstVolatileFunctionB4" == *sg_memberString);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, bool, int, int, int> intBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunctionB4);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB(false, 2, 3, 4));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, bool, double, double, double> doubleBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunctionB4);
    QVERIFY(1 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4));
}

void QEXTMemberFunctorTest::testFunctorWith5Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTMemberFunctor<void, MemberBase, int, int, int, int, int> voidMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidFunction5);
    voidMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5);
    QVERIFY("MemberBase::voidFunction5" == *sg_memberString);
    QEXTMemberFunctor<int, MemberBase, int, int, int, int, int> intMemberBaseFunctor = qextMemberFunctor(&MemberBase::intFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5));
    QEXTMemberFunctor<double, MemberBase, double, double, double, double, double> doubleMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTMemberFunctor<void, MemberBase, bool, int, int, int, int> voidMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidFunctionB5);
    voidMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5);
    QVERIFY("MemberBase::voidFunctionB5" == *sg_memberString);
    QEXTMemberFunctor<int, MemberBase, bool, int, int, int, int> intMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intMemberBaseFunctorB(&memberBase, false, 2, 3, 4, 5));
    QEXTMemberFunctor<double, MemberBase, bool, double, double, double, double> doubleMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleMemberBaseFunctorB(&memberBase, true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleMemberBaseFunctorB(&memberBase, false, 2.2, 3.3, 4.4, 5.5));
}

void QEXTMemberFunctorTest::testPolymorphismFunctorWith5Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTMemberFunctor<void, MemberBase, int, int, int, int, int> voidMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidFunction5);
    voidMemberBaseFunctor(&member, 1, 2, 3, 4, 5);
    QVERIFY("Member::voidFunction5" == *sg_memberString);
    QEXTMemberFunctor<int, MemberBase, int, int, int, int, int> intMemberBaseFunctor = qextMemberFunctor(&MemberBase::intFunction5);
    QVERIFY(0 == intMemberBaseFunctor(&member, 1, 2, 3, 4, 5));
    QEXTMemberFunctor<double, MemberBase, double, double, double, double, double> doubleMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleFunction5);
    QVERIFY(0 == doubleMemberBaseFunctor(&member, 1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTMemberFunctor<void, MemberBase, bool, int, int, int, int> voidMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidFunctionB5);
    voidMemberBaseFunctorB(&member, true, 2, 3, 4, 5);
    QVERIFY("Member::voidFunctionB5" == *sg_memberString);
    QEXTMemberFunctor<int, MemberBase, bool, int, int, int, int> intMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intFunctionB5);
    QVERIFY(1 == intMemberBaseFunctorB(&member, true, 2, 3, 4, 5));
    QVERIFY(0 == intMemberBaseFunctorB(&member, false, 2, 3, 4, 5));
    QEXTMemberFunctor<double, MemberBase, bool, double, double, double, double> doubleMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleFunctionB5);
    QVERIFY(1 == doubleMemberBaseFunctorB(&member, true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(0 == doubleMemberBaseFunctorB(&member, false, 2.2, 3.3, 4.4, 5.5));
}

void QEXTMemberFunctorTest::testConstFunctorWith5Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTConstMemberFunctor<void, MemberBase, int, int, int, int, int> voidConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstFunction5);
    voidConstMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5);
    QVERIFY("MemberBase::voidConstFunction5" == *sg_memberString);
    QEXTConstMemberFunctor<int, MemberBase, int, int, int, int, int> intConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intConstMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5));
    QEXTConstMemberFunctor<double, MemberBase, double, double, double, double, double> doubleConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleConstMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTConstMemberFunctor<void, MemberBase, bool, int, int, int, int> voidConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstFunctionB5);
    voidConstMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5);
    QVERIFY("MemberBase::voidConstFunctionB5" == *sg_memberString);
    QEXTConstMemberFunctor<int, MemberBase, bool, int, int, int, int> intConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intConstMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intConstMemberBaseFunctorB(&memberBase, false, 2, 3, 4, 5));
    QEXTConstMemberFunctor<double, MemberBase, bool, double, double, double, double> doubleConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleConstMemberBaseFunctorB(&memberBase, true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleConstMemberBaseFunctorB(&memberBase, false, 2.2, 3.3, 4.4, 5.5));
}

void QEXTMemberFunctorTest::testPolymorphismConstFunctorWith5Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTConstMemberFunctor<void, MemberBase, int, int, int, int, int> voidConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstFunction5);
    voidConstMemberBaseFunctor(&member, 1, 2, 3, 4, 5);
    QVERIFY("Member::voidConstFunction5" == *sg_memberString);
    QEXTConstMemberFunctor<int, MemberBase, int, int, int, int, int> intConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstFunction5);
    QVERIFY(0 == intConstMemberBaseFunctor(&member, 1, 2, 3, 4, 5));
    QEXTConstMemberFunctor<double, MemberBase, double, double, double, double, double> doubleConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstFunction5);
    QVERIFY(0 == doubleConstMemberBaseFunctor(&member, 1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTConstMemberFunctor<void, MemberBase, bool, int, int, int, int> voidConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstFunctionB5);
    voidConstMemberBaseFunctorB(&member, true, 2, 3, 4, 5);
    QVERIFY("Member::voidConstFunctionB5" == *sg_memberString);
    QEXTConstMemberFunctor<int, MemberBase, bool, int, int, int, int> intConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstFunctionB5);
    QVERIFY(1 == intConstMemberBaseFunctorB(&member, true, 2, 3, 4, 5));
    QVERIFY(0 == intConstMemberBaseFunctorB(&member, false, 2, 3, 4, 5));
    QEXTConstMemberFunctor<double, MemberBase, bool, double, double, double, double> doubleConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstFunctionB5);
    QVERIFY(1 == doubleConstMemberBaseFunctorB(&member, true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(0 == doubleConstMemberBaseFunctorB(&member, false, 2.2, 3.3, 4.4, 5.5));
}

void QEXTMemberFunctorTest::testVolatileFunctorWith5Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTVolatileMemberFunctor<void, MemberBase, int, int, int, int, int> voidVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidVolatileFunction5);
    voidVolatileMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5);
    QVERIFY("MemberBase::voidVolatileFunction5" == *sg_memberString);
    QEXTVolatileMemberFunctor<int, MemberBase, int, int, int, int, int> intVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intVolatileFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intVolatileMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5));
    QEXTVolatileMemberFunctor<double, MemberBase, double, double, double, double, double> doubleVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleVolatileFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleVolatileMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int> voidVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidVolatileFunctionB5);
    voidVolatileMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5);
    QVERIFY("MemberBase::voidVolatileFunctionB5" == *sg_memberString);
    QEXTVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int> intVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intVolatileFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intVolatileMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intVolatileMemberBaseFunctorB(&memberBase, false, 2, 3, 4, 5));
    QEXTVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double> doubleVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleVolatileMemberBaseFunctorB(&memberBase, true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleVolatileMemberBaseFunctorB(&memberBase, false, 2.2, 3.3, 4.4, 5.5));
}

void QEXTMemberFunctorTest::testPolymorphismVolatileFunctorWith5Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTVolatileMemberFunctor<void, MemberBase, int, int, int, int, int> voidVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidVolatileFunction5);
    voidVolatileMemberBaseFunctor(&member, 1, 2, 3, 4, 5);
    QVERIFY("Member::voidVolatileFunction5" == *sg_memberString);
    QEXTVolatileMemberFunctor<int, MemberBase, int, int, int, int, int> intVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intVolatileFunction5);
    QVERIFY(0 == intVolatileMemberBaseFunctor(&member, 1, 2, 3, 4, 5));
    QEXTVolatileMemberFunctor<double, MemberBase, double, double, double, double, double> doubleVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleVolatileFunction5);
    QVERIFY(0 == doubleVolatileMemberBaseFunctor(&member, 1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int> voidVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidVolatileFunctionB5);
    voidVolatileMemberBaseFunctorB(&member, true, 2, 3, 4, 5);
    QVERIFY("Member::voidVolatileFunctionB5" == *sg_memberString);
    QEXTVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int> intVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intVolatileFunctionB5);
    QVERIFY(1 == intVolatileMemberBaseFunctorB(&member, true, 2, 3, 4, 5));
    QVERIFY(0 == intVolatileMemberBaseFunctorB(&member, false, 2, 3, 4, 5));
    QEXTVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double> doubleVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB5);
    QVERIFY(1 == doubleVolatileMemberBaseFunctorB(&member, true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(0 == doubleVolatileMemberBaseFunctorB(&member, false, 2.2, 3.3, 4.4, 5.5));
}

void QEXTMemberFunctorTest::testConstVolatileFunctorWith5Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTConstVolatileMemberFunctor<void, MemberBase, int, int, int, int, int> voidConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstVolatileFunction5);
    voidConstVolatileMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5);
    QVERIFY("MemberBase::voidConstVolatileFunction5" == *sg_memberString);
    QEXTConstVolatileMemberFunctor<int, MemberBase, int, int, int, int, int> intConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstVolatileFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intConstVolatileMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5));
    QEXTConstVolatileMemberFunctor<double, MemberBase, double, double, double, double, double> doubleConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleConstVolatileMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTConstVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int> voidConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB5);
    voidConstVolatileMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5);
    QVERIFY("MemberBase::voidConstVolatileFunctionB5" == *sg_memberString);
    QEXTConstVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int> intConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intConstVolatileMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intConstVolatileMemberBaseFunctorB(&memberBase, false, 2, 3, 4, 5));
    QEXTConstVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double> doubleConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleConstVolatileMemberBaseFunctorB(&memberBase, true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleConstVolatileMemberBaseFunctorB(&memberBase, false, 2.2, 3.3, 4.4, 5.5));
}

void QEXTMemberFunctorTest::testPolymorphismConstVolatileFunctorWith5Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTConstVolatileMemberFunctor<void, MemberBase, int, int, int, int, int> voidConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstVolatileFunction5);
    voidConstVolatileMemberBaseFunctor(&member, 1, 2, 3, 4, 5);
    QVERIFY("Member::voidConstVolatileFunction5" == *sg_memberString);
    QEXTConstVolatileMemberFunctor<int, MemberBase, int, int, int, int, int> intConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstVolatileFunction5);
    QVERIFY(0 == intConstVolatileMemberBaseFunctor(&member, 1, 2, 3, 4, 5));
    QEXTConstVolatileMemberFunctor<double, MemberBase, double, double, double, double, double> doubleConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction5);
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctor(&member, 1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTConstVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int> voidConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB5);
    voidConstVolatileMemberBaseFunctorB(&member, true, 2, 3, 4, 5);
    QVERIFY("Member::voidConstVolatileFunctionB5" == *sg_memberString);
    QEXTConstVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int> intConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB5);
    QVERIFY(1 == intConstVolatileMemberBaseFunctorB(&member, true, 2, 3, 4, 5));
    QVERIFY(0 == intConstVolatileMemberBaseFunctorB(&member, false, 2, 3, 4, 5));
    QEXTConstVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double> doubleConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB5);
    QVERIFY(1 == doubleConstVolatileMemberBaseFunctorB(&member, true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctorB(&member, false, 2.2, 3.3, 4.4, 5.5));
}

void QEXTMemberFunctorTest::testBoundFunctorWith5Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTBoundMemberFunctor<void, MemberBase, int, int, int, int, int> voidBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidFunction5);
    voidBoundMemberBaseFunctor(1, 2, 3, 4, 5);
    QVERIFY("MemberBase::voidFunction5" == *sg_memberString);
    QEXTBoundMemberFunctor<int, MemberBase, int, int, int, int, int> intBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intBoundMemberBaseFunctor(1, 2, 3, 4, 5));
    QEXTBoundMemberFunctor<double, MemberBase, double, double, double, double, double> doubleBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleBoundMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundMemberFunctor<void, MemberBase, bool, int, int, int, int> voidBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidFunctionB5);
    voidBoundMemberBaseFunctorB(true, 2, 3, 4, 5);
    QVERIFY("MemberBase::voidFunctionB5" == *sg_memberString);
    QEXTBoundMemberFunctor<int, MemberBase, bool, int, int, int, int> intBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intBoundMemberBaseFunctorB(true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intBoundMemberBaseFunctorB(false, 2, 3, 4, 5));
    QEXTBoundMemberFunctor<double, MemberBase, bool, double, double, double, double> doubleBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleBoundMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleBoundMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5));
}

void QEXTMemberFunctorTest::testPolymorphismBoundFunctorWith5Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTBoundMemberFunctor<void, MemberBase, int, int, int, int, int> voidBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction5);
    voidBoundMemberBaseFunctor(1, 2, 3, 4, 5);
    QVERIFY("Member::voidFunction5" == *sg_memberString);
    QEXTBoundMemberFunctor<int, MemberBase, int, int, int, int, int> intBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction5);
    QVERIFY(0 == intBoundMemberBaseFunctor(1, 2, 3, 4, 5));
    QEXTBoundMemberFunctor<double, MemberBase, double, double, double, double, double> doubleBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction5);
    QVERIFY(0 == doubleBoundMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundMemberFunctor<void, MemberBase, bool, int, int, int, int> voidBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunctionB5);
    voidBoundMemberBaseFunctorB(true, 2, 3, 4, 5);
    QVERIFY("Member::voidFunctionB5" == *sg_memberString);
    QEXTBoundMemberFunctor<int, MemberBase, bool, int, int, int, int> intBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunctionB5);
    QVERIFY(1 == intBoundMemberBaseFunctorB(true, 2, 3, 4, 5));
    QVERIFY(0 == intBoundMemberBaseFunctorB(false, 2, 3, 4, 5));
    QEXTBoundMemberFunctor<double, MemberBase, bool, double, double, double, double> doubleBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunctionB5);
    QVERIFY(1 == doubleBoundMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5));
}

void QEXTMemberFunctorTest::testBoundConstFunctorWith5Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTBoundConstMemberFunctor<void, MemberBase, int, int, int, int, int> voidBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunction5);
    voidBoundConstMemberBaseFunctor(1, 2, 3, 4, 5);
    QVERIFY("MemberBase::voidConstFunction5" == *sg_memberString);
    QEXTBoundConstMemberFunctor<int, MemberBase, int, int, int, int, int> intBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intConstFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intBoundConstMemberBaseFunctor(1, 2, 3, 4, 5));
    QEXTBoundConstMemberFunctor<double, MemberBase, double, double, double, double, double> doubleBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleBoundConstMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundConstMemberFunctor<void, MemberBase, bool, int, int, int, int> voidBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunctionB5);
    voidBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5);
    QVERIFY("MemberBase::voidConstFunctionB5" == *sg_memberString);
    QEXTBoundConstMemberFunctor<int, MemberBase, bool, int, int, int, int> intBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intConstFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intBoundConstMemberBaseFunctorB(false, 2, 3, 4, 5));
    QEXTBoundConstMemberFunctor<double, MemberBase, bool, double, double, double, double> doubleBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleBoundConstMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleBoundConstMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5));
}

void QEXTMemberFunctorTest::testPolymorphismBoundConstFunctorWith5Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTBoundConstMemberFunctor<void, MemberBase, int, int, int, int, int> voidBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction5);
    voidBoundConstMemberBaseFunctor(1, 2, 3, 4, 5);
    QVERIFY("Member::voidConstFunction5" == *sg_memberString);
    QEXTBoundConstMemberFunctor<int, MemberBase, int, int, int, int, int> intBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction5);
    QVERIFY(0 == intBoundConstMemberBaseFunctor(1, 2, 3, 4, 5));
    QEXTBoundConstMemberFunctor<double, MemberBase, double, double, double, double, double> doubleBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction5);
    QVERIFY(0 == doubleBoundConstMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundConstMemberFunctor<void, MemberBase, bool, int, int, int, int> voidBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunctionB5);
    voidBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5);
    QVERIFY("Member::voidConstFunctionB5" == *sg_memberString);
    QEXTBoundConstMemberFunctor<int, MemberBase, bool, int, int, int, int> intBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunctionB5);
    QVERIFY(1 == intBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB(false, 2, 3, 4, 5));
    QEXTBoundConstMemberFunctor<double, MemberBase, bool, double, double, double, double> doubleBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunctionB5);
    QVERIFY(1 == doubleBoundConstMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5));
}

void QEXTMemberFunctorTest::testBoundVolatileFunctorWith5Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTBoundVolatileMemberFunctor<void, MemberBase, int, int, int, int, int> voidBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunction5);
    voidBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5);
    QVERIFY("MemberBase::voidVolatileFunction5" == *sg_memberString);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, int, int, int, int, int> intBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int> voidBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunctionB5);
    voidBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5);
    QVERIFY("MemberBase::voidVolatileFunctionB5" == *sg_memberString);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int> intBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intBoundVolatileMemberBaseFunctorB(false, 2, 3, 4, 5));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double> doubleBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5));
}

void QEXTMemberFunctorTest::testPolymorphismBoundVolatileFunctorWith5Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTBoundVolatileMemberFunctor<void, MemberBase, int, int, int, int, int> voidBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction5);
    voidBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5);
    QVERIFY("Member::voidVolatileFunction5" == *sg_memberString);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, int, int, int, int, int> intBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction5);
    QVERIFY(0 == intBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction5);
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int> voidBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunctionB5);
    voidBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5);
    QVERIFY("Member::voidVolatileFunctionB5" == *sg_memberString);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int> intBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunctionB5);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB(false, 2, 3, 4, 5));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double> doubleBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunctionB5);
    QVERIFY(1 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5));
}

void QEXTMemberFunctorTest::testBoundConstVolatileFunctorWith5Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunction5);
    voidBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5);
    QVERIFY("MemberBase::voidConstVolatileFunction5" == *sg_memberString);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int> voidBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunctionB5);
    voidBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5);
    QVERIFY("MemberBase::voidConstVolatileFunctionB5" == *sg_memberString);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int> intBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intBoundConstVolatileMemberBaseFunctorB(false, 2, 3, 4, 5));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5));
}

void QEXTMemberFunctorTest::testPolymorphismBoundConstVolatileFunctorWith5Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction5);
    voidBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5);
    QVERIFY("Member::voidConstVolatileFunction5" == *sg_memberString);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction5);
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction5);
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int> voidBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunctionB5);
    voidBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5);
    QVERIFY("Member::voidConstVolatileFunctionB5" == *sg_memberString);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int> intBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunctionB5);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB(false, 2, 3, 4, 5));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunctionB5);
    QVERIFY(1 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5));
}

void QEXTMemberFunctorTest::testFunctorWith6Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTMemberFunctor<void, MemberBase, int, int, int, int, int, int> voidMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidFunction6);
    voidMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5, 6);
    QVERIFY("MemberBase::voidFunction6" == *sg_memberString);
    QEXTMemberFunctor<int, MemberBase, int, int, int, int, int, int> intMemberBaseFunctor = qextMemberFunctor(&MemberBase::intFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5, 6));
    QEXTMemberFunctor<double, MemberBase, double, double, double, double, double, double> doubleMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTMemberFunctor<void, MemberBase, bool, int, int, int, int, int> voidMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidFunctionB6);
    voidMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5, 6);
    QVERIFY("MemberBase::voidFunctionB6" == *sg_memberString);
    QEXTMemberFunctor<int, MemberBase, bool, int, int, int, int, int> intMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intMemberBaseFunctorB(&memberBase, false, 2, 3, 4, 5, 6));
    QEXTMemberFunctor<double, MemberBase, bool, double, double, double, double, double> doubleMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleMemberBaseFunctorB(&memberBase, true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleMemberBaseFunctorB(&memberBase, false, 2.2, 3.3, 4.4, 5.5, 6.6));
}

void QEXTMemberFunctorTest::testPolymorphismFunctorWith6Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTMemberFunctor<void, MemberBase, int, int, int, int, int, int> voidMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidFunction6);
    voidMemberBaseFunctor(&member, 1, 2, 3, 4, 5, 6);
    QVERIFY("Member::voidFunction6" == *sg_memberString);
    QEXTMemberFunctor<int, MemberBase, int, int, int, int, int, int> intMemberBaseFunctor = qextMemberFunctor(&MemberBase::intFunction6);
    QVERIFY(0 == intMemberBaseFunctor(&member, 1, 2, 3, 4, 5, 6));
    QEXTMemberFunctor<double, MemberBase, double, double, double, double, double, double> doubleMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleFunction6);
    QVERIFY(0 == doubleMemberBaseFunctor(&member, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTMemberFunctor<void, MemberBase, bool, int, int, int, int, int> voidMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidFunctionB6);
    voidMemberBaseFunctorB(&member, true, 2, 3, 4, 5, 6);
    QVERIFY("Member::voidFunctionB6" == *sg_memberString);
    QEXTMemberFunctor<int, MemberBase, bool, int, int, int, int, int> intMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intFunctionB6);
    QVERIFY(1 == intMemberBaseFunctorB(&member, true, 2, 3, 4, 5, 6));
    QVERIFY(0 == intMemberBaseFunctorB(&member, false, 2, 3, 4, 5, 6));
    QEXTMemberFunctor<double, MemberBase, bool, double, double, double, double, double> doubleMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleFunctionB6);
    QVERIFY(1 == doubleMemberBaseFunctorB(&member, true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(0 == doubleMemberBaseFunctorB(&member, false, 2.2, 3.3, 4.4, 5.5, 6.6));
}

void QEXTMemberFunctorTest::testConstFunctorWith6Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTConstMemberFunctor<void, MemberBase, int, int, int, int, int, int> voidConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstFunction6);
    voidConstMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5, 6);
    QVERIFY("MemberBase::voidConstFunction6" == *sg_memberString);
    QEXTConstMemberFunctor<int, MemberBase, int, int, int, int, int, int> intConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intConstMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5, 6));
    QEXTConstMemberFunctor<double, MemberBase, double, double, double, double, double, double> doubleConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleConstMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTConstMemberFunctor<void, MemberBase, bool, int, int, int, int, int> voidConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstFunctionB6);
    voidConstMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5, 6);
    QVERIFY("MemberBase::voidConstFunctionB6" == *sg_memberString);
    QEXTConstMemberFunctor<int, MemberBase, bool, int, int, int, int, int> intConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intConstMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intConstMemberBaseFunctorB(&memberBase, false, 2, 3, 4, 5, 6));
    QEXTConstMemberFunctor<double, MemberBase, bool, double, double, double, double, double> doubleConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleConstMemberBaseFunctorB(&memberBase, true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleConstMemberBaseFunctorB(&memberBase, false, 2.2, 3.3, 4.4, 5.5, 6.6));
}

void QEXTMemberFunctorTest::testPolymorphismConstFunctorWith6Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTConstMemberFunctor<void, MemberBase, int, int, int, int, int, int> voidConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstFunction6);
    voidConstMemberBaseFunctor(&member, 1, 2, 3, 4, 5, 6);
    QVERIFY("Member::voidConstFunction6" == *sg_memberString);
    QEXTConstMemberFunctor<int, MemberBase, int, int, int, int, int, int> intConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstFunction6);
    QVERIFY(0 == intConstMemberBaseFunctor(&member, 1, 2, 3, 4, 5, 6));
    QEXTConstMemberFunctor<double, MemberBase, double, double, double, double, double, double> doubleConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstFunction6);
    QVERIFY(0 == doubleConstMemberBaseFunctor(&member, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTConstMemberFunctor<void, MemberBase, bool, int, int, int, int, int> voidConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstFunctionB6);
    voidConstMemberBaseFunctorB(&member, true, 2, 3, 4, 5, 6);
    QVERIFY("Member::voidConstFunctionB6" == *sg_memberString);
    QEXTConstMemberFunctor<int, MemberBase, bool, int, int, int, int, int> intConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstFunctionB6);
    QVERIFY(1 == intConstMemberBaseFunctorB(&member, true, 2, 3, 4, 5, 6));
    QVERIFY(0 == intConstMemberBaseFunctorB(&member, false, 2, 3, 4, 5, 6));
    QEXTConstMemberFunctor<double, MemberBase, bool, double, double, double, double, double> doubleConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstFunctionB6);
    QVERIFY(1 == doubleConstMemberBaseFunctorB(&member, true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(0 == doubleConstMemberBaseFunctorB(&member, false, 2.2, 3.3, 4.4, 5.5, 6.6));
}

void QEXTMemberFunctorTest::testVolatileFunctorWith6Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTVolatileMemberFunctor<void, MemberBase, int, int, int, int, int, int> voidVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidVolatileFunction6);
    voidVolatileMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5, 6);
    QVERIFY("MemberBase::voidVolatileFunction6" == *sg_memberString);
    QEXTVolatileMemberFunctor<int, MemberBase, int, int, int, int, int, int> intVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intVolatileFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intVolatileMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5, 6));
    QEXTVolatileMemberFunctor<double, MemberBase, double, double, double, double, double, double> doubleVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleVolatileFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleVolatileMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int, int> voidVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidVolatileFunctionB6);
    voidVolatileMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5, 6);
    QVERIFY("MemberBase::voidVolatileFunctionB6" == *sg_memberString);
    QEXTVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int, int> intVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intVolatileFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intVolatileMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intVolatileMemberBaseFunctorB(&memberBase, false, 2, 3, 4, 5, 6));
    QEXTVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double, double> doubleVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleVolatileMemberBaseFunctorB(&memberBase, true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleVolatileMemberBaseFunctorB(&memberBase, false, 2.2, 3.3, 4.4, 5.5, 6.6));
}

void QEXTMemberFunctorTest::testPolymorphismVolatileFunctorWith6Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTVolatileMemberFunctor<void, MemberBase, int, int, int, int, int, int> voidVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidVolatileFunction6);
    voidVolatileMemberBaseFunctor(&member, 1, 2, 3, 4, 5, 6);
    QVERIFY("Member::voidVolatileFunction6" == *sg_memberString);
    QEXTVolatileMemberFunctor<int, MemberBase, int, int, int, int, int, int> intVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intVolatileFunction6);
    QVERIFY(0 == intVolatileMemberBaseFunctor(&member, 1, 2, 3, 4, 5, 6));
    QEXTVolatileMemberFunctor<double, MemberBase, double, double, double, double, double, double> doubleVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleVolatileFunction6);
    QVERIFY(0 == doubleVolatileMemberBaseFunctor(&member, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int, int> voidVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidVolatileFunctionB6);
    voidVolatileMemberBaseFunctorB(&member, true, 2, 3, 4, 5, 6);
    QVERIFY("Member::voidVolatileFunctionB6" == *sg_memberString);
    QEXTVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int, int> intVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intVolatileFunctionB6);
    QVERIFY(1 == intVolatileMemberBaseFunctorB(&member, true, 2, 3, 4, 5, 6));
    QVERIFY(0 == intVolatileMemberBaseFunctorB(&member, false, 2, 3, 4, 5, 6));
    QEXTVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double, double> doubleVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB6);
    QVERIFY(1 == doubleVolatileMemberBaseFunctorB(&member, true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(0 == doubleVolatileMemberBaseFunctorB(&member, false, 2.2, 3.3, 4.4, 5.5, 6.6));
}

void QEXTMemberFunctorTest::testConstVolatileFunctorWith6Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTConstVolatileMemberFunctor<void, MemberBase, int, int, int, int, int, int> voidConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstVolatileFunction6);
    voidConstVolatileMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5, 6);
    QVERIFY("MemberBase::voidConstVolatileFunction6" == *sg_memberString);
    QEXTConstVolatileMemberFunctor<int, MemberBase, int, int, int, int, int, int> intConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstVolatileFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intConstVolatileMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5, 6));
    QEXTConstVolatileMemberFunctor<double, MemberBase, double, double, double, double, double, double> doubleConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleConstVolatileMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTConstVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int, int> voidConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB6);
    voidConstVolatileMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5, 6);
    QVERIFY("MemberBase::voidConstVolatileFunctionB6" == *sg_memberString);
    QEXTConstVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int, int> intConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intConstVolatileMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intConstVolatileMemberBaseFunctorB(&memberBase, false, 2, 3, 4, 5, 6));
    QEXTConstVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double, double> doubleConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleConstVolatileMemberBaseFunctorB(&memberBase, true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleConstVolatileMemberBaseFunctorB(&memberBase, false, 2.2, 3.3, 4.4, 5.5, 6.6));
}

void QEXTMemberFunctorTest::testPolymorphismConstVolatileFunctorWith6Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTConstVolatileMemberFunctor<void, MemberBase, int, int, int, int, int, int> voidConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstVolatileFunction6);
    voidConstVolatileMemberBaseFunctor(&member, 1, 2, 3, 4, 5, 6);
    QVERIFY("Member::voidConstVolatileFunction6" == *sg_memberString);
    QEXTConstVolatileMemberFunctor<int, MemberBase, int, int, int, int, int, int> intConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstVolatileFunction6);
    QVERIFY(0 == intConstVolatileMemberBaseFunctor(&member, 1, 2, 3, 4, 5, 6));
    QEXTConstVolatileMemberFunctor<double, MemberBase, double, double, double, double, double, double> doubleConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction6);
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctor(&member, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTConstVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int, int> voidConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB6);
    voidConstVolatileMemberBaseFunctorB(&member, true, 2, 3, 4, 5, 6);
    QVERIFY("Member::voidConstVolatileFunctionB6" == *sg_memberString);
    QEXTConstVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int, int> intConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB6);
    QVERIFY(1 == intConstVolatileMemberBaseFunctorB(&member, true, 2, 3, 4, 5, 6));
    QVERIFY(0 == intConstVolatileMemberBaseFunctorB(&member, false, 2, 3, 4, 5, 6));
    QEXTConstVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double, double> doubleConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB6);
    QVERIFY(1 == doubleConstVolatileMemberBaseFunctorB(&member, true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctorB(&member, false, 2.2, 3.3, 4.4, 5.5, 6.6));
}

void QEXTMemberFunctorTest::testBoundFunctorWith6Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTBoundMemberFunctor<void, MemberBase, int, int, int, int, int, int> voidBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidFunction6);
    voidBoundMemberBaseFunctor(1, 2, 3, 4, 5, 6);
    QVERIFY("MemberBase::voidFunction6" == *sg_memberString);
    QEXTBoundMemberFunctor<int, MemberBase, int, int, int, int, int, int> intBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intBoundMemberBaseFunctor(1, 2, 3, 4, 5, 6));
    QEXTBoundMemberFunctor<double, MemberBase, double, double, double, double, double, double> doubleBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundMemberFunctor<void, MemberBase, bool, int, int, int, int, int> voidBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidFunctionB6);
    voidBoundMemberBaseFunctorB(true, 2, 3, 4, 5, 6);
    QVERIFY("MemberBase::voidFunctionB6" == *sg_memberString);
    QEXTBoundMemberFunctor<int, MemberBase, bool, int, int, int, int, int> intBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intBoundMemberBaseFunctorB(true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intBoundMemberBaseFunctorB(false, 2, 3, 4, 5, 6));
    QEXTBoundMemberFunctor<double, MemberBase, bool, double, double, double, double, double> doubleBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleBoundMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6));
}

void QEXTMemberFunctorTest::testPolymorphismBoundFunctorWith6Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTBoundMemberFunctor<void, MemberBase, int, int, int, int, int, int> voidBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction6);
    voidBoundMemberBaseFunctor(1, 2, 3, 4, 5, 6);
    QVERIFY("Member::voidFunction6" == *sg_memberString);
    QEXTBoundMemberFunctor<int, MemberBase, int, int, int, int, int, int> intBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction6);
    QVERIFY(0 == intBoundMemberBaseFunctor(1, 2, 3, 4, 5, 6));
    QEXTBoundMemberFunctor<double, MemberBase, double, double, double, double, double, double> doubleBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction6);
    QVERIFY(0 == doubleBoundMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundMemberFunctor<void, MemberBase, bool, int, int, int, int, int> voidBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunctionB6);
    voidBoundMemberBaseFunctorB(true, 2, 3, 4, 5, 6);
    QVERIFY("Member::voidFunctionB6" == *sg_memberString);
    QEXTBoundMemberFunctor<int, MemberBase, bool, int, int, int, int, int> intBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunctionB6);
    QVERIFY(1 == intBoundMemberBaseFunctorB(true, 2, 3, 4, 5, 6));
    QVERIFY(0 == intBoundMemberBaseFunctorB(false, 2, 3, 4, 5, 6));
    QEXTBoundMemberFunctor<double, MemberBase, bool, double, double, double, double, double> doubleBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunctionB6);
    QVERIFY(1 == doubleBoundMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6));
}

void QEXTMemberFunctorTest::testBoundConstFunctorWith6Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTBoundConstMemberFunctor<void, MemberBase, int, int, int, int, int, int> voidBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunction6);
    voidBoundConstMemberBaseFunctor(1, 2, 3, 4, 5, 6);
    QVERIFY("MemberBase::voidConstFunction6" == *sg_memberString);
    QEXTBoundConstMemberFunctor<int, MemberBase, int, int, int, int, int, int> intBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intConstFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intBoundConstMemberBaseFunctor(1, 2, 3, 4, 5, 6));
    QEXTBoundConstMemberFunctor<double, MemberBase, double, double, double, double, double, double> doubleBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundConstMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundConstMemberFunctor<void, MemberBase, bool, int, int, int, int, int> voidBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunctionB6);
    voidBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5, 6);
    QVERIFY("MemberBase::voidConstFunctionB6" == *sg_memberString);
    QEXTBoundConstMemberFunctor<int, MemberBase, bool, int, int, int, int, int> intBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intConstFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intBoundConstMemberBaseFunctorB(false, 2, 3, 4, 5, 6));
    QEXTBoundConstMemberFunctor<double, MemberBase, bool, double, double, double, double, double> doubleBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundConstMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleBoundConstMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6));
}

void QEXTMemberFunctorTest::testPolymorphismBoundConstFunctorWith6Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTBoundConstMemberFunctor<void, MemberBase, int, int, int, int, int, int> voidBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction6);
    voidBoundConstMemberBaseFunctor(1, 2, 3, 4, 5, 6);
    QVERIFY("Member::voidConstFunction6" == *sg_memberString);
    QEXTBoundConstMemberFunctor<int, MemberBase, int, int, int, int, int, int> intBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction6);
    QVERIFY(0 == intBoundConstMemberBaseFunctor(1, 2, 3, 4, 5, 6));
    QEXTBoundConstMemberFunctor<double, MemberBase, double, double, double, double, double, double> doubleBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction6);
    QVERIFY(0 == doubleBoundConstMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundConstMemberFunctor<void, MemberBase, bool, int, int, int, int, int> voidBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunctionB6);
    voidBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5, 6);
    QVERIFY("Member::voidConstFunctionB6" == *sg_memberString);
    QEXTBoundConstMemberFunctor<int, MemberBase, bool, int, int, int, int, int> intBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunctionB6);
    QVERIFY(1 == intBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5, 6));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB(false, 2, 3, 4, 5, 6));
    QEXTBoundConstMemberFunctor<double, MemberBase, bool, double, double, double, double, double> doubleBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunctionB6);
    QVERIFY(1 == doubleBoundConstMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6));
}

void QEXTMemberFunctorTest::testBoundVolatileFunctorWith6Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTBoundVolatileMemberFunctor<void, MemberBase, int, int, int, int, int, int> voidBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunction6);
    voidBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6);
    QVERIFY("MemberBase::voidVolatileFunction6" == *sg_memberString);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, int, int, int, int, int, int> intBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, double, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int, int> voidBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunctionB6);
    voidBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6);
    QVERIFY("MemberBase::voidVolatileFunctionB6" == *sg_memberString);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int, int> intBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intBoundVolatileMemberBaseFunctorB(false, 2, 3, 4, 5, 6));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6));
}

void QEXTMemberFunctorTest::testPolymorphismBoundVolatileFunctorWith6Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTBoundVolatileMemberFunctor<void, MemberBase, int, int, int, int, int, int> voidBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction6);
    voidBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6);
    QVERIFY("Member::voidVolatileFunction6" == *sg_memberString);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, int, int, int, int, int, int> intBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction6);
    QVERIFY(0 == intBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, double, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction6);
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int, int> voidBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunctionB6);
    voidBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6);
    QVERIFY("Member::voidVolatileFunctionB6" == *sg_memberString);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int, int> intBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunctionB6);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB(false, 2, 3, 4, 5, 6));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunctionB6);
    QVERIFY(1 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6));
}

void QEXTMemberFunctorTest::testBoundConstVolatileFunctorWith6Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, int, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunction6);
    voidBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6);
    QVERIFY("MemberBase::voidConstVolatileFunction6" == *sg_memberString);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, int, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, double, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunctionB6);
    voidBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6);
    QVERIFY("MemberBase::voidConstVolatileFunctionB6" == *sg_memberString);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intBoundConstVolatileMemberBaseFunctorB(false, 2, 3, 4, 5, 6));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6));
}

void QEXTMemberFunctorTest::testPolymorphismBoundConstVolatileFunctorWith6Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, int, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction6);
    voidBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6);
    QVERIFY("Member::voidConstVolatileFunction6" == *sg_memberString);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, int, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction6);
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, double, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction6);
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunctionB6);
    voidBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6);
    QVERIFY("Member::voidConstVolatileFunctionB6" == *sg_memberString);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunctionB6);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB(false, 2, 3, 4, 5, 6));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunctionB6);
    QVERIFY(1 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6));
}

void QEXTMemberFunctorTest::testFunctorWith7Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTMemberFunctor<void, MemberBase, int, int, int, int, int, int, int> voidMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidFunction7);
    voidMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5, 6, 7);
    QVERIFY("MemberBase::voidFunction7" == *sg_memberString);
    QEXTMemberFunctor<int, MemberBase, int, int, int, int, int, int, int> intMemberBaseFunctor = qextMemberFunctor(&MemberBase::intFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5, 6, 7));
    QEXTMemberFunctor<double, MemberBase, double, double, double, double, double, double, double> doubleMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTMemberFunctor<void, MemberBase, bool, int, int, int, int, int, int> voidMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidFunctionB7);
    voidMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5, 6, 7);
    QVERIFY("MemberBase::voidFunctionB7" == *sg_memberString);
    QEXTMemberFunctor<int, MemberBase, bool, int, int, int, int, int, int> intMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intMemberBaseFunctorB(&memberBase, false, 2, 3, 4, 5, 6, 7));
    QEXTMemberFunctor<double, MemberBase, bool, double, double, double, double, double, double> doubleMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleMemberBaseFunctorB(&memberBase, true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleMemberBaseFunctorB(&memberBase, false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
}

void QEXTMemberFunctorTest::testPolymorphismFunctorWith7Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTMemberFunctor<void, MemberBase, int, int, int, int, int, int, int> voidMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidFunction7);
    voidMemberBaseFunctor(&member, 1, 2, 3, 4, 5, 6, 7);
    QVERIFY("Member::voidFunction7" == *sg_memberString);
    QEXTMemberFunctor<int, MemberBase, int, int, int, int, int, int, int> intMemberBaseFunctor = qextMemberFunctor(&MemberBase::intFunction7);
    QVERIFY(0 == intMemberBaseFunctor(&member, 1, 2, 3, 4, 5, 6, 7));
    QEXTMemberFunctor<double, MemberBase, double, double, double, double, double, double, double> doubleMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleFunction7);
    QVERIFY(0 == doubleMemberBaseFunctor(&member, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTMemberFunctor<void, MemberBase, bool, int, int, int, int, int, int> voidMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidFunctionB7);
    voidMemberBaseFunctorB(&member, true, 2, 3, 4, 5, 6, 7);
    QVERIFY("Member::voidFunctionB7" == *sg_memberString);
    QEXTMemberFunctor<int, MemberBase, bool, int, int, int, int, int, int> intMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intFunctionB7);
    QVERIFY(1 == intMemberBaseFunctorB(&member, true, 2, 3, 4, 5, 6, 7));
    QVERIFY(0 == intMemberBaseFunctorB(&member, false, 2, 3, 4, 5, 6, 7));
    QEXTMemberFunctor<double, MemberBase, bool, double, double, double, double, double, double> doubleMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleFunctionB7);
    QVERIFY(1 == doubleMemberBaseFunctorB(&member, true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(0 == doubleMemberBaseFunctorB(&member, false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
}

void QEXTMemberFunctorTest::testConstFunctorWith7Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTConstMemberFunctor<void, MemberBase, int, int, int, int, int, int, int> voidConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstFunction7);
    voidConstMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5, 6, 7);
    QVERIFY("MemberBase::voidConstFunction7" == *sg_memberString);
    QEXTConstMemberFunctor<int, MemberBase, int, int, int, int, int, int, int> intConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intConstMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5, 6, 7));
    QEXTConstMemberFunctor<double, MemberBase, double, double, double, double, double, double, double> doubleConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleConstMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTConstMemberFunctor<void, MemberBase, bool, int, int, int, int, int, int> voidConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstFunctionB7);
    voidConstMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5, 6, 7);
    QVERIFY("MemberBase::voidConstFunctionB7" == *sg_memberString);
    QEXTConstMemberFunctor<int, MemberBase, bool, int, int, int, int, int, int> intConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intConstMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intConstMemberBaseFunctorB(&memberBase, false, 2, 3, 4, 5, 6, 7));
    QEXTConstMemberFunctor<double, MemberBase, bool, double, double, double, double, double, double> doubleConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleConstMemberBaseFunctorB(&memberBase, true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleConstMemberBaseFunctorB(&memberBase, false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
}

void QEXTMemberFunctorTest::testPolymorphismConstFunctorWith7Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTConstMemberFunctor<void, MemberBase, int, int, int, int, int, int, int> voidConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstFunction7);
    voidConstMemberBaseFunctor(&member, 1, 2, 3, 4, 5, 6, 7);
    QVERIFY("Member::voidConstFunction7" == *sg_memberString);
    QEXTConstMemberFunctor<int, MemberBase, int, int, int, int, int, int, int> intConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstFunction7);
    QVERIFY(0 == intConstMemberBaseFunctor(&member, 1, 2, 3, 4, 5, 6, 7));
    QEXTConstMemberFunctor<double, MemberBase, double, double, double, double, double, double, double> doubleConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstFunction7);
    QVERIFY(0 == doubleConstMemberBaseFunctor(&member, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTConstMemberFunctor<void, MemberBase, bool, int, int, int, int, int, int> voidConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstFunctionB7);
    voidConstMemberBaseFunctorB(&member, true, 2, 3, 4, 5, 6, 7);
    QVERIFY("Member::voidConstFunctionB7" == *sg_memberString);
    QEXTConstMemberFunctor<int, MemberBase, bool, int, int, int, int, int, int> intConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstFunctionB7);
    QVERIFY(1 == intConstMemberBaseFunctorB(&member, true, 2, 3, 4, 5, 6, 7));
    QVERIFY(0 == intConstMemberBaseFunctorB(&member, false, 2, 3, 4, 5, 6, 7));
    QEXTConstMemberFunctor<double, MemberBase, bool, double, double, double, double, double, double> doubleConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstFunctionB7);
    QVERIFY(1 == doubleConstMemberBaseFunctorB(&member, true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(0 == doubleConstMemberBaseFunctorB(&member, false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
}

void QEXTMemberFunctorTest::testVolatileFunctorWith7Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTVolatileMemberFunctor<void, MemberBase, int, int, int, int, int, int, int> voidVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidVolatileFunction7);
    voidVolatileMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5, 6, 7);
    QVERIFY("MemberBase::voidVolatileFunction7" == *sg_memberString);
    QEXTVolatileMemberFunctor<int, MemberBase, int, int, int, int, int, int, int> intVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intVolatileFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intVolatileMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5, 6, 7));
    QEXTVolatileMemberFunctor<double, MemberBase, double, double, double, double, double, double, double> doubleVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleVolatileFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleVolatileMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int, int, int> voidVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidVolatileFunctionB7);
    voidVolatileMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5, 6, 7);
    QVERIFY("MemberBase::voidVolatileFunctionB7" == *sg_memberString);
    QEXTVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int, int, int> intVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intVolatileFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intVolatileMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intVolatileMemberBaseFunctorB(&memberBase, false, 2, 3, 4, 5, 6, 7));
    QEXTVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double, double, double> doubleVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleVolatileMemberBaseFunctorB(&memberBase, true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleVolatileMemberBaseFunctorB(&memberBase, false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
}

void QEXTMemberFunctorTest::testPolymorphismVolatileFunctorWith7Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTVolatileMemberFunctor<void, MemberBase, int, int, int, int, int, int, int> voidVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidVolatileFunction7);
    voidVolatileMemberBaseFunctor(&member, 1, 2, 3, 4, 5, 6, 7);
    QVERIFY("Member::voidVolatileFunction7" == *sg_memberString);
    QEXTVolatileMemberFunctor<int, MemberBase, int, int, int, int, int, int, int> intVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intVolatileFunction7);
    QVERIFY(0 == intVolatileMemberBaseFunctor(&member, 1, 2, 3, 4, 5, 6, 7));
    QEXTVolatileMemberFunctor<double, MemberBase, double, double, double, double, double, double, double> doubleVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleVolatileFunction7);
    QVERIFY(0 == doubleVolatileMemberBaseFunctor(&member, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int, int, int> voidVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidVolatileFunctionB7);
    voidVolatileMemberBaseFunctorB(&member, true, 2, 3, 4, 5, 6, 7);
    QVERIFY("Member::voidVolatileFunctionB7" == *sg_memberString);
    QEXTVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int, int, int> intVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intVolatileFunctionB7);
    QVERIFY(1 == intVolatileMemberBaseFunctorB(&member, true, 2, 3, 4, 5, 6, 7));
    QVERIFY(0 == intVolatileMemberBaseFunctorB(&member, false, 2, 3, 4, 5, 6, 7));
    QEXTVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double, double, double> doubleVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB7);
    QVERIFY(1 == doubleVolatileMemberBaseFunctorB(&member, true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(0 == doubleVolatileMemberBaseFunctorB(&member, false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
}

void QEXTMemberFunctorTest::testConstVolatileFunctorWith7Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTConstVolatileMemberFunctor<void, MemberBase, int, int, int, int, int, int, int> voidConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstVolatileFunction7);
    voidConstVolatileMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5, 6, 7);
    QVERIFY("MemberBase::voidConstVolatileFunction7" == *sg_memberString);
    QEXTConstVolatileMemberFunctor<int, MemberBase, int, int, int, int, int, int, int> intConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstVolatileFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intConstVolatileMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5, 6, 7));
    QEXTConstVolatileMemberFunctor<double, MemberBase, double, double, double, double, double, double, double> doubleConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleConstVolatileMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTConstVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int, int, int> voidConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB7);
    voidConstVolatileMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5, 6, 7);
    QVERIFY("MemberBase::voidConstVolatileFunctionB7" == *sg_memberString);
    QEXTConstVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int, int, int> intConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intConstVolatileMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intConstVolatileMemberBaseFunctorB(&memberBase, false, 2, 3, 4, 5, 6, 7));
    QEXTConstVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double, double, double> doubleConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleConstVolatileMemberBaseFunctorB(&memberBase, true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleConstVolatileMemberBaseFunctorB(&memberBase, false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
}

void QEXTMemberFunctorTest::testPolymorphismConstVolatileFunctorWith7Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTConstVolatileMemberFunctor<void, MemberBase, int, int, int, int, int, int, int> voidConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstVolatileFunction7);
    voidConstVolatileMemberBaseFunctor(&member, 1, 2, 3, 4, 5, 6, 7);
    QVERIFY("Member::voidConstVolatileFunction7" == *sg_memberString);
    QEXTConstVolatileMemberFunctor<int, MemberBase, int, int, int, int, int, int, int> intConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstVolatileFunction7);
    QVERIFY(0 == intConstVolatileMemberBaseFunctor(&member, 1, 2, 3, 4, 5, 6, 7));
    QEXTConstVolatileMemberFunctor<double, MemberBase, double, double, double, double, double, double, double> doubleConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction7);
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctor(&member, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTConstVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int, int, int> voidConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB7);
    voidConstVolatileMemberBaseFunctorB(&member, true, 2, 3, 4, 5, 6, 7);
    QVERIFY("Member::voidConstVolatileFunctionB7" == *sg_memberString);
    QEXTConstVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int, int, int> intConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB7);
    QVERIFY(1 == intConstVolatileMemberBaseFunctorB(&member, true, 2, 3, 4, 5, 6, 7));
    QVERIFY(0 == intConstVolatileMemberBaseFunctorB(&member, false, 2, 3, 4, 5, 6, 7));
    QEXTConstVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double, double, double> doubleConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB7);
    QVERIFY(1 == doubleConstVolatileMemberBaseFunctorB(&member, true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctorB(&member, false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
}

void QEXTMemberFunctorTest::testBoundFunctorWith7Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTBoundMemberFunctor<void, MemberBase, int, int, int, int, int, int, int> voidBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidFunction7);
    voidBoundMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7);
    QVERIFY("MemberBase::voidFunction7" == *sg_memberString);
    QEXTBoundMemberFunctor<int, MemberBase, int, int, int, int, int, int, int> intBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intBoundMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7));
    QEXTBoundMemberFunctor<double, MemberBase, double, double, double, double, double, double, double> doubleBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundMemberFunctor<void, MemberBase, bool, int, int, int, int, int, int> voidBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidFunctionB7);
    voidBoundMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7);
    QVERIFY("MemberBase::voidFunctionB7" == *sg_memberString);
    QEXTBoundMemberFunctor<int, MemberBase, bool, int, int, int, int, int, int> intBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intBoundMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intBoundMemberBaseFunctorB(false, 2, 3, 4, 5, 6, 7));
    QEXTBoundMemberFunctor<double, MemberBase, bool, double, double, double, double, double, double> doubleBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleBoundMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
}

void QEXTMemberFunctorTest::testPolymorphismBoundFunctorWith7Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTBoundMemberFunctor<void, MemberBase, int, int, int, int, int, int, int> voidBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction7);
    voidBoundMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7);
    QVERIFY("Member::voidFunction7" == *sg_memberString);
    QEXTBoundMemberFunctor<int, MemberBase, int, int, int, int, int, int, int> intBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction7);
    QVERIFY(0 == intBoundMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7));
    QEXTBoundMemberFunctor<double, MemberBase, double, double, double, double, double, double, double> doubleBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction7);
    QVERIFY(0 == doubleBoundMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundMemberFunctor<void, MemberBase, bool, int, int, int, int, int, int> voidBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunctionB7);
    voidBoundMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7);
    QVERIFY("Member::voidFunctionB7" == *sg_memberString);
    QEXTBoundMemberFunctor<int, MemberBase, bool, int, int, int, int, int, int> intBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunctionB7);
    QVERIFY(1 == intBoundMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(0 == intBoundMemberBaseFunctorB(false, 2, 3, 4, 5, 6, 7));
    QEXTBoundMemberFunctor<double, MemberBase, bool, double, double, double, double, double, double> doubleBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunctionB7);
    QVERIFY(1 == doubleBoundMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
}

void QEXTMemberFunctorTest::testBoundConstFunctorWith7Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTBoundConstMemberFunctor<void, MemberBase, int, int, int, int, int, int, int> voidBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunction7);
    voidBoundConstMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7);
    QVERIFY("MemberBase::voidConstFunction7" == *sg_memberString);
    QEXTBoundConstMemberFunctor<int, MemberBase, int, int, int, int, int, int, int> intBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intConstFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intBoundConstMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7));
    QEXTBoundConstMemberFunctor<double, MemberBase, double, double, double, double, double, double, double> doubleBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundConstMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundConstMemberFunctor<void, MemberBase, bool, int, int, int, int, int, int> voidBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunctionB7);
    voidBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7);
    QVERIFY("MemberBase::voidConstFunctionB7" == *sg_memberString);
    QEXTBoundConstMemberFunctor<int, MemberBase, bool, int, int, int, int, int, int> intBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intConstFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intBoundConstMemberBaseFunctorB(false, 2, 3, 4, 5, 6, 7));
    QEXTBoundConstMemberFunctor<double, MemberBase, bool, double, double, double, double, double, double> doubleBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundConstMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleBoundConstMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
}

void QEXTMemberFunctorTest::testPolymorphismBoundConstFunctorWith7Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTBoundConstMemberFunctor<void, MemberBase, int, int, int, int, int, int, int> voidBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction7);
    voidBoundConstMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7);
    QVERIFY("Member::voidConstFunction7" == *sg_memberString);
    QEXTBoundConstMemberFunctor<int, MemberBase, int, int, int, int, int, int, int> intBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction7);
    QVERIFY(0 == intBoundConstMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7));
    QEXTBoundConstMemberFunctor<double, MemberBase, double, double, double, double, double, double, double> doubleBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction7);
    QVERIFY(0 == doubleBoundConstMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundConstMemberFunctor<void, MemberBase, bool, int, int, int, int, int, int> voidBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunctionB7);
    voidBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7);
    QVERIFY("Member::voidConstFunctionB7" == *sg_memberString);
    QEXTBoundConstMemberFunctor<int, MemberBase, bool, int, int, int, int, int, int> intBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunctionB7);
    QVERIFY(1 == intBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB(false, 2, 3, 4, 5, 6, 7));
    QEXTBoundConstMemberFunctor<double, MemberBase, bool, double, double, double, double, double, double> doubleBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunctionB7);
    QVERIFY(1 == doubleBoundConstMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
}

void QEXTMemberFunctorTest::testBoundVolatileFunctorWith7Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTBoundVolatileMemberFunctor<void, MemberBase, int, int, int, int, int, int, int> voidBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunction7);
    voidBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7);
    QVERIFY("MemberBase::voidVolatileFunction7" == *sg_memberString);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, int, int, int, int, int, int, int> intBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, double, double, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int, int, int> voidBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunctionB7);
    voidBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7);
    QVERIFY("MemberBase::voidVolatileFunctionB7" == *sg_memberString);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int, int, int> intBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intBoundVolatileMemberBaseFunctorB(false, 2, 3, 4, 5, 6, 7));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
}

void QEXTMemberFunctorTest::testPolymorphismBoundVolatileFunctorWith7Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTBoundVolatileMemberFunctor<void, MemberBase, int, int, int, int, int, int, int> voidBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction7);
    voidBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7);
    QVERIFY("Member::voidVolatileFunction7" == *sg_memberString);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, int, int, int, int, int, int, int> intBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction7);
    QVERIFY(0 == intBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, double, double, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction7);
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int, int, int> voidBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunctionB7);
    voidBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7);
    QVERIFY("Member::voidVolatileFunctionB7" == *sg_memberString);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int, int, int> intBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunctionB7);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB(false, 2, 3, 4, 5, 6, 7));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunctionB7);
    QVERIFY(1 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
}

void QEXTMemberFunctorTest::testBoundConstVolatileFunctorWith7Arg()
{
    QString string;
    sg_memberString = &string;

    MemberBase memberBase;

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, int, int, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunction7);
    voidBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7);
    QVERIFY("MemberBase::voidConstVolatileFunction7" == *sg_memberString);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, int, int, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, double, double, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunctionB7);
    voidBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7);
    QVERIFY("MemberBase::voidConstVolatileFunctionB7" == *sg_memberString);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intBoundConstVolatileMemberBaseFunctorB(false, 2, 3, 4, 5, 6, 7));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
}

void QEXTMemberFunctorTest::testPolymorphismBoundConstVolatileFunctorWith7Arg()
{
    QString string;
    sg_memberString = &string;

    Member member;

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, int, int, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction7);
    voidBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7);
    QVERIFY("Member::voidConstVolatileFunction7" == *sg_memberString);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, int, int, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction7);
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, double, double, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction7);
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunctionB7);
    voidBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7);
    QVERIFY("Member::voidConstVolatileFunctionB7" == *sg_memberString);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunctionB7);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB(false, 2, 3, 4, 5, 6, 7));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunctionB7);
    QVERIFY(1 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
}


QTEST_APPLESS_MAIN(QEXTMemberFunctorTest)

#include <tst_qextMemberFunctor.moc>
