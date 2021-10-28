#ifndef QEXTMEMBER_H
#define QEXTMEMBER_H

#include <qextGlobal.h>

#include <string>
#include <sstream>

static std::string *sg_memberString = QEXT_DECL_NULLPTR;

class MemberBase
{
public:
    MemberBase() {}

    void voidFunc()
    {
        *sg_memberString = "MemberBase::voidFunc";
    }

    void voidFunc(int i)
    {
        Q_UNUSED(i)
        *sg_memberString = "MemberBase::voidFunc";
    }

    virtual void voidFunction0()
    {
        *sg_memberString = "MemberBase::voidFunction0";
    }
    virtual void voidFunction1(int a1)
    {
        Q_UNUSED(a1)
        *sg_memberString = "MemberBase::voidFunction1";
    }
    virtual void voidFunction2(int a1, int a2)
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        *sg_memberString = "MemberBase::voidFunction2";
    }
    virtual void voidFunction3(int a1, int a2, int a3)
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        *sg_memberString = "MemberBase::voidFunction3";
    }
    virtual void voidFunction4(int a1, int a2, int a3, int a4)
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        *sg_memberString = "MemberBase::voidFunction4";
    }
    virtual void voidFunction5(int a1, int a2, int a3, int a4, int a5)
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        *sg_memberString = "MemberBase::voidFunction5";
    }
    virtual void voidFunction6(int a1, int a2, int a3, int a4, int a5, int a6)
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        *sg_memberString = "MemberBase::voidFunction6";
    }
    virtual void voidFunction7(int a1, int a2, int a3, int a4, int a5, int a6, int a7)
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        Q_UNUSED(a7)
        *sg_memberString = "MemberBase::voidFunction7";
    }
    virtual void voidFunctionB1(bool a1)
    {
        Q_UNUSED(a1)
        *sg_memberString = "MemberBase::voidFunctionB1";
    }
    virtual void voidFunctionB2(bool a1, int a2)
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        *sg_memberString = "MemberBase::voidFunctionB2";
    }
    virtual void voidFunctionB3(bool a1, int a2, int a3)
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        *sg_memberString = "MemberBase::voidFunctionB3";
    }
    virtual void voidFunctionB4(bool a1, int a2, int a3, int a4)
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        *sg_memberString = "MemberBase::voidFunctionB4";
    }
    virtual void voidFunctionB5(bool a1, int a2, int a3, int a4, int a5)
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        *sg_memberString = "MemberBase::voidFunctionB5";
    }
    virtual void voidFunctionB6(bool a1, int a2, int a3, int a4, int a5, int a6)
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        *sg_memberString = "MemberBase::voidFunctionB6";
    }
    virtual void voidFunctionB7(bool a1, int a2, int a3, int a4, int a5, int a6, int a7)
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        Q_UNUSED(a7)
        *sg_memberString = "MemberBase::voidFunctionB7";
    }

    virtual int intFunction0()
    {
        *sg_memberString = "MemberBase::intFunction0";
        return 0;
    }
    virtual int intFunction1(int a1)
    {
        return a1;
    }
    virtual int intFunction2(int a1, int a2)
    {
        return a1 + a2;
    }
    virtual int intFunction3(int a1, int a2, int a3)
    {
        return a1 + a2 + a3;
    }
    virtual int intFunction4(int a1, int a2, int a3, int a4)
    {
        return a1 + a2 + a3 + a4;
    }
    virtual int intFunction5(int a1, int a2, int a3, int a4, int a5)
    {
        return a1 + a2 + a3 + a4 + a5;
    }
    virtual int intFunction6(int a1, int a2, int a3, int a4, int a5, int a6)
    {
        return a1 + a2 + a3 + a4 + a5 + a6;
    }
    virtual int intFunction7(int a1, int a2, int a3, int a4, int a5, int a6, int a7)
    {
        return a1 + a2 + a3 + a4 + a5 + a6 + a7;
    }
    virtual int intFunctionB1(bool a1)
    {
        return a1;
    }
    virtual int intFunctionB2(bool a1, int a2)
    {
        return a1 ? a2 : 0;
    }
    virtual int intFunctionB3(bool a1, int a2, int a3)
    {
        return a1 ? (a2 + a3) : (a2 * a3);
    }
    virtual int intFunctionB4(bool a1, int a2, int a3, int a4)
    {
        return a1 ? (a2 + a3 + a4) : (a2 * a3 * a4);
    }
    virtual int intFunctionB5(bool a1, int a2, int a3, int a4, int a5)
    {
        return a1 ? (a2 + a3 + a4 + a5) : (a2 * a3 * a4 * a5);
    }
    virtual int intFunctionB6(bool a1, int a2, int a3, int a4, int a5, int a6)
    {
        return a1 ? (a2 + a3 + a4 + a5 + a6) : (a2 * a3 * a4 * a5 * a6);
    }
    virtual int intFunctionB7(bool a1, int a2, int a3, int a4, int a5, int a6, int a7)
    {
        return a1 ? (a2 + a3 + a4 + a5 + a6 + a7) : (a2 * a3 * a4 * a5 * a6 * a7);
    }

    virtual double doubleFunction0()
    {
        *sg_memberString = "MemberBase::doubleFunction0";
        return 0;
    }
    virtual double doubleFunction1(double a1)
    {
        return a1;
    }
    virtual double doubleFunction2(double a1, double a2)
    {
        return a1 + a2;
    }
    virtual double doubleFunction3(double a1, double a2, double a3)
    {
        return a1 + a2 + a3;
    }
    virtual double doubleFunction4(double a1, double a2, double a3, double a4)
    {
        return a1 + a2 + a3 + a4;
    }
    virtual double doubleFunction5(double a1, double a2, double a3, double a4, double a5)
    {
        return a1 + a2 + a3 + a4 + a5;
    }
    virtual double doubleFunction6(double a1, double a2, double a3, double a4, double a5, double a6)
    {
        return a1 + a2 + a3 + a4 + a5 + a6;
    }
    virtual double doubleFunction7(double a1, double a2, double a3, double a4, double a5, double a6, double a7)
    {
        return a1 + a2 + a3 + a4 + a5 + a6 + a7;
    }
    virtual double doubleFunctionB1(bool a1)
    {
        return a1;
    }
    virtual double doubleFunctionB2(bool a1, double a2)
    {
        return a1 ? a2 : 0;
    }
    virtual double doubleFunctionB3(bool a1, double a2, double a3)
    {
        return a1 ? (a2 + a3) : (a2 * a3);
    }
    virtual double doubleFunctionB4(bool a1, double a2, double a3, double a4)
    {
        return a1 ? (a2 + a3 + a4) : (a2 * a3 * a4);
    }
    virtual double doubleFunctionB5(bool a1, double a2, double a3, double a4, double a5)
    {
        return a1 ? (a2 + a3 + a4 + a5) : (a2 * a3 * a4 * a5);
    }
    virtual double doubleFunctionB6(bool a1, double a2, double a3, double a4, double a5, double a6)
    {
        return a1 ? (a2 + a3 + a4 + a5 + a6) : (a2 * a3 * a4 * a5 * a6);
    }
    virtual double doubleFunctionB7(bool a1, double a2, double a3, double a4, double a5, double a6, double a7)
    {
        return a1 ? (a2 + a3 + a4 + a5 + a6 + a7) : (a2 * a3 * a4 * a5 * a6 * a7);
    }


    // const function
    virtual void voidConstFunction0() const
    {
        *sg_memberString = "MemberBase::voidConstFunction0";
    }
    virtual void voidConstFunction1(int a1) const
    {
        Q_UNUSED(a1)
        *sg_memberString = "MemberBase::voidConstFunction1";
    }
    virtual void voidConstFunction2(int a1, int a2) const
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        *sg_memberString = "MemberBase::voidConstFunction2";
    }
    virtual void voidConstFunction3(int a1, int a2, int a3) const
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        *sg_memberString = "MemberBase::voidConstFunction3";
    }
    virtual void voidConstFunction4(int a1, int a2, int a3, int a4) const
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        *sg_memberString = "MemberBase::voidConstFunction4";
    }
    virtual void voidConstFunction5(int a1, int a2, int a3, int a4, int a5) const
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        *sg_memberString = "MemberBase::voidConstFunction5";
    }
    virtual void voidConstFunction6(int a1, int a2, int a3, int a4, int a5, int a6) const
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        *sg_memberString = "MemberBase::voidConstFunction6";
    }
    virtual void voidConstFunction7(int a1, int a2, int a3, int a4, int a5, int a6, int a7) const
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        Q_UNUSED(a7)
        *sg_memberString = "MemberBase::voidConstFunction7";
    }
    virtual void voidConstFunctionB1(bool a1) const
    {
        Q_UNUSED(a1)
        *sg_memberString = "MemberBase::voidConstFunctionB1";
    }
    virtual void voidConstFunctionB2(bool a1, int a2) const
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        *sg_memberString = "MemberBase::voidConstFunctionB2";
    }
    virtual void voidConstFunctionB3(bool a1, int a2, int a3) const
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        *sg_memberString = "MemberBase::voidConstFunctionB3";
    }
    virtual void voidConstFunctionB4(bool a1, int a2, int a3, int a4) const
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        *sg_memberString = "MemberBase::voidConstFunctionB4";
    }
    virtual void voidConstFunctionB5(bool a1, int a2, int a3, int a4, int a5) const
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        *sg_memberString = "MemberBase::voidConstFunctionB5";
    }
    virtual void voidConstFunctionB6(bool a1, int a2, int a3, int a4, int a5, int a6) const
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        *sg_memberString = "MemberBase::voidConstFunctionB6";
    }
    virtual void voidConstFunctionB7(bool a1, int a2, int a3, int a4, int a5, int a6, int a7) const
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        Q_UNUSED(a7)
        *sg_memberString = "MemberBase::voidConstFunctionB7";
    }

    virtual int intConstFunction0() const
    {
        *sg_memberString = "MemberBase::intConstFunction0";
        return 0;
    }
    virtual int intConstFunction1(int a1) const
    {
        return a1;
    }
    virtual int intConstFunction2(int a1, int a2) const
    {
        return a1 + a2;
    }
    virtual int intConstFunction3(int a1, int a2, int a3) const
    {
        return a1 + a2 + a3;
    }
    virtual int intConstFunction4(int a1, int a2, int a3, int a4) const
    {
        return a1 + a2 + a3 + a4;
    }
    virtual int intConstFunction5(int a1, int a2, int a3, int a4, int a5) const
    {
        return a1 + a2 + a3 + a4 + a5;
    }
    virtual int intConstFunction6(int a1, int a2, int a3, int a4, int a5, int a6) const
    {
        return a1 + a2 + a3 + a4 + a5 + a6;
    }
    virtual int intConstFunction7(int a1, int a2, int a3, int a4, int a5, int a6, int a7) const
    {
        return a1 + a2 + a3 + a4 + a5 + a6 + a7;
    }
    virtual int intConstFunctionB1(bool a1) const
    {
        return a1;
    }
    virtual int intConstFunctionB2(bool a1, int a2) const
    {
        return a1 ? a2 : 0;
    }
    virtual int intConstFunctionB3(bool a1, int a2, int a3) const
    {
        return a1 ? (a2 + a3) : (a2 * a3);
    }
    virtual int intConstFunctionB4(bool a1, int a2, int a3, int a4) const
    {
        return a1 ? (a2 + a3 + a4) : (a2 * a3 * a4);
    }
    virtual int intConstFunctionB5(bool a1, int a2, int a3, int a4, int a5) const
    {
        return a1 ? (a2 + a3 + a4 + a5) : (a2 * a3 * a4 * a5);
    }
    virtual int intConstFunctionB6(bool a1, int a2, int a3, int a4, int a5, int a6) const
    {
        return a1 ? (a2 + a3 + a4 + a5 + a6) : (a2 * a3 * a4 * a5 * a6);
    }
    virtual int intConstFunctionB7(bool a1, int a2, int a3, int a4, int a5, int a6, int a7) const
    {
        return a1 ? (a2 + a3 + a4 + a5 + a6 + a7) : (a2 * a3 * a4 * a5 * a6 * a7);
    }

    virtual double doubleConstFunction0() const
    {
        *sg_memberString = "MemberBase::doubleConstFunction0";
        return 0;
    }
    virtual double doubleConstFunction1(double a1) const
    {
        return a1;
    }
    virtual double doubleConstFunction2(double a1, double a2) const
    {
        return a1 + a2;
    }
    virtual double doubleConstFunction3(double a1, double a2, double a3) const
    {
        return a1 + a2 + a3;
    }
    virtual double doubleConstFunction4(double a1, double a2, double a3, double a4) const
    {
        return a1 + a2 + a3 + a4;
    }
    virtual double doubleConstFunction5(double a1, double a2, double a3, double a4, double a5) const
    {
        return a1 + a2 + a3 + a4 + a5;
    }
    virtual double doubleConstFunction6(double a1, double a2, double a3, double a4, double a5, double a6) const
    {
        return a1 + a2 + a3 + a4 + a5 + a6;
    }
    virtual double doubleConstFunction7(double a1, double a2, double a3, double a4, double a5, double a6, double a7) const
    {
        return a1 + a2 + a3 + a4 + a5 + a6 + a7;
    }
    virtual double doubleConstFunctionB1(bool a1) const
    {
        return a1 ? 1 : 0;
    }
    virtual double doubleConstFunctionB2(bool a1, double a2) const
    {
        return a1 ? a2 : 0;
    }
    virtual double doubleConstFunctionB3(bool a1, double a2, double a3) const
    {
        return a1 ? (a2 + a3) : (a2 * a3);
    }
    virtual double doubleConstFunctionB4(bool a1, double a2, double a3, double a4) const
    {
        return a1 ? (a2 + a3 + a4) : (a2 * a3 * a4);
    }
    virtual double doubleConstFunctionB5(bool a1, double a2, double a3, double a4, double a5) const
    {
        return a1 ? (a2 + a3 + a4 + a5) : (a2 * a3 * a4 * a5);
    }
    virtual double doubleConstFunctionB6(bool a1, double a2, double a3, double a4, double a5, double a6) const
    {
        return a1 ? (a2 + a3 + a4 + a5 + a6) : (a2 * a3 * a4 * a5 * a6);
    }
    virtual double doubleConstFunctionB7(bool a1, double a2, double a3, double a4, double a5, double a6, double a7) const
    {
        return a1 ? (a2 + a3 + a4 + a5 + a6 + a7) : (a2 * a3 * a4 * a5 * a6 * a7);
    }



    // volatile function
    virtual void voidVolatileFunction0() volatile
    {
        *sg_memberString = "MemberBase::voidVolatileFunction0";
    }
    virtual void voidVolatileFunction1(int a1) volatile
    {
        Q_UNUSED(a1)
        *sg_memberString = "MemberBase::voidVolatileFunction1";
    }
    virtual void voidVolatileFunction2(int a1, int a2) volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        *sg_memberString = "MemberBase::voidVolatileFunction2";
    }
    virtual void voidVolatileFunction3(int a1, int a2, int a3) volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        *sg_memberString = "MemberBase::voidVolatileFunction3";
    }
    virtual void voidVolatileFunction4(int a1, int a2, int a3, int a4) volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        *sg_memberString = "MemberBase::voidVolatileFunction4";
    }
    virtual void voidVolatileFunction5(int a1, int a2, int a3, int a4, int a5) volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        *sg_memberString = "MemberBase::voidVolatileFunction5";
    }
    virtual void voidVolatileFunction6(int a1, int a2, int a3, int a4, int a5, int a6) volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        *sg_memberString = "MemberBase::voidVolatileFunction6";
    }
    virtual void voidVolatileFunction7(int a1, int a2, int a3, int a4, int a5, int a6, int a7) volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        Q_UNUSED(a7)
        *sg_memberString = "MemberBase::voidVolatileFunction7";
    }
    virtual void voidVolatileFunctionB1(bool a1) volatile
    {
        Q_UNUSED(a1)
        *sg_memberString = "MemberBase::voidVolatileFunctionB1";
    }
    virtual void voidVolatileFunctionB2(bool a1, int a2) volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        *sg_memberString = "MemberBase::voidVolatileFunctionB2";
    }
    virtual void voidVolatileFunctionB3(bool a1, int a2, int a3) volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        *sg_memberString = "MemberBase::voidVolatileFunctionB3";
    }
    virtual void voidVolatileFunctionB4(bool a1, int a2, int a3, int a4) volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        *sg_memberString = "MemberBase::voidVolatileFunctionB4";
    }
    virtual void voidVolatileFunctionB5(bool a1, int a2, int a3, int a4, int a5) volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        *sg_memberString = "MemberBase::voidVolatileFunctionB5";
    }
    virtual void voidVolatileFunctionB6(bool a1, int a2, int a3, int a4, int a5, int a6) volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        *sg_memberString = "MemberBase::voidVolatileFunctionB6";
    }
    virtual void voidVolatileFunctionB7(bool a1, int a2, int a3, int a4, int a5, int a6, int a7) volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        Q_UNUSED(a7)
        *sg_memberString = "MemberBase::voidVolatileFunctionB7";
    }

    virtual int intVolatileFunction0() volatile
    {
        *sg_memberString = "MemberBase::intVolatileFunction0";
        return 0;
    }
    virtual int intVolatileFunction1(int a1) volatile
    {
        return a1;
    }
    virtual int intVolatileFunction2(int a1, int a2) volatile
    {
        return a1 + a2;
    }
    virtual int intVolatileFunction3(int a1, int a2, int a3) volatile
    {
        return a1 + a2 + a3;
    }
    virtual int intVolatileFunction4(int a1, int a2, int a3, int a4) volatile
    {
        return a1 + a2 + a3 + a4;
    }
    virtual int intVolatileFunction5(int a1, int a2, int a3, int a4, int a5) volatile
    {
        return a1 + a2 + a3 + a4 + a5;
    }
    virtual int intVolatileFunction6(int a1, int a2, int a3, int a4, int a5, int a6) volatile
    {
        return a1 + a2 + a3 + a4 + a5 + a6;
    }
    virtual int intVolatileFunction7(int a1, int a2, int a3, int a4, int a5, int a6, int a7) volatile
    {
        return a1 + a2 + a3 + a4 + a5 + a6 + a7;
    }
    virtual int intVolatileFunctionB1(bool a1) volatile
    {
        return a1;
    }
    virtual int intVolatileFunctionB2(bool a1, int a2) volatile
    {
        return a1 ? a2 : 0;
    }
    virtual int intVolatileFunctionB3(bool a1, int a2, int a3) volatile
    {
        return a1 ? (a2 + a3) : (a2 * a3);
    }
    virtual int intVolatileFunctionB4(bool a1, int a2, int a3, int a4) volatile
    {
        return a1 ? (a2 + a3 + a4) : (a2 * a3 * a4);
    }
    virtual int intVolatileFunctionB5(bool a1, int a2, int a3, int a4, int a5) volatile
    {
        return a1 ? (a2 + a3 + a4 + a5) : (a2 * a3 * a4 * a5);
    }
    virtual int intVolatileFunctionB6(bool a1, int a2, int a3, int a4, int a5, int a6) volatile
    {
        return a1 ? (a2 + a3 + a4 + a5 + a6) : (a2 * a3 * a4 * a5 * a6);
    }
    virtual int intVolatileFunctionB7(bool a1, int a2, int a3, int a4, int a5, int a6, int a7) volatile
    {
        return a1 ? (a2 + a3 + a4 + a5 + a6 + a7) : (a2 * a3 * a4 * a5 * a6 * a7);
    }

    virtual double doubleVolatileFunction0() volatile
    {
        *sg_memberString = "MemberBase::doubleVolatileFunction0";
        return 0;
    }
    virtual double doubleVolatileFunction1(double a1) volatile
    {
        return a1;
    }
    virtual double doubleVolatileFunction2(double a1, double a2) volatile
    {
        return a1 + a2;
    }
    virtual double doubleVolatileFunction3(double a1, double a2, double a3) volatile
    {
        return a1 + a2 + a3;
    }
    virtual double doubleVolatileFunction4(double a1, double a2, double a3, double a4) volatile
    {
        return a1 + a2 + a3 + a4;
    }
    virtual double doubleVolatileFunction5(double a1, double a2, double a3, double a4, double a5) volatile
    {
        return a1 + a2 + a3 + a4 + a5;
    }
    virtual double doubleVolatileFunction6(double a1, double a2, double a3, double a4, double a5, double a6) volatile
    {
        return a1 + a2 + a3 + a4 + a5 + a6;
    }
    virtual double doubleVolatileFunction7(double a1, double a2, double a3, double a4, double a5, double a6, double a7) volatile
    {
        return a1 + a2 + a3 + a4 + a5 + a6 + a7;
    }
    virtual double doubleVolatileFunctionB1(bool a1) volatile
    {
        return a1 ? 1 : 0;
    }
    virtual double doubleVolatileFunctionB2(bool a1, double a2) volatile
    {
        return a1 ? a2 : 0;
    }
    virtual double doubleVolatileFunctionB3(bool a1, double a2, double a3) volatile
    {
        return a1 ? (a2 + a3) : (a2 * a3);
    }
    virtual double doubleVolatileFunctionB4(bool a1, double a2, double a3, double a4) volatile
    {
        return a1 ? (a2 + a3 + a4) : (a2 * a3 * a4);
    }
    virtual double doubleVolatileFunctionB5(bool a1, double a2, double a3, double a4, double a5) volatile
    {
        return a1 ? (a2 + a3 + a4 + a5) : (a2 * a3 * a4 * a5);
    }
    virtual double doubleVolatileFunctionB6(bool a1, double a2, double a3, double a4, double a5, double a6) volatile
    {
        return a1 ? (a2 + a3 + a4 + a5 + a6) : (a2 * a3 * a4 * a5 * a6);
    }
    virtual double doubleVolatileFunctionB7(bool a1, double a2, double a3, double a4, double a5, double a6, double a7) volatile
    {
        return a1 ? (a2 + a3 + a4 + a5 + a6 + a7) : (a2 * a3 * a4 * a5 * a6 * a7);
    }


    // const volatile
    virtual void voidConstVolatileFunction0() const volatile
    {
        *sg_memberString = "MemberBase::voidConstVolatileFunction0";
    }
    virtual void voidConstVolatileFunction1(int a1) const volatile
    {
        Q_UNUSED(a1)
        *sg_memberString = "MemberBase::voidConstVolatileFunction1";
    }
    virtual void voidConstVolatileFunction2(int a1, int a2) const volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        *sg_memberString = "MemberBase::voidConstVolatileFunction2";
    }
    virtual void voidConstVolatileFunction3(int a1, int a2, int a3) const volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        *sg_memberString = "MemberBase::voidConstVolatileFunction3";
    }
    virtual void voidConstVolatileFunction4(int a1, int a2, int a3, int a4) const volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        *sg_memberString = "MemberBase::voidConstVolatileFunction4";
    }
    virtual void voidConstVolatileFunction5(int a1, int a2, int a3, int a4, int a5) const volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        *sg_memberString = "MemberBase::voidConstVolatileFunction5";
    }
    virtual void voidConstVolatileFunction6(int a1, int a2, int a3, int a4, int a5, int a6) const volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        *sg_memberString = "MemberBase::voidConstVolatileFunction6";
    }
    virtual void voidConstVolatileFunction7(int a1, int a2, int a3, int a4, int a5, int a6, int a7) const volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        Q_UNUSED(a7)
        *sg_memberString = "MemberBase::voidConstVolatileFunction7";
    }
    virtual void voidConstVolatileFunctionB1(bool a1) const volatile
    {
        Q_UNUSED(a1)
        *sg_memberString = "MemberBase::voidConstVolatileFunctionB1";
    }
    virtual void voidConstVolatileFunctionB2(bool a1, int a2) const volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        *sg_memberString = "MemberBase::voidConstVolatileFunctionB2";
    }
    virtual void voidConstVolatileFunctionB3(bool a1, int a2, int a3) const volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        *sg_memberString = "MemberBase::voidConstVolatileFunctionB3";
    }
    virtual void voidConstVolatileFunctionB4(bool a1, int a2, int a3, int a4) const volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        *sg_memberString = "MemberBase::voidConstVolatileFunctionB4";
    }
    virtual void voidConstVolatileFunctionB5(bool a1, int a2, int a3, int a4, int a5) const volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        *sg_memberString = "MemberBase::voidConstVolatileFunctionB5";
    }
    virtual void voidConstVolatileFunctionB6(bool a1, int a2, int a3, int a4, int a5, int a6) const volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        *sg_memberString = "MemberBase::voidConstVolatileFunctionB6";
    }
    virtual void voidConstVolatileFunctionB7(bool a1, int a2, int a3, int a4, int a5, int a6, int a7) const volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        Q_UNUSED(a7)
        *sg_memberString = "MemberBase::voidConstVolatileFunctionB7";
    }

    virtual int intConstVolatileFunction0() const volatile
    {
        *sg_memberString = "MemberBase::intConstVolatileFunction0";
        return 0;
    }
    virtual int intConstVolatileFunction1(int a1) const volatile
    {
        return a1;
    }
    virtual int intConstVolatileFunction2(int a1, int a2) const volatile
    {
        return a1 + a2;
    }
    virtual int intConstVolatileFunction3(int a1, int a2, int a3) const volatile
    {
        return a1 + a2 + a3;
    }
    virtual int intConstVolatileFunction4(int a1, int a2, int a3, int a4) const volatile
    {
        return a1 + a2 + a3 + a4;
    }
    virtual int intConstVolatileFunction5(int a1, int a2, int a3, int a4, int a5) const volatile
    {
        return a1 + a2 + a3 + a4 + a5;
    }
    virtual int intConstVolatileFunction6(int a1, int a2, int a3, int a4, int a5, int a6) const volatile
    {
        return a1 + a2 + a3 + a4 + a5 + a6;
    }
    virtual int intConstVolatileFunction7(int a1, int a2, int a3, int a4, int a5, int a6, int a7) const volatile
    {
        return a1 + a2 + a3 + a4 + a5 + a6 + a7;
    }
    virtual int intConstVolatileFunctionB1(bool a1) const volatile
    {
        return a1;
    }
    virtual int intConstVolatileFunctionB2(bool a1, int a2) const volatile
    {
        return a1 ? a2 : 0;
    }
    virtual int intConstVolatileFunctionB3(bool a1, int a2, int a3) const volatile
    {
        return a1 ? (a2 + a3) : (a2 * a3);
    }
    virtual int intConstVolatileFunctionB4(bool a1, int a2, int a3, int a4) const volatile
    {
        return a1 ? (a2 + a3 + a4) : (a2 * a3 * a4);
    }
    virtual int intConstVolatileFunctionB5(bool a1, int a2, int a3, int a4, int a5) const volatile
    {
        return a1 ? (a2 + a3 + a4 + a5) : (a2 * a3 * a4 * a5);
    }
    virtual int intConstVolatileFunctionB6(bool a1, int a2, int a3, int a4, int a5, int a6) const volatile
    {
        return a1 ? (a2 + a3 + a4 + a5 + a6) : (a2 * a3 * a4 * a5 * a6);
    }
    virtual int intConstVolatileFunctionB7(bool a1, int a2, int a3, int a4, int a5, int a6, int a7) const volatile
    {
        return a1 ? (a2 + a3 + a4 + a5 + a6 + a7) : (a2 * a3 * a4 * a5 * a6 * a7);
    }

    virtual double doubleConstVolatileFunction0() const volatile
    {
        *sg_memberString = "MemberBase::doubleConstVolatileFunction0";
        return 0;
    }
    virtual double doubleConstVolatileFunction1(double a1) const volatile
    {
        return a1;
    }
    virtual double doubleConstVolatileFunction2(double a1, double a2) const volatile
    {
        return a1 + a2;
    }
    virtual double doubleConstVolatileFunction3(double a1, double a2, double a3) const volatile
    {
        return a1 + a2 + a3;
    }
    virtual double doubleConstVolatileFunction4(double a1, double a2, double a3, double a4) const volatile
    {
        return a1 + a2 + a3 + a4;
    }
    virtual double doubleConstVolatileFunction5(double a1, double a2, double a3, double a4, double a5) const volatile
    {
        return a1 + a2 + a3 + a4 + a5;
    }
    virtual double doubleConstVolatileFunction6(double a1, double a2, double a3, double a4, double a5, double a6) const volatile
    {
        return a1 + a2 + a3 + a4 + a5 + a6;
    }
    virtual double doubleConstVolatileFunction7(double a1, double a2, double a3, double a4, double a5, double a6, double a7) const volatile
    {
        return a1 + a2 + a3 + a4 + a5 + a6 + a7;
    }
    virtual double doubleConstVolatileFunctionB1(bool a1) const volatile
    {
        return a1 ? 1 : 0;
    }
    virtual double doubleConstVolatileFunctionB2(bool a1, double a2) const volatile
    {
        return a1 ? a2 : 0;
    }
    virtual double doubleConstVolatileFunctionB3(bool a1, double a2, double a3) const volatile
    {
        return a1 ? (a2 + a3) : (a2 * a3);
    }
    virtual double doubleConstVolatileFunctionB4(bool a1, double a2, double a3, double a4) const volatile
    {
        return a1 ? (a2 + a3 + a4) : (a2 * a3 * a4);
    }
    virtual double doubleConstVolatileFunctionB5(bool a1, double a2, double a3, double a4, double a5) const volatile
    {
        return a1 ? (a2 + a3 + a4 + a5) : (a2 * a3 * a4 * a5);
    }
    virtual double doubleConstVolatileFunctionB6(bool a1, double a2, double a3, double a4, double a5, double a6) const volatile
    {
        return a1 ? (a2 + a3 + a4 + a5 + a6) : (a2 * a3 * a4 * a5 * a6);
    }
    virtual double doubleConstVolatileFunctionB7(bool a1, double a2, double a3, double a4, double a5, double a6, double a7) const volatile
    {
        return a1 ? (a2 + a3 + a4 + a5 + a6 + a7) : (a2 * a3 * a4 * a5 * a6 * a7);
    }
};


class Member : public MemberBase
{
public:
    Member() {}


    void voidFunction0()
    {
        *sg_memberString = "Member::voidFunction0";
    }
    void voidFunction1(int a1)
    {
        Q_UNUSED(a1)
        *sg_memberString = "Member::voidFunction1";
    }
    void voidFunction2(int a1, int a2)
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        *sg_memberString = "Member::voidFunction2";
    }
    void voidFunction3(int a1, int a2, int a3)
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        *sg_memberString = "Member::voidFunction3";
    }
    void voidFunction4(int a1, int a2, int a3, int a4)
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        *sg_memberString = "Member::voidFunction4";
    }
    void voidFunction5(int a1, int a2, int a3, int a4, int a5)
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        *sg_memberString = "Member::voidFunction5";
    }
    void voidFunction6(int a1, int a2, int a3, int a4, int a5, int a6)
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        *sg_memberString = "Member::voidFunction6";
    }
    void voidFunction7(int a1, int a2, int a3, int a4, int a5, int a6, int a7)
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        Q_UNUSED(a7)
        *sg_memberString = "Member::voidFunction7";
    }
    void voidFunctionB1(bool a1)
    {
        Q_UNUSED(a1)
        *sg_memberString = "Member::voidFunctionB1";
    }
    void voidFunctionB2(bool a1, int a2)
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        *sg_memberString = "Member::voidFunctionB2";
    }
    void voidFunctionB3(bool a1, int a2, int a3)
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        *sg_memberString = "Member::voidFunctionB3";
    }
    void voidFunctionB4(bool a1, int a2, int a3, int a4)
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        *sg_memberString = "Member::voidFunctionB4";
    }
    void voidFunctionB5(bool a1, int a2, int a3, int a4, int a5)
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        *sg_memberString = "Member::voidFunctionB5";
    }
    void voidFunctionB6(bool a1, int a2, int a3, int a4, int a5, int a6)
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        *sg_memberString = "Member::voidFunctionB6";
    }
    void voidFunctionB7(bool a1, int a2, int a3, int a4, int a5, int a6, int a7)
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        Q_UNUSED(a7)
        *sg_memberString = "Member::voidFunctionB7";
    }

    int intFunction0()
    {
        *sg_memberString = "Member::intFunction0";
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
        *sg_memberString = "Member::doubleFunction0";
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
        *sg_memberString = "Member::voidConstFunction0";
    }
    void voidConstFunction1(int a1) const
    {
        Q_UNUSED(a1)
        *sg_memberString = "Member::voidConstFunction1";
    }
    void voidConstFunction2(int a1, int a2) const
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        *sg_memberString = "Member::voidConstFunction2";
    }
    void voidConstFunction3(int a1, int a2, int a3) const
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        *sg_memberString = "Member::voidConstFunction3";
    }
    void voidConstFunction4(int a1, int a2, int a3, int a4) const
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        *sg_memberString = "Member::voidConstFunction4";
    }
    void voidConstFunction5(int a1, int a2, int a3, int a4, int a5) const
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        *sg_memberString = "Member::voidConstFunction5";
    }
    void voidConstFunction6(int a1, int a2, int a3, int a4, int a5, int a6) const
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        *sg_memberString = "Member::voidConstFunction6";
    }
    void voidConstFunction7(int a1, int a2, int a3, int a4, int a5, int a6, int a7) const
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        Q_UNUSED(a7)
        *sg_memberString = "Member::voidConstFunction7";
    }
    void voidConstFunctionB1(bool a1) const
    {
        Q_UNUSED(a1)
        *sg_memberString = "Member::voidConstFunctionB1";
    }
    void voidConstFunctionB2(bool a1, int a2) const
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        *sg_memberString = "Member::voidConstFunctionB2";
    }
    void voidConstFunctionB3(bool a1, int a2, int a3) const
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        *sg_memberString = "Member::voidConstFunctionB3";
    }
    void voidConstFunctionB4(bool a1, int a2, int a3, int a4) const
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        *sg_memberString = "Member::voidConstFunctionB4";
    }
    void voidConstFunctionB5(bool a1, int a2, int a3, int a4, int a5) const
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        *sg_memberString = "Member::voidConstFunctionB5";
    }
    void voidConstFunctionB6(bool a1, int a2, int a3, int a4, int a5, int a6) const
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        *sg_memberString = "Member::voidConstFunctionB6";
    }
    void voidConstFunctionB7(bool a1, int a2, int a3, int a4, int a5, int a6, int a7) const
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        Q_UNUSED(a7)
        *sg_memberString = "Member::voidConstFunctionB7";
    }

    int intConstFunction0() const
    {
        *sg_memberString = "Member::intConstFunction0";
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
        *sg_memberString = "Member::doubleConstFunction0";
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
        *sg_memberString = "Member::voidVolatileFunction0";
    }
    void voidVolatileFunction1(int a1) volatile
    {
        Q_UNUSED(a1)
        *sg_memberString = "Member::voidVolatileFunction1";
    }
    void voidVolatileFunction2(int a1, int a2) volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        *sg_memberString = "Member::voidVolatileFunction2";
    }
    void voidVolatileFunction3(int a1, int a2, int a3) volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        *sg_memberString = "Member::voidVolatileFunction3";
    }
    void voidVolatileFunction4(int a1, int a2, int a3, int a4) volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        *sg_memberString = "Member::voidVolatileFunction4";
    }
    void voidVolatileFunction5(int a1, int a2, int a3, int a4, int a5) volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        *sg_memberString = "Member::voidVolatileFunction5";
    }
    void voidVolatileFunction6(int a1, int a2, int a3, int a4, int a5, int a6) volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        *sg_memberString = "Member::voidVolatileFunction6";
    }
    void voidVolatileFunction7(int a1, int a2, int a3, int a4, int a5, int a6, int a7) volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        Q_UNUSED(a7)
        *sg_memberString = "Member::voidVolatileFunction7";
    }
    void voidVolatileFunctionB1(bool a1) volatile
    {
        Q_UNUSED(a1)
        *sg_memberString = "Member::voidVolatileFunctionB1";
    }
    void voidVolatileFunctionB2(bool a1, int a2) volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        *sg_memberString = "Member::voidVolatileFunctionB2";
    }
    void voidVolatileFunctionB3(bool a1, int a2, int a3) volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        *sg_memberString = "Member::voidVolatileFunctionB3";
    }
    void voidVolatileFunctionB4(bool a1, int a2, int a3, int a4) volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        *sg_memberString = "Member::voidVolatileFunctionB4";
    }
    void voidVolatileFunctionB5(bool a1, int a2, int a3, int a4, int a5) volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        *sg_memberString = "Member::voidVolatileFunctionB5";
    }
    void voidVolatileFunctionB6(bool a1, int a2, int a3, int a4, int a5, int a6) volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        *sg_memberString = "Member::voidVolatileFunctionB6";
    }
    void voidVolatileFunctionB7(bool a1, int a2, int a3, int a4, int a5, int a6, int a7) volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        Q_UNUSED(a7)
        *sg_memberString = "Member::voidVolatileFunctionB7";
    }

    int intVolatileFunction0() volatile
    {
        *sg_memberString = "Member::intVolatileFunction0";
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
        *sg_memberString = "Member::doubleVolatileFunction0";
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
        *sg_memberString = "Member::voidConstVolatileFunction0";
    }
    void voidConstVolatileFunction1(int a1) const volatile
    {
        Q_UNUSED(a1)
        *sg_memberString = "Member::voidConstVolatileFunction1";
    }
    void voidConstVolatileFunction2(int a1, int a2) const volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        *sg_memberString = "Member::voidConstVolatileFunction2";
    }
    void voidConstVolatileFunction3(int a1, int a2, int a3) const volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        *sg_memberString = "Member::voidConstVolatileFunction3";
    }
    void voidConstVolatileFunction4(int a1, int a2, int a3, int a4) const volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        *sg_memberString = "Member::voidConstVolatileFunction4";
    }
    void voidConstVolatileFunction5(int a1, int a2, int a3, int a4, int a5) const volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        *sg_memberString = "Member::voidConstVolatileFunction5";
    }
    void voidConstVolatileFunction6(int a1, int a2, int a3, int a4, int a5, int a6) const volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        *sg_memberString = "Member::voidConstVolatileFunction6";
    }
    void voidConstVolatileFunction7(int a1, int a2, int a3, int a4, int a5, int a6, int a7) const volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        Q_UNUSED(a7)
        *sg_memberString = "Member::voidConstVolatileFunction7";
    }
    void voidConstVolatileFunctionB1(bool a1) const volatile
    {
        Q_UNUSED(a1)
        *sg_memberString = "Member::voidConstVolatileFunctionB1";
    }
    void voidConstVolatileFunctionB2(bool a1, int a2) const volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        *sg_memberString = "Member::voidConstVolatileFunctionB2";
    }
    void voidConstVolatileFunctionB3(bool a1, int a2, int a3) const volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        *sg_memberString = "Member::voidConstVolatileFunctionB3";
    }
    void voidConstVolatileFunctionB4(bool a1, int a2, int a3, int a4) const volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        *sg_memberString = "Member::voidConstVolatileFunctionB4";
    }
    void voidConstVolatileFunctionB5(bool a1, int a2, int a3, int a4, int a5) const volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        *sg_memberString = "Member::voidConstVolatileFunctionB5";
    }
    void voidConstVolatileFunctionB6(bool a1, int a2, int a3, int a4, int a5, int a6) const volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        *sg_memberString = "Member::voidConstVolatileFunctionB6";
    }
    void voidConstVolatileFunctionB7(bool a1, int a2, int a3, int a4, int a5, int a6, int a7) const volatile
    {
        Q_UNUSED(a1)
        Q_UNUSED(a2)
        Q_UNUSED(a3)
        Q_UNUSED(a4)
        Q_UNUSED(a5)
        Q_UNUSED(a6)
        Q_UNUSED(a7)
        *sg_memberString = "Member::voidConstVolatileFunctionB7";
    }

    int intConstVolatileFunction0() const volatile
    {
        *sg_memberString = "Member::intConstVolatileFunction0";
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
        *sg_memberString = "Member::doubleConstVolatileFunction0";
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

#endif // QEXTMEMBER_H
