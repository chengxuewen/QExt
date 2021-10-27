#ifndef QEXTFUNCTORTRAITTEST_H
#define QEXTFUNCTORTRAITTEST_H

#include <qextFunctorTrait.h>
#include <qextPointerFunctor.h>
#include <qextMemberFunctor.h>

#include <iostream>

#include <CppUTest/TestHarness.h>

QEXT_USE_NAMESPACE

namespace qextFunctorTraitTest
{

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
            QEXT_UNUSED(a1)
            return 0;
        }
        int intFunction2(int a1, int a2)
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            return 0;
        }
        int intFunction3(int a1, int a2, int a3)
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            return 0;
        }
        int intFunction4(int a1, int a2, int a3, int a4)
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            return 0;
        }
        int intFunction5(int a1, int a2, int a3, int a4, int a5)
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            return 0;
        }
        int intFunction6(int a1, int a2, int a3, int a4, int a5, int a6)
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            QEXT_UNUSED(a6)
            return 0;
        }
        int intFunction7(int a1, int a2, int a3, int a4, int a5, int a6, int a7)
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            QEXT_UNUSED(a6)
            QEXT_UNUSED(a7)
            return 0;
        }
        int intFunctionB1(bool a1)
        {
            return a1 ? 1 : 0;
        }
        int intFunctionB2(bool a1, int a2)
        {
            QEXT_UNUSED(a2)
            return a1 ? 1 : 0;
        }
        int intFunctionB3(bool a1, int a2, int a3)
        {
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            return a1 ? 1 : 0;
        }
        int intFunctionB4(bool a1, int a2, int a3, int a4)
        {
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            return a1 ? 1 : 0;
        }
        int intFunctionB5(bool a1, int a2, int a3, int a4, int a5)
        {
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            return a1 ? 1 : 0;
        }
        int intFunctionB6(bool a1, int a2, int a3, int a4, int a5, int a6)
        {
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            QEXT_UNUSED(a6)
            return a1 ? 1 : 0;
        }
        int intFunctionB7(bool a1, int a2, int a3, int a4, int a5, int a6, int a7)
        {
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            QEXT_UNUSED(a6)
            QEXT_UNUSED(a7)
            return a1 ? 1 : 0;
        }

        double doubleFunction0()
        {
            return 0;
        }
        double doubleFunction1(double a1)
        {
            QEXT_UNUSED(a1)
            return 0;
        }
        double doubleFunction2(double a1, double a2)
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            return 0;
        }
        double doubleFunction3(double a1, double a2, double a3)
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            return 0;
        }
        double doubleFunction4(double a1, double a2, double a3, double a4)
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            return 0;
        }
        double doubleFunction5(double a1, double a2, double a3, double a4, double a5)
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            return 0;
        }
        double doubleFunction6(double a1, double a2, double a3, double a4, double a5, double a6)
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            QEXT_UNUSED(a6)
            return 0;
        }
        double doubleFunction7(double a1, double a2, double a3, double a4, double a5, double a6, double a7)
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            QEXT_UNUSED(a6)
            QEXT_UNUSED(a7)
            return 0;
        }
        double doubleFunctionB1(bool a1)
        {
            return a1 ? 1 : 0;
        }
        double doubleFunctionB2(bool a1, double a2)
        {
            QEXT_UNUSED(a2)
            return a1 ? 1 : 0;
        }
        double doubleFunctionB3(bool a1, double a2, double a3)
        {
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            return a1 ? 1 : 0;
        }
        double doubleFunctionB4(bool a1, double a2, double a3, double a4)
        {
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            return a1 ? 1 : 0;
        }
        double doubleFunctionB5(bool a1, double a2, double a3, double a4, double a5)
        {
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            return a1 ? 1 : 0;
        }
        double doubleFunctionB6(bool a1, double a2, double a3, double a4, double a5, double a6)
        {
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            QEXT_UNUSED(a6)
            return a1 ? 1 : 0;
        }
        double doubleFunctionB7(bool a1, double a2, double a3, double a4, double a5, double a6, double a7)
        {
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            QEXT_UNUSED(a6)
            QEXT_UNUSED(a7)
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
            QEXT_UNUSED(a1)
            return 0;
        }
        int intConstFunction2(int a1, int a2) const
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            return 0;
        }
        int intConstFunction3(int a1, int a2, int a3) const
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            return 0;
        }
        int intConstFunction4(int a1, int a2, int a3, int a4) const
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            return 0;
        }
        int intConstFunction5(int a1, int a2, int a3, int a4, int a5) const
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            return 0;
        }
        int intConstFunction6(int a1, int a2, int a3, int a4, int a5, int a6) const
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            QEXT_UNUSED(a6)
            return 0;
        }
        int intConstFunction7(int a1, int a2, int a3, int a4, int a5, int a6, int a7) const
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            QEXT_UNUSED(a6)
            QEXT_UNUSED(a7)
            return 0;
        }
        int intConstFunctionB1(bool a1) const
        {
            return a1 ? 1 : 0;
        }
        int intConstFunctionB2(bool a1, int a2) const
        {
            QEXT_UNUSED(a2)
            return a1 ? 1 : 0;
        }
        int intConstFunctionB3(bool a1, int a2, int a3) const
        {
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            return a1 ? 1 : 0;
        }
        int intConstFunctionB4(bool a1, int a2, int a3, int a4) const
        {
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            return a1 ? 1 : 0;
        }
        int intConstFunctionB5(bool a1, int a2, int a3, int a4, int a5) const
        {
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            return a1 ? 1 : 0;
        }
        int intConstFunctionB6(bool a1, int a2, int a3, int a4, int a5, int a6) const
        {
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            QEXT_UNUSED(a6)
            return a1 ? 1 : 0;
        }
        int intConstFunctionB7(bool a1, int a2, int a3, int a4, int a5, int a6, int a7) const
        {
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            QEXT_UNUSED(a6)
            QEXT_UNUSED(a7)
            return a1 ? 1 : 0;
        }

        double doubleConstFunction0() const
        {
            return 0;
        }
        double doubleConstFunction1(double a1) const
        {
            QEXT_UNUSED(a1)
            return 0;
        }
        double doubleConstFunction2(double a1, double a2) const
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            return 0;
        }
        double doubleConstFunction3(double a1, double a2, double a3) const
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            return 0;
        }
        double doubleConstFunction4(double a1, double a2, double a3, double a4) const
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            return 0;
        }
        double doubleConstFunction5(double a1, double a2, double a3, double a4, double a5) const
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            return 0;
        }
        double doubleConstFunction6(double a1, double a2, double a3, double a4, double a5, double a6) const
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            QEXT_UNUSED(a6)
            return 0;
        }
        double doubleConstFunction7(double a1, double a2, double a3, double a4, double a5, double a6, double a7) const
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            QEXT_UNUSED(a6)
            QEXT_UNUSED(a7)
            return 0;
        }
        double doubleConstFunctionB1(bool a1) const
        {
            return a1 ? 1 : 0;
        }
        double doubleConstFunctionB2(bool a1, double a2) const
        {
            QEXT_UNUSED(a2)
            return a1 ? 1 : 0;
        }
        double doubleConstFunctionB3(bool a1, double a2, double a3) const
        {
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            return a1 ? 1 : 0;
        }
        double doubleConstFunctionB4(bool a1, double a2, double a3, double a4) const
        {
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            return a1 ? 1 : 0;
        }
        double doubleConstFunctionB5(bool a1, double a2, double a3, double a4, double a5) const
        {
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            return a1 ? 1 : 0;
        }
        double doubleConstFunctionB6(bool a1, double a2, double a3, double a4, double a5, double a6) const
        {
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            QEXT_UNUSED(a6)
            return a1 ? 1 : 0;
        }
        double doubleConstFunctionB7(bool a1, double a2, double a3, double a4, double a5, double a6, double a7) const
        {
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            QEXT_UNUSED(a6)
            QEXT_UNUSED(a7)
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
            QEXT_UNUSED(a1)
            return 0;
        }
        int intVolatileFunction2(int a1, int a2) volatile
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            return 0;
        }
        int intVolatileFunction3(int a1, int a2, int a3) volatile
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            return 0;
        }
        int intVolatileFunction4(int a1, int a2, int a3, int a4) volatile
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            return 0;
        }
        int intVolatileFunction5(int a1, int a2, int a3, int a4, int a5) volatile
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            return 0;
        }
        int intVolatileFunction6(int a1, int a2, int a3, int a4, int a5, int a6) volatile
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            QEXT_UNUSED(a6)
            return 0;
        }
        int intVolatileFunction7(int a1, int a2, int a3, int a4, int a5, int a6, int a7) volatile
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            QEXT_UNUSED(a6)
            QEXT_UNUSED(a7)
            return 0;
        }
        int intVolatileFunctionB1(bool a1) volatile
        {
            return a1;
        }
        int intVolatileFunctionB2(bool a1, int a2) volatile
        {
            QEXT_UNUSED(a2)
            return a1 ? 1 : 0;
        }
        int intVolatileFunctionB3(bool a1, int a2, int a3) volatile
        {
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            return a1 ? 1 : 0;
        }
        int intVolatileFunctionB4(bool a1, int a2, int a3, int a4) volatile
        {
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            return a1 ? 1 : 0;
        }
        int intVolatileFunctionB5(bool a1, int a2, int a3, int a4, int a5) volatile
        {
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            return a1 ? 1 : 0;
        }
        int intVolatileFunctionB6(bool a1, int a2, int a3, int a4, int a5, int a6) volatile
        {
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            QEXT_UNUSED(a6)
            return a1 ? 1 : 0;
        }
        int intVolatileFunctionB7(bool a1, int a2, int a3, int a4, int a5, int a6, int a7) volatile
        {
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            QEXT_UNUSED(a6)
            QEXT_UNUSED(a7)
            return a1 ? 1 : 0;
        }

        double doubleVolatileFunction0() volatile
        {
            return 0;
        }
        double doubleVolatileFunction1(double a1) volatile
        {
            QEXT_UNUSED(a1)
            return 0;
        }
        double doubleVolatileFunction2(double a1, double a2) volatile
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            return 0;
        }
        double doubleVolatileFunction3(double a1, double a2, double a3) volatile
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            return 0;
        }
        double doubleVolatileFunction4(double a1, double a2, double a3, double a4) volatile
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            return 0;
        }
        double doubleVolatileFunction5(double a1, double a2, double a3, double a4, double a5) volatile
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            return 0;
        }
        double doubleVolatileFunction6(double a1, double a2, double a3, double a4, double a5, double a6) volatile
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            QEXT_UNUSED(a6)
            return 0;
        }
        double doubleVolatileFunction7(double a1, double a2, double a3, double a4, double a5, double a6, double a7) volatile
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            QEXT_UNUSED(a6)
            QEXT_UNUSED(a7)
            return 0;
        }
        double doubleVolatileFunctionB1(bool a1) volatile
        {
            return a1 ? 1 : 0;
        }
        double doubleVolatileFunctionB2(bool a1, double a2) volatile
        {
            QEXT_UNUSED(a2)
            return a1 ? 1 : 0;
        }
        double doubleVolatileFunctionB3(bool a1, double a2, double a3) volatile
        {
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            return a1 ? 1 : 0;
        }
        double doubleVolatileFunctionB4(bool a1, double a2, double a3, double a4) volatile
        {
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            return a1 ? 1 : 0;
        }
        double doubleVolatileFunctionB5(bool a1, double a2, double a3, double a4, double a5) volatile
        {
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            return a1 ? 1 : 0;
        }
        double doubleVolatileFunctionB6(bool a1, double a2, double a3, double a4, double a5, double a6) volatile
        {
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            QEXT_UNUSED(a6)
            return a1 ? 1 : 0;
        }
        double doubleVolatileFunctionB7(bool a1, double a2, double a3, double a4, double a5, double a6, double a7) volatile
        {
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            QEXT_UNUSED(a6)
            QEXT_UNUSED(a7)
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
            QEXT_UNUSED(a1)
            return 0;
        }
        int intConstVolatileFunction2(int a1, int a2) const volatile
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            return 0;
        }
        int intConstVolatileFunction3(int a1, int a2, int a3) const volatile
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            return 0;
        }
        int intConstVolatileFunction4(int a1, int a2, int a3, int a4) const volatile
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            return 0;
        }
        int intConstVolatileFunction5(int a1, int a2, int a3, int a4, int a5) const volatile
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            return 0;
        }
        int intConstVolatileFunction6(int a1, int a2, int a3, int a4, int a5, int a6) const volatile
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            QEXT_UNUSED(a6)
            return 0;
        }
        int intConstVolatileFunction7(int a1, int a2, int a3, int a4, int a5, int a6, int a7) const volatile
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            QEXT_UNUSED(a6)
            QEXT_UNUSED(a7)
            return 0;
        }
        int intConstVolatileFunctionB1(bool a1) const volatile
        {
            return a1;
        }
        int intConstVolatileFunctionB2(bool a1, int a2) const volatile
        {
            QEXT_UNUSED(a2)
            return a1 ? 1 : 0;
        }
        int intConstVolatileFunctionB3(bool a1, int a2, int a3) const volatile
        {
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            return a1 ? 1 : 0;
        }
        int intConstVolatileFunctionB4(bool a1, int a2, int a3, int a4) const volatile
        {
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            return a1 ? 1 : 0;
        }
        int intConstVolatileFunctionB5(bool a1, int a2, int a3, int a4, int a5) const volatile
        {
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            return a1 ? 1 : 0;
        }
        int intConstVolatileFunctionB6(bool a1, int a2, int a3, int a4, int a5, int a6) const volatile
        {
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            QEXT_UNUSED(a6)
            return a1 ? 1 : 0;
        }
        int intConstVolatileFunctionB7(bool a1, int a2, int a3, int a4, int a5, int a6, int a7) const volatile
        {
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            QEXT_UNUSED(a6)
            QEXT_UNUSED(a7)
            return a1 ? 1 : 0;
        }

        double doubleConstVolatileFunction0() const volatile
        {
            return 0;
        }
        double doubleConstVolatileFunction1(double a1) const volatile
        {
            QEXT_UNUSED(a1)
            return 0;
        }
        double doubleConstVolatileFunction2(double a1, double a2) const volatile
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            return 0;
        }
        double doubleConstVolatileFunction3(double a1, double a2, double a3) const volatile
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            return 0;
        }
        double doubleConstVolatileFunction4(double a1, double a2, double a3, double a4) const volatile
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            return 0;
        }
        double doubleConstVolatileFunction5(double a1, double a2, double a3, double a4, double a5) const volatile
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            return 0;
        }
        double doubleConstVolatileFunction6(double a1, double a2, double a3, double a4, double a5, double a6) const volatile
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            QEXT_UNUSED(a6)
            return 0;
        }
        double doubleConstVolatileFunction7(double a1, double a2, double a3, double a4, double a5, double a6, double a7) const volatile
        {
            QEXT_UNUSED(a1)
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            QEXT_UNUSED(a6)
            QEXT_UNUSED(a7)
            return 0;
        }
        double doubleConstVolatileFunctionB1(bool a1) const volatile
        {
            QEXT_UNUSED(a1)
            return a1 ? 1 : 0;
        }
        double doubleConstVolatileFunctionB2(bool a1, double a2) const volatile
        {
            QEXT_UNUSED(a2)
            return a1 ? 1 : 0;
        }
        double doubleConstVolatileFunctionB3(bool a1, double a2, double a3) const volatile
        {
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            return a1 ? 1 : 0;
        }
        double doubleConstVolatileFunctionB4(bool a1, double a2, double a3, double a4) const volatile
        {
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            return a1 ? 1 : 0;
        }
        double doubleConstVolatileFunctionB5(bool a1, double a2, double a3, double a4, double a5) const volatile
        {
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            return a1 ? 1 : 0;
        }
        double doubleConstVolatileFunctionB6(bool a1, double a2, double a3, double a4, double a5, double a6) const volatile
        {
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            QEXT_UNUSED(a6)
            return a1 ? 1 : 0;
        }
        double doubleConstVolatileFunctionB7(bool a1, double a2, double a3, double a4, double a5, double a6, double a7) const volatile
        {
            QEXT_UNUSED(a2)
            QEXT_UNUSED(a3)
            QEXT_UNUSED(a4)
            QEXT_UNUSED(a5)
            QEXT_UNUSED(a6)
            QEXT_UNUSED(a7)
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

    TEST_GROUP(qextFunctorTraitTest)
    {
    };

    TEST(qextFunctorTraitTest, testCustomDerivedType)
    {
        CHECK("UnknownFunctor" == QEXTFunctorTrait<MCustomBase>().typeName());

        CHECK("QEXTFunctorBase" == QEXTFunctorTrait<QEXTFunctorBase>().typeName());
        CHECK("QEXTFunctorBase" == QEXTFunctorTrait<MClassBase>().typeName());
        CHECK("QEXTFunctorBase" == QEXTFunctorTrait<MClass>().typeName());
    }

    TEST(qextFunctorTraitTest, testFunctorArg0Type)
    {
        typedef QEXTPointerFunctor<void>::Function FunctionType0;
        CHECK("QEXTPointerFunctor0" == QEXTFunctorTrait<FunctionType0>().typeName());
        typedef void (*T_voidfunctor0)();
        CHECK("QEXTPointerFunctor0" == QEXTFunctorTrait<T_voidfunctor0>().typeName());
        typedef int (*T_intfunctor0)();
        CHECK("QEXTPointerFunctor0" == QEXTFunctorTrait<T_intfunctor0>().typeName());
    }

    TEST(qextFunctorTraitTest, testFunctorArg1Type)
    {
        typedef QEXTPointerFunctor<void, int>::Function FunctionType1;
        CHECK("QEXTPointerFunctor1" == QEXTFunctorTrait<FunctionType1>().typeName());
        typedef void (*T_voidfunctor1)(int);
        CHECK("QEXTPointerFunctor1" == QEXTFunctorTrait<T_voidfunctor1>().typeName());
        typedef int (*T_intfunctor1)(double);
        CHECK("QEXTPointerFunctor1" == QEXTFunctorTrait<T_intfunctor1>().typeName());
    }

    TEST(qextFunctorTraitTest, testFunctorArg2Type)
    {
        typedef QEXTPointerFunctor<void, int, double>::Function FunctionType2;
        CHECK("QEXTPointerFunctor2" == QEXTFunctorTrait<FunctionType2>().typeName());
        typedef void (*T_voidfunctor2)(int, std::string);
        CHECK("QEXTPointerFunctor2" == QEXTFunctorTrait<T_voidfunctor2>().typeName());
        typedef int (*T_intfunctor2)(int, long);
        CHECK("QEXTPointerFunctor2" == QEXTFunctorTrait<T_intfunctor2>().typeName());
    }

    TEST(qextFunctorTraitTest, testFunctorArg3Type)
    {
        typedef QEXTPointerFunctor<void, int, double, int>::Function FunctionType3;
        CHECK("QEXTPointerFunctor3" == QEXTFunctorTrait<FunctionType3>().typeName());
        typedef void (*T_voidfunctor3)(int, int, int);
        CHECK("QEXTPointerFunctor3" == QEXTFunctorTrait<T_voidfunctor3>().typeName());
        typedef int (*T_intfunctor3)(double, double, int);
        CHECK("QEXTPointerFunctor3" == QEXTFunctorTrait<T_intfunctor3>().typeName());
    }

    TEST(qextFunctorTraitTest, testFunctorArg4Type)
    {
        typedef QEXTPointerFunctor<void, int, double, int, float>::Function FunctionType4;
        CHECK("QEXTPointerFunctor4" == QEXTFunctorTrait<FunctionType4>().typeName());
        typedef void (*T_voidfunctor4)(double, int, double, int);
        CHECK("QEXTPointerFunctor4" == QEXTFunctorTrait<T_voidfunctor4>().typeName());
        typedef int (*T_intfunctor4)(float, int, double, long);
        CHECK("QEXTPointerFunctor4" == QEXTFunctorTrait<T_intfunctor4>().typeName());
    }

    TEST(qextFunctorTraitTest, testFunctorArg5Type)
    {
        typedef QEXTPointerFunctor<void, int, double, int, float, std::string>::Function FunctionType5;
        CHECK("QEXTPointerFunctor5" == QEXTFunctorTrait<FunctionType5>().typeName());
        typedef void (*T_voidfunctor5)(int, int, int, int, std::string);
        CHECK("QEXTPointerFunctor5" == QEXTFunctorTrait<T_voidfunctor5>().typeName());
        typedef int (*T_intfunctor5)(double, double, int, int, long);
        CHECK("QEXTPointerFunctor5" == QEXTFunctorTrait<T_intfunctor5>().typeName());
    }

    TEST(qextFunctorTraitTest, testFunctorArg6Type)
    {
        typedef QEXTPointerFunctor<void, int, double, int, float, std::string, int>::Function FunctionType6;
        CHECK("QEXTPointerFunctor6" == QEXTFunctorTrait<FunctionType6>().typeName());
        typedef void (*T_voidfunctor6)(int, int, int, int, std::string, float);
        CHECK("QEXTPointerFunctor6" == QEXTFunctorTrait<T_voidfunctor6>().typeName());
        typedef int (*T_intfunctor6)(double, double, int, int, long, float);
        CHECK("QEXTPointerFunctor6" == QEXTFunctorTrait<T_intfunctor6>().typeName());
    }

    TEST(qextFunctorTraitTest, testFunctorArg7Type)
    {
        typedef QEXTPointerFunctor<void, int, double, int, float, std::string, int, double>::Function FunctionType7;
        CHECK("QEXTPointerFunctor7" == QEXTFunctorTrait<FunctionType7>().typeName());
        typedef void (*T_voidfunctor7)(int, int, int, int, std::string, float, int);
        CHECK("QEXTPointerFunctor7" == QEXTFunctorTrait<T_voidfunctor7>().typeName());
        typedef int (*T_intfunctor7)(double, double, int, int, long, float, int);
        CHECK("QEXTPointerFunctor7" == QEXTFunctorTrait<T_intfunctor7>().typeName());
    }

    TEST(qextFunctorTraitTest, testMemberFunctorArg0Type)
    {
        typedef QEXTMemberFunctor<void, Member>::Function MemFunctionType0;
        CHECK("QEXTMemberFunctor0" == QEXTFunctorTrait<MemFunctionType0>().typeName());
    }

    TEST(qextFunctorTraitTest, testConstMemberFunctorArg0Type)
    {
        typedef QEXTConstMemberFunctor<void, Member>::Function MemFunctionType0;
        CHECK("QEXTConstMemberFunctor0" == QEXTFunctorTrait<MemFunctionType0>().typeName());
    }

    TEST(qextFunctorTraitTest, testVolatileMemberFunctorArg0Type)
    {
        typedef QEXTVolatileMemberFunctor<void, Member>::Function MemFunctionType0;
        CHECK("QEXTVolatileMemberFunctor0" == QEXTFunctorTrait<MemFunctionType0>().typeName());
    }

    TEST(qextFunctorTraitTest, testConstVolatileMemberFunctorArg0Type)
    {
        typedef QEXTConstVolatileMemberFunctor<void, Member>::Function MemFunctionType0;
        CHECK("QEXTConstVolatileMemberFunctor0" == QEXTFunctorTrait<MemFunctionType0>().typeName());
    }

    TEST(qextFunctorTraitTest, testBoundMemberFunctorArg0Type)
    {
        typedef QEXTBoundMemberFunctor<void, Member>::Function MemFunctionType0;
        CHECK("QEXTMemberFunctor0" == QEXTFunctorTrait<MemFunctionType0>().typeName());
    }

    TEST(qextFunctorTraitTest, testBoundConstMemberFunctorArg0Type)
    {
        typedef QEXTBoundConstMemberFunctor<void, Member>::Function MemFunctionType0;
        CHECK("QEXTConstMemberFunctor0" == QEXTFunctorTrait<MemFunctionType0>().typeName());
    }

    TEST(qextFunctorTraitTest, testBoundVolatileMemberFunctorArg0Type)
    {
        typedef QEXTBoundVolatileMemberFunctor<void, Member>::Function MemFunctionType0;
        CHECK("QEXTVolatileMemberFunctor0" == QEXTFunctorTrait<MemFunctionType0>().typeName());
    }

    TEST(qextFunctorTraitTest, testBoundConstVolatileMemberFunctorArg0Type)
    {
        typedef QEXTBoundConstVolatileMemberFunctor<void, Member>::Function MemFunctionType0;
        CHECK("QEXTConstVolatileMemberFunctor0" == QEXTFunctorTrait<MemFunctionType0>().typeName());
    }

    TEST(qextFunctorTraitTest, testMemberFunctorArg1Type)
    {
        typedef QEXTMemberFunctor<void, Member, int>::Function MemFunctionType1;
        CHECK("QEXTMemberFunctor1" == QEXTFunctorTrait<MemFunctionType1>().typeName());
    }

    TEST(qextFunctorTraitTest, testConstMemberFunctorArg1Type)
    {
        typedef QEXTConstMemberFunctor<void, Member, int>::Function MemFunctionType1;
        CHECK("QEXTConstMemberFunctor1" == QEXTFunctorTrait<MemFunctionType1>().typeName());
    }

    TEST(qextFunctorTraitTest, testVolatileMemberFunctorArg1Type)
    {
        typedef QEXTVolatileMemberFunctor<void, Member, int>::Function MemFunctionType1;
        CHECK("QEXTVolatileMemberFunctor1" == QEXTFunctorTrait<MemFunctionType1>().typeName());
    }

    TEST(qextFunctorTraitTest, testConstVolatileMemberFunctorArg1Type)
    {
        typedef QEXTConstVolatileMemberFunctor<void, Member, int>::Function MemFunctionType1;
        CHECK("QEXTConstVolatileMemberFunctor1" == QEXTFunctorTrait<MemFunctionType1>().typeName());
    }

    TEST(qextFunctorTraitTest, testBoundMemberFunctorArg1Type)
    {
        typedef QEXTBoundMemberFunctor<void, Member, int>::Function MemFunctionType1;
        CHECK("QEXTMemberFunctor1" == QEXTFunctorTrait<MemFunctionType1>().typeName());
    }

    TEST(qextFunctorTraitTest, testBoundConstMemberFunctorArg1Type)
    {
        typedef QEXTBoundConstMemberFunctor<void, Member, int>::Function MemFunctionType1;
        CHECK("QEXTConstMemberFunctor1" == QEXTFunctorTrait<MemFunctionType1>().typeName());
    }

    TEST(qextFunctorTraitTest, testBoundVolatileMemberFunctorArg1Type)
    {
        typedef QEXTBoundVolatileMemberFunctor<void, Member, int>::Function MemFunctionType1;
        CHECK("QEXTVolatileMemberFunctor1" == QEXTFunctorTrait<MemFunctionType1>().typeName());
    }

    TEST(qextFunctorTraitTest, testBoundConstVolatileMemberFunctorArg1Type)
    {
        typedef QEXTBoundConstVolatileMemberFunctor<void, Member, int>::Function MemFunctionType1;
        CHECK("QEXTConstVolatileMemberFunctor1" == QEXTFunctorTrait<MemFunctionType1>().typeName());
    }

    TEST(qextFunctorTraitTest, testMemberFunctorArg2Type)
    {
        typedef QEXTMemberFunctor<void, Member, int, int>::Function MemFunctionType2;
        CHECK("QEXTMemberFunctor2" == QEXTFunctorTrait<MemFunctionType2>().typeName());
    }

    TEST(qextFunctorTraitTest, testConstMemberFunctorArg2Type)
    {
        typedef QEXTConstMemberFunctor<void, Member, int, int>::Function MemFunctionType2;
        CHECK("QEXTConstMemberFunctor2" == QEXTFunctorTrait<MemFunctionType2>().typeName());
    }

    TEST(qextFunctorTraitTest, testVolatileMemberFunctorArg2Type)
    {
        typedef QEXTVolatileMemberFunctor<void, Member, int, int>::Function MemFunctionType2;
        CHECK("QEXTVolatileMemberFunctor2" == QEXTFunctorTrait<MemFunctionType2>().typeName());
    }

    TEST(qextFunctorTraitTest, testConstVolatileMemberFunctorArg2Type)
    {
        typedef QEXTConstVolatileMemberFunctor<void, Member, int, int>::Function MemFunctionType2;
        CHECK("QEXTConstVolatileMemberFunctor2" == QEXTFunctorTrait<MemFunctionType2>().typeName());
    }

    TEST(qextFunctorTraitTest, testBoundMemberFunctorArg2Type)
    {
        typedef QEXTBoundMemberFunctor<void, Member, int, int>::Function MemFunctionType2;
        CHECK("QEXTMemberFunctor2" == QEXTFunctorTrait<MemFunctionType2>().typeName());
    }

    TEST(qextFunctorTraitTest, testBoundConstMemberFunctorArg2Type)
    {
        typedef QEXTBoundConstMemberFunctor<void, Member, int, int>::Function MemFunctionType2;
        CHECK("QEXTConstMemberFunctor2" == QEXTFunctorTrait<MemFunctionType2>().typeName());
    }

    TEST(qextFunctorTraitTest, testBoundVolatileMemberFunctorArg2Type)
    {
        typedef QEXTBoundVolatileMemberFunctor<void, Member, int, int>::Function MemFunctionType2;
        CHECK("QEXTVolatileMemberFunctor2" == QEXTFunctorTrait<MemFunctionType2>().typeName());
    }

    TEST(qextFunctorTraitTest, testBoundConstVolatileMemberFunctorArg2Type)
    {
        typedef QEXTBoundConstVolatileMemberFunctor<void, Member, int, int>::Function MemFunctionType2;
        CHECK("QEXTConstVolatileMemberFunctor2" == QEXTFunctorTrait<MemFunctionType2>().typeName());
    }

    TEST(qextFunctorTraitTest, testMemberFunctorArg3Type)
    {
        typedef QEXTMemberFunctor<void, Member, int, int, int>::Function MemFunctionType3;
        CHECK("QEXTMemberFunctor3" == QEXTFunctorTrait<MemFunctionType3>().typeName());
    }

    TEST(qextFunctorTraitTest, testConstMemberFunctorArg3Type)
    {
        typedef QEXTConstMemberFunctor<void, Member, int, int, int>::Function MemFunctionType3;
        CHECK("QEXTConstMemberFunctor3" == QEXTFunctorTrait<MemFunctionType3>().typeName());
    }

    TEST(qextFunctorTraitTest, testVolatileMemberFunctorArg3Type)
    {
        typedef QEXTVolatileMemberFunctor<void, Member, int, int, int>::Function MemFunctionType3;
        CHECK("QEXTVolatileMemberFunctor3" == QEXTFunctorTrait<MemFunctionType3>().typeName());
    }

    TEST(qextFunctorTraitTest, testConstVolatileMemberFunctorArg3Type)
    {
        typedef QEXTConstVolatileMemberFunctor<void, Member, int, int, int>::Function MemFunctionType3;
        CHECK("QEXTConstVolatileMemberFunctor3" == QEXTFunctorTrait<MemFunctionType3>().typeName());
    }

    TEST(qextFunctorTraitTest, testBoundMemberFunctorArg3Type)
    {
        typedef QEXTBoundMemberFunctor<void, Member, int, int, int>::Function MemFunctionType3;
        CHECK("QEXTMemberFunctor3" == QEXTFunctorTrait<MemFunctionType3>().typeName());
    }

    TEST(qextFunctorTraitTest, testBoundConstMemberFunctorArg3Type)
    {
        typedef QEXTBoundConstMemberFunctor<void, Member, int, int, int>::Function MemFunctionType3;
        CHECK("QEXTConstMemberFunctor3" == QEXTFunctorTrait<MemFunctionType3>().typeName());
    }

    TEST(qextFunctorTraitTest, testBoundVolatileMemberFunctorArg3Type)
    {
        typedef QEXTBoundVolatileMemberFunctor<void, Member, int, int, int>::Function MemFunctionType3;
        CHECK("QEXTVolatileMemberFunctor3" == QEXTFunctorTrait<MemFunctionType3>().typeName());
    }

    TEST(qextFunctorTraitTest, testBoundConstVolatileMemberFunctorArg3Type)
    {
        typedef QEXTBoundConstVolatileMemberFunctor<void, Member, int, int, int>::Function MemFunctionType3;
        CHECK("QEXTConstVolatileMemberFunctor3" == QEXTFunctorTrait<MemFunctionType3>().typeName());
    }

    TEST(qextFunctorTraitTest, testMemberFunctorArg4Type)
    {
        typedef QEXTMemberFunctor<void, Member, int, int, int, int>::Function MemFunctionType4;
        CHECK("QEXTMemberFunctor4" == QEXTFunctorTrait<MemFunctionType4>().typeName());
    }

    TEST(qextFunctorTraitTest, testConstMemberFunctorArg4Type)
    {
        typedef QEXTConstMemberFunctor<void, Member, int, int, int, int>::Function MemFunctionType4;
        CHECK("QEXTConstMemberFunctor4" == QEXTFunctorTrait<MemFunctionType4>().typeName());
    }

    TEST(qextFunctorTraitTest, testVolatileMemberFunctorArg4Type)
    {
        typedef QEXTVolatileMemberFunctor<void, Member, int, int, int, int>::Function MemFunctionType4;
        CHECK("QEXTVolatileMemberFunctor4" == QEXTFunctorTrait<MemFunctionType4>().typeName());
    }

    TEST(qextFunctorTraitTest, testConstVolatileMemberFunctorArg4Type)
    {
        typedef QEXTConstVolatileMemberFunctor<void, Member, int, int, int, int>::Function MemFunctionType4;
        CHECK("QEXTConstVolatileMemberFunctor4" == QEXTFunctorTrait<MemFunctionType4>().typeName());
    }

    TEST(qextFunctorTraitTest, testBoundMemberFunctorArg4Type)
    {
        typedef QEXTBoundMemberFunctor<void, Member, int, int, int, int>::Function MemFunctionType4;
        CHECK("QEXTMemberFunctor4" == QEXTFunctorTrait<MemFunctionType4>().typeName());
    }

    TEST(qextFunctorTraitTest, testBoundConstMemberFunctorArg4Type)
    {
        typedef QEXTBoundConstMemberFunctor<void, Member, int, int, int, int>::Function MemFunctionType4;
        CHECK("QEXTConstMemberFunctor4" == QEXTFunctorTrait<MemFunctionType4>().typeName());
    }

    TEST(qextFunctorTraitTest, testBoundVolatileMemberFunctorArg4ype)
    {
        typedef QEXTBoundVolatileMemberFunctor<void, Member, int, int, int, int>::Function MemFunctionType4;
        CHECK("QEXTVolatileMemberFunctor4" == QEXTFunctorTrait<MemFunctionType4>().typeName());
    }

    TEST(qextFunctorTraitTest, testBoundConstVolatileMemberFunctorArg4Type)
    {
        typedef QEXTBoundConstVolatileMemberFunctor<void, Member, int, int, int, int>::Function MemFunctionType4;
        CHECK("QEXTConstVolatileMemberFunctor4" == QEXTFunctorTrait<MemFunctionType4>().typeName());
    }

    TEST(qextFunctorTraitTest, testMemberFunctorArg5Type)
    {
        typedef QEXTMemberFunctor<void, Member, int, int, int, int, int>::Function MemFunctionType5;
        CHECK("QEXTMemberFunctor5" == QEXTFunctorTrait<MemFunctionType5>().typeName());
    }

    TEST(qextFunctorTraitTest, testConstMemberFunctorArg5Type)
    {
        typedef QEXTConstMemberFunctor<void, Member, int, int, int, int, int>::Function MemFunctionType5;
        CHECK("QEXTConstMemberFunctor5" == QEXTFunctorTrait<MemFunctionType5>().typeName());
    }

    TEST(qextFunctorTraitTest, testVolatileMemberFunctorArg5Type)
    {
        typedef QEXTVolatileMemberFunctor<void, Member, int, int, int, int, int>::Function MemFunctionType5;
        CHECK("QEXTVolatileMemberFunctor5" == QEXTFunctorTrait<MemFunctionType5>().typeName());
    }

    TEST(qextFunctorTraitTest, testConstVolatileMemberFunctorArg5Type)
    {
        typedef QEXTConstVolatileMemberFunctor<void, Member, int, int, int, int, int>::Function MemFunctionType5;
        CHECK("QEXTConstVolatileMemberFunctor5" == QEXTFunctorTrait<MemFunctionType5>().typeName());
    }

    TEST(qextFunctorTraitTest, testBoundMemberFunctorArg5Type)
    {
        typedef QEXTBoundMemberFunctor<void, Member, int, int, int, int, int>::Function MemFunctionType5;
        CHECK("QEXTMemberFunctor5" == QEXTFunctorTrait<MemFunctionType5>().typeName());
    }

    TEST(qextFunctorTraitTest, testBoundConstMemberFunctorArg5Type)
    {
        typedef QEXTBoundConstMemberFunctor<void, Member, int, int, int, int, int>::Function MemFunctionType5;
        CHECK("QEXTConstMemberFunctor5" == QEXTFunctorTrait<MemFunctionType5>().typeName());
    }

    TEST(qextFunctorTraitTest, testBoundVolatileMemberFunctorArg5Type)
    {
        typedef QEXTBoundVolatileMemberFunctor<void, Member, int, int, int, int, int>::Function MemFunctionType5;
        CHECK("QEXTVolatileMemberFunctor5" == QEXTFunctorTrait<MemFunctionType5>().typeName());
    }

    TEST(qextFunctorTraitTest, testBoundConstVolatileMemberFunctorArg5Type)
    {
        typedef QEXTBoundConstVolatileMemberFunctor<void, Member, int, int, int, int, int>::Function MemFunctionType5;
        CHECK("QEXTConstVolatileMemberFunctor5" == QEXTFunctorTrait<MemFunctionType5>().typeName());
    }

    TEST(qextFunctorTraitTest, testMemberFunctorArg6Type)
    {
        typedef QEXTMemberFunctor<void, Member, int, int, int, int, int, int>::Function MemFunctionType6;
        CHECK("QEXTMemberFunctor6" == QEXTFunctorTrait<MemFunctionType6>().typeName());
    }

    TEST(qextFunctorTraitTest, testConstMemberFunctorArg6Type)
    {
        typedef QEXTConstMemberFunctor<void, Member, int, int, int, int, int, int>::Function MemFunctionType6;
        CHECK("QEXTConstMemberFunctor6" == QEXTFunctorTrait<MemFunctionType6>().typeName());
    }

    TEST(qextFunctorTraitTest, testVolatileMemberFunctorArg6Type)
    {
        typedef QEXTVolatileMemberFunctor<void, Member, int, int, int, int, int, int>::Function MemFunctionType6;
        CHECK("QEXTVolatileMemberFunctor6" == QEXTFunctorTrait<MemFunctionType6>().typeName());
    }

    TEST(qextFunctorTraitTest, testConstVolatileMemberFunctorArg6Type)
    {
        typedef QEXTConstVolatileMemberFunctor<void, Member, int, int, int, int, int, int>::Function MemFunctionType6;
        CHECK("QEXTConstVolatileMemberFunctor6" == QEXTFunctorTrait<MemFunctionType6>().typeName());
    }

    TEST(qextFunctorTraitTest, testBoundMemberFunctorArg6Type)
    {
        typedef QEXTBoundMemberFunctor<void, Member, int, int, int, int, int, int>::Function MemFunctionType6;
        CHECK("QEXTMemberFunctor6" == QEXTFunctorTrait<MemFunctionType6>().typeName());
    }

    TEST(qextFunctorTraitTest, testBoundConstMemberFunctorArg6Type)
    {
        typedef QEXTBoundConstMemberFunctor<void, Member, int, int, int, int, int, int>::Function MemFunctionType6;
        CHECK("QEXTConstMemberFunctor6" == QEXTFunctorTrait<MemFunctionType6>().typeName());
    }

    TEST(qextFunctorTraitTest, testBoundVolatileMemberFunctorArg6Type)
    {
        typedef QEXTBoundVolatileMemberFunctor<void, Member, int, int, int, int, int, int>::Function MemFunctionType6;
        CHECK("QEXTVolatileMemberFunctor6" == QEXTFunctorTrait<MemFunctionType6>().typeName());
    }

    TEST(qextFunctorTraitTest, testBoundConstVolatileMemberFunctorArg6Type)
    {
        typedef QEXTBoundConstVolatileMemberFunctor<void, Member, int, int, int, int, int, int>::Function MemFunctionType6;
        CHECK("QEXTConstVolatileMemberFunctor6" == QEXTFunctorTrait<MemFunctionType6>().typeName());
    }

    TEST(qextFunctorTraitTest, testMemberFunctorArg7Type)
    {
        typedef QEXTMemberFunctor<void, Member, int, int, int, int, int, int, int>::Function MemFunctionType7;
        CHECK("QEXTMemberFunctor7" == QEXTFunctorTrait<MemFunctionType7>().typeName());
    }

    TEST(qextFunctorTraitTest, testConstMemberFunctorArg7Type)
    {
        typedef QEXTConstMemberFunctor<void, Member, int, int, int, int, int, int, int>::Function MemFunctionType7;
        CHECK("QEXTConstMemberFunctor7" == QEXTFunctorTrait<MemFunctionType7>().typeName());
    }

    TEST(qextFunctorTraitTest, testVolatileMemberFunctorArg7Type)
    {
        typedef QEXTVolatileMemberFunctor<void, Member, int, int, int, int, int, int, int>::Function MemFunctionType7;
        CHECK("QEXTVolatileMemberFunctor7" == QEXTFunctorTrait<MemFunctionType7>().typeName());
    }

    TEST(qextFunctorTraitTest, testConstVolatileMemberFunctorArg7Type)
    {
        typedef QEXTConstVolatileMemberFunctor<void, Member, int, int, int, int, int, int, int>::Function MemFunctionType7;
        CHECK("QEXTConstVolatileMemberFunctor7" == QEXTFunctorTrait<MemFunctionType7>().typeName());
    }

    TEST(qextFunctorTraitTest, testBoundMemberFunctorArg7Type)
    {
        typedef QEXTBoundMemberFunctor<void, Member, int, int, int, int, int, int, int>::Function MemFunctionType7;
        CHECK("QEXTMemberFunctor7" == QEXTFunctorTrait<MemFunctionType7>().typeName());
    }

    TEST(qextFunctorTraitTest, testBoundConstMemberFunctorArg7Type)
    {
        typedef QEXTBoundConstMemberFunctor<void, Member, int, int, int, int, int, int, int>::Function MemFunctionType7;
        CHECK("QEXTConstMemberFunctor7" == QEXTFunctorTrait<MemFunctionType7>().typeName());
    }

    TEST(qextFunctorTraitTest, testBoundVolatileMemberFunctorArg7Type)
    {
        typedef QEXTBoundVolatileMemberFunctor<void, Member, int, int, int, int, int, int, int>::Function MemFunctionType7;
        CHECK("QEXTVolatileMemberFunctor7" == QEXTFunctorTrait<MemFunctionType7>().typeName());
    }

    TEST(qextFunctorTraitTest, testBoundConstVolatileMemberFunctorArg7Type)
    {
        typedef QEXTBoundConstVolatileMemberFunctor<void, Member, int, int, int, int, int, int, int>::Function MemFunctionType7;
        CHECK("QEXTConstVolatileMemberFunctor7" == QEXTFunctorTrait<MemFunctionType7>().typeName());
    }

} // namespace qextFunctorTraitTest

#endif // QEXTFUNCTORTRAITTEST_H
