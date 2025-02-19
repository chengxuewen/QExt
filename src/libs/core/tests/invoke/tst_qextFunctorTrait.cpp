#include <qextFunctorTrait.h>
#include <qextPointerFunctor.h>
#include <qextMemberFunctor.h>

#include <QtTest>
#include <QObject>

#include <iostream>

class QExtFunctorTraitTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void testCustomDerivedType();
    void testFunctorArg0Type();
    void testFunctorArg1Type();
    void testFunctorArg2Type();
    void testFunctorArg3Type();
    void testFunctorArg4Type();
    void testFunctorArg5Type();
    void testFunctorArg6Type();
    void testFunctorArg7Type();
    void testMemberFunctorArg0Type();
    void testConstMemberFunctorArg0Type();
    void testVolatileMemberFunctorArg0Type();
    void testConstVolatileMemberFunctorArg0Type();
    void testBoundMemberFunctorArg0Type();
    void testBoundConstMemberFunctorArg0Type();
    void testBoundVolatileMemberFunctorArg0Type();
    void testBoundConstVolatileMemberFunctorArg0Type();
    void testMemberFunctorArg1Type();
    void testConstMemberFunctorArg1Type();
    void testVolatileMemberFunctorArg1Type();
    void testConstVolatileMemberFunctorArg1Type();
    void testBoundMemberFunctorArg1Type();
    void testBoundConstMemberFunctorArg1Type();
    void testBoundVolatileMemberFunctorArg1Type();
    void testBoundConstVolatileMemberFunctorArg1Type();
    void testMemberFunctorArg2Type();
    void testConstMemberFunctorArg2Type();
    void testVolatileMemberFunctorArg2Type();
    void testConstVolatileMemberFunctorArg2Type();
    void testBoundMemberFunctorArg2Type();
    void testBoundConstMemberFunctorArg2Type();
    void testBoundVolatileMemberFunctorArg2Type();
    void testBoundConstVolatileMemberFunctorArg2Type();
    void testMemberFunctorArg3Type();
    void testConstMemberFunctorArg3Type();
    void testVolatileMemberFunctorArg3Type();
    void testConstVolatileMemberFunctorArg3Type();
    void testBoundMemberFunctorArg3Type();
    void testBoundConstMemberFunctorArg3Type();
    void testBoundVolatileMemberFunctorArg3Type();
    void testBoundConstVolatileMemberFunctorArg3Type();
    void testMemberFunctorArg4Type();
    void testConstMemberFunctorArg4Type();
    void testVolatileMemberFunctorArg4Type();
    void testConstVolatileMemberFunctorArg4Type();
    void testBoundMemberFunctorArg4Type();
    void testBoundConstMemberFunctorArg4Type();
    void testBoundVolatileMemberFunctorArg4ype();
    void testBoundConstVolatileMemberFunctorArg4Type();
    void testMemberFunctorArg5Type();
    void testConstMemberFunctorArg5Type();
    void testVolatileMemberFunctorArg5Type();
    void testConstVolatileMemberFunctorArg5Type();
    void testBoundMemberFunctorArg5Type();
    void testBoundConstMemberFunctorArg5Type();
    void testBoundVolatileMemberFunctorArg5Type();
    void testBoundConstVolatileMemberFunctorArg5Type();
    void testMemberFunctorArg6Type();
    void testConstMemberFunctorArg6Type();
    void testVolatileMemberFunctorArg6Type();
    void testConstVolatileMemberFunctorArg6Type();
    void testBoundMemberFunctorArg6Type();
    void testBoundConstMemberFunctorArg6Type();
    void testBoundVolatileMemberFunctorArg6Type();
    void testBoundConstVolatileMemberFunctorArg6Type();
    void testMemberFunctorArg7Type();
    void testConstMemberFunctorArg7Type();
    void testVolatileMemberFunctorArg7Type();
    void testConstVolatileMemberFunctorArg7Type();
    void testBoundMemberFunctorArg7Type();
    void testBoundConstMemberFunctorArg7Type();
    void testBoundVolatileMemberFunctorArg7Type();
    void testBoundConstVolatileMemberFunctorArg7Type();
};

class Member
{
public:
    Member() {}


    void voidFunction0()
    {
        std::cout << "Member::voidFunction0" << std::endl;
    }
    void voidFunction1(int a1)
    {
        std::cout << "Member::voidFunction1:" << a1 << std::endl;
    }
    void voidFunction2(int a1, int a2)
    {
        std::cout << "Member::voidFunction2:" << a1 << "," << a2 << std::endl;
    }
    void voidFunction3(int a1, int a2, int a3)
    {
        std::cout << "Member::voidFunction3:" << a1 << "," << a2 << "," << a3 << std::endl;
    }
    void voidFunction4(int a1, int a2, int a3, int a4)
    {
        std::cout << "Member::voidFunction4:" << a1 << "," << a2 << "," << a3 << "," << a4 << std::endl;
    }
    void voidFunction5(int a1, int a2, int a3, int a4, int a5)
    {
        std::cout << "Member::voidFunction5:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << std::endl;
    }
    void voidFunction6(int a1, int a2, int a3, int a4, int a5, int a6)
    {
        std::cout << "Member::voidFunction6:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6 << std::endl;
    }
    void voidFunction7(int a1, int a2, int a3, int a4, int a5, int a6, int a7)
    {
        std::cout << "Member::voidFunction7:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6 << "," << a7 << std::endl;
    }
    void voidFunctionB1(bool a1)
    {
        std::cout << "Member::voidFunctionB1:" << a1 << std::endl;
    }
    void voidFunctionB2(bool a1, int a2)
    {
        std::cout << "Member::voidFunctionB2:" << a1 << "," << a2 << std::endl;
    }
    void voidFunctionB3(bool a1, int a2, int a3)
    {
        std::cout << "Member::voidFunctionB3:" << a1 << "," << a2 << "," << a3 << std::endl;
    }
    void voidFunctionB4(bool a1, int a2, int a3, int a4)
    {
        std::cout << "Member::voidFunctionB4:" << a1 << "," << a2 << "," << a3 << "," << a4 << std::endl;
    }
    void voidFunctionB5(bool a1, int a2, int a3, int a4, int a5)
    {
        std::cout << "Member::voidFunctionB5:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << std::endl;
    }
    void voidFunctionB6(bool a1, int a2, int a3, int a4, int a5, int a6)
    {
        std::cout << "Member::voidFunctionB6:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6 << std::endl;
    }
    void voidFunctionB7(bool a1, int a2, int a3, int a4, int a5, int a6, int a7)
    {
        std::cout << "Member::voidFunctionB7:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6 << "," << a7 << std::endl;
    }

    int intFunction0()
    {
        return 0;
    }
    int intFunction1(int a1)
    {
        Q_UNUSED(a1)
        return 0;
    }
    int intFunction2(int a1, int a2)
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        return 0;
    }
    int intFunction3(int a1, int a2, int a3)
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        return 0;
    }
    int intFunction4(int a1, int a2, int a3, int a4)
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        return 0;
    }
    int intFunction5(int a1, int a2, int a3, int a4, int a5)
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        return 0;
    }
    int intFunction6(int a1, int a2, int a3, int a4, int a5, int a6)
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        return 0;
    }
    int intFunction7(int a1, int a2, int a3, int a4, int a5, int a6, int a7)
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        Q_UNUSED(a7)
        return 0;
    }
    int intFunctionB1(bool a1)
    {
        return a1 ? 1 : 0;
    }
    int intFunctionB2(bool a1, int a2)
    {
        Q_UNUSED(a2)
        return a1 ? 1 : 0;
    }
    int intFunctionB3(bool a1, int a2, int a3)
    {
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        return a1 ? 1 : 0;
    }
    int intFunctionB4(bool a1, int a2, int a3, int a4)
    {
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        return a1 ? 1 : 0;
    }
    int intFunctionB5(bool a1, int a2, int a3, int a4, int a5)
    {
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        return a1 ? 1 : 0;
    }
    int intFunctionB6(bool a1, int a2, int a3, int a4, int a5, int a6)
    {
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        return a1 ? 1 : 0;
    }
    int intFunctionB7(bool a1, int a2, int a3, int a4, int a5, int a6, int a7)
    {
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        Q_UNUSED(a7)
        return a1 ? 1 : 0;
    }

    double doubleFunction0()
    {
        return 0;
    }
    double doubleFunction1(double a1)
    {
        Q_UNUSED(a1)
        return 0;
    }
    double doubleFunction2(double a1, double a2)
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        return 0;
    }
    double doubleFunction3(double a1, double a2, double a3)
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        return 0;
    }
    double doubleFunction4(double a1, double a2, double a3, double a4)
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        return 0;
    }
    double doubleFunction5(double a1, double a2, double a3, double a4, double a5)
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        return 0;
    }
    double doubleFunction6(double a1, double a2, double a3, double a4, double a5, double a6)
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        return 0;
    }
    double doubleFunction7(double a1, double a2, double a3, double a4, double a5, double a6, double a7)
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        Q_UNUSED(a7)
        return 0;
    }
    double doubleFunctionB1(bool a1)
    {
        return a1 ? 1 : 0;
    }
    double doubleFunctionB2(bool a1, double a2)
    {
        Q_UNUSED(a2)
        return a1 ? 1 : 0;
    }
    double doubleFunctionB3(bool a1, double a2, double a3)
    {
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        return a1 ? 1 : 0;
    }
    double doubleFunctionB4(bool a1, double a2, double a3, double a4)
    {
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        return a1 ? 1 : 0;
    }
    double doubleFunctionB5(bool a1, double a2, double a3, double a4, double a5)
    {
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        return a1 ? 1 : 0;
    }
    double doubleFunctionB6(bool a1, double a2, double a3, double a4, double a5, double a6)
    {
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        return a1 ? 1 : 0;
    }
    double doubleFunctionB7(bool a1, double a2, double a3, double a4, double a5, double a6, double a7)
    {
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        Q_UNUSED(a7)
        return a1 ? 1 : 0;
    }



    // const function
    void voidConstFunction0() const
    {
        std::cout << "Member::voidConstFunction0" << std::endl;
    }
    void voidConstFunction1(int a1) const
    {
        std::cout << "Member::voidConstFunction1:" << a1 << std::endl;
    }
    void voidConstFunction2(int a1, int a2) const
    {
        std::cout << "Member::voidConstFunction2:" << a1 << "," << a2 << std::endl;
    }
    void voidConstFunction3(int a1, int a2, int a3) const
    {
        std::cout << "Member::voidConstFunction3:" << a1 << "," << a2 << "," << a3 << std::endl;
    }
    void voidConstFunction4(int a1, int a2, int a3, int a4) const
    {
        std::cout << "Member::voidConstFunction4:" << a1 << "," << a2 << "," << a3 << "," << a4 << std::endl;
    }
    void voidConstFunction5(int a1, int a2, int a3, int a4, int a5) const
    {
        std::cout << "Member::voidConstFunction5:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << std::endl;
    }
    void voidConstFunction6(int a1, int a2, int a3, int a4, int a5, int a6) const
    {
        std::cout << "Member::voidConstFunction6:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6 << std::endl;
    }
    void voidConstFunction7(int a1, int a2, int a3, int a4, int a5, int a6, int a7) const
    {
        std::cout << "Member::voidConstFunction7:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6 << "," << a7 << std::endl;
    }
    void voidConstFunctionB1(bool a1) const
    {
        std::cout << "Member::voidConstFunctionB1:" << a1 << std::endl;
    }
    void voidConstFunctionB2(bool a1, int a2) const
    {
        std::cout << "Member::voidConstFunctionB2:" << a1 << "," << a2 << std::endl;
    }
    void voidConstFunctionB3(bool a1, int a2, int a3) const
    {
        std::cout << "Member::voidConstFunctionB3:" << a1 << "," << a2 << "," << a3 << std::endl;
    }
    void voidConstFunctionB4(bool a1, int a2, int a3, int a4) const
    {
        std::cout << "Member::voidConstFunctionB4:" << a1 << "," << a2 << "," << a3 << "," << a4 << std::endl;
    }
    void voidConstFunctionB5(bool a1, int a2, int a3, int a4, int a5) const
    {
        std::cout << "Member::voidConstFunctionB5:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << std::endl;
    }
    void voidConstFunctionB6(bool a1, int a2, int a3, int a4, int a5, int a6) const
    {
        std::cout << "Member::voidConstFunctionB6:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6 << std::endl;
    }
    void voidConstFunctionB7(bool a1, int a2, int a3, int a4, int a5, int a6, int a7) const
    {
        std::cout << "Member::voidConstFunctionB7:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6 << "," << a7 << std::endl;
    }

    int intConstFunction0() const
    {
        return 0;
    }
    int intConstFunction1(int a1) const
    {
        Q_UNUSED(a1)
        return 0;
    }
    int intConstFunction2(int a1, int a2) const
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        return 0;
    }
    int intConstFunction3(int a1, int a2, int a3) const
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        return 0;
    }
    int intConstFunction4(int a1, int a2, int a3, int a4) const
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        return 0;
    }
    int intConstFunction5(int a1, int a2, int a3, int a4, int a5) const
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        return 0;
    }
    int intConstFunction6(int a1, int a2, int a3, int a4, int a5, int a6) const
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        return 0;
    }
    int intConstFunction7(int a1, int a2, int a3, int a4, int a5, int a6, int a7) const
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        Q_UNUSED(a7)
        return 0;
    }
    int intConstFunctionB1(bool a1) const
    {
        return a1 ? 1 : 0;
    }
    int intConstFunctionB2(bool a1, int a2) const
    {
        Q_UNUSED(a2)
        return a1 ? 1 : 0;
    }
    int intConstFunctionB3(bool a1, int a2, int a3) const
    {
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        return a1 ? 1 : 0;
    }
    int intConstFunctionB4(bool a1, int a2, int a3, int a4) const
    {
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        return a1 ? 1 : 0;
    }
    int intConstFunctionB5(bool a1, int a2, int a3, int a4, int a5) const
    {
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        return a1 ? 1 : 0;
    }
    int intConstFunctionB6(bool a1, int a2, int a3, int a4, int a5, int a6) const
    {
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        return a1 ? 1 : 0;
    }
    int intConstFunctionB7(bool a1, int a2, int a3, int a4, int a5, int a6, int a7) const
    {
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        Q_UNUSED(a7)
        return a1 ? 1 : 0;
    }

    double doubleConstFunction0() const
    {
        return 0;
    }
    double doubleConstFunction1(double a1) const
    {
        Q_UNUSED(a1)
        return 0;
    }
    double doubleConstFunction2(double a1, double a2) const
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        return 0;
    }
    double doubleConstFunction3(double a1, double a2, double a3) const
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        return 0;
    }
    double doubleConstFunction4(double a1, double a2, double a3, double a4) const
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        return 0;
    }
    double doubleConstFunction5(double a1, double a2, double a3, double a4, double a5) const
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        return 0;
    }
    double doubleConstFunction6(double a1, double a2, double a3, double a4, double a5, double a6) const
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        return 0;
    }
    double doubleConstFunction7(double a1, double a2, double a3, double a4, double a5, double a6, double a7) const
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        Q_UNUSED(a7)
        return 0;
    }
    double doubleConstFunctionB1(bool a1) const
    {
        return a1 ? 1 : 0;
    }
    double doubleConstFunctionB2(bool a1, double a2) const
    {
        Q_UNUSED(a2)
        return a1 ? 1 : 0;
    }
    double doubleConstFunctionB3(bool a1, double a2, double a3) const
    {
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        return a1 ? 1 : 0;
    }
    double doubleConstFunctionB4(bool a1, double a2, double a3, double a4) const
    {
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        return a1 ? 1 : 0;
    }
    double doubleConstFunctionB5(bool a1, double a2, double a3, double a4, double a5) const
    {
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        return a1 ? 1 : 0;
    }
    double doubleConstFunctionB6(bool a1, double a2, double a3, double a4, double a5, double a6) const
    {
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        return a1 ? 1 : 0;
    }
    double doubleConstFunctionB7(bool a1, double a2, double a3, double a4, double a5, double a6, double a7) const
    {
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        Q_UNUSED(a7)
        return a1 ? 1 : 0;
    }


    // volatile function
    void voidVolatileFunction0() volatile
    {
        std::cout << "Member::voidVolatileFunction0" << std::endl;
    }
    void voidVolatileFunction1(int a1) volatile
    {
        std::cout << "Member::voidVolatileFunction1:" << a1 << std::endl;
    }
    void voidVolatileFunction2(int a1, int a2) volatile
    {
        std::cout << "Member::voidVolatileFunction2:" << a1 << "," << a2 << std::endl;
    }
    void voidVolatileFunction3(int a1, int a2, int a3) volatile
    {
        std::cout << "Member::voidVolatileFunction3:" << a1 << "," << a2 << "," << a3 << std::endl;
    }
    void voidVolatileFunction4(int a1, int a2, int a3, int a4) volatile
    {
        std::cout << "Member::voidVolatileFunction4:" << a1 << "," << a2 << "," << a3 << "," << a4 << std::endl;
    }
    void voidVolatileFunction5(int a1, int a2, int a3, int a4, int a5) volatile
    {
        std::cout << "Member::voidVolatileFunction5:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << std::endl;
    }
    void voidVolatileFunction6(int a1, int a2, int a3, int a4, int a5, int a6) volatile
    {
        std::cout << "Member::voidVolatileFunction6:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6 << std::endl;
    }
    void voidVolatileFunction7(int a1, int a2, int a3, int a4, int a5, int a6, int a7) volatile
    {
        std::cout << "Member::voidVolatileFunction7:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6 << "," << a7 << std::endl;
    }
    void voidVolatileFunctionB1(bool a1) volatile
    {
        std::cout << "Member::voidVolatileFunctionB1:" << a1 << std::endl;
    }
    void voidVolatileFunctionB2(bool a1, int a2) volatile
    {
        std::cout << "Member::voidVolatileFunctionB2:" << a1 << "," << a2 << std::endl;
    }
    void voidVolatileFunctionB3(bool a1, int a2, int a3) volatile
    {
        std::cout << "Member::voidVolatileFunctionB3:" << a1 << "," << a2 << "," << a3 << std::endl;
    }
    void voidVolatileFunctionB4(bool a1, int a2, int a3, int a4) volatile
    {
        std::cout << "Member::voidVolatileFunctionB4:" << a1 << "," << a2 << "," << a3 << "," << a4 << std::endl;
    }
    void voidVolatileFunctionB5(bool a1, int a2, int a3, int a4, int a5) volatile
    {
        std::cout << "Member::voidVolatileFunctionB5:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << std::endl;
    }
    void voidVolatileFunctionB6(bool a1, int a2, int a3, int a4, int a5, int a6) volatile
    {
        std::cout << "Member::voidVolatileFunctionB6:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6 << std::endl;
    }
    void voidVolatileFunctionB7(bool a1, int a2, int a3, int a4, int a5, int a6, int a7) volatile
    {
        std::cout << "Member::voidVolatileFunctionB7:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6 << "," << a7 << std::endl;
    }

    int intVolatileFunction0() volatile
    {
        return 0;
    }
    int intVolatileFunction1(int a1) volatile
    {
        Q_UNUSED(a1)
        return 0;
    }
    int intVolatileFunction2(int a1, int a2) volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        return 0;
    }
    int intVolatileFunction3(int a1, int a2, int a3) volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        return 0;
    }
    int intVolatileFunction4(int a1, int a2, int a3, int a4) volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        return 0;
    }
    int intVolatileFunction5(int a1, int a2, int a3, int a4, int a5) volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        return 0;
    }
    int intVolatileFunction6(int a1, int a2, int a3, int a4, int a5, int a6) volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        return 0;
    }
    int intVolatileFunction7(int a1, int a2, int a3, int a4, int a5, int a6, int a7) volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        Q_UNUSED(a7)
        return 0;
    }
    int intVolatileFunctionB1(bool a1) volatile
    {
        return a1;
    }
    int intVolatileFunctionB2(bool a1, int a2) volatile
    {
        Q_UNUSED(a2)
        return a1 ? 1 : 0;
    }
    int intVolatileFunctionB3(bool a1, int a2, int a3) volatile
    {
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        return a1 ? 1 : 0;
    }
    int intVolatileFunctionB4(bool a1, int a2, int a3, int a4) volatile
    {
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        return a1 ? 1 : 0;
    }
    int intVolatileFunctionB5(bool a1, int a2, int a3, int a4, int a5) volatile
    {
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        return a1 ? 1 : 0;
    }
    int intVolatileFunctionB6(bool a1, int a2, int a3, int a4, int a5, int a6) volatile
    {
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        return a1 ? 1 : 0;
    }
    int intVolatileFunctionB7(bool a1, int a2, int a3, int a4, int a5, int a6, int a7) volatile
    {
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        Q_UNUSED(a7)
        return a1 ? 1 : 0;
    }

    double doubleVolatileFunction0() volatile
    {
        return 0;
    }
    double doubleVolatileFunction1(double a1) volatile
    {
        Q_UNUSED(a1)
        return 0;
    }
    double doubleVolatileFunction2(double a1, double a2) volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        return 0;
    }
    double doubleVolatileFunction3(double a1, double a2, double a3) volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        return 0;
    }
    double doubleVolatileFunction4(double a1, double a2, double a3, double a4) volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        return 0;
    }
    double doubleVolatileFunction5(double a1, double a2, double a3, double a4, double a5) volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        return 0;
    }
    double doubleVolatileFunction6(double a1, double a2, double a3, double a4, double a5, double a6) volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        return 0;
    }
    double doubleVolatileFunction7(double a1, double a2, double a3, double a4, double a5, double a6, double a7) volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        Q_UNUSED(a7)
        return 0;
    }
    double doubleVolatileFunctionB1(bool a1) volatile
    {
        return a1 ? 1 : 0;
    }
    double doubleVolatileFunctionB2(bool a1, double a2) volatile
    {
        Q_UNUSED(a2)
        return a1 ? 1 : 0;
    }
    double doubleVolatileFunctionB3(bool a1, double a2, double a3) volatile
    {
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        return a1 ? 1 : 0;
    }
    double doubleVolatileFunctionB4(bool a1, double a2, double a3, double a4) volatile
    {
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        return a1 ? 1 : 0;
    }
    double doubleVolatileFunctionB5(bool a1, double a2, double a3, double a4, double a5) volatile
    {
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        return a1 ? 1 : 0;
    }
    double doubleVolatileFunctionB6(bool a1, double a2, double a3, double a4, double a5, double a6) volatile
    {
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        return a1 ? 1 : 0;
    }
    double doubleVolatileFunctionB7(bool a1, double a2, double a3, double a4, double a5, double a6, double a7) volatile
    {
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        Q_UNUSED(a7)
        return a1 ? 1 : 0;
    }



    // const volatile
    void voidConstVolatileFunction0() const volatile
    {
        std::cout << "Member::voidConstVolatileFunction0" << std::endl;
    }
    void voidConstVolatileFunction1(int a1) const volatile
    {
        std::cout << "Member::voidConstVolatileFunction1:" << a1 << std::endl;
    }
    void voidConstVolatileFunction2(int a1, int a2) const volatile
    {
        std::cout << "Member::voidConstVolatileFunction2:" << a1 << "," << a2 << std::endl;
    }
    void voidConstVolatileFunction3(int a1, int a2, int a3) const volatile
    {
        std::cout << "Member::voidConstVolatileFunction3:" << a1 << "," << a2 << "," << a3 << std::endl;
    }
    void voidConstVolatileFunction4(int a1, int a2, int a3, int a4) const volatile
    {
        std::cout << "Member::voidConstVolatileFunction4:" << a1 << "," << a2 << "," << a3 << "," << a4 << std::endl;
    }
    void voidConstVolatileFunction5(int a1, int a2, int a3, int a4, int a5) const volatile
    {
        std::cout << "Member::voidConstVolatileFunction5:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << std::endl;
    }
    void voidConstVolatileFunction6(int a1, int a2, int a3, int a4, int a5, int a6) const volatile
    {
        std::cout << "Member::voidConstVolatileFunction6:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6 << std::endl;
    }
    void voidConstVolatileFunction7(int a1, int a2, int a3, int a4, int a5, int a6, int a7) const volatile
    {
        std::cout << "Member::voidConstVolatileFunction7:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6 << "," << a7 << std::endl;
    }
    void voidConstVolatileFunctionB1(bool a1) const volatile
    {
        std::cout << "Member::voidConstVolatileFunctionB1:" << a1 << std::endl;
    }
    void voidConstVolatileFunctionB2(bool a1, int a2) const volatile
    {
        std::cout << "Member::voidConstVolatileFunctionB2:" << a1 << "," << a2 << std::endl;
    }
    void voidConstVolatileFunctionB3(bool a1, int a2, int a3) const volatile
    {
        std::cout << "Member::voidConstVolatileFunctionB3:" << a1 << "," << a2 << "," << a3 << std::endl;
    }
    void voidConstVolatileFunctionB4(bool a1, int a2, int a3, int a4) const volatile
    {
        std::cout << "Member::voidConstVolatileFunctionB5:" << a1 << "," << a2 << "," << a3 << "," << a4 << std::endl;
    }
    void voidConstVolatileFunctionB5(bool a1, int a2, int a3, int a4, int a5) const volatile
    {
        std::cout << "Member::voidConstVolatileFunctionB5:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << std::endl;
    }
    void voidConstVolatileFunctionB6(bool a1, int a2, int a3, int a4, int a5, int a6) const volatile
    {
        std::cout << "Member::voidConstVolatileFunctionB6:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6 << std::endl;
    }
    void voidConstVolatileFunctionB7(bool a1, int a2, int a3, int a4, int a5, int a6, int a7) const volatile
    {
        std::cout << "Member::voidConstVolatileFunctionB7:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6 << "," << a7 << std::endl;
    }

    int intConstVolatileFunction0() const volatile
    {
        return 0;
    }
    int intConstVolatileFunction1(int a1) const volatile
    {
        Q_UNUSED(a1)
        return 0;
    }
    int intConstVolatileFunction2(int a1, int a2) const volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        return 0;
    }
    int intConstVolatileFunction3(int a1, int a2, int a3) const volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        return 0;
    }
    int intConstVolatileFunction4(int a1, int a2, int a3, int a4) const volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        return 0;
    }
    int intConstVolatileFunction5(int a1, int a2, int a3, int a4, int a5) const volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        return 0;
    }
    int intConstVolatileFunction6(int a1, int a2, int a3, int a4, int a5, int a6) const volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        return 0;
    }
    int intConstVolatileFunction7(int a1, int a2, int a3, int a4, int a5, int a6, int a7) const volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        Q_UNUSED(a7)
        return 0;
    }
    int intConstVolatileFunctionB1(bool a1) const volatile
    {
        return a1;
    }
    int intConstVolatileFunctionB2(bool a1, int a2) const volatile
    {
        Q_UNUSED(a2)
        return a1 ? 1 : 0;
    }
    int intConstVolatileFunctionB3(bool a1, int a2, int a3) const volatile
    {
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        return a1 ? 1 : 0;
    }
    int intConstVolatileFunctionB4(bool a1, int a2, int a3, int a4) const volatile
    {
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        return a1 ? 1 : 0;
    }
    int intConstVolatileFunctionB5(bool a1, int a2, int a3, int a4, int a5) const volatile
    {
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        return a1 ? 1 : 0;
    }
    int intConstVolatileFunctionB6(bool a1, int a2, int a3, int a4, int a5, int a6) const volatile
    {
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        return a1 ? 1 : 0;
    }
    int intConstVolatileFunctionB7(bool a1, int a2, int a3, int a4, int a5, int a6, int a7) const volatile
    {
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        Q_UNUSED(a7)
        return a1 ? 1 : 0;
    }

    double doubleConstVolatileFunction0() const volatile
    {
        return 0;
    }
    double doubleConstVolatileFunction1(double a1) const volatile
    {
        Q_UNUSED(a1)
        return 0;
    }
    double doubleConstVolatileFunction2(double a1, double a2) const volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        return 0;
    }
    double doubleConstVolatileFunction3(double a1, double a2, double a3) const volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        return 0;
    }
    double doubleConstVolatileFunction4(double a1, double a2, double a3, double a4) const volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        return 0;
    }
    double doubleConstVolatileFunction5(double a1, double a2, double a3, double a4, double a5) const volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        return 0;
    }
    double doubleConstVolatileFunction6(double a1, double a2, double a3, double a4, double a5, double a6) const volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        return 0;
    }
    double doubleConstVolatileFunction7(double a1, double a2, double a3, double a4, double a5, double a6, double a7) const volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        Q_UNUSED(a7)
        return 0;
    }
    double doubleConstVolatileFunctionB1(bool a1) const volatile
    {
        Q_UNUSED(a1)
        return a1 ? 1 : 0;
    }
    double doubleConstVolatileFunctionB2(bool a1, double a2) const volatile
    {
        Q_UNUSED(a2)
        return a1 ? 1 : 0;
    }
    double doubleConstVolatileFunctionB3(bool a1, double a2, double a3) const volatile
    {
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        return a1 ? 1 : 0;
    }
    double doubleConstVolatileFunctionB4(bool a1, double a2, double a3, double a4) const volatile
    {
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        return a1 ? 1 : 0;
    }
    double doubleConstVolatileFunctionB5(bool a1, double a2, double a3, double a4, double a5) const volatile
    {
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        return a1 ? 1 : 0;
    }
    double doubleConstVolatileFunctionB6(bool a1, double a2, double a3, double a4, double a5, double a6) const volatile
    {
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        return a1 ? 1 : 0;
    }
    double doubleConstVolatileFunctionB7(bool a1, double a2, double a3, double a4, double a5, double a6, double a7) const volatile
    {
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        Q_UNUSED(a7)
        return a1 ? 1 : 0;
    }
};

class MCustomBase
{
public:
    MCustomBase() {}

    void function0() { }
};

class MClassBase : public QExtFunctorBase
{
public:
    MClassBase() {}
};

class MClass : public MClassBase
{
public:
    MClass() {}
};

void function() {}



void QExtFunctorTraitTest::testCustomDerivedType()
{
    QVERIFY(QString("UnknownFunctor") == QExtFunctorTrait<MCustomBase>::typeName());

    QVERIFY(QString("QExtFunctorBase") == QExtFunctorTrait<QExtFunctorBase>::typeName());
    QVERIFY(QString("QExtFunctorBase") == QExtFunctorTrait<MClassBase>::typeName());
    QVERIFY(QString("QExtFunctorBase") == QExtFunctorTrait<MClass>::typeName());
}

void QExtFunctorTraitTest::testFunctorArg0Type()
{
    typedef QExtPointerFunctor<void>::FunctionType FunctionType0;
    QVERIFY(QString("QExtPointerFunctor0") == QExtFunctorTrait<FunctionType0>::typeName());
    typedef void (*T_voidfunctor0)();
    QVERIFY(QString("QExtPointerFunctor0") == QExtFunctorTrait<T_voidfunctor0>::typeName());
    typedef int (*T_intfunctor0)();
    QVERIFY(QString("QExtPointerFunctor0") == QExtFunctorTrait<T_intfunctor0>::typeName());
}

void QExtFunctorTraitTest::testFunctorArg1Type()
{
    typedef QExtPointerFunctor<void, int>::FunctionType FunctionType1;
    QVERIFY(QString("QExtPointerFunctor1") == QExtFunctorTrait<FunctionType1>::typeName());
    typedef void (*T_voidfunctor1)(int);
    QVERIFY(QString("QExtPointerFunctor1") == QExtFunctorTrait<T_voidfunctor1>::typeName());
    typedef int (*T_intfunctor1)(double);
    QVERIFY(QString("QExtPointerFunctor1") == QExtFunctorTrait<T_intfunctor1>::typeName());
}

void QExtFunctorTraitTest::testFunctorArg2Type()
{
    typedef QExtPointerFunctor<void, int, double>::FunctionType FunctionType2;
    QVERIFY(QString("QExtPointerFunctor2") == QExtFunctorTrait<FunctionType2>::typeName());
    typedef void (*T_voidfunctor2)(int, QString);
    QVERIFY(QString("QExtPointerFunctor2") == QExtFunctorTrait<T_voidfunctor2>::typeName());
    typedef int (*T_intfunctor2)(int, long);
    QVERIFY(QString("QExtPointerFunctor2") == QExtFunctorTrait<T_intfunctor2>::typeName());
}

void QExtFunctorTraitTest::testFunctorArg3Type()
{
    typedef QExtPointerFunctor<void, int, double, int>::FunctionType FunctionType3;
    QVERIFY(QString("QExtPointerFunctor3") == QExtFunctorTrait<FunctionType3>::typeName());
    typedef void (*T_voidfunctor3)(int, int, int);
    QVERIFY(QString("QExtPointerFunctor3") == QExtFunctorTrait<T_voidfunctor3>::typeName());
    typedef int (*T_intfunctor3)(double, double, int);
    QVERIFY(QString("QExtPointerFunctor3") == QExtFunctorTrait<T_intfunctor3>::typeName());
}

void QExtFunctorTraitTest::testFunctorArg4Type()
{
    typedef QExtPointerFunctor<void, int, double, int, float>::FunctionType FunctionType4;
    QVERIFY(QString("QExtPointerFunctor4") == QExtFunctorTrait<FunctionType4>::typeName());
    typedef void (*T_voidfunctor4)(double, int, double, int);
    QVERIFY(QString("QExtPointerFunctor4") == QExtFunctorTrait<T_voidfunctor4>::typeName());
    typedef int (*T_intfunctor4)(float, int, double, long);
    QVERIFY(QString("QExtPointerFunctor4") == QExtFunctorTrait<T_intfunctor4>::typeName());
}

void QExtFunctorTraitTest::testFunctorArg5Type()
{
    typedef QExtPointerFunctor<void, int, double, int, float, QString>::FunctionType FunctionType5;
    QVERIFY(QString("QExtPointerFunctor5") == QExtFunctorTrait<FunctionType5>::typeName());
    typedef void (*T_voidfunctor5)(int, int, int, int, QString);
    QVERIFY(QString("QExtPointerFunctor5") == QExtFunctorTrait<T_voidfunctor5>::typeName());
    typedef int (*T_intfunctor5)(double, double, int, int, long);
    QVERIFY(QString("QExtPointerFunctor5") == QExtFunctorTrait<T_intfunctor5>::typeName());
}

void QExtFunctorTraitTest::testFunctorArg6Type()
{
    typedef QExtPointerFunctor<void, int, double, int, float, QString, int>::FunctionType FunctionType6;
    QVERIFY(QString("QExtPointerFunctor6") == QExtFunctorTrait<FunctionType6>::typeName());
    typedef void (*T_voidfunctor6)(int, int, int, int, QString, float);
    QVERIFY(QString("QExtPointerFunctor6") == QExtFunctorTrait<T_voidfunctor6>::typeName());
    typedef int (*T_intfunctor6)(double, double, int, int, long, float);
    QVERIFY(QString("QExtPointerFunctor6") == QExtFunctorTrait<T_intfunctor6>::typeName());
}

void QExtFunctorTraitTest::testFunctorArg7Type()
{
    typedef QExtPointerFunctor<void, int, double, int, float, QString, int, double>::FunctionType FunctionType7;
    QVERIFY(QString("QExtPointerFunctor7") == QExtFunctorTrait<FunctionType7>::typeName());
    typedef void (*T_voidfunctor7)(int, int, int, int, QString, float, int);
    QVERIFY(QString("QExtPointerFunctor7") == QExtFunctorTrait<T_voidfunctor7>::typeName());
    typedef int (*T_intfunctor7)(double, double, int, int, long, float, int);
    QVERIFY(QString("QExtPointerFunctor7") == QExtFunctorTrait<T_intfunctor7>::typeName());
}

void QExtFunctorTraitTest::testMemberFunctorArg0Type()
{
    typedef QExtMemberFunctor<void, Member>::FunctionType MemFunctionType0;
    QVERIFY(QString("QExtMemberFunctor0") == QExtFunctorTrait<MemFunctionType0>::typeName());
}

void QExtFunctorTraitTest::testConstMemberFunctorArg0Type()
{
    typedef QExtConstMemberFunctor<void, Member>::FunctionType MemFunctionType0;
    QVERIFY(QString("QExtConstMemberFunctor0") == QExtFunctorTrait<MemFunctionType0>::typeName());
}

void QExtFunctorTraitTest::testVolatileMemberFunctorArg0Type()
{
    typedef QExtVolatileMemberFunctor<void, Member>::FunctionType MemFunctionType0;
    QVERIFY(QString("QExtVolatileMemberFunctor0") == QExtFunctorTrait<MemFunctionType0>::typeName());
}

void QExtFunctorTraitTest::testConstVolatileMemberFunctorArg0Type()
{
    typedef QExtConstVolatileMemberFunctor<void, Member>::FunctionType MemFunctionType0;
    QVERIFY(QString("QExtConstVolatileMemberFunctor0") == QExtFunctorTrait<MemFunctionType0>::typeName());
}

void QExtFunctorTraitTest::testBoundMemberFunctorArg0Type()
{
    typedef QExtBoundMemberFunctor<void, Member>::FunctionType MemFunctionType0;
    QVERIFY(QString("QExtMemberFunctor0") == QExtFunctorTrait<MemFunctionType0>::typeName());
}

void QExtFunctorTraitTest::testBoundConstMemberFunctorArg0Type()
{
    typedef QExtBoundConstMemberFunctor<void, Member>::FunctionType MemFunctionType0;
    QVERIFY(QString("QExtConstMemberFunctor0") == QExtFunctorTrait<MemFunctionType0>::typeName());
}

void QExtFunctorTraitTest::testBoundVolatileMemberFunctorArg0Type()
{
    typedef QExtBoundVolatileMemberFunctor<void, Member>::FunctionType MemFunctionType0;
    QVERIFY(QString("QExtVolatileMemberFunctor0") == QExtFunctorTrait<MemFunctionType0>::typeName());
}

void QExtFunctorTraitTest::testBoundConstVolatileMemberFunctorArg0Type()
{
    typedef QExtBoundConstVolatileMemberFunctor<void, Member>::FunctionType MemFunctionType0;
    QVERIFY(QString("QExtConstVolatileMemberFunctor0") == QExtFunctorTrait<MemFunctionType0>::typeName());
}

void QExtFunctorTraitTest::testMemberFunctorArg1Type()
{
    typedef QExtMemberFunctor<void, Member, int>::FunctionType MemFunctionType1;
    QVERIFY(QString("QExtMemberFunctor1") == QExtFunctorTrait<MemFunctionType1>::typeName());
}

void QExtFunctorTraitTest::testConstMemberFunctorArg1Type()
{
    typedef QExtConstMemberFunctor<void, Member, int>::FunctionType MemFunctionType1;
    QVERIFY(QString("QExtConstMemberFunctor1") == QExtFunctorTrait<MemFunctionType1>::typeName());
}

void QExtFunctorTraitTest::testVolatileMemberFunctorArg1Type()
{
    typedef QExtVolatileMemberFunctor<void, Member, int>::FunctionType MemFunctionType1;
    QVERIFY(QString("QExtVolatileMemberFunctor1") == QExtFunctorTrait<MemFunctionType1>::typeName());
}

void QExtFunctorTraitTest::testConstVolatileMemberFunctorArg1Type()
{
    typedef QExtConstVolatileMemberFunctor<void, Member, int>::FunctionType MemFunctionType1;
    QVERIFY(QString("QExtConstVolatileMemberFunctor1") == QExtFunctorTrait<MemFunctionType1>::typeName());
}

void QExtFunctorTraitTest::testBoundMemberFunctorArg1Type()
{
    typedef QExtBoundMemberFunctor<void, Member, int>::FunctionType MemFunctionType1;
    QVERIFY(QString("QExtMemberFunctor1") == QExtFunctorTrait<MemFunctionType1>::typeName());
}

void QExtFunctorTraitTest::testBoundConstMemberFunctorArg1Type()
{
    typedef QExtBoundConstMemberFunctor<void, Member, int>::FunctionType MemFunctionType1;
    QVERIFY(QString("QExtConstMemberFunctor1") == QExtFunctorTrait<MemFunctionType1>::typeName());
}

void QExtFunctorTraitTest::testBoundVolatileMemberFunctorArg1Type()
{
    typedef QExtBoundVolatileMemberFunctor<void, Member, int>::FunctionType MemFunctionType1;
    QVERIFY(QString("QExtVolatileMemberFunctor1") == QExtFunctorTrait<MemFunctionType1>::typeName());
}

void QExtFunctorTraitTest::testBoundConstVolatileMemberFunctorArg1Type()
{
    typedef QExtBoundConstVolatileMemberFunctor<void, Member, int>::FunctionType MemFunctionType1;
    QVERIFY(QString("QExtConstVolatileMemberFunctor1") == QExtFunctorTrait<MemFunctionType1>::typeName());
}

void QExtFunctorTraitTest::testMemberFunctorArg2Type()
{
    typedef QExtMemberFunctor<void, Member, int, int>::FunctionType MemFunctionType2;
    QVERIFY(QString("QExtMemberFunctor2") == QExtFunctorTrait<MemFunctionType2>::typeName());
}

void QExtFunctorTraitTest::testConstMemberFunctorArg2Type()
{
    typedef QExtConstMemberFunctor<void, Member, int, int>::FunctionType MemFunctionType2;
    QVERIFY(QString("QExtConstMemberFunctor2") == QExtFunctorTrait<MemFunctionType2>::typeName());
}

void QExtFunctorTraitTest::testVolatileMemberFunctorArg2Type()
{
    typedef QExtVolatileMemberFunctor<void, Member, int, int>::FunctionType MemFunctionType2;
    QVERIFY(QString("QExtVolatileMemberFunctor2") == QExtFunctorTrait<MemFunctionType2>::typeName());
}

void QExtFunctorTraitTest::testConstVolatileMemberFunctorArg2Type()
{
    typedef QExtConstVolatileMemberFunctor<void, Member, int, int>::FunctionType MemFunctionType2;
    QVERIFY(QString("QExtConstVolatileMemberFunctor2") == QExtFunctorTrait<MemFunctionType2>::typeName());
}

void QExtFunctorTraitTest::testBoundMemberFunctorArg2Type()
{
    typedef QExtBoundMemberFunctor<void, Member, int, int>::FunctionType MemFunctionType2;
    QVERIFY(QString("QExtMemberFunctor2") == QExtFunctorTrait<MemFunctionType2>::typeName());
}

void QExtFunctorTraitTest::testBoundConstMemberFunctorArg2Type()
{
    typedef QExtBoundConstMemberFunctor<void, Member, int, int>::FunctionType MemFunctionType2;
    QVERIFY(QString("QExtConstMemberFunctor2") == QExtFunctorTrait<MemFunctionType2>::typeName());
}

void QExtFunctorTraitTest::testBoundVolatileMemberFunctorArg2Type()
{
    typedef QExtBoundVolatileMemberFunctor<void, Member, int, int>::FunctionType MemFunctionType2;
    QVERIFY(QString("QExtVolatileMemberFunctor2") == QExtFunctorTrait<MemFunctionType2>::typeName());
}

void QExtFunctorTraitTest::testBoundConstVolatileMemberFunctorArg2Type()
{
    typedef QExtBoundConstVolatileMemberFunctor<void, Member, int, int>::FunctionType MemFunctionType2;
    QVERIFY(QString("QExtConstVolatileMemberFunctor2") == QExtFunctorTrait<MemFunctionType2>::typeName());
}

void QExtFunctorTraitTest::testMemberFunctorArg3Type()
{
    typedef QExtMemberFunctor<void, Member, int, int, int>::FunctionType MemFunctionType3;
    QVERIFY(QString("QExtMemberFunctor3") == QExtFunctorTrait<MemFunctionType3>::typeName());
}

void QExtFunctorTraitTest::testConstMemberFunctorArg3Type()
{
    typedef QExtConstMemberFunctor<void, Member, int, int, int>::FunctionType MemFunctionType3;
    QVERIFY(QString("QExtConstMemberFunctor3") == QExtFunctorTrait<MemFunctionType3>::typeName());
}

void QExtFunctorTraitTest::testVolatileMemberFunctorArg3Type()
{
    typedef QExtVolatileMemberFunctor<void, Member, int, int, int>::FunctionType MemFunctionType3;
    QVERIFY(QString("QExtVolatileMemberFunctor3") == QExtFunctorTrait<MemFunctionType3>::typeName());
}

void QExtFunctorTraitTest::testConstVolatileMemberFunctorArg3Type()
{
    typedef QExtConstVolatileMemberFunctor<void, Member, int, int, int>::FunctionType MemFunctionType3;
    QVERIFY(QString("QExtConstVolatileMemberFunctor3") == QExtFunctorTrait<MemFunctionType3>::typeName());
}

void QExtFunctorTraitTest::testBoundMemberFunctorArg3Type()
{
    typedef QExtBoundMemberFunctor<void, Member, int, int, int>::FunctionType MemFunctionType3;
    QVERIFY(QString("QExtMemberFunctor3") == QExtFunctorTrait<MemFunctionType3>::typeName());
}

void QExtFunctorTraitTest::testBoundConstMemberFunctorArg3Type()
{
    typedef QExtBoundConstMemberFunctor<void, Member, int, int, int>::FunctionType MemFunctionType3;
    QVERIFY(QString("QExtConstMemberFunctor3") == QExtFunctorTrait<MemFunctionType3>::typeName());
}

void QExtFunctorTraitTest::testBoundVolatileMemberFunctorArg3Type()
{
    typedef QExtBoundVolatileMemberFunctor<void, Member, int, int, int>::FunctionType MemFunctionType3;
    QVERIFY(QString("QExtVolatileMemberFunctor3") == QExtFunctorTrait<MemFunctionType3>::typeName());
}

void QExtFunctorTraitTest::testBoundConstVolatileMemberFunctorArg3Type()
{
    typedef QExtBoundConstVolatileMemberFunctor<void, Member, int, int, int>::FunctionType MemFunctionType3;
    QVERIFY(QString("QExtConstVolatileMemberFunctor3") == QExtFunctorTrait<MemFunctionType3>::typeName());
}

void QExtFunctorTraitTest::testMemberFunctorArg4Type()
{
    typedef QExtMemberFunctor<void, Member, int, int, int, int>::FunctionType MemFunctionType4;
    QVERIFY(QString("QExtMemberFunctor4") == QExtFunctorTrait<MemFunctionType4>::typeName());
}

void QExtFunctorTraitTest::testConstMemberFunctorArg4Type()
{
    typedef QExtConstMemberFunctor<void, Member, int, int, int, int>::FunctionType MemFunctionType4;
    QVERIFY(QString("QExtConstMemberFunctor4") == QExtFunctorTrait<MemFunctionType4>::typeName());
}

void QExtFunctorTraitTest::testVolatileMemberFunctorArg4Type()
{
    typedef QExtVolatileMemberFunctor<void, Member, int, int, int, int>::FunctionType MemFunctionType4;
    QVERIFY(QString("QExtVolatileMemberFunctor4") == QExtFunctorTrait<MemFunctionType4>::typeName());
}

void QExtFunctorTraitTest::testConstVolatileMemberFunctorArg4Type()
{
    typedef QExtConstVolatileMemberFunctor<void, Member, int, int, int, int>::FunctionType MemFunctionType4;
    QVERIFY(QString("QExtConstVolatileMemberFunctor4") == QExtFunctorTrait<MemFunctionType4>::typeName());
}

void QExtFunctorTraitTest::testBoundMemberFunctorArg4Type()
{
    typedef QExtBoundMemberFunctor<void, Member, int, int, int, int>::FunctionType MemFunctionType4;
    QVERIFY(QString("QExtMemberFunctor4") == QExtFunctorTrait<MemFunctionType4>::typeName());
}

void QExtFunctorTraitTest::testBoundConstMemberFunctorArg4Type()
{
    typedef QExtBoundConstMemberFunctor<void, Member, int, int, int, int>::FunctionType MemFunctionType4;
    QVERIFY(QString("QExtConstMemberFunctor4") == QExtFunctorTrait<MemFunctionType4>::typeName());
}

void QExtFunctorTraitTest::testBoundVolatileMemberFunctorArg4ype()
{
    typedef QExtBoundVolatileMemberFunctor<void, Member, int, int, int, int>::FunctionType MemFunctionType4;
    QVERIFY(QString("QExtVolatileMemberFunctor4") == QExtFunctorTrait<MemFunctionType4>::typeName());
}

void QExtFunctorTraitTest::testBoundConstVolatileMemberFunctorArg4Type()
{
    typedef QExtBoundConstVolatileMemberFunctor<void, Member, int, int, int, int>::FunctionType MemFunctionType4;
    QVERIFY(QString("QExtConstVolatileMemberFunctor4") == QExtFunctorTrait<MemFunctionType4>::typeName());
}

void QExtFunctorTraitTest::testMemberFunctorArg5Type()
{
    typedef QExtMemberFunctor<void, Member, int, int, int, int, int>::FunctionType MemFunctionType5;
    QVERIFY(QString("QExtMemberFunctor5") == QExtFunctorTrait<MemFunctionType5>::typeName());
}

void QExtFunctorTraitTest::testConstMemberFunctorArg5Type()
{
    typedef QExtConstMemberFunctor<void, Member, int, int, int, int, int>::FunctionType MemFunctionType5;
    QVERIFY(QString("QExtConstMemberFunctor5") == QExtFunctorTrait<MemFunctionType5>::typeName());
}

void QExtFunctorTraitTest::testVolatileMemberFunctorArg5Type()
{
    typedef QExtVolatileMemberFunctor<void, Member, int, int, int, int, int>::FunctionType MemFunctionType5;
    QVERIFY(QString("QExtVolatileMemberFunctor5") == QExtFunctorTrait<MemFunctionType5>::typeName());
}

void QExtFunctorTraitTest::testConstVolatileMemberFunctorArg5Type()
{
    typedef QExtConstVolatileMemberFunctor<void, Member, int, int, int, int, int>::FunctionType MemFunctionType5;
    QVERIFY(QString("QExtConstVolatileMemberFunctor5") == QExtFunctorTrait<MemFunctionType5>::typeName());
}

void QExtFunctorTraitTest::testBoundMemberFunctorArg5Type()
{
    typedef QExtBoundMemberFunctor<void, Member, int, int, int, int, int>::FunctionType MemFunctionType5;
    QVERIFY(QString("QExtMemberFunctor5") == QExtFunctorTrait<MemFunctionType5>::typeName());
}

void QExtFunctorTraitTest::testBoundConstMemberFunctorArg5Type()
{
    typedef QExtBoundConstMemberFunctor<void, Member, int, int, int, int, int>::FunctionType MemFunctionType5;
    QVERIFY(QString("QExtConstMemberFunctor5") == QExtFunctorTrait<MemFunctionType5>::typeName());
}

void QExtFunctorTraitTest::testBoundVolatileMemberFunctorArg5Type()
{
    typedef QExtBoundVolatileMemberFunctor<void, Member, int, int, int, int, int>::FunctionType MemFunctionType5;
    QVERIFY(QString("QExtVolatileMemberFunctor5") == QExtFunctorTrait<MemFunctionType5>::typeName());
}

void QExtFunctorTraitTest::testBoundConstVolatileMemberFunctorArg5Type()
{
    typedef QExtBoundConstVolatileMemberFunctor<void, Member, int, int, int, int, int>::FunctionType MemFunctionType5;
    QVERIFY(QString("QExtConstVolatileMemberFunctor5") == QExtFunctorTrait<MemFunctionType5>::typeName());
}

void QExtFunctorTraitTest::testMemberFunctorArg6Type()
{
    typedef QExtMemberFunctor<void, Member, int, int, int, int, int, int>::FunctionType MemFunctionType6;
    QVERIFY(QString("QExtMemberFunctor6") == QExtFunctorTrait<MemFunctionType6>::typeName());
}

void QExtFunctorTraitTest::testConstMemberFunctorArg6Type()
{
    typedef QExtConstMemberFunctor<void, Member, int, int, int, int, int, int>::FunctionType MemFunctionType6;
    QVERIFY(QString("QExtConstMemberFunctor6") == QExtFunctorTrait<MemFunctionType6>::typeName());
}

void QExtFunctorTraitTest::testVolatileMemberFunctorArg6Type()
{
    typedef QExtVolatileMemberFunctor<void, Member, int, int, int, int, int, int>::FunctionType MemFunctionType6;
    QVERIFY(QString("QExtVolatileMemberFunctor6") == QExtFunctorTrait<MemFunctionType6>::typeName());
}

void QExtFunctorTraitTest::testConstVolatileMemberFunctorArg6Type()
{
    typedef QExtConstVolatileMemberFunctor<void, Member, int, int, int, int, int, int>::FunctionType MemFunctionType6;
    QVERIFY(QString("QExtConstVolatileMemberFunctor6") == QExtFunctorTrait<MemFunctionType6>::typeName());
}

void QExtFunctorTraitTest::testBoundMemberFunctorArg6Type()
{
    typedef QExtBoundMemberFunctor<void, Member, int, int, int, int, int, int>::FunctionType MemFunctionType6;
    QVERIFY(QString("QExtMemberFunctor6") == QExtFunctorTrait<MemFunctionType6>::typeName());
}

void QExtFunctorTraitTest::testBoundConstMemberFunctorArg6Type()
{
    typedef QExtBoundConstMemberFunctor<void, Member, int, int, int, int, int, int>::FunctionType MemFunctionType6;
    QVERIFY(QString("QExtConstMemberFunctor6") == QExtFunctorTrait<MemFunctionType6>::typeName());
}

void QExtFunctorTraitTest::testBoundVolatileMemberFunctorArg6Type()
{
    typedef QExtBoundVolatileMemberFunctor<void, Member, int, int, int, int, int, int>::FunctionType MemFunctionType6;
    QVERIFY(QString("QExtVolatileMemberFunctor6") == QExtFunctorTrait<MemFunctionType6>::typeName());
}

void QExtFunctorTraitTest::testBoundConstVolatileMemberFunctorArg6Type()
{
    typedef QExtBoundConstVolatileMemberFunctor<void, Member, int, int, int, int, int, int>::FunctionType MemFunctionType6;
    QVERIFY(QString("QExtConstVolatileMemberFunctor6") == QExtFunctorTrait<MemFunctionType6>::typeName());
}

void QExtFunctorTraitTest::testMemberFunctorArg7Type()
{
    typedef QExtMemberFunctor<void, Member, int, int, int, int, int, int, int>::FunctionType MemFunctionType7;
    QVERIFY(QString("QExtMemberFunctor7") == QExtFunctorTrait<MemFunctionType7>::typeName());
}

void QExtFunctorTraitTest::testConstMemberFunctorArg7Type()
{
    typedef QExtConstMemberFunctor<void, Member, int, int, int, int, int, int, int>::FunctionType MemFunctionType7;
    QVERIFY(QString("QExtConstMemberFunctor7") == QExtFunctorTrait<MemFunctionType7>::typeName());
}

void QExtFunctorTraitTest::testVolatileMemberFunctorArg7Type()
{
    typedef QExtVolatileMemberFunctor<void, Member, int, int, int, int, int, int, int>::FunctionType MemFunctionType7;
    QVERIFY(QString("QExtVolatileMemberFunctor7") == QExtFunctorTrait<MemFunctionType7>::typeName());
}

void QExtFunctorTraitTest::testConstVolatileMemberFunctorArg7Type()
{
    typedef QExtConstVolatileMemberFunctor<void, Member, int, int, int, int, int, int, int>::FunctionType MemFunctionType7;
    QVERIFY(QString("QExtConstVolatileMemberFunctor7") == QExtFunctorTrait<MemFunctionType7>::typeName());
}

void QExtFunctorTraitTest::testBoundMemberFunctorArg7Type()
{
    typedef QExtBoundMemberFunctor<void, Member, int, int, int, int, int, int, int>::FunctionType MemFunctionType7;
    QVERIFY(QString("QExtMemberFunctor7") == QExtFunctorTrait<MemFunctionType7>::typeName());
}

void QExtFunctorTraitTest::testBoundConstMemberFunctorArg7Type()
{
    typedef QExtBoundConstMemberFunctor<void, Member, int, int, int, int, int, int, int>::FunctionType MemFunctionType7;
    QVERIFY(QString("QExtConstMemberFunctor7") == QExtFunctorTrait<MemFunctionType7>::typeName());
}

void QExtFunctorTraitTest::testBoundVolatileMemberFunctorArg7Type()
{
    typedef QExtBoundVolatileMemberFunctor<void, Member, int, int, int, int, int, int, int>::FunctionType MemFunctionType7;
    QVERIFY(QString("QExtVolatileMemberFunctor7") == QExtFunctorTrait<MemFunctionType7>::typeName());
}

void QExtFunctorTraitTest::testBoundConstVolatileMemberFunctorArg7Type()
{
    typedef QExtBoundConstVolatileMemberFunctor<void, Member, int, int, int, int, int, int, int>::FunctionType MemFunctionType7;
    QVERIFY(QString("QExtConstVolatileMemberFunctor7") == QExtFunctorTrait<MemFunctionType7>::typeName());
}


QTEST_APPLESS_MAIN(QExtFunctorTraitTest)

#include <tst_qextFunctorTrait.moc>
