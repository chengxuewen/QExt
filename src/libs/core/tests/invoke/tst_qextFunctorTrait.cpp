#include <qextFunctorTrait.h>
#include <qextPointerFunctor.h>
#include <qextMemberFunctor.h>

#include <QtTest>
#include <QObject>

#include <iostream>

class QEXTFunctorTraitTest : public QObject
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

class MClassBase : public QEXTFunctorBase
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



void QEXTFunctorTraitTest::testCustomDerivedType()
{
    QVERIFY("UnknownFunctor" == QEXTFunctorTrait<MCustomBase>().typeName());

    QVERIFY("QEXTFunctorBase" == QEXTFunctorTrait<QEXTFunctorBase>().typeName());
    QVERIFY("QEXTFunctorBase" == QEXTFunctorTrait<MClassBase>().typeName());
    QVERIFY("QEXTFunctorBase" == QEXTFunctorTrait<MClass>().typeName());
}

void QEXTFunctorTraitTest::testFunctorArg0Type()
{
    typedef QEXTPointerFunctor<void>::Function FunctionType0;
    QVERIFY("QEXTPointerFunctor0" == QEXTFunctorTrait<FunctionType0>().typeName());
    typedef void (*T_voidfunctor0)();
    QVERIFY("QEXTPointerFunctor0" == QEXTFunctorTrait<T_voidfunctor0>().typeName());
    typedef int (*T_intfunctor0)();
    QVERIFY("QEXTPointerFunctor0" == QEXTFunctorTrait<T_intfunctor0>().typeName());
}

void QEXTFunctorTraitTest::testFunctorArg1Type()
{
    typedef QEXTPointerFunctor<void, int>::Function FunctionType1;
    QVERIFY("QEXTPointerFunctor1" == QEXTFunctorTrait<FunctionType1>().typeName());
    typedef void (*T_voidfunctor1)(int);
    QVERIFY("QEXTPointerFunctor1" == QEXTFunctorTrait<T_voidfunctor1>().typeName());
    typedef int (*T_intfunctor1)(double);
    QVERIFY("QEXTPointerFunctor1" == QEXTFunctorTrait<T_intfunctor1>().typeName());
}

void QEXTFunctorTraitTest::testFunctorArg2Type()
{
    typedef QEXTPointerFunctor<void, int, double>::Function FunctionType2;
    QVERIFY("QEXTPointerFunctor2" == QEXTFunctorTrait<FunctionType2>().typeName());
    typedef void (*T_voidfunctor2)(int, QString);
    QVERIFY("QEXTPointerFunctor2" == QEXTFunctorTrait<T_voidfunctor2>().typeName());
    typedef int (*T_intfunctor2)(int, long);
    QVERIFY("QEXTPointerFunctor2" == QEXTFunctorTrait<T_intfunctor2>().typeName());
}

void QEXTFunctorTraitTest::testFunctorArg3Type()
{
    typedef QEXTPointerFunctor<void, int, double, int>::Function FunctionType3;
    QVERIFY("QEXTPointerFunctor3" == QEXTFunctorTrait<FunctionType3>().typeName());
    typedef void (*T_voidfunctor3)(int, int, int);
    QVERIFY("QEXTPointerFunctor3" == QEXTFunctorTrait<T_voidfunctor3>().typeName());
    typedef int (*T_intfunctor3)(double, double, int);
    QVERIFY("QEXTPointerFunctor3" == QEXTFunctorTrait<T_intfunctor3>().typeName());
}

void QEXTFunctorTraitTest::testFunctorArg4Type()
{
    typedef QEXTPointerFunctor<void, int, double, int, float>::Function FunctionType4;
    QVERIFY("QEXTPointerFunctor4" == QEXTFunctorTrait<FunctionType4>().typeName());
    typedef void (*T_voidfunctor4)(double, int, double, int);
    QVERIFY("QEXTPointerFunctor4" == QEXTFunctorTrait<T_voidfunctor4>().typeName());
    typedef int (*T_intfunctor4)(float, int, double, long);
    QVERIFY("QEXTPointerFunctor4" == QEXTFunctorTrait<T_intfunctor4>().typeName());
}

void QEXTFunctorTraitTest::testFunctorArg5Type()
{
    typedef QEXTPointerFunctor<void, int, double, int, float, QString>::Function FunctionType5;
    QVERIFY("QEXTPointerFunctor5" == QEXTFunctorTrait<FunctionType5>().typeName());
    typedef void (*T_voidfunctor5)(int, int, int, int, QString);
    QVERIFY("QEXTPointerFunctor5" == QEXTFunctorTrait<T_voidfunctor5>().typeName());
    typedef int (*T_intfunctor5)(double, double, int, int, long);
    QVERIFY("QEXTPointerFunctor5" == QEXTFunctorTrait<T_intfunctor5>().typeName());
}

void QEXTFunctorTraitTest::testFunctorArg6Type()
{
    typedef QEXTPointerFunctor<void, int, double, int, float, QString, int>::Function FunctionType6;
    QVERIFY("QEXTPointerFunctor6" == QEXTFunctorTrait<FunctionType6>().typeName());
    typedef void (*T_voidfunctor6)(int, int, int, int, QString, float);
    QVERIFY("QEXTPointerFunctor6" == QEXTFunctorTrait<T_voidfunctor6>().typeName());
    typedef int (*T_intfunctor6)(double, double, int, int, long, float);
    QVERIFY("QEXTPointerFunctor6" == QEXTFunctorTrait<T_intfunctor6>().typeName());
}

void QEXTFunctorTraitTest::testFunctorArg7Type()
{
    typedef QEXTPointerFunctor<void, int, double, int, float, QString, int, double>::Function FunctionType7;
    QVERIFY("QEXTPointerFunctor7" == QEXTFunctorTrait<FunctionType7>().typeName());
    typedef void (*T_voidfunctor7)(int, int, int, int, QString, float, int);
    QVERIFY("QEXTPointerFunctor7" == QEXTFunctorTrait<T_voidfunctor7>().typeName());
    typedef int (*T_intfunctor7)(double, double, int, int, long, float, int);
    QVERIFY("QEXTPointerFunctor7" == QEXTFunctorTrait<T_intfunctor7>().typeName());
}

void QEXTFunctorTraitTest::testMemberFunctorArg0Type()
{
    typedef QEXTMemberFunctor<void, Member>::Function MemFunctionType0;
    QVERIFY("QEXTMemberFunctor0" == QEXTFunctorTrait<MemFunctionType0>().typeName());
}

void QEXTFunctorTraitTest::testConstMemberFunctorArg0Type()
{
    typedef QEXTConstMemberFunctor<void, Member>::Function MemFunctionType0;
    QVERIFY("QEXTConstMemberFunctor0" == QEXTFunctorTrait<MemFunctionType0>().typeName());
}

void QEXTFunctorTraitTest::testVolatileMemberFunctorArg0Type()
{
    typedef QEXTVolatileMemberFunctor<void, Member>::Function MemFunctionType0;
    QVERIFY("QEXTVolatileMemberFunctor0" == QEXTFunctorTrait<MemFunctionType0>().typeName());
}

void QEXTFunctorTraitTest::testConstVolatileMemberFunctorArg0Type()
{
    typedef QEXTConstVolatileMemberFunctor<void, Member>::Function MemFunctionType0;
    QVERIFY("QEXTConstVolatileMemberFunctor0" == QEXTFunctorTrait<MemFunctionType0>().typeName());
}

void QEXTFunctorTraitTest::testBoundMemberFunctorArg0Type()
{
    typedef QEXTBoundMemberFunctor<void, Member>::Function MemFunctionType0;
    QVERIFY("QEXTMemberFunctor0" == QEXTFunctorTrait<MemFunctionType0>().typeName());
}

void QEXTFunctorTraitTest::testBoundConstMemberFunctorArg0Type()
{
    typedef QEXTBoundConstMemberFunctor<void, Member>::Function MemFunctionType0;
    QVERIFY("QEXTConstMemberFunctor0" == QEXTFunctorTrait<MemFunctionType0>().typeName());
}

void QEXTFunctorTraitTest::testBoundVolatileMemberFunctorArg0Type()
{
    typedef QEXTBoundVolatileMemberFunctor<void, Member>::Function MemFunctionType0;
    QVERIFY("QEXTVolatileMemberFunctor0" == QEXTFunctorTrait<MemFunctionType0>().typeName());
}

void QEXTFunctorTraitTest::testBoundConstVolatileMemberFunctorArg0Type()
{
    typedef QEXTBoundConstVolatileMemberFunctor<void, Member>::Function MemFunctionType0;
    QVERIFY("QEXTConstVolatileMemberFunctor0" == QEXTFunctorTrait<MemFunctionType0>().typeName());
}

void QEXTFunctorTraitTest::testMemberFunctorArg1Type()
{
    typedef QEXTMemberFunctor<void, Member, int>::Function MemFunctionType1;
    QVERIFY("QEXTMemberFunctor1" == QEXTFunctorTrait<MemFunctionType1>().typeName());
}

void QEXTFunctorTraitTest::testConstMemberFunctorArg1Type()
{
    typedef QEXTConstMemberFunctor<void, Member, int>::Function MemFunctionType1;
    QVERIFY("QEXTConstMemberFunctor1" == QEXTFunctorTrait<MemFunctionType1>().typeName());
}

void QEXTFunctorTraitTest::testVolatileMemberFunctorArg1Type()
{
    typedef QEXTVolatileMemberFunctor<void, Member, int>::Function MemFunctionType1;
    QVERIFY("QEXTVolatileMemberFunctor1" == QEXTFunctorTrait<MemFunctionType1>().typeName());
}

void QEXTFunctorTraitTest::testConstVolatileMemberFunctorArg1Type()
{
    typedef QEXTConstVolatileMemberFunctor<void, Member, int>::Function MemFunctionType1;
    QVERIFY("QEXTConstVolatileMemberFunctor1" == QEXTFunctorTrait<MemFunctionType1>().typeName());
}

void QEXTFunctorTraitTest::testBoundMemberFunctorArg1Type()
{
    typedef QEXTBoundMemberFunctor<void, Member, int>::Function MemFunctionType1;
    QVERIFY("QEXTMemberFunctor1" == QEXTFunctorTrait<MemFunctionType1>().typeName());
}

void QEXTFunctorTraitTest::testBoundConstMemberFunctorArg1Type()
{
    typedef QEXTBoundConstMemberFunctor<void, Member, int>::Function MemFunctionType1;
    QVERIFY("QEXTConstMemberFunctor1" == QEXTFunctorTrait<MemFunctionType1>().typeName());
}

void QEXTFunctorTraitTest::testBoundVolatileMemberFunctorArg1Type()
{
    typedef QEXTBoundVolatileMemberFunctor<void, Member, int>::Function MemFunctionType1;
    QVERIFY("QEXTVolatileMemberFunctor1" == QEXTFunctorTrait<MemFunctionType1>().typeName());
}

void QEXTFunctorTraitTest::testBoundConstVolatileMemberFunctorArg1Type()
{
    typedef QEXTBoundConstVolatileMemberFunctor<void, Member, int>::Function MemFunctionType1;
    QVERIFY("QEXTConstVolatileMemberFunctor1" == QEXTFunctorTrait<MemFunctionType1>().typeName());
}

void QEXTFunctorTraitTest::testMemberFunctorArg2Type()
{
    typedef QEXTMemberFunctor<void, Member, int, int>::Function MemFunctionType2;
    QVERIFY("QEXTMemberFunctor2" == QEXTFunctorTrait<MemFunctionType2>().typeName());
}

void QEXTFunctorTraitTest::testConstMemberFunctorArg2Type()
{
    typedef QEXTConstMemberFunctor<void, Member, int, int>::Function MemFunctionType2;
    QVERIFY("QEXTConstMemberFunctor2" == QEXTFunctorTrait<MemFunctionType2>().typeName());
}

void QEXTFunctorTraitTest::testVolatileMemberFunctorArg2Type()
{
    typedef QEXTVolatileMemberFunctor<void, Member, int, int>::Function MemFunctionType2;
    QVERIFY("QEXTVolatileMemberFunctor2" == QEXTFunctorTrait<MemFunctionType2>().typeName());
}

void QEXTFunctorTraitTest::testConstVolatileMemberFunctorArg2Type()
{
    typedef QEXTConstVolatileMemberFunctor<void, Member, int, int>::Function MemFunctionType2;
    QVERIFY("QEXTConstVolatileMemberFunctor2" == QEXTFunctorTrait<MemFunctionType2>().typeName());
}

void QEXTFunctorTraitTest::testBoundMemberFunctorArg2Type()
{
    typedef QEXTBoundMemberFunctor<void, Member, int, int>::Function MemFunctionType2;
    QVERIFY("QEXTMemberFunctor2" == QEXTFunctorTrait<MemFunctionType2>().typeName());
}

void QEXTFunctorTraitTest::testBoundConstMemberFunctorArg2Type()
{
    typedef QEXTBoundConstMemberFunctor<void, Member, int, int>::Function MemFunctionType2;
    QVERIFY("QEXTConstMemberFunctor2" == QEXTFunctorTrait<MemFunctionType2>().typeName());
}

void QEXTFunctorTraitTest::testBoundVolatileMemberFunctorArg2Type()
{
    typedef QEXTBoundVolatileMemberFunctor<void, Member, int, int>::Function MemFunctionType2;
    QVERIFY("QEXTVolatileMemberFunctor2" == QEXTFunctorTrait<MemFunctionType2>().typeName());
}

void QEXTFunctorTraitTest::testBoundConstVolatileMemberFunctorArg2Type()
{
    typedef QEXTBoundConstVolatileMemberFunctor<void, Member, int, int>::Function MemFunctionType2;
    QVERIFY("QEXTConstVolatileMemberFunctor2" == QEXTFunctorTrait<MemFunctionType2>().typeName());
}

void QEXTFunctorTraitTest::testMemberFunctorArg3Type()
{
    typedef QEXTMemberFunctor<void, Member, int, int, int>::Function MemFunctionType3;
    QVERIFY("QEXTMemberFunctor3" == QEXTFunctorTrait<MemFunctionType3>().typeName());
}

void QEXTFunctorTraitTest::testConstMemberFunctorArg3Type()
{
    typedef QEXTConstMemberFunctor<void, Member, int, int, int>::Function MemFunctionType3;
    QVERIFY("QEXTConstMemberFunctor3" == QEXTFunctorTrait<MemFunctionType3>().typeName());
}

void QEXTFunctorTraitTest::testVolatileMemberFunctorArg3Type()
{
    typedef QEXTVolatileMemberFunctor<void, Member, int, int, int>::Function MemFunctionType3;
    QVERIFY("QEXTVolatileMemberFunctor3" == QEXTFunctorTrait<MemFunctionType3>().typeName());
}

void QEXTFunctorTraitTest::testConstVolatileMemberFunctorArg3Type()
{
    typedef QEXTConstVolatileMemberFunctor<void, Member, int, int, int>::Function MemFunctionType3;
    QVERIFY("QEXTConstVolatileMemberFunctor3" == QEXTFunctorTrait<MemFunctionType3>().typeName());
}

void QEXTFunctorTraitTest::testBoundMemberFunctorArg3Type()
{
    typedef QEXTBoundMemberFunctor<void, Member, int, int, int>::Function MemFunctionType3;
    QVERIFY("QEXTMemberFunctor3" == QEXTFunctorTrait<MemFunctionType3>().typeName());
}

void QEXTFunctorTraitTest::testBoundConstMemberFunctorArg3Type()
{
    typedef QEXTBoundConstMemberFunctor<void, Member, int, int, int>::Function MemFunctionType3;
    QVERIFY("QEXTConstMemberFunctor3" == QEXTFunctorTrait<MemFunctionType3>().typeName());
}

void QEXTFunctorTraitTest::testBoundVolatileMemberFunctorArg3Type()
{
    typedef QEXTBoundVolatileMemberFunctor<void, Member, int, int, int>::Function MemFunctionType3;
    QVERIFY("QEXTVolatileMemberFunctor3" == QEXTFunctorTrait<MemFunctionType3>().typeName());
}

void QEXTFunctorTraitTest::testBoundConstVolatileMemberFunctorArg3Type()
{
    typedef QEXTBoundConstVolatileMemberFunctor<void, Member, int, int, int>::Function MemFunctionType3;
    QVERIFY("QEXTConstVolatileMemberFunctor3" == QEXTFunctorTrait<MemFunctionType3>().typeName());
}

void QEXTFunctorTraitTest::testMemberFunctorArg4Type()
{
    typedef QEXTMemberFunctor<void, Member, int, int, int, int>::Function MemFunctionType4;
    QVERIFY("QEXTMemberFunctor4" == QEXTFunctorTrait<MemFunctionType4>().typeName());
}

void QEXTFunctorTraitTest::testConstMemberFunctorArg4Type()
{
    typedef QEXTConstMemberFunctor<void, Member, int, int, int, int>::Function MemFunctionType4;
    QVERIFY("QEXTConstMemberFunctor4" == QEXTFunctorTrait<MemFunctionType4>().typeName());
}

void QEXTFunctorTraitTest::testVolatileMemberFunctorArg4Type()
{
    typedef QEXTVolatileMemberFunctor<void, Member, int, int, int, int>::Function MemFunctionType4;
    QVERIFY("QEXTVolatileMemberFunctor4" == QEXTFunctorTrait<MemFunctionType4>().typeName());
}

void QEXTFunctorTraitTest::testConstVolatileMemberFunctorArg4Type()
{
    typedef QEXTConstVolatileMemberFunctor<void, Member, int, int, int, int>::Function MemFunctionType4;
    QVERIFY("QEXTConstVolatileMemberFunctor4" == QEXTFunctorTrait<MemFunctionType4>().typeName());
}

void QEXTFunctorTraitTest::testBoundMemberFunctorArg4Type()
{
    typedef QEXTBoundMemberFunctor<void, Member, int, int, int, int>::Function MemFunctionType4;
    QVERIFY("QEXTMemberFunctor4" == QEXTFunctorTrait<MemFunctionType4>().typeName());
}

void QEXTFunctorTraitTest::testBoundConstMemberFunctorArg4Type()
{
    typedef QEXTBoundConstMemberFunctor<void, Member, int, int, int, int>::Function MemFunctionType4;
    QVERIFY("QEXTConstMemberFunctor4" == QEXTFunctorTrait<MemFunctionType4>().typeName());
}

void QEXTFunctorTraitTest::testBoundVolatileMemberFunctorArg4ype()
{
    typedef QEXTBoundVolatileMemberFunctor<void, Member, int, int, int, int>::Function MemFunctionType4;
    QVERIFY("QEXTVolatileMemberFunctor4" == QEXTFunctorTrait<MemFunctionType4>().typeName());
}

void QEXTFunctorTraitTest::testBoundConstVolatileMemberFunctorArg4Type()
{
    typedef QEXTBoundConstVolatileMemberFunctor<void, Member, int, int, int, int>::Function MemFunctionType4;
    QVERIFY("QEXTConstVolatileMemberFunctor4" == QEXTFunctorTrait<MemFunctionType4>().typeName());
}

void QEXTFunctorTraitTest::testMemberFunctorArg5Type()
{
    typedef QEXTMemberFunctor<void, Member, int, int, int, int, int>::Function MemFunctionType5;
    QVERIFY("QEXTMemberFunctor5" == QEXTFunctorTrait<MemFunctionType5>().typeName());
}

void QEXTFunctorTraitTest::testConstMemberFunctorArg5Type()
{
    typedef QEXTConstMemberFunctor<void, Member, int, int, int, int, int>::Function MemFunctionType5;
    QVERIFY("QEXTConstMemberFunctor5" == QEXTFunctorTrait<MemFunctionType5>().typeName());
}

void QEXTFunctorTraitTest::testVolatileMemberFunctorArg5Type()
{
    typedef QEXTVolatileMemberFunctor<void, Member, int, int, int, int, int>::Function MemFunctionType5;
    QVERIFY("QEXTVolatileMemberFunctor5" == QEXTFunctorTrait<MemFunctionType5>().typeName());
}

void QEXTFunctorTraitTest::testConstVolatileMemberFunctorArg5Type()
{
    typedef QEXTConstVolatileMemberFunctor<void, Member, int, int, int, int, int>::Function MemFunctionType5;
    QVERIFY("QEXTConstVolatileMemberFunctor5" == QEXTFunctorTrait<MemFunctionType5>().typeName());
}

void QEXTFunctorTraitTest::testBoundMemberFunctorArg5Type()
{
    typedef QEXTBoundMemberFunctor<void, Member, int, int, int, int, int>::Function MemFunctionType5;
    QVERIFY("QEXTMemberFunctor5" == QEXTFunctorTrait<MemFunctionType5>().typeName());
}

void QEXTFunctorTraitTest::testBoundConstMemberFunctorArg5Type()
{
    typedef QEXTBoundConstMemberFunctor<void, Member, int, int, int, int, int>::Function MemFunctionType5;
    QVERIFY("QEXTConstMemberFunctor5" == QEXTFunctorTrait<MemFunctionType5>().typeName());
}

void QEXTFunctorTraitTest::testBoundVolatileMemberFunctorArg5Type()
{
    typedef QEXTBoundVolatileMemberFunctor<void, Member, int, int, int, int, int>::Function MemFunctionType5;
    QVERIFY("QEXTVolatileMemberFunctor5" == QEXTFunctorTrait<MemFunctionType5>().typeName());
}

void QEXTFunctorTraitTest::testBoundConstVolatileMemberFunctorArg5Type()
{
    typedef QEXTBoundConstVolatileMemberFunctor<void, Member, int, int, int, int, int>::Function MemFunctionType5;
    QVERIFY("QEXTConstVolatileMemberFunctor5" == QEXTFunctorTrait<MemFunctionType5>().typeName());
}

void QEXTFunctorTraitTest::testMemberFunctorArg6Type()
{
    typedef QEXTMemberFunctor<void, Member, int, int, int, int, int, int>::Function MemFunctionType6;
    QVERIFY("QEXTMemberFunctor6" == QEXTFunctorTrait<MemFunctionType6>().typeName());
}

void QEXTFunctorTraitTest::testConstMemberFunctorArg6Type()
{
    typedef QEXTConstMemberFunctor<void, Member, int, int, int, int, int, int>::Function MemFunctionType6;
    QVERIFY("QEXTConstMemberFunctor6" == QEXTFunctorTrait<MemFunctionType6>().typeName());
}

void QEXTFunctorTraitTest::testVolatileMemberFunctorArg6Type()
{
    typedef QEXTVolatileMemberFunctor<void, Member, int, int, int, int, int, int>::Function MemFunctionType6;
    QVERIFY("QEXTVolatileMemberFunctor6" == QEXTFunctorTrait<MemFunctionType6>().typeName());
}

void QEXTFunctorTraitTest::testConstVolatileMemberFunctorArg6Type()
{
    typedef QEXTConstVolatileMemberFunctor<void, Member, int, int, int, int, int, int>::Function MemFunctionType6;
    QVERIFY("QEXTConstVolatileMemberFunctor6" == QEXTFunctorTrait<MemFunctionType6>().typeName());
}

void QEXTFunctorTraitTest::testBoundMemberFunctorArg6Type()
{
    typedef QEXTBoundMemberFunctor<void, Member, int, int, int, int, int, int>::Function MemFunctionType6;
    QVERIFY("QEXTMemberFunctor6" == QEXTFunctorTrait<MemFunctionType6>().typeName());
}

void QEXTFunctorTraitTest::testBoundConstMemberFunctorArg6Type()
{
    typedef QEXTBoundConstMemberFunctor<void, Member, int, int, int, int, int, int>::Function MemFunctionType6;
    QVERIFY("QEXTConstMemberFunctor6" == QEXTFunctorTrait<MemFunctionType6>().typeName());
}

void QEXTFunctorTraitTest::testBoundVolatileMemberFunctorArg6Type()
{
    typedef QEXTBoundVolatileMemberFunctor<void, Member, int, int, int, int, int, int>::Function MemFunctionType6;
    QVERIFY("QEXTVolatileMemberFunctor6" == QEXTFunctorTrait<MemFunctionType6>().typeName());
}

void QEXTFunctorTraitTest::testBoundConstVolatileMemberFunctorArg6Type()
{
    typedef QEXTBoundConstVolatileMemberFunctor<void, Member, int, int, int, int, int, int>::Function MemFunctionType6;
    QVERIFY("QEXTConstVolatileMemberFunctor6" == QEXTFunctorTrait<MemFunctionType6>().typeName());
}

void QEXTFunctorTraitTest::testMemberFunctorArg7Type()
{
    typedef QEXTMemberFunctor<void, Member, int, int, int, int, int, int, int>::Function MemFunctionType7;
    QVERIFY("QEXTMemberFunctor7" == QEXTFunctorTrait<MemFunctionType7>().typeName());
}

void QEXTFunctorTraitTest::testConstMemberFunctorArg7Type()
{
    typedef QEXTConstMemberFunctor<void, Member, int, int, int, int, int, int, int>::Function MemFunctionType7;
    QVERIFY("QEXTConstMemberFunctor7" == QEXTFunctorTrait<MemFunctionType7>().typeName());
}

void QEXTFunctorTraitTest::testVolatileMemberFunctorArg7Type()
{
    typedef QEXTVolatileMemberFunctor<void, Member, int, int, int, int, int, int, int>::Function MemFunctionType7;
    QVERIFY("QEXTVolatileMemberFunctor7" == QEXTFunctorTrait<MemFunctionType7>().typeName());
}

void QEXTFunctorTraitTest::testConstVolatileMemberFunctorArg7Type()
{
    typedef QEXTConstVolatileMemberFunctor<void, Member, int, int, int, int, int, int, int>::Function MemFunctionType7;
    QVERIFY("QEXTConstVolatileMemberFunctor7" == QEXTFunctorTrait<MemFunctionType7>().typeName());
}

void QEXTFunctorTraitTest::testBoundMemberFunctorArg7Type()
{
    typedef QEXTBoundMemberFunctor<void, Member, int, int, int, int, int, int, int>::Function MemFunctionType7;
    QVERIFY("QEXTMemberFunctor7" == QEXTFunctorTrait<MemFunctionType7>().typeName());
}

void QEXTFunctorTraitTest::testBoundConstMemberFunctorArg7Type()
{
    typedef QEXTBoundConstMemberFunctor<void, Member, int, int, int, int, int, int, int>::Function MemFunctionType7;
    QVERIFY("QEXTConstMemberFunctor7" == QEXTFunctorTrait<MemFunctionType7>().typeName());
}

void QEXTFunctorTraitTest::testBoundVolatileMemberFunctorArg7Type()
{
    typedef QEXTBoundVolatileMemberFunctor<void, Member, int, int, int, int, int, int, int>::Function MemFunctionType7;
    QVERIFY("QEXTVolatileMemberFunctor7" == QEXTFunctorTrait<MemFunctionType7>().typeName());
}

void QEXTFunctorTraitTest::testBoundConstVolatileMemberFunctorArg7Type()
{
    typedef QEXTBoundConstVolatileMemberFunctor<void, Member, int, int, int, int, int, int, int>::Function MemFunctionType7;
    QVERIFY("QEXTConstVolatileMemberFunctor7" == QEXTFunctorTrait<MemFunctionType7>().typeName());
}


QTEST_APPLESS_MAIN(QEXTFunctorTraitTest)

#include <tst_qextFunctorTrait.moc>
